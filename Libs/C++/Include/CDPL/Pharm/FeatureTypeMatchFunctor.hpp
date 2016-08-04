/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * FeatureTypeMatchFunctor.hpp 
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
 * \brief Definition of the class CDPL::Pharm::FeatureTypeMatchFunctor.
 */

#ifndef CDPL_PHARM_FEATURETYPEMATCHFUNCTOR_HPP
#define CDPL_PHARM_FEATURETYPEMATCHFUNCTOR_HPP

#include <functional>

#include "CDPL/Pharm/APIPrefix.hpp"


namespace CDPL 
{

    namespace Pharm
    {

		class Feature;

		/**
		 * \addtogroup CDPL_PHARM_ALIGNMENT
		 * @{
		 */

		/**
		 * \brief FeatureTypeMatchFunctor.
		 */
		class CDPL_PHARM_API FeatureTypeMatchFunctor : public std::binary_function<Feature, Feature, bool>
		{

		  public:
			/**
			 * \brief Checks if \a ftr1 and \a ftr2 have the same feature type.
			 * \param ftr1 The first feature.
			 * \param ftr2 The second feature.
			 * \return \c true if the feature types are equal, and \c false otherwise.
			 * \see Pharm::getType(const Feature&)
			 */
			bool operator()(const Feature& ftr1, const Feature& ftr2) const;
		};

		/**
		 * @}
		 */
    }
}

#endif // CDPL_PHARM_FEATURETYPEMATCHFUNCTOR_HPP
