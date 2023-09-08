/* 
 * MatchExpressionListExport.cpp 
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

#include "CDPL/Chem/MatchExpressionList.hpp"
#include "CDPL/Chem/AtomBondMapping.hpp"
#include "CDPL/Chem/Atom.hpp"
#include "CDPL/Chem/Bond.hpp"
#include "CDPL/Chem/MolecularGraph.hpp"
#include "CDPL/Chem/Reaction.hpp"

#include "Util/ArrayVisitor.hpp"
#include "Base/CopyAssOp.hpp"

#include "ClassExports.hpp"


namespace
{

    template <typename ObjType1, typename ObjType2 = void>
    struct MatchExpressionListExport
    {

        MatchExpressionListExport(const char* name) {
            using namespace boost;
            using namespace CDPL;

            python::class_<Chem::MatchExpressionList<ObjType1, ObjType2>, 
                typename Chem::MatchExpressionList<ObjType1, ObjType2>::SharedPointer,
                python::bases<Chem::MatchExpression<ObjType1, ObjType2> > >(name, python::no_init)
                .def(python::init<>(python::arg("self")))
                .def(python::init<const Chem::MatchExpressionList<ObjType1, ObjType2>&>((python::arg("self"), python::arg("expr")))
                     [python::with_custodian_and_ward<1, 2>()])
                .def(CDPLPythonUtil::ArrayVisitor<Chem::MatchExpressionList<ObjType1, ObjType2>, 
                     python::return_value_policy<python::copy_non_const_reference, 
                     python::with_custodian_and_ward_postcall<0, 1> >, 
                     python::with_custodian_and_ward<1, 2>, python::with_custodian_and_ward<1, 3>, 
                     python::with_custodian_and_ward<1, 4> >())
                .def("assign", CDPLPythonBase::copyAssOp(&Chem::MatchExpressionList<ObjType1, ObjType2>::operator=),
                     (python::arg("self"), python::arg("expr")),
                     python::return_self<python::with_custodian_and_ward<1, 2> >())
                .def("__eq__", &Util::operator==<typename Chem::MatchExpressionList<ObjType1, ObjType2>::BaseType::ElementType>, 
                     (python::arg("self"), python::arg("expr")))
                .def("__ne__", &Util::operator!=<typename Chem::MatchExpressionList<ObjType1, ObjType2>::BaseType::ElementType>,
                     (python::arg("self"), python::arg("expr")));
        }
    };
}


void CDPLPythonChem::exportMatchExpressionLists()
{
    using namespace boost;
    using namespace CDPL;

    MatchExpressionListExport<Chem::Atom, Chem::MolecularGraph>("AtomMatchExpressionList");
    MatchExpressionListExport<Chem::Bond, Chem::MolecularGraph>("BondMatchExpressionList");
    MatchExpressionListExport<Chem::MolecularGraph>("MolecularGraphMatchExpressionList");
    MatchExpressionListExport<Chem::Reaction>("ReactionMatchExpressionList");
}
