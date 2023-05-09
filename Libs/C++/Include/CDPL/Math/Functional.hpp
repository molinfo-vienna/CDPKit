/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * Functional.hpp 
 *
 VectorEqu* Copyright (C) 2010-2011 Thomas Seidel <thomas.seidel@univie.ac.at>
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
 * \brief Definition of various functors.
 */

#ifndef CDPL_MATH_FUNCTIONAL_HPP
#define CDPL_MATH_FUNCTIONAL_HPP

#include <boost/algorithm/clamp.hpp>

#include "CDPL/Math/Check.hpp"
#include "CDPL/Math/CommonType.hpp"
#include "CDPL/Math/TypeTraits.hpp"
#include "CDPL/Base/Exceptions.hpp"


namespace CDPL
{

	namespace Math
	{

		template <typename E> class VectorExpression;
		template <typename E> class MatrixExpression;
		template <typename E> class QuaternionExpression;
		template <typename E> class GridExpression;

		template <typename T1, typename T2>
		struct ScalarBinaryAssignmentFunctor
		{

			typedef T1 Argument1Type;
			typedef const T2& Argument2Type;
		};

		template <typename T1, typename T2>
		struct ScalarAssignment : public ScalarBinaryAssignmentFunctor<T1, T2>
		{

			typedef typename ScalarBinaryAssignmentFunctor<T1, T2>::Argument1Type Argument1Type;
			typedef typename ScalarBinaryAssignmentFunctor<T1, T2>::Argument2Type Argument2Type;

			static void apply(Argument1Type t1, Argument2Type t2) {
				t1 = t2;
			}
		};

		template <typename T1, typename T2>
		struct ScalarAdditionAssignment : public ScalarBinaryAssignmentFunctor<T1, T2>
		{

			typedef typename ScalarBinaryAssignmentFunctor<T1, T2>::Argument1Type Argument1Type;
			typedef typename ScalarBinaryAssignmentFunctor<T1, T2>::Argument2Type Argument2Type;

			static void apply(Argument1Type t1, Argument2Type t2) {
				t1 += t2;
			}
		};

		template <typename T1, typename T2>
		struct ScalarSubtractionAssignment : public ScalarBinaryAssignmentFunctor<T1, T2>
		{

			typedef typename ScalarBinaryAssignmentFunctor<T1, T2>::Argument1Type Argument1Type;
			typedef typename ScalarBinaryAssignmentFunctor<T1, T2>::Argument2Type Argument2Type;

			static void apply(Argument1Type t1, Argument2Type t2) {
				t1 -= t2;
			}
		};

		template <typename T1, typename T2>
		struct ScalarMultiplicationAssignment : public ScalarBinaryAssignmentFunctor<T1, T2>
		{

			typedef typename ScalarBinaryAssignmentFunctor<T1, T2>::Argument1Type Argument1Type;
			typedef typename ScalarBinaryAssignmentFunctor<T1, T2>::Argument2Type Argument2Type;

			static void apply(Argument1Type t1, Argument2Type t2) {
				t1 *= t2;
			}
		};

		template <typename T1, typename T2>
		struct ScalarDivisionAssignment : public ScalarBinaryAssignmentFunctor<T1, T2>
		{

			typedef typename ScalarBinaryAssignmentFunctor<T1, T2>::Argument1Type Argument1Type;
			typedef typename ScalarBinaryAssignmentFunctor<T1, T2>::Argument2Type Argument2Type;

			static void apply(Argument1Type t1, Argument2Type t2) {
				t1 /= t2;
			}
		};

		template <typename T>
		struct ScalarUnaryFunctor
		{

			typedef T ValueType;
			typedef const T& ArgumentType;
			typedef ValueType ResultType;
		};

		template <typename T>
		struct ScalarNegation : public ScalarUnaryFunctor<T>
		{

			typedef typename ScalarUnaryFunctor<T>::ValueType ValueType;
			typedef typename ScalarUnaryFunctor<T>::ArgumentType ArgumentType;
			typedef typename ScalarUnaryFunctor<T>::ResultType ResultType;

			static ResultType apply(ArgumentType v) {
				return -v;
			}
		};

		template <typename T>
		struct ScalarConjugation : public ScalarUnaryFunctor<T>
		{

			typedef typename ScalarUnaryFunctor<T>::ValueType ValueType;
			typedef typename ScalarUnaryFunctor<T>::ArgumentType ArgumentType;
			typedef typename ScalarUnaryFunctor<T>::ResultType ResultType;

			static ResultType apply(ArgumentType v) {
				return TypeTraits<ValueType>::conj(v);
			}
		};

		template <typename T>
		struct ScalarRealUnaryFunctor
		{

			typedef T ValueType;
			typedef const T& ArgumentType;
			typedef typename TypeTraits<T>::RealType ResultType;
		};

		template <typename T>
		struct ScalarReal : public ScalarRealUnaryFunctor<T>
		{

			typedef typename ScalarUnaryFunctor<T>::ValueType ValueType;
			typedef typename ScalarUnaryFunctor<T>::ArgumentType ArgumentType;
			typedef typename ScalarUnaryFunctor<T>::ResultType ResultType;

			static ResultType apply(ArgumentType v) {
				return TypeTraits<ValueType>::real(v);
			}
		};

		template <typename T>
		struct ScalarImaginary : public ScalarRealUnaryFunctor<T>
		{

			typedef typename ScalarUnaryFunctor<T>::ValueType ValueType;
			typedef typename ScalarUnaryFunctor<T>::ArgumentType ArgumentType;
			typedef typename ScalarUnaryFunctor<T>::ResultType ResultType;

			static ResultType apply(ArgumentType v) {
				return TypeTraits<ValueType>::imag(v);
			}
		};

		template <typename T1, typename T2>
		struct ScalarBinaryFunctor
		{

			typedef const T1& Argument1Type;
			typedef const T2& Argument2Type;
			typedef typename CommonType<T1, T2>::Type ResultType;
		};

		template <typename T1, typename T2>
		struct ScalarAddition : public ScalarBinaryFunctor<T1, T2>
		{

			typedef typename ScalarBinaryFunctor<T1, T2>::Argument1Type Argument1Type;
			typedef typename ScalarBinaryFunctor<T1, T2>::Argument2Type Argument2Type;
			typedef typename ScalarBinaryFunctor<T1, T2>::ResultType ResultType;

			static ResultType apply(Argument1Type t1, Argument2Type t2) {
				return (t1 + t2);
			}
		};

		template <typename T1, typename T2>
		struct ScalarSubtraction : public ScalarBinaryFunctor<T1, T2>
		{

			typedef typename ScalarBinaryFunctor<T1, T2>::Argument1Type Argument1Type;
			typedef typename ScalarBinaryFunctor<T1, T2>::Argument2Type Argument2Type;
			typedef typename ScalarBinaryFunctor<T1, T2>::ResultType ResultType;

			static ResultType apply(Argument1Type t1, Argument2Type t2) {
				return (t1 - t2);
			}
		};

