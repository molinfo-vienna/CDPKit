/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * BondStereoFlagGenerator.cpp 
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

#include <cassert>
#include <functional>
#include <algorithm>
#include <utility>

#define BOOST_BIND_GLOBAL_PLACEHOLDERS
#include <boost/bind.hpp>

#include "CDPL/Chem/BondStereoFlagGenerator.hpp"
#include "CDPL/Chem/Atom.hpp"
#include "CDPL/Chem/Bond.hpp"
#include "CDPL/Chem/AtomFunctions.hpp"
#include "CDPL/Chem/BondFunctions.hpp"
#include "CDPL/Chem/AtomConfiguration.hpp"
#include "CDPL/Chem/BondConfiguration.hpp"
#include "CDPL/Chem/BondStereoFlag.hpp"
#include "CDPL/Chem/AtomType.hpp"
#include "CDPL/Chem/StereoDescriptor.hpp"


using namespace CDPL;


Chem::BondStereoFlagGenerator::BondStereoFlagGenerator(): coordsFunc(&get2DCoordinates) {}

Chem::BondStereoFlagGenerator::BondStereoFlagGenerator(const MolecularGraph& molgraph, Util::UIArray& flags): coordsFunc(&get2DCoordinates)
{
	generate(molgraph, flags);
}

void Chem::BondStereoFlagGenerator::setAtom2DCoordinatesFunction(const Atom2DCoordinatesFunction& func)
{
	coordsFunc = func;
}

const Chem::BondStereoFlagGenerator::Atom2DCoordinatesFunction& Chem::BondStereoFlagGenerator::getAtom2DCoordinatesFunction() const
{
	return coordsFunc;
}

void Chem::BondStereoFlagGenerator::generate(const MolecularGraph& molgraph, Util::UIArray& flags)
{
	init(molgraph, flags);

	assignStereoFlags(flags);
}

