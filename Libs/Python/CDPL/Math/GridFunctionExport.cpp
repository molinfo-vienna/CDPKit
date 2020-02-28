/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * GridFunctionExport.cpp 
 *
 * This file is part of the Chemical Data Processing Toolkit
 *
 * Copyright (C) 2003-2020 Thomas A. Seidel <thomas.seidel@univie.ac.at>
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


#include <boost/python.hpp>

#include "CDPL/Math/Grid.hpp"

#include "GridExpression.hpp"
#include "GridExpressionAdapter.hpp"
#include "FunctionExports.hpp"


namespace
{

	template <typename T>
	bool equals(const typename CDPLPythonMath::ConstGridExpression<T>::SharedPointer& e1,
				const typename CDPLPythonMath::ConstGridExpression<T>::SharedPointer& e2,
				const T& eps)
	{
		return CDPL::Math::equals(*e1, *e2, eps);
	}

	template <typename T>
	typename CDPLPythonMath::ConstGridExpression<T>::SharedPointer
	conj(const typename CDPLPythonMath::ConstGridExpression<T>::SharedPointer& e)
	{
		using namespace CDPLPythonMath;

		typedef typename ConstGridExpression<T>::SharedPointer ExpressionPointer;

		return ExpressionPointer(makeConstGridExpressionAdapter(CDPL::Math::conj(*e), e));
	}

	template <typename T>
	typename CDPLPythonMath::ConstGridExpression<T>::SharedPointer
	herm(const typename CDPLPythonMath::ConstGridExpression<T>::SharedPointer& e)
	{
		using namespace CDPLPythonMath;

		typedef typename ConstGridExpression<T>::SharedPointer ExpressionPointer;

		return ExpressionPointer(makeConstGridExpressionAdapter(CDPL::Math::herm(*e), e));
	}

	template <typename T>
	typename CDPLPythonMath::ConstGridExpression<T>::SharedPointer
	real(const typename CDPLPythonMath::ConstGridExpression<T>::SharedPointer& e)
	{
		using namespace CDPLPythonMath;

		typedef typename ConstGridExpression<T>::SharedPointer ExpressionPointer;

		return ExpressionPointer(makeConstGridExpressionAdapter(CDPL::Math::real(*e), e));
	}

	template <typename T>
	typename CDPLPythonMath::ConstGridExpression<T>::SharedPointer
	imag(const typename CDPLPythonMath::ConstGridExpression<T>::SharedPointer& e)
	{
		using namespace CDPLPythonMath;

		typedef typename ConstGridExpression<T>::SharedPointer ExpressionPointer;

		return ExpressionPointer(makeConstGridExpressionAdapter(CDPL::Math::imag(*e), e));
	}

	template <typename T>
	typename CDPLPythonMath::ConstGridExpression<T>::SharedPointer
	elemDiv(const typename CDPLPythonMath::ConstGridExpression<T>::SharedPointer& e1,
			const typename CDPLPythonMath::ConstGridExpression<T>::SharedPointer& e2)
	{
		using namespace CDPLPythonMath;

		typedef typename ConstGridExpression<T>::SharedPointer ExpressionPointer;

		return ExpressionPointer(makeConstGridExpressionAdapter(CDPL::Math::elemDiv(*e1, *e2),
																  std::make_pair(e1, e2)));
	}

	template <typename T>
	typename CDPLPythonMath::ConstGridExpression<T>::SharedPointer
	elemProd(const typename CDPLPythonMath::ConstGridExpression<T>::SharedPointer& e1,
			 const typename CDPLPythonMath::ConstGridExpression<T>::SharedPointer& e2)
	{
		using namespace CDPLPythonMath;

		typedef typename ConstGridExpression<T>::SharedPointer ExpressionPointer;

		return ExpressionPointer(makeConstGridExpressionAdapter(CDPL::Math::elemProd(*e1, *e2),
																  std::make_pair(e1, e2)));
	}

	template <typename T>
	T sum(const typename CDPLPythonMath::ConstGridExpression<T>::SharedPointer& e)
	{
		return CDPL::Math::sum(*e);
	}
}


void CDPLPythonMath::exportGridFunctions()
{
	using namespace boost;

	python::def("equals", &equals<float>, (python::arg("e1"), python::arg("e2"), python::arg("eps")));
	python::def("equals", &equals<double>, (python::arg("e1"), python::arg("e2"), python::arg("eps")));

	python::def("real", &real<float>, python::arg("e"));
	python::def("real", &real<double>, python::arg("e"));

	python::def("imag", &imag<float>, python::arg("e"));
	python::def("imag", &imag<double>, python::arg("e"));

	python::def("conj", &conj<float>, python::arg("e"));
	python::def("conj", &conj<double>, python::arg("e"));

	python::def("herm", &herm<float>, python::arg("e"));
	python::def("herm", &herm<double>, python::arg("e"));

	python::def("elemDiv", &elemDiv<float>, (python::arg("e1"), python::arg("e2")));
	python::def("elemDiv", &elemDiv<double>, (python::arg("e1"), python::arg("e2")));

	python::def("elemProd", &elemProd<float>, (python::arg("e1"), python::arg("e2")));
	python::def("elemProd", &elemProd<double>, (python::arg("e1"), python::arg("e2")));

	python::def("sum", &sum<float>, python::arg("e"));
	python::def("sum", &sum<double>, python::arg("e"));
	python::def("sum", &sum<long>, python::arg("e"));
	python::def("sum", &sum<unsigned long>, python::arg("e"));
}
