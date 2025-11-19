/* 
 * KuvekPocketDescriptorCalculator.cpp 
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

#include <cmath>

#include "CDPL/Descr/KuvekPocketDescriptorCalculator.hpp"
#include "CDPL/Chem/Atom.hpp"
#include "CDPL/Chem/AtomContainer.hpp"
#include "CDPL/Chem/AtomFunctions.hpp"
#include "CDPL/Chem/Entity3DFunctions.hpp"
#include "CDPL/Base/Exceptions.hpp"


using namespace CDPL;


constexpr double Descr::KuvekPocketDescriptorCalculator::DEF_PROBE_RADIUS;
constexpr double Descr::KuvekPocketDescriptorCalculator::DEF_MAX_ATOM_TO_SPHERE_SURF_DIST;
constexpr std::size_t Descr::KuvekPocketDescriptorCalculator::DEF_NUM_TEST_VECTORS;

//-----

Descr::KuvekPocketDescriptorCalculator::KuvekPocketDescriptorCalculator(double sphere_radius,
                                                                        std::size_t num_test_vecs,
                                                                        double max_atom_to_sphr_surf_dist):
    sphereRadius(sphere_radius), numTestVectors(num_test_vecs), maxAtomToSphereSurfDist(max_atom_to_sphr_surf_dist),
    coordsFunc(&Chem::get3DCoordinates), chargeFunc(&Chem::getFormalCharge)
{}

void Descr::KuvekPocketDescriptorCalculator::setSphereRadius(double radius)
{
    sphereRadius = radius;
}

double Descr::KuvekPocketDescriptorCalculator::getSphereRadius() const
{
    return sphereRadius;
}

void Descr::KuvekPocketDescriptorCalculator::setMaxAtomToSphereSurfaceDistance(double dist)
{
    maxAtomToSphereSurfDist = dist;
}

double Descr::KuvekPocketDescriptorCalculator::getMaxAtomToSphereSurfaceDistance() const
{
    return maxAtomToSphereSurfDist;
}

void Descr::KuvekPocketDescriptorCalculator::setNumTestVectors(std::size_t num_vectors)
{
    numTestVectors = num_vectors;
}

std::size_t Descr::KuvekPocketDescriptorCalculator::getNumTestVectors() const
{
    return numTestVectors;
}

const Math::Vector3D& Descr::KuvekPocketDescriptorCalculator::getTestVector(std::size_t idx)
{
    if (idx >= numTestVectors)
        throw Base::IndexError("KuvekPocketDescriptorCalculator: test vector index out of bounds");

    genTestVectors();
        
    return testVectors[idx];
}

void Descr::KuvekPocketDescriptorCalculator::setAtom3DCoordinatesFunction(const Chem::Atom3DCoordinatesFunction& func)
{
    coordsFunc = func;
}

const Chem::Atom3DCoordinatesFunction&
Descr::KuvekPocketDescriptorCalculator::getAtom3DCoordinatesFunction() const
{
    return coordsFunc;
}

void Descr::KuvekPocketDescriptorCalculator::setAtomChargeFunction(const AtomChargeFunction& func)
{
    chargeFunc = func;
}

const Descr::KuvekPocketDescriptorCalculator::AtomChargeFunction&
Descr::KuvekPocketDescriptorCalculator::getAtomChargeFunction() const
{
    return chargeFunc;
}

void Descr::KuvekPocketDescriptorCalculator::calculate(const Math::Vector3D& pos, const Chem::AtomContainer& atoms, Math::DVector& descr)
{
    genTestVectors();

    // TODO
}

void Descr::KuvekPocketDescriptorCalculator::genTestVectors()
{
    if (numTestVectors == testVectors.size())
        return;

    testVectors.clear();

    // TODO
}
