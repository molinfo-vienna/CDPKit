/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * MinimizerVariableArrayTraits.hpp 
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
 * \brief Provides traits to flexibly handle different types of variable arrays in function
 *        optimization algorithms.
 */

#ifndef CDPL_MATH_MINIMIZERVARIABLEARRAYTRAITS_HPP
#define CDPL_MATH_MINIMIZERVARIABLEARRAYTRAITS_HPP

#include "CDPL/Math/Config.hpp"
#include "CDPL/Math/VectorArray.hpp"
#include "CDPL/Math/TypeTraits.hpp"


namespace CDPL
{

	namespace Math
	{

		template <typename A>
		struct MinimizerVariableArrayTraits
		{

			typedef A ArrayType;
			typedef typename A::ValueType ValueType;
			typedef typename A::SizeType SizeType;

			template <typename T>
			CDPL_MATH_INLINE
			static T dot(const ArrayType& a1, const ArrayType& a2) {
				return innerProd(a1, a2);
			}

			template <typename T>
			CDPL_MATH_INLINE
			static T norm2(const ArrayType& a) {
				T scale = T();
				T ssq = T(1);
				SizeType size = a.getSize();

				if (size == SizeType(0))
					return T();

				else if (size == SizeType(1)) 
					return TypeTraits<ValueType>::abs(a(0));
				
				for (SizeType i = 0; i < size; i++) {
					const ValueType& x = a(i);

					if (x != ValueType()) {
						const typename TypeTraits<ValueType>::RealType ax = TypeTraits<ValueType>::abs(x);

						if (scale < ax) {
							ssq = 1 + ssq * (scale / ax) * (scale / ax);
							scale = ax;

						} else {
							ssq += (ax / scale) * (ax / scale);
						}
					}
				}

				return (scale * TypeTraits<T>::sqrt(ssq));
			}
 
			template <typename T>
			CDPL_MATH_INLINE 
			static void axpy(const T& alpha, const ArrayType& x, ArrayType& y) {
				y.plusAssign(alpha * x);
			}
		
			CDPL_MATH_INLINE 
			static void clear(ArrayType& a) {
				a.clear(ValueType());
			}

			CDPL_MATH_INLINE 
			static void assign(ArrayType& a1, const ArrayType& a2) {
				a1.assign(a2);
			}

			template <typename T>
			CDPL_MATH_INLINE 
			static void multiply(ArrayType& a, const T& v) {
				a *= v;
			}

			CDPL_MATH_INLINE 
			static void sub(ArrayType& a1, const ArrayType& a2) {
				a1.minusAssign(a2);
			}
		};

		template <typename A>
		struct MinimizerVariableArrayTraits<VectorArray<A> >
		{

			typedef VectorArray<A> ArrayType;
			typedef A VectorType;
			typedef typename A::ValueType ValueType;
			typedef typename ArrayType::SizeType SizeType;

			template <typename T>
			CDPL_MATH_INLINE
			static T dot(const ArrayType& a1, const ArrayType& a2) {
				T result = T();

				for (SizeType i = 0, size = a1.getSize(); i < size; i++)
					result += innerProd(a1[i], a2[i]);

				return result;
			}

			template <typename T>
			CDPL_MATH_INLINE
			static T norm2(const ArrayType& a) {
				T scale = T();
				T ssq = T(1);
				SizeType size = a.getSize();

				if (size == SizeType(0))
					return T();

				for (SizeType i = 0; i < size; i++) {
					const VectorType& vx = a[i];

					for (typename VectorType::SizeType j = 0, dim = vx.getSize(); j < dim; j++) {
						const ValueType& x = vx(j);

						if (x != ValueType()) {
							const typename TypeTraits<ValueType>::RealType ax = TypeTraits<ValueType>::abs(x);

							if (scale < ax) {
								ssq = 1 + ssq * (scale / ax) * (scale / ax);
								scale = ax;

							} else {
								ssq += (ax / scale) * (ax / scale);
							}
						}
					}
				}

				return (scale * TypeTraits<T>::sqrt(ssq));
			}
 
			template <typename T>
			CDPL_MATH_INLINE 
			static void axpy(const T& alpha, const ArrayType& x, ArrayType& y) {
				for (SizeType i = 0, size = x.getSize(); i < size; i++)
					y[i].plusAssign(alpha * x[i]);
			}
		
			CDPL_MATH_INLINE 
			static void clear(ArrayType& a) {
				for (SizeType i = 0, size = a.getSize(); i < size; i++)
					a[i].clear(ValueType());
			}

			CDPL_MATH_INLINE 
			static void assign(ArrayType& a1, const ArrayType& a2) {
				if (a1.getSize() != a2.getSize())
					a1.resize(a2.getSize());

				for (SizeType i = 0, size = a1.getSize(); i < size; i++)
					a1[i].assign(a2[i]);
			}

			template <typename T>
			CDPL_MATH_INLINE 
			static void multiply(ArrayType& a, const T& v) {
				for (SizeType i = 0, size = a.getSize(); i < size; i++)
					a[i] *= v;
			}

			CDPL_MATH_INLINE 
			static void sub(ArrayType& a1, const ArrayType& a2) {
				for (SizeType i = 0, size = a1.getSize(); i < size; i++)
					a1[i].minusAssign(a2[i]);
			}
		};
	}
}

#endif // CDPL_MATH_MINIMIZERVARIABLEARRAYTRAITS_HPP
