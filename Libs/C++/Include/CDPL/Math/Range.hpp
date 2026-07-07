/* 
 * Range.hpp 
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
 * \brief Definition of a data type for describing index ranges.
 */

#ifndef CDPL_MATH_RANGE_HPP
#define CDPL_MATH_RANGE_HPP

#include <cstddef>
#include <utility>

#include "CDPL/Math/Check.hpp"
#include "CDPL/Base/Exceptions.hpp"


namespace CDPL
{

    namespace Math
    {

        /**
         * \brief Half-open index range <em>[start, stop)</em> used for slicing vector and matrix expressions.
         * \tparam S The integral size/index type.
         */
        template <typename S>
        class Range
        {

            typedef Range<S> SelfType;

          public:
            /**
             * \brief The integral size/index type.
             */
            typedef S SizeType;

            /**
             * \brief Constructs an empty range [0, 0).
             */
            Range():
                start(0), stop(0) {}

            /**
             * \brief Constructs the range [\a start, \a stop).
             * \param start The lower (inclusive) bound.
             * \param stop The upper (exclusive) bound.
             * \throw Base::RangeError if \a start \> \a stop.
             */
            Range(SizeType start, SizeType stop):
                start(start), stop(stop)
            {
                CDPL_MATH_CHECK(start <= stop, "Invalid range specification", Base::RangeError);
            }

            /**
             * \brief Maps the local position \a i to the global index \f$ start + i \f$.
             * \param i The zero-based local position.
             * \return The global index.
             * \throw Base::IndexError if \a i is not in the range [0, getSize()).
             */
            SizeType operator()(SizeType i) const
            {
                CDPL_MATH_CHECK(i < getSize(), "Index out of range", Base::IndexError);
                return (start + i);
            }

            /**
             * \brief Returns the lower (inclusive) bound.
             * \return The lower bound.
             */
            SizeType getStart() const
            {
                return start;
            }

            /**
             * \brief Returns the upper (exclusive) bound.
             * \return The upper bound.
             */
            SizeType getStop() const
            {
                return stop;
            }

            /**
             * \brief Returns the size of the range.
             * \return The range size.
             */
            SizeType getSize() const
            {
                return (stop - start);
            }

            /**
             * \brief Tells whether the range is empty.
             * \return \c true if the range is empty, and \c false otherwise.
             */
            bool isEmpty() const
            {
                return (stop == start);
            }

            /**
             * \brief Equality comparison.
             * \param r The other range.
             * \return \c true if both ranges have the same start and stop, and \c false otherwise.
             */
            bool operator==(const Range& r) const
            {
                return (start == r.start && stop == r.stop);
            }

            /**
             * \brief Inequality comparison.
             * \param r The other range.
             * \return \c true if the ranges differ in start or stop, and \c false otherwise.
             */
            bool operator!=(const Range& r) const
            {
                return !this->operator==(r);
            }

            /**
             * \brief Swaps the contents of \c *this and \a r.
             * \param r The other range.
             */
            void swap(Range& r)
            {
                if (this == &r)
                    return;

                std::swap(start, r.start);
                std::swap(stop, r.stop);
            }

            /**
             * \brief Free-function swap overload.
             * \param r1 The first range.
             * \param r2 The second range.
             */
            friend void swap(Range& r1, Range& r2)
            {
                r1.swap(r2);
            }

          private:
            SizeType start;
            SizeType stop;
        };

        /**
         * \brief Convenience factory function for Math::Range with \c std::size_t indices.
         * \param start The lower (inclusive) bound.
         * \param stop The upper (exclusive) bound.
         * \return The constructed Math::Range instance.
         */
        inline Range<std::size_t>
        range(std::size_t start, std::size_t stop)
        {
            return Range<std::size_t>(start, stop);
        }
    } // namespace Math
} // namespace CDPL

#endif // CDPL_MATH_RANGE_HPP
