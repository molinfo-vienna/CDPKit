/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * AtomSybylTypeFunctions.cpp 
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

#include "CDPL/Chem/AtomFunctions.hpp"
#include "CDPL/Chem/BondFunctions.hpp"
#include "CDPL/Chem/Atom.hpp"
#include "CDPL/Chem/Bond.hpp"
#include "CDPL/Chem/AtomType.hpp"
#include "CDPL/Chem/SybylAtomType.hpp"
#include "CDPL/Chem/HybridizationState.hpp"


using namespace CDPL; 


namespace
{

	bool isGuanidineCarbon(const Chem::Atom& atom, const Chem::MolecularGraph& molgraph)
	{
		if (getBondCount(atom, molgraph) != 3)
			return false;

		if (getBondCount(atom, molgraph, 1, Chem::AtomType::N) != 3)
			return false;

		return true;
	}

	bool isAmideNitrogen(const Chem::Atom& atom, const Chem::MolecularGraph& molgraph)
	{
		if (getBondCount(atom, molgraph) != 3)
			return false;

		if ((getBondCount(atom, molgraph, 1, Chem::AtomType::C) + getBondCount(atom, molgraph, 1, Chem::AtomType::H)) != 3)
			return false;

		for (std::size_t i = 0; i < atom.getNumBonds(); i++) {
			const Chem::Atom& nbr_atom = atom.getAtom(i);

			if (getType(nbr_atom) != Chem::AtomType::C)
				continue;

			if (getBondCount(nbr_atom, molgraph) != 3)
				continue;

			if (getBondCount(nbr_atom, molgraph, 1, Chem::AtomType::N) != 1)
				continue;

			if (getBondCount(nbr_atom, molgraph, 2, Chem::AtomType::O) != 1)
				continue;

			if (getBondCount(nbr_atom, molgraph, 1, Chem::AtomType::H) == 1 ||
				getBondCount(nbr_atom, molgraph, 1, Chem::AtomType::C) == 1)
				return true;
		}

		return false;
	}

	bool isPlanarNitrogen(const Chem::Atom& atom, const Chem::MolecularGraph& molgraph)
	{
		if (getBondCount(atom, molgraph) != 3)
			return false;

		if (getBondCount(atom, molgraph, 1) != 2)
			return false;
	
		if (getBondCount(atom, molgraph, 2) != 1)
			return false;

		return true;
	}

	bool isCarboxylateOxygen(const Chem::Atom& atom, const Chem::MolecularGraph& molgraph)
	{
		std::size_t bond_cnt = getBondCount(atom, molgraph);

		if (bond_cnt < 1 || bond_cnt > 2)
			return false;

		if (bond_cnt == 2 && (getBondCount(atom, molgraph, 1, Chem::AtomType::MH, false) != 1))
			return false;

		for (std::size_t i = 0; i < atom.getNumBonds(); i++) {
			const Chem::Atom& nbr_atom = atom.getAtom(i);

			if (getType(nbr_atom) != Chem::AtomType::C)
				continue;

			if (getBondCount(nbr_atom, molgraph) != 3)
				continue;

			if (getBondCount(nbr_atom, molgraph, 1, Chem::AtomType::O) != 1)
				continue;

			if (getBondCount(nbr_atom, molgraph, 2, Chem::AtomType::O) != 1)
				continue;

			if (getBondCount(nbr_atom, molgraph, 1, Chem::AtomType::H) == 1 ||
				getBondCount(nbr_atom, molgraph, 1, Chem::AtomType::C) == 1)
				return true;
		}

		return false;
	}

	bool isPhosphateOxygen(const Chem::Atom& atom, const Chem::MolecularGraph& molgraph)
	{
		std::size_t bond_cnt = getBondCount(atom, molgraph);

		if (bond_cnt < 1 || bond_cnt > 2)
			return false;

		if (bond_cnt == 2 && (getBondCount(atom, molgraph, 1, Chem::AtomType::MH, false) != 1))
			return false;

		for (std::size_t i = 0; i < atom.getNumBonds(); i++) {
			const Chem::Atom& nbr_atom = atom.getAtom(i);

			if (getType(nbr_atom) != Chem::AtomType::P)
				continue;

			if (getBondCount(nbr_atom, molgraph) != 4)
				continue;

			if (getBondCount(nbr_atom, molgraph, 1, Chem::AtomType::O) != 3)
				continue;

			if (getBondCount(nbr_atom, molgraph, 2, Chem::AtomType::O) == 1)
				return true;
		}

		return false;
	}

