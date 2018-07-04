/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * MoleculeAutoCorr2DDescriptorCalculatorExport.cpp 
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

#include "CDPL/Chem/MoleculeAutoCorr2DDescriptorCalculator.hpp"
#include "CDPL/Chem/MolecularGraph.hpp"

#include "Base/ObjectIdentityCheckVisitor.hpp"
#include "Base/CopyAssOp.hpp"

#include "ClassExports.hpp"


void CDPLPythonChem::exportMoleculeAutoCorr2DDescriptorCalculator()
{
	using namespace boost;
	using namespace CDPL;

	python::class_<Chem::MoleculeAutoCorr2DDescriptorCalculator, boost::noncopyable>("MoleculeAutoCorr2DDescriptorCalculator", python::no_init)
		.def(python::init<>(python::arg("self")))
		.def(python::init<const Chem::MoleculeAutoCorr2DDescriptorCalculator&>((python::arg("self"), python::arg("calculator"))))
		.def(python::init<const Chem::MolecularGraph&, Math::DVector&>(
				 (python::arg("self"), python::arg("molgraph"), python::arg("corr_vec"))))
		.def(CDPLPythonBase::ObjectIdentityCheckVisitor<Chem::MoleculeAutoCorr2DDescriptorCalculator>())	
		.def("assign", CDPLPythonBase::copyAssOp(&Chem::MoleculeAutoCorr2DDescriptorCalculator::operator=), 
			 (python::arg("self"), python::arg("calculator")), python::return_self<>())
		.def("setMaxDistance", &Chem::MoleculeAutoCorr2DDescriptorCalculator::setMaxDistance,
			 (python::arg("self"), python::arg("max_dist")))
		.def("getMaxDistance", &Chem::MoleculeAutoCorr2DDescriptorCalculator::getMaxDistance,
			 python::arg("self"))
		.def("setAtomPairWeightFunction", &Chem::MoleculeAutoCorr2DDescriptorCalculator::setAtomPairWeightFunction,
			 (python::arg("self"), python::arg("func")))
		.def("calculate", &Chem::MoleculeAutoCorr2DDescriptorCalculator::calculate, 
			 (python::arg("self"), python::arg("molgraph"), python::arg("corr_vec")))
		.add_property("maxDistance", &Chem::MoleculeAutoCorr2DDescriptorCalculator::getMaxDistance,
					  &Chem::MoleculeAutoCorr2DDescriptorCalculator::setMaxDistance);
}
