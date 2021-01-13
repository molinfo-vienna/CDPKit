/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * ReactionMatchExpressionFunctions.cpp 
 *
 * This file is part of the Chemical Data Processing Toolkit
 *
 * Copyright (C) 2003-2020 Thomas A. Seidel <thomas.seidel@univie.ac.at>
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

#include <algorithm>

#include <boost/bind.hpp>

#include "CDPL/Chem/ReactionFunctions.hpp"
#include "CDPL/Chem/MolecularGraphFunctions.hpp"
#include "CDPL/Chem/Reaction.hpp"
#include "CDPL/Chem/ReactionProperty.hpp"
#include "CDPL/Chem/ReactionMatchConstraint.hpp"
#include "CDPL/Chem/NOTMatchExpression.hpp"
#include "CDPL/Chem/ANDMatchExpressionList.hpp"
#include "CDPL/Chem/ORMatchExpressionList.hpp"
#include "CDPL/Chem/ReactionComponentGroupingMatchExpression.hpp"
#include "CDPL/Chem/ReactionAtomMappingMatchExpression.hpp"


using namespace CDPL; 


namespace
{

	Chem::MatchExpression<Chem::Reaction>::SharedPointer 
	createMatchExpressionList(const Chem::Reaction& rxn, const Chem::MatchConstraint& constraint);

	Chem::MatchExpression<Chem::Reaction>::SharedPointer 
	createMatchExpression(const Chem::Reaction& rxn, const Chem::MatchConstraintList& constr_list)
	{
		using namespace Chem;

		MatchExpressionList<Reaction>::SharedPointer expr_list_ptr;

		if (constr_list.getType() == MatchConstraintList::AND_LIST || 
			constr_list.getType() == MatchConstraintList::NOT_AND_LIST)
			expr_list_ptr.reset(new ANDMatchExpressionList<Reaction>());
		else
			expr_list_ptr.reset(new ORMatchExpressionList<Reaction>());

		MatchConstraintList::ConstElementIterator constr_end = constr_list.getElementsEnd();

		for (MatchConstraintList::ConstElementIterator it = constr_list.getElementsBegin(); it != constr_end; ++it) {
			const MatchConstraint& constraint = *it;

			if (constraint.getID() == ReactionMatchConstraint::COMPONENT_GROUPING && 
				constraint.getRelation() == MatchConstraint::EQUAL) {

				const FragmentList::SharedPointer& comp_groups = 
					rxn.getProperty<FragmentList::SharedPointer>(ReactionProperty::COMPONENT_GROUPS);

				if (comp_groups->getSize() == 0)
					continue;

				MatchExpression<Reaction>::SharedPointer expr_ptr(new ReactionComponentGroupingMatchExpression(comp_groups));
				
				expr_list_ptr->addElement(expr_ptr);
				continue;
			}

			if (constraint.getID() == ReactionMatchConstraint::ATOM_MAPPING && 
				constraint.getRelation() == MatchConstraint::EQUAL) {

				const AtomMapping::SharedPointer& atom_mapping = 
					rxn.getProperty<AtomMapping::SharedPointer>(ReactionProperty::ATOM_MAPPING);

				if (atom_mapping->getSize() == 0)
					continue;

				MatchExpression<Reaction>::SharedPointer expr_ptr(new ReactionAtomMappingMatchExpression(atom_mapping));

				expr_list_ptr->addElement(expr_ptr);
				continue;
			}

			if (constraint.getID() == ReactionMatchConstraint::CONSTRAINT_LIST) {
				MatchExpression<Reaction>::SharedPointer expr_ptr = createMatchExpressionList(rxn, constraint);
			
				if (expr_ptr)
					expr_list_ptr->addElement(expr_ptr);
			}
		}

		MatchExpression<Reaction>::SharedPointer expr_ptr;

		if (expr_list_ptr->getSize() == 0)
			expr_ptr.reset(new MatchExpression<Reaction>());
	
		else {
			if (expr_list_ptr->getSize() == 1)
				expr_ptr = expr_list_ptr->getBase().getFirstElement();
			else
				expr_ptr = expr_list_ptr;

			if (constr_list.getType() == MatchConstraintList::NOT_AND_LIST || 
				constr_list.getType() == MatchConstraintList::NOT_OR_LIST) 
				expr_ptr.reset(new NOTMatchExpression<Reaction>(expr_ptr));
		}

		return expr_ptr; 
	}

	Chem::MatchExpression<Chem::Reaction>::SharedPointer 
	createMatchExpressionList(const Chem::Reaction& rxn, const Chem::MatchConstraint& constraint)
	{
		using namespace Chem;

		if (constraint.getRelation() != MatchConstraint::EQUAL && 
			constraint.getRelation() != MatchConstraint::NOT_EQUAL)
			return MatchExpression<Reaction>::SharedPointer();

		const MatchConstraintList& constr_list = 
			*constraint.getValue<MatchConstraintList::SharedPointer>();
		MatchExpression<Reaction>::SharedPointer expr_ptr = createMatchExpression(rxn, constr_list);

		if (!expr_ptr)
			return expr_ptr;

		if (constraint.getRelation() == MatchConstraint::NOT_EQUAL)
			expr_ptr.reset(new NOTMatchExpression<Reaction>(expr_ptr));

		return expr_ptr;
	}
}


Chem::MatchExpression<Chem::Reaction>::SharedPointer Chem::buildMatchExpression(const Reaction& rxn)
{
	MatchExpression<Reaction>::SharedPointer expr_ptr = createMatchExpression(rxn, *getMatchConstraints(rxn));

	if (!expr_ptr)
		expr_ptr.reset(new MatchExpression<Reaction>());

	return expr_ptr; 
}

Chem::MatchExpression<Chem::Reaction>::SharedPointer Chem::buildMatchExpression(Reaction& rxn, bool overwrite)
{
	if (!overwrite) {
		Base::Variant prev_expr = rxn.getProperty(ReactionProperty::MATCH_EXPRESSION, false);
	
		if (!prev_expr.isEmpty())
			return prev_expr.getData<MatchExpression<Reaction>::SharedPointer>();
	}

	MatchExpression<Reaction>::SharedPointer expr_ptr = buildMatchExpression(rxn);

	setMatchExpression(rxn, expr_ptr);

	return expr_ptr; 
}
	
void Chem::buildMatchExpressions(Reaction& rxn, bool overwrite)
{
	buildMatchExpression(rxn, overwrite);

	std::for_each(rxn.getComponentsBegin(), rxn.getComponentsEnd(),
				  boost::bind(static_cast<void (*)(MolecularGraph&, bool)>(&buildMatchExpressions),
							  _1, overwrite));
}
