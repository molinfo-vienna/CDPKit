/* 
 * ConformerGeneratorSettings.hpp 
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
 * \brief Definition of class CDPL::ConfGen::ConformerGeneratorSettings.
 */

#ifndef CDPL_CONFGEN_CONFORMERGENERATORSETTINGS_HPP
#define CDPL_CONFGEN_CONFORMERGENERATORSETTINGS_HPP

#include <cstddef>
#include <vector>
#include <utility>

#include "CDPL/ConfGen/APIPrefix.hpp"
#include "CDPL/ConfGen/FragmentConformerGeneratorSettings.hpp"


namespace CDPL
{

    namespace ConfGen
    {

        /**
         * \brief Bundle of configuration parameters for conformer ensemble generation via class ConfGen::ConformerGenerator.
         */
        class CDPL_CONFGEN_API ConformerGeneratorSettings
        {

          public:
            /** \brief Instance providing configuration parameter default values. */
            static const ConformerGeneratorSettings DEFAULT;
            /** \brief Preset producing a small, diversity-optimized conformer ensemble. */
            static const ConformerGeneratorSettings SMALL_SET_DIVERSE;
            /** \brief Preset producing a medium-sized, diversity-optimized conformer ensemble. */
            static const ConformerGeneratorSettings MEDIUM_SET_DIVERSE;
            /** \brief Preset producing a large, diversity-optimized conformer ensemble. */
            static const ConformerGeneratorSettings LARGE_SET_DIVERSE;
            /** \brief Preset producing a small, dense conformer ensemble (tight RMSD threshold). */
            static const ConformerGeneratorSettings SMALL_SET_DENSE;
            /** \brief Preset producing a medium-sized, dense conformer ensemble (tight RMSD threshold). */
            static const ConformerGeneratorSettings MEDIUM_SET_DENSE;
            /** \brief Preset producing a large, dense conformer ensemble (tight RMSD threshold). */
            static const ConformerGeneratorSettings LARGE_SET_DENSE;

            /**
             * \brief Constructs the \c %ConformerGeneratorSettings instance with default configuration parameter values.
             */
            ConformerGeneratorSettings();

            /**
             * \brief Specifies the conformer-sampling strategy to use.
             * \param mode One of the ConfGen::ConformerSamplingMode values.
             */
            void setSamplingMode(unsigned int mode);

            /**
             * \brief Returns the currently configured conformer-sampling strategy.
             * \return One of the ConfGen::ConformerSamplingMode values.
             */
            unsigned int getSamplingMode() const;

            /**
             * \brief Specifies whether torsions of heteroatom hydrogen rotors shall be sampled.
             * \param sample If \c true, such torsions are sampled.
             */
            void sampleHeteroAtomHydrogens(bool sample);

            /**
             * \brief Tells whether torsions of heteroatom hydrogen rotors are sampled.
             * \return \c true if sampling is enabled, and \c false otherwise.
             */
            bool sampleHeteroAtomHydrogens() const;

            /**
             * \brief Specifies whether additional torsion samples within the tolerance ranges defined by the torsion library entries shall be generated.
             * \param sample If \c true, tolerance-range sampling is enabled.
             */
            void sampleAngleToleranceRanges(bool sample);

            /**
             * \brief Tells whether tolerance-range sampling is enabled.
             * \return \c true if tolerance-range sampling is enabled, and \c false otherwise.
             */
            bool sampleAngleToleranceRanges() const;

            /**
             * \brief Specifies whether ring conformations shall be enumerated.
             * \param enumerate If \c true, ring conformations are enumerated.
             */
            void enumerateRings(bool enumerate);

            /**
             * \brief Tells whether ring conformations are enumerated.
             * \return \c true if ring conformations are enumerated, and \c false otherwise.
             */
            bool enumerateRings() const;

            /**
             * \brief Sets the enumeration mode for stereogenic nitrogen centers.
             * \param mode One of the ConfGen::NitrogenEnumerationMode values.
             */
            void setNitrogenEnumerationMode(unsigned int mode);

