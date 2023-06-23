/* 
 * InteractionAnalyzer.cpp 
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


#include "StaticInit.hpp"

#include "CDPL/Pharm/InteractionAnalyzer.hpp"
#include "CDPL/Pharm/FeatureContainer.hpp"
#include "CDPL/Pharm/Feature.hpp"
#include "CDPL/Pharm/FeatureFunctions.hpp"


using namespace CDPL; 


namespace
{

    const Pharm::InteractionAnalyzer::ConstraintFunction DEF_FUNC;
}


void Pharm::InteractionAnalyzer::setConstraintFunction(unsigned int type1, unsigned int type2, const ConstraintFunction& func)
{
    constraintFuncMap[FeatureTypePair(type1, type2)] = func;
}

void Pharm::InteractionAnalyzer::removeConstraintFunction(unsigned int type1, unsigned int type2)
{
    constraintFuncMap.erase(FeatureTypePair(type1, type2));
}

const Pharm::InteractionAnalyzer::ConstraintFunction& 
Pharm::InteractionAnalyzer::getConstraintFunction(unsigned int type1, unsigned int type2) const
{
    ConstraintFunctionMap::const_iterator it = constraintFuncMap.find(FeatureTypePair(type1, type2));

    return (it == constraintFuncMap.end() ? DEF_FUNC : it->second);
}

void Pharm::InteractionAnalyzer::analyze(const FeatureContainer& cntnr1, const FeatureContainer& cntnr2, 
										 FeatureMapping& iactions, bool append) const
{
	if (!append)
		iactions.clear();
	
	ConstraintFunctionMap::const_iterator cf_map_end = constraintFuncMap.end();
	FeatureTypePair type_pair;

	for (FeatureContainer::ConstFeatureIterator it1 = cntnr1.getFeaturesBegin(), end1 = cntnr1.getFeaturesEnd(); it1 != end1; ++it1) {
		const Feature& ftr1 = *it1;
		type_pair.first = getType(ftr1);

		for (FeatureContainer::ConstFeatureIterator it2 = cntnr2.getFeaturesBegin(), end2 = cntnr2.getFeaturesEnd(); it2 != end2; ++it2) {
			const Feature& ftr2 = *it2;
			type_pair.second = getType(ftr2);

			ConstraintFunctionMap::const_iterator cf_it = constraintFuncMap.find(type_pair);

			if (cf_it == cf_map_end || !cf_it->second)
				continue;

			if (cf_it->second(ftr1, ftr2))
				iactions.insertEntry(&ftr1, &ftr2);
		}
	}
}
