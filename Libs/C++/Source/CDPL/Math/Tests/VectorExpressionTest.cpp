/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * VectorExpressionTest.cpp 
 *
 * Copyright (C) 2010-2011 Thomas A. Seidel <thomas.seidel@univie.ac.at>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program; see the file COPYING. If not, write to
 * the Free Software Foundation, Inc., 59 Temple Place - Suite 330,
 * Boston, MA 02111-1307, USA.
 */


#include <boost/test/auto_unit_test.hpp>

#include "CDPL/Math/VectorExpression.hpp"
#include "CDPL/Math/Vector.hpp"
#include "CDPL/Math/Quaternion.hpp"
#include "CDPL/Base/Exceptions.hpp"


namespace
{

	template <typename V1, typename V2>
	void checkVectorInnerProdFunction(const V1& v1, const V2& v2)
	{
		using namespace CDPL;
		using namespace Math;

		typedef typename CommonType<typename V1::SizeType, typename V2::SizeType>::Type SizeType;
		typedef typename CommonType<typename V1::ValueType, typename V2::ValueType>::Type ResultType;
		
		ResultType res = innerProd(v1, v2);
		ResultType exp_val = ResultType();

		for (SizeType i = 0; i < v1.getSize(); i++)
			exp_val += v1(i) * v2(i);

		BOOST_CHECK_EQUAL(res, exp_val);
		BOOST_CHECK_EQUAL(innerProd(v2, v1), exp_val);
	}

	template <typename V1, typename V2, typename T>
	void checkVectorAngleCosFunction(const V1& v1, const V2& v2, const T& sf, bool clamp)
	{
		using namespace CDPL;
		using namespace Math;

		typedef VectorInnerProduct<V1, V2> VIP;
		typedef typename CommonType<T, typename VIP::ResultType>::Type ResultType;

		ResultType exp_val = VIP::apply(v1, v2) / sf;

		if (clamp)
			exp_val = boost::algorithm::clamp(exp_val, ResultType(-1.0), ResultType(1.0));

		ResultType res = angleCos(v1, v2, sf, clamp);

		BOOST_CHECK_EQUAL(res, exp_val);
		BOOST_CHECK_EQUAL(angleCos(v2, v1, sf, clamp), exp_val);
	}

	template <typename V1, typename V2, typename V3>
	void checkVectorCrossProdFunction(const V1& v1, const V2& v2, const V3& exp_res)
	{
		using namespace CDPL;
		using namespace Math;

		typedef typename CommonType<typename V1::SizeType, typename V2::SizeType>::Type SizeType;
		typedef typename CommonType<typename V1::ValueType, typename V2::ValueType>::Type ResultType;
	
		for (SizeType i = 0; i < 3; i++)
			BOOST_CHECK_EQUAL(crossProd(v1, v2)(i), exp_res(i));

		for (SizeType i = 3; i < 6; i++)
			BOOST_CHECK_EQUAL(crossProd(v1, v2)(i), ResultType());
	}

	template <typename V>
	void checkVectorNorm1Function(const V& v)
	{
		using namespace CDPL;
		using namespace Math;

		typedef typename V::ValueType ValueType;	
		typedef typename V::SizeType SizeType;
		typedef typename TypeTraits<ValueType>::RealType RealType;

		RealType exp_val = RealType();

		for (SizeType i = 0; i < v.getSize(); i++)
			exp_val += TypeTraits<ValueType>::norm1(v(i));

		BOOST_CHECK_EQUAL(norm1(v), exp_val);
	}

	template <typename V>
	void checkVectorNorm2Function(const V& v)
	{
		using namespace CDPL;
		using namespace Math;

		typedef typename V::ValueType ValueType;	
		typedef typename V::SizeType SizeType;
		typedef typename TypeTraits<ValueType>::RealType RealType;

		RealType exp_val = RealType();

		for (SizeType i = 0; i < v.getSize(); i++) {
			RealType t = TypeTraits<ValueType>::norm2(v(i));
			exp_val += t * t;
		}

		exp_val = TypeTraits<RealType>::sqrt(exp_val);

		BOOST_CHECK_EQUAL(norm2(v), exp_val);
	}

	template <typename V>
	void checkVectorLengthFunction(const V& v)
	{
		using namespace CDPL;
		using namespace Math;

		typedef typename V::ValueType ValueType;	
		typedef typename V::SizeType SizeType;
		typedef typename TypeTraits<ValueType>::RealType RealType;

		RealType exp_val = RealType();

		for (SizeType i = 0; i < v.getSize(); i++) {
			RealType t = TypeTraits<ValueType>::norm2(v(i));
			exp_val += t * t;
		}

		exp_val = TypeTraits<RealType>::sqrt(exp_val);

		BOOST_CHECK_EQUAL(length(v), exp_val);
	}

	template <typename Q, typename V>
	void checkVectorRotateFunction(const Q& q, const V& v)
	{
		using namespace CDPL;
		using namespace Math;

		typedef typename CommonType<typename Q::ValueType, typename V::ValueType>::Type ResultType;

		// vr1 = (a2 + b2 - c2 - d2) * v1 + (2bc - 2ad) * v2 + (2bd + 2ac) * v3
		ResultType vr1 = (q.getC1() * q.getC1() + q.getC2() * q.getC2() - q.getC3() * q.getC3() - q.getC4() * q.getC4()) * v(0) +
			(ResultType(2) * (q.getC2() * q.getC3() - q.getC1() * q.getC4())) * v(1) +
			(ResultType(2) * (q.getC2() * q.getC4() + q.getC1() * q.getC4())) * v(2);

		// vr2 = (2bc + 2ad) * v1 + (a2 - b2 + c2 - d2) * v2 + (2cd - 2ab) * v3
		ResultType vr2 = (ResultType(2) * (q.getC2() * q.getC3() + q.getC1() * q.getC4())) * v(0) +
			(q.getC1() * q.getC1() - q.getC2() * q.getC2() + q.getC3() * q.getC3() - q.getC4() * q.getC4()) * v(1) +
			(ResultType(2) * (q.getC3() * q.getC4() - q.getC1() * q.getC2())) * v(2);
		
		// vr3 = (2bd - 2ac) * v1 + (2cd + 2ab) * v2 + (a2 - b2 - c2 + d2) * v3
		ResultType vr3 = (ResultType(2) * (q.getC2() * q.getC4() - q.getC1() * q.getC3())) * v(0) +
			(ResultType(2) * (q.getC3() * q.getC4() + q.getC1() * q.getC2())) * v(1) +
			(q.getC1() * q.getC1() - q.getC2() * q.getC2() - q.getC3() * q.getC3() + q.getC4() * q.getC4()) * v(2);
	
		BOOST_CHECK_EQUAL(rotate(q, v)(0), vr1);
		BOOST_CHECK_EQUAL(rotate(q, v)(1), vr2);
		BOOST_CHECK_EQUAL(rotate(q, v)(2), vr3);
		BOOST_CHECK_EQUAL(rotate(q, v)(3), ResultType());
	}

	template <typename V>
	void checkVectorTransFunction(V& v)
	{
		using namespace CDPL;

		typedef typename V::SizeType SizeType;
	
		BOOST_CHECK_EQUAL(trans(v).getSize(), v.getSize());
		BOOST_CHECK_EQUAL(trans(const_cast<const V&>(v)).getSize(), v.getSize());

		for (SizeType i = 0; i < v.getSize(); i++) {
			BOOST_CHECK_EQUAL(trans(v)(i), v(i));
			BOOST_CHECK_EQUAL(trans(const_cast<const V&>(v))(i), v(i));
		}

		BOOST_CHECK_THROW(trans(v)(v.getSize()), Base::IndexError);
		BOOST_CHECK_THROW(trans(const_cast<const V&>(v))(v.getSize()), Base::IndexError);
	}

	template <typename V>
	void checkVectorPlusOperator(const V& v)
	{
		using namespace CDPL;

		typedef typename V::SizeType SizeType;
	
		BOOST_CHECK_EQUAL(operator+(v).getSize(), v.getSize());
		BOOST_CHECK_EQUAL((+v).getSize(), v.getSize());

		for (SizeType i = 0; i < v.getSize(); i++) {
			BOOST_CHECK_EQUAL(operator+(v)(i), v(i));
			BOOST_CHECK_EQUAL((+v)(i), v(i));
		}

		BOOST_CHECK_THROW(operator+(v)(v.getSize()), Base::IndexError);
		BOOST_CHECK_THROW((+v)(v.getSize()), Base::IndexError);
	}

	template <typename V>
	void checkVectorMinusOperator(const V& v)
	{
		using namespace CDPL;

		typedef typename V::SizeType SizeType;
	
		BOOST_CHECK_EQUAL(operator-(v).getSize(), v.getSize());
		BOOST_CHECK_EQUAL((-v).getSize(), v.getSize());

		for (SizeType i = 0; i < v.getSize(); i++) {
			BOOST_CHECK_EQUAL(operator-(v)(i), -v(i));
			BOOST_CHECK_EQUAL((-v)(i), -v(i));
		}

		BOOST_CHECK_THROW(operator-(v)(v.getSize()), Base::IndexError);
		BOOST_CHECK_THROW((-v)(v.getSize()), Base::IndexError);
	}

	template <typename V>
	void checkVectorConjFunction(const V& v)
	{
		using namespace CDPL;
		using namespace Math;

		typedef typename V::SizeType SizeType;
		typedef typename V::ValueType ValueType;

		BOOST_CHECK_EQUAL(conj(v).getSize(), v.getSize());

		for (SizeType i = 0; i < v.getSize(); i++) {
			BOOST_CHECK_EQUAL(conj(v)(i), TypeTraits<ValueType>::conj(v(i)));
		}

		BOOST_CHECK_THROW(conj(v)(v.getSize()), Base::IndexError);
	}

	template <typename V>
	void checkVectorRealFunction(const V& v)
	{
		using namespace CDPL;
		using namespace Math;

		typedef typename V::SizeType SizeType;
		typedef typename V::ValueType ValueType;

		BOOST_CHECK_EQUAL(real(v).getSize(), v.getSize());

		for (SizeType i = 0; i < v.getSize(); i++) {
			BOOST_CHECK_EQUAL(real(v)(i), TypeTraits<ValueType>::real(v(i)));
		}

		BOOST_CHECK_THROW(real(v)(v.getSize()), Base::IndexError);
	}

	template <typename V>
	void checkVectorImagFunction(const V& v)
	{
		using namespace CDPL;
		using namespace Math;

		typedef typename V::SizeType SizeType;
		typedef typename V::ValueType ValueType;

		BOOST_CHECK_EQUAL(imag(v).getSize(), v.getSize());

		for (SizeType i = 0; i < v.getSize(); i++) {
			BOOST_CHECK_EQUAL(imag(v)(i), TypeTraits<ValueType>::imag(v(i)));
		}

		BOOST_CHECK_THROW(imag(v)(v.getSize()), Base::IndexError);
	}