            /**
             * \brief Returns the currently configured nitrogen enumeration mode.
             * \return One of the ConfGen::NitrogenEnumerationMode values.
             */
            unsigned int getNitrogenEnumerationMode() const;

            /**
             * \brief Specifies whether 3D coordinates shall be generated from scratch (ignoring any 3D input).
             * \param generate If \c true, 3D coordinates are always generated from scratch.
             */
            void generateCoordinatesFromScratch(bool generate);

            /**
             * \brief Tells whether 3D coordinates are generated from scratch.
             * \return \c true if 3D coordinates are always regenerated, and \c false otherwise.
             */
            bool generateCoordinatesFromScratch() const;

            /**
             * \brief Specifies whether the input conformation shall be included in the output conformer ensemble.
             * \param include If \c true, the input coordinates become part of the output ensemble.
             */
            void includeInputCoordinates(bool include);

            /**
             * \brief Tells whether the input coordinates are included in the output conformer ensemble.
             * \return \c true if the input coordinates are included, and \c false otherwise.
             */
            bool includeInputCoordinates() const;

            /**
             * \brief Sets the energy window size (in kcal/mol) above the found global minimum within which conformers are kept.
             * \param win_size The new energy window size in kcal/mol.
             */
            void setEnergyWindow(double win_size);

            /**
             * \brief Returns the configured energy window size.
             * \return The energy window size in kcal/mol.
             */
            double getEnergyWindow() const;

            /**
             * \brief Returns the energy window size that applies for molecules with \a num_rot_bonds rotatable bonds.
             *
             * If a rotatable bond-specific range was registered via addEnergyWindowRange(), the matching value
             * is returned; otherwise the global window from getEnergyWindow() is used.
             *
             * \param num_rot_bonds The rotatable bond count.
             * \return The energy window size in kcal/mol.
             * \since 1.1
             */
            double getEnergyWindow(std::size_t num_rot_bonds) const;

            /**
             * \brief Removes all registered rotatable bond count-dependent energy window overrides.
             * \since 1.1
             */
            void clearEnergyWindowRanges();

            /**
             * \brief Registers an energy window override that applies up to and including \a num_rot_bonds rotatable bonds.
             * \param num_rot_bonds The upper-bound rotatable bond count to which \a win_size applies.
             * \param win_size The energy window size (in kcal/mol).
             * \since 1.1
             */
            void addEnergyWindowRange(std::size_t num_rot_bonds, double win_size);

            /**
             * \brief Sets the maximum number of conformers to keep in the internal candidate pool.
             * \param max_size The new maximum pool size.
             */
            void setMaxPoolSize(std::size_t max_size);

            /**
             * \brief Returns the maximum number of conformers kept in the internal candidate pool.
             * \return The maximum pool size.
             */
            std::size_t getMaxPoolSize() const;

            /**
             * \brief Sets the upper limit on the number of rotatable bonds an input molecule may have to be processed.
             * \param max_count The new rotatable bond count limit (\e -1 disables the limit).
             * \since 1.1
             */
            void setMaxRotatableBondCount(long max_count);

            /**
             * \brief Returns the rotatable bond count limit above which input molecules are rejected.
             * \return The rotatable bond count limit (\e -1 disables the limit).
             * \since 1.1
             */
            long getMaxRotatableBondCount() const;

            /**
             * \brief Sets the maximum allowed wall clock processing time per molecule.
             * \param mil_secs The new time limit in milliseconds (zero disables the limit).
             */
            void setTimeout(std::size_t mil_secs);

            /**
             * \brief Returns the configured per-molecule wall clock time limit.
             * \return The time limit in milliseconds (zero if disabled).
             */
            std::size_t getTimeout() const;

            /**
             * \brief Sets the force field type used by the systematic sampling pipeline.
             * \param type One of the ConfGen::ForceFieldType values.
             */
            void setForceFieldTypeSystematic(unsigned int type);

