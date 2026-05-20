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
         * \brief Driver that generates an interaction pharmacophore by perceiving a core pharmacophore on a ligand,
         *        an environment pharmacophore on the surrounding pocket residues, analyzing the inter-feature
         *        interactions and emitting one feature per detected interaction (optionally with exclusion volumes).
         */
        class CDPL_PHARM_API InteractionPharmacophoreGenerator
        {

          public:
            /**
             * \brief Constructs the \c %InteractionPharmacophoreGenerator instance.
             * \param core_ph4_gen_cfg Configuration flags for the core (ligand) pharmacophore generator.
             * \param env_ph4_gen_cfg Configuration flags for the environment (pocket) pharmacophore generator.
             */
            InteractionPharmacophoreGenerator(DefaultPharmacophoreGenerator::Configuration core_ph4_gen_cfg = DefaultPharmacophoreGenerator::DEFAULT_CONFIG,
                                              DefaultPharmacophoreGenerator::Configuration env_ph4_gen_cfg  = DefaultPharmacophoreGenerator::DEFAULT_CONFIG);

            /**
             * \brief Sets the cutoff radius around the core used to extract the environment substructure.
             * \param radius The new core-environment radius.
             */
            void setCoreEnvironmentRadius(double radius);

            /**
             * \brief Returns the currently configured core-environment cutoff radius.
             * \return The core-environment radius.
             */
            double getCoreEnvironmentRadius() const;

            /**
             * \brief Specifies whether exclusion volume features shall be added for environment atoms not part of any interaction feature.
             * \param add \c true to add exclusion volumes, and \c false to skip them.
             */
            void addExclusionVolumes(bool add);

            /**
             * \brief Tells whether exclusion volume features are added.
             * \return \c true if exclusion volumes are added, and \c false otherwise.
             */
            bool exclusionVolumesAdded() const;

            /**
             * \brief Returns the core (ligand) pharmacophore generator.
             * \return A reference to the core pharmacophore generator.
             */
            PharmacophoreGenerator& getCorePharmacophoreGenerator();

            /**
             * \brief Returns the core (ligand) pharmacophore generator.
             * \return A \c const reference to the core pharmacophore generator.
             */
            const PharmacophoreGenerator& getCorePharmacophoreGenerator() const;

            /**
             * \brief Returns the environment (pocket) pharmacophore generator.
             * \return A reference to the environment pharmacophore generator.
             */
            PharmacophoreGenerator& getEnvironmentPharmacophoreGenerator();

            /**
             * \brief Returns the environment (pocket) pharmacophore generator.
             * \return A \c const reference to the environment pharmacophore generator.
             */
            const PharmacophoreGenerator& getEnvironmentPharmacophoreGenerator() const;

            /**
             * \brief Returns the interaction analyzer used to perceive feature-feature interactions.
             * \return A reference to the interaction analyzer.
             */
            InteractionAnalyzer& getInteractionAnalyzer();

            /**
             * \brief Returns the interaction analyzer used to perceive feature-feature interactions.
             * \return A \c const reference to the interaction analyzer.
             */
            const InteractionAnalyzer& getInteractionAnalyzer() const;

            /**
             * \brief Returns the core (ligand) pharmacophore produced by the last generate() call.
             * \return A \c const reference to the core pharmacophore.
             */
            const Pharmacophore& getCorePharmacophore() const;

            /**
             * \brief Returns the environment (pocket) pharmacophore produced by the last generate() call.
             * \return A \c const reference to the environment pharmacophore.
             */
            const Pharmacophore& getEnvironmentPharmacophore() const;

            /**
             * \brief Returns the feature-to-feature interaction mapping produced by the last generate() call.
             * \return A \c const reference to the interaction mapping.
             */
            const FeatureMapping& getInteractionMapping() const;

            /**
             * \brief Returns the core-environment substructure extracted by the last generate() call (only valid when \a extract_core_env was \c true).
             * \return A \c const reference to the core-environment fragment.
             */
            const Chem::Fragment& getCoreEnvironment() const;

            /**
             * \brief Generates the interaction pharmacophore for the (\a core, \a tgt) molecular graph pair.
             * \param core The core (ligand) molecular graph.
             * \param tgt The target (pocket) molecular graph.
             * \param ia_pharm The output interaction pharmacophore.
             * \param extract_core_env If \c true, the core environment is extracted from \a tgt before pharmacophore generation;
             *                         if \c false, the environment pharmacophore is generated on \a tgt directly.
             * \param append If \c false, \a ia_pharm is cleared before any features are added.
             */
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
