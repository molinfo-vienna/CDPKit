/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * ReactionComponentGroupsFunctions.cpp 
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

#include "CDPL/Chem/ReactionFunctions.hpp"
#include "CDPL/Chem/Reaction.hpp"
#include "CDPL/Chem/MolecularGraphProperty.hpp"
#include "CDPL/Chem/ReactionProperty.hpp"


using namespace CDPL; 


Chem::FragmentList::SharedPointer Chem::perceiveComponentGroups(const Reaction& rxn)
{
	FragmentList::SharedPointer comp_grps_ptr(new FragmentList());
	Reaction::ConstComponentIterator comps_end = rxn.getComponentsEnd();

	for (Reaction::ConstComponentIterator c_it = rxn.getComponentsBegin(); c_it != comps_end; ++c_it) {
		const Molecule& comp = *c_it;
		const Base::Variant& comp_comp_grps_prop = comp.getProperty(MolecularGraphProperty::COMPONENT_GROUPS);

		if (comp_comp_grps_prop.isEmpty())
			continue;

		const FragmentList& comp_comp_grps = *comp_comp_grps_prop.getData<FragmentList::SharedPointer>();

		comp_grps_ptr->insertElements(comp_grps_ptr->getElementsEnd(), 
									  comp_comp_grps.getBase().getElementsBegin(), comp_comp_grps.getBase().getElementsEnd());
	}

	return comp_grps_ptr;
}

Chem::FragmentList::SharedPointer Chem::perceiveComponentGroups(Reaction& rxn, bool overwrite)
{
	if (!overwrite) {
		Base::Variant prev_groups = rxn.getProperty(ReactionProperty::COMPONENT_GROUPS, false);
	
		if (!prev_groups.isEmpty())
			return prev_groups.getData<FragmentList::SharedPointer>();
	}

	FragmentList::SharedPointer comp_grps_ptr = perceiveComponentGroups(rxn);

	setComponentGroups(rxn, comp_grps_ptr);

	return comp_grps_ptr;
}
