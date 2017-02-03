/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * XLogPCalculator.cpp 
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
#include <functional>
#include <numeric>
#include <string>

#include <boost/bind.hpp>
#include <boost/thread.hpp>

#include "CDPL/Chem/XLogPCalculator.hpp"
#include "CDPL/Chem/BasicMolecule.hpp"
#include "CDPL/Chem/Atom.hpp"
#include "CDPL/Chem/Bond.hpp"
#include "CDPL/Chem/MolecularGraphFunctions.hpp"
#include "CDPL/Chem/AtomFunctions.hpp"
#include "CDPL/Chem/BondFunctions.hpp"
#include "CDPL/Chem/AtomType.hpp"
#include "CDPL/Chem/UtilityFunctions.hpp"
#include "CDPL/Math/VectorIterator.hpp"


using namespace CDPL;


namespace
{

	const std::size_t CORRECTION_FACTORS_BEGIN    = 90;
	const std::size_t HYDROPHOBIC_C_INDEX         = 90;
	const std::size_t INTERNAL_H_BOND_INDEX       = 91;
	const std::size_t HALOGEN_13_PAIR_INDEX       = 92;
	const std::size_t AROMATIC_N_14_PAIR_INDEX    = 93;
	const std::size_t ORTHO_SP3_O_PAIR_INDEX      = 94;
	const std::size_t PARA_DONOR_PAIR_INDEX       = 95;
	const std::size_t SP2_O_15_PAIR_INDEX         = 96;
	const std::size_t ALPHA_AMINO_ACID_INDEX      = 97;
	const std::size_t SALICYLIC_ACID_INDEX        = 98;
	const std::size_t P_AMINO_SULFONIC_ACID_INDEX = 99;

	const unsigned int UNKNOWN_ATOM_TYPE          = 100;	

	const std::string AROMATIC_N_14_PAIR_SMARTS    = "n1:a:a:n:a:a1";
	const std::string ORTHO_SP3_O_PAIR_SMARTS      = "O-c:c-O"; 
	const std::string PARA_DONOR_PAIR_SMARTS       = "c1(-[#7,#8]):a:a:c(-[#7,#8]):a:a:1";
	const std::string SP2_O_15_PAIR_SMARTS         = "O=C-*-C=O";
	const std::string ALPHA_AMINO_ACID_SMARTS      = "[CX4](-N)-C(=O)-O";
	const std::string SALICYLIC_ACID_SMARTS        = "c1:c(-C(=O)-O):c(-O):c:c:c:1";
	const std::string P_AMINO_SULFONIC_ACID_SMARTS = "S(=O)(=O)-c1:c:c:c:c:c:1-N";

	boost::once_flag initSSSPatternsFlag = BOOST_ONCE_INIT;

	Chem::Molecule::SharedPointer aromaticN14PairQuery;
	Chem::Molecule::SharedPointer orthoSP3OPairQuery;
	Chem::Molecule::SharedPointer paraDonorPairQuery;
	Chem::Molecule::SharedPointer sp2O15PairQuery;
	Chem::Molecule::SharedPointer alphaAminoAcidQuery;
	Chem::Molecule::SharedPointer salicylicAcid;
	Chem::Molecule::SharedPointer pAminoSulfonicAcidQuery;

	void initSSSPatterns()
	{
		aromaticN14PairQuery = Chem::parseSMARTS(AROMATIC_N_14_PAIR_SMARTS);
		orthoSP3OPairQuery = Chem::parseSMARTS(ORTHO_SP3_O_PAIR_SMARTS);
		paraDonorPairQuery = Chem::parseSMARTS(PARA_DONOR_PAIR_SMARTS);
		sp2O15PairQuery = Chem::parseSMARTS(SP2_O_15_PAIR_SMARTS);
		alphaAminoAcidQuery = Chem::parseSMARTS(ALPHA_AMINO_ACID_SMARTS);
		salicylicAcid = Chem::parseSMARTS(SALICYLIC_ACID_SMARTS);
		pAminoSulfonicAcidQuery = Chem::parseSMARTS(P_AMINO_SULFONIC_ACID_SMARTS);
	}

	const double REGRESSION_COEFFS[] = {
		0.545219,
		0.280277,
		0.0480369,
		0.358949,
		0.0306245,
		-0.109314,
		-0.044685,
		-0.148478,
		-0.707041,
		0.117624,
		-0.200231,
		-0.425323,
		-0.158051,
		-0.0326008,
		-0.407558,
		-0.249668,
		-0.514204,
		-0.234835,
		-0.20768,
		-0.491411,
		0.435908,
		0.414843,
		0.141315,
		0.0620506,
		-0.106993,
		-0.0514413,
		0.00665378,
		-0.0241289,
		0.0256664,
		0.119525,
		-0.374676,
		0.339993,
		-0.162011,
		0.276286,
		-0.0443752,
		-0.202019,
		0.180987,
		0.192405,
		0.333721,
		2.17745,
		-0.595278,
		-0.457035,
		-0.753663,
		-0.297418,
		-0.107949,
		0.306394,
		0.270281,
		0.587458,
		-0.203809,
		0.373824,
		0.610824,
		-0.808274,
		0.042134,
		-0.710239,
		-0.267076,
		-0.274135,
		-0.158558,
		-0.162949,
		-0.0608809,
		-0.30583,
		0.859388,
		0.0848922,
		0.0970587,
		-0.46587,
		0.773001,
		0.592069,
		0.0241904,
		-0.505819,
		-0.617211,
		-0.0511091,
		-0.682031,
		-0.0172158,
		0.229049,
		0.2495,
		-0.340034,
		0.474701,
		0.32913,
		-0.310581,
		-1.28721,
		-0.320445,
		-0.94932,
		0.909648,
		0.339747,
		0.26695,
		0.51751,
		0.690556,
		0.85767,
		0.879156,
		1.0224,
		1.13127,
		0.196031,
		0.194745,
		0.162908,
		0.483429,
		-0.187861,
		-0.30755,
		0.366468,
		-2.36494,
		0.45759,
		-0.204342
	};
}


