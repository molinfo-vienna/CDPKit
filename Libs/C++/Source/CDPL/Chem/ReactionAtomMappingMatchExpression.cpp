/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * ReactionAtomMappingMatchExpression.cpp 
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
#include <functional>

#include <boost/bind.hpp>

#include "CDPL/Chem/ReactionAtomMappingMatchExpression.hpp"
#include "CDPL/Chem/Reaction.hpp"
#include "CDPL/Chem/AtomBondMapping.hpp"
#include "CDPL/Chem/ReactionFunctions.hpp"
#include "CDPL/Chem/ReactionRole.hpp"


using namespace CDPL;


Chem::ReactionAtomMappingMatchExpression::ReactionAtomMappingMatchExpression(const AtomMapping::SharedPointer& atom_mapping):
	atomMapping(atom_mapping) {}

bool Chem::ReactionAtomMappingMatchExpression::operator()(const Reaction&, const Reaction& target_rxn, const AtomBondMapping& mapping, 
														  const Base::Variant& matched_rxn_roles) const
{
	if (matched_rxn_roles.isEmpty())
		return true;

	if (!atomMapping || atomMapping->getSize() == 0)
		return true;

	if ((matched_rxn_roles.getData<unsigned int>() & (ReactionRole::REACTANT | ReactionRole::PRODUCT)) !=
		(ReactionRole::REACTANT | ReactionRole::PRODUCT))
		return true;

	const AtomMapping& target_rxn_atom_mapping = *getAtomMapping(target_rxn);

	if (target_rxn_atom_mapping.getSize() == 0)
		return false;

	const AtomMapping& atom_mapping = mapping.getAtomMapping();

	AtomMapping::ConstEntryIterator query_atom_pairs_end = atomMapping->getEntriesEnd();

	for (AtomMapping::ConstEntryIterator query_ap_it = atomMapping->getEntriesBegin(); query_ap_it != query_atom_pairs_end; ) {
		const Atom* query_reac_atom = query_ap_it->first;
		const Atom* target_reac_atom = atom_mapping[query_reac_atom];

		AtomMapping::ConstEntryIteratorRange target_atom_pair_range = target_rxn_atom_mapping.getEntries(target_reac_atom);

		if (target_atom_pair_range.first == target_atom_pair_range.second)
			return false;

		bool found_mapping = false;

		for ( ; query_ap_it != query_atom_pairs_end && query_ap_it->first == query_reac_atom; ++query_ap_it) {
			const Atom* query_prod_atom = query_ap_it->second;
			const Atom* target_prod_atom = atom_mapping[query_prod_atom];
	
			if (std::find_if(target_atom_pair_range.first, target_atom_pair_range.second,
							 boost::bind(std::equal_to<const Atom*>(), target_prod_atom, 
										 boost::bind(&AtomMapping::Entry::second, _1))) != target_atom_pair_range.second) {
				
				found_mapping = true;
				break;
			}
		}

		if (!found_mapping)
			return false;
		
		for ( ; query_ap_it != query_atom_pairs_end && query_ap_it->first == query_reac_atom; ++query_ap_it);
	}

	return true;
}

bool Chem::ReactionAtomMappingMatchExpression::requiresAtomBondMapping() const
{
	return true;
}
