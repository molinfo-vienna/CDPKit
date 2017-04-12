/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * HydrophobicFeatureGenerator.cpp 
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
#include <cmath>

#include <boost/bind.hpp>
#include <boost/thread.hpp>

#include "CDPL/Pharm/HydrophobicFeatureGenerator.hpp"
#include "CDPL/Pharm/Feature.hpp"
#include "CDPL/Pharm/Pharmacophore.hpp"
#include "CDPL/Pharm/FeatureFunctions.hpp"
#include "CDPL/Chem/Atom.hpp"
#include "CDPL/Chem/Bond.hpp"
#include "CDPL/Chem/AtomContainerFunctions.hpp"
#include "CDPL/Chem/MolecularGraphFunctions.hpp"
#include "CDPL/Chem/AtomFunctions.hpp"
#include "CDPL/Chem/Entity3DFunctions.hpp"
#include "CDPL/Chem/UtilityFunctions.hpp"
#include "CDPL/Chem/AtomType.hpp"
#include "CDPL/Chem/AtomDictionary.hpp"
#include "CDPL/Chem/AtomBondMapping.hpp"
#include "CDPL/Math/Matrix.hpp"
#include "CDPL/Internal/AddressOf.hpp"


using namespace CDPL; 


namespace
{

	const double spherePoints[] = { 
	    -0.3090169944, -0.5,
		0.8090169944, -0.5877852523, -0.4253254042, 0.6881909602,
		-0.4253254042, -0.6881909602, 0.5877852523, 0.3090169944, 0.5,
		-0.8090169944, 0.4253254042, 0.6881909602, -0.5877852523,
		0.1606220356, 0.7020464448, -0.6937804776, 0.259891913,
		-0.8626684804, 0.4338885646, 0, -0.9619383578, 0.2732665289, 0,
		-0.8506508084, 0.5257311121, -0.5257311121, 0.8506508084, 0,
		-0.2628655561, 0.9510565163, 0.1624598481, -0.5, 0.8090169944,
		0.3090169944, -0.8090169944, 0.3090169944, -0.5, -0.8626684804,
		0.4338885646, -0.259891913, -0.6881909602, 0.5877852523,
		-0.4253254042, -0.4253254042, 0.6881909602, 0.5877852523,
		-0.259891913, 0.8626684804, 0.4338885646, -0.4338885646,
		0.259891913, 0.8626684804, -0.2732665289, 0, 0.9619383578,
		-0.1624598481, 0.2628655561, 0.9510565163, 1, 0, 0, 0.9619383578,
		-0.2732665289, 0, 0.9510565163, -0.1624598481, 0.2628655561, -1,
		0, 0, -0.9619383578, -0.2732665289, 0, -0.9510565163,
		-0.1624598481, -0.2628655561, -0.9510565163, 0.1624598481,
		0.2628655561, -0.8626684804, 0.4338885646, 0.259891913,
		-0.8090169944, 0.3090169944, 0.5, 0.5257311121, 0, 0.8506508084,
		0.6937804776, -0.1606220356, 0.7020464448, 0.4338885646,
		-0.259891913, 0.8626684804, 0.2732665289, 0, 0.9619383578,
		0.5257311121, 0, -0.8506508084, 0.2732665289, 0, -0.9619383578,
		0.4338885646, -0.259891913, -0.8626684804, -0.4338885646,
		-0.259891913, -0.8626684804, -0.5877852523, -0.4253254042,
		-0.6881909602, -0.3090169944, -0.5, -0.8090169944, 0.2628655561,
		-0.9510565163, 0.1624598481, 0.2628655561, -0.9510565163,
		-0.1624598481, 0.5257311121, -0.8506508084, 0, 0, -0.9619383578,
		-0.2732665289, 0, -1, 0, 0.1624598481, -0.2628655561,
		0.9510565163, 0.6881909602, 0.5877852523, 0.4253254042,
		0.8626684804, 0.4338885646, 0.259891913, 0.7020464448, 0.6937804776,
		0.1606220356, -0.6881909602, -0.5877852523, 0.4253254042, -0.5,
		-0.8090169944, -0.3090169944, -0.7020464448, -0.6937804776,
		-0.1606220356, -0.5257311121, -0.8506508084, 0, -0.5257311121, 0,
		0.8506508084, 0.3090169944, 0.5, 0.8090169944, 0, 0.5257311121,
		0.8506508084, 0.1606220356, 0.7020464448, 0.6937804776,
		0.8090169944, 0.3090169944, -0.5, 0.9510565163, 0.1624598481,
		-0.2628655561, 0.8506508084, 0, -0.5257311121, -0.2628655561,
		0.9510565163, -0.1624598481, 0, 1, 0, 0.2628655561, 0.9510565163,
		0.1624598481, 0, 0.9619383578, 0.2732665289, -0.9510565163,
		0.1624598481, -0.2628655561, 0, 0, 1, -0.1624598481,
		-0.2628655561, 0.9510565163, -0.4338885646, -0.259891913,
		0.8626684804, 0.5, -0.8090169944, -0.3090169944, 0.8506508084,
		-0.5257311121, 0, 0.7020464448, -0.6937804776, -0.1606220356,
		0.7020464448, -0.6937804776, 0.1606220356, 0.259891913,
		0.8626684804, -0.4338885646, 0.259891913, -0.8626684804,
		-0.4338885646, 0.1606220356, -0.7020464448, -0.6937804776, 0,
		-0.8506508084, -0.5257311121, 0.1624598481, -0.2628655561,
		-0.9510565163, 0, -0.5257311121, -0.8506508084, 0.3090169944, -0.5,
		-0.8090169944, -0.3090169944, 0.5, -0.8090169944, -0.5877852523,
		0.4253254042, -0.6881909602, -0.4253254042, 0.6881909602,
		-0.5877852523, 0.8090169944, -0.3090169944, -0.5, 0.6937804776,
		-0.1606220356, -0.7020464448, 0.8506508084, 0, 0.5257311121,
		0.9510565163, 0.1624598481, 0.2628655561, -0.8506508084,
		0.5257311121, 0, -0.7020464448, 0.6937804776, 0.1606220356,
		0.7020464448, 0.6937804776, -0.1606220356, 0.5257311121,
		0.8506508084, 0, 0.5, 0.8090169944, -0.3090169944, 0.2628655561,
		0.9510565163, -0.1624598481, -0.6937804776, 0.1606220356,
		-0.7020464448, -0.6937804776, -0.1606220356, -0.7020464448,
		-0.5257311121, 0, -0.8506508084, -0.259891913, -0.8626684804,
		0.4338885646, -0.1606220356, -0.7020464448, 0.6937804776,
		0.9619383578, 0.2732665289, 0, -0.6937804776, 0.1606220356,
		0.7020464448, -0.5877852523, 0.4253254042, 0.6881909602,
		-0.8506508084, 0, 0.5257311121, -0.8090169944, -0.3090169944, -0.5,
		-0.6881909602, -0.5877852523, -0.4253254042, 0.1624598481,
		0.2628655561, 0.9510565163, -0.5, -0.8090169944, 0.3090169944,
		-0.2628655561, -0.9510565163, 0.1624598481, -0.8506508084,
		-0.5257311121, 0, -0.8626684804, -0.4338885646, -0.259891913,
		0.8626684804, -0.4338885646, -0.259891913, 0, 0, -1, 0.1624598481,
		0.2628655561, -0.9510565163, -0.1624598481, 0.2628655561,
		-0.9510565163, -0.8090169944, -0.3090169944, 0.5, -0.6937804776,
		-0.1606220356, 0.7020464448, 0.6881909602, -0.5877852523,
		-0.4253254042, 0.5877852523, 0.4253254042, 0.6881909602,
		0.4338885646, 0.259891913, 0.8626684804, -0.9510565163,
		-0.1624598481, 0.2628655561, -0.8626684804, -0.4338885646,
		0.259891913, -0.1606220356, -0.7020464448, -0.6937804776,
		0.259891913, 0.8626684804, 0.4338885646, 0, 0.8506508084,
		0.5257311121, 0.4253254042, 0.6881909602, 0.5877852523, 0.5,
		0.8090169944, 0.3090169944, -0.7020464448, -0.6937804776,
		0.1606220356, 0.8506508084, 0.5257311121, 0, 0.8626684804,
		0.4338885646, -0.259891913, 0.5877852523, -0.4253254042,
		-0.6881909602, 0, 0.8506508084, -0.5257311121, -0.9619383578,
		0.2732665289, 0, 0.5877852523, -0.4253254042, 0.6881909602,
		0.4253254042, -0.6881909602, 0.5877852523, 0.3090169944, -0.5,
		0.8090169944, -0.7020464448, 0.6937804776, -0.1606220356,
		-0.3090169944, 0.5, 0.8090169944, -0.1606220356, 0.7020464448,
		0.6937804776, 0.8626684804, -0.4338885646, 0.259891913,
		0.8090169944, -0.3090169944, 0.5, 0, -0.5257311121, 0.8506508084,
		0.1606220356, -0.7020464448, 0.6937804776, 0.4338885646,
		0.259891913, -0.8626684804, -0.5, 0.8090169944, -0.3090169944,
		-0.259891913, 0.8626684804, -0.4338885646, 0.9510565163,
		-0.1624598481, -0.2628655561, -0.4253254042, -0.6881909602,
		-0.5877852523, -0.8506508084, 0, -0.5257311121, 0.5, -0.8090169944,
		0.3090169944, 0.6881909602, 0.5877852523, -0.4253254042,
		0.6937804776, 0.1606220356, -0.7020464448, -0.6881909602,
		0.5877852523, 0.4253254042, -0.259891913, -0.8626684804,
		-0.4338885646, -0.2732665289, 0, -0.9619383578, -0.2628655561,
		-0.9510565163, -0.1624598481, 0.8090169944, 0.3090169944, 0.5, 0,
		0.5257311121, -0.8506508084, 0.4253254042, -0.6881909602,
		-0.5877852523, 0.5877852523, 0.4253254042, -0.6881909602,
		-0.4338885646, 0.259891913, -0.8626684804, 0, 0.9619383578,
		-0.2732665289, -0.1606220356, 0.7020464448, -0.6937804776,
		0.6937804776, 0.1606220356, 0.7020464448, 0.6881909602,
		-0.5877852523, 0.4253254042, -0.1624598481, -0.2628655561,
		-0.9510565163
	};

