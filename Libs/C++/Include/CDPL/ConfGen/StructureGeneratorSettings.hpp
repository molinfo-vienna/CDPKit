/* 
 * StructureGeneratorSettings.hpp 
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
 * \brief Definition of class CDPL::ConfGen::StructureGeneratorSettings.
 */

#ifndef CDPL_CONFGEN_STRUCTUREGENERATORSETTINGS_HPP
#define CDPL_CONFGEN_STRUCTUREGENERATORSETTINGS_HPP

#include <cstddef>

#include "CDPL/ConfGen/APIPrefix.hpp"
#include "CDPL/ConfGen/FragmentConformerGeneratorSettings.hpp"


namespace CDPL
{

    namespace ConfGen
    {

        /**
         * \brief Bundle of configuration parameters for ConfGen::StructureGenerator.
         */
        class CDPL_CONFGEN_API StructureGeneratorSettings
        {

          public:
            /** \brief A static instance providing settings default values. */
            static const StructureGeneratorSettings DEFAULT;

            /**
             * \brief Constructs the \c %StructureGeneratorSettings instance with default values.
             */
            StructureGeneratorSettings();

            /**
             * \brief Sets the structure-generation mode (see ConfGen::StructureGenerationMode).
             * \param mode The new generation mode.
             */
            void setGenerationMode(unsigned int mode);

            /**
             * \brief Returns the currently configured structure-generation mode.
             * \return The ConfGen::StructureGenerationMode identifier.
             */
            unsigned int getGenerationMode() const;

            /**
             * \brief Specifies whether 3D coordinates should be generated from scratch (vs. starting from existing input coordinates).
             * \param generate \c true to generate coordinates from scratch, and \c false to keep existing input coordinates.
             */
            void generateCoordinatesFromScratch(bool generate);

            /**
             * \brief Tells whether 3D coordinates are generated from scratch.
             * \return \c true if coordinates are generated from scratch, and \c false otherwise.
             */
            bool generateCoordinatesFromScratch() const;

            /**
             * \brief Specifies whether torsion-angle tolerance ranges are sampled during structure generation.
             * \param sample \c true to enable sampling, and \c false to disable it.
             */
            void sampleAngleToleranceRanges(bool sample);

            /**
             * \brief Tells whether torsion-angle tolerance ranges are sampled during structure generation.
             * \return \c true if sampling is enabled, and \c false otherwise.
             */
            bool sampleAngleToleranceRanges() const;

            /**
             * \brief Sets the timeout for the structure-generation pipeline.
             * \param mil_secs The new timeout in milliseconds (\e 0 disables the timeout).
             */
            void setTimeout(std::size_t mil_secs);

            /**
             * \brief Returns the currently configured timeout in milliseconds.
             * \return The timeout in milliseconds.
             */
            std::size_t getTimeout() const;

            /**
             * \brief Sets the MMFF94 force-field variant used for fragment-mode structure generation (see ForceField::MMFF94 variants).
             * \param type The new force-field type.
             */
            void setFragmentModeForceFieldType(unsigned int type);

            /**
             * \brief Returns the currently configured fragment-mode force-field type.
             * \return The force-field type identifier.
             */
            unsigned int getFragmentModeForceFieldType() const;

            /**
             * \brief Sets the MMFF94 force-field variant used for distance-geometry-mode structure generation.
             * \param type The new force-field type.
             */
            void setDGModeForceFieldType(unsigned int type);

            /**
             * \brief Returns the currently configured DG-mode force-field type.
             * \return The force-field type identifier.
             */
            unsigned int getDGModeForceFieldType() const;

            /**
             * \brief Specifies whether force-field parameterization should be strict (missing parameters cause failure).
             * \param strict \c true to enable strict parameterization, and \c false to tolerate missing parameters.
             */
            void strictForceFieldParameterization(bool strict);

