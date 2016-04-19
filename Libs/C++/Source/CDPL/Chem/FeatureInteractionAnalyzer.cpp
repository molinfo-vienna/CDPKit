/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * FeatureInteractionAnalyzer.cpp 
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


#include "StaticInit.hpp"

#include "CDPL/Chem/FeatureInteractionAnalyzer.hpp"
#include "CDPL/Chem/Pharmacophore.hpp"
#include "CDPL/Chem/Feature.hpp"
#include "CDPL/Chem/FeatureFunctions.hpp"


using namespace CDPL; 


void Chem::FeatureInteractionAnalyzer::setConstraintFunction(unsigned int type1, unsigned int type2, const ConstraintFunction& func)
{
    ConstraintFunctionMap::iterator it = constraintFuncMap.find(std::make_pair(type1, type2));

    if (it == constraintFuncMap.end())
		constraintFuncMap.insert(ConstraintFunctionMap::value_type(std::make_pair(type1, type2), func));
    else
		it->second = func;
}

void Chem::FeatureInteractionAnalyzer::removeConstraintFunction(unsigned int type1, unsigned int type2)
{
    constraintFuncMap.erase(std::make_pair(type1, type2));
}

const Chem::FeatureInteractionAnalyzer::ConstraintFunction& 
Chem::FeatureInteractionAnalyzer::getConstraintFunction(unsigned int type1, unsigned int type2) const
{
    static const ConstraintFunction DEF_FUNC;

    ConstraintFunctionMap::const_iterator it = constraintFuncMap.find(std::make_pair(type1, type2));

    return (it == constraintFuncMap.end() ? DEF_FUNC : it->second);
}

void Chem::FeatureInteractionAnalyzer::analyze(const Pharmacophore& pharm1, const Pharmacophore& pharm2, FeatureMapping& interactions) const
{
	ConstraintFunctionMap::const_iterator cf_map_end = constraintFuncMap.end();
	std::pair<unsigned int, unsigned int> type_pair;

	for (Pharmacophore::ConstFeatureIterator it1 = pharm1.getFeaturesBegin(), end1 = pharm1.getFeaturesEnd(); it1 != end1; ++it1) {
		const Feature& ftr1 = *it1;
		type_pair.first = getType(ftr1);

		for (Pharmacophore::ConstFeatureIterator it2 = pharm2.getFeaturesBegin(), end2 = pharm2.getFeaturesEnd(); it2 != end2; ++it2) {
			const Feature& ftr2 = *it2;
			type_pair.second = getType(ftr2);

			ConstraintFunctionMap::const_iterator cf_it = constraintFuncMap.find(type_pair);

			if (cf_it == cf_map_end)
				continue;

			if (cf_it->second(ftr1, ftr2))
				interactions.insertEntry(&ftr1, &ftr2);
		}
	}
}
