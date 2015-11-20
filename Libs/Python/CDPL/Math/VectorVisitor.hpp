/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * VectorVisitor.hpp 
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


#ifndef CDPL_PYTHON_MATH_VECTORVISITOR_HPP
#define CDPL_PYTHON_MATH_VECTORVISITOR_HPP

#include <string>
#include <sstream>
#include <utility>

#include <boost/python.hpp>
#include <boost/python/def_visitor.hpp>

#include "VectorExpression.hpp"
#include "MatrixExpression.hpp"
#include "VectorExpressionAdapter.hpp"


namespace CDPLPythonMath
{

	template <typename VectorType>
	struct ConstVectorVisitor : 
		public boost::python::def_visitor<ConstVectorVisitor<VectorType> >
	{

		friend class boost::python::def_visitor_access;

		typedef typename VectorType::ValueType ValueType;
		typedef typename VectorType::SizeType SizeType;
		typedef typename ConstVectorExpression<ValueType>::SharedPointer ExpressionPointer;
		typedef typename ConstMatrixExpression<ValueType>::SharedPointer MatrixExpressionPointer;

		ConstVectorVisitor(const char* arg_name = "v"): argName(arg_name) {}

		template <typename ClassType>
		void visit(ClassType& cl) const {
			using namespace boost;

			cl
				.def("isEmpty", &VectorType::isEmpty, python::arg("self"))
				.def("getSize", &VectorType::getSize, python::arg("self"))
				.def("getElement", &getElement, (python::arg("self"), python::arg("i")))
				.def("__eq__", &eqOperator, (python::arg("self"), python::arg(argName)))
				.def("__ne__", &neOperator, (python::arg("self"), python::arg(argName)))
				.def("__eq__", &eqOperatorExpr, (python::arg("self"), python::arg("e")))
				.def("__ne__", &neOperatorExpr, (python::arg("self"), python::arg("e")))
				.def("__call__", &getElement, (python::arg("self"), python::arg("i")))
				.def("__getitem__", &getElement, (python::arg("self"), python::arg("i")))
				.def("__len__", &VectorType::getSize, python::arg("self"))
				.def("__str__", &toString, python::arg("self"))
				.def("__pos__", &posOperator, python::arg("self"), python::return_self<>())
				.def("__neg__", &negOperator, python::arg("self"))
				.def("__add__", &addOperator, (python::arg("self"), python::arg("e")))
				.def("__sub__", &subOperator, (python::arg("self"), python::arg("e")))
				.def("__mul__", &mulOperator, (python::arg("self"), python::arg("t")))
				.def("__mul__", &mulOperatorMtxExpr, (python::arg("self"), python::arg("e")))
				.def("__div__", &divOperator, (python::arg("self"), python::arg("t")))
				.def("__rmul__", &rmulOperator, (python::arg("self"), python::arg("t")))
				.add_property("size", &VectorType::getSize);
		}
	
		static std::string toString(const VectorType& vec) {
			std::ostringstream oss;

			oss << vec;

			return oss.str();
		}

		static bool eqOperator(const VectorType& vec1, const VectorType& vec2) {
			return (vec1 == vec2);
		}

		static bool neOperator(const VectorType& vec1, const VectorType& vec2) {
			return (vec1 != vec2);
		}

		static bool eqOperatorExpr(const VectorType& vec1, const ExpressionPointer& vec2_expr) {
			return (vec1 == *vec2_expr);
		}

		static bool neOperatorExpr(const VectorType& vec1, const ExpressionPointer& vec2_expr) {
			return (vec1 != *vec2_expr);
		}

		static ValueType getElement(const VectorType& vec, SizeType i) {
			return vec(i);
		}

		static void posOperator(const VectorType& vec) {}

		static ExpressionPointer negOperator(const boost::python::object& vec) {
			return makeConstVectorExpressionAdapter(-boost::python::extract<const VectorType&>(vec)(), vec);
		}
	
		static ExpressionPointer addOperator(const boost::python::object& vec1, const ExpressionPointer& vec2_expr) {
			return makeConstVectorExpressionAdapter(boost::python::extract<const VectorType&>(vec1)() + *vec2_expr,
													std::make_pair(vec1, vec2_expr));
		}

		static ExpressionPointer subOperator(const boost::python::object& vec1, const ExpressionPointer& vec2_expr) {
			return makeConstVectorExpressionAdapter(boost::python::extract<const VectorType&>(vec1)() - *vec2_expr,
													std::make_pair(vec1, vec2_expr));
		}

		static ExpressionPointer mulOperator(const boost::python::object& vec, const ValueType& value) {
			return makeConstVectorExpressionAdapter(boost::python::extract<const VectorType&>(vec)() * value, vec);
		}

		static ExpressionPointer mulOperatorMtxExpr(const boost::python::object& vec, const MatrixExpressionPointer& mtx_expr) {
			return makeConstVectorExpressionAdapter(boost::python::extract<const VectorType&>(vec)() * *mtx_expr, 
													std::make_pair(vec, mtx_expr));
		}

		static ExpressionPointer divOperator(const boost::python::object& vec, const ValueType& value) {
			return makeConstVectorExpressionAdapter(boost::python::extract<const VectorType&>(vec)() / value, vec);
		}
				
		static ExpressionPointer rmulOperator(const boost::python::object& vec, const ValueType& value) {
			return makeConstVectorExpressionAdapter(value * boost::python::extract<const VectorType&>(vec)(), vec);
		}

		const char* argName;
	};

