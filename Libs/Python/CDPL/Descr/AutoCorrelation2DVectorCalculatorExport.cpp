/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * AutoCorrelation2DVectorCalculatorExport.cpp 
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

#include "CDPL/Descr/AutoCorrelation2DVectorCalculator.hpp"
#include "CDPL/Chem/MolecularGraph.hpp"
#include "CDPL/Chem/Atom.hpp"

#include "Base/ObjectIdentityCheckVisitor.hpp"
#include "Base/CopyAssOp.hpp"

#include "ClassExports.hpp"


void CDPLPythonDescr::exportAutoCorrelation2DVectorCalculator()
{
	using namespace boost;
	using namespace CDPL;

	python::class_<Descr::AutoCorrelation2DVectorCalculator, boost::noncopyable>("AutoCorrelation2DVectorCalculator", python::no_init)
		.def(python::init<>(python::arg("self")))
		.def(python::init<const Descr::AutoCorrelation2DVectorCalculator&>((python::arg("self"), python::arg("calculator"))))
		.def(python::init<const Chem::MolecularGraph&, Math::DVector&>(
				 (python::arg("self"), python::arg("molgraph"), python::arg("corr_vec"))))
		.def(CDPLPythonBase::ObjectIdentityCheckVisitor<Descr::AutoCorrelation2DVectorCalculator>())	
		.def("assign", CDPLPythonBase::copyAssOp(&Descr::AutoCorrelation2DVectorCalculator::operator=), 
			 (python::arg("self"), python::arg("calculator")), python::return_self<>())
		.def("setMaxDistance", &Descr::AutoCorrelation2DVectorCalculator::setMaxDistance,
			 (python::arg("self"), python::arg("max_dist")))
		.def("getMaxDistance", &Descr::AutoCorrelation2DVectorCalculator::getMaxDistance,
			 python::arg("self"))
		.def("setAtomPairWeightFunction", &Descr::AutoCorrelation2DVectorCalculator::setAtomPairWeightFunction,
			 (python::arg("self"), python::arg("func")))
		.def("calculate", &Descr::AutoCorrelation2DVectorCalculator::calculate, 
			 (python::arg("self"), python::arg("molgraph"), python::arg("corr_vec")))
		.add_property("maxDistance", &Descr::AutoCorrelation2DVectorCalculator::getMaxDistance,
					  &Descr::AutoCorrelation2DVectorCalculator::setMaxDistance);
}
