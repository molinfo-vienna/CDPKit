/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * FeatureMapping.hpp 
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
 * \brief Definition of the type CDPL::Pharm::FeatureMapping.
 */

#ifndef CDPL_PHARM_FEATUREMAPPING_HPP
#define CDPL_PHARM_FEATUREMAPPING_HPP

#include "CDPL/Pharm/APIPrefix.hpp"
#include "CDPL/Util/MultiMap.hpp"


namespace CDPL 
{

	namespace Pharm
	{

		class Feature;

		/**
		 * \brief A data type for the storage and lookup of arbitrary feature to feature mappings.
		 *
		 * Features mappings are stored as pairs of pointers to the mapped \c const Pharm::Feature objects.
		 * Mappings do not have to be unique and multiple mappings of a given feature to other features are possible.
		 * If a mapping entry for a particular feature does not exist, the methods FeatureMapping::getValue()
		 * and FeatureMapping::operator[]() return a \e null pointer to indicate that the lookup of the 
		 * mapped feature has failed.
		 */
		class CDPL_PHARM_API FeatureMapping : public Util::MultiMap<const Feature*, const Feature*, true>
		{

		  public:
			typedef std::shared_ptr<FeatureMapping> SharedPointer;

		  private:
			const char* getClassName() const {
				return "FeatureMapping";
			}
		};
	}
}

#endif // CDPL_PHARM_FEATUREMAPPING_HPP