	double atomHydCategoryFactors[] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0.6, 0.6, 0.6, 0, 0.25, 0 };

	typedef std::vector<Chem::MolecularGraph::SharedPointer> PatternTable;
	PatternTable atomHydCategoryPatterns;

	boost::once_flag initHydCategoryPatternsFlag = BOOST_ONCE_INIT;

	void initHydCategoryPatterns() 
	{
		using namespace Chem;
			
		atomHydCategoryPatterns.push_back(parseSMARTS("[#1,#7,#8:1]"));
			
		atomHydCategoryPatterns.push_back(parseSMARTS("[S;!H0:2]"));
			
		atomHydCategoryPatterns.push_back(parseSMARTS("[*:3]~*~[!+0]"));
		atomHydCategoryPatterns.push_back(parseSMARTS("[*:3]~[!+0]"));
		atomHydCategoryPatterns.push_back(parseSMARTS("[!+0:3]"));
			
		atomHydCategoryPatterns.push_back(parseSMARTS("[*:4]~*~[O,N;!H0;!$(*-*=,:*)]"));
		atomHydCategoryPatterns.push_back(parseSMARTS("[*:4]~[O,N;!H0;!$(*-*=,:*)]"));
		atomHydCategoryPatterns.push_back(parseSMARTS("[O,N;!H0;!$(*-*=,:*):4]"));
			
		atomHydCategoryPatterns.push_back(parseSMARTS("[*:5]~[S;!H0;!$(*-*=,:*)]"));
		atomHydCategoryPatterns.push_back(parseSMARTS("[S;!H0;!$(*-*=,:*):5]"));
			
		atomHydCategoryPatterns.push_back(parseSMARTS("[*:6]~*=[O]"));
		atomHydCategoryPatterns.push_back(parseSMARTS("[*:6]=[O]"));
		atomHydCategoryPatterns.push_back(parseSMARTS("[O:6]=*"));
			
		atomHydCategoryPatterns.push_back(parseSMARTS("[*:7]~[#16;v3,v4,v5,v6]"));
		atomHydCategoryPatterns.push_back(parseSMARTS("[#16;v3,v4,v5,v6:7]"));
			
		atomHydCategoryPatterns.push_back(parseSMARTS("[#16:8]=*"));

		atomHydCategoryPatterns.push_back(parseSMARTS("[*:9]~*~*=[O]"));

		atomHydCategoryPatterns.push_back(parseSMARTS("[*:10]~*~[#16;v3,v4,v5,v6]"));

		atomHydCategoryPatterns.push_back(parseSMARTS("[*:11]~[#16;$(*=*)]"));

		atomHydCategoryPatterns.push_back(parseSMARTS("[O]=*~*~[*:12]~*~*=[O]"));
		atomHydCategoryPatterns.push_back(parseSMARTS("[O]=*~*~[*:12]~*~[#16;v3,v4,v5,v6]"));
		atomHydCategoryPatterns.push_back(parseSMARTS("[O]=*~*~[*:12]~[#16;$(*=*)]"));
		atomHydCategoryPatterns.push_back(parseSMARTS("[#16;v3,v4,v5,v6]~*~[*:12]~*~[#16;v3,v4,v5,v6]"));
		atomHydCategoryPatterns.push_back(parseSMARTS("[#16;v3,v4,v5,v6]~*~[*:12]~[#16;$(*=*)]"));
		atomHydCategoryPatterns.push_back(parseSMARTS("[#16;$(*=*)]~[*:12]~[#16;$(*=*)]"));

		atomHydCategoryPatterns.push_back(parseSMARTS("[*:13]~[N,O;!$(*-*=,:*)]"));

		atomHydCategoryPatterns.push_back(parseSMARTS("[N,O;!$(*-*=,:*)]~[*:14]~[N,O;!$(*-*=,:*)]"));
	}

	const std::size_t RING_SIZE_LIMIT      = 7;
	double MAX_CHAIN_HYD_FACTOR            = 2.0;
}


