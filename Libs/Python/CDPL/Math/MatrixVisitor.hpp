/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * MatrixVisitor.hpp 
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


#ifndef CDPL_PYTHON_MATH_MATRIXVISITOR_HPP
#define CDPL_PYTHON_MATH_MATRIXVISITOR_HPP

#include <string>
#include <sstream>
#include <utility>

#include <boost/python.hpp>
#include <boost/python/def_visitor.hpp>

#include "MatrixExpression.hpp"
#include "VectorExpression.hpp"
#include "MatrixExpressionAdapter.hpp"
#include "VectorExpressionAdapter.hpp"


#if (CDPL_MATH_CHECKS_DISABLE == 0)
#define CHECK_MATRIX_INDICES(m, i, j)
#else
#define CHECK_MATRIX_INDICES(m, i, j) \
	if (i >= m.getSize1() || j >= m.getSize2()) {						\
		throw CDPL::Base::IndexError("Matrix: element index out of bounds"); \
	}
#endif


namespace CDPLPythonMath
{

	template <typename MatrixType>
	struct ConstMatrixVisitor : public boost::python::def_visitor<ConstMatrixVisitor<MatrixType> >
	{

		friend class boost::python::def_visitor_access;

		typedef typename MatrixType::ValueType ValueType;
		typedef typename MatrixType::SizeType SizeType;
		typedef typename ConstMatrixExpression<ValueType>::SharedPointer ExpressionPointer;
		typedef typename ConstVectorExpression<ValueType>::SharedPointer VectorExpressionPointer;

		ConstMatrixVisitor(const char* arg_name = "m"): argName(arg_name) {}

		template <typename ClassType>
		void visit(ClassType& cl) const {
			using namespace boost;

			cl
				.def("getSize1", &MatrixType::getSize1, python::arg("self"))
				.def("getSize2", &MatrixType::getSize2, python::arg("self"))
				.def("isEmpty", &MatrixType::isEmpty, python::arg("self"))
				.def("getElement", &getElement, (python::arg("self"), python::arg("i"), python::arg("j")))
				.def("__call__", &getElement, (python::arg("self"), python::arg("i"), python::arg("j")))
				.def("__getitem__", &getElementByTuple, (python::arg("self"), python::arg("ij")))
				.def("__len__", &MatrixType::getSize1, python::arg("self"))
				.def("__eq__", &eqOperator, (python::arg("self"), python::arg(argName)))
				.def("__ne__", &neOperator, (python::arg("self"), python::arg(argName)))
				.def("__eq__", &eqOperatorExpr, (python::arg("self"), python::arg("e")))
				.def("__ne__", &neOperatorExpr, (python::arg("self"), python::arg("e")))
				.def("__str__", &toString, python::arg("self"))
				.def("__pos__", &posOperator, python::arg("self"), python::return_self<>())
				.def("__neg__", &negOperator, python::arg("self"))
				.def("__add__", &addOperator, (python::arg("self"), python::arg("e")))
				.def("__sub__", &subOperator, (python::arg("self"), python::arg("e")))
				.def("__mul__", &mulOperator, (python::arg("self"), python::arg("t")))
				.def("__mul__", &mulOperatorMtxExpr, (python::arg("self"), python::arg("e")))
				.def("__mul__", &mulOperatorVecExpr, (python::arg("self"), python::arg("e")))
				.def("__div__", &divOperator, (python::arg("self"), python::arg("t")))
				.def("__rmul__", &rmulOperator, (python::arg("self"), python::arg("t")))
				.add_property("size1", &MatrixType::getSize1)
				.add_property("size2", &MatrixType::getSize2);
		}

		static bool eqOperator(const MatrixType& mtx1, const MatrixType& mtx2) {
			return (mtx1 == mtx2);
		}

		static bool neOperator(const MatrixType& mtx1, const MatrixType& mtx2) {
			return (mtx1 != mtx2);
		}

		static bool eqOperatorExpr(const MatrixType& mtx1, const ExpressionPointer& mtx2_expr) {
			return (mtx1 == *mtx2_expr);
		}

		static bool neOperatorExpr(const MatrixType& mtx1, const ExpressionPointer& mtx2_expr) {
			return (mtx1 != *mtx2_expr);
		}

		static std::string toString(const MatrixType& mtx) {
			std::ostringstream oss;

			oss << mtx;

			return oss.str();
		}

		static ValueType getElement(const MatrixType& mtx, SizeType i, SizeType j) {
			CHECK_MATRIX_INDICES(mtx, i, j);

			return mtx(i, j);
		}

		static ValueType getElementByTuple(const MatrixType& mtx, const boost::python::tuple& indices) {
			using namespace boost;

			SizeType i = python::extract<SizeType>(indices[0]);
			SizeType j = python::extract<SizeType>(indices[1]);
			
			return getElement(mtx, i, j);
		}

		static void posOperator(const MatrixType& mtx) {}

		static ExpressionPointer negOperator(const boost::python::object& mtx) {
			return makeConstMatrixExpressionAdapter(-boost::python::extract<const MatrixType&>(mtx)(), mtx);
		}
	
		static ExpressionPointer addOperator(const boost::python::object& mtx1, const ExpressionPointer& mtx2_expr) {
			return makeConstMatrixExpressionAdapter(boost::python::extract<const MatrixType&>(mtx1)() + *mtx2_expr,
													std::make_pair(mtx1, mtx2_expr));
		}