	template <typename V>
	void checkVectorHermFunction(const V& v)
	{
		using namespace CDPL;
		using namespace Math;

		typedef typename V::SizeType SizeType;
		typedef typename V::ValueType ValueType;

		BOOST_CHECK_EQUAL(herm(v).getSize(), v.getSize());

		for (SizeType i = 0; i < v.getSize(); i++) {
			BOOST_CHECK_EQUAL(herm(v)(i), TypeTraits<ValueType>::conj(v(i)));
		}

		BOOST_CHECK_THROW(herm(v)(v.getSize()), Base::IndexError);
	}

	template <typename V1, typename V2>
	void checkVectorElemProdFunction(const V1& v1, const V2& v2)
	{
		using namespace CDPL;
		using namespace Math;

		typedef typename CommonType<typename V1::SizeType, typename V2::SizeType>::Type SizeType;
		
		BOOST_CHECK_EQUAL(elemProd(v1, v2).getSize(), v1.getSize());

		for (SizeType i = 0; i < v1.getSize(); i++) {
			BOOST_CHECK_EQUAL(elemProd(v1, v2)(i), v1(i) * v2(i));
			BOOST_CHECK_EQUAL(elemProd(v2, v1)(i), v1(i) * v2(i));
		}

		BOOST_CHECK_THROW(elemProd(v1, v2)(v1.getSize()), Base::IndexError);
	}

	template <typename V1, typename V2>
	void checkVectorElemDivFunction(const V1& v1, const V2& v2)
	{
		using namespace CDPL;
		using namespace Math;

		typedef typename CommonType<typename V1::SizeType, typename V2::SizeType>::Type SizeType;
		
		BOOST_CHECK_EQUAL(elemDiv(v1, v2).getSize(), v1.getSize());

		for (SizeType i = 0; i < v1.getSize(); i++) {
			BOOST_CHECK_EQUAL(elemDiv(v1, v2)(i), v1(i) / v2(i));
		}

		BOOST_CHECK_THROW(elemDiv(v1, v2)(v1.getSize()), Base::IndexError);
	}

	template <typename V1, typename V2>
	void checkVectorAddition(const V1& v1, const V2& v2)
	{
		using namespace CDPL;
		using namespace Math;

		typedef typename CommonType<typename V1::SizeType, typename V2::SizeType>::Type SizeType;
		
		BOOST_CHECK_EQUAL(operator+(v1, v2).getSize(), v1.getSize());
		BOOST_CHECK_EQUAL((v1 + v2).getSize(), v1.getSize());

		BOOST_CHECK_EQUAL(operator+(v2, v1).getSize(), v1.getSize());
		BOOST_CHECK_EQUAL((v2 + v1).getSize(), v1.getSize());

		for (SizeType i = 0; i < v1.getSize(); i++) {
			BOOST_CHECK_EQUAL(operator+(v1, v2)(i), v1(i) + v2(i));
			BOOST_CHECK_EQUAL(operator+(v2, v1)(i), v1(i) + v2(i));

			BOOST_CHECK_EQUAL((v1 + v2)(i), v1(i) + v2(i));
			BOOST_CHECK_EQUAL((v2 + v1)(i), v1(i) + v2(i));
		}

		BOOST_CHECK_THROW(operator+(v1, v2)(v1.getSize()), Base::IndexError);
		BOOST_CHECK_THROW((v1 + v2)(v1.getSize()), Base::IndexError);

		BOOST_CHECK_THROW(operator+(v2, v1)(v1.getSize()), Base::IndexError);
		BOOST_CHECK_THROW((v2 + v1)(v1.getSize()), Base::IndexError);
	}

	template <typename V1, typename V2>
	void checkVectorSubtraction(const V1& v1, const V2& v2)
	{
		using namespace CDPL;
		using namespace Math;

		typedef typename CommonType<typename V1::SizeType, typename V2::SizeType>::Type SizeType;
		
		BOOST_CHECK_EQUAL(operator-(v1, v2).getSize(), v1.getSize());
		BOOST_CHECK_EQUAL((v1 - v2).getSize(), v1.getSize());

		BOOST_CHECK_EQUAL(operator-(v2, v1).getSize(), v1.getSize());
		BOOST_CHECK_EQUAL((v2 - v1).getSize(), v1.getSize());

		for (SizeType i = 0; i < v1.getSize(); i++) {
			BOOST_CHECK_EQUAL(operator-(v1, v2)(i), v1(i) - v2(i));
			BOOST_CHECK_EQUAL(operator-(v2, v1)(i), -(v1(i) - v2(i)));

			BOOST_CHECK_EQUAL((v1 - v2)(i), v1(i) - v2(i));
			BOOST_CHECK_EQUAL((v2 - v1)(i), -(v1(i) - v2(i)));
		}

		BOOST_CHECK_THROW(operator-(v1, v2)(v1.getSize()), Base::IndexError);
		BOOST_CHECK_THROW((v1 - v2)(v1.getSize()), Base::IndexError);

		BOOST_CHECK_THROW(operator-(v2, v1)(v1.getSize()), Base::IndexError);
		BOOST_CHECK_THROW((v2 - v1)(v1.getSize()), Base::IndexError);
	}

	template <typename V, typename T>
	void checkVectorScalarMultiplication(const V& v, const T& t)
	{
		using namespace CDPL;

		typedef typename V::SizeType SizeType;

		BOOST_CHECK_EQUAL(operator*(v, t).getSize(), v.getSize());
		BOOST_CHECK_EQUAL((v * t).getSize(), v.getSize());

		for (SizeType i = 0; i < v.getSize(); i++) {
			BOOST_CHECK_EQUAL(operator*(v, t)(i), v(i) * t);
			BOOST_CHECK_EQUAL((v * t)(i), v(i) * t);
		}

		BOOST_CHECK_THROW(operator*(v, t)(v.getSize()), Base::IndexError);
		BOOST_CHECK_THROW((v * t)(v.getSize()), Base::IndexError);
	}

	template <typename V, typename T>
	void checkVectorScalarDivision(const V& v, const T& t)
	{
		using namespace CDPL;

		typedef typename V::SizeType SizeType;

		BOOST_CHECK_EQUAL(operator/(v, t).getSize(), v.getSize());
		BOOST_CHECK_EQUAL((v / t).getSize(), v.getSize());

		for (SizeType i = 0; i < v.getSize(); i++) {
			BOOST_CHECK_EQUAL(operator/(v, t)(i), v(i) / t);
			BOOST_CHECK_EQUAL((v / t)(i), v(i) / t);
		}

		BOOST_CHECK_THROW(operator/(v, t)(v.getSize()), Base::IndexError);
		BOOST_CHECK_THROW((v / t)(v.getSize()), Base::IndexError);
	}

	template <typename T, typename V>
	void checkScalarVectorMultiplication(const T& t, const V& v)
	{
		using namespace CDPL;

		typedef typename V::SizeType SizeType;

		BOOST_CHECK_EQUAL(operator*(t, v).getSize(), v.getSize());
		BOOST_CHECK_EQUAL((t * v).getSize(), v.getSize());

		for (SizeType i = 0; i < v.getSize(); i++) {
			BOOST_CHECK_EQUAL(operator*(t, v)(i), t * v(i));
			BOOST_CHECK_EQUAL((t * v)(i), t * v(i));
		}

		BOOST_CHECK_THROW(operator*(t, v)(v.getSize()), Base::IndexError);
		BOOST_CHECK_THROW((t * v)(v.getSize()), Base::IndexError);
	}

	template <typename ResType, typename ArgType>
	struct VectorUnaryTestFunctor
	{
		
		typedef ResType ResultType;
		typedef ArgType ArgumentType;

		static ResultType apply(ArgumentType arg) {
			return (arg * arg);
		}
	};

	template <typename ResType, typename ArgType1, typename ArgType2>
	struct VectorBinary1TestFunctor
	{
		
		typedef ResType ResultType;
		typedef ArgType1 ArgumentType1;
		typedef ArgType2 ArgumentType2;

		static ResultType apply(ArgumentType1 arg1, ArgumentType2 arg2) {
			return (arg1 * arg2 - arg1 / 2) ;
		}
	};

	template <typename ResType>
	struct VectorBinary2TestFunctor
	{
		
		typedef ResType ResultType;
	
		template <typename E1, typename E2>
		static ResultType apply(const CDPL::Math::VectorExpression<E1>& v1, 
								const CDPL::Math::VectorExpression<E2>& v2, 
								typename CDPL::Math::CommonType<typename E1::SizeType, typename E2::SizeType>::Type i) {

			return (v1()(i) * v2()(i));
		}
	};

	template <typename ResType, typename ArgType1, typename ArgType2>
	struct Scalar1VectorBinaryTestFunctor
	{
		
		typedef ResType ResultType;
		typedef ArgType1 ArgumentType1;
		typedef ArgType2 ArgumentType2;

		static ResultType apply(ArgumentType1 arg1, ArgumentType2 arg2) {
			return (arg1 * arg2 + arg1) ;
		}
	};

	template <typename ResType, typename ArgType1, typename ArgType2>
	struct Scalar2VectorBinaryTestFunctor
	{
		
		typedef ResType ResultType;
		typedef ArgType1 ArgumentType1;
		typedef ArgType2 ArgumentType2;

		static ResultType apply(ArgumentType1 arg1, ArgumentType2 arg2) {
			return (arg1 / arg2 - arg1) ;
		}
	};

	template <typename ResType>
	struct QuaternionVectorBinaryTestFunctor
	{
		
		typedef ResType ResultType;
	
		template <typename E1, typename E2>
		static ResultType apply(const CDPL::Math::QuaternionExpression<E1>& q, 
								const CDPL::Math::VectorExpression<E2>& v, 
								typename E2::SizeType i) {

			return (q().getC1() * q().getC2() + q().getC3() * q().getC4() * v()(i));
		}
	};
}


