/* 
 * AtomConfigurationMatchExpression.cpp
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

#include "CDPL/Chem/AtomConfigurationMatchExpression.hpp"
#include "CDPL/Chem/AtomBondMapping.hpp"
#include "CDPL/Chem/Atom.hpp"
#include "CDPL/Chem/Bond.hpp"
#include "CDPL/Chem/AtomFunctions.hpp"
#include "CDPL/Chem/AtomConfiguration.hpp"


using namespace CDPL;


Chem::AtomConfigurationMatchExpression::AtomConfigurationMatchExpression(const StereoDescriptor& query_stereo_descr, const Atom& query_atom, bool not_match, bool allow_part_maps): 
	queryStereoDescr(query_stereo_descr), queryAtom(&query_atom), queryDescrValid(query_stereo_descr.isValid(query_atom)),
	configFlags(query_stereo_descr.getConfiguration() & (AtomConfiguration::NONE | AtomConfiguration::R | AtomConfiguration::S | AtomConfiguration::EITHER)), 
	notMatch(not_match), allowPartMaps(allow_part_maps) {}

bool Chem::AtomConfigurationMatchExpression::operator()(const Atom& query_atom, const MolecularGraph&, 
														const Atom& target_atom, const MolecularGraph&, 
														const AtomBondMapping& mapping, const Base::Any&) const
{
	if (queryAtom != &query_atom || configFlags == 0)
		return true;

	const StereoDescriptor& target_stereo_desc = getStereoDescriptor(target_atom);
	unsigned int target_config = target_stereo_desc.getConfiguration();

	if ((configFlags & AtomConfiguration::EITHER) != 0 && 
		(target_config & (AtomConfiguration::R | AtomConfiguration::S | AtomConfiguration::EITHER)) != 0)
		return !notMatch;

	if (((configFlags & AtomConfiguration::NONE) & target_config) != 0)
		return !notMatch;

	unsigned int query_rs_config_flags = configFlags & (AtomConfiguration::R | AtomConfiguration::S);
	
	if (query_rs_config_flags == 0)
		return notMatch;

	unsigned int target_rs_config_flags = target_config & (AtomConfiguration::R | AtomConfiguration::S);

	if (query_rs_config_flags == (AtomConfiguration::R | AtomConfiguration::S)) {
		if (target_rs_config_flags != 0)
			return !notMatch;

		return notMatch;
	}

	if (target_rs_config_flags == 0)
		return notMatch;

	if (!queryDescrValid)
		return true;

	std::size_t num_query_ref_atoms = queryStereoDescr.getNumReferenceAtoms();
	const Atom* const* query_desc_atoms = queryStereoDescr.getReferenceAtoms();

	const Atom* mpd_query_ref_atoms[4] = { 0 };
	const AtomMapping& atom_mapping = mapping.getAtomMapping();

	for (std::size_t i = 0; i < num_query_ref_atoms; i++)
		if (!(mpd_query_ref_atoms[i] = atom_mapping[query_desc_atoms[i]]))
			return (allowPartMaps ^ notMatch);

	for (std::size_t i = 0; i < num_query_ref_atoms; i++)  // sanity check
		if (!target_atom.findBondToAtom(*mpd_query_ref_atoms[i]))
			return notMatch;

	unsigned int perm_parity = (num_query_ref_atoms == 3 ? 
								target_stereo_desc.getPermutationParity(*mpd_query_ref_atoms[0], *mpd_query_ref_atoms[1], *mpd_query_ref_atoms[2]) :
								target_stereo_desc.getPermutationParity(*mpd_query_ref_atoms[0], *mpd_query_ref_atoms[1], *mpd_query_ref_atoms[2], *mpd_query_ref_atoms[3]));
	bool match = false; 

	if (perm_parity == 2) 
		match = (query_rs_config_flags == target_rs_config_flags ? true : false);
	else if (perm_parity == 1) 
		match = (query_rs_config_flags == target_rs_config_flags ? false : true);
	else
		return notMatch;

	return (match ^ notMatch);
}

bool Chem::AtomConfigurationMatchExpression::requiresAtomBondMapping() const
{
	return true;
}
