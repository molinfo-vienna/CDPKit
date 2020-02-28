/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * GeometricalFeatureMappingExtractorExport.cpp 
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

#include "CDPL/Pharm/GeometricalFeatureMappingExtractor.hpp"
#include "CDPL/Pharm/FeatureContainer.hpp"
#include "CDPL/Pharm/Feature.hpp"

#include "Base/ObjectIdentityCheckVisitor.hpp"
#include "Base/CopyAssOp.hpp"

#include "ClassExports.hpp"


namespace
{

	double getPositionMatchScore(CDPL::Pharm::GeometricalFeatureMappingExtractor& xtractor,
								 CDPL::Pharm::Feature& ftr1, CDPL::Pharm::Feature& ftr2)
	{
		return xtractor.getPositionMatchScore(ftr1, ftr2);
	}

	double getGeometryMatchScore(CDPL::Pharm::GeometricalFeatureMappingExtractor& xtractor,
								 CDPL::Pharm::Feature& ftr1, CDPL::Pharm::Feature& ftr2)
	{
		return xtractor.getGeometryMatchScore(ftr1, ftr2);
	}
}


void CDPLPythonPharm::exportGeometricalFeatureMappingExtractor()
{
    using namespace boost;
    using namespace CDPL;

	python::class_<Pharm::GeometricalFeatureMappingExtractor, boost::noncopyable>("GeometricalFeatureMappingExtractor", python::no_init)
		.def(python::init<const Pharm::GeometricalFeatureMappingExtractor&>((python::arg("self"), python::arg("extor"))))
		.def(python::init<bool>((python::arg("self"), python::arg("query_mode") = false)))
		.def(CDPLPythonBase::ObjectIdentityCheckVisitor<Pharm::GeometricalFeatureMappingExtractor>())
		.def("assign", CDPLPythonBase::copyAssOp(&Pharm::GeometricalFeatureMappingExtractor::operator=), 
			 (python::arg("self"), python::arg("extor")), python::return_self<>())
		.def("getMapping", &Pharm::GeometricalFeatureMappingExtractor::getMapping, 
			 (python::arg("self"), python::arg("ref_cntnr"), python::arg("cntnr"), python::arg("xform"), python::arg("mapping")))
		.def("setTypeMatchFunction", &Pharm::GeometricalFeatureMappingExtractor::setTypeMatchFunction, 
			 (python::arg("self"), python::arg("func")))
		.def("getTypeMatchFunction", &Pharm::GeometricalFeatureMappingExtractor::getTypeMatchFunction, 
			 python::arg("self"), python::return_internal_reference<>())
		.def("setPositionMatchFunction", &Pharm::GeometricalFeatureMappingExtractor::setPositionMatchFunction,
			 (python::arg("self"), python::arg("func")))
		.def("getPositionMatchFunction", &Pharm::GeometricalFeatureMappingExtractor::getPositionMatchFunction, 
			 python::arg("self"), python::return_internal_reference<>())
		.def("setGeometryMatchFunction", &Pharm::GeometricalFeatureMappingExtractor::setGeometryMatchFunction,
			 (python::arg("self"), python::arg("func")))
		.def("getGeometryMatchFunction", &Pharm::GeometricalFeatureMappingExtractor::getGeometryMatchFunction, 
			 python::arg("self"), python::return_internal_reference<>())
		.def("getPositionMatchScore", &getPositionMatchScore, (python::arg("self"), python::arg("ftr1"), python::arg("ftr2")))
		.def("getGeometryMatchScore", &getGeometryMatchScore, (python::arg("self"), python::arg("ftr1"), python::arg("ftr2")))
		.add_property("typeMatchFunction", python::make_function(&Pharm::GeometricalFeatureMappingExtractor::getTypeMatchFunction,
																 python::return_internal_reference<>()), 
					  &Pharm::GeometricalFeatureMappingExtractor::setTypeMatchFunction)
		.add_property("positionMatchFunction", python::make_function(&Pharm::GeometricalFeatureMappingExtractor::getPositionMatchFunction,
																 python::return_internal_reference<>()), 
					  &Pharm::GeometricalFeatureMappingExtractor::setPositionMatchFunction)
		.add_property("geometryMatchFunction", python::make_function(&Pharm::GeometricalFeatureMappingExtractor::getGeometryMatchFunction,
																 python::return_internal_reference<>()), 
					  &Pharm::GeometricalFeatureMappingExtractor::setGeometryMatchFunction);
}
