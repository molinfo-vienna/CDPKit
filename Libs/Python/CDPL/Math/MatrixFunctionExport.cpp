/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * MatrixFunctionExport.cpp 
 *
 * This file is part of the Chemical Data Processing Toolkit
 *
 * Copyright (C) 2003-2010 Thomas A. Seidel <thomas.seidel@univie.ac.at>
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

#include "CDPL/Math/Matrix.hpp"
#include "CDPL/Math/MatrixExpression.hpp"
#include "CDPL/Math/LUDecomposition.hpp"
#include "CDPL/Math/SVDecomposition.hpp"
#include "CDPL/Math/JacobiDiagonalization.hpp"
#include "CDPL/Math/LinearSolve.hpp"

#include "MatrixExpression.hpp"
#include "VectorExpression.hpp"
#include "MatrixExpressionAdapter.hpp"
#include "VectorExpressionAdapter.hpp"
#include "FunctionExports.hpp"


namespace
{

	template <typename T>
	T det(const typename CDPLPythonMath::ConstMatrixExpression<T>::SharedPointer& e)
	{
		return CDPL::Math::det(*e);
	}

	template <typename T>
	bool invert2(const typename CDPLPythonMath::ConstMatrixExpression<T>::SharedPointer& e,
				 typename CDPLPythonMath::MatrixExpression<T>::SharedPointer& c)
	{
		return CDPL::Math::invert(*e, *c);
	}

	template <typename T>
	bool invert1(typename CDPLPythonMath::MatrixExpression<T>::SharedPointer& c)
	{
		return invert2<T>(c, c);
	}

	template <typename T>
	bool equals(const typename CDPLPythonMath::ConstMatrixExpression<T>::SharedPointer& e1,
				const typename CDPLPythonMath::ConstMatrixExpression<T>::SharedPointer& e2,
				const T& eps)
	{
		return CDPL::Math::equals(*e1, *e2, eps);
	}

	template <typename T>
	typename CDPLPythonMath::ConstMatrixExpression<T>::SharedPointer
	conj(const typename CDPLPythonMath::ConstMatrixExpression<T>::SharedPointer& e)
	{
		using namespace CDPLPythonMath;

		typedef typename ConstMatrixExpression<T>::SharedPointer ExpressionPointer;

		return ExpressionPointer(makeConstMatrixExpressionAdapter(CDPL::Math::conj(*e), e));
	}

	template <typename T>
	typename CDPLPythonMath::ConstMatrixExpression<T>::SharedPointer
	herm(const typename CDPLPythonMath::ConstMatrixExpression<T>::SharedPointer& e)
	{
		using namespace CDPLPythonMath;

		typedef typename ConstMatrixExpression<T>::SharedPointer ExpressionPointer;

		return ExpressionPointer(makeConstMatrixExpressionAdapter(CDPL::Math::herm(*e), e));
	}

	template <typename T>
	typename CDPLPythonMath::ConstMatrixExpression<T>::SharedPointer
	real(const typename CDPLPythonMath::ConstMatrixExpression<T>::SharedPointer& e)
	{
		using namespace CDPLPythonMath;

		typedef typename ConstMatrixExpression<T>::SharedPointer ExpressionPointer;

		return ExpressionPointer(makeConstMatrixExpressionAdapter(CDPL::Math::real(*e), e));
	}

	template <typename T>
	typename CDPLPythonMath::ConstMatrixExpression<T>::SharedPointer
	imag(const typename CDPLPythonMath::ConstMatrixExpression<T>::SharedPointer& e)
	{
		using namespace CDPLPythonMath;

		typedef typename ConstMatrixExpression<T>::SharedPointer ExpressionPointer;

		return ExpressionPointer(makeConstMatrixExpressionAdapter(CDPL::Math::imag(*e), e));
	}

	template <typename T>
	typename CDPLPythonMath::ConstMatrixExpression<T>::SharedPointer
	elemDiv(const typename CDPLPythonMath::ConstMatrixExpression<T>::SharedPointer& e1,
			const typename CDPLPythonMath::ConstMatrixExpression<T>::SharedPointer& e2)
	{
		using namespace CDPLPythonMath;

		typedef typename ConstMatrixExpression<T>::SharedPointer ExpressionPointer;

		return ExpressionPointer(makeConstMatrixExpressionAdapter(CDPL::Math::elemDiv(*e1, *e2),
																  std::make_pair(e1, e2)));
	}