const double       Pharm::HydrophobicFeatureGenerator::DEF_FEATURE_TOL         = 1.5;
const double       Pharm::HydrophobicFeatureGenerator::DEF_HYD_THRESHOLD_RING  = 1.2;
const double       Pharm::HydrophobicFeatureGenerator::DEF_HYD_THRESHOLD_CHAIN = 1.2;
const double       Pharm::HydrophobicFeatureGenerator::DEF_HYD_THRESHOLD_GROUP = 1.2;
const unsigned int Pharm::HydrophobicFeatureGenerator::DEF_FEATURE_TYPE;
const unsigned int Pharm::HydrophobicFeatureGenerator::DEF_FEATURE_GEOM;


Pharm::HydrophobicFeatureGenerator::HydrophobicFeatureGenerator():
	featureType(DEF_FEATURE_TYPE),  featureTol(DEF_FEATURE_TOL), featureGeom(DEF_FEATURE_GEOM),
	hydThreshRing(DEF_HYD_THRESHOLD_RING), hydThreshChain(DEF_HYD_THRESHOLD_CHAIN), 
	hydThreshGroup(DEF_HYD_THRESHOLD_GROUP)
{}

Pharm::HydrophobicFeatureGenerator::HydrophobicFeatureGenerator(const HydrophobicFeatureGenerator& gen):
	PatternBasedFeatureGenerator(gen), featureType(gen.featureType), featureTol(gen.featureTol), 
	featureGeom(gen.featureGeom), hydThreshRing(gen.hydThreshRing), hydThreshChain(gen.hydThreshChain), 
	hydThreshGroup(gen.hydThreshGroup)
{}

