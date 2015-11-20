/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * FunctionalTest.cpp 
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


#include <complex>
#include <cmath>

#include <boost/test/auto_unit_test.hpp>

#include "CDPL/Math/Functional.hpp"
#include "CDPL/Math/Vector.hpp"
#include "CDPL/Math/Matrix.hpp"
#include "CDPL/Math/Quaternion.hpp"
#include "CDPL/Base/Exceptions.hpp"


namespace
{
	
	template <typename V1, typename V2>
	void checkVectorInnerProduct(const V1& v1, const V2& v2)
	{
		using namespace CDPL;
		using namespace Math;

		typedef VectorInnerProduct<V1, V2> VIP;
		typedef typename CommonType<typename V1::SizeType, typename V2::SizeType>::Type SizeType;
		typedef typename VIP::ResultType ResultType;

		ResultType res = VIP::apply(v1, v2);
		ResultType exp_val = ResultType();

		for (SizeType i = 0; i < v1.getSize(); i++)
			exp_val += v1(i) * v2(i);

		BOOST_CHECK_EQUAL(res, exp_val);
		BOOST_CHECK_EQUAL((VectorInnerProduct<V2, V1>::apply(v2, v1)), exp_val);
	}

	template <typename V1, typename V2, typename V3>
	void checkVectorCrossProduct(const V1& v1, const V2& v2, const V3& exp_res)
	{
		using namespace CDPL;
		using namespace Math;

		typedef VectorCrossProduct<V1, V2> VCP;
		typedef typename CommonType<typename V1::SizeType, typename V2::SizeType>::Type SizeType;
		typedef typename VCP::ResultType ResultType;

		for (SizeType i = 0; i < 3; i++)
			BOOST_CHECK_EQUAL(VCP::apply(v1, v2, i), exp_res(i));

		for (SizeType i = 3; i < 6; i++)
			BOOST_CHECK_EQUAL(VCP::apply(v1, v2, i), ResultType());
	}

	template <typename V>
	void checkVectorNorm1(const V& v)
	{
		using namespace CDPL;
		using namespace Math;

		typedef VectorNorm1<V> VN;
		typedef typename VN::RealType RealType;
		typedef typename VN::ValueType ValueType;
		typedef typename V::SizeType SizeType;

		RealType exp_val = RealType();

		for (SizeType i = 0; i < v.getSize(); i++)
			exp_val += TypeTraits<ValueType>::norm1(v(i));

		BOOST_CHECK_EQUAL(VN::apply(v), exp_val);
	}

	template <typename V>
	void checkVectorNorm2(const V& v)
	{
		using namespace CDPL;
		using namespace Math;

		typedef VectorNorm2<V> VN;
		typedef typename VN::RealType RealType;
		typedef typename VN::ValueType ValueType;
		typedef typename V::SizeType SizeType;

		RealType exp_val = RealType();

		for (SizeType i = 0; i < v.getSize(); i++) {
			RealType t = TypeTraits<ValueType>::norm2(v(i));
			exp_val += t * t;
		}

		exp_val = TypeTraits<RealType>::sqrt(exp_val);

		BOOST_CHECK_EQUAL(VN::apply(v), exp_val);
	}

	template <typename V>
	void checkDiagonalMatrix(const V& v)
	{
		using namespace CDPL;
		using namespace Math;

		typedef DiagonalMatrixFromVector<V> VDM;
		typedef typename VDM::SizeType SizeType;
		typedef typename VDM::ResultType ResultType;

		for (SizeType i = 0; i < v.getSize() + 3; i++) {
			for (SizeType j = 0; j < v.getSize() + 2; j++) {
				if (i != j)
					BOOST_CHECK_EQUAL(VDM::apply(v, i, j), ResultType());
				else if (i >= v.getSize()) {
					BOOST_CHECK_THROW(VDM::apply(v, i, j), Base::IndexError);
				} else 
				 	BOOST_CHECK_EQUAL(VDM::apply(v, i, j), v(i));
			}
		}
	}

	template <typename V>
	void checkCrossProdMatrix(const V& v)
	{
		//                       |  0  -a3  a2 |
		// cross([a1, a2, a3]) = |  a3  0  -a1 |
		//                       | -a2  a1  0  |
		
		using namespace CDPL;
		using namespace Math;

		typedef CrossProductMatrixFromVector<V> VCPM;
		typedef typename VCPM::ResultType ResultType;
		typedef typename VCPM::SizeType SizeType;

		for (SizeType i = 0; i < 5; i++) {
			for (SizeType j = 0; j < 6; j++) {
				ResultType val = VCPM::apply(v, i, j);
				ResultType exp_val = ResultType();

				switch (i) {

					case 0:
						switch (j) {

							case 1:
								exp_val = -v(2);
								break;

							case 2:
								exp_val = v(1);

							default:
								break;
						}
						break;

					case 1:
						switch (j) {

							case 0:
								exp_val = v(2);
								break;

							case 2:
								exp_val = -v(0);

							default:
								break;
						}
						break;

					case 2:
						switch (j) {

							case 0:
								exp_val = -v(1);
								break;

							case 1:
								exp_val = v(0);

							default:
								break;
						}

					default:
						break;
				}

				BOOST_CHECK_EQUAL(val, exp_val);
			}
		}
	}

	template <typename M>
	void checkMatrixElementSum(const M& m)
	{
		using namespace CDPL;
		using namespace Math;

		typedef MatrixElementSum<M> MES;
		typedef typename MES::ResultType ResultType;
		typedef typename M::SizeType SizeType;

		ResultType exp_val = ResultType();

		for (SizeType i = 0; i < m.getSize1(); i++)
			for (SizeType j = 0; j < m.getSize2(); j++)
				exp_val += m(i, j);

		BOOST_CHECK_EQUAL(MES::apply(m), exp_val);
	}

	template <typename M>
	void checkMatrixTrace(const M& m)
	{
		using namespace CDPL;
		using namespace Math;

		typedef MatrixTrace<M> MT;
		typedef typename MT::ResultType ResultType;
		typedef typename M::SizeType SizeType;

		ResultType exp_val = ResultType();

		for (SizeType i = 0; i < m.getSize1(); i++)
			for (SizeType j = 0; j < m.getSize2(); j++)
				if (i == j)
					exp_val += m(i, j);

		BOOST_CHECK_EQUAL(MT::apply(m), exp_val);
	}

	template <typename M>
	void checkMatrixNorm1(const M& m, typename M::SizeType col)
	{
		using namespace CDPL;
		using namespace Math;

		typedef MatrixNorm1<M> MN;
		typedef typename MN::RealType RealType;
		typedef typename MN::ValueType ValueType;
		typedef typename M::SizeType SizeType;

		RealType exp_val = RealType();

		for (SizeType i = 0; i < m.getSize1(); i++)
			exp_val += TypeTraits<ValueType>::norm1(m(i, col));

		BOOST_CHECK_EQUAL(MN::apply(m), exp_val);
	}

	template <typename M>
	void checkMatrixNormFrobenius(const M& m)
	{
		using namespace CDPL;
		using namespace Math;

		typedef MatrixNormFrobenius<M> MN;
		typedef typename MN::RealType RealType;
		typedef typename MN::ValueType ValueType;
		typedef typename M::SizeType SizeType;

		RealType exp_val = RealType();

		for (SizeType i = 0; i < m.getSize1(); i++) {
			for (SizeType j = 0; j < m.getSize2(); j++) {
				RealType t = TypeTraits<ValueType>::norm2(m(i, j));
				exp_val += t * t;
			}
		}

		exp_val = TypeTraits<RealType>::sqrt(exp_val);

		BOOST_CHECK_EQUAL(MN::apply(m), exp_val);
	}

	template <typename M>
	void checkMatrixNormInfinity(const M& m, typename M::SizeType row)
	{
		using namespace CDPL;
		using namespace Math;

		typedef MatrixNormInfinity<M> MN;
		typedef typename MN::RealType RealType;
		typedef typename MN::ValueType ValueType;
		typedef typename M::SizeType SizeType;

		RealType exp_val = RealType();

		for (SizeType i = 0; i < m.getSize2(); i++)
			exp_val += TypeTraits<ValueType>::normInf(m(row, i));

		BOOST_CHECK_EQUAL(MN::apply(m), exp_val);
	}

	template <typename M, typename V>
	void checkMatrixVectorProd(const M& m, const V& v)
	{
		using namespace CDPL;
		using namespace Math;

		typedef MatrixVectorProduct<M, V> MVP;
		typedef typename MVP::ResultType ResultType;
		typedef typename MVP::SizeType SizeType;

		for (SizeType i = 0; i < m.getSize1(); i++) {
			ResultType val = MVP::apply(m, v, i);
			ResultType exp_val = ResultType();

			for (SizeType j = 0; j < v.getSize(); j++)
				exp_val += m(i, j) * v(j);

			BOOST_CHECK_EQUAL(val, exp_val);
		}

		if (m.getSize2() > 0)
			BOOST_CHECK_THROW(MVP::apply(m, v, m.getSize1()), Base::IndexError);
	}

	template <typename V, typename M>
	void checkVectorMatrixProd(const V& v, const M& m)
	{
		using namespace CDPL;
		using namespace Math;

		typedef VectorMatrixProduct<M, V> VMP;
		typedef typename VMP::ResultType ResultType;
		typedef typename VMP::SizeType SizeType;

		for (SizeType i = 0; i < m.getSize2(); i++) {
			ResultType val = VMP::apply(v, m, i);
			ResultType exp_val = ResultType();

			for (SizeType j = 0; j < v.getSize(); j++)
				exp_val += m(j, i) * v(j);

			BOOST_CHECK_EQUAL(val, exp_val);
		}

		if (m.getSize1() > 0)
			BOOST_CHECK_THROW(VMP::apply(v, m, m.getSize2()), Base::IndexError);
	}

	template <typename M1, typename M2>
	void checkMatrixProd(const M1& m1, const M2& m2)
	{
		using namespace CDPL;
		using namespace Math;

		typedef MatrixProduct<M1, M2> MP;
		typedef typename MP::ResultType ResultType;
		typedef typename MP::SizeType SizeType;

		for (SizeType i = 0; i < m1.getSize1(); i++) {
			for (SizeType j = 0; j < m2.getSize2(); j++) {
				ResultType val = MP::apply(m1, m2, i, j);
				ResultType exp_val = ResultType();

				for (SizeType k = 0; k < m1.getSize2(); k++)
					exp_val += m1(i, k) * m2(k, j);

				BOOST_CHECK_EQUAL(val, exp_val);
			}
		}

		if (m1.getSize2() > 0) {
			BOOST_CHECK_THROW(MP::apply(m1, m2, m1.getSize1(), 0), Base::IndexError);
			BOOST_CHECK_THROW(MP::apply(m1, m2, 0, m2.getSize2()), Base::IndexError);
		}
	}

	template <typename Q>
	void checkQuaternionNorm(const Q& q)
	{
		using namespace CDPL;
		using namespace Math;

		typedef QuaternionNorm<Q> QN;
		typedef typename QN::RealType RealType;

		BOOST_CHECK_EQUAL(QN::apply(q), TypeTraits<RealType>::sqrt(q.getC1() * q.getC1() + q.getC2() * q.getC2() +
																   q.getC3() * q.getC3() + q.getC4() * q.getC4()));
	}

	template <typename Q>
	void checkQuaternionNorm2(const Q& q)
	{
		using namespace CDPL;
		using namespace Math;

		typedef QuaternionNorm2<Q> QN;

		BOOST_CHECK_EQUAL(QN::apply(q), (q.getC1() * q.getC1() + q.getC2() * q.getC2() +
										 q.getC3() * q.getC3() + q.getC4() * q.getC4()));
	}

	template <typename Q>
	void checkQuaternionUnreal(const Q& q)
	{
		using namespace CDPL;
		using namespace Math;

		typedef QuaternionUnreal<Q> QU;

		BOOST_CHECK_EQUAL(QU::applyC1(q), typename QU::ResultType());
		BOOST_CHECK_EQUAL(QU::applyC2(q), q.getC2());
		BOOST_CHECK_EQUAL(QU::applyC3(q), q.getC3());
		BOOST_CHECK_EQUAL(QU::applyC4(q), q.getC4());
	}

	template <typename Q>
	void checkQuaternionConjugate(const Q& q)
	{
		using namespace CDPL;
		using namespace Math;

		typedef QuaternionConjugate<Q> QC;

		BOOST_CHECK_EQUAL(QC::applyC1(q),  q.getC1());
		BOOST_CHECK_EQUAL(QC::applyC2(q), -q.getC2());
		BOOST_CHECK_EQUAL(QC::applyC3(q), -q.getC3());
		BOOST_CHECK_EQUAL(QC::applyC4(q), -q.getC4());
	}

	template <typename T, typename Q>
	void checkScalarQuaternionAddition(const T& t, const Q& q)
	{
		using namespace CDPL;
		using namespace Math;

		typedef Scalar1QuaternionAddition<T, Q> SQA;

		BOOST_CHECK_EQUAL(SQA::applyC1(t, q), t + q.getC1());
		BOOST_CHECK_EQUAL(SQA::applyC2(t, q), q.getC2());
		BOOST_CHECK_EQUAL(SQA::applyC3(t, q), q.getC3());
		BOOST_CHECK_EQUAL(SQA::applyC4(t, q), q.getC4());
	}

	template <typename T, typename Q>
	void checkScalarQuaternionSubtraction(const T& t, const Q& q)
	{
		using namespace CDPL;
		using namespace Math;

		typedef Scalar1QuaternionSubtraction<T, Q> SQS;

		BOOST_CHECK_EQUAL(SQS::applyC1(t, q), t - q.getC1());
		BOOST_CHECK_EQUAL(SQS::applyC2(t, q), -q.getC2());
		BOOST_CHECK_EQUAL(SQS::applyC3(t, q), -q.getC3());
		BOOST_CHECK_EQUAL(SQS::applyC4(t, q), -q.getC4());
	}

	template <typename Q, typename T>
	void checkQuaternionScalarAddition(const Q& q, const T& t)
	{
		using namespace CDPL;
		using namespace Math;

		typedef Scalar2QuaternionAddition<Q, T> SQA;

		BOOST_CHECK_EQUAL(SQA::applyC1(q, t), q.getC1() + t);
		BOOST_CHECK_EQUAL(SQA::applyC2(q, t), q.getC2());
		BOOST_CHECK_EQUAL(SQA::applyC3(q, t), q.getC3());
		BOOST_CHECK_EQUAL(SQA::applyC4(q, t), q.getC4());
	}

	template <typename Q, typename T>
	void checkQuaternionScalarSubtraction(const Q& q, const T& t)
	{
		using namespace CDPL;
		using namespace Math;

		typedef Scalar2QuaternionSubtraction<Q, T> SQS;

		BOOST_CHECK_EQUAL(SQS::applyC1(q, t), q.getC1() - t);
		BOOST_CHECK_EQUAL(SQS::applyC2(q, t), q.getC2());
		BOOST_CHECK_EQUAL(SQS::applyC3(q, t), q.getC3());
		BOOST_CHECK_EQUAL(SQS::applyC4(q, t), q.getC4());
	}

	template <typename Q, typename T>
	void checkQuaternionInverse(const Q& q, const T& t)
	{
		using namespace CDPL;
		using namespace Math;

		typedef QuaternionInverse<Q, T> QI;

		BOOST_CHECK_EQUAL(QI::applyC1(q, t),  q.getC1() / t);
		BOOST_CHECK_EQUAL(QI::applyC2(q, t), -q.getC2() / t);
		BOOST_CHECK_EQUAL(QI::applyC3(q, t), -q.getC3() / t);
		BOOST_CHECK_EQUAL(QI::applyC4(q, t), -q.getC4() / t);
	}

