/* 
 * GRAILDataSetGenerator.hpp 
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
 * \brief Definition of class CDPL::GRAIL::GRAILDataSetGenerator.
 */

#ifndef CDPL_GRAIL_GRAILDATASETGENERATOR_HPP
#define CDPL_GRAIL_GRAILDATASETGENERATOR_HPP

#include <map>
#include <set>
#include <utility>
#include <string>
#include <memory>
#include <functional>

#include "CDPL/GRAIL/APIPrefix.hpp"
#include "CDPL/GRAIL/FeatureInteractionScoreGridCalculator.hpp"
#include "CDPL/GRAIL/AtomDensityGridCalculator.hpp"
#include "CDPL/Grid/RegularGridSet.hpp"
#include "CDPL/Pharm/DefaultPharmacophoreGenerator.hpp"
#include "CDPL/Pharm/BasicPharmacophore.hpp"
#include "CDPL/Chem/Atom3DCoordinatesFunction.hpp"
#include "CDPL/Math/Matrix.hpp"
#include "CDPL/Math/Vector.hpp"


namespace CDPL
{

    namespace GRAIL
    {

        /**
         * \brief Generator that pre-computes the per-cell interaction-score grids and the atom-density
         *        grid used by GRAIL scoring of ligand poses against a target environment.
         *
         * For every enabled (ligand feature type, target feature type) pair the generator runs a
         * GRAIL::FeatureInteractionScoreGridCalculator and stores the resulting grid in a
         * Grid::DRegularGridSet. Optionally the generator also produces an atom-density grid of the
         * target environment (e.g. for use as a buriedness or accessibility weight).
         *
         * \see [\ref GRAIL]
         * \since 1.1
         */
        class CDPL_GRAIL_API GRAILDataSetGenerator
        {

          public:
            /**
             * \brief A reference-counted smart pointer [\ref SHPTR] for dynamically allocated \c %GRAILDataSetGenerator instances.
             */
            typedef std::shared_ptr<GRAILDataSetGenerator> SharedPointer;

            /**
             * \brief Re-export of the scoring-function type used by the underlying score-grid calculator.
             */
            typedef FeatureInteractionScoreGridCalculator::ScoringFunction          ScoringFunction;

            /**
             * \brief Re-export of the score-combination function type used by the underlying score-grid calculator.
             */
            typedef FeatureInteractionScoreGridCalculator::ScoreCombinationFunction ScoreCombinationFunction;

            /**
             * \brief Type of the generic functor used to post-process a generated pharmacophore prior to grid calculation.
             */
            typedef std::function<void(CDPL::Pharm::Pharmacophore&)> PharmacophoreProcessingFunction;

            /**
             * \brief Default grid spacing (isotropic).
             */
            static constexpr double DEF_GRID_STEP_SIZE = 0.5;

            /**
             * \brief Constructs the \c %GRAILDataSetGenerator instance.
             */
            GRAILDataSetGenerator();

            /**
             * \brief Virtual destructor.
             */
            virtual ~GRAILDataSetGenerator() {}

            /**
             * \brief Enables or disables interaction-grid generation for the given (ligand feature type, target feature type) pair.
             * \param ftr_type The ligand feature type.
             * \param tgt_ftr_type The target feature type.
             * \param enable If \c true, the interaction is enabled.
             */
            void enableInteraction(unsigned int ftr_type, unsigned int tgt_ftr_type, bool enable);

            /**
             * \brief Tells whether interaction-grid generation is enabled for the given (ligand feature type, target feature type) pair.
             * \param ftr_type The ligand feature type.
             * \param tgt_ftr_type The target feature type.
             * \return \c true if the interaction is enabled, and \c false otherwise.
             */
            bool isInteractionEnabled(unsigned int ftr_type, unsigned int tgt_ftr_type) const;

            /**
             * \brief Disables interaction-grid generation for all feature-type pairs.
             */
            void clearEnabledInteractions();

            /**
             * \brief Sets the scoring function for the given (ligand feature type, target feature type) pair.
             * \param ftr_type The ligand feature type.
             * \param tgt_ftr_type The target feature type.
             * \param func The scoring function.
             */
            void setScoringFunction(unsigned int ftr_type, unsigned int tgt_ftr_type, const ScoringFunction& func);

            /**
             * \brief Returns the scoring function configured for the given (ligand feature type, target feature type) pair.
             * \param ftr_type The ligand feature type.
             * \param tgt_ftr_type The target feature type.
             * \return The configured scoring function (or an empty function if no entry is registered).
             */
            const ScoringFunction& getScoringFunction(unsigned int ftr_type, unsigned int tgt_ftr_type) const;

