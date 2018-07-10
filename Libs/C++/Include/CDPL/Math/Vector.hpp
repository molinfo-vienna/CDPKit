/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * Vector.hpp 
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
 * \brief Definition of vector data types.
 */

#ifndef CDPL_MATH_VECTOR_HPP
#define CDPL_MATH_VECTOR_HPP

#include <cstddef>
#include <algorithm>
#include <vector>
#include <limits>

#include <boost/mpl/if.hpp>
#include <boost/type_traits/is_const.hpp>
#include <boost/utility.hpp>
#include <boost/swap.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/unordered_map.hpp>

#include "CDPL/Math/Check.hpp"
#include "CDPL/Math/VectorExpression.hpp"
#include "CDPL/Math/VectorAssignment.hpp"
#include "CDPL/Math/SparseContainerAssignment.hpp"
#include "CDPL/Math/DirectAssignmentProxy.hpp"
#include "CDPL/Math/Functional.hpp"
#include "CDPL/Math/TypeTraits.hpp"
#include "CDPL/Math/SparseContainerElement.hpp"
#include "CDPL/Base/Exceptions.hpp"


namespace CDPL
{

	namespace Math
	{

		template <typename V> 
		class VectorReference : public VectorExpression<VectorReference<V> >
		{

			typedef VectorReference<V> SelfType;

		public:
			typedef V VectorType;
			typedef typename V::ValueType ValueType;
			typedef typename boost::mpl::if_<boost::is_const<V>,
											 typename V::ConstReference,
											 typename V::Reference>::type Reference;
			typedef typename V::ConstReference ConstReference;
			typedef typename V::SizeType SizeType;
			typedef typename V::DifferenceType DifferenceType;
			typedef SelfType ClosureType;
			typedef const SelfType ConstClosureType;
			
			explicit VectorReference(VectorType& v): data(v) {}

			Reference operator[](SizeType i) {
				return data[i];
			}

			ConstReference operator[](SizeType i) const {
				return data[i];
			}

			Reference operator()(SizeType i) {
				return data(i);
			}

			ConstReference operator()(SizeType i) const {
				return data(i);
			}
	
			SizeType getSize() const {
				return data.getSize();
			}

			SizeType getMaxSize() const {
				return data.getMaxSize();
			}

			bool isEmpty() const {
				return data.isEmpty();
			}

			const VectorType& getData() const {
				return data;
			}

			VectorType& getData() {
				return data;
			}

			VectorReference& operator=(const VectorReference& r) {
				data.operator=(r.data);
				return *this;
			}

			template <typename E>
			VectorReference& operator=(const VectorExpression<E>& e) {
				data.operator=(e);
				return *this;
			}

			template <typename E>
			VectorReference& operator+=(const VectorExpression<E>& e) {
				data.operator+=(e);
				return *this;
			}	

			template <typename E>
			VectorReference& operator-=(const VectorExpression<E>& e) {
				data.operator-=(e);
				return *this;
			}

			template <typename T>
			typename boost::enable_if<IsScalar<T>, VectorReference>::type& operator*=(const T& t) {
				data.operator*=(t);
				return *this;
			}
	
			template <typename T>
			typename boost::enable_if<IsScalar<T>, VectorReference>::type& operator/=(const T& t) {
				data.operator/=(t);
				return *this;
			}
			
			template <typename E>
			VectorReference& assign(const VectorExpression<E>& e) {
				data.assign(e);
				return *this;
			}

			template <typename E>
			VectorReference& plusAssign(const VectorExpression<E>& e) {
				data.plusAssign(e);
				return *this;
			}

			template <typename E>
			VectorReference& minusAssign(const VectorExpression<E>& e) {
				data.minusAssign(e);
				return *this;
			}

			void swap(VectorReference& r) {
				data.swap(r.data);
			}
	
			friend void swap(VectorReference& r1, VectorReference& r2) {
				r1.swap(r2);
			}

		private:
			VectorType& data;
		};

		template <typename T, typename A = std::vector<T> > 
		class Vector : public VectorContainer<Vector<T, A> >
		{

			typedef Vector<T, A> SelfType;