void Chem::BondStereoFlagGenerator::init(const MolecularGraph& molgraph, Util::UIArray& flags)
{
	molGraph = &molgraph;

	std::size_t num_atoms = molgraph.getNumAtoms();

	configMatchMask.resize(num_atoms);
	configMatchMask.reset();

	stereoDBAtomMask.resize(num_atoms);
	stereoDBAtomMask.reset();

	stereoAtomMask.resize(num_atoms);
	stereoAtomMask.reset();

	stereoAtomTable.clear();
	stereoAtomList.clear();

	std::size_t num_bonds = molgraph.getNumBonds();

	ringBondMask.resize(num_bonds);
	ringBondMask.reset();

	singleBondMask.resize(num_bonds);
	singleBondMask.reset();

	eitherBondList.clear();

	flags.assign(num_bonds, BondStereoFlag::PLAIN);

	numMismatchingCtrs = 0;
	minNumMismatchingCtrs = num_atoms + 1;

	MolecularGraph::ConstAtomIterator atoms_end = molgraph.getAtomsEnd();

	for (MolecularGraph::ConstAtomIterator it = molgraph.getAtomsBegin(); it != atoms_end; ++it) {
		const Atom& atom = *it;
		std::size_t num_bonds = atom.getNumBonds();

		if (num_bonds < 3 || num_bonds > 4 || (hasStereoCenterFlag(atom) && !getStereoCenterFlag(atom))) {
			stereoAtomTable.push_back(StereoAtomInfo::SharedPointer());
			continue;
		}

		const StereoDescriptor& stereo_desc = getStereoDescriptor(atom);
		unsigned int config = stereo_desc.getConfiguration();

		if (config != AtomConfiguration::EITHER && config != AtomConfiguration::R && 
			config != AtomConfiguration::S) {
			stereoAtomTable.push_back(StereoAtomInfo::SharedPointer());
			continue;
		}

		const Atom* nbr_atoms[4];
		const Bond* nbr_bonds[4];

		Atom::ConstAtomIterator nbr_atoms_end = atom.getAtomsEnd();
		Atom::ConstBondIterator b_it = atom.getBondsBegin();
		
		num_bonds = 0;

		for (Atom::ConstAtomIterator a_it = atom.getAtomsBegin(); a_it != nbr_atoms_end; ++a_it, ++b_it) {
			const Atom& nbr_atom = *a_it;
			const Bond& nbr_bond = *b_it;

			if (!molgraph.containsAtom(nbr_atom) || !molgraph.containsBond(nbr_bond))
				continue;

			nbr_atoms[num_bonds] = &nbr_atom;
			nbr_bonds[num_bonds++] = &nbr_bond;
		}

		if (num_bonds < 3) {
			stereoAtomTable.push_back(StereoAtomInfo::SharedPointer());
			continue;
		}

		unsigned int perm_parity = (num_bonds == 3 ? 
									stereo_desc.getPermutationParity(*nbr_atoms[0], *nbr_atoms[1], *nbr_atoms[2]) :
									stereo_desc.getPermutationParity(*nbr_atoms[0], *nbr_atoms[1], *nbr_atoms[2], *nbr_atoms[3]));
	
		StereoAtomInfo::SharedPointer info_ptr;

		if (perm_parity == 1) 
			info_ptr.reset(new StereoAtomInfo(molGraph, coordsFunc, &atom, config == AtomConfiguration::R ? AtomConfiguration::S : 
											  config == AtomConfiguration::S ? AtomConfiguration::R : AtomConfiguration::EITHER, 
											  num_bonds, nbr_atoms, nbr_bonds));
		else if (perm_parity == 2) 
			info_ptr.reset(new StereoAtomInfo(molGraph, coordsFunc, &atom, config, num_bonds, nbr_atoms, nbr_bonds));

		else if (config == AtomConfiguration::EITHER) 
			info_ptr.reset(new StereoAtomInfo(molGraph, coordsFunc, &atom, config, num_bonds, nbr_atoms, nbr_bonds));

		else {
			stereoAtomTable.push_back(StereoAtomInfo::SharedPointer());
			continue;
		}

		stereoAtomTable.push_back(info_ptr);
		stereoAtomList.push_back(info_ptr.get());
		stereoAtomMask.set(molgraph.getAtomIndex(atom));
	}

	MolecularGraph::ConstBondIterator bonds_end = molgraph.getBondsEnd();

	for (MolecularGraph::ConstBondIterator it = molgraph.getBondsBegin(); it != bonds_end; ++it) {
		const Bond& bond = *it;

		if (getOrder(bond) == 1)
			singleBondMask.set(molgraph.getBondIndex(bond));
	}

	std::for_each(molgraph.getBondsBegin(), molgraph.getBondsEnd(),
				  boost::bind(&Util::BitSet::set, 
							  boost::ref(ringBondMask), 
							  boost::bind(&MolecularGraph::getBondIndex, molGraph, _1),
							  boost::bind(static_cast<bool (*)(const Bond&)>(&getRingFlag), _1)));

	std::for_each(stereoAtomList.begin(), stereoAtomList.end(), 
				  boost::bind(&StereoAtomInfo::findBestBondOrder, _1, boost::ref(stereoAtomMask),
							  boost::ref(ringBondMask)));
}

