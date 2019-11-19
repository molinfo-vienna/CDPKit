/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * FragmentLibraryEntry.cpp 
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

#include <boost/bind.hpp>

#include "CDPL/ConfGen/FragmentLibraryEntry.hpp"
#include "CDPL/Chem/Atom.hpp"
#include "CDPL/Chem/Bond.hpp"
#include "CDPL/Chem/StereoDescriptor.hpp"
#include "CDPL/Chem/Entity3DFunctions.hpp"
#include "CDPL/Chem/AtomFunctions.hpp"
#include "CDPL/Chem/AtomContainerFunctions.hpp"
#include "CDPL/Chem/BondFunctions.hpp"
#include "CDPL/Chem/MolecularGraphFunctions.hpp"
#include "CDPL/Chem/AtomType.hpp"
#include "CDPL/Chem/HybridizationState.hpp"
#include "CDPL/Chem/AtomConfiguration.hpp"
#include "CDPL/Chem/BondConfiguration.hpp"
#include "CDPL/Chem/AtomPropertyFlag.hpp"
#include "CDPL/Chem/BondPropertyFlag.hpp"
#include "CDPL/Internal/SHA1.hpp"


using namespace CDPL;


namespace
{

	bool compareAtomIndex(const Chem::Atom& atom1, const Chem::Atom& atom2)
	{
		return (atom1.getIndex() < atom2.getIndex());
	}

	bool comparePointerAtomIndex(const Chem::Atom* atom1, const Chem::Atom* atom2)
	{
		return (atom1->getIndex() < atom2->getIndex());
	}

	bool compareBondAtomIndices(const Chem::Bond& bond1, const Chem::Bond& bond2)
	{
		std::size_t bond1_beg_idx = bond1.getBegin().getIndex();
		std::size_t bond2_beg_idx = bond2.getBegin().getIndex();

		if (bond1_beg_idx < bond2_beg_idx)
			return true;

		if (bond1_beg_idx > bond2_beg_idx)
			return false;
	
		return (bond1.getEnd().getIndex() < bond2.getEnd().getIndex());
	}

	const Chem::Atom* getNeighborWithLowestIndex(const Chem::Atom* atom, const Chem::Atom* x_atom)
	{
		using namespace Chem;

		for (Atom::ConstAtomIterator it = atom->getAtomsBegin(), end = atom->getAtomsBegin(); it != end; ++it) {
			const Atom* nbr = &*it;

			if (nbr == x_atom)
				continue;

			return nbr;
		}

		return 0;
	}
}


ConfGen::FragmentLibraryEntry::FragmentLibraryEntry(): hashCode(0)
{
	canonNumGen.setHydrogenCountFunction(boost::bind(&Chem::getExplicitAtomCount, _1, Chem::AtomType::H));
}
	  
ConfGen::FragmentLibraryEntry::FragmentLibraryEntry(const FragmentLibraryEntry& entry):  
	Chem::MolecularGraph(entry), molecule(entry.molecule), hashCode(entry.hashCode)
{
	for (AtomMapping::const_iterator it = entry.atomMapping.begin(), end = entry.atomMapping.end(); it != end; ++it) 
		atomMapping.push_back(&molecule.getAtom(entry.molecule.getAtomIndex(**it)));

	canonNumGen.setHydrogenCountFunction(boost::bind(&Chem::getExplicitAtomCount, _1, Chem::AtomType::H));
}

ConfGen::FragmentLibraryEntry::FragmentLibraryEntry(const Chem::MolecularGraph& molgraph)
{
	canonNumGen.setHydrogenCountFunction(boost::bind(&Chem::getExplicitAtomCount, _1, Chem::AtomType::H));

    create(molgraph);
}

void ConfGen::FragmentLibraryEntry::clear()
{
    clearProperties();

    molecule.clear();
	atomMapping.clear();
	hashCode = 0;
}

