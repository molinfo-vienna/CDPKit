/* 
 * Slice.hpp 
 *
 * Copyright (C) 2010-2011 Thomas Seidel <thomas.seidel@univie.ac.at>
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
 * \brief Definition of a data type for describing index slices.
 */

#ifndef CDPL_MATH_SLICE_HPP
#define CDPL_MATH_SLICE_HPP

#include <cstddef>
#include <utility>

#include "CDPL/Math/Check.hpp"
#include "CDPL/Base/Exceptions.hpp"


namespace CDPL
{

    namespace Math
    {

        template <typename S, typename D>
        class Slice
        {

            typedef Slice<S, D> SelfType;

          public:
            typedef S SizeType;
            typedef D DifferenceType;

            Slice():
                start(0), stride(0), size(0) {}

            Slice(SizeType start, DifferenceType stride, SizeType size):
                start(start), stride(stride), size(size)
            {
                CDPL_MATH_CHECK(stride >= 0 || size == 0 || start >= -stride * (size - 1), "Invalid slice specification", Base::RangeError);
            }

            SizeType operator()(SizeType i) const
            {
                CDPL_MATH_CHECK(i < getSize(), "Index out of range", Base::IndexError);
                return (start + i * stride);
            }

            SizeType getStart() const
            {
                return start;
            }

            DifferenceType getStride() const
            {
                return stride;
            }

            SizeType getSize() const
            {
                return size;
            }

            bool isEmpty() const
            {
                return (size == 0);
            }

            bool operator==(const Slice& s) const
            {
                return (start == s.start && stride == s.stride && size == s.size);
            }

            bool operator!=(const Slice& s) const
            {
                return !this->operator==(s);
            }

            void swap(Slice& s)
            {
                if (this == &s)
                    return;

                std::swap(start, s.start);
                std::swap(stride, s.stride);
                std::swap(size, s.size);
            }

            friend void swap(Slice& s1, Slice& s2)
            {
                s1.swap(s2);
            }

          private:
            SizeType       start;
            DifferenceType stride;
            SizeType       size;
        };

        inline Slice<std::size_t, std::ptrdiff_t>
        slice(std::size_t start, std::ptrdiff_t stride, std::size_t size)
        {
            return Slice<std::size_t, std::ptrdiff_t>(start, stride, size);
        }
    } // namespace Math
} // namespace CDPL

#endif // CDPL_MATH_SLICE_HPP