	template <typename Q1, typename Q2>
	void checkQuaternionProduct(const Q1& q1, const Q2& q2)
	{
		using namespace CDPL;
		using namespace Math;

		typedef QuaternionProduct<Q1, Q2> QP;
		typedef typename QP::ResultType ResultType;

		// a = a1 * a2 - b1 * b2 - c1 * c2 - d1 * d2
		ResultType c1 = q1.getC1() * q2.getC1() - q1.getC2() * q2.getC2() 
			- q1.getC3() * q2.getC3() - q1.getC4() * q2.getC4();

		// b = a1 * b2 + b1 * a2 + c1 * d2 - d1 * c2 
		ResultType c2 =	q1.getC1() * q2.getC2() + q1.getC2() * q2.getC1() 
			+ q1.getC3() * q2.getC4() - q1.getC4() * q2.getC3();

		// c = a1 * c2 - b1 * d2 + c1 * a2 + d1 * b2
		ResultType c3 =	q1.getC1() * q2.getC3() - q1.getC2() * q2.getC4() 
			+ q1.getC3() * q2.getC1() + q1.getC4() * q2.getC2();
	
		// d = a1 * d2 + b1 * c2 - c1 * b2 + d1 * a2
		ResultType c4 =	q1.getC1() * q2.getC4() + q1.getC2() * q2.getC3() 
			- q1.getC3() * q2.getC2() + q1.getC4() * q2.getC1();
	
		BOOST_CHECK_EQUAL(QP::applyC1(q1, q2), c1);
		BOOST_CHECK_EQUAL(QP::applyC2(q1, q2), c2);
		BOOST_CHECK_EQUAL(QP::applyC3(q1, q2), c3);
		BOOST_CHECK_EQUAL(QP::applyC4(q1, q2), c4);
	}

	template <typename Q1, typename Q2, typename T>
	void checkQuaternionDivision(const Q1& q1, const Q2& q2, const T& t)
	{
		using namespace CDPL;
		using namespace Math;

		typedef QuaternionDivision<Q1, Q2, T> QD;
		typedef typename QD::ResultType ResultType;

		// a = (a1 * a2 + b1 * b2 + c1 * c2 + d1 * d2) / t
		ResultType c1 = (q1.getC1() * q2.getC1() + q1.getC2() * q2.getC2() 
						 + q1.getC3() * q2.getC3() + q1.getC4() * q2.getC4()) / t;

		// b = (-a1 * b2 + b1 * a2 - c1 * d2 + d1 * c2 ) / t
		ResultType c2 =	(-q1.getC1() * q2.getC2() + q1.getC2() * q2.getC1() 
						 - q1.getC3() * q2.getC4() + q1.getC4() * q2.getC3()) / t;

		// c = (-a1 * c2 + b1 * d2 + c1 * a2 - d1 * b2) / t
		ResultType c3 =	(-q1.getC1() * q2.getC3() + q1.getC2() * q2.getC4() 
						 + q1.getC3() * q2.getC1() - q1.getC4() * q2.getC2()) / t;
	
		// d = (-a1 * d2 - b1 * c2 + c1 * b2 + d1 * a2) / t
		ResultType c4 =	(-q1.getC1() * q2.getC4() - q1.getC2() * q2.getC3() 
						 + q1.getC3() * q2.getC2() + q1.getC4() * q2.getC1()) / t;
	
		BOOST_CHECK_EQUAL(QD::applyC1(q1, q2, t), c1);
		BOOST_CHECK_EQUAL(QD::applyC2(q1, q2, t), c2);
		BOOST_CHECK_EQUAL(QD::applyC3(q1, q2, t), c3);
		BOOST_CHECK_EQUAL(QD::applyC4(q1, q2, t), c4);
	}

	template <typename T1, typename Q, typename T2>
	void checkScalarQuaternionDivision(const T1& t1, const Q& q, const T2& t2)
	{
		using namespace CDPL;
		using namespace Math;

		typedef ScalarQuaternionDivision<T1, Q, T2> SQD;
	
		BOOST_CHECK_EQUAL(SQD::applyC1(t1, q, t2), t1 * q.getC1() / t2);
		BOOST_CHECK_EQUAL(SQD::applyC2(t1, q, t2), t1 * -q.getC2() / t2);
		BOOST_CHECK_EQUAL(SQD::applyC3(t1, q, t2), t1 * -q.getC3() / t2);
		BOOST_CHECK_EQUAL(SQD::applyC4(t1, q, t2), t1 * -q.getC4() / t2);
	}

	template <typename Q, typename V>
	void checkQuaternionVectorRotation(const Q& q, const V& v)
	{
		using namespace CDPL;
		using namespace Math;

		typedef QuaternionVectorRotation<Q, V> QVR;
		typedef typename QVR::ResultType ResultType;

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
	
		BOOST_CHECK_EQUAL(QVR::apply(q, v, 0), vr1);
		BOOST_CHECK_EQUAL(QVR::apply(q, v, 1), vr2);
		BOOST_CHECK_EQUAL(QVR::apply(q, v, 2), vr3);

		BOOST_CHECK_EQUAL(QVR::apply(q, v, 3), ResultType());
		BOOST_CHECK_EQUAL(QVR::apply(q, v, 4), ResultType());
	}
}


BOOST_AUTO_TEST_CASE(ScalarAssignmentTest)
{
	using namespace CDPL;
	using namespace Math;

	double lhs1 = 3.0;
	float rhs1 = -2.0f;
	double result1;

	result1 = rhs1; 

	ScalarAssignment<double, float>::apply(lhs1, rhs1);

	BOOST_CHECK_EQUAL(lhs1, result1);

	// ----------

	std::complex<double> lhs2(3.1, -4.27);
	std::complex<float> rhs2(2.0f, 17.8);
	std::complex<double> result2;

	result2 = rhs2; 

	ScalarAssignment<std::complex<double>, std::complex<float> >::apply(lhs2, rhs2);

	BOOST_CHECK_EQUAL(lhs2, result2);
}

BOOST_AUTO_TEST_CASE(ScalarAdditionAssignmentTest)
{
	using namespace CDPL;
	using namespace Math;

	unsigned int lhs1 = 15;
	float rhs1 = -2.12f;
	unsigned int result1 = lhs1;

	result1 += rhs1; 

	ScalarAdditionAssignment<unsigned int, float>::apply(lhs1, rhs1);

	BOOST_CHECK_EQUAL(lhs1, result1);

	// ----------

	std::complex<double> lhs2(3.1, -4.27);
	std::complex<float> rhs2(2.0f, 17.8);
	std::complex<double> result2 = lhs2;

	result2 += rhs2; 

	ScalarAdditionAssignment<std::complex<double>, std::complex<float> >::apply(lhs2, rhs2);

	BOOST_CHECK_EQUAL(lhs2, result2);
}

BOOST_AUTO_TEST_CASE(ScalarSubtractionAssignmentTest)
{
	using namespace CDPL;
	using namespace Math;

	float lhs1 = -15.12f;
	int rhs1 = -12;
	float result1 = lhs1;

	result1 -= rhs1; 

	ScalarSubtractionAssignment<float, int>::apply(lhs1, rhs1);

	BOOST_CHECK_EQUAL(lhs1, result1);

	// ----------

	std::complex<double> lhs2(3.1, -4.27);
	std::complex<float> rhs2(2.0f, 17.8);
	std::complex<double> result2 = lhs2;

	result2 -= rhs2; 

	ScalarSubtractionAssignment<std::complex<double>, std::complex<float> >::apply(lhs2, rhs2);

	BOOST_CHECK_EQUAL(lhs2, result2);
}

BOOST_AUTO_TEST_CASE(ScalarMultiplicationAssignmentTest)
{
	using namespace CDPL;
	using namespace Math;

	double lhs1 = 3.0;
	int rhs1 = -2;
	double result1 = lhs1;

	result1 *= rhs1; 

	ScalarMultiplicationAssignment<double, int>::apply(lhs1, rhs1);

	BOOST_CHECK_EQUAL(lhs1, result1);

	// ----------

	std::complex<double> lhs2(3.1, -4.27);
	std::complex<float> rhs2(-2.12f, 1.1f);
	std::complex<double> result2 = lhs2;

	result2 *= rhs2; 

	ScalarMultiplicationAssignment<std::complex<double>, std::complex<float> >::apply(lhs2, rhs2);

	BOOST_CHECK_EQUAL(lhs2, result2);
}

BOOST_AUTO_TEST_CASE(ScalarDivisionAssignmentTest)
{
	using namespace CDPL;
	using namespace Math;

	double lhs1 = 3.0;
	int rhs1 = -2;
	double result1 = lhs1;

	result1 /= rhs1; 

	ScalarDivisionAssignment<double, int>::apply(lhs1, rhs1);

	BOOST_CHECK_EQUAL(lhs1, result1);

	// ----------

	std::complex<double> lhs2(3.1, -4.27);
	std::complex<float> rhs2(2.12f, 13.12f);
	std::complex<double> result2 = lhs2;

	result2 /= rhs2; 

	ScalarDivisionAssignment<std::complex<double>, std::complex<float> >::apply(lhs2, rhs2);

	BOOST_CHECK_EQUAL(lhs2, result2);
}

BOOST_AUTO_TEST_CASE(ScalarNegationTest)
{
	using namespace CDPL;
	using namespace Math;
	
	BOOST_CHECK_EQUAL(ScalarNegation<int>::apply(5), int(-5));
	BOOST_CHECK_EQUAL(ScalarNegation<unsigned int>::apply(5), static_cast<unsigned int>(-5));
	BOOST_CHECK_EQUAL(ScalarNegation<float>::apply(-5.0f), 5.0f);

	BOOST_CHECK_EQUAL(ScalarNegation<std::complex<double> >::apply(std::complex<double>(3.1, -4.27)), -std::complex<double>(3.1, -4.27));
}

BOOST_AUTO_TEST_CASE(ScalarConjugationTest)
{
	using namespace CDPL;
	using namespace Math;
	
	BOOST_CHECK_EQUAL(ScalarConjugation<int>::apply(5), int(5));
	BOOST_CHECK_EQUAL(ScalarConjugation<double>::apply(-5.0), -5.0);

	BOOST_CHECK_EQUAL(ScalarConjugation<std::complex<double> >::apply(std::complex<double>(3.1, -4.27)), std::complex<double>(3.1, 4.27));
}

BOOST_AUTO_TEST_CASE(ScalarRealTest)
{
	using namespace CDPL;
	using namespace Math;
	
	BOOST_CHECK_EQUAL(ScalarReal<int>::apply(5), int(5));
	BOOST_CHECK_EQUAL(ScalarReal<double>::apply(-5.0), -5.0);

	BOOST_CHECK_EQUAL(ScalarReal<std::complex<double> >::apply(std::complex<double>(3.1, -4.27)), 3.1);
}

BOOST_AUTO_TEST_CASE(ScalarImaginaryTest)
{
	using namespace CDPL;
	using namespace Math;

	BOOST_CHECK_EQUAL(ScalarImaginary<int>::apply(5), int(0));
	BOOST_CHECK_EQUAL(ScalarImaginary<double>::apply(-5.0), 0.0);

	BOOST_CHECK_EQUAL(ScalarImaginary<std::complex<double> >::apply(std::complex<double>(3.1, -4.27)), -4.27);
}

BOOST_AUTO_TEST_CASE(ScalarAdditionTest)
{
	using namespace CDPL;
	using namespace Math;

	unsigned int lhs1 = 15;
	float rhs1 = -2.12f;
	float result1 = lhs1 + rhs1;

	BOOST_CHECK_EQUAL((ScalarAddition<unsigned int, float>::apply(lhs1, rhs1)), result1);
	BOOST_CHECK_EQUAL((ScalarAddition<float, unsigned int>::apply(rhs1, lhs1)), result1);

	// ----------

	std::complex<double> lhs2(3.1, -4.27);
	std::complex<double> rhs2(2.0, 17.8);
	std::complex<double> result2 = lhs2 + rhs2;

	BOOST_CHECK_EQUAL((ScalarAddition<std::complex<double>, std::complex<double> >::apply(lhs2, rhs2)), result2);
}

BOOST_AUTO_TEST_CASE(ScalarSubtractionTest)
{
	using namespace CDPL;
	using namespace Math;

	float lhs1 = -15.67f;
	double rhs1 = 2.11111111;
	double result1 = lhs1 - rhs1;

	BOOST_CHECK_EQUAL((ScalarSubtraction<float, double>::apply(lhs1, rhs1)), result1);

	// ----------

	std::complex<double> lhs2(3.1, -4.27);
	std::complex<double> rhs2(-2.12, -17.8);
	std::complex<double> result2 = lhs2 - rhs2;

	BOOST_CHECK_EQUAL((ScalarSubtraction<std::complex<double>, std::complex<double> >::apply(lhs2, rhs2)), result2);
}

BOOST_AUTO_TEST_CASE(ScalarMultiplicationTest)
{
	using namespace CDPL;
	using namespace Math;

	unsigned int lhs1 = 15;
	long rhs1 = -22;
	long result1 = lhs1 * rhs1;

	BOOST_CHECK_EQUAL((ScalarMultiplication<unsigned int, long>::apply(lhs1, rhs1)), result1);
	BOOST_CHECK_EQUAL((ScalarMultiplication<long, unsigned int>::apply(rhs1, lhs1)), result1);

	// ----------

	std::complex<double> lhs2(13.1, -24.27);
	double rhs2 = -17.8;
	std::complex<double> result2 = lhs2 * rhs2;

	BOOST_CHECK_EQUAL((ScalarMultiplication<std::complex<double>, double>::apply(lhs2, rhs2)), result2);
	BOOST_CHECK_EQUAL((ScalarMultiplication<double, std::complex<double> >::apply(rhs2, lhs2)), result2);
}

BOOST_AUTO_TEST_CASE(ScalarDivisionTest)
{
	using namespace CDPL;
	using namespace Math;

	double lhs1 = 15.23;
	long rhs1 = -22;
	double result1 = lhs1 / rhs1;

	BOOST_CHECK_EQUAL((ScalarDivision<double, long>::apply(lhs1, rhs1)), result1);

	// ----------

	std::complex<float> lhs2(13.1, -24.27);
	std::complex<float> rhs2(10.0, 4.127);
	std::complex<float> result2 = lhs2 / rhs2;

	BOOST_CHECK_EQUAL((ScalarDivision<std::complex<float>, std::complex<float> >::apply(lhs2, rhs2)), result2);
}

BOOST_AUTO_TEST_CASE(VectorInnerProductTest)
{
	using namespace CDPL;
	using namespace Math;

	CVector<double, 4> v1 = vec(1.0, -2.0, 3.12, 4.14);
	CVector<int, 4> v2 = vec(int(15), int(17), int(-12), int(21));

	checkVectorInnerProduct(v1, v2);

	// ----------

	CVector<std::complex<double>, 4> v3 = vec(std::complex<double>(15.0, 12.3), 17.0, std::complex<double>(-12.2, 1.12), 
											  std::complex<double>(12.2, 11.12));

	checkVectorInnerProduct(v1, v3);

	// ----------

	checkVectorInnerProduct(CVector<double, 0>(), CVector<int, 0>());

	// ----------

	checkVectorInnerProduct(CVector<std::complex<double>, 0>(), CVector<std::complex<double>, 0>());
	
	// ----------

	BOOST_CHECK_THROW(checkVectorInnerProduct(CVector<double, 0>(), CVector<int, 4>()), Base::SizeError);
	BOOST_CHECK_THROW(checkVectorInnerProduct(CVector<double, 4>(), CVector<int, 0>()), Base::SizeError);
	BOOST_CHECK_THROW(checkVectorInnerProduct(CVector<double, 3>(), CVector<int, 2>()), Base::SizeError);
	BOOST_CHECK_THROW(checkVectorInnerProduct(CVector<double, 2>(), CVector<int, 3>()), Base::SizeError);
}