Chem::MolecularGraph::SharedPointer ConfGen::FragmentLibraryEntry::clone() const
{
	return Chem::MolecularGraph::SharedPointer(new FragmentLibraryEntry(*this));
}

std::size_t ConfGen::FragmentLibraryEntry::getNumAtoms() const
{
    return molecule.getNumAtoms();
}

const Chem::Atom& ConfGen::FragmentLibraryEntry::getAtom(std::size_t idx) const
{
    return molecule.getAtom(idx);
}
		
Chem::Atom& ConfGen::FragmentLibraryEntry::getAtom(std::size_t idx)
{
    return molecule.getAtom(idx);
}

ConfGen::FragmentLibraryEntry::ConstAtomIterator ConfGen::FragmentLibraryEntry::getAtomsBegin() const
{
    return molecule.getAtomsBegin();
}

ConfGen::FragmentLibraryEntry::ConstAtomIterator ConfGen::FragmentLibraryEntry::getAtomsEnd() const
{
    return molecule.getAtomsEnd();
}

ConfGen::FragmentLibraryEntry::AtomIterator ConfGen::FragmentLibraryEntry::getAtomsBegin()
{
    return molecule.getAtomsBegin();
}

ConfGen::FragmentLibraryEntry::AtomIterator ConfGen::FragmentLibraryEntry::getAtomsEnd()
{
    return molecule.getAtomsEnd();
}

bool ConfGen::FragmentLibraryEntry::containsAtom(const Chem::Atom& atom) const
{
    return molecule.containsAtom(atom);
}

std::size_t ConfGen::FragmentLibraryEntry::getAtomIndex(const Chem::Atom& atom) const
{
    return molecule.getAtomIndex(atom);
}

std::size_t ConfGen::FragmentLibraryEntry::getNumEntities() const
{
    return molecule.getNumEntities();
}

const Chem::Entity3D& ConfGen::FragmentLibraryEntry::getEntity(std::size_t idx) const
{
    return molecule.getEntity(idx);
}

Chem::Entity3D& ConfGen::FragmentLibraryEntry::getEntity(std::size_t idx)
{
    return molecule.getEntity(idx);
}

std::size_t ConfGen::FragmentLibraryEntry::getNumBonds() const
{
    return molecule.getNumBonds();
}
	    
const Chem::Bond& ConfGen::FragmentLibraryEntry::getBond(std::size_t idx) const
{
    return molecule.getBond(idx);
}

Chem::Bond& ConfGen::FragmentLibraryEntry::getBond(std::size_t idx)
{
    return molecule.getBond(idx);
}

ConfGen::FragmentLibraryEntry::ConstBondIterator ConfGen::FragmentLibraryEntry::getBondsBegin() const
{
    return molecule.getBondsBegin();
}

ConfGen::FragmentLibraryEntry::ConstBondIterator ConfGen::FragmentLibraryEntry::getBondsEnd() const
{
    return molecule.getBondsEnd();
}

ConfGen::FragmentLibraryEntry::BondIterator ConfGen::FragmentLibraryEntry::getBondsBegin()
{
    return molecule.getBondsBegin();
}

ConfGen::FragmentLibraryEntry::BondIterator ConfGen::FragmentLibraryEntry::getBondsEnd()
{
    return molecule.getBondsEnd();
}

bool ConfGen::FragmentLibraryEntry::containsBond(const Chem::Bond& bond) const
{
    return molecule.containsBond(bond);
}

std::size_t ConfGen::FragmentLibraryEntry::getBondIndex(const Chem::Bond& bond) const
{
    return molecule.getBondIndex(bond);
}

void ConfGen::FragmentLibraryEntry::orderAtoms(const Chem::AtomCompareFunction& func) {}

void ConfGen::FragmentLibraryEntry::orderBonds(const Chem::BondCompareFunction& func) {}

const Base::uint64& ConfGen::FragmentLibraryEntry::getHashCode() const
{
	return hashCode;
}