	template <typename T>
	typename CDPLPythonMath::ConstMatrixExpression<T>::SharedPointer
	elemProd(const typename CDPLPythonMath::ConstMatrixExpression<T>::SharedPointer& e1,
			 const typename CDPLPythonMath::ConstMatrixExpression<T>::SharedPointer& e2)
	{
		using namespace CDPLPythonMath;

		typedef typename ConstMatrixExpression<T>::SharedPointer ExpressionPointer;

		return ExpressionPointer(makeConstMatrixExpressionAdapter(CDPL::Math::elemProd(*e1, *e2),
																  std::make_pair(e1, e2)));
	}

	template <typename T>
	typename CDPLPythonMath::ConstMatrixExpression<T>::SharedPointer
	outerProd(const typename CDPLPythonMath::ConstVectorExpression<T>::SharedPointer& e1,
			  const typename CDPLPythonMath::ConstVectorExpression<T>::SharedPointer& e2)
	{
		using namespace CDPLPythonMath;

		typedef typename ConstMatrixExpression<T>::SharedPointer ExpressionPointer;

		return ExpressionPointer(makeConstMatrixExpressionAdapter(CDPL::Math::outerProd(*e1, *e2),
																  std::make_pair(e1, e2)));
	}

	template <typename T>
	typename CDPLPythonMath::ConstVectorExpression<T>::SharedPointer
	mtxVecProd1(const typename CDPLPythonMath::ConstMatrixExpression<T>::SharedPointer& e1,
				const typename CDPLPythonMath::ConstVectorExpression<T>::SharedPointer& e2)
	{
		using namespace CDPLPythonMath;

		typedef typename ConstVectorExpression<T>::SharedPointer ExpressionPointer;

		return ExpressionPointer(makeConstVectorExpressionAdapter(CDPL::Math::prod(*e1, *e2),
																  std::make_pair(e1, e2)));
	}

	template <typename T>
	typename CDPLPythonMath::VectorExpression<T>::SharedPointer
	mtxVecProd2(const typename CDPLPythonMath::ConstMatrixExpression<T>::SharedPointer& e1,
				const typename CDPLPythonMath::ConstVectorExpression<T>::SharedPointer& e2,
				const typename CDPLPythonMath::VectorExpression<T>::SharedPointer& c)
	{
		CDPL::Math::prod(*e1, *e2, *c);
		return c;
	}

	template <typename T>
	typename CDPLPythonMath::ConstVectorExpression<T>::SharedPointer
	vecMtxProd1(const typename CDPLPythonMath::ConstVectorExpression<T>::SharedPointer& e1,
				const typename CDPLPythonMath::ConstMatrixExpression<T>::SharedPointer& e2)
	{
		using namespace CDPLPythonMath;

		typedef typename ConstVectorExpression<T>::SharedPointer ExpressionPointer;

		return ExpressionPointer(makeConstVectorExpressionAdapter(CDPL::Math::prod(*e1, *e2),
																  std::make_pair(e1, e2)));
	}

	template <typename T>
	typename CDPLPythonMath::VectorExpression<T>::SharedPointer
	vecMtxProd2(const typename CDPLPythonMath::ConstVectorExpression<T>::SharedPointer& e1,
				const typename CDPLPythonMath::ConstMatrixExpression<T>::SharedPointer& e2,
				const typename CDPLPythonMath::VectorExpression<T>::SharedPointer& c)
	{
		CDPL::Math::prod(*e1, *e2, *c);
		return c;
	}

	template <typename T>
	typename CDPLPythonMath::ConstMatrixExpression<T>::SharedPointer
	mtxMtxProd1(const typename CDPLPythonMath::ConstMatrixExpression<T>::SharedPointer& e1,
				const typename CDPLPythonMath::ConstMatrixExpression<T>::SharedPointer& e2)
	{
		using namespace CDPLPythonMath;

		typedef typename ConstMatrixExpression<T>::SharedPointer ExpressionPointer;

		return ExpressionPointer(makeConstMatrixExpressionAdapter(CDPL::Math::prod(*e1, *e2),
																  std::make_pair(e1, e2)));
	}

	template <typename T>
	typename CDPLPythonMath::MatrixExpression<T>::SharedPointer
	mtxMtxProd2(const typename CDPLPythonMath::ConstMatrixExpression<T>::SharedPointer& e1,
				const typename CDPLPythonMath::ConstMatrixExpression<T>::SharedPointer& e2,
				const typename CDPLPythonMath::MatrixExpression<T>::SharedPointer& c)
	{
		CDPL::Math::prod(*e1, *e2, *c);
		return c;
	}

	template <typename T>
	T trace(const typename CDPLPythonMath::ConstMatrixExpression<T>::SharedPointer& e)
	{
		return CDPL::Math::trace(*e);
	}

