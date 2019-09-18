/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * RandomStructureGeneratorSettings.cpp 
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

#include "CDPL/ConfGen/RandomStructureGeneratorSettings.hpp"
#include "CDPL/ConfGen/ForceFieldType.hpp"


using namespace CDPL;


const ConfGen::RandomStructureGeneratorSettings ConfGen::RandomStructureGeneratorSettings::DEFAULT;


ConfGen::RandomStructureGeneratorSettings::RandomStructureGeneratorSettings(): 
    atomConfig(true), bondConfig(true), maxNumStructGenTrials(10), maxNumRefIters(0), 
	refStopGrad(0.1), timeout(600 * 1000), strictParam(true), forceFieldType(ForceFieldType::MMFF94S_NO_ESTAT) 
{}

void ConfGen::RandomStructureGeneratorSettings::regardAtomConfiguration(bool regard)
{
    atomConfig = regard;
}

bool ConfGen::RandomStructureGeneratorSettings::regardAtomConfiguration() const
{
    return atomConfig;
}

void ConfGen::RandomStructureGeneratorSettings::regardBondConfiguration(bool regard)
{
    bondConfig = regard;
}

bool ConfGen::RandomStructureGeneratorSettings::regardBondConfiguration() const
{
    return bondConfig;
}

void ConfGen::RandomStructureGeneratorSettings::setMaxNumStructureGenerationTrials(std::size_t max_num)
{
	maxNumStructGenTrials = max_num;
}

std::size_t ConfGen::RandomStructureGeneratorSettings::getMaxNumStructureGenerationTrials() const
{
	return maxNumStructGenTrials;
}

void ConfGen::RandomStructureGeneratorSettings::setMaxNumRefinementIterations(std::size_t max_num)
{
	maxNumRefIters = max_num;
}

std::size_t ConfGen::RandomStructureGeneratorSettings::getMaxNumRefinementIterations() const
{
	return maxNumRefIters;
}

void ConfGen::RandomStructureGeneratorSettings::setRefinementStopGradient(double grad_norm)
{
	refStopGrad = grad_norm;
}

double ConfGen::RandomStructureGeneratorSettings::getRefinementStopGradient() const
{
	return refStopGrad;
}

void ConfGen::RandomStructureGeneratorSettings::setTimeout(std::size_t mil_secs)
{
	timeout = mil_secs;
}

std::size_t ConfGen::RandomStructureGeneratorSettings::getTimeout() const
{
	return timeout;
}

void ConfGen::RandomStructureGeneratorSettings::strictForceFieldParameterization(bool strict)
{
	strictParam = strict;
}

bool ConfGen::RandomStructureGeneratorSettings::strictForceFieldParameterization() const
{
	return strictParam;
}
	
void ConfGen::RandomStructureGeneratorSettings::setForceFieldType(unsigned int type)
{
	forceFieldType = type;
}
	
unsigned int ConfGen::RandomStructureGeneratorSettings::getForceFieldType() const
{
	return forceFieldType;
}