ConfGen::FragmentLibraryEntry& ConfGen::FragmentLibraryEntry::operator=(const FragmentLibraryEntry& entry)
{
	if (&entry == this)
		return *this;

	MolecularGraph::operator=(entry);
	molecule.operator=(entry.molecule);
	hashCode = entry.hashCode;

	atomMapping.clear();

	for (AtomMapping::const_iterator it = entry.atomMapping.begin(), end = entry.atomMapping.end(); it != end; ++it) 
		atomMapping.push_back(&molecule.getAtom(entry.molecule.getAtomIndex(**it)));

	return *this;
}
	
void ConfGen::FragmentLibraryEntry::create(const Chem::MolecularGraph& molgraph)
{
    clear();
	copyAtoms(molgraph);

	bool flex_ring_rsys = copyBonds(molgraph);

	fixStereoDescriptors(molgraph);
	hydrogenize();
	canonicalize(flex_ring_rsys);
	calcHashCode(flex_ring_rsys);
}

const ConfGen::FragmentLibraryEntry::AtomMapping& ConfGen::FragmentLibraryEntry::getAtomMapping() const
{
	return atomMapping;
}

void ConfGen::FragmentLibraryEntry::copyAtoms(const Chem::MolecularGraph& molgraph)
{
    using namespace Chem;
 
	molecule.reserveMemoryForAtoms(molgraph.getNumAtoms());

	for (MolecularGraph::ConstAtomIterator it = molgraph.getAtomsBegin(), end =  molgraph.getAtomsEnd(); it != end; ++it) {
		const Atom& atom = *it;

		unsigned int atom_type = getType(atom);
		std::size_t exp_atom_count = 0;
		bool have_arom_ring_nbr = false;

		Atom::ConstBondIterator nb_it = atom.getBondsBegin();

		for (Atom::ConstAtomIterator na_it = atom.getAtomsBegin(), na_end = atom.getAtomsEnd(); na_it != na_end; ++na_it, ++nb_it) {
			const Atom& nbr_atom = *na_it;

			if (!molgraph.containsAtom(nbr_atom))
				continue;

			if (!molgraph.containsBond(*nb_it))
				continue;

			exp_atom_count++;

			if (getAromaticityFlag(nbr_atom) && getAromaticAtomCount(nbr_atom, molgraph) > 1)
				have_arom_ring_nbr = true;
		}

		Atom& new_atom = molecule.addAtom();

		atomMapping.push_back(&new_atom);

		if (exp_atom_count == 1 && have_arom_ring_nbr) {
			setType(new_atom, AtomType::H);
			setAromaticityFlag(new_atom, false);
			setRingFlag(new_atom, false);
			setHybridizationState(new_atom, HybridizationState::UNKNOWN);

			if (atom_type == AtomType::H && has3DCoordinates(atom))
				set3DCoordinates(new_atom, get3DCoordinates(atom));

			continue;
		} 

		bool arom_flag = getAromaticityFlag(atom);
		unsigned int hyb_state = getHybridizationState(atom);

		if (exp_atom_count >= 3 && !arom_flag && hyb_state == HybridizationState::SP3) {
			const StereoDescriptor& desc = getStereoDescriptor(atom);
	
			if ((desc.getConfiguration() == AtomConfiguration::R || desc.getConfiguration() == AtomConfiguration::S) && desc.isValid(atom) &&
				(getOrdinaryHydrogenCount(atom, molgraph, AtomPropertyFlag::ISOTOPE | AtomPropertyFlag::FORMAL_CHARGE | AtomPropertyFlag::H_COUNT) <= 1))

				setStereoDescriptor(new_atom, desc);
		}

		if (has3DCoordinates(atom))
			set3DCoordinates(new_atom, get3DCoordinates(atom));

		setType(new_atom, atom_type);
		setFormalCharge(new_atom, getFormalCharge(atom));
		setRingFlag(new_atom, getRingFlag(atom));
		setAromaticityFlag(new_atom, arom_flag);
		setHybridizationState(new_atom, hyb_state);
	
		if (arom_flag || (atom_type != AtomType::N && atom_type != AtomType::C && atom_type != AtomType::S) || exp_atom_count != 1)
			continue;
		
		if (hyb_state == HybridizationState::SP) {
			setFormalCharge(new_atom, 0);

			std::size_t exp_val = calcExplicitValence(atom, molgraph);

			if (exp_val == 1)
				setUnpairedElectronCount(new_atom, 2);
			else if (exp_val == 2)
				setUnpairedElectronCount(new_atom, 1);

		} else if (hyb_state == HybridizationState::SP2) {
			setFormalCharge(new_atom, 0);

			std::size_t exp_val = calcExplicitValence(atom, molgraph);

			if (exp_val == 1)
				setUnpairedElectronCount(new_atom, 1);
			else if (exp_val == 2)
				setUnpairedElectronCount(new_atom, 0);
		}
	}
}
	
