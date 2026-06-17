/* 
 * FragmentConformerGeneratorSettings.hpp 
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
 * \brief Definition of class CDPL::ConfGen::FragmentConformerGeneratorSettings.
 */

#ifndef CDPL_CONFGEN_FRAGMENTCONFORMERGENERATORSETTINGS_HPP
#define CDPL_CONFGEN_FRAGMENTCONFORMERGENERATORSETTINGS_HPP

#include <cstddef>

#include "CDPL/ConfGen/APIPrefix.hpp"


namespace CDPL
{

    namespace ConfGen
    {

        /**
         * \brief Bundle of configuration parameters for fragment conformer ensemble generation via
         *        class ConfGen::FragmentConformerGenerator.
         */
        class CDPL_CONFGEN_API FragmentConformerGeneratorSettings
        {

          public:
            /** \brief A static instance providing configuration parameter default values. */
            static const FragmentConformerGeneratorSettings DEFAULT;
            /** \brief A static instance preconfigured for fast (less thorough) conformer generation. */
            static const FragmentConformerGeneratorSettings FAST;
            /** \brief A static instance preconfigured for thorough (slower) conformer generation. */
            static const FragmentConformerGeneratorSettings THOROUGH;

            /**
             * \brief Per-fragment-class settings (separate parameters for chain, small ring system and macrocycle fragments).
             */
            class CDPL_CONFGEN_API FragmentSettings
            {

              public:
                /**
                 * \brief Constructs a \c %FragmentSettings instance with default configuration parameter values.
                 */
                FragmentSettings();

                /**
                 * \brief Sets the maximum number of trial conformers sampled per fragment.
                 * \param max_num The new num. conformers upper limit.
                 */
                void setMaxNumSampledConformers(std::size_t max_num);

                /**
                 * \brief Returns the maximum number of trial conformers sampled per fragment.
                 * \return The current num. conformers upper limit.
                 */
                std::size_t getMaxNumSampledConformers() const;

                /**
                 * \brief Sets the minimum number of trial conformers sampled per fragment before convergence is tested.
                 * \param min_num The new num. conformers lower limit.
                 */
                void setMinNumSampledConformers(std::size_t min_num);

                /**
                 * \brief Returns the minimum number of trial conformers sampled per fragment.
                 * \return The current num. conformers lower limit.
                 */
                std::size_t getMinNumSampledConformers() const;

                /**
                 * \brief Sets the per-fragment wall clock processing time limit.
                 * \param mil_secs The new time limit in milliseconds (zero disables the limit).
                 */
                void setTimeout(std::size_t mil_secs);

                /**
                 * \brief Returns the per-fragment wall clock processing time limit.
                 * \return The time limit in milliseconds (zero if disabled).
                 */
                std::size_t getTimeout() const;

                /**
                 * \brief Sets the energy window size (in kcal/mol) above the fragment conformer minimum within which fragment conformers are kept.
                 * \param win_size The new energy window size in kcal/mol.
                 */
                void setEnergyWindow(double win_size);

                /**
                 * \brief Returns the per-fragment energy window size.
                 * \return The energy window size in kcal/mol.
                 */
                double getEnergyWindow() const;

                /**
                 * \brief Sets the maximum number of output conformers per fragment.
                 * \param max_num The new output-conformer limit.
                 */
                void setMaxNumOutputConformers(std::size_t max_num);

                /**
                 * \brief Returns the maximum number of output conformers per fragment.
                 * \return The output-conformer limit.
                 */
                std::size_t getMaxNumOutputConformers() const;

                /**
                 * \brief Sets the minimum pairwise heavy atom RMSD that fragment conformers in the output set must have.
                 * \param min_rmsd The new minimum RMSD threshold (in &Aring;).
                 */
                void setMinRMSD(double min_rmsd);

                /**
                 * \brief Returns the minimum RMSD threshold used to filter fragment conformers.
                 * \return The minimum RMSD threshold (in &Aring;).
                 */
                double getMinRMSD() const;

              private:
                std::size_t maxNumSampledConfs;
                std::size_t minNumSampledConfs;
                std::size_t maxNumOutputConfs;
                std::size_t timeout;
                double      eWindow;
                double      minRMSD;
            };

            /**
             * \brief Constructs the \c % FragmentConformerGeneratorSettings instance with default configuration parameter values.
             */
            FragmentConformerGeneratorSettings();

            /**
             * \brief Virtual destructor.
             */
            virtual ~FragmentConformerGeneratorSettings() {}

            /**
             * \brief Specifies whether the bonding geometries (bond lengths and angles) of the input fragment shall be preserved.
             * \param preserve If \c true, the bonding geometry of the input is reused. Otherwise, it is rebuilt.
             */
            void preserveInputBondingGeometries(bool preserve);

            /**
             * \brief Tells whether the bonding geometries of the input fragment are preserved.
             * \return \c true if the input bonding geometry is reused, and \c false otherwise.
             */
            bool preserveInputBondingGeometries() const;

            /**
             * \brief Sets the force field type used for fragment conformer minimization.
             * \param type One of the ConfGen::ForceFieldType values.
             */
            void setForceFieldType(unsigned int type);

