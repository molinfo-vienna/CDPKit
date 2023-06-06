/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * AtomFunctionsImpl.hpp 
 *
 * This file is part of the Chemical Data Processing Toolkit
 *
 * Copyright (C) 2003 Thomas Seidel <thomas.seidel@univie.ac.at>
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


#include "CDPL/Chem/Atom.hpp"
#include "CDPL/Chem/Bond.hpp"
#include "CDPL/Chem/AtomFunctions.hpp"
#include "CDPL/Chem/BondFunctions.hpp"
#include "CDPL/Chem/MolecularGraphFunctions.hpp"
#include "CDPL/Chem/UtilityFunctions.hpp"
#include "CDPL/Chem/HybridizationState.hpp"
#include "CDPL/Chem/AtomType.hpp"
#include "CDPL/Chem/AtomConfiguration.hpp"
#include "CDPL/Chem/BondStereoFlag.hpp"
#include "CDPL/Chem/StereoDescriptor.hpp"
#include "CDPL/Chem/AtomDictionary.hpp"

#include "BondFunctions.hpp"


std::size_t CDPL::Internal::getNumContainingSSSRRings(const Chem::Atom& atom, const Chem::MolecularGraph& molgraph)
{
	return getNumContainingFragments(atom, *getSSSR(molgraph));
}

bool CDPL::Internal::isOrdinaryHydrogen(const Chem::Atom& atom, const Chem::MolecularGraph& molgraph, unsigned int flags)
{
	using namespace Chem;
	
    if (getType(atom) != AtomType::H)
		return false;
 
	if (flags == AtomPropertyFlag::DEFAULT)
		flags = AtomPropertyFlag::ISOTOPE | AtomPropertyFlag::FORMAL_CHARGE | AtomPropertyFlag::H_COUNT |
			AtomPropertyFlag::ATOM_MAPPING_ID | AtomPropertyFlag::CONFIGURATION;

	if ((flags & AtomPropertyFlag::ISOTOPE) && getIsotope(atom) > 0)
		return false;

    if ((flags & AtomPropertyFlag::FORMAL_CHARGE) && getFormalCharge(atom) != 0)
		return false;

    if ((flags & AtomPropertyFlag::H_COUNT) && getImplicitHydrogenCount(atom) != 0)
		return false;
	
	bool first_bond = true;

	Atom::ConstAtomIterator atoms_end = atom.getAtomsEnd();
	Atom::ConstBondIterator b_it = atom.getBondsBegin();

	for (Atom::ConstAtomIterator a_it = atom.getAtomsBegin(); a_it != atoms_end; ++a_it, ++b_it) {
		const Bond& bond = *b_it;
		const Atom& nbr_atom = *a_it;

		if (!molgraph.containsAtom(nbr_atom) || !molgraph.containsBond(bond))
			continue;
		
		if (!first_bond)
			return false;

		if (getOrder(bond) != 1)
			return false;

		first_bond = false;
				
		if (flags & AtomPropertyFlag::CONFIGURATION) {
			if (get2DStereoFlag(bond) != BondStereoFlag::PLAIN)
				return false;

			const StereoDescriptor& sto_descr = getStereoDescriptor(nbr_atom);
			unsigned int config = sto_descr.getConfiguration();

			if (config != AtomConfiguration::R && config != AtomConfiguration::S)
				continue;

			if (!sto_descr.isValid(nbr_atom))
				continue;

			const Chem::Atom* const* ref_atoms = sto_descr.getReferenceAtoms();

			for (std::size_t i = 0, num_ref = sto_descr.getNumReferenceAtoms(); i < num_ref; i++)
				if (ref_atoms[i] == &atom)
					return false;
		}
	}

	if (first_bond)
		return false;

    return true;
}

bool CDPL::Internal::isUnsaturated(const Chem::Atom& atom, const Chem::MolecularGraph& molgraph)
{
	using namespace Chem;
	
 	Atom::ConstBondIterator bonds_end = atom.getBondsEnd();
	Atom::ConstAtomIterator a_it = atom.getAtomsBegin();

	for (Atom::ConstBondIterator b_it = atom.getBondsBegin(); b_it != bonds_end; ++b_it, ++a_it) {
		const Bond& bond = *b_it;

		if (!molgraph.containsAtom(*a_it) || !molgraph.containsBond(bond))
			continue;

		if (getOrder(bond) > 1) 
			return true;
	}

	return false;
}