BOOST_AUTO_TEST_CASE(VectorEqualityTest)
{
	using namespace CDPL;
	using namespace Math;

	BOOST_CHECK((VectorEquality<Vector<int>, CVector<float, 0> >::apply(Vector<int>(), CVector<float, 0>())));
	BOOST_CHECK((VectorEquality<Vector<int>, CVector<float, 3> >::apply(Vector<int>(3, 1), CVector<float, 3>(1.0f))));

	// ----------

	CVector<int, 4> v1 = vec(int(1), int(2), int(-3), int(4));
	Vector<double> v2;

	BOOST_CHECK(!(VectorEquality<CVector<int, 4>, Vector<double> >::apply(v1, v2)));
	BOOST_CHECK(!(VectorEquality<Vector<double>, CVector<int, 4> >::apply(v2, v1)));

	v2.resize(2);

	BOOST_CHECK(!(VectorEquality<CVector<int, 4>, Vector<double> >::apply(v1, v2)));
	BOOST_CHECK(!(VectorEquality<Vector<double>, CVector<int, 4> >::apply(v2, v1)));

	v2.resize(4);

	BOOST_CHECK(!(VectorEquality<CVector<int, 4>, Vector<double> >::apply(v1, v2)));
	BOOST_CHECK(!(VectorEquality<Vector<double>, CVector<int, 4> >::apply(v2, v1)));

	v2(0) = 1;

	BOOST_CHECK(!(VectorEquality<CVector<int, 4>, Vector<double> >::apply(v1, v2)));
	BOOST_CHECK(!(VectorEquality<Vector<double>, CVector<int, 4> >::apply(v2, v1)));

	v2(1) = 2;

	BOOST_CHECK(!(VectorEquality<CVector<int, 4>, Vector<double> >::apply(v1, v2)));
	BOOST_CHECK(!(VectorEquality<Vector<double>, CVector<int, 4> >::apply(v2, v1)));

	v2(2) = -3;

	BOOST_CHECK(!(VectorEquality<CVector<int, 4>, Vector<double> >::apply(v1, v2)));
	BOOST_CHECK(!(VectorEquality<Vector<double>, CVector<int, 4> >::apply(v2, v1)));

	v2(3) = 4;

	BOOST_CHECK((VectorEquality<CVector<int, 4>, Vector<double> >::apply(v1, v2)));
	BOOST_CHECK((VectorEquality<Vector<double>, CVector<int, 4> >::apply(v2, v1)));

	// ----------

	v2.resize(5);

	BOOST_CHECK(!(VectorEquality<CVector<int, 4>, Vector<double> >::apply(v1, v2)));
	BOOST_CHECK(!(VectorEquality<Vector<double>, CVector<int, 4> >::apply(v2, v1)));

	// ----------

	v2.resize(4);

	BOOST_CHECK((VectorEquality<CVector<int, 4>, Vector<double> >::apply(v1, v2)));
	BOOST_CHECK((VectorEquality<Vector<double>, CVector<int, 4> >::apply(v2, v1)));
}

BOOST_AUTO_TEST_CASE(VectorToleranceEqualityTest)
{
	using namespace CDPL;
	using namespace Math;
	
	BOOST_CHECK((VectorToleranceEquality<Vector<int>, CVector<float, 0>, int>::apply(Vector<int>(), CVector<float, 0>(), 0)));
	BOOST_CHECK((VectorToleranceEquality<Vector<int>, CVector<float, 3>, double>::apply(Vector<int>(3, 1), CVector<float, 3>(1.0f), 0.0)));

	// ----------

	CVector<int, 4> v1 = vec(int(1), int(2), int(-3), int(4));
	Vector<double> v2;

	BOOST_CHECK(!(VectorToleranceEquality<CVector<int, 4>, Vector<double>, float>::apply(v1, v2, 0.0f)));
	BOOST_CHECK(!(VectorToleranceEquality<Vector<double>, CVector<int, 4>, float>::apply(v2, v1, 10.0f)));

	v2.resize(2, 0.0);

	BOOST_CHECK(!(VectorToleranceEquality<CVector<int, 4>, Vector<double>, float>::apply(v1, v2, 10.0f)));
	BOOST_CHECK(!(VectorToleranceEquality<Vector<double>, CVector<int, 4>, float>::apply(v2, v1, 0.0f)));

	v2.resize(4, 0.0);

	BOOST_CHECK(!(VectorToleranceEquality<CVector<int, 4>, Vector<double>, float>::apply(v1, v2, 0.0f)));
	BOOST_CHECK(!(VectorToleranceEquality<Vector<double>, CVector<int, 4>, float>::apply(v2, v1, 0.0f)));

	BOOST_CHECK(!(VectorToleranceEquality<CVector<int, 4>, Vector<double>, float>::apply(v1, v2, 3.9999f)));
	BOOST_CHECK(!(VectorToleranceEquality<Vector<double>, CVector<int, 4>, double>::apply(v2, v1, 3.9999)));

	BOOST_CHECK((VectorToleranceEquality<CVector<int, 4>, Vector<double>, float>::apply(v1, v2, 4.0f)));
	BOOST_CHECK((VectorToleranceEquality<Vector<double>, CVector<int, 4>, int>::apply(v2, v1, 4)));
	BOOST_CHECK(!(VectorToleranceEquality<Vector<double>, CVector<int, 4>, int>::apply(v2, v1, -4)));

	v2(3) = 4;

	BOOST_CHECK(!(VectorToleranceEquality<CVector<int, 4>, Vector<double>, float>::apply(v1, v2, 0.0f)));
	BOOST_CHECK(!(VectorToleranceEquality<Vector<double>, CVector<int, 4>, float>::apply(v2, v1, 0.0f)));

	BOOST_CHECK(!(VectorToleranceEquality<CVector<int, 4>, Vector<double>, double>::apply(v1, v2, 2.9999)));
	BOOST_CHECK(!(VectorToleranceEquality<Vector<double>, CVector<int, 4>, long double>::apply(v2, v1, 2.9999L)));

	BOOST_CHECK((VectorToleranceEquality<CVector<int, 4>, Vector<double>, double>::apply(v1, v2, 3.0)));
	BOOST_CHECK((VectorToleranceEquality<Vector<double>, CVector<int, 4>, short int>::apply(v2, v1, 3)));
	BOOST_CHECK(!(VectorToleranceEquality<Vector<double>, CVector<int, 4>, short int>::apply(v2, v1, -3)));

	v2(2) = -3;

	BOOST_CHECK(!(VectorToleranceEquality<CVector<int, 4>, Vector<double>, float>::apply(v1, v2, 0.0f)));
	BOOST_CHECK(!(VectorToleranceEquality<Vector<double>, CVector<int, 4>, float>::apply(v2, v1, 0.0f)));

	BOOST_CHECK(!(VectorToleranceEquality<CVector<int, 4>, Vector<double>, float>::apply(v1, v2, 1.9999f)));
	BOOST_CHECK(!(VectorToleranceEquality<Vector<double>, CVector<int, 4>, double>::apply(v2, v1, 1.9999)));

	BOOST_CHECK((VectorToleranceEquality<CVector<int, 4>, Vector<double>, int>::apply(v1, v2, 2)));
	BOOST_CHECK((VectorToleranceEquality<Vector<double>, CVector<int, 4>, float>::apply(v2, v1, 2.0f)));
	BOOST_CHECK(!(VectorToleranceEquality<Vector<double>, CVector<int, 4>, float>::apply(v2, v1, -2.0f)));

	v2(1) = 2;

	BOOST_CHECK(!(VectorToleranceEquality<CVector<int, 4>, Vector<double>, float>::apply(v1, v2, 0.0f)));
	BOOST_CHECK(!(VectorToleranceEquality<Vector<double>, CVector<int, 4>, float>::apply(v2, v1, 0.0f)));

	BOOST_CHECK(!(VectorToleranceEquality<CVector<int, 4>, Vector<double>, double>::apply(v1, v2, 0.9999)));
	BOOST_CHECK(!(VectorToleranceEquality<Vector<double>, CVector<int, 4>, long double>::apply(v2, v1, 0.9999L)));

	BOOST_CHECK((VectorToleranceEquality<CVector<int, 4>, Vector<double>, unsigned char>::apply(v1, v2, 1)));
	BOOST_CHECK((VectorToleranceEquality<Vector<double>, CVector<int, 4>, double>::apply(v2, v1, 1.0)));
	BOOST_CHECK(!(VectorToleranceEquality<Vector<double>, CVector<int, 4>, double>::apply(v2, v1, -1.0)));

	v2(0) = 1;

	BOOST_CHECK((VectorToleranceEquality<CVector<int, 4>, Vector<double>, float>::apply(v1, v2, 0.0f)));
	BOOST_CHECK((VectorToleranceEquality<Vector<double>, CVector<int, 4>, long int>::apply(v2, v1, 0)));
	BOOST_CHECK(!(VectorToleranceEquality<Vector<double>, CVector<int, 4>, long int>::apply(v2, v1, -1)));

	v2(0) = -1;

	BOOST_CHECK(!(VectorToleranceEquality<CVector<int, 4>, Vector<double>, float>::apply(v1, v2, 0.0f)));
	BOOST_CHECK(!(VectorToleranceEquality<Vector<double>, CVector<int, 4>, long int>::apply(v2, v1, 0)));
	BOOST_CHECK(!(VectorToleranceEquality<Vector<double>, CVector<int, 4>, long int>::apply(v2, v1, -1)));
	BOOST_CHECK(!(VectorToleranceEquality<Vector<double>, CVector<int, 4>, float>::apply(v2, v1, 1.999f)));
	BOOST_CHECK((VectorToleranceEquality<Vector<double>, CVector<int, 4>, float>::apply(v2, v1, 2.0f)));
	BOOST_CHECK((VectorToleranceEquality<Vector<double>, CVector<int, 4>, int>::apply(v2, v1, 2)));

	v2(0) = 1;

	BOOST_CHECK((VectorToleranceEquality<CVector<int, 4>, Vector<double>, float>::apply(v1, v2, 0.0f)));
	BOOST_CHECK((VectorToleranceEquality<Vector<double>, CVector<int, 4>, long int>::apply(v2, v1, 0)));
	BOOST_CHECK(!(VectorToleranceEquality<Vector<double>, CVector<int, 4>, long int>::apply(v2, v1, -1)));

	// ----------

	v2.resize(10);

	BOOST_CHECK(!(VectorToleranceEquality<CVector<int, 4>, Vector<double>, unsigned int>::apply(v1, v2, 10)));
	BOOST_CHECK(!(VectorToleranceEquality<Vector<double>, CVector<int, 4>, double>::apply(v2, v1, 4.0)));

	// ----------

	v2.resize(4);

	BOOST_CHECK((VectorToleranceEquality<CVector<int, 4>, Vector<double>, float>::apply(v1, v2, 0.0f)));
	BOOST_CHECK((VectorToleranceEquality<Vector<double>, CVector<int, 4>, long int>::apply(v2, v1, 0)));
}

BOOST_AUTO_TEST_CASE(VectorCrossProductTest)
{
	using namespace CDPL;
	using namespace Math;

	checkVectorCrossProduct(vec(0.0, 1.0, 0.0), vec(1.0, 0.0, 0.0), vec(0.0, 0.0, -1.0));
	checkVectorCrossProduct(vec(1.0, 0.0, 0.0), vec(0.0, 1.0, 0.0), vec(0.0, 0.0, 1.0));
	checkVectorCrossProduct(vec(0.0, -1.0, 0.0), vec(-1.0, 0.0, 0.0), vec(0.0, 0.0, -1.0));
	checkVectorCrossProduct(vec(-1.0, 0.0, 0.0), vec(0.0, -1.0, 0.0), vec(0.0, 0.0, 1.0));
	checkVectorCrossProduct(vec(0.0, -1.0, 0.0), vec(1.0, 0.0, 0.0), vec(0.0, 0.0, 1.0));
	checkVectorCrossProduct(vec(1.0, 0.0, 0.0), vec(0.0, -1.0, 0.0), vec(0.0, 0.0, -1.0));
	checkVectorCrossProduct(vec(0.0, 1.0, 0.0), vec(-1.0, 0.0, 0.0), vec(0.0, 0.0, 1.0));
	checkVectorCrossProduct(vec(-1.0, 0.0, 0.0), vec(0.0, 1.0, 0.0), vec(0.0, 0.0, -1.0));

	// ----------

	checkVectorCrossProduct(vec(0.0, 1.0, 0.0), vec(0.0, 0.0, 1.0), vec(1.0, 0.0, 0.0));
	checkVectorCrossProduct(vec(0.0, 0.0, 1.0), vec(0.0, 1.0, 0.0), vec(-1.0, 0.0, 0.0));
	checkVectorCrossProduct(vec(0.0, -1.0, 0.0), vec(0.0, 0.0, -1.0), vec(1.0, 0.0, 0.0));
	checkVectorCrossProduct(vec(0.0, 0.0, -1.0), vec(0.0, -1.0, 0.0), vec(-1.0, 0.0, 0.0));
	checkVectorCrossProduct(vec(0.0, -1.0, 0.0), vec(0.0, 0.0, 1.0), vec(-1.0, 0.0, 0.0));
	checkVectorCrossProduct(vec(0.0, 0.0, 1.0), vec(0.0, -1.0, 0.0), vec(1.0, 0.0, 0.0));
	checkVectorCrossProduct(vec(0.0, 1.0, 0.0), vec(0.0, 0.0, -1.0), vec(-1.0, 0.0, 0.0));
	checkVectorCrossProduct(vec(0.0, 0.0, -1.0), vec(0.0, 1.0, 0.0), vec(1.0, 0.0, 0.0));

	// ----------

	checkVectorCrossProduct(vec(1.0, 0.0, 0.0), vec(0.0, 0.0, 1.0), vec(0.0, -1.0, 0.0));
	checkVectorCrossProduct(vec(0.0, 0.0, 1.0), vec(1.0, 0.0, 0.0), vec(0.0, 1.0, 0.0));
	checkVectorCrossProduct(vec(-1.0, 0.0, 0.0), vec(0.0, 0.0, -1.0), vec(0.0, -1.0, 0.0));
	checkVectorCrossProduct(vec(0.0, 0.0, -1.0), vec(-1.0, 0.0, 0.0), vec(0.0, 1.0, 0.0));
	checkVectorCrossProduct(vec(-1.0, 0.0, 0.0), vec(0.0, 0.0, 1.0), vec(0.0, 1.0, 0.0));
	checkVectorCrossProduct(vec(0.0, 0.0, 1.0), vec(-1.0, 0.0, 0.0), vec(0.0, -1.0, 0.0));
	checkVectorCrossProduct(vec(1.0, 0.0, 0.0), vec(0.0, 0.0, -1.0), vec(0.0, 1.0, 0.0));
	checkVectorCrossProduct(vec(0.0, 0.0, -1.0), vec(1.0, 0.0, 0.0), vec(0.0, -1.0, 0.0));

	// ----------

	checkVectorCrossProduct(vec(1.0, 1.0, 1.0), vec(-1.0, 1.0, 1.0), vec(0.0, -2.0, 2.0));

	// ----------

	BOOST_CHECK_THROW(checkVectorCrossProduct(Vector<double>(), Vector<double>(), vec(0.0, 0.0, 0.0)), Base::SizeError);
	BOOST_CHECK_THROW(checkVectorCrossProduct(Vector<double>(1), Vector<double>(), vec(0.0, 0.0, 0.0)), Base::SizeError);
	BOOST_CHECK_THROW(checkVectorCrossProduct(Vector<double>(3), Vector<double>(), vec(0.0, 0.0, 0.0)), Base::SizeError);
	BOOST_CHECK_THROW(checkVectorCrossProduct(Vector<double>(4), Vector<double>(), vec(0.0, 0.0, 0.0)), Base::SizeError);

	BOOST_CHECK_THROW(checkVectorCrossProduct(Vector<double>(), Vector<double>(), vec(0.0, 0.0, 0.0)), Base::SizeError);
	BOOST_CHECK_THROW(checkVectorCrossProduct(Vector<double>(), Vector<double>(1), vec(0.0, 0.0, 0.0)), Base::SizeError);
	BOOST_CHECK_THROW(checkVectorCrossProduct(Vector<double>(), Vector<double>(3), vec(0.0, 0.0, 0.0)), Base::SizeError);
	BOOST_CHECK_THROW(checkVectorCrossProduct(Vector<double>(), Vector<double>(4), vec(0.0, 0.0, 0.0)), Base::SizeError);

	BOOST_CHECK_THROW(checkVectorCrossProduct(Vector<double>(2), Vector<double>(4), vec(0.0, 0.0, 0.0)), Base::SizeError);
	BOOST_CHECK_THROW(checkVectorCrossProduct(Vector<double>(4), Vector<double>(2), vec(0.0, 0.0, 0.0)), Base::SizeError);

	BOOST_CHECK_THROW(checkVectorCrossProduct(Vector<double>(1), Vector<double>(2), vec(0.0, 0.0, 0.0)), Base::SizeError);

	BOOST_CHECK_THROW(checkVectorCrossProduct(Vector<double>(4), Vector<double>(5), vec(0.0, 0.0, 0.0)), Base::SizeError);

	BOOST_CHECK_THROW(checkVectorCrossProduct(Vector<double>(2), Vector<double>(3), vec(0.0, 0.0, 0.0)), Base::SizeError);
	BOOST_CHECK_THROW(checkVectorCrossProduct(Vector<double>(3), Vector<double>(2), vec(0.0, 0.0, 0.0)), Base::SizeError);

	BOOST_CHECK_THROW(checkVectorCrossProduct(Vector<double>(4), Vector<double>(3), vec(0.0, 0.0, 0.0)), Base::SizeError);
	BOOST_CHECK_THROW(checkVectorCrossProduct(Vector<double>(3), Vector<double>(4), vec(0.0, 0.0, 0.0)), Base::SizeError);
}