Pharm::HydrophobicFeatureGenerator::HydrophobicFeatureGenerator(const Chem::MolecularGraph& molgraph, Pharmacophore& pharm):
	featureType(DEF_FEATURE_TYPE),  featureTol(DEF_FEATURE_TOL), featureGeom(DEF_FEATURE_GEOM),
	hydThreshRing(DEF_HYD_THRESHOLD_RING), hydThreshChain(DEF_HYD_THRESHOLD_CHAIN), 
	hydThreshGroup(DEF_HYD_THRESHOLD_GROUP)
{
    generate(molgraph, pharm);
}

Pharm::HydrophobicFeatureGenerator::~HydrophobicFeatureGenerator() {}

void Pharm::HydrophobicFeatureGenerator::setFeatureType(unsigned int type)
{
	featureType = type;
}

unsigned int Pharm::HydrophobicFeatureGenerator::getFeatureType() const
{
	return featureType;
}

void Pharm::HydrophobicFeatureGenerator::setFeatureTolerance(double tol)
{
	featureTol = tol;
}

double Pharm::HydrophobicFeatureGenerator::getFeatureTolerance() const
{
	return featureTol;
}

void Pharm::HydrophobicFeatureGenerator::setFeatureGeometry(unsigned int geom)
{
	featureGeom = geom;
}

unsigned int Pharm::HydrophobicFeatureGenerator::getFeatureGeometry() const
{
	return featureGeom;
}

void Pharm::HydrophobicFeatureGenerator::setRingHydrophobicityThreshold(double thresh)
{
	hydThreshRing = thresh;
}

double Pharm::HydrophobicFeatureGenerator::getRingHydrophobicityThreshold() const
{
	return hydThreshRing;
}

void Pharm::HydrophobicFeatureGenerator::setChainHydrophobicityThreshold(double thresh)
{
	hydThreshChain = thresh;
}

double Pharm::HydrophobicFeatureGenerator::getChainHydrophobicityThreshold() const
{
	return hydThreshChain;
}

void Pharm::HydrophobicFeatureGenerator::setGroupHydrophobicityThreshold(double thresh)
{
	hydThreshGroup = thresh;
}

double Pharm::HydrophobicFeatureGenerator::getGroupHydrophobicityThreshold() const
{
	return hydThreshGroup;
}

Pharm::HydrophobicFeatureGenerator& Pharm::HydrophobicFeatureGenerator::operator=(const HydrophobicFeatureGenerator& gen)
{
	if (this == &gen)
		return *this;

	PatternBasedFeatureGenerator::operator=(gen);

	featureType = gen.featureType; 
	featureTol = gen.featureTol; 
	featureGeom = gen.featureGeom;
	hydThreshRing = gen.hydThreshRing;
	hydThreshChain = gen.hydThreshChain; 
	hydThreshGroup = gen.hydThreshGroup;

	return *this;
}

void Pharm::HydrophobicFeatureGenerator::addNonPatternFeatures(const Chem::MolecularGraph& molgraph, Pharmacophore& pharm)
{
	init(molgraph);

	calcAtomHydrophobicities();

	genRingFeatures(pharm);
	genGroupFeatures(pharm);
	genChainFeatures(pharm);
}

void Pharm::HydrophobicFeatureGenerator::init(const Chem::MolecularGraph& molgraph)
{
	molGraph = &molgraph;

	std::size_t num_atoms = molgraph.getNumAtoms();

	procAtomMask.resize(num_atoms);
	procAtomMask.reset();

	hAtomMask.resize(num_atoms);
	hAtomMask.reset();

	tmpAtomMask.resize(num_atoms);

	buildAtomTypeMask(molgraph, hAtomMask, Chem::AtomType::H);

	boost::call_once(&initHydCategoryPatterns, initHydCategoryPatternsFlag);

	if (hydSubSearchTable.empty()) {
		for (PatternTable::const_iterator p_it = atomHydCategoryPatterns.begin(), p_end = atomHydCategoryPatterns.end(); p_it != p_end; ++p_it) {
			const Chem::MolecularGraph& ptn = **p_it;
			Chem::SubstructureSearch::SharedPointer ss_ptr(new Chem::SubstructureSearch(ptn));

			hydSubSearchTable.push_back(ss_ptr);
		}
	}
}

