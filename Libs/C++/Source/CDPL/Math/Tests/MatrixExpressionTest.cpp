/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * MatrixExpressionTest.cpp 
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

#include "CDPL/Math/MatrixExpression.hpp"
#include "CDPL/Math/Matrix.hpp"
#include "CDPL/Math/Vector.hpp"
#include "CDPL/Base/Exceptions.hpp"


namespace
{

	template <typename M>
	void checkMatrixTraceFunction(const M& m)
	{
		typedef typename M::ValueType ResultType;
		typedef typename M::SizeType SizeType;

		ResultType exp_val = ResultType();

		for (SizeType i = 0; i < m.getSize1(); i++)
			for (SizeType j = 0; j < m.getSize2(); j++)
				if (i == j)
					exp_val += m(i, j);

		BOOST_CHECK_EQUAL(trace(m), exp_val);
	}

	template <typename M>
	void checkMatrixSumFunction(const M& m)
	{
		typedef typename M::ValueType ResultType;
		typedef typename M::SizeType SizeType;

		ResultType exp_val = ResultType();

		for (SizeType i = 0; i < m.getSize1(); i++)
			for (SizeType j = 0; j < m.getSize2(); j++)
				exp_val += m(i, j);

		BOOST_CHECK_EQUAL(sum(m), exp_val);
	}

	template <typename M>
	void checkMatrixNorm1Function(const M& m, typename M::SizeType col)
	{
		using namespace CDPL;
		using namespace Math;

		typedef typename M::ValueType ValueType;
		typedef typename M::SizeType SizeType;
		typedef typename TypeTraits<ValueType>::RealType RealType;

		RealType exp_val = RealType();

		for (SizeType i = 0; i < m.getSize1(); i++)
			exp_val += TypeTraits<ValueType>::norm1(m(i, col));

		BOOST_CHECK_EQUAL(norm1(m), exp_val);
	}

	template <typename M>
	void checkMatrixNormFrobFunction(const M& m)
	{
		using namespace CDPL;
		using namespace Math;

		typedef typename M::ValueType ValueType;
		typedef typename M::SizeType SizeType;
		typedef typename TypeTraits<ValueType>::RealType RealType;

		RealType exp_val = RealType();

		for (SizeType i = 0; i < m.getSize1(); i++) {
			for (SizeType j = 0; j < m.getSize2(); j++) {
				RealType t = TypeTraits<ValueType>::norm2(m(i, j));
				exp_val += t * t;
			}
		}

		exp_val = TypeTraits<RealType>::sqrt(exp_val);

		BOOST_CHECK_EQUAL(normFrob(m), exp_val);
	}

	template <typename M>
	void checkMatrixNormInfFunction(const M& m, typename M::SizeType row)
	{
		using namespace CDPL;
		using namespace Math;

		typedef typename M::ValueType ValueType;
		typedef typename M::SizeType SizeType;
		typedef typename TypeTraits<ValueType>::RealType RealType;

		RealType exp_val = RealType();

		for (SizeType i = 0; i < m.getSize2(); i++)
			exp_val += TypeTraits<ValueType>::normInf(m(row, i));

		BOOST_CHECK_EQUAL(normInf(m), exp_val);
	}
	
	template <typename M>
	void checkMatrixConjFunction(const M& m)
	{
		using namespace CDPL;
		using namespace Math;

		typedef typename M::ValueType ValueType;
		typedef typename M::SizeType SizeType;

		BOOST_CHECK_EQUAL(conj(m).getSize1(), m.getSize1());
		BOOST_CHECK_EQUAL(conj(m).getSize2(), m.getSize2());

		for (SizeType i = 0; i < m.getSize1(); i++) 
			for (SizeType j = 0; j < m.getSize2(); j++) 
				BOOST_CHECK_EQUAL(conj(m)(i, j), TypeTraits<ValueType>::conj(m(i, j)));

		BOOST_CHECK_THROW(conj(m)(m.getSize1(), 0), Base::IndexError);
		BOOST_CHECK_THROW(conj(m)(0, m.getSize2()), Base::IndexError);
	}

	template <typename M>
	void checkMatrixRealFunction(const M& m)
	{
		using namespace CDPL;
		using namespace Math;

		typedef typename M::ValueType ValueType;
		typedef typename M::SizeType SizeType;

		BOOST_CHECK_EQUAL(real(m).getSize1(), m.getSize1());
		BOOST_CHECK_EQUAL(real(m).getSize2(), m.getSize2());

		for (SizeType i = 0; i < m.getSize1(); i++) 
			for (SizeType j = 0; j < m.getSize2(); j++) 
				BOOST_CHECK_EQUAL(real(m)(i, j), TypeTraits<ValueType>::real(m(i, j)));

		BOOST_CHECK_THROW(real(m)(m.getSize1(), 0), Base::IndexError);
		BOOST_CHECK_THROW(real(m)(0, m.getSize2()), Base::IndexError);
	}

	template <typename M>
	void checkMatrixImagFunction(const M& m)
	{
		using namespace CDPL;
		using namespace Math;

		typedef typename M::ValueType ValueType;
		typedef typename M::SizeType SizeType;

		BOOST_CHECK_EQUAL(imag(m).getSize1(), m.getSize1());
		BOOST_CHECK_EQUAL(imag(m).getSize2(), m.getSize2());

		for (SizeType i = 0; i < m.getSize1(); i++) 
			for (SizeType j = 0; j < m.getSize2(); j++) 
				BOOST_CHECK_EQUAL(imag(m)(i, j), TypeTraits<ValueType>::imag(m(i, j)));

		BOOST_CHECK_THROW(imag(m)(m.getSize1(), 0), Base::IndexError);
		BOOST_CHECK_THROW(imag(m)(0, m.getSize2()), Base::IndexError);
	}

	template <typename M>
	void checkMatrixHermFunction(const M& m)
	{
		using namespace CDPL;
		using namespace Math;

		typedef typename M::ValueType ValueType;
		typedef typename M::SizeType SizeType;

		BOOST_CHECK_EQUAL(herm(m).getSize1(), m.getSize1());
		BOOST_CHECK_EQUAL(herm(m).getSize2(), m.getSize2());

		for (SizeType i = 0; i < m.getSize1(); i++) 
			for (SizeType j = 0; j < m.getSize2(); j++) 
				BOOST_CHECK_EQUAL(herm(m)(i, j), TypeTraits<ValueType>::conj(m(i, j)));

		BOOST_CHECK_THROW(herm(m)(m.getSize1(), 0), Base::IndexError);
		BOOST_CHECK_THROW(herm(m)(0, m.getSize2()), Base::IndexError);
	}

	template <typename M>
	void checkMatrixPlusOperator(const M& m)
	{
		using namespace CDPL;

		typedef typename M::SizeType SizeType;

		BOOST_CHECK_EQUAL(operator+(m).getSize1(), m.getSize1());
		BOOST_CHECK_EQUAL(operator+(m).getSize2(), m.getSize2());

		BOOST_CHECK_EQUAL((+m).getSize1(), m.getSize1());
		BOOST_CHECK_EQUAL((+m).getSize2(), m.getSize2());

		for (SizeType i = 0; i < m.getSize1(); i++) 
			for (SizeType j = 0; j < m.getSize2(); j++) {
				BOOST_CHECK_EQUAL(operator+(m)(i, j), m(i, j));
				BOOST_CHECK_EQUAL((+m)(i, j), m(i, j));
			}

		BOOST_CHECK_THROW(operator+(m)(m.getSize1(), 0), Base::IndexError);
		BOOST_CHECK_THROW(operator+(m)(0, m.getSize2()), Base::IndexError);

		BOOST_CHECK_THROW((+m)(m.getSize1(), 0), Base::IndexError);
		BOOST_CHECK_THROW((+m)(0, m.getSize2()), Base::IndexError);
	}

	template <typename M>
	void checkMatrixMinusOperator(const M& m)
	{
		using namespace CDPL;

		typedef typename M::SizeType SizeType;

		BOOST_CHECK_EQUAL(operator-(m).getSize1(), m.getSize1());
		BOOST_CHECK_EQUAL(operator-(m).getSize2(), m.getSize2());

		BOOST_CHECK_EQUAL((-m).getSize1(), m.getSize1());
		BOOST_CHECK_EQUAL((-m).getSize2(), m.getSize2());

		for (SizeType i = 0; i < m.getSize1(); i++) 
			for (SizeType j = 0; j < m.getSize2(); j++) {
				BOOST_CHECK_EQUAL(operator-(m)(i, j), -m(i, j));
				BOOST_CHECK_EQUAL((-m)(i, j), -m(i, j));
			}

		BOOST_CHECK_THROW(operator-(m)(m.getSize1(), 0), Base::IndexError);
		BOOST_CHECK_THROW(operator-(m)(0, m.getSize2()), Base::IndexError);

		BOOST_CHECK_THROW((-m)(m.getSize1(), 0), Base::IndexError);
		BOOST_CHECK_THROW((-m)(0, m.getSize2()), Base::IndexError);
	}

	template <typename V>
	void checkVectorDiagFunction(const V& v)
	{
		using namespace CDPL;

		typedef typename V::SizeType SizeType;
		typedef typename V::ValueType ResultType;

		for (SizeType i = 0; i < v.getSize() + 3; i++) {
			for (SizeType j = 0; j < v.getSize() + 2; j++) {
				if (i != j)
					BOOST_CHECK_EQUAL(diag(v)(i, j), ResultType());
				else if (i >= v.getSize()) {
					BOOST_CHECK_THROW(diag(v)(i, j), Base::IndexError);
				} else 
				 	BOOST_CHECK_EQUAL(diag(v)(i, j), v(i));
			}
		}
	}

