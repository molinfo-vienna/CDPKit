/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * BondFragmentMembershipFunctions.cpp 
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

#include <boost/bind.hpp>

#include "CDPL/Chem/BondFunctions.hpp"


using namespace CDPL; 


bool Chem::isInFragmentOfSize(const Bond& bond, const FragmentList& frag_list, std::size_t size)
{
	for (FragmentList::ConstElementIterator it = frag_list.getElementsBegin(), 
			 end = frag_list.getElementsEnd(); it != end; ++it) {
	
		const Fragment& frag = *it;

		if (frag.containsBond(bond) && frag.getNumAtoms() == size)
			return true;
	}

	return false;
}

std::size_t Chem::getSizeOfSmallestContainingFragment(const Bond& bond, const FragmentList& frag_list)
{
	std::size_t smallest_rsize = 0;

	for (FragmentList::ConstElementIterator it = frag_list.getElementsBegin(), 
			 end = frag_list.getElementsEnd(); it != end; ++it) {
	
		const Fragment& frag = *it;

		if (frag.containsBond(bond) && (smallest_rsize == 0 || frag.getNumAtoms() < smallest_rsize))
			smallest_rsize = frag.getNumAtoms();
	}

	return smallest_rsize;
}

std::size_t Chem::getSizeOfLargestContainingFragment(const Bond& bond, const FragmentList& frag_list)
{
	std::size_t largest_rsize = 0;

	for (FragmentList::ConstElementIterator it = frag_list.getElementsBegin(), 
			 end = frag_list.getElementsEnd(); it != end; ++it) {
	
		const Fragment& frag = *it;

		if (frag.containsBond(bond) && frag.getNumAtoms() > largest_rsize)
			largest_rsize = frag.getNumAtoms();
	}

	return largest_rsize;
}

std::size_t Chem::getNumContainingFragments(const Bond& bond, const FragmentList& frag_list)
{
	std::size_t count = std::count_if(frag_list.getElementsBegin(), frag_list.getElementsEnd(), 
									  boost::bind(&Fragment::containsBond, _1, boost::ref(bond)));

	return count;
}

void Chem::getContainingFragments(const Bond& bond, const FragmentList& frag_list, FragmentList& cont_frag_list)
{
	for (FragmentList::BaseType::ConstElementIterator it = frag_list.getBase().getElementsBegin(), 
			 end = frag_list.getBase().getElementsEnd(); it != end; ++it)
		if ((*it)->containsBond(bond))
			cont_frag_list.addElement(*it);
}