BOOST_AUTO_TEST_CASE(VectorUnaryTest)
{
	using namespace CDPL;
	using namespace Math;

	BOOST_CHECK(typeid(VectorUnary<Vector<double>, VectorUnaryTestFunctor<long, float> >::ValueType) ==
					  typeid(const long));
	BOOST_CHECK(typeid(VectorUnary<Vector<double>, VectorUnaryTestFunctor<long, char> >::ConstReference) ==
					  typeid(const long));
	BOOST_CHECK(typeid(VectorUnary<Vector<double>, VectorUnaryTestFunctor<long, int> >::Reference) ==
					  typeid(const long));
	BOOST_CHECK(typeid(VectorUnary<Vector<float>, VectorUnaryTestFunctor<long double, double> >::ValueType) ==
					  typeid(const long double));
	BOOST_CHECK(typeid(VectorUnary<Vector<float>, VectorUnaryTestFunctor<long double, int> >::ConstReference) ==
					  typeid(const long double));
	BOOST_CHECK(typeid(VectorUnary<Vector<float>, VectorUnaryTestFunctor<long double, long> >::Reference) ==
					  typeid(const long double));

	BOOST_CHECK(typeid(VectorUnary<Vector<float>, VectorUnaryTestFunctor<double, long> >::SizeType) ==
					  typeid(Vector<float>::SizeType));
	BOOST_CHECK(typeid(VectorUnary<Vector<int>, VectorUnaryTestFunctor<double, long> >::DifferenceType) ==
					  typeid(Vector<int>::DifferenceType));

	// ----------

	typedef VectorUnaryTestFunctor<double, const int&> Functor;

	Vector<int> v = vec(-1, 0, 4, -22);
	VectorUnary<Vector<int>, Functor> v_un(v);

	BOOST_CHECK_EQUAL(v.getSize(), v_un.getSize());
	
	for (Vector<int>::SizeType i = 0; i < v.getSize(); i++) {
		BOOST_CHECK_EQUAL(v_un(i), Functor::apply(v(i)));
		BOOST_CHECK_EQUAL(v_un[i], Functor::apply(v(i)));
	}

	BOOST_CHECK_THROW(v_un(v.getSize()), Base::IndexError);
}

BOOST_AUTO_TEST_CASE(VectorBinary1Test)
{
	using namespace CDPL;
	using namespace Math;

	BOOST_CHECK(typeid(VectorBinary1<Vector<double>, Vector<char>, VectorBinary1TestFunctor<long, long double, float> >::ValueType) ==
					  typeid(const long));
	BOOST_CHECK(typeid(VectorBinary1<Vector<double>, Vector<short>, VectorBinary1TestFunctor<long, long double, int> >::ConstReference) ==
					  typeid(const long));
	BOOST_CHECK(typeid(VectorBinary1<Vector<double>, Vector<int>, VectorBinary1TestFunctor<long, long double, float> >::Reference) ==
					  typeid(const long));
	BOOST_CHECK(typeid(VectorBinary1<Vector<float>, Vector<float>, VectorBinary1TestFunctor<long double, char, short> >::ValueType) ==
					  typeid(const long double));
	BOOST_CHECK(typeid(VectorBinary1<Vector<float>, Vector<double>, VectorBinary1TestFunctor<long double, char, int> >::ConstReference) ==
					  typeid(const long double));
	BOOST_CHECK(typeid(VectorBinary1<Vector<float>, Vector<long>, VectorBinary1TestFunctor<long double, char, unsigned int> >::Reference) ==
					  typeid(const long double));

	BOOST_CHECK(typeid(VectorBinary1<Vector<float>, Vector<double>, VectorBinary1TestFunctor<long double, char, int> >::SizeType) ==
					  typeid(CommonType<Vector<float>::SizeType, Vector<double>::SizeType >::Type));
	BOOST_CHECK(typeid(VectorBinary1<Vector<float>, Vector<long>, VectorBinary1TestFunctor<long double, char, unsigned int> >::DifferenceType) ==
					  typeid(CommonType<Vector<float>::DifferenceType, Vector<long>::DifferenceType >::Type));

	// ----------

	typedef VectorBinary1TestFunctor<long double, const int&, const double&> Functor;
	typedef CommonType<Vector<int>::SizeType, Vector<double>::SizeType>::Type SizeType;

	Vector<int> v1 = vec(-1, 0, 4, 22);
	Vector<double> v2 = vec(50.2, 0.23, 24.23, -22.0);
	VectorBinary1<Vector<int>, Vector<double>, Functor> v_bin(v1, v2);

	BOOST_CHECK_EQUAL(v1.getSize(), v_bin.getSize());
	BOOST_CHECK_EQUAL(v2.getSize(), v_bin.getSize());
	
	for (SizeType i = 0; i < v1.getSize(); i++) {
		BOOST_CHECK_EQUAL(v_bin(i), Functor::apply(v1(i), v2(i)));
		BOOST_CHECK_EQUAL(v_bin[i], Functor::apply(v1(i), v2(i)));
	}

	BOOST_CHECK_THROW(v_bin(v1.getSize()), Base::IndexError);

	// ----------
			
	v1.resize(v1.getSize() + 3);

	BOOST_CHECK_THROW(v_bin.getSize(), Base::SizeError);	

	BOOST_CHECK_EQUAL(v_bin(0), Functor::apply(v1(0), v2(0)));

	BOOST_CHECK_THROW(v_bin(v1.getSize()), Base::IndexError);		  		  
}

BOOST_AUTO_TEST_CASE(VectorBinary2Test)
{
	using namespace CDPL;
	using namespace Math;

	BOOST_CHECK(typeid(VectorBinary2<Vector<double>, Vector<char>, VectorBinary2TestFunctor<long> >::ValueType) ==
					  typeid(const long));
	BOOST_CHECK(typeid(VectorBinary2<Vector<double>, Vector<short>, VectorBinary2TestFunctor<long> >::ConstReference) ==
					  typeid(const long));
	BOOST_CHECK(typeid(VectorBinary2<Vector<double>, Vector<int>, VectorBinary2TestFunctor<long> >::Reference) ==
					  typeid(const long));
	BOOST_CHECK(typeid(VectorBinary2<Vector<float>, Vector<float>, VectorBinary2TestFunctor<long double> >::ValueType) ==
					  typeid(const long double));
	BOOST_CHECK(typeid(VectorBinary2<Vector<float>, Vector<double>, VectorBinary2TestFunctor<long double> >::ConstReference) ==
					  typeid(const long double));
	BOOST_CHECK(typeid(VectorBinary2<Vector<float>, Vector<long>, VectorBinary2TestFunctor<long double> >::Reference) ==
					  typeid(const long double));

	BOOST_CHECK(typeid(VectorBinary2<Vector<float>, Vector<double>, VectorBinary2TestFunctor<long double> >::SizeType) ==
					  typeid(CommonType<Vector<float>::SizeType, Vector<double>::SizeType >::Type));
	BOOST_CHECK(typeid(VectorBinary2<Vector<float>, Vector<long>, VectorBinary2TestFunctor<long double> >::DifferenceType) ==
					  typeid(CommonType<Vector<float>::DifferenceType, Vector<long>::DifferenceType >::Type));

	// ----------

	typedef VectorBinary2TestFunctor<long double> Functor;
	typedef CommonType<Vector<int>::SizeType, Vector<double>::SizeType>::Type SizeType;

	Vector<int> v1 = vec(-1, 0, 4, 22);
	Vector<double> v2 = vec(50.2, 0.23, 24.23, -22.0);
	VectorBinary2<Vector<int>, Vector<double>, Functor> v_bin(v1, v2);

	BOOST_CHECK_EQUAL(v1.getSize(), v_bin.getSize());
	BOOST_CHECK_EQUAL(v2.getSize(), v_bin.getSize());
	
	for (SizeType i = 0; i < v1.getSize(); i++) {
		BOOST_CHECK_EQUAL(v_bin(i), Functor::apply(v1, v2, i));
		BOOST_CHECK_EQUAL(v_bin[i], Functor::apply(v1, v2, i));
	}

	BOOST_CHECK_THROW(v_bin(v1.getSize()), Base::IndexError);

	// ----------
			
	v2.resize(v2.getSize() + 3);

	BOOST_CHECK_THROW(v_bin.getSize(), Base::SizeError);	

	BOOST_CHECK_EQUAL(v_bin(0), Functor::apply(v1, v2, 0));		  

	BOOST_CHECK_THROW(v_bin(v2.getSize()), Base::IndexError);		  
}

BOOST_AUTO_TEST_CASE(Scalar1VectorBinaryTest)
{
	using namespace CDPL;
	using namespace Math;

	BOOST_CHECK(typeid(Scalar1VectorBinary<double, Vector<char>, Scalar1VectorBinaryTestFunctor<long, long double, float> >::ValueType) ==
 					  typeid(const long));
	BOOST_CHECK(typeid(Scalar1VectorBinary<double, Vector<short>, Scalar1VectorBinaryTestFunctor<long, long double, int> >::ConstReference) ==
					  typeid(const long));
	BOOST_CHECK(typeid(Scalar1VectorBinary<double, Vector<int>, Scalar1VectorBinaryTestFunctor<long, long double, float> >::Reference) ==
					  typeid(const long));
	BOOST_CHECK(typeid(Scalar1VectorBinary<float, Vector<float>, Scalar1VectorBinaryTestFunctor<long double, char, short> >::ValueType) ==
					  typeid(const long double));
	BOOST_CHECK(typeid(Scalar1VectorBinary<float, Vector<double>, Scalar1VectorBinaryTestFunctor<long double, char, int> >::ConstReference) ==
					  typeid(const long double));
	BOOST_CHECK(typeid(Scalar1VectorBinary<float, Vector<long>, Scalar1VectorBinaryTestFunctor<long double, char, unsigned int> >::Reference) ==
					  typeid(const long double));

	BOOST_CHECK(typeid(Scalar1VectorBinary<double, Vector<float>, Scalar1VectorBinaryTestFunctor<int, double, long> >::SizeType) ==
					  typeid(Vector<float>::SizeType));
	BOOST_CHECK(typeid(Scalar1VectorBinary<char, Vector<int>, Scalar1VectorBinaryTestFunctor<unsigned char, double, long> >::DifferenceType) ==
					  typeid(Vector<int>::DifferenceType));

	// ----------

	typedef Scalar1VectorBinaryTestFunctor<long double, const long&, const double&> Functor;

	Vector<double> v = vec(50.2, 0.23, 24.23, -22.0);
	Scalar1VectorBinary<long, Vector<double>, Functor> sv_bin(-34, v);

	BOOST_CHECK_EQUAL(v.getSize(), sv_bin.getSize());
	
	for (Vector<double>::SizeType i = 0; i < v.getSize(); i++) {
		BOOST_CHECK_EQUAL(sv_bin(i), Functor::apply(-34, v(i)));
		BOOST_CHECK_EQUAL(sv_bin[i], Functor::apply(-34, v(i)));
	}

	BOOST_CHECK_THROW(sv_bin(v.getSize()), Base::IndexError);
}

