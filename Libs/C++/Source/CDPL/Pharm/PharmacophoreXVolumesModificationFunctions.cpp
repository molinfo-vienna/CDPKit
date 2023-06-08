/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * PharmacophoreXVolumesModificationFunctions.cpp 
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

#include "CDPL/Pharm/PharmacophoreFunctions.hpp"
#include "CDPL/Pharm/Pharmacophore.hpp"
#include "CDPL/Pharm/Feature.hpp"
#include "CDPL/Pharm/FeatureFunctions.hpp"
#include "CDPL/Pharm/FeatureType.hpp"
#include "CDPL/Chem/AtomContainer.hpp"
#include "CDPL/Chem/Atom.hpp"
#include "CDPL/Chem/Entity3DFunctions.hpp"
#include "CDPL/MolProp/AtomFunctions.hpp"


using namespace CDPL; 


bool Pharm::removeExclusionVolumesWithClashes(Pharmacophore& pharm, const Chem::AtomContainer& cntnr,
											  const Chem::Atom3DCoordinatesFunction& coords_func, double vdw_scaling_fact)
{
	bool modif = false;

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

			tmp = xvol_pos;
			tmp.minusAssign(atom_pos);

			if ((length(tmp) - xvol_tol - MolProp::getVdWRadius(atom) * vdw_scaling_fact) < 0.0) {
				clash = true;
				break;;
			}
		}

		if (clash) {
			pharm.removeFeature(i);
			modif = true;
			continue;
		}

		i++;
	}

	return modif;
}

bool Pharm::resizeExclusionVolumesWithClashes(Pharmacophore& pharm, const Chem::AtomContainer& cntnr,
											  const Chem::Atom3DCoordinatesFunction& coords_func, double vdw_scaling_fact)
{
	bool modif = false;

	for (std::size_t i = 0; i < pharm.getNumFeatures(); ) {
		Feature& ftr = pharm.getFeature(i);

		if (getType(ftr) != FeatureType::EXCLUSION_VOLUME) {
			i++;
			continue;
		}

		const Math::Vector3D& xvol_pos = get3DCoordinates(ftr);
		double xvol_tol = getTolerance(ftr);
		Math::Vector3D tmp;
		bool remove = false;

		for (Chem::AtomContainer::ConstAtomIterator it = cntnr.getAtomsBegin(), end = cntnr.getAtomsEnd(); it != end; ++it) {
			const Chem::Atom& atom = *it;
			const Math::Vector3D& atom_pos = coords_func(atom);

			tmp = xvol_pos;
			tmp.minusAssign(atom_pos);

			double inters = (length(tmp) - xvol_tol - MolProp::getVdWRadius(atom) * vdw_scaling_fact);

			if (inters < 0.0) {
				modif = true;

				if ((xvol_tol + inters) < 0.25) {
					remove = true;
					break;
				}

				xvol_tol += inters;
			}
		}

		if (remove) {
			pharm.removeFeature(i);
			continue;
		}

		setTolerance(ftr, xvol_tol);
		i++;
	}

	return modif;
}
