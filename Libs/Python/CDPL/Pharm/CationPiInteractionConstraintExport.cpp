/* 
 * CationPiInteractionConstraintExport.cpp 
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

#include "CDPL/Pharm/CationPiInteractionConstraint.hpp"
#include "CDPL/Pharm/Feature.hpp"

#include "Base/ObjectIdentityCheckVisitor.hpp"
#include "Base/CopyAssOp.hpp"

#include "ClassExports.hpp"


namespace
{

    bool callOperator(CDPL::Pharm::CationPiInteractionConstraint& constr, 
                      CDPL::Pharm::Feature& ftr1, CDPL::Pharm::Feature& ftr2)
    {
        return constr(ftr1, ftr2);
    }
}


void CDPLPythonPharm::exportCationPiInteractionConstraint()
{
    using namespace boost;
    using namespace CDPL;

    python::class_<Pharm::CationPiInteractionConstraint, boost::noncopyable>("CationPiInteractionConstraint", python::no_init)
        .def(python::init<const Pharm::CationPiInteractionConstraint&>((python::arg("self"), python::arg("constr"))))
        .def(python::init<bool, double, double, double>((python::arg("self"), python::arg("aro_cat"), 
                                                         python::arg("min_dist") = Pharm::CationPiInteractionConstraint::DEF_MIN_DISTANCE, 
                                                         python::arg("max_dist") = Pharm::CationPiInteractionConstraint::DEF_MAX_DISTANCE,
                                                         python::arg("max_ang") = Pharm::CationPiInteractionConstraint::DEF_MAX_ANGLE)))
        .def(CDPLPythonBase::ObjectIdentityCheckVisitor<Pharm::CationPiInteractionConstraint>())
        .def("getMinDistance", &Pharm::CationPiInteractionConstraint::getMinDistance, python::arg("self"))
        .def("getMaxDistance", &Pharm::CationPiInteractionConstraint::getMaxDistance, python::arg("self"))
        .def("getMaxAngle", &Pharm::CationPiInteractionConstraint::getMaxAngle, python::arg("self"))
        .def("assign", CDPLPythonBase::copyAssOp<Pharm::CationPiInteractionConstraint>(), 
             (python::arg("self"), python::arg("constr")), python::return_self<>())
        .def("__call__", &callOperator, (python::arg("self"), python::arg("ftr1"), python::arg("ftr2")))
        .add_property("minDistance", &Pharm::CationPiInteractionConstraint::getMinDistance)
        .add_property("maxDistance", &Pharm::CationPiInteractionConstraint::getMaxDistance)
        .add_property("maxAngle", &Pharm::CationPiInteractionConstraint::getMaxAngle)
        .def_readonly("DEF_MIN_DISTANCE", Pharm::CationPiInteractionConstraint::DEF_MIN_DISTANCE)
        .def_readonly("DEF_MAX_DISTANCE", Pharm::CationPiInteractionConstraint::DEF_MAX_DISTANCE)
        .def_readonly("DEF_MAX_ANGLE", Pharm::CationPiInteractionConstraint::DEF_MAX_ANGLE);
}
