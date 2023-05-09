/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * NPointPharmacophoreGeneratorBase.hpp 
 *
 * This file is part of the Pharmical Data Processing Toolkit
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


#ifndef CDPL_PHARM_NPOINTPHARMACOPHOREGENERATORBASE_HPP
#define CDPL_PHARM_NPOINTPHARMACOPHOREGENERATORBASE_HPP

#include <vector>
#include <utility>
#include <algorithm>

#include <CDPL/Pharm/FeatureFunctions.hpp>


namespace CDPL 
{

    namespace Pharm
    {

		class NPointPharmacophoreGeneratorBase
		{

		public:
			typedef std::pair<const Feature*, unsigned int> FeatureAndType;
			typedef std::vector<FeatureAndType> FeatureAndTypeArray;

			template <typename Iter> 
			const FeatureAndTypeArray& getCanonOrderedFeatures(const Iter& beg, const Iter& end);

		private:
			struct FeatureAndTypeCmpFunc
			{

				inline bool operator()(const FeatureAndType& ft1, const FeatureAndType& ft2) const {
					return (ft1.second < ft2.second);
				}
			};

			FeatureAndTypeArray features;
		};
    }
}


// Implementation

template <typename Iter> 
const CDPL::Pharm::NPointPharmacophoreGeneratorBase::FeatureAndTypeArray& 
CDPL::Pharm::NPointPharmacophoreGeneratorBase::getCanonOrderedFeatures(const Iter& beg, const Iter& end)
{
	features.clear();

	for (Iter it = beg; it != end; ++it) {
		const Feature& ftr = *it;

		features.push_back(FeatureAndType(&ftr, getType(ftr)));
	}

	std::sort(features.begin(), features.end(), FeatureAndTypeCmpFunc());

	return features;
}

#endif // CDPL_PHARM_NPOINTPHARMACOPHOREGENERATORBASE_HPP