BOOST_AUTO_TEST_CASE(Scalar2VectorBinaryTest)
{
	using namespace CDPL;
	using namespace Math;

	BOOST_CHECK(typeid(Scalar2VectorBinary<Vector<char>, double, Scalar2VectorBinaryTestFunctor<long, long double, float> >::ValueType) ==
 					  typeid(const long));
	BOOST_CHECK(typeid(Scalar2VectorBinary<Vector<short>, double, Scalar2VectorBinaryTestFunctor<long, long double, int> >::ConstReference) ==
					  typeid(const long));
	BOOST_CHECK(typeid(Scalar2VectorBinary<Vector<int>, double, Scalar2VectorBinaryTestFunctor<long, long double, float> >::Reference) ==
					  typeid(const long));
	BOOST_CHECK(typeid(Scalar2VectorBinary<Vector<float>, float, Scalar2VectorBinaryTestFunctor<long double, char, short> >::ValueType) ==
					  typeid(const long double));
	BOOST_CHECK(typeid(Scalar2VectorBinary<Vector<double>, float, Scalar2VectorBinaryTestFunctor<long double, char, int> >::ConstReference) ==
					  typeid(const long double));
	BOOST_CHECK(typeid(Scalar2VectorBinary<Vector<long>, float, Scalar2VectorBinaryTestFunctor<long double, char, unsigned int> >::Reference) ==
					  typeid(const long double));

	BOOST_CHECK(typeid(Scalar2VectorBinary<Vector<float>, double, Scalar2VectorBinaryTestFunctor<char, double, long> >::SizeType) ==
					  typeid(Vector<float>::SizeType));
	BOOST_CHECK(typeid(Scalar2VectorBinary<Vector<int>, char, Scalar2VectorBinaryTestFunctor<short, double, long> >::DifferenceType) ==
					  typeid(Vector<int>::DifferenceType));

	// ----------

	typedef Scalar2VectorBinaryTestFunctor<long double, const double&, const long&> Functor;

	Vector<double> v = vec(50.2, 0.23, 24.23, -22.0);
	Scalar2VectorBinary<Vector<double>, long, Functor> vs_bin(v, 24);

	BOOST_CHECK_EQUAL(v.getSize(), vs_bin.getSize());
	
	for (Vector<double>::SizeType i = 0; i < v.getSize(); i++) {
		BOOST_CHECK_EQUAL(vs_bin(i), Functor::apply(v(i), 24));
		BOOST_CHECK_EQUAL(vs_bin[i], Functor::apply(v(i), 24));
	}

	BOOST_CHECK_THROW(vs_bin(v.getSize()), Base::IndexError);
}

BOOST_AUTO_TEST_CASE(QuaternionVectorBinaryTest)
{
	using namespace CDPL;
	using namespace Math;

	BOOST_CHECK(typeid(QuaternionVectorBinary<Quaternion<double>, Vector<char>, QuaternionVectorBinaryTestFunctor<long> >::ValueType) ==
					  typeid(const long));
	BOOST_CHECK(typeid(QuaternionVectorBinary<Quaternion<double>, Vector<short>, QuaternionVectorBinaryTestFunctor<long> >::ConstReference) ==
					  typeid(const long));
	BOOST_CHECK(typeid(QuaternionVectorBinary<Quaternion<double>, Vector<int>, QuaternionVectorBinaryTestFunctor<long> >::Reference) ==
					  typeid(const long));
	BOOST_CHECK(typeid(QuaternionVectorBinary<Quaternion<float>, Vector<float>, QuaternionVectorBinaryTestFunctor<long double> >::ValueType) ==
					  typeid(const long double));
	BOOST_CHECK(typeid(QuaternionVectorBinary<Quaternion<float>, Vector<double>, QuaternionVectorBinaryTestFunctor<long double> >::ConstReference) ==
					  typeid(const long double));
	BOOST_CHECK(typeid(QuaternionVectorBinary<Quaternion<float>, Vector<long>, QuaternionVectorBinaryTestFunctor<long double> >::Reference) ==
					  typeid(const long double));

	BOOST_CHECK(typeid(QuaternionVectorBinary<Quaternion<float>, Vector<double>, QuaternionVectorBinaryTestFunctor<long double> >::SizeType) ==
					  typeid(Vector<double>::SizeType));
	BOOST_CHECK(typeid(QuaternionVectorBinary<Quaternion<float>, Vector<long>, QuaternionVectorBinaryTestFunctor<long double> >::DifferenceType) ==
					  typeid(Vector<long>::DifferenceType));

	// ----------

	typedef QuaternionVectorBinaryTestFunctor<long double> Functor;

	Quaternion<int> q = quat(-1, 3, 4, -22);
	Vector<double> v = vec(50.2, 0.23, 24.23, -22.0);
	QuaternionVectorBinary<Quaternion<int>, Vector<double>, Functor> qv_bin(q, v);

	BOOST_CHECK_EQUAL(v.getSize(), qv_bin.getSize());
	
	for (Vector<double>::SizeType i = 0; i < v.getSize(); i++) {
		BOOST_CHECK_EQUAL(qv_bin(i), Functor::apply(q, v, i));
		BOOST_CHECK_EQUAL(qv_bin[i], Functor::apply(q, v, i));
	}

	BOOST_CHECK_THROW(qv_bin(v.getSize()), Base::IndexError);
}

BOOST_AUTO_TEST_CASE(VectorMinusTest)
{
	using namespace CDPL;
	using namespace Math;
	
	checkVectorMinusOperator(Vector<float>());

	checkVectorMinusOperator(vec(0.0, -120.2));

	checkVectorMinusOperator(vec(-1.1f, 2.1f));

	checkVectorMinusOperator(vec(-3, 3, 0));

	checkVectorMinusOperator(vec(-1.17f, 2.333, 3.21f));

	// ----------

	checkVectorMinusOperator(vec(std::complex<double>(-17.2, 4.5), std::complex<double>(15.16, -14.5), 
								 std::complex<double>(11.17, 22.15), std::complex<double>(-3.1, -1.25)));
}

BOOST_AUTO_TEST_CASE(VectorPlusTest)
{
	using namespace CDPL;
	using namespace Math;

	checkVectorPlusOperator(Vector<float>());

	checkVectorPlusOperator(vec(0.0, -120.2));

	checkVectorPlusOperator(vec(-1.1f, 2.1f));

	checkVectorPlusOperator(vec(-3, 3, 0));

	checkVectorPlusOperator(vec(-1.17f, 2.333, 3.21f));

	// ----------

	checkVectorPlusOperator(vec(std::complex<double>(-17.2, 4.5), std::complex<double>(15.16, -14.5), 
								std::complex<double>(11.17, 22.15), std::complex<double>(-3.1, -1.25)));
}

BOOST_AUTO_TEST_CASE(VectorAdditionTest)
{
	using namespace CDPL;
	using namespace Math;
	
	checkVectorAddition(Vector<float>(), Vector<int>());

	checkVectorAddition(vec(1.1, 2.3f, 1, 2), vec(-1, 2, -3, 4));

	checkVectorAddition(vec(1.1, 2.3f, 1, 2), vec(std::complex<double>(15.0, 12.3), 17.0, std::complex<double>(-12.2, 1.12), 
												  std::complex<double>(12.2, 11.12)));

	checkVectorAddition(vec(std::complex<double>(15.0, 12.3), 17.0, std::complex<double>(-12.2, 1.12), 
							std::complex<double>(12.2, 11.12)), vec(1.1, 2.3f, 1, 2));

	checkVectorAddition(vec(std::complex<double>(15.0, 12.3), -17.0, std::complex<double>(-12.2, 1.12), 
							std::complex<double>(12.2, 11.12)), 
						vec(std::complex<double>(1215.0, 212.3), 17.1, std::complex<double>(12.22, 21.12), 
							std::complex<double>(12.2, -131.12)));

	// ----------

	BOOST_CHECK_THROW((CVector<double, 0>() + CVector<int, 4>())(0), Base::IndexError);
	BOOST_CHECK_THROW((CVector<double, 4>() + CVector<int, 0>())(0), Base::IndexError);
	BOOST_CHECK_THROW((CVector<double, 3>() + CVector<int, 2>())(2), Base::IndexError);
	BOOST_CHECK_THROW((CVector<double, 2>() + CVector<int, 3>())(2), Base::IndexError);

	BOOST_CHECK_THROW(operator+(CVector<double, 0>(), CVector<int, 4>())(0), Base::IndexError);
	BOOST_CHECK_THROW(operator+(CVector<double, 4>(), CVector<int, 0>())(0), Base::IndexError);
	BOOST_CHECK_THROW(operator+(CVector<double, 3>(), CVector<int, 2>())(2), Base::IndexError);
	BOOST_CHECK_THROW(operator+(CVector<double, 2>(), CVector<int, 3>())(2), Base::IndexError);

	BOOST_CHECK_NO_THROW((CVector<double, 3>() + CVector<int, 2>()));
	BOOST_CHECK_NO_THROW(operator+(CVector<double, 3>(), CVector<int, 2>()));

	BOOST_CHECK_NO_THROW((CVector<double, 3>() + CVector<int, 2>())(1));
	BOOST_CHECK_NO_THROW(operator+(CVector<double, 3>(), CVector<int, 2>())(1));
}

BOOST_AUTO_TEST_CASE(VectorSubtractionTest)
{
	using namespace CDPL;
	using namespace Math;

	checkVectorSubtraction(Vector<float>(), Vector<int>());

	checkVectorSubtraction(vec(1.1, 2.3f, 1, 2), vec(-1, 2, -3, 4));

	checkVectorSubtraction(vec(1.1, 2.3f, 1, 2), vec(std::complex<double>(15.0, 12.3), 17.0, std::complex<double>(-12.2, 1.12), 
													 std::complex<double>(12.2, 11.12)));

	checkVectorSubtraction(vec(std::complex<double>(15.0, 12.3), 17.0, std::complex<double>(-12.2, 1.12), 
							   std::complex<double>(12.2, 11.12)), vec(1.1, 2.3f, 1, 2));

	checkVectorSubtraction(vec(std::complex<double>(15.0, 12.3), -17.0, std::complex<double>(-12.2, 1.12), 
							   std::complex<double>(12.2, 11.12)), 
						   vec(std::complex<double>(1215.0, 212.3), 17.1, std::complex<double>(12.22, 21.12), 
							   std::complex<double>(12.2, -131.12)));

	// ----------

	BOOST_CHECK_THROW((CVector<double, 0>() - CVector<int, 4>())(0), Base::IndexError);
	BOOST_CHECK_THROW((CVector<double, 4>() - CVector<int, 0>())(0), Base::IndexError);
	BOOST_CHECK_THROW((CVector<double, 3>() - CVector<int, 2>())(2), Base::IndexError);
	BOOST_CHECK_THROW((CVector<double, 2>() - CVector<int, 3>())(2), Base::IndexError);

	BOOST_CHECK_THROW(operator-(CVector<double, 0>(), CVector<int, 4>())(0), Base::IndexError);
	BOOST_CHECK_THROW(operator-(CVector<double, 4>(), CVector<int, 0>())(0), Base::IndexError);
	BOOST_CHECK_THROW(operator-(CVector<double, 3>(), CVector<int, 2>())(2), Base::IndexError);
	BOOST_CHECK_THROW(operator-(CVector<double, 2>(), CVector<int, 3>())(2), Base::IndexError);

	BOOST_CHECK_NO_THROW((CVector<double, 3>() - CVector<int, 2>()));
	BOOST_CHECK_NO_THROW(operator-(CVector<double, 3>(), CVector<int, 2>()));

	BOOST_CHECK_NO_THROW((CVector<double, 3>() - CVector<int, 2>())(1));
	BOOST_CHECK_NO_THROW(operator-(CVector<double, 3>(), CVector<int, 2>())(1));
}

