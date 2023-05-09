/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * QuaternionVisitor.hpp 
 *
 * This file is part of the Chemical Data Processing Toolkit
 *
 * Copyright (C) 2003 Thomas Seidel <thomas.seidel@univie.ac.at>
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


#ifndef CDPL_PYTHON_MATH_QUATERNIONVISITOR_HPP
#define CDPL_PYTHON_MATH_QUATERNIONVISITOR_HPP

#include <string>
#include <sstream>
#include <utility>

#include <boost/python.hpp>
#include <boost/python/def_visitor.hpp>

#include "CDPL/Config.hpp"
#include "CDPL/Math/QuaternionAdapter.hpp"

#include "QuaternionExpression.hpp"
#include "QuaternionExpressionAdapter.hpp"

#ifdef HAVE_NUMPY
# include "NumPy.hpp"
#endif


namespace CDPLPythonMath
{

	template <typename QuaternionType>
	struct ConstQuaternionVisitor : public boost::python::def_visitor<ConstQuaternionVisitor<QuaternionType> >
	{

		friend class boost::python::def_visitor_access;

		typedef typename QuaternionType::ValueType ValueType;
		typedef typename ConstQuaternionExpression<ValueType>::SharedPointer ExpressionPointer;

		ConstQuaternionVisitor(const char* arg_name = "q"): argName(arg_name) {}

		template <typename ClassType>
		void visit(ClassType& cl) const {
			using namespace boost;

			cl
				.def("getC1", &getC1, python::arg("self"))
				.def("getC2", &getC2, python::arg("self"))
				.def("getC3", &getC3, python::arg("self"))
				.def("getC4", &getC4, python::arg("self"))
				.def("__eq__", &eqOperator, (python::arg("self"), python::arg(argName)))
				.def("__ne__", &neOperator, (python::arg("self"), python::arg(argName)))
				.def("__eq__", &eqOperatorExpr, (python::arg("self"), python::arg("q")))
				.def("__ne__", &neOperatorExpr, (python::arg("self"), python::arg("q")))
				.def("__str__", &toString, python::arg("self"))
				.def("__pos__", &posOperator, python::arg("self"), python::return_self<>())
				.def("__neg__", &negOperator, python::arg("self"))
				.def("__add__", &addOperator, (python::arg("self"), python::arg("t")))
				.def("__radd__", &addOperator, (python::arg("self"), python::arg("t")))
				.def("__add__", &addOperatorExpr, (python::arg("self"), python::arg("e")))
				.def("__sub__", &subOperator, (python::arg("self"), python::arg("t")))
				.def("__rsub__", &rsubOperator, (python::arg("self"), python::arg("t")))
				.def("__sub__", &subOperatorExpr, (python::arg("self"), python::arg("e")))
				.def("__mul__", &mulOperator, (python::arg("self"), python::arg("t")))
				.def("__rmul__", &rmulOperator, (python::arg("self"), python::arg("t")))
				.def("__mul__", &mulOperatorExpr, (python::arg("self"), python::arg("e")))
				.def("__div__", &divOperator, (python::arg("self"), python::arg("t")))
				.def("__truediv__", &divOperator, (python::arg("self"), python::arg("t")))
				.def("__rdiv__", &rdivOperator, (python::arg("self"), python::arg("t")))
				.def("__div__", &divOperatorExpr, (python::arg("self"), python::arg("e")))
#ifdef HAVE_NUMPY
				.def("toArray", &toArray, python::arg("self"))
#endif
				;
		}
#ifdef HAVE_NUMPY
		static boost::python::object toArray(const QuaternionType& quat) {
			using namespace boost;

			if (NumPy::available()) {
				npy_intp shape[] = { 4 };
				PyObject* array = PyArray_SimpleNew(1, shape, NumPy::DataTypeNum<typename QuaternionType::ValueType>::Value);

				if (array) {
					typename QuaternionType::ValueType* data = static_cast<typename QuaternionType::ValueType*>(PyArray_GETPTR1(reinterpret_cast<PyArrayObject*>(array), 0));

					data[0] = quat.getC1();
					data[1] = quat.getC2();
					data[2] = quat.getC3();
					data[3] = quat.getC4();

					return python::object(python::handle<>(array));
				}
			}

			return python::object();			
		}
#endif	
		static ValueType getC1(const QuaternionType& quat) {
			return quat.getC1();
		}

		static ValueType getC2(const QuaternionType& quat) {
			return quat.getC2();
		}

		static ValueType getC3(const QuaternionType& quat) {
			return quat.getC3();
		}

