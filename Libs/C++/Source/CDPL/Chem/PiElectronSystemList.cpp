/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * PiElectronSystemList.cpp 
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


#include "StaticInit.hpp"

#include <algorithm>

#include "CDPL/Chem/PiElectronSystemList.hpp"
#include "CDPL/Chem/Atom.hpp"
#include "CDPL/Chem/Bond.hpp"
#include "CDPL/Chem/AtomFunctions.hpp"
#include "CDPL/Chem/BondFunctions.hpp"
#include "CDPL/Chem/AtomDictionary.hpp"
#include "CDPL/Chem/AtomType.hpp"


using namespace CDPL;


namespace
{

	struct ElecSysCmpFunc
	{

		bool operator()(const Chem::ElectronSystem::SharedPointer& e_sys1, const Chem::ElectronSystem::SharedPointer& e_sys2) const {
			switch (e_sys1->getNumElectrons()) {

				case 0:
					return false;
					
				case 1:
					return (e_sys2->getNumElectrons() != 1);
					
				default:
					return (e_sys2->getNumElectrons() == 0);
			};
		}
	};
}


Chem::PiElectronSystemList::PiElectronSystemList() {}

Chem::PiElectronSystemList::PiElectronSystemList(const MolecularGraph& molgraph)
{
    perceive(molgraph);
}

void Chem::PiElectronSystemList::perceive(const MolecularGraph& molgraph)
{
    clear();
	
	initStartElecSystems(molgraph);
	mergeElecSystems(molgraph);

	insertElements(getElementsEnd(), workingElecSystems.begin(), workingElecSystems.end());
}

void Chem::PiElectronSystemList::initStartElecSystems(const MolecularGraph& molgraph)
{
	workingElecSystems.clear();

	for (MolecularGraph::ConstAtomIterator it = molgraph.getAtomsBegin(), end = molgraph.getAtomsEnd(); it != end; ++it) {
		const Atom& atom = *it;
		unsigned int type = getType(atom);
		std::size_t iupac_grp = AtomDictionary::getIUPACGroup(type);

		if (iupac_grp < 13 || iupac_grp > 17)
			continue;

		std::size_t num_bonds = getImplicitHydrogenCount(atom);
		Atom::ConstBondIterator nb_it = atom.getBondsBegin();

		for (Atom::ConstAtomIterator na_it = atom.getAtomsBegin(), na_end = atom.getAtomsEnd(); na_it != na_end; ++na_it, ++nb_it) {
			const Bond& bond = *nb_it;

			if (!molgraph.containsBond(bond))
				continue;

			if (!molgraph.containsAtom(*na_it))
				continue;

			num_bonds++;
		}

		long form_chg = getFormalCharge(atom);
		std::size_t num_sys = 4;

		if (type > AtomType::O) {

			switch (iupac_grp) {

				case 15:
					if (num_bonds >= 4)
						num_sys = 5;

					break;

				case 16:
					if (num_bonds == 3) {
						if (form_chg == 0)
							num_sys = 5;

					} else if (num_bonds >= 4)
						num_sys = 6;
					
					break;

				case 17:
					if (num_bonds == 2)
						num_sys = 5;

					else if (num_bonds == 3)
						num_sys = 6;

					else if (num_bonds >= 4)
						num_sys = 7;

				default:
					break;
			}
		}

		if (num_bonds >= num_sys)
			continue;

		num_sys -= num_bonds;

		long num_el = AtomDictionary::getNumValenceElectrons(type) - form_chg - num_bonds;
		std::size_t el_cnts[7];

		std::fill(el_cnts, el_cnts + num_sys, 0);

		for (long i = 0; i < num_el; i++)
			el_cnts[i % num_sys] += 1;

		std::size_t num_lps = 0;

		for ( ; num_lps < num_sys && el_cnts[num_lps] == 2; num_lps++);
		
		std::size_t max_lp_cnt = 1; // allow only at most one lone-pair to be part of a pi-system

		if (num_lps < num_sys && el_cnts[num_lps] > 0)
			max_lp_cnt = 0;
				
		for (std::size_t i = 0; i < num_sys; i++) {
			ElectronSystem::SharedPointer e_sys(new ElectronSystem());
			
			e_sys->addAtom(atom, el_cnts[i]);

			if (num_lps >= 1 && i < (num_lps - max_lp_cnt)) 
				addElement(e_sys);
			else
				workingElecSystems.push_back(e_sys);
		}
	}
}

void Chem::PiElectronSystemList::mergeElecSystems(const MolecularGraph& molgraph)
{
	workingElecSystems.sort(ElecSysCmpFunc()); 	// elec. system merge priority: single electron > lone-pair > empty system

	mergeElecSystemsPass1(molgraph);
	mergeElecSystemsPass2(molgraph);
}

