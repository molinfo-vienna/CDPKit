/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * LogSCalculator.cpp 
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

#include <boost/bind.hpp>

#include "CDPL/Chem/LogSCalculator.hpp"
#include "CDPL/Chem/Atom.hpp"
#include "CDPL/Chem/Bond.hpp"
#include "CDPL/Chem/MolecularGraphFunctions.hpp"
#include "CDPL/Chem/BondFunctions.hpp"
#include "CDPL/Chem/AtomFunctions.hpp"
#include "CDPL/Chem/AtomType.hpp"
#include "CDPL/Math/VectorIterator.hpp"


namespace
{

	const std::size_t LOGS_OFFSET_INDEX    = 0;
	const std::size_t HYDROPHOBIC_C_INDEX  = 77;
	const std::size_t SQUARED_MW_INDEX     = 78;

	const unsigned int UNKNOWN_ATOM_TYPE   = 79;	

	const double REGRESSION_COEFFS[] = {
		-0.376348,
		0.491425,
		0.0243385,
		-0.219916,
		0.461234,
		0.120462,
		0.535382,
		0.0606046,
		-0.126279,
		-0.242554,
		0.308198,
		0.21453,
		0.0427422,
		0.156608,
		0.0856281,
		-0.109261,
		0.114046,
		-0.111933,
		-0.275089,
		-0.467752,
		-0.513873,
		0.161679,
		0.00285902,
		-0.141868,
		-0.219192,
		0.437756,
		-0.36074,
		-0.0454445,
		-0.242726,
		-0.0320181,
		-0.198365,
		0.127956,
		-0.00503451,
		0.17942,
		-0.783695,
		-0.414834,
		-0.21209,
		-0.661335,
		-0.290853,
		-0.764277,
		0.560622,
		0.480676,
		-0.312454,
		-0.181611,
		-0.120181,
		0.132187,
		-0.100615,
		-0.40896,
		0.0913582,
		-0.365258,
		0.432692,
		-0.0464361,
		-0.0354369,
		0.412064,
		-0.0926661,
		0.0919342,
		-0.476286,
		-0.00781926,
		0.327185,
		-0.0555695,
		-0.0827383,
		-0.234534,
		0.315073,
		0.174071,
		0.862449,
		-0.904607,
		-0.719789,
		0.0689605,
		-0.0809711,
		-0.110425,
		-0.40405,
		-0.373149,
		-0.367785,
		-0.173006,
		-0.609229,
		-0.762541,
		-0.224952,
		-0.22384,
		-6.24601e-06
	};
}


using namespace CDPL;


Chem::LogSCalculator::LogSCalculator(): featureVector(FEATURE_VECTOR_SIZE), logS(0.0) {}

Chem::LogSCalculator::LogSCalculator(const MolecularGraph& molgraph): featureVector(FEATURE_VECTOR_SIZE)
{
	calculate(molgraph);
}

double Chem::LogSCalculator::calculate(const MolecularGraph& molgraph) 
{
	init(molgraph);

	classifyAtoms();
	countAtomTypes();
	countHydrophicCarbons();
	calcLogS();

	return logS;
}

double Chem::LogSCalculator::getResult() const
{
	return logS;
}

const Math::DVector& Chem::LogSCalculator::getFeatureVector() const
{
	return featureVector;
}

void Chem::LogSCalculator::init(const MolecularGraph& molgraph)
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

	double mw = calcMass(molgraph);

	featureVector[LOGS_OFFSET_INDEX] = 1;
	featureVector[SQUARED_MW_INDEX] = mw * mw;
}

void Chem::LogSCalculator::classifyAtoms()
{
	std::for_each(atomInfos.begin(), atomInfos.end(),
				  boost::bind(&AtomInfo::analyzeAtom, _1, boost::ref(atomInfos)));

	std::for_each(atomInfos.begin(), atomInfos.end(),
				  boost::bind(&AtomInfo::classifyAtom, _1, boost::ref(atomInfos)));
}

void Chem::LogSCalculator::countAtomTypes()
{
	AtomInfoTable::const_iterator infos_end = atomInfos.end();

	for (AtomInfoTable::const_iterator it = atomInfos.begin(); it != infos_end; ++it) {
		unsigned int atom_type = it->getAtomType();

		if (atom_type != UNKNOWN_ATOM_TYPE)
			featureVector[atom_type]++;	
	}	
}