bool CDPL::Internal::isAmideNitrogen(const Chem::Atom& atom, const Chem::MolecularGraph& molgraph, bool c_only, bool db_o_only)
{
	using namespace Chem;
	
	if (getType(atom) != AtomType::N)
		return false;

	Atom::ConstAtomIterator atoms_end = atom.getAtomsEnd();
	Atom::ConstBondIterator b_it = atom.getBondsBegin();

	for (Atom::ConstAtomIterator a_it = atom.getAtomsBegin(); a_it != atoms_end; ++a_it, ++b_it) {
		const Bond& bond = *b_it;
		const Atom& nbr_atom = *a_it;

		if (!molgraph.containsAtom(nbr_atom) || !molgraph.containsBond(bond))
			continue;

		if (getOrder(bond) != 1)
			continue;

		if (isCarbonylLikeAtom(nbr_atom, molgraph, c_only, db_o_only))
			return true;
	}

	return false;
}

bool CDPL::Internal::isInvertibleNitrogen(const Chem::Atom& atom, const Chem::MolecularGraph& molgraph)
{
	using namespace Chem;
	
	if (getType(atom) != AtomType::N)
		return false;

	if (getAromaticityFlag(atom))
		return false;

	if (getHybridizationState(atom) != HybridizationState::SP3)
		return false;

	std::size_t bond_count = 0;
	std::size_t ring_bond_count = 0;

	Atom::ConstAtomIterator atoms_end = atom.getAtomsEnd();
	Atom::ConstBondIterator b_it = atom.getBondsBegin();

	for (Atom::ConstAtomIterator a_it = atom.getAtomsBegin(); a_it != atoms_end; ++a_it, ++b_it) {
		const Atom& nbr_atom = *a_it;
		const Bond& bond = *b_it;

		if (!molgraph.containsAtom(nbr_atom) || !molgraph.containsBond(bond))
			continue;

		if (getOrder(bond) != 1)
			return false;

		if (getRingFlag(bond) && (++ring_bond_count > 2))
			return false;

		if (getAromaticityFlag(nbr_atom)/* || isUnsaturated(nbr_atom, molgraph)*/)
			return false;

		switch (getHybridizationState(nbr_atom)) {

			case HybridizationState::SP2:
			case HybridizationState::SP:
				return false;

			default:
				break;
		} 

		bond_count++;
	}

	return ((bond_count + getImplicitHydrogenCount(atom)) == 3);
}

bool CDPL::Internal::isPlanarNitrogen(const Chem::Atom& atom, const Chem::MolecularGraph& molgraph)
{
	using namespace Chem;
	
	if (getType(atom) != AtomType::N)
		return false;

	std::size_t bond_count = 0;
	bool unsat_nbrs = false;

	Atom::ConstAtomIterator atoms_end = atom.getAtomsEnd();
	Atom::ConstBondIterator b_it = atom.getBondsBegin();

	for (Atom::ConstAtomIterator a_it = atom.getAtomsBegin(); a_it != atoms_end; ++a_it, ++b_it) {
		const Atom& nbr_atom = *a_it;
		const Bond& bond = *b_it;

		if (!molgraph.containsAtom(nbr_atom) || !molgraph.containsBond(bond))
			continue;

		if (getOrder(bond) != 1 || getAromaticityFlag(nbr_atom)/* || isUnsaturated(nbr_atom, molgraph)*/) {
			unsat_nbrs = true;

		} else {
			switch (getHybridizationState(nbr_atom)) {

				case HybridizationState::SP2:
				case HybridizationState::SP:
					unsat_nbrs = true;

				default:
					break;
			}
		}
		
		bond_count++;
	}

	if (getImplicitHydrogenCount(atom) + bond_count != 3)
		return false;

	return (unsat_nbrs || getAromaticityFlag(atom));
}

bool CDPL::Internal::isCarbonylLikeAtom(const Chem::Atom& atom, const Chem::MolecularGraph& molgraph, bool c_only, bool db_o_only)
{
	using namespace Chem;
	
	unsigned int type = getType(atom);

	switch (type) {

		case AtomType::C:
			break;

		case AtomType::S:
		case AtomType::P:
			if (!c_only)
				break;

		default:
			return false;
	}

	if (type == AtomType::C) {
		if (getExplicitBondCount(atom, molgraph, 2, AtomType::O, true) == 1)
			return true;
		
		if (db_o_only)
			return false;

		return (getExplicitBondCount(atom, molgraph, 2, AtomType::S, true) == 1);
	}

	if (getExplicitBondCount(atom, molgraph, 2, AtomType::O, true) > 0)
		return true;

	if (db_o_only)
		return false;

	return (type != AtomType::S && getExplicitBondCount(atom, molgraph, 2, AtomType::S, true) > 0);
}

