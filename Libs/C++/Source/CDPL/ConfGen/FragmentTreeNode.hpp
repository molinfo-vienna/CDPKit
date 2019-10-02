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

#include "CDPL/ConfGen/ConformerData.hpp"
#include "CDPL/ForceField/MMFF94InteractionData.hpp"
#include "CDPL/Util/BitSet.hpp"


namespace CDPL 
{

	namespace Chem
	{

		class MolecularGraph;
		class Atom;
		class Bond;
	}

    namespace ConfGen 
    {

		class FragmentTree;

		class FragmentTreeNode
		{

			friend class FragmentTree;

		public:
			typedef std::vector<ConformerData::SharedPointer> ConformerDataArray;
			typedef std::vector<std::size_t> IndexArray;
			typedef std::vector<double> TorsionAngleArray;	

			FragmentTreeNode* getParent() const;

			const Chem::MolecularGraph* getFragment() const;
			const Chem::MolecularGraph* getRootFragment() const;

			const Chem::Bond* getSplitBond() const;

			const Chem::Atom* const* getSplitBondAtoms() const;

			const Chem::Atom* const* getTorsionReferenceAtoms() const;

			void setTorsionReferenceAtoms(const Chem::Atom* left, const Chem::Atom* right);

			bool hasChildren() const;

			FragmentTreeNode* getLeftChild() const;
			FragmentTreeNode* getRightChild() const;

			const ConformerDataArray& getConformers() const;

			ConformerDataArray& getConformers();

			const IndexArray& getAtomIndices() const;

			const Util::BitSet& getAtomMask() const;

			const Util::BitSet& getCoreAtomMask() const;

			const TorsionAngleArray& getTorsionAngles() const;

			TorsionAngleArray& getTorsionAngles();

			ForceField::MMFF94InteractionData& getMMFF94InteractionData();

			const ForceField::MMFF94InteractionData& getMMFF94InteractionData() const;

		private:
			FragmentTreeNode();

			FragmentTreeNode(const FragmentTreeNode&);

			FragmentTreeNode& operator=(const FragmentTreeNode&);

			void setParent(FragmentTreeNode* node);

			void setChildren(FragmentTreeNode* left, FragmentTreeNode* right);

			void setSplitBond(const Chem::Bond* bond);
			void setSplitBondAtoms(const Chem::Atom* left, const Chem::Atom* right);

			void setFragment(const Chem::MolecularGraph* frag);
			void setRootFragment(const Chem::MolecularGraph* frag);

			void initFragmentData();
			void initFragmentData(const Chem::MolecularGraph& frag, const Chem::MolecularGraph& root_frag);
			
			FragmentTreeNode*                   parent;
			const Chem::Bond*                   splitBond;
			const Chem::Atom*                   splitBondAtoms[2];
			const Chem::Atom*                   torsionRefAtoms[2];
			FragmentTreeNode*                   leftChild;
			FragmentTreeNode*                   rightChild;
			IndexArray                          atomIndices;
			Util::BitSet                        atomMask;
			Util::BitSet                        coreAtomMask;
			const Chem::MolecularGraph*         rootFragment;
			const Chem::MolecularGraph*         fragment;
			ConformerDataArray                  conformers;
			TorsionAngleArray                   torsionAngles;
			ForceField::MMFF94InteractionData   mmff94Data;
		};
    }
}

#endif // CDPL_CONFGEN_FRAGMENTTREENODE_HPP
