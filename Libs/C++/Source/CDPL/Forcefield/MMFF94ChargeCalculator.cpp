/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * MMFF94ChargeCalculator.cpp 
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

#include <string>
#include <algorithm>

#include <boost/bind.hpp>
#include <boost/lexical_cast.hpp>

#include "CDPL/Forcefield/MMFF94ChargeCalculator.hpp"
#include "CDPL/Forcefield/MolecularGraphFunctions.hpp"
#include "CDPL/Forcefield/AtomFunctions.hpp"
#include "CDPL/Forcefield/BondFunctions.hpp"
#include "CDPL/Chem/FragmentList.hpp"
#include "CDPL/Chem/Fragment.hpp"
#include "CDPL/Chem/Atom.hpp"
#include "CDPL/Chem/Bond.hpp"
#include "CDPL/Chem/AtomFunctions.hpp"
#include "CDPL/Base/Exceptions.hpp"


using namespace CDPL; 


namespace
{

	bool symbolicTypeInList(const std::string& type, const std::string& type_list)
	{
	
		for (std::string::size_type pos = 0; (pos = type_list.find(type, pos)) != std::string::npos; pos++) {
			if (pos > 0 && type_list[pos - 1] != ',')
				continue;
			
			if ((pos + type.length()) < type_list.length() && type_list[pos + type.length()] != ',')
				continue;

			return true;
		}

		return false;
	}
}


Forcefield::MMFF94ChargeCalculator::MMFF94ChargeCalculator(const Chem::MolecularGraph& molgraph, Util::DArray& charges):
    aromRingSetFunc(&getMMFF94AromaticRings), numAtomTypeFunc(&getMMFF94NumericType), symAtomTypeFunc(&getMMFF94SymbolicType), 
	bondTypeIdxFunc(getMMFF94TypeIndex)
{
	setBondChargeIncrementTable(MMFF94BondChargeIncrementTable::get());
	setPartialBondChargeIncrementTable(MMFF94PartialBondChargeIncrementTable::get());
	setAtomTypePropertyTable(MMFF94AtomTypePropertyTable::get());
	setFormalChargeDefinitionTable(MMFF94FormalAtomChargeDefinitionTable::get());

	calculate(molgraph, charges);
}

Forcefield::MMFF94ChargeCalculator::MMFF94ChargeCalculator(): 
	aromRingSetFunc(&getMMFF94AromaticRings), numAtomTypeFunc(&getMMFF94NumericType), symAtomTypeFunc(&getMMFF94SymbolicType),
	bondTypeIdxFunc(getMMFF94TypeIndex)
{
	setBondChargeIncrementTable(MMFF94BondChargeIncrementTable::get());
	setPartialBondChargeIncrementTable(MMFF94PartialBondChargeIncrementTable::get());
	setAtomTypePropertyTable(MMFF94AtomTypePropertyTable::get());
	setFormalChargeDefinitionTable(MMFF94FormalAtomChargeDefinitionTable::get());
}

void Forcefield::MMFF94ChargeCalculator::setBondChargeIncrementTable(const MMFF94BondChargeIncrementTable::SharedPointer& table)
{
	bondChargeIncTable = table;
}

void Forcefield::MMFF94ChargeCalculator::setPartialBondChargeIncrementTable(const MMFF94PartialBondChargeIncrementTable::SharedPointer& table)
{
	partBondChargeIncTable = table;
}

void Forcefield::MMFF94ChargeCalculator::setAtomTypePropertyTable(const MMFF94AtomTypePropertyTable::SharedPointer& table)
{
	atomTypePropTable = table;
}

void Forcefield::MMFF94ChargeCalculator::setFormalChargeDefinitionTable(const MMFF94FormalAtomChargeDefinitionTable::SharedPointer& table)
{
	formChargeDefTable = table;
}

void Forcefield::MMFF94ChargeCalculator::setAromaticRingSetFunction(const MMFF94AromaticRingSetFunction& func)
{
	aromRingSetFunc = func;
}

void Forcefield::MMFF94ChargeCalculator::setNumericAtomTypeFunction(const MMFF94NumericAtomTypeFunction& func)
{
	numAtomTypeFunc = func;
}

void Forcefield::MMFF94ChargeCalculator::setSymbolicAtomTypeFunction(const MMFF94SymbolicAtomTypeFunction& func)
{
	symAtomTypeFunc = func;
}

void Forcefield::MMFF94ChargeCalculator::setBondTypeIndexFunction(const MMFF94BondTypeIndexFunction& func)
{
	bondTypeIdxFunc = func;
}