double CDPL::Internal::getVdWRadius(const Chem::Atom& atom)
{
    return Chem::AtomDictionary::getVdWRadius(getType(atom));
}

std::size_t CDPL::Internal::calcExplicitValence(const Chem::Atom& atom, const Chem::MolecularGraph& molgraph)
{
	using namespace Chem;

	std::size_t exp_val = 0;

	Atom::ConstAtomIterator atoms_end = atom.getAtomsEnd();
	Atom::ConstBondIterator b_it = atom.getBondsBegin();

	for (Atom::ConstAtomIterator a_it = atom.getAtomsBegin(); a_it != atoms_end; ++a_it, ++b_it)
		if (molgraph.containsAtom(*a_it) && molgraph.containsBond(*b_it))
			exp_val += getOrder(*b_it);

	return exp_val;
}
	
std::size_t CDPL::Internal::calcValence(const Chem::Atom& atom, const Chem::MolecularGraph& molgraph)
{
	return (calcExplicitValence(atom, molgraph) + getImplicitHydrogenCount(atom));
}

std::size_t CDPL::Internal::calcFreeValenceElectronCount(const Chem::Atom& atom, const Chem::MolecularGraph& molgraph)
{
	long free_el_count = calcValenceElectronCount(atom) - calcValence(atom, molgraph);

	return std::size_t(free_el_count < 0 ? 0 : free_el_count); 
}

std::size_t CDPL::Internal::calcValenceElectronCount(const Chem::Atom& atom)
{
	long el_count = Chem::AtomDictionary::getNumValenceElectrons(getType(atom)) - getFormalCharge(atom);

	return std::size_t(el_count < 0 ? 0 : el_count); 
}

std::size_t CDPL::Internal::getExplicitAtomCount(const Chem::Atom& atom, const Chem::MolecularGraph& molgraph, unsigned int type, bool strict)
{
	using namespace Chem;
	
    std::size_t count = 0;

	Atom::ConstAtomIterator atoms_end = atom.getAtomsEnd();
	Atom::ConstBondIterator b_it = atom.getBondsBegin();

	for (Atom::ConstAtomIterator a_it = atom.getAtomsBegin(); a_it != atoms_end; ++a_it, ++b_it)
		if (molgraph.containsAtom(*a_it) && molgraph.containsBond(*b_it) && (strict ? type == getType(*a_it) : atomTypesMatch(type, getType(*a_it))))
			count++;

    return count;
}

std::size_t CDPL::Internal::getAtomCount(const Chem::Atom& atom, const Chem::MolecularGraph& molgraph, unsigned int type, bool strict)
{
	using namespace Chem;
	
    std::size_t count = getExplicitAtomCount(atom, molgraph, type, strict);

    if (strict ? type == AtomType::H : atomTypesMatch(type, AtomType::H))
		count += getImplicitHydrogenCount(atom);

    return count;
}

std::size_t CDPL::Internal::getHeavyAtomCount(const Chem::Atom& atom, const Chem::MolecularGraph& molgraph)
{
	using namespace Chem;
	
	std::size_t count = 0;

 	Atom::ConstAtomIterator atoms_end = atom.getAtomsEnd();
	Atom::ConstBondIterator b_it = atom.getBondsBegin();

	for (Atom::ConstAtomIterator a_it = atom.getAtomsBegin(); a_it != atoms_end; ++a_it, ++b_it)
		if (molgraph.containsAtom(*a_it) && molgraph.containsBond(*b_it) && (getType(*a_it) != Chem::AtomType::H))
			count++;

	return count;
}

std::size_t CDPL::Internal::getOrdinaryHydrogenCount(const Chem::Atom& atom, const Chem::MolecularGraph& molgraph, unsigned int flags)
{
	using namespace Chem;
	
    std::size_t count = 0;

	Atom::ConstAtomIterator atoms_end = atom.getAtomsEnd();
	Atom::ConstBondIterator b_it = atom.getBondsBegin();

	for (Atom::ConstAtomIterator a_it = atom.getAtomsBegin(); a_it != atoms_end; ++a_it, ++b_it)
		if (molgraph.containsAtom(*a_it) && molgraph.containsBond(*b_it) && isOrdinaryHydrogen(*a_it, molgraph, flags))
			count++;

    return (count + getImplicitHydrogenCount(atom));
}