Chem::XLogPCalculator::XLogPCalculator(): featureVector(FEATURE_VECTOR_SIZE), logP(0.0) 
{
	substructSearch.uniqueMappingsOnly(true);
}

Chem::XLogPCalculator::XLogPCalculator(const MolecularGraph& molgraph): featureVector(FEATURE_VECTOR_SIZE)
{
	calculate(molgraph);
}

double Chem::XLogPCalculator::calculate(const MolecularGraph& molgraph)
{
	init(molgraph);

	classifyAtoms();

	countAtomTypes();
	countHydrophicCarbons();
	countInternalHBonds();
	countHalogen13Pairs();
	countAromaticNitrogen14Pairs();
	countOrthoSP3OxygenPairs();
	countParaDonorPairs();
	countSP2Oxygen15Pairs();
	countAlphaAminoAcidGroups();
	countSalicylicAcidGroups();
	countParaAminoSulfonicAcidGroups();
	
	calcLogP();

	return logP;
}

double Chem::XLogPCalculator::getResult() const
{
	return logP;
}

const Math::DVector& Chem::XLogPCalculator::getFeatureVector() const
{
	return featureVector;
}

void Chem::XLogPCalculator::init(const MolecularGraph& molgraph)
{
	molGraph = &molgraph;
	numAtoms = molgraph.getNumAtoms();

	atomInfos.clear();
	atomInfos.reserve(numAtoms);

	MolecularGraph::ConstAtomIterator atoms_end = molgraph.getAtomsEnd();

	for (MolecularGraph::ConstAtomIterator it = molgraph.getAtomsBegin(); it != atoms_end; ++it) {
		const Atom& atom = *it;

		atomInfos.push_back(AtomInfo(molgraph, *it, getAromaticityFlag(atom), getRingFlag(atom)));
	}

	featureVector.clear();

	setUnsaturationFlags();
}

void Chem::XLogPCalculator::setUnsaturationFlags()
{
	MolecularGraph::ConstBondIterator bonds_end = molGraph->getBondsEnd();

	for (MolecularGraph::ConstBondIterator it = molGraph->getBondsBegin(); it != bonds_end; ++it) {
		const Bond& bond = *it;

		if (!molGraph->containsAtom(bond.getBegin()) || !molGraph->containsAtom(bond.getEnd()))
			continue;

		std::size_t bond_order = getOrder(bond);

		if (bond_order == 2 || bond_order == 3) {
			atomInfos[molGraph->getAtomIndex(bond.getBegin())].setUnsaturationFlag();
			atomInfos[molGraph->getAtomIndex(bond.getEnd())].setUnsaturationFlag();
		}
	}
}

void Chem::XLogPCalculator::classifyAtoms()
{
	std::for_each(atomInfos.begin(), atomInfos.end(),
				  boost::bind(&AtomInfo::classifyAtom, _1, boost::ref(atomInfos)));
}

void Chem::XLogPCalculator::countAtomTypes()
{
	AtomInfoTable::const_iterator infos_end = atomInfos.end();

	for (AtomInfoTable::const_iterator it = atomInfos.begin(); it != infos_end; ++it) {
		unsigned int atom_type = it->getAtomType();

		if (atom_type != UNKNOWN_ATOM_TYPE)
			featureVector[atom_type]++;	
	}	
}

void Chem::XLogPCalculator::countHydrophicCarbons()
{
	const Math::ULMatrix& dist_mtx = *getTopologicalDistanceMatrix(*molGraph);

	for (std::size_t i = 0; i < numAtoms; i++) {
		const AtomInfo& atom_info = atomInfos[i];

		if (atom_info.getAtomicNo() != AtomType::C || atom_info.getAtomType() == UNKNOWN_ATOM_TYPE 
			|| atom_info.getNumBonds() < 3 || atom_info.isAromaticAtom())
			continue;

		bool hydrophobic = true;

		for (std::size_t j = 0; j < numAtoms && hydrophobic; j++) {
			if (i == j)
				continue;

			switch (atomInfos[j].getAtomicNo()) {

				case AtomType::N:
				case AtomType::O:
				case AtomType::S:
				case AtomType::P:
				case AtomType::F:
				case AtomType::Cl:
				case AtomType::Br:
				case AtomType::I:
					if (dist_mtx(i, j) < 4)
						hydrophobic = false;

				default:
					continue;
			}
		}

		if (hydrophobic)
			featureVector[HYDROPHOBIC_C_INDEX]++;
	}
}

