/* 
 * ResidueList.cpp 
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

#include <boost/functional/hash.hpp>

#include "CDPL/Biomol/ResidueList.hpp"
#include "CDPL/Biomol/AtomFunctions.hpp"
#include "CDPL/Biomol/MolecularGraphFunctions.hpp"
#include "CDPL/Chem/Atom.hpp"
#include "CDPL/Chem/Bond.hpp"


using namespace CDPL; 


Biomol::ResidueList::ResidueList(const Chem::MolecularGraph& molgraph, unsigned int flags)
{
	extract(molgraph, flags);
}

void Biomol::ResidueList::extract(const Chem::MolecularGraph& molgraph, unsigned int flags)
{
	using namespace Chem;

	clear();
	resIDsToFragments.clear();

	if (flags == AtomPropertyFlag::DEFAULT)
		flags = AtomPropertyFlag::RESIDUE_CODE |
			AtomPropertyFlag::RESIDUE_SEQ_NO |
			AtomPropertyFlag::RESIDUE_INS_CODE |
			AtomPropertyFlag::CHAIN_ID |
			AtomPropertyFlag::MODEL_NUMBER;
	
	ResidueID res_id;

	for (MolecularGraph::ConstAtomIterator a_it = molgraph.getAtomsBegin(), a_end = molgraph.getAtomsEnd(); a_it != a_end; ++a_it) {
		const Atom& atom = *a_it;

		initResidueID(atom, res_id, flags);

		ResidueIDToFragmentMap::iterator frag_it = resIDsToFragments.find(res_id);

		if (frag_it != resIDsToFragments.end()) {
			frag_it->second->addAtom(atom);
			continue;
		}

		Fragment::SharedPointer res_ptr(new Fragment());

		res_ptr->addAtom(atom);

		setModelNumber(*res_ptr, getModelNumber(atom));
		setChainID(*res_ptr, getChainID(atom));
		setResidueInsertionCode(*res_ptr, getResidueInsertionCode(atom));
		setResidueSequenceNumber(*res_ptr, getResidueSequenceNumber(atom));
		setResidueCode(*res_ptr, getResidueCode(atom));

		addElement(res_ptr);
		resIDsToFragments.insert(ResidueIDToFragmentMap::value_type(res_id, res_ptr));
	}

	for (FragmentList::ElementIterator res_it = getElementsBegin(), res_end = getElementsEnd(); res_it != res_end; ++res_it) {
		Fragment& res = *res_it;

		for (std::size_t i = 0, num_atoms = res.getNumAtoms(); i < num_atoms; i++) {
			const Atom& atom = res.getAtom(i);
			Atom::ConstAtomIterator a_it = atom.getAtomsBegin();

			for (Atom::ConstBondIterator b_it = atom.getBondsBegin(), b_end = atom.getBondsEnd(); b_it != b_end; ++b_it, ++a_it) {
				const Bond& bond = *b_it;

				if (res.containsBond(bond))
					continue;

				if (!res.containsAtom(*a_it))
					continue;

				if (!molgraph.containsBond(bond))
					continue;

				res.addBond(bond);
			}
		}
	}
}

void Biomol::ResidueList::initResidueID(const Chem::Atom& atom, ResidueID& res_id, unsigned int flags) const
{
	if (flags & AtomPropertyFlag::RESIDUE_SEQ_NO)
		res_id.seqNumber = getResidueSequenceNumber(atom);

	if (flags & AtomPropertyFlag::RESIDUE_INS_CODE)
		res_id.insCode = getResidueInsertionCode(atom);

	if (flags & AtomPropertyFlag::CHAIN_ID)
		res_id.chainID = getChainID(atom);

	if (flags & AtomPropertyFlag::MODEL_NUMBER)
		res_id.modelNumber = getModelNumber(atom);

	if (flags & AtomPropertyFlag::RESIDUE_CODE)
		res_id.resCode = getResidueCode(atom);
}

std::size_t Biomol::ResidueList::ResidueIDHashFunc::operator()(const ResidueID& res_id) const
{
	std::size_t hash = 0;

	boost::hash_combine(hash, res_id.modelNumber);
	boost::hash_combine(hash, res_id.seqNumber);
	boost::hash_combine(hash, res_id.chainID);
	boost::hash_combine(hash, res_id.insCode);
	boost::hash_combine(hash, res_id.resCode);

	return hash;
}

bool Biomol::ResidueList::ResidueID::operator==(const ResidueID& res_id) const
{
	return (res_id.modelNumber == modelNumber && res_id.seqNumber == seqNumber && 
			res_id.chainID == chainID && res_id.insCode == insCode &&
			res_id.resCode == resCode);
}
