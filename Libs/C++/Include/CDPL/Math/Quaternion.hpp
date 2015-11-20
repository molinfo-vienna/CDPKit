/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * Quaternion.hpp 
 *
 * Copyright (C) 2010-2011 Thomas A. Seidel <thomas.seidel@univie.ac.at>
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

#include <boost/mpl/if.hpp>
#include <boost/type_traits/is_const.hpp>
#include <boost/utility.hpp>
#include <boost/swap.hpp>

#include "CDPL/Math/Config.hpp"
#include "CDPL/Math/QuaternionExpression.hpp"
#include "CDPL/Math/QuaternionAssignment.hpp"
#include "CDPL/Math/Functional.hpp"
#include "CDPL/Math/TypeTraits.hpp"


namespace CDPL
{

	namespace Math
	{

		template <typename Q> 
		class QuaternionReference : public QuaternionExpression<QuaternionReference<Q> >
		{

			typedef QuaternionReference<Q> SelfType;

		public:
			typedef Q QuaternionType;
			typedef typename Q::ValueType ValueType;
			typedef typename boost::mpl::if_<boost::is_const<Q>,
											 typename Q::ConstReference,
											 typename Q::Reference>::type Reference;
			typedef typename Q::ConstReference ConstReference;
			typedef SelfType ClosureType;
			typedef const SelfType ConstClosureType;
			
			CDPL_MATH_INLINE explicit QuaternionReference(QuaternionType& q): data(q) {}

			CDPL_MATH_INLINE Reference getC1() {
				return data.getC1();
			}

			CDPL_MATH_INLINE Reference getC2() {
				return data.getC2();
			}

			CDPL_MATH_INLINE Reference getC3() {
				return data.getC3();
			}

			CDPL_MATH_INLINE Reference getC4() {
				return data.getC4();
			}

			CDPL_MATH_INLINE ConstReference getC1() const {
				return data.getC1();
			}

			CDPL_MATH_INLINE ConstReference getC2() const {
				return data.getC2();
			}

			CDPL_MATH_INLINE ConstReference getC3() const {
				return data.getC3();
			}

			CDPL_MATH_INLINE ConstReference getC4() const {
				return data.getC4();
			}
		
			CDPL_MATH_INLINE const QuaternionType& getData() const {
				return data;
			}

			CDPL_MATH_INLINE QuaternionType& getData() {
				return data;
			}

			CDPL_MATH_INLINE QuaternionReference& operator=(const QuaternionReference& r) {
				data.operator=(r.data);
				return *this;
			}

			template <typename E>
			CDPL_MATH_INLINE QuaternionReference& operator=(const QuaternionExpression<E>& e) {
				data.operator=(e);
				return *this;
			}

			template <typename T>
			CDPL_MATH_INLINE 
			typename boost::enable_if<IsScalar<T>, QuaternionReference>::type& 
			operator=(const T& t) {
				data.operator=(t);
				return *this;
			}

			template <typename E>
			CDPL_MATH_INLINE QuaternionReference& operator+=(const QuaternionExpression<E>& e) {
				data.operator+=(e);
				return *this;
			}	

			template <typename T>
			CDPL_MATH_INLINE 
			typename boost::enable_if<IsScalar<T>, QuaternionReference>::type& 
			operator+=(const T& t) {
				data.operator+=(t);
				return *this;
			}

			template <typename E>
			CDPL_MATH_INLINE QuaternionReference& operator-=(const QuaternionExpression<E>& e) {
				data.operator-=(e);
				return *this;
			}

			template <typename T>
			CDPL_MATH_INLINE 
			typename boost::enable_if<IsScalar<T>, QuaternionReference>::type& 
			operator-=(const T& t) {
				data.operator-=(t);
				return *this;
			}

			template <typename E>
			CDPL_MATH_INLINE QuaternionReference& operator*=(const QuaternionExpression<E>& e) {
				data.operator*=(e);
				return *this;
			}

			template <typename T>
			CDPL_MATH_INLINE 
			typename boost::enable_if<IsScalar<T>, QuaternionReference>::type& 
			operator*=(const T& t) {
				data.operator*=(t);
				return *this;
			}

			template <typename E>
			CDPL_MATH_INLINE QuaternionReference& operator/=(const QuaternionExpression<E>& e) {
				data.operator/=(e);
				return *this;
			}

			template <typename T>
			CDPL_MATH_INLINE 
			typename boost::enable_if<IsScalar<T>, QuaternionReference>::type& 
			operator/=(const T& t) {
				data.operator/=(t);
				return *this;
			}
			
			template <typename E>
			CDPL_MATH_INLINE QuaternionReference& assign(const QuaternionExpression<E>& e) {
				data.assign(e);
				return *this;
			}