void Chem::XLogPCalculator::countInternalHBonds()
{	
	const Math::ULMatrix& dist_mtx = *getTopologicalDistanceMatrix(*molGraph);

	for (std::size_t i = 0; i < numAtoms; i++) {
		const AtomInfo& atom_info1 = atomInfos[i];

		if (!atom_info1.isHBondDonorAtom() || atom_info1.isRingAtom())
			continue;

		bool has_ring_nbr1 = atom_info1.hasRingNeighbor();

		for (std::size_t j = 0; j < numAtoms; j++) {
			if (i == j)
				continue;

			const AtomInfo& atom_info2 = atomInfos[j];

			if (!atom_info2.isHBondAcceptorAtom() || atom_info2.isRingAtom())
				continue;

			bool has_ring_nbr2 = atom_info2.hasRingNeighbor();

			if (has_ring_nbr1 && has_ring_nbr2) {
				if (dist_mtx(i, j) == 3)
					featureVector[INTERNAL_H_BOND_INDEX]++;

			} else if (((!has_ring_nbr1 && has_ring_nbr2) || (has_ring_nbr1 && !has_ring_nbr2)) && dist_mtx(i, j) == 4)
				featureVector[INTERNAL_H_BOND_INDEX]++;
		}
	}
}

void Chem::XLogPCalculator::countHalogen13Pairs()
{
	featureVector[HALOGEN_13_PAIR_INDEX] = std::accumulate(atomInfos.begin(), atomInfos.end(), 0,
														   boost::bind(std::plus<std::size_t>(), _1, 
																	   boost::bind(&AtomInfo::getNumHalogenPairs, _2)));
}

void Chem::XLogPCalculator::countAromaticNitrogen14Pairs()
{	
	boost::call_once(&initSSSPatterns, initSSSPatternsFlag);

	substructSearch.setQuery(*aromaticN14PairQuery);
	substructSearch.findMappings(*molGraph);

	featureVector[AROMATIC_N_14_PAIR_INDEX] = substructSearch.getNumMappings();
}

void Chem::XLogPCalculator::countOrthoSP3OxygenPairs()
{
	boost::call_once(&initSSSPatterns, initSSSPatternsFlag);

	substructSearch.setQuery(*orthoSP3OPairQuery);
	substructSearch.findMappings(*molGraph);

	SubstructureSearch::ConstMappingIterator mappings_end = substructSearch.getMappingsEnd();

	for (SubstructureSearch::ConstMappingIterator it = substructSearch.getMappingsBegin(); it != mappings_end; ++it) {
		const AtomMapping& mapping = it->getAtomMapping();

		const AtomInfo& atom_info1 = atomInfos[molGraph->getAtomIndex(*mapping[&orthoSP3OPairQuery->getAtom(0)])];
		const AtomInfo& atom_info2 = atomInfos[molGraph->getAtomIndex(*mapping[&orthoSP3OPairQuery->getAtom(3)])];

		assert(atom_info1.getAtomicNo() == AtomType::O);
		assert(atom_info2.getAtomicNo() ==  AtomType::O);

		if (!atom_info1.isHBondDonorAtom() && !atom_info2.isHBondDonorAtom())
			featureVector[ORTHO_SP3_O_PAIR_INDEX]++;
	}
}

void Chem::XLogPCalculator::countParaDonorPairs()
{
	boost::call_once(&initSSSPatterns, initSSSPatternsFlag);

	substructSearch.setQuery(*paraDonorPairQuery);
	substructSearch.findMappings(*molGraph);

	SubstructureSearch::ConstMappingIterator mappings_end = substructSearch.getMappingsEnd();

	for (SubstructureSearch::ConstMappingIterator it = substructSearch.getMappingsBegin(); it != mappings_end; ++it) {
		const AtomMapping& mapping = it->getAtomMapping();
	
		const AtomInfo& atom_info1 = atomInfos[molGraph->getAtomIndex(*mapping[&paraDonorPairQuery->getAtom(1)])];
		const AtomInfo& atom_info2 = atomInfos[molGraph->getAtomIndex(*mapping[&paraDonorPairQuery->getAtom(5)])];

		assert(atom_info1.getAtomicNo() == AtomType::N || atom_info1.getAtomicNo() == AtomType::O);
		assert(atom_info2.getAtomicNo() == AtomType::N || atom_info2.getAtomicNo() == AtomType::O);

		if (atom_info1.isHBondDonorAtom() && atom_info2.isHBondDonorAtom())
			featureVector[PARA_DONOR_PAIR_INDEX]++;
	}
}

