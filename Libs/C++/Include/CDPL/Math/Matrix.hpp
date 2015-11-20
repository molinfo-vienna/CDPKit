/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * Matrix.hpp 
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
 * \brief Definition of matrix data types.
 */

#ifndef CDPL_MATH_MATRIX_HPP
#define CDPL_MATH_MATRIX_HPP

#include <cstddef>
#include <algorithm>
#include <vector>
#include <limits>

#include <boost/mpl/if.hpp>
#include <boost/type_traits/is_const.hpp>
#include <boost/utility.hpp>
#include <boost/swap.hpp>
#include <boost/shared_ptr.hpp>

#include "CDPL/Math/Config.hpp"
#include "CDPL/Math/Check.hpp"
#include "CDPL/Math/MatrixExpression.hpp"
#include "CDPL/Math/MatrixAssignment.hpp"
#include "CDPL/Math/DirectAssignmentProxy.hpp"
#include "CDPL/Math/Functional.hpp"
#include "CDPL/Math/TypeTraits.hpp"
#include "CDPL/Math/LUDecomposition.hpp"
#include "CDPL/Base/Exceptions.hpp"


namespace CDPL
{

	namespace Math
	{

		template <typename M> 
		class MatrixReference : public MatrixExpression<MatrixReference<M> >
		{

			typedef MatrixReference<M> SelfType;

		public:
			typedef M MatrixType;
			typedef typename M::ValueType ValueType;
			typedef typename boost::mpl::if_<boost::is_const<M>,
											 typename M::ConstReference,
											 typename M::Reference>::type Reference;
			typedef typename M::ConstReference ConstReference;
			typedef typename M::SizeType SizeType;
			typedef typename M::DifferenceType DifferenceType;
			typedef SelfType ClosureType;
			typedef const SelfType ConstClosureType;

			CDPL_MATH_INLINE explicit MatrixReference(MatrixType& m): data(m) {}

			CDPL_MATH_INLINE Reference operator()(SizeType i, SizeType j) {
				return data(i, j);
			}

			CDPL_MATH_INLINE ConstReference operator()(SizeType i, SizeType j) const {
				return data(i, j);
			}
	
			CDPL_MATH_INLINE SizeType getSize1() const {
				return data.getSize1();
			}

			CDPL_MATH_INLINE SizeType getSize2() const {
				return data.getSize2();
			}

			CDPL_MATH_INLINE SizeType getMaxSize() const {
				return data.getMaxSize();
			}
	
			CDPL_MATH_INLINE SizeType getMaxSize1() const {
				return data.getMaxSize1();
			}

			CDPL_MATH_INLINE SizeType getMaxSize2() const {
				return data.getMaxSize2();
			}
		
			CDPL_MATH_INLINE bool isEmpty() const {
				return data.isEmpty();
			}
	
			CDPL_MATH_INLINE const MatrixType& getData() const {
				return data;
			}

			CDPL_MATH_INLINE MatrixType& getData() {
				return data;
			}

			CDPL_MATH_INLINE MatrixReference& operator=(const MatrixReference& r) {
				data.operator=(r.data);
				return *this;
			}

			template <typename E>
			CDPL_MATH_INLINE MatrixReference& operator=(const MatrixExpression<E>& e) {
				data.operator=(e);
				return *this;
			}

			template <typename E>
			CDPL_MATH_INLINE MatrixReference& operator+=(const MatrixExpression<E>& e) {
				data.operator+=(e);
				return *this;
			}	

			template <typename E>
			CDPL_MATH_INLINE MatrixReference& operator-=(const MatrixExpression<E>& e) {
				data.operator-=(e);
				return *this;
			}

			template <typename T>
			CDPL_MATH_INLINE 
			typename boost::enable_if<IsScalar<T>, MatrixReference>::type& operator*=(const T& t) {
				data.operator*=(t);
				return *this;
			}
	
			template <typename T>
			CDPL_MATH_INLINE 
			typename boost::enable_if<IsScalar<T>, MatrixReference>::type& operator/=(const T& t) {
				data.operator/=(t);
				return *this;
			}
			
			template <typename E>
			CDPL_MATH_INLINE MatrixReference& assign(const MatrixExpression<E>& e) {
				data.assign(e);
				return *this;
			}

			template <typename E>
			CDPL_MATH_INLINE MatrixReference& plusAssign(const MatrixExpression<E>& e) {
				data.plusAssign(e);
				return *this;
			}

			template <typename E>
			CDPL_MATH_INLINE MatrixReference& minusAssign(const MatrixExpression<E>& e) {
				data.minusAssign(e);
				return *this;
			}

			CDPL_MATH_INLINE void swap(MatrixReference& r) {
				data.swap(r.data);
			}
	
			CDPL_MATH_INLINE friend void swap(MatrixReference& r1, MatrixReference& r2) {
				r1.swap(r2);
			}

		private:
			MatrixType& data;
		};

		template <typename T, typename A> class Vector;

		template <typename T, typename A = std::vector<T> > 
		class Matrix : public MatrixContainer<Matrix<T, A> >
		{

			typedef Matrix<T, A> SelfType;

