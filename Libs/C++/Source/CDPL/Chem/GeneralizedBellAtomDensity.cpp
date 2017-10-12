/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * GeneralizedBellAtomDensity.cpp 
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

#include "CDPL/Chem/GeneralizedBellAtomDensity.hpp"
#include "CDPL/Chem/AtomFunctions.hpp"
#include "CDPL/Math/SpecialFunctions.hpp"


using namespace CDPL; 


const double Chem::GeneralizedBellAtomDensity::DEF_PROBE_RADIUS          = 0.0;
const double Chem::GeneralizedBellAtomDensity::DEF_RADIUS_SCALING_FACTOR = 1.0;


double Chem::GeneralizedBellAtomDensity::getProbeRadius() const
{
    return probeRadius;
}

double Chem::GeneralizedBellAtomDensity::getRadiusScalingFactor() const
{
    return radiusScalingFactor;
}

double Chem::GeneralizedBellAtomDensity::operator()(const Math::Vector3D& pos, const Math::Vector3D& atom_pos, const Atom& atom) const
{
    Math::Vector3D tmp;

	tmp.assign(atom_pos);
	tmp.minusAssign(pos);

	double dist = length(tmp);
	double vdw_radius = getVdWRadius(atom);

	return Math::generalizedBell(dist, (vdw_radius + probeRadius) * radiusScalingFactor, 10.0, 0.0);
}