		static ValueType getC4(const QuaternionType& quat) {
			return quat.getC4();
		}

		static std::string toString(const QuaternionType& quat) {
			std::ostringstream oss;

			oss << quat;

			return oss.str();
		}

		static bool eqOperator(const QuaternionType& quat1, const QuaternionType& quat2) {
			return (quat1 == quat2);
		}

		static bool neOperator(const QuaternionType& quat1, const QuaternionType& quat2) {
			return (quat1 != quat2);
		}

		static bool eqOperatorExpr(const QuaternionType& quat1, const ExpressionPointer& quat2_expr) {
			return (quat1 == *quat2_expr);
		}

		static bool neOperatorExpr(const QuaternionType& quat1, const ExpressionPointer& quat2_expr) {
			return (quat1 != *quat2_expr);
		}

		static void posOperator(const QuaternionType& quat) {}

		static ExpressionPointer negOperator(const boost::python::object& quat) {
			return makeConstQuaternionExpressionAdapter(-boost::python::extract<const QuaternionType&>(quat)(), quat);
		}
	
		static ExpressionPointer addOperator(const boost::python::object& quat, const ValueType& value) {
			return makeConstQuaternionExpressionAdapter(boost::python::extract<const QuaternionType&>(quat)() + value, quat);
		}
	
		static ExpressionPointer raddOperator(const boost::python::object& quat, const ValueType& value) {
			return makeConstQuaternionExpressionAdapter(value + boost::python::extract<const QuaternionType&>(quat)(), quat);
		}

		static ExpressionPointer addOperatorExpr(const boost::python::object& quat1, const ExpressionPointer& quat2_expr) {
			return makeConstQuaternionExpressionAdapter(boost::python::extract<const QuaternionType&>(quat1)() + *quat2_expr,
														std::make_pair(quat1, quat2_expr));
		}

		static ExpressionPointer subOperator(const boost::python::object& quat, const ValueType& value) {
			return makeConstQuaternionExpressionAdapter(boost::python::extract<const QuaternionType&>(quat)() - value, quat);
		}
	
		static ExpressionPointer rsubOperator(const boost::python::object& quat, const ValueType& value) {
			return makeConstQuaternionExpressionAdapter(value - boost::python::extract<const QuaternionType&>(quat)(), quat);
		}
	
		static ExpressionPointer subOperatorExpr(const boost::python::object& quat1, const ExpressionPointer& quat2_expr) {
			return makeConstQuaternionExpressionAdapter(boost::python::extract<const QuaternionType&>(quat1)() - *quat2_expr,
														std::make_pair(quat1, quat2_expr));
		}

		static ExpressionPointer mulOperator(const boost::python::object& quat, const ValueType& value) {
			return makeConstQuaternionExpressionAdapter(boost::python::extract<const QuaternionType&>(quat)() * value, quat);
		}
			
		static ExpressionPointer rmulOperator(const boost::python::object& quat, const ValueType& value) {
			return makeConstQuaternionExpressionAdapter(value * boost::python::extract<const QuaternionType&>(quat)(), quat);
		}
		
		static ExpressionPointer mulOperatorExpr(const boost::python::object& quat1, const ExpressionPointer& quat2_expr) {
			return makeConstQuaternionExpressionAdapter(boost::python::extract<const QuaternionType&>(quat1)() * *quat2_expr,
														std::make_pair(quat1, quat2_expr));
		}

		static ExpressionPointer divOperator(const boost::python::object& quat, const ValueType& value) {
			return makeConstQuaternionExpressionAdapter(boost::python::extract<const QuaternionType&>(quat)() / value, quat);
		}

		static ExpressionPointer rdivOperator(const boost::python::object& quat, const ValueType& value) {
			return makeConstQuaternionExpressionAdapter(value / boost::python::extract<const QuaternionType&>(quat)(), quat);
		}
		
		static ExpressionPointer divOperatorExpr(const boost::python::object& quat1, const ExpressionPointer& quat2_expr) {
			return makeConstQuaternionExpressionAdapter(boost::python::extract<const QuaternionType&>(quat1)() / *quat2_expr,
														std::make_pair(quat1, quat2_expr));
		}

		const char* argName;
	};

