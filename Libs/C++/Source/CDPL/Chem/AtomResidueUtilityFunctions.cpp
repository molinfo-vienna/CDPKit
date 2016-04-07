/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * AtomResidueUtilityFunctions.cpp 
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

#include "CDPL/Chem/AtomFunctions.hpp"
#include "CDPL/Chem/Atom.hpp"
#include "CDPL/Chem/Bond.hpp"


using namespace CDPL; 


bool Chem::areInSameResidue(const Atom& atom1, const Atom& atom2, unsigned int flags)
{
	if (flags == AtomPropertyFlag::DEFAULT)
		flags = AtomPropertyFlag::RESIDUE_CODE |
			AtomPropertyFlag::RESIDUE_SEQ_NO |
			AtomPropertyFlag::RESIDUE_INS_CODE |
			AtomPropertyFlag::CHAIN_ID |
			AtomPropertyFlag::MODEL_NUMBER;

	if ((flags & AtomPropertyFlag::RESIDUE_SEQ_NO) && getResidueSequenceNumber(atom1) != getResidueSequenceNumber(atom2))
		return false;

	if ((flags & AtomPropertyFlag::RESIDUE_INS_CODE) && getResidueInsertionCode(atom1) != getResidueInsertionCode(atom2))
		return false;

	if ((flags & AtomPropertyFlag::CHAIN_ID) && getChainID(atom1) != getChainID(atom2))
		return false;

	if ((flags & AtomPropertyFlag::MODEL_NUMBER) && getModelNumber(atom1) != getModelNumber(atom2))
		return false;

	if ((flags & AtomPropertyFlag::RESIDUE_CODE) && getResidueCode(atom1) != getResidueCode(atom2))
		return false;

	return true;
}

void Chem::extractResidueSubstructure(const Atom& atom, const MolecularGraph& molgraph, Fragment& res_substruct, 
									  bool cnctd_only, unsigned int flags)
{
	if (flags == AtomPropertyFlag::DEFAULT)
		flags = AtomPropertyFlag::RESIDUE_CODE |
			AtomPropertyFlag::RESIDUE_SEQ_NO |
			AtomPropertyFlag::RESIDUE_INS_CODE |
			AtomPropertyFlag::CHAIN_ID |
			AtomPropertyFlag::MODEL_NUMBER;

	std::string res_code = (flags & AtomPropertyFlag::RESIDUE_CODE) ? getResidueCode(atom) : std::string();
	std::size_t model_no = (flags & AtomPropertyFlag::MODEL_NUMBER) ? getModelNumber(atom) : std::size_t(0);
	std::size_t seq_no = (flags & AtomPropertyFlag::RESIDUE_SEQ_NO) ? getResidueSequenceNumber(atom) : std::size_t(0);
	char chain_id = (flags & AtomPropertyFlag::CHAIN_ID) ? getChainID(atom) : ' ';
	char ins_code = (flags & AtomPropertyFlag::RESIDUE_INS_CODE) ? getResidueInsertionCode(atom) : ' ';

	res_substruct.addAtom(atom);

	if (!cnctd_only) {
		for (MolecularGraph::ConstAtomIterator it = molgraph.getAtomsBegin(), end = molgraph.getAtomsEnd(); it != end; ++it) {
			const Atom& cand_atom = *it;

			if (res_substruct.containsAtom(cand_atom))
				continue;
 
			if ((flags & AtomPropertyFlag::RESIDUE_SEQ_NO) && seq_no != getResidueSequenceNumber(cand_atom))
				continue;

			if ((flags & AtomPropertyFlag::RESIDUE_INS_CODE) && ins_code != getResidueInsertionCode(cand_atom))
				continue;
			
			if ((flags & AtomPropertyFlag::CHAIN_ID) && chain_id != getChainID(cand_atom))
				continue;

			if ((flags & AtomPropertyFlag::MODEL_NUMBER) && model_no != getModelNumber(cand_atom))
				continue;

			if ((flags & AtomPropertyFlag::RESIDUE_CODE) && res_code != getResidueCode(cand_atom))
				continue;
			
			res_substruct.addAtom(cand_atom);
		}

		for (MolecularGraph::ConstBondIterator it = molgraph.getBondsBegin(), end = molgraph.getBondsEnd(); it != end; ++it) {
			const Bond& bond = *it;

			if (res_substruct.containsAtom(bond.getBegin()) && res_substruct.containsAtom(bond.getEnd()))
				res_substruct.addBond(bond);
		}

		return;
	}

	Atom::ConstAtomIterator a_it = atom.getAtomsBegin();

	for (Atom::ConstBondIterator b_it = atom.getBondsBegin(), b_end = atom.getBondsEnd(); b_it != b_end; ++b_it, ++a_it) {
		const Atom& cand_atom = *a_it;
		
		if (!molgraph.containsAtom(cand_atom))
			continue;

		const Bond& bond = *b_it;

		if (!molgraph.containsBond(bond))
			continue;

		if (!res_substruct.containsAtom(cand_atom)) {
			if ((flags & AtomPropertyFlag::RESIDUE_SEQ_NO) && seq_no != getResidueSequenceNumber(cand_atom))
				continue;

			if ((flags & AtomPropertyFlag::RESIDUE_INS_CODE) && ins_code != getResidueInsertionCode(cand_atom))
				continue;
			
			if ((flags & AtomPropertyFlag::CHAIN_ID) && chain_id != getChainID(cand_atom))
				continue;

			if ((flags & AtomPropertyFlag::MODEL_NUMBER) && model_no != getModelNumber(cand_atom))
				continue;

			if ((flags & AtomPropertyFlag::RESIDUE_CODE) && res_code != getResidueCode(cand_atom))
				continue;

			extractResidueSubstructure(cand_atom, molgraph, res_substruct, cnctd_only, flags);
		}

		res_substruct.addBond(*b_it);
	}
}