		public:
			typedef T ValueType;
			typedef T& Reference;
			typedef const T& ConstReference;
			typedef typename A::size_type SizeType;
			typedef typename A::difference_type DifferenceType;
			typedef A ArrayType;
			typedef T* Pointer;
			typedef const T* ConstPointer;
			typedef VectorReference<SelfType> ClosureType;
			typedef const VectorReference<const SelfType> ConstClosureType;
			typedef SelfType VectorTemporaryType;
			typedef boost::shared_ptr<SelfType> SharedPointer;

			Vector(): data() {}

			explicit Vector(SizeType n): data(storageSize(n)) {}

			Vector(SizeType n, const ValueType& v): data(storageSize(n), v) {}

			Vector(const ArrayType& data): data(data) {}

			Vector(const Vector& v): data(v.data) {}

			template <typename E>
			Vector(const VectorExpression<E>& e): data(storageSize(e().getSize())) {
				vectorAssignVector<ScalarAssignment>(*this, e);
			}

			Reference operator[](SizeType i) {
				return this->operator()(i);
			}

			ConstReference operator[](SizeType i) const {
				return this->operator()(i);
			}

			Reference operator()(SizeType i) {
				CDPL_MATH_CHECK(i < getSize(), "Index out of range", Base::IndexError);
				return data[i];
			}

			ConstReference operator()(SizeType i) const {
				CDPL_MATH_CHECK(i < getSize(), "Index out of range", Base::IndexError);
				return data[i];
			}

			bool isEmpty() const {
				return data.empty();
			}

			SizeType getSize() const {
				return data.size();
			}

			SizeType getMaxSize() const {
				return data.max_size();
			}

			ArrayType& getData() {
				return data;
			}
			
			const ArrayType& getData() const {
				return data;
			}

			Vector& operator=(const Vector& v) {
				data = v.data;
				return *this;
			}

			template <typename C>
			Vector& operator=(const VectorContainer<C>& c) {
				return assign(c);
			}

			template <typename E>
			Vector& operator=(const VectorExpression<E>& e) {
				Vector tmp(e);
				swap(tmp);

				return *this;
			}

			template <typename C>
			Vector& operator+=(const VectorContainer<C>& c) {
				return plusAssign(c);
			}

			template <typename E>
			Vector& operator+=(const VectorExpression<E>& e) {
				Vector tmp(*this + e);
				swap(tmp);

				return *this;
			}	

			template <typename C>
			Vector& operator-=(const VectorContainer<C>& c) {
				return minusAssign(c);
			}

			template <typename E>
			Vector& operator-=(const VectorExpression<E>& e) {
				Vector tmp(*this - e);
				swap(tmp);

				return *this;
			}

			template <typename T1>
			typename boost::enable_if<IsScalar<T1>, Vector>::type& operator*=(const T1& t) {
				vectorAssignScalar<ScalarMultiplicationAssignment>(*this, t);
				return *this;
			}
	
			template <typename T1>
			typename boost::enable_if<IsScalar<T1>, Vector>::type& operator/=(const T1& t) {
				vectorAssignScalar<ScalarDivisionAssignment>(*this, t);
				return *this;
			}
			
			template <typename E>
			Vector& assign(const VectorExpression<E>& e) {
				resize(e().getSize());
				vectorAssignVector<ScalarAssignment>(*this, e);
				return *this;
			}

			template <typename E>
			Vector& plusAssign(const VectorExpression<E>& e) {
				vectorAssignVector<ScalarAdditionAssignment>(*this, e);
				return *this;
			}

			template <typename E>
			Vector& minusAssign(const VectorExpression<E>& e) {
				vectorAssignVector<ScalarSubtractionAssignment>(*this, e);
				return *this;
			}

			void swap(Vector& v) {
				if (this != &v)
					boost::swap(data, v.data);
			}
	
			friend void swap(Vector& v1, Vector& v2) {
				v1.swap(v2);
			}

			void clear(const ValueType& v = ValueType()) {
				std::fill(data.begin(), data.end(), v);
			}

			void resize(SizeType n, const ValueType& v = ValueType()) {
				data.resize(storageSize(n), v);
			}

		private:
			SizeType storageSize(SizeType n) {
				CDPL_MATH_CHECK(n <= data.max_size(), "Maximum size exceeded", Base::SizeError);
				return n;
			}

			ArrayType data;
		};
 
		template <typename T> 
		class SparseVector : public VectorContainer<SparseVector<T> >
		{

			typedef SparseVector<T> SelfType;

