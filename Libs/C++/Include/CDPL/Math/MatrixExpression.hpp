/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * MatrixExpression.hpp 
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
 * \brief Definition of various matrix expression types and operations.
 */

#ifndef CDPL_MATH_MATRIXEXPRESSION_HPP
#define CDPL_MATH_MATRIXEXPRESSION_HPP

#include <boost/mpl/if.hpp>
#include <boost/type_traits/is_const.hpp>
#include <boost/type_traits/is_arithmetic.hpp>
#include <boost/utility.hpp>

#include "CDPL/Math/Config.hpp"
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

		template <typename C> class VectorContainer;
		template <typename C> class MatrixContainer;

		template <typename E, typename F>
		class MatrixUnary : public MatrixExpression<MatrixUnary<E, F> >
		{

			typedef MatrixUnary<E, F> SelfType;
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

			CDPL_MATH_INLINE MatrixUnary(const ExpressionType& e): expr(e) {}

			CDPL_MATH_INLINE SizeType getSize1() const {
				return expr.getSize1();
			}

			CDPL_MATH_INLINE SizeType getSize2() const {
				return expr.getSize2();
			}

			CDPL_MATH_INLINE ConstReference operator()(SizeType i, SizeType j) const {
				return FunctorType::apply(expr(i, j));
			}

		private:
			ExpressionClosureType expr;
		};

		template <typename E, typename F>
		struct MatrixUnaryTraits
		{

			typedef MatrixUnary<E, F> ExpressionType;
			typedef ExpressionType ResultType;
		};
	
		template <typename E, typename F>
		class VectorMatrixUnary : public MatrixExpression<VectorMatrixUnary<E, F> >
		{

			typedef VectorMatrixUnary<E, F> SelfType;
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

			CDPL_MATH_INLINE VectorMatrixUnary(const ExpressionType& e): expr(e) {}

			CDPL_MATH_INLINE SizeType getSize1() const {
				return expr.getSize();
			}

			CDPL_MATH_INLINE SizeType getSize2() const {
				return expr.getSize();
			}

			CDPL_MATH_INLINE ConstReference operator()(SizeType i, SizeType j) const {
				return FunctorType::apply(expr, i, j);
			}

		private:
			ExpressionClosureType expr;
		};

		template <typename E, typename F>
		struct VectorMatrixUnaryTraits
		{

			typedef VectorMatrixUnary<E, F> ExpressionType;
			typedef ExpressionType ResultType;
		};

		template <typename E1, typename E2, typename F>
		class MatrixBinary1 : public MatrixExpression<MatrixBinary1<E1, E2, F> >
		{

			typedef MatrixBinary1<E1, E2, F> SelfType;
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

			CDPL_MATH_INLINE MatrixBinary1(const Expression1Type& e1, const Expression2Type& e2): expr1(e1), expr2(e2) {}

			CDPL_MATH_INLINE SizeType getSize1() const {
				return CDPL_MATH_CHECK_SIZE_EQUALITY(SizeType(expr1.getSize1()), SizeType(expr2.getSize1()), Base::SizeError);
			}

			CDPL_MATH_INLINE SizeType getSize2() const {
				return CDPL_MATH_CHECK_SIZE_EQUALITY(SizeType(expr1.getSize2()), SizeType(expr2.getSize2()), Base::SizeError);
			}

			CDPL_MATH_INLINE ConstReference operator()(SizeType i, SizeType j) const {
				return FunctorType::apply(expr1(i, j), expr2(i, j));
			}

		private:
			Expression1ClosureType expr1;
			Expression2ClosureType expr2;
		};

		template <typename E1, typename E2, typename F>
		struct MatrixBinary1Traits
		{

			typedef MatrixBinary1<E1, E2, F> ExpressionType;
			typedef ExpressionType ResultType;
		};

		template <typename E1, typename E2, typename F>
		class MatrixBinary2 : public MatrixExpression<MatrixBinary2<E1, E2, F> >
		{

			typedef MatrixBinary2<E1, E2, F> SelfType;
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

			CDPL_MATH_INLINE MatrixBinary2(const Expression1Type& e1, const Expression2Type& e2): expr1(e1), expr2(e2) {}

			CDPL_MATH_INLINE SizeType getSize1() const {
				return expr1.getSize1();
			}

			CDPL_MATH_INLINE SizeType getSize2() const {
				return expr2.getSize2();
			}

			CDPL_MATH_INLINE ConstReference operator()(SizeType i, SizeType j) const {
				return FunctorType::apply(expr1, expr2, i, j);
			}

		private:
			Expression1ClosureType expr1;
			Expression2ClosureType expr2;
		};

		template <typename E1, typename E2, typename F>
		struct MatrixBinary2Traits
		{

			typedef MatrixBinary2<E1, E2, F> ExpressionType;
			typedef ExpressionType ResultType;
		};

		template <typename E1, typename E2, typename F>
		class VectorMatrixBinary : public MatrixExpression<VectorMatrixBinary<E1, E2, F> >
		{

			typedef VectorMatrixBinary<E1, E2, F> SelfType;
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

			CDPL_MATH_INLINE VectorMatrixBinary(const Expression1Type& e1, const Expression2Type& e2): expr1(e1), expr2(e2) {}

			CDPL_MATH_INLINE SizeType getSize1() const {
				return expr1.getSize();
			}

			CDPL_MATH_INLINE SizeType getSize2() const {
				return expr2.getSize();
			}

			CDPL_MATH_INLINE ConstReference operator()(SizeType i, SizeType j) const {
				return FunctorType::apply(expr1(i), expr2(j));
			}

		private:
			Expression1ClosureType expr1;
			Expression2ClosureType expr2;
		};

		template <typename E1, typename E2, typename F>
		struct VectorMatrixBinaryTraits
		{

			typedef VectorMatrixBinary<E1, E2, F> ExpressionType;
			typedef ExpressionType ResultType;
		};

		template <typename E1, typename E2, typename F>
		class Matrix1VectorBinary : public VectorExpression<Matrix1VectorBinary<E1, E2, F> >
		{

			typedef Matrix1VectorBinary<E1, E2, F> SelfType;
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

			CDPL_MATH_INLINE Matrix1VectorBinary(const Expression1Type& e1, const Expression2Type& e2): expr1(e1), expr2(e2) {}

			CDPL_MATH_INLINE SizeType getSize() const {
				return expr1.getSize1();
			}

			CDPL_MATH_INLINE ConstReference operator()(SizeType i) const {
				return FunctorType::apply(expr1, expr2, i);
			}

			CDPL_MATH_INLINE ConstReference operator[](SizeType i) const {
				return FunctorType::apply(expr1, expr2, i);
			}

		private:
			Expression1ClosureType expr1;
			Expression2ClosureType expr2;
		};

		template <typename E1, typename E2, typename F>
		struct Matrix1VectorBinaryTraits
		{

			typedef Matrix1VectorBinary<E1, E2, F> ExpressionType;
			typedef ExpressionType ResultType;
		};

		template <typename E1, typename E2, typename F>
		class Matrix2VectorBinary : public VectorExpression<Matrix2VectorBinary<E1, E2, F> >
		{

			typedef Matrix2VectorBinary<E1, E2, F> SelfType;
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

			CDPL_MATH_INLINE Matrix2VectorBinary(const Expression1Type& e1, const Expression2Type& e2): expr1(e1), expr2(e2) {}

			CDPL_MATH_INLINE SizeType getSize() const {
				return expr2.getSize2();
			}

			CDPL_MATH_INLINE ConstReference operator()(SizeType i) const {
				return FunctorType::apply(expr1, expr2, i);
			}

			CDPL_MATH_INLINE ConstReference operator[](SizeType i) const {
				return FunctorType::apply(expr1, expr2, i);
			}

		private:
			Expression1ClosureType expr1;
			Expression2ClosureType expr2;
		};

		template <typename E1, typename E2, typename F>
		struct Matrix2VectorBinaryTraits
		{

			typedef Matrix2VectorBinary<E1, E2, F> ExpressionType;
			typedef ExpressionType ResultType;
		};

		template <typename E1, typename E2, typename F>
		class Scalar1MatrixBinary : public MatrixExpression<Scalar1MatrixBinary<E1, E2, F> >
		{

			typedef Scalar1MatrixBinary<E1, E2, F> SelfType;
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

			CDPL_MATH_INLINE Scalar1MatrixBinary(const Expression1Type& e1, const Expression2Type& e2): expr1(e1), expr2(e2) {}

			CDPL_MATH_INLINE SizeType getSize1() const {
				return expr2.getSize1();
			}

			CDPL_MATH_INLINE SizeType getSize2() const {
				return expr2.getSize2();
			}

			CDPL_MATH_INLINE ConstReference operator()(SizeType i, SizeType j) const {
				return FunctorType::apply(expr1, expr2(i, j));
			}

		private:
			Expression1ClosureType expr1;
			Expression2ClosureType expr2;
		};

		template <typename E1, typename E2, typename F>
		struct Scalar1MatrixBinaryTraits
		{

			typedef Scalar1MatrixBinary<E1, E2, F> ExpressionType;
			typedef ExpressionType ResultType;
		};

		template <typename E1, typename E2, typename F>
		class Scalar2MatrixBinary : public MatrixExpression<Scalar2MatrixBinary<E1, E2, F> >
		{

			typedef Scalar2MatrixBinary<E1, E2, F> SelfType;
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

			CDPL_MATH_INLINE Scalar2MatrixBinary(const Expression1Type& e1, const Expression2Type& e2): expr1(e1), expr2(e2) {}

			CDPL_MATH_INLINE SizeType getSize1() const {
				return expr1.getSize1();
			}

			CDPL_MATH_INLINE SizeType getSize2() const {
				return expr1.getSize2();
			}

			CDPL_MATH_INLINE ConstReference operator()(SizeType i, SizeType j) const {
				return FunctorType::apply(expr1(i, j), expr2);
			}

		private:
			Expression1ClosureType expr1;
			Expression2ClosureType expr2;
		};

		template <typename E1, typename E2, typename F>
		struct Scalar2MatrixBinaryTraits
		{

			typedef Scalar2MatrixBinary<E1, E2, F> ExpressionType;
			typedef ExpressionType ResultType;
		};

		template <typename M>
		class MatrixTranspose : public MatrixExpression<MatrixTranspose<M> >
		{

			typedef MatrixTranspose<M> SelfType;

		public:
			typedef M MatrixType;
			typedef typename M::SizeType SizeType;
			typedef typename M::DifferenceType DifferenceType;
			typedef typename M::ValueType ValueType;
			typedef typename M::ConstReference ConstReference;
			typedef typename boost::mpl::if_<boost::is_const<M>,
											 typename M::ConstReference,
											 typename M::Reference>::type Reference;
			typedef typename boost::mpl::if_<boost::is_const<M>,
											 typename M::ConstClosureType,
											 typename M::ClosureType>::type MatrixClosureType;
			typedef const SelfType ConstClosureType;
			typedef SelfType ClosureType;
			
			CDPL_MATH_INLINE explicit MatrixTranspose(MatrixType& m): data(m) {}

			CDPL_MATH_INLINE Reference operator()(SizeType i, SizeType j) {
				return data(j, i);
			}

			CDPL_MATH_INLINE ConstReference operator()(SizeType i, SizeType j) const {
				return data(j, i);
			}
	
			CDPL_MATH_INLINE SizeType getSize1() const {
				return data.getSize2();
			}

			CDPL_MATH_INLINE SizeType getSize2() const {
				return data.getSize1();
			}

			CDPL_MATH_INLINE SizeType getMaxSize() const {
				return data.getMaxSize();
			}

			CDPL_MATH_INLINE bool isEmpty() const {
				return (data.getSize1() == 0 || data.getSize2() == 0);
			}

			CDPL_MATH_INLINE MatrixClosureType& getData() {
				return data;
			}

			CDPL_MATH_INLINE const MatrixClosureType& getData() const {
				return data;
			}

			CDPL_MATH_INLINE MatrixTranspose& operator=(const MatrixTranspose& mt) {
				data.operator=(mt.data);
				return *this;
			}

			template <typename M1>
			CDPL_MATH_INLINE MatrixTranspose& operator=(const MatrixTranspose<M1>& mt) {
				data.operator=(mt.getData());
				return *this;
			}

			template <typename E>
			CDPL_MATH_INLINE MatrixTranspose& operator=(const MatrixExpression<E>& e) {
				data.operator=(MatrixTranspose<const E>(e()));
				return *this;
			}

			template <typename E>
			CDPL_MATH_INLINE MatrixTranspose& operator+=(const MatrixExpression<E>& e) {
				data.operator+=(MatrixTranspose<const E>(e()));
				return *this;
			}	

			template <typename E>
			CDPL_MATH_INLINE MatrixTranspose& operator-=(const MatrixExpression<E>& e) {
				data.operator-=(MatrixTranspose<const E>(e()));
				return *this;
			}

			template <typename T>
			CDPL_MATH_INLINE 
			typename boost::enable_if<IsScalar<T>, MatrixTranspose>::type& operator*=(const T& t) {
				data.operator*=(t);
				return *this;
			}
	
			template <typename T>
			CDPL_MATH_INLINE 
			typename boost::enable_if<IsScalar<T>, MatrixTranspose>::type& operator/=(const T& t) {
				data.operator/=(t);
				return *this;
			}
			
			template <typename E>
			CDPL_MATH_INLINE MatrixTranspose& assign(const MatrixExpression<E>& e) {
				data.assign((MatrixTranspose<const E>(e())));
				return *this;
			}

			template <typename E>
			CDPL_MATH_INLINE MatrixTranspose& plusAssign(const MatrixExpression<E>& e) {
				data.plusAssign((MatrixTranspose<const E>(e())));
				return *this;
			}

			template <typename E>
			CDPL_MATH_INLINE MatrixTranspose& minusAssign(const MatrixExpression<E>& e) {
				data.minusAssign((MatrixTranspose<const E>(e())));
				return *this;
			}
	
			CDPL_MATH_INLINE void swap(MatrixTranspose& mt) {
				data.swap(mt.data);
			}
	
			CDPL_MATH_INLINE friend void swap(MatrixTranspose& mt1, MatrixTranspose& mt2) {
				mt1.swap(mt2);
			}

		private:
			MatrixClosureType data;
		};

		template <typename M>
		struct VectorTemporaryTraits<MatrixTranspose<M> > : public VectorTemporaryTraits<M> {};

		template <typename M>
		struct VectorTemporaryTraits<const MatrixTranspose<M> > : public VectorTemporaryTraits<M> {};

		template <typename M>
		struct MatrixTemporaryTraits<MatrixTranspose<M> > : public MatrixTemporaryTraits<M> {};

		template <typename M>
		struct MatrixTemporaryTraits<const MatrixTranspose<M> > : public MatrixTemporaryTraits<M> {};

		template <typename E>
		CDPL_MATH_INLINE
		typename MatrixUnaryTraits<E, ScalarNegation<typename E::ValueType> >::ResultType 
		operator-(const MatrixExpression<E>& e)
		{
			typedef typename MatrixUnaryTraits<E, ScalarNegation<typename E::ValueType> >::ExpressionType ExpressionType;

			return ExpressionType(e());
		}
	
		template <typename E>
		CDPL_MATH_INLINE
		const E& 
		operator+(const MatrixExpression<E>& e)
		{
			return e();
		}

		template <typename E1, typename E2>
		CDPL_MATH_INLINE
		typename MatrixBinary1Traits<E1, E2, ScalarAddition<typename E1::ValueType, typename E2::ValueType> >::ResultType 
		operator+(const MatrixExpression<E1>& e1, const MatrixExpression<E2>& e2)
		{
			typedef typename MatrixBinary1Traits<E1, E2,
				ScalarAddition<typename E1::ValueType, typename E2::ValueType> >::ExpressionType ExpressionType;

			return ExpressionType(e1(), e2());
		}
	
		template <typename E1, typename E2>
		CDPL_MATH_INLINE
		typename MatrixBinary1Traits<E1, E2, ScalarSubtraction<typename E1::ValueType, typename E2::ValueType> >::ResultType 
		operator-(const MatrixExpression<E1>& e1, const MatrixExpression<E2>& e2)
		{
			typedef typename MatrixBinary1Traits<E1, E2,
				ScalarSubtraction<typename E1::ValueType, typename E2::ValueType> >::ExpressionType ExpressionType;

			return ExpressionType(e1(), e2());
		}

		template <typename E, typename T>
		CDPL_MATH_INLINE
		typename boost::enable_if<IsScalar<T>, typename Scalar2MatrixBinaryTraits<E, T, ScalarMultiplication<typename E::ValueType, T> >::ResultType>::type
		operator*(const MatrixExpression<E>& e, const T& t)
		{
			typedef typename Scalar2MatrixBinaryTraits<E, T,
				ScalarMultiplication<typename E::ValueType, T> >::ExpressionType ExpressionType;

			return ExpressionType(e(), t);
		}

		template <typename T, typename E>
		CDPL_MATH_INLINE
		typename boost::enable_if<IsScalar<T>, typename Scalar1MatrixBinaryTraits<T, E, ScalarMultiplication<T, typename E::ValueType> >::ResultType>::type 
		operator*(const T& t, const MatrixExpression<E>& e)
		{
			typedef typename Scalar1MatrixBinaryTraits<T, E,
				ScalarMultiplication<T, typename E::ValueType> >::ExpressionType ExpressionType;

			return ExpressionType(t, e());
		}

		template <typename E, typename T>
		CDPL_MATH_INLINE
		typename boost::enable_if<IsScalar<T>, typename Scalar2MatrixBinaryTraits<E, T, ScalarDivision<typename E::ValueType, T> >::ResultType>::type
		operator/(const MatrixExpression<E>& e, const T& t)
		{
			typedef typename Scalar2MatrixBinaryTraits<E, T,
				ScalarDivision<typename E::ValueType, T> >::ExpressionType ExpressionType;

			return ExpressionType(e(), t);
		}

		template <typename E1, typename E2>
		CDPL_MATH_INLINE
		typename MatrixEquality<E1, E2>::ResultType
		operator==(const MatrixExpression<E1>& e1, const MatrixExpression<E2>& e2)
		{
			return MatrixEquality<E1, E2>::apply(e1, e2);
		}

		template <typename E1, typename E2>
		CDPL_MATH_INLINE
		typename MatrixEquality<E1, E2>::ResultType
		operator!=(const MatrixExpression<E1>& e1, const MatrixExpression<E2>& e2)
		{
			return !MatrixEquality<E1, E2>::apply(e1, e2);
		}

		template <typename E1, typename E2, typename T>
		CDPL_MATH_INLINE
		typename boost::enable_if<boost::is_arithmetic<T>, typename MatrixToleranceEquality<E1, E2, T>::ResultType>::type
		equals(const MatrixExpression<E1>& e1, const MatrixExpression<E2>& e2, const T& eps)
		{
			return MatrixToleranceEquality<E1, E2, T>::apply(e1, e2, eps);
		}

		template <typename E>
		CDPL_MATH_INLINE
		typename MatrixUnaryTraits<E, ScalarConjugation<typename E::ValueType> >::ResultType 
		conj(const MatrixExpression<E>& e)
		{
			typedef typename MatrixUnaryTraits<E, ScalarConjugation<typename E::ValueType> >::ExpressionType ExpressionType;

			return ExpressionType(e());
		}

		template <typename E>
		CDPL_MATH_INLINE
		typename MatrixUnaryTraits<E, ScalarConjugation<typename E::ValueType> >::ResultType 
		herm(const MatrixExpression<E>& e)
		{
			typedef typename MatrixUnaryTraits<E, ScalarConjugation<typename E::ValueType> >::ExpressionType ExpressionType;

			return ExpressionType(e());
		}

		template <typename E>
		CDPL_MATH_INLINE
		typename MatrixUnaryTraits<E, ScalarReal<typename E::ValueType> >::ResultType 
		real(const MatrixExpression<E>& e)
		{
			typedef typename MatrixUnaryTraits<E, ScalarReal<typename E::ValueType> >::ExpressionType ExpressionType;

			return ExpressionType(e());
		}

		template <typename E>
		CDPL_MATH_INLINE
		typename MatrixUnaryTraits<E, ScalarImaginary<typename E::ValueType> >::ResultType 
		imag(const MatrixExpression<E>& e)
		{
			typedef typename MatrixUnaryTraits<E, ScalarImaginary<typename E::ValueType> >::ExpressionType ExpressionType;

			return ExpressionType(e());
		}

		template <typename E1, typename E2>
		CDPL_MATH_INLINE
		typename VectorMatrixBinaryTraits<E1, E2, ScalarMultiplication<typename E1::ValueType, typename E2::ValueType> >::ResultType 
		outerProd(const VectorExpression<E1>& e1, const VectorExpression<E2>& e2)
		{
			typedef typename VectorMatrixBinaryTraits<E1, E2,
				ScalarMultiplication<typename E1::ValueType, typename E2::ValueType> >::ExpressionType ExpressionType;

			return ExpressionType(e1(), e2());
		}

		template <typename E1, typename E2>
		CDPL_MATH_INLINE
		typename MatrixBinary1Traits<E1, E2, ScalarDivision<typename E1::ValueType, typename E2::ValueType> >::ResultType 
		elemDiv(const MatrixExpression<E1>& e1, const MatrixExpression<E2>& e2)
		{
			typedef typename MatrixBinary1Traits<E1, E2,
				ScalarDivision<typename E1::ValueType, typename E2::ValueType> >::ExpressionType ExpressionType;

			return ExpressionType(e1(), e2());
		}

		template <typename E1, typename E2>
		CDPL_MATH_INLINE
		typename MatrixBinary1Traits<E1, E2, ScalarMultiplication<typename E1::ValueType, typename E2::ValueType> >::ResultType 
		elemProd(const MatrixExpression<E1>& e1, const MatrixExpression<E2>& e2)
		{
			typedef typename MatrixBinary1Traits<E1, E2,
				ScalarMultiplication<typename E1::ValueType, typename E2::ValueType> >::ExpressionType ExpressionType;

			return ExpressionType(e1(), e2());
		}

		template <typename E1, typename E2>
		CDPL_MATH_INLINE
		typename Matrix1VectorBinaryTraits<E1, E2, MatrixVectorProduct<E1, E2> >::ResultType 
		operator*(const MatrixExpression<E1>& e1, const VectorExpression<E2>& e2)
		{
			typedef typename Matrix1VectorBinaryTraits<E1, E2, MatrixVectorProduct<E1, E2> >::ExpressionType ExpressionType;

			return ExpressionType(e1(), e2());
		}

		template <typename E1, typename E2>
		CDPL_MATH_INLINE
		typename Matrix1VectorBinaryTraits<E1, E2, MatrixVectorProduct<E1, E2> >::ResultType 
		prod(const MatrixExpression<E1>& e1, const VectorExpression<E2>& e2)
		{
			typedef typename Matrix1VectorBinaryTraits<E1, E2, MatrixVectorProduct<E1, E2> >::ExpressionType ExpressionType;

			return ExpressionType(e1(), e2());
		}

		template <typename C, typename E1, typename E2>
		CDPL_MATH_INLINE
		C& prod(const MatrixExpression<E1>& e1, const VectorExpression<E2>& e2, VectorContainer<C>& c)
		{
			return c().assign(prod(e1, e2));
		}

		template <typename E1, typename E2>
		CDPL_MATH_INLINE
		typename Matrix2VectorBinaryTraits<E1, E2, VectorMatrixProduct<E1, E2> >::ResultType 
		operator*(const VectorExpression<E1>& e1, const MatrixExpression<E2>& e2)
		{
			typedef typename Matrix2VectorBinaryTraits<E1, E2, VectorMatrixProduct<E1, E2> >::ExpressionType ExpressionType;

			return ExpressionType(e1(), e2());
		}

		template <typename E1, typename E2>
		CDPL_MATH_INLINE
		typename Matrix2VectorBinaryTraits<E1, E2, VectorMatrixProduct<E1, E2> >::ResultType 
		prod(const VectorExpression<E1>& e1, const MatrixExpression<E2>& e2)
		{
			typedef typename Matrix2VectorBinaryTraits<E1, E2, VectorMatrixProduct<E1, E2> >::ExpressionType ExpressionType;

			return ExpressionType(e1(), e2());
		}

		template <typename C, typename E1, typename E2>
		CDPL_MATH_INLINE
		C& prod(const VectorExpression<E1>& e1, const MatrixExpression<E2>& e2, VectorContainer<C>& c)
		{
			return c().assign(prod(e1, e2));
		}

		template <typename E1, typename E2>
		CDPL_MATH_INLINE
		typename MatrixBinary2Traits<E1, E2, MatrixProduct<E1, E2> >::ResultType 
		operator*(const MatrixExpression<E1>& e1, const MatrixExpression<E2>& e2)
		{
			typedef typename MatrixBinary2Traits<E1, E2, MatrixProduct<E1, E2> >::ExpressionType ExpressionType;

			return ExpressionType(e1(), e2());
		}

		template <typename E1, typename E2>
		CDPL_MATH_INLINE
		typename MatrixBinary2Traits<E1, E2, MatrixProduct<E1, E2> >::ResultType 
		prod(const MatrixExpression<E1>& e1, const MatrixExpression<E2>& e2)
		{
			typedef typename MatrixBinary2Traits<E1, E2, MatrixProduct<E1, E2> >::ExpressionType ExpressionType;

			return ExpressionType(e1(), e2());
		}
	
		template <typename C, typename E1, typename E2>
		CDPL_MATH_INLINE
		C& prod(const MatrixExpression<E1>& e1, const MatrixExpression<E2>& e2, MatrixContainer<C>& c)
		{
			return c().assign(prod(e1, e2));
		}

		template <typename E>
		CDPL_MATH_INLINE
		typename MatrixTrace<E>::ResultType
		trace(const MatrixExpression<E>& e)
		{
			return MatrixTrace<E>::apply(e);
		}

		template <typename E>
		CDPL_MATH_INLINE
		typename MatrixNorm1<E>::ResultType
		norm1(const MatrixExpression<E>& e)
		{
			return MatrixNorm1<E>::apply(e);
		}
	
		template <typename E>
		CDPL_MATH_INLINE
		typename MatrixNormFrobenius<E>::ResultType
		normFrob(const MatrixExpression<E>& e)
		{
			return MatrixNormFrobenius<E>::apply(e);
		}
	
		template <typename E>
		CDPL_MATH_INLINE
		typename MatrixNormInfinity<E>::ResultType
		normInf(const MatrixExpression<E>& e)
		{
			return MatrixNormInfinity<E>::apply(e);
		}
	
		template <typename E>
		CDPL_MATH_INLINE
		typename VectorMatrixUnaryTraits<E, DiagonalMatrixFromVector<E> >::ResultType 
		diag(const VectorExpression<E>& e)
		{
			typedef typename VectorMatrixUnaryTraits<E, DiagonalMatrixFromVector<E> >::ExpressionType ExpressionType;

			return ExpressionType(e());
		}

		template <typename E>
		CDPL_MATH_INLINE
		typename VectorMatrixUnaryTraits<E, CrossProductMatrixFromVector<E> >::ResultType 
		cross(const VectorExpression<E>& e)
		{
			typedef typename VectorMatrixUnaryTraits<E, CrossProductMatrixFromVector<E> >::ExpressionType ExpressionType;

			return ExpressionType(e());
		}

		template <typename E>
		CDPL_MATH_INLINE
		MatrixTranspose<E> trans(MatrixExpression<E>& e)
		{
			return MatrixTranspose<E>(e());
		}

		template <typename E>
		CDPL_MATH_INLINE
		MatrixTranspose<const E> trans(const MatrixExpression<E>& e)
		{
			return MatrixTranspose<const E>(e());
		}

		template <typename E>
		CDPL_MATH_INLINE
		typename MatrixElementSum<E>::ResultType
		sum(const MatrixExpression<E>& e)
		{
			return MatrixElementSum<E>::apply(e);
		}
	}
}

#endif // CDPL_MATH_MATRIXEXPRESSION_HPP
