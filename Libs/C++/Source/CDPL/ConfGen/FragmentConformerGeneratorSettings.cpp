/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * FragmentConformerGeneratorSettings.cpp 
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

#include "CDPL/ConfGen/FragmentConformerGeneratorSettings.hpp"
#include "CDPL/ConfGen/ForceFieldType.hpp"


using namespace CDPL;


const ConfGen::FragmentConformerGeneratorSettings ConfGen::FragmentConformerGeneratorSettings::DEFAULT;


ConfGen::FragmentConformerGeneratorSettings::RingFragmentSettings::RingFragmentSettings():
	maxNumSampledConfs(2000), minNumSampledConfs(30), maxNumOutputConfs(1000),
	timeout(0), eWindow(8.0), minRMSD(0.1)
{}

void ConfGen::FragmentConformerGeneratorSettings::RingFragmentSettings::setMaxNumSampledConformers(std::size_t max_num)
{
	maxNumSampledConfs = max_num;
}

std::size_t ConfGen::FragmentConformerGeneratorSettings::RingFragmentSettings::getMaxNumSampledConformers() const
{
	return maxNumSampledConfs;
}

void ConfGen::FragmentConformerGeneratorSettings::RingFragmentSettings::setMinNumSampledConformers(std::size_t min_num)
{
	minNumSampledConfs = min_num;
}

std::size_t ConfGen::FragmentConformerGeneratorSettings::RingFragmentSettings::getMinNumSampledConformers() const
{
	return minNumSampledConfs;
}

void ConfGen::FragmentConformerGeneratorSettings::RingFragmentSettings::setTimeout(std::size_t mil_secs)
{
	timeout = mil_secs;
}

std::size_t ConfGen::FragmentConformerGeneratorSettings::RingFragmentSettings::getTimeout() const
{
	return timeout;
}

void ConfGen::FragmentConformerGeneratorSettings::RingFragmentSettings::setEnergyWindow(double win_size)
{
	eWindow = win_size;
}

double ConfGen::FragmentConformerGeneratorSettings::RingFragmentSettings::getEnergyWindow() const
{
	return eWindow;
}

void ConfGen::FragmentConformerGeneratorSettings::RingFragmentSettings::setMaxNumOutputConformers(std::size_t max_num)
{
	maxNumOutputConfs = max_num;
}

std::size_t ConfGen::FragmentConformerGeneratorSettings::RingFragmentSettings::getMaxNumOutputConformers() const
{
	return maxNumOutputConfs;
}

void ConfGen::FragmentConformerGeneratorSettings::RingFragmentSettings::setMinRMSD(double min_rmsd)
{
	minRMSD = min_rmsd;
}

double ConfGen::FragmentConformerGeneratorSettings::RingFragmentSettings::getMinRMSD() const
{
	return minRMSD;
}


ConfGen::FragmentConformerGeneratorSettings::FragmentConformerGeneratorSettings():
	preserveBondGeom(false), forceFieldType(ForceFieldType::MMFF94S_NO_ESTAT), 
	strictParam(true), maxNumRefIters(0), refStopGrad(0.1), minMacrocycleSize(10), 
	srSamplingFactor(6) 
{
	srSettings.setMaxNumSampledConformers(1000);
	srSettings.setMinNumSampledConformers(50);
	srSettings.setTimeout(30 * 1000);
	srSettings.setEnergyWindow(6.0);
	srSettings.setMaxNumOutputConformers(1000);
	srSettings.setMinRMSD(0.1);

	mcSettings.setMaxNumSampledConformers(2000);
	mcSettings.setMinNumSampledConformers(100);
	mcSettings.setTimeout(10 * 60 * 1000);
	mcSettings.setEnergyWindow(20.0);
	mcSettings.setMaxNumOutputConformers(1000);
	mcSettings.setMinRMSD(0.1);
}

void ConfGen::FragmentConformerGeneratorSettings::preserveInputBondingGeometries(bool preserve)
{
	preserveBondGeom = preserve;
}

bool ConfGen::FragmentConformerGeneratorSettings::preserveInputBondingGeometries() const
{
	return preserveBondGeom;
}

void ConfGen::FragmentConformerGeneratorSettings::setForceFieldType(unsigned int type)
{
	forceFieldType = type;
}
	    
unsigned int ConfGen::FragmentConformerGeneratorSettings::getForceFieldType() const
{
	return forceFieldType;
}

void ConfGen::FragmentConformerGeneratorSettings::strictForceFieldParameterization(bool strict)
{
	strictParam = strict;
}

bool ConfGen::FragmentConformerGeneratorSettings::strictForceFieldParameterization() const
{
	return strictParam;
}

void ConfGen::FragmentConformerGeneratorSettings::setMaxNumRefinementIterations(std::size_t max_iter)
{
	maxNumRefIters = max_iter;
}

std::size_t ConfGen::FragmentConformerGeneratorSettings::getMaxNumRefinementIterations() const
{
	return maxNumRefIters;
}

void ConfGen::FragmentConformerGeneratorSettings::setRefinementStopGradient(double grad_norm)
{
	refStopGrad = grad_norm;
}

double ConfGen::FragmentConformerGeneratorSettings::getRefinementStopGradient() const
{
	return refStopGrad;
}

void ConfGen::FragmentConformerGeneratorSettings::setMinMacrocycleSize(std::size_t min_size)
{
	minMacrocycleSize = min_size;
}

std::size_t ConfGen::FragmentConformerGeneratorSettings::getMinMacrocycleSize() const
{
	return minMacrocycleSize;
}

ConfGen::FragmentConformerGeneratorSettings::RingFragmentSettings& 
ConfGen::FragmentConformerGeneratorSettings::getMacrocycleSettings()
{
	return mcSettings;
}

const ConfGen::FragmentConformerGeneratorSettings::RingFragmentSettings& 
ConfGen::FragmentConformerGeneratorSettings::getMacrocycleSettings() const
{
	return mcSettings;
}

ConfGen::FragmentConformerGeneratorSettings::RingFragmentSettings& 
ConfGen::FragmentConformerGeneratorSettings::getSmallRingSystemSettings()
{
	return srSettings;
}

const ConfGen::FragmentConformerGeneratorSettings::RingFragmentSettings& 
ConfGen::FragmentConformerGeneratorSettings::getSmallRingSystemSettings() const
{
	return srSettings;
}

void ConfGen::FragmentConformerGeneratorSettings::setSmallRingSystemSamplingFactor(std::size_t factor)
{
	srSamplingFactor = factor;
}

std::size_t ConfGen::FragmentConformerGeneratorSettings::getSmallRingSystemSamplingFactor() const
{
	return srSamplingFactor;
}