		public:
			typedef T ValueType;
			typedef std::size_t SizeType;
			typedef std::ptrdiff_t DifferenceType;
			typedef SizeType KeyType;
			typedef const T& ConstReference;
			typedef SparseContainerElement<SelfType, KeyType> Reference;
			typedef boost::unordered_map<KeyType, ValueType> ArrayType;
			typedef T* Pointer;
			typedef const T* ConstPointer;
			typedef VectorReference<SelfType> ClosureType;
			typedef const VectorReference<const SelfType> ConstClosureType;
			typedef SelfType VectorTemporaryType;
			typedef boost::shared_ptr<SelfType> SharedPointer;

			SparseVector(): data(), size(0), defValue() {}

			explicit SparseVector(SizeType n): data(), size(storageSize(n)), defValue() {}

			SparseVector(SizeType n, const ValueType& v): data(), size(storageSize(n)), defValue(v) {}
	
			SparseVector(const SparseVector& v): data(v.data), size(v.size), defValue(v.defValue) {}

			template <typename E>
			SparseVector(const VectorExpression<E>& e): data(), size(storageSize(e().getSize())), defValue() {
				vectorAssignVector<ScalarAssignment>(*this, e);
			}

			Reference operator[](SizeType i) {
				return this->operator()(i);
			}

			ConstReference operator[](SizeType i) const {
				return this->operator()(i);
			}

			Reference operator()(SizeType i) {
				CDPL_MATH_CHECK(i < getSize(), "Index out of range", Base::IndexError);
				return Reference(*this, i);
			}

			ConstReference operator()(SizeType i) const {
				CDPL_MATH_CHECK(i < getSize(), "Index out of range", Base::IndexError);

				typename ArrayType::const_iterator it = data.find(i);

				if (it == data.end())
					return defValue;

				return it->second;
			}

		    SizeType getNumElements() const {
				return data.size();
			}

			bool isEmpty() const {
				return (size == 0);
			}

			SizeType getSize() const {
				return size;
			}

			SizeType getMaxSize() const {
				return data.max_size();
			}

			ArrayType& getData() {
				return data;
			}
			
			const ArrayType& getData() const {
				return data;
			}

		    ConstReference getDefaultValue() const {
				return defValue;
			}

			ValueType& getDefaultValue() {
				return defValue;
			}

			SparseVector& operator=(const SparseVector& v) {
				data = v.data;
				defValue = v.defValue;
				size = v.size;
				return *this;
			}

			template <typename C>
			SparseVector& operator=(const VectorContainer<C>& c) {
				return assign(c);
			}

			template <typename E>
			SparseVector& operator=(const VectorExpression<E>& e) {
				SparseVector tmp(e);
				swap(tmp);

				return *this;
			}

			template <typename C>
			SparseVector& operator+=(const VectorContainer<C>& c) {
				return plusAssign(c);
			}

			template <typename E>
			SparseVector& operator+=(const VectorExpression<E>& e) {
				SparseVector tmp(*this + e);
				swap(tmp);

				return *this;
			}	

			template <typename C>
			SparseVector& operator-=(const VectorContainer<C>& c) {
				return minusAssign(c);
			}

			template <typename E>
			SparseVector& operator-=(const VectorExpression<E>& e) {
				SparseVector tmp(*this - e);
				swap(tmp);

				return *this;
			}

			template <typename T1>
			typename boost::enable_if<IsScalar<T1>, SparseVector>::type& operator*=(const T1& t) {
				sparseContainerAssignScalar<ScalarMultiplicationAssignment>(*this, t);
				return *this;
			}
	
			template <typename T1>
			typename boost::enable_if<IsScalar<T1>, SparseVector>::type& operator/=(const T1& t) {
				sparseContainerAssignScalar<ScalarDivisionAssignment>(*this, t);
				return *this;
			}
			
			template <typename E>
			SparseVector& assign(const VectorExpression<E>& e) {
				resize(e().getSize());
				vectorAssignVector<ScalarAssignment>(*this, e);
				return *this;
			}

			template <typename E>
			SparseVector& plusAssign(const VectorExpression<E>& e) {
				vectorAssignVector<ScalarAdditionAssignment>(*this, e);
				return *this;
			}

			template <typename E>
			SparseVector& minusAssign(const VectorExpression<E>& e) {
				vectorAssignVector<ScalarSubtractionAssignment>(*this, e);
				return *this;
			}