void Pharm::HydrophobicFeatureGenerator::genRingFeatures(Pharmacophore& pharm)
{
	using namespace Chem;

	const FragmentList::BaseType& sssr = *getSSSR(*molGraph);

	for (FragmentList::BaseType::ConstElementIterator it = sssr.getElementsBegin(), end = sssr.getElementsEnd(); it != end; ++it) {
		const Fragment& ring = **it;
	
		if (!isHydrophobicRing(ring))
			continue;
	
		emitFeature(featureAtoms, pharm, *it);
	} 
}
	
void Pharm::HydrophobicFeatureGenerator::genGroupFeatures(Pharmacophore& pharm)
{
	using namespace Chem;

	std::size_t idx = 0;

	for (MolecularGraph::ConstAtomIterator it = molGraph->getAtomsBegin(), end = molGraph->getAtomsEnd(); it != end; ++it, idx++) {
		const Atom& atom = *it;

		if (hAtomMask.test(idx))
			continue;

		featureAtoms.clear();

		if (procAtomMask.test(idx))
			continue; // Ignore already processed ring atoms?

		featureAtoms.push_back(&atom);

		std::size_t num_hvy_bonds = 0;
		Atom::ConstAtomIterator a_it = atom.getAtomsBegin();

		for (Atom::ConstBondIterator b_it = atom.getBondsBegin(), b_end = atom.getBondsEnd(); b_it != b_end; ++b_it, ++a_it) {
			const Atom& nbr_atom = *a_it;

			if (!molGraph->containsBond(*b_it))
				continue;

			if (!molGraph->containsAtom(nbr_atom))
				continue;

			std::size_t nbr_atom_idx = molGraph->getAtomIndex(nbr_atom);

			if (hAtomMask.test(nbr_atom_idx))
				continue;

			num_hvy_bonds++;

			if (procAtomMask.test(nbr_atom_idx))
				continue;

			if (getHeavyAtomCount(nbr_atom, *molGraph) == 1)
				featureAtoms.push_back(&nbr_atom);
		}

		// check if valid group
		
		if (num_hvy_bonds < 3 || featureAtoms.empty()) 
			continue;
		
		buildAtomMask(featureAtoms, tmpAtomMask);

		procAtomMask |= tmpAtomMask;

		if (isContainedInExMatchList(tmpAtomMask) || isContainedInIncMatchList(tmpAtomMask))
			continue;

		// check min. summed hydrophobicity

		if (calcSummedHydrophobicity(featureAtoms) < hydThreshGroup)
			continue;

		emitFeature(featureAtoms, pharm, makeFragment(featureAtoms));
	}
}
	
void Pharm::HydrophobicFeatureGenerator::genChainFeatures(Pharmacophore& pharm)
{
	using namespace Chem;

	std::size_t num_atoms = molGraph->getNumAtoms();

	for (std::size_t i = 0; i < num_atoms; i++)
		if (atomHydTable[i] == 0.0)
			procAtomMask.set(i);
	
	const FragmentList& sssr = *getSSSR(*molGraph);
	
	for (FragmentList::ConstElementIterator it = sssr.getElementsBegin(), end = sssr.getElementsEnd(); it != end; ++it) {
		const Fragment& ring = *it;
	
		if (ring.getNumAtoms() <= RING_SIZE_LIMIT) // check size
			continue;
	
		// check if all atoms have not yet been processed 

		tmpAtomMask.reset();

		for (Fragment::ConstAtomIterator it = ring.getAtomsBegin(), end = ring.getAtomsEnd(); it != end; ++it)
			tmpAtomMask.set(molGraph->getAtomIndex(*it));

		if (tmpAtomMask.intersects(procAtomMask))
			continue;

		procAtomMask |= tmpAtomMask;

		// process ring as a chain

		chainAtoms.clear();

		std::transform(ring.getAtomsBegin(), ring.getAtomsEnd(), 
					   std::back_inserter(chainAtoms), Internal::AddressOf<const Atom>());

		processChain(pharm);
	} 

	for (std::size_t i = 0; i < num_atoms; i++) {
		if (procAtomMask.test(i))
			continue;

		const Atom& atom = molGraph->getAtom(i);
			
		if (!isChainEndAtom(atom))
			continue;

		chainAtoms.clear();

		extractChain(atom);
		processChain(pharm);
	}
}

void Pharm::HydrophobicFeatureGenerator::extractChain(const Chem::Atom& atom)
{
	using namespace Chem;

	chainAtoms.push_back(&atom);
	procAtomMask.set(molGraph->getAtomIndex(atom));

	Atom::ConstAtomIterator a_it = atom.getAtomsBegin();

	for (Atom::ConstBondIterator b_it = atom.getBondsBegin(), b_end = atom.getBondsEnd(); b_it != b_end; ++b_it, ++a_it) {
		const Atom& nbr_atom = *a_it;

		if (!molGraph->containsBond(*b_it))
			continue;

		if (!molGraph->containsAtom(nbr_atom))
			continue;

		if (procAtomMask.test(molGraph->getAtomIndex(nbr_atom)))
			continue;

		extractChain(nbr_atom);
		return;
	}
}

