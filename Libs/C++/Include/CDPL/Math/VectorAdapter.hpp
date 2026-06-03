/* 
 * VectorAdapter.hpp 
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
 * \brief Provides vector adapter classes.
 */

#ifndef CDPL_MATH_VECTORADAPTER_HPP
#define CDPL_MATH_VECTORADAPTER_HPP

#include <type_traits>

#include "CDPL/Math/Expression.hpp"
#include "CDPL/Math/QuaternionAssignment.hpp"
#include "CDPL/Math/VectorAssignment.hpp"
#include "CDPL/Math/TypeTraits.hpp"
#include "CDPL/Math/Functional.hpp"


namespace CDPL
{

    namespace Math
    {

        /**
         * \brief Vector expression that exposes a vector \a V as its homogeneous-coordinate extension by appending an implicit \c 1 at the end.
         * \tparam V The wrapped vector type.
         */
        template <typename V>
        class HomogenousCoordsAdapter : public VectorExpression<HomogenousCoordsAdapter<V> >
        {

            typedef HomogenousCoordsAdapter<V> SelfType;

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
            /** \brief Constant closure type used when this adapter appears inside another expression. */
            typedef const SelfType                                           ConstClosureType;
            /** \brief Closure type used when this adapter appears inside another expression. */
            typedef SelfType                                                 ClosureType;

            /**
             * \brief Constructs the adapter wrapping \a v.
             * \param v The vector to be viewed as its homogeneous-coordinate extension.
             */
            HomogenousCoordsAdapter(VectorType& v):
                data(v), extElem(1) {}

            /**
             * \brief Returns a mutable reference to the element at index \a i of the view.
             *
             * Index <tt>getSize() - 1</tt> returns the extension element (initialized to \e 1); all lower indices
             * return the corresponding element of the wrapped vector.
             *
             * \param i The zero-based index within the view.
             * \return A mutable reference to the element.
             */
            Reference operator()(SizeType i)
            {
                if (i == data.getSize())
                    return extElem;

                return data(i);
            }

            /**
             * \brief Returns a \c const reference to the element at index \a i of the view.
             * \param i The zero-based index within the view.
             * \return A \c const reference to the element.
             */
            ConstReference operator()(SizeType i) const
            {
                if (i == data.getSize())
                    return extElem;

                return data(i);
            }

            /**
             * \brief Returns a mutable reference to the element at index \a i of the view (alias for operator()).
             * \param i The zero-based index within the view.
             * \return A mutable reference to the element.
             */
            Reference operator[](SizeType i)
            {
                if (i == data.getSize())
                    return extElem;

                return data[i];
            }

            /**
             * \brief Returns a \c const reference to the element at index \a i of the view (alias for operator()).
             * \param i The zero-based index within the view.
             * \return A \c const reference to the element.
             */
            ConstReference operator[](SizeType i) const
            {
                if (i == data.getSize())
                    return extElem;

                return data[i];
            }

            /**
             * \brief Returns the dimensionality of the view (wrapped vector size + 1).
             * \return The view size.
             */
            SizeType getSize() const
            {
                return (data.getSize() + SizeType(1));
            }

