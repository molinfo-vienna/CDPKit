/* 
 * VectorFunctionExport.cpp 
 *
 * This file is part of the Chemical Data Processing Toolkit
 *
 * Copyright (C) 2003 Thomas Seidel <thomas.seidel@univie.ac.at>
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


#include <utility>

#include <boost/python.hpp>

#include "CDPL/Math/Vector.hpp"
#include "CDPL/Math/VectorExpression.hpp"

#include "VectorExpression.hpp"
#include "QuaternionExpression.hpp"
#include "VectorExpressionAdapter.hpp"
#include "FunctionExports.hpp"


namespace
{

	template <typename T>
	CDPL::Math::CVector<T, 2> makeVec2(const T& t1, const T& t2) 
	{
		CDPL::Math::CVector<T, 2> v;

		v(0) = t1;
		v(1) = t2;

		return v;
	}

	template <typename T>
	CDPL::Math::CVector<T, 3> makeVec3(const T& t1, const T& t2, const T& t3) 
	{
		CDPL::Math::CVector<T, 3> v;

		v(0) = t1;
		v(1) = t2;
		v(2) = t3;

		return v;
	}

	template <typename T>
	CDPL::Math::CVector<T, 4> makeVec4(const T& t1, const T& t2, const T& t3, const T& t4) 
	{
		CDPL::Math::CVector<T, 4> v;

		v(0) = t1;
		v(1) = t2;
		v(2) = t3;
		v(3) = t4;

		return v;
	}

	template <typename T>
	bool equals(const typename CDPLPythonMath::ConstVectorExpression<T>::SharedPointer& e1,
				const typename CDPLPythonMath::ConstVectorExpression<T>::SharedPointer& e2,
				const T& eps)
	{
		return CDPL::Math::equals(*e1, *e2, eps);
	}

	template <typename T>
	typename CDPLPythonMath::ConstVectorExpression<T>::SharedPointer
	conj(const typename CDPLPythonMath::ConstVectorExpression<T>::SharedPointer& e)
	{
		using namespace CDPLPythonMath;

		typedef typename ConstVectorExpression<T>::SharedPointer ExpressionPointer;

		return ExpressionPointer(makeConstVectorExpressionAdapter(CDPL::Math::conj(*e), e));
	}

	template <typename T>
	typename CDPLPythonMath::ConstVectorExpression<T>::SharedPointer
	herm(const typename CDPLPythonMath::ConstVectorExpression<T>::SharedPointer& e)
	{
		using namespace CDPLPythonMath;

		typedef typename ConstVectorExpression<T>::SharedPointer ExpressionPointer;

		return ExpressionPointer(makeConstVectorExpressionAdapter(CDPL::Math::herm(*e), e));
	}

	template <typename T>
	typename CDPLPythonMath::ConstVectorExpression<T>::SharedPointer
	real(const typename CDPLPythonMath::ConstVectorExpression<T>::SharedPointer& e)
	{
		using namespace CDPLPythonMath;

		typedef typename ConstVectorExpression<T>::SharedPointer ExpressionPointer;

		return ExpressionPointer(makeConstVectorExpressionAdapter(CDPL::Math::real(*e), e));
	}

	template <typename T>
	typename CDPLPythonMath::ConstVectorExpression<T>::SharedPointer
	imag(const typename CDPLPythonMath::ConstVectorExpression<T>::SharedPointer& e)
	{
		using namespace CDPLPythonMath;

		typedef typename ConstVectorExpression<T>::SharedPointer ExpressionPointer;

		return ExpressionPointer(makeConstVectorExpressionAdapter(CDPL::Math::imag(*e), e));
	}

	template <typename T>
	typename CDPLPythonMath::ConstVectorExpression<T>::SharedPointer
	elemDiv(const typename CDPLPythonMath::ConstVectorExpression<T>::SharedPointer& e1,
			const typename CDPLPythonMath::ConstVectorExpression<T>::SharedPointer& e2)
	{
		using namespace CDPLPythonMath;

		typedef typename ConstVectorExpression<T>::SharedPointer ExpressionPointer;

		return ExpressionPointer(makeConstVectorExpressionAdapter(CDPL::Math::elemDiv(*e1, *e2),
																  std::make_pair(e1, e2)));
	}

	template <typename T>
	typename CDPLPythonMath::ConstVectorExpression<T>::SharedPointer
	elemProd(const typename CDPLPythonMath::ConstVectorExpression<T>::SharedPointer& e1,
			 const typename CDPLPythonMath::ConstVectorExpression<T>::SharedPointer& e2)
	{
		using namespace CDPLPythonMath;

		typedef typename ConstVectorExpression<T>::SharedPointer ExpressionPointer;

		return ExpressionPointer(makeConstVectorExpressionAdapter(CDPL::Math::elemProd(*e1, *e2),
																  std::make_pair(e1, e2)));
	}

	template <typename T>
	typename CDPLPythonMath::ConstVectorExpression<T>::SharedPointer
	crossProd(const typename CDPLPythonMath::ConstVectorExpression<T>::SharedPointer& e1,
			  const typename CDPLPythonMath::ConstVectorExpression<T>::SharedPointer& e2)
	{
		using namespace CDPLPythonMath;

		typedef typename ConstVectorExpression<T>::SharedPointer ExpressionPointer;

		return ExpressionPointer(makeConstVectorExpressionAdapter(CDPL::Math::crossProd(*e1, *e2),
																  std::make_pair(e1, e2)));
	}

	template <typename T>
	T innerProd(const typename CDPLPythonMath::ConstVectorExpression<T>::SharedPointer& e1,
				const typename CDPLPythonMath::ConstVectorExpression<T>::SharedPointer& e2)
	{
		return CDPL::Math::innerProd(*e1, *e2);
	}

	template <typename T>
	T angleCos(const typename CDPLPythonMath::ConstVectorExpression<T>::SharedPointer& e1,
			   const typename CDPLPythonMath::ConstVectorExpression<T>::SharedPointer& e2, const T& sd, bool clamp)
	{
		return CDPL::Math::angleCos(*e1, *e2, sd, clamp);
	}

	template <typename T>
	T sum(const typename CDPLPythonMath::ConstVectorExpression<T>::SharedPointer& e)
	{
		return CDPL::Math::sum(*e);
	}

	template <typename T>
	T norm1(const typename CDPLPythonMath::ConstVectorExpression<T>::SharedPointer& e)
	{
		return CDPL::Math::norm1(*e);
	}

	template <typename T>
	T norm2(const typename CDPLPythonMath::ConstVectorExpression<T>::SharedPointer& e)
	{
		return CDPL::Math::norm2(*e);
	}

	template <typename T>
	T normInf(const typename CDPLPythonMath::ConstVectorExpression<T>::SharedPointer& e)
	{
		return CDPL::Math::normInf(*e);
	}

	template <typename T>
	const typename CDPLPythonMath::ConstVectorExpression<T>::SizeType
	normInfIndex(const typename CDPLPythonMath::ConstVectorExpression<T>::SharedPointer& e)
	{
		return CDPL::Math::normInfIndex(*e);
	}

	template <typename T>
	T length(const typename CDPLPythonMath::ConstVectorExpression<T>::SharedPointer& e)
	{
		return CDPL::Math::length(*e);
	}

	template <typename T>
	typename CDPLPythonMath::ConstVectorExpression<T>::SharedPointer
	rotate(const typename CDPLPythonMath::ConstQuaternionExpression<T>::SharedPointer& e1,
		   const typename CDPLPythonMath::ConstVectorExpression<T>::SharedPointer& e2)
	{
		using namespace CDPLPythonMath;

		typedef typename ConstVectorExpression<T>::SharedPointer ExpressionPointer;

		return ExpressionPointer(makeConstVectorExpressionAdapter(CDPL::Math::rotate(*e1, *e2),
																  std::make_pair(e1, e2)));
	}
}


void CDPLPythonMath::exportVectorFunctions()
{
	using namespace boost;

	python::def("vec", &makeVec2<float>, (python::arg("t1"), python::arg("t2")));
	python::def("vec", &makeVec2<double>, (python::arg("t1"), python::arg("t2")));
	python::def("vec", &makeVec2<long>, (python::arg("t1"), python::arg("t2")));
	python::def("vec", &makeVec2<unsigned long>, (python::arg("t1"), python::arg("t2")));

	python::def("vec", &makeVec3<float>, (python::arg("t1"), python::arg("t2"), python::arg("t3")));
	python::def("vec", &makeVec3<double>, (python::arg("t1"), python::arg("t2"), python::arg("t3")));
	python::def("vec", &makeVec3<long>, (python::arg("t1"), python::arg("t2"), python::arg("t3")));
	python::def("vec", &makeVec3<unsigned long>, (python::arg("t1"), python::arg("t2"), python::arg("t3")));

	python::def("vec", &makeVec4<float>, (python::arg("t1"), python::arg("t2"), python::arg("t3"), python::arg("t4")));
	python::def("vec", &makeVec4<double>, (python::arg("t1"), python::arg("t2"), python::arg("t3"), python::arg("t4")));
	python::def("vec", &makeVec4<long>, (python::arg("t1"), python::arg("t2"), python::arg("t3"), python::arg("t4")));
	python::def("vec", &makeVec4<unsigned long>, (python::arg("t1"), python::arg("t2"), python::arg("t3"), python::arg("t4")));

	python::def("equals", &equals<float>, (python::arg("e1"), python::arg("e2"), python::arg("eps")));
	python::def("equals", &equals<double>, (python::arg("e1"), python::arg("e2"), python::arg("eps")));
	python::def("equals", &equals<long>, (python::arg("e1"), python::arg("e2"), python::arg("eps")));
	python::def("equals", &equals<unsigned long>, (python::arg("e1"), python::arg("e2"), python::arg("eps")));

	python::def("elemDiv", &elemDiv<float>, (python::arg("e1"), python::arg("e2")));
	python::def("elemDiv", &elemDiv<double>, (python::arg("e1"), python::arg("e2")));
	python::def("elemDiv", &elemDiv<long>, (python::arg("e1"), python::arg("e2")));
	python::def("elemDiv", &elemDiv<unsigned long>, (python::arg("e1"), python::arg("e2")));

	python::def("elemProd", &elemProd<float>, (python::arg("e1"), python::arg("e2")));
	python::def("elemProd", &elemProd<double>, (python::arg("e1"), python::arg("e2")));
	python::def("elemProd", &elemProd<long>, (python::arg("e1"), python::arg("e2")));
	python::def("elemProd", &elemProd<unsigned long>, (python::arg("e1"), python::arg("e2")));

	python::def("crossProd", &crossProd<float>, (python::arg("e1"), python::arg("e2")));
	python::def("crossProd", &crossProd<double>, (python::arg("e1"), python::arg("e2")));
	python::def("crossProd", &crossProd<long>, (python::arg("e1"), python::arg("e2")));
	python::def("crossProd", &crossProd<unsigned long>, (python::arg("e1"), python::arg("e2")));

	python::def("innerProd", &innerProd<float>, (python::arg("e1"), python::arg("e2")));
	python::def("innerProd", &innerProd<double>, (python::arg("e1"), python::arg("e2")));
	python::def("innerProd", &innerProd<long>, (python::arg("e1"), python::arg("e2")));
	python::def("innerProd", &innerProd<unsigned long>, (python::arg("e1"), python::arg("e2")));

	python::def("angleCos", &angleCos<float>, (python::arg("e1"), python::arg("e2"), python::arg("sd"), python::arg("clamp") = true));
	python::def("angleCos", &angleCos<double>, (python::arg("e1"), python::arg("e2"), python::arg("sd"), python::arg("clamp") = true));
	python::def("angleCos", &angleCos<long>, (python::arg("e1"), python::arg("e2"), python::arg("sd"), python::arg("clamp") = true));
	python::def("angleCos", &angleCos<unsigned long>, (python::arg("e1"), python::arg("e2"), python::arg("sd"), python::arg("clamp") = true));

	python::def("real", &real<float>, python::arg("e"));
	python::def("real", &real<double>, python::arg("e"));
	python::def("real", &real<long>, python::arg("e"));
	python::def("real", &real<unsigned long>, python::arg("e"));

	python::def("imag", &imag<float>, python::arg("e"));
	python::def("imag", &imag<double>, python::arg("e"));
	python::def("imag", &imag<long>, python::arg("e"));
	python::def("imag", &imag<unsigned long>, python::arg("e"));

	python::def("conj", &conj<float>, python::arg("e"));
	python::def("conj", &conj<double>, python::arg("e"));
	python::def("conj", &conj<long>, python::arg("e"));
	python::def("conj", &conj<unsigned long>, python::arg("e"));

	python::def("herm", &herm<float>, python::arg("e"));
	python::def("herm", &herm<double>, python::arg("e"));
	python::def("herm", &herm<long>, python::arg("e"));
	python::def("herm", &herm<unsigned long>, python::arg("e"));

	python::def("norm1", &norm1<float>, python::arg("e"));
	python::def("norm1", &norm1<double>, python::arg("e"));
	python::def("norm1", &norm1<long>, python::arg("e"));
	python::def("norm1", &norm1<unsigned long>, python::arg("e"));

	python::def("norm2", &norm2<float>, python::arg("e"));
	python::def("norm2", &norm2<double>, python::arg("e"));
	python::def("norm2", &norm2<long>, python::arg("e"));
	python::def("norm2", &norm2<unsigned long>, python::arg("e"));

	python::def("normInf", &normInf<float>, python::arg("e"));
	python::def("normInf", &normInf<double>, python::arg("e"));
	python::def("normInf", &normInf<long>, python::arg("e"));
	python::def("normInf", &normInf<unsigned long>, python::arg("e"));

	python::def("normInfIndex", &normInfIndex<float>, python::arg("e"));
	python::def("normInfIndex", &normInfIndex<double>, python::arg("e"));
	python::def("normInfIndex", &normInfIndex<long>, python::arg("e"));
	python::def("normInfIndex", &normInfIndex<unsigned long>, python::arg("e"));

	python::def("length", &length<float>, python::arg("e"));
	python::def("length", &length<double>, python::arg("e"));
	python::def("length", &length<long>, python::arg("e"));
	python::def("length", &length<unsigned long>, python::arg("e"));

	python::def("sum", &sum<float>, python::arg("e"));
	python::def("sum", &sum<double>, python::arg("e"));
	python::def("sum", &sum<long>, python::arg("e"));
	python::def("sum", &sum<unsigned long>, python::arg("e"));

	python::def("rotate", &rotate<float>, (python::arg("e1"), python::arg("e2")));
	python::def("rotate", &rotate<double>, (python::arg("e1"), python::arg("e2")));
	python::def("rotate", &rotate<long>, (python::arg("e1"), python::arg("e2")));
	python::def("rotate", &rotate<unsigned long>, (python::arg("e1"), python::arg("e2")));
}
