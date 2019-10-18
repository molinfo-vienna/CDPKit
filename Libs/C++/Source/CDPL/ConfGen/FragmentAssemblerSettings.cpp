/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * FragmentAssemblerSettings.cpp 
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

#include "CDPL/ConfGen/FragmentAssemblerSettings.hpp"
#include "CDPL/ConfGen/ForceFieldType.hpp"
#include "CDPL/ConfGen/NitrogenEnumerationMode.hpp"


using namespace CDPL;


const ConfGen::FragmentAssemblerSettings ConfGen::FragmentAssemblerSettings::DEFAULT;


ConfGen::FragmentAssemblerSettings::FragmentAssemblerSettings():
	enumRings(true), nitrogenEnumMode(NitrogenEnumerationMode::UNSPECIFIED_STEREO),
	generateCoords(true), eWindow(20.0), forceFieldType(ForceFieldType::MMFF94S_NO_ESTAT),
	strictParam(true), fragLib(FragmentLibrary::get()), torLib(TorsionLibrary::get()) 
{}

void ConfGen::FragmentAssemblerSettings::enumerateRings(bool enumerate)
{
	enumRings = enumerate;
}

bool ConfGen::FragmentAssemblerSettings::enumerateRings() const
{
	return enumRings;
}

void ConfGen::FragmentAssemblerSettings::setNitrogenEnumerationMode(unsigned int mode)
{
	nitrogenEnumMode = mode;
}

unsigned int ConfGen::FragmentAssemblerSettings::getNitrogenEnumerationMode() const
{
	return nitrogenEnumMode;
}

void ConfGen::FragmentAssemblerSettings::generateCoordinates(bool generate)
{
	generateCoords = generate;
}
	
bool ConfGen::FragmentAssemblerSettings::generateCoordinates() const
{
	return generateCoords;
}

void ConfGen::FragmentAssemblerSettings::setEnergyWindow(double win_size)
{
	eWindow = win_size;
}

double ConfGen::FragmentAssemblerSettings::getEnergyWindow() const
{
	return eWindow;
}

void ConfGen::FragmentAssemblerSettings::setForceFieldType(unsigned int type)
{
	forceFieldType = type;
}
	    
unsigned int ConfGen::FragmentAssemblerSettings::getForceFieldType() const
{
	return forceFieldType;
}
			
void ConfGen::FragmentAssemblerSettings::strictForceFieldParameterization(bool strict)
{
	strictParam = strict;
}

bool ConfGen::FragmentAssemblerSettings::strictForceFieldParameterization() const
{
	return strictParam;
}

void ConfGen::FragmentAssemblerSettings::setFragmentLibrary(const FragmentLibrary::SharedPointer& lib)
{
	fragLib = lib;
}

const ConfGen::FragmentLibrary::SharedPointer& ConfGen::FragmentAssemblerSettings::getFragmentLibrary() const
{
	return fragLib;
}

void ConfGen::FragmentAssemblerSettings::setTorsionLibrary(const TorsionLibrary::SharedPointer& lib)
{
	torLib = lib;
}

const ConfGen::TorsionLibrary::SharedPointer& ConfGen::FragmentAssemblerSettings::getTorsionLibrary() const
{
	return torLib;
}

ConfGen::FragmentConformerGeneratorSettings& ConfGen::FragmentAssemblerSettings::getFragmentBuildSettings()
{
	return fragBuildSettings;
}

const ConfGen::FragmentConformerGeneratorSettings& ConfGen::FragmentAssemblerSettings::getFragmentBuildSettings() const
{
	return fragBuildSettings;
}
