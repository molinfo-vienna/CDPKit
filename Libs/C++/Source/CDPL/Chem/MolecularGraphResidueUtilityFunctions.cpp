/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * MolecularGraphResidueUtilityFunctions.cpp 
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

#include "CDPL/Chem/MolecularGraphFunctions.hpp"
#include "CDPL/Chem/MolecularGraph.hpp"
#include "CDPL/Chem/Atom.hpp"
#include "CDPL/Chem/Entity3DContainerFunctions.hpp"
#include "CDPL/Chem/Entity3DFunctions.hpp"
#include "CDPL/Chem/AtomFunctions.hpp"
#include "CDPL/Chem/AtomType.hpp"
#include "CDPL/Math/VectorArrayFunctions.hpp"


using namespace CDPL; 


void Chem::extractEnvironmentResidues(const MolecularGraph& core, const MolecularGraph& macromol, Fragment& env_residues, double max_dist)
{
    if (core.getNumAtoms() == 0)
		return;

	Math::Vector3DArray core_coords; 
	get3DCoordinates(core, core_coords);
	
	Math::Vector3D core_ctr; 
	calcCentroid(core_coords, core_ctr);
	
	double bsphere_rad = 0.0;

	for (Math::Vector3DArray::ConstElementIterator it = core_coords.getElementsBegin(), end = core_coords.getElementsEnd(); it != end; ++it) 
		bsphere_rad = std::max(bsphere_rad, length(*it - core_ctr));

	bsphere_rad += max_dist;
	
	for (MolecularGraph::ConstAtomIterator it = macromol.getAtomsBegin(), end = macromol.getAtomsEnd(); it != end; ++it) {
		const Atom& atom = *it;
		const Math::Vector3D& atom_pos = get3DCoordinates(atom);

		if (length(atom_pos - core_ctr) > bsphere_rad)
			continue;

		if (core.containsAtom(atom) || env_residues.containsAtom(atom))
			continue;

		for (Math::Vector3DArray::ConstElementIterator c_it = core_coords.getElementsBegin(), c_end = core_coords.getElementsEnd(); c_it != c_end; ++c_it) {
			if (length(atom_pos - *c_it) <= max_dist) {
				extractResidueSubstructure(atom, macromol, env_residues, true);
				break;
			}
		}
	} 
}

void Chem::setHydrogenResidueSequenceInfo(MolecularGraph& molgraph, bool overwrite, unsigned int flags)
{
	if (flags == AtomPropertyFlag::DEFAULT)
		flags = AtomPropertyFlag::RESIDUE_CODE |
			AtomPropertyFlag::RESIDUE_SEQ_NO |
			AtomPropertyFlag::RESIDUE_INS_CODE |
			AtomPropertyFlag::CHAIN_ID |
			AtomPropertyFlag::MODEL_NUMBER;

	for (MolecularGraph::AtomIterator it = molgraph.getAtomsBegin(), end = molgraph.getAtomsEnd(); it != end; ++it) {
		Atom& atom = *it;

		if (getType(atom) != AtomType::H) 
			continue;
	
		if (atom.getNumAtoms() != 1 && getHeavyAtomCount(atom, molgraph) != 1) 
			continue;

		const Atom& prnt_atom = atom.getAtom(0);

		if (getType(prnt_atom) == AtomType::H) 
			overwrite = false;

		if (overwrite) {
			if (flags & AtomPropertyFlag::RESIDUE_CODE)
				setResidueCode(atom, getResidueCode(prnt_atom));

			if (flags & AtomPropertyFlag::MODEL_NUMBER)
				setModelNumber(atom, getModelNumber(prnt_atom));

			if (flags & AtomPropertyFlag::RESIDUE_SEQ_NO)
				setResidueSequenceNumber(atom, getResidueSequenceNumber(prnt_atom));

			if (flags & AtomPropertyFlag::CHAIN_ID)
				setChainID(atom, getChainID(prnt_atom));

			if (flags & AtomPropertyFlag::RESIDUE_INS_CODE)
				setResidueInsertionCode(atom, getResidueInsertionCode(prnt_atom));

		} else {
			if ((flags & AtomPropertyFlag::RESIDUE_CODE) && !hasResidueCode(atom))
				setResidueCode(atom, getResidueCode(prnt_atom));

			if ((flags & AtomPropertyFlag::MODEL_NUMBER) && !hasModelNumber(atom))
				setModelNumber(atom, getModelNumber(prnt_atom));

			if ((flags & AtomPropertyFlag::RESIDUE_SEQ_NO) && !hasResidueSequenceNumber(atom))
				setResidueSequenceNumber(atom, getResidueSequenceNumber(prnt_atom));

			if ((flags & AtomPropertyFlag::CHAIN_ID) && !hasChainID(atom))
				setChainID(atom, getChainID(prnt_atom));

			if ((flags & AtomPropertyFlag::RESIDUE_INS_CODE) && !hasResidueInsertionCode(atom))
				setResidueInsertionCode(atom, getResidueInsertionCode(prnt_atom));
		}
	}
}
