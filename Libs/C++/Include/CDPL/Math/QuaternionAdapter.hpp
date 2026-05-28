/* 
 * QuaternionAdapter.hpp 
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

        /**
         * \brief View adapter that exposes a quaternion as a 4-element vector expression (indices map to the components C1, C2, C3, C4).
         * \tparam Q The wrapped quaternion type.
         */
        template <typename Q>
        class QuaternionVectorAdapter : public VectorExpression<QuaternionVectorAdapter<Q> >
        {

            typedef QuaternionVectorAdapter<Q> SelfType;

          public:
            /** \brief The wrapped quaternion type. */
            typedef Q                                                        QuaternionType;
            /** \brief The size type (\c std::size_t). */
            typedef typename std::size_t                                     SizeType;
            /** \brief The signed difference type (\c std::ptrdiff_t). */
            typedef typename std::ptrdiff_t                                  DifferenceType;
            /** \brief The element value type of the wrapped quaternion. */
            typedef typename Q::ValueType                                    ValueType;
            /** \brief Constant reference type to an element of the wrapped quaternion. */
            typedef typename Q::ConstReference                               ConstReference;
            /** \brief Mutable reference type (degrades to ConstReference when the wrapped quaternion is \c const). */
            typedef typename std::conditional<std::is_const<Q>::value,
                                              typename Q::ConstReference,
                                              typename Q::Reference>::type   Reference;
            /** \brief Closure type used to store the wrapped quaternion internally (mutable or const flavor). */
            typedef typename std::conditional<std::is_const<Q>::value,
                                              typename Q::ConstClosureType,
                                              typename Q::ClosureType>::type QuaternionClosureType;
            /** \brief Constant closure type used when this adapter appears inside another expression. */
            typedef const SelfType                                           ConstClosureType;
            /** \brief Closure type used when this adapter appears inside another expression. */
            typedef SelfType                                                 ClosureType;

            /**
             * \brief Constructs the adapter wrapping the quaternion \a q.
             * \param q The quaternion to be viewed as a 4-element vector.
             */
            explicit QuaternionVectorAdapter(QuaternionType& q):
                data(q) {}

            /**
             * \brief Returns a mutable reference to the quaternion component at index \a i.
             * \param i The zero-based component index (\e 0 = C1, \e 1 = C2, \e 2 = C3, \e 3 = C4).
             * \return A mutable reference to the component.
             * \throw Base::IndexError if \a i is not in the range [0, 3].
             */
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

            /**
             * \brief Returns a \c const reference to the quaternion component at index \a i.
             * \param i The zero-based component index (\e 0 = C1, \e 1 = C2, \e 2 = C3, \e 3 = C4).
             * \return A \c const reference to the component.
             * \throw Base::IndexError if \a i is not in the range [0, 3].
             */
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

            /**
             * \brief Returns a mutable reference to the quaternion component at index \a i (alias for operator()).
             * \param i The zero-based component index.
             * \return A mutable reference to the component.
             * \throw Base::IndexError if \a i is not in the range [0, 3].
             */
            Reference operator[](SizeType i)
            {
                return this->operator()(i);
            }

            /**
             * \brief Returns a \c const reference to the quaternion component at index \a i (alias for operator()).
             * \param i The zero-based component index.
             * \return A \c const reference to the component.
             * \throw Base::IndexError if \a i is not in the range [0, 3].
             */
            ConstReference operator[](SizeType i) const
            {
                return this->operator()(i);
            }

            /**
             * \brief Returns the dimensionality of the view (always \e 4).
             * \return The size value \e 4.
             */
            SizeType getSize() const
            {
                return 4;
            }

            /**
             * \brief Tells whether the view is empty (always \c false; the view is fixed-size with 4 components).
             * \return \c false.
             */
            bool isEmpty() const
            {
                return false;
            }

            /**
             * \brief Returns a reference to the wrapped quaternion (via its stored closure).
             * \return A reference to the wrapped quaternion closure.
             */
            QuaternionClosureType& getData()
            {
                return data;
            }

            /**
             * \brief Returns a \c const reference to the wrapped quaternion (via its stored closure).
             * \return A \c const reference to the wrapped quaternion closure.
             */
            const QuaternionClosureType& getData() const
            {
                return data;
            }

            /**
             * \brief Copies the components of \a a into this view (writing through to the wrapped quaternion).
             * \param a The source adapter.
             * \return A reference to itself.
             */
            QuaternionVectorAdapter& operator=(const QuaternionVectorAdapter& a)
            {
                vectorAssignVector<ScalarAssignment>(*this, typename VectorTemporaryTraits<SelfType>::Type(a));
                return *this;
            }

            /**
             * \brief Assigns the vector expression \a e to this view (writing through to the wrapped quaternion).
             * \tparam E The source vector expression type.
             * \param e The source vector expression.
             * \return A reference to itself.
             */
            template <typename E>
            QuaternionVectorAdapter& operator=(const VectorExpression<E>& e)
            {
                vectorAssignVector<ScalarAssignment>(*this, typename VectorTemporaryTraits<SelfType>::Type(e));
                return *this;
            }

            /**
             * \brief Adds the vector expression \a e componentwise to this view.
             * \tparam E The source vector expression type.
             * \param e The vector expression to add.
             * \return A reference to itself.
             */
            template <typename E>
            QuaternionVectorAdapter& operator+=(const VectorExpression<E>& e)
            {
                vectorAssignVector<ScalarAssignment>(*this, typename VectorTemporaryTraits<SelfType>::Type(*this + e));
                return *this;
            }

            /**
             * \brief Subtracts the vector expression \a e componentwise from this view.
             * \tparam E The source vector expression type.
             * \param e The vector expression to subtract.
             * \return A reference to itself.
             */
            template <typename E>
            QuaternionVectorAdapter& operator-=(const VectorExpression<E>& e)
            {
                vectorAssignVector<ScalarAssignment>(*this, typename VectorTemporaryTraits<SelfType>::Type(*this - e));
                return *this;
            }

            /**
             * \brief Multiplies every component of this view by the scalar \a t.
             * \tparam T The scalar type.
             * \param t The scalar multiplier.
             * \return A reference to itself.
             */
            template <typename T>
            typename std::enable_if<IsScalar<T>::value, QuaternionVectorAdapter>::type& operator*=(const T& t)
            {
                vectorAssignScalar<ScalarMultiplicationAssignment>(*this, t);
                return *this;
            }

            /**
             * \brief Divides every component of this view by the scalar \a t.
             * \tparam T The scalar type.
             * \param t The scalar divisor.
             * \return A reference to itself.
             */
            template <typename T>
            typename std::enable_if<IsScalar<T>::value, QuaternionVectorAdapter>::type& operator/=(const T& t)
            {
                vectorAssignScalar<ScalarDivisionAssignment>(*this, t);
                return *this;
            }

            /**
             * \brief Assigns the vector expression \a e to this view without intermediate temporary
             *        (use only when \a e does not alias the wrapped quaternion).
             * \tparam E The source vector expression type.
             * \param e The source vector expression.
             * \return A reference to itself.
             */
            template <typename E>
            QuaternionVectorAdapter& assign(const VectorExpression<E>& e)
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
            QuaternionVectorAdapter& plusAssign(const VectorExpression<E>& e)
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
            QuaternionVectorAdapter& minusAssign(const VectorExpression<E>& e)
            {
                vectorAssignVector<ScalarSubtractionAssignment>(*this, e);
                return *this;
            }

            /**
             * \brief Swaps the components of this view with those of \a a.
             * \param a The adapter to swap with.
             */
            void swap(QuaternionVectorAdapter& a)
            {
                if (this != &a)
                    vectorSwap(*this, a);
            }

            /**
             * \brief ADL-enabled free-function form of swap().
             * \param a1 The first adapter.
             * \param a2 The second adapter.
             */
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

        /**
         * \brief Creates a mutable Math::QuaternionVectorAdapter view of the quaternion expression \a e.
         * \tparam E The quaternion expression type.
         * \param e The quaternion expression to wrap.
         * \return A mutable 4-element vector view of \a e.
         */
        template <typename E>
        QuaternionVectorAdapter<E>
        vec(QuaternionExpression<E>& e)
        {
            return QuaternionVectorAdapter<E>(e());
        }

        /**
         * \brief Creates a constant Math::QuaternionVectorAdapter view of the quaternion expression \a e.
         * \tparam E The quaternion expression type.
         * \param e The quaternion expression to wrap.
         * \return A constant 4-element vector view of \a e.
         */
        template <typename E>
        QuaternionVectorAdapter<const E>
        vec(const QuaternionExpression<E>& e)
        {
            return QuaternionVectorAdapter<const E>(e());
        }
    } // namespace Math
} // namespace CDPL

#endif // CDPL_MATH_QUATERNIONADAPTER_HPP
