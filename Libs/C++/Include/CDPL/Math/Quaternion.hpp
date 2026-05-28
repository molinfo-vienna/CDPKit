/* 
 * Quaternion.hpp 
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
 * \brief Definition of quaternion data types.
 */

#ifndef CDPL_MATH_QUATERNION_HPP
#define CDPL_MATH_QUATERNION_HPP

#include <algorithm>
#include <utility>
#include <type_traits>

#include "CDPL/Math/QuaternionExpression.hpp"
#include "CDPL/Math/QuaternionAssignment.hpp"
#include "CDPL/Math/Functional.hpp"
#include "CDPL/Math/TypeTraits.hpp"


namespace CDPL
{

    namespace Math
    {

        /**
         * \brief Lightweight quaternion expression that proxies a reference to an underlying quaternion container.
         * \tparam Q The wrapped quaternion type.
         */
        template <typename Q>
        class QuaternionReference : public QuaternionExpression<QuaternionReference<Q> >
        {

            typedef QuaternionReference<Q> SelfType;

          public:
            typedef Q                                                      QuaternionType;
            typedef typename Q::ValueType                                  ValueType;
            typedef typename std::conditional<std::is_const<Q>::value,
                                              typename Q::ConstReference,
                                              typename Q::Reference>::type Reference;
            typedef typename Q::ConstReference                             ConstReference;
            typedef SelfType                                               ClosureType;
            typedef const SelfType                                         ConstClosureType;

            explicit QuaternionReference(QuaternionType& q):
                data(q) {}

            Reference getC1()
            {
                return data.getC1();
            }

            Reference getC2()
            {
                return data.getC2();
            }

            Reference getC3()
            {
                return data.getC3();
            }

            Reference getC4()
            {
                return data.getC4();
            }

            ConstReference getC1() const
            {
                return data.getC1();
            }

            ConstReference getC2() const
            {
                return data.getC2();
            }

            ConstReference getC3() const
            {
                return data.getC3();
            }

            ConstReference getC4() const
            {
                return data.getC4();
            }

            const QuaternionType& getData() const
            {
                return data;
            }

            QuaternionType& getData()
            {
                return data;
            }

            QuaternionReference& operator=(const QuaternionReference& r)
            {
                data.operator=(r.data);
                return *this;
            }

            template <typename E>
            QuaternionReference& operator=(const QuaternionExpression<E>& e)
            {
                data.operator=(e);
                return *this;
            }

            template <typename T>
            typename std::enable_if<IsScalar<T>::value, QuaternionReference>::type&
            operator=(const T& t)
            {
                data.operator=(t);
                return *this;
            }

            template <typename E>
            QuaternionReference& operator+=(const QuaternionExpression<E>& e)
            {
                data.operator+=(e);
                return *this;
            }

            template <typename T>
            typename std::enable_if<IsScalar<T>::value, QuaternionReference>::type&
            operator+=(const T& t)
            {
                data.operator+=(t);
                return *this;
            }

            template <typename E>
            QuaternionReference& operator-=(const QuaternionExpression<E>& e)
            {
                data.operator-=(e);
                return *this;
            }

            template <typename T>
            typename std::enable_if<IsScalar<T>::value, QuaternionReference>::type&
            operator-=(const T& t)
            {
                data.operator-=(t);
                return *this;
            }

            template <typename E>
            QuaternionReference& operator*=(const QuaternionExpression<E>& e)
            {
                data.operator*=(e);
                return *this;
            }

            template <typename T>
            typename std::enable_if<IsScalar<T>::value, QuaternionReference>::type&
            operator*=(const T& t)
            {
                data.operator*=(t);
                return *this;
            }

            template <typename E>
            QuaternionReference& operator/=(const QuaternionExpression<E>& e)
            {
                data.operator/=(e);
                return *this;
            }

            template <typename T>
            typename std::enable_if<IsScalar<T>::value, QuaternionReference>::type&
            operator/=(const T& t)
            {
                data.operator/=(t);
                return *this;
            }

            template <typename E>
            QuaternionReference& assign(const QuaternionExpression<E>& e)
            {
                data.assign(e);
                return *this;
            }

            template <typename E>
            QuaternionReference& plusAssign(const QuaternionExpression<E>& e)
            {
                data.plusAssign(e);
                return *this;
            }

