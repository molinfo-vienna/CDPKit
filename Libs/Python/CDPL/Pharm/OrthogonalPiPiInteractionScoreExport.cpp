/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * OrthogonalPiPiInteractionScoreExport.cpp 
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

#include "CDPL/Pharm/OrthogonalPiPiInteractionScore.hpp"

#include "Base/CopyAssOp.hpp"

#include "ClassExports.hpp"


void CDPLPythonPharm::exportOrthogonalPiPiInteractionScore()
{
    using namespace boost;
    using namespace CDPL;

    python::class_<Pharm::OrthogonalPiPiInteractionScore, Pharm::OrthogonalPiPiInteractionScore::SharedPointer,
				   python::bases<Pharm::FeatureInteractionScore>, boost::noncopyable>("OrthogonalPiPiInteractionScore", python::no_init)
		.def(python::init<const Pharm::OrthogonalPiPiInteractionScore&>((python::arg("self"), python::arg("score"))))
		.def(python::init<double, double, double, double>((python::arg("self"),
														 python::arg("min_h_dist") = Pharm::OrthogonalPiPiInteractionScore::DEF_MIN_H_DISTANCE, 
														 python::arg("max_h_dist") = Pharm::OrthogonalPiPiInteractionScore::DEF_MAX_H_DISTANCE,
														 python::arg("max_v_dist") = Pharm::OrthogonalPiPiInteractionScore::DEF_MAX_V_DISTANCE,
														 python::arg("max_ang") = Pharm::OrthogonalPiPiInteractionScore::DEF_MAX_ANGLE)))

		.def("setDistanceScoringFunction", &Pharm::OrthogonalPiPiInteractionScore::setDistanceScoringFunction, (python::arg("self"), python::arg("func")))
		.def("setAngleScoringFunction", &Pharm::OrthogonalPiPiInteractionScore::setAngleScoringFunction, (python::arg("self"), python::arg("func")))
		.def("getMinHDistance", &Pharm::OrthogonalPiPiInteractionScore::getMinHDistance, python::arg("self"))
		.def("getMaxHDistance", &Pharm::OrthogonalPiPiInteractionScore::getMaxHDistance, python::arg("self"))
		.def("getMaxVDistance", &Pharm::OrthogonalPiPiInteractionScore::getMaxVDistance, python::arg("self"))
		.def("getMaxAngle", &Pharm::OrthogonalPiPiInteractionScore::getMaxAngle, python::arg("self"))
		.def("assign", CDPLPythonBase::copyAssOp(&Pharm::OrthogonalPiPiInteractionScore::operator=), 
			 (python::arg("self"), python::arg("constr")), python::return_self<>())
		.add_property("minHDistance", &Pharm::OrthogonalPiPiInteractionScore::getMinHDistance)
		.add_property("maxHDistance", &Pharm::OrthogonalPiPiInteractionScore::getMaxHDistance)
		.add_property("maxVDistance", &Pharm::OrthogonalPiPiInteractionScore::getMaxVDistance)
		.add_property("maxAngle", &Pharm::OrthogonalPiPiInteractionScore::getMaxAngle)
		.def_readonly("DEF_MIN_H_DISTANCE", Pharm::OrthogonalPiPiInteractionScore::DEF_MIN_H_DISTANCE)
		.def_readonly("DEF_MAX_H_DISTANCE", Pharm::OrthogonalPiPiInteractionScore::DEF_MAX_H_DISTANCE)
		.def_readonly("DEF_MAX_V_DISTANCE", Pharm::OrthogonalPiPiInteractionScore::DEF_MAX_V_DISTANCE)
		.def_readonly("DEF_MAX_ANGLE", Pharm::OrthogonalPiPiInteractionScore::DEF_MAX_ANGLE);
}