		template <typename T1, typename T2>
		struct ScalarMultiplication : public ScalarBinaryFunctor<T1, T2>
		{

			typedef typename ScalarBinaryFunctor<T1, T2>::Argument1Type Argument1Type;
			typedef typename ScalarBinaryFunctor<T1, T2>::Argument2Type Argument2Type;
			typedef typename ScalarBinaryFunctor<T1, T2>::ResultType ResultType;

			static ResultType apply(Argument1Type t1, Argument2Type t2) {
				return (t1 * t2);
			}
		};

		template <typename T1, typename T2>
		struct ScalarDivision : public ScalarBinaryFunctor<T1, T2>
		{

			typedef typename ScalarBinaryFunctor<T1, T2>::Argument1Type Argument1Type;
			typedef typename ScalarBinaryFunctor<T1, T2>::Argument2Type Argument2Type;
			typedef typename ScalarBinaryFunctor<T1, T2>::ResultType ResultType;

			static ResultType apply(Argument1Type t1, Argument2Type t2) {
				return (t1 / t2);
			}
		};

		template <typename V1, typename V2>
		struct VectorScalarBinaryFunctor
		{

			typedef typename CommonType<typename V1::ValueType, typename V2::ValueType>::Type ResultType;
		};

		template <typename V1, typename V2>
		struct VectorInnerProduct : public VectorScalarBinaryFunctor<V1, V2>
		{

			typedef typename VectorScalarBinaryFunctor<V1, V2>::ResultType ResultType;

			static ResultType apply(const VectorExpression<V1>& e1, const VectorExpression<V2>& e2) {
				typedef typename CommonType<typename V1::SizeType, typename V2::SizeType>::Type SizeType;

				SizeType size = CDPL_MATH_CHECK_SIZE_EQUALITY(SizeType(e1().getSize()), SizeType(e2().getSize()), Base::SizeError);
				ResultType res = ResultType();

				for (SizeType i = 0; i < size; i++) 
					res += e1()(i) * e2()(i);

				return res;
			}
		};

		template <typename V1, typename V2, typename T>
		struct VectorAngleCosine : public VectorScalarBinaryFunctor<V1, V2>
		{

			typedef typename CommonType<typename VectorInnerProduct<V1, V2>::ResultType, T>::Type ResultType;

			static ResultType apply(const VectorExpression<V1>& e1, const VectorExpression<V2>& e2, const T& sd, bool clamp) {
				ResultType res = VectorInnerProduct<V1, V2>::apply(e1, e2) / sd;
				
				if (!clamp)
					return res;

				return boost::algorithm::clamp(res, ResultType(-1), ResultType(1));
			}
		};

		template <typename V1, typename V2>
		struct VectorBooleanBinaryFunctor
		{

			typedef bool ResultType;
			typedef typename CommonType<typename V1::SizeType, typename V2::SizeType>::Type SizeType;
			typedef typename CommonType<typename V1::ValueType, typename V2::ValueType>::Type ValueType;
		};

		template <typename V1, typename V2>
		struct VectorEquality : public VectorBooleanBinaryFunctor<V1, V2>
		{

			typedef typename VectorBooleanBinaryFunctor<V1, V2>::SizeType SizeType;
			typedef typename VectorBooleanBinaryFunctor<V1, V2>::ValueType ValueType;
			typedef typename VectorBooleanBinaryFunctor<V1, V2>::ResultType ResultType;

			static ResultType apply(const VectorExpression<V1>& e1, const VectorExpression<V2>& e2) {
				if (SizeType(e1().getSize()) != SizeType(e2().getSize()))
					return false;

				for (SizeType i = 0, size = e1().getSize(); i < size; i++)
					if (ValueType(e1()(i)) != ValueType(e2()(i)))
						return false;

				return true;
			}
		};
	
		template <typename V1, typename V2, typename T>
		struct Scalar3VectorBooleanTernaryFunctor
		{

			typedef bool ResultType;
			typedef const T& Argument3Type;
			typedef typename CommonType<typename V1::SizeType, typename V2::SizeType>::Type SizeType;
			typedef typename CommonType<typename V1::ValueType, typename V2::ValueType>::Type ValueType;
		};

		template <typename V1, typename V2, typename T>
		struct VectorToleranceEquality : public Scalar3VectorBooleanTernaryFunctor<V1, V2, T>
		{

			typedef typename Scalar3VectorBooleanTernaryFunctor<V1, V2, T>::SizeType SizeType;
			typedef typename Scalar3VectorBooleanTernaryFunctor<V1, V2, T>::ValueType ValueType;
			typedef typename Scalar3VectorBooleanTernaryFunctor<V1, V2, T>::ResultType ResultType;
			typedef typename Scalar3VectorBooleanTernaryFunctor<V1, V2, T>::Argument3Type Argument3Type;

			static ResultType apply(const VectorExpression<V1>& e1, const VectorExpression<V2>& e2, Argument3Type epsilon) {
				typedef typename CommonType<typename TypeTraits<ValueType>::RealType, T>::Type ComparisonType;

				if (SizeType(e1().getSize()) != SizeType(e2().getSize()))
					return false;

				ComparisonType norm_inf_max(epsilon);

				for (SizeType i = 0, size = e1().getSize(); i < size; i++)
					if (ComparisonType(TypeTraits<ValueType>::normInf(e2()(i) - e1()(i))) > norm_inf_max)
						return false;

				return true;
			}
		};

		template <typename V1, typename V2>
		struct VectorBinaryFunctor
		{

			typedef typename CommonType<typename V1::ValueType, typename V2::ValueType>::Type ResultType;
		};

		template <typename V1, typename V2>
		struct VectorCrossProduct : public VectorBinaryFunctor<V1, V2>
		{

			typedef typename VectorScalarBinaryFunctor<V1, V2>::ResultType ResultType;

			template <typename E1, typename E2, typename SizeType>
			static ResultType apply(const VectorExpression<E1>& e1, const VectorExpression<E2>& e2, SizeType i) {
				CDPL_MATH_CHECK(e1().getSize() == 3, "Invalid vector size", Base::SizeError); 
				CDPL_MATH_CHECK(e2().getSize() == 3, "Invalid vector size", Base::SizeError); 

				switch (i) {
			
					case 0:
						return (e1()(1) * e2()(2) - e1()(2) * e2()(1)); // c1 = a2 * b3 - a3 * b2; 
				
					case 1:
						return (e1()(2) * e2()(0) - e1()(0) * e2()(2)); // c2 = a3 * b1 - a1 * b3; 

					case 2:
						return (e1()(0) * e2()(1) - e1()(1) * e2()(0)); // c3 = a1 * b2 - a2 * b1; 

					default:
						return ResultType();
				}
			}
		};

		template <typename V>
		struct VectorScalarUnaryFunctor
		{

			typedef typename V::ValueType ResultType;
			typedef typename V::SizeType SizeType;
		};

		template <typename V>
		struct VectorElementSum : public VectorScalarUnaryFunctor<V>
		{
			
