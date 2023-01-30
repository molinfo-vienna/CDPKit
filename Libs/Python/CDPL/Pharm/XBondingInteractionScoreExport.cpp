/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * XBondingInteractionScoreExport.cpp 
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

#include "CDPL/Pharm/XBondingInteractionScore.hpp"

#include "Base/CopyAssOp.hpp"

#include "ClassExports.hpp"


void CDPLPythonPharm::exportXBondingInteractionScore()
{
    using namespace boost;
    using namespace CDPL;

    python::class_<Pharm::XBondingInteractionScore, Pharm::XBondingInteractionScore::SharedPointer,
				   python::bases<Pharm::FeatureInteractionScore>, boost::noncopyable>("XBondingInteractionScore", python::no_init)
		.def(python::init<const Pharm::XBondingInteractionScore&>((python::arg("self"), python::arg("score"))))
		.def(python::init<bool, double, double, double, double>((python::arg("self"), python::arg("don_acc"), 
																 python::arg("min_ax_dist") = Pharm::XBondingInteractionScore::DEF_MIN_AX_DISTANCE, 
																 python::arg("max_ax_dist") = Pharm::XBondingInteractionScore::DEF_MAX_AX_DISTANCE,
																 python::arg("min_axb_ang") = Pharm::XBondingInteractionScore::DEF_MIN_AXB_ANGLE,
																 python::arg("acc_ang_tol") = Pharm::XBondingInteractionScore::DEF_ACC_ANGLE_TOLERANCE)))
		.def("setNormalizationFunction", &Pharm::XBondingInteractionScore::setNormalizationFunction, (python::arg("self"), python::arg("func")))
		.def("getMinAXDistance", &Pharm::XBondingInteractionScore::getMinAXDistance, python::arg("self"))
		.def("getMaxAXDistance", &Pharm::XBondingInteractionScore::getMaxAXDistance, python::arg("self"))
		.def("getMinAXBAngle", &Pharm::XBondingInteractionScore::getMinAXBAngle, python::arg("self"))
		.def("getAcceptorAngleTolerance", &Pharm::XBondingInteractionScore::getAcceptorAngleTolerance, python::arg("self"))	
		.def("assign", CDPLPythonBase::copyAssOp(&Pharm::XBondingInteractionScore::operator=), 
			 (python::arg("self"), python::arg("constr")), python::return_self<>())
		.add_property("minAXDistance", &Pharm::XBondingInteractionScore::getMinAXDistance)
		.add_property("maxAXDistance", &Pharm::XBondingInteractionScore::getMaxAXDistance)
		.add_property("minAXBAngle", &Pharm::XBondingInteractionScore::getMinAXBAngle)
		.add_property("acceptorAngleTolerance", &Pharm::XBondingInteractionScore::getAcceptorAngleTolerance)
		.def_readonly("DEF_MIN_AX_DISTANCE", Pharm::XBondingInteractionScore::DEF_MIN_AX_DISTANCE)
		.def_readonly("DEF_MAX_AX_DISTANCE", Pharm::XBondingInteractionScore::DEF_MAX_AX_DISTANCE)
		.def_readonly("DEF_MIN_AXB_ANGLE", Pharm::XBondingInteractionScore::DEF_MIN_AXB_ANGLE)
		.def_readonly("DEF_ACC_ANGLE_TOLERANCE", Pharm::XBondingInteractionScore::DEF_ACC_ANGLE_TOLERANCE);
}