void Forcefield::MMFF94ChargeCalculator::calculate(const Chem::MolecularGraph& molgraph, Util::DArray& charges)
{
	init(molgraph, charges);

	assignFormalCharges();
	calcPartialCharges(charges);
}

const Util::DArray& Forcefield::MMFF94ChargeCalculator::getFormalCharges() const
{
	return formCharges;
}

void Forcefield::MMFF94ChargeCalculator::init(const Chem::MolecularGraph& molgraph, Util::DArray& charges)
{
	std::size_t num_atoms = molgraph.getNumAtoms();

	formCharges.assign(num_atoms, 0.0);
	charges.assign(num_atoms, 0.0);
	assFormChargeMask.resize(num_atoms);
	assFormChargeMask.reset();

	molGraph = &molgraph;
}

void Forcefield::MMFF94ChargeCalculator::assignFormalCharges()
{
	using namespace Chem;
	
	std::size_t i = 0;

	for (MolecularGraph::ConstAtomIterator it = molGraph->getAtomsBegin(), end = molGraph->getAtomsEnd(); it != end; ++it, i++) {
		const Atom& atom = *it;

		if (assFormChargeMask.test(i))
			continue;

		const std::string& sym_type = symAtomTypeFunc(atom);
		const FormChargeDefEntry& entry = formChargeDefTable->getEntry(sym_type);

		if (!entry)
			continue;

		if (entry.getAssignmentMode() == 0) {
			formCharges[i] = entry.getFormalCharge();
			continue;
		}

		if (entry.getAssignmentMode() == 1) {
			distFormalNeighborCharges(atom, entry);
			continue;
		}

		if (entry.getAssignmentMode() >= 3)
			distFormalAromAtomCharges(atom, entry);
	}
}

void Forcefield::MMFF94ChargeCalculator::distFormalAromAtomCharges(const Chem::Atom& atom, const FormChargeDefEntry& entry)
{
	using namespace Chem;

	atomList.clear();

	double net_charge = entry.getFormalCharge();
	const FragmentList::SharedPointer& arom_rings = aromRingSetFunc(*molGraph);

	for (FragmentList::ConstElementIterator r_it = arom_rings->getElementsBegin(), r_end = arom_rings->getElementsEnd(); r_it != r_end; ++r_it) {
		const Fragment& ring = *r_it;

		if (!ring.getNumAtoms() == entry.getAssignmentMode())
			continue;

		if (!ring.containsAtom(atom))
			continue;

		for (Fragment::ConstAtomIterator a_it = ring.getAtomsBegin(), a_end = ring.getAtomsEnd(); a_it != a_end; ++a_it) {
			const Atom& rng_atom = *a_it;

			if (!symbolicTypeInList(symAtomTypeFunc(rng_atom), entry.getAtomTypeList()))
				continue;

			if (entry.getFormalCharge() == 0.0)
				net_charge += getFormalCharge(rng_atom);

			atomList.push_back(molGraph->getAtomIndex(rng_atom));
		}

		if (atomList.empty())
			continue;

		net_charge /= atomList.size();

		for (AtomIndexList::const_iterator it = atomList.begin(), end = atomList.end(); it != end; ++it) {
			std::size_t atom_idx = *it;

			assFormChargeMask.set(atom_idx);
			formCharges[atom_idx] = net_charge;
		}
	}
}

void Forcefield::MMFF94ChargeCalculator::distFormalNeighborCharges(const Chem::Atom& atom, const FormChargeDefEntry& entry)
{
	using namespace Chem;

	atomList.clear();

	double nbr_charge = (entry.getFormalCharge() == 0.0 ? getFormalCharge(atom) : entry.getFormalCharge());
	Atom::ConstAtomIterator a_it = atom.getAtomsBegin();

	for (Atom::ConstBondIterator b_it = atom.getBondsBegin(), b_end = atom.getBondsEnd(); b_it != b_end; ++b_it, ++a_it) {
		const Bond& nbr_bond = *b_it;
			
		if (!molGraph->containsBond(nbr_bond))
			continue;

		const Atom& nbr_atom = *a_it;

		if (!molGraph->containsAtom(nbr_atom))
			continue;

		if (!symbolicTypeInList(symAtomTypeFunc(nbr_atom), entry.getAtomTypeList()))
			continue;

		if (entry.getFormalCharge() == 0.0)
			nbr_charge += getFormalCharge(nbr_atom);

		atomList.push_back(molGraph->getAtomIndex(nbr_atom));
	}

	if (atomList.empty())
		return;

	nbr_charge /= atomList.size();

	for (AtomIndexList::const_iterator it = atomList.begin(), end = atomList.end(); it != end; ++it) {
		std::size_t atom_idx = *it;

		assFormChargeMask.set(atom_idx);
		formCharges[atom_idx] = nbr_charge;
	}
}

