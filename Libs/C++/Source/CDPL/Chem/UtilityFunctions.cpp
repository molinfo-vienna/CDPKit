/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * UtilityFunctions.cpp 
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

#include <sstream>
#include <algorithm>
#include <functional>

#include <boost/bind.hpp>
#include <boost/unordered_map.hpp>

#include "CDPL/Chem/UtilityFunctions.hpp"
#include "CDPL/Chem/MolecularGraphFunctions.hpp"
#include "CDPL/Chem/BasicMolecule.hpp"
#include "CDPL/Chem/Fragment.hpp"
#include "CDPL/Chem/Bond.hpp"
#include "CDPL/Chem/Atom.hpp"
#include "CDPL/Chem/BondFunctions.hpp"
#include "CDPL/Chem/AtomFunctions.hpp"
#include "CDPL/Chem/AtomType.hpp"
#include "CDPL/Chem/AtomDictionary.hpp"
#include "CDPL/Chem/SybylAtomType.hpp"
#include "CDPL/Chem/SMARTSMoleculeReader.hpp"
#include "CDPL/Chem/SMILESMoleculeReader.hpp"

#include "MOL2FormatData.hpp"


using namespace CDPL; 


namespace
{

	typedef boost::unordered_map<unsigned int, std::string> SybylTypeToStringMap;

	SybylTypeToStringMap sybylAtomTypeToStringMap;
	SybylTypeToStringMap sybylBondTypeToStringMap;
	const std::string    EMPTY_STRING;
	
	struct Init {

		Init() {
			using namespace Chem;
			using namespace MOL2;

			for (std::size_t i = 0; i < sizeof(ATOM_TYPE_STRINGS) / sizeof(TypeToString); i++)
				sybylAtomTypeToStringMap.insert(SybylTypeToStringMap::value_type(ATOM_TYPE_STRINGS[i].type, ATOM_TYPE_STRINGS[i].string));

			for (std::size_t i = 0; i < sizeof(BOND_TYPE_STRINGS) / sizeof(TypeToString); i++)
				sybylBondTypeToStringMap.insert(SybylTypeToStringMap::value_type(BOND_TYPE_STRINGS[i].type, BOND_TYPE_STRINGS[i].string));
		}

	} init;
}


Chem::Molecule::SharedPointer Chem::parseSMARTS(const std::string& smarts, bool init_qry)
{
	Molecule::SharedPointer mol_ptr(new BasicMolecule());

	parseSMARTS(smarts, *mol_ptr, init_qry);
	
	return mol_ptr;
}

bool Chem::parseSMARTS(const std::string& smarts, Molecule& mol, bool init_qry)
{
	std::istringstream iss(smarts);

	if (SMARTSMoleculeReader(iss).read(mol)) {
		if (init_qry)
			initSubstructureSearchQuery(mol, true);
		return true;
	}

	return false;
}

Chem::Molecule::SharedPointer Chem::parseSMILES(const std::string& smiles)
{
	Molecule::SharedPointer mol_ptr(new BasicMolecule());

	parseSMILES(smiles, *mol_ptr);

	return mol_ptr;
}

bool Chem::parseSMILES(const std::string& smiles, Molecule& mol)
{
	std::istringstream iss(smiles);

	if (SMILESMoleculeReader(iss).read(mol))
		return true;

	return false;
}

void Chem::extendBoundingBox(Math::Vector3D& min, Math::Vector3D& max, const Math::Vector3D& coords, bool reset)
{
	if (reset) {
		max(0) = coords(0);
		max(1) = coords(1);
		max(2) = coords(2);

		min(0) = coords(0);
		min(1) = coords(1);
		min(2) = coords(2);
		return;
	}

	if (coords(0) > max(0))
		max(0) = coords(0);

	else if (coords(0) < min(0))
		min(0) = coords(0);

	if (coords(1) > max(1))
		max(1) = coords(1);

	else if (coords(1) < min(1))
		min(1) = coords(1);

	if (coords(2) > max(2))
		max(2) = coords(2);
			
	else if (coords(2) < min(2))
		min(2) = coords(2);
}	

bool Chem::insideBoundingBox(const Math::Vector3D& min, const Math::Vector3D& max, const Math::Vector3D& coords)
{
	return (coords(0) <= max(0) && coords(0) >= min(0) &&
			coords(1) <= max(1) && coords(1) >= min(1) &&
			coords(2) <= max(2) && coords(2) >= min(2));
}