			template <typename E>
			CDPL_MATH_INLINE QuaternionReference& plusAssign(const QuaternionExpression<E>& e) {
				data.plusAssign(e);
				return *this;
			}

			template <typename E>
			CDPL_MATH_INLINE QuaternionReference& minusAssign(const QuaternionExpression<E>& e) {
				data.minusAssign(e);
				return *this;
			}

			CDPL_MATH_INLINE void swap(QuaternionReference& r) {
				data.swap(r.data);
			}
	
			CDPL_MATH_INLINE friend void swap(QuaternionReference& r1, QuaternionReference& r2) {
				r1.swap(r2);
			}

			CDPL_MATH_INLINE void set(const ValueType& c1 = ValueType(), const ValueType& c2 = ValueType(), 
									 const ValueType& c3 = ValueType(), const ValueType& c4 = ValueType()) {
				data.set(c1, c2, c3, c4);
			}

		private:
			QuaternionType& data;
		};

		template <typename T> 
		class Quaternion : public QuaternionContainer<Quaternion<T> >
		{

			typedef Quaternion<T> SelfType;

		public:
			typedef T ValueType;
			typedef T& Reference;
			typedef const T& ConstReference;
			typedef ValueType ArrayType[4];
			typedef T* Pointer;
			typedef const T* ConstPointer;
			typedef QuaternionReference<SelfType> ClosureType;
			typedef const QuaternionReference<const SelfType> ConstClosureType;
			typedef SelfType QuaternionTemporaryType;

			CDPL_MATH_INLINE Quaternion() {}

			CDPL_MATH_INLINE explicit Quaternion(const ValueType& c1, const ValueType& c2 = ValueType(), 
												const ValueType& c3 = ValueType(), const ValueType& c4 = ValueType()) {
				data[0] = c1;
				data[1] = c2;
				data[2] = c3;
				data[3] = c4;
			}

			CDPL_MATH_INLINE Quaternion(const Quaternion& q) {
				std::copy(q.data, q.data + 4, data);
			}

			template <typename E>
			CDPL_MATH_INLINE Quaternion(const QuaternionExpression<E>& e) {
				quaternionAssignQuaternion<ScalarAssignment>(*this, e);
			}

			CDPL_MATH_INLINE Pointer getData() {
				return data;
			}
			
			CDPL_MATH_INLINE ConstPointer getData() const {
				return data;
			}

			CDPL_MATH_INLINE Reference getC1() {
				return data[0];
			}

			CDPL_MATH_INLINE Reference getC2() {
				return data[1];
			}

			CDPL_MATH_INLINE Reference getC3() {
				return data[2];
			}

			CDPL_MATH_INLINE Reference getC4() {
				return data[3];
			}

			CDPL_MATH_INLINE ConstReference getC1() const {
				return data[0];
			}

			CDPL_MATH_INLINE ConstReference getC2() const {
				return data[1];
			}

			CDPL_MATH_INLINE ConstReference getC3() const {
				return data[2];
			}

			CDPL_MATH_INLINE ConstReference getC4() const {
				return data[3];
			}
			
			CDPL_MATH_INLINE void set(const ValueType& c1 = ValueType(), const ValueType& c2 = ValueType(), 
									 const ValueType& c3 = ValueType(), const ValueType& c4 = ValueType()) {
				data[0] = c1;
				data[1] = c2;
				data[2] = c3;
				data[3] = c4;
			}

			CDPL_MATH_INLINE Quaternion& operator=(const Quaternion& q) {
				if (this != &q)
					std::copy(q.data, q.data + 4, data);

				return *this;
			}

			template <typename C>
			CDPL_MATH_INLINE Quaternion& operator=(const QuaternionContainer<C>& c) {
				return assign(c);
			}

			template <typename E>
			CDPL_MATH_INLINE Quaternion& operator=(const QuaternionExpression<E>& e) {
				Quaternion tmp(e);

				return this->operator=(tmp);
			}

			template <typename T1>
			CDPL_MATH_INLINE 
			typename boost::enable_if<IsScalar<T1>, Quaternion>::type& 
			operator=(const T1& t) {
				data[0] = t;
				data[1] = ValueType();
				data[2] = ValueType();
				data[3] = ValueType();

				return *this;
			}

			template <typename T1>
			CDPL_MATH_INLINE
			typename boost::enable_if<IsScalar<T1>, Quaternion>::type&
			operator+=(const T1& t) {
				data[0] += t;
				return *this;
			}

			template <typename C>
			CDPL_MATH_INLINE Quaternion& operator+=(const QuaternionContainer<C>& c) {
				return plusAssign(c);
			}

			template <typename E>
			CDPL_MATH_INLINE Quaternion& operator+=(const QuaternionExpression<E>& e) {
				Quaternion tmp(*this + e);

				return this->operator=(tmp);
			}	

