/* 
 * BuriednessGridCalculator.cpp 
 *
 * This file is part of the Chemical Data Processing Toolkit
 *
 * Copyright (C) 2003 Thomas Seidel <thomas.seidel@univie.ac.at>
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

#include "CDPL/GRAIL/BuriednessGridCalculator.hpp"
#include "CDPL/Chem/AtomContainerFunctions.hpp"
#include "CDPL/Internal/Octree.hpp"


using namespace CDPL;


GRAIL::BuriednessGridCalculator::BuriednessGridCalculator() {}

GRAIL::BuriednessGridCalculator::BuriednessGridCalculator(const BuriednessGridCalculator& calc): 
    buriednessScore(calc.buriednessScore)
{}

void GRAIL::BuriednessGridCalculator::setProbeRadius(double radius)
{
    buriednessScore.setProbeRadius(radius);
}

double GRAIL::BuriednessGridCalculator::getProbeRadius() const
{
    return buriednessScore.getProbeRadius();
}

void GRAIL::BuriednessGridCalculator::setMinVdWSurfaceDistance(double dist)
{
    buriednessScore.setMinVdWSurfaceDistance(dist);
}

double GRAIL::BuriednessGridCalculator::getMinVdWSurfaceDistance() const
{
    return buriednessScore.getMinVdWSurfaceDistance();
}

void GRAIL::BuriednessGridCalculator::setNumTestRays(std::size_t num_rays)
{
    buriednessScore.setNumTestRays(num_rays);
}

std::size_t GRAIL::BuriednessGridCalculator::getNumTestRays() const
{
    return buriednessScore.getNumTestRays();
}

void GRAIL::BuriednessGridCalculator::setAtom3DCoordinatesFunction(const Chem::Atom3DCoordinatesFunction& func)
{
    buriednessScore.setAtom3DCoordinatesFunction(func);
}

const Chem::Atom3DCoordinatesFunction& GRAIL::BuriednessGridCalculator::getAtom3DCoordinatesFunction() const
{
    return buriednessScore.getAtom3DCoordinatesFunction();
}

GRAIL::BuriednessGridCalculator& GRAIL::BuriednessGridCalculator::operator=(const BuriednessGridCalculator& calc)
{
    if (this == &calc)
        return *this;

    buriednessScore = calc.buriednessScore;

    return *this;
}

void GRAIL::BuriednessGridCalculator::calculate(const Chem::AtomContainer& atoms, Grid::DSpatialGrid& grid)
{
     atomCoords.clear();
    get3DCoordinates(atoms, atomCoords, buriednessScore.getAtom3DCoordinatesFunction());

    if (!octree)
        octree.reset(new Octree());

    octree->initialize(atomCoords, 16);

    std::size_t num_pts = grid.getNumElements();
    Math::Vector3D grid_pos;

    for (std::size_t i = 0; i < num_pts; i++) {
        grid.getCoordinates(i, grid_pos);

        atomIndices.clear();

        octree->radiusNeighbors<Octree::L2Distance>(grid_pos, buriednessScore.getProbeRadius(), std::back_inserter(atomIndices));

        std::size_t num_inc_atoms = atomIndices.size();

        atomSubset.clear();

        for (std::size_t j = 0; j < num_inc_atoms; j++)
            atomSubset.addAtom(atoms.getAtom(atomIndices[j]));

        grid(i) = buriednessScore(grid_pos, atomSubset);
    }
}
