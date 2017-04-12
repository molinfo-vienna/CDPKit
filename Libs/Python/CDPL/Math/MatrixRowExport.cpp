/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * MatrixRowExport.cpp 
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

#include "CDPL/Math/MatrixProxy.hpp"
#include "CDPL/Math/IO.hpp"

#include "Base/ObjectIdentityCheckVisitor.hpp"

#include "ExpressionProxyWrapper.hpp"
#include "VectorExpression.hpp"
#include "VectorVisitor.hpp"
#include "WrappedDataVisitor.hpp"
#include "AssignFunctionGeneratorVisitor.hpp"
#include "ClassExports.hpp"


namespace
{

	template <typename ExpressionType>
	struct MatrixRowExport
	{

		typedef CDPL::Math::MatrixRow<ExpressionType> MatrixRowType;
		typedef typename MatrixRowType::SizeType SizeType;
		typedef CDPLPythonMath::VectorExpressionProxyWrapper<ExpressionType, SizeType, MatrixRowType> MatrixRowWrapper;
		typedef typename MatrixRowWrapper::ExpressionPointerType ExpressionPointerType;
		typedef typename MatrixRowWrapper::SharedPointer WrapperPointerType;

		MatrixRowExport(const char* name) {
			using namespace boost;
			using namespace CDPLPythonMath;

			python::class_<MatrixRowWrapper, WrapperPointerType, boost::noncopyable>(name, python::no_init)
				.def(python::init<const MatrixRowWrapper&>((python::arg("self"), python::arg("mr"))))
				.def(python::init<const ExpressionPointerType&, SizeType>((python::arg("self"), python::arg("e"), python::arg("i"))))
				.def("getIndex", &MatrixRowType::getIndex, python::arg("self"))
				.def(CDPLPythonBase::ObjectIdentityCheckVisitor<MatrixRowType>())
				.def(AssignFunctionGeneratorVisitor<MatrixRowType, ConstVectorExpression>("e"))
				.def(ConstVectorVisitor<MatrixRowType>("r"))
				.def(VectorAssignAndSwapVisitor<MatrixRowType>("r"))
				.def(VectorVisitor<MatrixRowType>("r"))
				.def(WrappedDataVisitor<MatrixRowWrapper>())
				.add_property("index", &MatrixRowType::getIndex);

			python::def("row", &row, (python::arg("e"), python::arg("i")));
		}

		static WrapperPointerType row(const ExpressionPointerType& e, SizeType i) {
			return WrapperPointerType(new MatrixRowWrapper(e, i));
		}
	};
}


void CDPLPythonMath::exportMatrixRowTypes()
{
	MatrixRowExport<MatrixExpression<float> >("FMatrixRow");
	MatrixRowExport<MatrixExpression<double> >("DMatrixRow");
	MatrixRowExport<MatrixExpression<long> >("LMatrixRow");
	MatrixRowExport<MatrixExpression<unsigned long> >("ULMatrixRow");
}
