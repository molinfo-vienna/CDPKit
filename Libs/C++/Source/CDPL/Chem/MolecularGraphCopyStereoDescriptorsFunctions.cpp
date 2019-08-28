/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * MolecularGraphCopyStereoDescriptorsFunctions.cpp 
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

#include "CDPL/Chem/MolecularGraphFunctions.hpp"
#include "CDPL/Chem/AtomFunctions.hpp"
#include "CDPL/Chem/BondFunctions.hpp"
#include "CDPL/Chem/Atom.hpp"
#include "CDPL/Chem/Bond.hpp"
#include "CDPL/Chem/StereoDescriptor.hpp"


using namespace CDPL; 


void Chem::copyAtomStereoDescriptors(MolecularGraph& molgraph_copy, const MolecularGraph& molgraph,
									 std::size_t atom_idx_offs)
{
	MolecularGraph::AtomIterator atoms_end = molgraph_copy.getAtomsEnd();
	std::size_t i = 0;
	std::size_t num_mg_atoms = molgraph.getNumAtoms();

	for (MolecularGraph::AtomIterator a_it = molgraph_copy.getAtomsBegin() + atom_idx_offs; a_it != atoms_end && i < num_mg_atoms; ++a_it, i++) {
		Atom& atom = *a_it;
		const StereoDescriptor& stereo_desc = getStereoDescriptor(atom);

		if (!stereo_desc.isValid(molgraph.getAtom(i))) {
			clearStereoDescriptor(atom);
			continue;
		}

		const Atom* const* ref_atoms = stereo_desc.getReferenceAtoms();

		try {
			if (stereo_desc.getNumReferenceAtoms() == 3) 
				setStereoDescriptor(atom, StereoDescriptor(stereo_desc.getConfiguration(),
														   molgraph_copy.getAtom(molgraph.getAtomIndex(*ref_atoms[0]) + atom_idx_offs),
														   molgraph_copy.getAtom(molgraph.getAtomIndex(*ref_atoms[1]) + atom_idx_offs),
														   molgraph_copy.getAtom(molgraph.getAtomIndex(*ref_atoms[2]) + atom_idx_offs)));
			else
				setStereoDescriptor(atom, StereoDescriptor(stereo_desc.getConfiguration(),
														   molgraph_copy.getAtom(molgraph.getAtomIndex(*ref_atoms[0]) + atom_idx_offs),
														   molgraph_copy.getAtom(molgraph.getAtomIndex(*ref_atoms[1]) + atom_idx_offs),
														   molgraph_copy.getAtom(molgraph.getAtomIndex(*ref_atoms[2]) + atom_idx_offs),
														   molgraph_copy.getAtom(molgraph.getAtomIndex(*ref_atoms[3]) + atom_idx_offs)));
		} catch (const Base::IndexError& e) {
			clearStereoDescriptor(atom);
		} 
	}
}

void Chem::copyBondStereoDescriptors(MolecularGraph& molgraph_copy, const MolecularGraph& molgraph, 
									 std::size_t atom_idx_offs, std::size_t bond_start_idx)
{
	MolecularGraph::BondIterator bonds_end = molgraph_copy.getBondsEnd();
	std::size_t i = 0;
	std::size_t num_mg_bonds = molgraph.getNumBonds();

	for (MolecularGraph::BondIterator b_it = molgraph_copy.getBondsBegin() + bond_start_idx; b_it != bonds_end && i < num_mg_bonds; ++b_it, i++) {
		Bond& bond = *b_it;
		const StereoDescriptor& stereo_desc = getStereoDescriptor(bond);

		if (!stereo_desc.isValid(molgraph.getBond(i))) {
			clearStereoDescriptor(bond);
			continue;
		}

		const Atom* const* ref_atoms = stereo_desc.getReferenceAtoms();

		try {
			setStereoDescriptor(bond, StereoDescriptor(stereo_desc.getConfiguration(),
													   molgraph_copy.getAtom(molgraph.getAtomIndex(*ref_atoms[0]) + atom_idx_offs),
													   molgraph_copy.getAtom(molgraph.getAtomIndex(*ref_atoms[1]) + atom_idx_offs),
													   molgraph_copy.getAtom(molgraph.getAtomIndex(*ref_atoms[2]) + atom_idx_offs),
													   molgraph_copy.getAtom(molgraph.getAtomIndex(*ref_atoms[3]) + atom_idx_offs)));
		} catch (const Base::IndexError& e) {
			clearStereoDescriptor(bond);
		} 
	}
}