	bool isSulfoxideSulfur(const Chem::Atom& atom, const Chem::MolecularGraph& molgraph)
	{
		if (getBondCount(atom, molgraph) != 3)
			return false;

		if (getBondCount(atom, molgraph, 2, Chem::AtomType::O) != 1)
			return false;

		if (getBondCount(atom, molgraph, 1, Chem::AtomType::C) != 2)
			return false;

		return true;
	}

	bool isSulfoneSulfur(const Chem::Atom& atom, const Chem::MolecularGraph& molgraph)
	{
		if (getBondCount(atom, molgraph) != 4)
			return false;

		if (getBondCount(atom, molgraph, 2, Chem::AtomType::O) != 2)
			return false;

		if (getBondCount(atom, molgraph, 1, Chem::AtomType::C) != 2)
			return false;

		return true;
	}
}


unsigned int Chem::sybylToAtomType(unsigned int sybyl_type)
{
	switch (sybyl_type) {

		case SybylAtomType::C_3:
	    case SybylAtomType::C_2:
	    case SybylAtomType::C_1:
	    case SybylAtomType::C_ar:
	    case SybylAtomType::C_cat:
	    case SybylAtomType::Du_C:
			return AtomType::C;
			
	    case SybylAtomType::N_3:
	    case SybylAtomType::N_2:
	    case SybylAtomType::N_1:
	    case SybylAtomType::N_ar:
	    case SybylAtomType::N_am:
	    case SybylAtomType::N_pl3:
	    case SybylAtomType::N_4:
			return AtomType::N;

	    case SybylAtomType::O_3:
	    case SybylAtomType::O_2:
	    case SybylAtomType::O_co2:
	    case SybylAtomType::O_spc:
	    case SybylAtomType::O_t3p:
			return AtomType::O;

	    case SybylAtomType::S_3:
	    case SybylAtomType::S_2:
	    case SybylAtomType::S_O:
	    case SybylAtomType::S_O2:
			return AtomType::S;

	    case SybylAtomType::P_3:
			return AtomType::P;

	    case SybylAtomType::H:
	    case SybylAtomType::H_spc:
	    case SybylAtomType::H_t3p:
			return AtomType::H;

	    case SybylAtomType::Any:
			return AtomType::AH;

	    case SybylAtomType::Hal:
			return AtomType::X;

	    case SybylAtomType::Hev:
			return AtomType::A;

	    case SybylAtomType::Het:
			return AtomType::HET;

	    case SybylAtomType::Li:
			return AtomType::Li;

	    case SybylAtomType::Na:
			return AtomType::Na;

	    case SybylAtomType::Mg:
			return AtomType::Mg;

	    case SybylAtomType::Al:
			return AtomType::Al;

	    case SybylAtomType::Si:
			return AtomType::Si;

	    case SybylAtomType::K:
			return AtomType::K;

	    case SybylAtomType::Ca:
			return AtomType::Ca;

	    case SybylAtomType::Cr_th:
	    case SybylAtomType::Cr_oh:
			return AtomType::Cr;

	    case SybylAtomType::Mn:
			return AtomType::Mn;

	    case SybylAtomType::Fe:
			return AtomType::Fe;

	    case SybylAtomType::Co_oh:
			return AtomType::Co;

	    case SybylAtomType::Cu:
			return AtomType::Cu;

	    case SybylAtomType::F:
			return AtomType::F;

	    case SybylAtomType::Cl:
			return AtomType::Cl;

	    case SybylAtomType::Br:
			return AtomType::Br;

	    case SybylAtomType::I:
			return AtomType::I;

	    case SybylAtomType::Zn:
			return AtomType::Zn;

	    case SybylAtomType::Se:
			return AtomType::Se;

	    case SybylAtomType::Mo:
			return AtomType::Mo;

	    case SybylAtomType::Sn:
			return AtomType::Sn;

		default:
			return AtomType::UNKNOWN;
	}
}
	
