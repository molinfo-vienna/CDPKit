/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * BondSubstituentDirectionMatchExpression.cpp
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

#include <algorithm>
#include <cassert>

#include "CDPL/Chem/BondSubstituentDirectionMatchExpression.hpp"
#include "CDPL/Chem/AtomBondMapping.hpp"
#include "CDPL/Chem/Atom.hpp"
#include "CDPL/Chem/Bond.hpp"
#include "CDPL/Chem/BondFunctions.hpp"
#include "CDPL/Chem/BondProperty.hpp"
#include "CDPL/Chem/BondDirection.hpp"
#include "CDPL/Chem/BondConfiguration.hpp"
#include "CDPL/Chem/StereoDescriptor.hpp"


using namespace CDPL;


bool Chem::BondSubstituentDirectionMatchExpression::operator()(const Bond& query_bond, const MolecularGraph& query_molgraph, 
															   const Bond& target_bond, const MolecularGraph& target_molgraph,
															   const AtomBondMapping& mapping, const Base::Variant& aux_data) const
{
	typedef MatchExpression<Bond, MolecularGraph>::SharedPointer BondExprPointer;

	const Atom* query_bond_atoms[2] = { &query_bond.getBegin(), &query_bond.getEnd() };

	if (query_bond_atoms[0]->getNumBonds() < 2 || query_bond_atoms[0]->getNumBonds() > 3)
		return true;

	if (query_bond_atoms[1]->getNumBonds() < 2 || query_bond_atoms[1]->getNumBonds() > 3)
		return true;

	const Atom* mpd_query_bond_atoms[2];
	const AtomMapping& atom_mapping = mapping.getAtomMapping();

	if (!(mpd_query_bond_atoms[0] = atom_mapping[query_bond_atoms[0]]))
		return true;

	if (!(mpd_query_bond_atoms[1] = atom_mapping[query_bond_atoms[1]]))
		return true;

	if (mpd_query_bond_atoms[0]->findBondToAtom(*mpd_query_bond_atoms[1]) != &target_bond)
		return true;

	BondExprPointer query_nbr_bond_exprs[2][2];
	const Bond* query_nbr_bonds[2][2] = { { 0, 0 }, { 0, 0 } };

	for (std::size_t i = 0; i < 2; i++) {
		Atom::ConstBondIterator bonds_end = query_bond_atoms[i]->getBondsEnd();
		Atom::ConstAtomIterator a_it = query_bond_atoms[i]->getAtomsBegin();

		bool query_bond_seen = false;

		for (Atom::ConstBondIterator b_it = query_bond_atoms[i]->getBondsBegin(); b_it != bonds_end; ++b_it, ++a_it) {
			const Bond* nbr_bond = &*b_it;

			if (!query_molgraph.containsBond(*nbr_bond) || !query_molgraph.containsAtom(*a_it))
				continue;

			if (nbr_bond == &query_bond) {
				query_bond_seen = true;
				continue;
			}

			if (!query_nbr_bonds[i][0]) {
				query_nbr_bonds[i][0] = nbr_bond;
				query_nbr_bond_exprs[i][0] = nbr_bond->getProperty<BondExprPointer>(BondProperty::MATCH_EXPRESSION);

			} else {
				query_nbr_bonds[i][1] = nbr_bond;
				query_nbr_bond_exprs[i][1] = nbr_bond->getProperty<BondExprPointer>(BondProperty::MATCH_EXPRESSION);
			}
		}

		if (!query_bond_seen || !query_nbr_bonds[i][0]) 
			return true;
	}

	const Bond* mpd_query_nbr_bonds[2][2] = { { 0, 0 }, { 0, 0 } };
	const BondMapping& bond_mapping = mapping.getBondMapping();

	for (std::size_t i = 0; i < 2; i++) {
		for (std::size_t j = 0; j < 2 && query_nbr_bonds[i][j]; j++) {
			const Bond* mpd_bond = bond_mapping[query_nbr_bonds[i][j]];

			if (mpd_bond && mpd_bond->containsAtom(*mpd_query_bond_atoms[i]))
				mpd_query_nbr_bonds[i][j] = mpd_bond;
		}

		if (!mpd_query_nbr_bonds[i][0] && !mpd_query_nbr_bonds[i][1])
			return true;

		if (!mpd_query_nbr_bonds[i][0]) {
			assert(mpd_query_nbr_bonds[i][1]);

			std::swap(mpd_query_nbr_bonds[i][0], mpd_query_nbr_bonds[i][1]);
			std::swap(query_nbr_bond_exprs[i][0], query_nbr_bond_exprs[i][1]);
			std::swap(query_nbr_bonds[i][0], query_nbr_bonds[i][1]);
		}
	}

	const StereoDescriptor& stereo_desc = getStereoDescriptor(target_bond);
	unsigned int target_config = stereo_desc.getConfiguration();

	if ((target_config == BondConfiguration::CIS || target_config == BondConfiguration::TRANS) && stereo_desc.isValid(target_bond)) {
		const Bond* target_config_ref_bonds[2] = { 0, 0 }; 
		const Atom* target_config_ref_atoms[2] = { 0, 0 }; 
		const Atom* const* target_sto_ref_atoms = stereo_desc.getReferenceAtoms();

		if (mpd_query_bond_atoms[0] == target_sto_ref_atoms[2] && mpd_query_bond_atoms[1] == target_sto_ref_atoms[1]) {
			target_config_ref_atoms[0] = target_sto_ref_atoms[3];
			target_config_ref_atoms[1] = target_sto_ref_atoms[0];

		} else {
			target_config_ref_atoms[0] = target_sto_ref_atoms[0];
			target_config_ref_atoms[1] = target_sto_ref_atoms[3];
		}

		target_config_ref_bonds[0] = mpd_query_bond_atoms[0]->findBondToAtom(*target_config_ref_atoms[0]);
		target_config_ref_bonds[1] = mpd_query_bond_atoms[1]->findBondToAtom(*target_config_ref_atoms[1]);
		
		if (target_config_ref_bonds[0] != 0 && target_config_ref_bonds[1] != 0) {
			unsigned int target_nbr_bond_dirs[2][2] = { { BondDirection::UP, BondDirection::DOWN } };

			if (target_config == BondConfiguration::CIS) {
				target_nbr_bond_dirs[1][0] = BondDirection::DOWN; 
				target_nbr_bond_dirs[1][1] = BondDirection::UP; 

			} else {
				target_nbr_bond_dirs[1][0] = BondDirection::UP; 
				target_nbr_bond_dirs[1][1] = BondDirection::DOWN; 
			}

			if ((mpd_query_nbr_bonds[0][0] == target_config_ref_bonds[0]) ^ (mpd_query_nbr_bonds[1][0] == target_config_ref_bonds[1]))
				std::swap(target_nbr_bond_dirs[1][0], target_nbr_bond_dirs[1][1]);

			for (bool first_check = true; true; first_check = false) {
				bool had_mismatch = false;

				for (std::size_t i = 0; i < 2 && !had_mismatch; i++) {
					for (std::size_t j = 0; j < 2 && mpd_query_nbr_bonds[i][j] && !had_mismatch; j++) {
						had_mismatch = !(*query_nbr_bond_exprs[i][j])(*query_nbr_bonds[i][j], query_molgraph, *mpd_query_nbr_bonds[i][j],
																	  target_molgraph, mapping, target_nbr_bond_dirs[i][j]);
					}
				}

				if (!had_mismatch)
					return true;

				if (!first_check)
					return false;

				std::swap(target_nbr_bond_dirs[0][0], target_nbr_bond_dirs[0][1]);
				std::swap(target_nbr_bond_dirs[1][0], target_nbr_bond_dirs[1][1]);
			}

			return false;
		}
	}

	//	if (target_config == BondConfiguration::EITHER) {
	const Base::Variant unspec_dir(BondDirection::UNSPECIFIED);

	for (std::size_t i = 0; i < 2; i++) 
		for (std::size_t j = 0; j < 2 && query_nbr_bonds[i][j]; j++) 
			if (mpd_query_nbr_bonds[i][j] && !(*query_nbr_bond_exprs[i][j])(*query_nbr_bonds[i][j], query_molgraph, *mpd_query_nbr_bonds[i][j],
																			target_molgraph, mapping, unspec_dir))
				return false;
	//	}

	return true;
}

bool Chem::BondSubstituentDirectionMatchExpression::requiresAtomBondMapping() const
{
	return true;
}
