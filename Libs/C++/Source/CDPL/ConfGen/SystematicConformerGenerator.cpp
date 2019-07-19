/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * SystematicConformerGenerator.cpp 
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

#include "SystematicConformerGeneratorImpl.hpp"


using namespace CDPL;


// Settings

const std::size_t  ConfGen::SystematicConformerGenerator::Settings::DEF_TIMEOUT;
const std::size_t  ConfGen::SystematicConformerGenerator::Settings::DEF_MAX_FRAG_BUILD_TIME;
const unsigned int ConfGen::SystematicConformerGenerator::Settings::DEF_SEARCH_FORCE_FIELD_TYPE;
const unsigned int ConfGen::SystematicConformerGenerator::Settings::DEF_BUILD_FORCE_FIELD_TYPE;
const double       ConfGen::SystematicConformerGenerator::Settings::DEF_ENERGY_WINDOW             = 10.0;


ConfGen::SystematicConformerGenerator::Settings::Settings(): 
	hRotors(false), enumRings(true), reuseExistingCoords(false), eWindow(DEF_ENERGY_WINDOW),
	timeout(DEF_TIMEOUT), maxFragBuildTime(DEF_MAX_FRAG_BUILD_TIME), searchFFieldType(DEF_SEARCH_FORCE_FIELD_TYPE),
	buildFFieldType(DEF_BUILD_FORCE_FIELD_TYPE), strictAtomTyping(true),
	fragLib(FragmentLibrary::get()), torLib(TorsionLibrary::get())
{}

void ConfGen::SystematicConformerGenerator::Settings::enableHydrogenRotors(bool enable)
{
	hRotors = enable; 
}

bool ConfGen::SystematicConformerGenerator::Settings::hydrogenRotorsEnabled() const
{
	return hRotors;
}

void ConfGen::SystematicConformerGenerator::Settings::enumerateRings(bool enumerate)
{
	enumRings = enumerate;
}

bool ConfGen::SystematicConformerGenerator::Settings::ringsEnumerated() const
{
	return enumRings;
}

void ConfGen::SystematicConformerGenerator::Settings::reuseExistingCoordinates(bool reuse)
{
	reuseExistingCoords = reuse;
}

bool ConfGen::SystematicConformerGenerator::Settings::existingCoordinatesReused() const
{
	return reuseExistingCoords;
}

void ConfGen::SystematicConformerGenerator::Settings::setEnergyWindow(double win_size)
{
	eWindow = win_size;
}

double ConfGen::SystematicConformerGenerator::Settings::getEnergyWindow() const
{
	return eWindow;
}

void ConfGen::SystematicConformerGenerator::Settings::setTimeout(std::size_t mil_secs)
{
	timeout = mil_secs;
}

std::size_t ConfGen::SystematicConformerGenerator::Settings::getTimeout() const
{
	return timeout;
}

void ConfGen::SystematicConformerGenerator::Settings::setMaxFragmentBuildTime(std::size_t mil_secs)
{
	maxFragBuildTime = mil_secs;
}

std::size_t ConfGen::SystematicConformerGenerator::Settings::getMaxFragmentBuildTime() const
{
	return maxFragBuildTime;
}

void ConfGen::SystematicConformerGenerator::Settings::setSearchForceFieldType(unsigned int type)
{
	searchFFieldType = type;
}
	    
unsigned int ConfGen::SystematicConformerGenerator::Settings::getSearchForceFieldType() const
{
	return searchFFieldType;
}

void ConfGen::SystematicConformerGenerator::Settings::setBuildForceFieldType(unsigned int type)
{
	buildFFieldType = type;
}
	    
unsigned int ConfGen::SystematicConformerGenerator::Settings::getBuildForceFieldType() const
{
	return buildFFieldType;
}

void ConfGen::SystematicConformerGenerator::Settings::performStrictAtomTyping(bool strict)
{
	strictAtomTyping = strict;
}

bool ConfGen::SystematicConformerGenerator::Settings::strictAtomTypingPerformed() const
{
	return strictAtomTyping;
}

void ConfGen::SystematicConformerGenerator::Settings::setFragmentLibrary(const FragmentLibrary::SharedPointer& lib)
{
	fragLib = lib;
}

const ConfGen::FragmentLibrary::SharedPointer& 
ConfGen::SystematicConformerGenerator::Settings::getFragmentLibrary() const
{
	return fragLib;
}

void ConfGen::SystematicConformerGenerator::Settings::setTorsionLibrary(const TorsionLibrary::SharedPointer& lib)
{
	torLib = lib;
}

const ConfGen::TorsionLibrary::SharedPointer& 
ConfGen::SystematicConformerGenerator::Settings::getTorsionLibrary() const
{
	return torLib;
}


// SystematicConformerGenerator

ConfGen::SystematicConformerGenerator::SystematicConformerGenerator(): impl(new SystematicConformerGeneratorImpl())
{}

void ConfGen::SystematicConformerGenerator::applySettings(const Settings& settings)
{
	impl->applySettings(settings);
}

const ConfGen::SystematicConformerGenerator::Settings& 
ConfGen::SystematicConformerGenerator::getSettings() const
{
	return impl->getSettings();
}

ConfGen::SystematicConformerGenerator::Status ConfGen::SystematicConformerGenerator::generate(const Chem::MolecularGraph& molgraph)
{
	return impl->generate(molgraph);
}
