/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * PharmacophoreXVolumeRemoveFunction.cpp 
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

#include "CDPL/Pharm/PharmacophoreFunctions.hpp"
#include "CDPL/Pharm/Pharmacophore.hpp"
#include "CDPL/Pharm/Feature.hpp"
#include "CDPL/Pharm/FeatureFunctions.hpp"
#include "CDPL/Pharm/FeatureType.hpp"
#include "CDPL/Chem/AtomContainer.hpp"
#include "CDPL/Chem/Atom.hpp"
#include "CDPL/Chem/AtomFunctions.hpp"
#include "CDPL/Chem/Entity3DFunctions.hpp"


using namespace CDPL; 


bool Pharm::removeExclusionVolumesWithClashes(Pharmacophore& pharm, const Chem::AtomContainer& cntnr, 
											  const Chem::Atom3DCoordinatesFunction& coords_func)
{
	bool removed = false;

	for (std::size_t i = 0; i < pharm.getNumFeatures(); ) {
		const Feature& ftr = pharm.getFeature(i);

		if (getType(ftr) != FeatureType::EXCLUSION_VOLUME) {
			i++;
			continue;
		}

		const Math::Vector3D& xvol_pos = get3DCoordinates(ftr);
		double xvol_tol = getTolerance(ftr);
		Math::Vector3D tmp;
		bool clash = false;

		for (Chem::AtomContainer::ConstAtomIterator it = cntnr.getAtomsBegin(), end = cntnr.getAtomsEnd(); it != end; ++it) {
			const Chem::Atom& atom = *it;
			const Math::Vector3D& atom_pos = coords_func(atom);

			tmp.assign(xvol_pos);
			tmp.minusAssign(atom_pos);

			if ((length(tmp) - xvol_tol - getVdWRadius(atom)) < 0.0) {
				clash = true;
				break;;
			}
		}

		if (clash) {
			pharm.removeFeature(i);
			removed = true;
			continue;
		}

		i++;
	}

	return removed;
}
