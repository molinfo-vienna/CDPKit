/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * ConformerDuplicateChecker.cpp 
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

#include "CDPL/ForceField/MMFF94EnergyFunctions.hpp"
#include "CDPL/ForceField/UtilityFunctions.hpp"

#include "ConformerDuplicateChecker.hpp"


using namespace CDPL;

	
ConfGen::ConformerDuplicateChecker::ConformerDuplicateChecker(const ForceField::MMFF94TorsionInteractionData& tor_ia_data):
	energyTol(0.05), angleTol(0.017), torIActionData(&tor_ia_data)
{}
	
void ConfGen::ConformerDuplicateChecker::setTorsionInteractionData(const ForceField::MMFF94TorsionInteractionData& tor_ia_data)
{
	torIActionData = &tor_ia_data;
}

const ForceField::MMFF94TorsionInteractionData& ConfGen::ConformerDuplicateChecker::setTorsionInteractionData() const
{
	return *torIActionData;
}

void ConfGen::ConformerDuplicateChecker::setEnergyTolerance(double tol)
{
	energyTol = tol;
}

double ConfGen::ConformerDuplicateChecker::getEnergyTolerance() const
{
	return energyTol;
}

void ConfGen::ConformerDuplicateChecker::setAngleTolerance(double tol)
{
	angleTol = tol;
}

double ConfGen::ConformerDuplicateChecker::getAngleTolerance() const
{
	return angleTol;
}

void ConfGen::ConformerDuplicateChecker::reset()
{
	registeredConfs.clear();
}

bool ConfGen::ConformerDuplicateChecker::isDuplicate(const Math::Vector3DArray& conf_coords)
{
	using namespace ForceField;
	using namespace Math;

	const Vector3DArray::StorageType& coords_data = conf_coords.getData();

	double energy = calcMMFF94TorsionEnergy<double>(torIActionData->getElementsBegin(), torIActionData->getElementsEnd(), coords_data);
	double angle_sum = 0.0;

	for (MMFF94TorsionInteractionData::ConstElementIterator it = torIActionData->getElementsBegin(), end = torIActionData->getElementsEnd(); it != end; ++it) {
		const MMFF94TorsionInteraction& ia = *it;

		angle_sum += std::acos(calcDihedralAngleCos<double>(coords_data[ia.getTerminalAtom1Index()].getData(), coords_data[ia.getCenterAtom1Index()].getData(), 
															coords_data[ia.getCenterAtom2Index()].getData(), coords_data[ia.getTerminalAtom2Index()].getData()));
	}

	double tot_angle_tol = torIActionData->getSize() * angleTol;

	if (!registeredConfs.empty()) {
		EnergyToAngleMap::const_iterator ub = registeredConfs.upper_bound(energy);

		for (EnergyToAngleMap::const_iterator it = ub, end = registeredConfs.end(); it != end && ((it->first - energy) < energyTol); ++it)
			if (std::abs(it->second - angle_sum) < tot_angle_tol)
				return true;
		
		if (ub != registeredConfs.begin())
			for (EnergyToAngleMap::const_iterator it = --ub, beg = registeredConfs.begin(); (energy - it->first) < energyTol; --it) {
				if (std::abs(it->second - angle_sum) < tot_angle_tol)
					return true;

				if (it == beg)
					break;
			}
	}

	registeredConfs.insert(EnergyToAngleMap::value_type(energy, angle_sum));

	return false;
}
