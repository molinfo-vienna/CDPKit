/* 
 * GridExpression.hpp 
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
 * \brief Definition of various grid expression types and operations.
 */

#ifndef CDPL_MATH_GRIDEXPRESSION_HPP
#define CDPL_MATH_GRIDEXPRESSION_HPP

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

		template <typename C> class GridContainer;

		template <typename E, typename F>
		class GridUnary : public GridExpression<GridUnary<E, F> >
		{

			typedef GridUnary<E, F> SelfType;
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

			GridUnary(const ExpressionType& e): expr(e) {}

			SizeType getSize1() const {
				return expr.getSize1();
			}

			SizeType getSize2() const {
				return expr.getSize2();
			}

			SizeType getSize3() const {
				return expr.getSize3();
			}

			ConstReference operator()(SizeType i, SizeType j, SizeType k) const {
				return FunctorType::apply(expr(i, j, k));
			}

		private:
			ExpressionClosureType expr;
		};

		template <typename E, typename F>
		struct GridUnaryTraits
		{

			typedef GridUnary<E, F> ExpressionType;
			typedef ExpressionType ResultType;
		};
	
		template <typename E1, typename E2, typename F>
		class GridBinary1 : public GridExpression<GridBinary1<E1, E2, F> >
		{

			typedef GridBinary1<E1, E2, F> SelfType;
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

			GridBinary1(const Expression1Type& e1, const Expression2Type& e2): expr1(e1), expr2(e2) {}

			SizeType getSize1() const {
				return CDPL_MATH_CHECK_SIZE_EQUALITY(SizeType(expr1.getSize1()), SizeType(expr2.getSize1()), Base::SizeError);
			}

			SizeType getSize2() const {
				return CDPL_MATH_CHECK_SIZE_EQUALITY(SizeType(expr1.getSize2()), SizeType(expr2.getSize2()), Base::SizeError);
			}

			SizeType getSize3() const {
				return CDPL_MATH_CHECK_SIZE_EQUALITY(SizeType(expr1.getSize3()), SizeType(expr2.getSize3()), Base::SizeError);
			}

			ConstReference operator()(SizeType i, SizeType j, SizeType k) const {
				return FunctorType::apply(expr1(i, j, k), expr2(i, j, k));
			}

		private:
			Expression1ClosureType expr1;
			Expression2ClosureType expr2;
		};

		template <typename E1, typename E2, typename F>
		struct GridBinary1Traits
		{

			typedef GridBinary1<E1, E2, F> ExpressionType;
			typedef ExpressionType ResultType;
		};

		template <typename E1, typename E2, typename F>
		class Scalar1GridBinary : public GridExpression<Scalar1GridBinary<E1, E2, F> >
		{

			typedef Scalar1GridBinary<E1, E2, F> SelfType;
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

			Scalar1GridBinary(const Expression1Type& e1, const Expression2Type& e2): expr1(e1), expr2(e2) {}

			SizeType getSize1() const {
				return expr2.getSize1();
			}

			SizeType getSize2() const {
				return expr2.getSize2();
			}

			SizeType getSize3() const {
				return expr2.getSize3();
			}

			ConstReference operator()(SizeType i, SizeType j, SizeType k) const {
				return FunctorType::apply(expr1, expr2(i, j, k));
			}

		private:
			Expression1ClosureType expr1;
			Expression2ClosureType expr2;
		};

		template <typename E1, typename E2, typename F>
		struct Scalar1GridBinaryTraits
		{

			typedef Scalar1GridBinary<E1, E2, F> ExpressionType;
			typedef ExpressionType ResultType;
		};

		template <typename E1, typename E2, typename F>
		class Scalar2GridBinary : public GridExpression<Scalar2GridBinary<E1, E2, F> >
		{

			typedef Scalar2GridBinary<E1, E2, F> SelfType;
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

			Scalar2GridBinary(const Expression1Type& e1, const Expression2Type& e2): expr1(e1), expr2(e2) {}

			SizeType getSize1() const {
				return expr1.getSize1();
			}

			SizeType getSize2() const {
				return expr1.getSize2();
			}

			SizeType getSize3() const {
				return expr1.getSize3();
			}

			ConstReference operator()(SizeType i, SizeType j, SizeType k) const {
				return FunctorType::apply(expr1(i, j, k), expr2);
			}

		private:
			Expression1ClosureType expr1;
			Expression2ClosureType expr2;
		};

		template <typename E1, typename E2, typename F>
		struct Scalar2GridBinaryTraits
		{

			typedef Scalar2GridBinary<E1, E2, F> ExpressionType;
			typedef ExpressionType ResultType;
		};

		template <typename E>		
		typename GridUnaryTraits<E, ScalarNegation<typename E::ValueType> >::ResultType 
		operator-(const GridExpression<E>& e)
		{
			typedef typename GridUnaryTraits<E, ScalarNegation<typename E::ValueType> >::ExpressionType ExpressionType;

			return ExpressionType(e());
		}
	
		template <typename E>
		
		const E& 
		operator+(const GridExpression<E>& e)
		{
			return e();
		}

		template <typename E1, typename E2>		
		typename GridBinary1Traits<E1, E2, ScalarAddition<typename E1::ValueType, typename E2::ValueType> >::ResultType 
		operator+(const GridExpression<E1>& e1, const GridExpression<E2>& e2)
		{
			typedef typename GridBinary1Traits<E1, E2,
				ScalarAddition<typename E1::ValueType, typename E2::ValueType> >::ExpressionType ExpressionType;

			return ExpressionType(e1(), e2());
		}
	
		template <typename E1, typename E2>		
		typename GridBinary1Traits<E1, E2, ScalarSubtraction<typename E1::ValueType, typename E2::ValueType> >::ResultType 
		operator-(const GridExpression<E1>& e1, const GridExpression<E2>& e2)
		{
			typedef typename GridBinary1Traits<E1, E2,
				ScalarSubtraction<typename E1::ValueType, typename E2::ValueType> >::ExpressionType ExpressionType;

			return ExpressionType(e1(), e2());
		}

		template <typename E, typename T>		
		typename std::enable_if<IsScalar<T>::value, typename Scalar2GridBinaryTraits<E, T, ScalarMultiplication<typename E::ValueType, T> >::ResultType>::type
		operator*(const GridExpression<E>& e, const T& t)
		{
			typedef typename Scalar2GridBinaryTraits<E, T,
				ScalarMultiplication<typename E::ValueType, T> >::ExpressionType ExpressionType;

			return ExpressionType(e(), t);
		}

		template <typename T, typename E>		
		typename std::enable_if<IsScalar<T>::value, typename Scalar1GridBinaryTraits<T, E, ScalarMultiplication<T, typename E::ValueType> >::ResultType>::type 
		operator*(const T& t, const GridExpression<E>& e)
		{
			typedef typename Scalar1GridBinaryTraits<T, E,
				ScalarMultiplication<T, typename E::ValueType> >::ExpressionType ExpressionType;

			return ExpressionType(t, e());
		}

		template <typename E, typename T>		
		typename std::enable_if<IsScalar<T>::value, typename Scalar2GridBinaryTraits<E, T, ScalarDivision<typename E::ValueType, T> >::ResultType>::type
		operator/(const GridExpression<E>& e, const T& t)
		{
			typedef typename Scalar2GridBinaryTraits<E, T,
				ScalarDivision<typename E::ValueType, T> >::ExpressionType ExpressionType;

			return ExpressionType(e(), t);
		}

		template <typename E1, typename E2>		
		typename GridEquality<E1, E2>::ResultType
		operator==(const GridExpression<E1>& e1, const GridExpression<E2>& e2)
		{
			return GridEquality<E1, E2>::apply(e1, e2);
		}

		template <typename E1, typename E2>		
		typename GridEquality<E1, E2>::ResultType
		operator!=(const GridExpression<E1>& e1, const GridExpression<E2>& e2)
		{
			return !GridEquality<E1, E2>::apply(e1, e2);
		}

		template <typename E1, typename E2, typename T>		
		typename std::enable_if<std::is_arithmetic<T>::value, typename GridToleranceEquality<E1, E2, T>::ResultType>::type
		equals(const GridExpression<E1>& e1, const GridExpression<E2>& e2, const T& eps)
		{
			return GridToleranceEquality<E1, E2, T>::apply(e1, e2, eps);
		}

		template <typename E>		
		typename GridUnaryTraits<E, ScalarConjugation<typename E::ValueType> >::ResultType 
		conj(const GridExpression<E>& e)
		{
			typedef typename GridUnaryTraits<E, ScalarConjugation<typename E::ValueType> >::ExpressionType ExpressionType;

			return ExpressionType(e());
		}

		template <typename E>		
		typename GridUnaryTraits<E, ScalarConjugation<typename E::ValueType> >::ResultType 
		herm(const GridExpression<E>& e)
		{
			typedef typename GridUnaryTraits<E, ScalarConjugation<typename E::ValueType> >::ExpressionType ExpressionType;

			return ExpressionType(e());
		}

		template <typename E>		
		typename GridUnaryTraits<E, ScalarReal<typename E::ValueType> >::ResultType 
		real(const GridExpression<E>& e)
		{
			typedef typename GridUnaryTraits<E, ScalarReal<typename E::ValueType> >::ExpressionType ExpressionType;

			return ExpressionType(e());
		}

		template <typename E>		
		typename GridUnaryTraits<E, ScalarImaginary<typename E::ValueType> >::ResultType 
		imag(const GridExpression<E>& e)
		{
			typedef typename GridUnaryTraits<E, ScalarImaginary<typename E::ValueType> >::ExpressionType ExpressionType;

			return ExpressionType(e());
		}

		template <typename E1, typename E2>		
		typename GridBinary1Traits<E1, E2, ScalarDivision<typename E1::ValueType, typename E2::ValueType> >::ResultType 
		elemDiv(const GridExpression<E1>& e1, const GridExpression<E2>& e2)
		{
			typedef typename GridBinary1Traits<E1, E2,
				ScalarDivision<typename E1::ValueType, typename E2::ValueType> >::ExpressionType ExpressionType;

			return ExpressionType(e1(), e2());
		}

		template <typename E1, typename E2>		
		typename GridBinary1Traits<E1, E2, ScalarMultiplication<typename E1::ValueType, typename E2::ValueType> >::ResultType 
		elemProd(const GridExpression<E1>& e1, const GridExpression<E2>& e2)
		{
			typedef typename GridBinary1Traits<E1, E2,
				ScalarMultiplication<typename E1::ValueType, typename E2::ValueType> >::ExpressionType ExpressionType;

			return ExpressionType(e1(), e2());
		}

		template <typename E>		
		typename GridElementSum<E>::ResultType
		sum(const GridExpression<E>& e)
		{
			return GridElementSum<E>::apply(e);
		}
	}
}

#endif // CDPL_MATH_GRIDEXPRESSION_HPP
