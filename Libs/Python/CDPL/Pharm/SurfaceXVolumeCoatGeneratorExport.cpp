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

#include "CDPL/Pharm/SurfaceXVolumeCoatGenerator.hpp"
#include "CDPL/Chem/MolecularGraph.hpp"
#include "CDPL/Chem/Atom.hpp"
#include "CDPL/Pharm/Pharmacophore.hpp"

#include "Base/CallableObjectAdapter.hpp"
#include "Base/ObjectIdentityCheckVisitor.hpp"

#include "ClassExports.hpp"


namespace
{
	
	CDPL::Pharm::SurfaceXVolumeCoatGenerator*
	construct(CDPL::Chem::AtomContainer& cntnr, CDPL::Chem::MolecularGraph& prnt_molgraph, CDPL::Pharm::Pharmacophore& pharm)
    {
		return new CDPL::Pharm::SurfaceXVolumeCoatGenerator(cntnr, prnt_molgraph, pharm);
    }

	void generate(CDPL::Pharm::SurfaceXVolumeCoatGenerator& gen, CDPL::Chem::AtomContainer& cntnr, 
				  CDPL::Chem::MolecularGraph& prnt_molgraph, CDPL::Pharm::Pharmacophore& pharm)
	{
		gen.generate(cntnr, prnt_molgraph, pharm);
	}

	void set3DCoordsFunc(CDPL::Pharm::SurfaceXVolumeCoatGenerator& gen, const boost::python::object& callable)
    {
		gen.setAtom3DCoordinatesFunction(CDPLPythonBase::UnaryFunctionAdapter<const CDPL::Math::Vector3D&, CDPL::Chem::Atom>(callable)); 
    }
}