bool ConfGen::FragmentLibraryEntry::copyBonds(const Chem::MolecularGraph& molgraph)
{
	using namespace Chem;
 
	molecule.reserveMemoryForBonds(molgraph.getNumBonds());

	bool flex_ring_sys = false;

    for (MolecularGraph::ConstBondIterator it = molgraph.getBondsBegin(), end = molgraph.getBondsEnd(); it != end; ++it) {
		const Bond& bond = *it;
		const Atom& atom1 = bond.getBegin();
		const Atom& atom2 = bond.getEnd();

		if (!molgraph.containsAtom(atom1) || !molgraph.containsAtom(atom2))
			continue;

		bool ring_flag = getRingFlag(bond);
		bool arom_flag = getAromaticityFlag(bond);
		std::size_t order = getOrder(bond);
		Bond& new_bond = molecule.addBond(molgraph.getAtomIndex(atom1), molgraph.getAtomIndex(atom2));

		if (ring_flag && !arom_flag && order == 1)
			flex_ring_sys = true;

		setOrder(new_bond, order);
		setRingFlag(new_bond, ring_flag);
		setAromaticityFlag(new_bond, arom_flag);

		if (!arom_flag && order == 2) {
			const StereoDescriptor& desc = getStereoDescriptor(bond);

			if (desc.getConfiguration() != BondConfiguration::CIS && desc.getConfiguration() != BondConfiguration::TRANS)
				continue;

			if (!desc.isValid(bond))
				continue;

			setStereoDescriptor(new_bond, desc);
		}
    }

	return flex_ring_sys;
}

void ConfGen::FragmentLibraryEntry::fixStereoDescriptors(const Chem::MolecularGraph& molgraph)
{
	using namespace Chem;

	MolecularGraph::ConstAtomIterator mg_a_it = molgraph.getAtomsBegin();

	for (AtomIterator it = molecule.getAtomsBegin(), end = molecule.getAtomsEnd(); it != end; ++it, ++mg_a_it) {
		Atom& atom = *it;

		if (!hasStereoDescriptor(atom))
			continue;

		const StereoDescriptor& stereo_desc = getStereoDescriptor(atom);
		unsigned int config = stereo_desc.getConfiguration();
		const Atom* const* ref_atoms = stereo_desc.getReferenceAtoms();

		try {
			if (stereo_desc.getNumReferenceAtoms() == 3) 
				setStereoDescriptor(atom, StereoDescriptor(config,
														   molecule.getAtom(molgraph.getAtomIndex(*ref_atoms[0])),
														   molecule.getAtom(molgraph.getAtomIndex(*ref_atoms[1])),
														   molecule.getAtom(molgraph.getAtomIndex(*ref_atoms[2]))));
			else
				setStereoDescriptor(atom, StereoDescriptor(config,
														   molecule.getAtom(molgraph.getAtomIndex(*ref_atoms[0])),
														   molecule.getAtom(molgraph.getAtomIndex(*ref_atoms[1])),
														   molecule.getAtom(molgraph.getAtomIndex(*ref_atoms[2])),
														   molecule.getAtom(molgraph.getAtomIndex(*ref_atoms[3]))));

		} catch (const Base::ItemNotFound& e) {
			clearStereoDescriptor(atom);
		} 
	}

	MolecularGraph::ConstBondIterator mg_b_it = molgraph.getBondsBegin();

	for (BondIterator it = molecule.getBondsBegin(), end = molecule.getBondsEnd(); it != end; ++it, ++mg_b_it) {
		Bond& bond = *it;

		if (!hasStereoDescriptor(bond))
			continue;

		const StereoDescriptor& stereo_desc = getStereoDescriptor(bond);
		const Atom* const* ref_atoms = stereo_desc.getReferenceAtoms();

		try {
			setStereoDescriptor(bond, StereoDescriptor(stereo_desc.getConfiguration(),
													   molecule.getAtom(molgraph.getAtomIndex(*ref_atoms[0])),
													   molecule.getAtom(molgraph.getAtomIndex(*ref_atoms[1])),
													   molecule.getAtom(molgraph.getAtomIndex(*ref_atoms[2])),
													   molecule.getAtom(molgraph.getAtomIndex(*ref_atoms[3]))));

		} catch (const Base::ItemNotFound& e) {
			clearStereoDescriptor(bond);
		} 
	}
}

