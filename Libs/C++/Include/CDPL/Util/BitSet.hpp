/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * BitSet.hpp 
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
 * \brief Definition of the type CDPL::Util::BitSet.
 */

#ifndef CDPL_UTIL_BITSET_HPP
#define CDPL_UTIL_BITSET_HPP

#include <boost/dynamic_bitset.hpp>


namespace CDPL
{

	namespace Util
	{

		/**
		 * \brief A dynamic bitset class.
		 *
		 * For further information see [\ref BDBS].
		 */
		typedef boost::dynamic_bitset<> BitSet;

		/**
		 * \brief Folds the bitset \a bs the specified number of times.
		 *
		 * Folding a bitset means that the lower and upper half of the bitset are combined
		 * by a logical OR operation to produce a new bitset which is half of the original
		 * size. This process is repeated the specified number of times. See also [\ref DTPFP].
		 *
		 * \param bs The bitset to fold.
		 * \param num_times The number of times the bitset has to be folded.
		 */
		inline void fold(BitSet& bs, std::size_t num_times)
		{
			BitSet tmp;

			for (std::size_t i = 0, new_num_bits = bs.size() >> 1; i < num_times; i++, new_num_bits >>= 1) {
				tmp = bs;
				tmp >>= new_num_bits;
		
				bs |= tmp;
				bs.resize(new_num_bits);
			}
		}
	}
}

#endif // CDPL_UTIL_BITSET_HPP
