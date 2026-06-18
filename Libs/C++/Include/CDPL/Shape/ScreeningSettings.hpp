/* 
 * ScreeningSettings.hpp 
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
 * \brief Definition of class CDPL::Shape::ScreeningSettings.
 */

#ifndef CDPL_SHAPE_SCREENINGSETTINGS_HPP
#define CDPL_SHAPE_SCREENINGSETTINGS_HPP

#include <cstddef>
#include <limits>
#include <functional>

#include "CDPL/Shape/APIPrefix.hpp"


namespace CDPL
{

    namespace Shape
    {

        class AlignmentResult;

        /**
         * \brief Bundle of configuration parameters for Shape::ScreeningProcessor.
         *
         * The settings select the scoring function, the type of color (pharmacophore) features used,
         * the screening mode (e.g. best-overall vs. best-per-query), the alignment-start strategy,
         * and the parameters of the iterative overlap optimization.
         */
        class CDPL_SHAPE_API ScreeningSettings
        {

          public:
            /**
             * \brief A static instance with default-initialized values.
             */
            static const ScreeningSettings DEFAULT;

            /**
             * \brief Sentinel value (NaN) used to disable the score cutoff.
             */
            static constexpr double        NO_CUTOFF = std::numeric_limits<double>::quiet_NaN();

            /**
             * \brief Type of the function used to score an alignment result.
             */
            typedef std::function<double(const AlignmentResult&)> ScoringFunction;

            /**
             * \brief Specifies which alignment hits are reported by the screening processor.
             */
            enum ScreeningMode
            {

                /**
                 * \brief Report only the single best-scoring alignment hit across all queries.
                 */
                BEST_OVERALL_MATCH,
                
                /**
                 * \brief Report the best-scoring alignment hit per query molecule.
                 */
                BEST_MATCH_PER_QUERY,
                
                /**
                 * \brief Report the best-scoring alignment hit per (query, query conformer) pair.
                 */
                BEST_MATCH_PER_QUERY_CONF
            };

            /**
             * \brief Specifies which kind of color (pharmacophore) features are used during shape alignment.
             */
            enum ColorFeatureType
            {

                /**
                 * \brief Disable color features (shape-only alignment).
                 */
                NO_FEATURES,
                
                /**
                 * \brief Use pharmacophore features derived from explicit charges.
                 */
                PHARMACOPHORE_EXP_CHARGES,
                
                /**
                 * \brief Use pharmacophore features derived from perceived (implicit) charges.
                 */
                PHARMACOPHORE_IMP_CHARGES
            };

            /**
             * \brief Bitmask flags specifying the strategies used to seed alignment starting transformations.
             */
            enum AlignmentMode
            {

                /**
                 * \brief Disable alignment entirely (overlap is computed in the input pose only).
                 */
                NO_ALIGNMENT          = 0x0,
                
                /**
                 * \brief Place the aligned shape at the centroid of the reference shape.
                 */
                SHAPE_CENTROID        = 0x1,
                
                /**
                 * \brief Seed alignments by superimposing pairs of atom centers.
                 */
                ATOM_CENTERS          = 0x2,
                
                /**
                 * \brief Seed alignments by superimposing pairs of color (pharmacophore) feature centers.
                 */
                COLOR_FEATURE_CENTERS = 0x4,
                
                /**
                 * \brief Seed alignments with random rotations.
                 */
                RANDOM                = 0x8
            };

            /**
             * \brief Constructs a \c %ScreeningSettings instance with default values.
             */
            ScreeningSettings();

            /**
             * \brief Sets the scoring function used to rank alignment results.
             * \param func The scoring function.
             */
            void setScoringFunction(const ScoringFunction& func);

            /**
             * \brief Returns the currently configured scoring function.
             * \return A \c const reference to the scoring function.
             */
            const ScoringFunction& getScoringFunction() const;

            /**
             * \brief Sets the color feature type to use during alignment.
             * \param type The new color-feature type.
             */
            void setColorFeatureType(ColorFeatureType type);

            /**
             * \brief Returns the currently configured color feature type.
             * \return The color-feature type.
             */
            ColorFeatureType getColorFeatureType() const;

            /**
             * \brief Sets the screening mode.
             * \param mode The new screening mode.
             */
            void setScreeningMode(ScreeningMode mode);

