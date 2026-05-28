/* 
 * VectorProxy.hpp 
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
 * \brief Definition of vector proxy types.
 */

#ifndef CDPL_MATH_VECTORPROXY_HPP
#define CDPL_MATH_VECTORPROXY_HPP

#include <type_traits>

#include "CDPL/Math/Expression.hpp"
#include "CDPL/Math/VectorAssignment.hpp"
#include "CDPL/Math/TypeTraits.hpp"
#include "CDPL/Math/Functional.hpp"
#include "CDPL/Math/Range.hpp"
#include "CDPL/Math/Slice.hpp"


namespace CDPL
{

    namespace Math
    {

        /**
         * \brief Vector-expression proxy that views a contiguous half-open subrange of an underlying vector.
         * \tparam V The wrapped vector type.
         */
        template <typename V>
        class VectorRange : public VectorExpression<VectorRange<V> >
        {

            typedef VectorRange<V> SelfType;

          public:
            /** \brief The wrapped vector type. */
            typedef V                                                        VectorType;
            /** \brief The size type used by the wrapped vector. */
            typedef typename V::SizeType                                     SizeType;
            /** \brief The signed difference type used by the wrapped vector. */
            typedef typename V::DifferenceType                               DifferenceType;
            /** \brief The element value type of the wrapped vector. */
            typedef typename V::ValueType                                    ValueType;
            /** \brief Constant reference type to an element. */
            typedef typename V::ConstReference                               ConstReference;
            /** \brief Mutable reference type (degrades to ConstReference when the wrapped vector is \c const). */
            typedef typename std::conditional<std::is_const<V>::value,
                                              typename V::ConstReference,
                                              typename V::Reference>::type   Reference;
            /** \brief Closure type used to store the wrapped vector internally (mutable or const flavor). */
            typedef typename std::conditional<std::is_const<V>::value,
                                              typename V::ConstClosureType,
                                              typename V::ClosureType>::type VectorClosureType;
            /** \brief Constant closure type used when this proxy appears inside another expression. */
            typedef const SelfType                                           ConstClosureType;
            /** \brief Closure type used when this proxy appears inside another expression. */
            typedef SelfType                                                 ClosureType;
            /** \brief The Math::Range type defining the half-open index subrange. */
            typedef Range<SizeType>                                          RangeType;

            /**
             * \brief Constructs the proxy viewing the subrange \a r of \a v.
             * \param v The wrapped vector.
             * \param r The half-open index range selecting the viewed subrange.
             */
            VectorRange(VectorType& v, const RangeType& r):
                data(v), range(r) {}

            /**
             * \brief Returns a mutable reference to the element at index \a i of the view.
             * \param i The zero-based index within the view.
             * \return A mutable reference to the underlying element <tt>v(range(i))</tt>.
             */
            Reference operator()(SizeType i)
            {
                return data(range(i));
            }

            /**
             * \brief Returns a \c const reference to the element at index \a i of the view.
             * \param i The zero-based index within the view.
             * \return A \c const reference to the underlying element <tt>v(range(i))</tt>.
             */
            ConstReference operator()(SizeType i) const
            {
                return data(range(i));
            }

            /**
             * \brief Returns a mutable reference to the element at index \a i of the view (alias for operator()).
             * \param i The zero-based index within the view.
             * \return A mutable reference to the underlying element.
             */
            Reference operator[](SizeType i)
            {
                return data[range(i)];
            }

            /**
             * \brief Returns a \c const reference to the element at index \a i of the view (alias for operator()).
             * \param i The zero-based index within the view.
             * \return A \c const reference to the underlying element.
             */
            ConstReference operator[](SizeType i) const
            {
                return data[range(i)];
            }

            /**
             * \brief Returns the start index of the viewed range within the wrapped vector.
             * \return The start index of the range.
             */
            SizeType getStart() const
            {
                return range.getStart();
            }

            /**
             * \brief Returns the size of the view (number of elements covered by the range).
             * \return The number of elements in the view.
             */
            SizeType getSize() const
            {
                return range.getSize();
            }

