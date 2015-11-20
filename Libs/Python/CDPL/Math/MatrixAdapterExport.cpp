/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * MatrixAdapterExport.cpp 
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


#include <cstddef>

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

	template <typename TriangType>
	struct TriangularityTypeExport
	{

		TriangularityTypeExport(const char* name) {
			using namespace boost;
			using namespace CDPLPythonMath;

			python::class_<TriangType>(name, python::no_init)
				.def(python::init<>(python::arg("self")))
				.def(python::init<const TriangType&>((python::arg("self"), python::arg("t"))));
		}
	};

	template <typename ExpressionType>
	struct ConstMatrixTransposeExport
	{

		typedef CDPL::Math::MatrixTranspose<const ExpressionType> MatrixTransposeType;
		typedef CDPLPythonMath::ExpressionAdapterWrapper<ExpressionType, MatrixTransposeType> MatrixTransposeWrapper;
		typedef typename MatrixTransposeWrapper::ExpressionPointerType ExpressionPointerType;
		typedef typename MatrixTransposeWrapper::SharedPointer WrapperPointerType;

		ConstMatrixTransposeExport(const char* name) {
			using namespace boost;
			using namespace CDPLPythonMath;
		
			python::class_<MatrixTransposeWrapper, WrapperPointerType, boost::noncopyable>(name, python::no_init)
				.def(python::init<const MatrixTransposeWrapper&>((python::arg("self"), python::arg("mt"))))
				.def(python::init<const ExpressionPointerType&>((python::arg("self"), python::arg("e"))))
				.def(CDPLPythonBase::ObjectIdentityCheckVisitor<MatrixTransposeType>())
				.def(ConstMatrixVisitor<MatrixTransposeType>("mt"))
				.def(WrappedDataVisitor<MatrixTransposeWrapper>());

			python::def("trans", &trans, python::arg("e"));
		}

		static WrapperPointerType trans(const ExpressionPointerType& e) {
			return WrapperPointerType(new MatrixTransposeWrapper(e));
		}
	};

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
				.def(WrappedDataVisitor<MatrixTransposeWrapper>());

			python::def("trans", &trans, python::arg("e"));
		}

		static WrapperPointerType trans(const ExpressionPointerType& e) {
			return WrapperPointerType(new MatrixTransposeWrapper(e));
		}
	};

	template <typename ExpressionType, typename TriangType>
	struct TriangularAdapterExport
	{
	
		typedef CDPL::Math::TriangularAdapter<const ExpressionType, TriangType> TriangularAdapterType;
		typedef CDPLPythonMath::ExpressionAdapterWrapper<ExpressionType, TriangularAdapterType> TriangularAdapterWrapper;
		typedef typename TriangularAdapterWrapper::ExpressionPointerType ExpressionPointerType;
		typedef typename TriangularAdapterWrapper::SharedPointer WrapperPointerType;

		TriangularAdapterExport(const char* name) {
			using namespace boost;
			using namespace CDPLPythonMath;
	
			python::class_<TriangularAdapterWrapper, WrapperPointerType, boost::noncopyable>(name, python::no_init)
				.def(python::init<const TriangularAdapterWrapper&>((python::arg("self"), python::arg("a"))))
				.def(python::init<const ExpressionPointerType&>((python::arg("self"), python::arg("e"))))
				.def(CDPLPythonBase::ObjectIdentityCheckVisitor<TriangularAdapterType>())
				.def(ConstMatrixVisitor<TriangularAdapterType>("a"))
				.def(WrappedDataVisitor<TriangularAdapterWrapper>());

			python::def("triang", &triang, (python::arg("e"), python::arg("type")));
		}

		static WrapperPointerType triang(const ExpressionPointerType& e, const TriangType&) {
			return WrapperPointerType(new TriangularAdapterWrapper(e));
		}
	};
}


void CDPLPythonMath::exportMatrixAdapters()
{
	using namespace CDPL;

	TriangularityTypeExport<Math::Upper>("Upper");
	TriangularityTypeExport<Math::Lower>("Lower");
	TriangularityTypeExport<Math::UnitUpper>("UnitUpper");
	TriangularityTypeExport<Math::UnitLower>("UnitLower");

	ConstMatrixTransposeExport<ConstMatrixExpression<float> >("ConstFMatrixTranspose");
	ConstMatrixTransposeExport<ConstMatrixExpression<double> >("ConstDMatrixTranspose");
	ConstMatrixTransposeExport<ConstMatrixExpression<long> >("ConstLMatrixTranspose");
	ConstMatrixTransposeExport<ConstMatrixExpression<unsigned long> >("ConstULMatrixTranspose");

	MatrixTransposeExport<MatrixExpression<float> >("FMatrixTranspose");
	MatrixTransposeExport<MatrixExpression<double> >("DMatrixTranspose");
	MatrixTransposeExport<MatrixExpression<long> >("LMatrixTranspose");
	MatrixTransposeExport<MatrixExpression<unsigned long> >("ULMatrixTranspose");

	TriangularAdapterExport<ConstMatrixExpression<float>, Math::Upper>("ConstUpperTriangularFMatrixAdapter");
	TriangularAdapterExport<ConstMatrixExpression<float>, Math::UnitUpper>("ConstUnitUpperTriangularFMatrixAdapter");
	TriangularAdapterExport<ConstMatrixExpression<float>, Math::Lower>("ConstLowerTriangularFMatrixAdapter");
	TriangularAdapterExport<ConstMatrixExpression<float>, Math::UnitLower>("ConstUnitLowerTriangularFMatrixAdapter");

	TriangularAdapterExport<ConstMatrixExpression<double>, Math::Upper>("ConstUpperTriangularDMatrixAdapter");
	TriangularAdapterExport<ConstMatrixExpression<double>, Math::UnitUpper>("ConstUnitUpperTriangularDMatrixAdapter");
	TriangularAdapterExport<ConstMatrixExpression<double>, Math::Lower>("ConstLowerTriangularDMatrixAdapter");
	TriangularAdapterExport<ConstMatrixExpression<double>, Math::UnitLower>("ConstUnitLowerTriangularDMatrixAdapter");

	TriangularAdapterExport<ConstMatrixExpression<long>, Math::Upper>("ConstUpperTriangularLMatrixAdapter");
	TriangularAdapterExport<ConstMatrixExpression<long>, Math::UnitUpper>("ConstUnitUpperTriangularLMatrixAdapter");
	TriangularAdapterExport<ConstMatrixExpression<long>, Math::Lower>("ConstLowerTriangularLMatrixAdapter");
	TriangularAdapterExport<ConstMatrixExpression<long>, Math::UnitLower>("ConstUnitLowerTriangularLMatrixAdapter");

	TriangularAdapterExport<ConstMatrixExpression<unsigned long>, Math::Upper>("ConstUpperTriangularULMatrixAdapter");
	TriangularAdapterExport<ConstMatrixExpression<unsigned long>, Math::UnitUpper>("ConstUnitUpperTriangularULMatrixAdapter");
	TriangularAdapterExport<ConstMatrixExpression<unsigned long>, Math::Lower>("ConstLowerTriangularULMatrixAdapter");
	TriangularAdapterExport<ConstMatrixExpression<unsigned long>, Math::UnitLower>("ConstUnitLowerTriangularULMatrixAdapter");
}
