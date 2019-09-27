/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * ConformerGeneratorSettings.cpp 
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

#include "CDPL/ConfGen/ConformerGeneratorSettings.hpp"
#include "CDPL/ConfGen/ForceFieldType.hpp"


using namespace CDPL;


const ConfGen::ConformerGeneratorSettings ConfGen::ConformerGeneratorSettings::DEFAULT;


ConfGen::ConformerGeneratorSettings::ConformerGeneratorSettings():
	enumHetHRotors(false), enumRings(true), enumNitrogens(true), useExistingCoords(false), 
	eWindow(10.0), timeout(30 * 60 * 1000), forceFieldType(ForceFieldType::MMFF94S_NO_ESTAT), 
	strictParam(true), maxNumOutputConfs(100), minRMSD(0.5), fragLib(FragmentLibrary::get()), 
	torLib(TorsionLibrary::get()) 
{}

void ConfGen::ConformerGeneratorSettings::enumerateHeteroHydrogenRotors(bool enumerate)
{
	enumHetHRotors = enumerate;
}
				
bool ConfGen::ConformerGeneratorSettings::enumerateHeteroHydrogenRotors() const
{
	return enumHetHRotors;
}

void ConfGen::ConformerGeneratorSettings::enumerateRings(bool enumerate)
{
	enumRings = enumerate;
}

bool ConfGen::ConformerGeneratorSettings::ringsEnumerated() const
{
	return enumRings;
}

void ConfGen::ConformerGeneratorSettings::enumerateNitrogens(bool enumerate)
{
	enumNitrogens = enumerate;
}

bool ConfGen::ConformerGeneratorSettings::nitrogensEnumerated() const
{
	return enumNitrogens;
}

void ConfGen::ConformerGeneratorSettings::useExistingCoordinates(bool use)
{
	useExistingCoords = use;
}
	
bool ConfGen::ConformerGeneratorSettings::useExistingCoordinates() const
{
	return useExistingCoords;
}

void ConfGen::ConformerGeneratorSettings::setEnergyWindow(double win_size)
{
	eWindow = win_size;
}

double ConfGen::ConformerGeneratorSettings::getEnergyWindow() const
{
	return eWindow;
}

void ConfGen::ConformerGeneratorSettings::setTimeout(std::size_t mil_secs)
{
	timeout = mil_secs;
}

std::size_t ConfGen::ConformerGeneratorSettings::getTimeout() const
{
	return timeout;
}

void ConfGen::ConformerGeneratorSettings::setForceFieldType(unsigned int type)
{
	forceFieldType = type;
}
	    
unsigned int ConfGen::ConformerGeneratorSettings::getForceFieldType() const
{
	return forceFieldType;
}
			
void ConfGen::ConformerGeneratorSettings::strictForceFieldParameterization(bool strict)
{
	strictParam = strict;
}

bool ConfGen::ConformerGeneratorSettings::strictForceFieldParameterization() const
{
	return strictParam;
}
			
void ConfGen::ConformerGeneratorSettings::setMaxNumOutputConformers(std::size_t max_num)
{
	maxNumOutputConfs = max_num;
}

std::size_t ConfGen::ConformerGeneratorSettings::getMaxNumOutputConformers() const
{
	return maxNumOutputConfs;
}

void ConfGen::ConformerGeneratorSettings::setMinRMSD(double min_rmsd)
{
	minRMSD = min_rmsd;
}

double ConfGen::ConformerGeneratorSettings::getMinRMSD() const
{
	return minRMSD;
}

void ConfGen::ConformerGeneratorSettings::setFragmentLibrary(const FragmentLibrary::SharedPointer& lib)
{
	fragLib = lib;
}

const ConfGen::FragmentLibrary::SharedPointer& ConfGen::ConformerGeneratorSettings::getFragmentLibrary() const
{
	return fragLib;
}

void ConfGen::ConformerGeneratorSettings::setTorsionLibrary(const TorsionLibrary::SharedPointer& lib)
{
	torLib = lib;
}

const ConfGen::TorsionLibrary::SharedPointer& ConfGen::ConformerGeneratorSettings::getTorsionLibrary() const
{
	return torLib;
}

ConfGen::FragmentConformerGeneratorSettings& ConfGen::ConformerGeneratorSettings::getFragmentBuildSettings()
{
	return fragBuildSettings;
}

const ConfGen::FragmentConformerGeneratorSettings& ConfGen::ConformerGeneratorSettings::getFragmentBuildSettings() const
{
	return fragBuildSettings;
}
