/* 
 * InteractionPharmacophoreGenerator.hpp 
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

/**
 * \file
 * \brief Definition of class CDPL::Pharm::InteractionPharmacophoreGenerator.
 */

#ifndef CDPL_PHARM_INTERACTIONPHARMACOPHOREGENERATOR_HPP
#define CDPL_PHARM_INTERACTIONPHARMACOPHOREGENERATOR_HPP

#include "CDPL/Pharm/APIPrefix.hpp"
#include "CDPL/Pharm/DefaultPharmacophoreGenerator.hpp"
#include "CDPL/Pharm/BasicPharmacophore.hpp"
#include "CDPL/Pharm/FeatureMapping.hpp"
#include "CDPL/Pharm/DefaultInteractionAnalyzer.hpp"
#include "CDPL/Pharm/FeatureSet.hpp"
#include "CDPL/Chem/Fragment.hpp"


namespace CDPL
{

    namespace Pharm
    {

        /**
         * \brief InteractionPharmacophoreGenerator.
         */
        class CDPL_PHARM_API InteractionPharmacophoreGenerator
        {

          public:
            /**
             * \brief Constructs the \c %InteractionPharmacophoreGenerator instance.
             */
            InteractionPharmacophoreGenerator(DefaultPharmacophoreGenerator::Configuration core_ph4_gen_cfg = DefaultPharmacophoreGenerator::DEFAULT_CONFIG,
                                              DefaultPharmacophoreGenerator::Configuration env_ph4_gen_cfg  = DefaultPharmacophoreGenerator::DEFAULT_CONFIG);

            void setCoreEnvironmentRadius(double radius);

            double getCoreEnvironmentRadius() const;

            void addExclusionVolumes(bool add);

            bool exclusionVolumesAdded() const;

            PharmacophoreGenerator& getCorePharmacophoreGenerator();

            const PharmacophoreGenerator& getCorePharmacophoreGenerator() const;

            PharmacophoreGenerator& getEnvironmentPharmacophoreGenerator();

            const PharmacophoreGenerator& getEnvironmentPharmacophoreGenerator() const;

            InteractionAnalyzer& getInteractionAnalyzer();

            const InteractionAnalyzer& getInteractionAnalyzer() const;

            const Pharmacophore& getCorePharmacophore() const;

            const Pharmacophore& getEnvironmentPharmacophore() const;

            const FeatureMapping& getInteractionMapping() const;

            const Chem::Fragment& getCoreEnvironment() const;

            void generate(const Chem::MolecularGraph& core, const Chem::MolecularGraph& tgt, Pharmacophore& ia_pharm,
                          bool extract_core_env, bool append = false);

          private:
            DefaultPharmacophoreGenerator corePharmGen;
            DefaultPharmacophoreGenerator envPharmGen;
            BasicPharmacophore            corePharm;
            BasicPharmacophore            envPharm;
            DefaultInteractionAnalyzer    iaAnalyzer;
            FeatureMapping                iaMapping;
            Chem::Fragment                coreEnv;
            Chem::Fragment                iaEnvFeatureResAtoms;
            Chem::Fragment                iaEnvFeatureAtoms;
            FeatureSet                    iaEnvFeatures;
            double                        coreEnvRadius;
            bool                          addXVolumes;
        };
    } // namespace Pharm
} // namespace CDPL

#endif // CDPL_PHARM_INTERACTIONPHARMACOPHOREGENERATOR_HPP