void Pharm::HydrophobicFeatureGenerator::processChain(Pharmacophore& pharm)
{
	while (!chainAtoms.empty()) {
		double hyd_sum = 0.0;

		featureAtoms.clear();
		tmpAtomMask.reset();

		while (!chainAtoms.empty()) {
			const Chem::Atom* atom = chainAtoms.back();
			std::size_t atom_idx = molGraph->getAtomIndex(*atom);
	
			if ((hyd_sum + atomHydTable[atom_idx] >= hydThreshChain * MAX_CHAIN_HYD_FACTOR) && !featureAtoms.empty())
				break;

			featureAtoms.push_back(atom);
			chainAtoms.pop_back();
			tmpAtomMask.set(atom_idx);
			hyd_sum += atomHydTable[atom_idx];
		} 

		if (hyd_sum < hydThreshChain) 
			break;
		
		if (isContainedInExMatchList(tmpAtomMask) || isContainedInIncMatchList(tmpAtomMask))
			continue;

		Feature& feature = emitFeature(featureAtoms, pharm, makeFragment(featureAtoms), false);
		const Chem::Atom3DCoordinatesFunction& coords_func = getAtom3DCoordinatesFunction();

		if (coords_func.empty())
			return;

		if (featureAtoms.size() == 1) {
			set3DCoordinates(feature, coords_func(*featureAtoms[0]));

		} else {
			bool term_atom1 = (getHeavyAtomCount(*featureAtoms.front(), *molGraph) == 1);
			bool term_atom2 = (getHeavyAtomCount(*featureAtoms.back(), *molGraph) == 1);

			if (term_atom1 && !term_atom2) {
				set3DCoordinates(feature, coords_func(*featureAtoms.front()));

			} else if (term_atom2 && !term_atom1) { 
				set3DCoordinates(feature, coords_func(*featureAtoms.back()));

			} else {
				Math::Vector3D pos;

				if (calcHydWeightedCentroid(featureAtoms, pos))
					set3DCoordinates(feature, pos);
			}
		}
	}
}

Pharm::Feature& Pharm::HydrophobicFeatureGenerator::emitFeature(const AtomList& alist, Pharmacophore& pharm, 
																const Chem::Fragment::SharedPointer& substruct, 
																bool set_pos) const
{
	Feature& feature = pharm.addFeature();

	setType(feature, featureType);
	setTolerance(feature, featureTol);
	setGeometry(feature, featureGeom);
	setSubstructure(feature, substruct);

	Math::Vector3D pos;

	if (calcHydWeightedCentroid(alist, pos))
		set3DCoordinates(feature, pos);

	return feature;
}

bool Pharm::HydrophobicFeatureGenerator::isHydrophobicRing(const Chem::Fragment& ring)
{ 
	using namespace Chem;

	std::size_t num_atoms = ring.getNumAtoms();

	if (num_atoms > RING_SIZE_LIMIT)
		return false;

	featureAtoms.clear();

	std::transform(ring.getAtomsBegin(), ring.getAtomsEnd(), 
				   std::back_inserter(featureAtoms), Internal::AddressOf<const Atom>());

	buildAtomMask(featureAtoms, tmpAtomMask);

	procAtomMask |= tmpAtomMask;

	if (isContainedInExMatchList(tmpAtomMask) || isContainedInIncMatchList(tmpAtomMask))
		return false;

	// check min. summed hydrophobicity

	if (calcSummedHydrophobicity(featureAtoms) < hydThreshRing) 
		return false;

	// check at least 2 neighboring atoms with h>0 and no substituent of more than 2 atoms 

	for (std::size_t i = 0; i < num_atoms; i++) {
		const Atom& atom1 = *featureAtoms[i];

		if (atomHydTable[molGraph->getAtomIndex(atom1)] <= 0.0)
			continue;

		const Atom& atom2 = *featureAtoms[(i + 1) % num_atoms];

		if (atomHydTable[molGraph->getAtomIndex(atom2)] <= 0.0) {
			i++;
			continue;
		}

		if (hasSubstWithMoreThan2Atoms(atom1, ring, true))
			continue;

		if (hasSubstWithMoreThan2Atoms(atom2, ring, true)) {
			i++;
			continue;
		}

	    return true;
	}

	const Atom3DCoordinatesFunction& coords_func = getAtom3DCoordinatesFunction();

	if (coords_func.empty())
		return true;

	// check if all substituents are on one side of the plane of the ring

	Math::Vector3D plane_dir, tmp;

	if (!calcPlaneFeatureOrientation(featureAtoms, plane_dir, tmp))
		return true;

	int subst_side = 0;
	const double subst_ang_thresh = std::cos(82.5 / 180.0 * M_PI); // plane angle threshold for substituents lying in the ring plane

	for (Fragment::ConstAtomIterator it = ring.getAtomsBegin(), end = ring.getAtomsEnd(); it != end; ++it) {
		const Atom& atom = *it;
		const Math::Vector3D& atom_pos = coords_func(atom);
		Atom::ConstAtomIterator a_it = atom.getAtomsBegin();

		for (Atom::ConstBondIterator b_it = atom.getBondsBegin(), b_end = atom.getBondsEnd(); b_it != b_end; ++b_it, ++a_it) {
			const Atom& nbr_atom = *a_it;

			if (ring.containsAtom(nbr_atom))
				continue;

			if (!molGraph->containsBond(*b_it))
				continue;

			if (!molGraph->containsAtom(nbr_atom))
				continue;

			if (hAtomMask.test(molGraph->getAtomIndex(nbr_atom)))
				continue;

			tmp.assign(coords_func(nbr_atom) - atom_pos);
			tmp /= length(tmp);

			double inner_prod = innerProd(tmp, plane_dir);

			if (std::abs(inner_prod) <= subst_ang_thresh)
				continue;

			int sign = (inner_prod < 0.0 ? -1 : 1);

			if (subst_side == 0)
				subst_side = sign;

			else if (subst_side != sign) 
				return false;
		}
	}

	return true;
}