void CDPLPythonPharm::exportSurfaceXVolumeCoatGenerator()
{
    using namespace boost;
    using namespace CDPL;

    python::class_<Pharm::SurfaceXVolumeCoatGenerator, boost::noncopyable>
		("SurfaceXVolumeCoatGenerator", python::no_init)
		.def(python::init<>(python::arg("self")))
		.def(python::init<const Pharm::SurfaceXVolumeCoatGenerator&>(
				 (python::arg("self"), python::arg("gen"))))
		.def("__init__", python::make_constructor(&construct, python::default_call_policies(),
												  (python::arg("cntnr"), python::arg("parent_molgraph"),
												   python::arg("pharm"))))
		.def(CDPLPythonBase::ObjectIdentityCheckVisitor<Pharm::SurfaceXVolumeCoatGenerator>())	
		.def("setAtom3DCoordinatesFunction", &set3DCoordsFunc, 
			 (python::arg("self"), python::arg("func")))
		.def("getAtom3DCoordinatesFunction", &Pharm::SurfaceXVolumeCoatGenerator::getAtom3DCoordinatesFunction, 
			 python::arg("self"), python::return_internal_reference<>())
		.def("setFeatureType", &Pharm::SurfaceXVolumeCoatGenerator::setFeatureType, 
			 (python::arg("self"), python::arg("type")))
		.def("setFeatureGeometry", &Pharm::SurfaceXVolumeCoatGenerator::setFeatureGeometry, 
			 (python::arg("self"), python::arg("geom")))
		.def("setProbeRadius", &Pharm::SurfaceXVolumeCoatGenerator::setProbeRadius, 
			 (python::arg("self"), python::arg("radius")))
		.def("setGridStepSize", &Pharm::SurfaceXVolumeCoatGenerator::setGridStepSize, 
			 (python::arg("self"), python::arg("size")))
		.def("setGridOversize", &Pharm::SurfaceXVolumeCoatGenerator::setGridOversize, 
			 (python::arg("self"), python::arg("size")))
		.def("setMinSurfaceAccessibility", &Pharm::SurfaceXVolumeCoatGenerator::setMinSurfaceAccessibility,
			 (python::arg("self"), python::arg("min_acc")))
		.def("setNumTestPoints", &Pharm::SurfaceXVolumeCoatGenerator::setNumTestPoints, 
			 (python::arg("self"), python::arg("num_points")))
		.def("getFeatureType", &Pharm::SurfaceXVolumeCoatGenerator::getFeatureType, python::arg("self"))
		.def("getFeatureGeometry", &Pharm::SurfaceXVolumeCoatGenerator::getFeatureGeometry, python::arg("self"))
		.def("getProbeRadius", &Pharm::SurfaceXVolumeCoatGenerator::getProbeRadius, python::arg("self"))
		.def("getGridStepSize", &Pharm::SurfaceXVolumeCoatGenerator::getGridStepSize, python::arg("self"))
		.def("getGridOversize", &Pharm::SurfaceXVolumeCoatGenerator::getGridOversize, python::arg("self"))
		.def("getMinSurfaceAccessibility", &Pharm::SurfaceXVolumeCoatGenerator::getMinSurfaceAccessibility, python::arg("self"))
		.def("getNumTestPoints", &Pharm::SurfaceXVolumeCoatGenerator::getNumTestPoints, python::arg("self"))
		.def("generate", &generate,
			 (python::arg("self"), python::arg("cntr"), python::arg("parent_molgraph"), python::arg("pharm")))
		.def("assign", &Pharm::SurfaceXVolumeCoatGenerator::operator=, 
			 (python::arg("self"), python::arg("gen")), python::return_self<>())
		.def_readonly("DEF_PROBE_RADIUS", Pharm::SurfaceXVolumeCoatGenerator::DEF_PROBE_RADIUS)
		.def_readonly("DEF_GRID_OVERSIZE", Pharm::SurfaceXVolumeCoatGenerator::DEF_GRID_OVERSIZE)
		.def_readonly("DEF_GRID_STEP_SIZE", Pharm::SurfaceXVolumeCoatGenerator::DEF_GRID_STEP_SIZE)
		.def_readonly("DEF_MIN_SURFACE_ACC", Pharm::SurfaceXVolumeCoatGenerator::DEF_MIN_SURFACE_ACC)
		.def_readonly("DEF_FEATURE_TYPE", Pharm::SurfaceXVolumeCoatGenerator::DEF_FEATURE_TYPE)
		.def_readonly("DEF_FEATURE_GEOM", Pharm::SurfaceXVolumeCoatGenerator::DEF_FEATURE_GEOM)
		.add_property("featureType", &Pharm::SurfaceXVolumeCoatGenerator::getFeatureType,
					  &Pharm::SurfaceXVolumeCoatGenerator::setFeatureType)
		.add_property("featureGeometry", &Pharm::SurfaceXVolumeCoatGenerator::getFeatureGeometry,
					  &Pharm::SurfaceXVolumeCoatGenerator::setFeatureGeometry)
		.add_property("probeRadius", &Pharm::SurfaceXVolumeCoatGenerator::getProbeRadius,
					  &Pharm::SurfaceXVolumeCoatGenerator::setProbeRadius)
		.add_property("gridStepSize", &Pharm::SurfaceXVolumeCoatGenerator::getGridStepSize,
					  &Pharm::SurfaceXVolumeCoatGenerator::setGridStepSize)
		.add_property("gridOversize", &Pharm::SurfaceXVolumeCoatGenerator::getGridOversize,
					  &Pharm::SurfaceXVolumeCoatGenerator::setGridOversize)
		.add_property("numTestPoints", &Pharm::SurfaceXVolumeCoatGenerator::getNumTestPoints,
					  &Pharm::SurfaceXVolumeCoatGenerator::setNumTestPoints)
		.add_property("minSurfaceAccessibility", &Pharm::SurfaceXVolumeCoatGenerator::getMinSurfaceAccessibility,
					  &Pharm::SurfaceXVolumeCoatGenerator::setMinSurfaceAccessibility);
}
