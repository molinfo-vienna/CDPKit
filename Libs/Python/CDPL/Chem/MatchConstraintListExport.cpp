/* 
 * MatchConstraintListExport.cpp 
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


#include <sstream>

#include <boost/python.hpp>

#include "CDPL/Chem/MatchConstraintList.hpp"

#include "Util/ArrayVisitor.hpp"
#include "Base/CopyAssOp.hpp"

#include "ClassExports.hpp"


namespace
{

    const CDPL::Base::Any& getConstraintValue(const CDPL::Chem::MatchConstraint& constr) 
    {
        return constr.getValue();
    }

    std::string toString(const CDPL::Chem::MatchConstraintList& list)
    {
        std::ostringstream oss;

        oss << "CDPL.Chem.MatchConstraintList(";
        
        if (!list.isEmpty())
            oss << "...";

        oss << ')';
        
        return oss.str();
    }
}


void CDPLPythonChem::exportMatchConstraintList()
{
    using namespace CDPL;
    using namespace boost;

    void (Chem::MatchConstraintList::*addElementFunc1)(unsigned int, Chem::MatchConstraint::Relation) 
        = &Chem::MatchConstraintList::addElement;
    void (Chem::MatchConstraintList::*addElementFunc2)(unsigned int, Chem::MatchConstraint::Relation, const Base::Any&) 
        = &Chem::MatchConstraintList::addElement<const Base::Any&>;

    {
        python::class_<Chem::MatchConstraint> mc_cls("MatchConstraint", python::no_init);
        python::scope scope = mc_cls;

        python::enum_<Chem::MatchConstraint::Relation>("Relation")
            .value("ANY", Chem::MatchConstraint::ANY)
            .value("LESS", Chem::MatchConstraint::LESS)
            .value("EQUAL", Chem::MatchConstraint::EQUAL)
            .value("GREATER", Chem::MatchConstraint::GREATER)
            .value("LESS_OR_EQUAL", Chem::MatchConstraint::LESS_OR_EQUAL)
            .value("GREATER_OR_EQUAL", Chem::MatchConstraint::GREATER_OR_EQUAL)
            .value("NOT_EQUAL", Chem::MatchConstraint::NOT_EQUAL)
            .export_values();

        mc_cls
            .def(python::init<const Chem::MatchConstraint&>((python::arg("self"), python::arg("constr"))))
            .def(python::init<unsigned int, Chem::MatchConstraint::Relation>((python::arg("self"),
                                                                              python::arg("id"),
                                                                              python::arg("rel"))))
            .def(python::init<unsigned int, Chem::MatchConstraint::Relation, const Base::Any&>((python::arg("self"),
                                                                                                python::arg("id"),
                                                                                                python::arg("rel"),
                                                                                                python::arg("val"))))
            .def("assign", CDPLPythonBase::copyAssOp(&Chem::MatchConstraint::operator=), (python::arg("self"), python::arg("constr")),
                 python::return_self<>())
            .def("getID", &Chem::MatchConstraint::getID, python::arg("self"))
            .def("setID", &Chem::MatchConstraint::setID, (python::arg("self"), python::arg("id")))
            .def("getRelation", &Chem::MatchConstraint::getRelation, python::arg("self"))
            .def("setRelation", &Chem::MatchConstraint::setRelation, (python::arg("self"), python::arg("rel")))
            .def("getValue", &getConstraintValue, python::arg("self"),
                 python::return_value_policy<python::copy_const_reference>())
            .def("setValue", &Chem::MatchConstraint::setValue<const Base::Any&>, (python::arg("self"), python::arg("val")))
            .def("hasValue", &Chem::MatchConstraint::hasValue, python::arg("self"))
            .add_property("id", &Chem::MatchConstraint::getID, &Chem::MatchConstraint::setID)
            .add_property("relation", &Chem::MatchConstraint::getRelation, &Chem::MatchConstraint::setRelation)
            .add_property("value", python::make_function(&getConstraintValue, python::return_value_policy<python::copy_const_reference>()),
                          &Chem::MatchConstraint::setValue<const Base::Any&>);
    }

    python::class_<Chem::MatchConstraintList, Chem::MatchConstraintList::SharedPointer>
        mcl_cls("MatchConstraintList", python::no_init);

    python::scope scope = mcl_cls;

    python::enum_<Chem::MatchConstraintList::Type>("Type")
        .value("AND_LIST", Chem::MatchConstraintList::AND_LIST)
        .value("OR_LIST", Chem::MatchConstraintList::OR_LIST)
        .value("NOT_AND_LIST", Chem::MatchConstraintList::NOT_AND_LIST)
        .value("NOT_OR_LIST", Chem::MatchConstraintList::NOT_OR_LIST)
        .export_values();

    mcl_cls
        .def(python::init<const Chem::MatchConstraintList&>((python::arg("self"), python::arg("list"))))
        .def(python::init<Chem::MatchConstraintList::Type>((python::arg("self"), python::arg("type") = Chem::MatchConstraintList::AND_LIST)))
        .def(CDPLPythonUtil::ArrayVisitor<Chem::MatchConstraintList, 
             python::return_internal_reference<>, python::default_call_policies,
             python::default_call_policies, python::default_call_policies>())
        .def("assign", CDPLPythonBase::copyAssOp(&Chem::MatchConstraintList::operator=), (python::arg("self"), python::arg("list")),
             python::return_self<>())
        .def("getType", &Chem::MatchConstraintList::getType, python::arg("self"))
        .def("setType", &Chem::MatchConstraintList::setType, (python::arg("self"), python::arg("type")))
        .def("addElement", addElementFunc1, (python::arg("self"), python::arg("id"), python::arg("rel")))
        .def("addElement", addElementFunc2, (python::arg("self"), python::arg("id"), python::arg("rel"), 
                                             python::arg("val")))
        .def("__str__", &toString, python::arg("self"))
        .add_property("type", &Chem::MatchConstraintList::getType, &Chem::MatchConstraintList::setType);   
}
