/* 
 * VectorExpression.hpp 
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
 * \brief Definition of various vector expression types and operations.
 */

#ifndef CDPL_MATH_VECTOREXPRESSION_HPP
#define CDPL_MATH_VECTOREXPRESSION_HPP

#include <type_traits>

#include "CDPL/Math/Check.hpp"
#include "CDPL/Math/Expression.hpp"
#include "CDPL/Math/CommonType.hpp"
#include "CDPL/Math/Functional.hpp"
#include "CDPL/Math/TypeTraits.hpp"
#include "CDPL/Base/Exceptions.hpp"


namespace CDPL
{

	namespace Math
	{

		template <typename E, typename F>
		class VectorUnary : public VectorExpression<VectorUnary<E, F> >
		{

			typedef VectorUnary<E, F> SelfType;
			typedef F FunctorType;
			typedef E ExpressionType;
			typedef typename E::ConstClosureType ExpressionClosureType;

		public:
			typedef typename F::ResultType ValueType;
			typedef const ValueType ConstReference;
			typedef const ValueType Reference;
			typedef const SelfType ConstClosureType;
			typedef SelfType ClosureType;
			typedef typename E::SizeType SizeType;
			typedef typename E::DifferenceType DifferenceType;

			VectorUnary(const ExpressionType& e): expr(e) {}

			SizeType getSize() const {
				return expr.getSize();
			}

			ConstReference operator()(SizeType i) const {
				return FunctorType::apply(expr(i));
			}

			ConstReference operator[](SizeType i) const {
				return FunctorType::apply(expr[i]);
			}

		private:
			ExpressionClosureType expr;
		};

		template <typename E, typename F>
		struct VectorUnaryTraits
		{

			typedef VectorUnary<E, F> ExpressionType;
			typedef ExpressionType ResultType;
		};

		template <typename E1, typename E2, typename F>
		class VectorBinary1 : public VectorExpression<VectorBinary1<E1, E2, F> >
		{

			typedef VectorBinary1<E1, E2, F> SelfType;
			typedef F FunctorType;
			typedef E1 Expression1Type;
			typedef E2 Expression2Type;
			typedef typename E1::ConstClosureType Expression1ClosureType;
			typedef typename E2::ConstClosureType Expression2ClosureType;

		public:
			typedef typename F::ResultType ValueType;
			typedef const ValueType ConstReference;
			typedef const ValueType Reference;
			typedef const SelfType ConstClosureType;
			typedef SelfType ClosureType;
			typedef typename CommonType<typename E1::SizeType, typename E2::SizeType>::Type SizeType;
			typedef typename CommonType<typename E1::DifferenceType, typename E2::DifferenceType>::Type DifferenceType;

			VectorBinary1(const Expression1Type& e1, const Expression2Type& e2): expr1(e1), expr2(e2) {}

			SizeType getSize() const {
				return CDPL_MATH_CHECK_SIZE_EQUALITY(SizeType(expr1.getSize()), SizeType(expr2.getSize()), Base::SizeError);
			}

			ConstReference operator()(SizeType i) const {
				return FunctorType::apply(expr1(i), expr2(i));
			}

			ConstReference operator[](SizeType i) const {
				return FunctorType::apply(expr1[i], expr2[i]);
			}

		private:
			Expression1ClosureType expr1;
			Expression2ClosureType expr2;
		};

		template <typename E1, typename E2, typename F>
		struct VectorBinary1Traits
		{

			typedef VectorBinary1<E1, E2, F> ExpressionType;
			typedef ExpressionType ResultType;
		};

		template <typename E1, typename E2, typename F>
		class VectorBinary2 : public VectorExpression<VectorBinary2<E1, E2, F> >
		{

			typedef VectorBinary2<E1, E2, F> SelfType;
			typedef F FunctorType;
			typedef E1 Expression1Type;
			typedef E2 Expression2Type;
			typedef typename E1::ConstClosureType Expression1ClosureType;
			typedef typename E2::ConstClosureType Expression2ClosureType;

		public:
			typedef typename F::ResultType ValueType;
			typedef const ValueType ConstReference;
			typedef const ValueType Reference;
			typedef const SelfType ConstClosureType;
			typedef SelfType ClosureType;
			typedef typename CommonType<typename E1::SizeType, typename E2::SizeType>::Type SizeType;
			typedef typename CommonType<typename E1::DifferenceType, typename E2::DifferenceType>::Type DifferenceType;

			VectorBinary2(const Expression1Type& e1, const Expression2Type& e2): expr1(e1), expr2(e2) {}

			SizeType getSize() const {
				return CDPL_MATH_CHECK_SIZE_EQUALITY(SizeType(expr1.getSize()), SizeType(expr2.getSize()), Base::SizeError);
			}