void Chem::BondStereoFlagGenerator::assignStereoFlags(Util::UIArray& flags)
{
	assignFlagsForEitherDoubleBonds(flags);

	StereoAtomInfoList::iterator isolated_ctrs_beg = std::partition(stereoAtomList.begin(), 
																	stereoAtomList.end(),
																	boost::bind(&StereoAtomInfo::hasStereoAtomNbrs, _1));
	std::for_each(isolated_ctrs_beg, stereoAtomList.end(),
				  boost::bind(&BondStereoFlagGenerator::assignFlagsForIsolatedCenter, this, _1, boost::ref(flags)));

	if (isolated_ctrs_beg != stereoAtomList.begin()) {
		currentStereoFlags = flags;

		assignFlagsForNonIsolatedCenters(0, isolated_ctrs_beg - stereoAtomList.begin(), flags);
	}

	MolecularGraph::ConstBondIterator bonds_end = molGraph->getBondsEnd();

	for (MolecularGraph::ConstBondIterator it = molGraph->getBondsBegin(); it != bonds_end; ++it) {
		const Bond& bond = *it;
		std::size_t bond_idx = molGraph->getBondIndex(bond);
		unsigned int stereo_flag = flags[bond_idx];

		if (stereo_flag == BondStereoFlag::PLAIN)
			continue;

		if (!molGraph->containsAtom(bond.getBegin()) || !molGraph->containsAtom(bond.getEnd()))
			continue;

		std::size_t atom1_idx = molGraph->getAtomIndex(bond.getBegin());
		std::size_t atom2_idx = molGraph->getAtomIndex(bond.getEnd());

		if (stereoAtomMask.test(atom2_idx) && !stereoAtomMask.test(atom1_idx)) {
			switch (stereo_flag) {

				case BondStereoFlag::UP:
					flags[bond_idx] = BondStereoFlag::REVERSE_DOWN;
					break;

				case BondStereoFlag::DOWN:
					flags[bond_idx] = BondStereoFlag::REVERSE_UP;
					break;

				case BondStereoFlag::EITHER:
					flags[bond_idx] = BondStereoFlag::REVERSE_EITHER;
					break;
			} 
		}
	}
}

void Chem::BondStereoFlagGenerator::assignFlagsForEitherDoubleBonds(Util::UIArray& flags)
{
	MolecularGraph::ConstBondIterator bonds_end = molGraph->getBondsEnd();

	for (MolecularGraph::ConstBondIterator it = molGraph->getBondsBegin(); it != bonds_end; ++it) {
		const Bond& bond = *it;

		if (!molGraph->containsAtom(bond.getBegin()) || !molGraph->containsAtom(bond.getEnd()))
			continue;

		if (hasStereoCenterFlag(bond) && !getStereoCenterFlag(bond))
			continue;

		const StereoDescriptor& stereo_desc = calcStereoDescriptor(bond, *molGraph, 0);
		unsigned int config = stereo_desc.getConfiguration();

		if (config == BondConfiguration::CIS || config == BondConfiguration::TRANS) {
			stereoDBAtomMask.set(molGraph->getAtomIndex(bond.getBegin()));
			stereoDBAtomMask.set(molGraph->getAtomIndex(bond.getEnd()));

		} else if (config == BondConfiguration::EITHER)
			eitherBondList.push_back(&bond);
	}

	BondList::const_iterator either_bonds_end = eitherBondList.end();

	for (BondList::const_iterator it = eitherBondList.begin(); it != either_bonds_end; ++it) {
		const Bond* bond = *it;
		const Atom* atoms[2] = { &bond->getBegin(), &bond->getEnd() };

		bool flag_set = false;

		const Bond* best_bond = 0;
		std::size_t best_bond_nbr_idx = 0;

		bool ring_bond = ringBondMask.test(molGraph->getBondIndex(*bond));

		for (std::size_t i = 0; i < 2 && !flag_set; i++) {
			const Atom* atom = atoms[i];

			Atom::ConstBondIterator bonds_end = atom->getBondsEnd();
			Atom::ConstAtomIterator a_it = atom->getAtomsBegin();
			
			for (Atom::ConstBondIterator b_it = atom->getBondsBegin(); b_it != bonds_end; ++b_it, ++a_it) {
				const Bond* nbr_bond = &*b_it;

				if (nbr_bond == bond)
					continue;

				const Atom& nbr_atom = *a_it;

				if (!molGraph->containsAtom(nbr_atom) || !molGraph->containsBond(*nbr_bond))
					continue;

				std::size_t nbr_bond_idx = molGraph->getBondIndex(*nbr_bond);

				if (flags[nbr_bond_idx] == BondStereoFlag::EITHER) {
					flag_set = true;
					break;
				}

				std::size_t nbr_atom_idx = molGraph->getAtomIndex(nbr_atom);

				if (stereoDBAtomMask.test(nbr_atom_idx))
					continue;

				if (stereoAtomMask.test(nbr_atom_idx)) {
					if (stereoAtomTable[nbr_atom_idx]->getConfiguration() != AtomConfiguration::EITHER)
						continue;

					best_bond = nbr_bond;
					best_bond_nbr_idx = nbr_atom_idx;

				} else {
					if (best_bond && stereoAtomMask.test(nbr_atom_idx) 
						&& stereoAtomTable[best_bond_nbr_idx]->getConfiguration() == AtomConfiguration::EITHER)
						continue;

					if (ring_bond) {
						if (ringBondMask.test(nbr_bond_idx)) {
							best_bond = nbr_bond;
							best_bond_nbr_idx = nbr_atom_idx;

						} else if (!best_bond) {
							best_bond = nbr_bond;
							best_bond_nbr_idx = nbr_atom_idx;
						}

					} else {
						if (!ringBondMask.test(nbr_bond_idx)) {
							best_bond = nbr_bond;
							best_bond_nbr_idx = nbr_atom_idx;

						} else if (!best_bond) {
							best_bond = nbr_bond;
							best_bond_nbr_idx = nbr_atom_idx;
						}
					}
				}
			}
		}

		if (!flag_set) {
			if (best_bond) {
				flags[molGraph->getBondIndex(*best_bond)] = BondStereoFlag::EITHER;

				if (stereoAtomMask.test(best_bond_nbr_idx))
					configMatchMask.set(best_bond_nbr_idx);

			} else
				flags[molGraph->getBondIndex(*bond)] = BondStereoFlag::EITHER;
		}
	}
}