            /**
             * \brief Tells whether the view is empty (always \c false; the view always has at least the extension element).
             * \return \c false.
             */
            bool isEmpty() const
            {
                return false;
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
             * \brief Copies the elements of \a va into this view (writing through to the wrapped vector and to the extension element).
             * \param va The source adapter.
             * \return A reference to itself.
             */
            HomogenousCoordsAdapter& operator=(const HomogenousCoordsAdapter& va)
            {
                vectorAssignVector<ScalarAssignment>(*this, typename VectorTemporaryTraits<V>::Type(va));
                return *this;
            }

            /**
             * \brief Assigns the vector expression \a e to this view (writing through to the wrapped vector).
             * \tparam E The source vector expression type.
             * \param e The source vector expression.
             * \return A reference to itself.
             */
            template <typename E>
            HomogenousCoordsAdapter& operator=(const VectorExpression<E>& e)
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
            HomogenousCoordsAdapter& operator+=(const VectorExpression<E>& e)
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
            HomogenousCoordsAdapter& operator-=(const VectorExpression<E>& e)
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
            typename std::enable_if<IsScalar<T>::value, HomogenousCoordsAdapter>::type& operator*=(const T& t)
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
            typename std::enable_if<IsScalar<T>::value, HomogenousCoordsAdapter>::type& operator/=(const T& t)
            {
                vectorAssignScalar<ScalarDivisionAssignment>(*this, t);
                return *this;
            }

            /**
             * \brief Assigns the vector expression \a e to this view without intermediate temporary.
             * \tparam E The source vector expression type.
             * \param e The source vector expression.
             * \return A reference to itself.
             */
            template <typename E>
            HomogenousCoordsAdapter& assign(const VectorExpression<E>& e)
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
            HomogenousCoordsAdapter& plusAssign(const VectorExpression<E>& e)
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
            HomogenousCoordsAdapter& minusAssign(const VectorExpression<E>& e)
            {
                vectorAssignVector<ScalarSubtractionAssignment>(*this, e);
                return *this;
            }

            /**
             * \brief Swaps the contents of this view with those of \a va.
             * \param va The view to swap with.
             */
            void swap(HomogenousCoordsAdapter& va)
            {
                if (this != &va)
                    vectorSwap(*this, va);
            }

            /**
             * \brief ADL-enabled free-function form of swap().
             * \param va1 The first adapter.
             * \param va2 The second adapter.
             */
            friend void swap(HomogenousCoordsAdapter& va1, HomogenousCoordsAdapter& va2)
            {
                va1.swap(va2);
            }

          private:
            VectorClosureType data;
            ValueType         extElem;
        };

        /**
         * \brief Quaternion expression that exposes a 4-element vector as a quaternion (component indices 0-3 map to C1-C4).
         * \tparam V The wrapped 4-element vector type.
         */
        template <typename V>
        class VectorQuaternionAdapter : public QuaternionExpression<VectorQuaternionAdapter<V> >
        {

            typedef VectorQuaternionAdapter<V> SelfType;

          public:
            /** \brief The wrapped 4-element vector type. */
            typedef V                                                        VectorType;
            /** \brief The element value type. */
            typedef typename V::ValueType                                    ValueType;
            /** \brief Constant reference type to a component. */
            typedef typename V::ConstReference                               ConstReference;
            /** \brief Mutable reference type (degrades to ConstReference when the wrapped vector is \c const). */
            typedef typename std::conditional<std::is_const<V>::value,
                                              typename V::ConstReference,
                                              typename V::Reference>::type   Reference;
            /** \brief Closure type used to store the wrapped vector internally. */
            typedef typename std::conditional<std::is_const<V>::value,
                                              typename V::ConstClosureType,
                                              typename V::ClosureType>::type VectorClosureType;
            /** \brief Constant closure type used when this adapter appears inside another expression. */
            typedef const SelfType                                           ConstClosureType;
            /** \brief Closure type used when this adapter appears inside another expression. */
            typedef SelfType                                                 ClosureType;

            /**
             * \brief Constructs the adapter wrapping the 4-element vector \a v.
             * \param v The 4-element vector to be viewed as a quaternion.
             */
            explicit VectorQuaternionAdapter(VectorType& v):
                data(v) {}

            /**
             * \brief Returns a mutable reference to component C1 (mapped to element 0 of the wrapped vector).
             * \return A mutable reference to C1.
             */
            Reference getC1()
            {
                return data(0);
            }

            /**
             * \brief Returns a mutable reference to component C2 (mapped to element 1 of the wrapped vector).
             * \return A mutable reference to C2.
             */
            Reference getC2()
            {
                return data(1);
            }

            /**
             * \brief Returns a mutable reference to component C3 (mapped to element 2 of the wrapped vector).
             * \return A mutable reference to C3.
             */
            Reference getC3()
            {
                return data(2);
            }