            /**
             * \brief Returns the force field type used by the systematic sampling pipeline.
             * \return One of the ConfGen::ForceFieldType values.
             */
            unsigned int getForceFieldTypeSystematic() const;

            /**
             * \brief Sets the force field type used by the stochastic sampling pipeline.
             * \param type One of the ConfGen::ForceFieldType values.
             */
            void setForceFieldTypeStochastic(unsigned int type);

            /**
             * \brief Returns the force field type used by the stochastic sampling pipeline.
             * \return One of the ConfGen::ForceFieldType values.
             */
            unsigned int getForceFieldTypeStochastic() const;

            /**
             * \brief Specifies whether strict MMFF94 parameterization is required.
             * \param strict If \c true, missing/ambiguous parameters cause a generation failure.
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
             * \brief Sets the maximum number of output conformers per molecule.
             * \param max_num The new output conformer count limit.
             */
            void setMaxNumOutputConformers(std::size_t max_num);

            /**
             * \brief Returns the configured maximum number of output conformers.
             * \return The output conformer count limit.
             */
            std::size_t getMaxNumOutputConformers() const;

            /**
             * \brief Returns the maximum number of output conformers that applies for molecules with \a num_rot_bonds rotatable bonds.
             *
             * If a rotatable bond-specific range was registered via addMaxNumOutputConformersRange(), the matching value
             * is returned; otherwise the global limit from getMaxNumOutputConformers() is used.
             *
             * \param num_rot_bonds The rotatable bond count.
             * \return The output conformer limit.
             * \since 1.1
             */
            std::size_t getMaxNumOutputConformers(std::size_t num_rot_bonds) const;

            /**
             * \brief Removes all registered rotatable bond count-dependent output conformer overrides.
             * \since 1.1
             */
            void clearMaxNumOutputConformersRanges();

            /**
             * \brief Registers an output conformer limit override that applies up to and including \a num_rot_bonds rotatable bonds.
             * \param num_rot_bonds The upper-bound rotatable bond count to which \a max_num applies.
             * \param max_num The output conformer limit used for matching molecules.
             * \since 1.1
             */
            void addMaxNumOutputConformersRange(std::size_t num_rot_bonds, std::size_t max_num);

            /**
             * \brief Sets the minimum pairwise heavy-atom RMSD that conformers in the output ensemble must keep.
             * \param min_rmsd The new minimum RMSD threshold (in &Aring;).
             */
            void setMinRMSD(double min_rmsd);

            /**
             * \brief Returns the globally configured minimum RMSD threshold.
             * \return The minimum RMSD threshold (in &Aring;).
             */
            double getMinRMSD() const;

            /**
             * \brief Returns the minimum RMSD threshold that applies for molecules with \a num_rot_bonds rotatable bonds.
             *
             * If a rotatable bond-specific range was registered via addMinRMSDRange(), the matching value
             * is returned; otherwise the global threshold from getMinRMSD() is used.
             *
             * \param num_rot_bonds The rotatable bond count.
             * \return The minimum RMSD threshold (in &Aring;).
             * \since 1.1
             */
            double getMinRMSD(std::size_t num_rot_bonds) const;

            /**
             * \brief Removes all registered rotatable bond count-dependent minimum RMSD overrides.
             * \since 1.1
             */
            void clearMinRMSDRanges();

            /**
             * \brief Registers a minimum RMSD override that applies up to and including \a num_rot_bonds rotatable bonds.
             * \param num_rot_bonds The upper-bound rotatable bond count to which \a min_rmsd applies.
             * \param min_rmsd The minimum RMSD threshold used for matching molecules.
             * \since 1.1
             */
            void addMinRMSDRange(std::size_t num_rot_bonds, double min_rmsd);

            /**
             * \brief Sets the maximum number of MMFF94 energy minimization iterations per conformer.
             * \param max_iter The new iteration limit (zero disables refinement).
             */
            void setMaxNumRefinementIterations(std::size_t max_iter);

