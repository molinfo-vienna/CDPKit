/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * FragmentTreeNode.hpp 
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

/**
 * \file
 * \brief Definition of the class CDPL::ConfGen::FragmentTreeNode.
 */

#ifndef CDPL_CONFGEN_FRAGMENTTREENODE_HPP
#define CDPL_CONFGEN_FRAGMENTTREENODE_HPP

#include <vector>
#include <memory>
#include <cstddef>
#include <utility>

#include "CDPL/ForceField/MMFF94InteractionData.hpp"
#include "CDPL/Math/VectorArray.hpp"
#include "CDPL/Util/BitSet.hpp"


namespace CDPL 
{
 
	namespace Chem
	{

		class MolecularGraph;
		class Fragment;
		class Atom;
		class Bond;
	}

    namespace ConfGen 
    {

		class FragmentTreeNode
		{

		public:
			typedef std::pair<Math::Vector3DArray::SharedPointer, double> ConfData;
			typedef std::vector<ConfData> ConfDataArray;
			typedef std::vector<const Chem::Bond*> BondList;
			typedef std::vector<const Chem::Atom*> AtomList;
			typedef std::vector<std::size_t> IndexArray;
			typedef std::vector<double> TorsionAngleArray;	

			typedef ConfDataArray::const_iterator ConstConformerIterator;
			typedef ConfDataArray::iterator ConformerIterator;

			FragmentTreeNode();

			const FragmentTreeNode& getParent() const;

			FragmentTreeNode& getParent();

			void splitRecursive(const Chem::MolecularGraph& frag, BondList& bonds);

			const Chem::MolecularGraph& getFragment() const;

			const Chem::Bond* getSplitBond() const;

			const Chem::Atom* const* getSplitBondAtoms() const;

			const Chem::Atom* const* getTorsionReferenceAtoms() const;

			void setTorsionReferenceAtoms(const Chem::Atom* ref_atom1, const Chem::Atom* ref_atom2);

			void setFragmentType(unsigned int type);

			unsigned int getFragmentType() const;

			bool hasChildren() const;

			FragmentTreeNode* getLeftChild() const;
			FragmentTreeNode* getRightChild() const;

			void addConformer(const Math::Vector3DArray::SharedPointer& coords, double energy = 0.0);

			std::size_t getNumConformers() const;

			const ConfDataArray& getConformers() const;

			ConfDataArray& getConformers();

			const IndexArray& getRootAtomIndices() const;

			IndexArray& getRootAtomIndices();

			const TorsionAngleArray& getTorsionAngles() const;

			TorsionAngleArray& getTorsionAngles();

			ForceField::MMFF94InteractionData& getMMFF94InteractionData();

			const ForceField::MMFF94InteractionData& getMMFF94InteractionData() const;

			void setKeepAllConformersFlag(bool keep);

			bool getKeepAllConformersFlag() const;

			AtomList& getSplitBondAtom1Neighbors();

			const AtomList& getSplitBondAtom1Neighbors() const;

			AtomList& getSplitBondAtom2Neighbors();

			const AtomList& getSplitBondAtom2Neighbors() const;


		private:
			FragmentTreeNode(FragmentTreeNode& root, FragmentTreeNode& parent); 

			FragmentTreeNode(const FragmentTreeNode&);

			FragmentTreeNode& operator=(const FragmentTreeNode&);

			void getSubstructure(Chem::Fragment& substruct, const Chem::Atom& atom) const;

			const Chem::Bond* extractMostCentralBond(BondList& bonds) const;

			std::size_t getMinMaxTopologicalDistance(const Chem::Bond& bond, Util::BitSet& atom_mask) const;
			std::size_t getMaxTopologicalDistance(const Chem::Atom& atom, const Util::BitSet& atom_mask) const;
			
			typedef std::auto_ptr<FragmentTreeNode> NodePointer;
			typedef std::auto_ptr<Chem::Fragment> FragmentPointer;
	
			FragmentTreeNode&                 root;
			FragmentTreeNode&                 parent;
			const Chem::MolecularGraph*       fragment;
			const Chem::Bond*                 splitBond;
			const Chem::Atom*                 splitBondAtoms[2];
			const Chem::Atom*                 torsionRefAtoms[2];
			AtomList                          splitBondAtom1Nbrs;
			AtomList                          splitBondAtom2Nbrs;
			bool                              keepAllConfsFlag;
			NodePointer                       leftChild;
			NodePointer                       rightChild;
			FragmentPointer                   leftFragment;
			FragmentPointer                   rightFragment;
			unsigned int                      fragmentType;
			IndexArray                        rootAtomIndices;
			ConfDataArray                     conformers;
			TorsionAngleArray                 torsionAngles;
			ForceField::MMFF94InteractionData mmff94Data;
		};
    }
}

#endif // CDPL_CONFGEN_FRAGMENTTREENODE_HPP