	template <typename V>
	void checkVectorCrossFunction(const V& v)
	{
		//                       |  0  -a3  a2 |
		// cross([a1, a2, a3]) = |  a3  0  -a1 |
		//                       | -a2  a1  0  |
		
		typedef typename V::ValueType ResultType;
		typedef typename V::SizeType SizeType;

		for (SizeType i = 0; i < 5; i++) {
			for (SizeType j = 0; j < 6; j++) {
				ResultType val = cross(v)(i, j);
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

	template <typename M, typename V>
	void checkMatrixVectorProdFunction(const M& m, const V& v)
	{
		using namespace CDPL;
		using namespace Math;

		typedef typename CommonType<typename M::ValueType, typename V::ValueType>::Type ResultType; 
		typedef typename CommonType<typename M::SizeType, typename V::SizeType>::Type SizeType; 

		Vector<ResultType> res_v;
		prod(m, v, res_v);

		BOOST_CHECK_EQUAL(res_v.getSize(), m.getSize1());
		BOOST_CHECK_EQUAL(prod(m, v).getSize(), m.getSize1());

		for (SizeType i = 0; i < m.getSize1(); i++) {
			ResultType val = prod(m, v)(i);

			BOOST_CHECK_EQUAL(res_v(i), val);

			ResultType exp_val = ResultType();

			for (SizeType j = 0; j < v.getSize(); j++)
				exp_val += m(i, j) * v(j);

			BOOST_CHECK_EQUAL(val, exp_val);
		}

		if (m.getSize2() > 0)
			BOOST_CHECK_THROW(prod(m, v)(m.getSize1()), Base::IndexError);
	}

	template <typename M, typename V>
	void checkMatrixVectorMultiplication(const M& m, const V& v)
	{
		using namespace CDPL;
		using namespace Math;

		typedef typename CommonType<typename M::ValueType, typename V::ValueType>::Type ResultType; 
		typedef typename CommonType<typename M::SizeType, typename V::SizeType>::Type SizeType; 

		BOOST_CHECK_EQUAL(operator*(m, v).getSize(), m.getSize1());
		BOOST_CHECK_EQUAL((m * v).getSize(), m.getSize1());

		for (SizeType i = 0; i < m.getSize1(); i++) {
			ResultType val = (m * v)(i);

			BOOST_CHECK_EQUAL(operator*(m, v)(i), val);

			ResultType exp_val = ResultType();

			for (SizeType j = 0; j < v.getSize(); j++)
				exp_val += m(i, j) * v(j);

			BOOST_CHECK_EQUAL(val, exp_val);
		}

		if (m.getSize2() > 0) {
			BOOST_CHECK_THROW((m * v)(m.getSize1()), Base::IndexError);
			BOOST_CHECK_THROW(operator*(m, v)(m.getSize1()), Base::IndexError);
		}
	}

	template <typename V, typename M>
	void checkVectorMatrixProdFunction(const V& v, const M& m)
	{
		using namespace CDPL;
		using namespace Math;

		typedef typename CommonType<typename M::ValueType, typename V::ValueType>::Type ResultType; 
		typedef typename CommonType<typename M::SizeType, typename V::SizeType>::Type SizeType; 
	
		Vector<ResultType> res_v;
		prod(v, m, res_v);

		BOOST_CHECK_EQUAL(res_v.getSize(), m.getSize2());
		BOOST_CHECK_EQUAL(prod(v, m).getSize(), m.getSize2());

		for (SizeType i = 0; i < m.getSize2(); i++) {
			ResultType val = prod(v, m)(i);

			BOOST_CHECK_EQUAL(res_v(i), val);

			ResultType exp_val = ResultType();

			for (SizeType j = 0; j < v.getSize(); j++)
				exp_val += m(j, i) * v(j);

			BOOST_CHECK_EQUAL(val, exp_val);
		}

		if (m.getSize1() > 0)
			BOOST_CHECK_THROW(prod(v, m)(m.getSize2()), Base::IndexError);
	}
	
	template <typename V, typename M>
	void checkVectorMatrixMultiplication(const V& v, const M& m)
	{
		using namespace CDPL;
		using namespace Math;

		typedef typename CommonType<typename M::ValueType, typename V::ValueType>::Type ResultType; 
		typedef typename CommonType<typename M::SizeType, typename V::SizeType>::Type SizeType; 

		BOOST_CHECK_EQUAL(operator*(v, m).getSize(), m.getSize2());
		BOOST_CHECK_EQUAL((v * m).getSize(), m.getSize2());

		for (SizeType i = 0; i < m.getSize2(); i++) {
			ResultType val = (v * m)(i);

			BOOST_CHECK_EQUAL(operator*(v, m)(i), val);

			ResultType exp_val = ResultType();

			for (SizeType j = 0; j < v.getSize(); j++)
				exp_val += m(j, i) * v(j);

			BOOST_CHECK_EQUAL(val, exp_val);
		}

		if (m.getSize1() > 0) {
			BOOST_CHECK_THROW((v * m)(m.getSize2()), Base::IndexError);
			BOOST_CHECK_THROW(operator*(v, m)(m.getSize2()), Base::IndexError);
		}
	}

	template <typename M1, typename M2>
	void checkMatrixProdFunction(const M1& m1, const M2& m2)
	{
		using namespace CDPL;
		using namespace Math;

		typedef typename CommonType<typename M1::ValueType, typename M2::ValueType>::Type ResultType; 
		typedef typename CommonType<typename M1::SizeType, typename M2::SizeType>::Type SizeType; 

		Matrix<ResultType> res_m;
		prod(m1, m2, res_m);
	
		BOOST_CHECK_EQUAL(res_m.getSize1(), m1.getSize1());
		BOOST_CHECK_EQUAL(res_m.getSize2(), m2.getSize2());

		BOOST_CHECK_EQUAL(prod(m1, m2).getSize1(), m1.getSize1());
		BOOST_CHECK_EQUAL(prod(m1, m2).getSize2(), m2.getSize2());

		for (SizeType i = 0; i < m1.getSize1(); i++) {
			for (SizeType j = 0; j < m2.getSize2(); j++) {
				ResultType val = prod(m1, m2)(i, j);

				BOOST_CHECK_EQUAL(res_m(i, j), val);

				ResultType exp_val = ResultType();

				for (SizeType k = 0; k < m1.getSize2(); k++)
					exp_val += m1(i, k) * m2(k, j);

				BOOST_CHECK_EQUAL(val, exp_val);
			}
		}

		if (m1.getSize2() > 0) {
			BOOST_CHECK_THROW(prod(m1, m2)(m1.getSize1(), 0), Base::IndexError);
			BOOST_CHECK_THROW(prod(m1, m2)(0, m2.getSize2()), Base::IndexError);
		}
	}

	template <typename M1, typename M2>
	void checkMatrixMultiplication(const M1& m1, const M2& m2)
	{
		using namespace CDPL;
		using namespace Math;

		typedef typename CommonType<typename M1::ValueType, typename M2::ValueType>::Type ResultType; 
		typedef typename CommonType<typename M1::SizeType, typename M2::SizeType>::Type SizeType; 

		BOOST_CHECK_EQUAL(operator*(m1, m2).getSize1(), m1.getSize1());
		BOOST_CHECK_EQUAL(operator*(m1, m2).getSize2(), m2.getSize2());

		BOOST_CHECK_EQUAL((m1 * m2).getSize1(), m1.getSize1());
		BOOST_CHECK_EQUAL((m1 * m2).getSize2(), m2.getSize2());

		for (SizeType i = 0; i < m1.getSize1(); i++) {
			for (SizeType j = 0; j < m2.getSize2(); j++) {
				ResultType val = (m1 * m2)(i, j);

				BOOST_CHECK_EQUAL(operator*(m1, m2)(i, j), val);

				ResultType exp_val = ResultType();

				for (SizeType k = 0; k < m1.getSize2(); k++)
					exp_val += m1(i, k) * m2(k, j);

				BOOST_CHECK_EQUAL(val, exp_val);
			}
		}

		if (m1.getSize2() > 0) {
			BOOST_CHECK_THROW((m1 * m2)(m1.getSize1(), 0), Base::IndexError);
			BOOST_CHECK_THROW((m1 * m2)(0, m2.getSize2()), Base::IndexError);
	
			BOOST_CHECK_THROW(operator*(m1, m2)(m1.getSize1(), 0), Base::IndexError);
			BOOST_CHECK_THROW(operator*(m1, m2)(0, m2.getSize2()), Base::IndexError);
		}
	}

	template <typename M1, typename M2>
	void checkMatrixAddition(const M1& m1, const M2& m2)
	{
		using namespace CDPL;
		using namespace Math;

		typedef typename CommonType<typename M1::SizeType, typename M2::SizeType>::Type SizeType; 

		BOOST_CHECK_EQUAL(operator+(m1, m2).getSize1(), (m1 + m2).getSize1());
		BOOST_CHECK_EQUAL(operator+(m1, m2).getSize2(), (m1 + m2).getSize2());

		BOOST_CHECK_EQUAL(operator+(m2, m1).getSize1(), (m2 + m1).getSize1());
		BOOST_CHECK_EQUAL(operator+(m2, m1).getSize2(), (m2 + m1).getSize2());

		BOOST_CHECK_EQUAL((m1 + m2).getSize1(), m1.getSize1());
		BOOST_CHECK_EQUAL((m1 + m2).getSize2(), m1.getSize2());

		BOOST_CHECK_EQUAL((m2 + m1).getSize1(), m1.getSize1());
		BOOST_CHECK_EQUAL((m2 + m1).getSize2(), m1.getSize2());

		BOOST_CHECK_EQUAL(m1.getSize1(), m2.getSize1());
		BOOST_CHECK_EQUAL(m1.getSize2(), m2.getSize2());

		for (SizeType i = 0; i < m1.getSize1(); i++) {
			for (SizeType j = 0; j < m1.getSize2(); j++) {
				BOOST_CHECK_EQUAL(operator+(m1, m2)(i, j), (m1 + m2)(i, j));
				BOOST_CHECK_EQUAL(operator+(m1, m2)(i, j), m1(i, j) + m2(i, j));

				BOOST_CHECK_EQUAL(operator+(m2, m1)(i, j), (m2 + m1)(i, j));
				BOOST_CHECK_EQUAL(operator+(m2, m1)(i, j), m1(i, j) + m2(i, j));
			}
		}

		BOOST_CHECK_THROW((m1 + m2)(m1.getSize1(), 0), Base::IndexError);
		BOOST_CHECK_THROW((m1 + m2)(0, m1.getSize2()), Base::IndexError);
	
		BOOST_CHECK_THROW(operator+(m1, m2)(m1.getSize1(), 0), Base::IndexError);
		BOOST_CHECK_THROW(operator+(m1, m2)(0, m1.getSize2()), Base::IndexError);

		BOOST_CHECK_THROW((m2 + m1)(m1.getSize1(), 0), Base::IndexError);
		BOOST_CHECK_THROW((m2 + m1)(0, m1.getSize2()), Base::IndexError);
	
		BOOST_CHECK_THROW(operator+(m2, m1)(m1.getSize1(), 0), Base::IndexError);
		BOOST_CHECK_THROW(operator+(m2, m1)(0, m1.getSize2()), Base::IndexError);
	}

	template <typename M1, typename M2>
	void checkMatrixSubtraction(const M1& m1, const M2& m2)
	{
		using namespace CDPL;
		using namespace Math;

		typedef typename CommonType<typename M1::SizeType, typename M2::SizeType>::Type SizeType; 

		BOOST_CHECK_EQUAL(operator-(m1, m2).getSize1(), (m1 - m2).getSize1());
		BOOST_CHECK_EQUAL(operator-(m1, m2).getSize2(), (m1 - m2).getSize2());

		BOOST_CHECK_EQUAL(operator-(m2, m1).getSize1(), (m2 - m1).getSize1());
		BOOST_CHECK_EQUAL(operator-(m2, m1).getSize2(), (m2 - m1).getSize2());

		BOOST_CHECK_EQUAL((m1 - m2).getSize1(), m1.getSize1());
		BOOST_CHECK_EQUAL((m1 - m2).getSize2(), m1.getSize2());

		BOOST_CHECK_EQUAL((m2 - m1).getSize1(), m1.getSize1());
		BOOST_CHECK_EQUAL((m2 - m1).getSize2(), m1.getSize2());

		BOOST_CHECK_EQUAL(m1.getSize1(), m2.getSize1());
		BOOST_CHECK_EQUAL(m1.getSize2(), m2.getSize2());

		for (SizeType i = 0; i < m1.getSize1(); i++) {
			for (SizeType j = 0; j < m1.getSize2(); j++) {
				BOOST_CHECK_EQUAL(operator-(m1, m2)(i, j), (m1 - m2)(i, j));
				BOOST_CHECK_EQUAL(operator-(m1, m2)(i, j), m1(i, j) - m2(i, j));

				BOOST_CHECK_EQUAL(operator-(m2, m1)(i, j), (m2 - m1)(i, j));
				BOOST_CHECK_EQUAL(operator-(m2, m1)(i, j), -(m1(i, j) - m2(i, j)));
			}
		}

		BOOST_CHECK_THROW((m1 - m2)(m1.getSize1(), 0), Base::IndexError);
		BOOST_CHECK_THROW((m1 - m2)(0, m1.getSize2()), Base::IndexError);
	
		BOOST_CHECK_THROW(operator-(m1, m2)(m1.getSize1(), 0), Base::IndexError);
		BOOST_CHECK_THROW(operator-(m1, m2)(0, m1.getSize2()), Base::IndexError);

		BOOST_CHECK_THROW((m2 - m1)(m1.getSize1(), 0), Base::IndexError);
		BOOST_CHECK_THROW((m2 - m1)(0, m1.getSize2()), Base::IndexError);
	
		BOOST_CHECK_THROW(operator-(m2, m1)(m1.getSize1(), 0), Base::IndexError);
		BOOST_CHECK_THROW(operator-(m2, m1)(0, m1.getSize2()), Base::IndexError);
	}

	template <typename M1, typename M2>
	void checkMatrixElemProdFunction(const M1& m1, const M2& m2)
	{
		using namespace CDPL;
		using namespace Math;

		typedef typename CommonType<typename M1::SizeType, typename M2::SizeType>::Type SizeType; 

		BOOST_CHECK_EQUAL(elemProd(m1, m2).getSize1(), m1.getSize1());
		BOOST_CHECK_EQUAL(elemProd(m1, m2).getSize2(), m1.getSize2());

		BOOST_CHECK_EQUAL(elemProd(m2, m1).getSize1(), m1.getSize1());
		BOOST_CHECK_EQUAL(elemProd(m2, m1).getSize2(), m1.getSize2());

		BOOST_CHECK_EQUAL(m1.getSize1(), m2.getSize1());
		BOOST_CHECK_EQUAL(m1.getSize2(), m2.getSize2());

		for (SizeType i = 0; i < m1.getSize1(); i++) {
			for (SizeType j = 0; j < m1.getSize2(); j++) {
				BOOST_CHECK_EQUAL(elemProd(m1, m2)(i, j), m1(i, j) * m2(i, j));
				BOOST_CHECK_EQUAL(elemProd(m2, m1)(i, j), m1(i, j) * m2(i, j));
			}
		}
		
		BOOST_CHECK_THROW(elemProd(m1, m2)(m1.getSize1(), 0), Base::IndexError);
		BOOST_CHECK_THROW(elemProd(m1, m2)(0, m1.getSize2()), Base::IndexError);

		BOOST_CHECK_THROW(elemProd(m2, m1)(m1.getSize1(), 0), Base::IndexError);
		BOOST_CHECK_THROW(elemProd(m2, m1)(0, m1.getSize2()), Base::IndexError);
	}

	template <typename M1, typename M2>
	void checkMatrixElemDivFunction(const M1& m1, const M2& m2)
	{
		using namespace CDPL;
		using namespace Math;

		typedef typename CommonType<typename M1::SizeType, typename M2::SizeType>::Type SizeType; 

		BOOST_CHECK_EQUAL(elemDiv(m1, m2).getSize1(), m1.getSize1());
		BOOST_CHECK_EQUAL(elemDiv(m1, m2).getSize2(), m1.getSize2());

		BOOST_CHECK_EQUAL(m1.getSize1(), m2.getSize1());
		BOOST_CHECK_EQUAL(m1.getSize2(), m2.getSize2());

		for (SizeType i = 0; i < m1.getSize1(); i++) 
			for (SizeType j = 0; j < m1.getSize2(); j++) 
				BOOST_CHECK_EQUAL(elemDiv(m1, m2)(i, j), m1(i, j) / m2(i, j));
		
		BOOST_CHECK_THROW(elemDiv(m1, m2)(m1.getSize1(), 0), Base::IndexError);
		BOOST_CHECK_THROW(elemDiv(m1, m2)(0, m1.getSize2()), Base::IndexError);
	}

	template <typename M, typename T>
	void checkMatrixScalarMultiplication(const M& m, const T& t)
	{
		using namespace CDPL;

		typedef typename M::SizeType SizeType; 
	
		BOOST_CHECK_EQUAL(operator*(m, t).getSize1(), m.getSize1());
		BOOST_CHECK_EQUAL(operator*(m, t).getSize2(), m.getSize2());

		BOOST_CHECK_EQUAL((m * t).getSize1(), m.getSize1());
		BOOST_CHECK_EQUAL((m * t).getSize2(), m.getSize2());

		for (SizeType i = 0; i < m.getSize1(); i++) {
			for (SizeType j = 0; j < m.getSize2(); j++) {
				BOOST_CHECK_EQUAL(operator*(m, t)(i, j), m(i, j) * t);
				BOOST_CHECK_EQUAL((m * t)(i, j), m(i, j) * t);
			}
		}

		BOOST_CHECK_THROW((m * t)(m.getSize1(), 0), Base::IndexError);
		BOOST_CHECK_THROW((m * t)(0, m.getSize2()), Base::IndexError);
	
		BOOST_CHECK_THROW(operator*(m, t)(m.getSize1(), 0), Base::IndexError);
		BOOST_CHECK_THROW(operator*(m, t)(0, m.getSize2()), Base::IndexError);
	}

	template <typename T, typename M>
	void checkScalarMatrixMultiplication(const T& t, const M& m)
	{
		using namespace CDPL;

		typedef typename M::SizeType SizeType; 
	
		BOOST_CHECK_EQUAL(operator*(t, m).getSize1(), m.getSize1());
		BOOST_CHECK_EQUAL(operator*(t, m).getSize2(), m.getSize2());

		BOOST_CHECK_EQUAL((t * m).getSize1(), m.getSize1());
		BOOST_CHECK_EQUAL((t * m).getSize2(), m.getSize2());

		for (SizeType i = 0; i < m.getSize1(); i++) {
			for (SizeType j = 0; j < m.getSize2(); j++) {
				BOOST_CHECK_EQUAL(operator*(t, m)(i, j), t * m(i, j));
				BOOST_CHECK_EQUAL((t * m)(i, j), t * m(i, j));
			}
		}

		BOOST_CHECK_THROW((t * m)(m.getSize1(), 0), Base::IndexError);
		BOOST_CHECK_THROW((t * m)(0, m.getSize2()), Base::IndexError);
	
		BOOST_CHECK_THROW(operator*(t, m)(m.getSize1(), 0), Base::IndexError);
		BOOST_CHECK_THROW(operator*(t, m)(0, m.getSize2()), Base::IndexError);
	}

	template <typename M, typename T>
	void checkMatrixScalarDivision(const M& m, const T& t)
	{
		using namespace CDPL;

		typedef typename M::SizeType SizeType; 
	
		BOOST_CHECK_EQUAL(operator/(m, t).getSize1(), m.getSize1());
		BOOST_CHECK_EQUAL(operator/(m, t).getSize2(), m.getSize2());

		BOOST_CHECK_EQUAL((m / t).getSize1(), m.getSize1());
		BOOST_CHECK_EQUAL((m / t).getSize2(), m.getSize2());

		for (SizeType i = 0; i < m.getSize1(); i++) {
			for (SizeType j = 0; j < m.getSize2(); j++) {
				BOOST_CHECK_EQUAL(operator/(m, t)(i, j), m(i, j) / t);
				BOOST_CHECK_EQUAL((m / t)(i, j), m(i, j) / t);
			}
		}

		BOOST_CHECK_THROW((m / t)(m.getSize1(), 0), Base::IndexError);
		BOOST_CHECK_THROW((m / t)(0, m.getSize2()), Base::IndexError);
	
		BOOST_CHECK_THROW(operator/(m, t)(m.getSize1(), 0), Base::IndexError);
		BOOST_CHECK_THROW(operator/(m, t)(0, m.getSize2()), Base::IndexError);
	}

	template <typename V1, typename V2>
	void checkVectorOuterProdFunction(const V1& v1, const V2& v2)
	{
		using namespace CDPL;
		using namespace Math;

		typedef typename CommonType<typename V1::SizeType, typename V2::SizeType>::Type SizeType; 

		BOOST_CHECK_EQUAL(outerProd(v1, v2).getSize1(), v1.getSize());
		BOOST_CHECK_EQUAL(outerProd(v1, v2).getSize2(), v2.getSize());

		BOOST_CHECK_EQUAL(outerProd(v2, v1).getSize1(), v2.getSize());
		BOOST_CHECK_EQUAL(outerProd(v2, v1).getSize2(), v1.getSize());

		for (SizeType i = 0; i < v1.getSize() + 3; i++) {
			for (SizeType j = 0; j < v2.getSize() + 2; j++) {
				if (i >= v1.getSize() || j >= v2.getSize()) {
					BOOST_CHECK_THROW(outerProd(v1, v2)(i, j), Base::IndexError);
					BOOST_CHECK_THROW(outerProd(v2, v1)(j, i), Base::IndexError);

				} else {
				 	BOOST_CHECK_EQUAL(outerProd(v1, v2)(i, j), v1(i) * v2(j));
				 	BOOST_CHECK_EQUAL(outerProd(v2, v1)(j, i), v1(i) * v2(j));
				}
			}
		}
	}

	template <typename MT, typename M>
	void checkTransposedMatrix(M& m, MT& m_trans)
	{
		using namespace CDPL;

		typedef typename M::SizeType SizeType; 

		BOOST_CHECK_EQUAL(m_trans.getSize1(), m.getSize2());
		BOOST_CHECK_EQUAL(m_trans.getSize2(), m.getSize1());
		BOOST_CHECK_EQUAL(m_trans.getMaxSize(), m.getMaxSize());
		BOOST_CHECK_EQUAL(m_trans.isEmpty(), m.isEmpty());

		BOOST_CHECK(&m_trans.getData().getData() == &m);
		BOOST_CHECK(&const_cast<const MT&>(m_trans).getData().getData() == &m);

		for (SizeType i = 0; i < m.getSize1() + 3; i++)
			for (SizeType j = 0; j < m.getSize2() + 4; j++) {
				if (i >= m.getSize1() || j >= m.getSize2()) { 
					BOOST_CHECK_THROW(m_trans(j, i), Base::IndexError);
					BOOST_CHECK_THROW(static_cast<const MT&>(m_trans)(j, i), Base::IndexError);

				} else {
					BOOST_CHECK_EQUAL(m(i, j), m_trans(j, i));
					BOOST_CHECK_EQUAL(m(i, j), static_cast<const MT&>(m_trans)(j, i));
			
					BOOST_CHECK_EQUAL(m_trans.getData()(i, j), m_trans(j, i));
					BOOST_CHECK_EQUAL(static_cast<const MT&>(m_trans).getData()(i, j), m_trans(j, i));
				}
			}
	}

	template <typename ResType, typename ArgType>
	struct MatrixUnaryTestFunctor
	{
		
		typedef ResType ResultType;
		typedef ArgType ArgumentType;

		static ResultType apply(ArgumentType arg) {
			return (arg * arg);
		}
	};

	template <typename ResType>
	struct VectorMatrixUnaryTestFunctor
	{
		
		typedef ResType ResultType;
	
		template <typename E>
		static ResultType apply(const CDPL::Math::VectorExpression<E>& v, 
								typename E::SizeType i, typename E::SizeType j) {

			return (v()(i) * v()(j));
		}
	};

	template <typename ResType, typename ArgType1, typename ArgType2>
	struct MatrixBinary1TestFunctor
	{
		
		typedef ResType ResultType;
		typedef ArgType1 ArgumentType1;
		typedef ArgType2 ArgumentType2;

		static ResultType apply(ArgumentType1 arg1, ArgumentType2 arg2) {
			return (arg1 * arg2 + arg1 / 2) ;
		}
	};

	template <typename ResType>
	struct MatrixBinary2TestFunctor
	{
		
		typedef ResType ResultType;
	
		template <typename E1, typename E2>
		static ResultType apply(const CDPL::Math::MatrixExpression<E1>& m1, 
								const CDPL::Math::MatrixExpression<E2>& m2, 
								typename CDPL::Math::CommonType<typename E1::SizeType, typename E2::SizeType>::Type i,
								typename CDPL::Math::CommonType<typename E1::SizeType, typename E2::SizeType>::Type j) {

			return (m1()(i, j) * m2()(i, j) - i * j);
		}
	};

	template <typename ResType, typename ArgType1, typename ArgType2>
	struct VectorMatrixBinaryTestFunctor
	{
		
		typedef ResType ResultType;
		typedef ArgType1 ArgumentType1;
		typedef ArgType2 ArgumentType2;

		static ResultType apply(ArgumentType1 arg1, ArgumentType2 arg2) {
			return (arg1 * arg1 - arg2 * arg2) ;
		}
	};

	template <typename ResType>
	struct Matrix1VectorBinaryTestFunctor
	{
		
		typedef ResType ResultType;
	
		template <typename E1, typename E2>
		static ResultType apply(const CDPL::Math::MatrixExpression<E1>& m, 
								const CDPL::Math::VectorExpression<E2>& v, 
								typename CDPL::Math::CommonType<typename E1::SizeType, typename E2::SizeType>::Type i) {

			typedef typename CDPL::Math::CommonType<typename E1::SizeType, typename E2::SizeType>::Type SizeType;

			ResultType r = ResultType();

			for (SizeType j = 0; j < v().getSize(); j++)
				r += m()(i, j) * m()(i, j) - v()(j);

			return r;
		}
	};

	template <typename ResType>
	struct Matrix2VectorBinaryTestFunctor
	{
		
		typedef ResType ResultType;
	
		template <typename E1, typename E2>
		static ResultType apply(const CDPL::Math::VectorExpression<E1>& v, 
								const CDPL::Math::MatrixExpression<E2>& m, 								
								typename CDPL::Math::CommonType<typename E1::SizeType, typename E2::SizeType>::Type i) {

			typedef typename CDPL::Math::CommonType<typename E1::SizeType, typename E2::SizeType>::Type SizeType;

			ResultType r = ResultType();

			for (SizeType j = 0; j < v().getSize(); j++)
				r += m()(j, i) * m()(j, i) + v()(j) * v()(j);

			return r;
		}
	};

	template <typename ResType, typename ArgType1, typename ArgType2>
	struct Scalar1MatrixBinaryTestFunctor
	{
		
		typedef ResType ResultType;
		typedef ArgType1 ArgumentType1;
		typedef ArgType2 ArgumentType2;

		static ResultType apply(ArgumentType1 arg1, ArgumentType2 arg2) {
			return (arg1 * arg1 - arg2 * arg1 / 2) ;
		}
	};

	template <typename ResType, typename ArgType1, typename ArgType2>
	struct Scalar2MatrixBinaryTestFunctor
	{
		
		typedef ResType ResultType;
		typedef ArgType1 ArgumentType1;
		typedef ArgType2 ArgumentType2;

		static ResultType apply(ArgumentType1 arg1, ArgumentType2 arg2) {
			return (arg1 * arg1 * 2 + arg2 * arg1 / 2) ;
		}
	};
}


BOOST_AUTO_TEST_CASE(MatrixUnaryTest)
{
	using namespace CDPL;
	using namespace Math;

	BOOST_CHECK(typeid(MatrixUnary<Matrix<double>, MatrixUnaryTestFunctor<long, float> >::ValueType) ==
					  typeid(const long));
	BOOST_CHECK(typeid(MatrixUnary<Matrix<double>, MatrixUnaryTestFunctor<long, char> >::ConstReference) ==
					  typeid(const long));
	BOOST_CHECK(typeid(MatrixUnary<Matrix<double>, MatrixUnaryTestFunctor<long, int> >::Reference) ==
					  typeid(const long));
	BOOST_CHECK(typeid(MatrixUnary<Matrix<float>, MatrixUnaryTestFunctor<long double, double> >::ValueType) ==
					  typeid(const long double));
	BOOST_CHECK(typeid(MatrixUnary<Matrix<float>, MatrixUnaryTestFunctor<long double, int> >::ConstReference) ==
					  typeid(const long double));
	BOOST_CHECK(typeid(MatrixUnary<Matrix<float>, MatrixUnaryTestFunctor<long double, long> >::Reference) ==
					  typeid(const long double));

	BOOST_CHECK(typeid(MatrixUnary<Matrix<float>, MatrixUnaryTestFunctor<double, long> >::SizeType) ==
					  typeid(Matrix<float>::SizeType));
	BOOST_CHECK(typeid(MatrixUnary<Matrix<int>, MatrixUnaryTestFunctor<double, long> >::DifferenceType) ==
					  typeid(Matrix<int>::DifferenceType));

	// ----------

	typedef MatrixUnaryTestFunctor<double, const int&> Functor;
	typedef Matrix<int>::SizeType SizeType;

	Matrix<int> m(3, 5);

	for (SizeType i = 0; i < m.getSize1(); i++)
		for (SizeType j = 0; j < m.getSize2(); j++)
			m(i, j) = i * m.getSize2() + j;

	MatrixUnary<Matrix<int>, Functor> m_un(m);

	BOOST_CHECK_EQUAL(m.getSize1(), m_un.getSize1());
	BOOST_CHECK_EQUAL(m.getSize2(), m_un.getSize2());
	
	for (SizeType i = 0; i < m.getSize1(); i++)
		for (SizeType j = 0; j < m.getSize2(); j++)
			BOOST_CHECK_EQUAL(m_un(i, j), Functor::apply(m(i, j)));

	BOOST_CHECK_THROW(m_un(m.getSize1(), 0), Base::IndexError);
	BOOST_CHECK_THROW(m_un(0, m.getSize2()), Base::IndexError);
	BOOST_CHECK_THROW(m_un(m.getSize1(), m.getSize2()), Base::IndexError);
}

BOOST_AUTO_TEST_CASE(VectorMatrixUnaryTest)
{
	using namespace CDPL;
	using namespace Math;

	BOOST_CHECK(typeid(VectorMatrixUnary<Vector<double>, VectorMatrixUnaryTestFunctor<long> >::ValueType) ==
					  typeid(const long));
	BOOST_CHECK(typeid(VectorMatrixUnary<Vector<short>, VectorMatrixUnaryTestFunctor<long> >::ConstReference) ==
					  typeid(const long));
	BOOST_CHECK(typeid(VectorMatrixUnary<Vector<int>, VectorMatrixUnaryTestFunctor<long> >::Reference) ==
					  typeid(const long));
	BOOST_CHECK(typeid(VectorMatrixUnary<Vector<float>, VectorMatrixUnaryTestFunctor<long double> >::ValueType) ==
					  typeid(const long double));
	BOOST_CHECK(typeid(VectorMatrixUnary<Vector<double>, VectorMatrixUnaryTestFunctor<long double> >::ConstReference) ==
					  typeid(const long double));
	BOOST_CHECK(typeid(VectorMatrixUnary<Vector<long>, VectorMatrixUnaryTestFunctor<long double> >::Reference) ==
					  typeid(const long double));

	BOOST_CHECK(typeid(VectorMatrixUnary<Vector<float>, VectorMatrixUnaryTestFunctor<long double> >::SizeType) ==
					  typeid(Vector<float>::SizeType));
	BOOST_CHECK(typeid(VectorMatrixUnary<Vector<long>, VectorMatrixUnaryTestFunctor<long double> >::DifferenceType) ==
					  typeid(Vector<long>::DifferenceType));

	// ----------

	typedef VectorMatrixUnaryTestFunctor<long double> Functor;
	typedef Vector<double>::SizeType SizeType;

	Vector<double> v = vec(50.2, 0.23, 24.23, -22.0);
	VectorMatrixUnary<Vector<double>, Functor> vm_un(v);

	BOOST_CHECK_EQUAL(v.getSize(), vm_un.getSize1());
	BOOST_CHECK_EQUAL(v.getSize(), vm_un.getSize2());
	
	for (SizeType i = 0; i < v.getSize(); i++)
		for (SizeType j = 0; j < v.getSize(); j++)
			BOOST_CHECK_EQUAL(vm_un(i, j), Functor::apply(v, i, j));

	BOOST_CHECK_THROW(vm_un(v.getSize(), 0), Base::IndexError);
	BOOST_CHECK_THROW(vm_un(0, v.getSize()), Base::IndexError);
	BOOST_CHECK_THROW(vm_un(v.getSize(), v.getSize()), Base::IndexError);
}

BOOST_AUTO_TEST_CASE(MatrixBinary1Test)
{
	using namespace CDPL;
	using namespace Math;

	BOOST_CHECK(typeid(MatrixBinary1<Matrix<double>, Matrix<char>, MatrixBinary1TestFunctor<long, long double, float> >::ValueType) ==
					  typeid(const long));
	BOOST_CHECK(typeid(MatrixBinary1<Matrix<double>, Matrix<short>, MatrixBinary1TestFunctor<long, long double, int> >::ConstReference) ==
					  typeid(const long));
	BOOST_CHECK(typeid(MatrixBinary1<Matrix<double>, Matrix<int>, MatrixBinary1TestFunctor<long, long double, float> >::Reference) ==
					  typeid(const long));
	BOOST_CHECK(typeid(MatrixBinary1<Matrix<float>, Matrix<float>, MatrixBinary1TestFunctor<long double, char, short> >::ValueType) ==
					  typeid(const long double));
	BOOST_CHECK(typeid(MatrixBinary1<Matrix<float>, Matrix<double>, MatrixBinary1TestFunctor<long double, char, int> >::ConstReference) ==
					  typeid(const long double));
	BOOST_CHECK(typeid(MatrixBinary1<Matrix<float>, Matrix<long>, MatrixBinary1TestFunctor<long double, char, unsigned int> >::Reference) ==
					  typeid(const long double));

	BOOST_CHECK(typeid(MatrixBinary1<Matrix<float>, Matrix<double>, MatrixBinary1TestFunctor<long double, char, int> >::SizeType) ==
					  typeid(CommonType<Matrix<float>::SizeType, Matrix<double>::SizeType >::Type));
	BOOST_CHECK(typeid(MatrixBinary1<Matrix<float>, Matrix<long>, MatrixBinary1TestFunctor<long double, char, unsigned int> >::DifferenceType) ==
					  typeid(CommonType<Matrix<float>::DifferenceType, Matrix<long>::DifferenceType >::Type));

	// ----------

	typedef MatrixBinary1TestFunctor<long double, const int&, const double&> Functor;
	typedef CommonType<Matrix<int>::SizeType, Matrix<double>::SizeType>::Type SizeType;

	Matrix<int> m1(3, 5);
	Matrix<double> m2(3, 5);

	for (SizeType i = 0; i < m1.getSize1(); i++)
		for (SizeType j = 0; j < m1.getSize2(); j++) {
			m1(i, j) = i * m1.getSize2() + j;
			m2(i, j) = -m1(i, j) / 3.17 + 100.2;
		}

	MatrixBinary1<Matrix<int>, Matrix<double>, Functor> m_bin(m1, m2);

	BOOST_CHECK_EQUAL(m1.getSize1(), m_bin.getSize1());
	BOOST_CHECK_EQUAL(m1.getSize2(), m_bin.getSize2());
	
	for (SizeType i = 0; i < m1.getSize1(); i++)
		for (SizeType j = 0; j < m1.getSize2(); j++)
			BOOST_CHECK_EQUAL(m_bin(i, j), Functor::apply(m1(i, j), m2(i, j)));

	BOOST_CHECK_THROW(m_bin(m1.getSize1(), 0), Base::IndexError);
	BOOST_CHECK_THROW(m_bin(0, m1.getSize2()), Base::IndexError);
	BOOST_CHECK_THROW(m_bin(m1.getSize1(), m1.getSize2()), Base::IndexError);

	// ----------
			
	m1.resize(3, 6, true);

	BOOST_CHECK_NO_THROW(m_bin.getSize1());	
	BOOST_CHECK_THROW(m_bin.getSize2(), Base::SizeError);	

	m2.resize(4, 6, true);

	BOOST_CHECK_THROW(m_bin.getSize1(), Base::SizeError);	
	BOOST_CHECK_NO_THROW(m_bin.getSize2());	

	m2.resize(4, 7, true);

	BOOST_CHECK_THROW(m_bin.getSize1(), Base::SizeError);	
	BOOST_CHECK_THROW(m_bin.getSize2(), Base::SizeError);	

	BOOST_CHECK_EQUAL(m_bin(0, 0), Functor::apply(m1(0, 0), m2(0, 0)));

	BOOST_CHECK_THROW(m_bin(m1.getSize1(), 0), Base::IndexError);
	BOOST_CHECK_THROW(m_bin(0, m1.getSize2()), Base::IndexError);
	BOOST_CHECK_THROW(m_bin(m1.getSize1(), m1.getSize2()), Base::IndexError);
}

BOOST_AUTO_TEST_CASE(MatrixBinary2Test)
{
	using namespace CDPL;
	using namespace Math;

	BOOST_CHECK(typeid(MatrixBinary2<Matrix<double>, Matrix<char>, MatrixBinary2TestFunctor<long> >::ValueType) ==
					  typeid(const long));
	BOOST_CHECK(typeid(MatrixBinary2<Matrix<double>, Matrix<short>, MatrixBinary2TestFunctor<long> >::ConstReference) ==
					  typeid(const long));
	BOOST_CHECK(typeid(MatrixBinary2<Matrix<double>, Matrix<int>, MatrixBinary2TestFunctor<long> >::Reference) ==
					  typeid(const long));
	BOOST_CHECK(typeid(MatrixBinary2<Matrix<float>, Matrix<float>, MatrixBinary2TestFunctor<long double> >::ValueType) ==
					  typeid(const long double));
	BOOST_CHECK(typeid(MatrixBinary2<Matrix<float>, Matrix<double>, MatrixBinary2TestFunctor<long double> >::ConstReference) ==
					  typeid(const long double));
	BOOST_CHECK(typeid(MatrixBinary2<Matrix<float>, Matrix<long>, MatrixBinary2TestFunctor<long double> >::Reference) ==
					  typeid(const long double));

	BOOST_CHECK(typeid(MatrixBinary2<Matrix<int>, Matrix<double>, MatrixBinary2TestFunctor<long double> >::SizeType) ==
					  typeid(CommonType<Matrix<int>::SizeType, Matrix<double>::SizeType >::Type));
	BOOST_CHECK(typeid(MatrixBinary2<Matrix<float>, Matrix<long>, MatrixBinary2TestFunctor<long double> >::DifferenceType) ==
					  typeid(CommonType<Matrix<float>::DifferenceType, Matrix<long>::DifferenceType >::Type));

	// ----------

	typedef MatrixBinary2TestFunctor<long double> Functor;
	typedef CommonType<Matrix<int>::SizeType, Matrix<double>::SizeType>::Type SizeType;

	Matrix<int> m1(3, 5);
	Matrix<double> m2(3, 5);

	for (SizeType i = 0; i < m1.getSize1(); i++)
		for (SizeType j = 0; j < m1.getSize2(); j++) {
			m1(i, j) = i * m1.getSize2() + j;
			m2(i, j) = -m1(i, j) / 3.17 + 100.2;
		}

	MatrixBinary2<Matrix<int>, Matrix<double>, Functor> m_bin(m1, m2);

	BOOST_CHECK_EQUAL(m1.getSize1(), m_bin.getSize1());
	BOOST_CHECK_EQUAL(m2.getSize2(), m_bin.getSize2());
	
	for (SizeType i = 0; i < m1.getSize1(); i++)
		for (SizeType j = 0; j < m1.getSize2(); j++)
			BOOST_CHECK_EQUAL(m_bin(i, j), Functor::apply(m1, m2, i, j));

	BOOST_CHECK_THROW(m_bin(m1.getSize1(), 0), Base::IndexError);
	BOOST_CHECK_THROW(m_bin(0, m1.getSize2()), Base::IndexError);
	BOOST_CHECK_THROW(m_bin(m1.getSize1(), m1.getSize2()), Base::IndexError);

	// ----------
			
	m1.resize(4, 6, true);

	BOOST_CHECK_EQUAL(m1.getSize1(), m_bin.getSize1());
	BOOST_CHECK_EQUAL(m2.getSize2(), m_bin.getSize2());

	BOOST_CHECK_EQUAL(m_bin(0, 0), Functor::apply(m1, m2, 0, 0));

	BOOST_CHECK_THROW(m_bin(m2.getSize1(), 0), Base::IndexError);
	BOOST_CHECK_THROW(m_bin(0, m2.getSize2()), Base::IndexError);
	BOOST_CHECK_THROW(m_bin(m2.getSize1(), m2.getSize2()), Base::IndexError);
}

BOOST_AUTO_TEST_CASE(VectorMatrixBinaryTest)
{
	using namespace CDPL;
	using namespace Math;

	BOOST_CHECK(typeid(VectorMatrixBinary<Vector<double>, Vector<char>, VectorMatrixBinaryTestFunctor<long, long double, float> >::ValueType) ==
					  typeid(const long));
	BOOST_CHECK(typeid(VectorMatrixBinary<Vector<double>, Vector<short>, VectorMatrixBinaryTestFunctor<long, long double, int> >::ConstReference) ==
					  typeid(const long));
	BOOST_CHECK(typeid(VectorMatrixBinary<Vector<double>, Vector<int>, VectorMatrixBinaryTestFunctor<long, long double, float> >::Reference) ==
					  typeid(const long));
	BOOST_CHECK(typeid(VectorMatrixBinary<Vector<float>, Vector<float>, VectorMatrixBinaryTestFunctor<long double, char, short> >::ValueType) ==
					  typeid(const long double));
	BOOST_CHECK(typeid(VectorMatrixBinary<Vector<float>, Vector<double>, VectorMatrixBinaryTestFunctor<long double, char, int> >::ConstReference) ==
					  typeid(const long double));
	BOOST_CHECK(typeid(VectorMatrixBinary<Vector<float>, Vector<long>, VectorMatrixBinaryTestFunctor<long double, char, unsigned int> >::Reference) ==
					  typeid(const long double));

	BOOST_CHECK(typeid(VectorMatrixBinary<Vector<float>, Vector<double>, VectorMatrixBinaryTestFunctor<long double, char, int> >::SizeType) ==
					  typeid(CommonType<Vector<float>::SizeType, Vector<double>::SizeType >::Type));
	BOOST_CHECK(typeid(VectorMatrixBinary<Vector<float>, Vector<long>, VectorMatrixBinaryTestFunctor<long double, char, unsigned int> >::DifferenceType) ==
					  typeid(CommonType<Vector<float>::DifferenceType, Vector<long>::DifferenceType >::Type));

	// ----------

	typedef VectorMatrixBinaryTestFunctor<long double, const int&, const double&> Functor;
	typedef CommonType<Vector<int>::SizeType, Vector<double>::SizeType>::Type SizeType;

	Vector<int> v1 = vec(-1, 0, 4, 22);
	Vector<double> v2 = vec(50.2, 0.23, 24.23, -22.0);

	VectorMatrixBinary<Vector<int>, Vector<double>, Functor> vm_bin(v1, v2);

	BOOST_CHECK_EQUAL(v1.getSize(), vm_bin.getSize1());
	BOOST_CHECK_EQUAL(v2.getSize(), vm_bin.getSize2());
	
	for (SizeType i = 0; i < v1.getSize(); i++)
		for (SizeType j = 0; j < v2.getSize(); j++)
			BOOST_CHECK_EQUAL(vm_bin(i, j), Functor::apply(v1(i), v2(j)));

	BOOST_CHECK_THROW(vm_bin(v1.getSize(), 0), Base::IndexError);
	BOOST_CHECK_THROW(vm_bin(0, v2.getSize()), Base::IndexError);
	BOOST_CHECK_THROW(vm_bin(v1.getSize(), v2.getSize()), Base::IndexError);
}

BOOST_AUTO_TEST_CASE(Matrix1VectorBinaryTest)
{
	using namespace CDPL;
	using namespace Math;

	BOOST_CHECK(typeid(Matrix1VectorBinary<Matrix<double>, Vector<char>, Matrix1VectorBinaryTestFunctor<long> >::ValueType) ==
					  typeid(const long));
	BOOST_CHECK(typeid(Matrix1VectorBinary<Matrix<double>, Vector<short>, Matrix1VectorBinaryTestFunctor<long> >::ConstReference) ==
					  typeid(const long));
	BOOST_CHECK(typeid(Matrix1VectorBinary<Matrix<double>, Vector<int>, Matrix1VectorBinaryTestFunctor<long> >::Reference) ==
					  typeid(const long));
	BOOST_CHECK(typeid(Matrix1VectorBinary<Matrix<float>, Vector<float>, Matrix1VectorBinaryTestFunctor<long double> >::ValueType) ==
					  typeid(const long double));
	BOOST_CHECK(typeid(Matrix1VectorBinary<Matrix<float>, Vector<double>, Matrix1VectorBinaryTestFunctor<long double> >::ConstReference) ==
					  typeid(const long double));
	BOOST_CHECK(typeid(Matrix1VectorBinary<Matrix<float>, Vector<long>, Matrix1VectorBinaryTestFunctor<long double> >::Reference) ==
					  typeid(const long double));

	BOOST_CHECK(typeid(Matrix1VectorBinary<Matrix<float>, Vector<double>, Matrix1VectorBinaryTestFunctor<long double> >::SizeType) ==
					  typeid(CommonType<Matrix<float>::SizeType, Vector<double>::SizeType >::Type));
	BOOST_CHECK(typeid(Matrix1VectorBinary<Matrix<float>, Vector<long>, Matrix1VectorBinaryTestFunctor<long double> >::DifferenceType) ==
					  typeid(CommonType<Matrix<float>::DifferenceType, Vector<long>::DifferenceType >::Type));

	// ----------

	typedef Matrix1VectorBinaryTestFunctor<long double> Functor;
	typedef CommonType<Matrix<int>::SizeType, Vector<double>::SizeType>::Type SizeType;

	Matrix<int> m(3, 4);
	Vector<double> v = vec(50.2, 0.23, 24.23, -22.0);
	Matrix1VectorBinary<Matrix<int>, Vector<double>, Functor> mv_bin(m, v);

	for (SizeType i = 0; i < m.getSize1(); i++)
		for (SizeType j = 0; j < m.getSize2(); j++) 
			m(i, j) = i * m.getSize2() + j * j;

	BOOST_CHECK_EQUAL(m.getSize1(), mv_bin.getSize());
	
	for (SizeType i = 0; i < m.getSize1(); i++) {
		BOOST_CHECK_EQUAL(mv_bin(i), Functor::apply(m, v, i));
		BOOST_CHECK_EQUAL(mv_bin[i], Functor::apply(m, v, i));
	}

	BOOST_CHECK_THROW(mv_bin(m.getSize1()), Base::IndexError);

	// ----------
			
	v.resize(v.getSize() + 3);

	BOOST_CHECK_EQUAL(mv_bin.getSize(), m.getSize1());	

	BOOST_CHECK_THROW(mv_bin(0), Base::IndexError);		  
}

BOOST_AUTO_TEST_CASE(Matrix2VectorBinaryTest)
{
	using namespace CDPL;
	using namespace Math;

	BOOST_CHECK(typeid(Matrix2VectorBinary<Vector<double>, Matrix<char>, Matrix2VectorBinaryTestFunctor<long> >::ValueType) ==
					  typeid(const long));
	BOOST_CHECK(typeid(Matrix2VectorBinary<Vector<double>, Matrix<short>, Matrix2VectorBinaryTestFunctor<long> >::ConstReference) ==
					  typeid(const long));
	BOOST_CHECK(typeid(Matrix2VectorBinary<Vector<double>, Matrix<int>, Matrix2VectorBinaryTestFunctor<long> >::Reference) ==
					  typeid(const long));
	BOOST_CHECK(typeid(Matrix2VectorBinary<Vector<float>, Matrix<float>, Matrix2VectorBinaryTestFunctor<long double> >::ValueType) ==
					  typeid(const long double));
	BOOST_CHECK(typeid(Matrix2VectorBinary<Vector<float>, Matrix<double>, Matrix2VectorBinaryTestFunctor<long double> >::ConstReference) ==
					  typeid(const long double));
	BOOST_CHECK(typeid(Matrix2VectorBinary<Vector<float>, Matrix<long>, Matrix2VectorBinaryTestFunctor<long double> >::Reference) ==
					  typeid(const long double));

	BOOST_CHECK(typeid(Matrix2VectorBinary<Vector<float>, Matrix<double>, Matrix2VectorBinaryTestFunctor<long double> >::SizeType) ==
					  typeid(CommonType<Vector<float>::SizeType, Matrix<double>::SizeType >::Type));
	BOOST_CHECK(typeid(Matrix2VectorBinary<Vector<float>, Matrix<long>, Matrix2VectorBinaryTestFunctor<long double> >::DifferenceType) ==
					  typeid(CommonType<Vector<float>::DifferenceType, Matrix<long>::DifferenceType >::Type));

	// ----------

	typedef Matrix2VectorBinaryTestFunctor<long double> Functor;
	typedef CommonType<Vector<double>::SizeType, Matrix<int>::SizeType>::Type SizeType;

	Matrix<int> m(4, 3);
	Vector<double> v = vec(50.2, 0.23, 24.23, -22.0);
	Matrix2VectorBinary<Vector<double>, Matrix<int>, Functor> mv_bin(v, m);

	for (SizeType i = 0; i < m.getSize1(); i++)
		for (SizeType j = 0; j < m.getSize2(); j++) 
			m(i, j) = i * m.getSize2() + j * j;

	BOOST_CHECK_EQUAL(m.getSize2(), mv_bin.getSize());
	
	for (SizeType i = 0; i < m.getSize2(); i++) {
		BOOST_CHECK_EQUAL(mv_bin(i), Functor::apply(v, m, i));
		BOOST_CHECK_EQUAL(mv_bin[i], Functor::apply(v, m, i));
	}

	BOOST_CHECK_THROW(mv_bin(m.getSize2()), Base::IndexError);

	// ----------
			
	v.resize(v.getSize() + 1);

	BOOST_CHECK_EQUAL(mv_bin.getSize(), m.getSize2());	

	BOOST_CHECK_THROW(mv_bin(0), Base::IndexError);		  
}

BOOST_AUTO_TEST_CASE(Scalar1MatrixBinaryTest)
{
	using namespace CDPL;
	using namespace Math;

	BOOST_CHECK(typeid(Scalar1MatrixBinary<double, Matrix<char>, Scalar1MatrixBinaryTestFunctor<long, long double, float> >::ValueType) ==
 					  typeid(const long));
	BOOST_CHECK(typeid(Scalar1MatrixBinary<double, Matrix<short>, Scalar1MatrixBinaryTestFunctor<long, long double, int> >::ConstReference) ==
					  typeid(const long));
	BOOST_CHECK(typeid(Scalar1MatrixBinary<double, Matrix<int>, Scalar1MatrixBinaryTestFunctor<long, long double, float> >::Reference) ==
					  typeid(const long));
	BOOST_CHECK(typeid(Scalar1MatrixBinary<float, Matrix<float>, Scalar1MatrixBinaryTestFunctor<long double, char, short> >::ValueType) ==
					  typeid(const long double));
	BOOST_CHECK(typeid(Scalar1MatrixBinary<float, Matrix<double>, Scalar1MatrixBinaryTestFunctor<long double, char, int> >::ConstReference) ==
					  typeid(const long double));
	BOOST_CHECK(typeid(Scalar1MatrixBinary<float, Matrix<long>, Scalar1MatrixBinaryTestFunctor<long double, char, unsigned int> >::Reference) ==
					  typeid(const long double));

	BOOST_CHECK(typeid(Scalar1MatrixBinary<double, Matrix<float>, Scalar1MatrixBinaryTestFunctor<int, double, long> >::SizeType) ==
					  typeid(Matrix<float>::SizeType));
	BOOST_CHECK(typeid(Scalar1MatrixBinary<char, Matrix<int>, Scalar1MatrixBinaryTestFunctor<unsigned char, double, long> >::DifferenceType) ==
					  typeid(Matrix<int>::DifferenceType));

	// ----------

	typedef Scalar1MatrixBinaryTestFunctor<long double, const long&, const double&> Functor;
	typedef Matrix<double>::SizeType SizeType;

	Matrix<double> m(8, 3);
	Scalar1MatrixBinary<long, Matrix<double>, Functor> sm_bin(-34, m);

	for (SizeType i = 0; i < m.getSize1(); i++)
		for (SizeType j = 0; j < m.getSize2(); j++) 
			m(i, j) = i * m.getSize2() + j * j;

	BOOST_CHECK_EQUAL(m.getSize1(), sm_bin.getSize1());
	BOOST_CHECK_EQUAL(m.getSize2(), sm_bin.getSize2());
	
	for (SizeType i = 0; i < m.getSize1(); i++)
		for (SizeType j = 0; j < m.getSize2(); j++)
			BOOST_CHECK_EQUAL(sm_bin(i, j), Functor::apply(-34, m(i, j)));

	BOOST_CHECK_THROW(sm_bin(m.getSize1(), 0), Base::IndexError);
	BOOST_CHECK_THROW(sm_bin(0, m.getSize2()), Base::IndexError);
	BOOST_CHECK_THROW(sm_bin(m.getSize1(), m.getSize2()), Base::IndexError);

	// ----------
			
	m.resize(4, 6, true);

	BOOST_CHECK_EQUAL(m.getSize1(), sm_bin.getSize1());
	BOOST_CHECK_EQUAL(m.getSize2(), sm_bin.getSize2());

	BOOST_CHECK_EQUAL(sm_bin(0, 0), Functor::apply(-34, m(0, 0)));

	BOOST_CHECK_THROW(sm_bin(m.getSize1(), 0), Base::IndexError);
	BOOST_CHECK_THROW(sm_bin(0, m.getSize2()), Base::IndexError);
	BOOST_CHECK_THROW(sm_bin(m.getSize1(), m.getSize2()), Base::IndexError);
}

BOOST_AUTO_TEST_CASE(Scalar2MatrixBinaryTest)
{
	using namespace CDPL;
	using namespace Math;

	BOOST_CHECK(typeid(Scalar2MatrixBinary<Matrix<char>, double, Scalar2MatrixBinaryTestFunctor<long, long double, float> >::ValueType) ==
 					  typeid(const long));
	BOOST_CHECK(typeid(Scalar2MatrixBinary<Matrix<short>, double, Scalar2MatrixBinaryTestFunctor<long, long double, int> >::ConstReference) ==
					  typeid(const long));
	BOOST_CHECK(typeid(Scalar2MatrixBinary<Matrix<int>, double, Scalar2MatrixBinaryTestFunctor<long, long double, float> >::Reference) ==
					  typeid(const long));
	BOOST_CHECK(typeid(Scalar2MatrixBinary<Matrix<float>, float, Scalar2MatrixBinaryTestFunctor<long double, char, short> >::ValueType) ==
					  typeid(const long double));
	BOOST_CHECK(typeid(Scalar2MatrixBinary<Matrix<double>, float, Scalar2MatrixBinaryTestFunctor<long double, char, int> >::ConstReference) ==
					  typeid(const long double));
	BOOST_CHECK(typeid(Scalar2MatrixBinary<Matrix<long>, float, Scalar2MatrixBinaryTestFunctor<long double, char, unsigned int> >::Reference) ==
					  typeid(const long double));

	BOOST_CHECK(typeid(Scalar2MatrixBinary<Matrix<float>, double, Scalar2MatrixBinaryTestFunctor<int, double, long> >::SizeType) ==
					  typeid(Matrix<float>::SizeType));
	BOOST_CHECK(typeid(Scalar2MatrixBinary<Matrix<int>, char, Scalar2MatrixBinaryTestFunctor<unsigned char, double, long> >::DifferenceType) ==
					  typeid(Matrix<int>::DifferenceType));

	// ----------

	typedef Scalar2MatrixBinaryTestFunctor<long double, const double&, const long&> Functor;
	typedef Matrix<double>::SizeType SizeType;

	Matrix<double> m(4, 5);
	Scalar2MatrixBinary<Matrix<double>, long, Functor> sm_bin(m, 72);

	for (SizeType i = 0; i < m.getSize1(); i++)
		for (SizeType j = 0; j < m.getSize2(); j++) 
			m(i, j) = i * m.getSize2() + j * j;

	BOOST_CHECK_EQUAL(m.getSize1(), sm_bin.getSize1());
	BOOST_CHECK_EQUAL(m.getSize2(), sm_bin.getSize2());
	
	for (SizeType i = 0; i < m.getSize1(); i++)
		for (SizeType j = 0; j < m.getSize2(); j++)
			BOOST_CHECK_EQUAL(sm_bin(i, j), Functor::apply(m(i, j), 72));

	BOOST_CHECK_THROW(sm_bin(m.getSize1(), 0), Base::IndexError);
	BOOST_CHECK_THROW(sm_bin(0, m.getSize2()), Base::IndexError);
	BOOST_CHECK_THROW(sm_bin(m.getSize1(), m.getSize2()), Base::IndexError);

	// ----------
			
	m.resize(3, 6, true);

	BOOST_CHECK_EQUAL(m.getSize1(), sm_bin.getSize1());
	BOOST_CHECK_EQUAL(m.getSize2(), sm_bin.getSize2());

	BOOST_CHECK_EQUAL(sm_bin(0, 0), Functor::apply(m(0, 0), 72));

	BOOST_CHECK_THROW(sm_bin(m.getSize1(), 0), Base::IndexError);
	BOOST_CHECK_THROW(sm_bin(0, m.getSize2()), Base::IndexError);
	BOOST_CHECK_THROW(sm_bin(m.getSize1(), m.getSize2()), Base::IndexError);
}

BOOST_AUTO_TEST_CASE(MatrixTransposeTest)
{
	using namespace CDPL;
	using namespace Math;

	BOOST_CHECK(typeid(Matrix<double>) == typeid(MatrixTranspose<Matrix<double> >::MatrixType));
	BOOST_CHECK(typeid(Matrix<double>::SizeType) == typeid(MatrixTranspose<Matrix<double> >::SizeType));
	BOOST_CHECK(typeid(Matrix<double>::DifferenceType) == typeid(MatrixTranspose<Matrix<double> >::DifferenceType));
	BOOST_CHECK(typeid(Matrix<double>::ValueType) == typeid(MatrixTranspose<Matrix<double> >::ValueType));
	BOOST_CHECK(typeid(Matrix<double>::Reference) == typeid(MatrixTranspose<Matrix<double> >::Reference));
	BOOST_CHECK(typeid(Matrix<double>::ConstReference) == typeid(MatrixTranspose<Matrix<double> >::ConstReference));
	BOOST_CHECK(typeid(Matrix<double>::ConstReference) == typeid(MatrixTranspose<const Matrix<double> >::Reference));
	BOOST_CHECK(typeid(Matrix<double>::ConstReference) == typeid(MatrixTranspose<const Matrix<double> >::ConstReference));
	BOOST_CHECK(typeid(const Matrix<double>) == typeid(MatrixTranspose<const Matrix<double> >::MatrixType));
	BOOST_CHECK(typeid(Matrix<double>) == typeid(MatrixTranspose<Matrix<double> >::MatrixType));

	// ----------

	typedef Matrix<double>::SizeType SizeType1;

	Matrix<double> m1(0, 0);
	MatrixTranspose<Matrix<double> > mt1(m1);

	checkTransposedMatrix(m1, mt1);

	// ----------

	m1.resize(5, 0);

	checkTransposedMatrix(m1, mt1);

	m1.resize(0, 4);

	checkTransposedMatrix(m1, mt1);

	// ----------
	
	m1.resize(5, 4);

	for (SizeType1 i = 0; i < m1.getSize1(); i++)
		for (SizeType1 j = 0; j < m1.getSize2(); j++)
			mt1(j, i) = i * m1.getSize2() + j + j / 10.0;

	for (SizeType1 i = 0; i < m1.getSize1(); i++)
		for (SizeType1 j = 0; j < m1.getSize2(); j++)
			BOOST_CHECK_EQUAL(m1(i, j), (i * m1.getSize2() + j + j / 10.0));

	checkTransposedMatrix(m1, mt1);

	// ----------

	Matrix<double> m2(m1);
	MatrixTranspose<Matrix<double> > mt2(m2);

	BOOST_CHECK(&(m2 /= 5.17) == &m2);
	m2.resize(6, 3, true, -4.17);

	checkTransposedMatrix(m2, mt2);

	BOOST_CHECK(m2 != m1);
	BOOST_CHECK(mt2 != mt1);
	BOOST_CHECK(mt1 != m2);
	BOOST_CHECK(mt2 != m1);

	BOOST_CHECK(&(mt1 = m2) == &mt1);

	checkTransposedMatrix(m1, mt1);
	checkTransposedMatrix(m2, mt2);
	
	BOOST_CHECK(mt1 == m2);
	BOOST_CHECK(mt2 == m1);
	BOOST_CHECK(m2 != m1);
	BOOST_CHECK(mt1 != mt2);

	// ----------

	BOOST_CHECK(&(mt1 = mt2) == &mt1);

	checkTransposedMatrix(m1, mt1);
	checkTransposedMatrix(m2, mt2);

	BOOST_CHECK(mt1 == mt2);
	BOOST_CHECK(m1 == m2);

	// ----------

	Matrix<float> m3(m1);
	MatrixTranspose<Matrix<float> > mt3(m3);

	m3 *= -2.23f;

	checkTransposedMatrix(m3, mt3);

	BOOST_CHECK(mt1 != mt3);
	BOOST_CHECK(m1 != m3);

	BOOST_CHECK(&(mt1 = mt3) == &mt1);

	checkTransposedMatrix(m1, mt1);
	checkTransposedMatrix(m3, mt3);

	BOOST_CHECK(mt1 == mt3);
	BOOST_CHECK(m1 == m3);
	BOOST_CHECK(mt1 != mt2);
	BOOST_CHECK(m1 != m2);

	// ----------

	m3 /= -7.123f;

	checkTransposedMatrix(m3, mt3);

	BOOST_CHECK(mt1 != mt3);
	BOOST_CHECK(m1 != m3);

	BOOST_CHECK(&mt1.assign(mt3) == &mt1);

	checkTransposedMatrix(m1, mt1);
	checkTransposedMatrix(m3, mt3);

	BOOST_CHECK(mt1 == mt3);
	BOOST_CHECK(m1 == m3);
	BOOST_CHECK(mt1 != mt2);
	BOOST_CHECK(m1 != m2);

	// ----------

	m1 = m2;

	checkTransposedMatrix(m1, mt1);
	checkTransposedMatrix(m2, mt2);

	BOOST_CHECK(mt1 == mt2);
	BOOST_CHECK(m1 == m2);

	BOOST_CHECK(&(mt1 += mt2) == &mt1);

	checkTransposedMatrix(m1, mt1);
	checkTransposedMatrix(m2, mt2);

	BOOST_CHECK(mt1 != mt2);
	BOOST_CHECK(m1 != m2);

	m2 += m2;
	
	checkTransposedMatrix(m1, mt1);
	checkTransposedMatrix(m2, mt2);

	BOOST_CHECK(mt1 == mt2);
	BOOST_CHECK(m1 == m2);

	// ----------

	BOOST_CHECK(&(mt1.plusAssign(mt2)) == &mt1);

	checkTransposedMatrix(m1, mt1);
	checkTransposedMatrix(m2, mt2);

	BOOST_CHECK(mt1 != mt2);
	BOOST_CHECK(m1 != m2);

	m2 += m2;
	
	checkTransposedMatrix(m1, mt1);
	checkTransposedMatrix(m2, mt2);

	BOOST_CHECK(mt1 == mt2);
	BOOST_CHECK(m1 == m2);

	// ----------

	Matrix<double> m4(mt2);
	MatrixTranspose<Matrix<double> > mt4_tmp(m4);
	MatrixTranspose<Matrix<double> > mt4(mt4_tmp);

	checkTransposedMatrix(m2, mt2);
	checkTransposedMatrix(m4, mt4);

	BOOST_CHECK(m4 == mt2);
	BOOST_CHECK(mt4 == m2);

	m4 /= 4.0;

	checkTransposedMatrix(m4, mt4);

	BOOST_CHECK(m4 != mt2);
	BOOST_CHECK(mt4 != m2);

	BOOST_CHECK(&(mt1 -= m4) == &mt1);

	checkTransposedMatrix(m1, mt1);
	checkTransposedMatrix(m4, mt4);

	BOOST_CHECK(mt1 != mt2);
	BOOST_CHECK(m1 != m2);

	m2 -= mt4;

	checkTransposedMatrix(m2, mt2);
	checkTransposedMatrix(m4, mt4);

	BOOST_CHECK(mt1 == mt2);
	BOOST_CHECK(m1 == m2);

	// ----------

	BOOST_CHECK(&(mt1.minusAssign(m4)) == &mt1);

	checkTransposedMatrix(m1, mt1);
	checkTransposedMatrix(m4, mt4);

	BOOST_CHECK(mt1 != mt2);
	BOOST_CHECK(m1 != m2);

	m2 -= mt4;

	checkTransposedMatrix(m2, mt2);
	checkTransposedMatrix(m4, mt4);

	BOOST_CHECK(mt1 == mt2);
	BOOST_CHECK(m1 == m2);

	// ----------

	BOOST_CHECK(&(mt1 *= 20.12) == &mt1);

	checkTransposedMatrix(m1, mt1);
	checkTransposedMatrix(m2, mt2);

	BOOST_CHECK(mt1 != mt2);
	BOOST_CHECK(m1 != m2);

	m2 *= 20.12;
	
	checkTransposedMatrix(m1, mt1);
	checkTransposedMatrix(m2, mt2);

	BOOST_CHECK(mt1 == mt2);
	BOOST_CHECK(m1 == m2);

	// ----------

	BOOST_CHECK(&(mt1 /= -1.2320) == &mt1);

	checkTransposedMatrix(m1, mt1);
	checkTransposedMatrix(m2, mt2);

	BOOST_CHECK(mt1 != mt2);
	BOOST_CHECK(m1 != m2);

	m2 /= -1.2320;
	
	checkTransposedMatrix(m1, mt1);
	checkTransposedMatrix(m2, mt2);

	BOOST_CHECK(mt1 == mt2);
	BOOST_CHECK(m1 == m2);

	// ----------

	m2.resize(m1.getSize1() + 2, m1.getSize2() + 1, true, -7.27);
	
	checkTransposedMatrix(m1, mt1);
	checkTransposedMatrix(m2, mt2);

	BOOST_CHECK(mt1 != mt2);
	BOOST_CHECK(m1 != m2);

	Matrix<double> m5(m2);

	m4 = m1;

	BOOST_CHECK(m4 == m1);
	BOOST_CHECK(m5 == m2);

	mt1.swap(mt1);

	checkTransposedMatrix(m1, mt1);

	mt1.swap(mt2);

	checkTransposedMatrix(m1, mt1);
	checkTransposedMatrix(m2, mt2);
	
	BOOST_CHECK(m4 == m2);
	BOOST_CHECK(m5 == m1);

	mt1.swap(mt2);

	checkTransposedMatrix(m1, mt1);
	checkTransposedMatrix(m2, mt2);
	
	BOOST_CHECK(m4 == m1);
	BOOST_CHECK(m5 == m2);

	mt2.swap(mt1);

	checkTransposedMatrix(m1, mt1);
	checkTransposedMatrix(m2, mt2);
	
	BOOST_CHECK(m4 == m2);
	BOOST_CHECK(m5 == m1);

	mt2.swap(mt1);

	checkTransposedMatrix(m1, mt1);
	checkTransposedMatrix(m2, mt2);
	
	BOOST_CHECK(m4 == m1);
	BOOST_CHECK(m5 == m2);

	// ----------

	swap(mt1, mt1);

	checkTransposedMatrix(m1, mt1);

	swap(mt1, mt2);

	checkTransposedMatrix(m1, mt1);
	checkTransposedMatrix(m2, mt2);
	
	BOOST_CHECK(m4 == m2);
	BOOST_CHECK(m5 == m1);

	swap(mt1, mt2);

	checkTransposedMatrix(m1, mt1);
	checkTransposedMatrix(m2, mt2);
	
	BOOST_CHECK(m4 == m1);
	BOOST_CHECK(m5 == m2);

	swap(mt2, mt1);

	checkTransposedMatrix(m1, mt1);
	checkTransposedMatrix(m2, mt2);
	
	BOOST_CHECK(m4 == m2);
	BOOST_CHECK(m5 == m1);

	swap(mt2, mt1);

	checkTransposedMatrix(m1, mt1);
	checkTransposedMatrix(m2, mt2);
	
	BOOST_CHECK(m4 == m1);
	BOOST_CHECK(m5 == m2);
}

BOOST_AUTO_TEST_CASE(TransFunctionTest)
{
	using namespace CDPL;
	using namespace Math;

	typedef const MatrixTranspose<Matrix<double> > CTMD;
	typedef Matrix<double>::SizeType SizeType1;

	Matrix<double> m1(0, 0);

	checkTransposedMatrix<CTMD>(m1, trans(m1));

	// ----------

	m1.resize(5, 0);

	checkTransposedMatrix<CTMD>(m1, trans(m1));

	m1.resize(0, 4);

	checkTransposedMatrix<CTMD>(m1, trans(m1));

	// ----------
	
	m1.resize(5, 4);

	for (SizeType1 i = 0; i < m1.getSize1(); i++)
		for (SizeType1 j = 0; j < m1.getSize2(); j++)
			m1(i, j) = i * m1.getSize2() + j + j / 10.0;
		
	checkTransposedMatrix<CTMD>(m1, trans(m1));

	// ----------

	typedef const MatrixTranspose<const Matrix<double> > CTCMD;

	Matrix<double> m2(m1);

	m2 /= 5.17;
	m2.resize(6, 3, true, -4.17);

	const Matrix<double>& m2_cref = m2;

	checkTransposedMatrix<CTCMD>(m2, trans(m2_cref));

	// ----------

	BOOST_CHECK(m2 != m1);
	BOOST_CHECK(trans(m2) != trans(m1));
	BOOST_CHECK(trans(m1) != m2);
	BOOST_CHECK(trans(m2) != m1);

	trans(m1) = m2;

	checkTransposedMatrix<CTMD>(m1, trans(m1));
	checkTransposedMatrix<CTMD>(m2, trans(m2));
	
	BOOST_CHECK(trans(m1) == m2);
	BOOST_CHECK(trans(m2) == m1);
	BOOST_CHECK(m2 != m1);
	BOOST_CHECK(trans(m1) != trans(m2));

	// ----------

	trans(m1) = trans(m2);

	checkTransposedMatrix<CTMD>(m1, trans(m1));
	checkTransposedMatrix<CTMD>(m2, trans(m2));

	BOOST_CHECK(trans(m1) == trans(m2));
	BOOST_CHECK(m1 == m2);

	// ----------

	typedef const MatrixTranspose<Matrix<std::complex<float> > > CTMCF;
	typedef Matrix<std::complex<float> >::SizeType SizeType2;

	Matrix<std::complex<float> > m3(0, 0);

	checkTransposedMatrix<CTMCF>(m3, trans(m3));

	// ----------

	m3.resize(4, 0);

	checkTransposedMatrix<CTMCF>(m3, trans(m3));

	m3.resize(0, 5);

	checkTransposedMatrix<CTMCF>(m3, trans(m3));

	// ----------

	typedef Matrix<std::complex<float> >::SizeType SizeType2;

	m3.resize(4, 5);

	for (SizeType2 i = 0; i < m3.getSize1(); i++)
		for (SizeType2 j = 0; j < m3.getSize2(); j++)
			m3(i, j) = std::complex<float>(i * m3.getSize2() + j + j / 10.0f, -i * m3.getSize2() + j);
		
	checkTransposedMatrix<CTMCF>(m3, trans(m3));
}

BOOST_AUTO_TEST_CASE(OuterProdFunctionTest)
{
	using namespace CDPL;
	using namespace Math;

	checkVectorOuterProdFunction(Vector<double>(0), CVector<float, 0>());
	checkVectorOuterProdFunction(Vector<int>(1, 14), CVector<float, 0>());
	checkVectorOuterProdFunction(vec(0.0, -120.2), CVector<float, 0>());
	checkVectorOuterProdFunction(vec(-1.1f, 2.1f), CVector<double, 0>());
	checkVectorOuterProdFunction(vec(1, 2, -6), CVector<long double, 0>());
	checkVectorOuterProdFunction(vec(1.2, -2.2, 6.12, 100.3), CVector<std::complex<double>, 0>());
	checkVectorOuterProdFunction(vec(std::complex<double>(-17.2, 4.5), std::complex<double>(15.16, -14.5), 
									 std::complex<double>(11.17, 22.15), std::complex<double>(-3.1, -1.25)), CVector<double, 0>());
	checkVectorOuterProdFunction(vec(std::complex<double>(-17.2, 4.5), std::complex<double>(15.16, -14.5), 
									 std::complex<double>(-3.1, -1.25)), CVector<std::complex<double>, 0>());

	// ----------

	checkVectorOuterProdFunction(Vector<double>(0), CVector<float, 1>(1.12f));
	checkVectorOuterProdFunction(Vector<int>(1, 14), CVector<float, 1>(-3));
	checkVectorOuterProdFunction(vec(0.0, -120.2), CVector<float, 1>(-1.123f));
	checkVectorOuterProdFunction(vec(-1.1f, 2.1f), CVector<double, 1>(4.5));
	checkVectorOuterProdFunction(vec(1, 2, -6), CVector<long double, 1>(-1.233456));
	checkVectorOuterProdFunction(vec(1.2, -2.2, 6.12, 100.3), CVector<std::complex<double>, 1>(std::complex<double>(1.2, -4.4)));
	checkVectorOuterProdFunction(vec(std::complex<double>(-17.2, 4.5), std::complex<double>(15.16, -14.5), 
									 std::complex<double>(11.17, 22.15), std::complex<double>(-3.1, -1.25)), CVector<double, 1>(4.65));
	checkVectorOuterProdFunction(vec(std::complex<double>(-17.2, 4.5), std::complex<double>(15.16, -14.5), 
									 std::complex<double>(-3.1, -1.25)), Vector<std::complex<double> >(1, std::complex<double>(1.2, -4.4)));

	// ----------

	checkVectorOuterProdFunction(Vector<double>(0), vec(-1.1f, 2.1f));
	checkVectorOuterProdFunction(Vector<int>(1, 14), vec(-1.1f, 2.1f));
	checkVectorOuterProdFunction(vec(0.0, -120.2), vec(-1.1f, 2.1f));
	checkVectorOuterProdFunction(vec(-1.1f, 2.1f), vec(21.1, 223.1));
	checkVectorOuterProdFunction(vec(1, 2, -6), vec(0.0, -120.2));
	checkVectorOuterProdFunction(vec(1.2, -2.2, 6.12, 100.3), vec(std::complex<double>(-17.2, 4.5), std::complex<double>(15.16, -14.5)));
	checkVectorOuterProdFunction(vec(std::complex<double>(-17.2, 4.5), std::complex<double>(15.16, -14.5), 
									 std::complex<double>(11.17, 22.15), std::complex<double>(-3.1, -1.25)), vec(0.0, -120.2));
	checkVectorOuterProdFunction(vec(std::complex<double>(-17.2, 4.5), std::complex<double>(15.16, -14.5), 
									 std::complex<double>(-3.1, -1.25)), vec(std::complex<double>(-17.2, 4.5), std::complex<double>(15.16, -14.5)));

	// ----------

	checkVectorOuterProdFunction(Vector<double>(0), vec(-1.1f, 2.1f, 2));
	checkVectorOuterProdFunction(Vector<int>(1, 14), vec(-1.1f, 2.1f, 2.3));
	checkVectorOuterProdFunction(vec(0.0, -120.2), vec(-1.1f, 2.1f, -0.22f));
	checkVectorOuterProdFunction(vec(-1.1f, 2.1f), vec(21.1, 223.1, 5.154));
	checkVectorOuterProdFunction(vec(1, 2, -6), vec(0.0, -120.2, 7));
	checkVectorOuterProdFunction(vec(1.2, -2.2, 100.3), vec(std::complex<double>(-17.2, 4.5), std::complex<double>(15.16, -14.5), 
															std::complex<double>(-3.1, -1.25)));
	checkVectorOuterProdFunction(vec(std::complex<double>(-17.2, 4.5), std::complex<double>(15.16, -14.5), 
									 std::complex<double>(11.17, 22.15), std::complex<double>(-3.1, -1.25)), vec(0.0, -120.2, -15.9));
	checkVectorOuterProdFunction(vec(std::complex<double>(-17.2, 4.5), std::complex<double>(15.16, -14.5), 
									 std::complex<double>(-3.1, -1.25)), 
								 vec(std::complex<double>(-7.23, 2.25), std::complex<double>(-17.2, 4.5), 
									 std::complex<double>(15.16, -14.5), std::complex<double>(13.16, 4.5)));
}

BOOST_AUTO_TEST_CASE(MatrixScalarDivisionTest)
{
	using namespace CDPL;
	using namespace Math;

	Matrix<double> m1(3, 0);

	checkMatrixScalarDivision(m1, int(5));
	checkMatrixScalarDivision(m1, std::complex<double>());

	// ----------

	m1.resize(3, 1);

	m1(0, 0) = -2.3;
	m1(1, 0) = 1.0;
	m1(2, 0) = -21.20;

	checkMatrixScalarDivision(m1, -2.37f);
	checkMatrixScalarDivision(m1, std::complex<double>(-2.37, 5.5));

	// ----------

	m1.resize(3, 2, true);

	m1(0, 1) = 2;
	m1(1, 1) = -1.10;
	m1(2, 1) = 0.001;

	checkMatrixScalarDivision(m1, -0.21);
	checkMatrixScalarDivision(m1, std::complex<double>(-0.21, 1.0));

	// ----------

	m1.resize(3, 3, true);

	m1(0, 2) = 0.12;
	m1(1, 2) = 2.10;
	m1(2, 2) = -20.001;

	checkMatrixScalarDivision(m1, long(-2));
	checkMatrixScalarDivision(m1, std::complex<double>(10.2, 3.22));

	// ----------

	m1.resize(3, 4, true);

	m1(0, 3) = 3;
	m1(1, 3) = 4;
	m1(2, 3) = 5;

	checkMatrixScalarDivision(m1, short(2));
	checkMatrixScalarDivision(m1, std::complex<double>(0.12, -3.2));

	// ----------

	m1.resize(0, 4);

	checkMatrixScalarDivision(m1, char(2));
	checkMatrixScalarDivision(m1, std::complex<double>(-0.812, -3.2));

	// ----------

	Matrix<std::complex<double> > m2(3, 0);

	checkMatrixScalarDivision(m2, 0.02);
	checkMatrixScalarDivision(m2, std::complex<double>());

	// ----------

	m2.resize(3, 1);

	m2(0, 0) = std::complex<double>(-2.3, 5.12);
	m2(1, 0) = std::complex<double>(1.0, 0.0);
	m2(2, 0) = std::complex<double>(-21.20, -17.2);

	checkMatrixScalarDivision(m2, -2.37);
	checkMatrixScalarDivision(m2, std::complex<double>(-2.37, 0.5));

	// ----------

	m2.resize(3, 2, true);

	m2(0, 1) = std::complex<double>(2, -4.3);
	m2(1, 1) = std::complex<double>(-1.10, -0.0002);
	m2(2, 1) = std::complex<double>(0.001, 0.1);

	checkMatrixScalarDivision(m2, 100.12);
	checkMatrixScalarDivision(m2, std::complex<double>(100, -3.2));

	// ----------

	m2.resize(3, 3, true);

	m2(0, 2) = std::complex<double>(0.12, 0.0);
	m2(1, 2) = std::complex<double>(2.10, 0.0);
	m2(2, 2) = std::complex<double>(-20.001, 0.0);

	checkMatrixScalarDivision(m2, -2.23);
	checkMatrixScalarDivision(m2, std::complex<double>(0.0, 3.22));

	// ----------

	m2.resize(3, 4, true);

	m2(0, 3) = std::complex<double>(3, 0.1);
	m2(1, 3) = std::complex<double>(4, 0.2);
	m2(2, 3) = std::complex<double>(5, -0.3);

	checkMatrixScalarDivision(m2, -22.123);
	checkMatrixScalarDivision(m2, std::complex<double>(180.12, 0.0));

	// ----------

	m2.resize(0, 4);

	checkMatrixScalarDivision(m2, 2.2);
	checkMatrixScalarDivision(m2, std::complex<double>(-180.12, 20.0));
}

BOOST_AUTO_TEST_CASE(MatrixScalarMultiplicationTest)
{
	using namespace CDPL;
	using namespace Math;

	Matrix<double> m1(3, 0);

	checkMatrixScalarMultiplication(m1, int(5));
	checkMatrixScalarMultiplication(m1, std::complex<double>());

	// ----------

	m1.resize(3, 1);

	m1(0, 0) = -2.3;
	m1(1, 0) = 1.0;
	m1(2, 0) = -21.20;

	checkMatrixScalarMultiplication(m1, -2.37f);
	checkMatrixScalarMultiplication(m1, std::complex<double>(-2.37, 5.5));

	// ----------

	m1.resize(3, 2, true);

	m1(0, 1) = 2;
	m1(1, 1) = -1.10;
	m1(2, 1) = 0.001;

	checkMatrixScalarMultiplication(m1, -0.21);
	checkMatrixScalarMultiplication(m1, std::complex<double>(-0.21, 1.0));

	// ----------

	m1.resize(3, 3, true);

	m1(0, 2) = 0.12;
	m1(1, 2) = 2.10;
	m1(2, 2) = -20.001;

	checkMatrixScalarMultiplication(m1, long(-2));
	checkMatrixScalarMultiplication(m1, std::complex<double>(10.2, 3.22));

	// ----------

	m1.resize(3, 4, true);

	m1(0, 3) = 3;
	m1(1, 3) = 4;
	m1(2, 3) = 5;

	checkMatrixScalarMultiplication(m1, short(2));
	checkMatrixScalarMultiplication(m1, std::complex<double>(0.12, -3.2));

	// ----------

	m1.resize(0, 4);

	checkMatrixScalarMultiplication(m1, char(2));
	checkMatrixScalarMultiplication(m1, std::complex<double>(-0.812, -3.2));

	// ----------

	Matrix<std::complex<double> > m2(3, 0);

	checkMatrixScalarMultiplication(m2, 0.02);
	checkMatrixScalarMultiplication(m2, std::complex<double>());

	// ----------

	m2.resize(3, 1);

	m2(0, 0) = std::complex<double>(-2.3, 5.12);
	m2(1, 0) = std::complex<double>(1.0, 0.0);
	m2(2, 0) = std::complex<double>(-21.20, -17.2);

	checkMatrixScalarMultiplication(m2, -2.37);
	checkMatrixScalarMultiplication(m2, std::complex<double>(-2.37, 0.5));

	// ----------

	m2.resize(3, 2, true);

	m2(0, 1) = std::complex<double>(2, -4.3);
	m2(1, 1) = std::complex<double>(-1.10, -0.0002);
	m2(2, 1) = std::complex<double>(0.001, 0.1);

	checkMatrixScalarMultiplication(m2, 100.12);
	checkMatrixScalarMultiplication(m2, std::complex<double>(100, -3.2));

	// ----------

	m2.resize(3, 3, true);

	m2(0, 2) = std::complex<double>(0.12, 0.0);
	m2(1, 2) = std::complex<double>(2.10, 0.0);
	m2(2, 2) = std::complex<double>(-20.001, 0.0);

	checkMatrixScalarMultiplication(m2, -2.23);
	checkMatrixScalarMultiplication(m2, std::complex<double>(0.0, 3.22));

	// ----------

	m2.resize(3, 4, true);

	m2(0, 3) = std::complex<double>(3, 0.1);
	m2(1, 3) = std::complex<double>(4, 0.2);
	m2(2, 3) = std::complex<double>(5, -0.3);

	checkMatrixScalarMultiplication(m2, -22.123);
	checkMatrixScalarMultiplication(m2, std::complex<double>(180.12, 0.0));

	// ----------

	m2.resize(0, 4);

	checkMatrixScalarMultiplication(m2, 2.2);
	checkMatrixScalarMultiplication(m2, std::complex<double>(-180.12, 20.0));
}

BOOST_AUTO_TEST_CASE(ScalarMatrixMultiplicationTest)
{
	using namespace CDPL;
	using namespace Math;

	Matrix<double> m1(3, 0);

	checkScalarMatrixMultiplication(int(5), m1);
	checkScalarMatrixMultiplication(std::complex<double>(), m1);

	// ----------

	m1.resize(3, 1);

	m1(0, 0) = -2.3;
	m1(1, 0) = 1.0;
	m1(2, 0) = -21.20;

	checkScalarMatrixMultiplication(-2.37f, m1);
	checkScalarMatrixMultiplication(std::complex<double>(-2.37, 5.5), m1);

	// ----------

	m1.resize(3, 2, true);

	m1(0, 1) = 2;
	m1(1, 1) = -1.10;
	m1(2, 1) = 0.001;

	checkScalarMatrixMultiplication(-0.21, m1);
	checkScalarMatrixMultiplication(std::complex<double>(-0.21, 1.0), m1);

	// ----------

	m1.resize(3, 3, true);

	m1(0, 2) = 0.12;
	m1(1, 2) = 2.10;
	m1(2, 2) = -20.001;

	checkScalarMatrixMultiplication(long(-2), m1);
	checkScalarMatrixMultiplication(std::complex<double>(10.2, 3.22), m1);

	// ----------

	m1.resize(3, 4, true);

	m1(0, 3) = 3;
	m1(1, 3) = 4;
	m1(2, 3) = 5;

	checkScalarMatrixMultiplication(short(2), m1);
	checkScalarMatrixMultiplication(std::complex<double>(0.12, -3.2), m1);

	// ----------

	m1.resize(0, 4);

	checkScalarMatrixMultiplication(char(2), m1);
	checkScalarMatrixMultiplication(std::complex<double>(-0.812, -3.2), m1);

	// ----------

	Matrix<std::complex<double> > m2(3, 0);

	checkScalarMatrixMultiplication(0.02, m2);
	checkScalarMatrixMultiplication(std::complex<double>(), m2);

	// ----------

	m2.resize(3, 1);

	m2(0, 0) = std::complex<double>(-2.3, 5.12);
	m2(1, 0) = std::complex<double>(1.0, 0.0);
	m2(2, 0) = std::complex<double>(-21.20, -17.2);

	checkScalarMatrixMultiplication(-2.37, m2);
	checkScalarMatrixMultiplication(std::complex<double>(-2.37, 0.5), m2);

	// ----------

	m2.resize(3, 2, true);

	m2(0, 1) = std::complex<double>(2, -4.3);
	m2(1, 1) = std::complex<double>(-1.10, -0.0002);
	m2(2, 1) = std::complex<double>(0.001, 0.1);

	checkScalarMatrixMultiplication(100.12, m2);
	checkScalarMatrixMultiplication(std::complex<double>(100, -3.2), m2);

	// ----------

	m2.resize(3, 3, true);

	m2(0, 2) = std::complex<double>(0.12, 0.0);
	m2(1, 2) = std::complex<double>(2.10, 0.0);
	m2(2, 2) = std::complex<double>(-20.001, 0.0);

	checkScalarMatrixMultiplication(-2.23, m2);
	checkScalarMatrixMultiplication(std::complex<double>(0.0, 3.22), m2);

	// ----------

	m2.resize(3, 4, true);

	m2(0, 3) = std::complex<double>(3, 0.1);
	m2(1, 3) = std::complex<double>(4, 0.2);
	m2(2, 3) = std::complex<double>(5, -0.3);

	checkScalarMatrixMultiplication(-22.123, m2);
	checkScalarMatrixMultiplication(std::complex<double>(180.12, 0.0), m2);

	// ----------

	m2.resize(0, 4);

	checkScalarMatrixMultiplication(2.2, m2);
	checkScalarMatrixMultiplication(std::complex<double>(-180.12, 20.0), m2);
}

BOOST_AUTO_TEST_CASE(MatrixAdditionTest)
{
	using namespace CDPL;
	using namespace Math;

	BOOST_CHECK_NO_THROW(operator+(CMatrix<int, 0, 1>(), Matrix<float>()));
	BOOST_CHECK_NO_THROW(operator+(Matrix<double>(0, 0), Matrix<float>(1, 0)));
	BOOST_CHECK_NO_THROW(operator+(Matrix<double>(0, 2), Matrix<float>(1, 0)));
	BOOST_CHECK_NO_THROW(operator+(Matrix<double>(0, 3), Matrix<float>(4, 0)));

	BOOST_CHECK_NO_THROW(operator+(Matrix<double>(1, 1), Matrix<int>(0, 2)));
	BOOST_CHECK_NO_THROW(operator+(Matrix<int>(3, 0), Matrix<float>(4, 1)));
	BOOST_CHECK_NO_THROW(operator+(Matrix<short>(3, 4), Matrix<float>(3, 6)));
	BOOST_CHECK_NO_THROW(operator+(Matrix<int>(2, 4), Matrix<float>(5, 4)));

	BOOST_CHECK_NO_THROW((CMatrix<int, 0, 1>() + Matrix<float>()));
	BOOST_CHECK_NO_THROW((Matrix<double>(0, 0) + Matrix<float>(1, 0)));
	BOOST_CHECK_NO_THROW((Matrix<double>(0, 2) + Matrix<float>(1, 0)));
	BOOST_CHECK_NO_THROW((Matrix<double>(0, 3) + Matrix<float>(4, 0)));

	BOOST_CHECK_NO_THROW((Matrix<double>(1, 1) + Matrix<int>(0, 2)));
	BOOST_CHECK_NO_THROW((Matrix<int>(3, 0) + Matrix<float>(4, 1)));
	BOOST_CHECK_NO_THROW((Matrix<short>(3, 4) + Matrix<float>(3, 6)));
	BOOST_CHECK_NO_THROW((Matrix<int>(2, 4) + Matrix<float>(5, 4)));

	BOOST_CHECK_NO_THROW(operator+(Matrix<int>(2, 4), Matrix<float>(5, 4))(0, 0));
	BOOST_CHECK_NO_THROW((Matrix<int>(2, 4) + Matrix<float>(2, 5))(0, 0));

	// ----------

	BOOST_CHECK_THROW(operator+(CMatrix<int, 0, 1>(), Matrix<float>())(0, 0), Base::IndexError);
	BOOST_CHECK_THROW(operator+(Matrix<double>(0, 0), Matrix<float>(1, 0))(10, 12), Base::IndexError);
	BOOST_CHECK_THROW(operator+(Matrix<double>(0, 2), Matrix<float>(1, 0))(3, 0), Base::IndexError);
	BOOST_CHECK_THROW(operator+(Matrix<double>(0, 3), Matrix<float>(4, 0)).getSize1(), Base::SizeError);
	BOOST_CHECK_THROW(operator+(Matrix<double>(0, 3), Matrix<float>(4, 0)).getSize2(), Base::SizeError);

	BOOST_CHECK_THROW(operator+(Matrix<double>(1, 1), Matrix<int>(0, 2))(1, 2), Base::IndexError);
	BOOST_CHECK_THROW(operator+(Matrix<int>(3, 0), Matrix<float>(4, 1))(2, 0), Base::IndexError);
	BOOST_CHECK_THROW(operator+(Matrix<short>(3, 4), Matrix<float>(3, 6))(5, 1), Base::IndexError);

	BOOST_CHECK_THROW((CMatrix<int, 0, 1>() + Matrix<float>())(0, 0), Base::IndexError);
	BOOST_CHECK_THROW((Matrix<double>(0, 0) + Matrix<float>(1, 0))(10, 12), Base::IndexError);
	BOOST_CHECK_THROW((Matrix<double>(0, 2) + Matrix<float>(1, 0))(3, 0), Base::IndexError);
	BOOST_CHECK_THROW((Matrix<double>(0, 3) + Matrix<float>(4, 0))(1, 1), Base::IndexError);

	BOOST_CHECK_THROW((Matrix<double>(1, 1) + Matrix<int>(0, 2))(1, 2), Base::IndexError);
	BOOST_CHECK_THROW((Matrix<int>(3, 0) + Matrix<float>(4, 1))(2, 0), Base::IndexError);
	BOOST_CHECK_THROW((Matrix<short>(3, 4) + Matrix<float>(3, 6))(5, 1), Base::IndexError);

	// ----------

	Matrix<double> m1(3, 0);
	Matrix<int> m2(3, 0);

	checkMatrixAddition(m1, m2);

	// ----------

	m1.resize(3, 1);
	m2.resize(3, 1);

	m1(0, 0) = -2.3;
	m1(1, 0) = 1.0;
	m1(2, 0) = -21.20;

	m2(0, 0) = -3;
	m2(1, 0) = 2;
	m2(2, 0) = 12;

	checkMatrixAddition(m1, m2);

	// ----------

	m1.resize(3, 2, true);
	m2.resize(3, 2, true);

	m1(0, 1) = 0.3;
	m1(1, 1) = -21.0;
	m1(2, 1) = 220;

	m2(0, 1) = 5;
	m2(1, 1) = -6;
	m2(2, 1) = 9;

	checkMatrixAddition(m1, m2);

	// ----------

	m1.resize(3, 3, true);
	m2.resize(3, 3, true);

	m1(0, 2) = 0.3;
	m1(1, 2) = -21.0;
	m1(2, 2) = 220;

	m2(0, 2) = 15;
	m2(1, 2) = 2;
	m2(2, 2) = -2;

	checkMatrixAddition(m1, m2);

	// ----------

	m1.resize(3, 4, true);
	m2.resize(3, 4, true);

	m1(0, 3) = 0.3;
	m1(1, 3) = 0.0;
	m1(2, 3) = 2.2;

	m2(0, 3) = 15;
	m2(1, 3) = 2;
	m2(2, 3) = 0;

	checkMatrixAddition(m1, m2);

	// ----------

	Matrix<std::complex<double> > m3(3, 3);

	m1.resize(3, 3);

	checkMatrixAddition(m1, m3);

	// ----------

	m3(0, 0) = std::complex<double>(-3.0, 0.0);
	m3(1, 0) = std::complex<double>(2.2, -3.23);
	m3(2, 0) = std::complex<double>(5.0, -1.0);
	m3(0, 1) = std::complex<double>(-6.0, 534.0);
	m3(1, 1) = std::complex<double>(9.0, 0.0);
	m3(2, 1) = std::complex<double>(8.0, 2.3);
	m3(0, 2) = std::complex<double>(-7.0, -4.4);
	m3(1, 2) = std::complex<double>(26.0, 0.0002);
	m3(2, 2) = std::complex<double>(8.0, 2.3);

	checkMatrixAddition(m1, m3);

	// ----------
	
	Matrix<std::complex<double> > m4(m3);

	m4 *= -1.12;

	m4(2, 0) = std::complex<double>(18.0, 22.3);
	m4(2, 1) = std::complex<double>(17.2, 4.4);
	m4(2, 2) = std::complex<double>(6.0, 10.0002);

	checkMatrixAddition(m3, m4);

	// ----------

	m1.resize(1, 3, true);
	m2.resize(1, 3, true);

	checkMatrixAddition(m1, m2);

	// ----------

	m1.resize(0, 3);
	m2.resize(0, 3);

	checkMatrixAddition(m1, m2);
}

BOOST_AUTO_TEST_CASE(MatrixSubtractionTest)
{
	using namespace CDPL;
	using namespace Math;

	BOOST_CHECK_NO_THROW(operator-(CMatrix<int, 0, 1>(), Matrix<float>()));
	BOOST_CHECK_NO_THROW(operator-(Matrix<double>(0, 0), Matrix<float>(1, 0)));
	BOOST_CHECK_NO_THROW(operator-(Matrix<double>(0, 2), Matrix<float>(1, 0)));
	BOOST_CHECK_NO_THROW(operator-(Matrix<double>(0, 3), Matrix<float>(4, 0)));

	BOOST_CHECK_NO_THROW(operator-(Matrix<double>(1, 1), Matrix<int>(0, 2)));
	BOOST_CHECK_NO_THROW(operator-(Matrix<int>(3, 0), Matrix<float>(4, 1)));
	BOOST_CHECK_NO_THROW(operator-(Matrix<short>(3, 4), Matrix<float>(3, 6)));
	BOOST_CHECK_NO_THROW(operator-(Matrix<int>(2, 4), Matrix<float>(5, 4)));

	BOOST_CHECK_NO_THROW((CMatrix<int, 0, 1>() - Matrix<float>()));
	BOOST_CHECK_NO_THROW((Matrix<double>(0, 0) - Matrix<float>(1, 0)));
	BOOST_CHECK_NO_THROW((Matrix<double>(0, 2) - Matrix<float>(1, 0)));
	BOOST_CHECK_NO_THROW((Matrix<double>(0, 3) - Matrix<float>(4, 0)));

	BOOST_CHECK_NO_THROW((Matrix<double>(1, 1) - Matrix<int>(0, 2)));
	BOOST_CHECK_NO_THROW((Matrix<int>(3, 0) - Matrix<float>(4, 1)));
	BOOST_CHECK_NO_THROW((Matrix<short>(3, 4) - Matrix<float>(3, 6)));
	BOOST_CHECK_NO_THROW((Matrix<int>(2, 4) - Matrix<float>(5, 4)));

	BOOST_CHECK_NO_THROW(operator-(Matrix<int>(2, 4), Matrix<float>(5, 4))(0, 0));
	BOOST_CHECK_NO_THROW((Matrix<int>(2, 4) - Matrix<float>(2, 5))(0, 0));

	// ----------

	BOOST_CHECK_THROW(operator-(CMatrix<int, 0, 1>(), Matrix<float>())(0, 0), Base::IndexError);
	BOOST_CHECK_THROW(operator-(Matrix<double>(0, 0), Matrix<float>(1, 0))(10, 12), Base::IndexError);
	BOOST_CHECK_THROW(operator-(Matrix<double>(0, 2), Matrix<float>(1, 0))(3, 0), Base::IndexError);
	BOOST_CHECK_THROW(operator-(Matrix<double>(0, 3), Matrix<float>(4, 0)).getSize1(), Base::SizeError);
	BOOST_CHECK_THROW(operator-(Matrix<double>(0, 3), Matrix<float>(4, 0)).getSize2(), Base::SizeError);

	BOOST_CHECK_THROW(operator-(Matrix<double>(1, 1), Matrix<int>(0, 2))(1, 2), Base::IndexError);
	BOOST_CHECK_THROW(operator-(Matrix<int>(3, 0), Matrix<float>(4, 1))(2, 0), Base::IndexError);
	BOOST_CHECK_THROW(operator-(Matrix<short>(3, 4), Matrix<float>(3, 6))(5, 1), Base::IndexError);

	BOOST_CHECK_THROW((CMatrix<int, 0, 1>() - Matrix<float>())(0, 0), Base::IndexError);
	BOOST_CHECK_THROW((Matrix<double>(0, 0) - Matrix<float>(1, 0))(10, 12), Base::IndexError);
	BOOST_CHECK_THROW((Matrix<double>(0, 2) - Matrix<float>(1, 0))(3, 0), Base::IndexError);
	BOOST_CHECK_THROW((Matrix<double>(0, 3) - Matrix<float>(4, 0))(1, 1), Base::IndexError);

	BOOST_CHECK_THROW((Matrix<double>(1, 1) - Matrix<int>(0, 2))(1, 2), Base::IndexError);
	BOOST_CHECK_THROW((Matrix<int>(3, 0) - Matrix<float>(4, 1))(2, 0), Base::IndexError);
	BOOST_CHECK_THROW((Matrix<short>(3, 4) - Matrix<float>(3, 6))(5, 1), Base::IndexError);

	// ----------

	Matrix<double> m1(3, 0);
	Matrix<int> m2(3, 0);

	checkMatrixSubtraction(m1, m2);

	// ----------

	m1.resize(3, 1);
	m2.resize(3, 1);

	m1(0, 0) = -2.3;
	m1(1, 0) = 1.0;
	m1(2, 0) = -21.20;

	m2(0, 0) = -3;
	m2(1, 0) = 2;
	m2(2, 0) = 12;

	checkMatrixSubtraction(m1, m2);

	// ----------

	m1.resize(3, 2, true);
	m2.resize(3, 2, true);

	m1(0, 1) = 0.3;
	m1(1, 1) = -21.0;
	m1(2, 1) = 220;

	m2(0, 1) = 5;
	m2(1, 1) = -6;
	m2(2, 1) = 9;

	checkMatrixSubtraction(m1, m2);

	// ----------

	m1.resize(3, 3, true);
	m2.resize(3, 3, true);

	m1(0, 2) = 0.3;
	m1(1, 2) = -21.0;
	m1(2, 2) = 220;

	m2(0, 2) = 15;
	m2(1, 2) = 2;
	m2(2, 2) = -2;

	checkMatrixSubtraction(m1, m2);

	// ----------

	m1.resize(3, 4, true);
	m2.resize(3, 4, true);

	m1(0, 3) = 0.3;
	m1(1, 3) = 0.0;
	m1(2, 3) = 2.2;

	m2(0, 3) = 15;
	m2(1, 3) = 2;
	m2(2, 3) = 0;

	checkMatrixSubtraction(m1, m2);

	// ----------

	Matrix<std::complex<double> > m3(3, 3);

	m1.resize(3, 3);

	checkMatrixSubtraction(m1, m3);

	// ----------

	m3(0, 0) = std::complex<double>(-3.0, 0.0);
	m3(1, 0) = std::complex<double>(2.2, -3.23);
	m3(2, 0) = std::complex<double>(5.0, -1.0);
	m3(0, 1) = std::complex<double>(-6.0, 534.0);
	m3(1, 1) = std::complex<double>(9.0, 0.0);
	m3(2, 1) = std::complex<double>(8.0, 2.3);
	m3(0, 2) = std::complex<double>(-7.0, -4.4);
	m3(1, 2) = std::complex<double>(26.0, 0.0002);
	m3(2, 2) = std::complex<double>(8.0, 2.3);

	checkMatrixSubtraction(m1, m3);

	// ----------
	
	Matrix<std::complex<double> > m4(m3);

	m4 *= -1.12;

	m4(2, 0) = std::complex<double>(18.0, 22.3);
	m4(2, 1) = std::complex<double>(17.2, 4.4);
	m4(2, 2) = std::complex<double>(6.0, 10.0002);

	checkMatrixSubtraction(m3, m4);

	// ----------

	m1.resize(1, 3, true);
	m2.resize(1, 3, true);

	checkMatrixSubtraction(m1, m2);

	// ----------

	m1.resize(0, 3);
	m2.resize(0, 3);

	checkMatrixSubtraction(m1, m2);
}

BOOST_AUTO_TEST_CASE(MatrixElemDivFunctionTest)
{
	using namespace CDPL;
	using namespace Math;

	BOOST_CHECK_NO_THROW(elemDiv(CMatrix<int, 0, 1>(), Matrix<float>()));
	BOOST_CHECK_NO_THROW(elemDiv(Matrix<double>(0, 0), Matrix<float>(1, 0)));
	BOOST_CHECK_NO_THROW(elemDiv(Matrix<double>(0, 2), Matrix<float>(1, 0)));
	BOOST_CHECK_NO_THROW(elemDiv(Matrix<double>(0, 3), Matrix<float>(4, 0)));

	BOOST_CHECK_NO_THROW(elemDiv(Matrix<double>(1, 1), Matrix<int>(0, 2)));
	BOOST_CHECK_NO_THROW(elemDiv(Matrix<int>(3, 0), Matrix<float>(4, 1)));
	BOOST_CHECK_NO_THROW(elemDiv(Matrix<short>(3, 4), Matrix<float>(3, 6)));
	BOOST_CHECK_NO_THROW(elemDiv(Matrix<int>(2, 4), Matrix<float>(5, 4)));

	BOOST_CHECK_NO_THROW(elemDiv(Matrix<int>(2, 4), Matrix<float>(5, 4))(0, 0));
	BOOST_CHECK_NO_THROW(elemDiv(Matrix<int>(2, 4), Matrix<float>(2, 5))(0, 0));

	// ----------

	BOOST_CHECK_THROW(elemDiv(CMatrix<int, 0, 1>(), Matrix<float>())(0, 0), Base::IndexError);
	BOOST_CHECK_THROW(elemDiv(Matrix<double>(0, 0), Matrix<float>(1, 0))(10, 12), Base::IndexError);
	BOOST_CHECK_THROW(elemDiv(Matrix<double>(0, 2), Matrix<float>(1, 0))(3, 0), Base::IndexError);
	BOOST_CHECK_THROW(elemDiv(Matrix<double>(0, 3), Matrix<float>(4, 0)).getSize1(), Base::SizeError);
	BOOST_CHECK_THROW(elemDiv(Matrix<double>(0, 3), Matrix<float>(4, 0)).getSize2(), Base::SizeError);

	BOOST_CHECK_THROW(elemDiv(Matrix<double>(1, 1), Matrix<int>(0, 2))(1, 2), Base::IndexError);
	BOOST_CHECK_THROW(elemDiv(Matrix<int>(3, 0), Matrix<float>(4, 1))(2, 0), Base::IndexError);
	BOOST_CHECK_THROW(elemDiv(Matrix<short>(3, 4), Matrix<float>(3, 6))(5, 1), Base::IndexError);

	// ----------

	Matrix<double> m1(3, 0, 1.0);
	Matrix<int> m2(3, 0, 1);

	checkMatrixElemDivFunction(m1, m2);

	// ----------

	m1.resize(3, 1);
	m2.resize(3, 1);

	m1(0, 0) = -2.3;
	m1(1, 0) = 1.0;
	m1(2, 0) = -21.20;

	m2(0, 0) = -3;
	m2(1, 0) = 2;
	m2(2, 0) = 12;

	checkMatrixElemDivFunction(m1, m2);

	// ----------

	m1.resize(3, 2, true);
	m2.resize(3, 2, true);

	m1(0, 1) = 0.3;
	m1(1, 1) = -21.0;
	m1(2, 1) = 220;

	m2(0, 1) = 5;
	m2(1, 1) = -6;
	m2(2, 1) = 9;

	checkMatrixElemDivFunction(m1, m2);

	// ----------

	m1.resize(3, 3, true);
	m2.resize(3, 3, true);

	m1(0, 2) = 0.3;
	m1(1, 2) = -21.0;
	m1(2, 2) = 220;

	m2(0, 2) = 15;
	m2(1, 2) = 2;
	m2(2, 2) = -2;

	checkMatrixElemDivFunction(m1, m2);

	// ----------

	m1.resize(3, 4, true);
	m2.resize(3, 4, true);

	m1(0, 3) = 0.3;
	m1(1, 3) = 0.001;
	m1(2, 3) = 2.2;

	m2(0, 3) = 15;
	m2(1, 3) = 2;
	m2(2, 3) = 1;

	checkMatrixElemDivFunction(m1, m2);

	// ----------

	Matrix<std::complex<double> > m3(3, 3, std::complex<double>(0.1, 0.3));

	m1.resize(3, 3, true);

	checkMatrixElemDivFunction(m1, m3);

	// ----------

	m3(0, 0) = std::complex<double>(-3.0, 0.0);
	m3(1, 0) = std::complex<double>(2.2, -3.23);
	m3(2, 0) = std::complex<double>(5.0, -1.0);
	m3(0, 1) = std::complex<double>(-6.0, 534.0);
	m3(1, 1) = std::complex<double>(9.0, 0.0);
	m3(2, 1) = std::complex<double>(8.0, 2.3);
	m3(0, 2) = std::complex<double>(-7.0, -4.4);
	m3(1, 2) = std::complex<double>(26.0, 0.0002);
	m3(2, 2) = std::complex<double>(0.0, 2.3);

	checkMatrixElemDivFunction(m1, m3);

	// ----------
	
	Matrix<std::complex<double> > m4(m3);

	m4 *= -1.12;

	m4(2, 0) = std::complex<double>(18.0, 22.3);
	m4(2, 1) = std::complex<double>(17.2, 4.4);
	m4(2, 2) = std::complex<double>(-0.00001, 0.0);

	checkMatrixElemDivFunction(m3, m4);

	// ----------

	m1.resize(1, 3, true);
	m2.resize(1, 3, true);

	checkMatrixElemDivFunction(m1, m2);

	// ----------

	m1.resize(0, 3);
	m2.resize(0, 3);

	checkMatrixElemDivFunction(m1, m2);
}

BOOST_AUTO_TEST_CASE(MatrixElemProdFunctionTest)
{
	using namespace CDPL;
	using namespace Math;

	BOOST_CHECK_NO_THROW(elemProd(CMatrix<int, 0, 1>(), Matrix<float>()));
	BOOST_CHECK_NO_THROW(elemProd(Matrix<double>(0, 0), Matrix<float>(1, 0)));
	BOOST_CHECK_NO_THROW(elemProd(Matrix<double>(0, 2), Matrix<float>(1, 0)));
	BOOST_CHECK_NO_THROW(elemProd(Matrix<double>(0, 3), Matrix<float>(4, 0)));

	BOOST_CHECK_NO_THROW(elemProd(Matrix<double>(1, 1), Matrix<int>(0, 2)));
	BOOST_CHECK_NO_THROW(elemProd(Matrix<int>(3, 0), Matrix<float>(4, 1)));
	BOOST_CHECK_NO_THROW(elemProd(Matrix<short>(3, 4), Matrix<float>(3, 6)));
	BOOST_CHECK_NO_THROW(elemProd(Matrix<int>(2, 4), Matrix<float>(5, 4)));

	BOOST_CHECK_NO_THROW(elemProd(Matrix<int>(2, 4), Matrix<float>(5, 4))(0, 0));
	BOOST_CHECK_NO_THROW(elemProd(Matrix<int>(2, 4), Matrix<float>(2, 5))(0, 0));

	// ----------

	BOOST_CHECK_THROW(elemProd(CMatrix<int, 0, 1>(), Matrix<float>())(0, 0), Base::IndexError);
	BOOST_CHECK_THROW(elemProd(Matrix<double>(0, 0), Matrix<float>(1, 0))(10, 12), Base::IndexError);
	BOOST_CHECK_THROW(elemProd(Matrix<double>(0, 2), Matrix<float>(1, 0))(3, 0), Base::IndexError);
	BOOST_CHECK_THROW(elemProd(Matrix<double>(0, 3), Matrix<float>(4, 0)).getSize1(), Base::SizeError);
	BOOST_CHECK_THROW(elemProd(Matrix<double>(0, 3), Matrix<float>(4, 0)).getSize2(), Base::SizeError);

	BOOST_CHECK_THROW(elemProd(Matrix<double>(1, 1), Matrix<int>(0, 2))(1, 2), Base::IndexError);
	BOOST_CHECK_THROW(elemProd(Matrix<int>(3, 0), Matrix<float>(4, 1))(2, 0), Base::IndexError);
	BOOST_CHECK_THROW(elemProd(Matrix<short>(3, 4), Matrix<float>(3, 6))(5, 1), Base::IndexError);

	// ----------

	Matrix<double> m1(3, 0);
	Matrix<int> m2(3, 0);

	checkMatrixElemProdFunction(m1, m2);

	// ----------

	m1.resize(3, 1);
	m2.resize(3, 1);

	m1(0, 0) = -2.3;
	m1(1, 0) = 1.0;
	m1(2, 0) = -21.20;

	m2(0, 0) = -3;
	m2(1, 0) = 2;
	m2(2, 0) = 12;

	checkMatrixElemProdFunction(m1, m2);

	// ----------

	m1.resize(3, 2, true);
	m2.resize(3, 2, true);

	m1(0, 1) = 0.3;
	m1(1, 1) = -21.0;
	m1(2, 1) = 220;

	m2(0, 1) = 5;
	m2(1, 1) = -6;
	m2(2, 1) = 9;

	checkMatrixElemProdFunction(m1, m2);

	// ----------

	m1.resize(3, 3, true);
	m2.resize(3, 3, true);

	m1(0, 2) = 0.3;
	m1(1, 2) = -21.0;
	m1(2, 2) = 220;

	m2(0, 2) = 15;
	m2(1, 2) = 2;
	m2(2, 2) = -2;

	checkMatrixElemProdFunction(m1, m2);

	// ----------

	m1.resize(3, 4, true);
	m2.resize(3, 4, true);

	m1(0, 3) = 0.3;
	m1(1, 3) = 0.0;
	m1(2, 3) = 2.2;

	m2(0, 3) = 15;
	m2(1, 3) = 2;
	m2(2, 3) = 0;

	checkMatrixElemProdFunction(m1, m2);

	// ----------

	Matrix<std::complex<double> > m3(3, 3);

	m1.resize(3, 3);

	checkMatrixElemProdFunction(m1, m3);

	// ----------

	m3(0, 0) = std::complex<double>(-3.0, 0.0);
	m3(1, 0) = std::complex<double>(2.2, -3.23);
	m3(2, 0) = std::complex<double>(5.0, -1.0);
	m3(0, 1) = std::complex<double>(-6.0, 534.0);
	m3(1, 1) = std::complex<double>(9.0, 0.0);
	m3(2, 1) = std::complex<double>(8.0, 2.3);
	m3(0, 2) = std::complex<double>(-7.0, -4.4);
	m3(1, 2) = std::complex<double>(26.0, 0.0002);
	m3(2, 2) = std::complex<double>(8.0, 2.3);

	checkMatrixElemProdFunction(m1, m3);

	// ----------
	
	Matrix<std::complex<double> > m4(m3);

	m4 *= -1.12;

	m4(2, 0) = std::complex<double>(18.0, 22.3);
	m4(2, 1) = std::complex<double>(17.2, 4.4);
	m4(2, 2) = std::complex<double>(6.0, 10.0002);

	checkMatrixElemProdFunction(m3, m4);

	// ----------

	m1.resize(1, 3, true);
	m2.resize(1, 3, true);

	checkMatrixElemProdFunction(m1, m2);

	// ----------

	m1.resize(0, 3);
	m2.resize(0, 3);

	checkMatrixElemProdFunction(m1, m2);
}

BOOST_AUTO_TEST_CASE(MatrixMinusTest)
{
	using namespace CDPL;
	using namespace Math;

	checkMatrixMinusOperator(Matrix<double>());
	checkMatrixMinusOperator(Matrix<std::complex<double> >());
	checkMatrixMinusOperator(Matrix<double>(0, 3));
	checkMatrixMinusOperator(Matrix<std::complex<double> >(0, 4));
	checkMatrixMinusOperator(Matrix<double>(5, 0));
	checkMatrixMinusOperator(Matrix<std::complex<double> >(2, 0));

	// ----------

	CMatrix<double, 3, 2> m1(0.0);

	checkMatrixMinusOperator(m1);

	// ----------

	m1(0, 0) = -17.2;
	m1(0, 1) = 15.16;
	m1(1, 0) = 11.17;
	m1(1, 1) = -13.1;
	m1(2, 0) = -23.1;
	m1(2, 1) = -33.1;

	checkMatrixMinusOperator(m1);

	// ----------

    Matrix<std::complex<double> > m2(2, 3, std::complex<double>(0.0, 0.0));

	checkMatrixMinusOperator(m2);

	// ----------

    m2(0, 0) = std::complex<double>(-17.2, 4.5);
    m2(0, 1) = std::complex<double>(15.16, -14.5);
    m2(0, 2) = std::complex<double>(11.17, 22.15);
    m2(1, 0) = std::complex<double>(-13.1, 31.15);
    m2(1, 1) = std::complex<double>(-23.1, 11.3425);
    m2(1, 2) = std::complex<double>(-33.1, 1.25);

	checkMatrixMinusOperator(m2);
}

BOOST_AUTO_TEST_CASE(MatrixPlusTest)
{
	using namespace CDPL;
	using namespace Math;

	checkMatrixPlusOperator(Matrix<double>());
	checkMatrixPlusOperator(Matrix<std::complex<double> >());
	checkMatrixPlusOperator(Matrix<double>(0, 3));
	checkMatrixPlusOperator(Matrix<std::complex<double> >(0, 4));
	checkMatrixPlusOperator(Matrix<double>(5, 0));
	checkMatrixPlusOperator(Matrix<std::complex<double> >(2, 0));

	// ----------

	CMatrix<double, 3, 2> m1(0.0);

	checkMatrixPlusOperator(m1);

	// ----------

	m1(0, 0) = -17.2;
	m1(0, 1) = 15.16;
	m1(1, 0) = 11.17;
	m1(1, 1) = -13.1;
	m1(2, 0) = -23.1;
	m1(2, 1) = -33.1;

	checkMatrixPlusOperator(m1);

	// ----------

    Matrix<std::complex<double> > m2(2, 3, std::complex<double>(0.0, 0.0));

	checkMatrixPlusOperator(m2);

	// ----------

    m2(0, 0) = std::complex<double>(-17.2, 4.5);
    m2(0, 1) = std::complex<double>(15.16, -14.5);
    m2(0, 2) = std::complex<double>(11.17, 22.15);
    m2(1, 0) = std::complex<double>(-13.1, 31.15);
    m2(1, 1) = std::complex<double>(-23.1, 11.3425);
    m2(1, 2) = std::complex<double>(-33.1, 1.25);

	checkMatrixPlusOperator(m2);
}

BOOST_AUTO_TEST_CASE(MatrixEqualTest)
{
	using namespace CDPL;
	using namespace Math;

	BOOST_CHECK((Matrix<int>(0, 0) == CMatrix<float, 0, 0>()));
	BOOST_CHECK_EQUAL(operator==(Matrix<int>(0, 0), CMatrix<float, 0, 0>()), (Matrix<int>(0, 0) == CMatrix<float, 0, 0>()));

	BOOST_CHECK((Matrix<int>(3, 3, 1) == CMatrix<float, 3, 3>(1.0f)));
	BOOST_CHECK_EQUAL(operator==(Matrix<int>(3, 3, 1), CMatrix<float, 3, 3>(1.0f)), (Matrix<int>(3, 3, 1) == CMatrix<float, 3, 3>(1.0f)));

	// ----------

	CMatrix<int, 4, 4> m1(0);
	
	m1(0, 0) = 1;
	m1(0, 3) = 2;
	m1(3, 0) = -3;
	m1(3, 3) = 4;

	Matrix<double> m2;

	BOOST_CHECK(!(m1 == m2));
	BOOST_CHECK_EQUAL(operator==(m1, m2), (m1 == m2));

	BOOST_CHECK(!(m2 == m1));
	BOOST_CHECK_EQUAL(operator==(m2, m1), (m2 == m1));

	m2.resize(2, 2);

	BOOST_CHECK(!(m1 == m2));
	BOOST_CHECK_EQUAL(operator==(m1, m2), (m1 == m2));

	BOOST_CHECK(!(m2 == m1));
	BOOST_CHECK_EQUAL(operator==(m2, m1), (m2 == m1));

	m2.resize(4, 4);

	BOOST_CHECK(!(m1 == m2));
	BOOST_CHECK_EQUAL(operator==(m1, m2), (m1 == m2));

	BOOST_CHECK(!(m2 == m1));
	BOOST_CHECK_EQUAL(operator==(m2, m1), (m2 == m1));

	m2(0, 0) = 1;

	BOOST_CHECK(!(m1 == m2));
	BOOST_CHECK_EQUAL(operator==(m1, m2), (m1 == m2));

	BOOST_CHECK(!(m2 == m1));
	BOOST_CHECK_EQUAL(operator==(m2, m1), (m2 == m1));

	m2(0, 3) = 2;

	BOOST_CHECK(!(m1 == m2));
	BOOST_CHECK_EQUAL(operator==(m1, m2), (m1 == m2));

	BOOST_CHECK(!(m2 == m1));
	BOOST_CHECK_EQUAL(operator==(m2, m1), (m2 == m1));

	m2(3, 0) = -3;

	BOOST_CHECK(!(m1 == m2));
	BOOST_CHECK_EQUAL(operator==(m1, m2), (m1 == m2));

	BOOST_CHECK(!(m2 == m1));
	BOOST_CHECK_EQUAL(operator==(m2, m1), (m2 == m1));

	m2(3, 3) = 4;

	BOOST_CHECK((m1 == m2));
	BOOST_CHECK_EQUAL(operator==(m1, m2), (m1 == m2));

	BOOST_CHECK((m2 == m1));
	BOOST_CHECK_EQUAL(operator==(m2, m1), (m2 == m1));

	// ----------

	m2(2, 2) = 5;

	BOOST_CHECK(!(m1 == m2));
	BOOST_CHECK_EQUAL(operator==(m1, m2), (m1 == m2));

	BOOST_CHECK(!(m2 == m1));
	BOOST_CHECK_EQUAL(operator==(m2, m1), (m2 == m1));

	// ----------

	m2(2, 2) = 0;

	BOOST_CHECK((m1 == m2));
	BOOST_CHECK_EQUAL(operator==(m1, m2), (m1 == m2));

	BOOST_CHECK((m2 == m1));
	BOOST_CHECK_EQUAL(operator==(m2, m1), (m2 == m1));

	// ----------

	m2.resize(5, 4);

	BOOST_CHECK(!(m1 == m2));
	BOOST_CHECK_EQUAL(operator==(m1, m2), (m1 == m2));

	BOOST_CHECK(!(m2 == m1));
	BOOST_CHECK_EQUAL(operator==(m2, m1), (m2 == m1));

	// ----------

	m2.resize(4, 4);

	BOOST_CHECK((m1 == m2));
	BOOST_CHECK_EQUAL(operator==(m1, m2), (m1 == m2));

	BOOST_CHECK((m2 == m1));
	BOOST_CHECK_EQUAL(operator==(m2, m1), (m2 == m1));
}

BOOST_AUTO_TEST_CASE(MatrixNotEqualTest)
{
	using namespace CDPL;
	using namespace Math;

	BOOST_CHECK(!(Matrix<int>(0, 0) != CMatrix<float, 0, 0>()));
	BOOST_CHECK_EQUAL(operator!=(Matrix<int>(0, 0), CMatrix<float, 0, 0>()), (Matrix<int>(0, 0) != CMatrix<float, 0, 0>()));

	BOOST_CHECK(!(Matrix<int>(3, 3, 1) != CMatrix<float, 3, 3>(1.0f)));
	BOOST_CHECK_EQUAL(operator!=(Matrix<int>(3, 3, 1), CMatrix<float, 3, 3>(1.0f)), (Matrix<int>(3, 3, 1) != CMatrix<float, 3, 3>(1.0f)));

	// ----------

	CMatrix<int, 4, 4> m1(0);
	
	m1(0, 0) = 1;
	m1(0, 3) = 2;
	m1(3, 0) = -3;
	m1(3, 3) = 4;

	Matrix<double> m2;

	BOOST_CHECK((m1 != m2));
	BOOST_CHECK_EQUAL(operator!=(m1, m2), (m1 != m2));

	BOOST_CHECK((m2 != m1));
	BOOST_CHECK_EQUAL(operator!=(m2, m1), (m2 != m1));

	m2.resize(2, 2);

	BOOST_CHECK((m1 != m2));
	BOOST_CHECK_EQUAL(operator!=(m1, m2), (m1 != m2));

	BOOST_CHECK((m2 != m1));
	BOOST_CHECK_EQUAL(operator!=(m2, m1), (m2 != m1));

	m2.resize(4, 4);

	BOOST_CHECK((m1 != m2));
	BOOST_CHECK_EQUAL(operator!=(m1, m2), (m1 != m2));

	BOOST_CHECK((m2 != m1));
	BOOST_CHECK_EQUAL(operator!=(m2, m1), (m2 != m1));

	m2(0, 0) = 1;

	BOOST_CHECK((m1 != m2));
	BOOST_CHECK_EQUAL(operator!=(m1, m2), (m1 != m2));

	BOOST_CHECK((m2 != m1));
	BOOST_CHECK_EQUAL(operator!=(m2, m1), (m2 != m1));

	m2(0, 3) = 2;

	BOOST_CHECK((m1 != m2));
	BOOST_CHECK_EQUAL(operator!=(m1, m2), (m1 != m2));

	BOOST_CHECK((m2 != m1));
	BOOST_CHECK_EQUAL(operator!=(m2, m1), (m2 != m1));

	m2(3, 0) = -3;

	BOOST_CHECK((m1 != m2));
	BOOST_CHECK_EQUAL(operator!=(m1, m2), (m1 != m2));

	BOOST_CHECK((m2 != m1));
	BOOST_CHECK_EQUAL(operator!=(m2, m1), (m2 != m1));

	m2(3, 3) = 4;

	BOOST_CHECK(!(m1 != m2));
	BOOST_CHECK_EQUAL(operator!=(m1, m2), (m1 != m2));

	BOOST_CHECK(!(m2 != m1));
	BOOST_CHECK_EQUAL(operator!=(m2, m1), (m2 != m1));

	// ----------

	m2(2, 2) = 5;

	BOOST_CHECK((m1 != m2));
	BOOST_CHECK_EQUAL(operator!=(m1, m2), (m1 != m2));

	BOOST_CHECK((m2 != m1));
	BOOST_CHECK_EQUAL(operator!=(m2, m1), (m2 != m1));

	// ----------

	m2(2, 2) = 0;

	BOOST_CHECK(!(m1 != m2));
	BOOST_CHECK_EQUAL(operator!=(m1, m2), (m1 != m2));

	BOOST_CHECK(!(m2 != m1));
	BOOST_CHECK_EQUAL(operator!=(m2, m1), (m2 != m1));

	// ----------

	m2.resize(5, 4);

	BOOST_CHECK((m1 != m2));
	BOOST_CHECK_EQUAL(operator!=(m1, m2), (m1 != m2));

	BOOST_CHECK((m2 != m1));
	BOOST_CHECK_EQUAL(operator!=(m2, m1), (m2 != m1));

	// ----------

	m2.resize(4, 4);

	BOOST_CHECK(!(m1 != m2));
	BOOST_CHECK_EQUAL(operator!=(m1, m2), (m1 != m2));

	BOOST_CHECK(!(m2 != m1));
	BOOST_CHECK_EQUAL(operator!=(m2, m1), (m2 != m1));
}

BOOST_AUTO_TEST_CASE(MatrixEqualsFunctionTest)
{
	using namespace CDPL;
	using namespace Math;

	BOOST_CHECK(equals(Matrix<int>(), CMatrix<float, 0, 0>(), 0));
	BOOST_CHECK(equals(Matrix<int>(3, 3, 1), CMatrix<float, 3, 3>(1.0f), 0.0));

	// ----------

	CMatrix<int, 4, 4> m1(0);

	m1(0, 0) = 1;
	m1(0, 3) = 2;
	m1(3, 0) = -3;
	m1(3, 3) = 4;

	Matrix<double> m2;

	BOOST_CHECK(!equals(m1, m2, 0.0f));
	BOOST_CHECK(!equals(m2, m1, 10.0f));

	m2.resize(2, 3);

	BOOST_CHECK(!equals(m1, m2, 10.0f));
	BOOST_CHECK(!equals(m2, m1, 0.0f));

	m2.resize(4, 4);

	BOOST_CHECK(!equals(m1, m2, 0.0f));
	BOOST_CHECK(!equals(m2, m1, 0.0f));

	BOOST_CHECK(!equals(m1, m2, 3.9999f));
	BOOST_CHECK(!equals(m2, m1, 3.9999));

	BOOST_CHECK(equals(m1, m2, 4.0f));
	BOOST_CHECK(equals(m2, m1, 4));
	BOOST_CHECK(!equals(m2, m1, -4));

	m2(3, 3) = 4;

	BOOST_CHECK(!equals(m1, m2, 0.0f));
	BOOST_CHECK(!equals(m2, m1, 0.0f));

	BOOST_CHECK(!equals(m1, m2, 2.9999));
	BOOST_CHECK(!equals(m2, m1, 2.9999L));

	BOOST_CHECK(equals(m1, m2, 3.0));
	BOOST_CHECK(equals(m2, m1, 3));
	BOOST_CHECK(!equals(m2, m1, -3));

	m2(3, 0) = -3;

	BOOST_CHECK(!equals(m1, m2, 0.0f));
	BOOST_CHECK(!equals(m2, m1, 0.0f));

	BOOST_CHECK(!equals(m1, m2, 1.9999f));
	BOOST_CHECK(!equals(m2, m1, 1.9999));

	BOOST_CHECK(equals(m1, m2, 2));
	BOOST_CHECK(equals(m2, m1, 2.0f));
	BOOST_CHECK(!equals(m2, m1, -2.0f));

	m2(0, 3) = 2;

	BOOST_CHECK(!equals(m1, m2, 0.0f));
	BOOST_CHECK(!equals(m2, m1, 0.0f));

	BOOST_CHECK(!equals(m1, m2, 0.9999));
	BOOST_CHECK(!equals(m2, m1, 0.9999L));

	BOOST_CHECK(equals(m1, m2, 1));
	BOOST_CHECK(equals(m2, m1, 1.0));
	BOOST_CHECK(!equals(m2, m1, -1.0));

	m2(0, 0) = 1;

	BOOST_CHECK(equals(m1, m2, 0.0f));
	BOOST_CHECK(equals(m2, m1, 0));
	BOOST_CHECK(!equals(m2, m1, -0.000001));

	m2(0, 0) = -1;

	BOOST_CHECK(!equals(m1, m2, 0.0f));
	BOOST_CHECK(!equals(m2, m1, 1));

	BOOST_CHECK(!equals(m1, m2, 1));
	BOOST_CHECK(!equals(m2, m1, 1.9999f));

	BOOST_CHECK(equals(m1, m2, 2.0f));
	BOOST_CHECK(equals(m2, m1, 2));

	m2(0, 0) = 1;

	BOOST_CHECK(equals(m1, m2, 0.0f));
	BOOST_CHECK(equals(m2, m1, 0));

	// ----------

	m2(2, 2) = 5;

	BOOST_CHECK(!equals(m1, m2, 4));
	BOOST_CHECK(!equals(m2, m1, 4.9999));

	BOOST_CHECK(equals(m1, m2, 5));
	BOOST_CHECK(equals(m2, m1, 5));
	BOOST_CHECK(!equals(m2, m1, -5));

	// ----------

	m2(2, 2) = 0;

	BOOST_CHECK(equals(m1, m2, 0.0f));
	BOOST_CHECK(equals(m2, m1, 0));
	BOOST_CHECK(!equals(m2, m1, -0.0000003));

	// ----------

	m2.resize(4, 5);

	BOOST_CHECK(!equals(m1, m2, 10));
	BOOST_CHECK(!equals(m2, m1, 4.0));
	BOOST_CHECK(!equals(m2, m1, -4.0));

	// ----------

	m2.resize(4, 4);

	BOOST_CHECK(equals(m1, m2, 0.0f));
	BOOST_CHECK(equals(m2, m1, 0));
	BOOST_CHECK(!equals(m2, m1, -0.000003));
}

BOOST_AUTO_TEST_CASE(MatrixConjFunctionTest)
{
	using namespace CDPL;
	using namespace Math;

	checkMatrixConjFunction(Matrix<double>());
	checkMatrixConjFunction(Matrix<std::complex<double> >());
	checkMatrixConjFunction(Matrix<double>(0, 3));
	checkMatrixConjFunction(Matrix<std::complex<double> >(0, 4));
	checkMatrixConjFunction(Matrix<double>(5, 0));
	checkMatrixConjFunction(Matrix<std::complex<double> >(2, 0));

	// ----------

	CMatrix<double, 3, 2> m1(0.0);

	checkMatrixConjFunction(m1);

	// ----------

	m1(0, 0) = -17.2;
	m1(0, 1) = 15.16;
	m1(1, 0) = 11.17;
	m1(1, 1) = -13.1;
	m1(2, 0) = -23.1;
	m1(2, 1) = -33.1;

	checkMatrixConjFunction(m1);

	// ----------

    Matrix<std::complex<double> > m2(2, 3, std::complex<double>(0.0, 0.0));

	checkMatrixConjFunction(m2);

	// ----------

    m2(0, 0) = std::complex<double>(-17.2, 4.5);
    m2(0, 1) = std::complex<double>(15.16, -14.5);
    m2(0, 2) = std::complex<double>(11.17, 22.15);
    m2(1, 0) = std::complex<double>(-13.1, 31.15);
    m2(1, 1) = std::complex<double>(-23.1, 11.3425);
    m2(1, 2) = std::complex<double>(-33.1, 1.25);

	checkMatrixConjFunction(m2);
}

BOOST_AUTO_TEST_CASE(MatrixHermFunctionTest)
{
	using namespace CDPL;
	using namespace Math;

	checkMatrixHermFunction(Matrix<double>());
	checkMatrixHermFunction(Matrix<std::complex<double> >());
	checkMatrixHermFunction(Matrix<double>(0, 3));
	checkMatrixHermFunction(Matrix<std::complex<double> >(0, 4));
	checkMatrixHermFunction(Matrix<double>(5, 0));
	checkMatrixHermFunction(Matrix<std::complex<double> >(2, 0));

	// ----------

	CMatrix<double, 3, 2> m1(0.0);

	checkMatrixHermFunction(m1);

	// ----------

	m1(0, 0) = -17.2;
	m1(0, 1) = 15.16;
	m1(1, 0) = 11.17;
	m1(1, 1) = -13.1;
	m1(2, 0) = -23.1;
	m1(2, 1) = -33.1;

	checkMatrixHermFunction(m1);

	// ----------

    Matrix<std::complex<double> > m2(2, 3, std::complex<double>(0.0, 0.0));

	checkMatrixHermFunction(m2);

	// ----------

    m2(0, 0) = std::complex<double>(-17.2, 4.5);
    m2(0, 1) = std::complex<double>(15.16, -14.5);
    m2(0, 2) = std::complex<double>(11.17, 22.15);
    m2(1, 0) = std::complex<double>(-13.1, 31.15);
    m2(1, 1) = std::complex<double>(-23.1, 11.3425);
    m2(1, 2) = std::complex<double>(-33.1, 1.25);

	checkMatrixHermFunction(m2);
}

BOOST_AUTO_TEST_CASE(MatrixRealFunctionTest)
{
	using namespace CDPL;
	using namespace Math;

	checkMatrixRealFunction(Matrix<double>());
	checkMatrixRealFunction(Matrix<std::complex<double> >());
	checkMatrixRealFunction(Matrix<double>(0, 3));
	checkMatrixRealFunction(Matrix<std::complex<double> >(0, 4));
	checkMatrixRealFunction(Matrix<double>(5, 0));
	checkMatrixRealFunction(Matrix<std::complex<double> >(2, 0));

	// ----------

	CMatrix<double, 3, 2> m1(0.0);

	checkMatrixRealFunction(m1);

	// ----------

	m1(0, 0) = -17.2;
	m1(0, 1) = 15.16;
	m1(1, 0) = 11.17;
	m1(1, 1) = -13.1;
	m1(2, 0) = -23.1;
	m1(2, 1) = -33.1;

	checkMatrixRealFunction(m1);

	// ----------

    Matrix<std::complex<double> > m2(2, 3, std::complex<double>(0.0, 0.0));

	checkMatrixRealFunction(m2);

	// ----------

    m2(0, 0) = std::complex<double>(-17.2, 4.5);
    m2(0, 1) = std::complex<double>(15.16, -14.5);
    m2(0, 2) = std::complex<double>(11.17, 22.15);
    m2(1, 0) = std::complex<double>(-13.1, 31.15);
    m2(1, 1) = std::complex<double>(-23.1, 11.3425);
    m2(1, 2) = std::complex<double>(-33.1, 1.25);

	checkMatrixRealFunction(m2);
}

BOOST_AUTO_TEST_CASE(MatrixImagFunctionTest)
{
	using namespace CDPL;
	using namespace Math;

	checkMatrixImagFunction(Matrix<double>());
	checkMatrixImagFunction(Matrix<std::complex<double> >());
	checkMatrixImagFunction(Matrix<double>(0, 3));
	checkMatrixImagFunction(Matrix<std::complex<double> >(0, 4));
	checkMatrixImagFunction(Matrix<double>(5, 0));
	checkMatrixImagFunction(Matrix<std::complex<double> >(2, 0));

	// ----------

	CMatrix<double, 3, 2> m1(0.0);

	checkMatrixImagFunction(m1);

	// ----------

	m1(0, 0) = -17.2;
	m1(0, 1) = 15.16;
	m1(1, 0) = 11.17;
	m1(1, 1) = -13.1;
	m1(2, 0) = -23.1;
	m1(2, 1) = -33.1;

	checkMatrixImagFunction(m1);

	// ----------

    Matrix<std::complex<double> > m2(2, 3, std::complex<double>(0.0, 0.0));

	checkMatrixImagFunction(m2);

	// ----------

    m2(0, 0) = std::complex<double>(-17.2, 4.5);
    m2(0, 1) = std::complex<double>(15.16, -14.5);
    m2(0, 2) = std::complex<double>(11.17, 22.15);
    m2(1, 0) = std::complex<double>(-13.1, 31.15);
    m2(1, 1) = std::complex<double>(-23.1, 11.3425);
    m2(1, 2) = std::complex<double>(-33.1, 1.25);

	checkMatrixImagFunction(m2);
}

BOOST_AUTO_TEST_CASE(MatrixVectorMultiplicationTest)
{
	using namespace CDPL;
	using namespace Math;

	BOOST_CHECK_NO_THROW(operator*(Matrix<float>(), CVector<int, 1>()));
	BOOST_CHECK_NO_THROW(operator*(Matrix<float>(0, 1), Vector<double>(0)));
	BOOST_CHECK_NO_THROW(operator*(Matrix<float>(0, 1), Vector<double>(2)));
	BOOST_CHECK_NO_THROW(operator*(Matrix<float>(0, 4), Vector<double>(3)));

	BOOST_CHECK_NO_THROW(operator*(Matrix<int>(2, 0), Vector<double>(1)));
	BOOST_CHECK_NO_THROW(operator*(Matrix<float>(1, 4), Vector<int>(0)));
	BOOST_CHECK_NO_THROW(operator*(Matrix<float>(66, 2), Vector<short>(3)));
	BOOST_CHECK_NO_THROW(operator*(Matrix<float>(1, 5), Vector<int>(2)));

	BOOST_CHECK_NO_THROW((Matrix<float>() * CVector<int, 1>()));
	BOOST_CHECK_NO_THROW((Matrix<float>(0, 1) * Vector<double>(0)));
	BOOST_CHECK_NO_THROW((Matrix<float>(0, 1) * Vector<double>(2)));
	BOOST_CHECK_NO_THROW((Matrix<float>(0, 4) * Vector<double>(3)));

	BOOST_CHECK_NO_THROW((Matrix<int>(2, 0) * Vector<double>(1)));
	BOOST_CHECK_NO_THROW((Matrix<float>(1, 4) * Vector<int>(0)));
	BOOST_CHECK_NO_THROW((Matrix<float>(66, 2) * Vector<short>(3)));
	BOOST_CHECK_NO_THROW((Matrix<float>(1, 5) * Vector<int>(2)));

	// ----------

	BOOST_CHECK_THROW(operator*(Matrix<float>(), CVector<int, 1>())(0), Base::SizeError);
	BOOST_CHECK_THROW(operator*(Matrix<float>(0, 1), Vector<double>(0))(2), Base::SizeError);
	BOOST_CHECK_THROW(operator*(Matrix<float>(0, 1), Vector<double>(2))(3), Base::SizeError);
	BOOST_CHECK_THROW(operator*(Matrix<float>(0, 4), Vector<double>(3))(1), Base::SizeError);

	BOOST_CHECK_THROW(operator*(Matrix<int>(2, 0), Vector<double>(1))(1), Base::SizeError);
	BOOST_CHECK_THROW(operator*(Matrix<float>(1, 4), Vector<int>(0))(2), Base::SizeError);
	BOOST_CHECK_THROW(operator*(Matrix<float>(66, 2), Vector<short>(3))(5), Base::SizeError);
	BOOST_CHECK_THROW(operator*(Matrix<float>(1, 5), Vector<int>(2))(0), Base::SizeError);

	BOOST_CHECK_THROW((Matrix<float>() * CVector<int, 1>())(0), Base::SizeError);
	BOOST_CHECK_THROW((Matrix<float>(0, 1) * Vector<double>(0))(2), Base::SizeError);
	BOOST_CHECK_THROW((Matrix<float>(0, 1) * Vector<double>(2))(3), Base::SizeError);
	BOOST_CHECK_THROW((Matrix<float>(0, 4) * Vector<double>(3))(1), Base::SizeError);

	BOOST_CHECK_THROW((Matrix<int>(2, 0) * Vector<double>(1))(1), Base::SizeError);
	BOOST_CHECK_THROW((Matrix<float>(1, 4) * Vector<int>(0))(2), Base::SizeError);
	BOOST_CHECK_THROW((Matrix<float>(66, 2) * Vector<short>(3))(5), Base::SizeError);
	BOOST_CHECK_THROW((Matrix<float>(1, 5) * Vector<int>(2))(0), Base::SizeError);

	// ----------

	Matrix<double> m1(3, 0);

	checkMatrixVectorMultiplication(m1, Vector<int>());
	checkMatrixVectorMultiplication(m1, Vector<std::complex<double> >());

	// ----------

	m1.resize(3, 1);

	m1(0, 0) = -2.3;
	m1(1, 0) = 1.0;
	m1(2, 0) = -21.20;

	checkMatrixVectorMultiplication(m1, Vector<float>(1, -2.37f));
	checkMatrixVectorMultiplication(m1, Vector<std::complex<double> >(1, std::complex<double>(-2.37, 5.5)));

	// ----------

	m1.resize(3, 2, true);

	m1(0, 1) = 2;
	m1(1, 1) = -1.10;
	m1(2, 1) = 0.001;

	checkMatrixVectorMultiplication(m1, vec(-0.21, 100));
	checkMatrixVectorMultiplication(m1, vec(std::complex<double>(-0.21, 1.0), std::complex<double>(100, -3.2)));

	// ----------

	m1.resize(3, 3, true);

	m1(0, 2) = 0.12;
	m1(1, 2) = 2.10;
	m1(2, 2) = -20.001;

	checkMatrixVectorMultiplication(m1, vec(1, -2, 3));
	checkMatrixVectorMultiplication(m1, vec(std::complex<double>(-0.21, 1.0), std::complex<double>(100, -3.2), 
											std::complex<double>(10.2, 3.22)));

	// ----------

	m1.resize(3, 4, true);

	m1(0, 3) = 3;
	m1(1, 3) = 4;
	m1(2, 3) = 5;

	checkMatrixVectorMultiplication(m1, vec(6, 7.12, -1, 2));
	checkMatrixVectorMultiplication(m1, vec(std::complex<double>(0.21, 1.0), std::complex<double>(80.12, -3.2), 
											std::complex<double>(-10.2, 3.22), std::complex<double>(180.12, 0.0)));

	// ----------

	Matrix<std::complex<double> > m2(3, 0);

	checkMatrixVectorMultiplication(m2, Vector<double>());
	checkMatrixVectorMultiplication(m2, Vector<std::complex<double> >());

	// ----------

	m2.resize(3, 1);

	m2(0, 0) = std::complex<double>(-2.3, 5.12);
	m2(1, 0) = std::complex<double>(1.0, 0.0);
	m2(2, 0) = std::complex<double>(-21.20, -17.2);

	checkMatrixVectorMultiplication(m2, Vector<double>(1, -2.37));
	checkMatrixVectorMultiplication(m2, Vector<std::complex<double> >(1, std::complex<double>(-2.37, 5.5)));

	// ----------

	m2.resize(3, 2, true);

	m2(0, 1) = std::complex<double>(2, -4.3);
	m2(1, 1) = std::complex<double>(-1.10, -0.0002);
	m2(2, 1) = std::complex<double>(0.001, 0.1);

	checkMatrixVectorMultiplication(m2, vec(-0.21, 100));
	checkMatrixVectorMultiplication(m2, vec(std::complex<double>(-0.21, 1.0), std::complex<double>(100, -3.2)));

	// ----------

	m2.resize(3, 3, true);

	m2(0, 2) = std::complex<double>(0.12, 0.0);
	m2(1, 2) = std::complex<double>(2.10, 0.0);
	m2(2, 2) = std::complex<double>(-20.001, 0.0);

	checkMatrixVectorMultiplication(m2, vec(1.0, -2.0, 3.0));
	checkMatrixVectorMultiplication(m2, vec(std::complex<double>(-0.21, 1.0), std::complex<double>(100, -3.2), 
											std::complex<double>(10.2, 3.22)));

	// ----------

	m2.resize(3, 4, true);

	m2(0, 3) = std::complex<double>(3, 0.1);
	m2(1, 3) = std::complex<double>(4, 0.2);
	m2(2, 3) = std::complex<double>(5, -0.3);

	checkMatrixVectorMultiplication(m2, vec(6, 7.12, -1, 2));
	checkMatrixVectorMultiplication(m2, vec(std::complex<double>(0.21, 1.0), std::complex<double>(80.12, -3.2), 
											std::complex<double>(-10.2, 3.22), std::complex<double>(180.12, 0.0)));

	// ----------

	m2.resize(0, 4);

	checkMatrixVectorMultiplication(m2, vec(6, 7.12, -1, 2));
	checkMatrixVectorMultiplication(m2, vec(std::complex<double>(0.21, 1.0), std::complex<double>(80.12, -3.2), 
											std::complex<double>(-10.2, 3.22), std::complex<double>(180.12, 0.0)));
}

BOOST_AUTO_TEST_CASE(MatrixVectorProdFunctionTest)
{
	using namespace CDPL;
	using namespace Math;

	BOOST_CHECK_NO_THROW(prod(Matrix<float>(), CVector<int, 1>()));
	BOOST_CHECK_NO_THROW(prod(Matrix<float>(0, 1), Vector<double>(0)));
	BOOST_CHECK_NO_THROW(prod(Matrix<float>(0, 1), Vector<double>(2)));
	BOOST_CHECK_NO_THROW(prod(Matrix<float>(0, 4), Vector<double>(3)));

	BOOST_CHECK_NO_THROW(prod(Matrix<int>(2, 0), Vector<double>(1)));
	BOOST_CHECK_NO_THROW(prod(Matrix<float>(1, 4), Vector<int>(0)));
	BOOST_CHECK_NO_THROW(prod(Matrix<float>(66, 2), Vector<short>(3)));
	BOOST_CHECK_NO_THROW(prod(Matrix<float>(1, 5), Vector<int>(2)));

	// ----------

	BOOST_CHECK_THROW(prod(Matrix<float>(), CVector<int, 1>())(0), Base::SizeError);
	BOOST_CHECK_THROW(prod(Matrix<float>(0, 1), Vector<double>(0))(2), Base::SizeError);
	BOOST_CHECK_THROW(prod(Matrix<float>(0, 1), Vector<double>(2))(3), Base::SizeError);
	BOOST_CHECK_THROW(prod(Matrix<float>(0, 4), Vector<double>(3))(1), Base::SizeError);

	BOOST_CHECK_THROW(prod(Matrix<int>(2, 0), Vector<double>(1))(1), Base::SizeError);
	BOOST_CHECK_THROW(prod(Matrix<float>(1, 4), Vector<int>(0))(2), Base::SizeError);
	BOOST_CHECK_THROW(prod(Matrix<float>(66, 2), Vector<short>(3))(5), Base::SizeError);
	BOOST_CHECK_THROW(prod(Matrix<float>(1, 5), Vector<int>(2))(0), Base::SizeError);

	// ----------

	Vector<double> res_v;

	BOOST_CHECK_NO_THROW(prod(Matrix<float>(), CVector<int, 1>(), res_v));
	BOOST_CHECK_NO_THROW(prod(Matrix<float>(0, 1), Vector<double>(0), res_v));
	BOOST_CHECK_NO_THROW(prod(Matrix<float>(0, 1), Vector<double>(2), res_v));
	BOOST_CHECK_NO_THROW(prod(Matrix<float>(0, 4), Vector<double>(3), res_v));

	BOOST_CHECK_THROW(prod(Matrix<int>(2, 0), Vector<double>(1), res_v), Base::SizeError);
	BOOST_CHECK_THROW(prod(Matrix<float>(1, 4), Vector<int>(0), res_v), Base::SizeError);
	BOOST_CHECK_THROW(prod(Matrix<float>(66, 2), Vector<short>(3), res_v), Base::SizeError);
	BOOST_CHECK_THROW(prod(Matrix<float>(1, 5), Vector<int>(2), res_v), Base::SizeError);

	// ----------

	Matrix<double> m1(3, 0);

	checkMatrixVectorProdFunction(m1, Vector<int>());
	checkMatrixVectorProdFunction(m1, Vector<std::complex<double> >());

	// ----------

	m1.resize(3, 1);

	m1(0, 0) = -2.3;
	m1(1, 0) = 1.0;
	m1(2, 0) = -21.20;

	checkMatrixVectorProdFunction(m1, Vector<float>(1, -2.37f));
	checkMatrixVectorProdFunction(m1, Vector<std::complex<double> >(1, std::complex<double>(-2.37, 5.5)));

	// ----------

	m1.resize(3, 2, true);

	m1(0, 1) = 2;
	m1(1, 1) = -1.10;
	m1(2, 1) = 0.001;

	checkMatrixVectorProdFunction(m1, vec(-0.21, 100));
	checkMatrixVectorProdFunction(m1, vec(std::complex<double>(-0.21, 1.0), std::complex<double>(100, -3.2)));

	// ----------

	m1.resize(3, 3, true);

	m1(0, 2) = 0.12;
	m1(1, 2) = 2.10;
	m1(2, 2) = -20.001;

	checkMatrixVectorProdFunction(m1, vec(1, -2, 3));
	checkMatrixVectorProdFunction(m1, vec(std::complex<double>(-0.21, 1.0), std::complex<double>(100, -3.2), 
										  std::complex<double>(10.2, 3.22)));

	// ----------

	m1.resize(3, 4, true);

	m1(0, 3) = 3;
	m1(1, 3) = 4;
	m1(2, 3) = 5;

	checkMatrixVectorProdFunction(m1, vec(6, 7.12, -1, 2));
	checkMatrixVectorProdFunction(m1, vec(std::complex<double>(0.21, 1.0), std::complex<double>(80.12, -3.2), 
										  std::complex<double>(-10.2, 3.22), std::complex<double>(180.12, 0.0)));

	// ----------

	Matrix<std::complex<double> > m2(3, 0);

	checkMatrixVectorProdFunction(m2, Vector<double>());
	checkMatrixVectorProdFunction(m2, Vector<std::complex<double> >());

	// ----------

	m2.resize(3, 1);

	m2(0, 0) = std::complex<double>(-2.3, 5.12);
	m2(1, 0) = std::complex<double>(1.0, 0.0);
	m2(2, 0) = std::complex<double>(-21.20, -17.2);

	checkMatrixVectorProdFunction(m2, Vector<double>(1, -2.37));
	checkMatrixVectorProdFunction(m2, Vector<std::complex<double> >(1, std::complex<double>(-2.37, 5.5)));

	// ----------

	m2.resize(3, 2, true);

	m2(0, 1) = std::complex<double>(2, -4.3);
	m2(1, 1) = std::complex<double>(-1.10, -0.0002);
	m2(2, 1) = std::complex<double>(0.001, 0.1);

	checkMatrixVectorProdFunction(m2, vec(-0.21, 100));
	checkMatrixVectorProdFunction(m2, vec(std::complex<double>(-0.21, 1.0), std::complex<double>(100, -3.2)));

	// ----------

	m2.resize(3, 3, true);

	m2(0, 2) = std::complex<double>(0.12, 0.0);
	m2(1, 2) = std::complex<double>(2.10, 0.0);
	m2(2, 2) = std::complex<double>(-20.001, 0.0);

	checkMatrixVectorProdFunction(m2, vec(1.0, -2.0, 3.0));
	checkMatrixVectorProdFunction(m2, vec(std::complex<double>(-0.21, 1.0), std::complex<double>(100, -3.2), 
										  std::complex<double>(10.2, 3.22)));

	// ----------

	m2.resize(3, 4, true);

	m2(0, 3) = std::complex<double>(3, 0.1);
	m2(1, 3) = std::complex<double>(4, 0.2);
	m2(2, 3) = std::complex<double>(5, -0.3);

	checkMatrixVectorProdFunction(m2, vec(6, 7.12, -1, 2));
	checkMatrixVectorProdFunction(m2, vec(std::complex<double>(0.21, 1.0), std::complex<double>(80.12, -3.2), 
										  std::complex<double>(-10.2, 3.22), std::complex<double>(180.12, 0.0)));

	// ----------

	m2.resize(0, 4);

	checkMatrixVectorProdFunction(m2, vec(6, 7.12, -1, 2));
	checkMatrixVectorProdFunction(m2, vec(std::complex<double>(0.21, 1.0), std::complex<double>(80.12, -3.2), 
										  std::complex<double>(-10.2, 3.22), std::complex<double>(180.12, 0.0)));
}

BOOST_AUTO_TEST_CASE(VectorMatrixMultiplicationTest)
{
	using namespace CDPL;
	using namespace Math;

	BOOST_CHECK_NO_THROW(operator*(CVector<int, 1>(), Matrix<float>()));
	BOOST_CHECK_NO_THROW(operator*(Vector<double>(0), Matrix<float>(1, 0)));
	BOOST_CHECK_NO_THROW(operator*(Vector<double>(2), Matrix<float>(1, 0)));
	BOOST_CHECK_NO_THROW(operator*(Vector<double>(3), Matrix<float>(4, 0)));

	BOOST_CHECK_NO_THROW(operator*(Vector<double>(1), Matrix<int>(0, 2)));
	BOOST_CHECK_NO_THROW(operator*(Vector<int>(0), Matrix<float>(4, 1)));
	BOOST_CHECK_NO_THROW(operator*(Vector<short>(3), Matrix<float>(2, 66)));
	BOOST_CHECK_NO_THROW(operator*(Vector<int>(2), Matrix<float>(5, 1)));

	BOOST_CHECK_NO_THROW((CVector<int, 1>() * Matrix<float>()));
	BOOST_CHECK_NO_THROW((Vector<double>(0) * Matrix<float>(1, 0)));
	BOOST_CHECK_NO_THROW((Vector<double>(2) * Matrix<float>(1, 0)));
	BOOST_CHECK_NO_THROW((Vector<double>(3) * Matrix<float>(4, 0)));

	BOOST_CHECK_NO_THROW((Vector<double>(1) * Matrix<int>(0, 2)));
	BOOST_CHECK_NO_THROW((Vector<int>(0) * Matrix<float>(4, 1)));
	BOOST_CHECK_NO_THROW((Vector<short>(3) * Matrix<float>(2, 66)));
	BOOST_CHECK_NO_THROW((Vector<int>(2) * Matrix<float>(5, 1)));

	// ----------

	BOOST_CHECK_THROW(operator*(CVector<int, 1>(), Matrix<float>())(0), Base::SizeError);
	BOOST_CHECK_THROW(operator*(Vector<double>(0), Matrix<float>(1, 0))(2), Base::SizeError);
	BOOST_CHECK_THROW(operator*(Vector<double>(2), Matrix<float>(1, 0))(3), Base::SizeError);
	BOOST_CHECK_THROW(operator*(Vector<double>(3), Matrix<float>(4, 0))(1), Base::SizeError);

	BOOST_CHECK_THROW(operator*(Vector<double>(1), Matrix<int>(0, 2))(1), Base::SizeError);
	BOOST_CHECK_THROW(operator*(Vector<int>(0), Matrix<float>(4, 1))(2), Base::SizeError);
	BOOST_CHECK_THROW(operator*(Vector<short>(3), Matrix<float>(2, 66))(5), Base::SizeError);
	BOOST_CHECK_THROW(operator*(Vector<int>(2), Matrix<float>(5, 1))(0), Base::SizeError);

	BOOST_CHECK_THROW((CVector<int, 1>() * Matrix<float>())(0), Base::SizeError);
	BOOST_CHECK_THROW((Vector<double>(0) * Matrix<float>(1, 0))(2), Base::SizeError);
	BOOST_CHECK_THROW((Vector<double>(2) * Matrix<float>(1, 0))(3), Base::SizeError);
	BOOST_CHECK_THROW((Vector<double>(3) * Matrix<float>(4, 0))(1), Base::SizeError);

	BOOST_CHECK_THROW((Vector<double>(1) * Matrix<int>(0, 2))(1), Base::SizeError);
	BOOST_CHECK_THROW((Vector<int>(0) * Matrix<float>(4, 1))(2), Base::SizeError);
	BOOST_CHECK_THROW((Vector<short>(3) * Matrix<float>(2, 66))(5), Base::SizeError);
	BOOST_CHECK_THROW((Vector<int>(2) * Matrix<float>(5, 1))(0), Base::SizeError);

	// ----------

	Matrix<double> m1(0, 3);

	checkVectorMatrixMultiplication(Vector<int>(), m1);
	checkVectorMatrixMultiplication(Vector<std::complex<double> >(), m1);

	// ----------

	m1.resize(1, 3);

	m1(0, 0) = -2.3;
	m1(0, 1) = 1.0;
	m1(0, 2) = -21.20;

	checkVectorMatrixMultiplication(Vector<float>(1, -2.37f), m1);
	checkVectorMatrixMultiplication(Vector<std::complex<double> >(1, std::complex<double>(-2.37, 5.5)), m1);

	// ----------

	m1.resize(2, 3, true);

	m1(1, 0) = 2;
	m1(1, 1) = -1.10;
	m1(1, 2) = 0.001;

	checkVectorMatrixMultiplication(vec(-0.21, 100), m1);
	checkVectorMatrixMultiplication(vec(std::complex<double>(-0.21, 1.0), std::complex<double>(100, -3.2)), m1);

	// ----------

	m1.resize(3, 3, true);

	m1(2, 0) = 0.12;
	m1(2, 1) = 2.10;
	m1(2, 2) = -20.001;

	checkVectorMatrixMultiplication(vec(1, -2, 3), m1);
	checkVectorMatrixMultiplication(vec(std::complex<double>(-0.21, 1.0), std::complex<double>(100, -3.2), 
										std::complex<double>(10.2, 3.22)), m1);

	// ----------

	m1.resize(4, 3, true);

	m1(3, 0) = 3;
	m1(3, 1) = 4;
	m1(3, 2) = 5;

	checkVectorMatrixMultiplication(vec(6, 7.12, -1, 2), m1);
	checkVectorMatrixMultiplication(vec(std::complex<double>(0.21, 1.0), std::complex<double>(80.12, -3.2), 
										std::complex<double>(-10.2, 3.22), std::complex<double>(180.12, 0.0)), m1);

	// ----------

	Matrix<std::complex<double> > m2(0, 3);

	checkVectorMatrixMultiplication(Vector<double>(), m2);
	checkVectorMatrixMultiplication(Vector<std::complex<double> >(), m2);

	// ----------

	m2.resize(1, 3);

	m2(0, 0) = std::complex<double>(-2.3, 5.12);
	m2(0, 1) = std::complex<double>(1.0, 0.0);
	m2(0, 2) = std::complex<double>(-21.20, -17.2);

	checkVectorMatrixMultiplication(Vector<double>(1, -2.37), m2);
	checkVectorMatrixMultiplication(Vector<std::complex<double> >(1, std::complex<double>(-2.37, 5.5)), m2);

	// ----------

	m2.resize(2, 3, true);

	m2(1, 0) = std::complex<double>(2, -4.3);
	m2(1, 1) = std::complex<double>(-1.10, -0.0002);
	m2(1, 2) = std::complex<double>(0.001, 0.1);

	checkVectorMatrixMultiplication(vec(-0.21, 100.0), m2);
	checkVectorMatrixMultiplication(vec(std::complex<double>(-0.21, 1.0), std::complex<double>(100, -3.2)), m2);

	// ----------

	m2.resize(3, 3, true);

	m2(2, 0) = std::complex<double>(0.12, 0.0);
	m2(2, 1) = std::complex<double>(2.10, 0.0);
	m2(2, 2) = std::complex<double>(-20.001, 0.0);

	checkVectorMatrixMultiplication(vec(1.0, -2.0, 3.0), m2);
	checkVectorMatrixMultiplication(vec(std::complex<double>(-0.21, 1.0), std::complex<double>(100, -3.2), 
										std::complex<double>(10.2, 3.22)), m2);

	// ----------

	m2.resize(4, 3, true);

	m2(3, 0) = std::complex<double>(3, 0.1);
	m2(3, 1) = std::complex<double>(4, 0.2);
	m2(3, 2) = std::complex<double>(5, -0.3);

	checkVectorMatrixMultiplication(vec(6.0, 7.12, -1.0, 2.0), m2);
	checkVectorMatrixMultiplication(vec(std::complex<double>(0.21, 1.0), std::complex<double>(80.12, -3.2), 
										std::complex<double>(-10.2, 3.22), std::complex<double>(180.12, 0.0)), m2);

	// ----------

	m2.resize(4, 0);

	checkVectorMatrixMultiplication(vec(6.0, 7.12, -1.0, 2.0), m2);
	checkVectorMatrixMultiplication(vec(std::complex<double>(0.21, 1.0), std::complex<double>(80.12, -3.2), 
										std::complex<double>(-10.2, 3.22), std::complex<double>(180.12, 0.0)), m2);
}

BOOST_AUTO_TEST_CASE(VectorMatrixProdFunctionTest)
{
	using namespace CDPL;
	using namespace Math;

	BOOST_CHECK_NO_THROW(prod(CVector<int, 1>(), Matrix<float>()));
	BOOST_CHECK_NO_THROW(prod(Vector<double>(0), Matrix<float>(1, 0)));
	BOOST_CHECK_NO_THROW(prod(Vector<double>(2), Matrix<float>(1, 0)));
	BOOST_CHECK_NO_THROW(prod(Vector<double>(3), Matrix<float>(4, 0)));

	BOOST_CHECK_NO_THROW(prod(Vector<double>(1), Matrix<int>(0, 2)));
	BOOST_CHECK_NO_THROW(prod(Vector<int>(0), Matrix<float>(4, 1)));
	BOOST_CHECK_NO_THROW(prod(Vector<short>(3), Matrix<float>(2, 66)));
	BOOST_CHECK_NO_THROW(prod(Vector<int>(2), Matrix<float>(5, 1)));

	// ----------

	BOOST_CHECK_THROW(prod(CVector<int, 1>(), Matrix<float>())(0), Base::SizeError);
	BOOST_CHECK_THROW(prod(Vector<double>(0), Matrix<float>(1, 0))(2), Base::SizeError);
	BOOST_CHECK_THROW(prod(Vector<double>(2), Matrix<float>(1, 0))(3), Base::SizeError);
	BOOST_CHECK_THROW(prod(Vector<double>(3), Matrix<float>(4, 0))(1), Base::SizeError);

	BOOST_CHECK_THROW(prod(Vector<double>(1), Matrix<int>(0, 2))(1), Base::SizeError);
	BOOST_CHECK_THROW(prod(Vector<int>(0), Matrix<float>(4, 1))(2), Base::SizeError);
	BOOST_CHECK_THROW(prod(Vector<short>(3), Matrix<float>(2, 66))(5), Base::SizeError);
	BOOST_CHECK_THROW(prod(Vector<int>(2), Matrix<float>(5, 1))(0), Base::SizeError);

	// ----------

	Vector<double> res_v;

	BOOST_CHECK_NO_THROW(prod(CVector<int, 1>(), Matrix<float>(), res_v));
	BOOST_CHECK_NO_THROW(prod(Vector<double>(0), Matrix<float>(1, 0), res_v));
	BOOST_CHECK_NO_THROW(prod(Vector<double>(2), Matrix<float>(1, 0), res_v));
	BOOST_CHECK_NO_THROW(prod(Vector<double>(3), Matrix<float>(4, 0), res_v));

	BOOST_CHECK_THROW(prod(Vector<double>(1), Matrix<int>(0, 2), res_v), Base::SizeError);
	BOOST_CHECK_THROW(prod(Vector<int>(0), Matrix<float>(4, 1), res_v), Base::SizeError);
	BOOST_CHECK_THROW(prod(Vector<short>(3), Matrix<float>(2, 66), res_v), Base::SizeError);
	BOOST_CHECK_THROW(prod(Vector<int>(2), Matrix<float>(5, 1), res_v), Base::SizeError);

	// ----------

	Matrix<double> m1(0, 3);

	checkVectorMatrixProdFunction(Vector<int>(), m1);
	checkVectorMatrixProdFunction(Vector<std::complex<double> >(), m1);

	// ----------

	m1.resize(1, 3);

	m1(0, 0) = -2.3;
	m1(0, 1) = 1.0;
	m1(0, 2) = -21.20;

	checkVectorMatrixProdFunction(Vector<float>(1, -2.37f), m1);
	checkVectorMatrixProdFunction(Vector<std::complex<double> >(1, std::complex<double>(-2.37, 5.5)), m1);

	// ----------

	m1.resize(2, 3, true);

	m1(1, 0) = 2;
	m1(1, 1) = -1.10;
	m1(1, 2) = 0.001;

	checkVectorMatrixProdFunction(vec(-0.21, 100), m1);
	checkVectorMatrixProdFunction(vec(std::complex<double>(-0.21, 1.0), std::complex<double>(100, -3.2)), m1);

	// ----------

	m1.resize(3, 3, true);

	m1(2, 0) = 0.12;
	m1(2, 1) = 2.10;
	m1(2, 2) = -20.001;

	checkVectorMatrixProdFunction(vec(1, -2, 3), m1);
	checkVectorMatrixProdFunction(vec(std::complex<double>(-0.21, 1.0), std::complex<double>(100, -3.2), 
									  std::complex<double>(10.2, 3.22)), m1);

	// ----------

	m1.resize(4, 3, true);

	m1(3, 0) = 3;
	m1(3, 1) = 4;
	m1(3, 2) = 5;

	checkVectorMatrixProdFunction(vec(6, 7.12, -1, 2), m1);
	checkVectorMatrixProdFunction(vec(std::complex<double>(0.21, 1.0), std::complex<double>(80.12, -3.2), 
									  std::complex<double>(-10.2, 3.22), std::complex<double>(180.12, 0.0)), m1);

	// ----------

	Matrix<std::complex<double> > m2(0, 3);

	checkVectorMatrixProdFunction(Vector<double>(), m2);
	checkVectorMatrixProdFunction(Vector<std::complex<double> >(), m2);

	// ----------

	m2.resize(1, 3);

	m2(0, 0) = std::complex<double>(-2.3, 5.12);
	m2(0, 1) = std::complex<double>(1.0, 0.0);
	m2(0, 2) = std::complex<double>(-21.20, -17.2);

	checkVectorMatrixProdFunction(Vector<double>(1, -2.37), m2);
	checkVectorMatrixProdFunction(Vector<std::complex<double> >(1, std::complex<double>(-2.37, 5.5)), m2);

	// ----------

	m2.resize(2, 3, true);

	m2(1, 0) = std::complex<double>(2, -4.3);
	m2(1, 1) = std::complex<double>(-1.10, -0.0002);
	m2(1, 2) = std::complex<double>(0.001, 0.1);

	checkVectorMatrixProdFunction(vec(-0.21, 100.0), m2);
	checkVectorMatrixProdFunction(vec(std::complex<double>(-0.21, 1.0), std::complex<double>(100, -3.2)), m2);

	// ----------

	m2.resize(3, 3, true);

	m2(2, 0) = std::complex<double>(0.12, 0.0);
	m2(2, 1) = std::complex<double>(2.10, 0.0);
	m2(2, 2) = std::complex<double>(-20.001, 0.0);

	checkVectorMatrixProdFunction(vec(1.0, -2.0, 3.0), m2);
	checkVectorMatrixProdFunction(vec(std::complex<double>(-0.21, 1.0), std::complex<double>(100, -3.2), 
									  std::complex<double>(10.2, 3.22)), m2);

	// ----------

	m2.resize(4, 3, true);

	m2(3, 0) = std::complex<double>(3, 0.1);
	m2(3, 1) = std::complex<double>(4, 0.2);
	m2(3, 2) = std::complex<double>(5, -0.3);

	checkVectorMatrixProdFunction(vec(6.0, 7.12, -1.0, 2.0), m2);
	checkVectorMatrixProdFunction(vec(std::complex<double>(0.21, 1.0), std::complex<double>(80.12, -3.2), 
									  std::complex<double>(-10.2, 3.22), std::complex<double>(180.12, 0.0)), m2);

	// ----------

	m2.resize(4, 0, true);

	checkVectorMatrixProdFunction(vec(6.0, 7.12, -1.0, 2.0), m2);
	checkVectorMatrixProdFunction(vec(std::complex<double>(0.21, 1.0), std::complex<double>(80.12, -3.2), 
									  std::complex<double>(-10.2, 3.22), std::complex<double>(180.12, 0.0)), m2);
}

BOOST_AUTO_TEST_CASE(MatrixMultiplicationTest)
{
	using namespace CDPL;
	using namespace Math;

	BOOST_CHECK_NO_THROW(operator*(CMatrix<int, 0, 1>(), Matrix<float>()));
	BOOST_CHECK_NO_THROW(operator*(Matrix<double>(0, 0), Matrix<float>(1, 0)));
	BOOST_CHECK_NO_THROW(operator*(Matrix<double>(0, 2), Matrix<float>(1, 0)));
	BOOST_CHECK_NO_THROW(operator*(Matrix<double>(0, 3), Matrix<float>(4, 0)));

	BOOST_CHECK_NO_THROW(operator*(Matrix<double>(1, 1), Matrix<int>(0, 2)));
	BOOST_CHECK_NO_THROW(operator*(Matrix<int>(3, 0), Matrix<float>(4, 1)));
	BOOST_CHECK_NO_THROW(operator*(Matrix<short>(3, 4), Matrix<float>(2, 6)));
	BOOST_CHECK_NO_THROW(operator*(Matrix<int>(2, 2), Matrix<float>(5, 1)));

	BOOST_CHECK_NO_THROW((CMatrix<int, 0, 1>() * Matrix<float>()));
	BOOST_CHECK_NO_THROW((Matrix<double>(0, 0) * Matrix<float>(1, 0)));
	BOOST_CHECK_NO_THROW((Matrix<double>(0, 2) * Matrix<float>(1, 0)));
	BOOST_CHECK_NO_THROW((Matrix<double>(0, 3) * Matrix<float>(4, 0)));

	BOOST_CHECK_NO_THROW((Matrix<double>(1, 1) * Matrix<int>(0, 2)));
	BOOST_CHECK_NO_THROW((Matrix<int>(3, 0) * Matrix<float>(4, 1)));
	BOOST_CHECK_NO_THROW((Matrix<short>(3, 4) * Matrix<float>(2, 6)));
	BOOST_CHECK_NO_THROW((Matrix<int>(2, 2) * Matrix<float>(5, 1)));

	// ----------

	BOOST_CHECK_THROW(operator*(CMatrix<int, 0, 1>(), Matrix<float>())(0, 0), Base::SizeError);
	BOOST_CHECK_THROW(operator*(Matrix<double>(0, 0), Matrix<float>(1, 0))(10, 12), Base::SizeError);
	BOOST_CHECK_THROW(operator*(Matrix<double>(0, 2), Matrix<float>(1, 0))(3, 0), Base::SizeError);
	BOOST_CHECK_THROW(operator*(Matrix<double>(0, 3), Matrix<float>(4, 0))(1, 1), Base::SizeError);

	BOOST_CHECK_THROW(operator*(Matrix<double>(1, 1), Matrix<int>(0, 2))(1, 2), Base::SizeError);
	BOOST_CHECK_THROW(operator*(Matrix<int>(3, 0), Matrix<float>(4, 1))(2, 0), Base::SizeError);
	BOOST_CHECK_THROW(operator*(Matrix<short>(3, 4), Matrix<float>(2, 6))(5, 1), Base::SizeError);
	BOOST_CHECK_THROW(operator*(Matrix<int>(2, 2), Matrix<float>(5, 1))(0, 0), Base::SizeError);

	BOOST_CHECK_THROW((CMatrix<int, 0, 1>() * Matrix<float>())(0, 0), Base::SizeError);
	BOOST_CHECK_THROW((Matrix<double>(0, 0) * Matrix<float>(1, 0))(10, 12), Base::SizeError);
	BOOST_CHECK_THROW((Matrix<double>(0, 2) * Matrix<float>(1, 0))(3, 0), Base::SizeError);
	BOOST_CHECK_THROW((Matrix<double>(0, 3) * Matrix<float>(4, 0))(1, 1), Base::SizeError);

	BOOST_CHECK_THROW((Matrix<double>(1, 1) * Matrix<int>(0, 2))(1, 2), Base::SizeError);
	BOOST_CHECK_THROW((Matrix<int>(3, 0) * Matrix<float>(4, 1))(2, 0), Base::SizeError);
	BOOST_CHECK_THROW((Matrix<short>(3, 4) * Matrix<float>(2, 6))(5, 1), Base::SizeError);
	BOOST_CHECK_THROW((Matrix<int>(2, 2) * Matrix<float>(5, 1))(0, 0), Base::SizeError);

	// ----------

	Matrix<double> m1(3, 0);
	Matrix<int> m2(0, 4);

	checkMatrixMultiplication(m1, m2);

	// ----------

	m1.resize(3, 1);
	m2.resize(1, 2);

	m1(0, 0) = -2.3;
	m1(1, 0) = 1.0;
	m1(2, 0) = -21.20;

	m2(0, 0) = -3;
	m2(0, 1) = 2;

	checkMatrixMultiplication(m1, m2);

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

	checkMatrixMultiplication(m1, m2);

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

	checkMatrixMultiplication(m1, m2);

	// ----------

	Matrix<std::complex<double> > m3(0, 4);

	m1.resize(3, 0);

	checkMatrixMultiplication(m1, m3);

	// ----------

	m1.resize(3, 1);
	m3.resize(1, 2);

	m1(0, 0) = -32.3;
	m1(1, 0) = 1.230;
	m1(2, 0) = -21.20;

	m3(0, 0) = std::complex<double>(-3.0, 0.0);
	m3(0, 1) = std::complex<double>(2.2, -3.23);

	checkMatrixMultiplication(m1, m3);

	// ----------

	m1.resize(3, 2, true);
	m3.resize(2, 4, true);

	m1(0, 1) = 20.3;
	m1(1, 1) = -21.0;
	m1(2, 1) = 2.20;

	m3(0, 2) = std::complex<double>(5.0, -1.0);
	m3(0, 3) = std::complex<double>(-6.0, 534.0);
	m3(1, 0) = std::complex<double>(9.0, 0.0);
	m3(1, 1) = std::complex<double>(8.0, 2.3);
	m3(1, 2) = std::complex<double>(-7.0, -4.4);
	m3(1, 3) = std::complex<double>(26.0, 0.0002);

	checkMatrixMultiplication(m1, m3);

	// ----------

	m3.resize(2, 3, true);

	checkMatrixMultiplication(m3, m1);

	// ----------
	
	Matrix<std::complex<double> > m4(m3);

	m4.resize(3, 3, true);

	m4(2, 0) = std::complex<double>(18.0, 22.3);
	m4(2, 1) = std::complex<double>(17.2, 4.4);
	m4(2, 2) = std::complex<double>(6.0, 10.0002);

	checkMatrixMultiplication(m3, m4);

	// ----------
	
	m4.resize(3, 0);
	m3.resize(0, 3);

	checkMatrixMultiplication(m3, m4);
}

BOOST_AUTO_TEST_CASE(MatrixProdFunctionTest)
{
	using namespace CDPL;
	using namespace Math;

	BOOST_CHECK_NO_THROW(prod(CMatrix<int, 0, 1>(), Matrix<float>()));
	BOOST_CHECK_NO_THROW(prod(Matrix<double>(0, 0), Matrix<float>(1, 0)));
	BOOST_CHECK_NO_THROW(prod(Matrix<double>(0, 2), Matrix<float>(1, 0)));
	BOOST_CHECK_NO_THROW(prod(Matrix<double>(0, 3), Matrix<float>(4, 0)));

	BOOST_CHECK_NO_THROW(prod(Matrix<double>(1, 1), Matrix<int>(0, 2)));
	BOOST_CHECK_NO_THROW(prod(Matrix<int>(3, 0), Matrix<float>(4, 1)));
	BOOST_CHECK_NO_THROW(prod(Matrix<short>(3, 4), Matrix<float>(2, 6)));
	BOOST_CHECK_NO_THROW(prod(Matrix<int>(2, 2), Matrix<float>(5, 1)));

	// ----------

	BOOST_CHECK_THROW(prod(CMatrix<int, 0, 1>(), Matrix<float>())(0, 0), Base::SizeError);
	BOOST_CHECK_THROW(prod(Matrix<double>(0, 0), Matrix<float>(1, 0))(10, 12), Base::SizeError);
	BOOST_CHECK_THROW(prod(Matrix<double>(0, 2), Matrix<float>(1, 0))(3, 0), Base::SizeError);
	BOOST_CHECK_THROW(prod(Matrix<double>(0, 3), Matrix<float>(4, 0))(1, 1), Base::SizeError);

	BOOST_CHECK_THROW(prod(Matrix<double>(1, 1), Matrix<int>(0, 2))(1, 2), Base::SizeError);
	BOOST_CHECK_THROW(prod(Matrix<int>(3, 0), Matrix<float>(4, 1))(2, 0), Base::SizeError);
	BOOST_CHECK_THROW(prod(Matrix<short>(3, 4), Matrix<float>(2, 6))(5, 1), Base::SizeError);
	BOOST_CHECK_THROW(prod(Matrix<int>(2, 2), Matrix<float>(5, 1))(0, 0), Base::SizeError);

	// ----------

	Matrix<double> res_m;

	BOOST_CHECK_NO_THROW(prod(CMatrix<int, 0, 1>(), Matrix<float>(), res_m));
	BOOST_CHECK_NO_THROW(prod(Matrix<double>(0, 0), Matrix<float>(1, 0), res_m));
	BOOST_CHECK_NO_THROW(prod(Matrix<double>(0, 2), Matrix<float>(1, 0), res_m));
	BOOST_CHECK_NO_THROW(prod(Matrix<double>(0, 3), Matrix<float>(4, 0), res_m));

	BOOST_CHECK_THROW(prod(Matrix<double>(1, 1), Matrix<int>(0, 2), res_m), Base::SizeError);
	BOOST_CHECK_THROW(prod(Matrix<int>(3, 0), Matrix<float>(4, 1), res_m), Base::SizeError);
	BOOST_CHECK_THROW(prod(Matrix<short>(3, 4), Matrix<float>(2, 6), res_m), Base::SizeError);
	BOOST_CHECK_THROW(prod(Matrix<int>(2, 2), Matrix<float>(5, 1), res_m), Base::SizeError);

	// ----------

	Matrix<double> m1(3, 0);
	Matrix<int> m2(0, 4);

	checkMatrixProdFunction(m1, m2);

	// ----------

	m1.resize(3, 1);
	m2.resize(1, 2);

	m1(0, 0) = -2.3;
	m1(1, 0) = 1.0;
	m1(2, 0) = -21.20;

	m2(0, 0) = -3;
	m2(0, 1) = 2;

	checkMatrixProdFunction(m1, m2);

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

	checkMatrixProdFunction(m1, m2);

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

	checkMatrixProdFunction(m1, m2);

	// ----------

	Matrix<std::complex<double> > m3(0, 4);

	m1.resize(3, 0);

	checkMatrixProdFunction(m1, m3);

	// ----------

	m1.resize(3, 1);
	m3.resize(1, 2);

	m1(0, 0) = -32.3;
	m1(1, 0) = 1.230;
	m1(2, 0) = -21.20;

	m3(0, 0) = std::complex<double>(-3.0, 0.0);
	m3(0, 1) = std::complex<double>(2.2, -3.23);

	checkMatrixProdFunction(m1, m3);

	// ----------

	m1.resize(3, 2, true);
	m3.resize(2, 4, true);

	m1(0, 1) = 20.3;
	m1(1, 1) = -21.0;
	m1(2, 1) = 2.20;

	m3(0, 2) = std::complex<double>(5.0, -1.0);
	m3(0, 3) = std::complex<double>(-6.0, 534.0);
	m3(1, 0) = std::complex<double>(9.0, 0.0);
	m3(1, 1) = std::complex<double>(8.0, 2.3);
	m3(1, 2) = std::complex<double>(-7.0, -4.4);
	m3(1, 3) = std::complex<double>(26.0, 0.0002);

	checkMatrixProdFunction(m1, m3);

	// ----------

	m3.resize(2, 3, true);

	checkMatrixProdFunction(m3, m1);

	// ----------
	
	Matrix<std::complex<double> > m4(m3);

	m4.resize(3, 3, true);

	m4(2, 0) = std::complex<double>(18.0, 22.3);
	m4(2, 1) = std::complex<double>(17.2, 4.4);
	m4(2, 2) = std::complex<double>(6.0, 10.0002);

	checkMatrixProdFunction(m3, m4);
	
	// ----------
	
	m4.resize(3, 0);
	m3.resize(0, 3);

	checkMatrixMultiplication(m3, m4);
}

BOOST_AUTO_TEST_CASE(TraceFunctionTest)
{
	using namespace CDPL;
	using namespace Math;

	BOOST_CHECK_THROW(trace(CMatrix<int, 0, 3>(4)), Base::SizeError);
	BOOST_CHECK_THROW(trace(CMatrix<int, 3, 0>(4)), Base::SizeError);
	BOOST_CHECK_THROW(trace(CMatrix<int, 2, 3>(4)), Base::SizeError);
	BOOST_CHECK_THROW(trace(CMatrix<int, 3, 2>(4)), Base::SizeError);

	// ----------

	checkMatrixTraceFunction(CMatrix<float, 0, 0>());
	checkMatrixTraceFunction(CMatrix<int, 3, 3>(4));

	// ----------

	typedef CMatrix<double, 4, 4>::SizeType SizeType;

	CMatrix<double, 4, 4> m1(0);

	BOOST_CHECK_EQUAL(trace(m1), 0.0);

    for (SizeType i = 0; i < 4; i++) {
		for (SizeType j = 0; j < 4; j++) {
			BOOST_CHECK_EQUAL((MatrixTrace<CMatrix<double, 4, 4> >::apply(m1)), 0.0);

			if (i != j)
				m1(i, j) = i * 4 + j;
		}
	}

  	checkMatrixTraceFunction(m1);

	// ----------

    m1(0, 0) = -1.0;
    m1(1, 1) = 1.1;
    m1(2, 2) = 17.2;
    m1(3, 3) = -617.2;
				  
  	checkMatrixTraceFunction(m1);

	// ----------

	CMatrix<std::complex<double>, 4, 4> m2(std::complex<double>(0, 0));

	m2(0, 0) = std::complex<double>(-17.2, 4.5);
    m2(1, 1) = std::complex<double>(15.16, -14.5);
    m2(2, 2) = std::complex<double>(11.17, 22.15);
    m2(3, 3) = std::complex<double>(-3.1, -1.25);
    m2(1, 3) = std::complex<double>(-33.1, -31.25);

  	checkMatrixTraceFunction(m2);
}

BOOST_AUTO_TEST_CASE(MatrixNormFrobFunctionTest)
{
	using namespace CDPL;
	using namespace Math;

	BOOST_CHECK_EQUAL(normFrob(Matrix<float>()), 0.0f);
	BOOST_CHECK_EQUAL(normFrob(CMatrix<double, 3, 0>()), 0.0);
	BOOST_CHECK_EQUAL(normFrob(CMatrix<double, 0, 4>()), 0.0);

	// ----------

	CMatrix<double, 3, 2> m1(0.0);

	checkMatrixNormFrobFunction(m1);

	// ----------

	m1(0, 0) = -17.2;
	m1(0, 1) = 15.16;
	m1(1, 0) = 11.17;
	m1(1, 1) = -13.1;
	m1(2, 0) = -23.1;
	m1(2, 1) = -33.1;

	checkMatrixNormFrobFunction(m1);

	// ----------

    CMatrix<std::complex<double>, 2, 3> m2(std::complex<double>(0.0, 0.0));

	checkMatrixNormFrobFunction(m2);

	// ----------

    m2(0, 0) = std::complex<double>(-17.2, 4.5);
    m2(0, 1) = std::complex<double>(15.16, -14.5);
    m2(0, 2) = std::complex<double>(11.17, 22.15);
    m2(1, 0) = std::complex<double>(-13.1, 31.15);
    m2(1, 1) = std::complex<double>(-23.1, 11.3425);
    m2(1, 2) = std::complex<double>(-33.1, 1.25);

	checkMatrixNormFrobFunction(m2);
}

BOOST_AUTO_TEST_CASE(MatrixNorm1FunctionTest)
{
	using namespace CDPL;
	using namespace Math;

	BOOST_CHECK_EQUAL(norm1(Matrix<float>()), 0.0f);
	BOOST_CHECK_EQUAL(norm1(CMatrix<double, 3, 0>()), 0.0);
	BOOST_CHECK_EQUAL(norm1(CMatrix<double, 0, 4>()), 0.0);

	// ----------

	CMatrix<double, 3, 2> m1(0.0);

	checkMatrixNorm1Function(m1, 0);
	checkMatrixNorm1Function(m1, 1);

	// ----------

	m1(0, 0) = -17.2;
	m1(0, 1) = 15.16;
	m1(1, 0) = 11.17;
	m1(1, 1) = -13.1;
	m1(2, 0) = -23.1;
	m1(2, 1) = -33.1;

	checkMatrixNorm1Function(m1, 1);

	// ----------

    CMatrix<std::complex<double>, 2, 3> m2(std::complex<double>(0.0, 0.0));

	checkMatrixNorm1Function(m2, 0);
	checkMatrixNorm1Function(m2, 1);
	checkMatrixNorm1Function(m2, 2);

	// ----------

    m2(0, 0) = std::complex<double>(-17.2, 4.5);
    m2(0, 1) = std::complex<double>(15.16, -14.5);
    m2(0, 2) = std::complex<double>(11.17, 22.15);
    m2(1, 0) = std::complex<double>(-13.1, 31.15);
    m2(1, 1) = std::complex<double>(-23.1, 11.3425);
    m2(1, 2) = std::complex<double>(-33.1, 1.25);

	checkMatrixNorm1Function(m2, 2);
}

BOOST_AUTO_TEST_CASE(MatrixNormInfFunctionTest)
{
	using namespace CDPL;
	using namespace Math;

	BOOST_CHECK_EQUAL(normInf(Matrix<float>()), 0.0f);
	BOOST_CHECK_EQUAL(normInf(CMatrix<double, 3, 0>()), 0.0);
	BOOST_CHECK_EQUAL(normInf(CMatrix<double, 0, 4>()), 0.0);

	// ----------

	CMatrix<double, 3, 2> m1(0.0);

	checkMatrixNormInfFunction(m1, 0);
	checkMatrixNormInfFunction(m1, 1);
	checkMatrixNormInfFunction(m1, 2);

	// ----------

	m1(0, 0) = -17.2;
	m1(0, 1) = 15.16;
	m1(1, 0) = 11.17;
	m1(1, 1) = -13.1;
	m1(2, 0) = -23.1;
	m1(2, 1) = -33.1;

	checkMatrixNormInfFunction(m1, 2);

	// ----------

    CMatrix<std::complex<double>, 2, 3> m2(std::complex<double>(0.0, 0.0));

	checkMatrixNormInfFunction(m2, 0);
	checkMatrixNormInfFunction(m2, 1);

	// ----------

    m2(0, 0) = std::complex<double>(-17.2, 4.5);
    m2(0, 1) = std::complex<double>(15.16, -14.5);
    m2(0, 2) = std::complex<double>(11.17, 22.15);
    m2(1, 0) = std::complex<double>(-13.1, 31.15);
    m2(1, 1) = std::complex<double>(-23.1, 11.3425);
    m2(1, 2) = std::complex<double>(-33.1, 1.25);

	checkMatrixNormInfFunction(m2, 1);
}

BOOST_AUTO_TEST_CASE(DiagFunctionTest)
{
	using namespace CDPL;
	using namespace Math;

	Vector<double> v1;

	checkVectorDiagFunction(v1);

	// ----------

	v1.resize(5, 0.0);

	checkVectorDiagFunction(v1);

	// ----------

	v1.clear(-1.27);

	checkVectorDiagFunction(v1);

	// ----------

	v1(0) = 2.2;
	v1(2) = -12.2;
	v1(4) = 18.12445;

	checkVectorDiagFunction(v1);

	// ----------
	
	Vector<std::complex<double> > v2(6);

	v2(0) = std::complex<double>(-17.2, 4.5);
    v2(1) = std::complex<double>(15.16, -14.5);
    v2(2) = std::complex<double>(11.17, 22.15);
    v2(3) = std::complex<double>(-13.1, 31.15);
    v2(4) = std::complex<double>(-23.1, 11.3425);
    v2(5) = std::complex<double>(-33.1, 1.25);

	checkVectorDiagFunction(v2);
}

BOOST_AUTO_TEST_CASE(CrossFunctionTest)
{
	using namespace CDPL;
	using namespace Math;

	BOOST_CHECK_NO_THROW(cross(CVector<float, 0>()));
	BOOST_CHECK_NO_THROW(cross(CVector<int, 2>()));
	BOOST_CHECK_NO_THROW(cross(Vector<double>(10)));

	BOOST_CHECK_THROW(cross(CVector<float, 0>())(0, 0), Base::SizeError);
	BOOST_CHECK_THROW(cross(CVector<int, 2>())(0, 0), Base::SizeError);
	BOOST_CHECK_THROW(cross(Vector<double>(10))(0, 0), Base::SizeError);

	// ----------

	BOOST_CHECK_THROW(checkVectorCrossFunction(vec(1.1, 2.2, 3.3, 0.0)), Base::SizeError);
	BOOST_CHECK_THROW(checkVectorCrossFunction(Vector<int>(10)), Base::SizeError);
	BOOST_CHECK_THROW(checkVectorCrossFunction(Vector<float>()), Base::SizeError);
	BOOST_CHECK_THROW(checkVectorCrossFunction(vec(-1.1, 0.2)), Base::SizeError);

	// ----------

	checkVectorCrossFunction(vec(0, 0, 0));
	checkVectorCrossFunction(vec(1, 0, 0));
	checkVectorCrossFunction(vec(0, 2.0f, 0));
	checkVectorCrossFunction(vec(0, 0.0, 1.0));

	checkVectorCrossFunction(vec(-1.2, 0, 0));
	checkVectorCrossFunction(vec(0, -2.2f, 0));
	checkVectorCrossFunction(vec(0, 0.0, -5));

	checkVectorCrossFunction(vec(2, 4, 1));
	checkVectorCrossFunction(vec(-2, -4.2, -1.4f));
}

BOOST_AUTO_TEST_CASE(MatrixSumFunctionTest)
{
	using namespace CDPL;
	using namespace Math;

	Matrix<double> m1;

	checkMatrixSumFunction(m1);

	m1.resize(2, 3);

	checkMatrixSumFunction(m1);

	m1(0, 0) = -1.1;
	m1(1, 2) = 1.1;

	checkMatrixSumFunction(m1);

	m1(0, 1) = 2.11;
	m1(1, 1) = -15.1;

	checkMatrixSumFunction(m1);

	// ----------

	CMatrix<std::complex<double>, 2, 2> m2;

	m2(0, 0) = std::complex<double>(-17.2, 4.5);
	m2(0, 1) = std::complex<double>(15.16, -14.5);
	m2(1, 0) = std::complex<double>(11.17, 22.15);
	m2(1, 1) = std::complex<double>(-3.1, -1.25);

	checkMatrixSumFunction(m2);
}