void Forcefield::MMFF94ChargeCalculator::calcPartialCharges(Util::DArray& charges) const
{
	using namespace Chem;

	for (std::size_t i = 0, num_atoms = molGraph->getNumAtoms(); i < num_atoms; i++) {
		const Atom& atom = molGraph->getAtom(i);
        unsigned int atom_type = numAtomTypeFunc(atom);

		const PBCIEntry& pbci_entry = partBondChargeIncTable->getEntry(atom_type);

		if (!pbci_entry)
			throw Base::ItemNotFound("MMFF94ChargeCalculator: could not find MMFF94 partial bond charge increment parameters for atom #" + 
									 boost::lexical_cast<std::string>(i));
	
		const TypePropertyEntry& prop_entry = atomTypePropTable->getEntry(atom_type);

		if (!prop_entry)
			throw Base::ItemNotFound("MMFF94ChargeCalculator: could not find MMFF94 atom type properties for atom #" + 
									 boost::lexical_cast<std::string>(i));

        double form_chg_adj_factor = pbci_entry.getFormalChargeAdjustmentFactor(); // uI
        double form_chg = formCharges[i];                                          // q0I
		std::size_t num_mand_nbrs = prop_entry.getNumNeighbors();                  // MI

        double charge = (1.0 - num_mand_nbrs * form_chg_adj_factor) * form_chg;    // (1 - MI * uI) * q0I

		Atom::ConstAtomIterator a_it = atom.getAtomsBegin();

        for (Atom::ConstBondIterator b_it = atom.getBondsBegin(), b_end = atom.getBondsEnd(); b_it != b_end; ++b_it, ++a_it) {
			const Bond& nbr_bond = *b_it;

			if (!molGraph->containsBond(nbr_bond))
				continue;

			const Atom& nbr_atom = *a_it;

			if (!molGraph->containsAtom(nbr_atom))
				continue;
			
			std::size_t nbr_atom_idx = molGraph->getAtomIndex(nbr_atom);
			unsigned int nbr_atom_type = numAtomTypeFunc(nbr_atom);

			const PBCIEntry& nbr_pbci_entry = partBondChargeIncTable->getEntry(nbr_atom_type);

			if (!nbr_pbci_entry)
				throw Base::ItemNotFound("MMFF94ChargeCalculator: could not find MMFF94 partial bond charge increment parameters for atom #" + 
										 boost::lexical_cast<std::string>(nbr_atom_idx));
	
			const TypePropertyEntry& nbr_prop_entry = atomTypePropTable->getEntry(nbr_atom_type);

			if (!nbr_prop_entry)
				throw Base::ItemNotFound("MMFF94ChargeCalculator: could not find MMFF94 atom type properties for atom #" + 
										 boost::lexical_cast<std::string>(nbr_atom_idx));

			double nbr_form_chg = formCharges[nbr_atom_idx];                                   // q0K
			double nbr_form_chg_adj_factor = nbr_pbci_entry.getFormalChargeAdjustmentFactor(); // uK

			charge += nbr_form_chg_adj_factor * nbr_form_chg;                                  // qi += uK * q0K
				
			double bond_chg_inc = getBondChargeIncrement(bondTypeIdxFunc(nbr_bond), nbr_atom_type, atom_type, 
														 nbr_pbci_entry, pbci_entry);                            // wKI
			charge += bond_chg_inc;                                                                              // qi += wKI
		}

        charges[i] = charge;
	}
}

double Forcefield::MMFF94ChargeCalculator::getBondChargeIncrement(unsigned int bnd_type_idx, unsigned int atom_type1, unsigned int atom_type2, 
																  const PBCIEntry& pbci_entry1, const PBCIEntry& pbci_entry2) const
{
	if (atom_type1 == atom_type2)
		return 0.0;

	const BCIEntry& bci_entry1 = bondChargeIncTable->getEntry(bnd_type_idx, atom_type1, atom_type2);

	if (bci_entry1)
		return bci_entry1.getChargeIncrement();

	const BCIEntry& bci_entry2 = bondChargeIncTable->getEntry(bnd_type_idx, atom_type2, atom_type1);

	if (bci_entry2)
		return -bci_entry2.getChargeIncrement();

    return (pbci_entry2.getPartialChargeIncrement() - pbci_entry1.getPartialChargeIncrement());
}
