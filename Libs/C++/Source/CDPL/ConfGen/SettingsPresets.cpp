/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * SettingsPresets.cpp 
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

#include "CDPL/ConfGen/FragmentConformerGeneratorSettings.hpp"
#include "CDPL/ConfGen/FragmentAssemblerSettings.hpp"
#include "CDPL/ConfGen/ConformerGeneratorSettings.hpp"
#include "CDPL/ConfGen/StructureGeneratorSettings.hpp"
#include "CDPL/ConfGen/TorsionDriverSettings.hpp"
#include "CDPL/ConfGen/DGStructureGeneratorSettings.hpp"
#include "CDPL/ConfGen/DGConstraintGeneratorSettings.hpp"
#include "CDPL/ConfGen/ForceFieldType.hpp"
#include "CDPL/ConfGen/ConformerSamplingMode.hpp"
#include "CDPL/ConfGen/NitrogenEnumerationMode.hpp"


using namespace CDPL;


namespace
{

    ConfGen::FragmentConformerGeneratorSettings FRAG_CONF_GEN_FAST;
    ConfGen::FragmentConformerGeneratorSettings FRAG_CONF_GEN_THOROUGH;

    ConfGen::ConformerGeneratorSettings CONF_GEN_SMALL_SET_DIVERSE;
    ConfGen::ConformerGeneratorSettings CONF_GEN_MEDIUM_SET_DIVERSE;
    ConfGen::ConformerGeneratorSettings CONF_GEN_LARGE_SET_DIVERSE;
    ConfGen::ConformerGeneratorSettings CONF_GEN_SMALL_SET_DENSE;
    ConfGen::ConformerGeneratorSettings CONF_GEN_MEDIUM_SET_DENSE;
    ConfGen::ConformerGeneratorSettings CONF_GEN_LARGE_SET_DENSE;

    struct Init {

