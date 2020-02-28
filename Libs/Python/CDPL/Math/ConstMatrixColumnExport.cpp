/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * ConstMatrixColumnExport.cpp 
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

#include "CDPL/Math/MatrixProxy.hpp"
#include "CDPL/Math/IO.hpp"

#include "Base/ObjectIdentityCheckVisitor.hpp"

#include "ExpressionProxyWrapper.hpp"
#include "VectorExpression.hpp"
#include "VectorVisitor.hpp"
#include "WrappedDataVisitor.hpp"
#include "ClassExports.hpp"


namespace
{

	template <typename ExpressionType>
	struct ConstMatrixColumnExport
	{
	
		typedef CDPL::Math::MatrixColumn<const ExpressionType> MatrixColumnType;
		typedef typename MatrixColumnType::SizeType SizeType;
		typedef CDPLPythonMath::VectorExpressionProxyWrapper<ExpressionType, SizeType, MatrixColumnType> MatrixColumnWrapper;
		typedef typename MatrixColumnWrapper::ExpressionPointerType ExpressionPointerType;
		typedef typename MatrixColumnWrapper::SharedPointer WrapperPointerType;

		ConstMatrixColumnExport(const char* name) {
			using namespace boost;
			using namespace CDPLPythonMath;

			python::class_<MatrixColumnWrapper, WrapperPointerType, boost::noncopyable>(name, python::no_init)
				.def(python::init<const MatrixColumnWrapper&>((python::arg("self"), python::arg("c"))))
				.def(python::init<const ExpressionPointerType&, SizeType>((python::arg("self"), python::arg("e"), python::arg("i"))))
				.def("getIndex", &MatrixColumnType::getIndex, python::arg("self"))
				.def(CDPLPythonBase::ObjectIdentityCheckVisitor<MatrixColumnType>())
				.def(ConstVectorVisitor<MatrixColumnType>("c"))
				.def(WrappedDataVisitor<MatrixColumnWrapper>())
				.add_property("index", &MatrixColumnType::getIndex);

			python::def("column", &column, (python::arg("e"), python::arg("i")));
		}

		static WrapperPointerType column(const ExpressionPointerType& e, SizeType i) {
			return WrapperPointerType(new MatrixColumnWrapper(e, i));
		}
	};
}


void CDPLPythonMath::exportConstMatrixColumnTypes()
{
	ConstMatrixColumnExport<ConstMatrixExpression<float> >("ConstFMatrixColumn");
	ConstMatrixColumnExport<ConstMatrixExpression<double> >("ConstDMatrixColumn");
	ConstMatrixColumnExport<ConstMatrixExpression<long> >("ConstLMatrixColumn");
	ConstMatrixColumnExport<ConstMatrixExpression<unsigned long> >("ConstULMatrixColumn");
}
