/* -*- mode: c++; c-basic-offcalculator: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * AtomDensityGridCalculator.cpp 
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

 
#include "StaticInit.hpp"

#include <iterator>

#include "CDPL/GRAILS/AtomDensityGridCalculator.hpp"
#include "CDPL/GRAILS/GeneralizedBellAtomDensity.hpp"  
#include "CDPL/Chem/Entity3DFunctions.hpp"
#include "CDPL/Chem/AtomContainer.hpp"
#include "CDPL/Chem/AtomContainerFunctions.hpp"
#include "CDPL/Chem/Atom.hpp"
#include "CDPL/Internal/Octree.hpp"


using namespace CDPL;


namespace
{

    double maxElement(const Math::DVector& vec)
    {
		return normInf(vec);
    }
}
 

const double GRAILS::AtomDensityGridCalculator::DEF_DISTANCE_CUTOFF = 4.5;


GRAILS::AtomDensityGridCalculator::AtomDensityGridCalculator(): 
    densityFunc(GeneralizedBellAtomDensity()), densityCombinationFunc(&maxElement), 
	coordsFunc(static_cast<const Math::Vector3D& (*)(const Chem::Entity3D&)>(&Chem::get3DCoordinates)), distCutoff(DEF_DISTANCE_CUTOFF)
{}

GRAILS::AtomDensityGridCalculator::AtomDensityGridCalculator(const AtomDensityGridCalculator& calc): 
    densityFunc(calc.densityFunc), densityCombinationFunc(calc.densityCombinationFunc), coordsFunc(calc.coordsFunc), distCutoff(calc.distCutoff)
{}

GRAILS::AtomDensityGridCalculator::AtomDensityGridCalculator(const DensityFunction& func): 
    densityFunc(func), densityCombinationFunc(&maxElement), 
	coordsFunc(static_cast<const Math::Vector3D& (*)(const Chem::Entity3D&)>(&Chem::get3DCoordinates)), distCutoff(DEF_DISTANCE_CUTOFF)
{}

GRAILS::AtomDensityGridCalculator::AtomDensityGridCalculator(const DensityFunction& density_func, const DensityCombinationFunction& comb_func): 
    densityFunc(density_func), densityCombinationFunc(comb_func), 
	coordsFunc(static_cast<const Math::Vector3D& (*)(const Chem::Entity3D&)>(&Chem::get3DCoordinates)), distCutoff(DEF_DISTANCE_CUTOFF)
{}

void GRAILS::AtomDensityGridCalculator::setDistanceCutoff(double dist)
{
	distCutoff = dist;
}

double GRAILS::AtomDensityGridCalculator::getDistanceCutoff() const
{
	return distCutoff;
}

void GRAILS::AtomDensityGridCalculator::setDensityFunction(const DensityFunction& func)
{
    densityFunc = func;
}

const GRAILS::AtomDensityGridCalculator::DensityFunction& GRAILS::AtomDensityGridCalculator::getDensityFunction() const
{
    return densityFunc;
}

void GRAILS::AtomDensityGridCalculator::setDensityCombinationFunction(const DensityCombinationFunction& func)
{
    densityCombinationFunc = func;
}

const GRAILS::AtomDensityGridCalculator::DensityCombinationFunction& GRAILS::AtomDensityGridCalculator::getDensityCombinationFunction() const
{
    return densityCombinationFunc;
}

void GRAILS::AtomDensityGridCalculator::setAtom3DCoordinatesFunction(const Chem::Atom3DCoordinatesFunction& func)
{
    coordsFunc = func;
}

const Chem::Atom3DCoordinatesFunction& GRAILS::AtomDensityGridCalculator::getAtom3DCoordinatesFunction() const
{
    return coordsFunc;
}

void GRAILS::AtomDensityGridCalculator::calculate(const Chem::AtomContainer& atoms, Grid::DSpatialGrid& grid)
{
	if (atoms.getNumAtoms() == 0) {
		for (std::size_t i = 0, num_pts = grid.getNumElements(); i < num_pts; i++)
			grid(i) = 0.0;

		return;
	}

	atomCoords.clear();
	get3DCoordinates(atoms, atomCoords, coordsFunc);

	if (!octree)
		octree.reset(new Octree());

	octree->initialize(atomCoords, 16);

	std::size_t num_pts = grid.getNumElements();
	Math::Vector3D grid_pos;

    for (std::size_t i = 0; i < num_pts; i++) {
		grid.getCoordinates(i, grid_pos);
		atomIndices.clear();

		octree->radiusNeighbors<Octree::L2Distance>(grid_pos, distCutoff, std::back_inserter(atomIndices));

		std::size_t num_inc_atoms = atomIndices.size();

		if (num_inc_atoms == 0) {
			grid(i) = 0.0;

		} else {
			partialDensities.resize(num_inc_atoms, false);

			for (std::size_t j = 0; j < num_inc_atoms; j++) {
				std::size_t atom_idx = atomIndices[j];

				partialDensities[j] = densityFunc(grid_pos, atomCoords[atom_idx], atoms.getAtom(atom_idx));
			}

			grid(i) = densityCombinationFunc(partialDensities);
		}
	}
}

GRAILS::AtomDensityGridCalculator& GRAILS::AtomDensityGridCalculator::operator=(const AtomDensityGridCalculator& calc)
{
	if (this == &calc)
		return *this;

	densityFunc = calc.densityFunc;
	densityCombinationFunc = calc.densityCombinationFunc;
	coordsFunc = calc.coordsFunc;
	distCutoff = calc.distCutoff;

	return *this;
}