			void swap(SparseVector& v) {
				if (this != &v) {
					boost::swap(data, v.data);
					boost::swap(size, v.size);
					boost::swap(defValue, v.defValue);
				}
			}
	
			friend void swap(SparseVector& v1, SparseVector& v2) {
				v1.swap(v2);
			}

			void clear(const ValueType& v = ValueType()) {
				defValue = v;
				data.clear();
			}

			void resize(SizeType n) {
				CDPL_MATH_CHECK(n <= data.max_size(), "Maximum size exceeded", Base::SizeError);

				for (typename ArrayType::iterator it = data.begin(); it != data.end(); ) {
					if (it->first >= n)
						it = data.erase(it);
					else
						++it;
				}

				size = n;
			}

		private:
			SizeType storageSize(SizeType n) {
				CDPL_MATH_CHECK(n <= data.max_size(), "Maximum size exceeded", Base::SizeError);
				return n;
			}

			ArrayType data;
			SizeType  size;
			ValueType defValue;
		};
 
		template <typename T, std::size_t N> 
		class BoundedVector : public VectorContainer<BoundedVector<T, N> >
		{

			typedef BoundedVector<T, N> SelfType;

		public:
			typedef T ValueType;
			typedef T& Reference;
			typedef const T& ConstReference;
			typedef std::size_t SizeType;
			typedef std::ptrdiff_t DifferenceType;
			typedef ValueType ArrayType[N];
			typedef T* Pointer;
			typedef const T* ConstPointer;
			typedef VectorReference<SelfType> ClosureType;
			typedef const VectorReference<const SelfType> ConstClosureType;
			typedef BoundedVector<T, N + 1> VectorTemporaryType;
			typedef boost::shared_ptr<SelfType> SharedPointer;

			static const SizeType MaxSize = N;

			BoundedVector(): size(0) {}

			explicit BoundedVector(SizeType n): size(0) {
				resize(n);
			}

			BoundedVector(SizeType n, const ValueType& v): size(0) {
				resize(n, v);
			}

			BoundedVector(const BoundedVector& v): size(v.size) {
				std::copy(v.data, v.data + v.size, data);
			}

			template <typename E>
			BoundedVector(const VectorExpression<E>& e): size(0) {
				resize(e().getSize());
				vectorAssignVector<ScalarAssignment>(*this, e);
			}

			Reference operator[](SizeType i) {
				return this->operator()(i);
			}

			ConstReference operator[](SizeType i) const {
				return this->operator()(i);
			}

			Reference operator()(SizeType i) {
				CDPL_MATH_CHECK(i < getSize(), "Index out of range", Base::IndexError);
				return data[i];
			}

			ConstReference operator()(SizeType i) const {
				CDPL_MATH_CHECK(i < getSize(), "Index out of range", Base::IndexError);
				return data[i];
			}

			bool isEmpty() const {
				return (size == 0);
			}

			SizeType getSize() const {
				return size;
			}

			SizeType getMaxSize() const {
				return N;
			}

			Pointer getData() {
				return data;
			}
			
			ConstPointer getData() const {
				return data;
			}

			BoundedVector& operator=(const BoundedVector& v) {
				if (this != &v) {
					std::copy(v.data, v.data + v.size, data);
					size = v.size;
				}

				return *this;
			}

			template <typename C>
			BoundedVector& operator=(const VectorContainer<C>& c) {
				return assign(c);
			}

			template <typename E>
			BoundedVector& operator=(const VectorExpression<E>& e) {
				BoundedVector tmp(e);

				return this->operator=(tmp);
			}

			template <typename C>
			BoundedVector& operator+=(const VectorContainer<C>& c) {
				return plusAssign(c);
			}

			template <typename E>
			BoundedVector& operator+=(const VectorExpression<E>& e) {
				BoundedVector tmp(*this + e);

				return this->operator=(tmp);
			}	

			template <typename C>
			BoundedVector& operator-=(const VectorContainer<C>& c) {
				return minusAssign(c);
			}

			template <typename E>
			BoundedVector& operator-=(const VectorExpression<E>& e) {
				BoundedVector tmp(*this - e);

				return this->operator=(tmp);
			}

			template <typename T1>
			typename boost::enable_if<IsScalar<T1>, BoundedVector>::type& operator*=(const T1& t) {
				vectorAssignScalar<ScalarMultiplicationAssignment>(*this, t);
				return *this;
			}
	