	template <typename T>
	T norm1(const typename CDPLPythonMath::ConstMatrixExpression<T>::SharedPointer& e)
	{
		return CDPL::Math::norm1(*e);
	}

	template <typename T>
	T normFrob(const typename CDPLPythonMath::ConstMatrixExpression<T>::SharedPointer& e)
	{
		return CDPL::Math::normFrob(*e);
	}

	template <typename T>
	T normInf(const typename CDPLPythonMath::ConstMatrixExpression<T>::SharedPointer& e)
	{
		return CDPL::Math::normInf(*e);
	}

	template <typename T>
	T sum(const typename CDPLPythonMath::ConstMatrixExpression<T>::SharedPointer& e)
	{
		return CDPL::Math::sum(*e);
	}

	template <typename T>
	typename CDPLPythonMath::ConstMatrixExpression<T>::SharedPointer
	cross(const typename CDPLPythonMath::ConstVectorExpression<T>::SharedPointer& e)
	{
		using namespace CDPLPythonMath;

		typedef typename ConstMatrixExpression<T>::SharedPointer ExpressionPointer;

		return ExpressionPointer(makeConstMatrixExpressionAdapter(CDPL::Math::cross(*e), e));
	}

	template <typename T>
	typename CDPLPythonMath::ConstMatrixExpression<T>::SharedPointer
	diag(const typename CDPLPythonMath::ConstVectorExpression<T>::SharedPointer& e)
	{
		using namespace CDPLPythonMath;

		typedef typename ConstMatrixExpression<T>::SharedPointer ExpressionPointer;

		return ExpressionPointer(makeConstMatrixExpressionAdapter(CDPL::Math::diag(*e), e));
	}

	template <typename T>
	bool jacobiDiagonalize(const typename CDPLPythonMath::MatrixExpression<T>::SharedPointer& a,
						   const typename CDPLPythonMath::VectorExpression<T>::SharedPointer& d,
						   const typename CDPLPythonMath::MatrixExpression<T>::SharedPointer& v, 
							   std::size_t max_iter)
	{
		return CDPL::Math::jacobiDiagonalize
			<CDPLPythonMath::MatrixExpression<T>, CDPLPythonMath::VectorExpression<T>, CDPLPythonMath::MatrixExpression<T> >
			(*a, *d, *v, max_iter);
	}

	template <typename T>
	typename CDPLPythonMath::MatrixExpression<T>::SizeType
	luDecompose1(const typename CDPLPythonMath::MatrixExpression<T>::SharedPointer& e)
	{
		return CDPL::Math::luDecompose<CDPLPythonMath::MatrixExpression<T> >(*e);
	}

	template <typename T>
	typename CDPLPythonMath::MatrixExpression<T>::SizeType
	luDecompose2(const typename CDPLPythonMath::MatrixExpression<T>::SharedPointer& e,
				 const CDPLPythonMath::VectorExpression<unsigned long>::SharedPointer& pv)
	{
		std::size_t num_swaps = 0;

		return CDPL::Math::luDecompose<CDPLPythonMath::MatrixExpression<T> >(*e, *pv, num_swaps);
	}

	template <typename T>
	bool luSubstitute11(const typename CDPLPythonMath::ConstMatrixExpression<T>::SharedPointer& lu,
						const typename CDPLPythonMath::VectorExpression<T>::SharedPointer& b)
	{
		return CDPL::Math::luSubstitute<CDPLPythonMath::ConstMatrixExpression<T>,
			CDPLPythonMath::VectorExpression<T> >(*lu, *b);
	}

	template <typename T>
	bool luSubstitute21(const typename CDPLPythonMath::ConstMatrixExpression<T>::SharedPointer& lu,
						const CDPLPythonMath::ConstVectorExpression<unsigned long>::SharedPointer& pv,
						const typename CDPLPythonMath::VectorExpression<T>::SharedPointer& b)
	{
		return CDPL::Math::luSubstitute
			<CDPLPythonMath::ConstMatrixExpression<T>, CDPLPythonMath::VectorExpression<T>,
			CDPLPythonMath::ConstVectorExpression<unsigned long> >(*lu, *pv, *b);
	}

	template <typename T>
	bool luSubstitute12(const typename CDPLPythonMath::ConstMatrixExpression<T>::SharedPointer& lu,
						const typename CDPLPythonMath::MatrixExpression<T>::SharedPointer& b)
	{
		return CDPL::Math::luSubstitute<CDPLPythonMath::ConstMatrixExpression<T>,
			CDPLPythonMath::MatrixExpression<T> >(*lu, *b);
	}

