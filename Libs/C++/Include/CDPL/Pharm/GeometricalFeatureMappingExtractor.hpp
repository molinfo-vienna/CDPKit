/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * GeometricalFeatureMappingExtractor.hpp 
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
 * \brief Definition of the class CDPL::Pharm::GeometricalFeatureMappingExtractor.
 */

#ifndef CDPL_PHARM_GEOMETRICALFEATUREMAPPINGEXTRACTOR_HPP
#define CDPL_PHARM_GEOMETRICALFEATUREMAPPINGEXTRACTOR_HPP

#include <boost/function.hpp>

#include "CDPL/Pharm/APIPrefix.hpp"
#include "CDPL/Pharm/FeatureMapping.hpp"
#include "CDPL/Math/Matrix.hpp"


namespace CDPL 
{

    namespace Pharm
    {

		class Pharmacophore;

		/**
		 * \addtogroup CDPL_PHARM_ALIGNMENT
		 * @{
		 */

		/**
		 * \brief GeometricalFeatureMappingExtractor.
		 */
		class CDPL_PHARM_API GeometricalFeatureMappingExtractor
		{

		  public:
			/**
			 * \brief A generic wrapper class used to store a user-defined feature type match function.
			 */
			typedef boost::function2<bool, const Feature&, const Feature&> FeatureTypeMatchFunction;

			/**
			 * \brief A generic wrapper class used to store a user-defined feature position match function.
			 */
			typedef boost::function3<bool, const Feature&, const Feature&, Math::Matrix4D&> FeaturePositionMatchFunction;

			/**
			 * \brief A generic wrapper class used to store a user-defined feature geometry match function.
			 */
			typedef boost::function3<bool, const Feature&, const Feature&, Math::Matrix4D&> FeatureGeometryMatchFunction;

			/**
			 * \brief Constructs a \c %GeometricalFeatureMappingExtractor instance.
			 * \param query_mode If \c true, the reference pharmacophore is interpreted as a query pharmacophore and some of the
			 *                   set default functions will operate in a special query mode.
			 */
			GeometricalFeatureMappingExtractor(bool query_mode = false);
			
			/**
			 * \brief Specifies a function for testing the type compatibility of features.
			 * \param func The type compatibility test function.
			 */
			void setFeatureTypeMatchFunction(const FeatureTypeMatchFunction& func);

			/**
			 * \brief Returns the function that was registered for testing the type compatibility of the features.
			 * \return The registered type compatibility test function.
			 */
			const FeatureTypeMatchFunction& getFeatureTypeMatchFunction() const;

			/**
			 * \brief Specifies a function for checking the acceptance of mapped feature position deviations.
			 * \param func The position deviation acceptance test function.
			 */
			void setFeaturePositionMatchFunction(const FeaturePositionMatchFunction& func);

			/**
			 * \brief Returns the function that was registered for checking the acceptance of mapped feature position deviations.
			 * \return The registered position deviation acceptance test function.
			 */
			const FeaturePositionMatchFunction& getFeaturePositionMatchFunction() const;

			/**
			 * \brief Specifies a function for checking allowed geometrical deviation constraints on the mapped features.
			 * \param func The geometrical deviation constraint test function.
			 */
			void setFeatureGeometryMatchFunction(const FeatureGeometryMatchFunction& func);

			/**
			 * \brief Returns the function that was registered for checking allowed geometrical deviation constraints on the mapped features.
			 * \return The registered geometrical deviation constraint test function.
			 */
			const FeatureGeometryMatchFunction& getFeatureGeometryMatchFunction() const;

			void getMapping(const Pharmacophore& ref_pharm, const Pharmacophore& pharm, Math::Matrix4D& xform, FeatureMapping& mapping) const;

		  private:
			FeatureTypeMatchFunction     typeMatchFunc;
			FeaturePositionMatchFunction posMatchFunc;
			FeatureGeometryMatchFunction geomMatchFunc;
		};

		/**
		 * @}
		 */
    }
}

#endif // CDPL_PHARM_GEOMETRICALFEATUREMAPPINGEXTRACTOR_HPP
