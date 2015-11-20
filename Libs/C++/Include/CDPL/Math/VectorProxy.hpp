/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * VectorProxy.hpp 
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
 * \brief Definition of vector proxy types.
 */

#ifndef CDPL_MATH_VECTORPROXY_HPP
#define CDPL_MATH_VECTORPROXY_HPP

#include <boost/mpl/if.hpp>
#include <boost/type_traits/is_const.hpp>
#include <boost/utility.hpp>

#include "CDPL/Math/Config.hpp"
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

		template <typename V>
		class VectorRange : public VectorExpression<VectorRange<V> >
		{

			typedef VectorRange<V> SelfType;

		public:
			typedef V VectorType;
			typedef typename V::SizeType SizeType;
			typedef typename V::DifferenceType DifferenceType;
			typedef typename V::ValueType ValueType;
			typedef typename V::ConstReference ConstReference;
			typedef typename boost::mpl::if_<boost::is_const<V>,
											 typename V::ConstReference,
											 typename V::Reference>::type Reference;
			typedef typename boost::mpl::if_<boost::is_const<V>,
											 typename V::ConstClosureType,
											 typename V::ClosureType>::type VectorClosureType;
			typedef const SelfType ConstClosureType;
			typedef SelfType ClosureType;
			typedef Range<SizeType> RangeType;
			
			CDPL_MATH_INLINE VectorRange(VectorType& v, const RangeType& r): data(v), range(r) {}

			CDPL_MATH_INLINE Reference operator()(SizeType i) {
				return data(range(i));
			}

			CDPL_MATH_INLINE ConstReference operator()(SizeType i) const {
				return data(range(i));
			}
	
			CDPL_MATH_INLINE Reference operator[](SizeType i) {
				return data[range(i)];
			}

			CDPL_MATH_INLINE ConstReference operator[](SizeType i) const {
				return data[range(i)];
			}

			CDPL_MATH_INLINE SizeType getStart() const {
				return range.getStart();
			}

			CDPL_MATH_INLINE SizeType getSize() const {
				return range.getSize();
			}

			CDPL_MATH_INLINE bool isEmpty() const {
				return range.isEmpty();
			}

			CDPL_MATH_INLINE VectorClosureType& getData() {
				return data;
			}

			CDPL_MATH_INLINE const VectorClosureType& getData() const {
				return data;
			}

			CDPL_MATH_INLINE VectorRange& operator=(const VectorRange& r) {
				vectorAssignVector<ScalarAssignment>(*this, typename VectorTemporaryTraits<V>::Type(r));
				return *this;
			}

			template <typename E>
			CDPL_MATH_INLINE VectorRange& operator=(const VectorExpression<E>& e) {
				vectorAssignVector<ScalarAssignment>(*this, typename VectorTemporaryTraits<V>::Type(e));
				return *this;
			}

			template <typename E>
			CDPL_MATH_INLINE VectorRange& operator+=(const VectorExpression<E>& e) {
				vectorAssignVector<ScalarAssignment>(*this, typename VectorTemporaryTraits<V>::Type(*this + e));
				return *this;
			}	

			template <typename E>
			CDPL_MATH_INLINE VectorRange& operator-=(const VectorExpression<E>& e) {
				vectorAssignVector<ScalarAssignment>(*this, typename VectorTemporaryTraits<V>::Type(*this - e));
				return *this;
			}

			template <typename T>
			CDPL_MATH_INLINE 
			typename boost::enable_if<IsScalar<T>, VectorRange>::type& operator*=(const T& t) {
				vectorAssignScalar<ScalarMultiplicationAssignment>(*this, t);
				return *this;
			}
	
			template <typename T>
			CDPL_MATH_INLINE 
			typename boost::enable_if<IsScalar<T>, VectorRange>::type& operator/=(const T& t) {
				vectorAssignScalar<ScalarDivisionAssignment>(*this, t);
				return *this;
			}
			
			template <typename E>
			CDPL_MATH_INLINE VectorRange& assign(const VectorExpression<E>& e) {
				vectorAssignVector<ScalarAssignment>(*this, e);
				return *this;
			}

			template <typename E>
			CDPL_MATH_INLINE VectorRange& plusAssign(const VectorExpression<E>& e) {
				vectorAssignVector<ScalarAdditionAssignment>(*this, e);
				return *this;
			}

			template <typename E>
			CDPL_MATH_INLINE VectorRange& minusAssign(const VectorExpression<E>& e) {
				vectorAssignVector<ScalarSubtractionAssignment>(*this, e);
				return *this;
			}
	
			CDPL_MATH_INLINE void swap(VectorRange& r) {
				if (this != &r)
					vectorSwap(*this, r);
			}
	
			CDPL_MATH_INLINE friend void swap(VectorRange& r1, VectorRange& r2) {
				r1.swap(r2);
			}

		private:
			VectorClosureType data;
			RangeType         range;
		};

		template <typename V>
		class VectorSlice : public VectorExpression<VectorSlice<V> >
		{

			typedef VectorSlice<V> SelfType;

		public:
			typedef V VectorType;
			typedef typename V::SizeType SizeType;
			typedef typename V::DifferenceType DifferenceType;
			typedef typename V::ValueType ValueType;
			typedef typename V::ConstReference ConstReference;
			typedef typename boost::mpl::if_<boost::is_const<V>,
											 typename V::ConstReference,
											 typename V::Reference>::type Reference;
			typedef typename boost::mpl::if_<boost::is_const<V>,
											 typename V::ConstClosureType,
											 typename V::ClosureType>::type VectorClosureType;
			typedef const SelfType ConstClosureType;
			typedef SelfType ClosureType;
			typedef Slice<SizeType, DifferenceType> SliceType;
			
			CDPL_MATH_INLINE VectorSlice(VectorType& v, const SliceType& s): data(v), slice(s) {}

			CDPL_MATH_INLINE Reference operator()(SizeType i) {
				return data(slice(i));
			}

			CDPL_MATH_INLINE ConstReference operator()(SizeType i) const {
				return data(slice(i));
			}
	
			CDPL_MATH_INLINE Reference operator[](SizeType i) {
				return data[slice(i)];
			}

			CDPL_MATH_INLINE ConstReference operator[](SizeType i) const {
				return data[slice(i)];
			}

			CDPL_MATH_INLINE SizeType getStart() const {
				return slice.getStart();
			}

			CDPL_MATH_INLINE DifferenceType getStride() const {
				return slice.getStride();
			}

			CDPL_MATH_INLINE SizeType getSize() const {
				return slice.getSize();
			}
			
			CDPL_MATH_INLINE bool isEmpty() const {
				return slice.isEmpty();
			}

			CDPL_MATH_INLINE VectorClosureType& getData() {
				return data;
			}

			CDPL_MATH_INLINE const VectorClosureType& getData() const {
				return data;
			}

			CDPL_MATH_INLINE VectorSlice& operator=(const VectorSlice& s) {
				vectorAssignVector<ScalarAssignment>(*this, typename VectorTemporaryTraits<V>::Type(s));
				return *this;
			}

			template <typename E>
			CDPL_MATH_INLINE VectorSlice& operator=(const VectorExpression<E>& e) {
				vectorAssignVector<ScalarAssignment>(*this, typename VectorTemporaryTraits<V>::Type(e));
				return *this;
			}

			template <typename E>
			CDPL_MATH_INLINE VectorSlice& operator+=(const VectorExpression<E>& e) {
				vectorAssignVector<ScalarAssignment>(*this, typename VectorTemporaryTraits<V>::Type(*this + e));
				return *this;
			}	

			template <typename E>
			CDPL_MATH_INLINE VectorSlice& operator-=(const VectorExpression<E>& e) {
				vectorAssignVector<ScalarAssignment>(*this, typename VectorTemporaryTraits<V>::Type(*this - e));
				return *this;
			}

			template <typename T>
			CDPL_MATH_INLINE 
			typename boost::enable_if<IsScalar<T>, VectorSlice>::type& operator*=(const T& t) {
				vectorAssignScalar<ScalarMultiplicationAssignment>(*this, t);
				return *this;
			}
	
			template <typename T>
			CDPL_MATH_INLINE 
			typename boost::enable_if<IsScalar<T>, VectorSlice>::type& operator/=(const T& t) {
				vectorAssignScalar<ScalarDivisionAssignment>(*this, t);
				return *this;
			}
			
			template <typename E>
			CDPL_MATH_INLINE VectorSlice& assign(const VectorExpression<E>& e) {
				vectorAssignVector<ScalarAssignment>(*this, e);
				return *this;
			}

			template <typename E>
			CDPL_MATH_INLINE VectorSlice& plusAssign(const VectorExpression<E>& e) {
				vectorAssignVector<ScalarAdditionAssignment>(*this, e);
				return *this;
			}

			template <typename E>
			CDPL_MATH_INLINE VectorSlice& minusAssign(const VectorExpression<E>& e) {
				vectorAssignVector<ScalarSubtractionAssignment>(*this, e);
				return *this;
			}
	
			CDPL_MATH_INLINE void swap(VectorSlice& s) {
				if (this != &s)
					vectorSwap(*this, s);
			}
	
			CDPL_MATH_INLINE friend void swap(VectorSlice& s1, VectorSlice& s2) {
				s1.swap(s2);
			}

		private:
			VectorClosureType data;
			SliceType         slice;
		};

		template <typename V>
		struct VectorTemporaryTraits<VectorRange<V> > : public VectorTemporaryTraits<V> {};
	
		template <typename V>
		struct VectorTemporaryTraits<const VectorRange<V> > : public VectorTemporaryTraits<V> {};

		template <typename V>
		struct VectorTemporaryTraits<VectorSlice<V> > : public VectorTemporaryTraits<V> {};
	
		template <typename V>
		struct VectorTemporaryTraits<const VectorSlice<V> > : public VectorTemporaryTraits<V> {};

		template <typename E>
		CDPL_MATH_INLINE
		VectorRange<E> 
		range(VectorExpression<E>& e, const typename VectorRange<E>::RangeType& r)
		{
			return VectorRange<E>(e(), r);
		} 

		template <typename E>
		CDPL_MATH_INLINE
		VectorRange<const E> 
		range(const VectorExpression<E>& e, const typename VectorRange<const E>::RangeType& r)
		{
			return VectorRange<const E>(e(), r);
		} 

		template <typename E>
		CDPL_MATH_INLINE
		VectorRange<E> 
		range(VectorExpression<E>& e, 
			  typename VectorRange<E>::RangeType::SizeType start, 
			  typename VectorRange<E>::RangeType::SizeType stop)
		{
			typedef typename VectorRange<E>::RangeType RangeType;

			return VectorRange<E>(e(), RangeType(start, stop));
		} 

		template <typename E>
		CDPL_MATH_INLINE
		VectorRange<const E> 
		range(const VectorExpression<E>& e, 
			  typename VectorRange<const E>::RangeType::SizeType start, 
			  typename VectorRange<const E>::RangeType::SizeType stop)
		{
			typedef typename VectorRange<const E>::RangeType RangeType;

			return VectorRange<const E>(e(), RangeType(start, stop));
		} 

		template <typename E>
		CDPL_MATH_INLINE
		VectorSlice<E> 
		slice(VectorExpression<E>& e, const typename VectorSlice<E>::SliceType& s)
		{
			return VectorSlice<E>(e(), s);
		} 

		template <typename E>
		CDPL_MATH_INLINE
		VectorSlice<const E> 
		slice(const VectorExpression<E>& e, const typename VectorSlice<const E>::SliceType& s)
		{
			return VectorSlice<const E>(e(), s);
		} 

		template <typename E>
		CDPL_MATH_INLINE
		VectorSlice<E> 
		slice(VectorExpression<E>& e, 
			  typename VectorSlice<E>::SliceType::SizeType start, 
			  typename VectorSlice<E>::SliceType::DifferenceType stride, 
			  typename VectorSlice<E>::SliceType::SizeType size)
		{
			typedef typename VectorSlice<E>::SliceType SliceType;

			return VectorSlice<E>(e(), SliceType(start, stride, size));
		} 

		template <typename E>
		CDPL_MATH_INLINE
		VectorSlice<const E> 
		slice(const VectorExpression<E>& e, 
			  typename VectorSlice<const E>::SliceType::SizeType start, 
			  typename VectorSlice<const E>::SliceType::DifferenceType stride, 
			  typename VectorSlice<const E>::SliceType::SizeType size)
		{
			typedef typename VectorSlice<const E>::SliceType SliceType;

			return VectorSlice<const E>(e(), SliceType(start, stride, size));
		} 
	}
}

#endif // CDPL_MATH_VECTORPROXY_HPP
