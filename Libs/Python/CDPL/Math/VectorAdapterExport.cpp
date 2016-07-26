/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * VectorAdapterExport.cpp 
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

#include "CDPL/Math/VectorAdapter.hpp"
#include "CDPL/Math/Quaternion.hpp"
#include "CDPL/Math/IO.hpp"

#include "Base/ObjectIdentityCheckVisitor.hpp"

#include "ExpressionAdapterWrapper.hpp"
#include "VectorExpression.hpp"
#include "QuaternionExpression.hpp"
#include "QuaternionVisitor.hpp"
#include "VectorVisitor.hpp"
#include "AssignFunctionGeneratorVisitor.hpp"
#include "WrappedDataVisitor.hpp"
#include "ClassExports.hpp"


namespace
{

	template <typename ExpressionType>
	struct ConstVectorQuaternionAdapterExport
	{
	
		typedef CDPL::Math::VectorQuaternionAdapter<const ExpressionType> VectorAdapterType;
		typedef CDPLPythonMath::ExpressionAdapterWrapper<ExpressionType, VectorAdapterType> VectorAdapterWrapper;
		typedef typename VectorAdapterWrapper::ExpressionPointerType ExpressionPointerType;
		typedef typename VectorAdapterWrapper::SharedPointer WrapperPointerType;

		ConstVectorQuaternionAdapterExport(const char* name) {
			using namespace boost;
			using namespace CDPLPythonMath;
		
			python::class_<VectorAdapterWrapper, WrapperPointerType, boost::noncopyable>(name, python::no_init)
				.def(python::init<const VectorAdapterWrapper&>((python::arg("self"), python::arg("a"))))
				.def(python::init<const ExpressionPointerType&>((python::arg("self"), python::arg("e"))))
				.def(CDPLPythonBase::ObjectIdentityCheckVisitor<VectorAdapterType>())
				.def(ConstQuaternionVisitor<VectorAdapterType>("a"))
				.def(WrappedDataVisitor<VectorAdapterWrapper>());

			python::def("quat", &quat, python::arg("e"));
		}

		static WrapperPointerType quat(const ExpressionPointerType& e) {
			return WrapperPointerType(new VectorAdapterWrapper(e));
		}
	};

	template <typename ExpressionType>
	struct VectorQuaternionAdapterExport
	{
		
		typedef CDPL::Math::VectorQuaternionAdapter<ExpressionType> VectorAdapterType;
		typedef CDPLPythonMath::ExpressionAdapterWrapper<ExpressionType, VectorAdapterType> VectorAdapterWrapper;
		typedef typename VectorAdapterWrapper::ExpressionPointerType ExpressionPointerType;
		typedef typename VectorAdapterWrapper::SharedPointer WrapperPointerType;

		VectorQuaternionAdapterExport(const char* name) {
			using namespace boost;
			using namespace CDPLPythonMath;

			python::class_<VectorAdapterWrapper, WrapperPointerType, boost::noncopyable>(name, python::no_init)
				.def(python::init<const VectorAdapterWrapper&>((python::arg("self"), python::arg("a"))))
				.def(python::init<const ExpressionPointerType&>((python::arg("self"), python::arg("e"))))
				.def(CDPLPythonBase::ObjectIdentityCheckVisitor<VectorAdapterType>())
				.def(AssignFunctionGeneratorVisitor<VectorAdapterType, ConstQuaternionExpression>("e"))
				.def(ConstQuaternionVisitor<VectorAdapterType>("a"))
				.def(QuaternionAssignAndSwapVisitor<VectorAdapterType>("a"))
				.def(QuaternionVisitor<VectorAdapterType>("a"))
				.def(WrappedDataVisitor<VectorAdapterWrapper>());

			python::def("quat", &quat, python::arg("e"));
		}

		static WrapperPointerType quat(const ExpressionPointerType& e) {
			return WrapperPointerType(new VectorAdapterWrapper(e));
		}
	};

	template <typename ExpressionType>
	struct ConstHomogenousCoordsAdapterExport
	{
	
		typedef CDPL::Math::HomogenousCoordsAdapter<const ExpressionType> HomogenousCoordsAdapterType;
		typedef CDPLPythonMath::ExpressionAdapterWrapper<ExpressionType, HomogenousCoordsAdapterType> HomogenousCoordsAdapterWrapper;
		typedef typename HomogenousCoordsAdapterWrapper::ExpressionPointerType ExpressionPointerType;
		typedef typename HomogenousCoordsAdapterWrapper::SharedPointer WrapperPointerType;