	template <typename T>
	bool luSubstitute22(const typename CDPLPythonMath::ConstMatrixExpression<T>::SharedPointer& lu,
						const CDPLPythonMath::ConstVectorExpression<unsigned long>::SharedPointer& pv,
						const typename CDPLPythonMath::MatrixExpression<T>::SharedPointer& b)
	{
		return CDPL::Math::luSubstitute
			<CDPLPythonMath::ConstMatrixExpression<T>, CDPLPythonMath::MatrixExpression<T>,
			CDPLPythonMath::ConstVectorExpression<unsigned long> >(*lu, *pv, *b);
	}

	template <typename T>
	bool svDecompose(const typename CDPLPythonMath::MatrixExpression<T>::SharedPointer& a,
					 const typename CDPLPythonMath::VectorExpression<T>::SharedPointer& w,
					 const typename CDPLPythonMath::MatrixExpression<T>::SharedPointer& v, 
					 std::size_t max_iter)
	{
		return CDPL::Math::svDecompose
			<CDPLPythonMath::MatrixExpression<T>, CDPLPythonMath::VectorExpression<T>, CDPLPythonMath::MatrixExpression<T> >
			(*a, *w, *v, max_iter);
	}

	template <typename T>
	void svSubstitute1(const typename CDPLPythonMath::ConstMatrixExpression<T>::SharedPointer& u,
					   const typename CDPLPythonMath::ConstVectorExpression<T>::SharedPointer& w,
					   const typename CDPLPythonMath::ConstMatrixExpression<T>::SharedPointer& v, 
					   const typename CDPLPythonMath::ConstVectorExpression<T>::SharedPointer& b,
					   const typename CDPLPythonMath::VectorExpression<T>::SharedPointer& x)
	{
		return CDPL::Math::svSubstitute
			<CDPLPythonMath::ConstMatrixExpression<T>, CDPLPythonMath::ConstVectorExpression<T>, 
			CDPLPythonMath::ConstMatrixExpression<T>, CDPLPythonMath::ConstVectorExpression<T>,
			CDPLPythonMath::VectorExpression<T> >
			(*u, *w, *v, *b, *x);
	}

	template <typename T>
	void svSubstitute2(const typename CDPLPythonMath::ConstMatrixExpression<T>::SharedPointer& u,
					   const typename CDPLPythonMath::ConstVectorExpression<T>::SharedPointer& w,
					   const typename CDPLPythonMath::ConstMatrixExpression<T>::SharedPointer& v, 
					   const typename CDPLPythonMath::ConstMatrixExpression<T>::SharedPointer& b,
					   const typename CDPLPythonMath::MatrixExpression<T>::SharedPointer& x)
	{
		return CDPL::Math::svSubstitute
			<CDPLPythonMath::ConstMatrixExpression<T>, CDPLPythonMath::ConstVectorExpression<T>, 
			CDPLPythonMath::ConstMatrixExpression<T>, CDPLPythonMath::ConstMatrixExpression<T>,
			CDPLPythonMath::MatrixExpression<T> >
			(*u, *w, *v, *b, *x);
	}

	template <typename T>
	bool solveLower1(const typename CDPLPythonMath::ConstMatrixExpression<T>::SharedPointer& e1,
					 const typename CDPLPythonMath::VectorExpression<T>::SharedPointer& e2)
	{
		return CDPL::Math::solveLower<CDPLPythonMath::ConstMatrixExpression<T>,
			CDPLPythonMath::VectorExpression<T> >(*e1, *e2);
	}

	template <typename T>
	bool solveLower2(const typename CDPLPythonMath::ConstMatrixExpression<T>::SharedPointer& e1,
					 const typename CDPLPythonMath::MatrixExpression<T>::SharedPointer& e2)
	{
		return CDPL::Math::solveLower<CDPLPythonMath::ConstMatrixExpression<T>,
			CDPLPythonMath::MatrixExpression<T> >(*e1, *e2);
	}

	template <typename T>
	bool solveUnitLower1(const typename CDPLPythonMath::ConstMatrixExpression<T>::SharedPointer& e1,
						 const typename CDPLPythonMath::VectorExpression<T>::SharedPointer& e2)
	{
		return CDPL::Math::solveUnitLower<CDPLPythonMath::ConstMatrixExpression<T>,
			CDPLPythonMath::VectorExpression<T> >(*e1, *e2);
	}