	template <typename QuaternionType>
	struct QuaternionAssignAndSwapVisitor : 
		public boost::python::def_visitor<QuaternionAssignAndSwapVisitor<QuaternionType> >
	{

		friend class boost::python::def_visitor_access;

		QuaternionAssignAndSwapVisitor(const char* arg_name = "q"): argName(arg_name) {}

		template <typename ClassType>
		void visit(ClassType& cl) const {
			using namespace boost;

			cl
				.def("assign", &assign, (python::arg("self"), python::arg(argName)), python::return_self<>())
				.def("swap", &swap, (python::arg("self"), python::arg(argName)));
		}

		static void assign(QuaternionType& quat1, const QuaternionType& quat2) {
			quat1 = quat2;
		}

		static void swap(QuaternionType& quat1, QuaternionType& quat2) {
			quat1.swap(quat2);
		}

		const char* argName;
	};

	template <typename QuaternionType>
	struct QuaternionVisitor : public boost::python::def_visitor<QuaternionVisitor<QuaternionType> >
	{

		friend class boost::python::def_visitor_access;

		typedef typename QuaternionType::ValueType ValueType;
		typedef typename ConstQuaternionExpression<ValueType>::SharedPointer ExpressionPointer;

		QuaternionVisitor(const char* arg_name = "q"): argName(arg_name) {}

		template <typename ClassType>
		void visit(ClassType& cl) const {
			using namespace boost;

			cl
				.def("setC1", &setC1, (python::arg("self"), python::arg("v")))
				.def("setC2", &setC2, (python::arg("self"), python::arg("v")))
				.def("setC3", &setC3, (python::arg("self"), python::arg("v")))
				.def("setC4", &setC4, (python::arg("self"), python::arg("v")))
				.def("set", &QuaternionType::set, (python::arg("self"), python::arg("c1") = ValueType(),
												   python::arg("c2") = ValueType(), python::arg("c3") = ValueType(),
												   python::arg("c4") = ValueType()))
				.def("__iadd__", &iaddOperator, (python::arg("self"), python::arg("t")), 
					 python::return_self<>())
				.def("__isub__", &isubOperator, (python::arg("self"), python::arg("t")), 
					 python::return_self<>())
				.def("__imul__", &imulOperator, 
					 (python::arg("self"), python::arg("t")), python::return_self<>())
				.def("__idiv__", &idivOperator, 
					 (python::arg("self"), python::arg("t")), python::return_self<>())
				.def("__itruediv__", &idivOperator, 
					 (python::arg("self"), python::arg("t")), python::return_self<>())
				.def("__iadd__", &iaddOperatorQuat, (python::arg("self"), python::arg(argName)), 
					 python::return_self<>())
				.def("__isub__", &isubOperatorQuat, (python::arg("self"), python::arg(argName)), 
					 python::return_self<>())
				.def("__imul__", &imulOperatorQuat, 
					 (python::arg("self"), python::arg(argName)), python::return_self<>())
				.def("__idiv__", &idivOperatorQuat, 
					 (python::arg("self"), python::arg(argName)), python::return_self<>())
				.def("__itruediv__", &idivOperatorQuat, 
					 (python::arg("self"), python::arg(argName)), python::return_self<>())
				.def("__iadd__", &iaddOperatorQuatExpr, (python::arg("self"), python::arg("q")),
					 python::return_self<>())
				.def("__isub__", &isubOperatorQuatExpr, (python::arg("self"), python::arg("q")),
					 python::return_self<>())
				.def("__imul__", &imulOperatorQuatExpr, (python::arg("self"), python::arg("q")), 
					 python::return_self<>())
				.def("__idiv__", &idivOperatorQuatExpr, (python::arg("self"), python::arg("q")),
					 python::return_self<>())
				.def("__itruediv__", &idivOperatorQuatExpr, (python::arg("self"), python::arg("q")),
					 python::return_self<>());
		}

		static void setC1(QuaternionType& quat, const ValueType& value) {
			quat.getC1() = value;
		}

		static void setC2(QuaternionType& quat, const ValueType& value) {
			quat.getC2() = value;
		}

		static void setC3(QuaternionType& quat, const ValueType& value) {
			quat.getC3() = value;
		}

		static void setC4(QuaternionType& quat, const ValueType& value) {
			quat.getC4() = value;
		}

		static void iaddOperator(QuaternionType& quat1, const ValueType& value) {
			quat1 += value;
		}

		static void isubOperator(QuaternionType& quat1, const ValueType& value) {
			quat1 -= value;
		}

		static void imulOperator(QuaternionType& quat1, const ValueType& value) {
			quat1 *= value;
		}

		static void idivOperator(QuaternionType& quat1, const ValueType& value) {
			quat1 /= value;
		}

		static void iaddOperatorQuat(QuaternionType& quat1, const QuaternionType& quat2) {
			quat1 += quat2;
		}