BOOST_AUTO_TEST_CASE(VectorScalarMultiplicationTest)
{
	using namespace CDPL;
	using namespace Math;

	checkVectorScalarMultiplication(Vector<float>(), -4.2f);
	checkVectorScalarMultiplication(Vector<int>(1, 5), 4.27);
	checkVectorScalarMultiplication(vec(5, -3), -25.778985f);
	checkVectorScalarMultiplication(vec(3, 23, -22), 0.3);
	checkVectorScalarMultiplication(vec(3, 0, 0, -2), int(15));
	checkVectorScalarMultiplication(vec(-233, 100.23, -5.5555, -2), -37.77);
	checkVectorScalarMultiplication(vec(-233, 100.23, -5.5555, -2), 0);

	// ----------

	checkVectorScalarMultiplication(vec(-25, -23, 27), std::complex<int>(-3, 1));
	checkVectorScalarMultiplication(vec(std::complex<double>(-17.2, 4.5), std::complex<double>(15.16, -14.5), 
										std::complex<double>(11.17, 22.15), std::complex<double>(-3.1, -1.25)), 12.2);
	checkVectorScalarMultiplication(vec(std::complex<double>(-17.2, 4.5),
										std::complex<double>(15.16, -14.5), 
										std::complex<double>(11.17, 22.15),
										std::complex<double>(-3.1, -1.25)), std::complex<double>(17.2, -4.5001));
	// ----------

	BOOST_CHECK_NO_THROW((CVector<double, 0>() * 2.12));
	BOOST_CHECK_NO_THROW(operator*(CVector<double, 0>(), 2.12));
}

BOOST_AUTO_TEST_CASE(ScalarVectorMultiplicationTest)
{
	using namespace CDPL;
	using namespace Math;

	checkScalarVectorMultiplication(-4.2f, Vector<float>());
	checkScalarVectorMultiplication(4.27, Vector<int>(1, 5));
	checkScalarVectorMultiplication(-25.778985f, vec(5, -3));
	checkScalarVectorMultiplication(0.3, vec(3, 23, -22));
	checkScalarVectorMultiplication(int(15), vec(3, 0, 0, -2));
	checkScalarVectorMultiplication(-37.77, vec(-233, 100.23, -5.5555, -2));
	checkScalarVectorMultiplication(0, vec(-233, 100.23, -5.5555, -2));

	// ----------

	checkScalarVectorMultiplication(std::complex<int>(-3, 1), vec(-25, -23, 27));
	checkScalarVectorMultiplication(12.2, vec(std::complex<double>(-17.2, 4.5), std::complex<double>(15.16, -14.5), 
											  std::complex<double>(11.17, 22.15), std::complex<double>(-3.1, -1.25)));
	checkScalarVectorMultiplication(std::complex<double>(17.2, -4.5001), vec(std::complex<double>(-17.2, 4.5),
																			 std::complex<double>(15.16, -14.5), 
																			 std::complex<double>(11.17, 22.15),
																			 std::complex<double>(-3.1, -1.25)));
	// ----------

	BOOST_CHECK_NO_THROW(2.12 * (CVector<double, 0>()));
	BOOST_CHECK_NO_THROW(operator*(2.12, CVector<double, 0>()));
}

BOOST_AUTO_TEST_CASE(VectorScalarDivisionTest)
{
	using namespace CDPL;
	using namespace Math;

	checkVectorScalarDivision(Vector<float>(), -4.2f);
	checkVectorScalarDivision(Vector<int>(1, 5), 4.27);
	checkVectorScalarDivision(vec(5, -3), -25.778985f);
	checkVectorScalarDivision(vec(3, 23, -22), 0.3);
	checkVectorScalarDivision(vec(3, 0, 0, -2), int(15));
	checkVectorScalarDivision(vec(-233, 100.23, -5.5555, -2), -37.77);
	checkVectorScalarDivision(vec(-233, 100.23, -5.5555, -2), 0);

	// ----------

	checkVectorScalarDivision(vec(-25, -23, 27), std::complex<int>(-3, 1));
	checkVectorScalarDivision(vec(std::complex<double>(-17.2, 4.5), std::complex<double>(15.16, -14.5), 
										std::complex<double>(11.17, 22.15), std::complex<double>(-3.1, -1.25)), 12.2);
	checkVectorScalarDivision(vec(std::complex<double>(-17.2, 4.5),
										std::complex<double>(15.16, -14.5), 
										std::complex<double>(11.17, 22.15),
										std::complex<double>(-3.1, -1.25)), std::complex<double>(17.2, -4.5001));
	// ----------

	BOOST_CHECK_NO_THROW((CVector<double, 0>() / 2.12));
	BOOST_CHECK_NO_THROW(operator/(CVector<double, 0>(), 2.12));
}

BOOST_AUTO_TEST_CASE(VectorEqualTest)
{
	using namespace CDPL;
	using namespace Math;

	BOOST_CHECK((Vector<int>() == CVector<float, 0>()));
	BOOST_CHECK_EQUAL(operator==(Vector<int>(), CVector<float, 0>()), (Vector<int>() == CVector<float, 0>()));

	BOOST_CHECK((Vector<int>(3, 1) == CVector<float, 3>(1.0f)));
	BOOST_CHECK_EQUAL(operator==(Vector<int>(3, 1), CVector<float, 3>(1.0f)), (Vector<int>(3, 1) == CVector<float, 3>(1.0f)));

	// ----------

	CVector<int, 4> v1 = vec(int(1), int(2), int(-3), int(4));
	Vector<double> v2;

	BOOST_CHECK(!(v1 == v2));
	BOOST_CHECK_EQUAL(operator==(v1, v2), v1 == v2);

	BOOST_CHECK(!(v2 == v1));
	BOOST_CHECK_EQUAL(operator==(v2, v1), v2 == v1);

	v2.resize(2);

	BOOST_CHECK(!(v1 == v2));
	BOOST_CHECK_EQUAL(operator==(v1, v2), v1 == v2);

	BOOST_CHECK(!(v2 == v1));
	BOOST_CHECK_EQUAL(operator==(v2, v1), v2 == v1);

	v2.resize(4);

	BOOST_CHECK(!(v1 == v2));
	BOOST_CHECK_EQUAL(operator==(v1, v2), v1 == v2);

	BOOST_CHECK(!(v2 == v1));
	BOOST_CHECK_EQUAL(operator==(v2, v1), v2 == v1);

	v2(0) = 1;

	BOOST_CHECK(!(v1 == v2));
	BOOST_CHECK_EQUAL(operator==(v1, v2), v1 == v2);

	BOOST_CHECK(!(v2 == v1));
	BOOST_CHECK_EQUAL(operator==(v2, v1), v2 == v1);

	v2(1) = 2;

	BOOST_CHECK(!(v1 == v2));
	BOOST_CHECK_EQUAL(operator==(v1, v2), v1 == v2);

	BOOST_CHECK(!(v2 == v1));
	BOOST_CHECK_EQUAL(operator==(v2, v1), v2 == v1);

	v2(2) = -3;

	BOOST_CHECK(!(v1 == v2));
	BOOST_CHECK_EQUAL(operator==(v1, v2), v1 == v2);

	BOOST_CHECK(!(v2 == v1));
	BOOST_CHECK_EQUAL(operator==(v2, v1), v2 == v1);

	v2(3) = 4;

	BOOST_CHECK(v1 == v2);
	BOOST_CHECK_EQUAL(operator==(v1, v2), v1 == v2);

	BOOST_CHECK(v2 == v1);
	BOOST_CHECK_EQUAL(operator==(v2, v1), v2 == v1);

	// ----------

	v2.resize(5);

	BOOST_CHECK(!(v1 == v2));
	BOOST_CHECK_EQUAL(operator==(v1, v2), v1 == v2);

	BOOST_CHECK(!(v2 == v1));
	BOOST_CHECK_EQUAL(operator==(v2, v1), v2 == v1);

	// ----------

	v2.resize(4);

	BOOST_CHECK(v1 == v2);
	BOOST_CHECK_EQUAL(operator==(v1, v2), v1 == v2);

	BOOST_CHECK(v2 == v1);
	BOOST_CHECK_EQUAL(operator==(v2, v1), v2 == v1);
}

BOOST_AUTO_TEST_CASE(VectorNotEqualTest)
{
	using namespace CDPL;
	using namespace Math;

	BOOST_CHECK(!(Vector<int>() != CVector<float, 0>()));
	BOOST_CHECK_EQUAL(operator!=(Vector<int>(), CVector<float, 0>()), (Vector<int>() != CVector<float, 0>()));

	BOOST_CHECK(!(Vector<int>(3, 1) != CVector<float, 3>(1.0f)));
	BOOST_CHECK_EQUAL(operator!=(Vector<int>(3, 1), CVector<float, 3>(1.0f)), (Vector<int>(3, 1) != CVector<float, 3>(1.0f)));

	// ----------

	CVector<int, 4> v1 = vec(int(1), int(2), int(-3), int(4));
	Vector<double> v2;

	BOOST_CHECK(v1 != v2);
	BOOST_CHECK_EQUAL(operator!=(v1, v2), v1 != v2);

	BOOST_CHECK(v2 != v1);
	BOOST_CHECK_EQUAL(operator!=(v2, v1), v2 != v1);

	v2.resize(2);

	BOOST_CHECK(v1 != v2);
	BOOST_CHECK_EQUAL(operator!=(v1, v2), v1 != v2);

	BOOST_CHECK(v2 != v1);
	BOOST_CHECK_EQUAL(operator!=(v2, v1), v2 != v1);

	v2.resize(4);

	BOOST_CHECK(v1 != v2);
	BOOST_CHECK_EQUAL(operator!=(v1, v2), v1 != v2);

	BOOST_CHECK(v2 != v1);
	BOOST_CHECK_EQUAL(operator!=(v2, v1), v2 != v1);

	v2(0) = 1;

	BOOST_CHECK(v1 != v2);
	BOOST_CHECK_EQUAL(operator!=(v1, v2), v1 != v2);

	BOOST_CHECK(v2 != v1);
	BOOST_CHECK_EQUAL(operator!=(v2, v1), v2 != v1);

	v2(1) = 2;

	BOOST_CHECK(v1 != v2);
	BOOST_CHECK_EQUAL(operator!=(v1, v2), v1 != v2);

	BOOST_CHECK(v2 != v1);
	BOOST_CHECK_EQUAL(operator!=(v2, v1), v2 != v1);

	v2(2) = -3;

	BOOST_CHECK(v1 != v2);
	BOOST_CHECK_EQUAL(operator!=(v1, v2), v1 != v2);

	BOOST_CHECK(v2 != v1);
	BOOST_CHECK_EQUAL(operator!=(v2, v1), v2 != v1);

	v2(3) = 4;

	BOOST_CHECK(!(v1 != v2));
	BOOST_CHECK_EQUAL(operator!=(v1, v2), v1 != v2);

	BOOST_CHECK(!(v2 != v1));
	BOOST_CHECK_EQUAL(operator!=(v2, v1), v2 != v1);

	// ----------

	v2.resize(5);

	BOOST_CHECK(v1 != v2);
	BOOST_CHECK_EQUAL(operator!=(v1, v2), v1 != v2);

	BOOST_CHECK(v2 != v1);
	BOOST_CHECK_EQUAL(operator!=(v2, v1), v2 != v1);

	// ----------

	v2.resize(4);

	BOOST_CHECK(!(v1 != v2));
	BOOST_CHECK_EQUAL(operator!=(v1, v2), v1 != v2);

	BOOST_CHECK(!(v2 != v1));
	BOOST_CHECK_EQUAL(operator!=(v2, v1), v2 != v1);
}

