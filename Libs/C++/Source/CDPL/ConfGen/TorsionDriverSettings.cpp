/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * TorsionDriverSettings.cpp 
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

#include "CDPL/ConfGen/TorsionDriverSettings.hpp"
#include "CDPL/ConfGen/ForceFieldType.hpp"
#include "CDPL/ForceField/MMFF94ElectrostaticInteractionParameterizer.hpp"


using namespace CDPL;


ConfGen::TorsionDriverSettings::TorsionDriverSettings(): 
	sampleHetAtomHs(false), sampleTolRanges(false), energyOrdered(true), eWindow(0.0), maxPoolSize(10000),
	forceFieldType(ForceFieldType::MMFF94S_EXT_NO_ESTAT), strictParam(true),
	dielectricConst(ForceField::MMFF94ElectrostaticInteractionParameterizer::DEF_DIELECTRIC_CONSTANT),
	distExponent(ForceField::MMFF94ElectrostaticInteractionParameterizer::DEF_DISTANCE_EXPONENT)
{}

void ConfGen::TorsionDriverSettings::sampleHeteroAtomHydrogens(bool sample)
{
	sampleHetAtomHs = sample;
}
				
bool ConfGen::TorsionDriverSettings::sampleHeteroAtomHydrogens() const
{
	return sampleHetAtomHs;
}

void ConfGen::TorsionDriverSettings::sampleAngleToleranceRanges(bool sample)
{
	sampleTolRanges = sample;
}
				
bool ConfGen::TorsionDriverSettings::sampleAngleToleranceRanges() const
{
	return sampleTolRanges;
}

void ConfGen::TorsionDriverSettings::orderByEnergy(bool order)
{
	energyOrdered = order;
}
				
bool ConfGen::TorsionDriverSettings::orderByEnergy() const
{
	return energyOrdered;
}

void ConfGen::TorsionDriverSettings::setEnergyWindow(double win_size)
{
	eWindow = win_size;
}

double ConfGen::TorsionDriverSettings::getEnergyWindow() const
{
	return eWindow;
}

void ConfGen::TorsionDriverSettings::setMaxPoolSize(std::size_t max_size)
{
	maxPoolSize = max_size;
}

std::size_t ConfGen::TorsionDriverSettings::getMaxPoolSize() const
{
	return maxPoolSize;
}

void ConfGen::TorsionDriverSettings::setForceFieldType(unsigned int type)
{
	forceFieldType = type;
}
	    
unsigned int ConfGen::TorsionDriverSettings::getForceFieldType() const
{
	return forceFieldType;
}
			
void ConfGen::TorsionDriverSettings::strictForceFieldParameterization(bool strict)
{
	strictParam = strict;
}

bool ConfGen::TorsionDriverSettings::strictForceFieldParameterization() const
{
	return strictParam;
}

void ConfGen::TorsionDriverSettings::setDielectricConstant(double de_const)
{
	dielectricConst = de_const;
}

double ConfGen::TorsionDriverSettings::getDielectricConstant() const
{
	return dielectricConst;
}

void ConfGen::TorsionDriverSettings::setDistanceExponent(double exponent)
{
	distExponent = exponent;
}

double ConfGen::TorsionDriverSettings::getDistanceExponent() const
{
	return distExponent;
}
