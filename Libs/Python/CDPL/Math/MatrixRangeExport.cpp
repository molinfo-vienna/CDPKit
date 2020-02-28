/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * MatrixRangeExport.cpp 
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
#include "MatrixExpression.hpp"
#include "MatrixVisitor.hpp"
#include "AssignFunctionGeneratorVisitor.hpp"
#include "WrappedDataVisitor.hpp"
#include "ClassExports.hpp"


namespace
{

	template <typename ExpressionType>
	struct MatrixRangeExport
	{
	
		typedef CDPL::Math::Range<std::size_t> RangeType;
		typedef CDPL::Math::MatrixRange<ExpressionType> MatrixRangeType;
		typedef CDPLPythonMath::MatrixExpressionProxyWrapper<ExpressionType, RangeType, MatrixRangeType> MatrixRangeWrapper;
		typedef typename MatrixRangeWrapper::ExpressionPointerType ExpressionPointerType;
		typedef typename MatrixRangeWrapper::SharedPointer WrapperPointerType;

		MatrixRangeExport(const char* name) {
			using namespace boost;
			using namespace CDPLPythonMath;
		
			python::class_<MatrixRangeWrapper, WrapperPointerType, boost::noncopyable>(name, python::no_init)
				.def(python::init<const MatrixRangeWrapper&>((python::arg("self"), python::arg("r"))))
				.def(python::init<const ExpressionPointerType&, const RangeType&, const RangeType&>(
						 (python::arg("self"), python::arg("e"), python::arg("r1"), python::arg("r2"))))
				.def("getStart1", &MatrixRangeType::getStart1, python::arg("self"))
				.def("getStart2", &MatrixRangeType::getStart2, python::arg("self"))
				.def(CDPLPythonBase::ObjectIdentityCheckVisitor<MatrixRangeType>())
				.def(AssignFunctionGeneratorVisitor<MatrixRangeType, ConstMatrixExpression>("e"))
				.def(ConstMatrixVisitor<MatrixRangeType>("r"))
				.def(MatrixAssignAndSwapVisitor<MatrixRangeType>("r"))
				.def(MatrixVisitor<MatrixRangeType>("r"))
				.def(WrappedDataVisitor<MatrixRangeWrapper>())
				.def(MatrixNDArrayAssignVisitor<MatrixRangeType>())
				.add_property("start1", &MatrixRangeType::getStart1)
				.add_property("start2", &MatrixRangeType::getStart2);

			python::def("range", &range1, (python::arg("e"), python::arg("r1"), python::arg("r2")));
			python::def("range", &range2, (python::arg("e"), python::arg("start1"), python::arg("stop1"),
										   python::arg("start2"), python::arg("stop2")));
		}

		static WrapperPointerType range1(const ExpressionPointerType& e, const RangeType& r1, const RangeType& r2) {
			return WrapperPointerType(new MatrixRangeWrapper(e, r1, r2));
		}

		static WrapperPointerType range2(const ExpressionPointerType& e, std::size_t start1, std::size_t stop1, 
										 std::size_t start2, std::size_t stop2) {
			return WrapperPointerType(new MatrixRangeWrapper(e, RangeType(start1, stop1), RangeType(start2, stop2)));
		}
	};
}


void CDPLPythonMath::exportMatrixRangeTypes()
{
	MatrixRangeExport<MatrixExpression<float> >("FMatrixRange");
	MatrixRangeExport<MatrixExpression<double> >("DMatrixRange");
	MatrixRangeExport<MatrixExpression<long> >("LMatrixRange");
	MatrixRangeExport<MatrixExpression<unsigned long> >("ULMatrixRange");
}
