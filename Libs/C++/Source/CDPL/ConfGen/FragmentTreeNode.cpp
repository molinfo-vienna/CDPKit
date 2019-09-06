/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * FragmentTreeNode.cpp 
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

#include "CDPL/Chem/Fragment.hpp"
#include "CDPL/Chem/Atom.hpp"
#include "CDPL/Chem/Bond.hpp"
#include "CDPL/Chem/MolecularGraphFunctions.hpp"
#include "CDPL/Chem/AtomFunctions.hpp"
#include "CDPL/Math/Matrix.hpp"

#include "FragmentTreeNode.hpp"


using namespace CDPL;


ConfGen::FragmentTreeNode::FragmentTreeNode(): 
	root(*this), parent(*this), fragment(0), splitBond(0), fragmentType(0) 
{}

ConfGen::FragmentTreeNode::FragmentTreeNode(FragmentTreeNode& root, FragmentTreeNode& parent): 
	root(root), parent(parent), fragment(0), splitBond(0), fragmentType(0) 
{}

const ConfGen::FragmentTreeNode& ConfGen::FragmentTreeNode::getParent() const
{
	return parent;
}

ConfGen::FragmentTreeNode& ConfGen::FragmentTreeNode::getParent()
{
	return parent;
}

const Chem::MolecularGraph& ConfGen::FragmentTreeNode::getFragment() const
{
	return *fragment;
}

const Chem::Bond* ConfGen::FragmentTreeNode::getSplitBond() const
{
	return splitBond;
}

const Chem::Atom* const* ConfGen::FragmentTreeNode::getSplitBondAtoms() const
{
	return splitBondAtoms;
}

const Chem::Atom* const* ConfGen::FragmentTreeNode::getTorsionReferenceAtoms() const
{
	return torsionRefAtoms;
}

void ConfGen::FragmentTreeNode::setTorsionReferenceAtoms(const Chem::Atom* ref_atom1, const Chem::Atom* ref_atom2)
{
	torsionRefAtoms[0] = ref_atom1;
	torsionRefAtoms[1] = ref_atom2;
}

void ConfGen::FragmentTreeNode::setFragmentType(unsigned int type)
{
	fragmentType = type;
}

unsigned int ConfGen::FragmentTreeNode::getFragmentType() const
{
	return fragmentType;
}

bool ConfGen::FragmentTreeNode::hasChildren() const
{
	return (splitBond != 0);
}

ConfGen::FragmentTreeNode* ConfGen::FragmentTreeNode::getLeftChild() const
{
	if (splitBond == 0)
		return 0;

	return leftChild.get();
}

ConfGen::FragmentTreeNode* ConfGen::FragmentTreeNode::getRightChild() const
{
	if (splitBond == 0)
		return 0;

	return rightChild.get();
}

void ConfGen::FragmentTreeNode::addConformer(Math::Vector3DArray* coords, double energy)
{
	conformers.push_back(ConfData(coords, energy));
}

std::size_t ConfGen::FragmentTreeNode::getNumConformers() const
{
	return conformers.size();
}

const ConfGen::FragmentTreeNode::ConfDataArray& ConfGen::FragmentTreeNode::getConformers() const
{
	return conformers;
}

ConfGen::FragmentTreeNode::ConfDataArray& ConfGen::FragmentTreeNode::getConformers()
{
	return conformers;
}

const ConfGen::FragmentTreeNode::IndexArray& ConfGen::FragmentTreeNode::getRootAtomIndices() const
{
	return rootAtomIndices;
}

ConfGen::FragmentTreeNode::IndexArray& ConfGen::FragmentTreeNode::getRootAtomIndices()
{
	return rootAtomIndices;
}

const ConfGen::FragmentTreeNode::TorsionAngleArray& ConfGen::FragmentTreeNode::getTorsionAngles() const
{
	return torsionAngles;
}

ConfGen::FragmentTreeNode::TorsionAngleArray& ConfGen::FragmentTreeNode::getTorsionAngles()
{
	return torsionAngles;
}

ForceField::MMFF94InteractionData& ConfGen::FragmentTreeNode::getMMFF94InteractionData()
{
	return mmff94Data;
}

void ConfGen::FragmentTreeNode::setKeepAllConformersFlag(bool keep)
{
	keepAllConfsFlag = keep;
}

bool ConfGen::FragmentTreeNode::getKeepAllConformersFlag() const
{
	return keepAllConfsFlag;
}

ConfGen::FragmentTreeNode::AtomList& ConfGen::FragmentTreeNode::getSplitBondAtom1Neighbors()
{
	return splitBondAtom1Nbrs;
}

const ConfGen::FragmentTreeNode::AtomList& ConfGen::FragmentTreeNode::getSplitBondAtom1Neighbors() const
{
	return splitBondAtom1Nbrs;
}

ConfGen::FragmentTreeNode::AtomList& ConfGen::FragmentTreeNode::getSplitBondAtom2Neighbors()
{
	return splitBondAtom2Nbrs;
}

const ConfGen::FragmentTreeNode::AtomList& ConfGen::FragmentTreeNode::getSplitBondAtom2Neighbors() const
{
	return splitBondAtom2Nbrs;
}

