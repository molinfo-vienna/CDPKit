/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * QuaternionExpressionExport.cpp 
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

#include "CDPL/Math/IO.hpp"

#include "Base/ObjectIdentityCheckVisitor.hpp"

#include "QuaternionExpression.hpp"
#include "QuaternionVisitor.hpp"
#include "AssignFunctionGeneratorVisitor.hpp"
#include "ClassExports.hpp"


namespace
{

	template <typename T>
	struct ConstQuaternionExpressionExport
	{

		typedef CDPLPythonMath::ConstQuaternionExpression<T> ExpressionType;
		typedef typename ExpressionType::SharedPointer ExpressionPointer;

		ConstQuaternionExpressionExport(const char* name) {
			using namespace boost;

			python::class_<ExpressionType, ExpressionPointer, boost::noncopyable>(name, python::no_init)
				.def(CDPLPythonBase::ObjectIdentityCheckVisitor<ExpressionType>())
				.def(CDPLPythonMath::ConstQuaternionVisitor<ExpressionType>("e"));
		}
	};

	template <typename T>
	struct QuaternionExpressionExport
	{

		typedef CDPLPythonMath::QuaternionExpression<T> ExpressionType;
		typedef typename ExpressionType::SharedPointer ExpressionPointer;
		typedef typename ExpressionType::ConstExpressionPointer ConstExpressionPointer;

		QuaternionExpressionExport(const char* name) {
			using namespace boost;
			using namespace CDPLPythonMath;

			python::class_<ExpressionType, ExpressionPointer, 
				python::bases<ConstQuaternionExpression<T> >, boost::noncopyable>(name, python::no_init)
				.def("swap", &swapExpr, (python::arg("self"), python::arg("e")))
				.def(QuaternionAssignAndSwapVisitor<ExpressionType>("e"))
				.def(AssignFunctionGeneratorVisitor<ExpressionType, ConstQuaternionExpression>("e"))
				.def(QuaternionNDArrayAssignVisitor<ExpressionType>())
				.def(QuaternionVisitor<ExpressionType>("e"));

			python::implicitly_convertible<ExpressionPointer, ConstExpressionPointer>();
		}

		static void swapExpr(ExpressionType& quat1, const ExpressionPointer& quat2_expr) {
			quat1.swap(*quat2_expr);
		}
	};
}


void CDPLPythonMath::exportQuaternionExpressionTypes()
{
	ConstQuaternionExpressionExport<float>("ConstFQuaternionExpression");
	QuaternionExpressionExport<float>("FQuaternionExpression");

	ConstQuaternionExpressionExport<double>("ConstDQuaternionExpression");
	QuaternionExpressionExport<double>("DQuaternionExpression");

	ConstQuaternionExpressionExport<long>("ConstLQuaternionExpression");
	QuaternionExpressionExport<long>("LQuaternionExpression");

	ConstQuaternionExpressionExport<unsigned long>("ConstULQuaternionExpression");
	QuaternionExpressionExport<unsigned long>("ULQuaternionExpression");
}