	template <typename T>
	bool solveUnitLower2(const typename CDPLPythonMath::ConstMatrixExpression<T>::SharedPointer& e1,
						 const typename CDPLPythonMath::MatrixExpression<T>::SharedPointer& e2)
	{
		return CDPL::Math::solveUnitLower<CDPLPythonMath::ConstMatrixExpression<T>,
			CDPLPythonMath::MatrixExpression<T> >(*e1, *e2);
	}

	template <typename T>
	bool solveUpper1(const typename CDPLPythonMath::ConstMatrixExpression<T>::SharedPointer& e1,
					 const typename CDPLPythonMath::VectorExpression<T>::SharedPointer& e2)
	{
		return CDPL::Math::solveUpper<CDPLPythonMath::ConstMatrixExpression<T>,
			CDPLPythonMath::VectorExpression<T> >(*e1, *e2);
	}

	template <typename T>
	bool solveUpper2(const typename CDPLPythonMath::ConstMatrixExpression<T>::SharedPointer& e1,
					 const typename CDPLPythonMath::MatrixExpression<T>::SharedPointer& e2)
	{
		return CDPL::Math::solveUpper<CDPLPythonMath::ConstMatrixExpression<T>,
			CDPLPythonMath::MatrixExpression<T> >(*e1, *e2);
	}

	template <typename T>
	bool solveUnitUpper1(const typename CDPLPythonMath::ConstMatrixExpression<T>::SharedPointer& e1,
						 const typename CDPLPythonMath::VectorExpression<T>::SharedPointer& e2)
	{
		return CDPL::Math::solveUnitUpper<CDPLPythonMath::ConstMatrixExpression<T>,
			CDPLPythonMath::VectorExpression<T> >(*e1, *e2);
	}

	template <typename T>
	bool solveUnitUpper2(const typename CDPLPythonMath::ConstMatrixExpression<T>::SharedPointer& e1,
						 const typename CDPLPythonMath::MatrixExpression<T>::SharedPointer& e2)
	{
		return CDPL::Math::solveUnitUpper<CDPLPythonMath::ConstMatrixExpression<T>,
			CDPLPythonMath::MatrixExpression<T> >(*e1, *e2);
	}
}