            /**
             * \brief Returns the force field type used for fragment conformer minimization.
             * \return One of the ConfGen::ForceFieldType values.
             */
            unsigned int getForceFieldType() const;

            /**
             * \brief Specifies whether strict MMFF94 parameterization is required.
             * \param strict If \c true, missing/ambiguous parameters cause a failure.
             *               Otherwise, in case of parameterization problems, suitable fallback parameters will be used.
             */
            void strictForceFieldParameterization(bool strict);

            /**
             * \brief Tells whether strict MMFF94 parameterization is required.
             * \return \c true if strict parameterization is required, and \c false otherwise.
             */
            bool strictForceFieldParameterization() const;

            /**
             * \brief Sets the dielectric constant used by the MMFF94 electrostatic interactions.
             * \param de_const The new dielectric constant.
             */
            void setDielectricConstant(double de_const);

            /**
             * \brief Returns the dielectric constant used by the MMFF94 electrostatic interactions.
             * \return The dielectric constant.
             */
            double getDielectricConstant() const;

            /**
             * \brief Sets the exponent of the MMFF94 distance-dependent electrostatic term.
             * \param exponent The new distance exponent.
             */
            void setDistanceExponent(double exponent);

            /**
             * \brief Returns the exponent of the MMFF94 distance-dependent electrostatic term.
             * \return The distance exponent.
             */
            double getDistanceExponent() const;

            /**
             * \brief Sets the maximum number of MMFF94 energy-minimization iterations per fragment conformer.
             * \param max_iter The new iteration limit (zero disables refinement).
             */
            void setMaxNumRefinementIterations(std::size_t max_iter);

            /**
             * \brief Returns the maximum number of MMFF94 energy-minimization iterations per fragment conformer.
             * \return The iteration limit (zero if refinement is disabled).
             */
            std::size_t getMaxNumRefinementIterations() const;

            /**
             * \brief Sets the gradient-norm threshold at which fragment conformer refinement is considered converged.
             * \param grad_norm The new stop-gradient threshold.
             */
            void setRefinementStopGradient(double grad_norm);

            /**
             * \brief Returns the gradient-norm threshold used to terminate refinement.
             * \return The stop-gradient threshold.
             */
            double getRefinementStopGradient() const;

            /**
             * \brief Sets the minimum number of rotatable bonds a macrocyclic ring must contain to be considered as a flexible macrocycle.
             * \param min_count The new flexible macrocycle rotatable bond count threshold.
             */
            void setMacrocycleRotorBondCountThreshold(std::size_t min_count);

            /**
             * \brief Returns the flexible macrocycle rotatable bond count threshold.
             * \return The current threshold.
             */
            std::size_t getMacrocycleRotorBondCountThreshold() const;

            /**
             * \brief Returns a reference to the per-fragment-class settings used for chain fragments.
             * \return A reference to the chain-fragment settings.
             */
            FragmentSettings& getChainSettings();

            /**
             * \brief Returns a \c const reference to the per-fragment-class settings used for chain fragments.
             * \return A \c const reference to the chain-fragment settings.
             */
            const FragmentSettings& getChainSettings() const;

            /**
             * \brief Returns a reference to the per-fragment-class settings used for flexible macrocyclic ring systems.
             * \return A reference to the macrocycle settings.
             */
            FragmentSettings& getMacrocycleSettings();

            /**
             * \brief Returns a \c const reference to the per-fragment-class settings used for flexible macrocyclic ring systems.
             * \return A \c const reference to the macrocycle settings.
             */
            const FragmentSettings& getMacrocycleSettings() const;

            /**
             * \brief Returns a reference to the per-fragment-class settings used for small ring systems.
             * \return A reference to the small ring system settings.
             */
            FragmentSettings& getSmallRingSystemSettings();

            /**
             * \brief Returns a \c const reference to the per-fragment-class settings used for small ring systems.
             * \return A \c const reference to the small ring system settings.
             */
            const FragmentSettings& getSmallRingSystemSettings() const;

            /**
             * \brief Sets a multiplicative factor scaling the sampling effort for small ring systems.
             * \param factor The new sampling-effort multiplier.
             */
            void setSmallRingSystemSamplingFactor(std::size_t factor);

            /**
             * \brief Returns the multiplicative factor scaling the sampling effort for small ring systems.
             * \return The sampling-effort multiplier.
             */
            std::size_t getSmallRingSystemSamplingFactor() const;

          private:
            bool             preserveBondGeom;
            unsigned int     forceFieldType;
            bool             strictParam;
            double           dielectricConst;
            double           distExponent;
            std::size_t      maxNumRefIters;
            double           refStopGrad;
            std::size_t      mcRotorBondCountThresh;
            std::size_t      srSamplingFactor;
            FragmentSettings chainSettings;
            FragmentSettings mcSettings;
            FragmentSettings srSettings;
        };
    } // namespace ConfGen
} // namespace CDPL

#endif // CDPL_CONFGEN_FRAGMENTCONFORMERGENERATORSETTINGS_HPP