			ConstReference operator()(SizeType i) const {
				return FunctorType::apply(expr1, expr2, i);
			}

			ConstReference operator[](SizeType i) const {
				return FunctorType::apply(expr1, expr2, i);
			}

		private:
			Expression1ClosureType expr1;
			Expression2ClosureType expr2;
		};

		template <typename E1, typename E2, typename F>
		struct VectorBinary2Traits
		{

			typedef VectorBinary2<E1, E2, F> ExpressionType;
			typedef ExpressionType ResultType;
		};

		template <typename E1, typename E2, typename F>
		class Scalar1VectorBinary : public VectorExpression<Scalar1VectorBinary<E1, E2, F> >
		{

			typedef Scalar1VectorBinary<E1, E2, F> SelfType;
			typedef F FunctorType;
			typedef E1 Expression1Type;
			typedef E2 Expression2Type;
			typedef const E1 Expression1ClosureType;
			typedef typename E2::ConstClosureType Expression2ClosureType;

		public:
			typedef typename F::ResultType ValueType;
			typedef const ValueType ConstReference;
			typedef const ValueType Reference;
			typedef const SelfType ConstClosureType;
			typedef SelfType ClosureType;
			typedef typename E2::SizeType SizeType;
			typedef typename E2::DifferenceType DifferenceType;

			Scalar1VectorBinary(const Expression1Type& e1, const Expression2Type& e2): expr1(e1), expr2(e2) {}

			SizeType getSize() const {
				return expr2.getSize();
			}

			ConstReference operator()(SizeType i) const {
				return FunctorType::apply(expr1, expr2(i));
			}

			ConstReference operator[](SizeType i) const {
				return FunctorType::apply(expr1, expr2[i]);
			}

		private:
			Expression1ClosureType expr1;
			Expression2ClosureType expr2;
		};

		template <typename E1, typename E2, typename F>
		struct Scalar1VectorBinaryTraits
		{

			typedef Scalar1VectorBinary<E1, E2, F> ExpressionType;
			typedef ExpressionType ResultType;
		};

		template <typename E1, typename E2, typename F>
		class Scalar2VectorBinary : public VectorExpression<Scalar2VectorBinary<E1, E2, F> >
		{

			typedef Scalar2VectorBinary<E1, E2, F> SelfType;
			typedef F FunctorType;
			typedef E1 Expression1Type;
			typedef E2 Expression2Type;
			typedef typename E1::ConstClosureType Expression1ClosureType;
			typedef const E2 Expression2ClosureType;

		public:
			typedef typename F::ResultType ValueType;
			typedef const ValueType ConstReference;
			typedef const ValueType Reference;
			typedef const SelfType ConstClosureType;
			typedef SelfType ClosureType;
			typedef typename E1::SizeType SizeType;
			typedef typename E1::DifferenceType DifferenceType;

			Scalar2VectorBinary(const Expression1Type& e1, const Expression2Type& e2): expr1(e1), expr2(e2) {}

			SizeType getSize() const {
				return expr1.getSize();
			}

			ConstReference operator()(SizeType i) const {
				return FunctorType::apply(expr1(i), expr2);
			}

			ConstReference operator[](SizeType i) const {
				return FunctorType::apply(expr1[i], expr2);
			}

		private:
			Expression1ClosureType expr1;
			Expression2ClosureType expr2;
		};

		template <typename E1, typename E2, typename F>
		struct Scalar2VectorBinaryTraits
		{

			typedef Scalar2VectorBinary<E1, E2, F> ExpressionType;
			typedef ExpressionType ResultType;
		};

		template <typename E1, typename E2, typename F>
		class QuaternionVectorBinary : public VectorExpression<QuaternionVectorBinary<E1, E2, F> >
		{

			typedef QuaternionVectorBinary<E1, E2, F> SelfType;
			typedef F FunctorType;
			typedef E1 Expression1Type;
			typedef E2 Expression2Type;
			typedef typename E1::ConstClosureType Expression1ClosureType;
			typedef typename E2::ConstClosureType Expression2ClosureType;

		public:
			typedef typename F::ResultType ValueType;
			typedef const ValueType ConstReference;
			typedef const ValueType Reference;
			typedef const SelfType ConstClosureType;
			typedef SelfType ClosureType;
			typedef typename E2::SizeType SizeType;
			typedef typename E2::DifferenceType DifferenceType;

			QuaternionVectorBinary(const Expression1Type& e1, const Expression2Type& e2): expr1(e1), expr2(e2) {}

			SizeType getSize() const {
				return expr2.getSize();
			}

			ConstReference operator()(SizeType i) const {
				return FunctorType::apply(expr1, expr2, i);
			}

			ConstReference operator[](SizeType i) const {
				return FunctorType::apply(expr1, expr2, i);
			}

