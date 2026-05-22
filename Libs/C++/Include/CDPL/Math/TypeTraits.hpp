/* 
 * TypeTraits.hpp 
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
 * \brief Definition of type traits.
 */

#ifndef CDPL_MATH_TYPETRAITS_HPP
#define CDPL_MATH_TYPETRAITS_HPP

#include <cmath>
#include <complex>
#include <algorithm>
#include <limits>
#include <type_traits>


namespace CDPL
{

    namespace Math
    {

        /**
         * \brief Helper template selecting \c std::abs() for signed types and the identity for unsigned types.
         * \tparam Signed Whether the scalar type is signed.
         */
        template <bool Signed>
        struct ScalarAbsImpl
        {

            template <typename T>
            static T abs(const T& t)
            {
                return std::abs(t);
            }
        };

        template <>
        struct ScalarAbsImpl<false>
        {

            template <typename T>
            static const T& abs(const T& t)
            {
                return t;
            }
        };

        /**
         * \brief Common operations and type aliases for scalar arithmetic types.
         * \tparam T The scalar value type.
         */
        template <typename T>
        struct ScalarTraits
        {

            typedef T               ValueType;
            typedef T               RealType;
            typedef const T&        ConstReference;
            typedef ScalarTraits<T> SelfType;

            static RealType real(ConstReference t)
            {
                return t;
            }

            static RealType imag(ConstReference)
            {
                return RealType();
            }

            static RealType conj(ConstReference t)
            {
                return t;
            }

            static RealType abs(ConstReference t)
            {
                return ScalarAbsImpl<std::numeric_limits<ValueType>::is_signed>::abs(t);
            }

            static ValueType sqrt(ConstReference t)
            {
                return ValueType(std::sqrt(t));
            }

            static RealType norm1(ConstReference t)
            {
                return SelfType::abs(t);
            }

            static RealType norm2(ConstReference t)
            {
                return SelfType::abs(t);
            }

            static RealType normInf(ConstReference t)
            {
                return SelfType::abs(t);
            }
        };

        /**
         * \brief Primary type traits template selecting between Math::ScalarTraits and Math::ComplexTraits based on \a T.
         * \tparam T The value type.
         */
        template <typename T>
        struct TypeTraits;

        /**
         * \brief Common operations and type aliases for complex arithmetic types.
         * \tparam T A \c std::complex specialization.
         */
        template <typename T>
        struct ComplexTraits
        {

            typedef T                      ValueType;
            typedef typename T::value_type RealType;
            typedef const T&               ConstReference;
            typedef ComplexTraits<T>       SelfType;

            static RealType real(ConstReference t)
            {
                return std::real(t);
            }

            static RealType imag(ConstReference t)
            {
                return std::imag(t);
            }

            static ValueType conj(ConstReference t)
            {
                return std::conj(t);
            }

            static RealType abs(ConstReference t)
            {
                return std::abs(t);
            }

            static ValueType sqrt(ConstReference t)
            {
                return std::sqrt(t);
            }

            static RealType norm1(ConstReference t)
            {
                return TypeTraits<RealType>::abs(SelfType::real(t)) + TypeTraits<RealType>::abs(SelfType::imag(t));
            }

            static RealType norm2(ConstReference t)
            {
                return SelfType::abs(t);
            }

            static RealType normInf(ConstReference t)
            {
                return std::max(TypeTraits<RealType>::abs(SelfType::real(t)),
                                TypeTraits<RealType>::abs(SelfType::imag(t)));
            }
        };

        template <typename T>
        struct TypeTraits : public ScalarTraits<T>
        {};

        template <typename T>
        struct TypeTraits<std::complex<T> > : public ComplexTraits<std::complex<T> >
        {};

        /**
         * \brief Selects a concrete temporary vector type compatible with the vector expression \a V.
         * \tparam V The vector expression type.
         */
        template <typename V>
        struct VectorTemporaryTraits
        {

            typedef typename V::VectorTemporaryType Type;
        };

        /**
         * \brief Selects a concrete temporary matrix type compatible with the matrix expression \a M.
         * \tparam M The matrix expression type.
         */
        template <typename M>
        struct MatrixTemporaryTraits
        {

            typedef typename M::MatrixTemporaryType Type;
        };

        /**
         * \brief Selects a concrete temporary quaternion type compatible with the quaternion expression \a Q.
         * \tparam Q The quaternion expression type.
         */
        template <typename Q>
        struct QuaternionTemporaryTraits
        {

            typedef typename Q::QuaternionTemporaryType Type;
        };

        /**
         * \brief Selects a concrete temporary grid type compatible with the grid expression \a G.
         * \tparam G The grid expression type.
         */
        template <typename G>
        struct GridTemporaryTraits
        {

            typedef typename G::GridTemporaryType Type;
        };

        /**
         * \brief Type trait identifying \a T as a scalar arithmetic type (true for built-in arithmetic types).
         * \tparam T The type to test.
         */
        template <typename T>
        struct IsScalar : public std::is_arithmetic<T>
        {};

        /**
         * \brief Math::IsScalar specialization that treats \c std::complex<T> as scalar when \c T is arithmetic.
         * \tparam T The underlying real value type.
         */
        template <typename T>
        struct IsScalar<std::complex<T> > : public std::is_arithmetic<T>
        {};
    } // namespace Math
} // namespace CDPL

#endif // CDPL_MATH_TYPETRAITS_HPP
