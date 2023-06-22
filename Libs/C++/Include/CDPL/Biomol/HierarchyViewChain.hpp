/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * HierarchyViewChain.hpp 
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

/**
 * \file
 * \brief Definition of the class CDPL::Biomol::HierarchyViewChain.
 */

#ifndef CDPL_BIOMOL_HIERARCHYVIEWCHAIN_HPP
#define CDPL_BIOMOL_HIERARCHYVIEWCHAIN_HPP

#include <cstddef>
#include <vector>
#include <memory>

#include <boost/iterator/indirect_iterator.hpp>

#include "CDPL/Biomol/APIPrefix.hpp"
#include "CDPL/Biomol/HierarchyViewFragment.hpp"
#include "CDPL/Util/BitSet.hpp"


namespace CDPL 
{

    namespace Biomol
    {

		class HierarchyViewModel;

		/**
		 * \brief HierarchyViewChain.
		 */
		class CDPL_BIOMOL_API HierarchyViewChain : public HierarchyViewNode
		{

			friend class HierarchyViewModel;

			typedef std::shared_ptr<HierarchyViewFragment> FragmentPtr;
			typedef std::vector<FragmentPtr> FragmentList;

		  public:
			typedef boost::indirect_iterator<FragmentList::const_iterator, const HierarchyViewFragment> ConstFragmentIterator;

			std::size_t getNumFragments() const;

			const HierarchyViewFragment& getFragment(std::size_t idx) const;

			ConstFragmentIterator getFragmentsBegin() const;

			ConstFragmentIterator getFragmentsEnd() const;

			ConstFragmentIterator begin() const;

			ConstFragmentIterator end() const;

		  private:
			HierarchyViewChain(): initFragments(true) {}

			void initFragmentList() const;
			void visitAtom(const Chem::Atom& atom, HierarchyViewFragment& frag, Util::BitSet& vis_atoms) const;

			mutable FragmentList fragments;
			mutable bool         initFragments;
		};
    }
}

#endif // CDPL_BIOMOL_HIERARCHYVIEWCHAIN_HPP