BOOST_AUTO_TEST_CASE(VectorEqualsFunctionTest)
{
	using namespace CDPL;
	using namespace Math;

	BOOST_CHECK(equals(Vector<int>(), CVector<float, 0>(), 0));
	BOOST_CHECK(equals(Vector<int>(3, 1), CVector<float, 3>(1.0f), 0.0));

	// ----------

	CVector<int, 4> v1 = vec(int(1), int(2), int(-3), int(4));
	Vector<double> v2;

	BOOST_CHECK(!equals(v1, v2, 0.0f));
	BOOST_CHECK(!equals(v2, v1, 10.0f));

	v2.resize(2, 0.0);

	BOOST_CHECK(!equals(v1, v2, 10.0f));
	BOOST_CHECK(!equals(v2, v1, 0.0f));

	v2.resize(4, 0.0);

	BOOST_CHECK(!equals(v1, v2, 0.0f));
	BOOST_CHECK(!equals(v2, v1, 0.0f));

	BOOST_CHECK(!equals(v1, v2, 3.9999f));
	BOOST_CHECK(!equals(v2, v1, 3.9999));

	BOOST_CHECK(equals(v1, v2, 4.0f));
	BOOST_CHECK(equals(v2, v1, 4));
	BOOST_CHECK(!equals(v2, v1, -4));

	v2(3) = 4;

	BOOST_CHECK(!equals(v1, v2, 0.0f));
	BOOST_CHECK(!equals(v2, v1, 0.0f));

	BOOST_CHECK(!equals(v1, v2, 2.9999));
	BOOST_CHECK(!equals(v2, v1, 2.9999L));

	BOOST_CHECK(equals(v1, v2, 3.0));
	BOOST_CHECK(equals(v2, v1, 3));
	BOOST_CHECK(!equals(v2, v1, -3));

	v2(2) = -3;

	BOOST_CHECK(!equals(v1, v2, 0.0f));
	BOOST_CHECK(!equals(v2, v1, 0.0f));

	BOOST_CHECK(!equals(v1, v2, 1.9999f));
	BOOST_CHECK(!equals(v2, v1, 1.9999));

	BOOST_CHECK(equals(v1, v2, 2));
	BOOST_CHECK(equals(v2, v1, 2.0f));
	BOOST_CHECK(!equals(v2, v1, -2.0f));

	v2(1) = 2;

	BOOST_CHECK(!equals(v1, v2, 0.0f));
	BOOST_CHECK(!equals(v2, v1, 0.0f));

	BOOST_CHECK(!equals(v1, v2, 0.9999));
	BOOST_CHECK(!equals(v2, v1, 0.9999L));

	BOOST_CHECK(equals(v1, v2, 1));
	BOOST_CHECK(equals(v2, v1, 1.0));
	BOOST_CHECK(!equals(v2, v1, -1.0));

	v2(0) = 1;

	BOOST_CHECK(equals(v1, v2, 0.0f));
	BOOST_CHECK(equals(v2, v1, 0));
	BOOST_CHECK(!equals(v2, v1, -1));

	v2(0) = -1;

	BOOST_CHECK(!equals(v1, v2, 0.0f));
	BOOST_CHECK(!equals(v2, v1, 0));
	BOOST_CHECK(!equals(v2, v1, -1));
	BOOST_CHECK(!equals(v2, v1, 1.999f));
	BOOST_CHECK(equals(v2, v1, 2.0f));
	BOOST_CHECK(equals(v2, v1, 2));

	v2(0) = 1;

	BOOST_CHECK(equals(v1, v2, 0.0f));
	BOOST_CHECK(equals(v2, v1, 0));
	BOOST_CHECK(!equals(v2, v1, -1));

	// ----------

	v2.resize(10);

	BOOST_CHECK(!equals(v1, v2, 10));
	BOOST_CHECK(!equals(v2, v1, 4.0));

	// ----------

	v2.resize(4);

	BOOST_CHECK(equals(v1, v2, 0.0f));
	BOOST_CHECK(equals(v2, v1, 0));
}

BOOST_AUTO_TEST_CASE(VectorConjFunctionTest)
{
	using namespace CDPL;
	using namespace Math;

	checkVectorConjFunction(Vector<float>());

	checkVectorConjFunction(vec(0.0, -120.2));

	checkVectorConjFunction(vec(-1.1f, 2.1f));

	checkVectorConjFunction(vec(-3, 3, 0));

	checkVectorConjFunction(vec(-1.17f, 2.333, 3.21f));

	// ----------

	checkVectorConjFunction(vec(std::complex<double>(-17.2, 4.5), std::complex<double>(15.16, -14.5), 
								std::complex<double>(11.17, 22.15), std::complex<double>(-3.1, -1.25)));
}

BOOST_AUTO_TEST_CASE(VectorHermFunctionTest)
{
	using namespace CDPL;
	using namespace Math;

	checkVectorHermFunction(Vector<float>());

	checkVectorHermFunction(vec(0.0, -120.2));

	checkVectorHermFunction(vec(-1.1f, 2.1f));

	checkVectorHermFunction(vec(-3, 3, 0));

	checkVectorHermFunction(vec(-1.17f, 2.333, 3.21f));

	// ----------

	checkVectorHermFunction(vec(std::complex<double>(-17.2, 4.5), std::complex<double>(15.16, -14.5), 
								std::complex<double>(11.17, 22.15), std::complex<double>(-3.1, -1.25)));
}

BOOST_AUTO_TEST_CASE(VectorRealFunctionTest)
{
	using namespace CDPL;
	using namespace Math;

	checkVectorRealFunction(Vector<float>());

	checkVectorRealFunction(vec(0.0, -120.2));

	checkVectorRealFunction(vec(-1.1f, 2.1f));

	checkVectorRealFunction(vec(-3, 3, 0));

	checkVectorRealFunction(vec(-1.17f, 2.333, 3.21f));

	// ----------

	checkVectorRealFunction(vec(std::complex<double>(-17.2, 4.5), std::complex<double>(15.16, -14.5), 
								std::complex<double>(11.17, 22.15), std::complex<double>(-3.1, -1.25)));
}

BOOST_AUTO_TEST_CASE(VectorImagFunctionTest)
{
	using namespace CDPL;
	using namespace Math;

	checkVectorImagFunction(Vector<float>());

	checkVectorImagFunction(vec(0.0, -120.2));

	checkVectorImagFunction(vec(-1.1f, 2.1f));

	checkVectorImagFunction(vec(-3, 3, 0));

	checkVectorImagFunction(vec(-1.17f, 2.333, 3.21f));

	// ----------

	checkVectorImagFunction(vec(std::complex<double>(-17.2, 4.5), std::complex<double>(15.16, -14.5), 
								std::complex<double>(11.17, 22.15), std::complex<double>(-3.1, -1.25)));
}

BOOST_AUTO_TEST_CASE(VectorElemDivFunctionTest)
{
	using namespace CDPL;
	using namespace Math;

	CVector<double, 4> v1 = vec(1.0, 0.0, 3.12, 4.14);
	CVector<int, 4> v2 = vec(int(15), int(17), int(-12), int(21));

	checkVectorElemDivFunction(v1, v2);

	// ----------

	CVector<std::complex<double>, 4> v3 = vec(std::complex<double>(15.0, 12.3), 17.0, std::complex<double>(-12.2, 1.12), 
											  std::complex<double>(12.2, 11.12));

	checkVectorElemDivFunction(v1, v3);

	// ----------
	CVector<std::complex<double>, 4> v4 = v3;

	v4(2) = -v3(0);
	v4(1) = -v3(3);

	checkVectorElemDivFunction(v3, v4);

	// ----------

	BOOST_CHECK_THROW(elemDiv(CVector<double, 0>(), CVector<int, 0>())(0), Base::IndexError);
	BOOST_CHECK_THROW(elemDiv(CVector<double, 0>(), CVector<int, 4>())(0), Base::IndexError);
	BOOST_CHECK_THROW(elemDiv(CVector<double, 4>(), CVector<int, 0>())(0), Base::IndexError);
	BOOST_CHECK_THROW(elemDiv(CVector<double, 3>(), CVector<int, 2>())(2), Base::IndexError);
	BOOST_CHECK_THROW(elemDiv(CVector<double, 2>(), CVector<int, 3>())(2), Base::IndexError);

	BOOST_CHECK_NO_THROW(elemDiv(CVector<double, 0>(), CVector<int, 0>()));
	BOOST_CHECK_NO_THROW(elemDiv(CVector<double, 3>(), CVector<int, 2>())(1));
	BOOST_CHECK_NO_THROW(elemDiv(CVector<double, 3>(), CVector<int, 2>()));
}

BOOST_AUTO_TEST_CASE(VectorElemProdFunctionTest)
{
	using namespace CDPL;
	using namespace Math;

	CVector<double, 4> v1 = vec(1.0, -2.0, 3.12, 4.14);
	CVector<int, 4> v2 = vec(int(15), int(17), int(-12), int(21));

	checkVectorElemProdFunction(v1, v2);

	// ----------

	CVector<std::complex<double>, 4> v3 = vec(std::complex<double>(15.0, 12.3), 17.0, std::complex<double>(-12.2, 1.12), 
											  std::complex<double>(12.2, 11.12));

	checkVectorElemProdFunction(v1, v3);

	// ----------
	CVector<std::complex<double>, 4> v4 = v3;

	v4(2) = -v3(0);
	v4(1) = -v3(3);

	checkVectorElemProdFunction(v3, v4);

	// ----------

	BOOST_CHECK_THROW(elemProd(CVector<double, 0>(), CVector<int, 0>())(0), Base::IndexError);
	BOOST_CHECK_THROW(elemProd(CVector<double, 0>(), CVector<int, 4>())(0), Base::IndexError);
	BOOST_CHECK_THROW(elemProd(CVector<double, 4>(), CVector<int, 0>())(0), Base::IndexError);
	BOOST_CHECK_THROW(elemProd(CVector<double, 3>(), CVector<int, 2>())(2), Base::IndexError);
	BOOST_CHECK_THROW(elemProd(CVector<double, 2>(), CVector<int, 3>())(2), Base::IndexError);

	BOOST_CHECK_NO_THROW(elemProd(CVector<double, 0>(), CVector<int, 0>()))
	BOOST_CHECK_NO_THROW(elemProd(CVector<double, 3>(), CVector<int, 2>())(1));
	BOOST_CHECK_NO_THROW(elemProd(CVector<double, 3>(), CVector<int, 2>()));
}