            template <typename E>
            QuaternionReference& minusAssign(const QuaternionExpression<E>& e)
            {
                data.minusAssign(e);
                return *this;
            }

            void swap(QuaternionReference& r)
            {
                data.swap(r.data);
            }

            friend void swap(QuaternionReference& r1, QuaternionReference& r2)
            {
                r1.swap(r2);
            }

            void set(const ValueType& c1 = ValueType(), const ValueType& c2 = ValueType(),
                     const ValueType& c3 = ValueType(), const ValueType& c4 = ValueType())
            {
                data.set(c1, c2, c3, c4);
            }

          private:
            QuaternionType& data;
        };

        /**
         * \brief A general 4-component quaternion \f$ q = c_1 + c_2 i + c_3 j + c_4 k \f$.
         * \tparam T The scalar component value type.
         */
        template <typename T>
        class Quaternion : public QuaternionContainer<Quaternion<T> >
        {

            typedef Quaternion<T> SelfType;

          public:
            /** \brief The scalar component value type. */
            typedef T                                         ValueType;
            /** \brief Mutable reference type to a component. */
            typedef T&                                        Reference;
            /** \brief Constant reference type to a component. */
            typedef const T&                                  ConstReference;
            /** \brief The plain C-array type used for in-memory storage of the four components. */
            typedef ValueType                                 ArrayType[4];
            /** \brief Pointer type for raw access to the component array. */
            typedef T*                                        Pointer;
            /** \brief Constant pointer type for raw access to the component array. */
            typedef const T*                                  ConstPointer;
            /** \brief Closure type used when this quaternion appears inside another expression. */
            typedef QuaternionReference<SelfType>             ClosureType;
            /** \brief Constant closure type used when this quaternion appears inside another expression. */
            typedef const QuaternionReference<const SelfType> ConstClosureType;
            /** \brief Concrete temporary quaternion type used by expression-template machinery. */
            typedef SelfType                                  QuaternionTemporaryType;

            /**
             * \brief Constructs an uninitialized quaternion.
             */
            Quaternion() {}

            /**
             * \brief Constructs the quaternion with the supplied component values (omitted components default to the value-initialized ValueType).
             * \param c1 The real component.
             * \param c2 The first imaginary component.
             * \param c3 The second imaginary component.
             * \param c4 The third imaginary component.
             */
            explicit Quaternion(const ValueType& c1, const ValueType& c2 = ValueType(),
                                const ValueType& c3 = ValueType(), const ValueType& c4 = ValueType())
            {
                data[0] = c1;
                data[1] = c2;
                data[2] = c3;
                data[3] = c4;
            }

            /**
             * \brief Constructs a copy of the quaternion \a q.
             * \param q The quaternion to copy.
             */
            Quaternion(const Quaternion& q)
            {
                std::copy(q.data, q.data + 4, data);
            }

            /**
             * \brief Constructs the quaternion from the quaternion expression \a e.
             * \tparam E The quaternion expression type.
             * \param e The quaternion expression to materialize.
             */
            template <typename E>
            Quaternion(const QuaternionExpression<E>& e)
            {
                quaternionAssignQuaternion<ScalarAssignment>(*this, e);
            }

            /**
             * \brief Returns a pointer to the contiguous 4-element component array.
             * \return A mutable pointer to the component array.
             */
            Pointer getData()
            {
                return data;
            }

            /**
             * \brief Returns a \c const pointer to the contiguous 4-element component array.
             * \return A \c const pointer to the component array.
             */
            ConstPointer getData() const
            {
                return data;
            }

            /**
             * \brief Returns a mutable reference to the real component \e C1.
             * \return A mutable reference to \e C1.
             */
            Reference getC1()
            {
                return data[0];
            }

            /**
             * \brief Returns a mutable reference to the imaginary component \e C2.
             * \return A mutable reference to \e C2.
             */
            Reference getC2()
            {
                return data[1];
            }

            /**
             * \brief Returns a mutable reference to the imaginary component \e C3.
             * \return A mutable reference to \e C3.
             */
            Reference getC3()
            {
                return data[2];
            }

