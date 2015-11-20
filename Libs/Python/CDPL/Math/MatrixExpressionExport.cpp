/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * MatrixExpressionExport.cpp 
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

#include "CDPL/Math/IO.hpp"

#include "Base/ObjectIdentityCheckVisitor.hpp"

#include "MatrixExpression.hpp"
#include "MatrixVisitor.hpp"
#include "AssignFunctionGeneratorVisitor.hpp"
#include "ClassExports.hpp"


namespace
{

	template <typename T>
	struct ConstMatrixExpressionExport
	{

		typedef CDPLPythonMath::ConstMatrixExpression<T> ExpressionType;
		typedef typename ExpressionType::SharedPointer ExpressionPointer;

		ConstMatrixExpressionExport(const char* name) {
			using namespace boost;

			python::class_<ExpressionType, ExpressionPointer, boost::noncopyable>(name, python::no_init)
				.def(CDPLPythonBase::ObjectIdentityCheckVisitor<ExpressionType>())
				.def(CDPLPythonMath::ConstMatrixVisitor<ExpressionType>("e"));
		}
	};

	template <typename T>
	struct MatrixExpressionExport
	{

		typedef CDPLPythonMath::MatrixExpression<T> ExpressionType;
		typedef typename ExpressionType::SharedPointer ExpressionPointer;
		typedef typename ExpressionType::ConstExpressionPointer ConstExpressionPointer;

		MatrixExpressionExport(const char* name) {
			using namespace boost;
			using namespace CDPLPythonMath;

			python::class_<ExpressionType, ExpressionPointer, 
				python::bases<ConstMatrixExpression<T> >, boost::noncopyable>(name, python::no_init)
				.def("swap", &swapExpr, (python::arg("self"), python::arg("e")))
				.def(MatrixAssignAndSwapVisitor<ExpressionType>("e"))
				.def(AssignFunctionGeneratorVisitor<ExpressionType, ConstMatrixExpression>("e"))
				.def(MatrixVisitor<ExpressionType>("e"));

			python::implicitly_convertible<ExpressionPointer, ConstExpressionPointer>();
		}

		static void swapExpr(ExpressionType& mtx1, const ExpressionPointer& mtx2_expr) {
			mtx1.swap(*mtx2_expr);
		}
	};
}


void CDPLPythonMath::exportMatrixExpressions()
{
	ConstMatrixExpressionExport<float>("ConstFMatrixExpression");
	MatrixExpressionExport<float>("FMatrixExpression");

	ConstMatrixExpressionExport<double>("ConstDMatrixExpression");
	MatrixExpressionExport<double>("DMatrixExpression");

	ConstMatrixExpressionExport<long>("ConstLMatrixExpression");
	MatrixExpressionExport<long>("LMatrixExpression");

	ConstMatrixExpressionExport<unsigned long>("ConstULMatrixExpression");
	MatrixExpressionExport<unsigned long>("ULMatrixExpression");
}