		public:
			typedef T ValueType;
			typedef T& Reference;
			typedef const T& ConstReference;
			typedef typename A::size_type SizeType;
			typedef typename A::difference_type DifferenceType;
			typedef A ArrayType;
			typedef T* Pointer;
			typedef const T* ConstPointer;
			typedef MatrixReference<SelfType> ClosureType;
			typedef const MatrixReference<const SelfType> ConstClosureType;
			typedef SelfType MatrixTemporaryType;
			typedef Vector<T, A> VectorTemporaryType;
			typedef boost::shared_ptr<SelfType> SharedPointer;

			CDPL_MATH_INLINE Matrix(): size1(0), size2(0), data() {}

			CDPL_MATH_INLINE Matrix(SizeType m, SizeType n): 
				size1(m), size2(n), data(storageSize(m, n)) {}

			CDPL_MATH_INLINE Matrix(SizeType m, SizeType n, const ValueType& v):  
				size1(m), size2(n), data(storageSize(m, n), v) {}

			CDPL_MATH_INLINE Matrix(const Matrix& m): size1(m.size1), size2(m.size2), data(m.data) {}

			template <typename E>
			CDPL_MATH_INLINE Matrix(const MatrixExpression<E>& e): 
				size1(e().getSize1()), size2(e().getSize2()), data(storageSize(e().getSize1(), e().getSize2())) {
				matrixAssignMatrix<ScalarAssignment>(*this, e);
			}

			CDPL_MATH_INLINE Reference operator()(SizeType i, SizeType j) {
				CDPL_MATH_CHECK(i < getSize1() && j < getSize2(), "Index out of range", Base::IndexError);
				return data[i * getSize2() + j];
			}

			CDPL_MATH_INLINE ConstReference operator()(SizeType i, SizeType j) const {
				CDPL_MATH_CHECK(i < getSize1() && j < getSize2(), "Index out of range", Base::IndexError);
				return data[i * getSize2() + j];
			}

			CDPL_MATH_INLINE bool isEmpty() const {
				return data.empty();
			}

			CDPL_MATH_INLINE SizeType getSize1() const {
				return size1;
			}
	
			CDPL_MATH_INLINE SizeType getSize2() const {
				return size2;
			}

			CDPL_MATH_INLINE SizeType getMaxSize() const {
				return data.max_size();
			}

			CDPL_MATH_INLINE ArrayType& getData() {
				return data;
			}
			
			CDPL_MATH_INLINE const ArrayType& getData() const {
				return data;
			}

			CDPL_MATH_INLINE Matrix& operator=(const Matrix& m) {
				data = m.data;
				size1 = m.size1;
				size2 = m.size2;
				return *this;
			}

			template <typename C>
			CDPL_MATH_INLINE Matrix& operator=(const MatrixContainer<C>& c) {
				return assign(c);
			}

			template <typename E>
			CDPL_MATH_INLINE Matrix& operator=(const MatrixExpression<E>& e) {
				Matrix tmp(e);
				swap(tmp);

				return *this;
			}

			template <typename C>
			CDPL_MATH_INLINE Matrix& operator+=(const MatrixContainer<C>& c) {
				return plusAssign(c);
			}

			template <typename E>
			CDPL_MATH_INLINE Matrix& operator+=(const MatrixExpression<E>& e) {
				Matrix tmp(*this + e);
				swap(tmp);

				return *this;
			}	

			template <typename C>
			CDPL_MATH_INLINE Matrix& operator-=(const MatrixContainer<C>& c) {
				return minusAssign(c);
			}

			template <typename E>
			CDPL_MATH_INLINE Matrix& operator-=(const MatrixExpression<E>& e) {
				Matrix tmp(*this - e);
				swap(tmp);

				return *this;
			}

			template <typename T1>
			CDPL_MATH_INLINE 
			typename boost::enable_if<IsScalar<T1>, Matrix>::type& operator*=(const T1& t) {
				matrixAssignScalar<ScalarMultiplicationAssignment>(*this, t);
				return *this;
			}
	
			template <typename T1>
			CDPL_MATH_INLINE 
			typename boost::enable_if<IsScalar<T1>, Matrix>::type& operator/=(const T1& t) {
				matrixAssignScalar<ScalarDivisionAssignment>(*this, t);
				return *this;
			}
			
			template <typename E>
			CDPL_MATH_INLINE Matrix& assign(const MatrixExpression<E>& e) {
				resize(e().getSize1(), e().getSize2());
				matrixAssignMatrix<ScalarAssignment>(*this, e);
				return *this;
			}

			template <typename E>
			CDPL_MATH_INLINE Matrix& plusAssign(const MatrixExpression<E>& e) {
				matrixAssignMatrix<ScalarAdditionAssignment>(*this, e);
				return *this;
			}

			template <typename E>
			CDPL_MATH_INLINE Matrix& minusAssign(const MatrixExpression<E>& e) {
				matrixAssignMatrix<ScalarSubtractionAssignment>(*this, e);
				return *this;
			}

			CDPL_MATH_INLINE void swap(Matrix& m) {
				if (this != &m) {
					boost::swap(data, m.data);
					boost::swap(size1, m.size1);
					boost::swap(size2, m.size2);
				}
			}
	