			typedef typename VectorScalarUnaryFunctor<V>::ResultType ResultType;

			static ResultType apply(const VectorExpression<V>& e) {
				typedef typename V::SizeType SizeType;

				ResultType res = ResultType();

				for (SizeType i = 0, size = e().getSize(); i < size; i++) 
					res += e()(i);

				return res;
			}
		};

		template <typename V>
		struct VectorScalarRealUnaryFunctor
		{

			typedef typename V::ValueType ValueType;
			typedef typename TypeTraits<ValueType>::RealType RealType;
			typedef RealType ResultType;
		};

		template <typename V>
		struct VectorNorm1 : public VectorScalarRealUnaryFunctor<V>
		{
			
			typedef typename VectorScalarRealUnaryFunctor<V>::ValueType ValueType;
			typedef typename VectorScalarRealUnaryFunctor<V>::RealType RealType;
			typedef typename VectorScalarRealUnaryFunctor<V>::ResultType ResultType;

			static ResultType apply(const VectorExpression<V>& e) {
				typedef typename V::SizeType SizeType;

				RealType res = RealType();

				for (SizeType i = 0, size = e().getSize(); i < size; i++)
					res += TypeTraits<ValueType>::norm1(e()(i));

				return res;
			}
		};

		template <typename V>
		struct VectorNorm2 : public VectorScalarRealUnaryFunctor<V>
		{
			
			typedef typename VectorScalarRealUnaryFunctor<V>::ValueType ValueType;
			typedef typename VectorScalarRealUnaryFunctor<V>::RealType RealType;
			typedef typename VectorScalarRealUnaryFunctor<V>::ResultType ResultType;

			static ResultType apply(const VectorExpression<V>& e) {
				typedef typename V::SizeType SizeType;

				RealType res2 = RealType();

				for (SizeType i = 0, size = e().getSize(); i < size; i++) { 
					RealType t = TypeTraits<ValueType>::norm2(e()(i));

					res2 += t * t;
				}

				return TypeTraits<RealType>::sqrt(res2);
			}
		};

		template <typename V>
		struct VectorNormInfinity : public VectorScalarRealUnaryFunctor<V>
		{
			
			typedef typename VectorScalarRealUnaryFunctor<V>::ValueType ValueType;
			typedef typename VectorScalarRealUnaryFunctor<V>::RealType RealType;
			typedef typename VectorScalarRealUnaryFunctor<V>::ResultType ResultType;

			static ResultType apply(const VectorExpression<V>& e) {
				typedef typename V::SizeType SizeType;

				RealType res = RealType();

				for (SizeType i = 0, size = e().getSize(); i < size; i++) { 
					RealType t = TypeTraits<ValueType>::normInf(e()(i));

					if (t > res)
						res = t;
				}

				return res;
			}
		};

		template <typename V>
		struct VectorScalarIndexUnaryFunctor
		{

			typedef typename V::ValueType ValueType;
			typedef typename TypeTraits<ValueType>::RealType RealType;
			typedef typename V::SizeType ResultType;
		};

		template <typename V>
		struct VectorNormInfinityIndex : public VectorScalarIndexUnaryFunctor<V>
		{
			
			typedef typename VectorScalarIndexUnaryFunctor<V>::ValueType ValueType;
			typedef typename VectorScalarIndexUnaryFunctor<V>::RealType RealType;
			typedef typename VectorScalarIndexUnaryFunctor<V>::ResultType ResultType;

			static ResultType apply(const VectorExpression<V>& e) {
				typedef typename V::SizeType SizeType;

				RealType norm = RealType();
				ResultType res = ResultType(0);

				for (SizeType i = 0, size = e().getSize(); i < size; i++) { 
					RealType t = TypeTraits<ValueType>::normInf(e()(i));

					if (t > norm) {
						norm = t;
						res = ResultType(i);
					}
				}

				return res;
			}
		};

		template <typename M1, typename M2>
		struct MatrixBooleanBinaryFunctor
		{

			typedef bool ResultType;
			typedef typename CommonType<typename M1::SizeType, typename M2::SizeType>::Type SizeType;
			typedef typename CommonType<typename M1::ValueType, typename M2::ValueType>::Type ValueType;
		};

		template <typename M1, typename M2>
		struct MatrixEquality : public MatrixBooleanBinaryFunctor<M1, M2>
		{

			typedef typename MatrixBooleanBinaryFunctor<M1, M2>::SizeType SizeType;
			typedef typename MatrixBooleanBinaryFunctor<M1, M2>::ValueType ValueType;
			typedef typename MatrixBooleanBinaryFunctor<M1, M2>::ResultType ResultType;

			static ResultType apply(const MatrixExpression<M1>& e1, const MatrixExpression<M2>& e2) {
				if (SizeType(e1().getSize1()) != SizeType(e2().getSize1()))
					return false;

				if (SizeType(e1().getSize2()) != SizeType(e2().getSize2()))
					return false;

				for (SizeType i = 0, size1 = e1().getSize1(); i < size1; i++)
					for (SizeType j = 0, size2 = e1().getSize2(); j < size2; j++)
						if (ValueType(e1()(i, j)) != ValueType(e2()(i, j)))
							return false;

				return true;
			}
		};

		template <typename M1, typename M2, typename T>
		struct Scalar3MatrixBooleanTernaryFunctor
		{

			typedef bool ResultType;
			typedef const T& Argument3Type;
			typedef typename CommonType<typename M1::SizeType, typename M2::SizeType>::Type SizeType;
			typedef typename CommonType<typename M1::ValueType, typename M2::ValueType>::Type ValueType;
		};

		template <typename M1, typename M2, typename T>
		struct MatrixToleranceEquality : public Scalar3MatrixBooleanTernaryFunctor<M1, M2, T>
		{

			typedef typename Scalar3MatrixBooleanTernaryFunctor<M1, M2, T>::SizeType SizeType;
			typedef typename Scalar3MatrixBooleanTernaryFunctor<M1, M2, T>::ValueType ValueType;
			typedef typename Scalar3MatrixBooleanTernaryFunctor<M1, M2, T>::ResultType ResultType;
			typedef typename Scalar3MatrixBooleanTernaryFunctor<M1, M2, T>::Argument3Type Argument3Type;

			static ResultType apply(const MatrixExpression<M1>& e1, const MatrixExpression<M2>& e2, Argument3Type epsilon) {
				typedef typename CommonType<typename TypeTraits<ValueType>::RealType, T>::Type ComparisonType;

				if (SizeType(e1().getSize1()) != SizeType(e2().getSize1()))
					return false;

				if (SizeType(e1().getSize2()) != SizeType(e2().getSize2()))
					return false;

				ComparisonType norm_inf_max(epsilon);

				for (SizeType i = 0, size1 = e1().getSize1(); i < size1; i++)
					for (SizeType j = 0, size2 = e1().getSize2(); j < size2; j++)
					if (ComparisonType(TypeTraits<ValueType>::normInf(e2()(i, j) - e1()(i, j))) > norm_inf_max)
						return false;

				return true;
			}
		};

