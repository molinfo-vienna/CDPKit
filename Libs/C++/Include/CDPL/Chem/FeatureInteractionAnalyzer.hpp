/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * FeatureInteractionAnalyzer.hpp 
 *
 * This file is part of the Chemical Data Processing Toolkit
 *
 * Copyright (C) 2003-2010 Thomas A. Seidel <thomas.seidel@univie.ac.at>
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
 * \brief Definition of the class CDPL::Chem::FeatureInteractionAnalyzer.
 */

#ifndef CDPL_CHEM_FEATUREINTERACTIONANALYZER_HPP
#define CDPL_CHEM_FEATUREINTERACTIONANALYZER_HPP

#include <utility>

#include <boost/function.hpp>
#include <boost/unordered_map.hpp>

#include "CDPL/Chem/APIPrefix.hpp"
#include "CDPL/Chem/FeatureMapping.hpp"


namespace CDPL 
{

    namespace Chem
    {

		class Pharmacophore;
		class Feature;

		/**
		 * \addtogroup CDPL_CHEM_INTERACTION_PERCEPTION
		 * @{
		 */

		/**
		 * \brief FeatureInteractionAnalyzer.
		 */
		class CDPL_CHEM_API FeatureInteractionAnalyzer 
		{

		  public:
			/**
			 * \brief A generic wrapper class used to store feature interaction constraint test functions.
			 */
			typedef boost::function2<bool, const Feature&, const Feature&> ConstraintFunction;

			/**
			 * \brief Constructs the \c %FeatureInteractionAnalyzer instance.
			 */
			FeatureInteractionAnalyzer() {}

			/**
			 * \brief Virtual destructor.
			 */
			virtual ~FeatureInteractionAnalyzer() {}

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
			 * \brief Analyzes possible interactions of the features in pharmacophore \a pharm1 and with features of \a pharm2 according
			 *        to the registered constraint functions.
			 *
			 * For every pairwise combination of the features in the first pharmacophore \a pharm1 with the features in the
			 * second pharmacophore \a pharm1 a lookup for a registered interaction constraint function using the respective feature types
			 * is performed. If no function for the corresponding type pair was registered, the pair of features is assumed to be
			 * incompatible and that no interaction between them can ever occur. Note that a function that was registered for the type pair
			 * <tt>[typeA, typeB]</tt> does not automatically get called for the reverse pair <tt>[typeB, typeA]</tt>! If, however, a function
			 * was found, it gets called with the current feature instance of the first pharmacophore as the first argument and the feature
			 * instance of the second pharmacophore as the second argument. If the constraint function evaluates to \c true, a corresponding
			 * mapping of the first to the second feature object is inserted in the specified output map \a interactions (be aware that a mapping
			 * of the second to the first feature is not added automatically!).
			 *
			 * \param pharm1 The first pharmacophore.
			 * \param pharm2 The second pharmacophore.
			 * \param interactions An output map that contains features of \a pharm1 as keys and interacting features of \a pharm2
			 *                     as values.
			 */
			void analyze(const Pharmacophore& pharm1, const Pharmacophore& pharm2, FeatureMapping& interactions) const;

		  private:
			/** \cond CDPL_PRIVATE_SECTION_DOC */
		
			typedef boost::unordered_multimap<std::pair<unsigned int, unsigned int>, ConstraintFunction> ConstraintFunctionMap;
		
			ConstraintFunctionMap constraintFuncMap;

			/** \endcond */
		};

		/**
		 * @}
		 */
    }
}

#endif // CDPL_CHEM_FEATUREINTERACTIONANALYZER_HPP
