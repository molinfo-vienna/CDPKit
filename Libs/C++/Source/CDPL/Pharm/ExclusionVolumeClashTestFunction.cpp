/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * ExclusionVolumeClashTestFunction.cpp 
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

#include <vector>
#include <algorithm>
#include <iterator>

#include <boost/bind.hpp>

#include "CDPL/Pharm/PharmacophoreFunctions.hpp"
#include "CDPL/Pharm/Feature.hpp"
#include "CDPL/Pharm/FeatureType.hpp"
#include "CDPL/Pharm/FeatureFunctions.hpp"
#include "CDPL/Pharm/Pharmacophore.hpp"
#include "CDPL/Chem/Atom.hpp"
#include "CDPL/Chem/AtomContainer.hpp"
#include "CDPL/Chem/AtomFunctions.hpp"
#include "CDPL/Chem/Entity3DFunctions.hpp"
#include "CDPL/Math/VectorAdapter.hpp"


using namespace CDPL; 


bool Pharm::checkExclusionVolumeClash(const Pharmacophore& pharm, const Chem::AtomContainer& cntnr, 
									  const Chem::Atom3DCoordinatesFunction& coords_func, 
									  const Math::Matrix4D& xform, bool vdw)
{
	Math::Vector3D tmp;
	std::vector<double> vdw_radii;
	std::vector<Math::Vector3D> atom_coords;
	std::size_t num_atoms = cntnr.getNumAtoms();

	atom_coords.reserve(num_atoms);
	vdw_radii.reserve(num_atoms);

	for (Chem::AtomContainer::ConstAtomIterator it = cntnr.getAtomsBegin(), end = cntnr.getAtomsEnd(); it != end; ++it) {
		tmp.assign(range(prod(xform, homog(coords_func(*it))), 0, 3));
		atom_coords.push_back(tmp);
	}

	if (vdw) 
		std::transform(cntnr.getAtomsBegin(), cntnr.getAtomsEnd(), std::back_inserter(vdw_radii), 
					   boost::bind(&Chem::getVdWRadius, _1));
	else
		vdw_radii.resize(num_atoms, 0.0);

	for (Pharmacophore::ConstFeatureIterator it = pharm.getFeaturesBegin(), 
			 end = pharm.getFeaturesEnd(); it != end; ++it) {

		const Feature& ftr = *it;

		if (getDisabledFlag(ftr))
			continue;

		if (getType(ftr) != FeatureType::X_VOLUME)
			continue;

		const Math::Vector3D& ftr_pos = get3DCoordinates(ftr);
		double tol = getTolerance(ftr);

		for (std::size_t i = 0; i < num_atoms; i++) {
			tmp.assign(ftr_pos);
			tmp.minusAssign(atom_coords[i]);

			double dist = length(tmp);

			if ((dist - tol - vdw_radii[i]) < 0.0)
				return false;
		}
	}

    return true;
}
