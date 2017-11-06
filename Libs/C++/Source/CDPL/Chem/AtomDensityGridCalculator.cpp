/* -*- mode: c++; c-basic-offcalculator: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * AtomDensityGridCalculator.cpp 
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

#include "CDPL/Chem/AtomDensityGridCalculator.hpp"
#include "CDPL/Chem/GeneralizedBellAtomDensity.hpp"  
#include "CDPL/Chem/Entity3DFunctions.hpp"
#include "CDPL/Chem/AtomContainer.hpp"
#include "CDPL/Chem/Atom.hpp"


using namespace CDPL;


namespace
{

    double maxElement(const Math::DVector& vec)
    {
		return normInf(vec);
    }
}
 

Chem::AtomDensityGridCalculator::AtomDensityGridCalculator(): 
    densityFunc(GeneralizedBellAtomDensity()), densityCombinationFunc(&maxElement), coordsFunc(&Chem::get3DCoordinates)
{}

Chem::AtomDensityGridCalculator::AtomDensityGridCalculator(const DensityFunction& func): 
    densityFunc(func), densityCombinationFunc(&maxElement), coordsFunc(&Chem::get3DCoordinates)
{}

Chem::AtomDensityGridCalculator::AtomDensityGridCalculator(const DensityFunction& density_func, const DensityCombinationFunction& comb_func): 
    densityFunc(density_func), densityCombinationFunc(comb_func), coordsFunc(&Chem::get3DCoordinates)
{}

void Chem::AtomDensityGridCalculator::setDensityFunction(const DensityFunction& func)
{
    densityFunc = func;
}

const Chem::AtomDensityGridCalculator::DensityFunction& Chem::AtomDensityGridCalculator::getDensityFunction() const
{
    return densityFunc;
}

void Chem::AtomDensityGridCalculator::setDensityCombinationFunction(const DensityCombinationFunction& func)
{
    densityCombinationFunc = func;
}

const Chem::AtomDensityGridCalculator::DensityCombinationFunction& Chem::AtomDensityGridCalculator::getDensityCombinationFunction() const
{
    return densityCombinationFunc;
}

void Chem::AtomDensityGridCalculator::setAtom3DCoordinatesFunction(const Atom3DCoordinatesFunction& func)
{
    coordsFunc = func;
}

const Chem::Atom3DCoordinatesFunction& Chem::AtomDensityGridCalculator::getAtom3DCoordinatesFunction() const
{
    return coordsFunc;
}

void Chem::AtomDensityGridCalculator::calculate(const AtomContainer& atoms, Grid::DSpatialGrid& grid)
{
    partialDensities.resize(atoms.getNumAtoms(), false);

    std::size_t num_pts = grid.getNumElements();
    Math::Vector3D grid_pos;

    for (std::size_t i = 0, l = 0; i < num_pts; i++, l = 0) {
		grid.getCoordinates(i, grid_pos);

		for (AtomContainer::ConstAtomIterator it = atoms.getAtomsBegin(), end = atoms.getAtomsEnd(); it != end; ++it) {
			const Atom& atom = *it;

			partialDensities[l++] = densityFunc(grid_pos, coordsFunc(atom), atom);
		}

		if (l == 0)
			grid(i) = 0.0;
		else
			grid(i) = densityCombinationFunc(partialDensities);
	}
}
