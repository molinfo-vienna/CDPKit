/* 
 * NOTMatchExpressionExport.cpp 
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


#include <boost/python.hpp>

#include "CDPL/Chem/NOTMatchExpression.hpp"
#include "CDPL/Chem/AtomBondMapping.hpp"
#include "CDPL/Chem/Atom.hpp"
#include "CDPL/Chem/Bond.hpp"
#include "CDPL/Chem/MolecularGraph.hpp"
#include "CDPL/Chem/Reaction.hpp"

#include "Base/CopyAssOp.hpp"

#include "ClassExports.hpp"


namespace
{

    template <typename ObjType1, typename ObjType2 = void>
    struct NOTMatchExprExport
    {

        NOTMatchExprExport(const char* name) {
            using namespace boost;
            using namespace CDPL;

            python::class_<Chem::NOTMatchExpression<ObjType1, ObjType2>, 
                typename Chem::NOTMatchExpression<ObjType1, ObjType2>::SharedPointer, 
                python::bases<Chem::MatchExpression<ObjType1, ObjType2> > >(name, python::no_init)
                .def(python::init<const Chem::NOTMatchExpression<ObjType1, ObjType2>&>((python::arg("self"), python::arg("expr_ptr")))
                     [python::with_custodian_and_ward<1, 2>()])
                .def(python::init<const typename Chem::MatchExpression<ObjType1, ObjType2>::SharedPointer&>((python::arg("self"), python::arg("expr_ptr")))
                     [python::with_custodian_and_ward<1, 2>()])
                .def("assign", CDPLPythonBase::copyAssOp(&Chem::NOTMatchExpression<ObjType1, ObjType2>::operator=),
                     (python::arg("self"), python::arg("expression")), 
                     python::return_self<python::with_custodian_and_ward<1, 2> >());
        }
    };
}


void CDPLPythonChem::exportNOTMatchExpressions()
{
    using namespace boost;
    using namespace CDPL;

    NOTMatchExprExport<Chem::Atom, Chem::MolecularGraph>("NOTAtomMatchExpression");
    NOTMatchExprExport<Chem::Bond, Chem::MolecularGraph>("NOTBondMatchExpression");
    NOTMatchExprExport<Chem::MolecularGraph>("NOTMolecularGraphMatchExpression");
    NOTMatchExprExport<Chem::Reaction>("NOTReactionMatchExpression");
}
