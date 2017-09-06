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

#include "CDPL/Pharm/PharmacophoreGenerator.hpp"


using namespace CDPL; 


void Pharm::PharmacophoreGenerator::enableFeature(unsigned int type, bool enable)
{
	if (enable)
		enabledFeatures.insert(type);
	else
		enabledFeatures.erase(type);
}

bool Pharm::PharmacophoreGenerator::isFeatureEnabled(unsigned int type) const
{
	return (enabledFeatures.find(type) != enabledFeatures.end());
}

void Pharm::PharmacophoreGenerator::clearEnabledFeatures()
{
	enabledFeatures.clear();
}

void Pharm::PharmacophoreGenerator::setFeatureGenerator(unsigned int type, const FeatureGenerator::SharedPointer& ftr_gen)
{
	featureGeneratorMap[type] = ftr_gen;
}

void Pharm::PharmacophoreGenerator::removeFeatureGenerator(unsigned int type)
{
	featureGeneratorMap.erase(type);
}

Pharm::PharmacophoreGenerator::FeatureGenerator::SharedPointer
Pharm::PharmacophoreGenerator::getFeatureGenerator(unsigned int type) const
{
	FeatureGeneratorMap::const_iterator it = featureGeneratorMap.find(type);

	return (it == featureGeneratorMap.end() ? FeatureGenerator::SharedPointer() : it->second);
}

void Pharm::PharmacophoreGenerator::generate(const Chem::MolecularGraph& molgraph, Pharmacophore& pharm)
{
	for (FeatureGeneratorMap::const_iterator it = featureGeneratorMap.begin(), end = featureGeneratorMap.end(); it != end; ++it)
		if (isFeatureEnabled(it->first) && it->second)
			it->second->generate(molgraph, pharm);
}

void Pharm::PharmacophoreGenerator::setAtom3DCoordinatesFunction(const Chem::Atom3DCoordinatesFunction& func)
{
	FeatureGenerator::setAtom3DCoordinatesFunction(func);

	for (FeatureGeneratorMap::const_iterator it = featureGeneratorMap.begin(), end = featureGeneratorMap.end(); it != end; ++it)
		it->second->setAtom3DCoordinatesFunction(func);
}
