/* 
 * MinimizerVariableArrayTraits.hpp 
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
 * \brief Provides traits to flexibly handle different types of variable arrays in function
 *        optimization algorithms.
 */

#ifndef CDPL_MATH_MINIMIZERVARIABLEARRAYTRAITS_HPP
#define CDPL_MATH_MINIMIZERVARIABLEARRAYTRAITS_HPP

#include <vector>

#include "CDPL/Math/VectorArray.hpp"
#include "CDPL/Math/TypeTraits.hpp"


namespace CDPL
{

    namespace Math
    {

        /**
         * \brief Traits template that adapts arbitrary variable-array types to the linear-algebra operations
         *        required by minimizer implementations (\c dot, \c norm2, \c axpy, \c clear, \c assign, \c multiply, \c sub).
         *
         * The primary template assumes \a A behaves like a Math::Vector (provides \c getSize, \c clear, \c assign,
         * \c plusAssign/\c minusAssign, \c innerProd and arithmetic operators). Specializations adapt other
         * array-of-vector storage types.
         *
         * \tparam A The variable array type.
         */
        template <typename A>
        struct MinimizerVariableArrayTraits
        {

            /** \brief The variable-array type. */
            typedef A                     ArrayType;
            /** \brief The scalar value type stored by the array. */
            typedef typename A::ValueType ValueType;
            /** \brief The size type used by the array. */
            typedef typename A::SizeType  SizeType;

            /**
             * \brief Computes the inner product (dot product) of two variable arrays.
             * \tparam T The scalar result type.
             * \param a1 The first variable array.
             * \param a2 The second variable array.
             * \return The inner product as a value of type \a T.
             */
            template <typename T>
            static T dot(const ArrayType& a1, const ArrayType& a2)
            {
                return innerProd(a1, a2);
            }

            /**
             * \brief Computes the Euclidean (L2) norm of \a a using a numerically stable scaling algorithm.
             * \tparam T The scalar result type.
             * \param a The variable array.
             * \return The Euclidean norm as a value of type \a T.
             */
            template <typename T>
            static T norm2(const ArrayType& a)
            {
                T        scale = T();
                T        ssq   = T(1);
                SizeType size  = a.getSize();

                if (size == SizeType(0))
                    return T();

                else if (size == SizeType(1))
                    return TypeTraits<ValueType>::abs(a(0));

                for (SizeType i = 0; i < size; i++) {
                    const ValueType& x = a(i);

                    if (x != ValueType()) {
                        const typename TypeTraits<ValueType>::RealType ax = TypeTraits<ValueType>::abs(x);

                        if (scale < ax) {
                            ssq   = 1 + ssq * (scale / ax) * (scale / ax);
                            scale = ax;

                        } else {
                            ssq += (ax / scale) * (ax / scale);
                        }
                    }
                }

                return (scale * TypeTraits<T>::sqrt(ssq));
            }

            /**
             * \brief Performs the in-place BLAS-style \e axpy operation \f$ y \leftarrow y + \alpha\, x \f$.
             * \tparam T The scalar type of \a alpha.
             * \param alpha The scalar multiplier.
             * \param x The variable array \e x.
             * \param y The variable array \e y (updated in place).
             */
            template <typename T>
            static void axpy(const T& alpha, const ArrayType& x, ArrayType& y)
            {
                y.plusAssign(alpha * x);
            }

            /**
             * \brief Sets all elements of \a a to the default-constructed ValueType.
             * \param a The variable array to clear.
             */
            static void clear(ArrayType& a)
            {
                a.clear(ValueType());
            }

            /**
             * \brief Copies the contents of \a a2 into \a a1.
             * \param a1 The destination variable array.
             * \param a2 The source variable array.
             */
            static void assign(ArrayType& a1, const ArrayType& a2)
            {
                a1.assign(a2);
            }

            /**
             * \brief Multiplies every element of \a a by the scalar \a v.
             * \tparam T The scalar type of \a v.
             * \param a The variable array to scale (updated in place).
             * \param v The scalar multiplier.
             */
            template <typename T>
            static void multiply(ArrayType& a, const T& v)
            {
                a *= v;
            }

            /**
             * \brief Subtracts \a a2 from \a a1 element-wise (\f$ a_1 \leftarrow a_1 - a_2 \f$).
             * \param a1 The destination variable array (updated in place).
             * \param a2 The variable array to subtract.
             */
            static void sub(ArrayType& a1, const ArrayType& a2)
            {
                a1.minusAssign(a2);
            }
        };

        /**
         * \brief Math::MinimizerVariableArrayTraits specialization for Math::VectorArray storage (a sequence of fixed-size vectors).
         * \tparam V The inner vector type stored by the array.
         */
        template <typename V>
        struct MinimizerVariableArrayTraits<VectorArray<V> >
        {

