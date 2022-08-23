/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * MolecularGraphComponentFunctions.cpp 
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
#include "CDPL/Chem/MolecularGraphProperty.hpp"
#include "CDPL/Chem/ComponentSet.hpp"


using namespace CDPL; 


Chem::FragmentList::SharedPointer Chem::perceiveComponents(const MolecularGraph& molgraph)
{
	FragmentList::SharedPointer comps_ptr(new ComponentSet(molgraph));

	return comps_ptr;
}

Chem::FragmentList::SharedPointer Chem::perceiveComponents(MolecularGraph& molgraph, bool overwrite)
{
	if (!overwrite) {
		Base::Variant prev_comps = molgraph.getProperty(MolecularGraphProperty::COMPONENTS, false);
	
		if (!prev_comps.isEmpty())
			return prev_comps.getData<FragmentList::SharedPointer>();
	}

	FragmentList::SharedPointer comps_ptr(new ComponentSet(molgraph));

	molgraph.setProperty(MolecularGraphProperty::COMPONENTS, comps_ptr);

	return comps_ptr;
}