void Chem::XLogPCalculator::countSP2Oxygen15Pairs()
{
	boost::call_once(&initSSSPatterns, initSSSPatternsFlag);

	substructSearch.setQuery(*sp2O15PairQuery);
	substructSearch.findMappings(*molGraph);

	SubstructureSearch::ConstMappingIterator mappings_end = substructSearch.getMappingsEnd();

	for (SubstructureSearch::ConstMappingIterator it = substructSearch.getMappingsBegin(); it != mappings_end; ++it) {
		const AtomMapping& mapping = it->getAtomMapping();

		const AtomInfo& atom_info1 = atomInfos[molGraph->getAtomIndex(*mapping[&sp2O15PairQuery->getAtom(1)])];
		const AtomInfo& atom_info2 = atomInfos[molGraph->getAtomIndex(*mapping[&sp2O15PairQuery->getAtom(2)])];
		const AtomInfo& atom_info3 = atomInfos[molGraph->getAtomIndex(*mapping[&sp2O15PairQuery->getAtom(3)])];

		assert(atom_info1.getAtomicNo() == AtomType::C);
		assert(atom_info3.getAtomicNo() == AtomType::C);

		if (atom_info1.isRingAtom() && atom_info2.isRingAtom() && atom_info3.isRingAtom())
			continue;

		featureVector[SP2_O_15_PAIR_INDEX]++;
	}
}

void Chem::XLogPCalculator::countAlphaAminoAcidGroups()
{
	boost::call_once(&initSSSPatterns, initSSSPatternsFlag);

	substructSearch.setQuery(*alphaAminoAcidQuery);
	substructSearch.findMappings(*molGraph);

	SubstructureSearch::ConstMappingIterator mappings_end = substructSearch.getMappingsEnd();

	for (SubstructureSearch::ConstMappingIterator it = substructSearch.getMappingsBegin(); it != mappings_end; ++it) {
		const AtomMapping& mapping = it->getAtomMapping();
		const AtomInfo& atom_info = atomInfos[molGraph->getAtomIndex(*mapping[&alphaAminoAcidQuery->getAtom(1)])];

		assert(atom_info.getAtomicNo() == AtomType::N);

		switch (atom_info.getAtomType()) {

			case 40:  // sp3 R-NH2 (pi = 0)
			case 43:  // sp3 R-NH-R (pi = 0)
			case 48:  // sp3 NR3 (pi = 0)
			case 66:  // A...N...A
				featureVector[ALPHA_AMINO_ACID_INDEX]++;

			default:
				continue;
		}
	}
}

void Chem::XLogPCalculator::countSalicylicAcidGroups()
{
	boost::call_once(&initSSSPatterns, initSSSPatternsFlag);

	substructSearch.setQuery(*salicylicAcid);
	substructSearch.findMappings(*molGraph);

	featureVector[SALICYLIC_ACID_INDEX] = substructSearch.getNumMappings();
}

void Chem::XLogPCalculator::countParaAminoSulfonicAcidGroups()
{
	boost::call_once(&initSSSPatterns, initSSSPatternsFlag);

	substructSearch.setQuery(*pAminoSulfonicAcidQuery);
	substructSearch.findMappings(*molGraph);

	featureVector[P_AMINO_SULFONIC_ACID_INDEX] = substructSearch.getNumMappings();
}

void Chem::XLogPCalculator::calcLogP()
{
	logP = std::inner_product(Math::vectorBegin(featureVector), Math::vectorEnd(featureVector), REGRESSION_COEFFS, 0.0);
}


Chem::XLogPCalculator::AtomInfo::AtomInfo(const MolecularGraph& molgraph, const Atom& atm, bool aromatic, bool in_ring): 
	molGraph(&molgraph), atom(&atm), isAromatic(aromatic), inRing(in_ring), isUnsaturated(false), analyzed(false)
{
	atomicNo  = getType(atm);

	isClassAAtom  = (atomicNo != AtomType::UNKNOWN && atomicNo <= AtomType::MAX_ATOMIC_NO 
					 && atomicNo != AtomType::H);
	isClassXAtom  = (atomicNo == AtomType::N || atomicNo == AtomType::O);
	isClassRAtom  = (isClassAAtom && !isClassXAtom);
	isHalogenAtom = (atomicNo == AtomType::F || atomicNo == AtomType::Cl 
					 || atomicNo == AtomType::Br || atomicNo == AtomType::I);
}

void Chem::XLogPCalculator::AtomInfo::classifyAtom(AtomInfoTable& atom_infos)
{
	analyzeAtom(atom_infos);

	switch (atomicNo) {

		case AtomType::C:
			atomType = classifyCAtom();
			break;

		case AtomType::N:
			atomType = classifyNAtom();
			break;

		case AtomType::O:
			atomType = classifyOAtom();
			break;

		case AtomType::S:
			atomType = classifySAtom();
			break;

		case AtomType::P:
			atomType = classifyPAtom();
			break;
			
		case AtomType::F:
			atomType = classifyFAtom();
			break;

		case AtomType::Cl:
			atomType = classifyClAtom();
			break;
				
		case AtomType::Br:
			atomType = classifyBrAtom();
			break;
				
		case AtomType::I:
			atomType = classifyIAtom();
			break;
				
		default:
			atomType = UNKNOWN_ATOM_TYPE;
	}
}