		static void isubOperatorQuat(QuaternionType& quat1, const QuaternionType& quat2) {
			quat1 -= quat2;
		}

		static void imulOperatorQuat(QuaternionType& quat1, const QuaternionType& quat2) {
			quat1 *= quat2;
		}

		static void idivOperatorQuat(QuaternionType& quat1, const QuaternionType& quat2) {
			quat1 /= quat2;
		}

		static void iaddOperatorQuatExpr(QuaternionType& quat1, const ExpressionPointer& quat2_expr) {
			quat1 += *quat2_expr;
		}

		static void isubOperatorQuatExpr(QuaternionType& quat1, const ExpressionPointer& quat2_expr) {
			quat1 -= *quat2_expr;
		}

		static void imulOperatorQuatExpr(QuaternionType& quat1, const ExpressionPointer& quat2_expr) {
			quat1 *= *quat2_expr;
		}

		static void idivOperatorQuatExpr(QuaternionType& quat1, const ExpressionPointer& quat2_expr) {
			quat1 /= *quat2_expr;
		}

		const char* argName;
	};

#ifdef HAVE_NUMPY
	template <typename QuaternionType>
	struct QuaternionNDArrayAssignVisitor : public boost::python::def_visitor<QuaternionNDArrayAssignVisitor<QuaternionType> >
	{

		friend class boost::python::def_visitor_access;

		typedef typename QuaternionType::ValueType ValueType;
	
		template <typename ClassType>
		void visit(ClassType& cl) const {
			using namespace boost;

			cl.def("assign", &assign, (python::arg("self"), python::arg("a")));
		}

		static void assign(QuaternionType& quat, PyArrayObject* arr) {
			using namespace CDPL;
			using namespace boost;

			if (!NumPy::checkSize(arr, 4)) {
				PyErr_SetString(PyExc_ValueError, "Quaternion: NumPy.NDArray size error");

				python::throw_error_already_set();
			}

			if (!NumPy::checkDataType<ValueType>(arr)) {
				PyErr_SetString(PyExc_TypeError, "Quaternion: NumPy.NDArray of incompatible type");

				python::throw_error_already_set();
			}

			Math::QuaternionVectorAdapter<QuaternionType> adapter(quat);

			NumPy::copyArray1(adapter, arr);
		}
	};

	template <typename QuaternionType>
	struct QuaternionNDArrayInitVisitor : public boost::python::def_visitor<QuaternionNDArrayInitVisitor<QuaternionType> >
	{

		friend class boost::python::def_visitor_access;

		typedef typename QuaternionType::ValueType ValueType;
	
		template <typename ClassType>
		void visit(ClassType& cl) const {
			using namespace boost;

			cl.def("__init__", python::make_constructor(&construct, 
														python::default_call_policies(),
														(python::arg("a"))));
		}

		static QuaternionType* construct(PyArrayObject* arr) {
			using namespace CDPL;
			using namespace boost;

			std::auto_ptr<QuaternionType> quat_ptr(new QuaternionType());
		
			if (!NumPy::checkSize(arr, 4)) {
				PyErr_SetString(PyExc_ValueError, "Quaternion: NumPy.NDArray size error");

				python::throw_error_already_set();
			}

			if (!NumPy::checkDataType<ValueType>(arr)) {
				PyErr_SetString(PyExc_TypeError, "Quaternion: NumPy.NDArray of incompatible type");

				python::throw_error_already_set();
			}

			Math::QuaternionVectorAdapter<QuaternionType> adapter(*quat_ptr);

			NumPy::copyArray1(adapter, arr);

			return quat_ptr.release();
		}
	};

#else // HAVE_NUMPY
	template <typename QuaternionType>
	struct QuaternionNDArrayAssignVisitor : public boost::python::def_visitor<QuaternionNDArrayAssignVisitor<QuaternionType> >
	{

		friend class boost::python::def_visitor_access;

		typedef typename QuaternionType::ValueType ValueType;
	
		template <typename ClassType>
		void visit(ClassType& cl) const {}
	};

	template <typename QuaternionType>
	struct QuaternionNDArrayInitVisitor : public boost::python::def_visitor<QuaternionNDArrayInitVisitor<QuaternionType> >
	{

		friend class boost::python::def_visitor_access;

		typedef typename QuaternionType::ValueType ValueType;
	
		template <typename ClassType>
		void visit(ClassType& cl) const {}
	};
#endif // HAVE_NUMPY
}

#endif // CDPL_PYTHON_MATH_QUATERNIONVISITOR_HPP
