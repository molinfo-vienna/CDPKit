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
         * \brief Helper class template for retrieving the absolute value of scalar arithmetic types.
         * \tparam Signed Whether the scalar type is signed or not.
         */
        template <bool Signed>
        struct ScalarAbsImpl
        {

            /**
             * \brief Returns the absolute value of \a t.
             * \return The absolute value of \a t.
             */
            template <typename T>
            static T abs(const T& t)
            {
                return std::abs(t);
            }
        };

        /**
         * \brief Specialization of Math::ScalarAbsImpl for unsigned types.
         */
        template <>
        struct ScalarAbsImpl<false>
        {

            /**
             * \brief Returns the absolute value of \a t.
             * \return The absolute value of \a t.
             */
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

            /**
             * \brief The scalar value type.
             */
            typedef T               ValueType;

            /**
             * \brief The real-valued type (identical to ValueType for scalar traits).
             */
            typedef T               RealType;

            /**
             * \brief Constant-reference type to a value.
             */
            typedef const T&        ConstReference;

            /**
             * \brief Convenience alias for this traits instantiation.
             */
            typedef ScalarTraits<T> SelfType;

            /**
             * \brief Returns the real part of \a t (identical to \a t for non-complex scalars).
             * \param t The value.
             * \return The real part of \a t.
             */
            static RealType real(ConstReference t)
            {
                return t;
            }

            /**
             * \brief Returns the imaginary part (always zero for non-complex scalars).
             * \return The default-constructed RealType.
             */
            static RealType imag(ConstReference)
            {
                return RealType();
            }

            /**
             * \brief Returns the complex conjugate of \a t (identical to \a t for non-complex scalars).
             * \param t The value.
             * \return The conjugate of \a t.
             */
            static RealType conj(ConstReference t)
            {
                return t;
            }

            /**
             * \brief Returns the absolute value of \a t (\c std::abs for signed types, the identity for unsigned types).
             * \param t The value.
             * \return The absolute value of \a t.
             */
            static RealType abs(ConstReference t)
            {
                return ScalarAbsImpl<std::numeric_limits<ValueType>::is_signed>::abs(t);
            }

            /**
             * \brief Returns the square root of \a t.
             * \param t The value.
             * \return \f$ \sqrt{t} \f$ as a ValueType.
             */
            static ValueType sqrt(ConstReference t)
            {
                return ValueType(std::sqrt(t));
            }

            /**
             * \brief Returns the L1 norm of \a t (identical to the absolute value for scalar values).
             * \param t The value.
             * \return The L1 norm of \a t.
             */
            static RealType norm1(ConstReference t)
            {
                return SelfType::abs(t);
            }

            /**
             * \brief Returns the L2 (Euclidean) norm of \a t (identical to the absolute value for scalar values).
             * \param t The value.
             * \return The L2 norm of \a t.
             */
            static RealType norm2(ConstReference t)
            {
                return SelfType::abs(t);
            }

            /**
             * \brief Returns the L&infin; norm of \a t (identical to the absolute value for scalar values).
             * \param t The value.
             * \return The L&infin; norm of \a t.
             */
            static RealType normInf(ConstReference t)
            {
                return SelfType::abs(t);
            }
        };

        template <typename T>
        struct TypeTraits;

        /**
         * \brief Common operations and type aliases for complex arithmetic types.
         * \tparam T A \c std::complex specialization.
         */
        template <typename T>
        struct ComplexTraits
        {

            /**
             * \brief The complex value type (a \c std::complex specialization).
             */
            typedef T                      ValueType;

            /**
             * \brief The underlying real-valued type.
             */
            typedef typename T::value_type RealType;

            /**
             * \brief Constant-reference type to a value.
             */
            typedef const T&               ConstReference;

            /**
             * \brief Convenience alias for this traits instantiation.
             */
            typedef ComplexTraits<T>       SelfType;

            /**
             * \brief Returns the real part of the complex value \a t.
             * \param t The complex value.
             * \return The real part \f$ \mathrm{Re}(t) \f$.
             */
            static RealType real(ConstReference t)
            {
                return std::real(t);
            }

            /**
             * \brief Returns the imaginary part of the complex value \a t.
             * \param t The complex value.
             * \return The imaginary part \f$ \mathrm{Im}(t) \f$.
             */
            static RealType imag(ConstReference t)
            {
                return std::imag(t);
            }

            /**
             * \brief Returns the complex conjugate of \a t.
             * \param t The complex value.
             * \return The conjugate \f$ \overline{t} \f$.
             */
            static ValueType conj(ConstReference t)
            {
                return std::conj(t);
            }

            /**
             * \brief Returns the modulus (absolute value) of the complex value \a t.
             * \param t The complex value.
             * \return The modulus \f$ |t| \f$.
             */
            static RealType abs(ConstReference t)
            {
                return std::abs(t);
            }

            /**
             * \brief Returns the principal complex square root of \a t.
             * \param t The complex value.
             * \return \f$ \sqrt{t} \f$ as a complex value.
             */
            static ValueType sqrt(ConstReference t)
            {
                return std::sqrt(t);
            }

            /**
             * \brief Returns the L1 norm of the complex value \a t (\f$ |\mathrm{Re}(t)| + |\mathrm{Im}(t)| \f$).
             * \param t The complex value.
             * \return The L1 norm of \a t.
             */
            static RealType norm1(ConstReference t)
            {
                return TypeTraits<RealType>::abs(SelfType::real(t)) + TypeTraits<RealType>::abs(SelfType::imag(t));
            }

            /**
             * \brief Returns the L2 norm of the complex value \a t (identical to its modulus).
             * \param t The complex value.
             * \return The L2 norm of \a t.
             */
            static RealType norm2(ConstReference t)
            {
                return SelfType::abs(t);
            }

            /**
             * \brief Returns the L&infin; norm of the complex value \a t (\f$ \max(|\mathrm{Re}(t)|, |\mathrm{Im}(t)|) \f$).
             * \param t The complex value.
             * \return The L&infin; norm of \a t.
             */
            static RealType normInf(ConstReference t)
            {
                return std::max(TypeTraits<RealType>::abs(SelfType::real(t)),
                                TypeTraits<RealType>::abs(SelfType::imag(t)));
            }
        };

        /**
         * \brief Primary traits template for scalar arithmetic value types.
         * \tparam T The value type.
         */
        template <typename T>
        struct TypeTraits : public ScalarTraits<T>
        {};

        /**
         * \brief Math::TypeTraits specialization for complex arithmetic value types.
         * \tparam T The value type.
         */
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

            /**
             * \brief The concrete temporary vector type compatible with the vector expression \a V.
             */
            typedef typename V::VectorTemporaryType Type;
        };

        /**
         * \brief Selects a concrete temporary matrix type compatible with the matrix expression \a M.
         * \tparam M The matrix expression type.
         */
        template <typename M>
        struct MatrixTemporaryTraits
        {

            /**
             * \brief The concrete temporary matrix type compatible with the matrix expression \a M.
             */
            typedef typename M::MatrixTemporaryType Type;
        };

        /**
         * \brief Selects a concrete temporary quaternion type compatible with the quaternion expression \a Q.
         * \tparam Q The quaternion expression type.
         */
        template <typename Q>
        struct QuaternionTemporaryTraits
        {

            /**
             * \brief The concrete temporary quaternion type compatible with the quaternion expression \a Q.
             */
            typedef typename Q::QuaternionTemporaryType Type;
        };

        /**
         * \brief Selects a concrete temporary grid type compatible with the grid expression \a G.
         * \tparam G The grid expression type.
         */
        template <typename G>
        struct GridTemporaryTraits
        {

            /**
             * \brief The concrete temporary grid type compatible with the grid expression \a G.
             */
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