// Carbon Classification

unsigned int Chem::XLogPCalculator::AtomInfo::classifyCAtom() const
{
	switch (bondCount) {

		case 4:
			if ((singleABondCount + hCount) == 4)
				return classifySP3CAtom();

			return UNKNOWN_ATOM_TYPE;

		case 3:
			if (doubleABondCount > 1)              // not more than 1 double bond allowed
				return UNKNOWN_ATOM_TYPE;

			return classifySP2CAtom();

		case 2:
			return classifySP1CAtom();

		default:
			return UNKNOWN_ATOM_TYPE;
	}
}

unsigned int Chem::XLogPCalculator::AtomInfo::classifySP3CAtom() const
{
	if (hCount == 3) {
		if (singleRBondCount == 1) {
			if (piSystemCount == 0)               // CH3R (pi = 0)
				return 0;

			if (piSystemCount == 1)               // CH3R (pi = 1)
				return 1;

		} else if (singleXBondCount == 1)         // CH3X
			return 2;

	} else if (hCount == 2) {
		if (singleRBondCount == 2) {
			if (piSystemCount == 0)               // CH2R2 (pi = 0)
				return 3;

			if (piSystemCount == 1)               // CH2R2 (pi = 1)
				return 4;

			if (piSystemCount == 2)               // CH2R2 (pi = 2)
				return 5;

		} else if ((singleRBondCount + singleXBondCount) == 2) {
			if (piSystemCount == 0)               // CH2RnX2-n (pi = 0)
				return 6;

			if (piSystemCount == 1)               // CH2RnX2-n (pi = 1)
				return 7;

			if (piSystemCount == 2)               // CH2RnX2-n (pi = 2)
				return 8;
		}

	} else if (hCount == 1) {
		if (singleRBondCount == 3) {
			if (piSystemCount == 0)               // CHR3 (pi = 0)
				return 9;

			if (piSystemCount == 1)               // CHR3 (pi = 1)
				return 10;

			return 11;                            // CHR3 (pi >= 2)
		}

		if ((singleRBondCount + singleXBondCount) == 3) {
			if (piSystemCount == 0)               // CHRnX3-n (pi = 0)
				return 12;

			if (piSystemCount == 1)               // CHRnX3-n (pi = 1)
				return 13;

			return 14;                            // CHRnX3-n (pi >= 2)
		}

	} else if (hCount == 0) {
		if (singleRBondCount == 4) {
			if (piSystemCount == 0)               // CR4 (pi = 0)
				return 15;

			if (piSystemCount == 1)               // CR4 (pi = 1)
				return 16;

			return 17;                            // CR4 (pi >= 2)
		}

		if ((singleRBondCount + singleXBondCount) == 4) {
			if (piSystemCount == 0)               // CRnX4-n (pi = 0)
				return 18;

			return 19;                            // CRnX4-n (pi > 0)
		}
	}

	return UNKNOWN_ATOM_TYPE;
}

unsigned int Chem::XLogPCalculator::AtomInfo::classifySP2CAtom() const
{
	if (aromCBondCount >= 2) {
		if (hCount == 1)                                                          // C...C(H)...C
			return 31;

		if ((singleRBondCount + doubleRBondCount) == 3)                           // C...C(R)...C
			return 33;

		if ((singleXBondCount + doubleXBondCount) == 1)                           // C...C(X)...C
			return 34;

	} else if (aromNBondCount >= 1) {
		if (hCount == 1)                                                          // A...C(H)...N
			return 32;

		if ((aromXBondCount == 2 && (singleRBondCount + doubleRBondCount) == 1 )
			|| (aromXBondCount == 1 && (singleRBondCount + doubleRBondCount) == 2)) // A...C(R)...N
			return 35;

		if ((aromXBondCount == 2 && (singleXBondCount + doubleXBondCount) == 3)
			|| (aromXBondCount == 1 && (singleXBondCount + doubleXBondCount) == 2)) // A...C(X)...N
			return 36;
	}

	if (doubleABondCount == 1 && (singleABondCount + hCount) == 2) {
		if (hCount == 2)                                                          // A=CH2
			return 20;                            

		if (hCount == 1) {
			if (singleRBondCount == 1) {
				if (piSystemCount == 0)                                           // A=CHR (pi = 0)
					return 21;

				if (piSystemCount == 1)                                           // A=CHR (pi = 1)
					return 22;

			} else if (singleXBondCount == 1) {
				if (piSystemCount == 0)                                           // A=CHX (pi = 0)
					return 23;

				if (piSystemCount == 1)                                           // A=CHX (pi = 1)
					return 24;
			}

		} else if (hCount == 0) { 
			if (singleRBondCount == 2) {
				if (piSystemCount == 0)                                           // A=CR2 (pi = 0)
					return 25;

				return 26;                                                        // A=CR2 (pi > 0)
			}

			if (singleRBondCount == 1 && singleXBondCount == 1) {
				if (piSystemCount == 0)                                           // A=CRX (pi = 0)
					return 27;

				return 28;                                                        // A=CRX (pi > 0)
			}

			if (singleXBondCount == 2) {
				if (piSystemCount == 0)                                           // A=CX2 (pi = 0)
					return 29;

				return 30;                                                        // A=CX2 (pi > 0)
			}
		}
	}

	return UNKNOWN_ATOM_TYPE;
}