void ConfGen::FragmentLibraryEntry::hydrogenize()
{
	using namespace Chem;

	for (std::size_t i = 0, num_atoms = molecule.getNumAtoms(); i < num_atoms; i++) {
		Atom& atom = molecule.getAtom(i);

		if (!(atom.getNumBonds() == 1 && getAromaticityFlag(atom))) {
			std::size_t impl_h_cnt = calcImplicitHydrogenCount(atom, molecule);

			for (std::size_t j = 0; j < impl_h_cnt; j++) {
				Atom& new_h_atom = molecule.addAtom();
				Bond& new_h_bond = molecule.addBond(i, molecule.getAtomIndex(new_h_atom));

				setType(new_h_atom, AtomType::H);
				setRingFlag(new_h_atom, false);
				setAromaticityFlag(new_h_atom, false);
				setHybridizationState(new_h_atom, HybridizationState::UNKNOWN);
				setImplicitHydrogenCount(new_h_atom, 0);

				setOrder(new_h_bond, 1);
				setRingFlag(new_h_bond, false);
				setAromaticityFlag(new_h_bond, false);
			}
		}

		setImplicitHydrogenCount(atom, 0);
	}
}

void ConfGen::FragmentLibraryEntry::canonicalize(bool stereo)
{
	using namespace Chem;

	if (stereo) {
		canonNumGen.setAtomPropertyFlags(AtomPropertyFlag::TYPE | AtomPropertyFlag::FORMAL_CHARGE |
										 AtomPropertyFlag::AROMATICITY | AtomPropertyFlag::CONFIGURATION |
										 AtomPropertyFlag::H_COUNT);
		canonNumGen.setBondPropertyFlags(BondPropertyFlag::ORDER | BondPropertyFlag::AROMATICITY | 
										 BondPropertyFlag::CONFIGURATION);
	} else {
		canonNumGen.setAtomPropertyFlags(AtomPropertyFlag::TYPE | AtomPropertyFlag::FORMAL_CHARGE |
										 AtomPropertyFlag::AROMATICITY | AtomPropertyFlag::H_COUNT);
		canonNumGen.setBondPropertyFlags(BondPropertyFlag::ORDER | BondPropertyFlag::AROMATICITY);
	}

	canonNumGen.generate(molecule, canonNumbers);

	molecule.orderAtoms(boost::bind(&FragmentLibraryEntry::compareCanonNumber, this, _1, _2));

	std::for_each(molecule.getAtomsBegin(), molecule.getAtomsEnd(), 
				  boost::bind(&Atom::orderAtoms, _1, &compareAtomIndex));

	std::for_each(molecule.getBondsBegin(), molecule.getBondsEnd(), 
				  boost::bind(&Bond::orderAtoms, _1, &compareAtomIndex));

	molecule.orderBonds(&compareBondAtomIndices);
}