		ConstHomogenousCoordsAdapterExport(const char* name) {
			using namespace boost;
			using namespace CDPLPythonMath;
		
			python::class_<HomogenousCoordsAdapterWrapper, WrapperPointerType, boost::noncopyable>(name, python::no_init)
				.def(python::init<const HomogenousCoordsAdapterWrapper&>((python::arg("self"), python::arg("a"))))
				.def(python::init<const ExpressionPointerType&>((python::arg("self"), python::arg("e"))))
				.def(CDPLPythonBase::ObjectIdentityCheckVisitor<HomogenousCoordsAdapterType>())
				.def(ConstVectorVisitor<HomogenousCoordsAdapterType>("a"))
				.def(WrappedDataVisitor<HomogenousCoordsAdapterWrapper>());

			python::def("homog", &homog, python::arg("e"));
		}

		static WrapperPointerType homog(const ExpressionPointerType& e) {
			return WrapperPointerType(new HomogenousCoordsAdapterWrapper(e));
		}
	};

	template <typename ExpressionType>
	struct HomogenousCoordsAdapterExport
	{
	
		typedef CDPL::Math::HomogenousCoordsAdapter<ExpressionType> HomogenousCoordsAdapterType;
		typedef CDPLPythonMath::ExpressionAdapterWrapper<ExpressionType, HomogenousCoordsAdapterType> HomogenousCoordsAdapterWrapper;
		typedef typename HomogenousCoordsAdapterWrapper::ExpressionPointerType ExpressionPointerType;
		typedef typename HomogenousCoordsAdapterWrapper::SharedPointer WrapperPointerType;

		HomogenousCoordsAdapterExport(const char* name) {
			using namespace boost;
			using namespace CDPLPythonMath;

			python::class_<HomogenousCoordsAdapterWrapper, WrapperPointerType, boost::noncopyable>(name, python::no_init)
				.def(python::init<const HomogenousCoordsAdapterWrapper&>((python::arg("self"), python::arg("a"))))
				.def(python::init<const ExpressionPointerType&>((python::arg("self"), python::arg("e"))))
				.def(CDPLPythonBase::ObjectIdentityCheckVisitor<HomogenousCoordsAdapterType>())
				.def(AssignFunctionGeneratorVisitor<HomogenousCoordsAdapterType, ConstVectorExpression>("e"))
				.def(ConstVectorVisitor<HomogenousCoordsAdapterType>("r"))
				.def(VectorAssignAndSwapVisitor<HomogenousCoordsAdapterType>("r"))
				.def(VectorVisitor<HomogenousCoordsAdapterType>("a"))
				.def(WrappedDataVisitor<HomogenousCoordsAdapterWrapper>());

			python::def("homog", &homog, python::arg("e"));
		}

		static WrapperPointerType homog(const ExpressionPointerType& e) {
			return WrapperPointerType(new HomogenousCoordsAdapterWrapper(e));
		}
	};

}


void CDPLPythonMath::exportVectorAdapters()
{
	ConstVectorQuaternionAdapterExport<ConstVectorExpression<float> >("ConstFVectorQuaternionAdapter");
	ConstVectorQuaternionAdapterExport<ConstVectorExpression<double> >("ConstDVectorQuaternionAdapter");
	ConstVectorQuaternionAdapterExport<ConstVectorExpression<long> >("ConstLVectorQuaternionAdapter");
	ConstVectorQuaternionAdapterExport<ConstVectorExpression<unsigned long> >("ConstULVectorQuaternionAdapter");

	VectorQuaternionAdapterExport<VectorExpression<float> >("FVectorQuaternionAdapter");
	VectorQuaternionAdapterExport<VectorExpression<double> >("DVectorQuaternionAdapter");
	VectorQuaternionAdapterExport<VectorExpression<long> >("LVectorQuaternionAdapter");
	VectorQuaternionAdapterExport<VectorExpression<unsigned long> >("ULVectorQuaternionAdapter");

	ConstHomogenousCoordsAdapterExport<ConstVectorExpression<float> >("ConstFHomogenousCoordsAdapter");
	ConstHomogenousCoordsAdapterExport<ConstVectorExpression<double> >("ConstDHomogenousCoordsAdapter");
	ConstHomogenousCoordsAdapterExport<ConstVectorExpression<long> >("ConstLHomogenousCoordsAdapter");
	ConstHomogenousCoordsAdapterExport<ConstVectorExpression<unsigned long> >("ConstULHomogenousCoordsAdapter");

	HomogenousCoordsAdapterExport<VectorExpression<float> >("FHomogenousCoordsAdapter");
	HomogenousCoordsAdapterExport<VectorExpression<double> >("DHomogenousCoordsAdapter");
	HomogenousCoordsAdapterExport<VectorExpression<long> >("LHomogenousCoordsAdapter");
	HomogenousCoordsAdapterExport<VectorExpression<unsigned long> >("ULHomogenousCoordsAdapter");
}
