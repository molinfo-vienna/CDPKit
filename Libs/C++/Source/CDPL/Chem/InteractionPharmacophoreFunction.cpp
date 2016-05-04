/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * InteractionPharmacophoreFunction.cpp 
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

#include "CDPL/Chem/PharmacophoreFunctions.hpp"
#include "CDPL/Chem/FeatureFunctions.hpp"
#include "CDPL/Chem/Entity3DFunctions.hpp"
#include "CDPL/Chem/Pharmacophore.hpp"
#include "CDPL/Chem/Feature.hpp"
#include "CDPL/Chem/FeatureType.hpp"
#include "CDPL/Chem/FeatureGeometry.hpp"


using namespace CDPL; 


void Chem::buildInteractionPharmacophore(Pharmacophore& pharm, const FeatureMapping& iactions)
{
	for (FeatureMapping::ConstEntryIterator it = iactions.getEntriesBegin(), end = iactions.getEntriesEnd(); it != end; ) {
		const Feature& ftr1 = *it->first;

		if (hasGeometry(ftr1) && getGeometry(ftr1) == FeatureGeometry::VECTOR && has3DCoordinates(ftr1)) {
			double dir_factor = 0.0;

			switch (getType(ftr1)) {

				case FeatureType::H_BOND_ACCEPTOR:
					dir_factor = -1.0;
					break;

				case FeatureType::H_BOND_DONOR:
					dir_factor = 1.0;

				default:
					break;
			}

			if (dir_factor != 0.0) {
				bool created_ftrs = false;
				const Math::Vector3D& ftr1_pos = get3DCoordinates(ftr1);

				for ( ; it != end && &ftr1 == it->first; ++it) {
					const Feature& ftr2 = *it->second;

					if (!has3DCoordinates(ftr2))
						continue;
					
					Feature& new_ftr = (pharm.addFeature() = ftr1);
					Math::Vector3D orient = get3DCoordinates(ftr2);
					
					orient.minusAssign(ftr1_pos);

					double len = length(orient);

					orient *= dir_factor / len; 

					setOrientation(new_ftr, orient);
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