void ConfGen::FragmentLibraryEntry::calcHashCode(bool stereo)
{
	using namespace Chem;

	hashInputData.clear();
	hashInputData.push_back(molecule.getNumAtoms());

	for (BasicMolecule::ConstAtomIterator it = molecule.getAtomsBegin(), end = molecule.getAtomsEnd(); it != end; ++it) {
		const Atom& atom = *it;

		hashInputData.push_back(getType(atom));
		hashInputData.push_back(getFormalCharge(atom) + 1000000);
		hashInputData.push_back(getAromaticityFlag(atom));
		hashInputData.push_back(getExplicitAtomCount(atom, AtomType::H));

		if (stereo && hasStereoDescriptor(atom)) {
			const StereoDescriptor& descr = getStereoDescriptor(atom);
			unsigned int perm_pty = (atom.getNumAtoms() == 3 ? descr.getPermutationParity(atom.getAtom(0), atom.getAtom(1), atom.getAtom(2)) :
									 descr.getPermutationParity(atom.getAtom(0), atom.getAtom(1), atom.getAtom(2), atom.getAtom(3)));

			if (perm_pty == 2) {
				hashInputData.push_back(descr.getConfiguration());
				continue;
			}

			if (perm_pty == 1) {
				hashInputData.push_back(descr.getConfiguration() == AtomConfiguration::R ? AtomConfiguration::S : AtomConfiguration::R);
				continue;
			}
		}

		hashInputData.push_back(AtomConfiguration::NONE);
	}

	hashInputData.push_back(molecule.getNumBonds());

	for (BasicMolecule::ConstBondIterator it = molecule.getBondsBegin(), end = molecule.getBondsEnd(); it != end; ++it) {
		const Bond& bond = *it;

		hashInputData.push_back(bond.getBegin().getIndex());
		hashInputData.push_back(bond.getEnd().getIndex());

		if (getAromaticityFlag(bond))
			hashInputData.push_back(4);
		else
			hashInputData.push_back(getOrder(bond));

		hashInputData.push_back(getRingFlag(bond));

		if (stereo && hasStereoDescriptor(bond)) { 
			const StereoDescriptor& descr = getStereoDescriptor(bond);
			const Atom* const* ref_atoms = descr.getReferenceAtoms();
			const Atom* li_nbr1 = getNeighborWithLowestIndex(ref_atoms[1], ref_atoms[2]); 
			const Atom* li_nbr2 = getNeighborWithLowestIndex(ref_atoms[2], ref_atoms[1]); 

			if (li_nbr1 && li_nbr2) {
				if ((li_nbr1 == ref_atoms[0]) ^ (li_nbr2 == ref_atoms[3]))
					hashInputData.push_back(descr.getConfiguration() == BondConfiguration::CIS ? BondConfiguration::TRANS : BondConfiguration::CIS);
				else
					hashInputData.push_back(descr.getConfiguration());

				continue;
			}
		}

		hashInputData.push_back(BondConfiguration::NONE);
	}

	Internal::SHA1 sha;
	Base::uint8 sha_hash[20];

	sha.input(hashInputData.begin(), hashInputData.end());
	sha.getResult(&sha_hash[0]);

	hashCode = 0;

	for (std::size_t i = 0; i < Internal::SHA1::HASH_SIZE; i++) 
		hashCode = hashCode ^ (Base::uint64(sha_hash[i]) << ((i % 8) * 8));
}

bool ConfGen::FragmentLibraryEntry::compareCanonNumber(const Chem::Atom& atom1, const Chem::Atom& atom2) const
{
	return (canonNumbers[atom1.getIndex()] < canonNumbers[atom2.getIndex()]);
}