			template <typename T1>
			typename boost::enable_if<IsScalar<T1>, BoundedVector>::type& operator/=(const T1& t) {
				vectorAssignScalar<ScalarDivisionAssignment>(*this, t);
				return *this;
			}
			
			template <typename E>
			BoundedVector& assign(const VectorExpression<E>& e) {
				resize(e().getSize());
				vectorAssignVector<ScalarAssignment>(*this, e);
				return *this;
			}

			template <typename E>
			BoundedVector& plusAssign(const VectorExpression<E>& e) {
				vectorAssignVector<ScalarAdditionAssignment>(*this, e);
				return *this;
			}

			template <typename E>
			BoundedVector& minusAssign(const VectorExpression<E>& e) {
				vectorAssignVector<ScalarSubtractionAssignment>(*this, e);
				return *this;
			}

			void swap(BoundedVector& v) {
				if (this != &v) {
					std::swap_ranges(data, data + std::max(size, v.size), v.data);
					boost::swap(size, v.size);
				}
			}
	
			friend void swap(BoundedVector& v1, BoundedVector& v2) {
				v1.swap(v2);
			}

			void clear(const ValueType& v = ValueType()) {
				std::fill(data, data + size, v);
			}

			void resize(SizeType n) {
				CDPL_MATH_CHECK(n <= getMaxSize(), "Maximum size exceeded", Base::RangeError);
				size = n;
			}

			void resize(SizeType n, const ValueType& v) {
				CDPL_MATH_CHECK(n <= getMaxSize(), "Maximum size exceeded", Base::RangeError);

				if (n > size)
					std::fill(data + size, data + n, v);

				size = n;
			}

		private:
			ArrayType data;
			SizeType  size;
		};

		template <typename T, std::size_t N> const typename BoundedVector<T, N>::SizeType BoundedVector<T, N>::MaxSize;

		template <typename T, std::size_t N> 
		class CVector : public VectorContainer<CVector<T, N> >
		{

			typedef CVector<T, N> SelfType;

		public:
			typedef T ValueType;
			typedef T& Reference;
			typedef const T& ConstReference;
			typedef std::size_t SizeType;
			typedef std::ptrdiff_t DifferenceType;
			typedef ValueType ArrayType[N];
			typedef T* Pointer;
			typedef const T* ConstPointer;
			typedef VectorReference<SelfType> ClosureType;
			typedef const VectorReference<const SelfType> ConstClosureType;
			typedef BoundedVector<T, N + 1> VectorTemporaryType;
			typedef boost::shared_ptr<SelfType> SharedPointer;

			static const SizeType Size = N;

			CVector() {
				clear();
			}

			explicit CVector(const ValueType& v) {
				clear(v);
			}

			CVector(const CVector& v) {
				std::copy(v.data, v.data + N, data);
			}

			template <typename E>
			CVector(const VectorExpression<E>& e) {
				vectorAssignVector<ScalarAssignment>(*this, e);
			}

			Reference operator[](SizeType i) {
				return this->operator()(i);
			}

			ConstReference operator[](SizeType i) const {
				return this->operator()(i);
			}

			Reference operator()(SizeType i) {
				CDPL_MATH_CHECK(i < getSize(), "Index out of range", Base::IndexError);
				return data[i];
			}

			ConstReference operator()(SizeType i) const {
				CDPL_MATH_CHECK(i < getSize(), "Index out of range", Base::IndexError);
				return data[i];
			}

			bool isEmpty() const {
				return (N == 0);
			}

			SizeType getSize() const {
				return N;
			}

			SizeType getMaxSize() const {
				return N;
			}

			Pointer getData() {
				return data;
			}
			
			ConstPointer getData() const {
				return data;
			}

			CVector& operator=(const CVector& v) {
				if (this != &v)
					std::copy(v.data, v.data + N, data);

				return *this;
			}

			template <typename C>
			CVector& operator=(const VectorContainer<C>& c) {
				return assign(c);
			}

			template <typename E>
			CVector& operator=(const VectorExpression<E>& e) {
				CVector tmp(e);

				return this->operator=(tmp);
			}

			template <typename C>
			CVector& operator+=(const VectorContainer<C>& c) {
				return plusAssign(c);
			}

