/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * MatrixProxyExport.cpp 
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

#include "CDPL/Math/MatrixProxy.hpp"
#include "CDPL/Math/IO.hpp"

#include "Base/ObjectIdentityCheckVisitor.hpp"

#include "ExpressionProxyWrapper.hpp"
#include "MatrixExpression.hpp"
#include "VectorExpression.hpp"
#include "MatrixVisitor.hpp"
#include "VectorVisitor.hpp"
#include "AssignFunctionGeneratorVisitor.hpp"
#include "WrappedDataVisitor.hpp"
#include "ClassExports.hpp"


namespace
{

	template <typename ExpressionType>
	struct ConstMatrixRowExport
	{
	
		typedef CDPL::Math::MatrixRow<const ExpressionType> MatrixRowType;
		typedef typename MatrixRowType::SizeType SizeType;
		typedef CDPLPythonMath::VectorExpressionProxyWrapper<ExpressionType, SizeType, MatrixRowType> MatrixRowWrapper;
		typedef typename MatrixRowWrapper::ExpressionPointerType ExpressionPointerType;
		typedef typename MatrixRowWrapper::SharedPointer WrapperPointerType;

		ConstMatrixRowExport(const char* name) {
			using namespace boost;
			using namespace CDPLPythonMath;

			python::class_<MatrixRowWrapper, WrapperPointerType, boost::noncopyable>(name, python::no_init)
				.def(python::init<const MatrixRowWrapper&>((python::arg("self"), python::arg("r"))))
				.def(python::init<const ExpressionPointerType&, SizeType>((python::arg("self"), python::arg("e"), python::arg("i"))))
				.def("getIndex", &MatrixRowType::getIndex, python::arg("self"))
				.def(CDPLPythonBase::ObjectIdentityCheckVisitor<MatrixRowType>())
				.def(ConstVectorVisitor<MatrixRowType>("r"))
				.def(WrappedDataVisitor<MatrixRowWrapper>())
				.add_property("index", &MatrixRowType::getIndex);

			python::def("row", &row, (python::arg("e"), python::arg("i")));
		}

		static WrapperPointerType row(const ExpressionPointerType& e, SizeType i) {
			return WrapperPointerType(new MatrixRowWrapper(e, i));
		}
	};

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

	template <typename ExpressionType>
	struct MatrixColumnExport
	{
	
		typedef CDPL::Math::MatrixColumn<ExpressionType> MatrixColumnType;
		typedef typename MatrixColumnType::SizeType SizeType;
		typedef CDPLPythonMath::VectorExpressionProxyWrapper<ExpressionType, SizeType, MatrixColumnType> MatrixColumnWrapper;
		typedef typename MatrixColumnWrapper::ExpressionPointerType ExpressionPointerType;
		typedef typename MatrixColumnWrapper::SharedPointer WrapperPointerType;

		MatrixColumnExport(const char* name) {
			using namespace boost;
			using namespace CDPLPythonMath;

			python::class_<MatrixColumnWrapper, WrapperPointerType, boost::noncopyable>(name, python::no_init)
				.def(python::init<const MatrixColumnWrapper&>((python::arg("self"), python::arg("mc"))))
				.def(python::init<const ExpressionPointerType&, SizeType>((python::arg("self"), python::arg("e"), python::arg("i"))))
				.def("getIndex", &MatrixColumnType::getIndex, python::arg("self"))
				.def(CDPLPythonBase::ObjectIdentityCheckVisitor<MatrixColumnType>())
				.def(AssignFunctionGeneratorVisitor<MatrixColumnType, ConstVectorExpression>("e"))
				.def(ConstVectorVisitor<MatrixColumnType>("c"))
				.def(VectorAssignAndSwapVisitor<MatrixColumnType>("c"))
				.def(VectorVisitor<MatrixColumnType>("c"))
				.def(WrappedDataVisitor<MatrixColumnWrapper>())
				.add_property("index", &MatrixColumnType::getIndex);

			python::def("column", &column, (python::arg("e"), python::arg("i")));
		}

		static WrapperPointerType column(const ExpressionPointerType& e, SizeType i) {
			return WrapperPointerType(new MatrixColumnWrapper(e, i));
		}
	};

	template <typename ExpressionType>
	struct ConstMatrixRangeExport
	{
	
		typedef CDPL::Math::Range<std::size_t> RangeType;
		typedef CDPL::Math::MatrixRange<const ExpressionType> MatrixRangeType;
		typedef CDPLPythonMath::MatrixExpressionProxyWrapper<ExpressionType, RangeType, MatrixRangeType> MatrixRangeWrapper;
		typedef typename MatrixRangeWrapper::ExpressionPointerType ExpressionPointerType;
		typedef typename MatrixRangeWrapper::SharedPointer WrapperPointerType;