            /** \brief The vector-array type. */
            typedef VectorArray<V>               ArrayType;
            /** \brief The vector type of the array elements. */
            typedef V                            VectorType;
            /** \brief The scalar value type stored in the array elements. */
            typedef typename V::ValueType        ValueType;
            /** \brief The size type used by the vector array. */
            typedef typename ArrayType::SizeType SizeType;

            /**
             * \brief Computes the inner product (dot product) of two vector arrays.
             * \tparam T The scalar result type.
             * \param a1 The first vector array.
             * \param a2 The second vector array.
             * \return The inner product as a value of type \a T.
             */
            template <typename T>
            static T dot(const ArrayType& a1, const ArrayType& a2)
            {
                T result = T();

                for (typename ArrayType::ConstElementIterator it1 = a1.getElementsBegin(), it2 = a2.getElementsBegin(), end1 = a1.getElementsEnd(); it1 != end1; ++it1, ++it2)
                    result += innerProd(*it1, *it2);

                return result;
            }

            /**
             * \brief Computes the Euclidean (L2) norm of \a a using a numerically stable scaling algorithm.
             * \tparam T The scalar result type.
             * \param a The vector array.
             * \return The Euclidean norm as a value of type \a T.
             */
            template <typename T>
            static T norm2(const ArrayType& a)
            {
                T scale = T();
                T ssq   = T(1);

                for (typename ArrayType::ConstElementIterator it = a.getElementsBegin(), end = a.getElementsEnd(); it != end; ++it) {
                    const typename VectorType::ConstPointer vx  = it->getData();
                    typename VectorType::SizeType           dim = it->getSize();

                    for (typename VectorType::SizeType i = 0; i < dim; i++) {
                        const ValueType& x = vx[i];

                        if (x != ValueType()) {
                            const typename TypeTraits<ValueType>::RealType ax = TypeTraits<ValueType>::abs(x);

                            if (scale < ax) {
                                ssq   = 1 + ssq * (scale / ax) * (scale / ax);
                                scale = ax;

                            } else {
                                ssq += (ax / scale) * (ax / scale);
                            }
                        }
                    }
                }

                return (scale * TypeTraits<T>::sqrt(ssq));
            }

            /**
             * \brief Performs the in-place BLAS-style \e axpy operation \f$ y \leftarrow y + \alpha\, x \f$.
             * \tparam T The scalar type of \a alpha.
             * \param alpha The scalar multiplier.
             * \param x The vector array \e x.
             * \param y The vector array \e y (updated in place).
             */
            template <typename T>
            static void axpy(const T& alpha, const ArrayType& x, ArrayType& y)
            {
                typename ArrayType::ElementIterator it2 = y.getElementsBegin();
                VectorType                          tmp;

                for (typename ArrayType::ConstElementIterator it1 = x.getElementsBegin(), end1 = x.getElementsEnd(); it1 != end1; ++it1, ++it2) {
                    tmp.assign(*it1);
                    tmp *= alpha;

                    it2->plusAssign(tmp);
                }
            }

            /**
             * \brief Sets all vector elements in \a a to the default-constructed ValueType.
             * \param a The vector array to clear.
             */
            static void clear(ArrayType& a)
            {
                for (typename ArrayType::ElementIterator it = a.getElementsBegin(), end = a.getElementsEnd(); it != end; ++it)
                    it->clear(ValueType());
            }

            /**
             * \brief Copies the contents of \a a2 into \a a1.
             * \param a1 The destination vector array.
             * \param a2 The source vector array.
             */
            static void assign(ArrayType& a1, const ArrayType& a2)
            {
                a1 = a2;
            }

            /**
             * \brief Multiplies every element of \a a by the scalar \a v.
             * \tparam T The scalar type of \a v.
             * \param a The vector array to scale (updated in place).
             * \param v The scalar multiplier.
             */
            template <typename T>
            static void multiply(ArrayType& a, const T& v)
            {
                for (typename ArrayType::ElementIterator it = a.getElementsBegin(), end = a.getElementsEnd(); it != end; ++it)
                    *it *= v;
            }

            /**
             * \brief Subtracts \a a2 from \a a1 element-wise (\f$ a_1 \leftarrow a_1 - a_2 \f$).
             * \param a1 The destination vector array (updated in place).
             * \param a2 The vector array to subtract.
             */
            static void sub(ArrayType& a1, const ArrayType& a2)
            {
                typename ArrayType::ConstElementIterator it2 = a2.getElementsBegin();

                for (typename ArrayType::ElementIterator it1 = a1.getElementsBegin(), end1 = a1.getElementsEnd(); it1 != end1; ++it1, ++it2)
                    it1->minusAssign(*it2);
            }
        };

