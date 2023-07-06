/* 
 * MolecularGraphMatchExpressionFunctions.cpp 
 *
 * This file is part of the Chemical Data Processing Toolkit
 *
 * Copyright (C) 2003 Thomas Seidel <thomas.seidel@univie.ac.at>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this library; see the file COPYING. If not, write to
 * the Free Software Foundation, Inc., 59 Temple Place - Suite 330,
 * Boston, MA 02111-1307, USA.
 */


#include "StaticInit.hpp"

#include "CDPL/Chem/MolecularGraphFunctions.hpp"
#include "CDPL/Chem/AtomFunctions.hpp"
#include "CDPL/Chem/BondFunctions.hpp"
#include "CDPL/Chem/Atom.hpp"
#include "CDPL/Chem/Bond.hpp"
#include "CDPL/Chem/MolecularGraphProperty.hpp"
#include "CDPL/Chem/MolecularGraphMatchConstraint.hpp"
#include "CDPL/Chem/NOTMatchExpression.hpp"
#include "CDPL/Chem/ANDMatchExpressionList.hpp"
#include "CDPL/Chem/ORMatchExpressionList.hpp"
#include "CDPL/Chem/MolecularGraphComponentGroupingMatchExpression.hpp"


using namespace CDPL; 


namespace
{

    Chem::MatchExpression<Chem::MolecularGraph>::SharedPointer 
    createMatchExpressionList(const Chem::MolecularGraph& molgraph, const Chem::MatchConstraint& constraint);

    Chem::MatchExpression<Chem::MolecularGraph>::SharedPointer 
    createMatchExpression(const Chem::MolecularGraph& molgraph, const Chem::MatchConstraintList& constr_list)
    {
        using namespace Chem;

        MatchExpressionList<MolecularGraph>::SharedPointer expr_list_ptr;

        if (constr_list.getType() == MatchConstraintList::AND_LIST || 
            constr_list.getType() == MatchConstraintList::NOT_AND_LIST)
            expr_list_ptr.reset(new ANDMatchExpressionList<MolecularGraph>());
        else
            expr_list_ptr.reset(new ORMatchExpressionList<MolecularGraph>());

        MatchConstraintList::ConstElementIterator constr_end = constr_list.getElementsEnd();

        for (MatchConstraintList::ConstElementIterator it = constr_list.getElementsBegin(); it != constr_end; ++it) {
            const MatchConstraint& constraint = *it;

            if (constraint.getID() == MolecularGraphMatchConstraint::CONSTRAINT_LIST) {
                MatchExpression<MolecularGraph>::SharedPointer expr_ptr = createMatchExpressionList(molgraph, constraint);
            
                if (expr_ptr)
                    expr_list_ptr->addElement(expr_ptr);

                continue;
            }

            if (constraint.getID() != MolecularGraphMatchConstraint::COMPONENT_GROUPING)
                continue;

            if (constraint.getRelation() != MatchConstraint::EQUAL)
                continue;

            const FragmentList::SharedPointer& comp_groups = 
                molgraph.getProperty<FragmentList::SharedPointer>(MolecularGraphProperty::COMPONENT_GROUPS);

            if (comp_groups->getSize() == 0)
                continue;

            MatchExpression<MolecularGraph>::SharedPointer expr_ptr(new MolecularGraphComponentGroupingMatchExpression(comp_groups));
                
            expr_list_ptr->addElement(expr_ptr);
        }

        MatchExpression<MolecularGraph>::SharedPointer expr_ptr;

        if (expr_list_ptr->getSize() == 0)
            expr_ptr.reset(new MatchExpression<MolecularGraph>());
    
        else {
            if (expr_list_ptr->getSize() == 1)
                expr_ptr = expr_list_ptr->getBase().getFirstElement();
            else
                expr_ptr = expr_list_ptr;

            if (constr_list.getType() == MatchConstraintList::NOT_AND_LIST || 
                constr_list.getType() == MatchConstraintList::NOT_OR_LIST) 
                expr_ptr.reset(new NOTMatchExpression<MolecularGraph>(expr_ptr));
        }

        return expr_ptr; 
    }

    Chem::MatchExpression<Chem::MolecularGraph>::SharedPointer 
    createMatchExpressionList(const Chem::MolecularGraph& molgraph, const Chem::MatchConstraint& constraint)
    {
        using namespace Chem;

        if (constraint.getRelation() != MatchConstraint::EQUAL && 
            constraint.getRelation() != MatchConstraint::NOT_EQUAL)
            return MatchExpression<MolecularGraph>::SharedPointer();

        const MatchConstraintList& constr_list = 
            *constraint.getValue<MatchConstraintList::SharedPointer>();

        MatchExpression<MolecularGraph>::SharedPointer expr_ptr = createMatchExpression(molgraph, constr_list);

        if (!expr_ptr)
            return expr_ptr;

        if (constraint.getRelation() == MatchConstraint::NOT_EQUAL)
            expr_ptr.reset(new NOTMatchExpression<MolecularGraph>(expr_ptr));

        return expr_ptr;
    }
}


Chem::MatchExpression<Chem::MolecularGraph>::SharedPointer Chem::generateMatchExpression(const MolecularGraph& molgraph)
{
    MatchExpression<MolecularGraph>::SharedPointer expr_ptr = createMatchExpression(molgraph, *getMatchConstraints(molgraph));

    if (!expr_ptr)
        expr_ptr.reset(new MatchExpression<MolecularGraph>());

    return expr_ptr; 
}
    
Chem::MatchExpression<Chem::MolecularGraph>::SharedPointer Chem::generateMatchExpression(MolecularGraph& molgraph, bool overwrite)
{
    if (!overwrite) {
        Base::Any prev_expr = molgraph.getProperty(MolecularGraphProperty::MATCH_EXPRESSION, false);
    
        if (!prev_expr.isEmpty())
            return prev_expr.getData<MatchExpression<MolecularGraph>::SharedPointer>();
    }

    MatchExpression<MolecularGraph>::SharedPointer expr_ptr = generateMatchExpression(molgraph);

    setMatchExpression(molgraph, expr_ptr);

    return expr_ptr; 
}

void Chem::generateMatchExpressions(MolecularGraph& molgraph, bool overwrite)
{
    generateMatchExpression(molgraph, overwrite);

    MolecularGraph::AtomIterator atoms_end = molgraph.getAtomsEnd();

    for (MolecularGraph::AtomIterator a_it = molgraph.getAtomsBegin(); a_it != atoms_end; ++a_it) {
        Atom& atom = *a_it;
 
        if (!overwrite && hasMatchExpression(atom))
            continue;

        setMatchExpression(atom, generateMatchExpression(atom, molgraph));
    }

    MolecularGraph::BondIterator bonds_end = molgraph.getBondsEnd();

    for (MolecularGraph::BondIterator b_it = molgraph.getBondsBegin(); b_it != bonds_end; ++b_it) {
        Bond& bond = *b_it;
 
        if (!overwrite && hasMatchExpression(bond))
            continue;

        setMatchExpression(bond, generateMatchExpression(bond, molgraph));
    }
}
