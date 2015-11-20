/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * BCUTDescriptorCalculator.cpp 
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


#include "StaticInit.hpp"

#include <algorithm>

#include "CDPL/Chem/BCUTDescriptorCalculator.hpp"
#include "CDPL/Math/JacobiDiagonalization.hpp"
#include "CDPL/Math/VectorIterator.hpp"


using namespace CDPL;


Chem::BCUTDescriptorCalculator::BCUTDescriptorCalculator(const MolecularGraph& molgraph)
{
	calculate(molgraph);
}

const Math::DVector& Chem::BCUTDescriptorCalculator::calculate(const MolecularGraph& molgraph)
{
	tmpBurdenMatrix = burdenMatrixGenerator.generate(molgraph);

	eigenVectors.resize(tmpBurdenMatrix.getSize1(), tmpBurdenMatrix.getSize1());
	bcutDescriptor.resize(tmpBurdenMatrix.getSize1());
	
	Math::jacobiDiagonalize(tmpBurdenMatrix, bcutDescriptor, eigenVectors);

	std::sort(Math::vectorBegin(bcutDescriptor), Math::vectorEnd(bcutDescriptor));

	return bcutDescriptor;
}

const Math::DVector& Chem::BCUTDescriptorCalculator::getResult() const
{
	return bcutDescriptor;
}

void Chem::BCUTDescriptorCalculator::setAtomWeightFunction(const AtomWeightFunction& func)
{
	burdenMatrixGenerator.setAtomWeightFunction(func);
}
