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

#include "CDPL/Chem/MolecularGraph.hpp"
#include "CDPL/Chem/Atom.hpp"
#include "CDPL/Chem/AtomFunctions.hpp"

#include "FragmentTreeNode.hpp"
#include "FragmentTree.hpp"
#include "ForceFieldInteractionMask.hpp"


using namespace CDPL;


namespace
{

	template <typename InteractionData>
	void extractFragmentMMFF94InteractionData2(const InteractionData& src_ia_data, InteractionData& tgt_ia_data,
											   Util::BitSet& free_ia_mask, const Util::BitSet& tgt_atom_mask)
	{
		for (Util::BitSet::size_type i = free_ia_mask.find_first(); i != Util::BitSet::npos; i = free_ia_mask.find_next(i)) {
			const typename InteractionData::ElementType& params = src_ia_data[i];

			if (tgt_atom_mask.test(params.getAtom1Index()) && 
				tgt_atom_mask.test(params.getAtom2Index())) {

				tgt_ia_data.addElement(params);
				free_ia_mask.reset(i);
			}
		}
	}

	template <typename InteractionData>
	void extractFragmentMMFF94InteractionData3(const InteractionData& src_ia_data, InteractionData& tgt_ia_data,
											   Util::BitSet& free_ia_mask, const Util::BitSet& tgt_atom_mask)
	{
		for (Util::BitSet::size_type i = free_ia_mask.find_first(); i != Util::BitSet::npos; i = free_ia_mask.find_next(i)) {
			const typename InteractionData::ElementType& params = src_ia_data[i];

			if (tgt_atom_mask.test(params.getAtom1Index()) &&
				tgt_atom_mask.test(params.getAtom2Index()) && 
				tgt_atom_mask.test(params.getAtom3Index())) {

				tgt_ia_data.addElement(params);
				free_ia_mask.reset(i);
			}
		}
	}

	template <typename InteractionData>
	void extractFragmentMMFF94InteractionData4(const InteractionData& src_ia_data, InteractionData& tgt_ia_data,
											   Util::BitSet& free_ia_mask, const Util::BitSet& tgt_atom_mask)
	{
		for (Util::BitSet::size_type i = free_ia_mask.find_first(); i != Util::BitSet::npos; i = free_ia_mask.find_next(i)) {
			const typename InteractionData::ElementType& params = src_ia_data[i];

			if (tgt_atom_mask.test(params.getAtom1Index()) &&
				tgt_atom_mask.test(params.getAtom2Index()) && 
				tgt_atom_mask.test(params.getAtom3Index()) &&
				tgt_atom_mask.test(params.getAtom4Index())) {

				tgt_ia_data.addElement(params);
				free_ia_mask.reset(i);
			}
		}
	}
}


ConfGen::FragmentTreeNode::FragmentTreeNode(ConfGen::FragmentTree& owner): 
	owner(owner), parent(0), splitBond(0), splitBondLength(0.0), rootFragment(), fragment(0)
{
	splitBondAtoms[0] = 0;
	splitBondAtoms[1] = 0;

	torsionRefAtoms[0] = 0;
	torsionRefAtoms[1] = 0;
}

ConfGen::FragmentTreeNode* ConfGen::FragmentTreeNode::getParent() const
{
	return parent;
}

const Chem::MolecularGraph* ConfGen::FragmentTreeNode::getFragment() const
{
	return fragment;
}

const Chem::MolecularGraph* ConfGen::FragmentTreeNode::getRootFragment() const
{
	return rootFragment;
}

const Chem::Bond* ConfGen::FragmentTreeNode::getSplitBond() const
{
	return splitBond;
}

void ConfGen::FragmentTreeNode:: setSplitBondLength(double length)
{
	splitBondLength = length;
}

double ConfGen::FragmentTreeNode::getSplitBondLength() const
{
	return splitBondLength;
}

const Chem::Atom* const* ConfGen::FragmentTreeNode::getSplitBondAtoms() const
{
	return splitBondAtoms;
}

const Chem::Atom* const* ConfGen::FragmentTreeNode::getTorsionReferenceAtoms() const
{
	return torsionRefAtoms;
}

void ConfGen::FragmentTreeNode::setTorsionReferenceAtoms(const Chem::Atom* left, const Chem::Atom* right)
{
	torsionRefAtoms[0] = left;
	torsionRefAtoms[1] = right;
}

bool ConfGen::FragmentTreeNode::hasChildren() const
{
	return (leftChild && rightChild);
}

ConfGen::FragmentTreeNode* ConfGen::FragmentTreeNode::getLeftChild() const
{
	return leftChild;
}

ConfGen::FragmentTreeNode* ConfGen::FragmentTreeNode::getRightChild() const
{
	return rightChild;
}

const ConfGen::FragmentTreeNode::ConformerDataArray& ConfGen::FragmentTreeNode::getConformers() const
{
	return conformers;
}

