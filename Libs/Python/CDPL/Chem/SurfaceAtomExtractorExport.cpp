/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * SurfaceAtomExtractorExport.cpp 
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

#include "CDPL/Chem/SurfaceAtomExtractor.hpp"
#include "CDPL/Chem/Fragment.hpp"

#include "Base/ObjectIdentityCheckVisitor.hpp"
#include "Base/CopyAssOp.hpp"

#include "ClassExports.hpp"


namespace
{

	void extract(CDPL::Chem::SurfaceAtomExtractor& xtor, CDPL::Chem::AtomContainer& cntnr, 
				 CDPL::Chem::MolecularGraph& prnt_molgraph, CDPL::Chem::Fragment& frag)
	{
		xtor.extract(cntnr, prnt_molgraph, frag);
	}
}


void CDPLPythonChem::exportSurfaceAtomExtractor()
{
    using namespace boost;
    using namespace CDPL;

    python::class_<Chem::SurfaceAtomExtractor, boost::noncopyable>
		("SurfaceAtomExtractor", python::no_init)
		.def(python::init<>(python::arg("self")))
		.def(python::init<const Chem::SurfaceAtomExtractor&>(
				 (python::arg("self"), python::arg("extractor"))))
		.def(python::init<CDPL::Chem::AtomContainer&, CDPL::Chem::MolecularGraph&, CDPL::Chem::Fragment&>(
				 (python::arg("self"), python::arg("cntnr"), python::arg("parent_molgraph"), python::arg("frag"))))
		.def(CDPLPythonBase::ObjectIdentityCheckVisitor<Chem::SurfaceAtomExtractor>())	
		.def("setAtom3DCoordinatesFunction", &Chem::SurfaceAtomExtractor::setAtom3DCoordinatesFunction,
			 (python::arg("self"), python::arg("func")))
		.def("getAtom3DCoordinatesFunction", &Chem::SurfaceAtomExtractor::getAtom3DCoordinatesFunction, 
			 python::arg("self"), python::return_internal_reference<>())
		.def("setProbeRadius", &Chem::SurfaceAtomExtractor::setProbeRadius, 
			 (python::arg("self"), python::arg("radius")))
		.def("setGridStepSize", &Chem::SurfaceAtomExtractor::setGridStepSize, 
			 (python::arg("self"), python::arg("size")))
		.def("setGridOversize", &Chem::SurfaceAtomExtractor::setGridOversize, 
			 (python::arg("self"), python::arg("size")))
		.def("setMinSurfaceAccessibility", &Chem::SurfaceAtomExtractor::setMinSurfaceAccessibility,
			 (python::arg("self"), python::arg("min_acc")))
		.def("setNumTestPoints", &Chem::SurfaceAtomExtractor::setNumTestPoints, 
			 (python::arg("self"), python::arg("num_points")))
		.def("getProbeRadius", &Chem::SurfaceAtomExtractor::getProbeRadius, python::arg("self"))
		.def("getGridStepSize", &Chem::SurfaceAtomExtractor::getGridStepSize, python::arg("self"))
		.def("getGridOversize", &Chem::SurfaceAtomExtractor::getGridOversize, python::arg("self"))
		.def("getMinSurfaceAccessibility", &Chem::SurfaceAtomExtractor::getMinSurfaceAccessibility, python::arg("self"))
		.def("getNumTestPoints", &Chem::SurfaceAtomExtractor::getNumTestPoints, python::arg("self"))
		.def("extract", &extract,
			 (python::arg("self"), python::arg("cntr"), python::arg("parent_molgraph"), python::arg("frag")))
		.def("assign", CDPLPythonBase::copyAssOp(&Chem::SurfaceAtomExtractor::operator=), 
			 (python::arg("self"), python::arg("extractor")), python::return_self<>())
		.def_readonly("DEF_PROBE_RADIUS", Chem::SurfaceAtomExtractor::DEF_PROBE_RADIUS)
		.def_readonly("DEF_GRID_OVERSIZE", Chem::SurfaceAtomExtractor::DEF_GRID_OVERSIZE)
		.def_readonly("DEF_GRID_STEP_SIZE", Chem::SurfaceAtomExtractor::DEF_GRID_STEP_SIZE)
		.def_readonly("DEF_MIN_SURFACE_ACC", Chem::SurfaceAtomExtractor::DEF_MIN_SURFACE_ACC)
		.add_property("probeRadius", &Chem::SurfaceAtomExtractor::getProbeRadius,
					  &Chem::SurfaceAtomExtractor::setProbeRadius)
		.add_property("gridStepSize", &Chem::SurfaceAtomExtractor::getGridStepSize,
					  &Chem::SurfaceAtomExtractor::setGridStepSize)
		.add_property("gridOversize", &Chem::SurfaceAtomExtractor::getGridOversize,
					  &Chem::SurfaceAtomExtractor::setGridOversize)
		.add_property("numTestPoints", &Chem::SurfaceAtomExtractor::getNumTestPoints,
					  &Chem::SurfaceAtomExtractor::setNumTestPoints)
		.add_property("minSurfaceAccessibility", &Chem::SurfaceAtomExtractor::getMinSurfaceAccessibility,
					  &Chem::SurfaceAtomExtractor::setMinSurfaceAccessibility);
}