			template <typename E>
			CVector& operator+=(const VectorExpression<E>& e) {
				CVector tmp(*this + e);

				return this->operator=(tmp);
			}	

			template <typename C>
			CVector& operator-=(const VectorContainer<C>& c) {
				return minusAssign(c);
			}

			template <typename E>
			CVector& operator-=(const VectorExpression<E>& e) {
				CVector tmp(*this - e);

				return this->operator=(tmp);
			}

			template <typename T1>
			typename boost::enable_if<IsScalar<T1>, CVector>::type& operator*=(const T1& t) {
				vectorAssignScalar<ScalarMultiplicationAssignment>(*this, t);
				return *this;
			}
	
			template <typename T1>
			typename boost::enable_if<IsScalar<T1>, CVector>::type& operator/=(const T1& t) {
				vectorAssignScalar<ScalarDivisionAssignment>(*this, t);
				return *this;
			}
			
			template <typename E>
			CVector& assign(const VectorExpression<E>& e) {
				vectorAssignVector<ScalarAssignment>(*this, e);
				return *this;
			}

			template <typename E>
			CVector& plusAssign(const VectorExpression<E>& e) {
				vectorAssignVector<ScalarAdditionAssignment>(*this, e);
				return *this;
			}

			template <typename E>
			CVector& minusAssign(const VectorExpression<E>& e) {
				vectorAssignVector<ScalarSubtractionAssignment>(*this, e);
				return *this;
			}

			void swap(CVector& v) {
				if (this != &v)
					std::swap_ranges(data, data + N, v.data);
			}
	
			friend void swap(CVector& v1, CVector& v2) {
				v1.swap(v2);
			}

			void clear(const ValueType& v = ValueType()) {
				std::fill(data, data + N, v);
			}

		private:
			ArrayType data;
		};

		template <typename T, std::size_t N> const typename CVector<T, N>::SizeType CVector<T, N>::Size;

		template <typename T> 
		class ZeroVector : public VectorContainer<ZeroVector<T> >
		{

			typedef ZeroVector<T> SelfType;

		public:
			typedef T ValueType;
			typedef const T& Reference;
			typedef const T& ConstReference;
			typedef std::size_t SizeType;
			typedef std::ptrdiff_t DifferenceType;
			typedef VectorReference<SelfType> ClosureType;
			typedef const VectorReference<const SelfType> ConstClosureType;
			typedef Vector<T> VectorTemporaryType;

			ZeroVector(): size(0) {}

			explicit ZeroVector(SizeType n): size(n) {}

			ZeroVector(const ZeroVector& v): size(v.size) {}
	
			ConstReference operator[](SizeType i) const {
				return this->operator()(i);
			}

			ConstReference operator()(SizeType i) const {
				CDPL_MATH_CHECK(i < getSize(), "Index out of range", Base::IndexError);
				return zero;
			}

			bool isEmpty() const {
				return (size == 0);
			}

			SizeType getSize() const {
				return size;
			}

			SizeType getMaxSize() const {
				return std::numeric_limits<SizeType>::max();
			}
		
			ZeroVector& operator=(const ZeroVector& v) {
				size = v.size;
				return *this;
			}

			void resize(SizeType n) {
				size = n;
			}

			void swap(ZeroVector& v) {
				if (this != &v)
					boost::swap(size, v.size);
			}
	
			friend void swap(ZeroVector& v1, ZeroVector& v2) {
				v1.swap(v2);
			}

		private:
			SizeType               size;
			static const ValueType zero;
		};

		template <typename T> const typename ZeroVector<T>::ValueType ZeroVector<T>::zero = ZeroVector<T>::ValueType();

		template <typename T> 
		class UnitVector : public VectorContainer<UnitVector<T> >
		{

			typedef UnitVector<T> SelfType;

		public:
			typedef T ValueType;
			typedef const T& Reference;
			typedef const T& ConstReference;
			typedef std::size_t SizeType;
			typedef std::ptrdiff_t DifferenceType;
			typedef VectorReference<SelfType> ClosureType;
			typedef const VectorReference<const SelfType> ConstClosureType;
			typedef Vector<T> VectorTemporaryType;

			UnitVector(): size(0), index(0) {}

			UnitVector(SizeType n, SizeType i): size(n), index(i) {}

			UnitVector(const UnitVector& v): size(v.size), index(v.index) {}
	