void Chem::LogSCalculator::countHydrophicCarbons()
{
	const Math::ULMatrix& dist_mtx = *getTopologicalDistanceMatrix(*molGraph);

	for (std::size_t i = 0; i < numAtoms; i++) {
		const AtomInfo& atom_info = atomInfos[i];

		if (atom_info.getAtomicNo() != AtomType::C || atom_info.getNumBonds() < 3 || atom_info.isAromaticAtom()
			|| (atom_info.getNumBonds() == 3 && atom_info.isRingAtom()))
			continue;

		bool hydrophobic = true;

		for (std::size_t j = 0; j < numAtoms && hydrophobic; j++) {
			if (i == j)
				continue;

			switch (atomInfos[j].getAtomicNo()) {

				case AtomType::C:
				case AtomType::H:
					continue;

				default:
					if (dist_mtx(i, j) < 4)
						hydrophobic = false;
					continue;
			}
		}

		if (hydrophobic)
			featureVector[HYDROPHOBIC_C_INDEX]++;
	}
}

void Chem::LogSCalculator::calcLogS()
{
	logS = std::inner_product(Math::vectorBegin(featureVector), Math::vectorEnd(featureVector), REGRESSION_COEFFS, 0.0);
}


Chem::LogSCalculator::AtomInfo::AtomInfo(const MolecularGraph& molgraph, const Atom& atm, bool aromatic, bool in_ring): 
	molGraph(&molgraph), atom(&atm), isAromatic(aromatic), inRing(in_ring)
{
	atomicNo = getType(atm);

	isHalogenAtom = (atomicNo == AtomType::F || atomicNo == AtomType::Cl 
					 || atomicNo == AtomType::Br || atomicNo == AtomType::I);
}

unsigned int Chem::LogSCalculator::AtomInfo::getAtomType() const
{
	return atomType;
}

std::size_t Chem::LogSCalculator::AtomInfo::getNumBonds() const
{
	return bondCount;
}

unsigned int Chem::LogSCalculator::AtomInfo::getAtomicNo() const
{
	return atomicNo;
}

bool Chem::LogSCalculator::AtomInfo::isRingAtom() const
{
	return inRing;
}

bool Chem::LogSCalculator::AtomInfo::isAromaticAtom() const
{
	return isAromatic;
}

