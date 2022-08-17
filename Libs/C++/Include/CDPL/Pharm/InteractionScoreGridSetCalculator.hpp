/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * InteractionScoreGridSetCalculator.hpp 
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

/**
 * \file
 * \brief Definition of the class CDPL::Pharm::InteractionScoreGridSetCalculator.
 */

#ifndef CDPL_PHARM_INTERACTIONSCOREGRIDSETCALCULATOR_HPP
#define CDPL_PHARM_INTERACTIONSCOREGRIDSETCALCULATOR_HPP

#include <map>
#include <set>
#include <utility>

#include "CDPL/Pharm/APIPrefix.hpp"
#include "CDPL/Pharm/InteractionScoreGridCalculator.hpp"
#include "CDPL/Grid/RegularGrid.hpp"


namespace CDPL 
{

    namespace Pharm
    {
	
		/**
		 * \brief InteractionScoreGridSetCalculator.
		 */
		class CDPL_PHARM_API InteractionScoreGridSetCalculator
		{

		  public:
			typedef InteractionScoreGridCalculator::ScoringFunction ScoringFunction;
			typedef InteractionScoreGridCalculator::ScoreCombinationFunction ScoreCombinationFunction;

			virtual ~InteractionScoreGridSetCalculator() {}
		
			void enableInteraction(unsigned int ftr_type, unsigned int tgt_ftr_type, bool enable);

			bool isInteractionEnabled(unsigned int ftr_type, unsigned int tgt_ftr_type) const;

			void clearEnabledInteractions();

			void setScoringFunction(unsigned int ftr_type, unsigned int tgt_ftr_type, const ScoringFunction& func);

			const ScoringFunction& getScoringFunction(unsigned int ftr_type, unsigned int tgt_ftr_type) const;

			void removeScoringFunction(unsigned int ftr_type, unsigned int tgt_ftr_type);

			void setScoreCombinationFunction(const ScoreCombinationFunction& func);

			const ScoreCombinationFunction& getScoreCombinationFunction() const;

			void normalizeScores(bool normalize);

			bool scoresNormalized() const;

		  protected:
			void calculate(const FeatureContainer& features);

		  private:
			virtual Grid::DSpatialGrid::SharedPointer createGrid(unsigned int ftr_type, unsigned int tgt_ftr_type) const = 0;

			typedef std::pair<unsigned int, unsigned int> FeatureTypePair;
			typedef std::map<FeatureTypePair, ScoringFunction> ScoringFuncMap;
			typedef std::set<FeatureTypePair> EnabledInteractionsMap;
		
			ScoringFuncMap                  scoringFuncMap;
			EnabledInteractionsMap          enabledInteractions;
            InteractionScoreGridCalculator  gridCalculator;
		};
    }
}

#endif // CDPL_PHARM_INTERACTIONSCOREGRIDSETCALCULATOR_HPP