			CDPL_MATH_INLINE friend void swap(Matrix& m1, Matrix& m2) {
				m1.swap(m2);
			}

			CDPL_MATH_INLINE void clear(const ValueType& v = ValueType()) {
				std::fill(data.begin(), data.end(), v);
			}

			CDPL_MATH_INLINE void resize(SizeType m, SizeType n, bool preserve = true, const ValueType& v = ValueType()) {
				if (preserve) {
					Matrix tmp(m, n, v);

					for (SizeType i = 0, min_size1 = std::min(size1, m); i < min_size1; i++)
						for (SizeType j = 0, min_size2 = std::min(size2, n); j < min_size2; j++)
							tmp(i, j) = (*this)(i, j);

					swap(tmp);

				} else {
					data.resize(storageSize(m, n), v);
					size1 = m;
					size2 = n;
				}
			}

		private:
			static CDPL_MATH_INLINE SizeType storageSize(SizeType m, SizeType n) {
				CDPL_MATH_CHECK(n == 0 || m <= std::numeric_limits<SizeType>::max() / n, "Maximum size exceeded", Base::SizeError);
				return (m * n);
			}

			SizeType  size1;
			SizeType  size2;
			ArrayType data;
		};

		template <typename T, std::size_t N> class BoundedVector;

		template <typename T, std::size_t M, std::size_t N> 
		class BoundedMatrix : public MatrixContainer<BoundedMatrix<T, M, N> >
		{

			typedef BoundedMatrix<T, M, N> SelfType;

		public:
			typedef T ValueType;
			typedef T& Reference;
			typedef const T& ConstReference;
			typedef std::size_t SizeType;
			typedef std::ptrdiff_t DifferenceType;
			typedef ValueType ArrayType[M][N];
			typedef T (*ArrayPointer)[N];
			typedef const T (*ConstArrayPointer)[N];
			typedef T* Pointer;
			typedef const T* ConstPointer;
			typedef MatrixReference<SelfType> ClosureType;
			typedef const MatrixReference<const SelfType> ConstClosureType;
			typedef SelfType MatrixTemporaryType;
			typedef BoundedVector<T, M * N> VectorTemporaryType;
			typedef boost::shared_ptr<SelfType> SharedPointer;

			static const SizeType MaxSize1 = M;
			static const SizeType MaxSize2 = N;

			CDPL_MATH_INLINE BoundedMatrix(): size1(0), size2(0) {}

			CDPL_MATH_INLINE BoundedMatrix(SizeType m, SizeType n): size1(0), size2(0) {
				resize(m, n);
			}

			CDPL_MATH_INLINE BoundedMatrix(SizeType m, SizeType n, const ValueType& v): size1(0), size2(0) {
				resize(m, n, v);
			}

			CDPL_MATH_INLINE BoundedMatrix(const BoundedMatrix& m): size1(m.size1), size2(m.size2) {
				for (SizeType i = 0; i < size1; i++)
					std::copy(m.data[i], m.data[i] + size2, data[i]);
			}

			template <typename E>
			CDPL_MATH_INLINE BoundedMatrix(const MatrixExpression<E>& e): size1(0), size2(0) {
				resize(e().getSize1(), e().getSize2());
				matrixAssignMatrix<ScalarAssignment>(*this, e);
			}


			CDPL_MATH_INLINE Reference operator()(SizeType i, SizeType j) {
				CDPL_MATH_CHECK(i < getSize1() && j < getSize2(), "Index out of range", Base::IndexError);
				return data[i][j];
			}

			CDPL_MATH_INLINE ConstReference operator()(SizeType i, SizeType j) const {
				CDPL_MATH_CHECK(i < getSize1() && j < getSize2(), "Index out of range", Base::IndexError);
				return data[i][j];
			}

			CDPL_MATH_INLINE bool isEmpty() const {
				return (size1 == 0 || size2 == 0);
			}

			CDPL_MATH_INLINE SizeType getSize1() const {
				return size1;
			}
	
			CDPL_MATH_INLINE SizeType getSize2() const {
				return size2;
			}

			CDPL_MATH_INLINE SizeType getMaxSize1() const {
				return M;
			}
	
			CDPL_MATH_INLINE SizeType getMaxSize2() const {
				return N;
			}

			CDPL_MATH_INLINE ArrayPointer getData() {
				return data;
			}
			
			CDPL_MATH_INLINE ConstArrayPointer getData() const {
				return data;
			}

			CDPL_MATH_INLINE BoundedMatrix& operator=(const BoundedMatrix& m) {
				if (this != &m) {
					for (SizeType i = 0; i < m.size1; i++)
						std::copy(m.data[i], m.data[i] + m.size2, data[i]);

					size1 = m.size1;
					size2 = m.size2;
				}

				return *this;
			}

			template <typename C>
			CDPL_MATH_INLINE BoundedMatrix& operator=(const MatrixContainer<C>& c) {
				return assign(c);
			}

			template <typename E>
			CDPL_MATH_INLINE BoundedMatrix& operator=(const MatrixExpression<E>& e) {
				BoundedMatrix tmp(e);

				return this->operator=(tmp);
			}