			template <typename T1>
			CDPL_MATH_INLINE
			typename boost::enable_if<IsScalar<T1>, Quaternion>::type&
			operator-=(const T1& t) {
				data[0] -= t;
				return *this;
			}

			template <typename C>
			CDPL_MATH_INLINE Quaternion& operator-=(const QuaternionContainer<C>& c) {
				return minusAssign(c);
			}

			template <typename E>
			CDPL_MATH_INLINE Quaternion& operator-=(const QuaternionExpression<E>& e) {
				Quaternion tmp(*this - e);

				return this->operator=(tmp);
			}

			template <typename T1>
			CDPL_MATH_INLINE 
			typename boost::enable_if<IsScalar<T1>, Quaternion>::type&
			operator*=(const T1& t) {
				quaternionAssignScalar<ScalarMultiplicationAssignment>(*this, t);
				return *this;
			}

			template <typename E>
			CDPL_MATH_INLINE Quaternion& operator*=(const QuaternionExpression<E>& e) {
				Quaternion tmp(*this * e);

				return this->operator=(tmp);
			}	

			template <typename T1>
			CDPL_MATH_INLINE 
			typename boost::enable_if<IsScalar<T1>, Quaternion>::type&
			operator/=(const T1& t) {
				quaternionAssignScalar<ScalarDivisionAssignment>(*this, t);
				return *this;
			}
			
			template <typename E>
			CDPL_MATH_INLINE Quaternion& operator/=(const QuaternionExpression<E>& e) {
				Quaternion tmp(*this / e);

				return this->operator=(tmp);
			}	

			template <typename E>
			CDPL_MATH_INLINE Quaternion& assign(const QuaternionExpression<E>& e) {
				quaternionAssignQuaternion<ScalarAssignment>(*this, e);
				return *this;
			}

			template <typename E>
			CDPL_MATH_INLINE Quaternion& plusAssign(const QuaternionExpression<E>& e) {
				quaternionAssignQuaternion<ScalarAdditionAssignment>(*this, e);
				return *this;
			}

			template <typename E>
			CDPL_MATH_INLINE Quaternion& minusAssign(const QuaternionExpression<E>& e) {
				quaternionAssignQuaternion<ScalarSubtractionAssignment>(*this, e);
				return *this;
			}

			CDPL_MATH_INLINE void swap(Quaternion& q) {
				if (this != &q)
					std::swap_ranges(data, data + 4, q.data);
			}
	
			CDPL_MATH_INLINE friend void swap(Quaternion& q1, Quaternion& q2) {
				q1.swap(q2);
			}

		private:
			ArrayType data;
		};

		template <typename T> 
		class RealQuaternion : public QuaternionContainer<RealQuaternion<T> >
		{

			typedef RealQuaternion<T> SelfType;

		public:
			typedef T ValueType;
			typedef const T& Reference;
			typedef const T& ConstReference;
			typedef QuaternionReference<SelfType> ClosureType;
			typedef const QuaternionReference<const SelfType> ConstClosureType;
			typedef Quaternion<T> QuaternionTemporaryType;

			CDPL_MATH_INLINE RealQuaternion(): value() {}

			CDPL_MATH_INLINE RealQuaternion(const ValueType& r): value(r) {}

			template <typename T1>
			CDPL_MATH_INLINE RealQuaternion(const RealQuaternion<T1>& q): value(q.getC1()) {}

			CDPL_MATH_INLINE ConstReference getC1() const {
				return value;
			}

			CDPL_MATH_INLINE ConstReference getC2() const {
				return zero;
			}

			CDPL_MATH_INLINE ConstReference getC3() const {
				return zero;
			}

			CDPL_MATH_INLINE ConstReference getC4() const {
				return zero;
			}
			
			CDPL_MATH_INLINE operator ValueType() const {
				return value;
			}

			CDPL_MATH_INLINE RealQuaternion& operator=(const RealQuaternion& q) {
				value = q.value;
				return *this;
			}

			template <typename T1>
			CDPL_MATH_INLINE RealQuaternion& operator=(const RealQuaternion<T1>& q) {
				value = q.getC1();
				return *this;
			}

			template <typename T1>
			CDPL_MATH_INLINE 
			typename boost::enable_if<IsScalar<T1>, RealQuaternion>::type&
			operator=(const T1& t) {
				value = t;
				return *this;
			}

			template <typename T1>
			CDPL_MATH_INLINE RealQuaternion& operator+=(const RealQuaternion<T1>& q) {
				value += q.getC1();
				return *this;
			}

			template <typename T1>
			CDPL_MATH_INLINE
			typename boost::enable_if<IsScalar<T1>, RealQuaternion>::type&
			operator+=(const T1& t) {
				value += t;
				return *this;
			}