void CDPLPythonMath::exportMatrixFunctions()
{
	using namespace boost;

	python::def("det", &det<float>, python::arg("e"));
	python::def("det", &det<double>, python::arg("e"));
	python::def("det", &det<long>, python::arg("e"));
	python::def("det", &det<unsigned long>, python::arg("e"));

	python::def("invert", &invert1<float>, python::arg("c"));
	python::def("invert", &invert1<double>, python::arg("c"));
	python::def("invert", &invert1<long>, python::arg("c"));
	python::def("invert", &invert1<unsigned long>, python::arg("c"));

	python::def("invert", &invert2<float>, (python::arg("e"), python::arg("c")));
	python::def("invert", &invert2<double>, (python::arg("e"), python::arg("c")));
	python::def("invert", &invert2<long>, (python::arg("e"), python::arg("c")));
	python::def("invert", &invert2<unsigned long>, (python::arg("e"), python::arg("c")));

	python::def("equals", &equals<float>, (python::arg("e1"), python::arg("e2"), python::arg("eps")));
	python::def("equals", &equals<double>, (python::arg("e1"), python::arg("e2"), python::arg("eps")));
	python::def("equals", &equals<long>, (python::arg("e1"), python::arg("e2"), python::arg("eps")));
	python::def("equals", &equals<unsigned long>, (python::arg("e1"), python::arg("e2"), python::arg("eps")));

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

	python::def("elemDiv", &elemDiv<float>, (python::arg("e1"), python::arg("e2")));
	python::def("elemDiv", &elemDiv<double>, (python::arg("e1"), python::arg("e2")));
	python::def("elemDiv", &elemDiv<long>, (python::arg("e1"), python::arg("e2")));
	python::def("elemDiv", &elemDiv<unsigned long>, (python::arg("e1"), python::arg("e2")));

	python::def("elemProd", &elemProd<float>, (python::arg("e1"), python::arg("e2")));
	python::def("elemProd", &elemProd<double>, (python::arg("e1"), python::arg("e2")));
	python::def("elemProd", &elemProd<long>, (python::arg("e1"), python::arg("e2")));
	python::def("elemProd", &elemProd<unsigned long>, (python::arg("e1"), python::arg("e2")));

	python::def("outerProd", &outerProd<float>, (python::arg("e1"), python::arg("e2")));
	python::def("outerProd", &outerProd<double>, (python::arg("e1"), python::arg("e2")));
	python::def("outerProd", &outerProd<long>, (python::arg("e1"), python::arg("e2")));
	python::def("outerProd", &outerProd<unsigned long>, (python::arg("e1"), python::arg("e2")));

	python::def("prod", &mtxVecProd1<float>, (python::arg("e1"), python::arg("e2")));
	python::def("prod", &mtxVecProd1<double>, (python::arg("e1"), python::arg("e2")));
	python::def("prod", &mtxVecProd1<long>, (python::arg("e1"), python::arg("e2")));
	python::def("prod", &mtxVecProd1<unsigned long>, (python::arg("e1"), python::arg("e2")));

	python::def("prod", &mtxVecProd2<float>, (python::arg("e1"), python::arg("e2"), python::arg("c")));
	python::def("prod", &mtxVecProd2<double>, (python::arg("e1"), python::arg("e2"), python::arg("c")));
	python::def("prod", &mtxVecProd2<long>, (python::arg("e1"), python::arg("e2"), python::arg("c")));
	python::def("prod", &mtxVecProd2<unsigned long>, (python::arg("e1"), python::arg("e2"), python::arg("c")));

	python::def("prod", &vecMtxProd1<float>, (python::arg("e1"), python::arg("e2")));
	python::def("prod", &vecMtxProd1<double>, (python::arg("e1"), python::arg("e2")));
	python::def("prod", &vecMtxProd1<long>, (python::arg("e1"), python::arg("e2")));
	python::def("prod", &vecMtxProd1<unsigned long>, (python::arg("e1"), python::arg("e2")));

	python::def("prod", &vecMtxProd2<float>, (python::arg("e1"), python::arg("e2"), python::arg("c")));
	python::def("prod", &vecMtxProd2<double>, (python::arg("e1"), python::arg("e2"), python::arg("c")));
	python::def("prod", &vecMtxProd2<long>, (python::arg("e1"), python::arg("e2"), python::arg("c")));
	python::def("prod", &vecMtxProd2<unsigned long>, (python::arg("e1"), python::arg("e2"), python::arg("c")));

	python::def("prod", &mtxMtxProd1<float>, (python::arg("e1"), python::arg("e2")));
	python::def("prod", &mtxMtxProd1<double>, (python::arg("e1"), python::arg("e2")));
	python::def("prod", &mtxMtxProd1<long>, (python::arg("e1"), python::arg("e2")));
	python::def("prod", &mtxMtxProd1<unsigned long>, (python::arg("e1"), python::arg("e2")));

	python::def("prod", &mtxMtxProd2<float>, (python::arg("e1"), python::arg("e2"), python::arg("c")));
	python::def("prod", &mtxMtxProd2<double>, (python::arg("e1"), python::arg("e2"), python::arg("c")));
	python::def("prod", &mtxMtxProd2<long>, (python::arg("e1"), python::arg("e2"), python::arg("c")));
	python::def("prod", &mtxMtxProd2<unsigned long>, (python::arg("e1"), python::arg("e2"), python::arg("c")));

	python::def("trace", &trace<float>, python::arg("e"));
	python::def("trace", &trace<double>, python::arg("e"));
	python::def("trace", &trace<long>, python::arg("e"));
	python::def("trace", &trace<unsigned long>, python::arg("e"));

	python::def("norm1", &norm1<float>, python::arg("e"));
	python::def("norm1", &norm1<double>, python::arg("e"));
	python::def("norm1", &norm1<long>, python::arg("e"));
	python::def("norm1", &norm1<unsigned long>, python::arg("e"));

	python::def("normFrob", &normFrob<float>, python::arg("e"));
	python::def("normFrob", &normFrob<double>, python::arg("e"));
	python::def("normFrob", &normFrob<long>, python::arg("e"));
	python::def("normFrob", &normFrob<unsigned long>, python::arg("e"));

	python::def("normInf", &normInf<float>, python::arg("e"));
	python::def("normInf", &normInf<double>, python::arg("e"));
	python::def("normInf", &normInf<long>, python::arg("e"));
	python::def("normInf", &normInf<unsigned long>, python::arg("e"));

	python::def("sum", &sum<float>, python::arg("e"));
	python::def("sum", &sum<double>, python::arg("e"));
	python::def("sum", &sum<long>, python::arg("e"));
	python::def("sum", &sum<unsigned long>, python::arg("e"));

	python::def("cross", &cross<float>, python::arg("e"));
	python::def("cross", &cross<double>, python::arg("e"));
	python::def("cross", &cross<long>, python::arg("e"));
	python::def("cross", &cross<unsigned long>, python::arg("e"));

	python::def("diag", &diag<float>, python::arg("e"));
	python::def("diag", &diag<double>, python::arg("e"));
	python::def("diag", &diag<long>, python::arg("e"));
	python::def("diag", &diag<unsigned long>, python::arg("e"));

	python::def("jacobiDiagonalize", &jacobiDiagonalize<float>, 
				(python::arg("a"), python::arg("d"), python::arg("v"), python::arg("max_iter") = 50));
	python::def("jacobiDiagonalize", &jacobiDiagonalize<double>, 
				(python::arg("a"), python::arg("d"), python::arg("v"), python::arg("max_iter") = 50));
	python::def("jacobiDiagonalize", &jacobiDiagonalize<long>, 
				(python::arg("a"), python::arg("d"), python::arg("v"), python::arg("max_iter") = 50));
	python::def("jacobiDiagonalize", &jacobiDiagonalize<unsigned long>, 
				(python::arg("a"), python::arg("d"), python::arg("v"), python::arg("max_iter") = 50));

	python::def("luDecompose", &luDecompose1<float>, python::arg("e"));
	python::def("luDecompose", &luDecompose1<double>, python::arg("e"));
	python::def("luDecompose", &luDecompose1<long>, python::arg("e"));
	python::def("luDecompose", &luDecompose1<unsigned long>, python::arg("e"));

	python::def("luDecompose", &luDecompose2<float>, (python::arg("e"), python::arg("pv")));
	python::def("luDecompose", &luDecompose2<double>, (python::arg("e"), python::arg("pv")));
	python::def("luDecompose", &luDecompose2<long>, (python::arg("e"), python::arg("pv")));
	python::def("luDecompose", &luDecompose2<unsigned long>, (python::arg("e"), python::arg("pv")));

	python::def("luSubstitute", &luSubstitute11<float>, (python::arg("e"), python::arg("b")));
	python::def("luSubstitute", &luSubstitute11<double>, (python::arg("e"), python::arg("b")));
	python::def("luSubstitute", &luSubstitute11<long>, (python::arg("e"), python::arg("b")));
	python::def("luSubstitute", &luSubstitute11<unsigned long>, (python::arg("e"), python::arg("b")));

	python::def("luSubstitute", &luSubstitute21<float>, (python::arg("e"), python::arg("pv"), python::arg("b")));
	python::def("luSubstitute", &luSubstitute21<double>, (python::arg("e"), python::arg("pv"), python::arg("b")));
	python::def("luSubstitute", &luSubstitute21<long>, (python::arg("e"), python::arg("pv"), python::arg("b")));
	python::def("luSubstitute", &luSubstitute21<unsigned long>, (python::arg("e"), python::arg("pv"), python::arg("b")));

	python::def("luSubstitute", &luSubstitute12<float>, (python::arg("e"), python::arg("b")));
	python::def("luSubstitute", &luSubstitute12<double>, (python::arg("e"), python::arg("b")));
	python::def("luSubstitute", &luSubstitute12<long>, (python::arg("e"), python::arg("b")));
	python::def("luSubstitute", &luSubstitute12<unsigned long>, (python::arg("e"), python::arg("b")));

	python::def("luSubstitute", &luSubstitute22<float>, (python::arg("e"), python::arg("pv"), python::arg("b")));
	python::def("luSubstitute", &luSubstitute22<double>, (python::arg("e"), python::arg("pv"), python::arg("b")));
	python::def("luSubstitute", &luSubstitute22<long>, (python::arg("e"), python::arg("pv"), python::arg("b")));
	python::def("luSubstitute", &luSubstitute22<unsigned long>, (python::arg("e"), python::arg("pv"), python::arg("b")));

	python::def("svDecompose", &svDecompose<float>, 
				(python::arg("a"), python::arg("w"), python::arg("v"), python::arg("max_iter") = 0));
	python::def("svDecompose", &svDecompose<double>, 
				(python::arg("a"), python::arg("w"), python::arg("v"), python::arg("max_iter") = 0));
	python::def("svDecompose", &svDecompose<long>, 
				(python::arg("a"), python::arg("w"), python::arg("v"), python::arg("max_iter") = 0));
	python::def("svDecompose", &svDecompose<unsigned long>, 
				(python::arg("a"), python::arg("w"), python::arg("v"), python::arg("max_iter") = 0));

	python::def("svSubstitute", &svSubstitute1<float>, 
				(python::arg("u"), python::arg("w"), python::arg("v"), python::arg("b"),  python::arg("x")));
	python::def("svSubstitute", &svSubstitute1<double>, 
				(python::arg("u"), python::arg("w"), python::arg("v"), python::arg("b"),  python::arg("x")));
	python::def("svSubstitute", &svSubstitute1<long>, 
				(python::arg("u"), python::arg("w"), python::arg("v"), python::arg("b"),  python::arg("x")));
	python::def("svSubstitute", &svSubstitute1<unsigned long>, 
				(python::arg("u"), python::arg("w"), python::arg("v"), python::arg("b"),  python::arg("x")));

	python::def("svSubstitute", &svSubstitute2<float>, 
				(python::arg("u"), python::arg("w"), python::arg("v"), python::arg("b"),  python::arg("x")));
	python::def("svSubstitute", &svSubstitute2<double>, 
				(python::arg("u"), python::arg("w"), python::arg("v"), python::arg("b"),  python::arg("x")));
	python::def("svSubstitute", &svSubstitute2<long>, 
				(python::arg("u"), python::arg("w"), python::arg("v"), python::arg("b"),  python::arg("x")));
	python::def("svSubstitute", &svSubstitute2<unsigned long>, 
				(python::arg("u"), python::arg("w"), python::arg("v"), python::arg("b"),  python::arg("x")));

	python::def("solveLower", &solveLower1<float>, (python::arg("e1"), python::arg("e2")));
	python::def("solveLower", &solveLower1<double>, (python::arg("e1"), python::arg("e2")));
	python::def("solveLower", &solveLower1<long>, (python::arg("e1"), python::arg("e2")));
	python::def("solveLower", &solveLower1<unsigned long>, (python::arg("e1"), python::arg("e2")));

	python::def("solveLower", &solveLower2<float>, (python::arg("e1"), python::arg("e2")));
	python::def("solveLower", &solveLower2<double>, (python::arg("e1"), python::arg("e2")));
	python::def("solveLower", &solveLower2<long>, (python::arg("e1"), python::arg("e2")));
	python::def("solveLower", &solveLower2<unsigned long>, (python::arg("e1"), python::arg("e2")));

	python::def("solveUnitLower", &solveUnitLower1<float>, (python::arg("e1"), python::arg("e2")));
	python::def("solveUnitLower", &solveUnitLower1<double>, (python::arg("e1"), python::arg("e2")));
	python::def("solveUnitLower", &solveUnitLower1<long>, (python::arg("e1"), python::arg("e2")));
	python::def("solveUnitLower", &solveUnitLower1<unsigned long>, (python::arg("e1"), python::arg("e2")));

	python::def("solveUnitLower", &solveUnitLower2<float>, (python::arg("e1"), python::arg("e2")));
	python::def("solveUnitLower", &solveUnitLower2<double>, (python::arg("e1"), python::arg("e2")));
	python::def("solveUnitLower", &solveUnitLower2<long>, (python::arg("e1"), python::arg("e2")));
	python::def("solveUnitLower", &solveUnitLower2<unsigned long>, (python::arg("e1"), python::arg("e2")));

	python::def("solveUpper", &solveUpper1<float>, (python::arg("e1"), python::arg("e2")));
	python::def("solveUpper", &solveUpper1<double>, (python::arg("e1"), python::arg("e2")));
	python::def("solveUpper", &solveUpper1<long>, (python::arg("e1"), python::arg("e2")));
	python::def("solveUpper", &solveUpper1<unsigned long>, (python::arg("e1"), python::arg("e2")));

	python::def("solveUpper", &solveUpper2<float>, (python::arg("e1"), python::arg("e2")));
	python::def("solveUpper", &solveUpper2<double>, (python::arg("e1"), python::arg("e2")));
	python::def("solveUpper", &solveUpper2<long>, (python::arg("e1"), python::arg("e2")));
	python::def("solveUpper", &solveUpper2<unsigned long>, (python::arg("e1"), python::arg("e2")));

	python::def("solveUnitUpper", &solveUnitUpper1<float>, (python::arg("e1"), python::arg("e2")));
	python::def("solveUnitUpper", &solveUnitUpper1<double>, (python::arg("e1"), python::arg("e2")));
	python::def("solveUnitUpper", &solveUnitUpper1<long>, (python::arg("e1"), python::arg("e2")));
	python::def("solveUnitUpper", &solveUnitUpper1<unsigned long>, (python::arg("e1"), python::arg("e2")));

	python::def("solveUnitUpper", &solveUnitUpper2<float>, (python::arg("e1"), python::arg("e2")));
	python::def("solveUnitUpper", &solveUnitUpper2<double>, (python::arg("e1"), python::arg("e2")));
	python::def("solveUnitUpper", &solveUnitUpper2<long>, (python::arg("e1"), python::arg("e2")));
	python::def("solveUnitUpper", &solveUnitUpper2<unsigned long>, (python::arg("e1"), python::arg("e2")));
}