			template <typename C>
			CDPL_MATH_INLINE BoundedMatrix& operator+=(const MatrixContainer<C>& c) {
				return plusAssign(c);
			}

			template <typename E>
			CDPL_MATH_INLINE BoundedMatrix& operator+=(const MatrixExpression<E>& e) {
				BoundedMatrix tmp(*this + e);

				return this->operator=(tmp);
			}	

			template <typename C>
			CDPL_MATH_INLINE BoundedMatrix& operator-=(const MatrixContainer<C>& c) {
				return minusAssign(c);
			}

			template <typename E>
			CDPL_MATH_INLINE BoundedMatrix& operator-=(const MatrixExpression<E>& e) {
				BoundedMatrix tmp(*this - e);

				return this->operator=(tmp);
			}

			template <typename T1>
			CDPL_MATH_INLINE 
			typename boost::enable_if<IsScalar<T1>, BoundedMatrix>::type& operator*=(const T1& v) {
				matrixAssignScalar<ScalarMultiplicationAssignment>(*this, v);
				return *this;
			}
	
			template <typename T1>
			CDPL_MATH_INLINE 
			typename boost::enable_if<IsScalar<T1>, BoundedMatrix>::type& operator/=(const T1& v) {
				matrixAssignScalar<ScalarDivisionAssignment>(*this, v);
				return *this;
			}
			
			template <typename E>
			CDPL_MATH_INLINE BoundedMatrix& assign(const MatrixExpression<E>& e) {
				resize(e().getSize1(), e().getSize2());
				matrixAssignMatrix<ScalarAssignment>(*this, e);
				return *this;
			}

			template <typename E>
			CDPL_MATH_INLINE BoundedMatrix& plusAssign(const MatrixExpression<E>& e) {
				matrixAssignMatrix<ScalarAdditionAssignment>(*this, e);
				return *this;
			}

			template <typename E>
			CDPL_MATH_INLINE BoundedMatrix& minusAssign(const MatrixExpression<E>& e) {
				matrixAssignMatrix<ScalarSubtractionAssignment>(*this, e);
				return *this;
			}

			CDPL_MATH_INLINE void swap(BoundedMatrix& m) {
				if (this != &m) {
					SizeType max_size1 = std::max(size1, m.size1);
					SizeType max_size2 = std::max(size2, m.size2);

					for (SizeType i = 0; i < max_size1; i++)
						std::swap_ranges(data[i], data[i] + max_size2, m.data[i]);

					boost::swap(size1, m.size1);
					boost::swap(size2, m.size2);
				}
			}
	
			CDPL_MATH_INLINE friend void swap(BoundedMatrix& m1, BoundedMatrix& m2) {
				m1.swap(m2);
			}

			CDPL_MATH_INLINE void clear(const ValueType& v = ValueType()) {
				for (SizeType i = 0; i < size1; i++)
					std::fill(data[i], data[i] + size2, v);
			}

			CDPL_MATH_INLINE void resize(SizeType m, SizeType n) {
				CDPL_MATH_CHECK(m <= getMaxSize1() && n <= getMaxSize2(), "Maximum size exceeded", Base::RangeError);
				size1 = m;
				size2 = n;
			}

			CDPL_MATH_INLINE void resize(SizeType m, SizeType n, const ValueType& v) {
				CDPL_MATH_CHECK(m <= getMaxSize1() && n <= getMaxSize2(), "Maximum size exceeded", Base::RangeError);
				
				if (n > size2) {
					SizeType min_size1 = std::min(size1, m);

					for (SizeType i = 0; i < min_size1; i++)
						std::fill(data[i] + size2, data[i] + n, v);
				}

				if (m > size1)
					for (SizeType i = size1; i < m; i++)
						std::fill(data[i], data[i] + n, v);

				size1 = m;
				size2 = n;
			}

		private:
			SizeType  size1;
			SizeType  size2;
			ArrayType data;
		};

		template <typename T, std::size_t M, std::size_t N> const typename BoundedMatrix<T, M, N>::SizeType BoundedMatrix<T, M, N>::MaxSize1;
		template <typename T, std::size_t M, std::size_t N> const typename BoundedMatrix<T, M, N>::SizeType BoundedMatrix<T, M, N>::MaxSize2;

		template <typename T, std::size_t M, std::size_t N> 
		class CMatrix : public MatrixContainer<CMatrix<T, M, N> >
		{

			typedef CMatrix<T, M, N> SelfType;

		public:
			typedef T ValueType;
			typedef T& Reference;
			typedef const T& ConstReference;
			typedef std::size_t SizeType;
			typedef std::ptrdiff_t DifferenceType;
			typedef ValueType ArrayType[M][N];
			typedef T (*ArrayPointer)[N];
			typedef const T (*ConstArrayPointer)[N];
			typedef T* Pointer;
			typedef const T* ConstPointer;
			typedef MatrixReference<SelfType> ClosureType;
			typedef const MatrixReference<const SelfType> ConstClosureType;
			typedef BoundedMatrix<T, M, N> MatrixTemporaryType;
			typedef BoundedVector<T, M * N> VectorTemporaryType;
			typedef boost::shared_ptr<SelfType> SharedPointer;