		Init() {
			using namespace ConfGen;

			FRAG_CONF_GEN_FAST.preserveInputBondingGeometries(false);
			FRAG_CONF_GEN_FAST.setForceFieldType(ForceFieldType::MMFF94S_NO_ESTAT);
			FRAG_CONF_GEN_FAST.strictForceFieldParameterization(true);
			FRAG_CONF_GEN_FAST.setMaxNumRefinementIterations(0);
			FRAG_CONF_GEN_FAST.setRefinementStopGradient(0.25);
			FRAG_CONF_GEN_FAST.setMacrocycleRotorBondCountThreshold(10);
			FRAG_CONF_GEN_FAST.setSmallRingSystemSamplingFactor(6);

			FragmentConformerGeneratorSettings::FragmentSettings* chain_settings = &FRAG_CONF_GEN_FAST.getChainSettings();

			chain_settings->setMaxNumSampledConformers(50);
			chain_settings->setMinNumSampledConformers(10);
			chain_settings->setMaxNumOutputConformers(1);
			chain_settings->setTimeout(400 * 1000);
			chain_settings->setEnergyWindow(8.0);
			chain_settings->setMinRMSD(0.1);

			FragmentConformerGeneratorSettings::FragmentSettings* sr_settings = &FRAG_CONF_GEN_FAST.getSmallRingSystemSettings();

			sr_settings->setMaxNumSampledConformers(1000);
			sr_settings->setMinNumSampledConformers(30);
			sr_settings->setMaxNumOutputConformers(1000);
			sr_settings->setTimeout(800 * 1000);
			sr_settings->setEnergyWindow(8.0);
			sr_settings->setMinRMSD(0.1);

			FragmentConformerGeneratorSettings::FragmentSettings* mc_settings = &FRAG_CONF_GEN_FAST.getMacrocycleSettings();

			mc_settings->setMaxNumSampledConformers(2000);
			mc_settings->setMinNumSampledConformers(100);
			mc_settings->setMaxNumOutputConformers(1000);
			mc_settings->setTimeout(1800 * 1000);
			mc_settings->setEnergyWindow(25.0);
			mc_settings->setMinRMSD(0.1);

			//--

			FRAG_CONF_GEN_THOROUGH = FRAG_CONF_GEN_FAST;
			FRAG_CONF_GEN_THOROUGH.setRefinementStopGradient(0.1);
			FRAG_CONF_GEN_THOROUGH.setSmallRingSystemSamplingFactor(20);

			chain_settings = &FRAG_CONF_GEN_THOROUGH.getChainSettings();

			chain_settings->setMaxNumSampledConformers(200);
			chain_settings->setMinNumSampledConformers(40);
			chain_settings->setEnergyWindow(2.0);
			chain_settings->setTimeout(1800 * 1000);

			sr_settings = &FRAG_CONF_GEN_THOROUGH.getSmallRingSystemSettings();

			sr_settings->setMinNumSampledConformers(50);
			//sr_settings->setEnergyWindow(6.0);
			sr_settings->setTimeout(1800 * 1000);

			//----------------

			CONF_GEN_SMALL_SET_DIVERSE.getFragmentBuildSettings() = FRAG_CONF_GEN_FAST;
			CONF_GEN_SMALL_SET_DIVERSE.setSamplingMode(ConformerSamplingMode::AUTO);
			CONF_GEN_SMALL_SET_DIVERSE.sampleHeteroAtomHydrogens(false);
			CONF_GEN_SMALL_SET_DIVERSE.sampleAngleToleranceRanges(false);
			CONF_GEN_SMALL_SET_DIVERSE.enumerateRings(true);
			CONF_GEN_SMALL_SET_DIVERSE.setNitrogenEnumerationMode(NitrogenEnumerationMode::UNSPECIFIED_STEREO);
			CONF_GEN_SMALL_SET_DIVERSE.generateCoordinatesFromScratch(true);
			CONF_GEN_SMALL_SET_DIVERSE.includeInputCoordinates(false);
			CONF_GEN_SMALL_SET_DIVERSE.setTimeout(60 * 60 * 1000);
			CONF_GEN_SMALL_SET_DIVERSE.setForceFieldTypeSystematic(ForceFieldType::MMFF94S_NO_ESTAT);
			CONF_GEN_SMALL_SET_DIVERSE.setForceFieldTypeStochastic(ForceFieldType::MMFF94S);
			CONF_GEN_SMALL_SET_DIVERSE.strictForceFieldParameterization(true);
			CONF_GEN_SMALL_SET_DIVERSE.setMaxNumRefinementIterations(0);
			CONF_GEN_SMALL_SET_DIVERSE.setRefinementTolerance(0.001);
			CONF_GEN_SMALL_SET_DIVERSE.setMacrocycleRotorBondCountThreshold(10);
			CONF_GEN_SMALL_SET_DIVERSE.setConvergenceCheckCycleSize(100);
			CONF_GEN_SMALL_SET_DIVERSE.setMaxNumSampledConformers(2000);
			CONF_GEN_SMALL_SET_DIVERSE.setEnergyWindow(10.0);
			CONF_GEN_SMALL_SET_DIVERSE.setMaxNumOutputConformers(50);
			CONF_GEN_SMALL_SET_DIVERSE.setMinRMSD(0.5);
			
			//--

			CONF_GEN_MEDIUM_SET_DIVERSE = CONF_GEN_SMALL_SET_DIVERSE;
			CONF_GEN_MEDIUM_SET_DIVERSE.setEnergyWindow(15.0);
			CONF_GEN_MEDIUM_SET_DIVERSE.setMaxNumOutputConformers(100);
			CONF_GEN_MEDIUM_SET_DIVERSE.setMinRMSD(0.5);

			//--

			CONF_GEN_LARGE_SET_DIVERSE = CONF_GEN_SMALL_SET_DIVERSE;
			CONF_GEN_LARGE_SET_DIVERSE.setEnergyWindow(20.0);
			CONF_GEN_LARGE_SET_DIVERSE.setMaxNumOutputConformers(250);
			CONF_GEN_LARGE_SET_DIVERSE.setMinRMSD(0.5);

			//--

			CONF_GEN_SMALL_SET_DENSE = CONF_GEN_SMALL_SET_DIVERSE;
			CONF_GEN_SMALL_SET_DENSE.setEnergyWindow(10.0);
			CONF_GEN_SMALL_SET_DENSE.setMaxNumOutputConformers(50);
			CONF_GEN_SMALL_SET_DENSE.setMinRMSD(0.3);

			//--

			CONF_GEN_MEDIUM_SET_DENSE = CONF_GEN_MEDIUM_SET_DIVERSE;
			CONF_GEN_MEDIUM_SET_DENSE.setEnergyWindow(15.0);
			CONF_GEN_MEDIUM_SET_DENSE.setMaxNumOutputConformers(100);
			CONF_GEN_MEDIUM_SET_DENSE.setMinRMSD(0.3);

			//--

			CONF_GEN_LARGE_SET_DENSE = CONF_GEN_LARGE_SET_DIVERSE;
			CONF_GEN_LARGE_SET_DENSE.setEnergyWindow(20.0);
			CONF_GEN_LARGE_SET_DENSE.setMaxNumOutputConformers(250);
			CONF_GEN_LARGE_SET_DENSE.setMinRMSD(0.3);
		}

    } init;
}


