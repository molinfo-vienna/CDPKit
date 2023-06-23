/* 
 * TypeTraits.hpp 
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
 * \brief Definition of type traits.
 */

#ifndef CDPL_MATH_TYPETRAITS_HPP
#define CDPL_MATH_TYPETRAITS_HPP

#include <cmath>
#include <complex>
#include <algorithm>
#include <limits>
#include <type_traits>


namespace CDPL
{

	namespace Math
	{

		template <bool Signed>
		struct ScalarAbsImpl
		{

			template <typename T> 
			static T abs(const T& t) {
				return std::abs(t);
			}
		};

		template <>
		struct ScalarAbsImpl<false>
		{

			template <typename T> 
			static const T& abs(const T& t) {
				return t;
			}
		};

		template <typename T>
		struct ScalarTraits
		{

			typedef T ValueType;
			typedef T RealType;
			typedef const T& ConstReference;
			typedef ScalarTraits<T> SelfType;

			static RealType real(ConstReference t) {
				return t;
			}

			static RealType imag(ConstReference) {
				return RealType();
			}

			static RealType conj(ConstReference t) {
				return t;
			}

			static RealType abs(ConstReference t) {
				return ScalarAbsImpl<std::numeric_limits<ValueType>::is_signed>::abs(t);
			}

			static ValueType sqrt(ConstReference t) {
				return ValueType(std::sqrt(t));
			}
	
			static RealType norm1(ConstReference t) {
				return SelfType::abs(t);
			}
	
			static RealType norm2(ConstReference t) {
				return SelfType::abs(t);
			}

			static RealType normInf(ConstReference t) {
				return SelfType::abs(t);
			}
		};

		template <typename T> struct TypeTraits;
		template <typename T>
		struct ComplexTraits
		{

			typedef T ValueType;
			typedef typename T::value_type RealType;
			typedef const T& ConstReference;
			typedef ComplexTraits<T> SelfType;

			static RealType real(ConstReference t) {
				return std::real(t);
			}

			static RealType imag(ConstReference t) {
				return std::imag(t);
			}

			static ValueType conj(ConstReference t) {
				return std::conj(t);
			}

			static RealType abs(ConstReference t) {
				return std::abs(t);
			}

			static ValueType sqrt(ConstReference t) {
				return std::sqrt(t);
			}

			static RealType norm1(ConstReference t) {
				return TypeTraits<RealType>::abs(SelfType::real(t)) 
					+ TypeTraits<RealType>::abs(SelfType::imag(t));
			}
	
			static RealType norm2(ConstReference t) {
				return SelfType::abs(t);
			}

			static RealType normInf(ConstReference t) {
				return std::max(TypeTraits<RealType>::abs(SelfType::real(t)),
								TypeTraits<RealType>::abs(SelfType::imag(t)));
			}
		};

		template <typename T>
		struct TypeTraits : public ScalarTraits<T> {};

		template <typename T>
		struct TypeTraits<std::complex<T> > : public ComplexTraits<std::complex<T> >  {};

		template <typename V>
		struct VectorTemporaryTraits 
		{

			typedef typename V::VectorTemporaryType Type;
		};

		template <typename M>
		struct MatrixTemporaryTraits 
		{

			typedef typename M::MatrixTemporaryType Type;
		};

		template <typename Q>
		struct QuaternionTemporaryTraits 
		{

			typedef typename Q::QuaternionTemporaryType Type;
		};

		template <typename G>
		struct GridTemporaryTraits 
		{

			typedef typename G::GridTemporaryType Type;
		};

		template <typename T>
		struct IsScalar : public std::is_arithmetic<T> {};

		template <typename T>
		struct IsScalar<std::complex<T> > : public std::is_arithmetic<T> {};

	}
}

#endif // CDPL_MATH_TYPETRAITS_HPP