            /**
             * \brief Tells whether the view is empty (zero-length range).
             * \return \c true if the range is empty, and \c false otherwise.
             */
            bool isEmpty() const
            {
                return range.isEmpty();
            }

            /**
             * \brief Returns a reference to the wrapped vector (via its stored closure).
             * \return A reference to the wrapped vector closure.
             */
            VectorClosureType& getData()
            {
                return data;
            }

            /**
             * \brief Returns a \c const reference to the wrapped vector (via its stored closure).
             * \return A \c const reference to the wrapped vector closure.
             */
            const VectorClosureType& getData() const
            {
                return data;
            }

            /**
             * \brief Copies the elements of \a r into this view (writing through to the wrapped vector).
             * \param r The source range view.
             * \return A reference to itself.
             */
            VectorRange& operator=(const VectorRange& r)
            {
                vectorAssignVector<ScalarAssignment>(*this, typename VectorTemporaryTraits<V>::Type(r));
                return *this;
            }

            /**
             * \brief Assigns the vector expression \a e to this view (writing through to the wrapped vector).
             * \tparam E The source vector expression type.
             * \param e The source vector expression.
             * \return A reference to itself.
             */
            template <typename E>
            VectorRange& operator=(const VectorExpression<E>& e)
            {
                vectorAssignVector<ScalarAssignment>(*this, typename VectorTemporaryTraits<V>::Type(e));
                return *this;
            }

            /**
             * \brief Adds the vector expression \a e componentwise to this view.
             * \tparam E The source vector expression type.
             * \param e The vector expression to add.
             * \return A reference to itself.
             */
            template <typename E>
            VectorRange& operator+=(const VectorExpression<E>& e)
            {
                vectorAssignVector<ScalarAssignment>(*this, typename VectorTemporaryTraits<V>::Type(*this + e));
                return *this;
            }

            /**
             * \brief Subtracts the vector expression \a e componentwise from this view.
             * \tparam E The source vector expression type.
             * \param e The vector expression to subtract.
             * \return A reference to itself.
             */
            template <typename E>
            VectorRange& operator-=(const VectorExpression<E>& e)
            {
                vectorAssignVector<ScalarAssignment>(*this, typename VectorTemporaryTraits<V>::Type(*this - e));
                return *this;
            }

            /**
             * \brief Multiplies every element of this view by the scalar \a t.
             * \tparam T The scalar type.
             * \param t The scalar multiplier.
             * \return A reference to itself.
             */
            template <typename T>
            typename std::enable_if<IsScalar<T>::value, VectorRange>::type& operator*=(const T& t)
            {
                vectorAssignScalar<ScalarMultiplicationAssignment>(*this, t);
                return *this;
            }

            /**
             * \brief Divides every element of this view by the scalar \a t.
             * \tparam T The scalar type.
             * \param t The scalar divisor.
             * \return A reference to itself.
             */
            template <typename T>
            typename std::enable_if<IsScalar<T>::value, VectorRange>::type& operator/=(const T& t)
            {
                vectorAssignScalar<ScalarDivisionAssignment>(*this, t);
                return *this;
            }

            /**
             * \brief Assigns the vector expression \a e to this view without intermediate temporary
             *        (use only when \a e does not alias the wrapped vector).
             * \tparam E The source vector expression type.
             * \param e The source vector expression.
             * \return A reference to itself.
             */
            template <typename E>
            VectorRange& assign(const VectorExpression<E>& e)
            {
                vectorAssignVector<ScalarAssignment>(*this, e);
                return *this;
            }

            /**
             * \brief Adds the vector expression \a e to this view without intermediate temporary.
             * \tparam E The source vector expression type.
             * \param e The source vector expression.
             * \return A reference to itself.
             */
            template <typename E>
            VectorRange& plusAssign(const VectorExpression<E>& e)
            {
                vectorAssignVector<ScalarAdditionAssignment>(*this, e);
                return *this;
            }

