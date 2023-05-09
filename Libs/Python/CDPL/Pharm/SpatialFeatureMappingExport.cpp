/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * SpatialFeatureMappingExport.cpp 
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

#include "CDPL/Pharm/SpatialFeatureMapping.hpp"
#include "CDPL/Pharm/FeatureContainer.hpp"
#include "CDPL/Pharm/Feature.hpp"

#include "Base/ObjectIdentityCheckVisitor.hpp"
#include "Base/CopyAssOp.hpp"

#include "ClassExports.hpp"


namespace
{

	double getPositionMatchScore(CDPL::Pharm::SpatialFeatureMapping& mapping,
								 CDPL::Pharm::Feature& ref_ftr, CDPL::Pharm::Feature& aligned_ftr)
	{
		return mapping.getPositionMatchScore(ref_ftr, aligned_ftr);
	}

	double getGeometryMatchScore(CDPL::Pharm::SpatialFeatureMapping& mapping,
								 CDPL::Pharm::Feature& ref_ftr, CDPL::Pharm::Feature& aligned_ftr)
	{
		return mapping.getGeometryMatchScore(ref_ftr, aligned_ftr);
	}
}


void CDPLPythonPharm::exportSpatialFeatureMapping()
{
    using namespace boost;
    using namespace CDPL;

	python::class_<Pharm::SpatialFeatureMapping, python::bases<Pharm::FeatureMapping>, boost::noncopyable>("SpatialFeatureMapping", python::no_init)
		.def(python::init<const Pharm::SpatialFeatureMapping&>((python::arg("self"), python::arg("mapping")))[python::with_custodian_and_ward<1, 2>()])
		.def(python::init<bool>((python::arg("self"), python::arg("query_mode") = false)))
		.def(CDPLPythonBase::ObjectIdentityCheckVisitor<Pharm::SpatialFeatureMapping>())
		.def("assign", CDPLPythonBase::copyAssOp(&Pharm::SpatialFeatureMapping::operator=), 
			 (python::arg("self"), python::arg("mapping")), python::return_self<python::with_custodian_and_ward<1, 2> >())
		.def("perceive", &Pharm::SpatialFeatureMapping::perceive, 
			 (python::arg("self"), python::arg("ref_ftrs"), python::arg("aligned_ftrs"), python::arg("xform")),
			 python::with_custodian_and_ward<1, 2, python::with_custodian_and_ward<1, 3> >())
		.def("setTypeMatchFunction", &Pharm::SpatialFeatureMapping::setTypeMatchFunction, 
			 (python::arg("self"), python::arg("func")))
		.def("getTypeMatchFunction", &Pharm::SpatialFeatureMapping::getTypeMatchFunction, 
			 python::arg("self"), python::return_internal_reference<>())
		.def("setPositionMatchFunction", &Pharm::SpatialFeatureMapping::setPositionMatchFunction,
			 (python::arg("self"), python::arg("func")))
		.def("getPositionMatchFunction", &Pharm::SpatialFeatureMapping::getPositionMatchFunction, 
			 python::arg("self"), python::return_internal_reference<>())
		.def("setGeometryMatchFunction", &Pharm::SpatialFeatureMapping::setGeometryMatchFunction,
			 (python::arg("self"), python::arg("func")))
		.def("getGeometryMatchFunction", &Pharm::SpatialFeatureMapping::getGeometryMatchFunction, 
			 python::arg("self"), python::return_internal_reference<>())
		.def("getPositionMatchScore", &getPositionMatchScore, (python::arg("self"), python::arg("ref_ftr"), python::arg("aligned_ftr")))
		.def("getGeometryMatchScore", &getGeometryMatchScore, (python::arg("self"), python::arg("ref_ftr"), python::arg("aligned_ftr")))
		.add_property("typeMatchFunction", python::make_function(&Pharm::SpatialFeatureMapping::getTypeMatchFunction,
																 python::return_internal_reference<>()), 
					  &Pharm::SpatialFeatureMapping::setTypeMatchFunction)
		.add_property("positionMatchFunction", python::make_function(&Pharm::SpatialFeatureMapping::getPositionMatchFunction,
																 python::return_internal_reference<>()), 
					  &Pharm::SpatialFeatureMapping::setPositionMatchFunction)
		.add_property("geometryMatchFunction", python::make_function(&Pharm::SpatialFeatureMapping::getGeometryMatchFunction,
																 python::return_internal_reference<>()), 
					  &Pharm::SpatialFeatureMapping::setGeometryMatchFunction);
}