BOOST_AUTO_TEST_CASE(VectorCrossProdFunctionTest)
{
	using namespace CDPL;
	using namespace Math;

	checkVectorCrossProdFunction(vec(0.0, 1.0, 0.0), vec(1.0, 0.0, 0.0), vec(0.0, 0.0, -1.0));
	checkVectorCrossProdFunction(vec(1.0, 0.0, 0.0), vec(0.0, 1.0, 0.0), vec(0.0, 0.0, 1.0));
	checkVectorCrossProdFunction(vec(0.0, -1.0, 0.0), vec(-1.0, 0.0, 0.0), vec(0.0, 0.0, -1.0));
	checkVectorCrossProdFunction(vec(-1.0, 0.0, 0.0), vec(0.0, -1.0, 0.0), vec(0.0, 0.0, 1.0));
	checkVectorCrossProdFunction(vec(0.0, -1.0, 0.0), vec(1.0, 0.0, 0.0), vec(0.0, 0.0, 1.0));
	checkVectorCrossProdFunction(vec(1.0, 0.0, 0.0), vec(0.0, -1.0, 0.0), vec(0.0, 0.0, -1.0));
	checkVectorCrossProdFunction(vec(0.0, 1.0, 0.0), vec(-1.0, 0.0, 0.0), vec(0.0, 0.0, 1.0));
	checkVectorCrossProdFunction(vec(-1.0, 0.0, 0.0), vec(0.0, 1.0, 0.0), vec(0.0, 0.0, -1.0));

	// ----------

	checkVectorCrossProdFunction(vec(0.0, 1.0, 0.0), vec(0.0, 0.0, 1.0), vec(1.0, 0.0, 0.0));
	checkVectorCrossProdFunction(vec(0.0, 0.0, 1.0), vec(0.0, 1.0, 0.0), vec(-1.0, 0.0, 0.0));
	checkVectorCrossProdFunction(vec(0.0, -1.0, 0.0), vec(0.0, 0.0, -1.0), vec(1.0, 0.0, 0.0));
	checkVectorCrossProdFunction(vec(0.0, 0.0, -1.0), vec(0.0, -1.0, 0.0), vec(-1.0, 0.0, 0.0));
	checkVectorCrossProdFunction(vec(0.0, -1.0, 0.0), vec(0.0, 0.0, 1.0), vec(-1.0, 0.0, 0.0));
	checkVectorCrossProdFunction(vec(0.0, 0.0, 1.0), vec(0.0, -1.0, 0.0), vec(1.0, 0.0, 0.0));
	checkVectorCrossProdFunction(vec(0.0, 1.0, 0.0), vec(0.0, 0.0, -1.0), vec(-1.0, 0.0, 0.0));
	checkVectorCrossProdFunction(vec(0.0, 0.0, -1.0), vec(0.0, 1.0, 0.0), vec(1.0, 0.0, 0.0));

	// ----------

	checkVectorCrossProdFunction(vec(1.0, 0.0, 0.0), vec(0.0, 0.0, 1.0), vec(0.0, -1.0, 0.0));
	checkVectorCrossProdFunction(vec(0.0, 0.0, 1.0), vec(1.0, 0.0, 0.0), vec(0.0, 1.0, 0.0));
	checkVectorCrossProdFunction(vec(-1.0, 0.0, 0.0), vec(0.0, 0.0, -1.0), vec(0.0, -1.0, 0.0));
	checkVectorCrossProdFunction(vec(0.0, 0.0, -1.0), vec(-1.0, 0.0, 0.0), vec(0.0, 1.0, 0.0));
	checkVectorCrossProdFunction(vec(-1.0, 0.0, 0.0), vec(0.0, 0.0, 1.0), vec(0.0, 1.0, 0.0));
	checkVectorCrossProdFunction(vec(0.0, 0.0, 1.0), vec(-1.0, 0.0, 0.0), vec(0.0, -1.0, 0.0));
	checkVectorCrossProdFunction(vec(1.0, 0.0, 0.0), vec(0.0, 0.0, -1.0), vec(0.0, 1.0, 0.0));
	checkVectorCrossProdFunction(vec(0.0, 0.0, -1.0), vec(1.0, 0.0, 0.0), vec(0.0, -1.0, 0.0));

	// ----------

	checkVectorCrossProdFunction(vec(1.0, 1.0, 1.0), vec(-1.0, 1.0, 1.0), vec(0.0, -2.0, 2.0));

	// ----------

	BOOST_CHECK_THROW(crossProd(Vector<double>(), Vector<double>())(0), Base::SizeError);
	BOOST_CHECK_THROW(crossProd(Vector<double>(1), Vector<double>())(0), Base::SizeError);
	BOOST_CHECK_THROW(crossProd(Vector<double>(3), Vector<double>())(0), Base::SizeError);
	BOOST_CHECK_THROW(crossProd(Vector<double>(4), Vector<double>())(0), Base::SizeError);

	BOOST_CHECK_THROW(crossProd(Vector<double>(), Vector<double>())(0), Base::SizeError);
	BOOST_CHECK_THROW(crossProd(Vector<double>(), Vector<double>(1))(0), Base::SizeError);
	BOOST_CHECK_THROW(crossProd(Vector<double>(), Vector<double>(3))(0), Base::SizeError);
	BOOST_CHECK_THROW(crossProd(Vector<double>(), Vector<double>(4))(0), Base::SizeError);

	BOOST_CHECK_THROW(crossProd(Vector<double>(2), Vector<double>(4))(0), Base::SizeError);
	BOOST_CHECK_THROW(crossProd(Vector<double>(4), Vector<double>(2))(0), Base::SizeError);

	BOOST_CHECK_THROW(crossProd(Vector<double>(1), Vector<double>(2))(0), Base::SizeError);

	BOOST_CHECK_THROW(crossProd(Vector<double>(4), Vector<double>(5))(0), Base::SizeError);

	BOOST_CHECK_THROW(crossProd(Vector<double>(2), Vector<double>(3))(0), Base::SizeError);
	BOOST_CHECK_THROW(crossProd(Vector<double>(3), Vector<double>(2))(0), Base::SizeError);

	BOOST_CHECK_THROW(crossProd(Vector<double>(4), Vector<double>(3))(0), Base::SizeError);
	BOOST_CHECK_THROW(crossProd(Vector<double>(3), Vector<double>(4))(0), Base::SizeError);

	BOOST_CHECK_THROW(crossProd(Vector<double>(4), Vector<double>(3))(3), Base::SizeError);
	BOOST_CHECK_THROW(crossProd(Vector<double>(3), Vector<double>(4))(4), Base::SizeError);


	BOOST_CHECK_NO_THROW(crossProd(Vector<double>(), Vector<double>()));
	BOOST_CHECK_NO_THROW(crossProd(Vector<double>(1), Vector<double>()));
	BOOST_CHECK_NO_THROW(crossProd(Vector<double>(3), Vector<double>()));
	BOOST_CHECK_NO_THROW(crossProd(Vector<double>(4), Vector<double>()));

	BOOST_CHECK_NO_THROW(crossProd(Vector<double>(), Vector<double>()));
	BOOST_CHECK_NO_THROW(crossProd(Vector<double>(), Vector<double>(1)));
	BOOST_CHECK_NO_THROW(crossProd(Vector<double>(), Vector<double>(3)));
	BOOST_CHECK_NO_THROW(crossProd(Vector<double>(), Vector<double>(4)));

	BOOST_CHECK_NO_THROW(crossProd(Vector<double>(2), Vector<double>(4)));
	BOOST_CHECK_NO_THROW(crossProd(Vector<double>(4), Vector<double>(2)));

	BOOST_CHECK_NO_THROW(crossProd(Vector<double>(1), Vector<double>(2)));

	BOOST_CHECK_NO_THROW(crossProd(Vector<double>(4), Vector<double>(5)));

	BOOST_CHECK_NO_THROW(crossProd(Vector<double>(2), Vector<double>(3)));
	BOOST_CHECK_NO_THROW(crossProd(Vector<double>(3), Vector<double>(2)));

	BOOST_CHECK_NO_THROW(crossProd(Vector<double>(4), Vector<double>(3)));
	BOOST_CHECK_NO_THROW(crossProd(Vector<double>(3), Vector<double>(4)));

	BOOST_CHECK_NO_THROW(crossProd(Vector<double>(4), Vector<double>(3)));
	BOOST_CHECK_NO_THROW(crossProd(Vector<double>(3), Vector<double>(4)));
}

BOOST_AUTO_TEST_CASE(VectorInnerProdFunctionTest)
{
	using namespace CDPL;
	using namespace Math;

	CVector<double, 4> v1 = vec(1.0, -2.0, 3.12, 4.14);
	CVector<int, 4> v2 = vec(int(15), int(17), int(-12), int(21));

	checkVectorInnerProdFunction(v1, v2);

	// ----------

	CVector<std::complex<double>, 4> v3 = vec(std::complex<double>(15.0, 12.3), 17.0, std::complex<double>(-12.2, 1.12), 
											  std::complex<double>(12.2, 11.12));

	checkVectorInnerProdFunction(v1, v3);

	// ----------

	checkVectorInnerProdFunction(CVector<double, 0>(), CVector<int, 0>());

	// ----------

	checkVectorInnerProdFunction(CVector<std::complex<double>, 0>(), CVector<std::complex<double>, 0>());
	
	// ----------

	BOOST_CHECK_THROW(innerProd(CVector<double, 0>(), CVector<int, 4>()), Base::SizeError);
	BOOST_CHECK_THROW(innerProd(CVector<double, 4>(), CVector<int, 0>()), Base::SizeError);
	BOOST_CHECK_THROW(innerProd(CVector<double, 3>(), CVector<int, 2>()), Base::SizeError);
	BOOST_CHECK_THROW(innerProd(CVector<double, 2>(), CVector<int, 3>()), Base::SizeError);
}

BOOST_AUTO_TEST_CASE(VectorAngleCosFunctionTest)
{
	using namespace CDPL;
	using namespace Math;

	CVector<double, 4> v1 = vec(1.0, -2.0, 3.12, 4.14);
	CVector<int, 4> v2 = vec(int(15), int(17), int(-12), int(21));

	checkVectorAngleCosFunction(v1, v2, 2.0f, true);

	// ----------

	CVector<float, 4> v3 = vec(17.f, -12.2f, 12.2f, 11.12f);

	checkVectorAngleCosFunction(v1, v3, 1.0, false);

	// ----------

	checkVectorAngleCosFunction(CVector<double, 0>(), CVector<int, 0>(), 3.2, true);

	// ----------

	checkVectorAngleCosFunction(CVector<float, 0>(), CVector<double, 0>(), 0.1, false);
	
	// ----------

	BOOST_CHECK_THROW(angleCos(CVector<double, 0>(), CVector<int, 4>(), 0, true), Base::SizeError);
	BOOST_CHECK_THROW(angleCos(CVector<double, 4>(), CVector<int, 0>(), 1.1, false), Base::SizeError);
	BOOST_CHECK_THROW(angleCos(CVector<double, 3>(), CVector<int, 2>(), -1.2f, true), Base::SizeError);
	BOOST_CHECK_THROW(angleCos(CVector<double, 2>(), CVector<int, 3>(), 100, false), Base::SizeError);
}