            /**
             * \brief Subtracts the vector expression \a e from this view without intermediate temporary.
             * \tparam E The source vector expression type.
             * \param e The source vector expression.
             * \return A reference to itself.
             */
            template <typename E>
            VectorRange& minusAssign(const VectorExpression<E>& e)
            {
                vectorAssignVector<ScalarSubtractionAssignment>(*this, e);
                return *this;
            }

            /**
             * \brief Swaps the elements of this view with those of \a r.
             * \param r The view to swap with.
             */
            void swap(VectorRange& r)
            {
                if (this != &r)
                    vectorSwap(*this, r);
            }

            /**
             * \brief ADL-enabled free-function form of swap().
             * \param r1 The first view.
             * \param r2 The second view.
             */
            friend void swap(VectorRange& r1, VectorRange& r2)
            {
                r1.swap(r2);
            }

          private:
            VectorClosureType data;
            RangeType         range;
        };

        /**
         * \brief Vector-expression proxy that views a strided slice of an underlying vector.
         * \tparam V The wrapped vector type.
         */
        template <typename V>
        class VectorSlice : public VectorExpression<VectorSlice<V> >
        {

            typedef VectorSlice<V> SelfType;

          public:
            /** \brief The wrapped vector type. */
            typedef V                                                        VectorType;
            /** \brief The size type used by the wrapped vector. */
            typedef typename V::SizeType                                     SizeType;
            /** \brief The signed difference type used by the wrapped vector. */
            typedef typename V::DifferenceType                               DifferenceType;
            /** \brief The element value type of the wrapped vector. */
            typedef typename V::ValueType                                    ValueType;
            /** \brief Constant reference type to an element. */
            typedef typename V::ConstReference                               ConstReference;
            /** \brief Mutable reference type (degrades to ConstReference when the wrapped vector is \c const). */
            typedef typename std::conditional<std::is_const<V>::value,
                                              typename V::ConstReference,
                                              typename V::Reference>::type   Reference;
            /** \brief Closure type used to store the wrapped vector internally (mutable or const flavor). */
            typedef typename std::conditional<std::is_const<V>::value,
                                              typename V::ConstClosureType,
                                              typename V::ClosureType>::type VectorClosureType;
            /** \brief Constant closure type used when this proxy appears inside another expression. */
            typedef const SelfType                                           ConstClosureType;
            /** \brief Closure type used when this proxy appears inside another expression. */
            typedef SelfType                                                 ClosureType;
            /** \brief The Math::Slice type defining the (start, stride, size) selection. */
            typedef Slice<SizeType, DifferenceType>                          SliceType;

            /**
             * \brief Constructs the proxy viewing the slice \a s of \a v.
             * \param v The wrapped vector.
             * \param s The slice (start, stride, size) selecting the viewed elements.
             */
            VectorSlice(VectorType& v, const SliceType& s):
                data(v), slice(s) {}

            /**
             * \brief Returns a mutable reference to the element at index \a i of the view.
             * \param i The zero-based index within the view.
             * \return A mutable reference to the underlying element <tt>v(slice(i))</tt>.
             */
            Reference operator()(SizeType i)
            {
                return data(slice(i));
            }

            /**
             * \brief Returns a \c const reference to the element at index \a i of the view.
             * \param i The zero-based index within the view.
             * \return A \c const reference to the underlying element <tt>v(slice(i))</tt>.
             */
            ConstReference operator()(SizeType i) const
            {
                return data(slice(i));
            }

            /**
             * \brief Returns a mutable reference to the element at index \a i of the view (alias for operator()).
             * \param i The zero-based index within the view.
             * \return A mutable reference to the underlying element.
             */
            Reference operator[](SizeType i)
            {
                return data[slice(i)];
            }

            /**
             * \brief Returns a \c const reference to the element at index \a i of the view (alias for operator()).
             * \param i The zero-based index within the view.
             * \return A \c const reference to the underlying element.
             */
            ConstReference operator[](SizeType i) const
            {
                return data[slice(i)];
            }