			ConstReference operator[](SizeType i) const {
				return this->operator()(i);
			}

			ConstReference operator()(SizeType i) const {
				CDPL_MATH_CHECK(i < getSize(), "Index out of range", Base::IndexError);

				return (i == index ? one : zero);
			}

			bool isEmpty() const {
				return (size == 0);
			}

			SizeType getSize() const {
				return size;
			}

			SizeType getIndex() const {
				return index;
			}

			SizeType getMaxSize() const {
				return std::numeric_limits<SizeType>::max();
			}
		
			UnitVector& operator=(const UnitVector& v) {
				if (this != &v) {
					size = v.size;
					index = v.index;
				}

				return *this;
			}

			void resize(SizeType n) {
				size = n;
			}

			void swap(UnitVector& v) {
				if (this != &v) {
					boost::swap(size, v.size);
					boost::swap(index, v.index);
				}
			}
	
			friend void swap(UnitVector& v1, UnitVector& v2) {
				v1.swap(v2);
			}

		private:
			SizeType               size;
			SizeType               index;
			static const ValueType zero;
			static const ValueType one;
		};

		template <typename T> const typename UnitVector<T>::ValueType UnitVector<T>::zero = UnitVector<T>::ValueType();
		template <typename T> const typename UnitVector<T>::ValueType UnitVector<T>::one  = UnitVector<T>::ValueType(1);

		template <typename T> 
		class ScalarVector : public VectorContainer<ScalarVector<T> >
		{

			typedef ScalarVector<T> SelfType;

		public:
			typedef T ValueType;
			typedef const T& Reference;
			typedef const T& ConstReference;
			typedef std::size_t SizeType;
			typedef std::ptrdiff_t DifferenceType;
			typedef VectorReference<SelfType> ClosureType;
			typedef const VectorReference<const SelfType> ConstClosureType;
			typedef Vector<T> VectorTemporaryType;

			ScalarVector(): size(0) {}

			ScalarVector(SizeType n, const ValueType& v = ValueType()): size(n), value(v) {}

			ScalarVector(const ScalarVector& v): size(v.size), value(v.value) {}
	
			ConstReference operator[](SizeType i) const {
				return this->operator()(i);
			}

			ConstReference operator()(SizeType i) const {
				CDPL_MATH_CHECK(i < getSize(), "Index out of range", Base::IndexError);
				return value;
			}

			bool isEmpty() const {
				return (size == 0);
			}

			SizeType getSize() const {
				return size;
			}

			SizeType getMaxSize() const {
				return std::numeric_limits<SizeType>::max();
			}
		
			ScalarVector& operator=(const ScalarVector& v) {
				if (this != &v) {
					size = v.size;
					value = v.value;
				}

				return *this;
			}

			void resize(SizeType n) {
				size = n;
			}

			void swap(ScalarVector& v) {
				if (this != &v) {
					boost::swap(size, v.size);
					boost::swap(value, v.value);
				}
			}
	
			friend void swap(ScalarVector& v1, ScalarVector& v2) {
				v1.swap(v2);
			}

		private:
			SizeType  size;
			ValueType value;
		};

		template <typename V>
		struct VectorTemporaryTraits<const VectorReference<V> > : public VectorTemporaryTraits<V> {};

		template <typename V>
		struct VectorTemporaryTraits<VectorReference<V> > : public VectorTemporaryTraits<V> {};

		template <typename T1, typename T2>
		CVector<typename CommonType<T1, T2>::Type, 2> 
		vec(const T1& t1, const T2& t2)
		{
			CVector<typename CommonType<T1, T2>::Type, 2> v;

			v(0) = t1;
			v(1) = t2;

			return v;
		}
		
		template <typename T1, typename T2, typename T3>
		CVector<typename CommonType<typename CommonType<T1, T2>::Type, T3>::Type, 3> 
		vec(const T1& t1, const T2& t2, const T3& t3)
		{
			CVector<typename CommonType<typename CommonType<T1, T2>::Type, T3>::Type, 3> v;

			v(0) = t1;
			v(1) = t2;
			v(2) = t3;

			return v;
		}

