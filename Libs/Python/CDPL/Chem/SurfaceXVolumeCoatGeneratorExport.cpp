/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * SurfaceXVolumeCoatGeneratorExport.cpp 
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

#include "CDPL/Chem/SurfaceXVolumeCoatGenerator.hpp"
#include "CDPL/Chem/MolecularGraph.hpp"
#include "CDPL/Chem/Pharmacophore.hpp"

#include "ClassExports.hpp"


namespace
{
	
	CDPL::Chem::SurfaceXVolumeCoatGenerator*
	construct(CDPL::Chem::AtomContainer& cntnr, CDPL::Chem::MolecularGraph& prnt_molgraph, CDPL::Chem::Pharmacophore& pharm)
    {
		return new CDPL::Chem::SurfaceXVolumeCoatGenerator(cntnr, prnt_molgraph, pharm);
    }

	void generate(CDPL::Chem::SurfaceXVolumeCoatGenerator& gen, CDPL::Chem::AtomContainer& cntnr, 
				  CDPL::Chem::MolecularGraph& prnt_molgraph, CDPL::Chem::Pharmacophore& pharm)
	{
		gen.generate(cntnr, prnt_molgraph, pharm);
	}
}


void CDPLPythonChem::exportSurfaceXVolumeCoatGenerator()
{
    using namespace boost;
    using namespace CDPL;

    python::class_<Chem::SurfaceXVolumeCoatGenerator, 
				   boost::noncopyable>("SurfaceXVolumeCoatGenerator", python::no_init)
		.def(python::init<>(python::arg("self")))
		.def(python::init<const Chem::SurfaceXVolumeCoatGenerator&>(
				 (python::arg("self"), python::arg("gen"))))
		.def("__init__", python::make_constructor(&construct, python::default_call_policies(),
												  (python::arg("cntnr"), python::arg("parent_molgraph"),
												   python::arg("pharm"))))
		.def("setFeatureType", &Chem::SurfaceXVolumeCoatGenerator::setFeatureType, 
			 (python::arg("self"), python::arg("type")))
		.def("setFeatureGeometry", &Chem::SurfaceXVolumeCoatGenerator::setFeatureGeometry, 
			 (python::arg("self"), python::arg("geom")))
		.def("setProbeRadius", &Chem::SurfaceXVolumeCoatGenerator::setProbeRadius, 
			 (python::arg("self"), python::arg("radius")))
		.def("setGridStepSize", &Chem::SurfaceXVolumeCoatGenerator::setGridStepSize, 
			 (python::arg("self"), python::arg("size")))
		.def("setGridOversize", &Chem::SurfaceXVolumeCoatGenerator::setGridOversize, 
			 (python::arg("self"), python::arg("size")))
		.def("setMinSurfaceAccessibility", &Chem::SurfaceXVolumeCoatGenerator::setMinSurfaceAccessibility,
			 (python::arg("self"), python::arg("min_acc")))
		.def("setNumTestPoints", &Chem::SurfaceXVolumeCoatGenerator::setNumTestPoints, 
			 (python::arg("self"), python::arg("num_points")))
		.def("getFeatureType", &Chem::SurfaceXVolumeCoatGenerator::getFeatureType, python::arg("self"))
		.def("getFeatureGeometry", &Chem::SurfaceXVolumeCoatGenerator::getFeatureGeometry, python::arg("self"))
		.def("getProbeRadius", &Chem::SurfaceXVolumeCoatGenerator::getProbeRadius, python::arg("self"))
		.def("getGridStepSize", &Chem::SurfaceXVolumeCoatGenerator::getGridStepSize, python::arg("self"))
		.def("getGridOversize", &Chem::SurfaceXVolumeCoatGenerator::getGridOversize, python::arg("self"))
		.def("getMinSurfaceAccessibility", &Chem::SurfaceXVolumeCoatGenerator::getMinSurfaceAccessibility, python::arg("self"))
		.def("getNumTestPoints", &Chem::SurfaceXVolumeCoatGenerator::getNumTestPoints, python::arg("self"))
		.def("generate", &generate,
			 (python::arg("self"), python::arg("cntr"), python::arg("parent_molgraph"), python::arg("pharm")))
		.def("assign", &Chem::SurfaceXVolumeCoatGenerator::operator=, 
			 (python::arg("self"), python::arg("gen")), python::return_self<>())
		.def_readonly("DEF_PROBE_RADIUS", Chem::SurfaceXVolumeCoatGenerator::DEF_PROBE_RADIUS)
		.def_readonly("DEF_GRID_OVERSIZE", Chem::SurfaceXVolumeCoatGenerator::DEF_GRID_OVERSIZE)
		.def_readonly("DEF_GRID_STEP_SIZE", Chem::SurfaceXVolumeCoatGenerator::DEF_GRID_STEP_SIZE)
		.def_readonly("DEF_MIN_SURFACE_ACC", Chem::SurfaceXVolumeCoatGenerator::DEF_MIN_SURFACE_ACC)
		.def_readonly("DEF_FEATURE_TYPE", Chem::SurfaceXVolumeCoatGenerator::DEF_FEATURE_TYPE)
		.def_readonly("DEF_FEATURE_GEOM", Chem::SurfaceXVolumeCoatGenerator::DEF_FEATURE_GEOM)
		.add_property("featureType", &Chem::SurfaceXVolumeCoatGenerator::getFeatureType,
					  &Chem::SurfaceXVolumeCoatGenerator::setFeatureType)
		.add_property("featureGeometry", &Chem::SurfaceXVolumeCoatGenerator::getFeatureGeometry,
					  &Chem::SurfaceXVolumeCoatGenerator::setFeatureGeometry)
		.add_property("probeRadius", &Chem::SurfaceXVolumeCoatGenerator::getProbeRadius,
					  &Chem::SurfaceXVolumeCoatGenerator::setProbeRadius)
		.add_property("gridStepSize", &Chem::SurfaceXVolumeCoatGenerator::getGridStepSize,
					  &Chem::SurfaceXVolumeCoatGenerator::setGridStepSize)
		.add_property("gridOversize", &Chem::SurfaceXVolumeCoatGenerator::getGridOversize,
					  &Chem::SurfaceXVolumeCoatGenerator::setGridOversize)
		.add_property("numTestPoints", &Chem::SurfaceXVolumeCoatGenerator::getNumTestPoints,
					  &Chem::SurfaceXVolumeCoatGenerator::setNumTestPoints)
		.add_property("minSurfaceAccessibility", &Chem::SurfaceXVolumeCoatGenerator::getMinSurfaceAccessibility,
					  &Chem::SurfaceXVolumeCoatGenerator::setMinSurfaceAccessibility);
}
