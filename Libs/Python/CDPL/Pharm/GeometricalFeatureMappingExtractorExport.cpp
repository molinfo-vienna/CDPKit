/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * GeometricalFeatureMappingExtractorExport.cpp 
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

#include "CDPL/Pharm/GeometricalFeatureMappingExtractor.hpp"
#include "CDPL/Pharm/Pharmacophore.hpp"
#include "CDPL/Pharm/Feature.hpp"

#include "Base/ObjectIdentityCheckVisitor.hpp"

#include "ClassExports.hpp"


void CDPLPythonPharm::exportGeometricalFeatureMappingExtractor()
{
    using namespace boost;
    using namespace CDPL;

	python::class_<Pharm::GeometricalFeatureMappingExtractor, boost::noncopyable>("GeometricalFeatureMappingExtractor", python::no_init)
		.def(python::init<const Pharm::GeometricalFeatureMappingExtractor&>((python::arg("self"), python::arg("extor"))))
		.def(python::init<bool>((python::arg("self"), python::arg("query_mode") = false)))
		.def(CDPLPythonBase::ObjectIdentityCheckVisitor<Pharm::GeometricalFeatureMappingExtractor>())
		.def("assign", &Pharm::GeometricalFeatureMappingExtractor::operator=, 
			 (python::arg("self"), python::arg("extor")), python::return_self<>())
		.def("getMapping", &Pharm::GeometricalFeatureMappingExtractor::getMapping, 
			 (python::arg("self"), python::arg("mpd_pharm"), python::arg("ref_pharm"), python::arg("xform"), python::arg("mapping")))
		.def("setFeatureTypeMatchFunction", &Pharm::GeometricalFeatureMappingExtractor::setFeatureTypeMatchFunction, 
			 (python::arg("self"), python::arg("func")))
		.def("getFeatureTypeMatchFunction", &Pharm::GeometricalFeatureMappingExtractor::getFeatureTypeMatchFunction, 
			 python::arg("self"), python::return_internal_reference<>())
		.def("setFeaturePositionMatchFunction", &Pharm::GeometricalFeatureMappingExtractor::setFeaturePositionMatchFunction,
			 (python::arg("self"), python::arg("func")))
		.def("getFeaturePositionMatchFunction", &Pharm::GeometricalFeatureMappingExtractor::getFeaturePositionMatchFunction, 
			 python::arg("self"), python::return_internal_reference<>())
		.def("setFeatureGeometryMatchFunction", &Pharm::GeometricalFeatureMappingExtractor::setFeatureGeometryMatchFunction,
			 (python::arg("self"), python::arg("func")))
		.def("getFeatureGeometryMatchFunction", &Pharm::GeometricalFeatureMappingExtractor::getFeatureGeometryMatchFunction, 
			 python::arg("self"), python::return_internal_reference<>());
}