			static const SizeType Size1 = M;
			static const SizeType Size2 = N;

			CDPL_MATH_INLINE CMatrix() {
				for (SizeType i = 0; i < M; i++)
					std::fill(data[i], data[i] + N, ValueType());
			}

			CDPL_MATH_INLINE explicit CMatrix(const ValueType& v) {
				for (SizeType i = 0; i < M; i++)
					std::fill(data[i], data[i] + N, v);
			}

			CDPL_MATH_INLINE CMatrix(const CMatrix& m) {
				for (SizeType i = 0; i < M; i++)
					std::copy(m.data[i], m.data[i] + N, data[i]);
			}

			template <typename E>
			CDPL_MATH_INLINE CMatrix(const MatrixExpression<E>& e) {
				matrixAssignMatrix<ScalarAssignment>(*this, e);
			}

			CDPL_MATH_INLINE Reference operator()(SizeType i, SizeType j) {
				CDPL_MATH_CHECK(i < getSize1() && j < getSize2(), "Index out of range", Base::IndexError);
				return data[i][j];
			}

			CDPL_MATH_INLINE ConstReference operator()(SizeType i, SizeType j) const {
				CDPL_MATH_CHECK(i < getSize1() && j < getSize2(), "Index out of range", Base::IndexError);
				return data[i][j];
			}

			CDPL_MATH_INLINE bool isEmpty() const {
				return (M == 0 || N == 0);
			}

			CDPL_MATH_INLINE SizeType getSize1() const {
				return M;
			}
	
			CDPL_MATH_INLINE SizeType getSize2() const {
				return N;
			}

			CDPL_MATH_INLINE SizeType getMaxSize1() const {
				return M;
			}
	
			CDPL_MATH_INLINE SizeType getMaxSize2() const {
				return N;
			}

			CDPL_MATH_INLINE ArrayPointer getData() {
				return data;
			}
			
			CDPL_MATH_INLINE ConstArrayPointer getData() const {
				return data;
			}

			CDPL_MATH_INLINE CMatrix& operator=(const CMatrix& m) {
				if (this != &m) {
					for (SizeType i = 0; i < M; i++)
						std::copy(m.data[i], m.data[i] + N, data[i]);
				}

				return *this;
			}

			template <typename C>
			CDPL_MATH_INLINE CMatrix& operator=(const MatrixContainer<C>& c) {
				return assign(c);
			}

			template <typename E>
			CDPL_MATH_INLINE CMatrix& operator=(const MatrixExpression<E>& e) {
				CMatrix tmp(e);

				return this->operator=(tmp);
			}

			template <typename C>
			CDPL_MATH_INLINE CMatrix& operator+=(const MatrixContainer<C>& c) {
				return plusAssign(c);
			}

			template <typename E>
			CDPL_MATH_INLINE CMatrix& operator+=(const MatrixExpression<E>& e) {
				CMatrix tmp(*this + e);

				return this->operator=(tmp);
			}	

			template <typename C>
			CDPL_MATH_INLINE CMatrix& operator-=(const MatrixContainer<C>& c) {
				return minusAssign(c);
			}

			template <typename E>
			CDPL_MATH_INLINE CMatrix& operator-=(const MatrixExpression<E>& e) {
				CMatrix tmp(*this - e);

				return this->operator=(tmp);
			}

			template <typename T1>
			CDPL_MATH_INLINE 
			typename boost::enable_if<IsScalar<T1>, CMatrix>::type& operator*=(const T1& t) {
				matrixAssignScalar<ScalarMultiplicationAssignment>(*this, t);
				return *this;
			}
	
			template <typename T1>
			CDPL_MATH_INLINE 
			typename boost::enable_if<IsScalar<T1>, CMatrix>::type& operator/=(const T1& t) {
				matrixAssignScalar<ScalarDivisionAssignment>(*this, t);
				return *this;
			}
			
			template <typename E>
			CDPL_MATH_INLINE CMatrix& assign(const MatrixExpression<E>& e) {
				matrixAssignMatrix<ScalarAssignment>(*this, e);
				return *this;
			}

			template <typename E>
			CDPL_MATH_INLINE CMatrix& plusAssign(const MatrixExpression<E>& e) {
				matrixAssignMatrix<ScalarAdditionAssignment>(*this, e);
				return *this;
			}

			template <typename E>
			CDPL_MATH_INLINE CMatrix& minusAssign(const MatrixExpression<E>& e) {
				matrixAssignMatrix<ScalarSubtractionAssignment>(*this, e);
				return *this;
			}

			CDPL_MATH_INLINE void swap(CMatrix& m) {
				if (this != &m) {
					for (SizeType i = 0; i < M; i++)
						std::swap_ranges(data[i], data[i] + N, m.data[i]);
				}
			}
	
			CDPL_MATH_INLINE friend void swap(CMatrix& m1, CMatrix& m2) {
				m1.swap(m2);
			}

