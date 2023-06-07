/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * GridVisitor.hpp 
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


#ifndef CDPL_PYTHON_MATH_GRIDVISITOR_HPP
#define CDPL_PYTHON_MATH_GRIDVISITOR_HPP

#include <string>
#include <sstream>
#include <utility>

#include <boost/python.hpp>
#include <boost/python/def_visitor.hpp>

#include "CDPL/Config.hpp"

#include "GridExpression.hpp"
#include "GridExpressionAdapter.hpp"

#ifdef HAVE_NUMPY
# include "NumPy.hpp"
#endif

 
#ifndef CDPL_MATH_CHECKS_DISABLE
# define CHECK_GRID_INDICES(g, i, j, k)
#else
# define CHECK_GRID_INDICES(g, i, j, k)									\
	if (i >= g.getSize1() || j >= g.getSize2() || k >= g.getSize3()) {	\
		throw CDPL::Base::IndexError("Grid: element index out of bounds"); \
	}
#endif


namespace CDPLPythonMath
{

	template <typename GridType>
	struct ConstGridContainerVisitor : public boost::python::def_visitor<ConstGridContainerVisitor<GridType> >
	{

		friend class boost::python::def_visitor_access;

		typedef typename GridType::ValueType ValueType;
		typedef typename GridType::SizeType SizeType;

		template <typename ClassType>
		void visit(ClassType& cl) const {
			using namespace boost;

			cl
				.def("getSize", &GridType::getSize, python::arg("self"))
				.def("getElement", &getSeqElement, (python::arg("self"), python::arg("i")))
				.def("__getitem__", &getSeqElement, (python::arg("self"), python::arg("i")))
				.def("__call__", &getSeqElement, (python::arg("self"), python::arg("i")));
		}

		static ValueType getSeqElement(const GridType& grd, SizeType i) {
			return grd(i);
		}
	};

	template <typename GridType>
	struct ConstGridVisitor : public boost::python::def_visitor<ConstGridVisitor<GridType> >
	{

		friend class boost::python::def_visitor_access;

		typedef typename GridType::ValueType ValueType;
		typedef typename GridType::SizeType SizeType;
		typedef typename ConstGridExpression<ValueType>::SharedPointer ExpressionPointer;

		ConstGridVisitor(const char* arg_name = "g"): argName(arg_name) {}

		template <typename ClassType>
		void visit(ClassType& cl) const {
			using namespace boost;

			cl
				.def("getSize1", &GridType::getSize1, python::arg("self"))
				.def("getSize2", &GridType::getSize2, python::arg("self"))
				.def("getSize3", &GridType::getSize3, python::arg("self"))
				.def("isEmpty", &GridType::isEmpty, python::arg("self"))
				.def("getElement", &getElement, (python::arg("self"), python::arg("i"), python::arg("j"), python::arg("k")))
				.def("__call__", &getElement, (python::arg("self"), python::arg("i"), python::arg("j"), python::arg("k")))
				.def("__getitem__", &getElementByTuple, (python::arg("self"), python::arg("ijk")))
				.def("__len__", &GridType::getSize1, python::arg("self"))
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
				.def("__div__", &divOperator, (python::arg("self"), python::arg("t")))
				.def("__truediv__", &divOperator, (python::arg("self"), python::arg("t")))
				.def("__rmul__", &rmulOperator, (python::arg("self"), python::arg("t")))
#ifdef HAVE_NUMPY
				.def("toArray", &toArray, python::arg("self"))
#endif
				.add_property("size1", &GridType::getSize1)
				.add_property("size2", &GridType::getSize2)
				.add_property("size3", &GridType::getSize3);
		}
#ifdef HAVE_NUMPY
		static boost::python::object toArray(const GridType& grd) {
			using namespace boost;

			if (NumPy::available()) {
				npy_intp shape[] = { npy_intp(grd.getSize1()), npy_intp(grd.getSize2()), npy_intp(grd.getSize3()) };
				PyObject* py_obj = PyArray_SimpleNew(3, shape, NumPy::DataTypeNum<typename GridType::ValueType>::Value);
				PyArrayObject* array = reinterpret_cast<PyArrayObject*>(py_obj);

				if (array) {
					for (std::size_t i = 0, size1 = grd.getSize1(), size2 = grd.getSize2(), size3 = grd.getSize3(); i < size1; i++)
						for (std::size_t j = 0; j < size2; j++)
							for (std::size_t k = 0; k < size3; k++)
								*static_cast<typename GridType::ValueType*>(PyArray_GETPTR3(array, i, j, k)) = grd(i, j, k);

					return python::object(python::handle<>(py_obj));
				}
			}

			return python::object();			
		}
#endif
		static bool eqOperator(const GridType& grd1, const GridType& grd2) {
			return (grd1 == grd2);
		}