		static ExpressionPointer subOperator(const boost::python::object& mtx1, const ExpressionPointer& mtx2_expr) {
			return makeConstMatrixExpressionAdapter(boost::python::extract<const MatrixType&>(mtx1)() - *mtx2_expr,
													std::make_pair(mtx1, mtx2_expr));
		}

		static ExpressionPointer mulOperator(const boost::python::object& mtx, const ValueType& value) {
			return makeConstMatrixExpressionAdapter(boost::python::extract<const MatrixType&>(mtx)() * value, mtx);
		}

		static VectorExpressionPointer mulOperatorVecExpr(const boost::python::object& mtx, const VectorExpressionPointer& vec_expr) {
			return makeConstVectorExpressionAdapter(boost::python::extract<const MatrixType&>(mtx)() * *vec_expr,
													std::make_pair(mtx, vec_expr));
		}

		static ExpressionPointer mulOperatorMtxExpr(const boost::python::object& mtx1, const ExpressionPointer& mtx2_expr) {
			return makeConstMatrixExpressionAdapter(boost::python::extract<const MatrixType&>(mtx1)() * *mtx2_expr, 
													std::make_pair(mtx1, mtx2_expr));
		}

		static ExpressionPointer divOperator(const boost::python::object& mtx, const ValueType& value) {
			return makeConstMatrixExpressionAdapter(boost::python::extract<const MatrixType&>(mtx)() / value, mtx);
		}
				
		static ExpressionPointer rmulOperator(const boost::python::object& mtx, const ValueType& value) {
			return makeConstMatrixExpressionAdapter(value * boost::python::extract<const MatrixType&>(mtx)(), mtx);
		}
		
		const char* argName;
	};

	template <typename MatrixType>
	struct MatrixAssignAndSwapVisitor : 
		public boost::python::def_visitor<MatrixAssignAndSwapVisitor<MatrixType> >
	{

		friend class boost::python::def_visitor_access;

		MatrixAssignAndSwapVisitor(const char* arg_name = "m"): argName(arg_name) {}

		template <typename ClassType>
		void visit(ClassType& cl) const {
			using namespace boost;

			cl
				.def("assign", &assign, (python::arg("self"), python::arg(argName)), python::return_self<>())
				.def("swap", &swap, (python::arg("self"), python::arg(argName)));
		}

		static void assign(MatrixType& mtx1, const MatrixType& mtx2) {
			mtx1 = mtx2;
		}

		static void swap(MatrixType& mtx1, MatrixType& mtx2) {
			mtx1.swap(mtx2);
		}

		const char* argName;
	};

	template <typename MatrixType>
	struct MatrixVisitor : public boost::python::def_visitor<MatrixVisitor<MatrixType> >
	{

		friend class boost::python::def_visitor_access;

		typedef typename MatrixType::ValueType ValueType;
		typedef typename MatrixType::SizeType SizeType;
		typedef typename ConstMatrixExpression<ValueType>::SharedPointer ExpressionPointer;

		MatrixVisitor(const char* arg_name = "m"): argName(arg_name) {}

		template <typename ClassType>
		void visit(ClassType& cl) const {
			using namespace boost;

			cl
				.def("setElement", &setElement, (python::arg("self"), python::arg("i"), python::arg("j"), python::arg("v")))
				.def("__setitem__", &setElementByTuple, (python::arg("self"), python::arg("ij"), python::arg("v")))
				.def("__iadd__", &iaddOperator, (python::arg("self"), python::arg(argName)),
					 python::return_self<>())
				.def("__iadd__", &iaddOperatorExpr, (python::arg("self"), python::arg("e")),
					 python::return_self<>())
				.def("__isub__", &isubOperator, (python::arg("self"), python::arg(argName)), 
					 python::return_self<>())
				.def("__isub__", &isubOperatorExpr, (python::arg("self"), python::arg("e")),
					 python::return_self<>())
				.def("__imul__", &imulOperator, (python::arg("self"), python::arg("t")),
					 python::return_self<>())
				.def("__idiv__", &idivOperator, (python::arg("self"), python::arg("t")),
					 python::return_self<>());
		}

		static void setElement(MatrixType& mtx, SizeType i, SizeType j, const ValueType& value) {
			CHECK_MATRIX_INDICES(mtx, i, j);

			mtx(i, j) = value;
		}
	
		static void setElementByTuple(MatrixType& mtx, const boost::python::tuple& indices, const ValueType& value) {
			using namespace boost;

			SizeType i = python::extract<SizeType>(indices[0]);
			SizeType j = python::extract<SizeType>(indices[1]);

			setElement(mtx, i, j, value);
		}

		static void iaddOperator(MatrixType& mtx1, const MatrixType& mtx2) {
			mtx1 += mtx2;
		}

		static void isubOperator(MatrixType& mtx1, const MatrixType& mtx2) {
			mtx1 -= mtx2;
		}

		static void iaddOperatorExpr(MatrixType& mtx1, const ExpressionPointer& mtx2_expr) {
			mtx1 += *mtx2_expr;
		}

		static void isubOperatorExpr(MatrixType& mtx1, const ExpressionPointer& mtx2_expr) {
			mtx1 -= *mtx2_expr;
		}

		static void imulOperator(MatrixType& mtx, const ValueType& value) {
			mtx *= value;
		}

		static void idivOperator(MatrixType& mtx, const ValueType& value) {
			mtx /= value;
		}

		const char* argName;
	};
}

#endif // CDPL_PYTHON_MATH_MATRIXVISITOR_HPP
