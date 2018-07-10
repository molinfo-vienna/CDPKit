/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * AffineTransform.hpp 
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
 * \brief Matrix types for various affine transformations.
 */

#ifndef CDPL_MATH_AFFINETRANSFORM_HPP
#define CDPL_MATH_AFFINETRANSFORM_HPP

#include <algorithm>
#include <cmath>
#include <limits>
#include <cstddef>
#include <vector>

#include <boost/swap.hpp>

#include "CDPL/Math/Check.hpp"
#include "CDPL/Math/Expression.hpp"
#include "CDPL/Base/Exceptions.hpp"


namespace CDPL
{

	namespace Math
	{

		template <typename V> class MatrixReference;
		template <typename T, typename A> class Vector;
		template <typename T, typename A> class Matrix;

		template <typename T> 
		class RotationMatrix : public MatrixContainer<RotationMatrix<T> >
		{

			typedef RotationMatrix<T> SelfType;

		public:
			typedef T ValueType;
			typedef const T Reference;
			typedef const T ConstReference;
			typedef std::size_t SizeType;
			typedef std::ptrdiff_t DifferenceType;
			typedef MatrixReference<SelfType> ClosureType;
			typedef const MatrixReference<const SelfType> ConstClosureType;
			typedef Matrix<T, std::vector<T> > MatrixTemporaryType;
			typedef Vector<T, std::vector<T> > VectorTemporaryType;
	
			template <typename E>
			RotationMatrix(SizeType n, const QuaternionExpression<E>& q): size(n) {
				set(q);
			}

			template <typename T1, typename T2, typename T3, typename T4>
			RotationMatrix(SizeType n, const T1& w, const T2& ux, const T3& uy, const T4& uz): size(n) {
				set(w, ux, uy, uz);
			}

			RotationMatrix(const RotationMatrix& m): size(m.size) {
				std::copy(m.data, m.data + 4, data);
			}

			template <typename E>
			void set(const QuaternionExpression<E>& q) {
				data[0] = q().getC1();
				data[1] = q().getC2();
				data[2] = q().getC3();
				data[3] = q().getC4();
			}

			template <typename T1, typename T2, typename T3, typename T4>
			void set(const T1& w, const T2& ux, const T3& uy, const T4& uz) {
				data[0] = std::cos(w / 2.0);
				data[1] = std::sin(w / 2.0) * ux;
				data[2] = std::sin(w / 2.0) * uy;
				data[3] = std::sin(w / 2.0) * uz;
			}

			ConstReference operator()(SizeType i, SizeType j) const {
				CDPL_MATH_CHECK(i < getSize1() && j < getSize2(), "Index out of range", Base::IndexError);
				
				if (i >= 3 || i >= size || j >= 3 || j >= size)
					return (i == j ? ValueType(1) : ValueType());

				switch (i) {

					case 0:
						switch (j) {
				
							case 0:
								// a2 + b2 - c2 - d2
								return (data[0] * data[0] + data[1] * data[1] - data[2] * data[2] - data[3] * data[3]);

							case 1:
								// 2(bc - ad)
								return 2 * (data[1] * data[2] - data[0] * data[3]);

							case 2:
								// 2(bd + ac)
								return 2 * (data[1] * data[3] + data[0] * data[2]);

							default:
								return ValueType();
						}

					case 1:
						switch (j) {
				
							case 0:
								// 2(bc + ad)
								return 2 * (data[1] * data[2] + data[0] * data[3]);

							case 1:
								// a2 - b2 + c2 - d2
								return (data[0] * data[0] - data[1] * data[1] + data[2] * data[2] - data[3] * data[3]);

							case 2:
								// 2(cd - ab)
								return 2 * (data[2] * data[3] - data[0] * data[1]);

							default:
								return ValueType();
						}

					case 2:
						switch (j) {
				
							case 0:
								// 2(bd - ac)
								return 2 * (data[1] * data[3] - data[0] * data[2]);

							case 1:
								// 2(cd + ab)
								return 2 * (data[2] * data[3] + data[0] * data[1]);

							case 2:
								// a2 - b2 - c2 + d2
								return (data[0] * data[0] - data[1] * data[1] - data[2] * data[2] + data[3] * data[3]);

							default:
								return ValueType();
						}

					default:
						return (i == j ? ValueType(1) : ValueType());
				}
			}

			bool isEmpty() const {
				return (size == 0);
			}

			SizeType getSize1() const {
				return size;
			}
	
			SizeType getSize2() const {
				return size;
			}

			SizeType getMaxSize1() const {
				return std::numeric_limits<SizeType>::max();
			}

			SizeType getMaxSize2() const {
				return std::numeric_limits<SizeType>::max();
			}

			RotationMatrix& operator=(const RotationMatrix& m) {
				if (this != &m) {
					std::copy(m.data, m.data + 4, data);
					size = m.size;
				}

				return *this;
			}

			void swap(RotationMatrix& m) {
				if (this != &m) {
					std::swap_ranges(data, data + 4, m.data);
					boost::swap(size, m.size);
				}
			}
	
			friend void swap(RotationMatrix& m1, RotationMatrix& m2) {
				m1.swap(m2);
			}

			void resize(SizeType n) {
				size = n;
			}

		private:
			typedef ValueType ArrayType[4];

			SizeType  size;
			ArrayType data;
		};

		template <typename T> 
		class ScalingMatrix : public MatrixContainer<ScalingMatrix<T> >
		{

			typedef ScalingMatrix<T> SelfType;

