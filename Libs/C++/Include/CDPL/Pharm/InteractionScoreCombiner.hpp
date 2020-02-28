/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * InteractionScoreCombiner.hpp 
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
 * \brief Definition of the class CDPL::Pharm::InteractionScoreCombiner.
 */

#ifndef CDPL_PHARM_INTERACTIONSCORECOMBINER_HPP
#define CDPL_PHARM_INTERACTIONSCORECOMBINER_HPP

#include <functional>

#include <boost/function.hpp>

#include "CDPL/Pharm/APIPrefix.hpp"
#include "CDPL/Math/Vector.hpp"


namespace CDPL 
{

    namespace Pharm
    {

		class Feature;

		/**
		 * \addtogroup CDPL_PHARM_FUNCTORS
		 * @{
		 */

		/**
		 * \brief InteractionScoreCombiner.
		 */
		class CDPL_PHARM_API InteractionScoreCombiner : public std::binary_function<Math::Vector3D, Feature, double>
		{

		  public:
			/**
			 * \brief A generic wrapper class used to store interaction scoring functions.
			 */
			typedef boost::function2<double, const Math::Vector3D&, const Feature&> ScoringFunction;

			typedef boost::function2<double, double, double> CombinationFunction;

			/**
			 * \brief Constructs a \c %InteractionScoreCombiner that combines the score values calculated by two scoring functions.
			 * \param func1 The first interaction scoring function.
			 * \param func2 The second interaction scoring function.
			 * \param comb_func The function calculating the final score value.
			 */
            InteractionScoreCombiner(const ScoringFunction& func1, const ScoringFunction& func2, const CombinationFunction& comb_func);

            InteractionScoreCombiner(const ScoringFunction& func1, const ScoringFunction& func2);

			double operator()(const Math::Vector3D& ftr1, const Feature& ftr2) const;

		  private:
			ScoringFunction     scoringFunc1;
			ScoringFunction     scoringFunc2;
			CombinationFunction combFunc;
		};

		/**
		 * @}
		 */
    }
}

#endif // CDPL_PHARM_INTERACTIONSCORECOMBINER_HPP
