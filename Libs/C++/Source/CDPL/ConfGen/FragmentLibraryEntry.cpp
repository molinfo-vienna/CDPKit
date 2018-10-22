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

#include "CDPL/ConfGen/FragmentLibraryEntry.hpp"
#include "CDPL/Chem/Atom.hpp"
#include "CDPL/Chem/Bond.hpp"
#include "CDPL/Chem/StereoDescriptor.hpp"
#include "CDPL/Chem/Entity3DFunctions.hpp"
#include "CDPL/Chem/AtomFunctions.hpp"
#include "CDPL/Chem/BondFunctions.hpp"
#include "CDPL/Chem/MolecularGraphFunctions.hpp"
#include "CDPL/Chem/AtomType.hpp"
#include "CDPL/Chem/HybridizationState.hpp"
#include "CDPL/Chem/AtomConfiguration.hpp"
#include "CDPL/Chem/BondConfiguration.hpp"
#include "CDPL/Chem/AtomPropertyFlag.hpp"
#include "CDPL/Chem/BondPropertyFlag.hpp"


using namespace CDPL;


ConfGen::FragmentLibraryEntry::FragmentLibraryEntry(): hashCode(0)
{}
	  
ConfGen::FragmentLibraryEntry::FragmentLibraryEntry(const FragmentLibraryEntry& entry):  
	Chem::MolecularGraph(entry), molecule(entry.molecule), hashCode(entry.hashCode)
{}

ConfGen::FragmentLibraryEntry::FragmentLibraryEntry(const Chem::MolecularGraph& molgraph)
{
    create(molgraph);
}

void ConfGen::FragmentLibraryEntry::clear()
{
    clearProperties();

    molecule.clear();
	hashCode = 0;
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

	return *this;
}
	
void ConfGen::FragmentLibraryEntry::create(const Chem::MolecularGraph& molgraph)
{
    clear();
	copyAtoms(molgraph);

	bool ring_rsys = copyBonds(molgraph);

	fixStereoDescriptors(molgraph);
	hydrogenize();
	calcHashCode(ring_rsys);
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

		if (exp_atom_count == 1 && have_arom_ring_nbr) {
			setType(new_atom, AtomType::H);
			setAromaticityFlag(new_atom, false);
			setRingFlag(new_atom, false);
			setHybridizationState(new_atom, HybridizationState::UNKNOWN);
			continue;
		} 

		if (exp_atom_count >= 3) {
			const StereoDescriptor& desc = getStereoDescriptor(atom);
	
			if ((desc.getConfiguration() == AtomConfiguration::R || desc.getConfiguration() == AtomConfiguration::S) && desc.isValid(atom))
				setStereoDescriptor(new_atom, desc);
		}

		if (has3DCoordinates(atom))
			set3DCoordinates(new_atom, get3DCoordinates(atom));

		setType(new_atom, atom_type);
		setIsotope(new_atom, getIsotope(atom));
		setFormalCharge(new_atom, getFormalCharge(atom));
		setRingFlag(new_atom, getRingFlag(atom));

		bool arom_flag = getAromaticityFlag(atom);

		setAromaticityFlag(new_atom, arom_flag);
		
		unsigned int hyb_state = getHybridizationState(atom);

		setHybridizationState(new_atom, hyb_state);
	
		if (arom_flag || (atom_type != AtomType::N && atom_type != AtomType::C) || exp_atom_count != 1)
			continue;
		
		if (hyb_state == HybridizationState::SP) {
			std::size_t exp_val = calcExplicitValence(atom, molgraph);

			if (exp_val == 1)
				setUnpairedElectronCount(new_atom, 2);
			else if (exp_val == 2)
				setUnpairedElectronCount(new_atom, 1);

		} else if (hyb_state == HybridizationState::SP2) {
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

	bool ring_sys = false;

    for (MolecularGraph::ConstBondIterator it = molgraph.getBondsBegin(), end =  molgraph.getBondsEnd(); it != end; ++it) {
		const Bond& bond = *it;
		const Atom& atom1 = bond.getBegin();
		const Atom& atom2 = bond.getEnd();

		if (!molgraph.containsAtom(atom1) || !molgraph.containsAtom(atom2))
			continue;

		bool ring_flag = getRingFlag(bond);
	
		if (ring_flag)
			ring_sys = true;

		bool arom_flag = getAromaticityFlag(bond);
		std::size_t order = getOrder(bond);
		Bond& new_bond = molecule.addBond(molgraph.getAtomIndex(atom1), molgraph.getAtomIndex(atom2));

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

	return ring_sys;
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
			continue;
		} catch (const Base::ItemNotFound& e) {} 
		
		clearStereoDescriptor(atom);
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
			continue;
		} catch (const Base::ItemNotFound& e) {} 

		clearStereoDescriptor(bond);
	}
}

void ConfGen::FragmentLibraryEntry::hydrogenize()
{
	using namespace Chem;

	for (std::size_t i = 0, num_atoms = molecule.getNumAtoms(); i < num_atoms; i++) {
		Atom& atom = molecule.getAtom(i);

		setImplicitHydrogenCount(atom, 0);

		if (atom.getNumBonds() == 1 && getAromaticityFlag(atom))
			continue;
		
		for (std::size_t j = 0, impl_h_cnt = calcImplicitHydrogenCount(atom, molecule); j < impl_h_cnt; j++) {
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
}

void ConfGen::FragmentLibraryEntry::calcHashCode(bool stereo)
{
	using namespace Chem;

	if (stereo) {
		cipPriorityCalc.calculate(molecule, cipPriorities);

		for (std::size_t i = 0, num_atoms = molecule.getNumAtoms(); i < num_atoms; i++)
			setCIPPriority(molecule.getAtom(i), cipPriorities[i]);

		calcAtomCIPConfigurations(molecule, true);
		calcBondCIPConfigurations(molecule, true);

		hashCodeCalc.setAtomHashSeedFunction(HashCodeCalculator::DefAtomHashSeedFunctor(hashCodeCalc, 
																						AtomPropertyFlag::TYPE | 
																						AtomPropertyFlag::FORMAL_CHARGE |
																						AtomPropertyFlag::AROMATICITY |
																						AtomPropertyFlag::CONFIGURATION));
		hashCodeCalc.setBondHashSeedFunction(HashCodeCalculator::DefBondHashSeedFunctor(hashCodeCalc, 
																						BondPropertyFlag::ORDER | 
																						BondPropertyFlag::TOPOLOGY |
																						BondPropertyFlag::AROMATICITY |
																						BondPropertyFlag::CONFIGURATION));
		hashCodeCalc.includeGlobalStereoFeatures(true);

	} else {
		hashCodeCalc.setAtomHashSeedFunction(HashCodeCalculator::DefAtomHashSeedFunctor(hashCodeCalc, 
																						AtomPropertyFlag::TYPE | 
																						AtomPropertyFlag::FORMAL_CHARGE |
																						AtomPropertyFlag::AROMATICITY));
		hashCodeCalc.setBondHashSeedFunction(HashCodeCalculator::DefBondHashSeedFunctor(hashCodeCalc, 
																						BondPropertyFlag::ORDER | 
																						BondPropertyFlag::TOPOLOGY |
																						BondPropertyFlag::AROMATICITY));
		hashCodeCalc.includeGlobalStereoFeatures(false);

	}

	hashCode = hashCodeCalc.calculate(molecule);
}
