/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * MolecularGraphFragmentMembershipFunctions.cpp 
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

#include "CDPL/Chem/MolecularGraphFunctions.hpp"
#include "CDPL/Chem/Atom.hpp"
#include "CDPL/Chem/Bond.hpp"


using namespace CDPL; 


bool Chem::containsMolecularGraph(const MolecularGraph& molgraph, const MolecularGraph& sub_molgraph, bool atoms, bool bonds)
{
    if (atoms)
		for (MolecularGraph::ConstAtomIterator it = sub_molgraph.getAtomsBegin(), end = sub_molgraph.getAtomsEnd(); it != end; ++it)
			if (!molgraph.containsAtom(*it))
				return false;
	if (bonds)
		for (MolecularGraph::ConstBondIterator it = sub_molgraph.getBondsBegin(), end = sub_molgraph.getBondsEnd(); it != end; ++it)
			if (!molgraph.containsBond(*it))
				return false;

	return true;
}

void Chem::getContainedFragments(const MolecularGraph& molgraph, const FragmentList& frag_list, 
								 FragmentList& cont_frag_list, bool append, bool atoms, bool bonds)
{
    if (!append)
		cont_frag_list.clear();

    for (FragmentList::BaseType::ConstElementIterator it = frag_list.getBase().getElementsBegin(), 
			 end = frag_list.getBase().getElementsEnd(); it != end; ++it)
		if (containsMolecularGraph(molgraph, **it, atoms, bonds))
			cont_frag_list.addElement(*it);
}

void Chem::getContainingFragments(const MolecularGraph& molgraph, const FragmentList& frag_list, 
								  FragmentList& cont_frag_list, bool append, bool atoms, bool bonds)
{
    if (!append)
		cont_frag_list.clear();

    for (FragmentList::BaseType::ConstElementIterator it = frag_list.getBase().getElementsBegin(), 
			 end = frag_list.getBase().getElementsEnd(); it != end; ++it)
		if (containsMolecularGraph(**it, molgraph , atoms, bonds))
			cont_frag_list.addElement(*it);
}
