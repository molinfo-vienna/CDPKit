/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * GeneralizedBellAtomDensityExport.cpp 
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

#include "CDPL/GRAILS/GeneralizedBellAtomDensity.hpp"
#include "CDPL/Chem/Atom.hpp"

#include "Base/ObjectIdentityCheckVisitor.hpp"
#include "Base/CopyAssOp.hpp"

#include "ClassExports.hpp"


namespace
{

	double callOperator(CDPL::GRAILS::GeneralizedBellAtomDensity& func, const CDPL::Math::Vector3D& pos, const CDPL::Math::Vector3D& atom_pos,
						CDPL::Chem::Atom& atom)
	{
		return func(pos, atom_pos, atom);
	}
}


void CDPLPythonGRAILS::exportGeneralizedBellAtomDensity()
{
	using namespace boost;
	using namespace CDPL;

	python::class_<GRAILS::GeneralizedBellAtomDensity, boost::noncopyable>("GeneralizedBellAtomDensity", python::no_init)
		.def(python::init<const GRAILS::GeneralizedBellAtomDensity&>((python::arg("self"), python::arg("func"))))
		.def(python::init<double, double>((python::arg("self"), python::arg("probe_radius") = GRAILS::GeneralizedBellAtomDensity::DEF_PROBE_RADIUS,
								   python::arg("rad_scaling_factor") = GRAILS::GeneralizedBellAtomDensity::DEF_RADIUS_SCALING_FACTOR)))
		.def(CDPLPythonBase::ObjectIdentityCheckVisitor<GRAILS::GeneralizedBellAtomDensity>())
		.def("getProbeRadius", &GRAILS::GeneralizedBellAtomDensity::getProbeRadius, python::arg("self"))
		.def("getRadiusScalingFactor", &GRAILS::GeneralizedBellAtomDensity::getRadiusScalingFactor, python::arg("self"))
		.def("assign", CDPLPythonBase::copyAssOp(&GRAILS::GeneralizedBellAtomDensity::operator=), 
			 (python::arg("self"), python::arg("func")), python::return_self<>())
		.def("__call__", &callOperator, (python::arg("self"), python::arg("pos"), python::arg("atom_pos"), python::arg("atom")))
		.add_property("probeRadius", &GRAILS::GeneralizedBellAtomDensity::getProbeRadius)
		.add_property("radiusScalingFactor", &GRAILS::GeneralizedBellAtomDensity::getRadiusScalingFactor)
		.def_readonly("DEF_RADIUS_SCALING_FACTOR", GRAILS::GeneralizedBellAtomDensity::DEF_RADIUS_SCALING_FACTOR)
		.def_readonly("DEF_PROBE_RADIUS", GRAILS::GeneralizedBellAtomDensity::DEF_PROBE_RADIUS);
}