		private:
			Expression1ClosureType expr1;
			Expression2ClosureType expr2;
		};

		template <typename E1, typename E2, typename F>
		struct QuaternionVectorBinaryTraits
		{

			typedef QuaternionVectorBinary<E1, E2, F> ExpressionType;
			typedef ExpressionType ResultType;
		};

		template <typename E>
		typename VectorUnaryTraits<E, ScalarNegation<typename E::ValueType> >::ResultType 
		operator-(const VectorExpression<E>& e)
		{
			typedef typename VectorUnaryTraits<E, ScalarNegation<typename E::ValueType> >::ExpressionType ExpressionType;

			return ExpressionType(e());
		}
	
		template <typename E>
		const E& 
		operator+(const VectorExpression<E>& e)
		{
			return e();
		}

		template <typename E1, typename E2>
		typename VectorBinary1Traits<E1, E2, ScalarAddition<typename E1::ValueType, typename E2::ValueType> >::ResultType 
		operator+(const VectorExpression<E1>& e1, const VectorExpression<E2>& e2)
		{
			typedef typename VectorBinary1Traits<E1, E2,
				ScalarAddition<typename E1::ValueType, typename E2::ValueType> >::ExpressionType ExpressionType;

			return ExpressionType(e1(), e2());
		}
	
		template <typename E1, typename E2>
		typename VectorBinary1Traits<E1, E2, ScalarSubtraction<typename E1::ValueType, typename E2::ValueType> >::ResultType 
		operator-(const VectorExpression<E1>& e1, const VectorExpression<E2>& e2)
		{
			typedef typename VectorBinary1Traits<E1, E2,
				ScalarSubtraction<typename E1::ValueType, typename E2::ValueType> >::ExpressionType ExpressionType;

			return ExpressionType(e1(), e2());
		}

		template <typename E, typename T>
		typename std::enable_if<IsScalar<T>::value, typename Scalar2VectorBinaryTraits<E, T, ScalarMultiplication<typename E::ValueType, T> >::ResultType>::type
		operator*(const VectorExpression<E>& e, const T& t)
		{
			typedef typename Scalar2VectorBinaryTraits<E, T,
				ScalarMultiplication<typename E::ValueType, T> >::ExpressionType ExpressionType;

			return ExpressionType(e(), t);
		}

		template <typename T, typename E>
		typename std::enable_if<IsScalar<T>::value, typename Scalar1VectorBinaryTraits<T, E, ScalarMultiplication<T, typename E::ValueType> >::ResultType>::type
		operator*(const T& t, const VectorExpression<E>& e)
		{
			typedef typename Scalar1VectorBinaryTraits<T, E,
				ScalarMultiplication<T, typename E::ValueType> >::ExpressionType ExpressionType;

			return ExpressionType(t, e());
		}

		template <typename E, typename T>
		typename std::enable_if<IsScalar<T>::value, typename Scalar2VectorBinaryTraits<E, T, ScalarDivision<typename E::ValueType, T> >::ResultType>::type
		operator/(const VectorExpression<E>& e, const T& t)
		{
			typedef typename Scalar2VectorBinaryTraits<E, T,
				ScalarDivision<typename E::ValueType, T> >::ExpressionType ExpressionType;

			return ExpressionType(e(), t);
		}

		template <typename E1, typename E2>
		typename VectorEquality<E1, E2>::ResultType
		operator==(const VectorExpression<E1>& e1, const VectorExpression<E2>& e2)
		{
			return VectorEquality<E1, E2>::apply(e1, e2);
		}

		template <typename E1, typename E2>
		typename VectorEquality<E1, E2>::ResultType
		operator!=(const VectorExpression<E1>& e1, const VectorExpression<E2>& e2)
		{
			return !VectorEquality<E1, E2>::apply(e1, e2);
		}

		template <typename E1, typename E2, typename T>
		typename std::enable_if<std::is_arithmetic<T>::value, typename VectorToleranceEquality<E1, E2, T>::ResultType>::type
		equals(const VectorExpression<E1>& e1, const VectorExpression<E2>& e2, const T& eps)
		{
			return VectorToleranceEquality<E1, E2, T>::apply(e1, e2, eps);
		}

		template <typename E>
		typename VectorUnaryTraits<E, ScalarConjugation<typename E::ValueType> >::ResultType 
		conj(const VectorExpression<E>& e)
		{
			typedef typename VectorUnaryTraits<E, ScalarConjugation<typename E::ValueType> >::ExpressionType ExpressionType;

			return ExpressionType(e());
		}

		template <typename E>
		typename VectorUnaryTraits<E, ScalarConjugation<typename E::ValueType> >::ResultType 
		herm(const VectorExpression<E>& e)
		{
			typedef typename VectorUnaryTraits<E, ScalarConjugation<typename E::ValueType> >::ExpressionType ExpressionType;

			return ExpressionType(e());
		}

