/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * BuriednessScoreExport.cpp 
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

#include "CDPL/Chem/BuriednessScore.hpp"
#include "CDPL/Chem/AtomContainer.hpp"

#include "Base/ObjectIdentityCheckVisitor.hpp"
#include "Base/CopyAssOp.hpp"

#include "ClassExports.hpp"


namespace
{

    double callOperator(CDPL::Chem::BuriednessScore& func, const CDPL::Math::Vector3D& pos, 
						CDPL::Chem::AtomContainer& atoms)
    {
		return func(pos, atoms);
    }
}


void CDPLPythonChem::exportBuriednessScore()
{
    using namespace boost;
    using namespace CDPL;

    python::class_<Chem::BuriednessScore, boost::noncopyable>("BuriednessScore", python::no_init)
		.def(python::init<const Chem::BuriednessScore&>((python::arg("self"), python::arg("score"))))
		.def(python::init<double, double, double>((python::arg("self"), python::arg("probe_radius") = Chem::BuriednessScore::DEF_PROBE_RADIUS,
												   python::arg("min_vdw_surf_dist") = Chem::BuriednessScore::DEF_MIN_VDW_SURFACE_DISTANCE,
												   python::arg("num_test_rays") = Chem::BuriednessScore::DEF_NUM_TEST_RAYS)))
		.def(CDPLPythonBase::ObjectIdentityCheckVisitor<Chem::BuriednessScore>())
		.def("setMinVdWSurfaceDistance", &Chem::BuriednessScore::setMinVdWSurfaceDistance, (python::arg("self"), python::arg("dist")))
		.def("getMinVdWSurfaceDistance", &Chem::BuriednessScore::getMinVdWSurfaceDistance, python::arg("self"))
		.def("setProbeRadius", &Chem::BuriednessScore::setProbeRadius, (python::arg("self"), python::arg("radius")))
		.def("getProbeRadius", &Chem::BuriednessScore::getProbeRadius, python::arg("self"))
		.def("setNumTestRays", &Chem::BuriednessScore::setNumTestRays, (python::arg("self"), python::arg("num_rays")))
		.def("getNumTestRays", &Chem::BuriednessScore::getNumTestRays, python::arg("self"))
		.def("setAtom3DCoordinatesFunction", &Chem::BuriednessScore::setAtom3DCoordinatesFunction,
			 (python::arg("self"), python::arg("func")))
		.def("getAtom3DCoordinatesFunction", &Chem::BuriednessScore::getAtom3DCoordinatesFunction,
			 python::arg("self"), python::return_internal_reference<>())
		.def("assign", CDPLPythonBase::copyAssOp(&Chem::BuriednessScore::operator=), 
			 (python::arg("self"), python::arg("score")), python::return_self<>())
		.def("__call__", &callOperator, (python::arg("self"), python::arg("pos"), python::arg("atoms")))
		.add_property("probeRadius", &Chem::BuriednessScore::getProbeRadius, &Chem::BuriednessScore::setProbeRadius)
		.add_property("minVdWSurfaceDistance", &Chem::BuriednessScore::getMinVdWSurfaceDistance, 
					  &Chem::BuriednessScore::setMinVdWSurfaceDistance)
		.add_property("numTestRays", &Chem::BuriednessScore::getNumTestRays, &Chem::BuriednessScore::setNumTestRays)
		.add_property("atomCoordinatesFunction", 
					  python::make_function(&Chem::BuriednessScore::getAtom3DCoordinatesFunction, python::return_internal_reference<>()),
					  &Chem::BuriednessScore::setAtom3DCoordinatesFunction)
		.def_readonly("DEF_NUM_TEST_RAYS", Chem::BuriednessScore::DEF_NUM_TEST_RAYS)
		.def_readonly("DEF_PROBE_RADIUS", Chem::BuriednessScore::DEF_PROBE_RADIUS);
}
