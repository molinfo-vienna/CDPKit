/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * BuriednessScore.cpp 
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

#include <cmath>

#include "CDPL/Chem/BuriednessScore.hpp"
#include "CDPL/Chem/AtomContainer.hpp"
#include "CDPL/Chem/Atom.hpp"
#include "CDPL/Chem/AtomFunctions.hpp"
#include "CDPL/Chem/Entity3DFunctions.hpp"


using namespace CDPL; 


const double Chem::BuriednessScore::DEF_PROBE_RADIUS             = 8.0;
const double Chem::BuriednessScore::DEF_MIN_VDW_SURFACE_DISTANCE = 1.0;
const std::size_t Chem::BuriednessScore::DEF_NUM_TEST_RAYS       = 200;


Chem::BuriednessScore::BuriednessScore(double probe_radius, double min_vdw_surf_dist, std::size_t num_test_rays): 
    probeRadius(probe_radius), minVdWSurfaceDist(min_vdw_surf_dist), numTestRays(num_test_rays), 
	coordsFunc(&get3DCoordinates), probeSurfPoints(num_test_rays), hitRaysMask(num_test_rays)
{
	genSphereSurfacePoints();
}

void Chem::BuriednessScore::setProbeRadius(double radius)
{
    probeRadius = radius;;
}

double Chem::BuriednessScore::getProbeRadius() const
{
    return probeRadius;
}

void Chem::BuriednessScore::setMinVdWSurfaceDistance(double dist)
{
	minVdWSurfaceDist = dist;
}

double Chem::BuriednessScore::getMinVdWSurfaceDistance() const
{
	return minVdWSurfaceDist;
}

void Chem::BuriednessScore::setNumTestRays(std::size_t num_rays)
{
    numTestRays = num_rays;

	probeSurfPoints.resize(num_rays);
	hitRaysMask.resize(num_rays);

	genSphereSurfacePoints();
}

std::size_t Chem::BuriednessScore::getNumTestRays() const
{
    return numTestRays;
}

void Chem::BuriednessScore::setAtom3DCoordinatesFunction(const Atom3DCoordinatesFunction& func)
{
	coordsFunc = func;
}

const Chem::Atom3DCoordinatesFunction& Chem::BuriednessScore::getAtom3DCoordinatesFunction() const
{
	return coordsFunc;
}
	
double Chem::BuriednessScore::operator()(const Math::Vector3D& pos, const AtomContainer& atoms)
{
    if (numTestRays == 0)
		return 0.0;

	Math::Vector3D tmp;

    hitRaysMask.reset();
	
    for (AtomContainer::ConstAtomIterator it = atoms.getAtomsBegin(), end = atoms.getAtomsEnd(); it != end; ++it) {
		const Atom& atom = *it;
		const Math::Vector3D& atom_pos = coordsFunc(atom);
		double vdw_radius = getVdWRadius(atom);
		
		tmp.assign(atom_pos - pos);

		double atom_dist = length(tmp);

		if (atom_dist < (vdw_radius + minVdWSurfaceDist))
			return 0.0;

		if (atom_dist > probeRadius)
			continue;

		for (std::size_t i = 0; i < numTestRays; i++) {
			if (hitRaysMask.test(i))
				continue;

			double ang_cos = angleCos(probeSurfPoints[i], tmp, atom_dist);

			if (ang_cos < 0.0)
				continue;

			double ray_atom_dist = std::sqrt(1 - ang_cos * ang_cos) * atom_dist;

			if (ray_atom_dist <= vdw_radius)
				hitRaysMask.set(i);
		}
	}
    
    return (double(hitRaysMask.count()) / numTestRays);
}

void Chem::BuriednessScore::genSphereSurfacePoints()
{
	// Golden section spiral point distribution

    double inc = M_PI * (3.0 - std::sqrt(5.0));
    double off = 2.0 / numTestRays;

	for (std::size_t i = 0; i < numTestRays; i++) {
		double y = i * off - 1.0 + off * 0.5;
		double r = std::sqrt(1.0 - y * y);
		double phi = i * inc;
		
		probeSurfPoints[i](0) = std::cos(phi) * r;
		probeSurfPoints[i](1) = y;
		probeSurfPoints[i](2) = std::sin(phi) * r;
	}
}