        /**
         * \brief Math::MinimizerVariableArrayTraits specialization for \c std::vector storage of fixed-size vectors.
         * \tparam V The inner vector type stored in the \c std::vector.
         */
        template <typename V>
        struct MinimizerVariableArrayTraits<std::vector<V> >
        {

            /** \brief The vector-array type. */
            typedef std::vector<V>                ArrayType;
            /** \brief The vector type of the array elements. */
            typedef V                             VectorType;
            /** \brief The scalar value type stored in the array elements. */
            typedef typename V::ValueType         ValueType;
            /** \brief The size type used by the vector array. */
            typedef typename ArrayType::size_type SizeType;

            /**
             * \brief Computes the inner product (dot product) of two vector arrays.
             * \tparam T The scalar result type.
             * \param a1 The first vector array.
             * \param a2 The second vector array.
             * \return The inner product as a value of type \a T.
             */
            template <typename T>
            static T dot(const ArrayType& a1, const ArrayType& a2)
            {
                T result = T();

                for (typename ArrayType::const_iterator it1 = a1.begin(), it2 = a2.begin(), end1 = a1.end(); it1 != end1; ++it1, ++it2)
                    result += innerProd(*it1, *it2);

                return result;
            }

            /**
             * \brief Computes the Euclidean (L2) norm of \a a using a numerically stable scaling algorithm.
             * \tparam T The scalar result type.
             * \param a The vector array.
             * \return The Euclidean norm as a value of type \a T.
             */
            template <typename T>
            static T norm2(const ArrayType& a)
            {
                T scale = T();
                T ssq   = T(1);

                for (typename ArrayType::const_iterator it = a.begin(), end = a.end(); it != end; ++it) {
                    const typename VectorType::ConstPointer vx  = it->getData();
                    typename VectorType::SizeType           dim = it->getSize();

                    for (typename VectorType::SizeType i = 0; i < dim; i++) {
                        const ValueType& x = vx[i];

                        if (x != ValueType()) {
                            const typename TypeTraits<ValueType>::RealType ax = TypeTraits<ValueType>::abs(x);

                            if (scale < ax) {
                                ssq   = 1 + ssq * (scale / ax) * (scale / ax);
                                scale = ax;

                            } else {
                                ssq += (ax / scale) * (ax / scale);
                            }
                        }
                    }
                }

                return (scale * TypeTraits<T>::sqrt(ssq));
            }

           /**
             * \brief Performs the in-place BLAS-style \e axpy operation \f$ y \leftarrow y + \alpha\, x \f$.
             * \tparam T The scalar type of \a alpha.
             * \param alpha The scalar multiplier.
             * \param x The vector array \e x.
             * \param y The vector array \e y (updated in place).
             */
            template <typename T>
            static void axpy(const T& alpha, const ArrayType& x, ArrayType& y)
            {
                typename ArrayType::iterator it2 = y.begin();
                VectorType                   tmp;

                for (typename ArrayType::const_iterator it1 = x.begin(), end1 = x.end(); it1 != end1; ++it1, ++it2) {
                    tmp.assign(*it1);
                    tmp *= alpha;

                    it2->plusAssign(tmp);
                }
            }

            /**
             * \brief Sets all vector elements in \a a to the default-constructed ValueType.
             * \param a The vector array to clear.
             */
            static void clear(ArrayType& a)
            {
                for (typename ArrayType::iterator it = a.begin(), end = a.end(); it != end; ++it)
                    it->clear(ValueType());
            }

            /**
             * \brief Copies the contents of \a a2 into \a a1.
             * \param a1 The destination vector array.
             * \param a2 The source vector array.
             */
            static void assign(ArrayType& a1, const ArrayType& a2)
            {
                a1 = a2;
            }

            /**
             * \brief Multiplies every element of \a a by the scalar \a v.
             * \tparam T The scalar type of \a v.
             * \param a The vector array to scale (updated in place).
             * \param v The scalar multiplier.
             */
            template <typename T>
            static void multiply(ArrayType& a, const T& v)
            {
                for (typename ArrayType::iterator it = a.begin(), end = a.end(); it != end; ++it)
                    *it *= v;
            }

            /**
             * \brief Subtracts \a a2 from \a a1 element-wise (\f$ a_1 \leftarrow a_1 - a_2 \f$).
             * \param a1 The destination vector array (updated in place).
             * \param a2 The vector array to subtract.
             */
            static void sub(ArrayType& a1, const ArrayType& a2)
            {
                typename ArrayType::const_iterator it2 = a2.begin();

                for (typename ArrayType::iterator it1 = a1.begin(), end1 = a1.end(); it1 != end1; ++it1, ++it2)
                    it1->minusAssign(*it2);
            }
        };
        
    } // namespace Math
} // namespace CDPL

#endif // CDPL_MATH_MINIMIZERVARIABLEARRAYTRAITS_HPP