bool Pharm::HydrophobicFeatureGenerator::hasSubstWithMoreThan2Atoms(const Chem::Atom& atom, const Chem::Fragment& ring, bool first_level) const
{
	using namespace Chem;

	Atom::ConstAtomIterator a_it = atom.getAtomsBegin();

	for (Atom::ConstBondIterator b_it = atom.getBondsBegin(), b_end = atom.getBondsEnd(); b_it != b_end; ++b_it, ++a_it) {
		const Atom& nbr_atom = *a_it;

		if (ring.containsAtom(nbr_atom))
			continue;

		if (!molGraph->containsBond(*b_it))
			continue;

		if (!molGraph->containsAtom(nbr_atom))
			continue;

		if (hAtomMask.test(molGraph->getAtomIndex(nbr_atom)))
			continue;

		std::size_t hvy_cnt = getHeavyAtomCount(nbr_atom, *molGraph);

		if (!first_level) 
			return (hvy_cnt > 1);

		if (hvy_cnt > 2)
			return true;
		
		if (hvy_cnt < 2)
			continue;

		if (hasSubstWithMoreThan2Atoms(nbr_atom, ring, false))
			return true;
	}

	return false;
}

bool Pharm::HydrophobicFeatureGenerator::calcHydWeightedCentroid(const AtomList& alist, Math::Vector3D& centroid) const
{
	const Chem::Atom3DCoordinatesFunction& coords_func = getAtom3DCoordinatesFunction();

	if (coords_func.empty())
		return false;

	double total_hyd = 0.0;

	for (AtomList::const_iterator it = alist.begin(), end = alist.end(); it != end; ++it) {
		const Chem::Atom& atom = **it;
		double atom_hyd = atomHydTable[molGraph->getAtomIndex(atom)];

		centroid.plusAssign(coords_func(atom) * atom_hyd);
		total_hyd += atom_hyd;
	}

	if (total_hyd == 0.0)
		return false;

	centroid /= total_hyd;

	return true;
}

void Pharm::HydrophobicFeatureGenerator::calcAtomHydrophobicities()
{
	using namespace Chem;

	std::size_t num_atoms = molGraph->getNumAtoms();

	atomHydTable.assign(num_atoms, 1.0);

	for (HydPatternSubSearchTable::const_iterator ss_it = hydSubSearchTable.begin(), ss_end = hydSubSearchTable.end(); 
		 ss_it != ss_end; ++ss_it) {

		SubstructureSearch& sub_search = **ss_it;

		sub_search.findMappings(*molGraph);

		for (SubstructureSearch::ConstMappingIterator m_it = sub_search.getMappingsBegin(),
				 m_end = sub_search.getMappingsEnd(); m_it != m_end; ++m_it) {

			const AtomMapping& mapping = m_it->getAtomMapping();

			for (AtomMapping::ConstEntryIterator it = mapping.getEntriesBegin(), end = mapping.getEntriesEnd(); it != end; ++it) {
				std::size_t hyd_cat = getReactionAtomMappingID(*it->first);

				if (hyd_cat == 0)
					continue;

				atomHydTable[molGraph->getAtomIndex(*it->second)] *= atomHydCategoryFactors[hyd_cat];
			}
		}
	}

	for (std::size_t i = 0; i < num_atoms; i++) {
		if (atomHydTable[i] == 0.0)
			continue;

		atomHydTable[i] *= calcAccessibleSurfaceFactor(molGraph->getAtom(i));
	}
}


// Simplified implementation without probe-sphere

