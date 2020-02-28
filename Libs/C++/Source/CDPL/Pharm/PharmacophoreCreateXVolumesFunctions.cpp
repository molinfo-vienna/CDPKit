/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * PharmacophoreCreateXVolumesFunctions.cpp 
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

#include <vector>
#include <utility>

#include "CDPL/Pharm/Pharmacophore.hpp"
#include "CDPL/Pharm/Feature.hpp"
#include "CDPL/Pharm/PharmacophoreFunctions.hpp"
#include "CDPL/Pharm/FeatureFunctions.hpp"
#include "CDPL/Pharm/FeatureType.hpp"
#include "CDPL/Pharm/FeatureGeometry.hpp"
#include "CDPL/Chem/Atom.hpp"
#include "CDPL/Chem/AtomFunctions.hpp"
#include "CDPL/Chem/Entity3DFunctions.hpp"
#include "CDPL/Math/Vector.hpp"


using namespace CDPL; 


void Pharm::createExclusionVolumes(Pharmacophore& pharm, const Chem::AtomContainer& cntnr, 
								   const Chem::Atom3DCoordinatesFunction& coords_func, 
								   double tol, double min_dist, bool rel_dist, bool append)
{
	using namespace Chem;

	if (!append)
		pharm.clear();

	typedef std::vector<Math::Vector3D> PositionArray;
	typedef std::vector<double> ToleranceArray;

	PositionArray xvol_positions;
	ToleranceArray xvol_tolerances;

	for (Pharmacophore::ConstFeatureIterator it = pharm.getFeaturesBegin(), end = pharm.getFeaturesEnd(); it != end; ++it) {
		const Feature& ftr = *it;

		if (getType(ftr) != FeatureType::X_VOLUME)
			continue;

		xvol_positions.push_back(get3DCoordinates(ftr));

		if (rel_dist)
			xvol_tolerances.push_back(getTolerance(ftr));
	}

	for (AtomContainer::ConstAtomIterator it = cntnr.getAtomsBegin(), end = cntnr.getAtomsEnd(); it != end; ++it) {
		const Atom& atom = *it;
		const Math::Vector3D& atom_pos = coords_func(atom);
		double xvol_tol = (tol > 0.0 ? tol : getVdWRadius(atom)); 
		bool invalid = false;

		for (std::size_t i = 0, num_xvols = xvol_positions.size(); i < num_xvols; i++) {
			Math::Vector3D tmp = xvol_positions[i] - atom_pos;
			double dist = length(tmp);

			if (rel_dist) 
				dist -= xvol_tol + xvol_tolerances[i];

			if (dist < min_dist) {
				invalid = true;
				break;
			}
		}

		if (invalid)
			continue;

		Feature& xvol = pharm.addFeature();

		set3DCoordinates(xvol, atom_pos);
		setTolerance(xvol, xvol_tol);
		setType(xvol, FeatureType::X_VOLUME);
		setGeometry(xvol, FeatureGeometry::SPHERE);

		Fragment::SharedPointer substruct(new Fragment());

		substruct->addAtom(atom);
		setSubstructure(xvol, substruct);

		xvol_positions.push_back(atom_pos);

		if (rel_dist)
			xvol_tolerances.push_back(xvol_tol);
	}
}

void Pharm::createExclusionVolumes(Pharmacophore& pharm, const FeatureContainer& cntnr, 
								   double tol, double min_dist, bool rel_dist, bool append)
{
	using namespace Chem;

	if (!append)
		pharm.clear();

	typedef std::vector<Math::Vector3D> PositionArray;
	typedef std::vector<double> ToleranceArray;

	PositionArray xvol_positions;
	ToleranceArray xvol_tolerances;

	for (Pharmacophore::ConstFeatureIterator it = pharm.getFeaturesBegin(), end = pharm.getFeaturesEnd(); it != end; ++it) {
		const Feature& ftr = *it;

		if (getType(ftr) != FeatureType::X_VOLUME)
			continue;

		xvol_positions.push_back(get3DCoordinates(ftr));

		if (rel_dist)
			xvol_tolerances.push_back(getTolerance(ftr));
	}

	for (FeatureContainer::ConstFeatureIterator it = cntnr.getFeaturesBegin(), end = cntnr.getFeaturesEnd(); it != end; ++it) {
		const Feature& ftr = *it;
		const Math::Vector3D& ftr_pos = get3DCoordinates(ftr);
		double xvol_tol = (tol > 0.0 ? tol : getTolerance(ftr)); 
		bool invalid = false;

		for (std::size_t i = 0, num_xvols = xvol_positions.size(); i < num_xvols; i++) {
			Math::Vector3D tmp = xvol_positions[i] - ftr_pos;
			double dist = length(tmp);

			if (rel_dist) 
				dist -= xvol_tol + xvol_tolerances[i];

			if (dist < min_dist) {
				invalid = true;
				break;
			}
		}

		if (invalid)
			continue;

		Feature& xvol = pharm.addFeature();

		set3DCoordinates(xvol, ftr_pos);
		setTolerance(xvol, xvol_tol);
		setType(xvol, FeatureType::X_VOLUME);
		setGeometry(xvol, FeatureGeometry::SPHERE);

		if (hasSubstructure(ftr))
			setSubstructure(xvol, getSubstructure(ftr));

		xvol_positions.push_back(ftr_pos);

		if (rel_dist)
			xvol_tolerances.push_back(xvol_tol);
	}
}
