/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * HydrophobicAtomFeatureGenerator.cpp 
 *
 * This file is part of the Chemical Data Processing Toolkit
 *
 * Copyright (C) 2003-2020 Thomas A. Seidel <thomas.seidel@univie.ac.at>
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

#include <cstddef>

#include "CDPL/Pharm/HydrophobicAtomFeatureGenerator.hpp"
#include "CDPL/Pharm/Feature.hpp"
#include "CDPL/Pharm/Pharmacophore.hpp"
#include "CDPL/Pharm/FeatureFunctions.hpp"
#include "CDPL/Chem/Atom.hpp"
#include "CDPL/Chem/Entity3DFunctions.hpp"
#include "CDPL/Chem/AtomFunctions.hpp"
#include "CDPL/MolProp/AtomFunctions.hpp"
#include "CDPL/Base/Exceptions.hpp"


using namespace CDPL; 


const double       Pharm::HydrophobicAtomFeatureGenerator::DEF_FEATURE_TOL         = 1.5;
const double       Pharm::HydrophobicAtomFeatureGenerator::DEF_HYD_THRESHOLD       = 0.5;
const unsigned int Pharm::HydrophobicAtomFeatureGenerator::DEF_FEATURE_TYPE;
const unsigned int Pharm::HydrophobicAtomFeatureGenerator::DEF_FEATURE_GEOM;


Pharm::HydrophobicAtomFeatureGenerator::HydrophobicAtomFeatureGenerator():
	featureType(DEF_FEATURE_TYPE),  featureTol(DEF_FEATURE_TOL), featureGeom(DEF_FEATURE_GEOM),
	hydThreshold(DEF_HYD_THRESHOLD)
{}

Pharm::HydrophobicAtomFeatureGenerator::HydrophobicAtomFeatureGenerator(const HydrophobicAtomFeatureGenerator& gen):
	PatternBasedFeatureGenerator(gen), featureType(gen.featureType), featureTol(gen.featureTol), 
	featureGeom(gen.featureGeom), hydThreshold(gen.hydThreshold)
{}

Pharm::HydrophobicAtomFeatureGenerator::HydrophobicAtomFeatureGenerator(const Chem::MolecularGraph& molgraph, Pharmacophore& pharm):
	featureType(DEF_FEATURE_TYPE),  featureTol(DEF_FEATURE_TOL), featureGeom(DEF_FEATURE_GEOM),
	hydThreshold(DEF_HYD_THRESHOLD)
{
    generate(molgraph, pharm);
}

Pharm::HydrophobicAtomFeatureGenerator::~HydrophobicAtomFeatureGenerator() {}

void Pharm::HydrophobicAtomFeatureGenerator::setFeatureType(unsigned int type)
{
	featureType = type;
}

unsigned int Pharm::HydrophobicAtomFeatureGenerator::getFeatureType() const
{
	return featureType;
}

void Pharm::HydrophobicAtomFeatureGenerator::setFeatureTolerance(double tol)
{
	featureTol = tol;
}

double Pharm::HydrophobicAtomFeatureGenerator::getFeatureTolerance() const
{
	return featureTol;
}

void Pharm::HydrophobicAtomFeatureGenerator::setFeatureGeometry(unsigned int geom)
{
	featureGeom = geom;
}

unsigned int Pharm::HydrophobicAtomFeatureGenerator::getFeatureGeometry() const
{
	return featureGeom;
}

void Pharm::HydrophobicAtomFeatureGenerator::setHydrophobicityThreshold(double thresh)
{
	hydThreshold = thresh;
}

double Pharm::HydrophobicAtomFeatureGenerator::getHydrophobicityThreshold() const
{
	return hydThreshold;
}

Pharm::HydrophobicAtomFeatureGenerator& Pharm::HydrophobicAtomFeatureGenerator::operator=(const HydrophobicAtomFeatureGenerator& gen)
{
	if (this == &gen)
		return *this;

	FeatureGenerator::operator=(gen);

	featureType = gen.featureType; 
	featureTol = gen.featureTol; 
	featureGeom = gen.featureGeom;
	hydThreshold = gen.hydThreshold;

	return *this;
}

Pharm::FeatureGenerator::SharedPointer Pharm::HydrophobicAtomFeatureGenerator::clone() const
{
	return FeatureGenerator::SharedPointer(new HydrophobicAtomFeatureGenerator(*this));
}

void Pharm::HydrophobicAtomFeatureGenerator::addNonPatternFeatures(const Chem::MolecularGraph& molgraph, Pharmacophore& pharm)
{
	using namespace Chem;

	for (MolecularGraph::ConstAtomIterator it = molgraph.getAtomsBegin(), end = molgraph.getAtomsEnd(); it != end; ++it) {
		const Atom& atom = *it;
		double hyd = MolProp::getHydrophobicity(atom);
		
		if (hyd < hydThreshold)
			continue;

		emitFeature(atom, pharm, makeFragment(atom), hyd);
	}
}

void Pharm::HydrophobicAtomFeatureGenerator::emitFeature(const Chem::Atom& atom, Pharmacophore& pharm, 
														 const Chem::Fragment::SharedPointer& substruct, 
														 double hyd) const
{
	Feature& feature = pharm.addFeature();

	setType(feature, featureType);
	setTolerance(feature, featureTol);
	setGeometry(feature, featureGeom);
	setSubstructure(feature, substruct);
	setHydrophobicity(feature, hyd);

	const Chem::Atom3DCoordinatesFunction& coords_func = getAtom3DCoordinatesFunction();

	if (coords_func.empty())
		return;

	try {
		set3DCoordinates(feature, coords_func(atom));
	} catch (const Base::ItemNotFound& e) {
	} catch (...) {
		throw;
	}
}

Chem::Fragment::SharedPointer Pharm::HydrophobicAtomFeatureGenerator::makeFragment(const Chem::Atom& atom) const
{
	using namespace Chem;

	Fragment::SharedPointer frag(new Fragment());

	frag->addAtom(atom);

	return frag;
}