void Chem::LogSCalculator::AtomInfo::analyzeAtom(const AtomInfoTable& atom_infos)
{
	hCount                  = getImplicitHydrogenCount(*atom);
	bondCount               = hCount;
	bSArAHalCount           = 0;
	bSArAAnyCount           = 0;
	bSArAArCCount           = 0;
	bSArAAlCCount           = 0;
	bSArAAlOCount           = 0;
	bSArACCount             = 0;
	bSArAAlPCount           = 0;
	bSAAlOX1Count           = 0;
	bDAAlCCount             = 0; 
	bDACCount               = 0; 
	bDAAnyCount             = 0; 
	bDAAlOX1Count           = 0; 
	bDANOCount              = 0;
	bTAAnyCount             = 0; 
	bAnyAAnyCount           = 0; 
	bAnyAAnyNonCCount       = 0; 
	bAnyAAnyArNonCCount     = 0; 
	bAnyANonCNonFNonClCount = 0;
	bAnyAArCCount           = 0; 
	bAnyAAlCCount           = 0; 
	bAnyAArNCount           = 0; 
	bAnyAAlPCount           = 0;
	bAnyAAlSCount           = 0;
	bAnyANOCount            = 0;

	Atom::ConstAtomIterator atoms_end = atom->getAtomsEnd();
	Atom::ConstBondIterator b_it = atom->getBondsBegin();
	
	for (Atom::ConstAtomIterator a_it = atom->getAtomsBegin(); a_it != atoms_end; ++a_it, ++b_it) {
		const Bond& bond = *b_it;

		if (!molGraph->containsAtom(*a_it) || !molGraph->containsBond(bond))
			continue;

		std::size_t nbr_atom_idx = molGraph->getAtomIndex(*a_it);
		std::size_t bond_order = getOrder(bond);
		bool arom_bond = getAromaticityFlag(bond);

		bondCount++;

		const AtomInfo& nbr_atom_info = atom_infos[nbr_atom_idx];
	
		switch (nbr_atom_info.atomicNo) {
			
			case AtomType::H:
				hCount++;
				break;

			case AtomType::C:
				if (nbr_atom_info.isAromatic) {
					if (bond_order == 1 || arom_bond) {
						bSArAArCCount++;	
						bSArACCount++;	
					}

					bAnyAArCCount++;

				} else {
					if (bond_order == 1 || arom_bond) {
						bSArAAlCCount++;
						bSArACCount++;	
					}

					if (bond_order == 2)
						bDAAlCCount++;

					bAnyAAlCCount++;
				}

				if (bond_order == 2)
					bDACCount++;
	
				break;

			case AtomType::N:
				if (nbr_atom_info.isAromatic)
					bAnyAArNCount++; 
				
				if (bond_order == 2)
					bDANOCount++;

				bAnyANOCount++;

				break;

			case AtomType::O:
				if (!nbr_atom_info.isAromatic) {
					if (bond_order == 2) 
						bDAAlOX1Count++;

					else if (bond_order == 1) {
						bSAAlOX1Count++;
						bSArAAlOCount++;

					} else if (arom_bond)
						bSArAAlOCount++;
				}

				if (bond_order == 2) 
					bDANOCount++;

				bAnyANOCount++;

				break;

			case AtomType::S:
				if (!nbr_atom_info.isAromatic)
					bAnyAAlSCount++;

				break;

			case AtomType::P:
				if (!nbr_atom_info.isAromatic) {
					bAnyAAlPCount++;

					if (bond_order == 1 || arom_bond) 
						bSArAAlPCount++;	
				}

				break;

			default:
				break;
		}

		if (bond_order == 1 || arom_bond) {
			if (nbr_atom_info.atomicNo != AtomType::H) {
				bSArAAnyCount++;

				if (nbr_atom_info.isHalogenAtom) 
					bSArAHalCount++;
			}
		}

		if (nbr_atom_info.atomicNo != AtomType::H) {
			if (bond_order == 2)
				bDAAnyCount++;

			else if (bond_order == 3)
				bTAAnyCount++;

			bAnyAAnyCount++;
		}

		if (nbr_atom_info.atomicNo != AtomType::C) {
			if (nbr_atom_info.isAromatic) 
				bAnyAAnyArNonCCount++;

			if (nbr_atom_info.atomicNo != AtomType::F && nbr_atom_info.atomicNo != AtomType::Cl)
				bAnyANonCNonFNonClCount++;

			bAnyAAnyNonCCount++;
		}
	}
}