void Chem::BondStereoFlagGenerator::assignFlagsForIsolatedCenter(const StereoAtomInfo* stereo_atom, Util::UIArray& flags)
{
	if (stereo_atom->getConfiguration() == AtomConfiguration::EITHER) 
		return;

	std::size_t num_bonds = stereo_atom->getNumBonds();

	for (std::size_t i = 0; i < num_bonds; i++) {
		std::size_t bond_idx = stereo_atom->getBondIndex(i);

		if (!singleBondMask.test(bond_idx))
			continue;

		flags[bond_idx] = BondStereoFlag::UP;

		if (stereo_atom->configMatches(flags))
			return;

		flags[bond_idx] = BondStereoFlag::DOWN;

		if (stereo_atom->configMatches(flags))
			return;

		flags[bond_idx] = BondStereoFlag::PLAIN;
	}
}

bool Chem::BondStereoFlagGenerator::assignFlagsForNonIsolatedCenters(std::size_t list_idx, std::size_t max_idx, Util::UIArray& flags)
{
	if (numMismatchingCtrs >= minNumMismatchingCtrs)
		return false;

	if (list_idx == max_idx) {
		flags = currentStereoFlags;
		minNumMismatchingCtrs = numMismatchingCtrs;

		if (numMismatchingCtrs == 0)
			return true;

		return false;
	}

	const StereoAtomInfo* stereo_atom = stereoAtomList[list_idx];
	std::size_t atom_idx = stereo_atom->getAtomIndex();

	if (configMatchMask.test(atom_idx)) 
		return assignFlagsForNonIsolatedCenters(list_idx + 1, max_idx, flags);
	
	bool already_matches = stereo_atom->configMatches(currentStereoFlags);

	if (already_matches) {
		configMatchMask.set(atom_idx);

		if (assignFlagsForNonIsolatedCenters(list_idx + 1, max_idx, flags)) 
			return true;

		configMatchMask.reset(atom_idx);
	}

	std::size_t num_bonds = stereo_atom->getNumBonds();
	bool has_config = (stereo_atom->getConfiguration() != AtomConfiguration::EITHER);

	for (std::size_t i = 0; i < num_bonds; i++) {
		std::size_t bond_idx = stereo_atom->getBondIndex(i);

		if (!singleBondMask.test(bond_idx))
			continue;

		std::size_t nbr_atom_idx = stereo_atom->getNbrAtomIndex(i);
		
		bool matching_nbr = configMatchMask.test(nbr_atom_idx);
		bool stereo_db_nbr = stereoDBAtomMask.test(nbr_atom_idx);

		for (std::size_t j = 0; j < 3; j++) {
			switchStereoFlag(bond_idx);

			if (currentStereoFlags[bond_idx] == BondStereoFlag::EITHER && (has_config || stereo_db_nbr))
				continue;

			if (stereo_atom->configMatches(currentStereoFlags)
				&& (!matching_nbr || stereoAtomTable[nbr_atom_idx]->configMatches(currentStereoFlags))) {

				configMatchMask.set(atom_idx);

				if (assignFlagsForNonIsolatedCenters(list_idx + 1, max_idx, flags))
					return true;

				configMatchMask.reset(atom_idx);
			}
		}

		switchStereoFlag(bond_idx);
	}

    if (!already_matches) {
		numMismatchingCtrs++;

		assignFlagsForNonIsolatedCenters(list_idx + 1, max_idx, flags);

		numMismatchingCtrs--;
	}

	return false;
}