			CDPL_MATH_INLINE void clear(const ValueType& v = ValueType()) {
				for (SizeType i = 0; i < M; i++)
					std::fill(data[i], data[i] + N, v);
			}

		private:
			ArrayType data;
		};

		template <typename T, std::size_t M, std::size_t N> const typename CMatrix<T, M, N>::SizeType CMatrix<T, M, N>::Size1;
		template <typename T, std::size_t M, std::size_t N> const typename CMatrix<T, M, N>::SizeType CMatrix<T, M, N>::Size2;

		template <typename T> 
		class ZeroMatrix : public MatrixContainer<ZeroMatrix<T> >
		{

			typedef ZeroMatrix<T> SelfType;

		public:
			typedef T ValueType;
			typedef const T& Reference;
			typedef const T& ConstReference;
			typedef std::size_t SizeType;
			typedef std::ptrdiff_t DifferenceType;
			typedef MatrixReference<SelfType> ClosureType;
			typedef const MatrixReference<const SelfType> ConstClosureType;
			typedef Matrix<T> MatrixTemporaryType;
			typedef Vector<T, std::vector<T> > VectorTemporaryType;

			CDPL_MATH_INLINE ZeroMatrix(): size1(0), size2(0) {}

			CDPL_MATH_INLINE ZeroMatrix(SizeType m, SizeType n): size1(m), size2(n) {}

			CDPL_MATH_INLINE ZeroMatrix(const ZeroMatrix& m): size1(m.size1), size2(m.size2) {}
		
			CDPL_MATH_INLINE ConstReference operator()(SizeType i, SizeType j) const {
				CDPL_MATH_CHECK(i < getSize1() && j < getSize2(), "Index out of range", Base::IndexError);
				return zero;
			}

			CDPL_MATH_INLINE bool isEmpty() const {
				return (size1 == 0 || size2 == 0);
			}

			CDPL_MATH_INLINE SizeType getSize1() const {
				return size1;
			}
	
			CDPL_MATH_INLINE SizeType getSize2() const {
				return size2;
			}

			CDPL_MATH_INLINE SizeType getMaxSize1() const {
				return std::numeric_limits<SizeType>::max();
			}
	
			CDPL_MATH_INLINE SizeType getMaxSize2() const {
				return std::numeric_limits<SizeType>::max();
			}

			CDPL_MATH_INLINE ZeroMatrix& operator=(const ZeroMatrix& m) {
				if (this != &m) {
					size1 = m.size1;
					size2 = m.size2;
				}

				return *this;
			}

			CDPL_MATH_INLINE void swap(ZeroMatrix& m) {
				if (this != &m) {
					boost::swap(size1, m.size1);
					boost::swap(size2, m.size2);
				}
			}
	
			CDPL_MATH_INLINE friend void swap(ZeroMatrix& m1, ZeroMatrix& m2) {
				m1.swap(m2);
			}

			CDPL_MATH_INLINE void resize(SizeType m, SizeType n) {
				size1 = m;
				size2 = n;
			}

		private:
			SizeType               size1;
			SizeType               size2;
			static const ValueType zero;
		};

		template <typename T> const typename ZeroMatrix<T>::ValueType ZeroMatrix<T>::zero = ZeroMatrix<T>::ValueType();

		template <typename T> 
		class ScalarMatrix : public MatrixContainer<ScalarMatrix<T> >
		{

			typedef ScalarMatrix<T> SelfType;

		public:
			typedef T ValueType;
			typedef const T& Reference;
			typedef const T& ConstReference;
			typedef std::size_t SizeType;
			typedef std::ptrdiff_t DifferenceType;
			typedef MatrixReference<SelfType> ClosureType;
			typedef const MatrixReference<const SelfType> ConstClosureType;
			typedef Matrix<T> MatrixTemporaryType;
			typedef Vector<T, std::vector<T> > VectorTemporaryType;

			CDPL_MATH_INLINE ScalarMatrix(): size1(0), size2(0), value() {}

			CDPL_MATH_INLINE ScalarMatrix(SizeType m, SizeType n, const ValueType& v = ValueType()): size1(m), size2(n), value(v) {}

			CDPL_MATH_INLINE ScalarMatrix(const ScalarMatrix& m): size1(m.size1), size2(m.size2), value(m.value) {}
		
			CDPL_MATH_INLINE ConstReference operator()(SizeType i, SizeType j) const {
				CDPL_MATH_CHECK(i < getSize1() && j < getSize2(), "Index out of range", Base::IndexError);
				return value;
			}

			CDPL_MATH_INLINE bool isEmpty() const {
				return (size1 == 0 || size2 == 0);
			}

			CDPL_MATH_INLINE SizeType getSize1() const {
				return size1;
			}
	
			CDPL_MATH_INLINE SizeType getSize2() const {
				return size2;
			}

			CDPL_MATH_INLINE SizeType getMaxSize1() const {
				return std::numeric_limits<SizeType>::max();
			}
	
			CDPL_MATH_INLINE SizeType getMaxSize2() const {
				return std::numeric_limits<SizeType>::max();
			}

			CDPL_MATH_INLINE ScalarMatrix& operator=(const ScalarMatrix& m) {
				if (this != &m) {
					size1 = m.size1;
					size2 = m.size2;
					value = m.value;
				}

				return *this;
			}

