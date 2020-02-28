/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * VectorSliceExport.cpp 
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

#include "CDPL/Math/VectorProxy.hpp"
#include "CDPL/Math/IO.hpp"

#include "Base/ObjectIdentityCheckVisitor.hpp"

#include "ExpressionProxyWrapper.hpp"
#include "VectorExpression.hpp"
#include "VectorVisitor.hpp"
#include "AssignFunctionGeneratorVisitor.hpp"
#include "WrappedDataVisitor.hpp"
#include "ClassExports.hpp"


namespace
{

	template <typename ExpressionType>
	struct VectorSliceExport
	{
			
		typedef CDPL::Math::Slice<std::size_t, std::ptrdiff_t> SliceType;
		typedef CDPL::Math::VectorSlice<ExpressionType> VectorSliceType;
		typedef CDPLPythonMath::VectorExpressionProxyWrapper<ExpressionType, SliceType, VectorSliceType> VectorSliceWrapper;
		typedef typename VectorSliceWrapper::ExpressionPointerType ExpressionPointerType;
		typedef typename VectorSliceWrapper::SharedPointer WrapperPointerType;

		VectorSliceExport(const char* name) {
			using namespace boost;
			using namespace CDPLPythonMath;

			python::class_<VectorSliceWrapper, WrapperPointerType, boost::noncopyable>(name, python::no_init)
				.def(python::init<const VectorSliceWrapper&>((python::arg("self"), python::arg("s"))))
				.def(python::init<const ExpressionPointerType&, const SliceType&>((python::arg("self"), python::arg("e"), python::arg("s"))))
				.def("getStart", &VectorSliceType::getStart, python::arg("self"))
				.def("getStride", &VectorSliceType::getStride, python::arg("self"))
				.def(CDPLPythonBase::ObjectIdentityCheckVisitor<VectorSliceType>())
				.def(AssignFunctionGeneratorVisitor<VectorSliceType, ConstVectorExpression>("e"))
				.def(ConstVectorVisitor<VectorSliceType>("s"))
				.def(VectorAssignAndSwapVisitor<VectorSliceType>("s"))
				.def(VectorVisitor<VectorSliceType>("s"))
				.def(VectorNDArrayAssignVisitor<VectorSliceType>())
				.def(WrappedDataVisitor<VectorSliceWrapper>())
				.add_property("start", &VectorSliceType::getStart)
				.add_property("stride", &VectorSliceType::getStride);

			python::def("slice", &slice1, (python::arg("e"), python::arg("s")));
			python::def("slice", &slice2, (python::arg("e"), python::arg("start"), python::arg("stride"), python::arg("size")));
		}

		static WrapperPointerType slice1(const ExpressionPointerType& e, const SliceType& s) {
			return WrapperPointerType(new VectorSliceWrapper(e, s));
		}

		static WrapperPointerType slice2(const ExpressionPointerType& e, std::size_t start, std::ptrdiff_t stride, std::size_t size) {
			return WrapperPointerType(new VectorSliceWrapper(e, SliceType(start, stride, size)));
		}
	};
}


void CDPLPythonMath::exportVectorSliceTypes()
{
	VectorSliceExport<VectorExpression<float> >("FVectorSlice");
	VectorSliceExport<VectorExpression<double> >("DVectorSlice");
	VectorSliceExport<VectorExpression<long> >("LVectorSlice");
	VectorSliceExport<VectorExpression<unsigned long> >("ULVectorSlice");
}