            /**
             * \brief Removes the scoring function configured for the given (ligand feature type, target feature type) pair.
             * \param ftr_type The ligand feature type.
             * \param tgt_ftr_type The target feature type.
             */
            void removeScoringFunction(unsigned int ftr_type, unsigned int tgt_ftr_type);

            /**
             * \brief Sets the grid name associated with the given (ligand feature type, target feature type) pair.
             * \param ftr_type The ligand feature type.
             * \param tgt_ftr_type The target feature type.
             * \param name The grid name.
             */
            void setGridName(unsigned int ftr_type, unsigned int tgt_ftr_type, const std::string& name);

            /**
             * \brief Returns the grid name associated with the given (ligand feature type, target feature type) pair.
             * \param ftr_type The ligand feature type.
             * \param tgt_ftr_type The target feature type.
             * \return The grid name.
             */
            const std::string& getGridName(unsigned int ftr_type, unsigned int tgt_ftr_type) const;

            /**
             * \brief Removes the grid name associated with the given (ligand feature type, target feature type) pair.
             * \param ftr_type The ligand feature type.
             * \param tgt_ftr_type The target feature type.
             */
            void removeGridName(unsigned int ftr_type, unsigned int tgt_ftr_type);

            /**
             * \brief Sets the function used to combine per-feature scores into a single grid cell value.
             * \param func The score-combination function.
             */
            void setScoreCombinationFunction(const ScoreCombinationFunction& func);

            /**
             * \brief Returns the currently configured score-combination function.
             * \return The configured score-combination function.
             */
            const ScoreCombinationFunction& getScoreCombinationFunction() const;

            /**
             * \brief Enables or disables normalization of the combined per-cell scores to the range [0, 1].
             * \param normalize If \c true, the combined scores are normalized.
             */
            void normalizeScores(bool normalize);

            /**
             * \brief Tells whether the combined per-cell scores are normalized.
             * \return \c true if the combined scores are normalized, and \c false otherwise.
             */
            bool scoresNormalized() const;

            /**
             * \brief Enables or disables multiplicative diminishing of interaction scores by the (normalized) atom density of the target environment.
             * \param diminish If \c true, scores are diminished by atom density.
             */
            void diminishScoresByAtomDensity(bool diminish);

            /**
             * \brief Tells whether the interaction scores are diminished by the atom density of the target environment.
             * \return \c true if scores are diminished by atom density, and \c false otherwise.
             */
            bool scoresDiminishedByAtomDensity() const;

            /**
             * \brief Specifies whether the target environment atom-density grid shall be added to the produced grid set.
             * \param store If \c true, the atom-density grid is stored.
             */
            void storeEnvironmentAtomDensityGrid(bool store);

            /**
             * \brief Tells whether the target environment atom-density grid is stored in the produced grid set.
             * \return \c true if the atom-density grid is stored, and \c false otherwise.
             */
            bool environmentAtomDensityGridStored() const;

            /**
             * \brief Sets the name to assign to the target environment atom-density grid in the produced grid set.
             * \param name The grid name.
             */
            void setEnvironmentAtomDensityGridName(const std::string& name);

            /**
             * \brief Returns the name assigned to the target environment atom-density grid.
             * \return The grid name.
             */
            const std::string& getEnvironmentAtomDensityGridName() const;

            /**
             * \brief Returns the affine transformation matrix that places the grids in the target coordinate frame.
             * \return The grid transformation matrix.
             */
            const Math::Matrix4D& getGridTransform() const;

            /**
             * \brief Sets the affine transformation matrix that places the grids in the target coordinate frame.
             * \tparam T The transformation matrix expression type.
             * \param xform The transformation matrix.
             */
            template <typename T>
            void setGridTransform(const T& xform)
            {
                gridTransform = xform;
            }

            /**
             * \brief Returns the currently configured grid spacing.
             * \return The configured grid spacing.
             */
            double getGridStepSize() const;

            /**
             * \brief Sets the grid spacing (isotropic).
             * \param size The grid spacing.
             */
            void setGridStepSize(double size);

            /**
             * \brief Returns the grid size in the \e x direction.
             * \return The grid size in the \e x direction.
             */
            std::size_t getGridXSize() const;

            /**
             * \brief Sets the grid size in the \e x direction.
             * \param size The grid size.
             */
            void setGridXSize(std::size_t size);