unsigned int Chem::XLogPCalculator::AtomInfo::classifySP1CAtom() const
{
	if (tripleRBondCount == 1 && hCount == 1)           // R#CH
		return 37;

	if (tripleABondCount == 1 && singleABondCount == 1) // A#C-A
		return 38;

	if (doubleABondCount == 2)                          // A=C=A
		return 39;

	return UNKNOWN_ATOM_TYPE;
}

// Nitrogen Classification

unsigned int Chem::XLogPCalculator::AtomInfo::classifyNAtom() const
{
	switch (bondCount) {

		case 3:
			if ((singleABondCount + hCount) == 3) {
				if (hasAmideCNbr)
					return classifyAmideNAtom();

				return classifySP3NAtom();
			}

			if ((singleOBondCount >= 1 && doubleOBondCount == 1 && singleABondCount == 2)
				|| (doubleOBondCount == 2 && singleABondCount == 1))
				return 65;                 // sp2: -NO2

			return UNKNOWN_ATOM_TYPE;

		case 2:
			if (aromCBondCount == 2)       // sp2: A...N...A
				return 66;

			return classifySP2NAtom();

		case 1:
			if (tripleCBondCount == 1)     // sp1: -C#N
				return 67;

		default:
			return UNKNOWN_ATOM_TYPE;
	}
}

unsigned int Chem::XLogPCalculator::AtomInfo::classifySP3NAtom() const
{
	if (hCount == 2) {
		if (singleRBondCount == 1) {
			if (piSystemCount == 0)           // R-NH2 (pi = 0)
				return 40;

			if (piSystemCount == 1)           // R-NH2 (pi = 1)
				return 41;

		} else if (singleXBondCount == 1)     // X-NH2
			return 42;

	} else if (hCount == 1) {
		if (singleRBondCount == 2) {
			if (piSystemCount == 0)           // R-NH-R (pi = 0)
				return 43;

			if (piSystemCount == 2 && inRing) // R-NH-R (conj. ring)
				return 45;           

			return 44;                        // R-NH-R (pi > 0)
		}

		if (singleXBondCount >= 1) {
			if (piSystemCount != 2 || !inRing)
				return 46;                    // A-NH-X

			return 47;                        // A-NH-X (conj. ring)
		}

	} else if (hCount == 0) {
		if (singleRBondCount == 3) {
			if (piSystemCount == 0)           // NR3 (pi = 0)
				return 48;

			if (piSystemCount > 1 && inRing)  // NR3 (conj. ring)
				return 50;            

			return 49;                        // NR3 (pi > 0)
		}

		if ((singleXBondCount + singleRBondCount) == 3) {
			if (piSystemCount < 2 || !inRing)
				return 51;                    // NRnX3-n

			return 52;                        // NRnX3-n (conj. ring)
		}
	}

	return UNKNOWN_ATOM_TYPE;
}

unsigned int Chem::XLogPCalculator::AtomInfo::classifySP2NAtom() const
{
	if (hCount > 0 || doubleABondCount != 1)
		return UNKNOWN_ATOM_TYPE;

	if (doubleCBondCount == 1) {
		if (singleRBondCount == 1) {
			if (piSystemCount == 0)                             // C=N-R (pi = 0)
				return 58;

			if (piSystemCount == 1)                             // C=N-R (pi = 1)
				return 59;

		} else if (singleXBondCount == 1) {
			if (piSystemCount == 0)                             // C=N-X (pi = 0)
				return 60;

			if (piSystemCount == 1)                             // C=N-X (pi = 1)
				return 61;
		}

	} else if (doubleNBondCount == 1) {
		if (singleRBondCount == 1)                              // N=N-R
			return 62;

		if (singleXBondCount == 1)                              // N=N-X
			return 63;

	} else if (doubleOBondCount == 1 && singleABondCount == 1)  // A-N=O
		return 64;

	return UNKNOWN_ATOM_TYPE;
}

unsigned int Chem::XLogPCalculator::AtomInfo::classifyAmideNAtom() const
{
	if (hCount == 2)                                        // -NH2
		return 53;

	if (hCount == 1) {
		if (singleRBondCount == 2)                          // -NHR
			return 54;           

		if (singleRBondCount == 1 && singleXBondCount == 1) // -NHX
			return 55;

	} else if (hCount == 0) {
		if (singleRBondCount == 3)                          // -NR2
			return 56;

		if (singleRBondCount == 2 && singleXBondCount == 1) // -NRX
			return 57;
	}

	return UNKNOWN_ATOM_TYPE;
}

// Oxygen Classification

unsigned int Chem::XLogPCalculator::AtomInfo::classifyOAtom() const
{
	if (bondCount == 2) {
		if ((singleABondCount + hCount) == 2) 
			return classifySP3OAtom();

	} else if (bondCount == 1 && doubleABondCount == 1)     // sp2: A=O
		return 74;

	return UNKNOWN_ATOM_TYPE;
}