		static bool neOperator(const GridType& grd1, const GridType& grd2) {
			return (grd1 != grd2);
		}

		static bool eqOperatorExpr(const GridType& grd1, const ExpressionPointer& grd2_expr) {
			return (grd1 == *grd2_expr);
		}

		static bool neOperatorExpr(const GridType& grd1, const ExpressionPointer& grd2_expr) {
			return (grd1 != *grd2_expr);
		}

		static std::string toString(const GridType& grd) {
			std::ostringstream oss;

			oss << grd;

			return oss.str();
		}

		static ValueType getElement(const GridType& grd, SizeType i, SizeType j, SizeType k) {
			CHECK_GRID_INDICES(grd, i, j, k);

			return grd(i, j, k);
		}

		static ValueType getElementByTuple(const GridType& grd, const boost::python::tuple& indices) {
			using namespace boost;

			SizeType i = python::extract<SizeType>(indices[0]);
			SizeType j = python::extract<SizeType>(indices[1]);
			SizeType k = python::extract<SizeType>(indices[2]);
			
			return getElement(grd, i, j, k);
		}

		static void posOperator(const GridType& grd) {}

		static ExpressionPointer negOperator(const boost::python::object& grd) {
			return makeConstGridExpressionAdapter(-boost::python::extract<const GridType&>(grd)(), grd);
		}
	
		static ExpressionPointer addOperator(const boost::python::object& grd1, const ExpressionPointer& grd2_expr) {
			return makeConstGridExpressionAdapter(boost::python::extract<const GridType&>(grd1)() + *grd2_expr,
												  std::make_pair(grd1, grd2_expr));
		}

		static ExpressionPointer subOperator(const boost::python::object& grd1, const ExpressionPointer& grd2_expr) {
			return makeConstGridExpressionAdapter(boost::python::extract<const GridType&>(grd1)() - *grd2_expr,
												  std::make_pair(grd1, grd2_expr));
		}

		static ExpressionPointer mulOperator(const boost::python::object& grd, const ValueType& value) {
			return makeConstGridExpressionAdapter(boost::python::extract<const GridType&>(grd)() * value, grd);
		}

		static ExpressionPointer divOperator(const boost::python::object& grd, const ValueType& value) {
			return makeConstGridExpressionAdapter(boost::python::extract<const GridType&>(grd)() / value, grd);
		}
				
		static ExpressionPointer rmulOperator(const boost::python::object& grd, const ValueType& value) {
			return makeConstGridExpressionAdapter(value * boost::python::extract<const GridType&>(grd)(), grd);
		}
		
		const char* argName;
	};