void Chem::BondStereoFlagGenerator::switchStereoFlag(std::size_t bond_idx)
{
	unsigned int& stereo_flag = currentStereoFlags[bond_idx]; 

	switch (stereo_flag) {

		case BondStereoFlag::PLAIN:
			stereo_flag = BondStereoFlag::UP;
			return;

		case BondStereoFlag::UP:
			stereo_flag = BondStereoFlag::DOWN;
			return;

		case BondStereoFlag::DOWN:
			stereo_flag = BondStereoFlag::EITHER;
			return;

		case BondStereoFlag::EITHER:
			stereo_flag = BondStereoFlag::PLAIN;
			return;

		default:
			stereo_flag = BondStereoFlag::PLAIN;
			return;
	}
}


//--------------

Chem::BondStereoFlagGenerator::StereoAtomInfo::StereoAtomInfo(const MolecularGraph* molgraph, 
															  const Atom2DCoordinatesFunction& coords_func,
															  const Atom* atom, unsigned int config, 
															  std::size_t num_bonds, const Atom** nbr_atoms,
															  const Bond** nbr_bonds): 
	molGraph(molgraph), atom(atom), configuration(config), numBonds(num_bonds)
{
	for (std::size_t i = 0; i < num_bonds; i++) {
		const Atom* nbr_atom = nbr_atoms[i];
		const Bond* nbr_bond = nbr_bonds[i];
		std::size_t bond_idx = molgraph->getBondIndex(*nbr_bond);

		bondEndFlags[i] = (&nbr_bond->getEnd() == nbr_atom);
		ligands[i] = Ligand(nbr_atom, bond_idx);
	}

	const Math::Vector2D& atom1_coords = coords_func(*nbr_atoms[0]);
	const Math::Vector2D& atom2_coords = coords_func(*nbr_atoms[1]);
	const Math::Vector2D& atom3_coords = coords_func(*nbr_atoms[2]);

	const Atom& ref_atom4 = (num_bonds == 3 ? *atom : *nbr_atoms[3]);

	const Math::Vector2D& atom4_coords = coords_func(ref_atom4);

	configCalcTerms[0] = (atom2_coords[0] - atom4_coords[0]) * (atom3_coords[1] - atom4_coords[1])
		- (atom2_coords[1] - atom4_coords[1]) * (atom3_coords[0] - atom4_coords[0]);

	configCalcTerms[1] = (atom1_coords[0] - atom4_coords[0]) * (atom3_coords[1] - atom4_coords[1])
		- (atom1_coords[1] - atom4_coords[1]) * (atom3_coords[0] - atom4_coords[0]);

	configCalcTerms[2] = (atom1_coords[0] - atom4_coords[0]) * (atom2_coords[1] - atom4_coords[1])
		- (atom1_coords[1] - atom4_coords[1]) * (atom2_coords[0] - atom4_coords[0]);

	configCalcTerms[3] = (atom1_coords[0] - atom3_coords[0]) * (atom2_coords[1] - atom3_coords[1])
		- (atom1_coords[1] - atom3_coords[1]) * (atom2_coords[0] - atom3_coords[0]);
}