unsigned int Chem::XLogPCalculator::AtomInfo::classifySP3OAtom() const
{
	if (hCount == 1) {
		if (singleRBondCount == 1) {
			if (piSystemCount == 0)                         // R-OH (pi = 0)
				return 68;
 
			if (piSystemCount == 1)                         // R-OH (pi = 1)
				return 69;

		} else if (singleXBondCount == 1)                   // X-OH
			return 70;

	} else if (hCount == 0) {
		if (singleRBondCount == 2) {
			if (piSystemCount == 0)                         // R-O-R (pi = 0)
				return 71;

			return 72;                                      // R-O-R (pi > 0)
		}

		if (singleRBondCount == 1 && singleXBondCount == 1) // R-O-X
			return 73;
	}

	return UNKNOWN_ATOM_TYPE;
}

// Sulfur Classification

unsigned int Chem::XLogPCalculator::AtomInfo::classifySAtom() const
{
	switch (bondCount) {

		case 4:
			if (singleABondCount == 2 && doubleOBondCount == 2)  // A-SO2-A
				return 79;       

			return UNKNOWN_ATOM_TYPE;

		case 3:
			if (singleABondCount == 2 && doubleOBondCount == 1)  // A-SO-A
				return 78;       

			return UNKNOWN_ATOM_TYPE;

		case 2:
			if ((singleABondCount + hCount) == 2) {
				if (hCount == 1)                                 // sp3: A-SH
					return 75;     

				if (hCount == 0)                                 // sp3: A-S-A
					return 76; 
			}

			return UNKNOWN_ATOM_TYPE;

		case 1:
			if (doubleABondCount == 1)                           // sp2: A=S
				return 77;      

		default:
			return UNKNOWN_ATOM_TYPE;
	}
}

// Phosphorus Classification

unsigned int Chem::XLogPCalculator::AtomInfo::classifyPAtom() const
{
	if (bondCount == 4 && singleABondCount == 3) {
		if (doubleOBondCount == 1)  // O=PA3
			return 80;

		if (doubleSBondCount == 1)  // S=PA3
			return 81;
	}

	return UNKNOWN_ATOM_TYPE;
}

// Fluorine Classification

unsigned int Chem::XLogPCalculator::AtomInfo::classifyFAtom() const
{
	if (bondCount == 1) {
		if (piSystemCount == 0)   // -F (pi = 0)
			return 82;

		if (piSystemCount == 1)   // -F (pi = 1)
			return 83;
	}

	return UNKNOWN_ATOM_TYPE;
}

// Chlorine Classification

unsigned int Chem::XLogPCalculator::AtomInfo::classifyClAtom() const
{
	if (bondCount == 1) {
		if (piSystemCount == 0)   // -Cl (pi = 0)
			return 84;

		if (piSystemCount == 1)   // -Cl (pi = 1)
			return 85;
	}

	return UNKNOWN_ATOM_TYPE;
}

// Bromine Classification

unsigned int Chem::XLogPCalculator::AtomInfo::classifyBrAtom() const
{
	if (bondCount == 1) {
		if (piSystemCount == 0)   // -Br (pi = 0)
			return 86;

		if (piSystemCount == 1)   // -Br (pi = 1)
			return 87;
	}

	return UNKNOWN_ATOM_TYPE;
}

// Iodine Classification

unsigned int Chem::XLogPCalculator::AtomInfo::classifyIAtom() const
{
	if (bondCount == 1) {
		if (piSystemCount == 0)   // -I (pi = 0)
			return 88;

		if (piSystemCount == 1)   // -I (pi = 1)
			return 89;
	}

	return UNKNOWN_ATOM_TYPE;
}

