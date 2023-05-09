/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

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
 * \brief Definition of the class CDPL::Shape::ScreeningSettings.
 */

#ifndef CDPL_SHAPE_SCREENINGSETTINGS_HPP
#define CDPL_SHAPE_SCREENINGSETTINGS_HPP

#include <cstddef>

#include <boost/function.hpp>

#include "CDPL/Shape/APIPrefix.hpp"


namespace CDPL 
{

    namespace Shape
    {

		class AlignmentResult;

		class CDPL_SHAPE_API ScreeningSettings
		{

		  public:
			static const ScreeningSettings DEFAULT;
			static const double            NO_CUTOFF;

			typedef boost::function1<double, const AlignmentResult&> ScoringFunction;

			enum ScreeningMode
			{

			    BEST_OVERALL_MATCH,
				BEST_MATCH_PER_QUERY,
				BEST_MATCH_PER_QUERY_CONF
			};

			enum ColorFeatureType
			{

			    NO_FEATURES,
				PHARMACOPHORE_EXP_CHARGES,
				PHARMACOPHORE_IMP_CHARGES
			};

			enum AlignmentMode
			{
			
	    		NO_ALIGNMENT          = 0x0,
			    SHAPE_CENTROID        = 0x1,
				ATOM_CENTERS          = 0x2,
				COLOR_FEATURE_CENTERS = 0x4,
				RANDOM                = 0x8
			};

			ScreeningSettings();
		
			void setScoringFunction(const ScoringFunction& func);

			const ScoringFunction& getScoringFunction() const;

			void setColorFeatureType(ColorFeatureType type);

			ColorFeatureType getColorFeatureType() const;

			void setScreeningMode(ScreeningMode mode);

			ScreeningMode getScreeningMode() const;

			void setAlignmentMode(AlignmentMode mode);

			AlignmentMode getAlignmentMode() const;

			void setNumRandomStarts(std::size_t num_starts);

			std::size_t getNumRandomStarts() const;

			void allCarbonMode(bool all_c);

			bool allCarbonMode() const;

			void singleConformerSearch(bool single_conf);

			bool singleConformerSearch() const;

			void optimizeOverlap(bool optimize);

			bool optimizeOverlap() const;

			void greedyOptimization(bool greedy);

			bool greedyOptimization() const;

			void setMaxNumOptimizationIterations(std::size_t max_iter);

			std::size_t getMaxNumOptimizationIterations() const;

			void setOptimizationStopGradient(double grad_norm);

			double getOptimizationStopGradient() const;
		
			void setScoreCutoff(double cutoff);

			double getScoreCutoff() const;

		  private:
			ScoringFunction   scoringFunc;
			ColorFeatureType  colorFtrType;
			ScreeningMode     screeningMode;
			AlignmentMode     almntMode;
			std::size_t       numRandomStarts;
			bool              allCarbon;
			bool              singleConfSearch;
			bool              optOverlap;
			bool              greedyOpt;
			std::size_t       numOptIter;
			double            optStopGrad;
			double            scoreCutoff;
		};
    }
}

#endif // CDPL_SHAPE_SCREENINGSETTINGS_HPP