BOOST_AUTO_TEST_CASE(VectorElementSumTest)
{
	using namespace CDPL;
	using namespace Math;

	BOOST_CHECK_EQUAL((VectorElementSum<Vector<float> >::apply(Vector<float>())), 0.0f);

	BOOST_CHECK_EQUAL((VectorElementSum<CVector<double, 2> >::apply(vec(0.0, 0.0))), 0.0 + 0.0);

	BOOST_CHECK_EQUAL((VectorElementSum<CVector<double, 2> >::apply(vec(-1.1, 1.1))), -1.1 + 1.1);

	BOOST_CHECK_EQUAL((VectorElementSum<CVector<double, 3> >::apply(vec(-1.3, 1.3, 0.0))), -1.3 + 1.3 + 0.0);

	BOOST_CHECK_EQUAL((VectorElementSum<CVector<double, 3> >::apply(vec(-1.17, 2.333, 3.21))), -1.17 + 2.333 + 3.21);

	// ----------

	BOOST_CHECK_EQUAL((VectorElementSum<CVector<std::complex<double>, 4> >::apply(vec(std::complex<double>(-17.2, 4.5), std::complex<double>(15.16, -14.5), 
																					  std::complex<double>(11.17, 22.15), std::complex<double>(-3.1, -1.25)))),
		std::complex<double>(-17.2, 4.5) + std::complex<double>(15.16, -14.5) + std::complex<double>(11.17, 22.15) + std::complex<double>(-3.1, -1.25));
}

BOOST_AUTO_TEST_CASE(VectorNorm1Test)
{
	using namespace CDPL;
	using namespace Math;

	checkVectorNorm1(Vector<float>());

	checkVectorNorm1(vec(0.0, 0.0));
	checkVectorNorm1(vec(-1.0, 1.0));
	checkVectorNorm1(vec(-1.0, 1.0, 0.0));
	checkVectorNorm1(vec(-1.0, 2.0, -3.0));
	checkVectorNorm1(vec(-1.0, -2.0, 3.0));

	// ----------

	checkVectorNorm1(vec(std::complex<double>(-17.2, 4.5), std::complex<double>(15.16, -14.5), 
						 std::complex<double>(11.17, 22.15), std::complex<double>(-3.1, -1.25)));
}

BOOST_AUTO_TEST_CASE(VectorNorm2Test)
{
	using namespace CDPL;
	using namespace Math;

	checkVectorNorm2(Vector<float>());

	checkVectorNorm2(vec(0.0, 0.0));
	checkVectorNorm2(vec(-1.0, 1.0));
	checkVectorNorm2(vec(-1.0, 1.0, 0.0));
	checkVectorNorm2(vec(-1.0, 2.0, -3.0));
	checkVectorNorm2(vec(-1.0, -2.0, 3.0));

	// ----------

	checkVectorNorm2(vec(std::complex<double>(-17.2, 4.5), std::complex<double>(15.16, -14.5), 
						 std::complex<double>(11.17, 22.15), std::complex<double>(-3.1, -1.25)));
}

BOOST_AUTO_TEST_CASE(VectorNormInfinityTest)
{
	using namespace CDPL;
	using namespace Math;

	BOOST_CHECK_EQUAL((VectorNormInfinity<Vector<float> >::apply(Vector<float>())), 0.0f);

	BOOST_CHECK_EQUAL((VectorNormInfinity<CVector<double, 2> >::apply(vec(0.0, 0.0))), TypeTraits<double>::normInf(0.0));

	BOOST_CHECK_EQUAL((VectorNormInfinity<CVector<double, 2> >::apply(vec(-1.0, 1.0))), TypeTraits<double>::normInf(-1.0));

	BOOST_CHECK_EQUAL((VectorNormInfinity<CVector<double, 3> >::apply(vec(-1.0, 1.0, 0.0))), TypeTraits<double>::normInf(-1.0));

	BOOST_CHECK_EQUAL((VectorNormInfinity<CVector<double, 3> >::apply(vec(-1.0, 2.0, -3.0))), TypeTraits<double>::normInf(-3.0));

	BOOST_CHECK_EQUAL((VectorNormInfinity<CVector<double, 3> >::apply(vec(-1.0, -2.0, 3.0))), TypeTraits<double>::normInf(3.0));

	// ----------

	BOOST_CHECK_EQUAL((VectorNormInfinity<CVector<std::complex<double>, 4> >::apply(vec(std::complex<double>(-17.2, 4.5), std::complex<double>(15.16, -14.5), 
																						std::complex<double>(11.17, 22.15), std::complex<double>(-3.1, -1.25)))),
					  TypeTraits<std::complex<double> >::normInf(std::complex<double>(11.17, 22.15)));
}

BOOST_AUTO_TEST_CASE(VectorNormInfinityIndexTest)
{
	using namespace CDPL;
	using namespace Math;

	BOOST_CHECK_EQUAL((VectorNormInfinityIndex<Vector<float> >::apply(Vector<float>())), 0);

	BOOST_CHECK_EQUAL((VectorNormInfinityIndex<CVector<double, 2> >::apply(vec(0.0, 0.0))), 0);

	BOOST_CHECK_EQUAL((VectorNormInfinityIndex<CVector<double, 2> >::apply(vec(-1.0, 1.0))), 0);

	BOOST_CHECK_EQUAL((VectorNormInfinityIndex<CVector<double, 3> >::apply(vec(-1.0, 1.0, 0.0))), 0);

	BOOST_CHECK_EQUAL((VectorNormInfinityIndex<CVector<double, 3> >::apply(vec(-1.0, 2.0, -3.0))), 2);

	BOOST_CHECK_EQUAL((VectorNormInfinityIndex<CVector<double, 3> >::apply(vec(-1.0, -2.0, 3.0))), 2);

	BOOST_CHECK_EQUAL((VectorNormInfinityIndex<CVector<double, 3> >::apply(vec(-1.0, -3.0, 2.0))), 1);

	// ----------

	BOOST_CHECK_EQUAL((VectorNormInfinityIndex<CVector<std::complex<double>, 4> >::apply(vec(std::complex<double>(-17.2, 4.5), std::complex<double>(15.16, -14.5), 
																				 std::complex<double>(11.17, 22.15), std::complex<double>(-3.1, -1.25)))), 2);
}

BOOST_AUTO_TEST_CASE(MatrixEqualityTest)
{
	using namespace CDPL;
	using namespace Math;

	BOOST_CHECK((MatrixEquality<Matrix<int>, CMatrix<float, 0, 0> >::apply(Matrix<int>(0, 0), CMatrix<float, 0, 0>())));
	BOOST_CHECK((MatrixEquality<Matrix<int>, CMatrix<float, 3, 3> >::apply(Matrix<int>(3, 3, 1), CMatrix<float, 3, 3>(1.0f))));

	// ----------

	CMatrix<int, 4, 4> m1(0);
	
	m1(0, 0) = 1;
	m1(0, 3) = 2;
	m1(3, 0) = -3;
	m1(3, 3) = 4;

	Matrix<double> m2;

	BOOST_CHECK(!(MatrixEquality<CMatrix<int, 4, 4>, Matrix<double> >::apply(m1, m2)));
	BOOST_CHECK(!(MatrixEquality<Matrix<double>, CMatrix<int, 4, 4> >::apply(m2, m1)));

	m2.resize(2, 2);

	BOOST_CHECK(!(MatrixEquality<CMatrix<int, 4, 4>, Matrix<double> >::apply(m1, m2)));
	BOOST_CHECK(!(MatrixEquality<Matrix<double>, CMatrix<int, 4, 4> >::apply(m2, m1)));

	m2.resize(4, 4);

	BOOST_CHECK(!(MatrixEquality<CMatrix<int, 4, 4>, Matrix<double> >::apply(m1, m2)));
	BOOST_CHECK(!(MatrixEquality<Matrix<double>, CMatrix<int, 4, 4> >::apply(m2, m1)));

	m2(0, 0) = 1;

	BOOST_CHECK(!(MatrixEquality<CMatrix<int, 4, 4>, Matrix<double> >::apply(m1, m2)));
	BOOST_CHECK(!(MatrixEquality<Matrix<double>, CMatrix<int, 4, 4> >::apply(m2, m1)));

	m2(0, 3) = 2;

	BOOST_CHECK(!(MatrixEquality<CMatrix<int, 4, 4>, Matrix<double> >::apply(m1, m2)));
	BOOST_CHECK(!(MatrixEquality<Matrix<double>, CMatrix<int, 4, 4> >::apply(m2, m1)));

	m2(3, 0) = -3;

	BOOST_CHECK(!(MatrixEquality<CMatrix<int, 4, 4>, Matrix<double> >::apply(m1, m2)));
	BOOST_CHECK(!(MatrixEquality<Matrix<double>, CMatrix<int, 4, 4> >::apply(m2, m1)));

	m2(3, 3) = 4;

	BOOST_CHECK((MatrixEquality<CMatrix<int, 4, 4>, Matrix<double> >::apply(m1, m2)));
	BOOST_CHECK((MatrixEquality<Matrix<double>, CMatrix<int, 4, 4> >::apply(m2, m1)));

	// ----------

	m2(2, 2) = 5;

	BOOST_CHECK(!(MatrixEquality<CMatrix<int, 4, 4>, Matrix<double> >::apply(m1, m2)));
	BOOST_CHECK(!(MatrixEquality<Matrix<double>, CMatrix<int, 4, 4> >::apply(m2, m1)));

	// ----------

	m2(2, 2) = 0;

	BOOST_CHECK((MatrixEquality<CMatrix<int, 4, 4>, Matrix<double> >::apply(m1, m2)));
	BOOST_CHECK((MatrixEquality<Matrix<double>, CMatrix<int, 4, 4> >::apply(m2, m1)));

	// ----------

	m2.resize(5, 4);

	BOOST_CHECK(!(MatrixEquality<CMatrix<int, 4, 4>, Matrix<double> >::apply(m1, m2)));
	BOOST_CHECK(!(MatrixEquality<Matrix<double>, CMatrix<int, 4, 4> >::apply(m2, m1)));

	// ----------

	m2.resize(4, 4);

	BOOST_CHECK((MatrixEquality<CMatrix<int, 4, 4>, Matrix<double> >::apply(m1, m2)));
	BOOST_CHECK((MatrixEquality<Matrix<double>, CMatrix<int, 4, 4> >::apply(m2, m1)));
}

BOOST_AUTO_TEST_CASE(MatrixToleranceEqualityTest)
{
	using namespace CDPL;
	using namespace Math;
	
	BOOST_CHECK((MatrixToleranceEquality<Matrix<int>, CMatrix<float, 0, 0>, int>::apply(Matrix<int>(), CMatrix<float, 0, 0>(), 0)));
	BOOST_CHECK((MatrixToleranceEquality<Matrix<int>, CMatrix<float, 3, 3>, double>::apply(Matrix<int>(3, 3, 1), CMatrix<float, 3, 3>(1.0f), 0.0)));

	// ----------

	CMatrix<int, 4, 4> m1(0);

	m1(0, 0) = 1;
	m1(0, 3) = 2;
	m1(3, 0) = -3;
	m1(3, 3) = 4;

	Matrix<double> m2;

	BOOST_CHECK(!(MatrixToleranceEquality<CMatrix<int, 4, 4>, Matrix<double>, float>::apply(m1, m2, 0.0f)));
	BOOST_CHECK(!(MatrixToleranceEquality<Matrix<double>, CMatrix<int, 4, 4>, float>::apply(m2, m1, 10.0f)));

	m2.resize(2, 3);

	BOOST_CHECK(!(MatrixToleranceEquality<CMatrix<int, 4, 4>, Matrix<double>, float>::apply(m1, m2, 10.0f)));
	BOOST_CHECK(!(MatrixToleranceEquality<Matrix<double>, CMatrix<int, 4, 4>, float>::apply(m2, m1, 0.0f)));

	m2.resize(4, 4);

	BOOST_CHECK(!(MatrixToleranceEquality<CMatrix<int, 4, 4>, Matrix<double>, float>::apply(m1, m2, 0.0f)));
	BOOST_CHECK(!(MatrixToleranceEquality<Matrix<double>, CMatrix<int, 4, 4>, float>::apply(m2, m1, 0.0f)));

	BOOST_CHECK(!(MatrixToleranceEquality<CMatrix<int, 4, 4>, Matrix<double>, float>::apply(m1, m2, 3.9999f)));
	BOOST_CHECK(!(MatrixToleranceEquality<Matrix<double>, CMatrix<int, 4, 4>, double>::apply(m2, m1, 3.9999)));

	BOOST_CHECK((MatrixToleranceEquality<CMatrix<int, 4, 4>, Matrix<double>, float>::apply(m1, m2, 4.0f)));
	BOOST_CHECK((MatrixToleranceEquality<Matrix<double>, CMatrix<int, 4, 4>, int>::apply(m2, m1, 4)));
	BOOST_CHECK(!(MatrixToleranceEquality<Matrix<double>, CMatrix<int, 4, 4>, int>::apply(m2, m1, -4)));

	m2(3, 3) = 4;

	BOOST_CHECK(!(MatrixToleranceEquality<CMatrix<int, 4, 4>, Matrix<double>, float>::apply(m1, m2, 0.0f)));
	BOOST_CHECK(!(MatrixToleranceEquality<Matrix<double>, CMatrix<int, 4, 4>, float>::apply(m2, m1, 0.0f)));

	BOOST_CHECK(!(MatrixToleranceEquality<CMatrix<int, 4, 4>, Matrix<double>, double>::apply(m1, m2, 2.9999)));
	BOOST_CHECK(!(MatrixToleranceEquality<Matrix<double>, CMatrix<int, 4, 4>, long double>::apply(m2, m1, 2.9999L)));

	BOOST_CHECK((MatrixToleranceEquality<CMatrix<int, 4, 4>, Matrix<double>, double>::apply(m1, m2, 3.0)));
	BOOST_CHECK((MatrixToleranceEquality<Matrix<double>, CMatrix<int, 4, 4>, short int>::apply(m2, m1, 3)));
	BOOST_CHECK(!(MatrixToleranceEquality<Matrix<double>, CMatrix<int, 4, 4>, short int>::apply(m2, m1, -3)));

	m2(3, 0) = -3;

	BOOST_CHECK(!(MatrixToleranceEquality<CMatrix<int, 4, 4>, Matrix<double>, float>::apply(m1, m2, 0.0f)));
	BOOST_CHECK(!(MatrixToleranceEquality<Matrix<double>, CMatrix<int, 4, 4>, float>::apply(m2, m1, 0.0f)));

	BOOST_CHECK(!(MatrixToleranceEquality<CMatrix<int, 4, 4>, Matrix<double>, float>::apply(m1, m2, 1.9999f)));
	BOOST_CHECK(!(MatrixToleranceEquality<Matrix<double>, CMatrix<int, 4, 4>, double>::apply(m2, m1, 1.9999)));

	BOOST_CHECK((MatrixToleranceEquality<CMatrix<int, 4, 4>, Matrix<double>, int>::apply(m1, m2, 2)));
	BOOST_CHECK((MatrixToleranceEquality<Matrix<double>, CMatrix<int, 4, 4>, float>::apply(m2, m1, 2.0f)));
	BOOST_CHECK(!(MatrixToleranceEquality<Matrix<double>, CMatrix<int, 4, 4>, float>::apply(m2, m1, -2.0f)));

	m2(0, 3) = 2;

	BOOST_CHECK(!(MatrixToleranceEquality<CMatrix<int, 4, 4>, Matrix<double>, float>::apply(m1, m2, 0.0f)));
	BOOST_CHECK(!(MatrixToleranceEquality<Matrix<double>, CMatrix<int, 4, 4>, float>::apply(m2, m1, 0.0f)));

	BOOST_CHECK(!(MatrixToleranceEquality<CMatrix<int, 4, 4>, Matrix<double>, double>::apply(m1, m2, 0.9999)));
	BOOST_CHECK(!(MatrixToleranceEquality<Matrix<double>, CMatrix<int, 4, 4>, long double>::apply(m2, m1, 0.9999L)));

	BOOST_CHECK((MatrixToleranceEquality<CMatrix<int, 4, 4>, Matrix<double>, unsigned char>::apply(m1, m2, 1)));
	BOOST_CHECK((MatrixToleranceEquality<Matrix<double>, CMatrix<int, 4, 4>, double>::apply(m2, m1, 1.0)));
	BOOST_CHECK(!(MatrixToleranceEquality<Matrix<double>, CMatrix<int, 4, 4>, double>::apply(m2, m1, -1.0)));

	m2(0, 0) = 1;

	BOOST_CHECK((MatrixToleranceEquality<CMatrix<int, 4, 4>, Matrix<double>, float>::apply(m1, m2, 0.0f)));
	BOOST_CHECK((MatrixToleranceEquality<Matrix<double>, CMatrix<int, 4, 4>, long int>::apply(m2, m1, 0)));
	BOOST_CHECK(!(MatrixToleranceEquality<Matrix<double>, CMatrix<int, 4, 4>, double>::apply(m2, m1, -0.000001)));

	m2(0, 0) = -1;

	BOOST_CHECK(!(MatrixToleranceEquality<CMatrix<int, 4, 4>, Matrix<double>, float>::apply(m1, m2, 0.0f)));
	BOOST_CHECK(!(MatrixToleranceEquality<Matrix<double>, CMatrix<int, 4, 4>, long int>::apply(m2, m1, 1)));

	BOOST_CHECK(!(MatrixToleranceEquality<CMatrix<int, 4, 4>, Matrix<double>, float>::apply(m1, m2, 1)));
	BOOST_CHECK(!(MatrixToleranceEquality<Matrix<double>, CMatrix<int, 4, 4>, float>::apply(m2, m1, 1.9999f)));

	BOOST_CHECK((MatrixToleranceEquality<CMatrix<int, 4, 4>, Matrix<double>, float>::apply(m1, m2, 2.0f)));
	BOOST_CHECK((MatrixToleranceEquality<Matrix<double>, CMatrix<int, 4, 4>, long int>::apply(m2, m1, 2)));

	m2(0, 0) = 1;

	BOOST_CHECK((MatrixToleranceEquality<CMatrix<int, 4, 4>, Matrix<double>, float>::apply(m1, m2, 0.0f)));
	BOOST_CHECK((MatrixToleranceEquality<Matrix<double>, CMatrix<int, 4, 4>, long int>::apply(m2, m1, 0)));

	// ----------

	m2(2, 2) = 5;

	BOOST_CHECK(!(MatrixToleranceEquality<CMatrix<int, 4, 4>, Matrix<double>, int>::apply(m1, m2, 4)));
	BOOST_CHECK(!(MatrixToleranceEquality<Matrix<double>, CMatrix<int, 4, 4>, double>::apply(m2, m1, 4.9999)));

	BOOST_CHECK((MatrixToleranceEquality<CMatrix<int, 4, 4>, Matrix<double>, int>::apply(m1, m2, 5)));
	BOOST_CHECK((MatrixToleranceEquality<Matrix<double>, CMatrix<int, 4, 4>, int>::apply(m2, m1, 5)));
	BOOST_CHECK(!(MatrixToleranceEquality<Matrix<double>, CMatrix<int, 4, 4>, int>::apply(m2, m1, -5)));

	// ----------

	m2(2, 2) = 0;

	BOOST_CHECK((MatrixToleranceEquality<CMatrix<int, 4, 4>, Matrix<double>, float>::apply(m1, m2, 0.0f)));
	BOOST_CHECK((MatrixToleranceEquality<Matrix<double>, CMatrix<int, 4, 4>, long int>::apply(m2, m1, 0)));
	BOOST_CHECK(!(MatrixToleranceEquality<Matrix<double>, CMatrix<int, 4, 4>, double>::apply(m2, m1, -0.0000003)));

	// ----------

	m2.resize(4, 5);

	BOOST_CHECK(!(MatrixToleranceEquality<CMatrix<int, 4, 4>, Matrix<double>, unsigned int>::apply(m1, m2, 10)));
	BOOST_CHECK(!(MatrixToleranceEquality<Matrix<double>, CMatrix<int, 4, 4>, double>::apply(m2, m1, 4.0)));
	BOOST_CHECK(!(MatrixToleranceEquality<Matrix<double>, CMatrix<int, 4, 4>, double>::apply(m2, m1, -4.0)));

	// ----------

	m2.resize(4, 4);

	BOOST_CHECK((MatrixToleranceEquality<CMatrix<int, 4, 4>, Matrix<double>, float>::apply(m1, m2, 0.0f)));
	BOOST_CHECK((MatrixToleranceEquality<Matrix<double>, CMatrix<int, 4, 4>, long int>::apply(m2, m1, 0)));
	BOOST_CHECK(!(MatrixToleranceEquality<Matrix<double>, CMatrix<int, 4, 4>, double>::apply(m2, m1, -0.000003)));
}

