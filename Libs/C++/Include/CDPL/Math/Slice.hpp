/* 
 * Slice.hpp 
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

        /**
         * \brief Index slice (\f$ start, stride, size \f$) used for strided slicing of vector and matrix expressions.
         *
         * Local position \a i is mapped to the global index \f$ start + i \cdot stride \f$. Negative strides
         * (reverse iteration) are supported as long as the resulting indices stay non-negative.
         *
         * \tparam S The integral size/index type.
         * \tparam D The signed difference type used for the stride.
         */
        template <typename S, typename D>
        class Slice
        {

            typedef Slice<S, D> SelfType;

          public:
            /** \brief The integral size/index type. */
            typedef S SizeType;
            /** \brief The signed difference type used for the stride. */
            typedef D DifferenceType;

            /**
             * \brief Constructs an empty slice (\f$ 0, 0, 0 \f$).
             */
            Slice():
                start(0), stride(0), size(0) {}

            /**
             * \brief Constructs the slice (\a start, \a stride, \a size).
             * \param start The starting global index.
             * \param stride The signed step size between consecutive entries.
             * \param size The number of entries.
             * \throw Base::RangeError if the slice would produce a negative global index.
             */
            Slice(SizeType start, DifferenceType stride, SizeType size):
                start(start), stride(stride), size(size)
            {
                CDPL_MATH_CHECK(stride >= 0 || size == 0 || start >= -stride * (size - 1), "Invalid slice specification", Base::RangeError);
            }

            /**
             * \brief Maps the local position \a i to the global index \f$ start + i \cdot stride \f$.
             * \param i The zero-based local position.
             * \return The global index.
             * \throw Base::IndexError if \a i is not in the range \f$ [0, size) \f$.
             */
            SizeType operator()(SizeType i) const
            {
                CDPL_MATH_CHECK(i < getSize(), "Index out of range", Base::IndexError);
                return (start + i * stride);
            }

            /**
             * \brief Returns the starting global index.
             * \return The starting index.
             */
            SizeType getStart() const
            {
                return start;
            }

            /**
             * \brief Returns the signed step size between consecutive entries.
             * \return The stride.
             */
            DifferenceType getStride() const
            {
                return stride;
            }

            /**
             * \brief Returns the number of entries in the slice.
             * \return The slice size.
             */
            SizeType getSize() const
            {
                return size;
            }

            /**
             * \brief Tells whether the slice is empty.
             * \return \c true if the slice contains no entries, and \c false otherwise.
             */
            bool isEmpty() const
            {
                return (size == 0);
            }

            /**
             * \brief Equality comparison.
             * \param s The other slice.
             * \return \c true if both slices have the same start, stride and size, and \c false otherwise.
             */
            bool operator==(const Slice& s) const
            {
                return (start == s.start && stride == s.stride && size == s.size);
            }

            /**
             * \brief Inequality comparison.
             * \param s The other slice.
             * \return \c true if the slices differ in start, stride or size, and \c false otherwise.
             */
            bool operator!=(const Slice& s) const
            {
                return !this->operator==(s);
            }

            /**
             * \brief Swaps the contents of \c *this and \a s.
             * \param s The other slice.
             */
            void swap(Slice& s)
            {
                if (this == &s)
                    return;

                std::swap(start, s.start);
                std::swap(stride, s.stride);
                std::swap(size, s.size);
            }

            /**
             * \brief Free-function swap overload.
             * \param s1 The first slice.
             * \param s2 The second slice.
             */
            friend void swap(Slice& s1, Slice& s2)
            {
                s1.swap(s2);
            }

          private:
            SizeType       start;
            DifferenceType stride;
            SizeType       size;
        };

        /**
         * \brief Convenience factory for Math::Slice with \c std::size_t indices and \c std::ptrdiff_t stride.
         * \param start The starting global index.
         * \param stride The signed step size between consecutive entries.
         * \param size The number of entries.
         * \return The constructed Math::Slice instance.
         */
        inline Slice<std::size_t, std::ptrdiff_t>
        slice(std::size_t start, std::ptrdiff_t stride, std::size_t size)
        {
            return Slice<std::size_t, std::ptrdiff_t>(start, stride, size);
        }
    } // namespace Math
} // namespace CDPL

#endif // CDPL_MATH_SLICE_HPP
