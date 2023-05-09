/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * InteractionAnalyzer.hpp 
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
 * \brief Definition of the class CDPL::Pharm::InteractionAnalyzer.
 */

#ifndef CDPL_PHARM_INTERACTIONANALYZER_HPP
#define CDPL_PHARM_INTERACTIONANALYZER_HPP

#include <utility>
#include <map>

#include <boost/function.hpp>

#include "CDPL/Pharm/APIPrefix.hpp"
#include "CDPL/Pharm/FeatureMapping.hpp"


namespace CDPL 
{

    namespace Pharm
    {

		class FeatureContainer;
		class Feature;

		/**
		 * \brief InteractionAnalyzer.
		 */
		class CDPL_PHARM_API InteractionAnalyzer 
		{

		  public:
			/**
			 * \brief A generic wrapper class used to store feature interaction constraint test functions.
			 */
			typedef boost::function2<bool, const Feature&, const Feature&> ConstraintFunction;

			/**
			 * \brief Constructs the \c %InteractionAnalyzer instance.
			 */
			InteractionAnalyzer() {}

			/**
			 * \brief Virtual destructor.
			 */
			virtual ~InteractionAnalyzer() {}

			/**
			 * \brief Specifies a function that gets used for checking whether all constraints are actually
			 *        fulfilled for an interaction between a pair of features of the specified types.
			 * \param type1 An identifier for the type of the first feature.
			 * \param type2 An identifier for the type of the second feature.
			 * \param func The constraint check function.
			 */
			void setConstraintFunction(unsigned int type1, unsigned type2, const ConstraintFunction& func);

			/**
			 * \brief Removes the constraint check function that was registered for the specified pair of feature types.
			 * \param type1 An identifier for the type of the first feature.
			 * \param type2 An identifier for the type of the second feature.
			 */
			void removeConstraintFunction(unsigned int type1, unsigned type2);

			/**
			 * \brief Returns the constraint check function that was registered for the specified pair of feature types.
			 * \param type1 An identifier for the type of the first feature.
			 * \param type2 An identifier for the type of the second feature.
			 * \return The registered constraint check function.
			 */
			const ConstraintFunction& getConstraintFunction(unsigned int type1, unsigned type2) const;
 
			/**
			 * \brief Analyzes possible interactions of the features in feature container \a cntnr1 and with features of \a cntnr2 according
			 *        to the registered constraint functions.
			 *
			 * For every pairwise combination of the features in the first feature container \a cntnr1 with the features in the
			 * second feature container \a cntnr1 a lookup for a registered interaction constraint function using the respective feature types
			 * is performed. If no function for the corresponding type pair was registered, the pair of features is assumed to be
			 * incompatible and that no interaction between them can ever occur. Note that a function that was registered for the type pair
			 * <tt>[typeA, typeB]</tt> does not automatically get called for the reverse pair <tt>[typeB, typeA]</tt>! If, however, a function
			 * was found, it gets called with the current feature instance of the first feature container as the first argument and the feature
			 * instance of the second feature container as the second argument. If the constraint function evaluates to \c true, a corresponding
			 * mapping of the first to the second feature object is inserted in the specified output map \a iactions (be aware that a mapping
			 * of the second to the first feature is not added automatically!).
			 *
			 * \param cntnr1 The first feature container.
			 * \param cntnr2 The second feature container.
			 * \param iactions An output map that contains features of \a cntnr1 as keys and interacting features of \a cntnr2
			 *                     as values.
			 * \param append If \c false, \a iactions gets cleared before adding any feature mappings.
			 */
			void analyze(const FeatureContainer& cntnr1, const FeatureContainer& cntnr2, FeatureMapping& iactions, bool append = false) const;

		  private:
			typedef std::pair<unsigned int, unsigned int> FeatureTypePair;
			typedef std::map<FeatureTypePair, ConstraintFunction> ConstraintFunctionMap;
		
			ConstraintFunctionMap constraintFuncMap;
		};
    }
}

#endif // CDPL_PHARM_INTERACTIONANALYZER_HPP