BOOST_AUTO_TEST_CASE(MatrixElementSumTest)
{
	using namespace CDPL;
	using namespace Math;

	Matrix<double> m1;

	checkMatrixElementSum(m1);

	m1.resize(2, 3);

	checkMatrixElementSum(m1);

	m1(0, 0) = -1.1;
	m1(1, 2) = 1.1;

	checkMatrixElementSum(m1);

	m1(0, 1) = 2.11;
	m1(1, 1) = -15.1;

	checkMatrixElementSum(m1);

	// ----------

	CMatrix<std::complex<double>, 2, 2> m2;

	m2(0, 0) = std::complex<double>(-17.2, 4.5);
	m2(0, 1) = std::complex<double>(15.16, -14.5);
	m2(1, 0) = std::complex<double>(11.17, 22.15);
	m2(1, 1) = std::complex<double>(-3.1, -1.25);

	checkMatrixElementSum(m2);
}

BOOST_AUTO_TEST_CASE(MatrixTraceTest)
{
	using namespace CDPL;
	using namespace Math;
	
	BOOST_CHECK_THROW((MatrixTrace<CMatrix<int, 0, 3> >::apply(CMatrix<int, 0, 3>(4))), Base::SizeError);
	BOOST_CHECK_THROW((MatrixTrace<CMatrix<int, 3, 0> >::apply(CMatrix<int, 3, 0>(4))), Base::SizeError);
	BOOST_CHECK_THROW((MatrixTrace<CMatrix<int, 2, 3> >::apply(CMatrix<int, 2, 3>(4))), Base::SizeError);
	BOOST_CHECK_THROW((MatrixTrace<CMatrix<int, 3, 2> >::apply(CMatrix<int, 3, 2>(4))), Base::SizeError);

	// ----------

	checkMatrixTrace(CMatrix<float, 0, 0>());
	checkMatrixTrace(CMatrix<int, 3, 3>(4));

	// ----------

	CMatrix<double, 4, 4> m1(0);
	typedef CMatrix<double, 4, 4>::SizeType SizeType;

	BOOST_CHECK_EQUAL((MatrixTrace<CMatrix<double, 4, 4> >::apply(m1)), 0.0);

    for (SizeType i = 0; i < 4; i++) {
		for (SizeType j = 0; j < 4; j++) {
			BOOST_CHECK_EQUAL((MatrixTrace<CMatrix<double, 4, 4> >::apply(m1)), 0.0);

			if (i != j)
				m1(i, j) = i * 4 + j;
		}
	}

  	checkMatrixTrace(m1);

	// ----------

    m1(0, 0) = -1.0;
    m1(1, 1) = 1.1;
    m1(2, 2) = 17.2;
    m1(3, 3) = -617.2;
				  
  	checkMatrixTrace(m1);

	// ----------

	CMatrix<std::complex<double>, 4, 4> m2(std::complex<double>(0, 0));

	m2(0, 0) = std::complex<double>(-17.2, 4.5);
    m2(1, 1) = std::complex<double>(15.16, -14.5);
    m2(2, 2) = std::complex<double>(11.17, 22.15);
    m2(3, 3) = std::complex<double>(-3.1, -1.25);
    m2(1, 3) = std::complex<double>(-33.1, -31.25);

  	checkMatrixTrace(m2);
}

BOOST_AUTO_TEST_CASE(MatrixNorm1Test)
{
	using namespace CDPL;
	using namespace Math;

	BOOST_CHECK_EQUAL((MatrixNorm1<Matrix<float> >::apply(Matrix<float>())), 0.0f);

	BOOST_CHECK_EQUAL((MatrixNorm1<CMatrix<double, 3, 0> >::apply(CMatrix<double, 3, 0>())), 0.0);
	BOOST_CHECK_EQUAL((MatrixNorm1<CMatrix<double, 0, 4> >::apply(CMatrix<double, 0, 4>())), 0.0);

	// ----------

	CMatrix<double, 3, 2> m1(0.0);

	checkMatrixNorm1(m1, 0);
	checkMatrixNorm1(m1, 1);

	// ----------

	m1(0, 0) = -17.2;
	m1(0, 1) = 15.16;
	m1(1, 0) = 11.17;
	m1(1, 1) = -13.1;
	m1(2, 0) = -23.1;
	m1(2, 1) = -33.1;

	checkMatrixNorm1(m1, 1);

	// ----------

    CMatrix<std::complex<double>, 2, 3> m2(std::complex<double>(0.0, 0.0));

	checkMatrixNorm1(m2, 0);
	checkMatrixNorm1(m2, 1);
	checkMatrixNorm1(m2, 2);

	// ----------

    m2(0, 0) = std::complex<double>(-17.2, 4.5);
    m2(0, 1) = std::complex<double>(15.16, -14.5);
    m2(0, 2) = std::complex<double>(11.17, 22.15);
    m2(1, 0) = std::complex<double>(-13.1, 31.15);
    m2(1, 1) = std::complex<double>(-23.1, 11.3425);
    m2(1, 2) = std::complex<double>(-33.1, 1.25);

	checkMatrixNorm1(m2, 2);
}

BOOST_AUTO_TEST_CASE(MatrixNormFrobeniusTest)
{
	using namespace CDPL;
	using namespace Math;

	BOOST_CHECK_EQUAL((MatrixNormFrobenius<Matrix<float> >::apply(Matrix<float>())), 0.0f);

	BOOST_CHECK_EQUAL((MatrixNormFrobenius<CMatrix<double, 3, 0> >::apply(CMatrix<double, 3, 0>())), 0.0);
	BOOST_CHECK_EQUAL((MatrixNormFrobenius<CMatrix<double, 0, 4> >::apply(CMatrix<double, 0, 4>())), 0.0);

	// ----------

	CMatrix<double, 3, 2> m1(0.0);

	checkMatrixNormFrobenius(m1);

	// ----------

	m1(0, 0) = -17.2;
	m1(0, 1) = 15.16;
	m1(1, 0) = 11.17;
	m1(1, 1) = -13.1;
	m1(2, 0) = -23.1;
	m1(2, 1) = -33.1;

	checkMatrixNormFrobenius(m1);

	// ----------

    CMatrix<std::complex<double>, 2, 3> m2(std::complex<double>(0.0, 0.0));

	checkMatrixNormFrobenius(m2);

	// ----------

    m2(0, 0) = std::complex<double>(-17.2, 4.5);
    m2(0, 1) = std::complex<double>(15.16, -14.5);
    m2(0, 2) = std::complex<double>(11.17, 22.15);
    m2(1, 0) = std::complex<double>(-13.1, 31.15);
    m2(1, 1) = std::complex<double>(-23.1, 11.3425);
    m2(1, 2) = std::complex<double>(-33.1, 1.25);

	checkMatrixNormFrobenius(m2);
}

BOOST_AUTO_TEST_CASE(MatrixNormInfinityTest)
{
	using namespace CDPL;
	using namespace Math;

	BOOST_CHECK_EQUAL((MatrixNormInfinity<Matrix<float> >::apply(Matrix<float>())), 0.0f);

	BOOST_CHECK_EQUAL((MatrixNormInfinity<CMatrix<double, 3, 0> >::apply(CMatrix<double, 3, 0>())), 0.0);
	BOOST_CHECK_EQUAL((MatrixNormInfinity<CMatrix<double, 0, 4> >::apply(CMatrix<double, 0, 4>())), 0.0);

	// ----------

	CMatrix<double, 3, 2> m1(0.0);

	checkMatrixNormInfinity(m1, 0);
	checkMatrixNormInfinity(m1, 1);
	checkMatrixNormInfinity(m1, 2);

	// ----------

	m1(0, 0) = -17.2;
	m1(0, 1) = 15.16;
	m1(1, 0) = 11.17;
	m1(1, 1) = -13.1;
	m1(2, 0) = -23.1;
	m1(2, 1) = -33.1;

	checkMatrixNormInfinity(m1, 2);

	// ----------

    CMatrix<std::complex<double>, 2, 3> m2(std::complex<double>(0.0, 0.0));

	checkMatrixNormInfinity(m2, 0);
	checkMatrixNormInfinity(m2, 1);

	// ----------

    m2(0, 0) = std::complex<double>(-17.2, 4.5);
    m2(0, 1) = std::complex<double>(15.16, -14.5);
    m2(0, 2) = std::complex<double>(11.17, 22.15);
    m2(1, 0) = std::complex<double>(-13.1, 31.15);
    m2(1, 1) = std::complex<double>(-23.1, 11.3425);
    m2(1, 2) = std::complex<double>(-33.1, 1.25);

	checkMatrixNormInfinity(m2, 1);
}

BOOST_AUTO_TEST_CASE(DiagonalMatrixFromVectorTest)
{
	using namespace CDPL;
	using namespace Math;

	Vector<double> v1;

	checkDiagonalMatrix(v1);

	// ----------

	v1.resize(5, 0.0);

	checkDiagonalMatrix(v1);

	// ----------

	v1.clear(-1.27);

	checkDiagonalMatrix(v1);

	// ----------

	v1(0) = 2.2;
	v1(2) = -12.2;
	v1(4) = 18.12445;

	checkDiagonalMatrix(v1);
}

BOOST_AUTO_TEST_CASE(CrossProductMatrixFromVectorTest)
{
	using namespace CDPL;
	using namespace Math;

	BOOST_CHECK_THROW((CrossProductMatrixFromVector<CVector<float, 0> >::apply(CVector<float, 0>(), 0, 0)), Base::SizeError);
	BOOST_CHECK_THROW((CrossProductMatrixFromVector<CVector<int, 2> >::apply(CVector<int, 2>(), 0, 0)), Base::SizeError);
	BOOST_CHECK_THROW((CrossProductMatrixFromVector<Vector<double> >::apply(Vector<double>(10), 0, 0)), Base::SizeError);

	// ----------

	BOOST_CHECK_THROW(checkCrossProdMatrix(vec(1.1, 2.2, 3.3, 0.0)), Base::SizeError);
	BOOST_CHECK_THROW(checkCrossProdMatrix(Vector<int>(10)), Base::SizeError);
	BOOST_CHECK_THROW(checkCrossProdMatrix(Vector<float>()), Base::SizeError);
	BOOST_CHECK_THROW(checkCrossProdMatrix(vec(-1.1, 0.2)), Base::SizeError);

	// ----------

	checkCrossProdMatrix(vec(0, 0, 0));
	checkCrossProdMatrix(vec(1, 0, 0));
	checkCrossProdMatrix(vec(0, 2.0f, 0));
	checkCrossProdMatrix(vec(0, 0.0, 1.0));

	checkCrossProdMatrix(vec(-1.2, 0, 0));
	checkCrossProdMatrix(vec(0, -2.2f, 0));
	checkCrossProdMatrix(vec(0, 0.0, -5));

	checkCrossProdMatrix(vec(2, 4, 1));
	checkCrossProdMatrix(vec(-2, -4.2, -1.4f));
}