	template <typename GridType>
	struct GridAssignAndSwapVisitor : 
		public boost::python::def_visitor<GridAssignAndSwapVisitor<GridType> >
	{

		friend class boost::python::def_visitor_access;

		GridAssignAndSwapVisitor(const char* arg_name = "g"): argName(arg_name) {}

		template <typename ClassType>
		void visit(ClassType& cl) const {
			using namespace boost;

			cl
				.def("assign", &assign, (python::arg("self"), python::arg(argName)), python::return_self<>())
				.def("swap", &swap, (python::arg("self"), python::arg(argName)));
		}

		static void assign(GridType& grd1, const GridType& grd2) {
			grd1 = grd2;
		}

		static void swap(GridType& grd1, GridType& grd2) {
			grd1.swap(grd2);
		}

		const char* argName;
	};

	template <typename GridType>
	struct GridContainerVisitor : public boost::python::def_visitor<GridContainerVisitor<GridType> >
	{

		friend class boost::python::def_visitor_access;

		typedef typename GridType::ValueType ValueType;
		typedef typename GridType::SizeType SizeType;

		template <typename ClassType>
		void visit(ClassType& cl) const {
			using namespace boost;

			cl
				.def("__setitem__", &setSeqElement, (python::arg("self"), python::arg("i"), python::arg("v")))
				.def("setElement", &setSeqElement, (python::arg("self"), python::arg("i"), python::arg("v")));
		}
	
		static void setSeqElement(GridType& grd, SizeType i, const ValueType& value) {
			grd(i) = value;
		}
	};

	template <typename GridType>
	struct GridVisitor : public boost::python::def_visitor<GridVisitor<GridType> >
	{

		friend class boost::python::def_visitor_access;

		typedef typename GridType::ValueType ValueType;
		typedef typename GridType::SizeType SizeType;
		typedef typename ConstGridExpression<ValueType>::SharedPointer ExpressionPointer;

		GridVisitor(const char* arg_name = "g"): argName(arg_name) {}

		template <typename ClassType>
		void visit(ClassType& cl) const {
			using namespace boost;

			cl
				.def("setElement", &setElement, (python::arg("self"), python::arg("i"), python::arg("j"), python::arg("k"), python::arg("v")))
				.def("__setitem__", &setElementByTuple, (python::arg("self"), python::arg("ijk"), python::arg("v")))
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
					 python::return_self<>())
				.def("__itruediv__", &idivOperator, (python::arg("self"), python::arg("t")),
					 python::return_self<>());
		}
	
		static void setElement(GridType& grd, SizeType i, SizeType j, SizeType k, const ValueType& value) {
			CHECK_GRID_INDICES(grd, i, j, k);

			grd(i, j, k) = value;
		}
	
		static void setElementByTuple(GridType& grd, const boost::python::tuple& indices, const ValueType& value) {
			using namespace boost;

			SizeType i = python::extract<SizeType>(indices[0]);
			SizeType j = python::extract<SizeType>(indices[1]);
			SizeType k = python::extract<SizeType>(indices[2]);

			setElement(grd, i, j, k, value);
		}

		static void iaddOperator(GridType& grd1, const GridType& grd2) {
			grd1 += grd2;
		}

		static void isubOperator(GridType& grd1, const GridType& grd2) {
			grd1 -= grd2;
		}

		static void iaddOperatorExpr(GridType& grd1, const ExpressionPointer& grd2_expr) {
			grd1 += *grd2_expr;
		}

		static void isubOperatorExpr(GridType& grd1, const ExpressionPointer& grd2_expr) {
			grd1 -= *grd2_expr;
		}

		static void imulOperator(GridType& grd, const ValueType& value) {
			grd *= value;
		}

		static void idivOperator(GridType& grd, const ValueType& value) {
			grd /= value;
		}

		const char* argName;
	};

