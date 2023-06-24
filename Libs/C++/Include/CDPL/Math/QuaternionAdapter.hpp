/* 
 * QuaternionAdapter.hpp 
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
 * \brief Provides quaternion adapter classes.
 */

#ifndef CDPL_MATH_QUATERNIONADAPTER_HPP
#define CDPL_MATH_QUATERNIONADAPTER_HPP

#include <cstddef>
#include <type_traits>

#include "CDPL/Math/Expression.hpp"
#include "CDPL/Math/VectorAssignment.hpp"
#include "CDPL/Math/TypeTraits.hpp"
#include "CDPL/Math/Functional.hpp"
#include "CDPL/Base/Exceptions.hpp"


namespace CDPL
{

    namespace Math
    {

        template <typename Q>
        class QuaternionVectorAdapter : public VectorExpression<QuaternionVectorAdapter<Q> >
        {

            typedef QuaternionVectorAdapter<Q> SelfType;

          public:
            typedef Q                                                        QuaternionType;
            typedef typename std::size_t                                     SizeType;
            typedef typename std::ptrdiff_t                                  DifferenceType;
            typedef typename Q::ValueType                                    ValueType;
            typedef typename Q::ConstReference                               ConstReference;
            typedef typename std::conditional<std::is_const<Q>::value,
                                              typename Q::ConstReference,
                                              typename Q::Reference>::type   Reference;
            typedef typename std::conditional<std::is_const<Q>::value,
                                              typename Q::ConstClosureType,
                                              typename Q::ClosureType>::type QuaternionClosureType;
            typedef const SelfType                                           ConstClosureType;
            typedef SelfType                                                 ClosureType;

            explicit QuaternionVectorAdapter(QuaternionType& q):
                data(q) {}

            Reference operator()(SizeType i)
            {
                switch (i) {

                    case 0:
                        return data.getC1();

                    case 1:
                        return data.getC2();

                    case 2:
                        return data.getC3();

                    case 3:
                        return data.getC4();

                    default:
                        throw Base::IndexError("QuaternionVectorAdapter: Index out of range");
                }
            }

            ConstReference operator()(SizeType i) const
            {
                switch (i) {

                    case 0:
                        return data.getC1();

                    case 1:
                        return data.getC2();

                    case 2:
                        return data.getC3();

                    case 3:
                        return data.getC4();

                    default:
                        throw Base::IndexError("QuaternionVectorAdapter: Index out of range");
                }
            }

            Reference operator[](SizeType i)
            {
                return this->operator()(i);
            }

            ConstReference operator[](SizeType i) const
            {
                return this->operator()(i);
            }

            SizeType getSize() const
            {
                return 4;
            }

            bool isEmpty() const
            {
                return false;
            }

            QuaternionClosureType& getData()
            {
                return data;
            }

            const QuaternionClosureType& getData() const
            {
                return data;
            }

            QuaternionVectorAdapter& operator=(const QuaternionVectorAdapter& a)
            {
                vectorAssignVector<ScalarAssignment>(*this, typename VectorTemporaryTraits<SelfType>::Type(a));
                return *this;
            }

            template <typename E>
            QuaternionVectorAdapter& operator=(const VectorExpression<E>& e)
            {
                vectorAssignVector<ScalarAssignment>(*this, typename VectorTemporaryTraits<SelfType>::Type(e));
                return *this;
            }

            template <typename E>
            QuaternionVectorAdapter& operator+=(const VectorExpression<E>& e)
            {
                vectorAssignVector<ScalarAssignment>(*this, typename VectorTemporaryTraits<SelfType>::Type(*this + e));
                return *this;
            }

            template <typename E>
            QuaternionVectorAdapter& operator-=(const VectorExpression<E>& e)
            {
                vectorAssignVector<ScalarAssignment>(*this, typename VectorTemporaryTraits<SelfType>::Type(*this - e));
                return *this;
            }

            template <typename T>
            typename std::enable_if<IsScalar<T>::value, QuaternionVectorAdapter>::type& operator*=(const T& t)
            {
                vectorAssignScalar<ScalarMultiplicationAssignment>(*this, t);
                return *this;
            }

            template <typename T>
            typename std::enable_if<IsScalar<T>::value, QuaternionVectorAdapter>::type& operator/=(const T& t)
            {
                vectorAssignScalar<ScalarDivisionAssignment>(*this, t);
                return *this;
            }

            template <typename E>
            QuaternionVectorAdapter& assign(const VectorExpression<E>& e)
            {
                vectorAssignVector<ScalarAssignment>(*this, e);
                return *this;
            }

            template <typename E>
            QuaternionVectorAdapter& plusAssign(const VectorExpression<E>& e)
            {
                vectorAssignVector<ScalarAdditionAssignment>(*this, e);
                return *this;
            }

            template <typename E>
            QuaternionVectorAdapter& minusAssign(const VectorExpression<E>& e)
            {
                vectorAssignVector<ScalarSubtractionAssignment>(*this, e);
                return *this;
            }

            void swap(QuaternionVectorAdapter& a)
            {
                if (this != &a)
                    vectorSwap(*this, a);
            }

            friend void swap(QuaternionVectorAdapter& a1, QuaternionVectorAdapter& a2)
            {
                a1.swap(a2);
            }

          private:
            QuaternionClosureType data;
        };

        template <typename T, std::size_t N>
        class CVector;
        template <typename Q>
        struct VectorTemporaryTraits<QuaternionVectorAdapter<Q> >
        {

            typedef CVector<typename Q::ValueType, 4> Type;
        };

        template <typename Q>
        struct VectorTemporaryTraits<const QuaternionVectorAdapter<Q> >
        {

            typedef CVector<typename Q::ValueType, 4> Type;
        };

        template <typename E>
        QuaternionVectorAdapter<E>
        vec(QuaternionExpression<E>& e)
        {
            return QuaternionVectorAdapter<E>(e());
        }

        template <typename E>
        QuaternionVectorAdapter<const E>
        vec(const QuaternionExpression<E>& e)
        {
            return QuaternionVectorAdapter<const E>(e());
        }
    } // namespace Math
} // namespace CDPL

#endif // CDPL_MATH_QUATERNIONADAPTER_HPP
