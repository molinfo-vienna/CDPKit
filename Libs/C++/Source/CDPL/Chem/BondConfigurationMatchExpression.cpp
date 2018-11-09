/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * BondConfigurationMatchExpression.cpp
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

#include "CDPL/Chem/BondConfigurationMatchExpression.hpp"
#include "CDPL/Chem/AtomBondMapping.hpp"
#include "CDPL/Chem/Atom.hpp"
#include "CDPL/Chem/Bond.hpp"
#include "CDPL/Chem/BondFunctions.hpp"
#include "CDPL/Chem/BondConfiguration.hpp"


using namespace CDPL;


Chem::BondConfigurationMatchExpression::BondConfigurationMatchExpression(const StereoDescriptor& query_stereo_descr, const Bond& query_bond, bool not_match, bool allow_part_maps): 
	queryStereoDescr(query_stereo_descr), queryBond(&query_bond), queryDescrValid(query_stereo_descr.isValid(query_bond)),
	configFlags(query_stereo_descr.getConfiguration() & (BondConfiguration::NONE | BondConfiguration::CIS | BondConfiguration::TRANS | BondConfiguration::EITHER)),
	notMatch(not_match), allowPartMaps(allow_part_maps) {}

bool Chem::BondConfigurationMatchExpression::operator()(const Bond& query_bond, const MolecularGraph&, 
														const Bond& target_bond, const MolecularGraph&, 
														const AtomBondMapping& mapping, const Base::Variant&) const
{
	if (queryBond != &query_bond || configFlags == 0)
		return true;

	const StereoDescriptor& target_stereo_desc = getStereoDescriptor(target_bond);
	unsigned int target_config = target_stereo_desc.getConfiguration();

	if ((configFlags & BondConfiguration::EITHER) != 0 && 
		(target_config & (BondConfiguration::CIS | BondConfiguration::TRANS | BondConfiguration::EITHER)) != 0)
		return !notMatch;

	if (((configFlags & BondConfiguration::NONE) & target_config) != 0)
		return !notMatch;

	unsigned int query_ct_config_flags = configFlags & (BondConfiguration::CIS | BondConfiguration::TRANS);
	
	if (query_ct_config_flags == 0)
		return notMatch;

	unsigned int target_ct_config_flags = target_config & (BondConfiguration::CIS | BondConfiguration::TRANS);

	if (query_ct_config_flags == (BondConfiguration::CIS | BondConfiguration::TRANS)) {
		if (target_ct_config_flags != 0)
			return !notMatch;

		return notMatch;
	}

	if (target_ct_config_flags == 0)
		return notMatch;

	if (!queryDescrValid)
		return true;

	if (!target_stereo_desc.isValid(target_bond))
		return notMatch;

	const Atom* const* query_desc_atoms = queryStereoDescr.getReferenceAtoms();
	const Atom* mpd_query_bond_atoms[2];
	const AtomMapping& atom_mapping = mapping.getAtomMapping();

	if (!(mpd_query_bond_atoms[0] = atom_mapping[query_desc_atoms[1]]))
		return (allowPartMaps ^ notMatch);

	if (!(mpd_query_bond_atoms[1] = atom_mapping[query_desc_atoms[2]]))
		return (allowPartMaps ^ notMatch);

	if (mpd_query_bond_atoms[0]->findBondToAtom(*mpd_query_bond_atoms[1]) != &target_bond)
		return notMatch;

	const Atom* mpd_query_config_ref_atoms[2];

	if (!(mpd_query_config_ref_atoms[0] = atom_mapping[query_desc_atoms[0]]))
		return (allowPartMaps ^ notMatch);

	if (!(mpd_query_config_ref_atoms[1] = atom_mapping[query_desc_atoms[3]]))
		return (allowPartMaps ^ notMatch);

	if (!mpd_query_bond_atoms[0]->findBondToAtom(*mpd_query_config_ref_atoms[0]) ||
		!mpd_query_bond_atoms[1]->findBondToAtom(*mpd_query_config_ref_atoms[1]))
		return notMatch;

	const Atom* const* target_desc_atoms = target_stereo_desc.getReferenceAtoms();
	const Atom* target_config_ref_atoms[2] = { 0, 0 };

	if (mpd_query_bond_atoms[0] == target_desc_atoms[2] && mpd_query_bond_atoms[1] == target_desc_atoms[1]) {
		target_config_ref_atoms[0] = target_desc_atoms[3];
		target_config_ref_atoms[1] = target_desc_atoms[0];

	} else {
		target_config_ref_atoms[0] = target_desc_atoms[0];
		target_config_ref_atoms[1] = target_desc_atoms[3];
	}

	bool match;

	if ((mpd_query_config_ref_atoms[0] != target_config_ref_atoms[0]) ^ (mpd_query_config_ref_atoms[1] != target_config_ref_atoms[1]))
		match = (query_ct_config_flags == target_ct_config_flags ? false : true);
	else
		match = (query_ct_config_flags == target_ct_config_flags ? true : false);

	return (match ^ notMatch);
}

bool Chem::BondConfigurationMatchExpression::requiresAtomBondMapping() const
{
	return true;
}