unsigned int Chem::perceiveSybylType(const Atom& atom, const MolecularGraph& molgraph)
{
	switch (getType(atom)) {

		case AtomType::C:
			if (getAromaticityFlag(atom))
				return SybylAtomType::C_ar;

			if (getFormalCharge(atom) == 1 && isGuanidineCarbon(atom, molgraph))
				return SybylAtomType::C_cat;				

			switch (getHybridizationState(atom)) {

				case HybridizationState::SP3:
					return SybylAtomType::C_3;
		
				case HybridizationState::SP2:
					return SybylAtomType::C_2;
					
				case HybridizationState::SP1:
					return SybylAtomType::C_1;
		
				default:
					return SybylAtomType::UNKNOWN;
			}

		case AtomType::N:
			if (getAromaticityFlag(atom))
				return SybylAtomType::N_ar;

			if (getFormalCharge(atom) == 1 && getBondCount(atom, molgraph) == 4 && getBondCount(atom, molgraph, 1) == 4)
				return SybylAtomType::N_4;				

			if (isAmideNitrogen(atom, molgraph))
				return SybylAtomType::N_am;
	
			if (isPlanarNitrogen(atom, molgraph))
				return SybylAtomType::N_pl3;

			switch (getHybridizationState(atom)) {

				case HybridizationState::SP3:
					return SybylAtomType::N_3;
		
				case HybridizationState::SP2:
					return SybylAtomType::N_2;
					
				case HybridizationState::SP1:
					return SybylAtomType::N_1;
		
				default:
					return SybylAtomType::UNKNOWN;
			}

		case AtomType::O:
			if (isCarboxylateOxygen(atom, molgraph))
				return SybylAtomType::O_co2;

			if (isPhosphateOxygen(atom, molgraph))
				return SybylAtomType::O_co2;

			switch (getHybridizationState(atom)) {

				case HybridizationState::SP3:
					return SybylAtomType::O_3;
		
				case HybridizationState::SP2:
					return SybylAtomType::O_2;
		
				default:
					return SybylAtomType::UNKNOWN;
			}

		case AtomType::S:
			if (isSulfoxideSulfur(atom, molgraph))
				return SybylAtomType::S_O;

			if (isSulfoneSulfur(atom, molgraph))
				return SybylAtomType::S_O2;

			switch (getHybridizationState(atom)) {

				case HybridizationState::SP3:
					return SybylAtomType::S_3;
		
				case HybridizationState::SP2:
					return SybylAtomType::S_2;
		
				default:
					return SybylAtomType::UNKNOWN;
			}

		case AtomType::P:
			return SybylAtomType::P_3;

		case AtomType::H:
			return SybylAtomType::H;

		case AtomType::F:
			return SybylAtomType::F;

		case AtomType::Cl:
			return SybylAtomType::Cl;

		case AtomType::Br:
			return SybylAtomType::Br;

		case AtomType::I:
			return SybylAtomType::I;

		case AtomType::Li:
			return SybylAtomType::Li;

		case AtomType::Na:
			return SybylAtomType::Na;

		case AtomType::Mg:
			return SybylAtomType::Mg;

		case AtomType::Al:
			return SybylAtomType::Al;

		case AtomType::Si:
			return SybylAtomType::Si;

		case AtomType::K:
			return SybylAtomType::K;

		case AtomType::Ca:
			return SybylAtomType::Ca;

		case AtomType::Cr:
			if (getBondCount(atom, molgraph) <= 4)
				return SybylAtomType::Cr_th;

			return SybylAtomType::Cr_oh;

		case AtomType::Mn:
			return SybylAtomType::Mn;

		case AtomType::Fe:
			return SybylAtomType::Fe;

		case AtomType::Co:
			return SybylAtomType::Co_oh;

		case AtomType::Cu:
			return SybylAtomType::Cu;

		case AtomType::Zn:
			return SybylAtomType::Zn;

		case AtomType::Se:
			return SybylAtomType::Se;

		case AtomType::Mo:
			return SybylAtomType::Mo;

		case AtomType::Sn:
			return SybylAtomType::Sn;

		case AtomType::AH:
			return SybylAtomType::Any;

		case AtomType::A:
			return SybylAtomType::Hev;

		case AtomType::X:
			return SybylAtomType::Hal;

		case AtomType::HET:
			return SybylAtomType::Het;

		default:
			return SybylAtomType::UNKNOWN;
	}
}
	