void ConfGen::FragmentTreeNode::splitRecursive(const Chem::MolecularGraph& frag, BondList& bonds)
{
    using namespace Chem;

    fragment = &frag;

    if (!(splitBond = extractMostCentralBond(bonds)))
		return;

    if (!leftFragment.get()) {
		leftFragment.reset(new Fragment());
		leftChild.reset(new FragmentTreeNode(root, *this));
    } else 
		leftFragment->clear();

    if (!rightFragment.get()) {
		rightFragment.reset(new Fragment());
		rightChild.reset(new FragmentTreeNode(root, *this));
    } else 
		rightFragment->clear();

    leftFragment->addBond(*splitBond);
    rightFragment->addBond(*splitBond);

	splitBondAtoms[0] = &splitBond->getBegin();
	splitBondAtoms[1] = &splitBond->getEnd();

    getSubstructure(*leftFragment, *splitBondAtoms[0]);
    getSubstructure(*rightFragment, *splitBondAtoms[1]);

	// ensure left fragment is always larger or equal to right fragment

	if (leftFragment->getNumAtoms() < rightFragment->getNumAtoms()) { 
 		leftFragment->swap(*rightFragment);
		std::swap(splitBondAtoms[0], splitBondAtoms[1]);
	}

    leftChild->splitRecursive(*leftFragment, bonds);
    rightChild->splitRecursive(*rightFragment, bonds);
}

void ConfGen::FragmentTreeNode::getSubstructure(Chem::Fragment& substruct, const Chem::Atom& atom) const
{
    using namespace Chem;

    Atom::ConstBondIterator b_it = atom.getBondsBegin();

    for (Atom::ConstAtomIterator a_it = atom.getAtomsBegin(), a_end = atom.getAtomsEnd(); a_it != a_end; ++a_it, ++b_it) {
		const Bond& bond = *b_it;

		if (substruct.containsBond(bond))
			continue;

		if (!fragment->containsBond(bond))
			continue;

		const Atom& nbr_atom = *a_it;

		if (!fragment->containsAtom(nbr_atom))
			continue;

		substruct.addBond(bond);

		getSubstructure(substruct, nbr_atom);
    } 
}

const Chem::Bond* ConfGen::FragmentTreeNode::extractMostCentralBond(BondList& bonds) const
{
    using namespace Chem;

	if (bonds.empty())
		return 0;

	Util::BitSet atom_mask(fragment->getNumAtoms());
	const Bond* mc_bond = 0;
    std::size_t mc_bond_idx = 0;
	std::size_t max_top_dist = 0;

    for (std::size_t i = 0, num_bonds = bonds.size(); i < num_bonds; i++) {
		const Bond* bond = bonds[i];

		if (!fragment->containsBond(*bond))
			continue;

		std::size_t top_dist = getMinMaxTopologicalDistance(*bond, atom_mask);

		if (!mc_bond || top_dist > max_top_dist) {
			mc_bond = bond;
			max_top_dist = top_dist;
			mc_bond_idx = i;
		}
    }

    if (mc_bond != 0) {
		bonds[mc_bond_idx] = bonds.back();
		bonds.pop_back();

		return mc_bond;
    }

    return 0;
}

std::size_t ConfGen::FragmentTreeNode::getMinMaxTopologicalDistance(const Chem::Bond& bond, Util::BitSet& atom_mask) const
{
	using namespace Chem;

	const Atom& atom1 = bond.getBegin();
	const Atom& atom2 = bond.getEnd();

	std::size_t atom1_idx = fragment->getAtomIndex(atom1);
	std::size_t atom2_idx = fragment->getAtomIndex(atom2);

	atom_mask.reset();
	atom_mask.set(atom1_idx);
	atom_mask.set(atom2_idx);

	markReachableAtoms(atom1, *fragment, atom_mask, false);
	atom_mask.reset(atom2_idx);

	std::size_t max_dist1 = getMaxTopologicalDistance(atom1, atom_mask);

	atom_mask.reset();
	atom_mask.set(atom1_idx);
	atom_mask.set(atom2_idx);

	markReachableAtoms(atom2, *fragment, atom_mask, false);
	atom_mask.reset(atom1_idx);

	std::size_t max_dist2 = getMaxTopologicalDistance(atom2, atom_mask);

	return std::min(max_dist1, max_dist2);
}

std::size_t ConfGen::FragmentTreeNode::getMaxTopologicalDistance(const Chem::Atom& atom, const Util::BitSet& atom_mask) const
{
	using namespace Chem;

	const Math::ULMatrix& dist_mtx = *getTopologicalDistanceMatrix(*root.fragment);
	std::size_t root_atom_idx = root.fragment->getAtomIndex(atom);
	std::size_t max_atom_dist = 0;

	for (Util::BitSet::size_type i = atom_mask.find_first(); i != Util::BitSet::npos; i = atom_mask.find_next(i)) {
		std::size_t dist = dist_mtx(root_atom_idx, root.fragment->getAtomIndex(fragment->getAtom(i)));

		if (dist > max_atom_dist)
			max_atom_dist = dist;
	}

	return max_atom_dist;
}
