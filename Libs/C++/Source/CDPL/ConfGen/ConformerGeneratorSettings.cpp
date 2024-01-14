/* 
 * ConformerGeneratorSettings.cpp 
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

#include "CDPL/ConfGen/ConformerGeneratorSettings.hpp"
#include "CDPL/ConfGen/ForceFieldType.hpp"
#include "CDPL/ConfGen/NitrogenEnumerationMode.hpp"
#include "CDPL/ConfGen/ConformerSamplingMode.hpp"
#include "CDPL/ForceField/MMFF94ElectrostaticInteractionParameterizer.hpp"


using namespace CDPL;


ConfGen::ConformerGeneratorSettings::ConformerGeneratorSettings():
    samplingMode(ConformerSamplingMode::AUTO), sampleHetAtomHs(false), sampleTolRanges(true), 
    enumRings(true), nitrogenEnumMode(NitrogenEnumerationMode::UNSPECIFIED_STEREO),
    fromScratch(true), incInputCoords(false), eWindow(10.0), maxPoolSize(10000), maxRotorBondCount(-1), timeout(60 * 60 * 1000), 
    forceFieldTypeSys(ForceFieldType::MMFF94S_RTOR_NO_ESTAT), forceFieldTypeStoch(ForceFieldType::MMFF94S_RTOR), strictParam(true), 
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

double ConfGen::ConformerGeneratorSettings::getEnergyWindow(std::size_t num_rot_bonds) const
{
    if (eWindowRanges.empty())
        return eWindow;

    return getValueForCount(eWindowRanges, num_rot_bonds);
}

void ConfGen::ConformerGeneratorSettings::clearEnergyWindowRanges()
{
    eWindowRanges.clear();
}

void ConfGen::ConformerGeneratorSettings::addEnergyWindowRange(std::size_t num_rot_bonds, double win_size)
{
    eWindowRanges.emplace_back(num_rot_bonds, win_size);
}
            
void ConfGen::ConformerGeneratorSettings::setMaxPoolSize(std::size_t max_size)
{
    maxPoolSize = max_size;
}

std::size_t ConfGen::ConformerGeneratorSettings::getMaxPoolSize() const
{
    return maxPoolSize;
}

void ConfGen::ConformerGeneratorSettings::setMaxRotatableBondCount(long max_count)
{
    maxRotorBondCount = max_count;
}

long ConfGen::ConformerGeneratorSettings::getMaxRotatableBondCount() const
{
    return maxRotorBondCount;
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

std::size_t ConfGen::ConformerGeneratorSettings::getMaxNumOutputConformers(std::size_t num_rot_bonds) const
{
    if (maxNumOutputConfRanges.empty())
        return maxNumOutputConfs;

    return getValueForCount(maxNumOutputConfRanges, num_rot_bonds);
}

void ConfGen::ConformerGeneratorSettings::clearMaxNumOutputConformersRanges()
{
    maxNumOutputConfRanges.clear();
}

void ConfGen::ConformerGeneratorSettings::addMaxNumOutputConformersRange(std::size_t num_rot_bonds, std::size_t max_num)
{
    maxNumOutputConfRanges.emplace_back(num_rot_bonds, max_num);
}

void ConfGen::ConformerGeneratorSettings::setMinRMSD(double min_rmsd)
{
    minRMSD = min_rmsd;
}

double ConfGen::ConformerGeneratorSettings::getMinRMSD() const
{
    return minRMSD;
}

double ConfGen::ConformerGeneratorSettings::getMinRMSD(std::size_t num_rot_bonds) const
{
    if (minRMSDRanges.empty())
        return minRMSD;

    return getValueForCount(minRMSDRanges, num_rot_bonds);
}

void ConfGen::ConformerGeneratorSettings::clearMinRMSDRanges()
{
    minRMSDRanges.clear();
}

void ConfGen::ConformerGeneratorSettings::addMinRMSDRange(std::size_t num_rot_bonds, double min_rmsd)
{
    minRMSDRanges.emplace_back(num_rot_bonds, min_rmsd);
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

template <typename A>
typename A::value_type::second_type ConfGen::ConformerGeneratorSettings::getValueForCount(const A& array, std::size_t num_rot_bonds)
{
    const typename A::value_type* best_match = 0;
    const typename A::value_type* max_rbc_entry = 0;

    for (auto& entry : array) {
        if (num_rot_bonds <= entry.first && (!best_match || entry.first < best_match->first))
            best_match = &entry;

        if (!max_rbc_entry || entry.first > max_rbc_entry->first)
            max_rbc_entry = &entry;
    }

    if (best_match)
        return best_match->second;

    return max_rbc_entry->second;
}