            /**
             * \brief Returns the maximum number of MMFF94 energy minimization iterations per conformer.
             * \return The iteration limit (zero if refinement is disabled).
             */
            std::size_t getMaxNumRefinementIterations() const;

            /**
             * \brief Sets the convergence tolerance of the MMFF94 energy minimization step.
             * \param tol The new convergence tolerance.
             */
            void setRefinementTolerance(double tol);

            /**
             * \brief Returns the convergence tolerance of the MMFF94 energy minimization step.
             * \return The convergence tolerance.
             */
            double getRefinementTolerance() const;

            /**
             * \brief Sets the upper bound on the number of trial conformations produced by the stochastic sampler.
             * \param max_num The new sampled conformer limit.
             */
            void setMaxNumSampledConformers(std::size_t max_num);

            /**
             * \brief Returns the upper bound on the number of trial conformations produced by the stochastic sampler.
             * \return The sampled conformer limit.
             */
            std::size_t getMaxNumSampledConformers() const;

            /**
             * \brief Sets the cycle size (in trial conformations) at which the stochastic sampler tests for convergence.
             * \param size The new convergence check cycle size.
             */
            void setConvergenceCheckCycleSize(std::size_t size);

            /**
             * \brief Returns the cycle size at which the stochastic sampler tests for convergence.
             * \return The convergence check cycle size.
             */
            std::size_t getConvergenceCheckCycleSize() const;

            /**
             * \brief Sets the minimum number of rotatable bonds a ring must contain to be considered as a flexible macrocycle.
             * \param min_count The new flexible macrocycle rotatable bond count threshold.
             */
            void setMacrocycleRotorBondCountThreshold(std::size_t min_count);

            /**
             * \brief Returns the flexible macrocycle rotatable bond count threshold.
             * \return The threshold.
             */
            std::size_t getMacrocycleRotorBondCountThreshold() const;

            /**
             * \brief Returns a reference to the nested fragment conformer build settings.
             * \return A reference to the build settings.
             */
            FragmentConformerGeneratorSettings& getFragmentBuildSettings();

            /**
             * \brief Returns a \c const reference to the nested fragment conformer build settings.
             * \return A \c const reference to the build settings.
             */
            const FragmentConformerGeneratorSettings& getFragmentBuildSettings() const;

          private:
            typedef std::pair<std::size_t, std::size_t> STPair;
            typedef std::pair<std::size_t, double>      STDoublePair;
            typedef std::vector<STPair>                 STPairArray;
            typedef std::vector<STDoublePair>           STDoublePairArray;

            template <typename A>
            static typename A::value_type::second_type getValueForCount(const A& array, std::size_t num_rot_bonds);
            
            unsigned int                       samplingMode;
            bool                               sampleHetAtomHs;
            bool                               sampleTolRanges;
            bool                               enumRings;
            unsigned int                       nitrogenEnumMode;
            bool                               fromScratch;
            bool                               incInputCoords;
            double                             eWindow;
            STDoublePairArray                  eWindowRanges;
            std::size_t                        maxPoolSize;
            long                               maxRotorBondCount;
            std::size_t                        timeout;
            unsigned int                       forceFieldTypeSys;
            unsigned int                       forceFieldTypeStoch;
            bool                               strictParam;
            double                             dielectricConst;
            double                             distExponent;
            std::size_t                        maxNumOutputConfs;
            STPairArray                        maxNumOutputConfRanges;
            double                             minRMSD;
            STDoublePairArray                  minRMSDRanges;
            std::size_t                        maxNumRefIters;
            double                             refTolerance;
            std::size_t                        maxNumSampledConfs;
            std::size_t                        convCheckCycleSize;
            std::size_t                        mcRotorBondCountThresh;
            FragmentConformerGeneratorSettings fragBuildSettings;
        };
    }; // namespace ConfGen
} // namespace CDPL

#endif // CDPL_CONFGEN_CONFORMERGENERATORSETTINGS_HPP