		template <typename M>
		struct MatrixScalarUnaryFunctor
		{

			typedef typename M::ValueType ResultType;
		};

		template <typename M>
		struct MatrixElementSum : public MatrixScalarUnaryFunctor<M>
		{
			
			typedef typename MatrixScalarUnaryFunctor<M>::ResultType ResultType;

			static ResultType apply(const MatrixExpression<M>& e) {
				typedef typename M::SizeType SizeType;

				ResultType res = ResultType();
				SizeType size1 = e().getSize1();
				SizeType size2 = e().getSize2();

				for (SizeType i = 0; i < size1; i++) 
					for (SizeType j = 0; j < size2; j++) 
						res += e()(i, j);

				return res;
			}
		};

		template <typename M>
		struct MatrixTrace : public MatrixScalarUnaryFunctor<M>
		{
			
			typedef typename MatrixScalarUnaryFunctor<M>::ResultType ResultType;

			static ResultType apply(const MatrixExpression<M>& e) {
				typedef typename M::SizeType SizeType;

				SizeType size = CDPL_MATH_CHECK_SIZE_EQUALITY(e().getSize1(), e().getSize2(), Base::SizeError);
				ResultType res = ResultType();

				for (SizeType i = 0; i < size; i++) 
					res += e()(i, i);

				return res;
			}
		};

		template <typename M>
		struct MatrixScalarRealUnaryFunctor
		{

			typedef typename M::ValueType ValueType;
			typedef typename TypeTraits<ValueType>::RealType RealType;
			typedef RealType ResultType;
		};

		template <typename M>
		struct MatrixNorm1 : public MatrixScalarRealUnaryFunctor<M>
		{
			
			typedef typename MatrixScalarRealUnaryFunctor<M>::ValueType ValueType;
			typedef typename MatrixScalarRealUnaryFunctor<M>::RealType RealType;
			typedef typename MatrixScalarRealUnaryFunctor<M>::ResultType ResultType;

			static ResultType apply(const MatrixExpression<M>& e) {
				typedef typename M::SizeType SizeType;

				RealType res = RealType();
				SizeType size1 = e().getSize1();
				SizeType size2 = e().getSize2();

				for (SizeType j = 0; j < size2; j++) { 
					RealType t = RealType();

					for (SizeType i = 0; i < size1; i++)  
						t += TypeTraits<ValueType>::norm1(e()(i, j));

					if (t > res)
						res = t;
				}

				return res;
			}
		};

		template <typename M>
		struct MatrixNormFrobenius : public MatrixScalarRealUnaryFunctor<M>
		{
			
			typedef typename MatrixScalarRealUnaryFunctor<M>::ValueType ValueType;
			typedef typename MatrixScalarRealUnaryFunctor<M>::RealType RealType;
			typedef typename MatrixScalarRealUnaryFunctor<M>::ResultType ResultType;

			static ResultType apply(const MatrixExpression<M>& e) {
				typedef typename M::SizeType SizeType;

				RealType res2 = RealType();
				SizeType size1 = e().getSize1();
				SizeType size2 = e().getSize2();

				for (SizeType i = 0; i < size1; i++) {
					for (SizeType j = 0; j < size2; j++) { 
						RealType t = TypeTraits<ValueType>::norm2(e()(i, j));

						res2 += t * t;
					}
				}

				return TypeTraits<RealType>::sqrt(res2);
			}
		};

		template <typename M>
		struct MatrixNormInfinity : public MatrixScalarRealUnaryFunctor<M>
		{
			
			typedef typename MatrixScalarRealUnaryFunctor<M>::ValueType ValueType;
			typedef typename MatrixScalarRealUnaryFunctor<M>::RealType RealType;
			typedef typename MatrixScalarRealUnaryFunctor<M>::ResultType ResultType;

			static ResultType apply(const MatrixExpression<M>& e) {
				typedef typename M::SizeType SizeType;

				RealType res = RealType();
				SizeType size1 = e().getSize1();
				SizeType size2 = e().getSize2();

				for (SizeType i = 0; i < size1; i++) {
					RealType t = RealType();

					for (SizeType j = 0; j < size2; j++) 
						t += TypeTraits<ValueType>::normInf(e()(i, j));

					if (t > res)
						res = t;
				}

				return res;
			}
		};

		template <typename V>
		struct VectorMatrixUnaryFunctor
		{

			typedef typename V::ValueType ResultType;
			typedef typename V::SizeType SizeType;
		};

		template <typename V>
		struct DiagonalMatrixFromVector : public VectorMatrixUnaryFunctor<V>
		{
			
			typedef typename VectorScalarUnaryFunctor<V>::ResultType ResultType;
			typedef typename VectorScalarUnaryFunctor<V>::SizeType SizeType;

			template <typename E>
			static ResultType apply(const VectorExpression<E>& e, SizeType i, SizeType j) {
				if (i == j)
					return e()(i);

				return ResultType();
			}
		};

		template <typename V>
		struct CrossProductMatrixFromVector : public VectorMatrixUnaryFunctor<V>
		{
			
			typedef typename VectorScalarUnaryFunctor<V>::ResultType ResultType;
			typedef typename VectorScalarUnaryFunctor<V>::SizeType SizeType;

			template <typename E>
			static ResultType apply(const VectorExpression<E>& e, SizeType i, SizeType j) {
				CDPL_MATH_CHECK(e().getSize() == 3, "Invalid vector size", Base::SizeError);

				//                       |  0  -a3  a2 |
				// cross([a1, a2, a3]) = |  a3  0  -a1 |
				//                       | -a2  a1  0  |
				switch (i) {

					case 0:
						switch (j) {

							case 1:
								return -e()(2);

							case 2:
								return e()(1);

							default:
								return ResultType();
						}
					
					case 1:
						switch (j) {

							case 0:
								return e()(2);

							case 2:
								return -e()(0);

							default:
								return ResultType();
						}

					case 2:
						switch (j) {

							case 0:
								return -e()(1);

							case 1:
								return e()(0);

							default:
								return ResultType();
						}

					default:
						return ResultType();
				}
			}
		};

		template <typename M, typename V>
		struct MatrixVectorBinaryFunctor
		{

			typedef typename CommonType<typename M::ValueType, typename V::ValueType>::Type ValueType;
			typedef typename CommonType<typename M::SizeType, typename V::SizeType>::Type SizeType;
			typedef ValueType ResultType;
		};

		template <typename M, typename V>
		struct MatrixVectorProduct : public MatrixVectorBinaryFunctor<M, V>
		{

			typedef typename MatrixVectorBinaryFunctor<M, V>::ValueType ValueType;
			typedef typename MatrixVectorBinaryFunctor<M, V>::SizeType SizeType;
			typedef typename MatrixVectorBinaryFunctor<M, V>::ResultType ResultType;

