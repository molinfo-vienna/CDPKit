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
//#include <iosfwd>

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
			typedef std::vector<const Chem::Bond*> BondList;
			typedef std::vector<FragmentTreeNode*> NodeList;
	
			FragmentTreeNode();

			void splitRecursive(const Chem::MolecularGraph& frag, BondList& bonds);

			const Chem::MolecularGraph& getFragment() const;

			const Chem::Bond* getSplitBond() const;

			void setFragmentType(unsigned int type);

			unsigned int getFragmentType() const;

			bool hasChildren() const;

			FragmentTreeNode* getLeftChild() const;
			FragmentTreeNode* getRightChild() const;

			void getLeafNodes(NodeList& nodes);

			//void printTree(std::ostream& os) const;

		private:
			FragmentTreeNode(FragmentTreeNode& root); 

			FragmentTreeNode(const FragmentTreeNode&);

			FragmentTreeNode& operator=(const FragmentTreeNode&);

			void getSubstructure(Chem::Fragment& substruct, const Chem::Atom& atom) const;

			const Chem::Bond* extractMostCentralBond(BondList& bonds) const;

			std::size_t getMinMaxTopologicalDistance(const Chem::Bond& bond, Util::BitSet& atom_mask) const;
			std::size_t getMaxTopologicalDistance(const Chem::Atom& atom, const Util::BitSet& atom_mask) const;
			
			typedef std::auto_ptr<FragmentTreeNode> NodePointer;
			typedef std::auto_ptr<Chem::Fragment> FragmentPointer;

			FragmentTreeNode&           root;
			const Chem::MolecularGraph* fragment;
			const Chem::Bond*           splitBond;
			NodePointer                 leftChild;
			NodePointer                 rightChild;
			FragmentPointer             leftFragment;
			FragmentPointer             rightFragment;
			unsigned int                fragmentType;
		};
    }
}

#endif // CDPL_CONFGEN_FRAGMENTTREENODE_HPP
