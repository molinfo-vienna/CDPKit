/* 
 * StructureGeneratorSettings.cpp 
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

#include "CDPL/ConfGen/StructureGeneratorSettings.hpp"
#include "CDPL/ConfGen/ForceFieldType.hpp"
#include "CDPL/ConfGen/StructureGenerationMode.hpp"
#include "CDPL/ForceField/MMFF94ElectrostaticInteractionParameterizer.hpp"


using namespace CDPL;


ConfGen::StructureGeneratorSettings::StructureGeneratorSettings():
	generationMode(StructureGenerationMode::AUTO), fromScratch(true), sampleTolRanges(true), 
	timeout(20 * 60 * 1000), fragModeForceFieldType(ForceFieldType::MMFF94S_RTOR_NO_ESTAT), 
	dgModeForceFieldType(ForceFieldType::MMFF94S), strictParam(true), 
	dielectricConst(ForceField::MMFF94ElectrostaticInteractionParameterizer::DIELECTRIC_CONSTANT_WATER),
	distExponent(ForceField::MMFF94ElectrostaticInteractionParameterizer::DEF_DISTANCE_EXPONENT),
	maxNumRefIters(0), refTolerance(0.001), maxNumSampledConfs(50), convCheckCycleSize(10), 
	mcRotorBondCountThresh(10)
{}

void ConfGen::StructureGeneratorSettings::setGenerationMode(unsigned int mode)
{
	generationMode = mode;
}

unsigned int ConfGen::StructureGeneratorSettings::getGenerationMode() const
{
	return generationMode;
}

void ConfGen::StructureGeneratorSettings::generateCoordinatesFromScratch(bool generate)
{
	fromScratch = generate;
}
	
bool ConfGen::StructureGeneratorSettings::generateCoordinatesFromScratch() const
{
	return fromScratch;
}

void ConfGen::StructureGeneratorSettings::sampleAngleToleranceRanges(bool sample)
{
	sampleTolRanges = sample;
}
				
bool ConfGen::StructureGeneratorSettings::sampleAngleToleranceRanges() const
{
	return sampleTolRanges;
}

void ConfGen::StructureGeneratorSettings::setTimeout(std::size_t mil_secs)
{
	timeout = mil_secs;
}

std::size_t ConfGen::StructureGeneratorSettings::getTimeout() const
{
	return timeout;
}
		
void ConfGen::StructureGeneratorSettings::setFragmentModeForceFieldType(unsigned int type)
{
	fragModeForceFieldType = type;
}
	    
unsigned int ConfGen::StructureGeneratorSettings::getFragmentModeForceFieldType() const
{
	return fragModeForceFieldType;
}

void ConfGen::StructureGeneratorSettings::setDGModeForceFieldType(unsigned int type)
{
	dgModeForceFieldType = type;
}
		    
unsigned int ConfGen::StructureGeneratorSettings::getDGModeForceFieldType() const
{
	return dgModeForceFieldType;
}
    
void ConfGen::StructureGeneratorSettings::strictForceFieldParameterization(bool strict)
{
	strictParam = strict;
}

bool ConfGen::StructureGeneratorSettings::strictForceFieldParameterization() const
{
	return strictParam;
}

void ConfGen::StructureGeneratorSettings::setDielectricConstant(double de_const)
{
	dielectricConst = de_const;
}

double ConfGen::StructureGeneratorSettings::getDielectricConstant() const
{
	return dielectricConst;
}

void ConfGen::StructureGeneratorSettings::setDistanceExponent(double exponent)
{
	distExponent = exponent;
}

double ConfGen::StructureGeneratorSettings::getDistanceExponent() const
{
	return distExponent;
}

void ConfGen::StructureGeneratorSettings::setMaxNumRefinementIterations(std::size_t max_iter)
{
	maxNumRefIters = max_iter;
}

std::size_t ConfGen::StructureGeneratorSettings::getMaxNumRefinementIterations() const
{
	return maxNumRefIters;
}

void ConfGen::StructureGeneratorSettings::setRefinementTolerance(double tol)
{
	refTolerance = tol;
}

double ConfGen::StructureGeneratorSettings::getRefinementTolerance() const
{
	return refTolerance;
}

void ConfGen::StructureGeneratorSettings::setMaxNumSampledConformers(std::size_t max_num)
{
	maxNumSampledConfs = max_num;
}

std::size_t ConfGen::StructureGeneratorSettings::getMaxNumSampledConformers() const
{
	return maxNumSampledConfs;
}

void ConfGen::StructureGeneratorSettings::setConvergenceCheckCycleSize(std::size_t size)
{
	convCheckCycleSize = size;
}

std::size_t ConfGen::StructureGeneratorSettings::getConvergenceCheckCycleSize() const
{
	return convCheckCycleSize;
}

void ConfGen::StructureGeneratorSettings::setMacrocycleRotorBondCountThreshold(std::size_t min_count)
{
	mcRotorBondCountThresh = min_count;
}

std::size_t ConfGen::StructureGeneratorSettings::getMacrocycleRotorBondCountThreshold() const
{
	return mcRotorBondCountThresh;
}

ConfGen::FragmentConformerGeneratorSettings& ConfGen::StructureGeneratorSettings::getFragmentBuildSettings()
{
	return fragBuildSettings;
}

const ConfGen::FragmentConformerGeneratorSettings& ConfGen::StructureGeneratorSettings::getFragmentBuildSettings() const
{
	return fragBuildSettings;
}