			CDPL_MATH_INLINE void swap(ScalarMatrix& m) {
				if (this != &m) {
					boost::swap(size1, m.size1);
					boost::swap(size2, m.size2);
					boost::swap(value, m.value);
				}
			}
	
			CDPL_MATH_INLINE friend void swap(ScalarMatrix& m1, ScalarMatrix& m2) {
				m1.swap(m2);
			}

			CDPL_MATH_INLINE void resize(SizeType m, SizeType n) {
				size1 = m;
				size2 = n;
			}

		private:
			SizeType  size1;
			SizeType  size2;
			ValueType value;
		};

		template <typename T> 
		class IdentityMatrix : public MatrixContainer<IdentityMatrix<T> >
		{

			typedef IdentityMatrix<T> SelfType;

		public:
			typedef T ValueType;
			typedef const T& Reference;
			typedef const T& ConstReference;
			typedef std::size_t SizeType;
			typedef std::ptrdiff_t DifferenceType;
			typedef MatrixReference<SelfType> ClosureType;
			typedef const MatrixReference<const SelfType> ConstClosureType;
			typedef Matrix<T> MatrixTemporaryType;
			typedef Vector<T, std::vector<T> > VectorTemporaryType;
	
			CDPL_MATH_INLINE IdentityMatrix(): size1(0), size2(0) {}

			CDPL_MATH_INLINE IdentityMatrix(SizeType m, SizeType n): size1(m), size2(n) {}

			CDPL_MATH_INLINE IdentityMatrix(const IdentityMatrix& m): size1(m.size1), size2(m.size2) {}
		
			CDPL_MATH_INLINE ConstReference operator()(SizeType i, SizeType j) const {
				CDPL_MATH_CHECK(i < getSize1() && j < getSize2(), "Index out of range", Base::IndexError);
				return (i == j ? one : zero);
			}

			CDPL_MATH_INLINE bool isEmpty() const {
				return (size1 == 0 || size2 == 0);
			}

			CDPL_MATH_INLINE SizeType getSize1() const {
				return size1;
			}
	
			CDPL_MATH_INLINE SizeType getSize2() const {
				return size2;
			}

			CDPL_MATH_INLINE SizeType getMaxSize1() const {
				return std::numeric_limits<SizeType>::max();
			}
	
			CDPL_MATH_INLINE SizeType getMaxSize2() const {
				return std::numeric_limits<SizeType>::max();
			}

			CDPL_MATH_INLINE IdentityMatrix& operator=(const IdentityMatrix& m) {
				if (this != &m) {
					size1 = m.size1;
					size2 = m.size2;
				}

				return *this;
			}

			CDPL_MATH_INLINE void swap(IdentityMatrix& m) {
				if (this != &m) {
					boost::swap(size1, m.size1);
					boost::swap(size2, m.size2);
				}
			}
	
			CDPL_MATH_INLINE friend void swap(IdentityMatrix& m1, IdentityMatrix& m2) {
				m1.swap(m2);
			}

			CDPL_MATH_INLINE void resize(SizeType m, SizeType n) {
				size1 = m;
				size2 = n;
			}

		private:
			SizeType               size1;
			SizeType               size2;
			static const ValueType zero;
			static const ValueType one;
		};

		template <typename T> const typename IdentityMatrix<T>::ValueType IdentityMatrix<T>::zero = IdentityMatrix<T>::ValueType();
		template <typename T> const typename IdentityMatrix<T>::ValueType IdentityMatrix<T>::one  = IdentityMatrix<T>::ValueType(1);

		template <typename M>
		struct VectorTemporaryTraits<MatrixReference<M> > : public VectorTemporaryTraits<M> {};

		template <typename M>
		struct VectorTemporaryTraits<const MatrixReference<M> > : public VectorTemporaryTraits<M> {};

		template <typename M>
		struct MatrixTemporaryTraits<MatrixReference<M> > : public MatrixTemporaryTraits<M> {};

		template <typename M>
		struct MatrixTemporaryTraits<const MatrixReference<M> > : public MatrixTemporaryTraits<M> {};

		template <typename E>
		CDPL_MATH_INLINE
		typename E::ValueType
		det(const MatrixExpression<E>& e)
		{
			typedef typename E::ValueType ValueType;
			typedef typename Matrix<ValueType>::SizeType SizeType;

			Matrix<ValueType> lu(e);
			std::vector<SizeType> pv(lu.getSize1());
			std::size_t num_row_swaps;
		
			luDecompose(lu, pv, num_row_swaps);

			ValueType res(1);
			SizeType size = std::min(lu.getSize1(), lu.getSize2());

			for (SizeType i = 0; i < size; i++)
				res *= lu(i, i);

			return (num_row_swaps % 2 == 0 ? res : -res);
		}