			template <typename T1>
			CDPL_MATH_INLINE RealQuaternion& operator-=(const RealQuaternion<T1>& q) {
				value -= q.getC1();
				return *this;
			}

			template <typename T1>
			CDPL_MATH_INLINE
			typename boost::enable_if<IsScalar<T1>, RealQuaternion>::type&
			operator-=(const T1& t) {
				value -= t;
				return *this;
			}

			template <typename T1>
			CDPL_MATH_INLINE RealQuaternion& operator*=(const RealQuaternion<T1>& q) {
				value *= q.getC1();
				return *this;
			}	

			template <typename T1>
			CDPL_MATH_INLINE 
			typename boost::enable_if<IsScalar<T1>, RealQuaternion>::type&
			operator*=(const T1& t) {
				value *= t;
				return *this;
			}

			template <typename T1>
			CDPL_MATH_INLINE RealQuaternion& operator/=(const RealQuaternion<T1>& q) {
				value /= q.getC1();
				return *this;
			}	

			template <typename T1>
			CDPL_MATH_INLINE 
			typename boost::enable_if<IsScalar<T1>, RealQuaternion>::type&
			operator/=(const T1& t) {
				value /= t;
				return *this;
			}
			
			template <typename T1>
			CDPL_MATH_INLINE RealQuaternion& assign(const RealQuaternion<T1>& q) {
				value = q.getC1();
				return *this;
			}

			template <typename T1>
			CDPL_MATH_INLINE RealQuaternion& plusAssign(const RealQuaternion<T1>& q) {
				value += q.getC1();
				return *this;
			}

			template <typename T1>
			CDPL_MATH_INLINE RealQuaternion& minusAssign(const RealQuaternion<T1>& q) {
				value -= q.getC1();
				return *this;
			}

			CDPL_MATH_INLINE void swap(RealQuaternion& q) {
				if (this != &q)
					boost::swap(value, q.value);
			}
	
			CDPL_MATH_INLINE friend void swap(RealQuaternion& q1, RealQuaternion& q2) {
				q1.swap(q2);
			}

		private:
			ValueType              value;
			static const ValueType zero;
		};

		template <typename T> const typename RealQuaternion<T>::ValueType RealQuaternion<T>::zero = RealQuaternion<T>::ValueType();

		template <typename Q>
		struct QuaternionTemporaryTraits<const QuaternionReference<Q> > : public QuaternionTemporaryTraits<Q> {};

		template <typename Q>
		struct QuaternionTemporaryTraits<QuaternionReference<Q> > : public QuaternionTemporaryTraits<Q> {};
	
		template <typename T>
		CDPL_MATH_INLINE
		typename boost::enable_if<IsScalar<T>, RealQuaternion<T> >::type 
		quat(const T& t)
		{
			return RealQuaternion<T>(t);
		}

		template <typename T1, typename T2>
		CDPL_MATH_INLINE
		Quaternion<typename CommonType<T1, T2>::Type> 
		quat(const T1& t1, const T2& t2)
		{
			typedef Quaternion<typename CommonType<T1, T2>::Type> QuaternionType;

			return QuaternionType(t1, t2);
		}
		
		template <typename T1, typename T2, typename T3>
		CDPL_MATH_INLINE 
		Quaternion<typename CommonType<typename CommonType<T1, T2>::Type, T3>::Type> 
		quat(const T1& t1, const T2& t2, const T3& t3)
		{
			typedef Quaternion<typename CommonType<typename CommonType<T1, T2>::Type, T3>::Type> QuaternionType;

			return QuaternionType(t1, t2, t3);
		}

		template <typename T1, typename T2, typename T3, typename T4>
		CDPL_MATH_INLINE 
		Quaternion<typename CommonType<typename CommonType<typename CommonType<T1, T2>::Type, T3>::Type, T4>::Type> 
		quat(const T1& t1, const T2& t2, const T3& t3, const T4& t4)
		{
			typedef Quaternion<typename CommonType<typename CommonType<typename CommonType<T1, T2>::Type, T3>::Type, T4>::Type> QuaternionType;

			return QuaternionType(t1, t2, t3, t4);
		}

		typedef Quaternion<float> FQuaternion;
		typedef Quaternion<double> DQuaternion;
		typedef Quaternion<long> LQuaternion;
		typedef Quaternion<unsigned long> ULQuaternion;

		typedef RealQuaternion<float> FRealQuaternion;
		typedef RealQuaternion<double> DRealQuaternion;
		typedef RealQuaternion<long> LRealQuaternion;
		typedef RealQuaternion<unsigned long> ULRealQuaternion;
	}
}

#endif // CDPL_MATH_QUATERNION_HPP
