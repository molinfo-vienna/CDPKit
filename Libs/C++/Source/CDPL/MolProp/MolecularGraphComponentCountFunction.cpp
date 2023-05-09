/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * MolecularGraphComponentCountFunction.cpp 
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

#include "CDPL/MolProp/MolecularGraphFunctions.hpp"
#include "CDPL/Chem/AtomFunctions.hpp"
#include "CDPL/Chem/Atom.hpp"


using namespace CDPL; 


std::size_t MolProp::getComponentCount(const Chem::MolecularGraph& molgraph)
{
	using namespace Chem;
	
	Util::BitSet vis_atoms(molgraph.getNumAtoms());
	std::size_t count = 0;
	std::size_t i = 0;

	MolecularGraph::ConstAtomIterator atoms_end = molgraph.getAtomsEnd();
	
	for (MolecularGraph::ConstAtomIterator it = molgraph.getAtomsBegin(); it != atoms_end; ++it, i++) {
		const Atom& atom = *it;

		if (!vis_atoms.test(i)) {
			count++;
			vis_atoms.set(i);

			markReachableAtoms(atom, molgraph, vis_atoms, false);
		}
	}

	return count;
}