            /**
             * \brief Returns the start index of the slice within the wrapped vector.
             * \return The start index of the slice.
             */
            SizeType getStart() const
            {
                return slice.getStart();
            }

            /**
             * \brief Returns the stride of the slice (step between successive viewed elements).
             * \return The stride.
             */
            DifferenceType getStride() const
            {
                return slice.getStride();
            }

            /**
             * \brief Returns the size of the view (number of elements covered by the slice).
             * \return The number of elements in the view.
             */
            SizeType getSize() const
            {
                return slice.getSize();
            }

            /**
             * \brief Tells whether the view is empty (zero-length slice).
             * \return \c true if the slice is empty, and \c false otherwise.
             */
            bool isEmpty() const
            {
                return slice.isEmpty();
            }

            /**
             * \brief Returns a reference to the wrapped vector (via its stored closure).
             * \return A reference to the wrapped vector closure.
             */
            VectorClosureType& getData()
            {
                return data;
            }

            /**
             * \brief Returns a \c const reference to the wrapped vector (via its stored closure).
             * \return A \c const reference to the wrapped vector closure.
             */
            const VectorClosureType& getData() const
            {
                return data;
            }

            /**
             * \brief Copies the elements of \a s into this view (writing through to the wrapped vector).
             * \param s The source slice view.
             * \return A reference to itself.
             */
            VectorSlice& operator=(const VectorSlice& s)
            {
                vectorAssignVector<ScalarAssignment>(*this, typename VectorTemporaryTraits<V>::Type(s));
                return *this;
            }

            /**
             * \brief Assigns the vector expression \a e to this view (writing through to the wrapped vector).
             * \tparam E The source vector expression type.
             * \param e The source vector expression.
             * \return A reference to itself.
             */
            template <typename E>
            VectorSlice& operator=(const VectorExpression<E>& e)
            {
                vectorAssignVector<ScalarAssignment>(*this, typename VectorTemporaryTraits<V>::Type(e));
                return *this;
            }

            /**
             * \brief Adds the vector expression \a e componentwise to this view.
             * \tparam E The source vector expression type.
             * \param e The vector expression to add.
             * \return A reference to itself.
             */
            template <typename E>
            VectorSlice& operator+=(const VectorExpression<E>& e)
            {
                vectorAssignVector<ScalarAssignment>(*this, typename VectorTemporaryTraits<V>::Type(*this + e));
                return *this;
            }

            /**
             * \brief Subtracts the vector expression \a e componentwise from this view.
             * \tparam E The source vector expression type.
             * \param e The vector expression to subtract.
             * \return A reference to itself.
             */
            template <typename E>
            VectorSlice& operator-=(const VectorExpression<E>& e)
            {
                vectorAssignVector<ScalarAssignment>(*this, typename VectorTemporaryTraits<V>::Type(*this - e));
                return *this;
            }

            /**
             * \brief Multiplies every element of this view by the scalar \a t.
             * \tparam T The scalar type.
             * \param t The scalar multiplier.
             * \return A reference to itself.
             */
            template <typename T>
            typename std::enable_if<IsScalar<T>::value, VectorSlice>::type& operator*=(const T& t)
            {
                vectorAssignScalar<ScalarMultiplicationAssignment>(*this, t);
                return *this;
            }

            /**
             * \brief Divides every element of this view by the scalar \a t.
             * \tparam T The scalar type.
             * \param t The scalar divisor.
             * \return A reference to itself.
             */
            template <typename T>
            typename std::enable_if<IsScalar<T>::value, VectorSlice>::type& operator/=(const T& t)
            {
                vectorAssignScalar<ScalarDivisionAssignment>(*this, t);
                return *this;
            }

