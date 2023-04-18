/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * PharmacophoreFitScoreExport.cpp 
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

#include "CDPL/Pharm/PharmacophoreFitScore.hpp"
#include "CDPL/Pharm/FeatureContainer.hpp"

#include "Base/ObjectIdentityCheckVisitor.hpp"
#include "Base/CopyAssOp.hpp"

#include "ClassExports.hpp"


void CDPLPythonPharm::exportPharmacophoreFitScore()
{
    using namespace boost;
    using namespace CDPL;

    python::class_<Pharm::PharmacophoreFitScore, boost::noncopyable>("PharmacophoreFitScore", python::no_init)
		.def(python::init<const Pharm::PharmacophoreFitScore&>((python::arg("self"), python::arg("score"))))
		.def(python::init<double, double, double>((python::arg("self"), 
												   python::arg("match_cnt_weight") = Pharm::PharmacophoreFitScore::DEF_FTR_MATCH_COUNT_WEIGHT, 
												   python::arg("pos_match_weight") = Pharm::PharmacophoreFitScore::DEF_FTR_POS_MATCH_WEIGHT,
												   python::arg("geom_match_weight") = Pharm::PharmacophoreFitScore::DEF_FTR_GEOM_MATCH_WEIGHT)))
		.def(CDPLPythonBase::ObjectIdentityCheckVisitor<Pharm::PharmacophoreFitScore>())
		.def("assign", CDPLPythonBase::copyAssOp(&Pharm::PharmacophoreFitScore::operator=), 
			 (python::arg("self"), python::arg("score")), python::return_self<>())
		.def("__call__", static_cast<double (Pharm::PharmacophoreFitScore::*)
			 (const Pharm::FeatureContainer&, const Pharm::FeatureContainer&, const Math::Matrix4D&)>(&Pharm::PharmacophoreFitScore::operator()),
			 (python::arg("self"), python::arg("ref_ftrs"), python::arg("algnd_ftrs"), python::arg("xform")))
		.def("__call__", static_cast<double (Pharm::PharmacophoreFitScore::*)
			 (const Pharm::FeatureContainer&, const Pharm::SpatialFeatureMapping&)>(&Pharm::PharmacophoreFitScore::operator()),
			 (python::arg("self"), python::arg("ref_ftrs"), python::arg("mapping")))
		.add_property("featureMatchCountWeight", &Pharm::PharmacophoreFitScore::getFeatureMatchCountWeight, 
					  &Pharm::PharmacophoreFitScore::setFeatureMatchCountWeight)
		.add_property("featurePositionMatchWeight", &Pharm::PharmacophoreFitScore::getFeaturePositionMatchWeight, 
					  &Pharm::PharmacophoreFitScore::setFeaturePositionMatchWeight)
		.add_property("featureGeometryMatchWeight", &Pharm::PharmacophoreFitScore::getFeatureGeometryMatchWeight, 
					  &Pharm::PharmacophoreFitScore::setFeatureGeometryMatchWeight)
		.def_readonly("DEF_FTR_MATCH_COUNT_WEIGHT", Pharm::PharmacophoreFitScore::DEF_FTR_MATCH_COUNT_WEIGHT)
		.def_readonly("DEF_FTR_POS_MATCH_WEIGHT", Pharm::PharmacophoreFitScore::DEF_FTR_POS_MATCH_WEIGHT)
		.def_readonly("DEF_FTR_GEOM_MATCH_WEIGHT", Pharm::PharmacophoreFitScore::DEF_FTR_GEOM_MATCH_WEIGHT);
}
