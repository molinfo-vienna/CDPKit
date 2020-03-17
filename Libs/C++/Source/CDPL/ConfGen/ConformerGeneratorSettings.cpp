/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * ConformerGeneratorSettings.cpp 
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

#include "CDPL/ConfGen/ConformerGeneratorSettings.hpp"
#include "CDPL/ConfGen/ForceFieldType.hpp"
#include "CDPL/ConfGen/NitrogenEnumerationMode.hpp"
#include "CDPL/ConfGen/ConformerSamplingMode.hpp"
#include "CDPL/ForceField/MMFF94ElectrostaticInteractionParameterizer.hpp"


using namespace CDPL;


ConfGen::ConformerGeneratorSettings::ConformerGeneratorSettings():
	samplingMode(ConformerSamplingMode::AUTO), sampleHetAtomHs(false), sampleTolRanges(true), 
	enumRings(true), nitrogenEnumMode(NitrogenEnumerationMode::UNSPECIFIED_STEREO),
	fromScratch(true), incInputCoords(false), eWindow(10.0), maxPoolSize(10000), timeout(60 * 60 * 1000), 
	forceFieldTypeSys(ForceFieldType::MMFF94S_NO_ESTAT), forceFieldTypeStoch(ForceFieldType::MMFF94S), strictParam(true), 
	dielectricConst(ForceField::MMFF94ElectrostaticInteractionParameterizer::DIELECTRIC_CONSTANT_WATER),
	distExponent(ForceField::MMFF94ElectrostaticInteractionParameterizer::DEF_DISTANCE_EXPONENT),
	maxNumOutputConfs(100), minRMSD(0.5), maxNumRefIters(0), refTolerance(0.001), maxNumSampledConfs(2000),
	convCheckCycleSize(100), mcRotorBondCountThresh(10)
{}

void ConfGen::ConformerGeneratorSettings::setSamplingMode(unsigned int mode)
{
	samplingMode = mode;
}

unsigned int ConfGen::ConformerGeneratorSettings::getSamplingMode() const
{
	return samplingMode;
}

void ConfGen::ConformerGeneratorSettings::sampleHeteroAtomHydrogens(bool sample)
{
	sampleHetAtomHs = sample;
}
				
bool ConfGen::ConformerGeneratorSettings::sampleHeteroAtomHydrogens() const
{
	return sampleHetAtomHs;
}

void ConfGen::ConformerGeneratorSettings::sampleAngleToleranceRanges(bool sample)
{
	sampleTolRanges = sample;
}
				
bool ConfGen::ConformerGeneratorSettings::sampleAngleToleranceRanges() const
{
	return sampleTolRanges;
}

void ConfGen::ConformerGeneratorSettings::enumerateRings(bool enumerate)
{
	enumRings = enumerate;
}

bool ConfGen::ConformerGeneratorSettings::enumerateRings() const
{
	return enumRings;
}

void ConfGen::ConformerGeneratorSettings::setNitrogenEnumerationMode(unsigned int mode)
{
	nitrogenEnumMode = mode;
}

unsigned int ConfGen::ConformerGeneratorSettings::getNitrogenEnumerationMode() const
{
	return nitrogenEnumMode;
}

void ConfGen::ConformerGeneratorSettings::generateCoordinatesFromScratch(bool generate)
{
	fromScratch = generate;
}
	
bool ConfGen::ConformerGeneratorSettings::generateCoordinatesFromScratch() const
{
	return fromScratch;
}

void ConfGen::ConformerGeneratorSettings::includeInputCoordinates(bool include)
{
	incInputCoords = include;
}
	
bool ConfGen::ConformerGeneratorSettings::includeInputCoordinates() const
{
	return incInputCoords;
}

void ConfGen::ConformerGeneratorSettings::setEnergyWindow(double win_size)
{
	eWindow = win_size;
}

double ConfGen::ConformerGeneratorSettings::getEnergyWindow() const
{
	return eWindow;
}

void ConfGen::ConformerGeneratorSettings::setMaxPoolSize(std::size_t max_size)
{
	maxPoolSize = max_size;
}

std::size_t ConfGen::ConformerGeneratorSettings::getMaxPoolSize() const
{
	return maxPoolSize;
}

void ConfGen::ConformerGeneratorSettings::setTimeout(std::size_t mil_secs)
{
	timeout = mil_secs;
}

std::size_t ConfGen::ConformerGeneratorSettings::getTimeout() const
{
	return timeout;
}

void ConfGen::ConformerGeneratorSettings::setForceFieldTypeSystematic(unsigned int type)
{
	forceFieldTypeSys = type;
}
	    
unsigned int ConfGen::ConformerGeneratorSettings::getForceFieldTypeSystematic() const
{
	return forceFieldTypeSys;
}

void ConfGen::ConformerGeneratorSettings::setForceFieldTypeStochastic(unsigned int type)
{
	forceFieldTypeStoch = type;
}
	    
unsigned int ConfGen::ConformerGeneratorSettings::getForceFieldTypeStochastic() const
{
	return forceFieldTypeStoch;
}
			
void ConfGen::ConformerGeneratorSettings::strictForceFieldParameterization(bool strict)
{
	strictParam = strict;
}

bool ConfGen::ConformerGeneratorSettings::strictForceFieldParameterization() const
{
	return strictParam;
}
			
void ConfGen::ConformerGeneratorSettings::setDielectricConstant(double de_const)
{
	dielectricConst = de_const;
}

double ConfGen::ConformerGeneratorSettings::getDielectricConstant() const
{
	return dielectricConst;
}

void ConfGen::ConformerGeneratorSettings::setDistanceExponent(double exponent)
{
	distExponent = exponent;
}

double ConfGen::ConformerGeneratorSettings::getDistanceExponent() const
{
	return distExponent;
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

void ConfGen::ConformerGeneratorSettings::setMaxNumRefinementIterations(std::size_t max_iter)
{
	maxNumRefIters = max_iter;
}

std::size_t ConfGen::ConformerGeneratorSettings::getMaxNumRefinementIterations() const
{
	return maxNumRefIters;
}

void ConfGen::ConformerGeneratorSettings::setRefinementTolerance(double tol)
{
	refTolerance = tol;
}

double ConfGen::ConformerGeneratorSettings::getRefinementTolerance() const
{
	return refTolerance;
}

void ConfGen::ConformerGeneratorSettings::setMaxNumSampledConformers(std::size_t max_num)
{
	maxNumSampledConfs = max_num;
}

std::size_t ConfGen::ConformerGeneratorSettings::getMaxNumSampledConformers() const
{
	return maxNumSampledConfs;
}

void ConfGen::ConformerGeneratorSettings::setConvergenceCheckCycleSize(std::size_t size)
{
	convCheckCycleSize = size;
}

std::size_t ConfGen::ConformerGeneratorSettings::getConvergenceCheckCycleSize() const
{
	return convCheckCycleSize;
}

void ConfGen::ConformerGeneratorSettings::setMacrocycleRotorBondCountThreshold(std::size_t min_count)
{
	mcRotorBondCountThresh = min_count;
}

std::size_t ConfGen::ConformerGeneratorSettings::getMacrocycleRotorBondCountThreshold() const
{
	return mcRotorBondCountThresh;
}

ConfGen::FragmentConformerGeneratorSettings& ConfGen::ConformerGeneratorSettings::getFragmentBuildSettings()
{
	return fragBuildSettings;
}

const ConfGen::FragmentConformerGeneratorSettings& ConfGen::ConformerGeneratorSettings::getFragmentBuildSettings() const
{
	return fragBuildSettings;
}