            /**
             * \brief Returns the currently configured screening mode.
             * \return The screening mode.
             */
            ScreeningMode getScreeningMode() const;

            /**
             * \brief Sets the alignment-mode bitmask (see AlignmentMode).
             * \param mode The new alignment-mode bitmask.
             */
            void setAlignmentMode(AlignmentMode mode);

            /**
             * \brief Returns the currently configured alignment-mode bitmask.
             * \return The alignment-mode bitmask.
             */
            AlignmentMode getAlignmentMode() const;

            /**
             * \brief Sets the number of random starting transformations when AlignmentMode::RANDOM is enabled.
             * \param num_starts The new number of random starts.
             */
            void setNumRandomStarts(std::size_t num_starts);

            /**
             * \brief Returns the currently configured number of random starts.
             * \return The number of random starts.
             */
            std::size_t getNumRandomStarts() const;

            /**
             * \brief Enables or disables the all-carbon mode (treats every heavy atom as carbon for shape generation).
             * \param all_c \c true to enable the all-carbon mode, and \c false to use the actual atom types.
             */
            void allCarbonMode(bool all_c);

            /**
             * \brief Tells whether the all-carbon mode is enabled.
             * \return \c true if the all-carbon mode is enabled, and \c false otherwise.
             */
            bool allCarbonMode() const;

            /**
             * \brief Specifies whether only a single conformer of each molecule is considered.
             * \param single_conf \c true to consider only a single conformer, and \c false to consider all conformers.
             */
            void singleConformerSearch(bool single_conf);

            /**
             * \brief Tells whether only a single conformer of each molecule is considered.
             * \return \c true if only a single conformer is considered, and \c false otherwise.
             */
            bool singleConformerSearch() const;

            /**
             * \brief Specifies whether the overlap shall be optimized iteratively after the initial alignment.
             * \param optimize \c true to optimize the overlap, and \c false to skip optimization.
             */
            void optimizeOverlap(bool optimize);

            /**
             * \brief Tells whether the overlap is optimized iteratively.
             * \return \c true if the overlap is optimized, and \c false otherwise.
             */
            bool optimizeOverlap() const;

            /**
             * \brief Specifies whether the overlap optimization shall use a greedy strategy that stops at the first local maximum.
             * \param greedy \c true to use the greedy strategy, and \c false to use the full optimization.
             */
            void greedyOptimization(bool greedy);

            /**
             * \brief Tells whether the overlap optimization uses a greedy strategy.
             * \return \c true if the greedy strategy is used, and \c false otherwise.
             */
            bool greedyOptimization() const;

            /**
             * \brief Sets the maximum number of overlap-optimization iterations.
             * \param max_iter The new maximum number of iterations.
             */
            void setMaxNumOptimizationIterations(std::size_t max_iter);

            /**
             * \brief Returns the currently configured maximum number of overlap-optimization iterations.
             * \return The maximum number of iterations.
             */
            std::size_t getMaxNumOptimizationIterations() const;

            /**
             * \brief Sets the gradient norm at which the overlap optimization is stopped.
             * \param grad_norm The new stop gradient norm.
             */
            void setOptimizationStopGradient(double grad_norm);

            /**
             * \brief Returns the currently configured overlap-optimization stop gradient.
             * \return The stop gradient norm.
             */
            double getOptimizationStopGradient() const;

            /**
             * \brief Sets the minimum score below which alignment hits are discarded (or NO_CUTOFF).
             * \param cutoff The new score cutoff (or NO_CUTOFF to disable cutoff filtering).
             */
            void setScoreCutoff(double cutoff);

            /**
             * \brief Returns the currently configured score cutoff (or NO_CUTOFF).
             * \return The score cutoff (or NO_CUTOFF if cutoff filtering is disabled).
             */
            double getScoreCutoff() const;

          private:
            ScoringFunction  scoringFunc;
            ColorFeatureType colorFtrType;
            ScreeningMode    screeningMode;
            AlignmentMode    almntMode;
            std::size_t      numRandomStarts;
            bool             allCarbon;
            bool             singleConfSearch;
            bool             optOverlap;
            bool             greedyOpt;
            std::size_t      numOptIter;
            double           optStopGrad;
            double           scoreCutoff;
        };
    } // namespace Shape
} // namespace CDPL

#endif // CDPL_SHAPE_SCREENINGSETTINGS_HPP