BOOST_AUTO_TEST_CASE(VectorSumFunctionTest)
{
	using namespace CDPL;
	using namespace Math;
	
	BOOST_CHECK_EQUAL(sum(Vector<float>()), 0.0f);

	BOOST_CHECK_EQUAL(sum(vec(0.0, 0.0)), 0.0 + 0.0);

	BOOST_CHECK_EQUAL(sum(vec(-1.1f, 1.1f)), -1.1f + 1.1f);

	BOOST_CHECK_EQUAL(sum(vec(-3, 3, 0)), -3 + 3 + 0);

	BOOST_CHECK_EQUAL(sum(vec(-1.17f, 2.333, 3.21f)), -1.17f + 2.333 + 3.21f);

	// ----------

	BOOST_CHECK_EQUAL(sum(vec(std::complex<double>(-17.2, 4.5), std::complex<double>(15.16, -14.5), 
							  std::complex<double>(11.17, 22.15), std::complex<double>(-3.1, -1.25))),
					  std::complex<double>(-17.2, 4.5) + std::complex<double>(15.16, -14.5) + 
					  std::complex<double>(11.17, 22.15) + std::complex<double>(-3.1, -1.25));
}

BOOST_AUTO_TEST_CASE(VectorNorm1FunctionTest)
{
	using namespace CDPL;
	using namespace Math;

	checkVectorNorm1Function(Vector<float>());

	checkVectorNorm1Function(vec(0.0, 0.0));
	checkVectorNorm1Function(vec(-1.0, 1.0));
	checkVectorNorm1Function(vec(-1.0, 1.0, 0.0));
	checkVectorNorm1Function(vec(-1.0, 2.0, -3.0));
	checkVectorNorm1Function(vec(-1.0, -2.0, 3.0));

	// ----------

	checkVectorNorm1Function(vec(std::complex<double>(-17.2, 4.5), std::complex<double>(15.16, -14.5), 
								 std::complex<double>(11.17, 22.15), std::complex<double>(-3.1, -1.25)));
}

BOOST_AUTO_TEST_CASE(VectorNorm2FunctionTest)
{
	using namespace CDPL;
	using namespace Math;

	checkVectorNorm2Function(Vector<float>());

	checkVectorNorm2Function(vec(0.0, 0.0));
	checkVectorNorm2Function(vec(-1.0, 1.0));
	checkVectorNorm2Function(vec(-1.0, 1.0, 0.0));
	checkVectorNorm2Function(vec(-1.0, 2.0, -3.0));
	checkVectorNorm2Function(vec(-1.0, -2.0, 3.0));

	// ----------

	checkVectorNorm2Function(vec(std::complex<double>(-17.2, 4.5), std::complex<double>(15.16, -14.5), 
								 std::complex<double>(11.17, 22.15), std::complex<double>(-3.1, -1.25)));
}

BOOST_AUTO_TEST_CASE(VectorNormInfFunctionTest)
{
	using namespace CDPL;
	using namespace Math;

	BOOST_CHECK_EQUAL(normInf(Vector<float>()), 0.0f);

	BOOST_CHECK_EQUAL(normInf(vec(0.0, 0.0)), TypeTraits<double>::normInf(0.0));

	BOOST_CHECK_EQUAL(normInf(vec(-1.0, 1.0)), TypeTraits<double>::normInf(-1.0));

	BOOST_CHECK_EQUAL(normInf(vec(-1.0, 1.0, 0.0)), TypeTraits<double>::normInf(-1.0));

	BOOST_CHECK_EQUAL(normInf(vec(-1.0, 2.0, -3.0)), TypeTraits<double>::normInf(-3.0));

	BOOST_CHECK_EQUAL(normInf(vec(-1.0, -2.0, 3.0)), TypeTraits<double>::normInf(3.0));

	// ----------

	BOOST_CHECK_EQUAL(normInf(vec(std::complex<double>(-17.2, 4.5), std::complex<double>(15.16, -14.5), 
								  std::complex<double>(11.17, 22.15), std::complex<double>(-3.1, -1.25))),
					  TypeTraits<std::complex<double> >::normInf(std::complex<double>(11.17, 22.15)));
}

BOOST_AUTO_TEST_CASE(VectorNormInfIndexFunctionTest)
{
	using namespace CDPL;
	using namespace Math;

	BOOST_CHECK_EQUAL(normInfIndex(Vector<float>()), 0);

	BOOST_CHECK_EQUAL(normInfIndex(vec(0.0, 0.0)), 0);

	BOOST_CHECK_EQUAL(normInfIndex(vec(-1.0, 1.0)), 0);

	BOOST_CHECK_EQUAL(normInfIndex(vec(-1.0, 1.0, 0.0)), 0);

	BOOST_CHECK_EQUAL(normInfIndex(vec(-1.0, 2.0, -3.0)), 2);

	BOOST_CHECK_EQUAL(normInfIndex(vec(-1.0, -2.0, 3.0)), 2);

	BOOST_CHECK_EQUAL(normInfIndex(vec(-1.0, -3.0, 2.0)), 1);

	// ----------

	BOOST_CHECK_EQUAL(normInfIndex(vec(std::complex<double>(-17.2, 4.5), std::complex<double>(15.16, -14.5), 
									   std::complex<double>(11.17, 22.15), std::complex<double>(-3.1, -1.25))), 2);
}

BOOST_AUTO_TEST_CASE(VectorLengthFunctionTest)
{
	using namespace CDPL;
	using namespace Math;

	checkVectorLengthFunction(Vector<float>());

	checkVectorLengthFunction(vec(0.0, 0.0));
	checkVectorLengthFunction(vec(-1.0, 1.0));
	checkVectorLengthFunction(vec(-1.0, 1.0, 0.0));
	checkVectorLengthFunction(vec(-1.0, 2.0, -3.0));
	checkVectorLengthFunction(vec(-1.0, -2.0, 3.0));

	// ----------

	checkVectorLengthFunction(vec(std::complex<double>(-17.2, 4.5), std::complex<double>(15.16, -14.5), 
								  std::complex<double>(11.17, 22.15), std::complex<double>(-3.1, -1.25)));
}

BOOST_AUTO_TEST_CASE(VectorTransFunctionTest)
{
	using namespace CDPL;
	using namespace Math;

	Vector<double> v1;

	checkVectorTransFunction(v1);

	// ----------

	v1.resize(2, 1.2);

	checkVectorTransFunction(v1);

	v1.resize(4, 3.2);

	checkVectorTransFunction(v1);

	// ----------

	v1 = vec(-2, 4.5, 6.7, 2.0f);

	checkVectorTransFunction(v1);

	// ----------

	Vector<std::complex<double> > v2 = vec(std::complex<double>(-17.2, 4.5), std::complex<double>(15.16, -14.5), 
										   std::complex<double>(11.17, 22.15), std::complex<double>(-3.1, -1.25));

	checkVectorTransFunction(v2);
}

BOOST_AUTO_TEST_CASE(VectorRotateFunctionTest)
{
	using namespace CDPL;
	using namespace Math;

	BOOST_CHECK_THROW(rotate(Quaternion<double>(0), vec(int(5), int(0)))(0), Base::SizeError);
	BOOST_CHECK_THROW(rotate(Quaternion<double>(0), Vector<int>(1))(0), Base::SizeError);
	BOOST_CHECK_THROW(rotate(Quaternion<double>(0), Vector<float>())(0), Base::SizeError);

	// ----------

	checkVectorRotateFunction(Quaternion<double>(0), vec(int(5), int(0), int(0)));
	checkVectorRotateFunction(Quaternion<int>(5), vec(0.0, 0.0, 0.0, 2.0));
	checkVectorRotateFunction(Quaternion<double>(5, -3), vec(3.0f, 23.0f, -22.0f, -13.2f));
	checkVectorRotateFunction(Quaternion<float>(3, 23, -22, 1), vec(3.0, 0.01, -2.0));
	checkVectorRotateFunction(Quaternion<int>(3, 0, 0, -2), vec(-233.0, 100.23, -5.5555));
	checkVectorRotateFunction(Quaternion<double>(-233, 100.23, -5.5555, -2), vec(0.230, -42.4245, -0.1));

	// ----------

	checkVectorRotateFunction(RealQuaternion<int>(0), vec(0.230, -42.4245, -0.1));
	checkVectorRotateFunction(RealQuaternion<float>(-2.34245f), vec(0.230, -42.4245, -0.1, 0.0));
	checkVectorRotateFunction(RealQuaternion<double>(42.4245), vec(0.230, -42.4245, -0.1, 1.2));
	checkVectorRotateFunction(RealQuaternion<std::complex<double> >(std::complex<double>(-17.2, 4.5)), vec(0.230, -42.4245, -0.1));

	// ----------

	checkVectorRotateFunction(Quaternion<std::complex<double> >(std::complex<double>(-17.2, 4.5), std::complex<double>(15.16, -14.5), 
																std::complex<double>(11.17, 22.15), std::complex<double>(-3.1, -1.25)), 
							  vec(std::complex<double>(37.2, 24.5), std::complex<double>(-15.16, 14.5), std::complex<double>(-1.17, -52.15),
								  std::complex<double>(3.1, 1.425)));

	// ----------

	Quaternion<double> q(1.0, 0.0, 0.0, 0.0);
	Vector<double> v = vec(1.0, 0.0, 0.0);

	BOOST_CHECK_CLOSE(rotate(q, v)(0), 1.0, 0.0000001);
	BOOST_CHECK_SMALL(rotate(q, v)(1), 0.0000001);
	BOOST_CHECK_SMALL(rotate(q, v)(2), 0.0000001);

	q.getC1() = std::cos(M_PI / 180.0 * 60.0); 
	q.getC2() = std::sin(M_PI / 180.0 * 60.0) / std::sqrt(3.0); 
	q.getC3() = std::sin(M_PI / 180.0 * 60.0) / std::sqrt(3.0); 
	q.getC4() = std::sin(M_PI / 180.0 * 60.0) / std::sqrt(3.0); 

	BOOST_CHECK_SMALL(rotate(q, v)(0), 0.0000001);
	BOOST_CHECK_CLOSE(rotate(q, v)(1), 1.0, 0.0000001);
	BOOST_CHECK_SMALL(rotate(q, v)(2), 0.0000001);
}
