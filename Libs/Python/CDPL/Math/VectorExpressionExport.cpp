/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * VectorExpressionExport.cpp 
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


#include <boost/python.hpp>

#include "CDPL/Math/MatrixExpression.hpp"
#include "CDPL/Math/IO.hpp"

#include "Base/ObjectIdentityCheckVisitor.hpp"

#include "VectorExpression.hpp"
#include "VectorVisitor.hpp"
#include "AssignFunctionGeneratorVisitor.hpp"
#include "ClassExports.hpp"


namespace
{

	template <typename T>
	struct ConstVectorExpressionExport
	{

		typedef CDPLPythonMath::ConstVectorExpression<T> ExpressionType;
		typedef typename ExpressionType::SharedPointer ExpressionPointer;

		ConstVectorExpressionExport(const char* name) {
			using namespace boost;

			python::class_<ExpressionType, ExpressionPointer, boost::noncopyable>(name, python::no_init)
				.def(CDPLPythonBase::ObjectIdentityCheckVisitor<ExpressionType>())
				.def(CDPLPythonMath::ConstVectorVisitor<ExpressionType>("e"));
		}
	};

	template <typename T>
	struct VectorExpressionExport
	{

		typedef CDPLPythonMath::VectorExpression<T> ExpressionType;
		typedef typename ExpressionType::SharedPointer ExpressionPointer;
		typedef typename ExpressionType::ConstExpressionPointer ConstExpressionPointer;

		VectorExpressionExport(const char* name) {
			using namespace boost;
			using namespace CDPLPythonMath;

			python::class_<ExpressionType, ExpressionPointer, 
				python::bases<ConstVectorExpression<T> >, boost::noncopyable>(name, python::no_init)
				.def("swap", &swapExpr, (python::arg("self"), python::arg("e")))
				.def(VectorAssignAndSwapVisitor<ExpressionType>("e"))
				.def(AssignFunctionGeneratorVisitor<ExpressionType, ConstVectorExpression>("e"))
				.def(VectorNDArrayAssignVisitor<ExpressionType, false>())
				.def(VectorVisitor<ExpressionType>("e"));

			python::implicitly_convertible<ExpressionPointer, ConstExpressionPointer>();
		}

		static void swapExpr(ExpressionType& vec1, const ExpressionPointer& vec2_expr) {
			vec1.swap(*vec2_expr);
		}
	};
}


void CDPLPythonMath::exportVectorExpressionTypes()
{
	ConstVectorExpressionExport<float>("ConstFVectorExpression");
	VectorExpressionExport<float>("FVectorExpression");

	ConstVectorExpressionExport<double>("ConstDVectorExpression");
	VectorExpressionExport<double>("DVectorExpression");

	ConstVectorExpressionExport<long>("ConstLVectorExpression");
	VectorExpressionExport<long>("LVectorExpression");

	ConstVectorExpressionExport<unsigned long>("ConstULVectorExpression");
	VectorExpressionExport<unsigned long>("ULVectorExpression");
}
