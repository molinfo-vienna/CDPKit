/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * ReactionAtomMappingFunctions.cpp 
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

#include <vector>
#include <map>

#include "CDPL/Chem/ReactionFunctions.hpp"
#include "CDPL/Chem/Reaction.hpp"
#include "CDPL/Chem/Atom.hpp"
#include "CDPL/Chem/AtomFunctions.hpp"
#include "CDPL/Chem/ReactionProperty.hpp"
#include "CDPL/Chem/ReactionRole.hpp"


using namespace CDPL; 



Chem::AtomMapping::SharedPointer Chem::perceiveAtomMapping(const Reaction& rxn)
{
	typedef std::vector<const Atom*> AtomList;
	typedef std::map<std::size_t, AtomList> IDAtomListMap;

	IDAtomListMap reactant_alist_map;
	IDAtomListMap product_alist_map;
	
	for (std::size_t i = 0; i < 2; i++) {
		unsigned int role = (i == 0 ? ReactionRole::REACTANT : ReactionRole::PRODUCT);
		IDAtomListMap& alist_map = (i == 0 ? reactant_alist_map : product_alist_map);

		Reaction::ConstComponentIterator reactants_end = rxn.getComponentsEnd(role);

		for (Reaction::ConstComponentIterator c_it = rxn.getComponentsBegin(role); c_it != reactants_end; ++c_it) {
			const Molecule& comp = *c_it;
			Molecule::ConstAtomIterator atoms_end = comp.getAtomsEnd();

			for (Molecule::ConstAtomIterator a_it = comp.getAtomsBegin(); a_it != atoms_end; ++a_it) {
				const Atom& atom = *a_it;
				std::size_t aam_id = getAtomMappingID(atom);

				if (aam_id > 0)
					alist_map[aam_id].push_back(&atom);
			}
		}	
	}

	AtomMapping::SharedPointer mapping_ptr(new AtomMapping());
	AtomMapping* mapping = mapping_ptr.get();

	IDAtomListMap::const_iterator reactant_alist_map_end = reactant_alist_map.end();
	IDAtomListMap::const_iterator product_alist_map_end = product_alist_map.end();

	for (IDAtomListMap::const_iterator ral_it = reactant_alist_map.begin(); ral_it != reactant_alist_map_end; ++ral_it) {
		IDAtomListMap::const_iterator pal_it = product_alist_map.find(ral_it->first);

		if (pal_it == product_alist_map_end)
			continue;

		const AtomList& reactant_alist = ral_it->second;
		const AtomList& product_alist = pal_it->second;

		AtomList::const_iterator reactant_alist_end = reactant_alist.end();
		AtomList::const_iterator product_alist_beg = product_alist.begin();
		AtomList::const_iterator product_alist_end = product_alist.end();
		
		for (AtomList::const_iterator ra_it = reactant_alist.begin(); ra_it != reactant_alist_end; ++ra_it) {
			const Atom* reactant_atm = *ra_it;

			for (AtomList::const_iterator pa_it = product_alist_beg; pa_it != product_alist_end; ++pa_it)
				mapping->insertEntry(reactant_atm, *pa_it);
		}
	}

	return mapping_ptr;
}

Chem::AtomMapping::SharedPointer Chem::perceiveAtomMapping(Reaction& rxn, bool overwrite)
{
	if (!overwrite) {
		Base::Variant prev_mapping = rxn.getProperty(ReactionProperty::ATOM_MAPPING, false);
	
		if (!prev_mapping.isEmpty())
			return prev_mapping.getData<AtomMapping::SharedPointer>();
	}

	AtomMapping::SharedPointer mapping_ptr = perceiveAtomMapping(rxn);

	setAtomMapping(rxn, mapping_ptr);

	return mapping_ptr;
}