void Chem::PiElectronSystemList::mergeElecSystemsPass1(const MolecularGraph& molgraph)
{
	for (WorkingElecSysList::iterator it1 = workingElecSystems.begin(); it1 != workingElecSystems.end(); ++it1) {
		ElectronSystem& e_sys1 = **it1;
		std::size_t num_el1 = e_sys1.getNumElectrons();

		if (num_el1 == 0) // don't merge empty systems
			break;

		for (bool merges = true, sys1_is_lp = (e_sys1.getNumAtoms() == 1 && num_el1 == 2); merges; ) {
			merges = false;
			WorkingElecSysList::iterator it2 = it1;
			
			for (++it2; it2 != workingElecSystems.end(); ++it2) {
				const ElectronSystem& e_sys2 = **it2;
		
				if (sys1_is_lp && e_sys2.getNumAtoms() == 1 && e_sys2.getNumElectrons() == 2) // don't merge two lone-pairs
					continue;
				
				if (e_sys1.connected(e_sys2, molgraph)) {
					e_sys1.addAtoms(e_sys2);
					workingElecSystems.erase(it2);

					merges = true;
					sys1_is_lp = false;
					break;
				}
			}
		}
	}
}

void Chem::PiElectronSystemList::mergeElecSystemsPass2(const MolecularGraph& molgraph) // merge split pi-systems of cumulenes with even number of bonds (helical orbitals)
{
	for (WorkingElecSysList::iterator it1 = workingElecSystems.begin(); it1 != workingElecSystems.end(); ++it1) {
		ElectronSystem& e_sys1 = **it1;

		if (e_sys1.getNumElectrons() == 0) // don't merge empty systems
			break;

		bool sys1_maybe_cumulene = ((e_sys1.getNumAtoms() % 2) == 1 && isLinChainPiSysWith1ElecPerAtom(e_sys1, molgraph));
		WorkingElecSysList::iterator it2 = it1;

		for (++it2; it2 != workingElecSystems.end(); ++it2) {
			const ElectronSystem& e_sys2 = **it2;
		
			if ((sys1_maybe_cumulene && isCumuleneSubPiSystem(e_sys1, e_sys2, molgraph)) || 
				((e_sys2.getNumAtoms() % 2) == 1 && isLinChainPiSysWith1ElecPerAtom(e_sys2, molgraph) && isCumuleneSubPiSystem(e_sys2, e_sys1, molgraph))) {

				e_sys1.merge(e_sys2);
				workingElecSystems.erase(it2);
				break;
			}
		}
	}
}

bool Chem::PiElectronSystemList::isCumuleneSubPiSystem(const ElectronSystem& sub_e_sys, const ElectronSystem& parent_e_sys, const MolecularGraph& molgraph) const 
{
	if (parent_e_sys.getNumAtoms() <= sub_e_sys.getNumAtoms())
		return false;

	for (ElectronSystem::ConstAtomIterator a_it = sub_e_sys.getAtomsBegin(), a_end = sub_e_sys.getAtomsEnd(); a_it != a_end; ++a_it) {
		const Atom& atom = *a_it;

		if (!parent_e_sys.containsAtom(atom) || parent_e_sys.getElectronContrib(atom) != 1 || !has2NeighborsWith1Elec(atom, parent_e_sys, molgraph))
			return false;
	}

	return true;
}

bool Chem::PiElectronSystemList::isLinChainPiSysWith1ElecPerAtom(const ElectronSystem& e_sys, const MolecularGraph& molgraph) const
{
	if (e_sys.getNumAtoms() == 1) 
		return (e_sys.getElectronContrib(e_sys.getAtom(0)) == 1);

	std::size_t num_term_atoms = 0;

	for (ElectronSystem::ConstAtomIterator it = e_sys.getAtomsBegin(), end = e_sys.getAtomsEnd(); it != end; ++it) {
		const Atom& atom = *it;

		if (e_sys.getElectronContrib(atom) != 1)
			return false;

		Atom::ConstBondIterator nb_it = atom.getBondsBegin();
		std::size_t num_e_sys_nbrs = 0;

		for (Atom::ConstAtomIterator na_it = atom.getAtomsBegin(), na_end = atom.getAtomsEnd(); na_it != na_end; ++na_it, ++nb_it) {
			if (!molgraph.containsBond(*nb_it))
				continue;

			if (!molgraph.containsAtom(*na_it))
				continue;

			if (e_sys.containsAtom(*na_it))
				if (++num_e_sys_nbrs > 2)
					return false;
		}

		switch (num_e_sys_nbrs) {

			case 1:
				num_term_atoms++;

			case 2:
				continue;

			default:
				return false;
		}
	}

	return (num_term_atoms == 2);
}

bool Chem::PiElectronSystemList::has2NeighborsWith1Elec(const Atom& atom, const ElectronSystem& e_sys, const MolecularGraph& molgraph) const
{
	Atom::ConstBondIterator nb_it = atom.getBondsBegin();
	std::size_t num_e_sys_nbrs = 0;

	for (Atom::ConstAtomIterator na_it = atom.getAtomsBegin(), na_end = atom.getAtomsEnd(); na_it != na_end; ++na_it, ++nb_it) {
		if (!molgraph.containsBond(*nb_it))
			continue;

		const Atom& nbr_atom = *na_it;

		if (!molgraph.containsAtom(nbr_atom))
			continue;

		if (e_sys.containsAtom(nbr_atom)) {
			if (e_sys.getElectronContrib(nbr_atom) != 1)
				continue;

			num_e_sys_nbrs++;
		}
	}

	return (num_e_sys_nbrs >= 2);
}