            /**
             * \brief Returns the grid size in the \e y direction.
             * \return The grid size in the \e y direction.
             */
            std::size_t getGridYSize() const;

            /**
             * \brief Sets the grid size in the \e y direction.
             * \param size The grid size.
             */
            void setGridYSize(std::size_t size);

            /**
             * \brief Returns the grid size in the \e z direction.
             * \return The grid size in the \e z direction.
             */
            std::size_t getGridZSize() const;

            /**
             * \brief Sets the grid size in the \e z direction.
             * \param size The grid size.
             */
            void setGridZSize(std::size_t size);

            /**
             * \brief Convenience method that configures grid size, spacing and transformation so that the grid covers the given axis-aligned bounding box.
             * \param bbox_min The bounding box minimum-corner coordinates.
             * \param bbox_max The bounding box maximum-corner coordinates.
             * \param step_size The grid spacing.
             */
            void setGridParamsForBoundingBox(const Math::Vector3D& bbox_min, const Math::Vector3D& bbox_max, double step_size = DEF_GRID_STEP_SIZE);

            /**
             * \brief Returns the internal pharmacophore generator used for the target environment.
             * \return A \c const reference to the pharmacophore generator.
             */
            const Pharm::DefaultPharmacophoreGenerator& getPharmacophoreGenerator() const;

            /**
             * \brief Returns the internal pharmacophore generator used for the target environment.
             * \return A reference to the pharmacophore generator.
             */
            Pharm::DefaultPharmacophoreGenerator& getPharmacophoreGenerator();

            /**
             * \brief Sets the function applied to the generated target pharmacophore before grid calculation (e.g. for filtering or modification).
             * \param func The pharmacophore processing function.
             */
            void setPharmacophoreProcessingFunction(const PharmacophoreProcessingFunction& func);

            /**
             * \brief Returns the currently configured pharmacophore processing function.
             * \return The configured pharmacophore processing function.
             */
            const PharmacophoreProcessingFunction& getPharmacophoreProcessingFunction() const;

            /**
             * \brief Calculates the interaction-score grids for all enabled feature-type pairs and stores them in \a grid_set.
             * \param tgt_env The target environment.
             * \param coords_func The function used to retrieve atom 3D-coordinates from \a tgt_env.
             * \param grid_set The output grid set.
             * \param append If \c true, the new grids are appended to \a grid_set; otherwise \a grid_set is cleared first.
             */
            void calcInteractionGrids(const Chem::MolecularGraph& tgt_env, const Chem::Atom3DCoordinatesFunction& coords_func,
                                      Grid::DRegularGridSet& grid_set, bool append = false);

            /**
             * \brief Calculates an atom-density grid for the given atoms.
             * \param atoms The atoms contributing to the density.
             * \param coords_func The function used to retrieve atom 3D-coordinates.
             * \param grid_name The name to assign to the resulting grid.
             * \return A smart pointer to the calculated atom-density grid.
             */
            Grid::DRegularGrid::SharedPointer
            calcAtomDensityGrid(const Chem::AtomContainer& atoms, const Chem::Atom3DCoordinatesFunction& coords_func,
                                const std::string& grid_name);

          private:
            Grid::DRegularGrid::SharedPointer createGrid() const;

            void init();

            typedef std::pair<unsigned int, unsigned int>      FeatureTypePair;
            typedef std::map<FeatureTypePair, ScoringFunction> ScoringFuncMap;
            typedef std::map<FeatureTypePair, std::string>     GridNameMap;
            typedef std::set<FeatureTypePair>                  EnabledInteractionsSet;

            ScoringFuncMap                        ftrInteractionScoringFuncMap;
            GridNameMap                           gridNameMap;
            EnabledInteractionsSet                enabledFtrInteractions;
            FeatureInteractionScoreGridCalculator ftrInteractionGridCalc;
            AtomDensityGridCalculator             atomDensityGridCalc;
            Pharm::DefaultPharmacophoreGenerator  pharmGenerator;
            PharmacophoreProcessingFunction       pharmProcessingFunc;
            Pharm::BasicPharmacophore             pharmacophore;
            double                                gridStepSize;
            std::size_t                           gridXSize;
            std::size_t                           gridYSize;
            std::size_t                           gridZSize;
            Math::Matrix4D                        gridTransform;
            bool                                  diminishByAtomDensity;
            bool                                  storeEnvAtomDensityGrid;
            std::string                           envAtomDensityGridName;
        };
    } // namespace GRAIL
} // namespace CDPL

#endif // CDPL_GRAIL_GRAILDATASETGENERATOR_HPP
