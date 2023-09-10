/* 
 * HBondingInteractionConstraintExport.cpp 
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

#include "CDPL/Pharm/HBondingInteractionConstraint.hpp"
#include "CDPL/Pharm/Feature.hpp"

#include "Base/ObjectIdentityCheckVisitor.hpp"
#include "Base/CopyAssOp.hpp"

#include "ClassExports.hpp"


namespace
{

    bool callOperator(CDPL::Pharm::HBondingInteractionConstraint& constr, 
                      CDPL::Pharm::Feature& ftr1, CDPL::Pharm::Feature& ftr2)
    {
        return constr(ftr1, ftr2);
    }
}


void CDPLPythonPharm::exportHBondingInteractionConstraint()
{
    using namespace boost;
    using namespace CDPL;

    python::class_<Pharm::HBondingInteractionConstraint, boost::noncopyable>("HBondingInteractionConstraint", python::no_init)
        .def(python::init<const Pharm::HBondingInteractionConstraint&>((python::arg("self"), python::arg("constr"))))
        .def(python::init<bool, double, double, double, double>((python::arg("self"), python::arg("don_acc"), 
                                                                 python::arg("min_len") = Pharm::HBondingInteractionConstraint::DEF_MIN_HB_LENGTH, 
                                                                 python::arg("max_len") = Pharm::HBondingInteractionConstraint::DEF_MIN_HB_LENGTH,
                                                                 python::arg("min_ahd_ang") = Pharm::HBondingInteractionConstraint::DEF_MIN_AHD_ANGLE,
                                                                 python::arg("max_acc_ang") = Pharm::HBondingInteractionConstraint::DEF_MAX_ACC_ANGLE)))
        .def(CDPLPythonBase::ObjectIdentityCheckVisitor<Pharm::HBondingInteractionConstraint>())
        .def("getMinLength", &Pharm::HBondingInteractionConstraint::getMinLength, python::arg("self"))
        .def("getMaxLength", &Pharm::HBondingInteractionConstraint::getMaxLength, python::arg("self"))
        .def("getMinAHDAngle", &Pharm::HBondingInteractionConstraint::getMinAHDAngle, python::arg("self"))
        .def("getMaxAcceptorAngle", &Pharm::HBondingInteractionConstraint::getMaxAcceptorAngle, python::arg("self"))
        .def("assign", CDPLPythonBase::copyAssOp<Pharm::HBondingInteractionConstraint>(), 
             (python::arg("self"), python::arg("constr")), python::return_self<>())
        .def("__call__", &callOperator, (python::arg("self"), python::arg("ftr1"), python::arg("ftr2")))
        .add_property("minLength", &Pharm::HBondingInteractionConstraint::getMinLength)
        .add_property("maxLength", &Pharm::HBondingInteractionConstraint::getMaxLength)
        .add_property("minAHDAngle", &Pharm::HBondingInteractionConstraint::getMinAHDAngle)
        .add_property("maxAcceptorAngle", &Pharm::HBondingInteractionConstraint::getMaxAcceptorAngle)
        .def_readonly("DEF_MIN_HB_LENGTH", Pharm::HBondingInteractionConstraint::DEF_MIN_HB_LENGTH)
        .def_readonly("DEF_MAX_HB_LENGTH", Pharm::HBondingInteractionConstraint::DEF_MAX_HB_LENGTH)
        .def_readonly("DEF_MIN_AHD_ANGLE", Pharm::HBondingInteractionConstraint::DEF_MIN_AHD_ANGLE)
        .def_readonly("DEF_MAX_ACC_ANGLE", Pharm::HBondingInteractionConstraint::DEF_MAX_ACC_ANGLE);
}
