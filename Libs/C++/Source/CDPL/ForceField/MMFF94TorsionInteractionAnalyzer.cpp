/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * MMFF94TorsionInteractionAnalyzer.cpp 
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

#include <iterator>
#include <cstddef>

#include "CDPL/ForceField/MMFF94TorsionInteractionAnalyzer.hpp"
#include "CDPL/ForceField/MolecularGraphFunctions.hpp"
#include "CDPL/ForceField/AtomFunctions.hpp"
#include "CDPL/ForceField/BondFunctions.hpp"
#include "CDPL/Chem/MolecularGraph.hpp"
#include "CDPL/Chem/Atom.hpp"
#include "CDPL/Chem/Bond.hpp"
#include "CDPL/Chem/AtomFunctions.hpp"
#include "CDPL/Chem/BondFunctions.hpp"
#include "CDPL/Chem/AtomType.hpp"
#include "CDPL/Chem/UtilityFunctions.hpp"
#include "CDPL/Base/Exceptions.hpp"


using namespace CDPL; 


ForceField::MMFF94TorsionInteractionAnalyzer::MMFF94TorsionInteractionAnalyzer(const Chem::MolecularGraph& molgraph, 
																			   MMFF94TorsionInteractionList& iactions):
	filterFunc(), atomTypeFunc(&getMMFF94NumericType), bondTypeIdxFunc(&getMMFF94TypeIndex), 
	aromRingSetFunc(&getMMFF94AromaticRings), paramTable(MMFF94TorsionParameterTable::get(true)),
	typePropTable(MMFF94AtomTypePropertyTable::get()), paramTypeMap(MMFF94PrimaryToParameterAtomTypeMap::get())
{
    analyze(molgraph, iactions);
}

ForceField::MMFF94TorsionInteractionAnalyzer::MMFF94TorsionInteractionAnalyzer():
	filterFunc(), atomTypeFunc(&getMMFF94NumericType), bondTypeIdxFunc(&getMMFF94TypeIndex), 
	aromRingSetFunc(&getMMFF94AromaticRings), paramTable(MMFF94TorsionParameterTable::get(true)),
	typePropTable(MMFF94AtomTypePropertyTable::get()), paramTypeMap(MMFF94PrimaryToParameterAtomTypeMap::get())
{}

void ForceField::MMFF94TorsionInteractionAnalyzer::setFilterFunction(const InteractionFilterFunction4& func)
{
	filterFunc = func;
} 

void ForceField::MMFF94TorsionInteractionAnalyzer::setAtomTypeFunction(const MMFF94NumericAtomTypeFunction& func)
{
	atomTypeFunc = func;
}  

void ForceField::MMFF94TorsionInteractionAnalyzer::setBondTypeIndexFunction(const MMFF94BondTypeIndexFunction& func)
{
	bondTypeIdxFunc = func;
}  

void ForceField::MMFF94TorsionInteractionAnalyzer::setAromaticRingSetFunction(const MMFF94AromaticRingSetFunction& func)
{
	aromRingSetFunc = func;
}

void ForceField::MMFF94TorsionInteractionAnalyzer::setAtomTypePropertyTable(const MMFF94AtomTypePropertyTable::SharedPointer& table)
{
	typePropTable = table;
}

void ForceField::MMFF94TorsionInteractionAnalyzer::setTorsionParameterTable(const MMFF94TorsionParameterTable::SharedPointer& table)
{
	paramTable = table;
}

void ForceField::MMFF94TorsionInteractionAnalyzer::setParameterAtomTypeMap(const MMFF94PrimaryToParameterAtomTypeMap::SharedPointer& map)
{
	paramTypeMap = map;
}