			template <typename E1, typename E2>
			static ResultType apply(const MatrixExpression<E1>& e1, const VectorExpression<E2>& e2, SizeType i) {
				SizeType size = CDPL_MATH_CHECK_SIZE_EQUALITY(SizeType(e1().getSize2()), SizeType(e2().getSize()), Base::SizeError);
				ResultType res = ResultType();

				for (SizeType j = 0; j < size; j++)
					res += e1()(i, j) * e2()(j);

				return res;
			}
		};

		template <typename V, typename M>
		struct VectorMatrixProduct : public MatrixVectorBinaryFunctor<M, V>
		{

			typedef typename MatrixVectorBinaryFunctor<M, V>::ValueType ValueType;
			typedef typename MatrixVectorBinaryFunctor<M, V>::SizeType SizeType;
			typedef typename MatrixVectorBinaryFunctor<M, V>::ResultType ResultType;

			template <typename E1, typename E2>
			static ResultType apply(const VectorExpression<E1>& e1, const MatrixExpression<E2>& e2, SizeType i) {
				SizeType size = CDPL_MATH_CHECK_SIZE_EQUALITY(SizeType(e1().getSize()), SizeType(e2().getSize1()), Base::SizeError);
				ResultType res = ResultType();

				for (SizeType j = 0; j < size; j++)
					res += e1()(j) * e2()(j, i);

				return res;
			}
		};

		template <typename M1, typename M2>
		struct MatrixBinaryFunctor
		{

			typedef typename CommonType<typename M1::ValueType, typename M2::ValueType>::Type ValueType;
			typedef typename CommonType<typename M1::SizeType, typename M2::SizeType>::Type SizeType;
			typedef ValueType ResultType;
		};

		template <typename M1, typename M2>
		struct MatrixProduct : public MatrixBinaryFunctor<M1, M2>
		{

			typedef typename MatrixVectorBinaryFunctor<M1, M2>::ValueType ValueType;
			typedef typename MatrixVectorBinaryFunctor<M1, M2>::SizeType SizeType;
			typedef typename MatrixVectorBinaryFunctor<M1, M2>::ResultType ResultType;

			template <typename E1, typename E2>
			static ResultType apply(const MatrixExpression<E1>& e1, const MatrixExpression<E2>& e2, SizeType i, SizeType j) {
				SizeType size = CDPL_MATH_CHECK_SIZE_EQUALITY(SizeType(e1().getSize2()), SizeType(e2().getSize1()), Base::SizeError);
				ResultType res = ResultType();

				for (SizeType k = 0; k < size; k++)
					res += e1()(i, k) * e2()(k, j);

				return res;
			}
		};

		template <typename Q1, typename Q2>
		struct QuaternionBooleanBinaryFunctor
		{

			typedef bool ResultType;
			typedef typename CommonType<typename Q1::ValueType, typename Q2::ValueType>::Type ValueType;
		};

		template <typename Q1, typename Q2>
		struct QuaternionEquality : public QuaternionBooleanBinaryFunctor<Q1, Q2>
		{

			typedef typename QuaternionBooleanBinaryFunctor<Q1, Q2>::ValueType ValueType;
			typedef typename QuaternionBooleanBinaryFunctor<Q1, Q2>::ResultType ResultType;

			static ResultType apply(const QuaternionExpression<Q1>& e1, const QuaternionExpression<Q2>& e2) {
				return (ValueType(e1().getC1()) == ValueType(e2().getC1())
						&& ValueType(e1().getC2()) == ValueType(e2().getC2())
						&& ValueType(e1().getC3()) == ValueType(e2().getC3())
						&& ValueType(e1().getC4()) == ValueType(e2().getC4()));
			}
		};

		template <typename Q1, typename Q2, typename T>
		struct Scalar3QuaternionBooleanTernaryFunctor
		{

			typedef bool ResultType;
			typedef const T& Argument3Type;
			typedef typename CommonType<typename Q1::ValueType, typename Q2::ValueType>::Type ValueType;
		};

		template <typename Q1, typename Q2, typename T>
		struct QuaternionToleranceEquality : public Scalar3QuaternionBooleanTernaryFunctor<Q1, Q2, T>
		{

			typedef typename Scalar3QuaternionBooleanTernaryFunctor<Q1, Q2, T>::ValueType ValueType;
			typedef typename Scalar3QuaternionBooleanTernaryFunctor<Q1, Q2, T>::ResultType ResultType;
			typedef typename Scalar3QuaternionBooleanTernaryFunctor<Q1, Q2, T>::Argument3Type Argument3Type;

			static ResultType apply(const QuaternionExpression<Q1>& e1, const QuaternionExpression<Q2>& e2, Argument3Type epsilon) {
				typedef typename CommonType<typename TypeTraits<ValueType>::RealType, T>::Type ComparisonType;

				ComparisonType norm_inf_max(epsilon);

				return (ComparisonType(TypeTraits<ValueType>::normInf(e2().getC1() - e1().getC1())) <= norm_inf_max
						&& ComparisonType(TypeTraits<ValueType>::normInf(e2().getC2() - e1().getC2())) <= norm_inf_max
						&& ComparisonType(TypeTraits<ValueType>::normInf(e2().getC3() - e1().getC3())) <= norm_inf_max
						&& ComparisonType(TypeTraits<ValueType>::normInf(e2().getC4() - e1().getC4())) <= norm_inf_max);
			}
		};

		template <typename Q>
		struct QuaternionScalarUnaryFunctor
		{

			typedef typename Q::ValueType ResultType;
		};

		template <typename Q>
		struct QuaternionElementSum : public QuaternionScalarUnaryFunctor<Q>
		{
			
			typedef typename QuaternionScalarUnaryFunctor<Q>::ResultType ResultType;

			static ResultType apply(const QuaternionExpression<Q>& e) {
				return (e().getC1() + e().getC2() + e().getC3() + e().getC4());
			}
		};

		template <typename Q>
		struct QuaternionScalarRealUnaryFunctor
		{

			typedef typename Q::ValueType ValueType;
			typedef ValueType RealType;
			typedef RealType ResultType;
		};

		template <typename Q>
		struct QuaternionNorm : public QuaternionScalarRealUnaryFunctor<Q>
		{
			
			typedef typename QuaternionScalarRealUnaryFunctor<Q>::ValueType ValueType;
			typedef typename QuaternionScalarRealUnaryFunctor<Q>::RealType RealType;
			typedef typename QuaternionScalarRealUnaryFunctor<Q>::ResultType ResultType;

			static ResultType apply(const QuaternionExpression<Q>& e) {
				RealType t = e().getC1() * e().getC1() +
					e().getC2() * e().getC2() +
					e().getC3() * e().getC3() +
					e().getC4() * e().getC4();

				return TypeTraits<RealType>::sqrt(t);
			}
		};

		template <typename Q>
		struct QuaternionNorm2 : public QuaternionScalarRealUnaryFunctor<Q>
		{
			
			typedef typename QuaternionScalarRealUnaryFunctor<Q>::ValueType ValueType;
			typedef typename QuaternionScalarRealUnaryFunctor<Q>::RealType RealType;
			typedef typename QuaternionScalarRealUnaryFunctor<Q>::ResultType ResultType;

