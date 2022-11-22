/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * HBondingInteractionScoreExport.cpp 
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


#include <boost/python.hpp>

#include "CDPL/Pharm/HBondingInteractionScore.hpp"
#include "CDPL/Pharm/Feature.hpp"

#include "Base/ObjectIdentityCheckVisitor.hpp"
#include "Base/CopyAssOp.hpp"

#include "ClassExports.hpp"


namespace
{

    double callOperator1(CDPL::Pharm::HBondingInteractionScore& score, 
						 CDPL::Pharm::Feature& ftr1, CDPL::Pharm::Feature& ftr2)
    {
		return score(ftr1, ftr2);
    }

	double callOperator2(CDPL::Pharm::HBondingInteractionScore& score, 
						 const CDPL::Math::Vector3D& ftr1_pos, CDPL::Pharm::Feature& ftr2)
    {
		return score(ftr1_pos, ftr2);
    }
}


void CDPLPythonPharm::exportHBondingInteractionScore()
{
    using namespace boost;
    using namespace CDPL;

    python::class_<Pharm::HBondingInteractionScore, boost::noncopyable>("HBondingInteractionScore", python::no_init)
		.def(python::init<const Pharm::HBondingInteractionScore&>((python::arg("self"), python::arg("score"))))
		.def(python::init<bool, double, double, double, double>((python::arg("self"), python::arg("don_acc"), 
																 python::arg("min_len") = Pharm::HBondingInteractionScore::DEF_MIN_HB_LENGTH, 
																 python::arg("max_len") = Pharm::HBondingInteractionScore::DEF_MAX_HB_LENGTH,
																 python::arg("min_ahd_ang") = Pharm::HBondingInteractionScore::DEF_MIN_AHD_ANGLE,
																 python::arg("max_acc_ang") = Pharm::HBondingInteractionScore::DEF_MAX_ACC_ANGLE)))
		.def(CDPLPythonBase::ObjectIdentityCheckVisitor<Pharm::HBondingInteractionScore>())
		.def("setNormalizationFunction", &Pharm::HBondingInteractionScore::setNormalizationFunction, (python::arg("self"), python::arg("func")))
		.def("getMinLength", &Pharm::HBondingInteractionScore::getMinLength, python::arg("self"))
		.def("getMaxLength", &Pharm::HBondingInteractionScore::getMaxLength, python::arg("self"))
		.def("getMinAHDAngle", &Pharm::HBondingInteractionScore::getMinAHDAngle, python::arg("self"))
		.def("getMaxAcceptorAngle", &Pharm::HBondingInteractionScore::getMaxAcceptorAngle, python::arg("self"))
		.def("assign", CDPLPythonBase::copyAssOp(&Pharm::HBondingInteractionScore::operator=), 
			 (python::arg("self"), python::arg("constr")), python::return_self<>())
		.def("__call__", &callOperator1, (python::arg("self"), python::arg("ftr1"), python::arg("ftr2")))
		.def("__call__", &callOperator2, (python::arg("self"), python::arg("ftr1_pos"), python::arg("ftr2")))
		.add_property("minLength", &Pharm::HBondingInteractionScore::getMinLength)
		.add_property("maxLength", &Pharm::HBondingInteractionScore::getMaxLength)
		.add_property("minAHDAngle", &Pharm::HBondingInteractionScore::getMinAHDAngle)
		.add_property("maxAcceptorAngle", &Pharm::HBondingInteractionScore::getMaxAcceptorAngle)
		.def_readonly("DEF_MIN_HB_LENGTH", Pharm::HBondingInteractionScore::DEF_MIN_HB_LENGTH)
		.def_readonly("DEF_MAX_HB_LENGTH", Pharm::HBondingInteractionScore::DEF_MAX_HB_LENGTH)
		.def_readonly("DEF_MIN_AHD_ANGLE", Pharm::HBondingInteractionScore::DEF_MIN_AHD_ANGLE)
		.def_readonly("DEF_MAX_ACC_ANGLE", Pharm::HBondingInteractionScore::DEF_MAX_ACC_ANGLE);
}
