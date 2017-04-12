/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * ConstMatrixSliceExport.cpp 
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
#include "MatrixExpression.hpp"
#include "MatrixVisitor.hpp"
#include "WrappedDataVisitor.hpp"
#include "ClassExports.hpp"


namespace
{

	template <typename ExpressionType>
	struct ConstMatrixSliceExport
	{
	
		typedef CDPL::Math::Slice<std::size_t, std::ptrdiff_t> SliceType;
		typedef CDPL::Math::MatrixSlice<const ExpressionType> MatrixSliceType;
		typedef CDPLPythonMath::MatrixExpressionProxyWrapper<ExpressionType, SliceType, MatrixSliceType> MatrixSliceWrapper;
		typedef typename MatrixSliceWrapper::ExpressionPointerType ExpressionPointerType;
		typedef typename MatrixSliceWrapper::SharedPointer WrapperPointerType;

		ConstMatrixSliceExport(const char* name) {
			using namespace boost;
			using namespace CDPLPythonMath;

			python::class_<MatrixSliceWrapper, WrapperPointerType, boost::noncopyable>(name, python::no_init)
				.def(python::init<const MatrixSliceWrapper&>((python::arg("self"), python::arg("s"))))
				.def(python::init<const ExpressionPointerType&, const SliceType&, const SliceType&>(
						 (python::arg("self"), python::arg("e"), python::arg("s1"), python::arg("s2"))))
				.def("getStart1", &MatrixSliceType::getStart1, python::arg("self"))
				.def("getStart2", &MatrixSliceType::getStart2, python::arg("self"))
				.def("getStride1", &MatrixSliceType::getStride1, python::arg("self"))
				.def("getStride2", &MatrixSliceType::getStride2, python::arg("self"))
				.def(CDPLPythonBase::ObjectIdentityCheckVisitor<MatrixSliceType>())
				.def(ConstMatrixVisitor<MatrixSliceType>("s"))
				.def(WrappedDataVisitor<MatrixSliceWrapper>())
				.add_property("start1", &MatrixSliceType::getStart1)
				.add_property("start2", &MatrixSliceType::getStart2)
				.add_property("stride1", &MatrixSliceType::getStride1)
				.add_property("stride2", &MatrixSliceType::getStride2);

			python::def("slice", &slice1, (python::arg("e"), python::arg("s1"), python::arg("s2")));
			python::def("slice", &slice2, (python::arg("e"), python::arg("start1"), python::arg("stride1"), 
										   python::arg("size1"), python::arg("start2"), python::arg("stride2"), 
										   python::arg("size2")));
		}

		static WrapperPointerType slice1(const ExpressionPointerType& e, const SliceType& s1, const SliceType& s2) {
			return WrapperPointerType(new MatrixSliceWrapper(e, s1, s2));
		}

		static WrapperPointerType slice2(const ExpressionPointerType& e, std::size_t start1, 
										 std::ptrdiff_t stride1, std::size_t size1, std::size_t start2, 
										 std::ptrdiff_t stride2, std::size_t size2) {
			return WrapperPointerType(new MatrixSliceWrapper(e, SliceType(start1, stride1, size1),
															 SliceType(start2, stride2, size2)));
		}
	};
}


void CDPLPythonMath::exportConstMatrixSliceTypes()
{
	ConstMatrixSliceExport<ConstMatrixExpression<float> >("ConstFMatrixSlice");
	ConstMatrixSliceExport<ConstMatrixExpression<double> >("ConstDMatrixSlice");
	ConstMatrixSliceExport<ConstMatrixExpression<long> >("ConstLMatrixSlice");
	ConstMatrixSliceExport<ConstMatrixExpression<unsigned long> >("ConstULMatrixSlice");
}