            /**
             * \brief Tells whether force-field parameterization is strict.
             * \return \c true if strict parameterization is enabled, and \c false otherwise.
             */
            bool strictForceFieldParameterization() const;

            /**
             * \brief Sets the dielectric constant used in the electrostatic-energy term.
             * \param de_const The new dielectric constant.
             */
            void setDielectricConstant(double de_const);

            /**
             * \brief Returns the currently configured dielectric constant.
             * \return The dielectric constant.
             */
            double getDielectricConstant() const;

            /**
             * \brief Sets the distance exponent used in the electrostatic-energy term.
             * \param exponent The new distance exponent.
             */
            void setDistanceExponent(double exponent);

            /**
             * \brief Returns the currently configured distance exponent.
             * \return The distance exponent.
             */
            double getDistanceExponent() const;

            /**
             * \brief Sets the maximum number of iterations of the force-field-based coordinate refinement step.
             * \param max_iter The new maximum number of iterations.
             */
            void setMaxNumRefinementIterations(std::size_t max_iter);

            /**
             * \brief Returns the currently configured maximum number of refinement iterations.
             * \return The maximum number of iterations.
             */
            std::size_t getMaxNumRefinementIterations() const;

            /**
             * \brief Sets the convergence tolerance of the force-field-based coordinate refinement step.
             * \param tol The new refinement tolerance.
             */
            void setRefinementTolerance(double tol);

            /**
             * \brief Returns the currently configured refinement tolerance.
             * \return The refinement tolerance.
             */
            double getRefinementTolerance() const;

            /**
             * \brief Sets the maximum number of conformers sampled during structure generation.
             * \param max_num The new maximum number of sampled conformers.
             */
            void setMaxNumSampledConformers(std::size_t max_num);

            /**
             * \brief Returns the currently configured maximum number of sampled conformers.
             * \return The maximum number of sampled conformers.
             */
            std::size_t getMaxNumSampledConformers() const;

            /**
             * \brief Sets the cycle size for the convergence check of the structure-sampling loop.
             * \param size The new convergence-check cycle size.
             */
            void setConvergenceCheckCycleSize(std::size_t size);

            /**
             * \brief Returns the currently configured convergence-check cycle size.
             * \return The convergence-check cycle size.
             */
            std::size_t getConvergenceCheckCycleSize() const;

            /**
             * \brief Sets the minimum number of rotatable bonds in a macrocycle for it to be considered macrocyclic.
             * \param min_count The new threshold.
             */
            void setMacrocycleRotorBondCountThreshold(std::size_t min_count);

            /**
             * \brief Returns the currently configured macrocycle rotor-bond-count threshold.
             * \return The threshold.
             */
            std::size_t getMacrocycleRotorBondCountThreshold() const;

            /**
             * \brief Returns the embedded fragment-build settings (mutable).
             * \return A reference to the fragment-build settings.
             */
            FragmentConformerGeneratorSettings& getFragmentBuildSettings();

            /**
             * \brief Returns the embedded fragment-build settings.
             * \return A \c const reference to the fragment-build settings.
             */
            const FragmentConformerGeneratorSettings& getFragmentBuildSettings() const;

          private:
            unsigned int                       generationMode;
            bool                               fromScratch;
            bool                               sampleTolRanges;
            std::size_t                        timeout;
            unsigned int                       fragModeForceFieldType;
            unsigned int                       dgModeForceFieldType;
            bool                               strictParam;
            double                             dielectricConst;
            double                             distExponent;
            std::size_t                        maxNumRefIters;
            double                             refTolerance;
            std::size_t                        maxNumSampledConfs;
            std::size_t                        convCheckCycleSize;
            std::size_t                        mcRotorBondCountThresh;
            FragmentConformerGeneratorSettings fragBuildSettings;
        };
    }; // namespace ConfGen
} // namespace CDPL

#endif // CDPL_CONFGEN_STRUCTUREGENERATORSETTINGS_HPP
