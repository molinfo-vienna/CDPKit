/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * StericAtomClashFactorCalculator.cpp 
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

#include "CDPL/Pharm/StericAtomClashFactorCalculator.hpp"
#include "CDPL/Chem/AtomContainer.hpp"
#include "CDPL/Chem/Atom.hpp"
#include "CDPL/Chem/AtomFunctions.hpp"


using namespace CDPL; 


const double Pharm::StericAtomClashFactorCalculator::DEF_PROBE_RADIUS = 1.0;


double Pharm::StericAtomClashFactorCalculator::getProbeRadius() const
{
    return probeRadius;
}

double Pharm::StericAtomClashFactorCalculator::operator()(const Math::Vector3D& pos, const Chem::AtomContainer& cntnr,
														  const Chem::Atom3DCoordinatesFunction& coords_func) const
{
    Math::Vector3D tmp;
    double clash_score = 0.0;

    for (Chem::AtomContainer::ConstAtomIterator it = cntnr.getAtomsBegin(), end = cntnr.getAtomsEnd(); it != end; ++it) {
		const Chem::Atom& atom = *it;

		tmp.assign(coords_func(atom));
		tmp.minusAssign(pos);

		double dist = length(tmp);
		double vdw_radius = getVdWRadius(atom);

		if (dist >= (vdw_radius + probeRadius))
			continue;
		
		if (dist < 0.000001)
			dist = 0.000001;

		double inv_dist_diff = 1.0 / dist - 1.0 / (vdw_radius + probeRadius);
		clash_score += 0.5 * inv_dist_diff * inv_dist_diff;
    }

	return (1.0 / (1.0 + clash_score));
}
