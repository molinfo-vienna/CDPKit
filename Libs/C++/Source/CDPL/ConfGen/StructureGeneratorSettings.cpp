/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * StructureGeneratorSettings.cpp 
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

#include "CDPL/ConfGen/StructureGeneratorSettings.hpp"
#include "CDPL/ConfGen/ForceFieldType.hpp"


using namespace CDPL;


ConfGen::StructureGeneratorSettings::StructureGeneratorSettings():
	fromScratch(true), timeout(5 * 60 * 1000), 
	forceFieldType(ForceFieldType::MMFF94S_NO_ESTAT), strictParam(true), 
	maxNumRefIters(0), refStopGrad(0.25), minMacrocycleSize(14)
{}

void ConfGen::StructureGeneratorSettings::generateCoordinatesFromScratch(bool generate)
{
	fromScratch = generate;
}
	
bool ConfGen::StructureGeneratorSettings::generateCoordinatesFromScratch() const
{
	return fromScratch;
}

void ConfGen::StructureGeneratorSettings::setTimeout(std::size_t mil_secs)
{
	timeout = mil_secs;
}

std::size_t ConfGen::StructureGeneratorSettings::getTimeout() const
{
	return timeout;
}

void ConfGen::StructureGeneratorSettings::setForceFieldType(unsigned int type)
{
	forceFieldType = type;
}
	    
unsigned int ConfGen::StructureGeneratorSettings::getForceFieldType() const
{
	return forceFieldType;
}
			
void ConfGen::StructureGeneratorSettings::strictForceFieldParameterization(bool strict)
{
	strictParam = strict;
}

bool ConfGen::StructureGeneratorSettings::strictForceFieldParameterization() const
{
	return strictParam;
}

void ConfGen::StructureGeneratorSettings::setMaxNumRefinementIterations(std::size_t max_iter)
{
	maxNumRefIters = max_iter;
}

std::size_t ConfGen::StructureGeneratorSettings::getMaxNumRefinementIterations() const
{
	return maxNumRefIters;
}

void ConfGen::StructureGeneratorSettings::setRefinementStopGradient(double grad_norm)
{
	refStopGrad = grad_norm;
}

double ConfGen::StructureGeneratorSettings::getRefinementStopGradient() const
{
	return refStopGrad;
}

void ConfGen::StructureGeneratorSettings::setMinMacrocycleSize(std::size_t min_size)
{
	minMacrocycleSize = min_size;
}

std::size_t ConfGen::StructureGeneratorSettings::getMinMacrocycleSize() const
{
	return minMacrocycleSize;
}

ConfGen::FragmentConformerGeneratorSettings& ConfGen::StructureGeneratorSettings::getFragmentBuildSettings()
{
	return fragBuildSettings;
}

const ConfGen::FragmentConformerGeneratorSettings& ConfGen::StructureGeneratorSettings::getFragmentBuildSettings() const
{
	return fragBuildSettings;
}