			static ResultType apply(const QuaternionExpression<Q>& e) {
				RealType t = e().getC1() * e().getC1() +
					e().getC2() * e().getC2() +
					e().getC3() * e().getC3() +
					e().getC4() * e().getC4();

				return t;
			}
		};

		template <typename Q>
		struct QuaternionUnaryFunctor
		{

			typedef typename Q::ValueType ResultType;
		};

		template <typename Q>
		struct QuaternionUnreal : public QuaternionUnaryFunctor<Q>
		{

			typedef typename QuaternionUnaryFunctor<Q>::ResultType ResultType;

			template <typename E>
			static ResultType applyC1(const QuaternionExpression<E>& e)
			{
				return ResultType();
			}

			template <typename E>
			static ResultType applyC2(const QuaternionExpression<E>& e)
			{
				return e().getC2();
			}

			template <typename E>
			static ResultType applyC3(const QuaternionExpression<E>& e)
			{
				return e().getC3();
			}

			template <typename E>
			static ResultType applyC4(const QuaternionExpression<E>& e)
			{
				return e().getC4();
			}
		};

		template <typename Q>
		struct QuaternionConjugate : public QuaternionUnaryFunctor<Q>
		{

			typedef typename QuaternionUnaryFunctor<Q>::ResultType ResultType;

			template <typename E>
			static ResultType applyC1(const QuaternionExpression<E>& e)
			{
				return e().getC1();
			}

			template <typename E>
			static ResultType applyC2(const QuaternionExpression<E>& e)
			{
				return -e().getC2();
			}

			template <typename E>
			static ResultType applyC3(const QuaternionExpression<E>& e)
			{
				return -e().getC3();
			}

			template <typename E>
			static ResultType applyC4(const QuaternionExpression<E>& e)
			{
				return -e().getC4();
			}
		};

		template <typename T, typename Q>
		struct Scalar1QuaternionBinaryFunctor
		{

			typedef typename CommonType<T, typename Q::ValueType>::Type ResultType;
			typedef const T& Argument1Type;
		};

		template <typename T, typename Q>
		struct Scalar1QuaternionAddition : public Scalar1QuaternionBinaryFunctor<T, Q>
		{

			typedef typename Scalar1QuaternionBinaryFunctor<T, Q>::Argument1Type Argument1Type;
			typedef typename Scalar1QuaternionBinaryFunctor<T, Q>::ResultType ResultType;

			template <typename E>
			static ResultType applyC1(Argument1Type t, const QuaternionExpression<E>& e)
			{
				return (t + e().getC1());
			}

			template <typename E>
			static ResultType applyC2(Argument1Type, const QuaternionExpression<E>& e)
			{
				return e().getC2();
			}

			template <typename E>
			static ResultType applyC3(Argument1Type, const QuaternionExpression<E>& e)
			{
				return e().getC3();
			}

			template <typename E>
			static ResultType applyC4(Argument1Type, const QuaternionExpression<E>& e)
			{
				return e().getC4();
			}
		};

		template <typename T, typename Q>
		struct Scalar1QuaternionSubtraction : public Scalar1QuaternionBinaryFunctor<T, Q>
		{

			typedef typename Scalar1QuaternionBinaryFunctor<T, Q>::Argument1Type Argument1Type;
			typedef typename Scalar1QuaternionBinaryFunctor<T, Q>::ResultType ResultType;

			template <typename E>
			static ResultType applyC1(Argument1Type t, const QuaternionExpression<E>& e)
			{
				return (t - e().getC1());
			}

			template <typename E>
			static ResultType applyC2(Argument1Type, const QuaternionExpression<E>& e)
			{
				return -e().getC2();
			}

			template <typename E>
			static ResultType applyC3(Argument1Type, const QuaternionExpression<E>& e)
			{
				return -e().getC3();
			}

			template <typename E>
			static ResultType applyC4(Argument1Type, const QuaternionExpression<E>& e)
			{
				return -e().getC4();
			}
		};

		template <typename Q, typename T>
		struct Scalar2QuaternionBinaryFunctor
		{

			typedef typename CommonType<typename Q::ValueType, T>::Type ResultType;
			typedef const T& Argument2Type;
		};

		template <typename Q, typename T>
		struct Scalar2QuaternionAddition : public Scalar2QuaternionBinaryFunctor<Q, T>
		{

			typedef typename Scalar2QuaternionBinaryFunctor<Q, T>::Argument2Type Argument2Type;
			typedef typename Scalar2QuaternionBinaryFunctor<Q, T>::ResultType ResultType;

			template <typename E>
			static ResultType applyC1(const QuaternionExpression<E>& e, Argument2Type t)
			{
				return (e().getC1() + t);
			}

			template <typename E>
			static ResultType applyC2(const QuaternionExpression<E>& e, Argument2Type)
			{
				return e().getC2();
			}

			template <typename E>
			static ResultType applyC3(const QuaternionExpression<E>& e, Argument2Type)
			{
				return e().getC3();
			}

			template <typename E>
			static ResultType applyC4(const QuaternionExpression<E>& e, Argument2Type)
			{
				return e().getC4();
			}
		};

		template <typename Q, typename T>
		struct Scalar2QuaternionSubtraction : public Scalar2QuaternionBinaryFunctor<Q, T>
		{

			typedef typename Scalar2QuaternionBinaryFunctor<Q, T>::Argument2Type Argument2Type;
			typedef typename Scalar2QuaternionBinaryFunctor<Q, T>::ResultType ResultType;

			template <typename E>
			static ResultType applyC1(const QuaternionExpression<E>& e, Argument2Type t)
			{
				return (e().getC1() - t);
			}

			template <typename E>
			static ResultType applyC2(const QuaternionExpression<E>& e, Argument2Type)
			{
				return e().getC2();
			}

			template <typename E>
			static ResultType applyC3(const QuaternionExpression<E>& e, Argument2Type)
			{
				return e().getC3();
			}

			template <typename E>
			static ResultType applyC4(const QuaternionExpression<E>& e, Argument2Type)
			{
				return e().getC4();
			}
		};

		template <typename Q, typename T>
		struct QuaternionInverse : public Scalar2QuaternionBinaryFunctor<Q, T>
		{

			typedef typename Scalar2QuaternionBinaryFunctor<Q, T>::Argument2Type Argument2Type;
			typedef typename Scalar2QuaternionBinaryFunctor<Q, T>::ResultType ResultType;

			template <typename E>
			static ResultType applyC1(const QuaternionExpression<E>& e, Argument2Type n2)
			{
				return (e().getC1() / n2);
			}

			template <typename E>
			static ResultType applyC2(const QuaternionExpression<E>& e, Argument2Type n2)
			{
				return (-e().getC2() / n2);
			}

			template <typename E>
			static ResultType applyC3(const QuaternionExpression<E>& e, Argument2Type n2)
			{
				return (-e().getC3() / n2);
			}