		template <typename E>
		typename VectorUnaryTraits<E, ScalarReal<typename E::ValueType> >::ResultType 
		real(const VectorExpression<E>& e)
		{
			typedef typename VectorUnaryTraits<E, ScalarReal<typename E::ValueType> >::ExpressionType ExpressionType;

			return ExpressionType(e());
		}

		template <typename E>
		typename VectorUnaryTraits<E, ScalarImaginary<typename E::ValueType> >::ResultType 
		imag(const VectorExpression<E>& e)
		{
			typedef typename VectorUnaryTraits<E, ScalarImaginary<typename E::ValueType> >::ExpressionType ExpressionType;

			return ExpressionType(e());
		}

		template <typename E1, typename E2>
		typename VectorBinary1Traits<E1, E2, ScalarDivision<typename E1::ValueType, typename E2::ValueType> >::ResultType 
		elemDiv(const VectorExpression<E1>& e1, const VectorExpression<E2>& e2)
		{
			typedef typename VectorBinary1Traits<E1, E2,
				ScalarDivision<typename E1::ValueType, typename E2::ValueType> >::ExpressionType ExpressionType;

			return ExpressionType(e1(), e2());
		}

		template <typename E1, typename E2>
		typename VectorBinary1Traits<E1, E2, ScalarMultiplication<typename E1::ValueType, typename E2::ValueType> >::ResultType 
		elemProd(const VectorExpression<E1>& e1, const VectorExpression<E2>& e2)
		{
			typedef typename VectorBinary1Traits<E1, E2,
				ScalarMultiplication<typename E1::ValueType, typename E2::ValueType> >::ExpressionType ExpressionType;

			return ExpressionType(e1(), e2());
		}

		template <typename E1, typename E2>
		typename VectorBinary2Traits<E1, E2, VectorCrossProduct<E1, E2> >::ResultType 
		crossProd(const VectorExpression<E1>& e1, const VectorExpression<E2>& e2)
		{
			typedef typename VectorBinary2Traits<E1, E2,
				VectorCrossProduct<E1, E2> >::ExpressionType ExpressionType;

			return ExpressionType(e1(), e2());
		}

		template <typename E1, typename E2>
		typename VectorInnerProduct<E1, E2>::ResultType
		innerProd(const VectorExpression<E1>& e1, const VectorExpression<E2>& e2)
		{
			return VectorInnerProduct<E1, E2>::apply(e1, e2);
		}

		template <typename E1, typename E2, typename T>
		typename VectorAngleCosine<E1, E2, T>::ResultType
		angleCos(const VectorExpression<E1>& e1, const VectorExpression<E2>& e2, const T& sd, bool clamp = true)
		{
			return VectorAngleCosine<E1, E2, T>::apply(e1, e2, sd, clamp);
		}
	
		template <typename E>
		typename VectorElementSum<E>::ResultType
		sum(const VectorExpression<E>& e)
		{
			return VectorElementSum<E>::apply(e);
		}

		template <typename E>
		typename VectorNorm1<E>::ResultType
		norm1(const VectorExpression<E>& e)
		{
			return VectorNorm1<E>::apply(e);
		}
	
		template <typename E>
		typename VectorNorm2<E>::ResultType
		norm2(const VectorExpression<E>& e)
		{
			return VectorNorm2<E>::apply(e);
		}

		template <typename E>
		typename VectorNormInfinity<E>::ResultType
		normInf(const VectorExpression<E>& e)
		{
			return VectorNormInfinity<E>::apply(e);
		}

		template <typename E>
		typename VectorNormInfinityIndex<E>::ResultType
		normInfIndex(const VectorExpression<E>& e)
		{
			return VectorNormInfinityIndex<E>::apply(e);
		}

		template <typename E>
		typename VectorNorm2<E>::ResultType
		length(const VectorExpression<E>& e)
		{
			return norm2(e);
		}

		template <typename E>
		const E& 
		trans(const VectorExpression<E>& e)
		{
			return e();
		}

		template <typename E>
		E& 
		trans(VectorExpression<E>& e)
		{
			return e();
		}

		template <typename E1, typename E2>
		typename QuaternionVectorBinaryTraits<E1, E2, QuaternionVectorRotation<E1, E2> >::ResultType 
		rotate(const QuaternionExpression<E1>& e1, const VectorExpression<E2>& e2)
		{
			typedef typename QuaternionVectorBinaryTraits<E1, E2, QuaternionVectorRotation<E1, E2> >::ExpressionType ExpressionType;

			return ExpressionType(e1(), e2());
		}
	}
}

#endif // CDPL_MATH_VECTOREXPRESSION_HPP