BOOST_AUTO_TEST_CASE(MatrixVectorProductTest)
{
	using namespace CDPL;
	using namespace Math;

	BOOST_CHECK_THROW((MatrixVectorProduct<Matrix<float>, CVector<int, 1> >::apply(Matrix<float>(), CVector<int, 1>(), 0)), Base::SizeError);
	BOOST_CHECK_THROW((MatrixVectorProduct<Matrix<float>, Vector<double> >::apply(Matrix<float>(0, 1), Vector<double>(0), 2)), Base::SizeError);
	BOOST_CHECK_THROW((MatrixVectorProduct<Matrix<float>, Vector<double> >::apply(Matrix<float>(0, 1), Vector<double>(2), 3)), Base::SizeError);
	BOOST_CHECK_THROW((MatrixVectorProduct<Matrix<float>, Vector<double> >::apply(Matrix<float>(0, 4), Vector<double>(3), 1)), Base::SizeError);

	BOOST_CHECK_THROW((MatrixVectorProduct<Matrix<float>, Vector<double> >::apply(Matrix<int>(2, 0), Vector<double>(1), 1)), Base::SizeError);
	BOOST_CHECK_THROW((MatrixVectorProduct<Matrix<float>, Vector<double> >::apply(Matrix<float>(1, 4), Vector<int>(0), 2)), Base::SizeError);
	BOOST_CHECK_THROW((MatrixVectorProduct<Matrix<float>, Vector<double> >::apply(Matrix<float>(66, 2), Vector<short>(3), 5)), Base::SizeError);
	BOOST_CHECK_THROW((MatrixVectorProduct<Matrix<float>, Vector<double> >::apply(Matrix<float>(1, 5), Vector<int>(2), 0)), Base::SizeError);

	// ----------

	Matrix<double> m1(3, 0);

	checkMatrixVectorProd(m1, Vector<int>());

	// ----------

	m1.resize(3, 1);

	m1(0, 0) = -2.3;
	m1(1, 0) = 1.0;
	m1(2, 0) = -21.20;

	checkMatrixVectorProd(m1, Vector<float>(1, -2.37f));

	// ----------

	m1.resize(3, 2, true);

	m1(0, 1) = 2;
	m1(1, 1) = -1.10;
	m1(2, 1) = 0.001;

	checkMatrixVectorProd(m1, vec(-0.21, 100));

	// ----------

	m1.resize(3, 3, true);

	m1(0, 2) = 0.12;
	m1(1, 2) = 2.10;
	m1(2, 2) = -20.001;

	checkMatrixVectorProd(m1, vec(1, -2, 3));

	// ----------

	m1.resize(3, 4, true);

	m1(0, 3) = 3;
	m1(1, 3) = 4;
	m1(2, 3) = 5;

	checkMatrixVectorProd(m1, vec(6, 7.12, -1, 2));
}

BOOST_AUTO_TEST_CASE(VectorMatrixProductTest)
{
	using namespace CDPL;
	using namespace Math;

	BOOST_CHECK_THROW((VectorMatrixProduct<CVector<int, 1>, Matrix<float> >::apply(CVector<int, 1>(), Matrix<float>(), 0)), Base::SizeError);
	BOOST_CHECK_THROW((VectorMatrixProduct<Vector<double>, Matrix<float> >::apply(Vector<double>(0), Matrix<float>(1, 0), 2)), Base::SizeError);
	BOOST_CHECK_THROW((VectorMatrixProduct<Vector<double>, Matrix<float> >::apply(Vector<double>(2), Matrix<float>(1, 0), 3)), Base::SizeError);
	BOOST_CHECK_THROW((VectorMatrixProduct<Vector<double>, Matrix<float> >::apply(Vector<double>(3), Matrix<float>(4, 0), 1)), Base::SizeError);

	BOOST_CHECK_THROW((VectorMatrixProduct<Vector<double>, Matrix<float> >::apply(Vector<double>(1), Matrix<int>(0, 2), 1)), Base::SizeError);
	BOOST_CHECK_THROW((VectorMatrixProduct<Vector<double>, Matrix<float> >::apply(Vector<int>(0), Matrix<float>(4, 1), 2)), Base::SizeError);
	BOOST_CHECK_THROW((VectorMatrixProduct<Vector<double>, Matrix<float> >::apply(Vector<short>(3), Matrix<float>(2, 66), 5)), Base::SizeError);
	BOOST_CHECK_THROW((VectorMatrixProduct<Vector<double>, Matrix<float> >::apply(Vector<int>(2), Matrix<float>(5, 1), 0)), Base::SizeError);

	// ----------

	Matrix<double> m1(0, 3);

	checkVectorMatrixProd(Vector<int>(), m1);

	// ----------

	m1.resize(1, 3);

	m1(0, 0) = -2.3;
	m1(0, 1) = 1.0;
	m1(0, 2) = -21.20;

	checkVectorMatrixProd(Vector<float>(1, -2.37f), m1);

	// ----------

	m1.resize(2, 3, true);

	m1(1, 0) = 2;
	m1(1, 1) = -1.10;
	m1(1, 2) = 0.001;

	checkVectorMatrixProd(vec(-0.21, 100), m1);

	// ----------

	m1.resize(3, 3, true);

	m1(2, 0) = 0.12;
	m1(2, 1) = 2.10;
	m1(2, 2) = -20.001;

	checkVectorMatrixProd(vec(1, -2, 3), m1);

	// ----------

	m1.resize(4, 3, true);

	m1(3, 0) = 3;
	m1(3, 1) = 4;
	m1(3, 2) = 5;

	checkVectorMatrixProd(vec(6, 7.12, -1, 2), m1);
}

BOOST_AUTO_TEST_CASE(MatrixProductTest)
{
	using namespace CDPL;
	using namespace Math;

	BOOST_CHECK_THROW((MatrixProduct<CMatrix<int, 0, 1>, Matrix<float> >::apply(CMatrix<int, 0, 1>(), Matrix<float>(), 0, 0)), Base::SizeError);
	BOOST_CHECK_THROW((MatrixProduct<Matrix<double>, Matrix<float> >::apply(Matrix<double>(0, 0), Matrix<float>(1, 0), 10, 12)), Base::SizeError);
	BOOST_CHECK_THROW((MatrixProduct<Matrix<double>, Matrix<float> >::apply(Matrix<double>(0, 2), Matrix<float>(1, 0), 3, 0)), Base::SizeError);
	BOOST_CHECK_THROW((MatrixProduct<Matrix<double>, Matrix<float> >::apply(Matrix<double>(0, 3), Matrix<float>(4, 0), 1, 1)), Base::SizeError);

	BOOST_CHECK_THROW((MatrixProduct<Matrix<double>, Matrix<float> >::apply(Matrix<double>(1, 1), Matrix<int>(0, 2), 1, 2)), Base::SizeError);
	BOOST_CHECK_THROW((MatrixProduct<Matrix<double>, Matrix<float> >::apply(Matrix<int>(3, 0), Matrix<float>(4, 1), 2, 0)), Base::SizeError);
	BOOST_CHECK_THROW((MatrixProduct<Matrix<double>, Matrix<float> >::apply(Matrix<short>(3, 4), Matrix<float>(2, 6), 5, 1)), Base::SizeError);
	BOOST_CHECK_THROW((MatrixProduct<Matrix<double>, Matrix<float> >::apply(Matrix<int>(2, 2), Matrix<float>(5, 1), 0, 0)), Base::SizeError);

	// ----------

	Matrix<double> m1(3, 0);
	Matrix<int> m2(0, 4);

	checkMatrixProd(m1, m2);

	// ----------

	m1.resize(3, 1);
	m2.resize(1, 2);

	m1(0, 0) = -2.3;
	m1(1, 0) = 1.0;
	m1(2, 0) = -21.20;

	m2(0, 0) = -3;
	m2(0, 1) = 2;

	checkMatrixProd(m1, m2);

	// ----------

	m1.resize(3, 2, true);
	m2.resize(2, 4, true);

	m1(0, 1) = 0.3;
	m1(1, 1) = -21.0;
	m1(2, 1) = 220;

	m2(0, 2) = 5;
	m2(0, 3) = -6;
	m2(1, 0) = 9;
	m2(1, 1) = 8;
	m2(1, 2) = -7;
	m2(1, 3) = 26;

	checkMatrixProd(m1, m2);

	// ----------

	m1 = m2;
	m2.resize(4, 2);

	m2(0, 0) = -1;
	m2(1, 0) = 2;
	m2(2, 0) = -3;
	m2(3, 0) = 4;
	m2(0, 1) = 5;
	m2(1, 1) = -6;
	m2(2, 1) = 7;
	m2(3, 1) = -234;

	checkMatrixProd(m1, m2);
}

BOOST_AUTO_TEST_CASE(QuaternionEqualityTest)
{
	using namespace CDPL;
	using namespace Math;

	BOOST_CHECK((QuaternionEquality<Quaternion<int>, RealQuaternion<float> >::apply(Quaternion<int>(0), RealQuaternion<float>())));
	BOOST_CHECK((QuaternionEquality<RealQuaternion<double>, Quaternion<float> >::apply(RealQuaternion<double>(0), Quaternion<float>(0))));
	
	BOOST_CHECK((QuaternionEquality<Quaternion<int>, RealQuaternion<float> >::apply(Quaternion<int>(3), RealQuaternion<float>(3))));
	BOOST_CHECK((QuaternionEquality<RealQuaternion<double>, Quaternion<float> >::apply(RealQuaternion<double>(-2), Quaternion<float>(-2))));

	BOOST_CHECK(!(QuaternionEquality<Quaternion<float>, RealQuaternion<float> >::apply(Quaternion<float>(2), RealQuaternion<float>(3))));
	BOOST_CHECK(!(QuaternionEquality<RealQuaternion<double>, Quaternion<float> >::apply(RealQuaternion<double>(5), Quaternion<float>(5, 2))));
	
	// ----------

	Quaternion<int> q1(0);
	Quaternion<double> q2(0);

	BOOST_CHECK((QuaternionEquality<Quaternion<int>, Quaternion<double> >::apply(q1, q2)));
	BOOST_CHECK((QuaternionEquality<Quaternion<double>, Quaternion<int> >::apply(q2, q1)));

	q1.getC1() = -2;

	BOOST_CHECK(!(QuaternionEquality<Quaternion<int>, Quaternion<double> >::apply(q1, q2)));
	BOOST_CHECK(!(QuaternionEquality<Quaternion<double>, Quaternion<int> >::apply(q2, q1)));

	q2.getC1() = -2;

	BOOST_CHECK((QuaternionEquality<Quaternion<int>, Quaternion<double> >::apply(q1, q2)));
	BOOST_CHECK((QuaternionEquality<Quaternion<double>, Quaternion<int> >::apply(q2, q1)));

	// ----------

	q1.getC4() = 5;

	BOOST_CHECK(!(QuaternionEquality<Quaternion<int>, Quaternion<double> >::apply(q1, q2)));
	BOOST_CHECK(!(QuaternionEquality<Quaternion<double>, Quaternion<int> >::apply(q2, q1)));

	q2.getC4() = 5;

	BOOST_CHECK((QuaternionEquality<Quaternion<int>, Quaternion<double> >::apply(q1, q2)));
	BOOST_CHECK((QuaternionEquality<Quaternion<double>, Quaternion<int> >::apply(q2, q1)));

	// ----------

	q1.getC3() = -6;

	BOOST_CHECK(!(QuaternionEquality<Quaternion<int>, Quaternion<double> >::apply(q1, q2)));
	BOOST_CHECK(!(QuaternionEquality<Quaternion<double>, Quaternion<int> >::apply(q2, q1)));

	q2.getC3() = -6;

	BOOST_CHECK((QuaternionEquality<Quaternion<int>, Quaternion<double> >::apply(q1, q2)));
	BOOST_CHECK((QuaternionEquality<Quaternion<double>, Quaternion<int> >::apply(q2, q1)));

	// ----------

	q1.getC2() = 15;

	BOOST_CHECK(!(QuaternionEquality<Quaternion<int>, Quaternion<double> >::apply(q1, q2)));
	BOOST_CHECK(!(QuaternionEquality<Quaternion<double>, Quaternion<int> >::apply(q2, q1)));

	q2.getC2() = 15;

	BOOST_CHECK((QuaternionEquality<Quaternion<int>, Quaternion<double> >::apply(q1, q2)));
	BOOST_CHECK((QuaternionEquality<Quaternion<double>, Quaternion<int> >::apply(q2, q1)));

	// ----------

	q1.getC4() = -15;

	BOOST_CHECK(!(QuaternionEquality<Quaternion<int>, Quaternion<double> >::apply(q1, q2)));
	BOOST_CHECK(!(QuaternionEquality<Quaternion<double>, Quaternion<int> >::apply(q2, q1)));

	q2.getC4() = -15;

	BOOST_CHECK((QuaternionEquality<Quaternion<int>, Quaternion<double> >::apply(q1, q2)));
	BOOST_CHECK((QuaternionEquality<Quaternion<double>, Quaternion<int> >::apply(q2, q1)));

	// ----------

	BOOST_CHECK((QuaternionEquality<Quaternion<double>, Quaternion<double> >::apply(Quaternion<double>(0.1, -0.2, 2, 3), 
																					Quaternion<double>(0.1, -0.2, 2, 3))));
	BOOST_CHECK(!(QuaternionEquality<Quaternion<double>, Quaternion<double> >::apply(Quaternion<double>(0.1, -0.2, 2, 3), 
																					Quaternion<double>(0.1, -0.2, 2, 3.00001))));
}

BOOST_AUTO_TEST_CASE(QuaternionToleranceEqualityTest)
{
	using namespace CDPL;
	using namespace Math;

	BOOST_CHECK((QuaternionToleranceEquality<RealQuaternion<int>, Quaternion<float>, int>::apply(RealQuaternion<int>(0), Quaternion<float>(0), 0)));
	BOOST_CHECK((QuaternionToleranceEquality<Quaternion<int>, RealQuaternion<float>, double>::apply(Quaternion<int>(3), RealQuaternion<float>(3), 0.0)));
	BOOST_CHECK((QuaternionToleranceEquality<Quaternion<int>, RealQuaternion<float>, double>::apply(Quaternion<int>(3), RealQuaternion<float>(3), 2.23)));

	BOOST_CHECK(!(QuaternionToleranceEquality<Quaternion<double>, RealQuaternion<float>, double>::apply(Quaternion<double>(3.01), RealQuaternion<float>(3), 0)));
	BOOST_CHECK((QuaternionToleranceEquality<Quaternion<double>, RealQuaternion<float>, double>::apply(Quaternion<double>(3.01, 0.002), RealQuaternion<float>(3), 0.01)));
	BOOST_CHECK(!(QuaternionToleranceEquality<Quaternion<double>, RealQuaternion<float>, double>::apply(Quaternion<double>(3.01, 0.002), RealQuaternion<float>(3), 0.009)));

	// ----------

	Quaternion<int> q1(1, -2, 3, 4);
	Quaternion<double> q2(0);

	BOOST_CHECK(!(QuaternionToleranceEquality<Quaternion<int>, Quaternion<double>, float>::apply(q1, q2, 0.0f)));
	BOOST_CHECK(!(QuaternionToleranceEquality<Quaternion<double>, Quaternion<int>, float>::apply(q2, q1, 0.0f)));

	BOOST_CHECK(!(QuaternionToleranceEquality<Quaternion<int>, Quaternion<double>, float>::apply(q1, q2, 3.9999f)));
	BOOST_CHECK(!(QuaternionToleranceEquality<Quaternion<double>, Quaternion<int>, double>::apply(q2, q1, 3.9999)));

	BOOST_CHECK((QuaternionToleranceEquality<Quaternion<int>, Quaternion<double>, float>::apply(q1, q2, 4.0f)));
	BOOST_CHECK((QuaternionToleranceEquality<Quaternion<double>, Quaternion<int>, int>::apply(q2, q1, 4)));
	BOOST_CHECK(!(QuaternionToleranceEquality<Quaternion<double>, Quaternion<int>, int>::apply(q2, q1, -4)));

	q2.getC4() = 4;

	BOOST_CHECK(!(QuaternionToleranceEquality<Quaternion<int>, Quaternion<double>, float>::apply(q1, q2, 0.0f)));
	BOOST_CHECK(!(QuaternionToleranceEquality<Quaternion<double>, Quaternion<int>, float>::apply(q2, q1, 0.0f)));

	BOOST_CHECK(!(QuaternionToleranceEquality<Quaternion<int>, Quaternion<double>, double>::apply(q1, q2, 2.9999)));
	BOOST_CHECK(!(QuaternionToleranceEquality<Quaternion<double>, Quaternion<int>, long double>::apply(q2, q1, 2.9999L)));

	BOOST_CHECK((QuaternionToleranceEquality<Quaternion<int>, Quaternion<double>, double>::apply(q1, q2, 3.0)));
	BOOST_CHECK((QuaternionToleranceEquality<Quaternion<double>, Quaternion<int>, short int>::apply(q2, q1, 3)));
	BOOST_CHECK(!(QuaternionToleranceEquality<Quaternion<double>, Quaternion<int>, short int>::apply(q2, q1, -3)));

	q2.getC3() = 3;

	BOOST_CHECK(!(QuaternionToleranceEquality<Quaternion<int>, Quaternion<double>, float>::apply(q1, q2, 0.0f)));
	BOOST_CHECK(!(QuaternionToleranceEquality<Quaternion<double>, Quaternion<int>, float>::apply(q2, q1, 0.0f)));

	BOOST_CHECK(!(QuaternionToleranceEquality<Quaternion<int>, Quaternion<double>, float>::apply(q1, q2, 1.9999f)));
	BOOST_CHECK(!(QuaternionToleranceEquality<Quaternion<double>, Quaternion<int>, double>::apply(q2, q1, 1.9999)));

	BOOST_CHECK((QuaternionToleranceEquality<Quaternion<int>, Quaternion<double>, int>::apply(q1, q2, 2)));
	BOOST_CHECK((QuaternionToleranceEquality<Quaternion<double>, Quaternion<int>, float>::apply(q2, q1, 2.0f)));
	BOOST_CHECK(!(QuaternionToleranceEquality<Quaternion<double>, Quaternion<int>, float>::apply(q2, q1, -2.0f)));

	q2.getC2() = -2;

	BOOST_CHECK(!(QuaternionToleranceEquality<Quaternion<int>, Quaternion<double>, float>::apply(q1, q2, 0.0f)));
	BOOST_CHECK(!(QuaternionToleranceEquality<Quaternion<double>, Quaternion<int>, float>::apply(q2, q1, 0.0f)));

	BOOST_CHECK(!(QuaternionToleranceEquality<Quaternion<int>, Quaternion<double>, double>::apply(q1, q2, 0.9999)));
	BOOST_CHECK(!(QuaternionToleranceEquality<Quaternion<double>, Quaternion<int>, long double>::apply(q2, q1, 0.9999L)));

	BOOST_CHECK((QuaternionToleranceEquality<Quaternion<int>, Quaternion<double>, unsigned char>::apply(q1, q2, 1)));
	BOOST_CHECK((QuaternionToleranceEquality<Quaternion<double>, Quaternion<int>, double>::apply(q2, q1, 1.0)));
	BOOST_CHECK(!(QuaternionToleranceEquality<Quaternion<double>, Quaternion<int>, double>::apply(q2, q1, -1.0)));

	q2.getC1() = 1;

	BOOST_CHECK((QuaternionToleranceEquality<Quaternion<int>, Quaternion<double>, float>::apply(q1, q2, 0.0f)));
	BOOST_CHECK((QuaternionToleranceEquality<Quaternion<double>, Quaternion<int>, long int>::apply(q2, q1, 0)));
	BOOST_CHECK((QuaternionToleranceEquality<Quaternion<int>, Quaternion<double>, double>::apply(q1, q2, 0.000001)));
	BOOST_CHECK(!(QuaternionToleranceEquality<Quaternion<int>, Quaternion<double>, double>::apply(q1, q2, -0.000001)));

	// ----------

	q2.getC1() = -1;

	BOOST_CHECK(!(QuaternionToleranceEquality<Quaternion<int>, Quaternion<double>, float>::apply(q1, q2, 0.0f)));
	BOOST_CHECK(!(QuaternionToleranceEquality<Quaternion<double>, Quaternion<int>, long int>::apply(q2, q1, 0)));
	BOOST_CHECK(!(QuaternionToleranceEquality<Quaternion<int>, Quaternion<double>, float>::apply(q1, q2, 1.0f)));
	BOOST_CHECK(!(QuaternionToleranceEquality<Quaternion<double>, Quaternion<int>, long int>::apply(q2, q1, 1)));
	BOOST_CHECK(!(QuaternionToleranceEquality<Quaternion<int>, Quaternion<double>, float>::apply(q1, q2, 1.99f)));
	BOOST_CHECK(!(QuaternionToleranceEquality<Quaternion<double>, Quaternion<int>, long int>::apply(q2, q1, 1)));
	BOOST_CHECK((QuaternionToleranceEquality<Quaternion<int>, Quaternion<double>, float>::apply(q1, q2, 2.0f)));
	BOOST_CHECK((QuaternionToleranceEquality<Quaternion<double>, Quaternion<int>, long int>::apply(q2, q1, 2)));
}