#ifdef HAVE_NUMPY
	template <typename GridType, bool RESIZE = false>
	struct GridNDArrayAssignVisitor : public boost::python::def_visitor<GridNDArrayAssignVisitor<GridType, RESIZE> >
	{

		friend class boost::python::def_visitor_access;

		typedef typename GridType::ValueType ValueType;
	
		template <typename ClassType>
		void visit(ClassType& cl) const {
			using namespace boost;

			cl.def("assign", &assign, (python::arg("self"), python::arg("a")));
		}

		static void assign(GridType& grd, PyArrayObject* arr) {
			using namespace CDPL;
			using namespace boost;

			if (!NumPy::checkSize(arr, grd.getSize1(), grd.getSize2(), grd.getSize3())) {
				PyErr_SetString(PyExc_ValueError, "Grid: NumPy.NDArray dimension error");

				python::throw_error_already_set();
			}

			if (!NumPy::checkDataType<ValueType>(arr)) {
				PyErr_SetString(PyExc_TypeError, "Grid: NumPy.NDArray of incompatible type");

				python::throw_error_already_set();
			}

			NumPy::copyArray3(grd, arr);
		}
	};

	template <typename GridType>
	struct GridNDArrayAssignVisitor<GridType, true> : public boost::python::def_visitor<GridNDArrayAssignVisitor<GridType, true> >
	{

		friend class boost::python::def_visitor_access;

		typedef typename GridType::ValueType ValueType;
	
		template <typename ClassType>
		void visit(ClassType& cl) const {
			using namespace boost;

			cl.def("assign", &assign, (python::arg("self"), python::arg("a")));
		}

		static void assign(GridType& grd, PyArrayObject* arr) {
			using namespace CDPL;
			using namespace boost;

			if (!NumPy::checkDim(arr, 3)) {
				PyErr_SetString(PyExc_ValueError, "Grid: NumPy.NDArray dimension error");

				python::throw_error_already_set();
			}

			if (!NumPy::checkDataType<ValueType>(arr)) {
				PyErr_SetString(PyExc_TypeError, "Grid: NumPy.NDArray of incompatible type");

				python::throw_error_already_set();
			}

			NumPy::resizeTarget3(grd, arr);
			NumPy::copyArray3(grd, arr);
		}
	};

	template <typename GridType>
	struct GridNDArrayInitVisitor : public boost::python::def_visitor<GridNDArrayInitVisitor<GridType> >
	{

		friend class boost::python::def_visitor_access;

		typedef typename GridType::ValueType ValueType;
	
		template <typename ClassType>
		void visit(ClassType& cl) const {
			using namespace boost;

			cl.def("__init__", python::make_constructor(&construct, 
														python::default_call_policies(),
														(python::arg("a"))));
		}

		static GridType* construct(PyArrayObject* arr) {
			using namespace CDPL;
			using namespace boost;

			if (!NumPy::checkDim(arr, 3)) {
				PyErr_SetString(PyExc_ValueError, "Grid: NumPy.NDArray dimension error");

				python::throw_error_already_set();
			}

			if (!NumPy::checkDataType<ValueType>(arr)) {
				PyErr_SetString(PyExc_TypeError, "Grid: NumPy.NDArray of incompatible type");

				python::throw_error_already_set();
			}

			std::auto_ptr<GridType> grd_ptr(new GridType());

			NumPy::resizeTarget3(*grd_ptr, arr);
			NumPy::copyArray3(*grd_ptr, arr);

			return grd_ptr.release();
		}
	};

#else // HAVE_NUMPY
	template <typename GridType, bool RESIZE = false>
	struct GridNDArrayAssignVisitor : public boost::python::def_visitor<GridNDArrayAssignVisitor<GridType, RESIZE> >
	{

		friend class boost::python::def_visitor_access;

		typedef typename GridType::ValueType ValueType;
	
		template <typename ClassType>
		void visit(ClassType& cl) const {}
	};

	template <typename GridType>
	struct GridNDArrayInitVisitor : public boost::python::def_visitor<GridNDArrayInitVisitor<GridType> >
	{

		friend class boost::python::def_visitor_access;

		typedef typename GridType::ValueType ValueType;
	
		template <typename ClassType>
		void visit(ClassType& cl) const {}
	};
#endif // HAVE_NUMPY
}

#endif // CDPL_PYTHON_MATH_GRIDVISITOR_HPP
