/* 
 * InteractionPharmacophoreGenerator.cpp 
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

#include "CDPL/Pharm/InteractionPharmacophoreGenerator.hpp"
#include "CDPL/Pharm/PharmacophoreFunctions.hpp"
#include "CDPL/Pharm/FeatureContainerFunctions.hpp"
#include "CDPL/Pharm/FeatureFunctions.hpp"
#include "CDPL/Pharm/FeatureType.hpp"
#include "CDPL/Biomol/UtilityFunctions.hpp"
#include "CDPL/Chem/MolecularGraphFunctions.hpp"
#include "CDPL/Chem/FragmentFunctions.hpp"


using namespace CDPL; 


namespace
{

    bool isPDBAlphaAtom(const Chem::Atom& atom)
    {
        return (Biomol::getResidueAtomName(atom) == "CA");
    }
}


Pharm::InteractionPharmacophoreGenerator::InteractionPharmacophoreGenerator(DefaultPharmacophoreGenerator::Configuration core_ph4_gen_cfg,
                                                                            DefaultPharmacophoreGenerator::Configuration env_ph4_gen_cfg):
    corePharmGen(core_ph4_gen_cfg), envPharmGen(env_ph4_gen_cfg), coreEnvRadius(8.0), addXVolumes(true)
{
    envPharmGen.enableFeature(FeatureType::HALOGEN_BOND_ACCEPTOR, true);
}

void Pharm::InteractionPharmacophoreGenerator::setCoreEnvironmentRadius(double radius)
{
    coreEnvRadius = radius;
}

double Pharm::InteractionPharmacophoreGenerator::getCoreEnvironmentRadius() const
{
    return coreEnvRadius;
}

void Pharm::InteractionPharmacophoreGenerator::addExclusionVolumes(bool add)
{
    addXVolumes = add;
}

bool Pharm::InteractionPharmacophoreGenerator::exclusionVolumesAdded() const
{
    return addXVolumes;
}

Pharm::PharmacophoreGenerator& Pharm::InteractionPharmacophoreGenerator::getCorePharmacophoreGenerator()
{
    return corePharmGen;
}

const Pharm::PharmacophoreGenerator& Pharm::InteractionPharmacophoreGenerator::getCorePharmacophoreGenerator() const
{
    return corePharmGen;
}

Pharm::PharmacophoreGenerator& Pharm::InteractionPharmacophoreGenerator::getEnvironmentPharmacophoreGenerator()
{
    return envPharmGen;
}

const Pharm::PharmacophoreGenerator& Pharm::InteractionPharmacophoreGenerator::getEnvironmentPharmacophoreGenerator() const
{
    return envPharmGen;
}

Pharm::InteractionAnalyzer& Pharm::InteractionPharmacophoreGenerator::getInteractionAnalyzer()
{
    return iaAnalyzer;
}

const Pharm::InteractionAnalyzer& Pharm::InteractionPharmacophoreGenerator::getInteractionAnalyzer() const
{
    return iaAnalyzer;
}

const Pharm::Pharmacophore& Pharm::InteractionPharmacophoreGenerator::getCorePharmacophore() const
{
    return corePharm;
}

const Pharm::Pharmacophore& Pharm::InteractionPharmacophoreGenerator::getEnvironmentPharmacophore() const
{
    return envPharm;
}

const Pharm::FeatureMapping& Pharm::InteractionPharmacophoreGenerator::getInteractionMapping() const
{
    return iaMapping;
}

const Chem::Fragment& Pharm::InteractionPharmacophoreGenerator::getCoreEnvironment() const
{
    return coreEnv;
}

void Pharm::InteractionPharmacophoreGenerator::generate(const Chem::MolecularGraph& core, const Chem::MolecularGraph& tgt, 
                                                        Pharmacophore& ia_pharm, bool extract_core_env, bool append)
{
    const Chem::MolecularGraph* env = &tgt;

    if (extract_core_env) {
        env = &coreEnv;

        Biomol::extractEnvironmentResidues(core, tgt, coreEnv, corePharmGen.getAtom3DCoordinatesFunction(), coreEnvRadius, false);

        perceiveSSSR(coreEnv, true);
    }

    corePharmGen.generate(core, corePharm, false);
    envPharmGen.generate(*env, envPharm, false);

    iaAnalyzer.analyze(corePharm, envPharm, iaMapping, false);

    generateInteractionPharmacophore(ia_pharm, iaMapping, append);

    if (addXVolumes) {
        iaEnvFeatures.clear();

        for (FeatureMapping::EntryIterator it = iaMapping.getEntriesBegin(), end = iaMapping.getEntriesEnd(); it != end; ++it) {
            Feature& env_ftr = envPharm.getFeature(envPharm.getFeatureIndex(*it->second));

            if (iaEnvFeatures.addFeature(env_ftr)) {
                unsigned int type = getType(env_ftr);

                if (type == FeatureType::H_BOND_DONOR || type == FeatureType::H_BOND_ACCEPTOR)
                    setTolerance(env_ftr, 1.0);
                else
                    setTolerance(env_ftr, 1.5);
            }
        }

        createExclusionVolumes(ia_pharm, iaEnvFeatures, 0.0, 0.1, false);

        iaEnvFeatureResAtoms.clear();
        iaEnvFeatureAtoms.clear();

        getFeatureAtoms(iaEnvFeatures, iaEnvFeatureAtoms);
        Biomol::extractResidueSubstructures(iaEnvFeatureAtoms, *env, iaEnvFeatureResAtoms, true);

        makeHydrogenDeplete(iaEnvFeatureResAtoms);
        removeAtomsIfNot(iaEnvFeatureResAtoms, &isPDBAlphaAtom);

        createExclusionVolumes(ia_pharm, iaEnvFeatureResAtoms, envPharmGen.getAtom3DCoordinatesFunction(), 1.0, 2.0, false);
        resizeExclusionVolumesWithClashes(ia_pharm, core, corePharmGen.getAtom3DCoordinatesFunction());
    }
}
