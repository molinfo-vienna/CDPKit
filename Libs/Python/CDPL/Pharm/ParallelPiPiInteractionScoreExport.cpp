/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * ParallelPiPiInteractionScoreExport.cpp 
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

#include "CDPL/Pharm/ParallelPiPiInteractionScore.hpp"
#include "CDPL/Pharm/Feature.hpp"

#include "Base/ObjectIdentityCheckVisitor.hpp"
#include "Base/CopyAssOp.hpp"

#include "ClassExports.hpp"


namespace
{

    double callOperator(CDPL::Pharm::ParallelPiPiInteractionScore& score, 
						CDPL::Pharm::Feature& ftr1, CDPL::Pharm::Feature& ftr2)
    {
		return score(ftr1, ftr2);
    }
}


void CDPLPythonPharm::exportParallelPiPiInteractionScore()
{
    using namespace boost;
    using namespace CDPL;

    python::class_<Pharm::ParallelPiPiInteractionScore, boost::noncopyable>("ParallelPiPiInteractionScore", python::no_init)
		.def(python::init<const Pharm::ParallelPiPiInteractionScore&>((python::arg("self"), python::arg("score"))))
		.def(python::init<double, double, double, double>((python::arg("self"),
														 python::arg("min_v_dist") = Pharm::ParallelPiPiInteractionScore::DEF_MIN_V_DISTANCE, 
														 python::arg("max_v_dist") = Pharm::ParallelPiPiInteractionScore::DEF_MAX_V_DISTANCE,
														 python::arg("max_h_dist") = Pharm::ParallelPiPiInteractionScore::DEF_MAX_H_DISTANCE,
														 python::arg("ang_tol") = Pharm::ParallelPiPiInteractionScore::DEF_ANGLE_TOLERANCE)))
		.def(CDPLPythonBase::ObjectIdentityCheckVisitor<Pharm::ParallelPiPiInteractionScore>())
		.def("setNormalizationFunction", &Pharm::ParallelPiPiInteractionScore::setNormalizationFunction, (python::arg("self"), python::arg("func")))
		.def("getMinVDistance", &Pharm::ParallelPiPiInteractionScore::getMinVDistance, python::arg("self"))
		.def("getMaxVDistance", &Pharm::ParallelPiPiInteractionScore::getMaxVDistance, python::arg("self"))
		.def("getMaxHDistance", &Pharm::ParallelPiPiInteractionScore::getMaxHDistance, python::arg("self"))
		.def("getAngleTolerance", &Pharm::ParallelPiPiInteractionScore::getAngleTolerance, python::arg("self"))
		.def("assign", CDPLPythonBase::copyAssOp(&Pharm::ParallelPiPiInteractionScore::operator=), 
			 (python::arg("self"), python::arg("constr")), python::return_self<>())
		.def("__call__", &callOperator, (python::arg("self"), python::arg("ftr1"), python::arg("ftr2")))
		.add_property("minVDistance", &Pharm::ParallelPiPiInteractionScore::getMinVDistance)
		.add_property("maxVDistance", &Pharm::ParallelPiPiInteractionScore::getMaxVDistance)
		.add_property("maxHDistance", &Pharm::ParallelPiPiInteractionScore::getMaxHDistance)
		.add_property("angleTolerance", &Pharm::ParallelPiPiInteractionScore::getAngleTolerance)
		.def_readonly("DEF_MIN_V_DISTANCE", Pharm::ParallelPiPiInteractionScore::DEF_MIN_V_DISTANCE)
		.def_readonly("DEF_MAX_V_DISTANCE", Pharm::ParallelPiPiInteractionScore::DEF_MAX_V_DISTANCE)
		.def_readonly("DEF_MAX_H_DISTANCE", Pharm::ParallelPiPiInteractionScore::DEF_MAX_H_DISTANCE)
		.def_readonly("DEF_ANGLE_TOLERANCE", Pharm::ParallelPiPiInteractionScore::DEF_ANGLE_TOLERANCE);
}