double Pharm::HydrophobicFeatureGenerator::calcAccessibleSurfaceFactor(const Chem::Atom& atom)
{
	using namespace Chem;

	double vdw_radius = getVdWRadius(atom);
	const Atom3DCoordinatesFunction& coords_func = getAtom3DCoordinatesFunction();

	if (coords_func.empty())
		return vdw_radius * vdw_radius;

	const Math::Vector3D& atom_pos = coords_func(atom);

	nbrAtomVdWRadii.clear();
	nbrAtomPositions.clear();

	Atom::ConstAtomIterator a_it = atom.getAtomsBegin();

	for (Atom::ConstBondIterator b_it = atom.getBondsBegin(), b_end = atom.getBondsEnd(); b_it != b_end; ++b_it, ++a_it) {
		if (!molGraph->containsBond(*b_it))
			continue;

		const Atom& nbr_atom = *a_it;

		if (!molGraph->containsAtom(nbr_atom))
			continue;

		nbrAtomPositions.push_back(coords_func(nbr_atom));
		nbrAtomVdWRadii.push_back(getVdWRadius(nbr_atom));
	}

	std::size_t num_nbrs = nbrAtomPositions.size();

	if (num_nbrs == 0)
		return vdw_radius * vdw_radius;

	Math::Vector3D ref_vec1(nbrAtomPositions[0] - atom_pos);
	Math::Vector3D ref_vec2;

	if (num_nbrs > 1) {
		ref_vec2.assign(nbrAtomPositions[1] - atom_pos);

	} else {
		if (ref_vec1(0) != 0) {
			ref_vec2(0) = ref_vec1(1);
			ref_vec2(1) = -ref_vec1(0);
			ref_vec2(2) = 0.0;

		} else if (ref_vec1(1) != 0) {
			ref_vec2(0) = -ref_vec1(1);
			ref_vec2(1) = ref_vec1(0);
			ref_vec2(2) = 0.0;

		} else {
			ref_vec2(0) = 0.0;
			ref_vec2(1) = -ref_vec1(2);
			ref_vec2(2) = ref_vec1(1);
		}
	}

	ref_vec1 /= length(ref_vec1);

	Math::Matrix3D xform;

	column(xform, 0) = ref_vec1;
	column(xform, 1) = crossProd(ref_vec1, ref_vec2);
	column(xform, 1) /= length(column(xform, 1));
	column(xform, 2) = crossProd(ref_vec1, column(xform, 1));

	Math::Vector3D trans_sp;
	std::size_t inacc_cnt = 0;

	for (std::size_t i = 0; i < sizeof(spherePoints) / sizeof(double); i += 3) {
		double sp_x = spherePoints[i] * vdw_radius;
		double sp_y = spherePoints[i + 1] * vdw_radius;
		double sp_z = spherePoints[i + 2] * vdw_radius;

		trans_sp(0) = xform(0, 0) * sp_x + xform(0, 1) * sp_y +  xform(0, 2) * sp_z + atom_pos(0);
		trans_sp(1) = xform(1, 0) * sp_x + xform(1, 1) * sp_y +  xform(1, 2) * sp_z + atom_pos(1);
		trans_sp(2) = xform(2, 0) * sp_x + xform(2, 1) * sp_y +  xform(2, 2) * sp_z + atom_pos(2);

		for (std::size_t j = 0; j < num_nbrs; j++) {
			if (length(trans_sp - nbrAtomPositions[j]) < nbrAtomVdWRadii[j]) {
				inacc_cnt++;
				break;
			}
		}
	} 

	std::size_t num_spts = sizeof(spherePoints) / sizeof(double) / 3;

	return double(num_spts - inacc_cnt) * vdw_radius * vdw_radius / num_spts;
}

void Pharm::HydrophobicFeatureGenerator::buildAtomMask(const AtomList& alist, Util::BitSet& mask) const
{
	mask.reset();

	for (AtomList::const_iterator it = alist.begin(), end = alist.end(); it != end; ++it)
		mask.set(molGraph->getAtomIndex(**it));
}

double Pharm::HydrophobicFeatureGenerator::calcSummedHydrophobicity(const AtomList& alist) const
{
	double total_hyd = 0.0;

	for (AtomList::const_iterator it = alist.begin(), end = alist.end(); it != end; ++it) 
		total_hyd += atomHydTable[molGraph->getAtomIndex(**it)];

	return total_hyd;
}

Chem::Fragment::SharedPointer Pharm::HydrophobicFeatureGenerator::makeFragment(const AtomList& alist) const
{
	using namespace Chem;

	Fragment::SharedPointer frag(new Fragment());

	for (AtomList::const_iterator it = alist.begin(), end = alist.end(); it != end; ++it) 
		frag->addAtom(**it);

	for (AtomList::const_iterator it = alist.begin(), end = alist.end(); it != end; ++it) {
		const Atom& atom = **it;
		Atom::ConstAtomIterator a_it = atom.getAtomsBegin();

		for (Atom::ConstBondIterator b_it = atom.getBondsBegin(), b_end = atom.getBondsEnd(); b_it != b_end; ++b_it, ++a_it) {
			const Atom& nbr_atom = *a_it;

			if (!frag->containsAtom(nbr_atom))
				continue;

			const Bond& nbr_bond = *b_it;

			if (!molGraph->containsBond(nbr_bond))
				continue;
			
			frag->addBond(nbr_bond);
		}
	}

	return frag;
}

bool Pharm::HydrophobicFeatureGenerator::isChainEndAtom(const Chem::Atom& atom) const
{
	using namespace Chem;

	bool found_unproc_nbr;
	Atom::ConstAtomIterator a_it = atom.getAtomsBegin();

	for (Atom::ConstBondIterator b_it = atom.getBondsBegin(), b_end = atom.getBondsEnd(); b_it != b_end; ++b_it, ++a_it) {
		const Atom& nbr_atom = *a_it;

		if (!molGraph->containsAtom(nbr_atom))
			continue;

		const Bond& nbr_bond = *b_it;

		if (!molGraph->containsBond(nbr_bond))
			continue;
			
		if (!procAtomMask.test(molGraph->getAtomIndex(nbr_atom))) {
			if (found_unproc_nbr)
				return false;

			found_unproc_nbr = true;
		}
	}

	return true;
}
