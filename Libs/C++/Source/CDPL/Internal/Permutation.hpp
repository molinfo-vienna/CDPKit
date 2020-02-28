/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * Permutation.hpp 
 *
 * This file is part of the Chemical Data Processing Toolkit
 *
 * Copyright (C) 2003-2020 Thomas A. Seidel <thomas.seidel@univie.ac.at>
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
 * \brief Provides a function for the generation of sequence permutations.
 */

#ifndef CDPL_INTERNAL_PERMUTATION_HPP
#define CDPL_INTERNAL_PERMUTATION_HPP

#include <algorithm>
#include <iterator>


namespace CDPL
{

	namespace Internal
	{

		/**
		 * \brief Permutes the range of elements [\a first, \a last) into the 
		 *        lexicographically next greater sequence of the elements.
		 *
		 * The function treats all permutations of the range as a set of "dictionary"
		 * sorted sequences and permutes the current sequence into the next one of this
		 * set. If the current sequence is already the largest of the set, the smallest
		 * is generated. 
		 *
		 * \param first The start of the range.
		 * \param last The end of the range.
		 * \return The number of performed pairwise element swaps.
		 */
		template<typename BidirIter>
		typename std::iterator_traits<BidirIter>::difference_type nextPermutation(BidirIter first, BidirIter last);
	}
}


// Implementation

template<typename BidirIter>
typename std::iterator_traits<BidirIter>::difference_type CDPL::Internal::nextPermutation(BidirIter first, BidirIter last)
{
	if (first == last)
		return 0;

	BidirIter i = first; ++i;

	if (i == last)
		return 0;

	i = last; --i;

	while (true) {
		BidirIter k = i;
		--i;

		if (*i < *k) {
			BidirIter j = last;

			while (!(*i < *--j));

			std::iter_swap(i, j);
			std::reverse(k, last);
			
			return ((std::distance(k, last) / 2) + 1);
	    }

		if (i == first) {
			std::reverse(first, last);

			return (std::distance(first, last) / 2);
	    }
	}
}

#endif // CDPL_INTERNAL_PERMUTATION_HPP