            /**
             * \brief Returns a mutable reference to the imaginary component \e C4.
             * \return A mutable reference to \e C4.
             */
            Reference getC4()
            {
                return data[3];
            }

            /**
             * \brief Returns a \c const reference to the real component \e C1.
             * \return A \c const reference to \e C1.
             */
            ConstReference getC1() const
            {
                return data[0];
            }

            /**
             * \brief Returns a \c const reference to the imaginary component \e C2.
             * \return A \c const reference to \e C2.
             */
            ConstReference getC2() const
            {
                return data[1];
            }

            /**
             * \brief Returns a \c const reference to the imaginary component \e C3.
             * \return A \c const reference to \e C3.
             */
            ConstReference getC3() const
            {
                return data[2];
            }

            /**
             * \brief Returns a \c const reference to the imaginary component \e C4.
             * \return A \c const reference to \e C4.
             */
            ConstReference getC4() const
            {
                return data[3];
            }

            /**
             * \brief Sets the four quaternion components to the supplied values (omitted arguments default to the value-initialized ValueType).
             * \param c1 The new real component.
             * \param c2 The new first imaginary component.
             * \param c3 The new second imaginary component.
             * \param c4 The new third imaginary component.
             */
            void set(const ValueType& c1 = ValueType(), const ValueType& c2 = ValueType(),
                     const ValueType& c3 = ValueType(), const ValueType& c4 = ValueType())
            {
                data[0] = c1;
                data[1] = c2;
                data[2] = c3;
                data[3] = c4;
            }

            Quaternion& operator=(const Quaternion& q)
            {
                if (this != &q)
                    std::copy(q.data, q.data + 4, data);

                return *this;
            }

            template <typename C>
            Quaternion& operator=(const QuaternionContainer<C>& c)
            {
                return assign(c);
            }

            template <typename E>
            Quaternion& operator=(const QuaternionExpression<E>& e)
            {
                Quaternion tmp(e);

                return this->operator=(tmp);
            }

            template <typename T1>
            typename std::enable_if<IsScalar<T1>::value, Quaternion>::type&
            operator=(const T1& t)
            {
                data[0] = t;
                data[1] = ValueType();
                data[2] = ValueType();
                data[3] = ValueType();

                return *this;
            }

            template <typename T1>
            typename std::enable_if<IsScalar<T1>::value, Quaternion>::type&
            operator+=(const T1& t)
            {
                data[0] += t;
                return *this;
            }

            template <typename C>
            Quaternion& operator+=(const QuaternionContainer<C>& c)
            {
                return plusAssign(c);
            }

            template <typename E>
            Quaternion& operator+=(const QuaternionExpression<E>& e)
            {
                Quaternion tmp(*this + e);

                return this->operator=(tmp);
            }

            template <typename T1>
            typename std::enable_if<IsScalar<T1>::value, Quaternion>::type&
            operator-=(const T1& t)
            {
                data[0] -= t;
                return *this;
            }

            template <typename C>
            Quaternion& operator-=(const QuaternionContainer<C>& c)
            {
                return minusAssign(c);
            }

            template <typename E>
            Quaternion& operator-=(const QuaternionExpression<E>& e)
            {
                Quaternion tmp(*this - e);

                return this->operator=(tmp);
            }

            template <typename T1>
            typename std::enable_if<IsScalar<T1>::value, Quaternion>::type&
            operator*=(const T1& t)
            {
                quaternionAssignScalar<ScalarMultiplicationAssignment>(*this, t);
                return *this;
            }

            template <typename E>
            Quaternion& operator*=(const QuaternionExpression<E>& e)
            {
                Quaternion tmp(*this * e);

                return this->operator=(tmp);
            }

            template <typename T1>
            typename std::enable_if<IsScalar<T1>::value, Quaternion>::type&
            operator/=(const T1& t)
            {
                quaternionAssignScalar<ScalarDivisionAssignment>(*this, t);
                return *this;
            }

            template <typename E>
            Quaternion& operator/=(const QuaternionExpression<E>& e)
            {
                Quaternion tmp(*this / e);

                return this->operator=(tmp);
            }

            template <typename E>
            Quaternion& assign(const QuaternionExpression<E>& e)
            {
                quaternionAssignQuaternion<ScalarAssignment>(*this, e);
                return *this;
            }

