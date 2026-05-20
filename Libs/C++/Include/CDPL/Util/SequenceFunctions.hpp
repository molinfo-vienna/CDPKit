/* 
 * SequenceFunctions.hpp 
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
 * \brief Utility functions for sequential processing.
 */

#ifndef CDPL_UTIL_SEQUENCEFUNCTIONS_HPP
#define CDPL_UTIL_SEQUENCEFUNCTIONS_HPP

#include "CDPL/Util/APIPrefix.hpp"


namespace CDPL
{

    namespace Util
    {

        /**
         * \brief Invokes the binary function \a func on every pair of corresponding elements drawn from two parallel input sequences.
         * \tparam InputIt1 The input iterator type of the first sequence.
         * \tparam InputIt2 The input iterator type of the second sequence.
         * \tparam BinaryFunc The type of the binary function.
         * \param it1 An iterator pointing to the first element of the first sequence.
         * \param end1 An iterator pointing one past the last element of the first sequence.
         * \param it2 An iterator pointing to the first element of the second sequence (assumed to have at least as many elements as the first).
         * \param func The binary function invoked for each pair.
         */
        template <typename InputIt1, typename InputIt2, typename BinaryFunc>
        void forEachPair(InputIt1 it1, InputIt1 end1, InputIt2 it2, BinaryFunc func);

        /**
         * \brief Invokes the binary function \a func on every pair of corresponding elements drawn from two parallel input sequences,
         *        stopping when either sequence is exhausted.
         * \tparam InputIt1 The input iterator type of the first sequence.
         * \tparam InputIt2 The input iterator type of the second sequence.
         * \tparam BinaryFunc The type of the binary function.
         * \param it1 An iterator pointing to the first element of the first sequence.
         * \param end1 An iterator pointing one past the last element of the first sequence.
         * \param it2 An iterator pointing to the first element of the second sequence.
         * \param end2 An iterator pointing one past the last element of the second sequence.
         * \param func The binary function invoked for each pair.
         */
        template <typename InputIt1, typename InputIt2, typename BinaryFunc>
        void forEachPair(InputIt1 it1, InputIt1 end1, InputIt2 it2, InputIt2 end2, BinaryFunc func);
    } // namespace Util
} // namespace CDPL


// Implementation
// \cond DOC_IMPL_DETAILS

template <typename InputIt1, typename InputIt2, typename BinaryFunc>
void CDPL::Util::forEachPair(InputIt1 it1, InputIt1 end1, InputIt2 it2, BinaryFunc func)
{
    for (; it1 != end1; ++it1, ++it2)
        func(*it1, *it2);
}

template <typename InputIt1, typename InputIt2, typename BinaryFunc>
void CDPL::Util::forEachPair(InputIt1 it1, InputIt1 end1, InputIt2 it2, InputIt2 end2, BinaryFunc func)
{
    for (; it1 != end1 && it2 != end2; ++it1, ++it2)
        func(*it1, *it2);
}

// \endcond

#endif // CDPL_UTIL_SEQUENCEFUNCTIONS_HPP
