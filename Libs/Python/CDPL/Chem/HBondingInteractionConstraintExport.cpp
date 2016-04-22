/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * HBondingInteractionConstraintExport.cpp 
 *
 * This file is part of the Chemical Data Processing Toolkit
 *
 * Copyright (C) 2003-2010 Thomas A. Seidel <thomas.seidel@univie.ac.at>
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

#include "CDPL/Chem/HBondingInteractionConstraint.hpp"
#include "CDPL/Chem/Feature.hpp"

#include "Base/ObjectIdentityCheckVisitor.hpp"

#include "ClassExports.hpp"


namespace
{

    bool callOperator(CDPL::Chem::HBondingInteractionConstraint& constr, 
					  CDPL::Chem::Feature& ftr1, CDPL::Chem::Feature& ftr2)
    {
		return constr(ftr1, ftr2);
    }
}


void CDPLPythonChem::exportHBondingInteractionConstraint()
{
    using namespace boost;
    using namespace CDPL;

    python::class_<Chem::HBondingInteractionConstraint, boost::noncopyable>("HBondingInteractionConstraint", python::no_init)
		.def(python::init<const Chem::HBondingInteractionConstraint&>((python::arg("self"), python::arg("constr"))))
		.def(python::init<bool, double, double, double, double>((python::arg("self"), python::arg("don_acc"), 
																 python::arg("min_len") = Chem::HBondingInteractionConstraint::DEF_MIN_HB_LENGTH, 
																 python::arg("max_len") = Chem::HBondingInteractionConstraint::DEF_MIN_HB_LENGTH,
																 python::arg("min_ahd_ang") = Chem::HBondingInteractionConstraint::DEF_MIN_AHD_ANGLE,
																 python::arg("max_acc_ang") = Chem::HBondingInteractionConstraint::DEF_MAX_ACC_ANGLE)))
		.def(CDPLPythonBase::ObjectIdentityCheckVisitor<Chem::HBondingInteractionConstraint>())
		.def("getMinLength", &Chem::HBondingInteractionConstraint::getMinLength, python::arg("self"))
		.def("getMaxLength", &Chem::HBondingInteractionConstraint::getMaxLength, python::arg("self"))
		.def("getMinAHDAngle", &Chem::HBondingInteractionConstraint::getMinAHDAngle, python::arg("self"))
		.def("getMaxAcceptorAngle", &Chem::HBondingInteractionConstraint::getMaxAcceptorAngle, python::arg("self"))
		.def("assign", &Chem::HBondingInteractionConstraint::operator=, 
			 (python::arg("self"), python::arg("constr")), python::return_self<>())
		.def("__call__", &callOperator, (python::arg("self"), python::arg("ftr1"), python::arg("ftr2")))
		.add_property("minLength", &Chem::HBondingInteractionConstraint::getMinLength)
		.add_property("maxLength", &Chem::HBondingInteractionConstraint::getMaxLength)
		.add_property("minAHDAngle", &Chem::HBondingInteractionConstraint::getMinAHDAngle)
		.add_property("maxAcceptorAngle", &Chem::HBondingInteractionConstraint::getMaxAcceptorAngle)
		.def_readonly("DEF_MIN_HB_LENGTH", Chem::HBondingInteractionConstraint::DEF_MIN_HB_LENGTH)
		.def_readonly("DEF_MAX_HB_LENGTH", Chem::HBondingInteractionConstraint::DEF_MAX_HB_LENGTH)
		.def_readonly("DEF_MIN_AHD_ANGLE", Chem::HBondingInteractionConstraint::DEF_MIN_AHD_ANGLE)
		.def_readonly("DEF_MAX_ACC_ANGLE", Chem::HBondingInteractionConstraint::DEF_MAX_ACC_ANGLE);
}