void Chem::LogSCalculator::AtomInfo::classifyAtom(const AtomInfoTable& atom_infos)
{
	switch (atomicNo) {

		case AtomType::C:
			atomType = classifyCAtom(atom_infos);
			break;

		case AtomType::N:
			atomType = classifyNAtom(atom_infos);
			break;

		case AtomType::O:
			atomType = classifyOAtom(atom_infos);
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

unsigned int Chem::LogSCalculator::AtomInfo::classifyCAtom(const AtomInfoTable& atom_infos) const
{
	if (isAromatic) {
		if (hCount == 0) {
			if (bAnyAAnyNonCCount >= 3 && bAnyAAnyArNonCCount >= 2) // [c;H0](~[!#6])(~[a;!c])~[a;!c]
				return 34;

			if (bAnyAAnyArNonCCount >= 2)                           // [c;H0](~[a;!c])~[a;!c]
				return 33;

			if (getBAnyACX4HalCount(atom_infos) >= 1) {
				if (bAnyAArCCount >= 2)                             // [c;H0](~[CX4,F,Cl,Br,I])(~c)~c
					return 36;

				if (bAnyAArCCount >= 1 && bAnyAAnyArNonCCount >= 1) // [c;H0](~[CX4,F,Cl,Br,I])(~c)~[a;!c]
					return 36;
			}

			if (bAnyAArCCount >= 2                                  // [c;H0](~[!#6;!F;!Cl])(~c)~c
				&& bAnyANonCNonFNonClCount >= 1)
				return 38;

			if (bAnyAArCCount >= 3)                                 // [c;H0](~c)(~[c])~[c]
				return 37;

			if (bAnyAAnyNonCCount >= 2 && bAnyAArCCount >= 1        // [c;H0](~[!#6])(~c)~[a;!c]
				&& bAnyAAnyArNonCCount >= 1)
				return 39;

			if (bAnyAAlCCount >= 1 && bAnyAArCCount >= 1 && bAnyAAnyArNonCCount >= 1)  // [c;H0](~C)(~[c])~[a;!c]
				return 35;

			if (bAnyAAnyCount >= 3 && bAnyAArCCount >= 2)           // [c;H0](~*)(~[c])~[c]
				return 35;

		} else if (hCount == 1) {
			if (bAnyAAnyArNonCCount >= 2)                           // [c;H1](~[a;!c])~[a;!c]
				return 32;

			if (bAnyAArCCount >=1 && bAnyAAnyArNonCCount >= 1)      // [c;H1](~c)~[a;!c]
				return 31;

			if (bAnyAArCCount >= 2) {
				if (in6Ring())                                      // [c;H1;r6](~c)~c
					return 30;

				return 29;                                          // [c;H1](~c)~c
			}
		} 

	} else if (bondCount == 4) {
		if (hCount == 4)                                            // [CX4;H4]
			return 1;

		if (hCount == 3) {
			if (hasBSArACX4cHalBAnyANONbr(atom_infos))              // [CX4;H3][CX4,c,F,Cl,Br,I]~[#7,#8]
				return 5;

			if (hasBSArACX3cHalBDANONbr(atom_infos))                // [CX4;H3][CX3,c,F,Cl,Br,I]=[#7,#8]
				return 4;

			if (getBSArACX4cHalCount(atom_infos) >= 1)              // [CX4;H3][CX4,c,F,Cl,Br,I]
				return 3;

			if (bSArACCount >= 1)                                   // [CX4;H3][#6]
				return 2;

			return 1;                                               // [CX4;H3]
		}

		if (hCount == 2) {
			if (hasBSAOHNH2NHNbr(atom_infos))                       // [CX4;H2]-[OH,NH2,NH]
				return 13;

			if (hasBSArACX4cHalBAnyANONbr(atom_infos)) {
				if (getBSArACX4cHalCount(atom_infos) >= 2)          // [CX4;H2]([CX4,c,F,Cl,Br,I])[CX4,c,F,Cl,Br,I]~[#7,#8]
					return 12; 

				return 11;                                          // [CX4;H2][CX4,c,F,Cl,Br,I]~[#7,#8]
			}

			if (getBSArAAnyCX4cHalCount(atom_infos) >= 2)           // [CX4;H2]([#6X4,c,F,Cl,Br,I])[#6X4,c,F,Cl,Br,I]
				return 9;

			if (hasBSArAAnyCBDANONbr(atom_infos))                   // [CX4;H2][#6]=[#7,#8]
				return 10;

			if (bSArACCount >= 2)                                   // [CX4;H2]([#6])[#6]
				return 8;

			if (bSArACCount >= 1)                                   // [CX4;H2][#6]
				return 7;

			return 6;                                               // [CX4;H2]
		}

		if (hCount == 1) {
			if (getBSArAAnyCX4cHalCount(atom_infos) >= 3)           // [CX4;H1]([#6X4,c,F,Cl,Br,I])([#6X4,c,F,Cl,Br,I])[#6X4,c,F,Cl,Br,I]
				return 17;

			if (hasBSAOHNH2NHNbr(atom_infos))                       // [CX4;H0]-[OH,NH2,NH]
				return 18;

			if (bSArACCount >= 3)                                   // [CX4;H1]([#6])([#6])[#6]
				return 16;

			if (bSArACCount >= 2)                                   // [CX4;H1]([#6])[#6]
				return 15;

			return 14;                                              // [CX4;H1]
		}

		if (hCount == 0) {
			if (bSArACCount > 3)                                    // [CX4;H0]([#6])([#6])([#6])[#6] or [CX4;H0]([#6X4,c])([#6X4,c])([#6X4,c])[#6]
				return 21;                                          // or [CX4;H0]([#6X4,c])([#6X4,c])([#6X4,c])[#6X4,c]

			if (bSArACCount <= 2)                                   // [CX4;H0] or [CX4;H0][#6]  or [CX4;H0]([#6])[#6]
				return 19;

			return 20;                                              // [CX4;H0]([#6])([#6])[#6]
		}

	} else {
		if (bDAAlCCount >= 2 || bTAAnyCount >= 1)                   // C#* or C(=C)=C
			return 28;

		if (inRing && bDAAlOX1Count >= 1)                           // [C;r]=O
			return 27;

		if (hCount == 0) {
			if (bDAAlOX1Count >= 1)                                 // [C;H0]=O
				return 26;

			if (bDAAnyCount >= 1)                                   // [C;H0]=*
				return 24;

		} else if (hCount == 1) {
			if (bDAAlOX1Count >= 1)                                 // [C;H1]=O
				return 25;

			if (bDAAnyCount >= 1)                                   // [C;H1]=*
				return 23;

		} else if (hCount == 2 && bDAAnyCount >= 1)                 // [C;H2]=*
			return 22;
	}

	return UNKNOWN_ATOM_TYPE;
}

// Nitrogen Classification

unsigned int Chem::LogSCalculator::AtomInfo::classifyNAtom(const AtomInfoTable& atom_infos) const
{
	if (isAromatic) {
		if (bAnyAArNCount >= 1 || hasBAnyAAnyBAnyAArNNbr(atom_infos)) // [n]~[n] or [n]~[*]~[n]
			return 59;			

		if (hCount == 1)                                               // [nH]
			return 60;

		return 58;                                                     // [n]
	}

	if (bondCount == 3                                                 // [NX3](O)=O or [NX3](O)-O
		&& ((bSArAAlOCount >= 1 && bDAAlOX1Count >= 1) || (bSAAlOX1Count >= 1 && bSArAAlOCount >= 2)))
		return 63;

	if (bTAAnyCount >= 1 || bDAAnyCount >= 2)                          // N#* or N(=*)=*
		return 62;

	if (bDAAnyCount >= 1)                                              // N(=*)
		return 61;

	if (hCount == 0) {
		std::size_t num_sp3_c_nbrs = getBSArACX4Count(atom_infos);

		if (num_sp3_c_nbrs <= 2) {
			if (num_sp3_c_nbrs > 0)                                    // [N;H0]([#6X4]) or [N;H0]([#6X4])[#6X4]
				return 56;

			return 55;                                                 // [N;H0]

		} 
			
		if (inRing)
			return 57;                                                 // [N;H0;r]([#6X4])([#6X4])[#6X4]

		return 56;                                                     // [N;H0]([#6X4])([#6X4])[#6X4]
	}

	if (hCount == 1) {
		std::size_t num_sp3_c_nbrs = getBSArACX4Count(atom_infos);

		if (num_sp3_c_nbrs == 1)                                       // [N;H1]([#6X4])
			return 52;

		if (num_sp3_c_nbrs >= 2)                                       // [N;H1]([#6X4])[#6X4]
			return 53;

		if (inRing)                                                    // [N;H1;r]
			return 54; 

		return 51;                                                     // [N;H1]
	}

	if (hCount == 2)                                                   // [N;H2] or [N;H2][C]
		return 50;

	return UNKNOWN_ATOM_TYPE;
}

// Oxygen Classification

unsigned int Chem::LogSCalculator::AtomInfo::classifyOAtom(const AtomInfoTable& atom_infos) const
{
	if (has2PropyleneNbr(atom_infos))                               // [#8]=C([#6])[#6] or [#8]=c([#6])[#6]
		return 46;

	if (bDACCount >= 1)                                             // [#8]=C or [#8]=c
		return 45;

	if (isAromatic)                                                 // [o]
		return 47;

	if (bondCount == 1 && (bAnyAAlPCount + bAnyAAlSCount) >= 1)     // [OX1]~P or OX1]~S
		return  48;

	if (bondCount == 2 && bSArAAlPCount >= 1 && bSArAAnyCount == 2) // [OX2](*)[P]
		return 49;

	if (hCount == 1) {
		if (bSArAAlCCount >= 1)                                     // [#8;H1]C
			return 41;

		return 40;                                                  // [#8;H1]
	}

	if (hCount == 0) {
		if (hasCarbonylCNbr(atom_infos))                            // [#8;H0]C=O
			return 43;

		if (getBSArACX4Count(atom_infos) >= 2)                      // [#8;H0]([#6X4])[#6X4]
			return 44;

		return 42;                                                  // [#8;H0]
	}

	return UNKNOWN_ATOM_TYPE;
}

// Sulfur Classification

unsigned int Chem::LogSCalculator::AtomInfo::classifySAtom() const
{
	if (bondCount == 3 && (bDAAlOX1Count >= 1 || bSAAlOX1Count >= 1)) // [SX3]=[OX1] or [SX3]-[OX1]
		return 67;

	if (bondCount == 4 && (bDAAlOX1Count >= 2 || bSAAlOX1Count >= 2)) // [SX4](=[OX1])=[OX1] or [SX3](-[OX1])-[OX1]
		return 67;

	if ((inRing && hCount == 0) || isAromatic)                        // s or [S;H0]1*=**=*1 or [S;H0]1*:**:*1 or [S;H0]1*=**:*1 
		return 66;                                                    // or [S;H0]1*=*~*~*=*1 or [S;H0]1*:*~*~*:*1 or [S;H0]1*=*~*~*:*1

	if (hCount == 1)                                                  // [S;H1]
		return 64;

	if (hCount == 0)                                                  // [S;H0]
		return 65;

	return UNKNOWN_ATOM_TYPE;
}

// Phosphorus Classification

unsigned int Chem::LogSCalculator::AtomInfo::classifyPAtom() const
{
	if (bondCount == 3 || bondCount == 4)  // [PX3] or [PX4]
		return 68;

	return UNKNOWN_ATOM_TYPE;
}

// Fluorine Classification

unsigned int Chem::LogSCalculator::AtomInfo::classifyFAtom() const
{
	if (bondCount == 1) {
		if (bSArAArCCount == 0)   // [F]
			return 69;
		
		return 73;                // [F]c
	}

	return UNKNOWN_ATOM_TYPE;
}

// Chlorine Classification

unsigned int Chem::LogSCalculator::AtomInfo::classifyClAtom() const
{
	if (bondCount == 1) {
		if (bSArAArCCount == 0)   // [Cl]
			return 70;
		
		return 74;                // [Cl]c
	}

	return UNKNOWN_ATOM_TYPE;
}

// Bromine Classification

unsigned int Chem::LogSCalculator::AtomInfo::classifyBrAtom() const
{
	if (bondCount == 1) {
		if (bSArAArCCount == 0)   // [Br]
			return 71;
		
		return 75;                // [Br]c
	}

	return UNKNOWN_ATOM_TYPE;
}

// Iodine Classification

unsigned int Chem::LogSCalculator::AtomInfo::classifyIAtom() const
{
	if (bondCount == 1) {
		if (bSArAArCCount == 0)   // [I]
			return 72;
		
		return 76;                // [I]c
	}

	return UNKNOWN_ATOM_TYPE;
}

bool Chem::LogSCalculator::AtomInfo::hasCarbonylCNbr(const AtomInfoTable& atom_infos) const
{
	Atom::ConstAtomIterator atoms_end = atom->getAtomsEnd();
	Atom::ConstBondIterator b_it = atom->getBondsBegin();
	
	for (Atom::ConstAtomIterator a_it = atom->getAtomsBegin(); a_it != atoms_end; ++a_it, ++b_it) {
		if (!molGraph->containsAtom(*a_it) || !molGraph->containsBond(*b_it))
			continue;

		const AtomInfo& nbr_atom_info = atom_infos[molGraph->getAtomIndex(*a_it)];

		if (nbr_atom_info.atomicNo == AtomType::C && !nbr_atom_info.isAromatic && nbr_atom_info.bDAAlOX1Count >= 1)
			return true;
	}

	return false;
}

bool Chem::LogSCalculator::AtomInfo::has2PropyleneNbr(const AtomInfoTable& atom_infos) const
{
	Atom::ConstAtomIterator atoms_end = atom->getAtomsEnd();
	Atom::ConstBondIterator b_it = atom->getBondsBegin();

	for (Atom::ConstAtomIterator a_it = atom->getAtomsBegin(); a_it != atoms_end; ++a_it, ++b_it) {
		if (!molGraph->containsAtom(*a_it) || !molGraph->containsBond(*b_it))
			continue;

		const AtomInfo& nbr_atom_info = atom_infos[molGraph->getAtomIndex(*a_it)];

		if (nbr_atom_info.atomicNo == AtomType::C && getOrder(*b_it) == 2 
			&& nbr_atom_info.bSArACCount >= 2)
			return true;
	}

	return false;
}

bool Chem::LogSCalculator::AtomInfo::hasBAnyAAnyBAnyAArNNbr(const AtomInfoTable& atom_infos) const
{
	Atom::ConstAtomIterator atoms_end = atom->getAtomsEnd();
	Atom::ConstBondIterator b_it = atom->getBondsBegin();

	for (Atom::ConstAtomIterator a_it = atom->getAtomsBegin(); a_it != atoms_end; ++a_it, ++b_it) {
		if (!molGraph->containsAtom(*a_it) || !molGraph->containsBond(*b_it))
			continue;

		if (atom_infos[molGraph->getAtomIndex(*a_it)].bAnyAArNCount >= 2)
			return true;
	}

	return false;
}

bool Chem::LogSCalculator::AtomInfo::hasBSArACX3cHalBDANONbr(const AtomInfoTable& atom_infos) const
{
	Atom::ConstAtomIterator atoms_end = atom->getAtomsEnd();
	Atom::ConstBondIterator b_it = atom->getBondsBegin();

	for (Atom::ConstAtomIterator a_it = atom->getAtomsBegin(); a_it != atoms_end; ++a_it, ++b_it) {
		if (!molGraph->containsAtom(*a_it) || !molGraph->containsBond(*b_it))
			continue;

		const AtomInfo& nbr_atom_info = atom_infos[molGraph->getAtomIndex(*a_it)];

		if (nbr_atom_info.isHalogenAtom ||
			(nbr_atom_info.atomicNo == AtomType::C && 
			 ((!nbr_atom_info.isAromatic && nbr_atom_info.bondCount == 3) || nbr_atom_info.isAromatic))) {
			const Bond& bond = *b_it;

			if (nbr_atom_info.bDANOCount >= 1 && (getAromaticityFlag(bond) || getOrder(bond) == 1))
				return true;
		}
	}

	return false;
}

bool Chem::LogSCalculator::AtomInfo::hasBSArACX4cHalBAnyANONbr(const AtomInfoTable& atom_infos) const
{
	Atom::ConstAtomIterator atoms_end = atom->getAtomsEnd();
	Atom::ConstBondIterator b_it = atom->getBondsBegin();

	for (Atom::ConstAtomIterator a_it = atom->getAtomsBegin(); a_it != atoms_end; ++a_it, ++b_it) {
		if (!molGraph->containsAtom(*a_it) || !molGraph->containsBond(*b_it))
			continue;

		const AtomInfo& nbr_atom_info = atom_infos[molGraph->getAtomIndex(*a_it)];

		if (nbr_atom_info.isHalogenAtom || 
			(nbr_atom_info.atomicNo == AtomType::C &&
			 ((!nbr_atom_info.isAromatic && nbr_atom_info.bondCount == 4) || nbr_atom_info.isAromatic))) {
			const Bond& bond = *b_it;

			if (nbr_atom_info.bAnyANOCount >= 1 && (getAromaticityFlag(bond) || getOrder(bond) == 1))
				return true;
		}
	}

	return false;
}

bool Chem::LogSCalculator::AtomInfo::hasBSArAAnyCBDANONbr(const AtomInfoTable& atom_infos) const
{
	Atom::ConstAtomIterator atoms_end = atom->getAtomsEnd();
	Atom::ConstBondIterator b_it = atom->getBondsBegin();

	for (Atom::ConstAtomIterator a_it = atom->getAtomsBegin(); a_it != atoms_end; ++a_it, ++b_it) {
		if (!molGraph->containsAtom(*a_it) || !molGraph->containsBond(*b_it))
			continue;

		const AtomInfo& nbr_atom_info = atom_infos[molGraph->getAtomIndex(*a_it)];

		if (nbr_atom_info.atomicNo == AtomType::C && nbr_atom_info.bDANOCount >= 1) {
			const Bond& bond = *b_it;

			if (getAromaticityFlag(bond) || getOrder(bond) == 1)
				return true;
		}
	}

	return false;
}

bool Chem::LogSCalculator::AtomInfo::hasBSAOHNH2NHNbr(const AtomInfoTable& atom_infos) const
{
	Atom::ConstAtomIterator atoms_end = atom->getAtomsEnd();
	Atom::ConstBondIterator b_it = atom->getBondsBegin();

	for (Atom::ConstAtomIterator a_it = atom->getAtomsBegin(); a_it != atoms_end; ++a_it, ++b_it) {
		if (!molGraph->containsAtom(*a_it) || !molGraph->containsBond(*b_it))
			continue;

		const AtomInfo& nbr_atom_info = atom_infos[molGraph->getAtomIndex(*a_it)];

		if (!nbr_atom_info.isAromatic && 
			((nbr_atom_info.atomicNo == AtomType::O && nbr_atom_info.hCount == 1) || 
			 (nbr_atom_info.atomicNo == AtomType::N && nbr_atom_info.hCount >= 1)) &&
			getOrder(*b_it) == 1) 
			return true;
	}

	return false;
}

bool Chem::LogSCalculator::AtomInfo::in6Ring() const
{
	return isInFragmentOfSize(*atom, *getSSSR(*molGraph), 6);
}

std::size_t Chem::LogSCalculator::AtomInfo::getBSArACX4Count(const AtomInfoTable& atom_infos) const
{
	std::size_t count = 0;

	Atom::ConstAtomIterator atoms_end = atom->getAtomsEnd();
	Atom::ConstBondIterator b_it = atom->getBondsBegin();

	for (Atom::ConstAtomIterator a_it = atom->getAtomsBegin(); a_it != atoms_end; ++a_it, ++b_it) {
		if (!molGraph->containsAtom(*a_it) || !molGraph->containsBond(*b_it))
			continue;

		const AtomInfo& nbr_atom_info = atom_infos[molGraph->getAtomIndex(*a_it)];

		if (nbr_atom_info.atomicNo != AtomType::C || nbr_atom_info.bondCount != 4)
			continue;

		const Bond& bond = *b_it;

		if (getAromaticityFlag(bond) || getOrder(bond) == 1)
			count++;
	}

	return count;
}

std::size_t Chem::LogSCalculator::AtomInfo::getBAnyACX4HalCount(const AtomInfoTable& atom_infos) const
{
	std::size_t count = 0;

	Atom::ConstAtomIterator atoms_end = atom->getAtomsEnd();
	Atom::ConstBondIterator b_it = atom->getBondsBegin();

	for (Atom::ConstAtomIterator a_it = atom->getAtomsBegin(); a_it != atoms_end; ++a_it, ++b_it) {
		if (!molGraph->containsAtom(*a_it) || !molGraph->containsBond(*b_it))
			continue;

		const AtomInfo& nbr_atom_info = atom_infos[molGraph->getAtomIndex(*a_it)];

		if (nbr_atom_info.isHalogenAtom || 
			(nbr_atom_info.atomicNo == AtomType::C && !nbr_atom_info.isAromatic && nbr_atom_info.bondCount == 4))
			count++;
	}

	return count;
}

std::size_t Chem::LogSCalculator::AtomInfo::getBSArACX4cHalCount(const AtomInfoTable& atom_infos) const
{
	std::size_t count = 0;

	Atom::ConstAtomIterator atoms_end = atom->getAtomsEnd();
	Atom::ConstBondIterator b_it = atom->getBondsBegin();

	for (Atom::ConstAtomIterator a_it = atom->getAtomsBegin(); a_it != atoms_end; ++a_it, ++b_it) {
		if (!molGraph->containsAtom(*a_it) || !molGraph->containsBond(*b_it))
			continue;

		const AtomInfo& nbr_atom_info = atom_infos[molGraph->getAtomIndex(*a_it)];

		if (nbr_atom_info.isHalogenAtom || 
			(nbr_atom_info.atomicNo == AtomType::C && 
			 ((!nbr_atom_info.isAromatic && nbr_atom_info.bondCount == 4) || nbr_atom_info.isAromatic))) {
			const Bond& bond = *b_it;

			if (getAromaticityFlag(bond) || getOrder(bond) == 1)
				count++;
		}
	}

	return count;
}

std::size_t Chem::LogSCalculator::AtomInfo::getBSArAAnyCX4cHalCount(const AtomInfoTable& atom_infos) const
{
	std::size_t count = 0;

	Atom::ConstAtomIterator atoms_end = atom->getAtomsEnd();
	Atom::ConstBondIterator b_it = atom->getBondsBegin();

	for (Atom::ConstAtomIterator a_it = atom->getAtomsBegin(); a_it != atoms_end; ++a_it, ++b_it) {
		if (!molGraph->containsAtom(*a_it) || !molGraph->containsBond(*b_it))
			continue;

		const AtomInfo& nbr_atom_info = atom_infos[molGraph->getAtomIndex(*a_it)];

		if (nbr_atom_info.isHalogenAtom || (nbr_atom_info.atomicNo == AtomType::C && 
											(nbr_atom_info.bondCount == 4 || nbr_atom_info.isAromatic))) {
			const Bond& bond = *b_it;

			if (getAromaticityFlag(bond) || getOrder(bond) == 1)
				count++;
		}
	}

	return count;
}
