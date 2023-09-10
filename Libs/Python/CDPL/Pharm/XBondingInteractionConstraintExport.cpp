/* 
 * XBondingInteractionConstraintExport.cpp 
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

#include "CDPL/Pharm/XBondingInteractionConstraint.hpp"
#include "CDPL/Pharm/Feature.hpp"

#include "Base/ObjectIdentityCheckVisitor.hpp"
#include "Base/CopyAssOp.hpp"

#include "ClassExports.hpp"


namespace
{

    bool callOperator(CDPL::Pharm::XBondingInteractionConstraint& constr, 
                      CDPL::Pharm::Feature& ftr1, CDPL::Pharm::Feature& ftr2)
    {
        return constr(ftr1, ftr2);
    }
}


void CDPLPythonPharm::exportXBondingInteractionConstraint()
{
    using namespace boost;
    using namespace CDPL;

    python::class_<Pharm::XBondingInteractionConstraint, boost::noncopyable>("XBondingInteractionConstraint", python::no_init)
        .def(python::init<const Pharm::XBondingInteractionConstraint&>((python::arg("self"), python::arg("constr"))))
        .def(python::init<bool, double, double, double, double>((python::arg("self"), python::arg("don_acc"), 
                                                                 python::arg("min_ax_dist") = Pharm::XBondingInteractionConstraint::DEF_MIN_AX_DISTANCE, 
                                                                 python::arg("max_ax_dist") = Pharm::XBondingInteractionConstraint::DEF_MIN_AX_DISTANCE,
                                                                 python::arg("min_axb_ang") = Pharm::XBondingInteractionConstraint::DEF_MIN_AXB_ANGLE,
                                                                 python::arg("max_acc_ang") = Pharm::XBondingInteractionConstraint::DEF_MAX_ACC_ANGLE)))
        .def(CDPLPythonBase::ObjectIdentityCheckVisitor<Pharm::XBondingInteractionConstraint>())
        .def("getMinAXDistance", &Pharm::XBondingInteractionConstraint::getMinAXDistance, python::arg("self"))
        .def("getMaxAXDistance", &Pharm::XBondingInteractionConstraint::getMaxAXDistance, python::arg("self"))
        .def("getMinAXBAngle", &Pharm::XBondingInteractionConstraint::getMinAXBAngle, python::arg("self"))
        .def("getMaxAcceptorAngle", &Pharm::XBondingInteractionConstraint::getMaxAcceptorAngle, python::arg("self"))
        .def("assign", CDPLPythonBase::copyAssOp<Pharm::XBondingInteractionConstraint>(), 
             (python::arg("self"), python::arg("constr")), python::return_self<>())
        .def("__call__", &callOperator, (python::arg("self"), python::arg("ftr1"), python::arg("ftr2")))
        .add_property("minAXDistance", &Pharm::XBondingInteractionConstraint::getMinAXDistance)
        .add_property("maxAXDistance", &Pharm::XBondingInteractionConstraint::getMaxAXDistance)
        .add_property("minAXBAngle", &Pharm::XBondingInteractionConstraint::getMinAXBAngle)
        .add_property("maxAcceptorAngle", &Pharm::XBondingInteractionConstraint::getMaxAcceptorAngle)
        .def_readonly("DEF_MIN_AX_DISTANCE", Pharm::XBondingInteractionConstraint::DEF_MIN_AX_DISTANCE)
        .def_readonly("DEF_MAX_AX_DISTANCE", Pharm::XBondingInteractionConstraint::DEF_MAX_AX_DISTANCE)
        .def_readonly("DEF_MIN_AXB_ANGLE", Pharm::XBondingInteractionConstraint::DEF_MIN_AXB_ANGLE)
        .def_readonly("DEF_MAX_ACC_ANGLE", Pharm::XBondingInteractionConstraint::DEF_MAX_ACC_ANGLE);
}
