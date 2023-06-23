/* 
 * FragmentAssemblerSettings.cpp 
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

#include "CDPL/ConfGen/FragmentAssemblerSettings.hpp"
#include "CDPL/ConfGen/ForceFieldType.hpp"
#include "CDPL/ConfGen/NitrogenEnumerationMode.hpp"


using namespace CDPL;


ConfGen::FragmentAssemblerSettings::FragmentAssemblerSettings():
    enumRings(true), nitrogenEnumMode(NitrogenEnumerationMode::UNSPECIFIED_STEREO),
    fromScratch(true)
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

void ConfGen::FragmentAssemblerSettings::generateCoordinatesFromScratch(bool generate)
{
    fromScratch = generate;
}
    
bool ConfGen::FragmentAssemblerSettings::generateCoordinatesFromScratch() const
{
    return fromScratch;
}

ConfGen::FragmentConformerGeneratorSettings& ConfGen::FragmentAssemblerSettings::getFragmentBuildSettings()
{
    return fragBuildSettings;
}

const ConfGen::FragmentConformerGeneratorSettings& ConfGen::FragmentAssemblerSettings::getFragmentBuildSettings() const
{
    return fragBuildSettings;
}