            template <typename E>
            Quaternion& plusAssign(const QuaternionExpression<E>& e)
            {
                quaternionAssignQuaternion<ScalarAdditionAssignment>(*this, e);
                return *this;
            }

            template <typename E>
            Quaternion& minusAssign(const QuaternionExpression<E>& e)
            {
                quaternionAssignQuaternion<ScalarSubtractionAssignment>(*this, e);
                return *this;
            }

            void swap(Quaternion& q)
            {
                if (this != &q)
                    std::swap_ranges(data, data + 4, q.data);
            }

            friend void swap(Quaternion& q1, Quaternion& q2)
            {
                q1.swap(q2);
            }

          private:
            ArrayType data;
        };

        /**
         * \brief A pure-real quaternion \f$ q = c_1 + 0i + 0j + 0k \f$ that stores only the real component.
         * \tparam T The scalar component value type.
         */
        template <typename T>
        class RealQuaternion : public QuaternionContainer<RealQuaternion<T> >
        {

            typedef RealQuaternion<T> SelfType;

          public:
            /** \brief The scalar component value type. */
            typedef T                                         ValueType;
            /** \brief Reference type (always a \c const reference — only the real component is mutable, via assignment). */
            typedef const T&                                  Reference;
            /** \brief Constant reference type to the real component. */
            typedef const T&                                  ConstReference;
            /** \brief Closure type used when this quaternion appears inside another expression. */
            typedef QuaternionReference<SelfType>             ClosureType;
            /** \brief Constant closure type used when this quaternion appears inside another expression. */
            typedef const QuaternionReference<const SelfType> ConstClosureType;
            /** \brief Concrete temporary quaternion type used by expression-template machinery (a general Math::Quaternion<T>). */
            typedef Quaternion<T>                             QuaternionTemporaryType;

            /**
             * \brief Constructs a zero-valued real quaternion (\e C1 = 0).
             */
            RealQuaternion():
                value() {}

            /**
             * \brief Constructs the real quaternion with the supplied real component.
             * \param r The real component value.
             */
            RealQuaternion(const ValueType& r):
                value(r) {}

            /**
             * \brief Constructs a copy of the real quaternion \a q (possibly converting the component type).
             * \tparam T1 The source component type.
             * \param q The real quaternion to copy.
             */
            template <typename T1>
            RealQuaternion(const RealQuaternion<T1>& q):
                value(q.getC1())
            {}

            /**
             * \brief Returns a \c const reference to the real component \e C1.
             * \return A \c const reference to \e C1.
             */
            ConstReference getC1() const
            {
                return value;
            }

            /**
             * \brief Returns a \c const reference to the imaginary component \e C2 (always zero for a real quaternion).
             * \return A \c const reference to the zero element.
             */
            ConstReference getC2() const
            {
                return zero;
            }

            /**
             * \brief Returns a \c const reference to the imaginary component \e C3 (always zero for a real quaternion).
             * \return A \c const reference to the zero element.
             */
            ConstReference getC3() const
            {
                return zero;
            }

            /**
             * \brief Returns a \c const reference to the imaginary component \e C4 (always zero for a real quaternion).
             * \return A \c const reference to the zero element.
             */
            ConstReference getC4() const
            {
                return zero;
            }

            /**
             * \brief Implicit conversion to the underlying scalar value (the real component).
             * \return The real component \e C1 by value.
             */
            operator ValueType() const
            {
                return value;
            }

            RealQuaternion& operator=(const RealQuaternion& q)
            {
                value = q.value;
                return *this;
            }

            template <typename T1>
            RealQuaternion& operator=(const RealQuaternion<T1>& q)
            {
                value = q.getC1();
                return *this;
            }

            template <typename T1>
            typename std::enable_if<IsScalar<T1>::value, RealQuaternion>::type&
            operator=(const T1& t)
            {
                value = t;
                return *this;
            }

            template <typename T1>
            RealQuaternion& operator+=(const RealQuaternion<T1>& q)
            {
                value += q.getC1();
                return *this;
            }

            template <typename T1>
            typename std::enable_if<IsScalar<T1>::value, RealQuaternion>::type&
            operator+=(const T1& t)
            {
                value += t;
                return *this;
            }