	template <typename VectorType>
	struct VectorAssignAndSwapVisitor : 
		public boost::python::def_visitor<VectorAssignAndSwapVisitor<VectorType> >
	{

		friend class boost::python::def_visitor_access;

		VectorAssignAndSwapVisitor(const char* arg_name = "v"): argName(arg_name) {}

		template <typename ClassType>
		void visit(ClassType& cl) const {
			using namespace boost;

			cl
				.def("assign", &assign, (python::arg("self"), python::arg(argName)), python::return_self<>())
				.def("swap", &swap, (python::arg("self"), python::arg(argName)));
		}

		static void assign(VectorType& vec1, const VectorType& vec2) {
			vec1 = vec2;
		}

		static void swap(VectorType& vec1, VectorType& vec2) {
			vec1.swap(vec2);
		}

		const char* argName;
	};

	template <typename VectorType>
	struct VectorVisitor : public boost::python::def_visitor<VectorVisitor<VectorType> >
	{

		friend class boost::python::def_visitor_access;

		typedef typename VectorType::ValueType ValueType;
		typedef typename VectorType::SizeType SizeType;
		typedef typename ConstVectorExpression<ValueType>::SharedPointer ExpressionPointer;

		VectorVisitor(const char* arg_name = "v"): argName(arg_name) {}

		template <typename ClassType>
		void visit(ClassType& cl) const {
			using namespace boost;

			cl
				.def("setElement", &setElement, (python::arg("self"), python::arg("i"), python::arg("v")))
				.def("__setitem__", &setElement, (python::arg("self"), python::arg("i"), python::arg("v")))
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

		static void setElement(VectorType& vec, SizeType i, const ValueType& value) {
			vec(i) = value;
		}

		static void iaddOperator(VectorType& vec1, const VectorType& vec2) {
			vec1 += vec2;
		}

		static void isubOperator(VectorType& vec1, const VectorType& vec2) {
			vec1 -= vec2;
		}

		static void iaddOperatorExpr(VectorType& vec1, const ExpressionPointer& vec2_expr) {
			vec1 += *vec2_expr;
		}

		static void isubOperatorExpr(VectorType& vec1, const ExpressionPointer& vec2_expr) {
			vec1 -= *vec2_expr;
		}

		static void imulOperator(VectorType& vec, const ValueType& value) {
			vec *= value;
		}

		static void idivOperator(VectorType& vec, const ValueType& value) {
			vec /= value;
		}

		const char* argName;
	};
}

#endif // CDPL_PYTHON_MATH_VECTORVISITOR_HPP