		ConstMatrixRangeExport(const char* name) {
			using namespace boost;
			using namespace CDPLPythonMath;
		
			python::class_<MatrixRangeWrapper, WrapperPointerType, boost::noncopyable>(name, python::no_init)
				.def(python::init<const MatrixRangeWrapper&>((python::arg("self"), python::arg("r"))))
				.def(python::init<const ExpressionPointerType&, const RangeType&, const RangeType&>(
						 (python::arg("self"), python::arg("e"), python::arg("r1"), python::arg("r2"))))
				.def("getStart1", &MatrixRangeType::getStart1, python::arg("self"))
				.def("getStart2", &MatrixRangeType::getStart2, python::arg("self"))
				.def(CDPLPythonBase::ObjectIdentityCheckVisitor<MatrixRangeType>())
				.def(ConstMatrixVisitor<MatrixRangeType>("r"))
				.def(WrappedDataVisitor<MatrixRangeWrapper>())
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

	template <typename ExpressionType>
	struct MatrixSliceExport
	{
	
		typedef CDPL::Math::Slice<std::size_t, std::ptrdiff_t> SliceType;
		typedef CDPL::Math::MatrixSlice<ExpressionType> MatrixSliceType;
		typedef CDPLPythonMath::MatrixExpressionProxyWrapper<ExpressionType, SliceType, MatrixSliceType> MatrixSliceWrapper;
		typedef typename MatrixSliceWrapper::ExpressionPointerType ExpressionPointerType;
		typedef typename MatrixSliceWrapper::SharedPointer WrapperPointerType;

		MatrixSliceExport(const char* name) {
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
				.def(AssignFunctionGeneratorVisitor<MatrixSliceType, ConstMatrixExpression>("e"))
				.def(ConstMatrixVisitor<MatrixSliceType>("s"))
				.def(MatrixAssignAndSwapVisitor<MatrixSliceType>("s"))
				.def(MatrixVisitor<MatrixSliceType>("s"))
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


void CDPLPythonMath::exportMatrixProxies()
{
	ConstMatrixRowExport<ConstMatrixExpression<float> >("ConstFMatrixRow");
	ConstMatrixRowExport<ConstMatrixExpression<double> >("ConstDMatrixRow");
	ConstMatrixRowExport<ConstMatrixExpression<long> >("ConstLMatrixRow");
	ConstMatrixRowExport<ConstMatrixExpression<unsigned long> >("ConstULMatrixRow");

	MatrixRowExport<MatrixExpression<float> >("FMatrixRow");
	MatrixRowExport<MatrixExpression<double> >("DMatrixRow");
	MatrixRowExport<MatrixExpression<long> >("LMatrixRow");
	MatrixRowExport<MatrixExpression<unsigned long> >("ULMatrixRow");

	ConstMatrixColumnExport<ConstMatrixExpression<float> >("ConstFMatrixColumn");
	ConstMatrixColumnExport<ConstMatrixExpression<double> >("ConstDMatrixColumn");
	ConstMatrixColumnExport<ConstMatrixExpression<long> >("ConstLMatrixColumn");
	ConstMatrixColumnExport<ConstMatrixExpression<unsigned long> >("ConstULMatrixColumn");

	MatrixColumnExport<MatrixExpression<float> >("FMatrixColumn");
	MatrixColumnExport<MatrixExpression<double> >("DMatrixColumn");
	MatrixColumnExport<MatrixExpression<long> >("LMatrixColumn");
	MatrixColumnExport<MatrixExpression<unsigned long> >("ULMatrixColumn");

	ConstMatrixRangeExport<ConstMatrixExpression<float> >("ConstFMatrixRange");
	ConstMatrixRangeExport<ConstMatrixExpression<double> >("ConstDMatrixRange");
	ConstMatrixRangeExport<ConstMatrixExpression<long> >("ConstLMatrixRange");
	ConstMatrixRangeExport<ConstMatrixExpression<unsigned long> >("ConstULMatrixRange");

	MatrixRangeExport<MatrixExpression<float> >("FMatrixRange");
	MatrixRangeExport<MatrixExpression<double> >("DMatrixRange");
	MatrixRangeExport<MatrixExpression<long> >("LMatrixRange");
	MatrixRangeExport<MatrixExpression<unsigned long> >("ULMatrixRange");

	ConstMatrixSliceExport<ConstMatrixExpression<float> >("ConstFMatrixSlice");
	ConstMatrixSliceExport<ConstMatrixExpression<double> >("ConstDMatrixSlice");
	ConstMatrixSliceExport<ConstMatrixExpression<long> >("ConstLMatrixSlice");
	ConstMatrixSliceExport<ConstMatrixExpression<unsigned long> >("ConstULMatrixSlice");

	MatrixSliceExport<MatrixExpression<float> >("FMatrixSlice");
	MatrixSliceExport<MatrixExpression<double> >("DMatrixSlice");
	MatrixSliceExport<MatrixExpression<long> >("LMatrixSlice");
	MatrixSliceExport<MatrixExpression<unsigned long> >("ULMatrixSlice");
}