            /**
             * \brief Returns a mutable reference to component C4 (mapped to element 3 of the wrapped vector).
             * \return A mutable reference to C4.
             */
            Reference getC4()
            {
                return data(3);
            }

            /**
             * \brief Returns a \c const reference to component C1.
             * \return A \c const reference to C1.
             */
            ConstReference getC1() const
            {
                return data(0);
            }

            /**
             * \brief Returns a \c const reference to component C2.
             * \return A \c const reference to C2.
             */
            ConstReference getC2() const
            {
                return data(1);
            }

            /**
             * \brief Returns a \c const reference to component C3.
             * \return A \c const reference to C3.
             */
            ConstReference getC3() const
            {
                return data(2);
            }

            /**
             * \brief Returns a \c const reference to component C4.
             * \return A \c const reference to C4.
             */
            ConstReference getC4() const
            {
                return data(3);
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
             * \brief Copies the components of \a a into this view (writing through to the wrapped vector).
             * \param a The source adapter.
             * \return A reference to itself.
             */
            VectorQuaternionAdapter& operator=(const VectorQuaternionAdapter& a)
            {
                quaternionAssignQuaternion<ScalarAssignment>(*this, typename QuaternionTemporaryTraits<SelfType>::Type(a));
                return *this;
            }

            /**
             * \brief Assigns the quaternion expression \a e to this view (writing through to the wrapped vector).
             * \tparam E The source quaternion expression type.
             * \param e The source quaternion expression.
             * \return A reference to itself.
             */
            template <typename E>
            VectorQuaternionAdapter& operator=(const QuaternionExpression<E>& e)
            {
                quaternionAssignQuaternion<ScalarAssignment>(*this, typename QuaternionTemporaryTraits<SelfType>::Type(e));
                return *this;
            }

            /**
             * \brief Assigns the scalar \a t to this view (sets C1 to \a t and the remaining components to the default value).
             * \tparam T The scalar type.
             * \param t The scalar to assign.
             * \return A reference to itself.
             */
            template <typename T>
            typename std::enable_if<IsScalar<T>::value, VectorQuaternionAdapter>::type&
            operator=(const T& t)
            {
                data(0) = t;
                data(1) = ValueType();
                data(2) = ValueType();
                data(3) = ValueType();
                return *this;
            }

            /**
             * \brief Adds the quaternion expression \a e componentwise to this view.
             * \tparam E The source quaternion expression type.
             * \param e The quaternion expression to add.
             * \return A reference to itself.
             */
            template <typename E>
            VectorQuaternionAdapter& operator+=(const QuaternionExpression<E>& e)
            {
                quaternionAssignQuaternion<ScalarAssignment>(*this, typename QuaternionTemporaryTraits<SelfType>::Type(*this + e));
                return *this;
            }

            /**
             * \brief Adds the scalar \a t to component C1 of this view.
             * \tparam T The scalar type.
             * \param t The scalar summand.
             * \return A reference to itself.
             */
            template <typename T>
            typename std::enable_if<IsScalar<T>::value, VectorQuaternionAdapter>::type&
            operator+=(const T& t)
            {
                data(0) += t;
                return *this;
            }

            /**
             * \brief Subtracts the quaternion expression \a e componentwise from this view.
             * \tparam E The source quaternion expression type.
             * \param e The quaternion expression to subtract.
             * \return A reference to itself.
             */
            template <typename E>
            VectorQuaternionAdapter& operator-=(const QuaternionExpression<E>& e)
            {
                quaternionAssignQuaternion<ScalarAssignment>(*this, typename QuaternionTemporaryTraits<SelfType>::Type(*this - e));
                return *this;
            }

            /**
             * \brief Subtracts the scalar \a t from component C1 of this view.
             * \tparam T The scalar type.
             * \param t The scalar subtrahend.
             * \return A reference to itself.
             */
            template <typename T>
            typename std::enable_if<IsScalar<T>::value, VectorQuaternionAdapter>::type&
            operator-=(const T& t)
            {
                data(0) -= t;
                return *this;
            }

            /**
             * \brief Multiplies this view by the quaternion expression \a e (Hamilton-product semantics).
             * \tparam E The source quaternion expression type.
             * \param e The quaternion expression to multiply by.
             * \return A reference to itself.
             */
            template <typename E>
            VectorQuaternionAdapter& operator*=(const QuaternionExpression<E>& e)
            {
                quaternionAssignQuaternion<ScalarAssignment>(*this, typename QuaternionTemporaryTraits<SelfType>::Type(*this * e));
                return *this;
            }

            /**
             * \brief Multiplies every component of this view by the scalar \a t.
             * \tparam T The scalar type.
             * \param t The scalar multiplier.
             * \return A reference to itself.
             */
            template <typename T>
            typename std::enable_if<IsScalar<T>::value, VectorQuaternionAdapter>::type&
            operator*=(const T& t)
            {
                quaternionAssignScalar<ScalarMultiplicationAssignment>(*this, t);
                return *this;
            }

            /**
             * \brief Divides this view by the quaternion expression \a e (Hamilton-quotient semantics).
             * \tparam E The source quaternion expression type.
             * \param e The quaternion expression to divide by.
             * \return A reference to itself.
             */
            template <typename E>
            VectorQuaternionAdapter& operator/=(const QuaternionExpression<E>& e)
            {
                quaternionAssignQuaternion<ScalarAssignment>(*this, typename QuaternionTemporaryTraits<SelfType>::Type(*this / e));
                return *this;
            }

            /**
             * \brief Divides every component of this view by the scalar \a t.
             * \tparam T The scalar type.
             * \param t The scalar divisor.
             * \return A reference to itself.
             */
            template <typename T>
            typename std::enable_if<IsScalar<T>::value, VectorQuaternionAdapter>::type&
            operator/=(const T& t)
            {
                quaternionAssignScalar<ScalarDivisionAssignment>(*this, t);
                return *this;
            }

            /**
             * \brief Assigns the quaternion expression \a e to this view without intermediate temporary
             *        (use only when \a e does not alias the wrapped vector).
             * \tparam E The source quaternion expression type.
             * \param e The source quaternion expression.
             * \return A reference to itself.
             */
            template <typename E>
            VectorQuaternionAdapter& assign(const QuaternionExpression<E>& e)
            {
                quaternionAssignQuaternion<ScalarAssignment>(*this, e);
                return *this;
            }

            /**
             * \brief Adds the quaternion expression \a e to this view without intermediate temporary.
             * \tparam E The source quaternion expression type.
             * \param e The source quaternion expression.
             * \return A reference to itself.
             */
            template <typename E>
            VectorQuaternionAdapter& plusAssign(const QuaternionExpression<E>& e)
            {
                quaternionAssignQuaternion<ScalarAdditionAssignment>(*this, e);
                return *this;
            }

            /**
             * \brief Subtracts the quaternion expression \a e from this view without intermediate temporary.
             * \tparam E The source quaternion expression type.
             * \param e The source quaternion expression.
             * \return A reference to itself.
             */
            template <typename E>
            VectorQuaternionAdapter& minusAssign(const QuaternionExpression<E>& e)
            {
                quaternionAssignQuaternion<ScalarSubtractionAssignment>(*this, e);
                return *this;
            }

            /**
             * \brief Swaps the components of this view with those of \a a.
             * \param a The adapter to swap with.
             */
            void swap(VectorQuaternionAdapter& a)
            {
                if (this != &a)
                    quaternionSwap(*this, a);
            }

            /**
             * \brief ADL-enabled free-function form of swap().
             * \param a1 The first adapter.
             * \param a2 The second adapter.
             */
            friend void swap(VectorQuaternionAdapter& a1, VectorQuaternionAdapter& a2)
            {
                a1.swap(a2);
            }

            /**
             * \brief Assigns the four supplied component values to this view (writing through to the wrapped vector).
             * \param c1 The C1 component value.
             * \param c2 The C2 component value.
             * \param c3 The C3 component value.
             * \param c4 The C4 component value.
             */
            void set(const ValueType& c1 = ValueType(), const ValueType& c2 = ValueType(),
                     const ValueType& c3 = ValueType(), const ValueType& c4 = ValueType())
            {
                data(0) = c1;
                data(1) = c2;
                data(2) = c3;
                data(3) = c4;
            }

          private:
            VectorClosureType data;
        };

