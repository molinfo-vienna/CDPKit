/* 
 * VectorVisitor.hpp 
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


#ifndef CDPL_PYTHON_MATH_VECTORVISITOR_HPP
#define CDPL_PYTHON_MATH_VECTORVISITOR_HPP

#include <string>
#include <sstream>
#include <utility>
#include <memory>

#include <boost/python.hpp>
#include <boost/python/def_visitor.hpp>

#include "CDPL/Config.hpp"

#include "VectorExpression.hpp"
#include "MatrixExpression.hpp"
#include "VectorExpressionAdapter.hpp"

#ifdef HAVE_NUMPY
# include "NumPy.hpp"
#endif


#ifndef CDPL_MATH_CHECKS_DISABLE
# define CHECK_VECTOR_INDEX(v, i)
#else
# define CHECK_VECTOR_INDEX(v, i) \
    if (i >= v.getSize()) {                        \
        throw CDPL::Base::IndexError("Vector: element index out of bounds"); \
    }
#endif


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
                .def("__truediv__", &divOperator, (python::arg("self"), python::arg("t")))
                .def("__rmul__", &rmulOperator, (python::arg("self"), python::arg("t")))
#ifdef HAVE_NUMPY
                .def("toArray", &toArray, python::arg("self"))
#endif
                .add_property("size", &VectorType::getSize);
        }
#ifdef HAVE_NUMPY
        static boost::python::object toArray(const VectorType& vec) {
            using namespace boost;

            if (NumPy::available()) {
                npy_intp shape[] = { npy_intp(vec.getSize()) };
                PyObject* array = PyArray_SimpleNew(1, shape, NumPy::DataTypeNum<typename VectorType::ValueType>::Value);

                if (array) {
                    typename VectorType::ValueType* data = static_cast<typename VectorType::ValueType*>(PyArray_GETPTR1(reinterpret_cast<PyArrayObject*>(array), 0));

                    for (std::size_t i = 0, size = vec.getSize(); i < size; i++, data++) 
                        *data = vec[i];

                    return python::object(python::handle<>(array));
                }
            }

            return python::object();            
        }
#endif
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
            CHECK_VECTOR_INDEX(vec, i);

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
                     python::return_self<>())
                .def("__itruediv__", &idivOperator, (python::arg("self"), python::arg("t")),
                     python::return_self<>());
        }

        static void setElement(VectorType& vec, SizeType i, const ValueType& value) {
            CHECK_VECTOR_INDEX(vec, i);

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

#ifdef HAVE_NUMPY
    template <typename VectorType, bool RESIZE = false>
    struct VectorNDArrayAssignVisitor : public boost::python::def_visitor<VectorNDArrayAssignVisitor<VectorType, RESIZE> >
    {

        friend class boost::python::def_visitor_access;

        typedef typename VectorType::ValueType ValueType;
    
        template <typename ClassType>
        void visit(ClassType& cl) const {
            using namespace boost;

            cl.def("assign", &assign, (python::arg("self"), python::arg("a")));
        }

        static void assign(VectorType& vec, PyArrayObject* arr) {
            using namespace CDPL;
            using namespace boost;

            if (!NumPy::checkSize(arr, vec.getSize())) {
                PyErr_SetString(PyExc_ValueError, "Vector: NumPy.NDArray size error");

                python::throw_error_already_set();
            }

            if (!NumPy::checkDataType<ValueType>(arr)) {
                PyErr_SetString(PyExc_TypeError, "Vector: NumPy.NDArray of incompatible type");

                python::throw_error_already_set();
            }

            NumPy::copyArray1(vec, arr);
        }
    };

    template <typename VectorType>
    struct VectorNDArrayAssignVisitor<VectorType, true> : public boost::python::def_visitor<VectorNDArrayAssignVisitor<VectorType, true> >
    {

        friend class boost::python::def_visitor_access;

        typedef typename VectorType::ValueType ValueType;
    
        template <typename ClassType>
        void visit(ClassType& cl) const {
            using namespace boost;

            cl.def("assign", &assign, (python::arg("self"), python::arg("a")));
        }

        static void assign(VectorType& vec, PyArrayObject* arr) {
            using namespace CDPL;
            using namespace boost;

            if (!NumPy::checkDim(arr, 1)) {
                PyErr_SetString(PyExc_ValueError, "Vector: NumPy.NDArray dimension error");

                python::throw_error_already_set();
            }

            if (!NumPy::checkDataType<ValueType>(arr)) {
                PyErr_SetString(PyExc_TypeError, "Vector: NumPy.NDArray of incompatible type");

                python::throw_error_already_set();
            }

            NumPy::resizeTarget1(vec, arr);
            NumPy::copyArray1(vec, arr);
        }
    };

    template <typename VectorType, bool RESIZE = false>
    struct VectorNDArrayInitVisitor : public boost::python::def_visitor<VectorNDArrayInitVisitor<VectorType, RESIZE> >
    {

        friend class boost::python::def_visitor_access;

        typedef typename VectorType::ValueType ValueType;
    
        template <typename ClassType>
        void visit(ClassType& cl) const {
            using namespace boost;

            cl.def("__init__", python::make_constructor(&construct, 
                                                        python::default_call_policies(),
                                                        (python::arg("a"))));
        }

        static VectorType* construct(PyArrayObject* arr) {
            using namespace CDPL;
            using namespace boost;

            std::auto_ptr<VectorType> vec_ptr(new VectorType());

            if (!NumPy::checkSize(arr, vec_ptr->getSize())) {
                PyErr_SetString(PyExc_ValueError, "Vector: NumPy.NDArray size error");

                python::throw_error_already_set();
            }

            if (!NumPy::checkDataType<ValueType>(arr)) {
                PyErr_SetString(PyExc_TypeError, "Vector: NumPy.NDArray of incompatible type");

                python::throw_error_already_set();
            }

            NumPy::copyArray1(*vec_ptr, arr);

            return vec_ptr.release();
        }
    };

    template <typename VectorType>
    struct VectorNDArrayInitVisitor<VectorType, true> : public boost::python::def_visitor<VectorNDArrayInitVisitor<VectorType, true> >
    {

        friend class boost::python::def_visitor_access;

        typedef typename VectorType::ValueType ValueType;
    
        template <typename ClassType>
        void visit(ClassType& cl) const {
            using namespace boost;

            cl.def("__init__", python::make_constructor(&construct, 
                                                        python::default_call_policies(),
                                                        (python::arg("a"))));
        }

        static VectorType* construct(PyArrayObject* arr) {
            using namespace CDPL;
            using namespace boost;

            if (!NumPy::checkDim(arr, 1)) {
                PyErr_SetString(PyExc_ValueError, "Vector: NumPy.NDArray dimension error");

                python::throw_error_already_set();
            }

            if (!NumPy::checkDataType<ValueType>(arr)) {
                PyErr_SetString(PyExc_TypeError, "Vector: NumPy.NDArray of incompatible type");

                python::throw_error_already_set();
            }

            std::auto_ptr<VectorType> vec_ptr(new VectorType());

            NumPy::resizeTarget1(*vec_ptr, arr);
            NumPy::copyArray1(*vec_ptr, arr);

            return vec_ptr.release();
        }
    };

#else // HAVE_NUMPY
    template <typename VectorType, bool RESIZE = false>
    struct VectorNDArrayAssignVisitor : public boost::python::def_visitor<VectorNDArrayAssignVisitor<VectorType, RESIZE> >
    {

        friend class boost::python::def_visitor_access;

        typedef typename VectorType::ValueType ValueType;
    
        template <typename ClassType>
        void visit(ClassType& cl) const {}
    };

    template <typename VectorType, bool RESIZE = false>
    struct VectorNDArrayInitVisitor : public boost::python::def_visitor<VectorNDArrayInitVisitor<VectorType, RESIZE> >
    {

        friend class boost::python::def_visitor_access;

        typedef typename VectorType::ValueType ValueType;
    
        template <typename ClassType>
        void visit(ClassType& cl) const {}
    };
#endif // HAVE_NUMPY
}

#endif // CDPL_PYTHON_MATH_VECTORVISITOR_HPP