bool Chem::isAromatic(const Fragment& ring, const MolecularGraph& molgraph, const Util::BitSet& arom_bond_mask)
{
	std::size_t num_pi_electrons = 0;

	Fragment::ConstAtomIterator atoms_end = ring.getAtomsEnd();

	for (Fragment::ConstAtomIterator a_it = ring.getAtomsBegin(); a_it != atoms_end; ++a_it) {
		const Atom& atom = *a_it;

		std::size_t num_single_bonds = 0;
		std::size_t num_ring_double_bonds = 0;
		std::size_t num_exo_double_bonds = 0;
		std::size_t num_arom_bonds = 0;
		std::size_t num_bonds = 0;

		Atom::ConstBondIterator bonds_end = atom.getBondsEnd();
		Atom::ConstAtomIterator a_it2 = atom.getAtomsBegin();

		for (Atom::ConstBondIterator b_it = atom.getBondsBegin(); b_it != bonds_end; ++b_it, ++a_it2) {
			const Bond& bond = *b_it;

			if (!(molgraph.containsAtom(*a_it2) && molgraph.containsBond(bond)))
				continue;

			bool in_ring = ring.containsBond(bond);

			switch (getOrder(bond)) {

				case 1:
					num_single_bonds++;
					break;

				case 2:
					if (in_ring)
						num_ring_double_bonds++;
					else
						num_exo_double_bonds++;

					break;

				default:
					return false;
			}

			num_bonds++;

			if (arom_bond_mask.test(molgraph.getBondIndex(bond))) 
				num_arom_bonds++;
		}

		std::size_t impl_h_count = getImplicitHydrogenCount(atom);

		num_bonds += impl_h_count;
		num_single_bonds += impl_h_count;

		unsigned int atom_type = getType(atom);
		long charge = getFormalCharge(atom);

		switch (atom_type) {

			case AtomType::C:
			case AtomType::Si:
			case AtomType::Sn:
				switch (num_bonds) {
					/*
					case 2:
						if (num_single_bonds == 2) {
							if (charge == 0)
								continue;

							if (charge == -1) {
								num_pi_electrons += 2;
								continue;
							}

							return false;
						}

						if (num_ring_double_bonds == 1 && charge == 0) {
							num_pi_electrons++;
							continue;
						}

						return false;
					*/
					case 3:
						if (num_single_bonds == 3) {
							if (charge == 1)
								continue;

							if (charge == -1) {
								num_pi_electrons += 2;
								continue;
							}

							return false;
						}

						if (charge != 0)
							return false;

						if (num_single_bonds == 2 &&
							(num_ring_double_bonds == 1 || (num_arom_bonds > 0 && num_exo_double_bonds == 1))) {
							num_pi_electrons++;
							continue;
						}

					default:
						return false;
				}

				return false;

			case AtomType::N:
			case AtomType::P:
			case AtomType::As:
				switch (num_bonds) {

					case 2:
						if (num_single_bonds == 2) {
							if (charge == -1) {
								num_pi_electrons += 2;
								continue;
							}

							return false;
						}

						if (num_ring_double_bonds == 1 && (charge == 0 || charge == 1)) {
							num_pi_electrons++;
							continue;
						}

						return false;

					case 3:
						if (num_single_bonds == 3) {
							if (charge == 0) {
								num_pi_electrons += 2;
								continue;
							}

							return false;
						}

						if (charge != 1)
							return false;

						if (num_single_bonds == 2 && 
							(num_ring_double_bonds == 1 || (num_arom_bonds > 0 && num_exo_double_bonds == 1))) {
							num_pi_electrons++;
							continue;
						}

					default:
						return false;
				}

				return false;

			case AtomType::O:
			case AtomType::S:
			case AtomType::Se:
				if (num_bonds == 2 && num_single_bonds == 2 && charge == 0) {
					num_pi_electrons += 2;
					continue;	
				}

			default:
				return false;
		}
	}

	return ((num_pi_electrons & 0x3) == 2);
}

