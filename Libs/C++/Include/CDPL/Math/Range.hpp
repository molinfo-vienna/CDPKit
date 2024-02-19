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

        template <typename S>
        class Range
        {

            typedef Range<S> SelfType;

          public:
            typedef S SizeType;

            Range():
                start(0), stop(0) {}

            Range(SizeType start, SizeType stop):
                start(start), stop(stop)
            {
                CDPL_MATH_CHECK(start <= stop, "Invalid range specification", Base::RangeError);
            }

            SizeType operator()(SizeType i) const
            {
                CDPL_MATH_CHECK(i < getSize(), "Index out of range", Base::IndexError);
                return (start + i);
            }

            SizeType getStart() const
            {
                return start;
            }

            SizeType getStop() const
            {
                return stop;
            }

            SizeType getSize() const
            {
                return (stop - start);
            }

            bool isEmpty() const
            {
                return (stop == start);
            }

            bool operator==(const Range& r) const
            {
                return (start == r.start && stop == r.stop);
            }

            bool operator!=(const Range& r) const
            {
                return !this->operator==(r);
            }

            void swap(Range& r)
            {
                if (this == &r)
                    return;

                std::swap(start, r.start);
                std::swap(stop, r.stop);
            }

            friend void swap(Range& r1, Range& r2)
            {
                r1.swap(r2);
            }

          private:
            SizeType start;
            SizeType stop;
        };

        inline Range<std::size_t>
        range(std::size_t start, std::size_t stop)
        {
            return Range<std::size_t>(start, stop);
        }
    } // namespace Math
} // namespace CDPL

#endif // CDPL_MATH_RANGE_HPP