const ConfGen::FragmentConformerGeneratorSettings ConfGen::FragmentConformerGeneratorSettings::FAST     = FRAG_CONF_GEN_FAST;
const ConfGen::FragmentConformerGeneratorSettings ConfGen::FragmentConformerGeneratorSettings::THOROUGH = FRAG_CONF_GEN_THOROUGH;
const ConfGen::FragmentConformerGeneratorSettings ConfGen::FragmentConformerGeneratorSettings::DEFAULT  = FRAG_CONF_GEN_FAST;

const ConfGen::FragmentAssemblerSettings ConfGen::FragmentAssemblerSettings::DEFAULT;

const ConfGen::ConformerGeneratorSettings ConfGen::ConformerGeneratorSettings::SMALL_SET_DIVERSE   = CONF_GEN_SMALL_SET_DIVERSE;
const ConfGen::ConformerGeneratorSettings ConfGen::ConformerGeneratorSettings::MEDIUM_SET_DIVERSE  = CONF_GEN_MEDIUM_SET_DIVERSE;
const ConfGen::ConformerGeneratorSettings ConfGen::ConformerGeneratorSettings::LARGE_SET_DIVERSE   = CONF_GEN_LARGE_SET_DIVERSE;
const ConfGen::ConformerGeneratorSettings ConfGen::ConformerGeneratorSettings::SMALL_SET_DENSE     = CONF_GEN_SMALL_SET_DENSE;
const ConfGen::ConformerGeneratorSettings ConfGen::ConformerGeneratorSettings::MEDIUM_SET_DENSE    = CONF_GEN_MEDIUM_SET_DENSE;
const ConfGen::ConformerGeneratorSettings ConfGen::ConformerGeneratorSettings::LARGE_SET_DENSE     = CONF_GEN_LARGE_SET_DENSE;
const ConfGen::ConformerGeneratorSettings ConfGen::ConformerGeneratorSettings::DEFAULT             = CONF_GEN_MEDIUM_SET_DIVERSE;

const ConfGen::StructureGeneratorSettings ConfGen::StructureGeneratorSettings::DEFAULT;

const ConfGen::TorsionDriverSettings ConfGen::TorsionDriverSettings::DEFAULT;

const ConfGen::DGStructureGeneratorSettings ConfGen::DGStructureGeneratorSettings::DEFAULT;

const ConfGen::DGConstraintGeneratorSettings ConfGen::DGConstraintGeneratorSettings::DEFAULT;