        template <typename T>
        class Quaternion;

        /**
         * \brief Math::QuaternionTemporaryTraits specialization selecting Math::Quaternion as the temporary type for a Math::VectorQuaternionAdapter view.
         * \tparam V The wrapped 4-element vector type.
         */
        template <typename V>
        struct QuaternionTemporaryTraits<VectorQuaternionAdapter<V> >
        {

            /** \brief The Math::Quaternion specialization used as the temporary quaternion type. */
            typedef Quaternion<typename V::ValueType> Type;
        };

        /**
         * \brief Math::QuaternionTemporaryTraits specialization selecting Math::Quaternion as the temporary type for a \c const Math::VectorQuaternionAdapter view.
         * \tparam V The wrapped 4-element vector type.
         */
        template <typename V>
        struct QuaternionTemporaryTraits<const VectorQuaternionAdapter<V> >
        {

            /** \brief The Math::Quaternion specialization used as the temporary quaternion type. */
            typedef Quaternion<typename V::ValueType> Type;
        };

        /**
         * \brief Math::VectorTemporaryTraits specialization inheriting the temporary type of the wrapped vector for a Math::HomogenousCoordsAdapter view.
         * \tparam V The wrapped vector type.
         */
        template <typename V>
        struct VectorTemporaryTraits<HomogenousCoordsAdapter<V> > : public VectorTemporaryTraits<V>
        {};