BOOST_AUTO_TEST_CASE(QuaternionElementSumTest)
{
	using namespace CDPL;
	using namespace Math;

	BOOST_CHECK_EQUAL((QuaternionElementSum<Quaternion<double> >::apply(Quaternion<double>(0))), 0.0 + 0.0 + 0.0 + 0.0);

	BOOST_CHECK_EQUAL((QuaternionElementSum<Quaternion<float> >::apply(Quaternion<float>(1.123f))), 1.123f + 0.0f + 0.0f + 0.0f);

	BOOST_CHECK_EQUAL((QuaternionElementSum<RealQuaternion<double> >::apply(RealQuaternion<double>(0))), 0.0 + 0.0 + 0.0 + 0.0);

	BOOST_CHECK_EQUAL((QuaternionElementSum<RealQuaternion<double> >::apply(RealQuaternion<double>(-2.1234))), -2.1234 + 0.0 + 0.0 + 0.0);

	BOOST_CHECK_EQUAL((QuaternionElementSum<Quaternion<int> >::apply(Quaternion<int>(-1, 2, -3))), -1 + 2 + -3 + 0);

	BOOST_CHECK_EQUAL((QuaternionElementSum<Quaternion<double> >::apply(Quaternion<double>(1.2, 2.345, -15.67, 20.111))), 1.2 + 2.345 + -15.67 + 20.111);

	BOOST_CHECK_EQUAL((QuaternionElementSum<Quaternion<float> >::apply(Quaternion<float>(-100.2f, 40.0f, 50.2f, 10.0f))), -100.2f + 40.0f + 50.2f + 10.0f);

	// ----------

	BOOST_CHECK_EQUAL((QuaternionElementSum<Quaternion<std::complex<double> > >::apply(Quaternion<std::complex<double> >(std::complex<double>(-17.2, 4.5), 
																														 std::complex<double>(15.16, -14.5), 
																														 std::complex<double>(11.17, 22.15),
																														 std::complex<double>(-3.1, -1.25)))),
					  std::complex<double>(-17.2, 4.5) + std::complex<double>(15.16, -14.5) 
					  + std::complex<double>(11.17, 22.15) + std::complex<double>(-3.1, -1.25));
}

BOOST_AUTO_TEST_CASE(QuaternionNormTest)
{
	using namespace CDPL;
	using namespace Math;

	checkQuaternionNorm(Quaternion<int>(0));
	checkQuaternionNorm(Quaternion<int>(5));
	checkQuaternionNorm(Quaternion<int>(5, -3));
	checkQuaternionNorm(Quaternion<int>(-25, -23, 27));
	checkQuaternionNorm(Quaternion<int>(3, 23, -22, 1));
	checkQuaternionNorm(Quaternion<int>(3, 0, 0, -2));

	// ----------

	checkQuaternionNorm(RealQuaternion<float>(0));
	checkQuaternionNorm(RealQuaternion<float>(-2.34245f));
	checkQuaternionNorm(RealQuaternion<float>(42.4245f));

	// ----------

	checkQuaternionNorm(Quaternion<double>(0));
	checkQuaternionNorm(Quaternion<double>(-2.34245));
	checkQuaternionNorm(Quaternion<double>(42.4245, 0.0, 0.0001, 1.234));
	checkQuaternionNorm(Quaternion<double>(2.4245, 1.23, 5.27, -2.2223));

	// ----------

	checkQuaternionNorm(Quaternion<std::complex<double> >(std::complex<double>(-17.2, 4.5), std::complex<double>(15.16, -14.5), 
														  std::complex<double>(11.17, 22.15), std::complex<double>(-3.1, -1.25)));
}

BOOST_AUTO_TEST_CASE(QuaternionNorm2Test)
{
	using namespace CDPL;
	using namespace Math;

	checkQuaternionNorm2(Quaternion<int>(0));
	checkQuaternionNorm2(Quaternion<int>(5));
	checkQuaternionNorm2(Quaternion<int>(5, -3));
	checkQuaternionNorm2(Quaternion<int>(-25, -23, 27));
	checkQuaternionNorm2(Quaternion<int>(3, 23, -22, 1));
	checkQuaternionNorm2(Quaternion<int>(3, 0, 0, -2));

	// ----------

	checkQuaternionNorm2(RealQuaternion<float>(0));
	checkQuaternionNorm2(RealQuaternion<float>(-2.34245f));
	checkQuaternionNorm2(RealQuaternion<float>(42.4245f));

	// ----------

	checkQuaternionNorm2(Quaternion<double>(0));
	checkQuaternionNorm2(Quaternion<double>(-2.34245));
	checkQuaternionNorm2(Quaternion<double>(42.4245, 0.0, 0.0001, 1.234));
	checkQuaternionNorm2(Quaternion<double>(2.4245, 1.23, 5.27, -2.2223));

	// ----------

	checkQuaternionNorm2(Quaternion<std::complex<double> >(std::complex<double>(-17.2, 4.5), std::complex<double>(15.16, -14.5), 
														   std::complex<double>(11.17, 22.15), std::complex<double>(-3.1, -1.25)));
}

BOOST_AUTO_TEST_CASE(QuaternionUnrealTest)
{
	using namespace CDPL;
	using namespace Math;

	checkQuaternionUnreal(Quaternion<int>(0));
	checkQuaternionUnreal(Quaternion<int>(5));
	checkQuaternionUnreal(Quaternion<int>(5, -3));
	checkQuaternionUnreal(Quaternion<int>(-25, -23, 27));
	checkQuaternionUnreal(Quaternion<int>(3, 23, -22, 1));
	checkQuaternionUnreal(Quaternion<int>(3, 0, 0, -2));

	// ----------

	checkQuaternionUnreal(RealQuaternion<float>(0));
	checkQuaternionUnreal(RealQuaternion<float>(-2.34245f));
	checkQuaternionUnreal(RealQuaternion<float>(42.4245f));

	// ----------

	checkQuaternionUnreal(Quaternion<double>(0));
	checkQuaternionUnreal(Quaternion<double>(-2.34245));
	checkQuaternionUnreal(Quaternion<double>(42.4245, 0.0, 0.0001, 1.234));
	checkQuaternionUnreal(Quaternion<double>(2.4245, 1.23, 5.27, -2.2223));

	// ----------

	checkQuaternionUnreal(Quaternion<std::complex<double> >(std::complex<double>(-17.2, 4.5), std::complex<double>(15.16, -14.5), 
															std::complex<double>(11.17, 22.15), std::complex<double>(-3.1, -1.25)));
}

BOOST_AUTO_TEST_CASE(QuaternionConjugateTest)
{
	using namespace CDPL;
	using namespace Math;

	checkQuaternionConjugate(Quaternion<int>(0));
	checkQuaternionConjugate(Quaternion<int>(5));
	checkQuaternionConjugate(Quaternion<int>(5, -3));
	checkQuaternionConjugate(Quaternion<int>(-25, -23, 27));
	checkQuaternionConjugate(Quaternion<int>(3, 23, -22, 1));
	checkQuaternionConjugate(Quaternion<int>(3, 0, 0, -2));

	// ----------

	checkQuaternionConjugate(RealQuaternion<float>(0));
	checkQuaternionConjugate(RealQuaternion<float>(-2.34245f));
	checkQuaternionConjugate(RealQuaternion<float>(42.4245f));

	// ----------

	checkQuaternionConjugate(Quaternion<double>(0));
	checkQuaternionConjugate(Quaternion<double>(-2.34245));
	checkQuaternionConjugate(Quaternion<double>(42.4245, 0.0, 0.0001, 1.234));
	checkQuaternionConjugate(Quaternion<double>(2.4245, 1.23, 5.27, -2.2223));

	// ----------

	checkQuaternionConjugate(Quaternion<std::complex<double> >(std::complex<double>(-17.2, 4.5), std::complex<double>(15.16, -14.5), 
															   std::complex<double>(11.17, 22.15), std::complex<double>(-3.1, -1.25)));
}

BOOST_AUTO_TEST_CASE(Scalar1QuaternionAdditionTest)
{
	using namespace CDPL;
	using namespace Math;

	checkScalarQuaternionAddition(int(-4), Quaternion<double>(0));
	checkScalarQuaternionAddition(4.27, Quaternion<int>(5));
	checkScalarQuaternionAddition(-25.778985f, Quaternion<double>(5, -3));
	checkScalarQuaternionAddition(0.3, Quaternion<float>(3, 23, -22, 1));
	checkScalarQuaternionAddition(int(15), Quaternion<int>(3, 0, 0, -2));
	checkScalarQuaternionAddition(-37.77, Quaternion<double>(-233, 100.23, -5.5555, -2));

	// ----------

	checkScalarQuaternionAddition(1.12, RealQuaternion<int>(0));
	checkScalarQuaternionAddition(16.66f, RealQuaternion<float>(-2.34245f));
	checkScalarQuaternionAddition(int(-51), RealQuaternion<double>(42.4245f));
	checkScalarQuaternionAddition(short(0), RealQuaternion<double>(42.4245f));

	// ----------

	checkScalarQuaternionAddition(std::complex<int>(-3, 1), Quaternion<int>(-25, -23, 27));
	checkScalarQuaternionAddition(12.2, Quaternion<std::complex<double> >(std::complex<double>(-17.2, 4.5), std::complex<double>(15.16, -14.5), 
																		  std::complex<double>(11.17, 22.15), std::complex<double>(-3.1, -1.25)));
	checkScalarQuaternionAddition(std::complex<double>(17.2, -4.5001), Quaternion<std::complex<double> >(std::complex<double>(-17.2, 4.5),
																										 std::complex<double>(15.16, -14.5), 
																										 std::complex<double>(11.17, 22.15),
																										 std::complex<double>(-3.1, -1.25)));
}

BOOST_AUTO_TEST_CASE(Scalar1QuaternionSubtractionTest)
{
	using namespace CDPL;
	using namespace Math;

	checkScalarQuaternionSubtraction(int(-4), Quaternion<double>(0));
	checkScalarQuaternionSubtraction(4.27, Quaternion<int>(5));
	checkScalarQuaternionSubtraction(-25.778985f, Quaternion<double>(5, -3));
	checkScalarQuaternionSubtraction(0.3, Quaternion<float>(3, 23, -22, 1));
	checkScalarQuaternionSubtraction(int(15), Quaternion<int>(3, 0, 0, -2));
	checkScalarQuaternionSubtraction(-37.77, Quaternion<double>(-233, 100.23, -5.5555, -2));

	// ----------

	checkScalarQuaternionSubtraction(1.12, RealQuaternion<int>(0));
	checkScalarQuaternionSubtraction(16.66f, RealQuaternion<float>(-2.34245f));
	checkScalarQuaternionSubtraction(int(-51), RealQuaternion<double>(42.4245f));
	checkScalarQuaternionSubtraction(short(0), RealQuaternion<double>(42.4245f));

	// ----------

	checkScalarQuaternionSubtraction(std::complex<int>(-3, 1), Quaternion<int>(-25, -23, 27));
	checkScalarQuaternionSubtraction(12.2, Quaternion<std::complex<double> >(std::complex<double>(-17.2, 4.5), std::complex<double>(15.16, -14.5), 
																			 std::complex<double>(11.17, 22.15), std::complex<double>(-3.1, -1.25)));
	checkScalarQuaternionSubtraction(std::complex<double>(17.2, -4.5001), Quaternion<std::complex<double> >(std::complex<double>(-17.2, 4.5),
																											std::complex<double>(15.16, -14.5), 
																											std::complex<double>(11.17, 22.15),
																											std::complex<double>(-3.1, -1.25)));
}

BOOST_AUTO_TEST_CASE(Scalar2QuaternionAdditionTest)
{
	using namespace CDPL;
	using namespace Math;

	checkQuaternionScalarAddition(Quaternion<double>(0), int(-4));
	checkQuaternionScalarAddition(Quaternion<int>(5), 4.27);
	checkQuaternionScalarAddition(Quaternion<double>(5, -3), -25.778985f);
	checkQuaternionScalarAddition(Quaternion<float>(3, 23, -22, 1), 0.3);
	checkQuaternionScalarAddition(Quaternion<int>(3, 0, 0, -2), int(15));
	checkQuaternionScalarAddition(Quaternion<double>(-233, 100.23, -5.5555, -2), -37.77);

	// ----------

	checkQuaternionScalarAddition(RealQuaternion<int>(0), 1.12);
	checkQuaternionScalarAddition(RealQuaternion<float>(-2.34245f), 16.66f);
	checkQuaternionScalarAddition(RealQuaternion<double>(42.4245f), int(-51));
	checkQuaternionScalarAddition(RealQuaternion<double>(42.4245f), short(0));

	// ----------

	checkQuaternionScalarAddition(Quaternion<int>(-25, -23, 27), std::complex<int>(-3, 1));
	checkQuaternionScalarAddition(Quaternion<std::complex<double> >(std::complex<double>(-17.2, 4.5), std::complex<double>(15.16, -14.5), 
																	std::complex<double>(11.17, 22.15), std::complex<double>(-3.1, -1.25)), 12.2);
	checkQuaternionScalarAddition(Quaternion<std::complex<double> >(std::complex<double>(-17.2, 4.5),
																	std::complex<double>(15.16, -14.5), 
																	std::complex<double>(11.17, 22.15),
																	std::complex<double>(-3.1, -1.25)), std::complex<double>(17.2, -4.5001));
}