		template <typename T1, typename T2, typename T3, typename T4>
		CVector<typename CommonType<typename CommonType<typename CommonType<T1, T2>::Type, T3>::Type, T4>::Type, 4> 
		vec(const T1& t1, const T2& t2, const T3& t3, const T4& t4)
		{
			CVector<typename CommonType<typename CommonType<typename CommonType<T1, T2>::Type, T3>::Type, T4>::Type, 4> v;

			v(0) = t1;
			v(1) = t2;
			v(2) = t3;
			v(3) = t4;

			return v;
		}

		typedef ScalarVector<float> FScalarVector;
		typedef ScalarVector<double> DScalarVector;
		typedef ScalarVector<long> LScalarVector;
		typedef ScalarVector<unsigned long> ULScalarVector;

		typedef ZeroVector<float> FZeroVector;
		typedef ZeroVector<double> DZeroVector;
		typedef ZeroVector<long> LZeroVector;
		typedef ZeroVector<unsigned long> ULZeroVector;

		typedef UnitVector<float> FUnitVector;
		typedef UnitVector<double> DUnitVector;
		typedef UnitVector<long> LUnitVector;
		typedef UnitVector<unsigned long> ULUnitVector;

		/**
		 * \brief A bounded 2 element vector holding floating point values of type <tt>float</tt>.
		 */
		typedef CVector<float, 2> Vector2F;

		/**
		 * \brief A bounded 3 element vector holding floating point values of type <tt>float</tt>.
		 */
		typedef CVector<float, 3> Vector3F;

		/**
		 * \brief A bounded 4 element vector holding floating point values of type <tt>float</tt>.
		 */
		typedef CVector<float, 4> Vector4F;

		/**
		 * \brief A bounded 2 element vector holding floating point values of type <tt>double</tt>.
		 */
		typedef CVector<double, 2> Vector2D;

		/**
		 * \brief A bounded 3 element vector holding floating point values of type <tt>double</tt>.
		 */
		typedef CVector<double, 3> Vector3D;

		/**
		 * \brief A bounded 4 element vector holding floating point values of type <tt>double</tt>.
		 */
		typedef CVector<double, 4> Vector4D;

		/**
		 * \brief A bounded 2 element vector holding signed integers of type <tt>long</tt>.
		 */
		typedef CVector<long, 2> Vector2L;

		/**
		 * \brief A bounded 3 element vector holding signed integers of type <tt>long</tt>.
		 */
		typedef CVector<long, 3> Vector3L;

		/**
		 * \brief A bounded 4 element vector holding signed integers of type <tt>long</tt>.
		 */
		typedef CVector<long, 4> Vector4L;

		/**
		 * \brief A bounded 2 element vector holding unsigned integers of type <tt>unsigned long</tt>.
		 */
		typedef CVector<unsigned long, 2> Vector2UL;

		/**
		 * \brief A bounded 3 element vector holding unsigned integers of type <tt>unsigned long</tt>.
		 */
		typedef CVector<unsigned long, 3> Vector3UL;

		/**
		 * \brief A bounded 4 element vector holding unsigned integers of type <tt>unsigned long</tt>.
		 */
		typedef CVector<unsigned long, 4> Vector4UL;

		/**
		 * \brief An unbounded dense vector holding floating point values of type <tt>float</tt>.
		 */
		typedef Vector<float> FVector;

		/**
		 * \brief An unbounded dense vector holding floating point values of type <tt>double</tt>.
		 */
		typedef Vector<double> DVector;

		/**
		 * \brief An unbounded dense vector holding signed integers of type <tt>long</tt>.
		 */
		typedef Vector<long> LVector;

		/**
		 * \brief An unbounded dense vector holding unsigned integers of type <tt>unsigned long</tt>.
		 */
		typedef Vector<unsigned long> ULVector;

		/**
		 * \brief An unbounded sparse vector holding floating point values of type <tt>float</tt>.
		 */
		typedef SparseVector<float> SparseFVector;

		/**
		 * \brief An unbounded sparse vector holding floating point values of type <tt>double</tt>.
		 */
		typedef SparseVector<double> SparseDVector;

		/**
		 * \brief An unbounded sparse vector holding signed integers of type <tt>long</tt>.
		 */
		typedef SparseVector<long> SparseLVector;

		/**
		 * \brief An unbounded sparse vector holding unsigned integers of type <tt>unsigned long</tt>.
		 */
		typedef SparseVector<unsigned long> SparseULVector;
	}
}

#endif // CDPL_MATH_VECTOR_HPP
