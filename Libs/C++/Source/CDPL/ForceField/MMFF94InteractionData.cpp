/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * MMFF94InteractionData.cpp 
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

#include "CDPL/ForceField/MMFF94InteractionData.hpp"


using namespace CDPL; 


const ForceField::MMFF94BondStretchingInteractionData& ForceField::MMFF94InteractionData::getBondStretchingInteractions() const
{
	return bondStretchingData;
}

ForceField::MMFF94BondStretchingInteractionData& ForceField::MMFF94InteractionData::getBondStretchingInteractions()
{
	return bondStretchingData;
}

const ForceField::MMFF94AngleBendingInteractionData& ForceField::MMFF94InteractionData::getAngleBendingInteractions() const
{
	return angleBendingData;
}

ForceField::MMFF94AngleBendingInteractionData& ForceField::MMFF94InteractionData::getAngleBendingInteractions()
{
	return angleBendingData;
}

const ForceField::MMFF94StretchBendInteractionData& ForceField::MMFF94InteractionData::getStretchBendInteractions() const
{
	return stretchBendData;
}

ForceField::MMFF94StretchBendInteractionData& ForceField::MMFF94InteractionData::getStretchBendInteractions()
{
	return stretchBendData;
}

const ForceField::MMFF94OutOfPlaneBendingInteractionData& ForceField::MMFF94InteractionData::getOutOfPlaneBendingInteractions() const
{
	return outOfPlaneData;
}

ForceField::MMFF94OutOfPlaneBendingInteractionData& ForceField::MMFF94InteractionData::getOutOfPlaneBendingInteractions()
{
	return outOfPlaneData;
}

const ForceField::MMFF94TorsionInteractionData& ForceField::MMFF94InteractionData::getTorsionInteractions() const
{
	return torsionData;
}

ForceField::MMFF94TorsionInteractionData& ForceField::MMFF94InteractionData::getTorsionInteractions()
{
	return torsionData;
}

const ForceField::MMFF94ElectrostaticInteractionData& ForceField::MMFF94InteractionData::getElectrostaticInteractions() const
{
	return electrostaticData;
}

ForceField::MMFF94ElectrostaticInteractionData& ForceField::MMFF94InteractionData::getElectrostaticInteractions()
{
	return electrostaticData;
}

const ForceField::MMFF94VanDerWaalsInteractionData& ForceField::MMFF94InteractionData::getVanDerWaalsInteractions() const
{
	return vanDerWaalsData;
}

ForceField::MMFF94VanDerWaalsInteractionData& ForceField::MMFF94InteractionData::getVanDerWaalsInteractions()
{
	return vanDerWaalsData;
}

void ForceField::MMFF94InteractionData::clear()
{
	bondStretchingData.clear();
	angleBendingData.clear();
	stretchBendData.clear();
	outOfPlaneData.clear();
	torsionData.clear();
	electrostaticData.clear();
	vanDerWaalsData.clear();
}

void ForceField::MMFF94InteractionData::swap(MMFF94InteractionData& ia_data)
{
	bondStretchingData.swap(ia_data.bondStretchingData);
	angleBendingData.swap(ia_data.angleBendingData);
	stretchBendData.swap(ia_data.stretchBendData);
	outOfPlaneData.swap(ia_data.outOfPlaneData);
	torsionData.swap(ia_data.torsionData);
	electrostaticData.swap(ia_data.electrostaticData);
	vanDerWaalsData.swap(ia_data.vanDerWaalsData);
}
