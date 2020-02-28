/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * QuaternionAdapterExport.cpp 
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

#include "CDPL/Math/QuaternionAdapter.hpp"
#include "CDPL/Math/IO.hpp"

#include "Base/ObjectIdentityCheckVisitor.hpp"

#include "ExpressionAdapterWrapper.hpp"
#include "VectorExpression.hpp"
#include "QuaternionExpression.hpp"
#include "VectorVisitor.hpp"
#include "AssignFunctionGeneratorVisitor.hpp"
#include "WrappedDataVisitor.hpp"
#include "ClassExports.hpp"


namespace
{

	template <typename ExpressionType>
	struct ConstQuaternionVectorAdapterExport
	{
	
		typedef CDPL::Math::QuaternionVectorAdapter<ExpressionType> QuaternionAdapterType;
		typedef CDPLPythonMath::ExpressionAdapterWrapper<ExpressionType, QuaternionAdapterType> QuaternionAdapterWrapper;
		typedef typename QuaternionAdapterWrapper::ExpressionPointerType ExpressionPointerType;
		typedef typename QuaternionAdapterWrapper::SharedPointer WrapperPointerType;

		ConstQuaternionVectorAdapterExport(const char* name) {
			using namespace boost;
			using namespace CDPLPythonMath;

			python::class_<QuaternionAdapterWrapper, WrapperPointerType, boost::noncopyable>(name, python::no_init)
				.def(python::init<const QuaternionAdapterWrapper&>((python::arg("self"), python::arg("a"))))
				.def(python::init<const ExpressionPointerType&>((python::arg("self"), python::arg("e"))))
				.def(CDPLPythonBase::ObjectIdentityCheckVisitor<QuaternionAdapterType>())
				.def(ConstVectorVisitor<QuaternionAdapterType>("a"))
				.def(WrappedDataVisitor<QuaternionAdapterWrapper>());

			python::def("vec", &vec, python::arg("e"));
		}

		static WrapperPointerType vec(const ExpressionPointerType& e) {
			return WrapperPointerType(new QuaternionAdapterWrapper(e));
		}
	};

	template <typename ExpressionType>
	struct QuaternionVectorAdapterExport
	{
	
		typedef CDPL::Math::QuaternionVectorAdapter<ExpressionType> QuaternionAdapterType;
		typedef CDPLPythonMath::ExpressionAdapterWrapper<ExpressionType, QuaternionAdapterType> QuaternionAdapterWrapper;
		typedef typename QuaternionAdapterWrapper::ExpressionPointerType ExpressionPointerType;
		typedef typename QuaternionAdapterWrapper::SharedPointer WrapperPointerType;

		QuaternionVectorAdapterExport(const char* name) {
			using namespace boost;
			using namespace CDPLPythonMath;

			python::class_<QuaternionAdapterWrapper, WrapperPointerType, boost::noncopyable>(name, python::no_init)
				.def(python::init<const QuaternionAdapterWrapper&>((python::arg("self"), python::arg("a"))))
				.def(python::init<const ExpressionPointerType&>((python::arg("self"), python::arg("e"))))
				.def(CDPLPythonBase::ObjectIdentityCheckVisitor<QuaternionAdapterType>())
				.def(AssignFunctionGeneratorVisitor<QuaternionAdapterType, ConstVectorExpression>("e"))
				.def(ConstVectorVisitor<QuaternionAdapterType>("a"))
				.def(VectorAssignAndSwapVisitor<QuaternionAdapterType>("a"))
				.def(VectorVisitor<QuaternionAdapterType>("a"))
				.def(VectorNDArrayAssignVisitor<QuaternionAdapterType>())
				.def(WrappedDataVisitor<QuaternionAdapterWrapper>());
		}

		static WrapperPointerType vec(const ExpressionPointerType& e) {
			return WrapperPointerType(new QuaternionAdapterWrapper(e));
		}
	};
}


void CDPLPythonMath::exportQuaternionAdapterTypes()
{
	ConstQuaternionVectorAdapterExport<ConstQuaternionExpression<float> >("ConstFQuaternionVectorAdapter");
	ConstQuaternionVectorAdapterExport<ConstQuaternionExpression<double> >("ConstDQuaternionVectorAdapter");
	ConstQuaternionVectorAdapterExport<ConstQuaternionExpression<long> >("ConstLQuaternionVectorAdapter");
	ConstQuaternionVectorAdapterExport<ConstQuaternionExpression<unsigned long> >("ConstULQuaternionVectorAdapter");

	QuaternionVectorAdapterExport<QuaternionExpression<float> >("FQuaternionVectorAdapter");
	QuaternionVectorAdapterExport<QuaternionExpression<double> >("DQuaternionVectorAdapter");
	QuaternionVectorAdapterExport<QuaternionExpression<long> >("LQuaternionVectorAdapter");
	QuaternionVectorAdapterExport<QuaternionExpression<unsigned long> >("ULQuaternionVectorAdapter");
}
