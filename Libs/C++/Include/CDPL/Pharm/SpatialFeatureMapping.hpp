/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * SpatialFeatureMappingExtractor.hpp 
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
 * \brief Definition of the class CDPL::Pharm::SpatialFeatureMapping.
 */

#ifndef CDPL_PHARM_SPATIALFEATUREMAPPING_HPP
#define CDPL_PHARM_SPATIALFEATUREMAPPING_HPP

#include <utility>
#include <unordered_map>

#include <boost/function.hpp>
#include <boost/functional/hash.hpp>

#include "CDPL/Pharm/APIPrefix.hpp"
#include "CDPL/Pharm/FeatureMapping.hpp"
#include "CDPL/Math/Matrix.hpp"


namespace CDPL 
{

    namespace Pharm
    {

		class FeatureContainer;

		/**
		 * \brief SpatialFeatureMapping.
		 */
		class CDPL_PHARM_API SpatialFeatureMapping : public FeatureMapping
		{

		  public:
			/**
			 * \brief A generic wrapper class used to store a user-defined feature type match function.
			 */
			typedef boost::function2<bool, const Feature&, const Feature&> TypeMatchFunction;

			/**
			 * \brief A generic wrapper class used to store a user-defined feature position match function.
			 */
			typedef boost::function3<double, const Feature&, const Feature&, const Math::Matrix4D&> PositionMatchFunction;

			/**
			 * \brief A generic wrapper class used to store a user-defined feature geometry match function.
			 */
			typedef boost::function3<double, const Feature&, const Feature&, const Math::Matrix4D&> GeometryMatchFunction;

			/**
			 * \brief Constructs a \c %SpatialFeatureMapping instance.
			 * \param query_mode If \c true, the reference feature container is interpreted as a query feature container and some of the
			 *                   set default functions will operate in a special query mode.
			 */
			SpatialFeatureMapping(bool query_mode = false);
			
			/**
			 * \brief Specifies a function for testing the type compatibility of features.
			 * \param func The type compatibility test function.
			 */
			void setTypeMatchFunction(const TypeMatchFunction& func);

			/**
			 * \brief Returns the function that was registered for testing the type compatibility of the features.
			 * \return The registered type compatibility test function.
			 */
			const TypeMatchFunction& getTypeMatchFunction() const;

			/**
			 * \brief Specifies a function for checking the proximity of mapped feature positions.
			 * \param func The position proximity test function.
			 */
			void setPositionMatchFunction(const PositionMatchFunction& func);

			/**
			 * \brief Returns the function that was registered for checking the proximity of mapped feature positions.
			 * \return The registered position proximity test function.
			 */
			const PositionMatchFunction& getPositionMatchFunction() const;

			/**
			 * \brief Specifies a function for checking the match of mapped feature geometries.
			 * \param func The feature geometry match test function.
			 */
			void setGeometryMatchFunction(const GeometryMatchFunction& func);

			/**
			 * \brief Returns the function that was registered for checking the match of mapped feature geometries.
			 * \return The registered geometry match test function.
			 */
			const GeometryMatchFunction& getGeometryMatchFunction() const;

			double getPositionMatchScore(const Feature& ref_ftr, const Feature& aligned_ftr) const;

			double getGeometryMatchScore(const Feature& ref_ftr, const Feature& aligned_ftr) const;

			void perceive(const FeatureContainer& ref_ftrs, const FeatureContainer& aligned_ftrs, const Math::Matrix4D& xform);

		  private:
            typedef std::pair<const Feature*, const Feature*> FeaturePair;
            typedef std::unordered_map<FeaturePair, double, boost::hash<FeaturePair> > FeaturePairToScoreMap;

			TypeMatchFunction     typeMatchFunc;
			PositionMatchFunction posMatchFunc;
			GeometryMatchFunction geomMatchFunc;
			FeaturePairToScoreMap posMatchScores;
			FeaturePairToScoreMap geomMatchScores;
		};
    }
}

#endif // CDPL_PHARM_SPATIALFEATUREMAPPING_HPP
