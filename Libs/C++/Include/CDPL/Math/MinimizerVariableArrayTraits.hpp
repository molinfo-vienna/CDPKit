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

#include <vector>

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
			
			static T dot(const ArrayType& a1, const ArrayType& a2) {
				return innerProd(a1, a2);
			}

			template <typename T>
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
			static void axpy(const T& alpha, const ArrayType& x, ArrayType& y) {
				y.plusAssign(alpha * x);
			}
			
			static void clear(ArrayType& a) {
				a.clear(ValueType());
			}
			
			static void assign(ArrayType& a1, const ArrayType& a2) {
				a1.assign(a2);
			}

			template <typename T>
			static void multiply(ArrayType& a, const T& v) {
				a *= v;
			}
			
			static void sub(ArrayType& a1, const ArrayType& a2) {
				a1.minusAssign(a2);
			}
		};

		template <typename V>
		struct MinimizerVariableArrayTraits<VectorArray<V> >
		{

			typedef VectorArray<V> ArrayType;
			typedef V VectorType;
			typedef typename V::ValueType ValueType;
			typedef typename ArrayType::SizeType SizeType;

			template <typename T>
			static T dot(const ArrayType& a1, const ArrayType& a2) {
				T result = T();

				for (typename ArrayType::ConstElementIterator it1 = a1.getElementsBegin(), it2 = a2.getElementsBegin(), end1 = a1.getElementsEnd(); it1 != end1; ++it1, ++it2)
					result += innerProd(*it1, *it2);

				return result;
			}

			template <typename T>
			static T norm2(const ArrayType& a) {
				T scale = T();
				T ssq = T(1);

				for (typename ArrayType::ConstElementIterator it = a.getElementsBegin(), end = a.getElementsEnd(); it != end; ++it) {
					const typename VectorType::ConstPointer vx = it->getData();
					typename VectorType::SizeType dim = it->getSize();

					for (typename VectorType::SizeType i = 0; i < dim; i++) {
						const ValueType& x = vx[i];

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
			static void axpy(const T& alpha, const ArrayType& x, ArrayType& y) {
				typename ArrayType::ElementIterator it2 = y.getElementsBegin();
				VectorType tmp;

				for (typename ArrayType::ConstElementIterator it1 = x.getElementsBegin(), end1 = x.getElementsEnd(); it1 != end1; ++it1, ++it2) {
					tmp.assign(*it1);
					tmp *= alpha;

					it2->plusAssign(tmp);
				}
			}
			
			static void clear(ArrayType& a) {
				for (typename ArrayType::ElementIterator it = a.getElementsBegin(), end = a.getElementsEnd(); it != end; ++it)
					it->clear(ValueType());
			}

			static void assign(ArrayType& a1, const ArrayType& a2) {
				a1 = a2;
			}

			template <typename T>
			static void multiply(ArrayType& a, const T& v) {
				for (typename ArrayType::ElementIterator it = a.getElementsBegin(), end = a.getElementsEnd(); it != end; ++it)
					*it *= v;
			}

			
			static void sub(ArrayType& a1, const ArrayType& a2) {
				typename ArrayType::ConstElementIterator it2 = a2.getElementsBegin();

				for (typename ArrayType::ElementIterator it1 = a1.getElementsBegin(), end1 = a1.getElementsEnd(); it1 != end1; ++it1, ++it2)
					it1->minusAssign(*it2);
			}
		};

		template <typename V>
		struct MinimizerVariableArrayTraits<std::vector<V> >
		{

			typedef std::vector<V> ArrayType;
			typedef V VectorType;
			typedef typename V::ValueType ValueType;
			typedef typename ArrayType::size_type SizeType;

			template <typename T>
			static T dot(const ArrayType& a1, const ArrayType& a2) {
				T result = T();

				for (typename ArrayType::const_iterator it1 = a1.begin(), it2 = a2.begin(), end1 = a1.end(); it1 != end1; ++it1, ++it2)
					result += innerProd(*it1, *it2);

				return result;
			}

			template <typename T>
			static T norm2(const ArrayType& a) {
				T scale = T();
				T ssq = T(1);

				for (typename ArrayType::const_iterator it = a.begin(), end = a.end(); it != end; ++it) {
					const typename VectorType::ConstPointer vx = it->getData();
					typename VectorType::SizeType dim = it->getSize();

					for (typename VectorType::SizeType i = 0; i < dim; i++) {
						const ValueType& x = vx[i];

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
			static void axpy(const T& alpha, const ArrayType& x, ArrayType& y) {
				typename ArrayType::iterator it2 = y.begin();
				VectorType tmp;

				for (typename ArrayType::const_iterator it1 = x.begin(), end1 = x.end(); it1 != end1; ++it1, ++it2) {
					tmp.assign(*it1);
					tmp *= alpha;

					it2->plusAssign(tmp);
				}
			}
			
			static void clear(ArrayType& a) {
				for (typename ArrayType::iterator it = a.begin(), end = a.end(); it != end; ++it)
					it->clear(ValueType());
			}

			static void assign(ArrayType& a1, const ArrayType& a2) {
				a1 = a2;
			}

			template <typename T>
			static void multiply(ArrayType& a, const T& v) {
				for (typename ArrayType::iterator it = a.begin(), end = a.end(); it != end; ++it)
					*it *= v;
			}

			
			static void sub(ArrayType& a1, const ArrayType& a2) {
				typename ArrayType::const_iterator it2 = a2.begin();

				for (typename ArrayType::iterator it1 = a1.begin(), end1 = a1.end(); it1 != end1; ++it1, ++it2)
					it1->minusAssign(*it2);
			}
		};
	}
}

#endif // CDPL_MATH_MINIMIZERVARIABLEARRAYTRAITS_HPP
