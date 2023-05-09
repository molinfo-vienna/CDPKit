/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * MolecularGraphComponentGroupsFunctions.cpp 
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

#include <map>

#include "CDPL/Chem/MolecularGraphFunctions.hpp"
#include "CDPL/Chem/AtomFunctions.hpp"
#include "CDPL/Chem/Atom.hpp"
#include "CDPL/Chem/MolecularGraphProperty.hpp"


using namespace CDPL; 


Chem::FragmentList::SharedPointer Chem::perceiveComponentGroups(const MolecularGraph& molgraph)
{
	typedef std::map<std::size_t, Fragment::SharedPointer> ComponentGroupMap;

	ComponentGroupMap group_map;
	const FragmentList& comps = *getComponents(molgraph);

	FragmentList::ConstElementIterator comps_end = comps.getElementsEnd();

	for (FragmentList::ConstElementIterator c_it = comps.getElementsBegin(); c_it != comps_end; ++c_it) {
		const Fragment& comp = *c_it;
		Fragment::ConstAtomIterator atoms_end = comp.getAtomsEnd();

		for (Fragment::ConstAtomIterator a_it = comp.getAtomsBegin(); a_it != atoms_end; ++a_it) {
			const Atom& atom = *a_it;
			std::size_t group_id = getComponentGroupID(atom);
		
			if (group_id == 0)
				continue;

			Fragment::SharedPointer& grp_ptr = group_map[group_id];

			if (!grp_ptr) 
				grp_ptr.reset(new Fragment(comp));

			else 
				(*grp_ptr) += comp;
			
			break;
		}
	}

	FragmentList::SharedPointer comp_grps_ptr(new FragmentList());
	FragmentList* comp_grps = comp_grps_ptr.get();

	for (ComponentGroupMap::const_iterator g_it = group_map.begin(), grps_end = group_map.end(); g_it != grps_end; ++g_it)
		comp_grps->addElement(g_it->second);

	return comp_grps_ptr;
}

Chem::FragmentList::SharedPointer Chem::perceiveComponentGroups(MolecularGraph& molgraph, bool overwrite)
{
	if (!overwrite) {
		Base::Variant prev_groups = molgraph.getProperty(MolecularGraphProperty::COMPONENT_GROUPS, false);
	
		if (!prev_groups.isEmpty())
			return prev_groups.getData<FragmentList::SharedPointer>();
	}

	FragmentList::SharedPointer comp_grps_ptr = perceiveComponentGroups(molgraph);

	setComponentGroups(molgraph, comp_grps_ptr);

	return comp_grps_ptr;
}