std::size_t CDPL::Internal::getExplicitBondCount(const Chem::Atom& atom, const Chem::MolecularGraph& molgraph)
{
	using namespace Chem;
	
	if (&atom.getMolecule() == &molgraph)
		return atom.getNumAtoms();

	std::size_t count = 0;

	Atom::ConstAtomIterator atoms_end = atom.getAtomsEnd();
	Atom::ConstBondIterator b_it = atom.getBondsBegin();

	for (Atom::ConstAtomIterator a_it = atom.getAtomsBegin(); a_it != atoms_end; ++a_it, ++b_it)
		if (molgraph.containsAtom(*a_it) && molgraph.containsBond(*b_it))
			count++;

	return count;
}

std::size_t CDPL::Internal::getBondCount(const Chem::Atom& atom, const Chem::MolecularGraph& molgraph)
{
    return (getExplicitBondCount(atom, molgraph) + getImplicitHydrogenCount(atom));
}

std::size_t CDPL::Internal::getExplicitBondCount(const Chem::Atom& atom, const Chem::MolecularGraph& molgraph, std::size_t order)
{
	using namespace Chem;
	
	std::size_t count = 0;

	Atom::ConstAtomIterator atoms_end = atom.getAtomsEnd();
	Atom::ConstBondIterator b_it = atom.getBondsBegin();

	for (Atom::ConstAtomIterator a_it = atom.getAtomsBegin(); a_it != atoms_end; ++a_it, ++b_it)
		if (molgraph.containsAtom(*a_it) && molgraph.containsBond(*b_it) && getOrder(*b_it) == order)
			count++;

	return count;
}

std::size_t CDPL::Internal::getBondCount(const Chem::Atom& atom, const Chem::MolecularGraph& molgraph, std::size_t order)
{
	std::size_t count = getExplicitBondCount(atom, molgraph, order);

    if (order == 1)
		count += getImplicitHydrogenCount(atom);

    return count;
}

std::size_t CDPL::Internal::getExplicitBondCount(const Chem::Atom& atom, const Chem::MolecularGraph& molgraph, std::size_t order, unsigned int type, bool strict)
{
	using namespace Chem;
	
	std::size_t count = 0;

	Atom::ConstAtomIterator atoms_end = atom.getAtomsEnd();
	Atom::ConstBondIterator b_it = atom.getBondsBegin();

	for (Atom::ConstAtomIterator a_it = atom.getAtomsBegin(); a_it != atoms_end; ++a_it, ++b_it)
		if (molgraph.containsAtom(*a_it) && molgraph.containsBond(*b_it) &&
			getOrder(*b_it) == order && (strict ? type == getType(*a_it) : atomTypesMatch(type, getType(*a_it))))
			count++;

    return count;
}

std::size_t CDPL::Internal::getBondCount(const Chem::Atom& atom, const Chem::MolecularGraph& molgraph, std::size_t order, unsigned int type, bool strict)
{
	using namespace Chem;

    std::size_t count = getExplicitBondCount(atom, molgraph, order, type, strict);
 
    if (order == 1 && (strict ? type == AtomType::H : atomTypesMatch(type, AtomType::H)))
		count += getImplicitHydrogenCount(atom);

    return count;
}

std::size_t CDPL::Internal::getRingBondCount(const Chem::Atom& atom, const Chem::MolecularGraph& molgraph)
{
	using namespace Chem;
	
	std::size_t count = 0;

 	Atom::ConstAtomIterator atoms_end = atom.getAtomsEnd();
	Atom::ConstBondIterator b_it = atom.getBondsBegin();

	for (Atom::ConstAtomIterator a_it = atom.getAtomsBegin(); a_it != atoms_end; ++a_it, ++b_it)
		if (molgraph.containsAtom(*a_it) && molgraph.containsBond(*b_it) && getRingFlag(*b_it))
			count++;

    return count;
}

std::size_t CDPL::Internal::getHeavyBondCount(const Chem::Atom& atom, const Chem::MolecularGraph& molgraph)
{
	using namespace Chem;
	
	std::size_t count = 0;

 	Atom::ConstAtomIterator atoms_end = atom.getAtomsEnd();
	Atom::ConstBondIterator b_it = atom.getBondsBegin();

	for (Atom::ConstAtomIterator a_it = atom.getAtomsBegin(); a_it != atoms_end; ++a_it, ++b_it)
		if (molgraph.containsAtom(*a_it) && molgraph.containsBond(*b_it) && !isHydrogenBond(*b_it))
			count++;

    return count;
}