bool Chem::isNotAromatic(const Fragment& ring, const MolecularGraph& molgraph)
{
	Fragment::ConstAtomIterator atoms_end = ring.getAtomsEnd();

	for (Fragment::ConstAtomIterator a_it = ring.getAtomsBegin(); a_it != atoms_end; ++a_it) {
		const Atom& atom = *a_it;

		std::size_t num_single_bonds = 0;
		std::size_t num_double_bonds = 0;
		std::size_t num_bonds = 0;

		Atom::ConstBondIterator bonds_end = atom.getBondsEnd();
		Atom::ConstAtomIterator a_it2 = atom.getAtomsBegin();

		for (Atom::ConstBondIterator b_it = atom.getBondsBegin(); b_it != bonds_end; ++b_it, ++a_it2) {
			const Bond& bond = *b_it;

			if (!(molgraph.containsAtom(*a_it2) && molgraph.containsBond(bond)))
				continue;

			switch (getOrder(bond)) {

				case 1:
					num_single_bonds++;
					break;

				case 2:
					num_double_bonds++;
					break;

				default:
					return false;
			}

			num_bonds++;
		}

		std::size_t impl_h_count = getImplicitHydrogenCount(atom);

		num_bonds += impl_h_count;
		num_single_bonds += impl_h_count;

		unsigned int atom_type = getType(atom);
		long charge = getFormalCharge(atom);

		switch (atom_type) {

			case AtomType::C:
			case AtomType::Si:
			case AtomType::Sn:
				switch (num_bonds) {
					/*
					case 2:
						if (num_single_bonds == 2) {
							if (charge == 1 || charge == -1)
								continue;

							return true;
						}

						if (num_double_bonds == 1 && charge == 0)
							continue;

						return true;
					*/
					case 3:
						if (num_single_bonds == 3) {
							if (charge == 1 || charge == -1)
								continue;

							return true;
						}

						if (charge != 0)
							return true;

						if (num_single_bonds == 2 && num_double_bonds == 1)
							continue;

					default:
						return true;
				}

				return true;

			case AtomType::N:
			case AtomType::P:
			case AtomType::As:
				switch (num_bonds) {

					case 2:
						if (num_single_bonds == 2) {
							if (charge == -1)
								continue;

							return true;
						}

						if (num_double_bonds == 1 && (charge == 0 || charge == 1)) 
							continue;

						return true;

					case 3:
						if (num_single_bonds == 3) {
							if (charge == 0) 
								continue;

							return true;
						}

						if (charge != 1)
							return true;

						if (num_single_bonds == 2 && num_double_bonds == 1)
							continue;

					default:
						return true;
				}

				return false;

			case AtomType::O:
			case AtomType::S:
			case AtomType::Se:
				if (num_bonds == 2 && num_single_bonds == 2 && charge == 0)
					continue;	

			default:
				return true;
		}
	}

	return false;
}

bool Chem::containsFragmentWithBond(const FragmentList& frag_list, const Bond& bond)
{
	FragmentList::ConstElementIterator end = frag_list.getElementsEnd();

	return (std::find_if(frag_list.getElementsBegin(), end, boost::bind(&Fragment::containsBond, _1, boost::ref(bond))) != end);
}
		
bool Chem::containsFragmentWithMinSize(const FragmentList& frag_list, std::size_t min_size)
{
	FragmentList::ConstElementIterator end = frag_list.getElementsEnd();

	return (std::find_if(frag_list.getElementsBegin(), end, 
						 boost::bind(std::greater_equal<std::size_t>(), boost::bind(&Fragment::getNumAtoms, _1), min_size)) != end);
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

const std::string& Chem::getSybylAtomTypeString(unsigned int sybyl_type)
{
	SybylTypeToStringMap::const_iterator it = sybylAtomTypeToStringMap.find(sybyl_type);

	if (it != sybylAtomTypeToStringMap.end())
		return it->second;

	return EMPTY_STRING;
}

const std::string& Chem::getSybylBondTypeString(unsigned int sybyl_type)
{
	SybylTypeToStringMap::const_iterator it = sybylBondTypeToStringMap.find(sybyl_type);

	if (it != sybylBondTypeToStringMap.end())
		return it->second;

	return EMPTY_STRING;
}

bool Chem::atomTypesMatch(unsigned int qry_type, unsigned int tgt_type)
{
    switch (qry_type) {

		case AtomType::ANY:
		case AtomType::AH:
			return true;

		case AtomType::A:
			return (tgt_type != AtomType::H);
			
		case AtomType::Q:
			return (tgt_type != AtomType::H && tgt_type != AtomType::C);

		case AtomType::QH:
			return (tgt_type != AtomType::C);

		case AtomType::M:
			return AtomDictionary::isMetal(tgt_type);

		case AtomType::MH:
			return (tgt_type == AtomType::H || AtomDictionary::isMetal(tgt_type));

		case AtomType::X:
			return AtomDictionary::isHalogen(tgt_type);

		case AtomType::XH:
			return (tgt_type == AtomType::H || AtomDictionary::isHalogen(tgt_type));

		case AtomType::HET:
			return (tgt_type == AtomType::N || tgt_type == AtomType::O || tgt_type == AtomType::S || tgt_type == AtomType::P);

		default:
			return (qry_type == tgt_type);
    }
}