			template <typename E>
			static ResultType applyC4(const QuaternionExpression<E>& e, Argument2Type n2)
			{
				return (-e().getC4() / n2);
			}
		};

		template <typename Q1, typename Q2>
		struct QuaternionBinaryFunctor
		{

			typedef typename CommonType<typename Q1::ValueType, typename Q2::ValueType>::Type ResultType;
		};

		template <typename Q1, typename Q2>
		struct QuaternionProduct : public QuaternionBinaryFunctor<Q1, Q2>
		{

			typedef typename QuaternionBinaryFunctor<Q1, Q2>::ResultType ResultType;

			template <typename E1, typename E2>
			static ResultType applyC1(const QuaternionExpression<E1>& e1, const QuaternionExpression<E2>& e2)
			{
				// a = a1 * a2 - b1 * b2 - c1 * c2 - d1 * d2
				return (e1().getC1() * e2().getC1() - e1().getC2() * e2().getC2() 
						- e1().getC3() * e2().getC3() - e1().getC4() * e2().getC4());
			}
		
			template <typename E1, typename E2>
			static ResultType applyC2(const QuaternionExpression<E1>& e1, const QuaternionExpression<E2>& e2)
			{
				// b = a1 * b2 + b1 * a2 + c1 * d2 - d1 * c2 
				return (e1().getC1() * e2().getC2() + e1().getC2() * e2().getC1() 
						+ e1().getC3() * e2().getC4() - e1().getC4() * e2().getC3());
			}

			template <typename E1, typename E2>
			static ResultType applyC3(const QuaternionExpression<E1>& e1, const QuaternionExpression<E2>& e2)
			{
				// c = a1 * c2 - b1 * d2 + c1 * a2 + d1 * b2
				return (e1().getC1() * e2().getC3() - e1().getC2() * e2().getC4() 
						+ e1().getC3() * e2().getC1() + e1().getC4() * e2().getC2());
			}

			template <typename E1, typename E2>
			static ResultType applyC4(const QuaternionExpression<E1>& e1, const QuaternionExpression<E2>& e2)
			{
				// d = a1 * d2 + b1 * c2 - c1 * b2 + d1 * a2
				return (e1().getC1() * e2().getC4() + e1().getC2() * e2().getC3() 
						- e1().getC3() * e2().getC2() + e1().getC4() * e2().getC1());
			}
		};

		template <typename Q1, typename Q2, typename T>
		struct Scalar3QuaternionTernaryFunctor
		{

			typedef typename CommonType<typename CommonType<typename Q1::ValueType, typename Q2::ValueType>::Type, T>::Type ResultType;
			typedef const T& Argument3Type;
		};

		template <typename Q1, typename Q2, typename T>
		struct QuaternionDivision : public Scalar3QuaternionTernaryFunctor<Q1, Q2, T>
		{

			typedef typename Scalar3QuaternionTernaryFunctor<Q1, Q2, T>::Argument3Type Argument3Type;
			typedef typename Scalar3QuaternionTernaryFunctor<Q1, Q2, T>::ResultType ResultType;

			template <typename E1, typename E2>
			static ResultType applyC1(const QuaternionExpression<E1>& e1, const QuaternionExpression<E2>& e2, Argument3Type n2)
			{
				// a = (a1 * a2 + b1 * b2 + c1 * c2 + d1 * d2) / n2
				return ((e1().getC1() * e2().getC1() + e1().getC2() * e2().getC2() 
						 + e1().getC3() * e2().getC3() + e1().getC4() * e2().getC4()) / n2);
			}

			template <typename E1, typename E2>
			static ResultType applyC2(const QuaternionExpression<E1>& e1, const QuaternionExpression<E2>& e2, Argument3Type n2)
			{
				// b = (-a1 * b2 + b1 * a2 - c1 * d2 + d1 * c2) / n2 
				return ((-e1().getC1() * e2().getC2() + e1().getC2() * e2().getC1() 
						 - e1().getC3() * e2().getC4() + e1().getC4() * e2().getC3()) / n2);
			}

			template <typename E1, typename E2>
			static ResultType applyC3(const QuaternionExpression<E1>& e1, const QuaternionExpression<E2>& e2, Argument3Type n2)
			{
				// c = (-a1 * c2 + b1 * d2 + c1 * a2 - d1 * b2) / n2
				return ((-e1().getC1() * e2().getC3() + e1().getC2() * e2().getC4() 
						 + e1().getC3() * e2().getC1() - e1().getC4() * e2().getC2()) / n2);
			}

			template <typename E1, typename E2>
			static ResultType applyC4(const QuaternionExpression<E1>& e1, const QuaternionExpression<E2>& e2, Argument3Type n2)
			{
				// d = (-a1 * d2 - b1 * c2 + c1 * b2 + d1 * a2) / n2
				return ((-e1().getC1() * e2().getC4() - e1().getC2() * e2().getC3() 
						 + e1().getC3() * e2().getC2() + e1().getC4() * e2().getC1()) / n2);
			}
		};

		template <typename T1, typename Q, typename T2>
		struct Scalar13QuaternionTernaryFunctor
		{

			typedef typename CommonType<typename CommonType<T1, typename Q::ValueType>::Type, T2>::Type ResultType;
			typedef const T1& Argument1Type;
			typedef const T2& Argument3Type;
		};

		template <typename T1, typename Q, typename T2>
		struct ScalarQuaternionDivision : public Scalar13QuaternionTernaryFunctor<T1, Q, T2>
		{

			typedef typename Scalar13QuaternionTernaryFunctor<T1, Q, T2>::Argument1Type Argument1Type;
			typedef typename Scalar13QuaternionTernaryFunctor<T1, Q, T2>::Argument3Type Argument3Type;
			typedef typename Scalar13QuaternionTernaryFunctor<T1, Q, T2>::ResultType ResultType;

			template <typename E>
			static ResultType applyC1(Argument1Type t, const QuaternionExpression<E>& e, Argument3Type n2)
			{
				return (t * e().getC1() / n2);
			}

			template <typename E>
			static ResultType applyC2(Argument1Type t, const QuaternionExpression<E>& e, Argument3Type n2)
			{
				return (t * -e().getC2() / n2);
			}

			template <typename E>
			static ResultType applyC3(Argument1Type t, const QuaternionExpression<E>& e, Argument3Type n2)
			{
				return (t * -e().getC3() / n2);
			}

			template <typename E>
			static ResultType applyC4(Argument1Type t, const QuaternionExpression<E>& e, Argument3Type n2)
			{
				return (t * -e().getC4() / n2);
			}
		};

		template <typename Q, typename V>
		struct QuaternionVectorBinaryFunctor
		{

			typedef typename CommonType<typename Q::ValueType, typename V::ValueType>::Type ValueType;
			typedef typename V::SizeType SizeType;
			typedef ValueType ResultType;
		};

		template <typename Q, typename V>
		struct QuaternionVectorRotation : public QuaternionVectorBinaryFunctor<Q, V>
		{

