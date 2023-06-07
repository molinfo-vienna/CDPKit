/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * VectorAdapter.hpp 
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

		template <typename V>
		class HomogenousCoordsAdapter : public VectorExpression<HomogenousCoordsAdapter<V> >
		{

			typedef HomogenousCoordsAdapter<V> SelfType;

		public:
			typedef V VectorType;
			typedef typename V::SizeType SizeType;
			typedef typename V::DifferenceType DifferenceType;
			typedef typename V::ValueType ValueType;
			typedef typename V::ConstReference ConstReference;
			typedef typename std::conditional<std::is_const<V>::value,
											 typename V::ConstReference,
											 typename V::Reference>::type Reference;
			typedef typename std::conditional<std::is_const<V>::value,
											 typename V::ConstClosureType,
											 typename V::ClosureType>::type VectorClosureType;
			typedef const SelfType ConstClosureType;
			typedef SelfType ClosureType;
			
			HomogenousCoordsAdapter(VectorType& v): data(v), extElem(1) {}

			Reference operator()(SizeType i) {
				if (i == data.getSize())
					return extElem;

				return data(i);
			}

			ConstReference operator()(SizeType i) const {
				if (i == data.getSize())
					return extElem;

				return data(i);
			}
	
			Reference operator[](SizeType i) {
				if (i == data.getSize())
					return extElem;

				return data[i];
			}

			ConstReference operator[](SizeType i) const {
				if (i == data.getSize())
					return extElem;

				return data[i];
			}

			SizeType getSize() const {
				return (data.getSize() + SizeType(1));
			}

			bool isEmpty() const {
				return false;
			}

			VectorClosureType& getData() {
				return data;
			}

			const VectorClosureType& getData() const {
				return data;
			}

			HomogenousCoordsAdapter& operator=(const HomogenousCoordsAdapter& va) {
				vectorAssignVector<ScalarAssignment>(*this, typename VectorTemporaryTraits<V>::Type(va));
				return *this;
			}

			template <typename E>
			HomogenousCoordsAdapter& operator=(const VectorExpression<E>& e) {
				vectorAssignVector<ScalarAssignment>(*this, typename VectorTemporaryTraits<V>::Type(e));
				return *this;
			}

			template <typename E>
			HomogenousCoordsAdapter& operator+=(const VectorExpression<E>& e) {
				vectorAssignVector<ScalarAssignment>(*this, typename VectorTemporaryTraits<V>::Type(*this + e));
				return *this;
			}	

			template <typename E>
			HomogenousCoordsAdapter& operator-=(const VectorExpression<E>& e) {
				vectorAssignVector<ScalarAssignment>(*this, typename VectorTemporaryTraits<V>::Type(*this - e));
				return *this;
			}

			template <typename T>
			typename std::enable_if<IsScalar<T>::value, HomogenousCoordsAdapter>::type& operator*=(const T& t) {
				vectorAssignScalar<ScalarMultiplicationAssignment>(*this, t);
				return *this;
			}
	
			template <typename T>
			typename std::enable_if<IsScalar<T>::value, HomogenousCoordsAdapter>::type& operator/=(const T& t) {
				vectorAssignScalar<ScalarDivisionAssignment>(*this, t);
				return *this;
			}
			
			template <typename E>
			HomogenousCoordsAdapter& assign(const VectorExpression<E>& e) {
				vectorAssignVector<ScalarAssignment>(*this, e);
				return *this;
			}

			template <typename E>
			HomogenousCoordsAdapter& plusAssign(const VectorExpression<E>& e) {
				vectorAssignVector<ScalarAdditionAssignment>(*this, e);
				return *this;
			}

			template <typename E>
			HomogenousCoordsAdapter& minusAssign(const VectorExpression<E>& e) {
				vectorAssignVector<ScalarSubtractionAssignment>(*this, e);
				return *this;
			}
	
			void swap(HomogenousCoordsAdapter& va) {
				if (this != &va)
					vectorSwap(*this, va);
			}
	
			friend void swap(HomogenousCoordsAdapter& va1, HomogenousCoordsAdapter& va2) {
				va1.swap(va2);
			}

		private:
			VectorClosureType data;
			ValueType         extElem;
		};

		template <typename V>
		class VectorQuaternionAdapter : public QuaternionExpression<VectorQuaternionAdapter<V> >
		{

			typedef VectorQuaternionAdapter<V> SelfType;

		public:
			typedef V VectorType;
			typedef typename V::ValueType ValueType;
			typedef typename V::ConstReference ConstReference;
			typedef typename std::conditional<std::is_const<V>::value,
											 typename V::ConstReference,
											 typename V::Reference>::type Reference;
			typedef typename std::conditional<std::is_const<V>::value,
											 typename V::ConstClosureType,
											 typename V::ClosureType>::type VectorClosureType;
			typedef const SelfType ConstClosureType;
			typedef SelfType ClosureType;
					
			explicit VectorQuaternionAdapter(VectorType& v): data(v) {}

			Reference getC1() {
				return data(0);
			}

			Reference getC2() {
				return data(1);
			}

			Reference getC3() {
				return data(2);
			}

			Reference getC4() {
				return data(3);
			}

			ConstReference getC1() const {
				return data(0);
			}

			ConstReference getC2() const {
				return data(1);
			}

			ConstReference getC3() const {
				return data(2);
			}

			ConstReference getC4() const {
				return data(3);
			}

			VectorClosureType& getData() {
				return data;
			}

			const VectorClosureType& getData() const {
				return data;
			}

			VectorQuaternionAdapter& operator=(const VectorQuaternionAdapter& a) {
				quaternionAssignQuaternion<ScalarAssignment>(*this, typename QuaternionTemporaryTraits<SelfType>::Type(a));
				return *this;
			}

			template <typename E>
			VectorQuaternionAdapter& operator=(const QuaternionExpression<E>& e) {
				quaternionAssignQuaternion<ScalarAssignment>(*this, typename QuaternionTemporaryTraits<SelfType>::Type(e));
				return *this;
			}

			template <typename T>
			typename std::enable_if<IsScalar<T>::value, VectorQuaternionAdapter>::type& 
			operator=(const T& t) {
				data(0) = t;
				data(1) = ValueType();
				data(2) = ValueType();
				data(3) = ValueType();
				return *this;
			}

			template <typename E>
			VectorQuaternionAdapter& operator+=(const QuaternionExpression<E>& e) {
				quaternionAssignQuaternion<ScalarAssignment>(*this, typename QuaternionTemporaryTraits<SelfType>::Type(*this + e));
				return *this;
			}	

			template <typename T>
			typename std::enable_if<IsScalar<T>::value, VectorQuaternionAdapter>::type& 
			operator+=(const T& t) {
				data(0) += t;
				return *this;
			}

			template <typename E>
			VectorQuaternionAdapter& operator-=(const QuaternionExpression<E>& e) {
				quaternionAssignQuaternion<ScalarAssignment>(*this, typename QuaternionTemporaryTraits<SelfType>::Type(*this - e));
				return *this;
			}

			template <typename T>
			typename std::enable_if<IsScalar<T>::value, VectorQuaternionAdapter>::type& 
			operator-=(const T& t) {
				data(0) -= t;
				return *this;
			}

			template <typename E>
			VectorQuaternionAdapter& operator*=(const QuaternionExpression<E>& e) {
				quaternionAssignQuaternion<ScalarAssignment>(*this, typename QuaternionTemporaryTraits<SelfType>::Type(*this * e));
				return *this;
			}

			template <typename T>
			typename std::enable_if<IsScalar<T>::value, VectorQuaternionAdapter>::type& 
			operator*=(const T& t) {
				quaternionAssignScalar<ScalarMultiplicationAssignment>(*this, t);
				return *this;
			}

			template <typename E>
			VectorQuaternionAdapter& operator/=(const QuaternionExpression<E>& e) {
				quaternionAssignQuaternion<ScalarAssignment>(*this, typename QuaternionTemporaryTraits<SelfType>::Type(*this / e));
				return *this;
			}

			template <typename T>
			typename std::enable_if<IsScalar<T>::value, VectorQuaternionAdapter>::type& 
			operator/=(const T& t) {
				quaternionAssignScalar<ScalarDivisionAssignment>(*this, t);
				return *this;
			}
			
			template <typename E>
			VectorQuaternionAdapter& assign(const QuaternionExpression<E>& e) {
				quaternionAssignQuaternion<ScalarAssignment>(*this, e);
				return *this;
			}

			template <typename E>
			VectorQuaternionAdapter& plusAssign(const QuaternionExpression<E>& e) {
				quaternionAssignQuaternion<ScalarAdditionAssignment>(*this, e);
				return *this;
			}

			template <typename E>
			VectorQuaternionAdapter& minusAssign(const QuaternionExpression<E>& e) {
				quaternionAssignQuaternion<ScalarSubtractionAssignment>(*this, e);
				return *this;
			}

			void swap(VectorQuaternionAdapter& a) {
				if (this != &a)
					quaternionSwap(*this, a);
			}
	
			friend void swap(VectorQuaternionAdapter& a1, VectorQuaternionAdapter& a2) {
				a1.swap(a2);
			}

			void set(const ValueType& c1 = ValueType(), const ValueType& c2 = ValueType(), 
									 const ValueType& c3 = ValueType(), const ValueType& c4 = ValueType()) {
				data(0) = c1;
				data(1) = c2;
				data(2) = c3;
				data(3) = c4;
			}

		private:
			VectorClosureType data;
		};

		template <typename T> class Quaternion;
		template <typename V>
		struct QuaternionTemporaryTraits<VectorQuaternionAdapter<V> >  
		{

			typedef Quaternion<typename V::ValueType> Type;
		}; 
	
		template <typename V>
		struct QuaternionTemporaryTraits<const VectorQuaternionAdapter<V> >  
		{

			typedef Quaternion<typename V::ValueType> Type;
		}; 

		template <typename V>
		struct VectorTemporaryTraits<HomogenousCoordsAdapter<V> > : public VectorTemporaryTraits<V> {};

		template <typename V>
		struct VectorTemporaryTraits<const HomogenousCoordsAdapter<V> > : public VectorTemporaryTraits<V> {};
	
		template <typename E>
		VectorQuaternionAdapter<E> 
		quat(VectorExpression<E>& e)
		{
			return VectorQuaternionAdapter<E>(e());
		}

		template <typename E>
		VectorQuaternionAdapter<const E> 
		quat(const VectorExpression<E>& e)
		{
			return VectorQuaternionAdapter<const E>(e());
		}

		template <typename E>
		HomogenousCoordsAdapter<E> 
		homog(VectorExpression<E>& e)
		{
			return HomogenousCoordsAdapter<E>(e());
		}

		template <typename E>
		HomogenousCoordsAdapter<const E> 
		homog(const VectorExpression<E>& e)
		{
			return HomogenousCoordsAdapter<const E>(e());
		}
	}
}

#endif // CDPL_MATH_VECTORADAPTER_HPP