            template <typename T1>
            RealQuaternion& operator-=(const RealQuaternion<T1>& q)
            {
                value -= q.getC1();
                return *this;
            }

            template <typename T1>
            typename std::enable_if<IsScalar<T1>::value, RealQuaternion>::type&
            operator-=(const T1& t)
            {
                value -= t;
                return *this;
            }

            template <typename T1>
            RealQuaternion& operator*=(const RealQuaternion<T1>& q)
            {
                value *= q.getC1();
                return *this;
            }

            template <typename T1>
            typename std::enable_if<IsScalar<T1>::value, RealQuaternion>::type&
            operator*=(const T1& t)
            {
                value *= t;
                return *this;
            }

            template <typename T1>
            RealQuaternion& operator/=(const RealQuaternion<T1>& q)
            {
                value /= q.getC1();
                return *this;
            }

            template <typename T1>
            typename std::enable_if<IsScalar<T1>::value, RealQuaternion>::type&
            operator/=(const T1& t)
            {
                value /= t;
                return *this;
            }

            template <typename T1>
            RealQuaternion& assign(const RealQuaternion<T1>& q)
            {
                value = q.getC1();
                return *this;
            }

            template <typename T1>
            RealQuaternion& plusAssign(const RealQuaternion<T1>& q)
            {
                value += q.getC1();
                return *this;
            }

            template <typename T1>
            RealQuaternion& minusAssign(const RealQuaternion<T1>& q)
            {
                value -= q.getC1();
                return *this;
            }

            void swap(RealQuaternion& q)
            {
                if (this != &q)
                    std::swap(value, q.value);
            }

            friend void swap(RealQuaternion& q1, RealQuaternion& q2)
            {
                q1.swap(q2);
            }

          private:
            ValueType              value;
            static const ValueType zero;
        };

        template <typename T>
        const typename RealQuaternion<T>::ValueType RealQuaternion<T>::zero = RealQuaternion<T>::ValueType();

        template <typename Q>
        struct QuaternionTemporaryTraits<const QuaternionReference<Q> > : public QuaternionTemporaryTraits<Q>
        {};

        template <typename Q>
        struct QuaternionTemporaryTraits<QuaternionReference<Q> > : public QuaternionTemporaryTraits<Q>
        {};

        template <typename T>
        typename std::enable_if<IsScalar<T>::value, RealQuaternion<T> >::type
        quat(const T& t)
        {
            return RealQuaternion<T>(t);
        }

        template <typename T1, typename T2>
        Quaternion<typename CommonType<T1, T2>::Type>
        quat(const T1& t1, const T2& t2)
        {
            typedef Quaternion<typename CommonType<T1, T2>::Type> QuaternionType;

            return QuaternionType(t1, t2);
        }

        template <typename T1, typename T2, typename T3>
        Quaternion<typename CommonType<typename CommonType<T1, T2>::Type, T3>::Type>
        quat(const T1& t1, const T2& t2, const T3& t3)
        {
            typedef Quaternion<typename CommonType<typename CommonType<T1, T2>::Type, T3>::Type> QuaternionType;

            return QuaternionType(t1, t2, t3);
        }

        template <typename T1, typename T2, typename T3, typename T4>
        Quaternion<typename CommonType<typename CommonType<typename CommonType<T1, T2>::Type, T3>::Type, T4>::Type>
        quat(const T1& t1, const T2& t2, const T3& t3, const T4& t4)
        {
            typedef Quaternion<typename CommonType<typename CommonType<typename CommonType<T1, T2>::Type, T3>::Type, T4>::Type> QuaternionType;

            return QuaternionType(t1, t2, t3, t4);
        }

        typedef Quaternion<float>         FQuaternion;
        typedef Quaternion<double>        DQuaternion;
        typedef Quaternion<long>          LQuaternion;
        typedef Quaternion<unsigned long> ULQuaternion;

        typedef RealQuaternion<float>         FRealQuaternion;
        typedef RealQuaternion<double>        DRealQuaternion;
        typedef RealQuaternion<long>          LRealQuaternion;
        typedef RealQuaternion<unsigned long> ULRealQuaternion;
    } // namespace Math
} // namespace CDPL

#endif // CDPL_MATH_QUATERNION_HPP