void ForceField::MMFF94TorsionInteractionAnalyzer::analyze(const Chem::MolecularGraph& molgraph, 
														   MMFF94TorsionInteractionList& iactions)
{
	using namespace Chem;

	typedef MMFF94AtomTypePropertyTable::Entry AtomTypePropEntry;

	for (MolecularGraph::ConstBondIterator it = molgraph.getBondsBegin(), end = molgraph.getBondsEnd(); it != end; ++it) {
		const Bond& ctr_bond = *it;
		const Atom& ctr_atom1 = ctr_bond.getBegin();
		const Atom& ctr_atom2 = ctr_bond.getEnd();

		if (!molgraph.containsAtom(ctr_atom1) || !molgraph.containsAtom(ctr_atom2))  // sanity check
			continue;

		std::size_t ctr_atom1_idx = molgraph.getAtomIndex(ctr_atom1);
		unsigned int ctr_atom1_type = atomTypeFunc(ctr_atom1);
		const AtomTypePropEntry& ctr_atom1_prop_entry = typePropTable->getEntry(ctr_atom1_type);

		if (!ctr_atom1_prop_entry)
			throw Base::ItemNotFound("MMFF94TorsionInteractionAnalyzer: could not find MMFF94 atom type properties for atom #" + 
									 boost::lexical_cast<std::string>(ctr_atom1_idx));

		if (ctr_atom1_prop_entry.formsLinearBondAngle())
			continue;

		std::size_t ctr_atom2_idx = molgraph.getAtomIndex(ctr_atom2);
		unsigned int ctr_atom2_type = atomTypeFunc(ctr_atom2);
		const AtomTypePropEntry& ctr_atom2_prop_entry = typePropTable->getEntry(ctr_atom2_type);

		if (!ctr_atom2_prop_entry)
			throw Base::ItemNotFound("MMFF94TorsionInteractionAnalyzer: could not find MMFF94 atom type properties for atom #" + 
									 boost::lexical_cast<std::string>(ctr_atom2_idx));

		if (ctr_atom2_prop_entry.formsLinearBondAngle())
			continue;

		nbrAtoms1.clear();
		nbrBonds1.clear();

		getConnectedAtomsAndBonds(ctr_atom1, molgraph, std::back_inserter(nbrAtoms1), std::back_inserter(nbrBonds1));

		std::size_t num_nbrs1 = nbrAtoms1.size();

		if (num_nbrs1 <= 1)
			continue;

		nbrAtoms2.clear();
		nbrBonds2.clear();

		getConnectedAtomsAndBonds(ctr_atom2, molgraph, std::back_inserter(nbrAtoms2), std::back_inserter(nbrBonds2));

		std::size_t num_nbrs2 = nbrAtoms2.size();

		if (num_nbrs2 <= 1)
			continue;

		unsigned int ctr_bond_type_idx = bondTypeIdxFunc(ctr_bond);

		for (std::size_t i = 0; i < num_nbrs1; i++) {
			if (nbrAtoms1[i] == &ctr_atom2)
				continue;

			std::size_t term_atom1_idx = molgraph.getAtomIndex(*nbrAtoms1[i]);
			unsigned int term_atom1_type = atomTypeFunc(*nbrAtoms1[i]);
			unsigned int term_bond1_type_idx = bondTypeIdxFunc(*nbrBonds1[i]);

			for (std::size_t j = 0; j < num_nbrs2; j++) {
				if (nbrAtoms2[j] == &ctr_atom1)
					continue;
				
				std::size_t term_atom2_idx = molgraph.getAtomIndex(*nbrAtoms2[j]);
				unsigned int term_atom2_type = atomTypeFunc(*nbrAtoms2[j]);
				unsigned int term_bond2_type_idx = bondTypeIdxFunc(*nbrBonds2[j]);

				unsigned int tor_type_idx = getTorsionTypeIndex(molgraph, *nbrAtoms1[i], ctr_atom1, ctr_atom2, *nbrAtoms2[j], ctr_bond,
																term_atom1_type, ctr_atom1_type, ctr_atom2_type, term_atom2_type,
																term_bond1_type_idx, ctr_bond_type_idx, term_bond2_type_idx);
				double tor_param1 = 0.0;
				double tor_param2 = 0.0;
				double tor_param3 = 0.0;
																
				iactions.addElement(MMFF94TorsionInteraction(term_atom1_idx, ctr_atom1_idx, ctr_atom2_idx, term_atom2_idx, tor_type_idx,
															 tor_param1, tor_param2, tor_param3));
			}
		}
	}
}

unsigned int ForceField::MMFF94TorsionInteractionAnalyzer::getTorsionTypeIndex(const Chem::MolecularGraph& molgraph, const Chem::Atom& term_atom1, const Chem::Atom& ctr_atom1, 
																			   const Chem::Atom& ctr_atom2, const Chem::Atom& term_atom2, const Chem::Bond& ctr_bond,
																			   unsigned int term_atom1_type, unsigned int ctr_atom1_type, unsigned int ctr_atom2_type, 
																			   unsigned int term_atom2_type, unsigned int term_bond1_type_idx, unsigned int ctr_bond_type_idx,
																			   unsigned int term_bond2_type_idx) const
{
	using namespace Chem;

	bool in_3_ring = false;
	const Bond* bond = term_atom1.findBondToAtom(ctr_atom2);

	if (bond && molgraph.containsBond(*bond))
		in_3_ring = true;

	else {
		bond = term_atom2.findBondToAtom(ctr_atom1);

		if (bond && molgraph.containsBond(*bond))
			in_3_ring = true;
	}

	if (!in_3_ring) {
		bond = term_atom2.findBondToAtom(term_atom1);

		if (bond && molgraph.containsBond(*bond))
			return 4;
	}
  
    if (ctr_bond_type_idx == 1) 
		return 1;

    if ((term_bond1_type_idx == 1 || term_bond2_type_idx == 1) && getOrder(ctr_bond) == 1 && 
		!containsFragmentWithBond(*aromRingSetFunc(molgraph), ctr_bond))
        return 2;

    if (!in_3_ring && (term_atom1_type == 1 || ctr_atom1_type == 1 || ctr_atom2_type == 1 || term_atom2_type == 1)) { // have sp3 carbon?
		Atom::ConstBondIterator b_it = term_atom1.getBondsBegin();

		for (Atom::ConstAtomIterator a_it = term_atom1.getAtomsBegin(), a_end = term_atom1.getAtomsEnd(); a_it != a_end; ++a_it, ++b_it) {
			const Atom& nbr_atom = *a_it;

			if (&nbr_atom == &ctr_atom1)
				continue;

			if (!molgraph.containsAtom(nbr_atom) || !molgraph.containsBond(*b_it))
				continue;

			bond = nbr_atom.findBondToAtom(term_atom2);

			if (bond && molgraph.containsBond(*bond))
				return 5;
		}
	}

    return 0;
}