		template <typename C>
		CDPL_MATH_INLINE
		typename C::ValueType
		det(const MatrixContainer<C>& c)
		{
			typedef typename C::ValueType ValueType;
			typedef typename MatrixTemporaryTraits<C>::Type CTemporaryType;
			typedef typename CTemporaryType::SizeType SizeType;

			CTemporaryType lu(c);
			std::vector<SizeType> pv(lu.getSize1());
			std::size_t num_row_swaps;
		
			luDecompose(lu, pv, num_row_swaps);

			ValueType res(1);
			SizeType size = std::min(lu.getSize1(), lu.getSize2());

			for (SizeType i = 0; i < size; i++)
				res *= lu(i, i);
			
			return (num_row_swaps % 2 == 0 ? res : -res);
		}

		template <typename E, typename C>
		CDPL_MATH_INLINE
		bool
		invert(const MatrixExpression<E>& e, MatrixContainer<C>& c)
		{
			typedef typename C::ValueType ValueType;
			typedef typename MatrixTemporaryTraits<C>::Type CTemporaryType;
			typedef typename CTemporaryType::SizeType SizeType;

			CTemporaryType lu(e);
			std::vector<SizeType> pv(lu.getSize1());
			std::size_t num_row_swaps;
		
			if (luDecompose(lu, pv, num_row_swaps) > 0)
				return false;

			c().assign(IdentityMatrix<ValueType>(lu.getSize1(), lu.getSize2()));

			return luSubstitute(lu, pv, c);
		}

		template <typename C>
		CDPL_MATH_INLINE
		bool
		invert(MatrixContainer<C>& c)
		{
			return invert(c, c);
		}

		typedef ZeroMatrix<float> FZeroMatrix;
		typedef ZeroMatrix<double> DZeroMatrix;
		typedef ZeroMatrix<long> LZeroMatrix;
		typedef ZeroMatrix<unsigned long> ULZeroMatrix;

		typedef ScalarMatrix<float> FScalarMatrix;
		typedef ScalarMatrix<double> DScalarMatrix;
		typedef ScalarMatrix<long> LScalarMatrix;
		typedef ScalarMatrix<unsigned long> ULScalarMatrix;

		typedef IdentityMatrix<float> FIdentityMatrix;
		typedef IdentityMatrix<double> DIdentityMatrix;
		typedef IdentityMatrix<long> LIdentityMatrix;
		typedef IdentityMatrix<unsigned long> ULIdentityMatrix;

		/**
		 * \brief An unbounded dense matrix holding floating point values of type <tt>float</tt>..
		 */
		typedef Matrix<float> FMatrix;

		/**
		 * \brief An unbounded dense matrix holding floating point values of type <tt>double</tt>..
		 */
		typedef Matrix<double> DMatrix;

		/**
		 * \brief An unbounded dense matrix holding signed integers of type <tt>long</tt>.
		 */
		typedef Matrix<long> LMatrix;

		/**
		 * \brief An unbounded dense matrix holding unsigned integers of type <tt>unsigned long</tt>.
		 */
		typedef Matrix<unsigned long> ULMatrix;

		/**
		 * \brief A bounded 2x2 matrix holding floating point values of type <tt>float</tt>.
		 */
		typedef CMatrix<float, 2, 2> Matrix2F;

		/**
		 * \brief A bounded 3x3 matrix holding floating point values of type <tt>float</tt>.
		 */
		typedef CMatrix<float, 3, 3> Matrix3F;

		/**
		 * \brief A bounded 4x4 matrix holding floating point values of type <tt>float</tt>.
		 */
		typedef CMatrix<float, 4, 4> Matrix4F;
		
		/**
		 * \brief A bounded 2x2 matrix holding floating point values of type <tt>double</tt>.
		 */
		typedef CMatrix<double, 2, 2> Matrix2D;

		/**
		 * \brief A bounded 3x3 matrix holding floating point values of type <tt>double</tt>.
		 */
		typedef CMatrix<double, 3, 3> Matrix3D;

		/**
		 * \brief A bounded 4x4 matrix holding floating point values of type <tt>double</tt>.
		 */
		typedef CMatrix<double, 4, 4> Matrix4D;
	
		/**
		 * \brief A bounded 2x2 matrix holding signed integers of type <tt>long</tt>.
		 */
		typedef CMatrix<long, 2, 2> Matrix2L;

		/**
		 * \brief A bounded 3x3 matrix holding signed integers of type <tt>long</tt>.
		 */
		typedef CMatrix<long, 3, 3> Matrix3L;

		/**
		 * \brief A bounded 4x4 matrix holding signed integers of type <tt>long</tt>.
		 */
		typedef CMatrix<long, 4, 4> Matrix4L;

		/**
		 * \brief A bounded 2x2 matrix holding unsigned integers of type <tt>unsigned long</tt>.
		 */
		typedef CMatrix<unsigned long, 2, 2> Matrix2UL;

		/**
		 * \brief A bounded 3x3 matrix holding unsigned integers of type <tt>unsigned long</tt>.
		 */
		typedef CMatrix<unsigned long, 3, 3> Matrix3UL;

		/**
		 * \brief A bounded 4x4 matrix holding unsigned integers of type <tt>unsigned long</tt>.
		 */
		typedef CMatrix<unsigned long, 4, 4> Matrix4UL;
	}
}

#endif // CDPL_MATH_MATRIX_HPP
