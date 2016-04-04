/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * AromaticFeatureGenerator.cpp 
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

#include <algorithm>
#include <iterator>

#include <boost/bind.hpp>

#include "CDPL/Chem/AromaticFeatureGenerator.hpp"
#include "CDPL/Chem/MolecularGraph.hpp"
#include "CDPL/Chem/Pharmacophore.hpp"
#include "CDPL/Chem/Feature.hpp"
#include "CDPL/Chem/Atom.hpp"
#include "CDPL/Chem/Entity3DFunctions.hpp"
#include "CDPL/Chem/FeatureFunctions.hpp"
#include "CDPL/Chem/FeatureType.hpp"
#include "CDPL/Chem/FeatureGeometry.hpp"
#include "CDPL/Math/Vector.hpp"
#include "CDPL/Util/AddressOf.hpp"


using namespace CDPL; 


Chem::AromaticFeatureGenerator::AromaticFeatureGenerator(): 
	featureType(FeatureType::AROMATIC), featureGeom(FeatureGeometry::PLANE), featureTol(0.9) 
{}

Chem::AromaticFeatureGenerator::AromaticFeatureGenerator(const MolecularGraph& molgraph, Pharmacophore& pharm):
	featureType(FeatureType::AROMATIC), featureGeom(FeatureGeometry::PLANE), featureTol(0.9) 
{
    generate(molgraph, pharm);
}

Chem::AromaticFeatureGenerator::~AromaticFeatureGenerator() {}

void Chem::AromaticFeatureGenerator::setFeatureType(unsigned int type)
{
	featureType = type;
}

unsigned int Chem::AromaticFeatureGenerator::getFeatureType() const
{
	return featureType;
}

void Chem::AromaticFeatureGenerator::setFeatureGeometry(unsigned int geom)
{
	featureGeom = geom;
}

unsigned int Chem::AromaticFeatureGenerator::getFeatureGeometry() const
{
	return featureGeom;
}

void Chem::AromaticFeatureGenerator::setFeatureTolerance(double tol)
{
	featureTol = tol;
}

double Chem::AromaticFeatureGenerator::getFeatureTolerance() const
{
	return featureTol;
}

void Chem::AromaticFeatureGenerator::addNonPatternFeatures(const MolecularGraph& molgraph, Pharmacophore& pharm)
{
	aromSSSRSubset.extract(molgraph);
	ringAtomMask.resize(molgraph.getNumAtoms());

	const FragmentList::BaseType& sssr_subset = aromSSSRSubset;

	for (FragmentList::BaseType::ConstElementIterator it = sssr_subset.getElementsBegin(), end = sssr_subset.getElementsEnd(); it != end; ++it) {
		const Fragment& ring = **it;

		ringAtomMask.reset();

		std::for_each(ring.getAtomsBegin(), ring.getAtomsEnd(),
					  boost::bind(&Util::BitSet::set, boost::ref(ringAtomMask), 
								  boost::bind(&AtomContainer::getAtomIndex, &molgraph, _1), true));

		if (isContainedInExMatchList(ringAtomMask) || isContainedInIncMatchList(ringAtomMask))
			continue;

		featureAtoms.clear();

		std::transform(ring.getAtomsBegin(), ring.getAtomsEnd(), 
					   std::back_inserter(featureAtoms), Util::AddressOf<const Atom>());

		Feature& feature = pharm.addFeature();

		setType(feature, featureType);
		setTolerance(feature, featureTol);
		setGeometry(feature, featureGeom);
		setSubstructure(feature, *it);

		Math::Vector3D pos, orient;

		if (calcPlaneFeatureOrientation(featureAtoms, orient, pos)) {
			set3DCoordinates(feature, pos);
			setOrientation(feature, orient);
		}
	} 
}