            /**
             * \brief Assigns the vector expression \a e to this view without intermediate temporary
             *        (use only when \a e does not alias the wrapped vector).
             * \tparam E The source vector expression type.
             * \param e The source vector expression.
             * \return A reference to itself.
             */
            template <typename E>
            VectorSlice& assign(const VectorExpression<E>& e)
            {
                vectorAssignVector<ScalarAssignment>(*this, e);
                return *this;
            }

            /**
             * \brief Adds the vector expression \a e to this view without intermediate temporary.
             * \tparam E The source vector expression type.
             * \param e The source vector expression.
             * \return A reference to itself.
             */
            template <typename E>
            VectorSlice& plusAssign(const VectorExpression<E>& e)
            {
                vectorAssignVector<ScalarAdditionAssignment>(*this, e);
                return *this;
            }

            /**
             * \brief Subtracts the vector expression \a e from this view without intermediate temporary.
             * \tparam E The source vector expression type.
             * \param e The source vector expression.
             * \return A reference to itself.
             */
            template <typename E>
            VectorSlice& minusAssign(const VectorExpression<E>& e)
            {
                vectorAssignVector<ScalarSubtractionAssignment>(*this, e);
                return *this;
            }

            /**
             * \brief Swaps the elements of this view with those of \a s.
             * \param s The view to swap with.
             */
            void swap(VectorSlice& s)
            {
                if (this != &s)
                    vectorSwap(*this, s);
            }

            /**
             * \brief ADL-enabled free-function form of swap().
             * \param s1 The first view.
             * \param s2 The second view.
             */
            friend void swap(VectorSlice& s1, VectorSlice& s2)
            {
                s1.swap(s2);
            }

          private:
            VectorClosureType data;
            SliceType         slice;
        };

        /**
         * \brief Math::VectorTemporaryTraits specialization inheriting the temporary type of the underlying vector for a Math::VectorRange view.
         * \tparam V The underlying vector type.
         */
        template <typename V>
        struct VectorTemporaryTraits<VectorRange<V> > : public VectorTemporaryTraits<V>
        {};

        /**
         * \brief Math::VectorTemporaryTraits specialization inheriting the temporary type of the underlying vector for a \c const Math::VectorRange view.
         * \tparam V The underlying vector type.
         */
        template <typename V>
        struct VectorTemporaryTraits<const VectorRange<V> > : public VectorTemporaryTraits<V>
        {};

        /**
         * \brief Math::VectorTemporaryTraits specialization inheriting the temporary type of the underlying vector for a Math::VectorSlice view.
         * \tparam V The underlying vector type.
         */
        template <typename V>
        struct VectorTemporaryTraits<VectorSlice<V> > : public VectorTemporaryTraits<V>
        {};

        /**
         * \brief Math::VectorTemporaryTraits specialization inheriting the temporary type of the underlying vector for a \c const Math::VectorSlice view.
         * \tparam V The underlying vector type.
         */
        template <typename V>
        struct VectorTemporaryTraits<const VectorSlice<V> > : public VectorTemporaryTraits<V>
        {};

        /**
         * \brief Creates a mutable Math::VectorRange view of the subrange \a r of the vector expression \a e.
         * \tparam E The vector expression type.
         * \param e The vector expression.
         * \param r The index range to view.
         * \return A mutable range view of \a e.
         */
        template <typename E>
        VectorRange<E>
        range(VectorExpression<E>& e, const typename VectorRange<E>::RangeType& r)
        {
            return VectorRange<E>(e(), r);
        }

        /**
         * \brief Creates a constant Math::VectorRange view of the subrange \a r of the vector expression \a e.
         * \tparam E The vector expression type.
         * \param e The vector expression.
         * \param r The index range to view.
         * \return A constant range view of \a e.
         */
        template <typename E>
        VectorRange<const E>
        range(const VectorExpression<E>& e, const typename VectorRange<const E>::RangeType& r)
        {
            return VectorRange<const E>(e(), r);
        }

