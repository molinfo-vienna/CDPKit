/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * FeatureDistanceScoreExport.cpp 
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

#include "CDPL/Pharm/FeatureDistanceScore.hpp"
#include "CDPL/Pharm/Feature.hpp"

#include "Base/ObjectIdentityCheckVisitor.hpp"
#include "Base/CopyAssOp.hpp"

#include "ClassExports.hpp"


namespace
{

    double callOperator1(CDPL::Pharm::FeatureDistanceScore& score, 
						CDPL::Pharm::Feature& ftr1, CDPL::Pharm::Feature& ftr2)
    {
		return score(ftr1, ftr2);
    }

	double callOperator2(CDPL::Pharm::FeatureDistanceScore& score, 
						 const CDPL::Math::Vector3D& ftr1_pos, CDPL::Pharm::Feature& ftr2)
    {
		return score(ftr1_pos, ftr2);
    }
}


void CDPLPythonPharm::exportFeatureDistanceScore()
{
    using namespace boost;
    using namespace CDPL;

    python::class_<Pharm::FeatureDistanceScore, boost::noncopyable>("FeatureDistanceScore", python::no_init)
		.def(python::init<const Pharm::FeatureDistanceScore&>((python::arg("self"), python::arg("score"))))
		.def(python::init<double, double>((python::arg("self"), python::arg("min_dist"), python::arg("max_dist"))))
		.def(CDPLPythonBase::ObjectIdentityCheckVisitor<Pharm::FeatureDistanceScore>())
		.def("setNormalizationFunction", &Pharm::FeatureDistanceScore::setNormalizationFunction, (python::arg("self"), python::arg("func")))
		.def("getMinDistance", &Pharm::FeatureDistanceScore::getMinDistance, python::arg("self"))
		.def("getMaxDistance", &Pharm::FeatureDistanceScore::getMaxDistance, python::arg("self"))
		.def("assign", CDPLPythonBase::copyAssOp(&Pharm::FeatureDistanceScore::operator=), 
			 (python::arg("self"), python::arg("func")), python::return_self<>())
		.def("__call__", &callOperator1, (python::arg("self"), python::arg("ftr1"), python::arg("ftr2")))
		.def("__call__", &callOperator2, (python::arg("self"), python::arg("ftr1_pos"), python::arg("ftr2")))
		.add_property("minDistance", &Pharm::FeatureDistanceScore::getMinDistance)
		.add_property("maxDistance", &Pharm::FeatureDistanceScore::getMaxDistance);
}