		public:
			typedef T ValueType;
			typedef const T Reference;
			typedef const T ConstReference;
			typedef std::size_t SizeType;
			typedef std::ptrdiff_t DifferenceType;
			typedef MatrixReference<SelfType> ClosureType;
			typedef const MatrixReference<const SelfType> ConstClosureType;
			typedef Matrix<T, std::vector<T> > MatrixTemporaryType;
			typedef Vector<T, std::vector<T> > VectorTemporaryType;
	
			explicit ScalingMatrix(SizeType n, const ValueType& sx = ValueType(1), 
												   const ValueType& sy = ValueType(1), const ValueType& sz = ValueType(1)): size(n) {
				set(sx, sy, sz);
			}

			ScalingMatrix(const ScalingMatrix& m): size(m.size) {
				std::copy(m.data, m.data + 3, data);
			}

			void set(const ValueType& sx = ValueType(1), const ValueType& sy = ValueType(1), 
									 const ValueType& sz = ValueType(1)) {
				data[0] = sx;
				data[1] = sy;
				data[2] = sz;
			}

			ConstReference operator()(SizeType i, SizeType j) const {
				CDPL_MATH_CHECK(i < getSize1() && j < getSize2(), "Index out of range", Base::IndexError);

				if (i != j)
					return ValueType();
				
				if (i < size && i < 3)
					return data[i];

				return ValueType(1);
			}

			bool isEmpty() const {
				return (size == 0);
			}

			SizeType getSize1() const {
				return size;
			}
	
			SizeType getSize2() const {
				return size;
			}

			SizeType getMaxSize1() const {
				return std::numeric_limits<SizeType>::max();
			}

			SizeType getMaxSize2() const {
				return std::numeric_limits<SizeType>::max();
			}

			ScalingMatrix& operator=(const ScalingMatrix& m) {
				if (this != &m) {
					std::copy(m.data, m.data + 3, data);
					size = m.size;
				}

				return *this;
			}

			void swap(ScalingMatrix& m) {
				if (this != &m) {
					std::swap_ranges(data, data + 3, m.data);
					boost::swap(size, m.size);
				}
			}
	
			friend void swap(ScalingMatrix& m1, ScalingMatrix& m2) {
				m1.swap(m2);
			}

			void resize(SizeType n) {
				size = n;
			}

		private:
			typedef ValueType ArrayType[3];

			SizeType  size;
			ArrayType data;
		};
	
		template <typename T> 
		class TranslationMatrix : public MatrixContainer<TranslationMatrix<T> >
		{

			typedef TranslationMatrix<T> SelfType;

		public:
			typedef T ValueType;
			typedef const T Reference;
			typedef const T ConstReference;
			typedef std::size_t SizeType;
			typedef std::ptrdiff_t DifferenceType;
			typedef MatrixReference<SelfType> ClosureType;
			typedef const MatrixReference<const SelfType> ConstClosureType;
			typedef Matrix<T, std::vector<T> > MatrixTemporaryType;
			typedef Vector<T, std::vector<T> > VectorTemporaryType;
	
			explicit TranslationMatrix(SizeType n, const ValueType& tx = ValueType(), 
									   const ValueType& ty = ValueType(), const ValueType& tz = ValueType()): size(n) {
				set(tx, ty, tz);
			}

			TranslationMatrix(const TranslationMatrix& m): size(m.size) {
				std::copy(m.data, m.data + 3, data);
			}

			void set(const ValueType& tx = ValueType(), const ValueType& ty = ValueType(), 
					 const ValueType& tz = ValueType()) {
				data[0] = tx;
				data[1] = ty;
				data[2] = tz;
			}

			ConstReference operator()(SizeType i, SizeType j) const {
				CDPL_MATH_CHECK(i < getSize1() && j < getSize2(), "Index out of range", Base::IndexError);

				if (i == j)
					return ValueType(1);

				if (j == (size - 1) && i < size && i < 3)
					return data[i];

				return ValueType();
			}

			bool isEmpty() const {
				return (size == 0);
			}

			SizeType getSize1() const {
				return size;
			}
	
			SizeType getSize2() const {
				return size;
			}

			SizeType getMaxSize1() const {
				return std::numeric_limits<SizeType>::max();
			}

			SizeType getMaxSize2() const {
				return std::numeric_limits<SizeType>::max();
			}

			TranslationMatrix& operator=(const TranslationMatrix& m) {
				if (this != &m) {
					std::copy(m.data, m.data + 3, data);
					size = m.size;
				}

				return *this;
			}

			void swap(TranslationMatrix& m) {
				if (this != &m) {
					std::swap_ranges(data, data + 3, m.data);
					boost::swap(size, m.size);
				}
			}
	
			friend void swap(TranslationMatrix& m1, TranslationMatrix& m2) {
				m1.swap(m2);
			}

			void resize(SizeType n) {
				size = n;
			}

		private:
			typedef ValueType ArrayType[3];

			SizeType  size;
			ArrayType data;
		};

		typedef ScalingMatrix<float> FScalingMatrix;
		typedef ScalingMatrix<double> DScalingMatrix;
		typedef ScalingMatrix<long> LScalingMatrix;
		typedef ScalingMatrix<unsigned long> ULScalingMatrix;

		typedef RotationMatrix<float> FRotationMatrix;
		typedef RotationMatrix<double> DRotationMatrix;
		typedef RotationMatrix<long> LRotationMatrix;
		typedef RotationMatrix<unsigned long> ULRotationMatrix;

		typedef TranslationMatrix<float> FTranslationMatrix;
		typedef TranslationMatrix<double> DTranslationMatrix;
		typedef TranslationMatrix<long> LTranslationMatrix;
		typedef TranslationMatrix<unsigned long> ULTranslationMatrix;
	}
}

#endif // CDPL_MATH_AFFINETRANSFORM_HPP
