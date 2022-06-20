/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * PharmacophoreBuildInteractionPharmFunction.cpp 
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
#include "CDPL/Pharm/FeatureFunctions.hpp"
#include "CDPL/Pharm/Pharmacophore.hpp"
#include "CDPL/Pharm/Feature.hpp"
#include "CDPL/Pharm/FeatureType.hpp"
#include "CDPL/Pharm/FeatureGeometry.hpp"
#include "CDPL/Pharm/FeatureMapping.hpp"
#include "CDPL/Chem/Entity3DFunctions.hpp"


using namespace CDPL; 


void Pharm::buildInteractionPharmacophore(Pharmacophore& pharm, const FeatureMapping& iactions, bool append)
{
	if (!append)
		pharm.clear();

	for (FeatureMapping::ConstEntryIterator it = iactions.getEntriesBegin(), end = iactions.getEntriesEnd(); it != end; ) {
		if (!it->first || !it->second) {
			++it;
			continue;
		}

		const Feature& ftr1 = *it->first;

		if (has3DCoordinates(ftr1)) {
			double dir_factor = 0.0;

			switch (getType(ftr1)) {

				case FeatureType::H_BOND_ACCEPTOR:
				case FeatureType::HALOGEN_BOND_ACCEPTOR:
					dir_factor = -1.0;
					break;

				case FeatureType::H_BOND_DONOR:
				case FeatureType::HALOGEN_BOND_DONOR:
					dir_factor = 1.0;

				default:
					break;
			}

			if (dir_factor != 0.0) {
				bool created_ftrs = false;
				const Math::Vector3D& ftr1_pos = get3DCoordinates(ftr1);

				for ( ; it != end && &ftr1 == it->first; ++it) {
					if (!it->second)
						continue;

					const Feature& ftr2 = *it->second;

					if (!has3DCoordinates(ftr2))
						continue;
					
					Feature& new_ftr = (pharm.addFeature() = ftr1);
					Math::Vector3D orient = get3DCoordinates(ftr2);
					
					orient.minusAssign(ftr1_pos);

					double len = length(orient);

					orient *= dir_factor / len; 

					setOrientation(new_ftr, orient);
					setGeometry(new_ftr, FeatureGeometry::VECTOR);
					setLength(new_ftr, len);

					created_ftrs = true;
				}

				if (!created_ftrs)
					pharm.addFeature() = ftr1;

				continue;
			}
		}

		pharm.addFeature() = ftr1;
		
		for (++it; it != end && &ftr1 == it->first; ++it);
	}
}
