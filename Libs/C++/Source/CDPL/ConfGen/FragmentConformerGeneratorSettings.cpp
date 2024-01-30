/* 
 * FragmentConformerGeneratorSettings.cpp 
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

#include "CDPL/ConfGen/FragmentConformerGeneratorSettings.hpp"
#include "CDPL/ConfGen/ForceFieldType.hpp"
#include "CDPL/ForceField/MMFF94ElectrostaticInteractionParameterizer.hpp"


using namespace CDPL;


ConfGen::FragmentConformerGeneratorSettings::FragmentSettings::FragmentSettings():
    maxNumSampledConfs(2000), minNumSampledConfs(40), maxNumOutputConfs(1000),
    timeout(0), eWindow(8.0), minRMSD(0.1)
{}

void ConfGen::FragmentConformerGeneratorSettings::FragmentSettings::setMaxNumSampledConformers(std::size_t max_num)
{
    maxNumSampledConfs = max_num;
}

std::size_t ConfGen::FragmentConformerGeneratorSettings::FragmentSettings::getMaxNumSampledConformers() const
{
    return maxNumSampledConfs;
}

void ConfGen::FragmentConformerGeneratorSettings::FragmentSettings::setMinNumSampledConformers(std::size_t min_num)
{
    minNumSampledConfs = min_num;
}

std::size_t ConfGen::FragmentConformerGeneratorSettings::FragmentSettings::getMinNumSampledConformers() const
{
    return minNumSampledConfs;
}

void ConfGen::FragmentConformerGeneratorSettings::FragmentSettings::setTimeout(std::size_t mil_secs)
{
    timeout = mil_secs;
}

std::size_t ConfGen::FragmentConformerGeneratorSettings::FragmentSettings::getTimeout() const
{
    return timeout;
}

void ConfGen::FragmentConformerGeneratorSettings::FragmentSettings::setEnergyWindow(double win_size)
{
    eWindow = win_size;
}

double ConfGen::FragmentConformerGeneratorSettings::FragmentSettings::getEnergyWindow() const
{
    return eWindow;
}

void ConfGen::FragmentConformerGeneratorSettings::FragmentSettings::setMaxNumOutputConformers(std::size_t max_num)
{
    maxNumOutputConfs = max_num;
}

std::size_t ConfGen::FragmentConformerGeneratorSettings::FragmentSettings::getMaxNumOutputConformers() const
{
    return maxNumOutputConfs;
}

void ConfGen::FragmentConformerGeneratorSettings::FragmentSettings::setMinRMSD(double min_rmsd)
{
    minRMSD = min_rmsd;
}

double ConfGen::FragmentConformerGeneratorSettings::FragmentSettings::getMinRMSD() const
{
    return minRMSD;
}


ConfGen::FragmentConformerGeneratorSettings::FragmentConformerGeneratorSettings():
    preserveBondGeom(false), forceFieldType(ForceFieldType::MMFF94S_RTOR_NO_ESTAT), strictParam(true), 
    dielectricConst(ForceField::MMFF94ElectrostaticInteractionParameterizer::DEF_DIELECTRIC_CONSTANT),
    distExponent(ForceField::MMFF94ElectrostaticInteractionParameterizer::DEF_DISTANCE_EXPONENT),
    maxNumRefIters(0), refStopGrad(0.1), mcRotorBondCountThresh(10), srSamplingFactor(6) 
{
    chainSettings.setMaxNumSampledConformers(100);
    chainSettings.setMinNumSampledConformers(5);
    chainSettings.setTimeout(400 * 1000);
    chainSettings.setEnergyWindow(2.0);
    chainSettings.setMaxNumOutputConformers(1);
    chainSettings.setMinRMSD(0.1);

    srSettings.setMaxNumSampledConformers(1000);
    srSettings.setMinNumSampledConformers(30);
    srSettings.setTimeout(400 * 1000);
    srSettings.setEnergyWindow(8.0);
    srSettings.setMaxNumOutputConformers(1000);
    srSettings.setMinRMSD(0.1);

    mcSettings.setMaxNumSampledConformers(2000);
    mcSettings.setMinNumSampledConformers(100);
    mcSettings.setTimeout(1800 * 1000);
    mcSettings.setEnergyWindow(25.0);
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

void ConfGen::FragmentConformerGeneratorSettings::setDielectricConstant(double de_const)
{
    dielectricConst = de_const;
}

double ConfGen::FragmentConformerGeneratorSettings::getDielectricConstant() const
{
    return dielectricConst;
}

void ConfGen::FragmentConformerGeneratorSettings::setDistanceExponent(double exponent)
{
    distExponent = exponent;
}

double ConfGen::FragmentConformerGeneratorSettings::getDistanceExponent() const
{
    return distExponent;
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

void ConfGen::FragmentConformerGeneratorSettings::setMacrocycleRotorBondCountThreshold(std::size_t min_count)
{
    mcRotorBondCountThresh = min_count;
}

std::size_t ConfGen::FragmentConformerGeneratorSettings::getMacrocycleRotorBondCountThreshold() const
{
    return mcRotorBondCountThresh;
}

ConfGen::FragmentConformerGeneratorSettings::FragmentSettings& 
ConfGen::FragmentConformerGeneratorSettings::getChainSettings()
{
    return chainSettings;
}

const ConfGen::FragmentConformerGeneratorSettings::FragmentSettings& 
ConfGen::FragmentConformerGeneratorSettings::getChainSettings() const
{
    return chainSettings;
}

ConfGen::FragmentConformerGeneratorSettings::FragmentSettings& 
ConfGen::FragmentConformerGeneratorSettings::getMacrocycleSettings()
{
    return mcSettings;
}

const ConfGen::FragmentConformerGeneratorSettings::FragmentSettings& 
ConfGen::FragmentConformerGeneratorSettings::getMacrocycleSettings() const
{
    return mcSettings;
}

ConfGen::FragmentConformerGeneratorSettings::FragmentSettings& 
ConfGen::FragmentConformerGeneratorSettings::getSmallRingSystemSettings()
{
    return srSettings;
}

const ConfGen::FragmentConformerGeneratorSettings::FragmentSettings& 
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