unsigned int Chem::BondStereoFlagGenerator::StereoAtomInfo::getConfiguration() const
{
	return configuration;
}

void Chem::BondStereoFlagGenerator::StereoAtomInfo::findBestBondOrder(const Util::BitSet& stereo_ctr_mask, 
																	  const Util::BitSet& ring_bnd_mask)
{
	hasStereoNbrs = false;

	typedef std::pair<std::size_t, unsigned int> LigandTypeDescr;

	LigandTypeDescr ordered_ligs[4];

	for (std::size_t i = 0; i < numBonds; i++) {
		const Atom* nbr_atom = ligands[i].first;
		std::size_t bond_idx = ligands[i].second;

		ordered_ligs[i].first = i;
		ordered_ligs[i].second = 0;

		if (stereo_ctr_mask.test(molGraph->getAtomIndex(*nbr_atom))) {
			hasStereoNbrs = true;
			ordered_ligs[i].second |= 16;
		}

		if (ring_bnd_mask.test(bond_idx))
			ordered_ligs[i].second |= 8;

		if (getType(*nbr_atom) == AtomType::H || isUnsaturated(*nbr_atom, *molGraph))
			ordered_ligs[i].second |= 4;

		if (getHeavyBondCount(*nbr_atom, *molGraph) > 1)
			ordered_ligs[i].second |= 2;
	}

	std::sort(ordered_ligs, ordered_ligs + numBonds, 
			  boost::bind(std::less<unsigned int>(), boost::bind(&LigandTypeDescr::second, _1), boost::bind(&LigandTypeDescr::second, _2)));

	for (std::size_t i = 0; i < numBonds; i++)
		orderedLigands[i] = ligands[ordered_ligs[i].first];
}

bool Chem::BondStereoFlagGenerator::StereoAtomInfo::hasStereoAtomNbrs() const
{
	return hasStereoNbrs;
}

bool Chem::BondStereoFlagGenerator::StereoAtomInfo::configMatches(const Util::UIArray& stereo_flags) const
{
	int z_signs[4] = { 0, 0, 0, 0 };

	for (std::size_t i = 0; i < numBonds; i++) {
		switch (stereo_flags[ligands[i].second]) {

			case BondStereoFlag::UP:
				z_signs[i] = (bondEndFlags[i] ? 1 : -1);
				continue;

			case BondStereoFlag::DOWN:
				z_signs[i] = (bondEndFlags[i] ? -1 : 1);
				continue;

			case BondStereoFlag::EITHER:
				return (configuration == AtomConfiguration::EITHER);

			case BondStereoFlag::PLAIN:
				continue;

			default:		
				assert(false);
				continue;
		}
	}

	double sign = z_signs[0] * configCalcTerms[0] 
		- z_signs[1] * configCalcTerms[1]
		+ z_signs[2] * configCalcTerms[2]
		- z_signs[3] * configCalcTerms[3];

	return ((sign > 0.0 ? AtomConfiguration::S : sign < 0.0 ? AtomConfiguration::R : AtomConfiguration::EITHER) == configuration);
}

std::size_t Chem::BondStereoFlagGenerator::StereoAtomInfo::getNumBonds() const
{
	return numBonds;
}

std::size_t Chem::BondStereoFlagGenerator::StereoAtomInfo::getBondIndex(std::size_t list_idx) const
{
	return orderedLigands[list_idx].second;
}

std::size_t Chem::BondStereoFlagGenerator::StereoAtomInfo::getNbrAtomIndex(std::size_t list_idx) const
{
	return molGraph->getAtomIndex(*orderedLigands[list_idx].first);
}

std::size_t Chem::BondStereoFlagGenerator::StereoAtomInfo::getAtomIndex() const
{
	return molGraph->getAtomIndex(*atom);
}