void Chem::XLogPCalculator::AtomInfo::analyzeAtom(AtomInfoTable& atom_infos)
{
	if (analyzed)
		return;

	hCount           = getImplicitHydrogenCount(*atom);
	bondCount        = hCount;
	halogenCount     = 0;
	piSystemCount    = 0;
	singleRBondCount = 0;
	singleXBondCount = 0;
	singleOBondCount = 0;
	doubleRBondCount = 0;
	doubleXBondCount = 0;
	doubleCBondCount = 0; 
	doubleNBondCount = 0; 
	doubleOBondCount = 0; 
	doubleSBondCount = 0; 
	tripleABondCount = 0; 
	tripleCBondCount = 0; 
	tripleRBondCount = 0; 
	aromABondCount   = 0; 
	aromXBondCount   = 0; 
	aromCBondCount   = 0; 
	aromNBondCount   = 0; 
	hasAmideCNbr     = false;
	hasRingNbr       = false;

	std::size_t single_c_bnd_cnt = 0;
	std::size_t single_n_bnd_cnt = 0;

	Atom::ConstAtomIterator atoms_end = atom->getAtomsEnd();
	Atom::ConstBondIterator b_it = atom->getBondsBegin();
	
	for (Atom::ConstAtomIterator a_it = atom->getAtomsBegin(); a_it != atoms_end; ++a_it, ++b_it) {
		const Bond& bond = *b_it;

		if (!molGraph->containsAtom(*a_it) || !molGraph->containsBond(bond))
			continue;

		std::size_t nbr_atom_idx = molGraph->getAtomIndex(*a_it);
		AtomInfo& nbr_atom_info = atom_infos[nbr_atom_idx];

		hasRingNbr |= nbr_atom_info.inRing;

		switch (getOrder(bond)) {

			case 1:
				if (nbr_atom_info.isClassXAtom) {
					singleXBondCount++;
		
					if (nbr_atom_info.atomicNo == AtomType::O)
						singleOBondCount++;

					else 
						single_n_bnd_cnt++;

				} else if (nbr_atom_info.isClassRAtom) {
					singleRBondCount++;

					if (nbr_atom_info.atomicNo == AtomType::C) {
						if (atomicNo == AtomType::N)
							hasAmideCNbr |= nbr_atom_info.isAmideCarbon(atom_infos);
							
						single_c_bnd_cnt++;

					} else if (nbr_atom_info.isHalogenAtom) 
						halogenCount++;

				} else if (nbr_atom_info.atomicNo == AtomType::H)
					hCount++;

				if (nbr_atom_info.isAromatic || nbr_atom_info.isUnsaturated)
					piSystemCount++;

				break;

			case 2:
				if (nbr_atom_info.isClassXAtom) {
					doubleXBondCount++;

					if (nbr_atom_info.atomicNo == AtomType::O)
						doubleOBondCount++;
					
					else 
						doubleNBondCount++;

				} else if (nbr_atom_info.isClassRAtom) {
					doubleRBondCount++;

					if (nbr_atom_info.atomicNo == AtomType::S)
						doubleSBondCount++;

					else if (nbr_atom_info.atomicNo == AtomType::C)
						doubleCBondCount++;
				}

				break;

			case 3:
				if (nbr_atom_info.isClassRAtom) { 
					tripleRBondCount++;
					tripleABondCount++;

					if (nbr_atom_info.atomicNo == AtomType::C)
						tripleCBondCount++;

				} else if (nbr_atom_info.isClassAAtom)
					tripleABondCount++;
				
				break;

			default:
				break;
		}

		if (getAromaticityFlag(bond)) {
			if (nbr_atom_info.isClassXAtom) {
				aromXBondCount++;
				aromABondCount++;

				if (nbr_atom_info.atomicNo == AtomType::N) 
					aromNBondCount++; 

			} else if (nbr_atom_info.isClassAAtom) {
				aromABondCount++;

				if (nbr_atom_info.atomicNo == AtomType::C) 
					aromCBondCount++; 	
			}
		}

		bondCount++;
	}

	singleABondCount = singleRBondCount + singleXBondCount;
	doubleABondCount = doubleRBondCount + doubleXBondCount;

	isAmideCAtom = (atomicNo == AtomType::C && bondCount == 3 && doubleOBondCount == 1 
					&& single_n_bnd_cnt >= 1);

	if (atomicNo == AtomType::N) {
		isDonor = (bondCount == 3 && singleABondCount < 3 && hCount > 0);
		isAcceptor = (bondCount == 1 && tripleCBondCount == 1);

	} else if (atomicNo == AtomType::O) {
		isDonor = (bondCount == 2 && singleABondCount == 1 && hCount == 1);
		isAcceptor = (isDonor || (bondCount == 1 && doubleABondCount == 1));

	} else {
		isDonor = false;
		isAcceptor = false;
	}

	analyzed = true;
}

unsigned int Chem::XLogPCalculator::AtomInfo::getAtomType() const
{
	return atomType;
}

std::size_t Chem::XLogPCalculator::AtomInfo::getNumBonds() const
{
	return bondCount;
}

std::size_t Chem::XLogPCalculator::AtomInfo::getNumHalogenPairs() const
{
	if (halogenCount <= 1 || isUnsaturated)
		return 0;

	return ((halogenCount * (halogenCount - 1)) / 2);
}

unsigned int Chem::XLogPCalculator::AtomInfo::getAtomicNo() const
{
	return atomicNo;
}

void Chem::XLogPCalculator::AtomInfo::setUnsaturationFlag()
{
	isUnsaturated = true;
}

bool Chem::XLogPCalculator::AtomInfo::getUnsaturationFlag() const
{
	return isUnsaturated;
}

bool Chem::XLogPCalculator::AtomInfo::isRingAtom() const
{
	return inRing;
}

bool Chem::XLogPCalculator::AtomInfo::isAromaticAtom() const
{
	return isAromatic;
}

bool Chem::XLogPCalculator::AtomInfo::isHBondDonorAtom() const
{
	return isDonor;
}

bool Chem::XLogPCalculator::AtomInfo::isHBondAcceptorAtom() const
{
	return isAcceptor;
}

bool Chem::XLogPCalculator::AtomInfo::hasRingNeighbor() const
{
	return hasRingNbr;
}

bool Chem::XLogPCalculator::AtomInfo::isAmideCarbon(AtomInfoTable& atom_infos)
{
	analyzeAtom(atom_infos);

	return isAmideCAtom;
}
