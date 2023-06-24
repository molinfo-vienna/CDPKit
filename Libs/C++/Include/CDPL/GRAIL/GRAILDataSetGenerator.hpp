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
 * \brief Definition of the class CDPL::GRAIL::GRAILDataSetGenerator.
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
         * \brief GRAILDataSetGenerator.
         * \see [\ref GRAIL]
         */
        class CDPL_GRAIL_API GRAILDataSetGenerator
        {

          public:
            typedef std::shared_ptr<GRAILDataSetGenerator> SharedPointer;

            typedef FeatureInteractionScoreGridCalculator::ScoringFunction          ScoringFunction;
            typedef FeatureInteractionScoreGridCalculator::ScoreCombinationFunction ScoreCombinationFunction;

            typedef std::function<void(CDPL::Pharm::Pharmacophore&)> PharmacophoreProcessingFunction;

            static constexpr double DEF_GRID_STEP_SIZE = 0.5;

            GRAILDataSetGenerator();

            virtual ~GRAILDataSetGenerator() {}

            void enableInteraction(unsigned int ftr_type, unsigned int tgt_ftr_type, bool enable);

            bool isInteractionEnabled(unsigned int ftr_type, unsigned int tgt_ftr_type) const;

            void clearEnabledInteractions();

            void setScoringFunction(unsigned int ftr_type, unsigned int tgt_ftr_type, const ScoringFunction& func);

            const ScoringFunction& getScoringFunction(unsigned int ftr_type, unsigned int tgt_ftr_type) const;

            void removeScoringFunction(unsigned int ftr_type, unsigned int tgt_ftr_type);

            void setGridName(unsigned int ftr_type, unsigned int tgt_ftr_type, const std::string& name);

            const std::string& getGridName(unsigned int ftr_type, unsigned int tgt_ftr_type) const;

            void removeGridName(unsigned int ftr_type, unsigned int tgt_ftr_type);

            void setScoreCombinationFunction(const ScoreCombinationFunction& func);

            const ScoreCombinationFunction& getScoreCombinationFunction() const;

            void normalizeScores(bool normalize);

            bool scoresNormalized() const;

            void diminishScoresByAtomDensity(bool diminish);

            bool scoresDiminishedByAtomDensity() const;

            void storeEnvironmentAtomDensityGrid(bool store);

            bool environmentAtomDensityGridStored() const;

            void setEnvironmentAtomDensityGridName(const std::string& name);

            const std::string& getEnvironmentAtomDensityGridName() const;

            const Math::Matrix4D& getGridTransform() const;

            template <typename T>
            void setGridTransform(const T& xform)
            {
                gridTransform = xform;
            }

            double getGridStepSize() const;

            void setGridStepSize(double size);

            std::size_t getGridXSize() const;

            void setGridXSize(std::size_t size);

            std::size_t getGridYSize() const;

            void setGridYSize(std::size_t size);

            std::size_t getGridZSize() const;

            void setGridZSize(std::size_t size);

            void setGridParamsForBoundingBox(const Math::Vector3D& bbox_min, const Math::Vector3D& bbox_max, double step_size = DEF_GRID_STEP_SIZE);

            const Pharm::DefaultPharmacophoreGenerator& getPharmacophoreGenerator() const;

            Pharm::DefaultPharmacophoreGenerator& getPharmacophoreGenerator();

            void setPharmacophoreProcessingFunction(const PharmacophoreProcessingFunction& func);

            const PharmacophoreProcessingFunction& getPharmacophoreProcessingFunction() const;

            void calcInteractionGrids(const Chem::MolecularGraph& tgt_env, const Chem::Atom3DCoordinatesFunction& coords_func,
                                      Grid::DRegularGridSet& grid_set, bool append = false);

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