        /**
         * \brief Creates a mutable Math::VectorRange view of the subrange [\a start, \a stop) of the vector expression \a e.
         * \tparam E The vector expression type.
         * \param e The vector expression.
         * \param start The (inclusive) start index of the range.
         * \param stop The (exclusive) end index of the range.
         * \return A mutable range view of \a e.
         */
        template <typename E>
        VectorRange<E>
        range(VectorExpression<E>&                         e,
              typename VectorRange<E>::RangeType::SizeType start,
              typename VectorRange<E>::RangeType::SizeType stop)
        {
            typedef typename VectorRange<E>::RangeType RangeType;

            return VectorRange<E>(e(), RangeType(start, stop));
        }

        /**
         * \brief Creates a constant Math::VectorRange view of the subrange [\a start, \a stop) of the vector expression \a e.
         * \tparam E The vector expression type.
         * \param e The vector expression.
         * \param start The (inclusive) start index of the range.
         * \param stop The (exclusive) end index of the range.
         * \return A constant range view of \a e.
         */
        template <typename E>
        VectorRange<const E>
        range(const VectorExpression<E>&                         e,
              typename VectorRange<const E>::RangeType::SizeType start,
              typename VectorRange<const E>::RangeType::SizeType stop)
        {
            typedef typename VectorRange<const E>::RangeType RangeType;

            return VectorRange<const E>(e(), RangeType(start, stop));
        }

        /**
         * \brief Creates a mutable Math::VectorSlice view of the slice \a s of the vector expression \a e.
         * \tparam E The vector expression type.
         * \param e The vector expression.
         * \param s The (start, stride, size) slice to view.
         * \return A mutable slice view of \a e.
         */
        template <typename E>
        VectorSlice<E>
        slice(VectorExpression<E>& e, const typename VectorSlice<E>::SliceType& s)
        {
            return VectorSlice<E>(e(), s);
        }

        /**
         * \brief Creates a constant Math::VectorSlice view of the slice \a s of the vector expression \a e.
         * \tparam E The vector expression type.
         * \param e The vector expression.
         * \param s The (start, stride, size) slice to view.
         * \return A constant slice view of \a e.
         */
        template <typename E>
        VectorSlice<const E>
        slice(const VectorExpression<E>& e, const typename VectorSlice<const E>::SliceType& s)
        {
            return VectorSlice<const E>(e(), s);
        }

        /**
         * \brief Creates a mutable Math::VectorSlice view of the slice (\a start, \a stride, \a size) of the vector expression \a e.
         * \tparam E The vector expression type.
         * \param e The vector expression.
         * \param start The (inclusive) start index of the slice.
         * \param stride The stride between successive slice elements.
         * \param size The number of elements of the slice.
         * \return A mutable slice view of \a e.
         */
        template <typename E>
        VectorSlice<E>
        slice(VectorExpression<E>&                               e,
              typename VectorSlice<E>::SliceType::SizeType       start,
              typename VectorSlice<E>::SliceType::DifferenceType stride,
              typename VectorSlice<E>::SliceType::SizeType       size)
        {
            typedef typename VectorSlice<E>::SliceType SliceType;

            return VectorSlice<E>(e(), SliceType(start, stride, size));
        }

        /**
         * \brief Creates a constant Math::VectorSlice view of the slice (\a start, \a stride, \a size) of the vector expression \a e.
         * \tparam E The vector expression type.
         * \param e The vector expression.
         * \param start The (inclusive) start index of the slice.
         * \param stride The stride between successive slice elements.
         * \param size The number of elements of the slice.
         * \return A constant slice view of \a e.
         */
        template <typename E>
        VectorSlice<const E>
        slice(const VectorExpression<E>&                               e,
              typename VectorSlice<const E>::SliceType::SizeType       start,
              typename VectorSlice<const E>::SliceType::DifferenceType stride,
              typename VectorSlice<const E>::SliceType::SizeType       size)
        {
            typedef typename VectorSlice<const E>::SliceType SliceType;

            return VectorSlice<const E>(e(), SliceType(start, stride, size));
        }
    } // namespace Math
} // namespace CDPL

#endif // CDPL_MATH_VECTORPROXY_HPP
