/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * MatrixTransposeExport.cpp 
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

#include "CDPL/Math/MatrixAdapter.hpp"
#include "CDPL/Math/IO.hpp"

#include "Base/ObjectIdentityCheckVisitor.hpp"

#include "ExpressionAdapterWrapper.hpp"
#include "MatrixExpression.hpp"
#include "MatrixVisitor.hpp"
#include "AssignFunctionGeneratorVisitor.hpp"
#include "WrappedDataVisitor.hpp"
#include "ClassExports.hpp"


namespace
{

	template <typename ExpressionType>
	struct MatrixTransposeExport
	{

		typedef CDPL::Math::MatrixTranspose<ExpressionType> MatrixTransposeType;
		typedef CDPLPythonMath::ExpressionAdapterWrapper<ExpressionType, MatrixTransposeType> MatrixTransposeWrapper;
		typedef typename MatrixTransposeWrapper::ExpressionPointerType ExpressionPointerType;
		typedef typename MatrixTransposeWrapper::SharedPointer WrapperPointerType;

		MatrixTransposeExport(const char* name) {
			using namespace boost;
			using namespace CDPLPythonMath;
		
			python::class_<MatrixTransposeWrapper, WrapperPointerType, boost::noncopyable>(name, python::no_init)
				.def(python::init<const MatrixTransposeWrapper&>((python::arg("self"), python::arg("mt"))))
				.def(python::init<const ExpressionPointerType&>((python::arg("self"), python::arg("e"))))
				.def(CDPLPythonBase::ObjectIdentityCheckVisitor<MatrixTransposeType>())
				.def(AssignFunctionGeneratorVisitor<MatrixTransposeType, ConstMatrixExpression>("e"))
				.def(ConstMatrixVisitor<MatrixTransposeType>("mt"))
				.def(MatrixAssignAndSwapVisitor<MatrixTransposeType>("mt"))
				.def(MatrixVisitor<MatrixTransposeType>("mt"))
				.def(MatrixNDArrayAssignVisitor<MatrixTransposeType>())
				.def(WrappedDataVisitor<MatrixTransposeWrapper>());

			python::def("trans", &trans, python::arg("e"));
		}

		static WrapperPointerType trans(const ExpressionPointerType& e) {
			return WrapperPointerType(new MatrixTransposeWrapper(e));
		}
	};
}


void CDPLPythonMath::exportMatrixTransposeTypes()
{
	using namespace CDPL;

	MatrixTransposeExport<MatrixExpression<float> >("FMatrixTranspose");
	MatrixTransposeExport<MatrixExpression<double> >("DMatrixTranspose");
	MatrixTransposeExport<MatrixExpression<long> >("LMatrixTranspose");
	MatrixTransposeExport<MatrixExpression<unsigned long> >("ULMatrixTranspose");
}