BOOST_AUTO_TEST_CASE(Scalar2QuaternionSubtractionTest)
{
	using namespace CDPL;
	using namespace Math;

	checkQuaternionScalarSubtraction(Quaternion<double>(0), int(-4));
	checkQuaternionScalarSubtraction(Quaternion<int>(5), 4.27);
	checkQuaternionScalarSubtraction(Quaternion<double>(5, -3), -25.778985f);
	checkQuaternionScalarSubtraction(Quaternion<float>(3, 23, -22, 1), 0.3);
	checkQuaternionScalarSubtraction(Quaternion<int>(3, 0, 0, -2), int(15));
	checkQuaternionScalarSubtraction(Quaternion<double>(-233, 100.23, -5.5555, -2), -37.77);

	// ----------

	checkQuaternionScalarSubtraction(RealQuaternion<int>(0), 1.12);
	checkQuaternionScalarSubtraction(RealQuaternion<float>(-2.34245f), 16.66f);
	checkQuaternionScalarSubtraction(RealQuaternion<double>(42.4245f), int(-51));
	checkQuaternionScalarSubtraction(RealQuaternion<double>(42.4245f), short(0));

	// ----------

	checkQuaternionScalarSubtraction(Quaternion<int>(-25, -23, 27), std::complex<int>(-3, 1));
	checkQuaternionScalarSubtraction(Quaternion<std::complex<double> >(std::complex<double>(-17.2, 4.5), std::complex<double>(15.16, -14.5), 
																	   std::complex<double>(11.17, 22.15), std::complex<double>(-3.1, -1.25)), 12.2);
	checkQuaternionScalarSubtraction(Quaternion<std::complex<double> >(std::complex<double>(-17.2, 4.5),
																	   std::complex<double>(15.16, -14.5), 
																	   std::complex<double>(11.17, 22.15),
																	   std::complex<double>(-3.1, -1.25)), std::complex<double>(17.2, -4.5001));
}

BOOST_AUTO_TEST_CASE(QuaternionInverseTest)
{
	using namespace CDPL;
	using namespace Math;

	checkQuaternionInverse(Quaternion<double>(0), int(-4));
	checkQuaternionInverse(Quaternion<int>(5), 4.27);
	checkQuaternionInverse(Quaternion<double>(5, -3), -25.778985f);
	checkQuaternionInverse(Quaternion<float>(3, 23, -22, 1), 0.3);
	checkQuaternionInverse(Quaternion<int>(3, 0, 0, -2), int(15));
	checkQuaternionInverse(Quaternion<double>(-233, 100.23, -5.5555, -2), -37.77);

	// ----------

	checkQuaternionInverse(RealQuaternion<int>(0), 1.12);
	checkQuaternionInverse(RealQuaternion<float>(-2.34245f), 16.66f);
	checkQuaternionInverse(RealQuaternion<double>(42.4245), int(-51));

	// ----------

	checkQuaternionInverse(Quaternion<int>(-25, -23, 27), std::complex<int>(-3, 1));
	checkQuaternionInverse(Quaternion<std::complex<double> >(std::complex<double>(-17.2, 4.5), std::complex<double>(15.16, -14.5), 
															 std::complex<double>(11.17, 22.15), std::complex<double>(-3.1, -1.25)), 12.2);
	checkQuaternionInverse(Quaternion<std::complex<double> >(std::complex<double>(-17.2, 4.5),
															 std::complex<double>(15.16, -14.5), 
															 std::complex<double>(11.17, 22.15),
															 std::complex<double>(-3.1, -1.25)), std::complex<double>(17.2, -4.5001));
}

BOOST_AUTO_TEST_CASE(QuaternionProductTest)
{
	using namespace CDPL;
	using namespace Math;

	checkQuaternionProduct(Quaternion<double>(0), Quaternion<int>(5));
	checkQuaternionProduct(Quaternion<int>(5), Quaternion<double>(5, -3));
	checkQuaternionProduct(Quaternion<double>(5, -3), Quaternion<float>(3, 23, -22, 1));
	checkQuaternionProduct(Quaternion<float>(3, 23, -22, 1), Quaternion<int>(3, 0, 0, -2));
	checkQuaternionProduct(Quaternion<int>(3, 0, 0, -2), Quaternion<double>(-233, 100.23, -5.5555, -2));
	checkQuaternionProduct(Quaternion<double>(-233, 100.23, -5.5555, -2), RealQuaternion<double>(42.4245));

	// ----------

	checkQuaternionProduct(RealQuaternion<int>(0), Quaternion<double>(-233, 100.23, -5.5555, -2));
	checkQuaternionProduct(RealQuaternion<float>(-2.34245f), RealQuaternion<double>(42.4245));
	checkQuaternionProduct(RealQuaternion<double>(42.4245), RealQuaternion<std::complex<double> >(std::complex<double>(-17.2, 4.5)));
	checkQuaternionProduct(RealQuaternion<std::complex<double> >(std::complex<double>(-17.2, 4.5)), RealQuaternion<double>(42.4245));

	// ----------

	checkQuaternionProduct(Quaternion<int>(-25, -23, 27), Quaternion<std::complex<int> >(std::complex<int>(-17, 5)));
	checkQuaternionProduct(Quaternion<std::complex<double> >(std::complex<double>(-17.2, 4.5), std::complex<double>(15.16, -14.5), 
															 std::complex<double>(11.17, 22.15), std::complex<double>(-3.1, -1.25)), 
						   Quaternion<double>(-233, 100.23, -5.5555, -2));
	checkQuaternionProduct(Quaternion<std::complex<double> >(std::complex<double>(-17.2, 4.5),
															 std::complex<double>(15.16, -14.5), 
															 std::complex<double>(11.17, 22.15),
															 std::complex<double>(-3.1, -1.25)),
						   Quaternion<std::complex<double> >(std::complex<double>(17.2, 54.5),
															 std::complex<double>(0.0, -14.5), 
															 std::complex<double>(11.17, 0.15),
															 std::complex<double>(-33.1, 1.25)));
	// ----------

	Quaternion<double> q1(1, 0, 1, 0);
	Quaternion<double> q2(1, 0.5, 0.5, 0.75);

	typedef QuaternionProduct<Quaternion<double>, Quaternion<double> > QP;

	BOOST_CHECK_CLOSE(QP::applyC1(q1, q2), 0.5, 0.0000001);
	BOOST_CHECK_CLOSE(QP::applyC2(q1, q2), 1.25, 0.0000001);
	BOOST_CHECK_CLOSE(QP::applyC3(q1, q2), 1.5, 0.0000001);
	BOOST_CHECK_CLOSE(QP::applyC4(q1, q2), 0.25, 0.0000001);
}

BOOST_AUTO_TEST_CASE(QuaternionDivisionTest)
{
	using namespace CDPL;
	using namespace Math;

	checkQuaternionDivision(Quaternion<double>(0), Quaternion<int>(5), int(-2));
	checkQuaternionDivision(Quaternion<int>(5), Quaternion<double>(5, -3), 2.25f);
	checkQuaternionDivision(Quaternion<double>(5, -3), Quaternion<float>(3, 23, -22, 1), 5.5);
	checkQuaternionDivision(Quaternion<float>(3, 23, -22, 1), Quaternion<int>(3, 0, 0, -2), int(-2));
	checkQuaternionDivision(Quaternion<int>(3, 0, 0, -2), Quaternion<double>(-233, 100.23, -5.5555, -2), -223.2);
	checkQuaternionDivision(Quaternion<double>(-233, 100.23, -5.5555, -2), RealQuaternion<double>(42.4245), 1.17f);

	// ----------

	checkQuaternionDivision(RealQuaternion<int>(0), Quaternion<double>(-233, 100.23, -5.5555, -2), int(3));
	checkQuaternionDivision(RealQuaternion<float>(-2.34245f), RealQuaternion<double>(42.4245), 2.24f);
	checkQuaternionDivision(RealQuaternion<double>(42.4245), RealQuaternion<std::complex<double> >(std::complex<double>(-17.2, 4.5)), -234.232);
	checkQuaternionDivision(RealQuaternion<std::complex<double> >(std::complex<double>(-17.2, 4.5)), RealQuaternion<double>(42.4245), std::complex<double>(2.2, -3.3));

	// ----------

	checkQuaternionDivision(Quaternion<int>(-25, -23, 27), Quaternion<std::complex<int> >(std::complex<int>(-17, 5)), int(-13));
	checkQuaternionDivision(Quaternion<std::complex<double> >(std::complex<double>(-17.2, 4.5), std::complex<double>(15.16, -14.5), 
															  std::complex<double>(11.17, 22.15), std::complex<double>(-3.1, -1.25)), 
							Quaternion<double>(-233, 100.23, -5.5555, -2), 5.45);
	checkQuaternionDivision(Quaternion<std::complex<double> >(std::complex<double>(-17.2, 4.5),
															  std::complex<double>(15.16, -14.5), 
															  std::complex<double>(11.17, 22.15),
															  std::complex<double>(-3.1, -1.25)),
							Quaternion<std::complex<double> >(std::complex<double>(17.2, 54.5),
															  std::complex<double>(0.0, -14.5), 
															  std::complex<double>(11.17, 0.15),
															  std::complex<double>(-33.1, 1.25)), 100.13);
	checkQuaternionDivision(Quaternion<std::complex<double> >(std::complex<double>(-17.2, 4.5),
															  std::complex<double>(15.16, -14.5), 
															  std::complex<double>(11.17, 22.15),
															  std::complex<double>(-3.1, -1.25)),
							Quaternion<std::complex<double> >(std::complex<double>(17.2, 54.5),
															  std::complex<double>(0.0, -24.5), 
															  std::complex<double>(11.17, 1.15),
															  std::complex<double>(-33.1, 1.25)), 
							std::complex<double>(-3.1, -1.25));
}

BOOST_AUTO_TEST_CASE(ScalarQuaternionDivisionTest)
{
	using namespace CDPL;
	using namespace Math;

	checkScalarQuaternionDivision(3.2f, Quaternion<double>(0), int(-4));
	checkScalarQuaternionDivision(int(0), Quaternion<int>(5), 4.27);
	checkScalarQuaternionDivision(2.2, Quaternion<double>(5, -3), -25.778985f);
	checkScalarQuaternionDivision(int(-5), Quaternion<int>(3, 0, 0, -2), int(15));
	checkScalarQuaternionDivision(2.23, Quaternion<double>(-233, 100.23, -5.5555, -2), -37.77);

	// ----------

	checkScalarQuaternionDivision(int(5), RealQuaternion<int>(0), 1.12);
	checkScalarQuaternionDivision(2.2f, RealQuaternion<float>(-2.34245f), 16.66f);
	checkScalarQuaternionDivision(232.5, RealQuaternion<double>(42.4245f), int(-51));
	checkScalarQuaternionDivision(-34.4f, RealQuaternion<double>(42.4245f), short(23));

	// ----------

	checkScalarQuaternionDivision(std::complex<int>(2, -123), Quaternion<int>(-25, -23, 27), std::complex<int>(-3, 1));
	checkScalarQuaternionDivision(323, Quaternion<int>(-25, -23, 27), std::complex<int>(-3, 1));
	checkScalarQuaternionDivision(std::complex<float>(2.3f, -123.2f), Quaternion<float>(3, 23, -22, 1), 0.3f);

	checkScalarQuaternionDivision(std::complex<double>(7.2, 34.5), 
								  Quaternion<std::complex<double> >(std::complex<double>(-17.2, 4.5), std::complex<double>(15.16, -14.5), 
																	std::complex<double>(11.17, 22.15), std::complex<double>(-3.1, -1.25)), 
								  12.2);
	checkScalarQuaternionDivision(-32.4, 
								  Quaternion<std::complex<double> >(std::complex<double>(-17.2, 4.5), std::complex<double>(15.16, -14.5), 
																	std::complex<double>(11.17, 22.15), std::complex<double>(-3.1, -1.25)),
								  std::complex<double>(17.2, -4.5001));
	checkScalarQuaternionDivision(std::complex<double>(0.0, 414.5), 
								  Quaternion<std::complex<double> >(std::complex<double>(-17.2, 4.5), std::complex<double>(15.16, -14.5), 
																	std::complex<double>(11.17, 22.15), std::complex<double>(-3.1, -1.25)),
								  std::complex<double>(-217.2, 4.3501));
}

BOOST_AUTO_TEST_CASE(QuaternionVectorRotationTest)
{
	using namespace CDPL;
	using namespace Math;

	checkQuaternionVectorRotation(Quaternion<double>(0), vec(int(5), int(0), int(0)));
	checkQuaternionVectorRotation(Quaternion<int>(5), vec(0.0, 0.0, 0.0, 2.0));
	checkQuaternionVectorRotation(Quaternion<double>(5, -3), vec(3.0f, 23.0f, -22.0f, -13.2f));
	checkQuaternionVectorRotation(Quaternion<float>(3, 23, -22, 1), vec(3.0, 0.01, -2.0));
	checkQuaternionVectorRotation(Quaternion<int>(3, 0, 0, -2), vec(-233.0, 100.23, -5.5555));
	checkQuaternionVectorRotation(Quaternion<double>(-233, 100.23, -5.5555, -2), vec(0.230, -42.4245, -0.1));

	// ----------

	checkQuaternionVectorRotation(RealQuaternion<int>(0), vec(0.230, -42.4245, -0.1));
	checkQuaternionVectorRotation(RealQuaternion<float>(-2.34245f), vec(0.230, -42.4245, -0.1, 0.0));
	checkQuaternionVectorRotation(RealQuaternion<double>(42.4245), vec(0.230, -42.4245, -0.1, 1.2));
	checkQuaternionVectorRotation(RealQuaternion<std::complex<double> >(std::complex<double>(-17.2, 4.5)), vec(0.230, -42.4245, -0.1));

	// ----------

	checkQuaternionVectorRotation(Quaternion<std::complex<double> >(std::complex<double>(-17.2, 4.5), std::complex<double>(15.16, -14.5), 
																	std::complex<double>(11.17, 22.15), std::complex<double>(-3.1, -1.25)), 
								  vec(std::complex<double>(37.2, 24.5),
									  std::complex<double>(-15.16, 14.5), 
									  std::complex<double>(-1.17, -52.15),
									  std::complex<double>(3.1, 1.425)));

	// ----------

	typedef QuaternionVectorRotation<Quaternion<double>, Vector<double> > QVR;

	Quaternion<double> q(1.0, 0.0, 0.0, 0.0);
	Vector<double> v = vec(1.0, 0.0, 0.0);

	BOOST_CHECK_CLOSE(QVR::apply(q, v, 0), 1.0, 0.0000001);
	BOOST_CHECK_SMALL(QVR::apply(q, v, 1), 0.0000001);
	BOOST_CHECK_SMALL(QVR::apply(q, v, 2), 0.0000001);

	q.getC1() = std::cos(M_PI / 180.0 * 60.0); 
	q.getC2() = std::sin(M_PI / 180.0 * 60.0) / std::sqrt(3.0); 
	q.getC3() = std::sin(M_PI / 180.0 * 60.0) / std::sqrt(3.0); 
	q.getC4() = std::sin(M_PI / 180.0 * 60.0) / std::sqrt(3.0); 

	BOOST_CHECK_SMALL(QVR::apply(q, v, 0), 0.0000001);
	BOOST_CHECK_CLOSE(QVR::apply(q, v, 1), 1.0, 0.0000001);
	BOOST_CHECK_SMALL(QVR::apply(q, v, 2), 0.0000001);

	// ----------

	v.resize(2);

	BOOST_CHECK_THROW(QVR::apply(q, v, 0), Base::SizeError);
	BOOST_CHECK_THROW(QVR::apply(q, v, 1), Base::SizeError);
	BOOST_CHECK_THROW(QVR::apply(q, v, 2), Base::SizeError);

	v.resize(1);

	BOOST_CHECK_THROW(QVR::apply(q, v, 0), Base::SizeError);
	BOOST_CHECK_THROW(QVR::apply(q, v, 1), Base::SizeError);

	v.resize(0);

	BOOST_CHECK_THROW(QVR::apply(q, v, 0), Base::SizeError);
}
