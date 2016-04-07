/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * PharmacophoreGenerator.cpp 
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

#include "CDPL/Chem/PharmacophoreGenerator.hpp"


using namespace CDPL; 


void Chem::PharmacophoreGenerator::enableFeature(unsigned int type, bool enable)
{
	if (enable)
		enabledFeatures.insert(type);
	else
		enabledFeatures.erase(type);
}

bool Chem::PharmacophoreGenerator::isFeatureEnabled(unsigned int type) const
{
	return (enabledFeatures.find(type) != enabledFeatures.end());
}

void Chem::PharmacophoreGenerator::clearEnabledFeatures()
{
	enabledFeatures.clear();
}

void Chem::PharmacophoreGenerator::setFeatureFunction(unsigned int type, const FeatureFunction& func)
{
	FeatureFunctionMap::iterator it = featureFuncMap.find(type);

	if (it == featureFuncMap.end())
		featureFuncMap.insert(FeatureFunctionMap::value_type(type, func));
	else
		it->second = func;
}

const Chem::PharmacophoreGenerator::FeatureFunction& 
Chem::PharmacophoreGenerator::getFeatureFunction(unsigned int type) const
{
	static const FeatureFunction DEF_FUNC;

	FeatureFunctionMap::const_iterator it = featureFuncMap.find(type);

	return (it == featureFuncMap.end() ? DEF_FUNC : it->second);
}

void Chem::PharmacophoreGenerator::generate(const MolecularGraph& molgraph, Pharmacophore& pharm)
{
	for (FeatureFunctionMap::const_iterator it = featureFuncMap.begin(), end = featureFuncMap.end(); it != end; ++it)
		if (isFeatureEnabled(it->first))
			it->second(molgraph, pharm);
}
