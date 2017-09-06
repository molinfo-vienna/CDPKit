/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * StericAtomClashFactorCalculatorExport.cpp 
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

#include "CDPL/Pharm/StericAtomClashFactorCalculator.hpp"
#include "CDPL/Chem/AtomContainer.hpp"

#include "Base/ObjectIdentityCheckVisitor.hpp"
#include "Base/CopyAssOp.hpp"

#include "ClassExports.hpp"


namespace
{

	double callOperator(CDPL::Pharm::StericAtomClashFactorCalculator& calculator, const CDPL::Math::Vector3D& pos,
						CDPL::Chem::AtomContainer& atoms, const CDPL::Chem::Atom3DCoordinatesFunction& coords_func)
	{
		return calculator(pos, atoms, coords_func);
	}
}


void CDPLPythonPharm::exportStericAtomClashFactorCalculator()
{
	using namespace boost;
	using namespace CDPL;

	python::class_<Pharm::StericAtomClashFactorCalculator, boost::noncopyable>("StericAtomClashFactorCalculator", python::no_init)
		.def(python::init<const Pharm::StericAtomClashFactorCalculator&>((python::arg("self"), python::arg("calculator"))))
		.def(python::init<double>((python::arg("self"), python::arg("probe_radius") = Pharm::StericAtomClashFactorCalculator::DEF_PROBE_RADIUS)))
		.def(CDPLPythonBase::ObjectIdentityCheckVisitor<Pharm::StericAtomClashFactorCalculator>())
		.def("getProbeRadius", &Pharm::StericAtomClashFactorCalculator::getProbeRadius, python::arg("self"))
		.def("assign", CDPLPythonBase::copyAssOp(&Pharm::StericAtomClashFactorCalculator::operator=), 
			 (python::arg("self"), python::arg("calculator")), python::return_self<>())
		.def("__call__", &callOperator, (python::arg("self"), python::arg("pos"), python::arg("atoms"), python::arg("coords_func")))
		.add_property("probeRadius", &Pharm::StericAtomClashFactorCalculator::getProbeRadius)
		.def_readonly("DEF_PROBE_RADIUS", Pharm::StericAtomClashFactorCalculator::DEF_PROBE_RADIUS);
}