			typedef typename QuaternionVectorBinaryFunctor<Q, V>::ValueType ValueType;
			typedef typename QuaternionVectorBinaryFunctor<Q, V>::SizeType SizeType;
			typedef typename QuaternionVectorBinaryFunctor<Q, V>::ResultType ResultType;

			template <typename E1, typename E2>
			static ResultType apply(const QuaternionExpression<E1>& e1, const VectorExpression<E2>& e2, SizeType i) {
				CDPL_MATH_CHECK(e2().getSize() >= 3, "Invalid vector size", Base::SizeError);

				switch (i) {

				case 0: {
					// vr1 = (a2 + b2 - c2 - d2) * v1 + (2bc - 2ad) * v2 + (2bd + 2ac) * v3
					ValueType t1 = e1().getC1() * e1().getC1() + e1().getC2() * e1().getC2() - e1().getC3() * e1().getC3() - e1().getC4() * e1().getC4();
					ValueType t2 = ValueType(2) * (e1().getC2() * e1().getC3() - e1().getC1() * e1().getC4());
					ValueType t3 = ValueType(2) * (e1().getC2() * e1().getC4() + e1().getC1() * e1().getC3());

					return (t1 * e2()(0) + t2 * e2()(1) + t3 * e2()(2));
				}

				case 1: {
					// vr2 = (2bc + 2ad) * v1 + (a2 - b2 + c2 - d2) * v2 + (2cd - 2ab) * v3
					ValueType t1 = ValueType(2) * (e1().getC2() * e1().getC3() + e1().getC1() * e1().getC4());
					ValueType t2 = e1().getC1() * e1().getC1() - e1().getC2() * e1().getC2() + e1().getC3() * e1().getC3() - e1().getC4() * e1().getC4();
					ValueType t3 = ValueType(2) * (e1().getC3() * e1().getC4() - e1().getC1() * e1().getC2());

					return (t1 * e2()(0) + t2 * e2()(1) + t3 * e2()(2));
				}

				case 2: {
					// vr3 = (2bd - 2ac) * v1 + (2cd + 2ab) * v2 + (a2 - b2 - c2 + d2) * v3
					ValueType t1 = ValueType(2) * (e1().getC2() * e1().getC4() - e1().getC1() * e1().getC3());
					ValueType t2 = ValueType(2) * (e1().getC3() * e1().getC4() + e1().getC1() * e1().getC2());
					ValueType t3 = e1().getC1() * e1().getC1() - e1().getC2() * e1().getC2() - e1().getC3() * e1().getC3() + e1().getC4() * e1().getC4();

					return (t1 * e2()(0) + t2 * e2()(1) + t3 * e2()(2));
				}

				default:
					return ResultType();
				}
			}
		};
	   
		template <typename G1, typename G2>
		struct GridBooleanBinaryFunctor
		{

			typedef bool ResultType;
			typedef typename CommonType<typename G1::SizeType, typename G2::SizeType>::Type SizeType;
			typedef typename CommonType<typename G1::ValueType, typename G2::ValueType>::Type ValueType;
		};

		template <typename G1, typename G2>
		struct GridEquality : public GridBooleanBinaryFunctor<G1, G2>
		{

			typedef typename GridBooleanBinaryFunctor<G1, G2>::SizeType SizeType;
			typedef typename GridBooleanBinaryFunctor<G1, G2>::ValueType ValueType;
			typedef typename GridBooleanBinaryFunctor<G1, G2>::ResultType ResultType;

			static ResultType apply(const GridExpression<G1>& e1, const GridExpression<G2>& e2) {
				if (SizeType(e1().getSize1()) != SizeType(e2().getSize1()))
					return false;

				if (SizeType(e1().getSize2()) != SizeType(e2().getSize2()))
					return false;

				if (SizeType(e1().getSize3()) != SizeType(e2().getSize3()))
					return false;

				for (SizeType i = 0, size1 = e1().getSize1(); i < size1; i++)
					for (SizeType j = 0, size2 = e1().getSize2(); j < size2; j++)
						for (SizeType k = 0, size3 = e1().getSize3(); k < size3; k++)
							if (ValueType(e1()(i, j, k)) != ValueType(e2()(i, j, k)))
								return false;

				return true;
			}
		};

		template <typename G1, typename G2, typename T>
		struct Scalar3GridBooleanTernaryFunctor
		{

			typedef bool ResultType;
			typedef const T& Argument3Type;
			typedef typename CommonType<typename G1::SizeType, typename G2::SizeType>::Type SizeType;
			typedef typename CommonType<typename G1::ValueType, typename G2::ValueType>::Type ValueType;
		};

		template <typename G1, typename G2, typename T>
		struct GridToleranceEquality : public Scalar3GridBooleanTernaryFunctor<G1, G2, T>
		{

			typedef typename Scalar3GridBooleanTernaryFunctor<G1, G2, T>::SizeType SizeType;
			typedef typename Scalar3GridBooleanTernaryFunctor<G1, G2, T>::ValueType ValueType;
			typedef typename Scalar3GridBooleanTernaryFunctor<G1, G2, T>::ResultType ResultType;
			typedef typename Scalar3GridBooleanTernaryFunctor<G1, G2, T>::Argument3Type Argument3Type;

			static ResultType apply(const GridExpression<G1>& e1, const GridExpression<G2>& e2, Argument3Type epsilon) {
				typedef typename CommonType<typename TypeTraits<ValueType>::RealType, T>::Type ComparisonType;

				if (SizeType(e1().getSize1()) != SizeType(e2().getSize1()))
					return false;

				if (SizeType(e1().getSize2()) != SizeType(e2().getSize2()))
					return false;

				if (SizeType(e1().getSize3()) != SizeType(e2().getSize3()))
					return false;

				ComparisonType norm_inf_max(epsilon);

				for (SizeType i = 0, size1 = e1().getSize1(); i < size1; i++)
					for (SizeType j = 0, size2 = e1().getSize2(); j < size2; j++)
						for (SizeType k = 0, size3 = e1().getSize3(); k < size3; k++)
							if (ComparisonType(TypeTraits<ValueType>::normInf(e2()(i, j, k) - e1()(i, j, k))) > norm_inf_max)
								return false;

				return true;
			}
		};

		template <typename M>
		struct GridScalarUnaryFunctor
		{

			typedef typename M::ValueType ResultType;
		};

		template <typename G>
		struct GridElementSum : public GridScalarUnaryFunctor<G>
		{
			
			typedef typename GridScalarUnaryFunctor<G>::ResultType ResultType;

			static ResultType apply(const GridExpression<G>& e) {
				typedef typename G::SizeType SizeType;

				ResultType res = ResultType();
				SizeType size1 = e().getSize1();
				SizeType size2 = e().getSize2();
				SizeType size3 = e().getSize3();

				for (SizeType i = 0; i < size1; i++) 
					for (SizeType j = 0; j < size2; j++) 
						for (SizeType k = 0; k < size3; k++) 
							res += e()(i, j, k);

				return res;
			}
		};
	}
}

#endif // CDPL_MATH_FUNCTIONAL_HPP