        /**
         * \brief Math::VectorTemporaryTraits specialization inheriting the temporary type of the wrapped vector for a \c const Math::HomogenousCoordsAdapter view.
         * \tparam V The wrapped vector type.
         */
        template <typename V>
        struct VectorTemporaryTraits<const HomogenousCoordsAdapter<V> > : public VectorTemporaryTraits<V>
        {};

        /**
         * \brief Creates a mutable Math::VectorQuaternionAdapter view of the 4-element vector expression \a e.
         * \tparam E The vector expression type.
         * \param e The vector expression to wrap.
         * \return A mutable quaternion view of \a e.
         */
        template <typename E>
        VectorQuaternionAdapter<E>
        quat(VectorExpression<E>& e)
        {
            return VectorQuaternionAdapter<E>(e());
        }

        /**
         * \brief Creates a constant Math::VectorQuaternionAdapter view of the 4-element vector expression \a e.
         * \tparam E The vector expression type.
         * \param e The vector expression to wrap.
         * \return A constant quaternion view of \a e.
         */
        template <typename E>
        VectorQuaternionAdapter<const E>
        quat(const VectorExpression<E>& e)
        {
            return VectorQuaternionAdapter<const E>(e());
        }

        /**
         * \brief Creates a mutable Math::HomogenousCoordsAdapter view of the vector expression \a e (extends \a e by an implicit \c 1).
         * \tparam E The vector expression type.
         * \param e The vector expression to wrap.
         * \return A mutable homogeneous-coordinates view of \a e.
         */
        template <typename E>
        HomogenousCoordsAdapter<E>
        homog(VectorExpression<E>& e)
        {
            return HomogenousCoordsAdapter<E>(e());
        }

        /**
         * \brief Creates a constant Math::HomogenousCoordsAdapter view of the vector expression \a e.
         * \tparam E The vector expression type.
         * \param e The vector expression to wrap.
         * \return A constant homogeneous-coordinates view of \a e.
         */
        template <typename E>
        HomogenousCoordsAdapter<const E>
        homog(const VectorExpression<E>& e)
        {
            return HomogenousCoordsAdapter<const E>(e());
        }
    } // namespace Math
} // namespace CDPL

#endif // CDPL_MATH_VECTORADAPTER_HPP