ConfGen::FragmentTreeNode::ConformerDataArray& ConfGen::FragmentTreeNode::getConformers()
{
	return conformers;
}

const ConfGen::FragmentTreeNode::IndexArray& ConfGen::FragmentTreeNode::getAtomIndices() const
{
	return atomIndices;
}

const Util::BitSet& ConfGen::FragmentTreeNode::getAtomMask() const
{
	return atomMask;
}

const Util::BitSet& ConfGen::FragmentTreeNode::getCoreAtomMask() const
{
	return coreAtomMask;
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

const ForceField::MMFF94InteractionData& ConfGen::FragmentTreeNode::getMMFF94InteractionData() const
{
	return mmff94Data;
}

void ConfGen::FragmentTreeNode::extractMMFF94Interactions(const ForceField::MMFF94InteractionData& ia_data,
														  ForceFieldInteractionMask& ia_mask)
{
	if (leftChild)
		leftChild->extractMMFF94Interactions(ia_data, ia_mask);

	if (rightChild)
		rightChild->extractMMFF94Interactions(ia_data, ia_mask);

	extractFragmentMMFF94InteractionData2(ia_data.getBondStretchingInteractions(), mmff94Data.getBondStretchingInteractions(), 
										  ia_mask.bondStretching, coreAtomMask);
	extractFragmentMMFF94InteractionData2(ia_data.getElectrostaticInteractions(), mmff94Data.getElectrostaticInteractions(), 
										  ia_mask.electrostatic, coreAtomMask);
	extractFragmentMMFF94InteractionData2(ia_data.getVanDerWaalsInteractions(), mmff94Data.getVanDerWaalsInteractions(), 
										  ia_mask.vanDerWaals, coreAtomMask);
	extractFragmentMMFF94InteractionData3(ia_data.getAngleBendingInteractions(), mmff94Data.getAngleBendingInteractions(), 
										  ia_mask.angleBending, atomMask);
	extractFragmentMMFF94InteractionData3(ia_data.getStretchBendInteractions(), mmff94Data.getStretchBendInteractions(), 
										  ia_mask.stretchBend, atomMask);
	extractFragmentMMFF94InteractionData4(ia_data.getOutOfPlaneBendingInteractions(), mmff94Data.getOutOfPlaneBendingInteractions(), 
										  ia_mask.outOfPlaneBending, atomMask);
	extractFragmentMMFF94InteractionData4(ia_data.getTorsionInteractions(), mmff94Data.getTorsionInteractions(), 
										  ia_mask.torsion, atomMask);
}

void ConfGen::FragmentTreeNode::setParent(FragmentTreeNode* node)
{
	parent = node;
}

void ConfGen::FragmentTreeNode::setSplitBond(const Chem::Bond* bond)
{
	splitBond = bond;
}

void ConfGen::FragmentTreeNode::setSplitBondAtoms(const Chem::Atom* left, const Chem::Atom* right)
{
	splitBondAtoms[0] = left;
	splitBondAtoms[1] = right;
}

void ConfGen::FragmentTreeNode::setChildren(FragmentTreeNode* left, FragmentTreeNode* right)
{
	leftChild = left;
	rightChild = right;
}

void ConfGen::FragmentTreeNode::setFragment(const Chem::MolecularGraph* frag)
{
	fragment = frag;
}

void ConfGen::FragmentTreeNode::setRootFragment(const Chem::MolecularGraph* frag)
{
	rootFragment = frag;
}

void ConfGen::FragmentTreeNode::initFragmentData()
{
	if (!hasChildren()) // sanity check
		return;
		
	atomMask = leftChild->atomMask;
	atomMask |= rightChild->atomMask;

	coreAtomMask = leftChild->coreAtomMask;
	coreAtomMask |= rightChild->coreAtomMask;

	atomIndices.clear();

	for (Util::BitSet::size_type i = atomMask.find_first(); i != Util::BitSet::npos; i = atomMask.find_next(i))
		atomIndices.push_back(i);
}

void ConfGen::FragmentTreeNode::initFragmentData(const Chem::MolecularGraph& frag, const Chem::MolecularGraph& root_frag)
{
	using namespace Chem;

	std::size_t num_atoms = root_frag.getNumAtoms();

	atomMask.resize(num_atoms);
	atomMask.reset();

	coreAtomMask.resize(num_atoms);
	coreAtomMask.reset();

	atomIndices.clear();

	for (MolecularGraph::ConstAtomIterator it = frag.getAtomsBegin(), end = frag.getAtomsEnd(); it != end; ++it) {
		const Atom& atom = *it;
		std::size_t atom_idx = root_frag.getAtomIndex(atom);

		atomIndices.push_back(atom_idx);
		atomMask.set(atom_idx);

		if (getExplicitBondCount(atom, frag) == 1 && getExplicitBondCount(atom, root_frag) > 1) // is connected fragment atom?
			continue;

		coreAtomMask.set(atom_idx);
	}
}
