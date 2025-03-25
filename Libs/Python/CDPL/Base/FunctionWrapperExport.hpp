/* 
 * FunctionWrapperExport.hpp 
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


#ifndef CDPL_PYTHON_BASE_FUNCTIONWRAPPEREXPORT_HPP
#define CDPL_PYTHON_BASE_FUNCTIONWRAPPEREXPORT_HPP

#include <functional>

#include <boost/python.hpp>
#include <boost/type_traits.hpp>

#include "CallableObjectAdapter.hpp"


namespace CDPLPythonBase
{

    template <typename FunctionType>
    struct FunctionExportBase
    {

        typedef std::function<FunctionType> FunctionWrapperType;

        static void* convertible(PyObject* obj_ptr)
        {
            return (obj_ptr && PyCallable_Check(obj_ptr) ? obj_ptr : nullptr);
        }

        static bool nonZero(FunctionWrapperType& func)
        {
            return func.operator bool();
        }
    };

    template <typename FunctionType,
              typename Arg1Type     = typename boost::function_traits<FunctionType>::arg1_type,
              typename Arg2Type     = typename boost::function_traits<FunctionType>::arg2_type,
              typename Arg3Type     = typename boost::function_traits<FunctionType>::arg3_type,
              typename Arg4Type     = typename boost::function_traits<FunctionType>::arg4_type,
              typename RetValPolicy = boost::python::return_value_policy<boost::python::return_by_value> >
    struct Function4Export : private FunctionExportBase<FunctionType>
    {

        typedef std::function<FunctionType> FunctionWrapperType;

        Function4Export(const char* name)
        {
            using namespace boost;

            python::class_<FunctionWrapperType, boost::noncopyable>(name, python::no_init)
                .def(python::init<>(python::arg("self")))
                .def(python::init<const FunctionWrapperType&>((python::arg("self"), python::arg("func"))))
                .def("__init__", python::make_constructor(&construct, python::default_call_policies(),
                                                          (python::arg("callable"))))
                .def("__call__", &callOperator,
                     (python::arg("self"), python::arg("arg1"), python::arg("arg2"),
                      python::arg("arg3"), python::arg("arg4")),
                     RetValPolicy())
                .def("__bool__", &this->nonZero, python::arg("self"))
                .def("__nonzero__", &this->nonZero, python::arg("self"));

            python::converter::registry::push_back(&this->convertible, &convConstruct, python::type_id<FunctionWrapperType>());
        }

        static typename boost::function_traits<FunctionType>::result_type
        callOperator(FunctionWrapperType& func, Arg1Type& a1, Arg2Type& a2, Arg3Type& a3, Arg4Type& a4)
        {
            return func(a1, a2, a3, a4);
        }

        static FunctionWrapperType* construct(const boost::python::object& callable)
        {
            if (callable.ptr() == Py_None)
                return new FunctionWrapperType();

            return new FunctionWrapperType(QuarternaryFunctionAdapter<typename boost::function_traits<FunctionType>::result_type,
                                                                      typename boost::function_traits<FunctionType>::arg1_type,
                                                                      typename boost::function_traits<FunctionType>::arg2_type,
                                                                      typename boost::function_traits<FunctionType>::arg3_type,
                                                                      typename boost::function_traits<FunctionType>::arg4_type>(callable));
        }

        static void convConstruct(PyObject* obj_ptr, boost::python::converter::rvalue_from_python_stage1_data* data)
        {
            using namespace boost;

            void* storage = ((python::converter::rvalue_from_python_storage<FunctionWrapperType>*)data)->storage.bytes;

            if (obj_ptr == Py_None)
                new (storage) FunctionWrapperType();
            else
                new (storage) FunctionWrapperType(QuarternaryFunctionAdapter<typename boost::function_traits<FunctionType>::result_type,
                                                                             typename boost::function_traits<FunctionType>::arg1_type,
                                                                             typename boost::function_traits<FunctionType>::arg2_type,
                                                                             typename boost::function_traits<FunctionType>::arg3_type,
                                                                             typename boost::function_traits<FunctionType>::arg4_type>(
                    python::object(python::handle<>(boost::python::borrowed(obj_ptr)))));

            data->convertible = storage;
        }
    };

    template <typename FunctionType,
              typename Arg1Type     = typename boost::function_traits<FunctionType>::arg1_type,
              typename Arg2Type     = typename boost::function_traits<FunctionType>::arg2_type,
              typename Arg3Type     = typename boost::function_traits<FunctionType>::arg3_type,
              typename RetValPolicy = boost::python::return_value_policy<boost::python::return_by_value> >
    struct Function3Export : private FunctionExportBase<FunctionType>
    {

        typedef std::function<FunctionType> FunctionWrapperType;

        Function3Export(const char* name)
        {
            using namespace boost;

            python::class_<FunctionWrapperType, boost::noncopyable>(name, python::no_init)
                .def(python::init<>(python::arg("self")))
                .def(python::init<const FunctionWrapperType&>((python::arg("self"), python::arg("func"))))
                .def("__init__", python::make_constructor(&construct, python::default_call_policies(),
                                                          (python::arg("callable"))))
                .def("__call__", &callOperator,
                     (python::arg("self"), python::arg("arg1"), python::arg("arg2"), python::arg("arg3")),
                     RetValPolicy())
                .def("__bool__", &this->nonZero, python::arg("self"))
                .def("__nonzero__", &this->nonZero, python::arg("self"));

            python::converter::registry::push_back(&this->convertible, &convConstruct, python::type_id<FunctionWrapperType>());
        }

        static typename boost::function_traits<FunctionType>::result_type
        callOperator(FunctionWrapperType& func, Arg1Type& a1, Arg2Type& a2, Arg3Type& a3)
        {
            return func(a1, a2, a3);
        }

        static FunctionWrapperType* construct(const boost::python::object& callable)
        {
            if (callable.ptr() == Py_None)
                return new FunctionWrapperType();

            return new FunctionWrapperType(TernaryFunctionAdapter<typename boost::function_traits<FunctionType>::result_type,
                                                                  typename boost::function_traits<FunctionType>::arg1_type,
                                                                  typename boost::function_traits<FunctionType>::arg2_type,
                                                                  typename boost::function_traits<FunctionType>::arg3_type>(callable));
        }

        static void convConstruct(PyObject* obj_ptr, boost::python::converter::rvalue_from_python_stage1_data* data)
        {
            using namespace boost;

            void* storage = ((python::converter::rvalue_from_python_storage<FunctionWrapperType>*)data)->storage.bytes;

            if (obj_ptr == Py_None)
                new (storage) FunctionWrapperType();
            else
                new (storage) FunctionWrapperType(TernaryFunctionAdapter<typename boost::function_traits<FunctionType>::result_type,
                                                                         typename boost::function_traits<FunctionType>::arg1_type,
                                                                         typename boost::function_traits<FunctionType>::arg2_type,
                                                                         typename boost::function_traits<FunctionType>::arg3_type>(
                    python::object(python::handle<>(boost::python::borrowed(obj_ptr)))));

            data->convertible = storage;
        }
    };

    template <typename FunctionType,
              typename Arg1Type     = typename boost::function_traits<FunctionType>::arg1_type,
              typename Arg2Type     = typename boost::function_traits<FunctionType>::arg2_type,
              typename RetValPolicy = boost::python::return_value_policy<boost::python::return_by_value> >
    struct Function2Export : private FunctionExportBase<FunctionType>
    {

        typedef std::function<FunctionType> FunctionWrapperType;

        Function2Export(const char* name)
        {
            using namespace boost;

            python::class_<FunctionWrapperType, boost::noncopyable>(name, python::no_init)
                .def(python::init<>(python::arg("self")))
                .def(python::init<const FunctionWrapperType&>((python::arg("self"), python::arg("func"))))
                .def("__init__", python::make_constructor(&construct, python::default_call_policies(),
                                                          (python::arg("callable"))))
                .def("__call__", &callOperator,
                     (python::arg("self"), python::arg("arg1"), python::arg("arg2")),
                     RetValPolicy())
                .def("__bool__", &this->nonZero, python::arg("self"))
                .def("__nonzero__", &this->nonZero, python::arg("self"));

            python::converter::registry::push_back(&this->convertible, &convConstruct, python::type_id<FunctionWrapperType>());
        }

        static typename boost::function_traits<FunctionType>::result_type
        callOperator(FunctionWrapperType& func, Arg1Type& a1, Arg2Type& a2)
        {
            return func(a1, a2);
        }

        static FunctionWrapperType* construct(const boost::python::object& callable)
        {
            if (callable.ptr() == Py_None)
                return new FunctionWrapperType();

            return new FunctionWrapperType(BinaryFunctionAdapter<typename boost::function_traits<FunctionType>::result_type,
                                                                 typename boost::function_traits<FunctionType>::arg1_type,
                                                                 typename boost::function_traits<FunctionType>::arg2_type>(callable));
        }

        static void convConstruct(PyObject* obj_ptr, boost::python::converter::rvalue_from_python_stage1_data* data)
        {
            using namespace boost;

            void* storage = ((python::converter::rvalue_from_python_storage<FunctionWrapperType>*)data)->storage.bytes;

            if (obj_ptr == Py_None)
                new (storage) FunctionWrapperType();
            else
                new (storage) FunctionWrapperType(BinaryFunctionAdapter<typename boost::function_traits<FunctionType>::result_type,
                                                                        typename boost::function_traits<FunctionType>::arg1_type,
                                                                        typename boost::function_traits<FunctionType>::arg2_type>(
                    python::object(python::handle<>(boost::python::borrowed(obj_ptr)))));

            data->convertible = storage;
        }
    };

    template <typename FunctionType, typename Arg1Type = typename boost::function_traits<FunctionType>::arg1_type,
              typename RetValPolicy = boost::python::return_value_policy<boost::python::return_by_value> >
    struct Function1Export : private FunctionExportBase<FunctionType>
    {

        typedef std::function<FunctionType> FunctionWrapperType;

        Function1Export(const char* name)
        {
            using namespace boost;

            python::class_<FunctionWrapperType, boost::noncopyable>(name, python::no_init)
                .def(python::init<>(python::arg("self")))
                .def(python::init<const FunctionWrapperType&>((python::arg("self"), python::arg("func"))))
                .def("__init__", python::make_constructor(&construct, python::default_call_policies(),
                                                          (python::arg("callable"))))
                .def("__call__", &callOperator, (python::arg("self"), python::arg("arg1")), RetValPolicy())
                .def("__bool__", &this->nonZero, python::arg("self"))
                .def("__nonzero__", &this->nonZero, python::arg("self"));

            python::converter::registry::push_back(&this->convertible, &convConstruct, python::type_id<FunctionWrapperType>());
        }

        static typename boost::function_traits<FunctionType>::result_type
        callOperator(FunctionWrapperType& func, Arg1Type& a1)
        {
            return func(a1);
        }

        static FunctionWrapperType* construct(const boost::python::object& callable)
        {
            if (callable.ptr() == Py_None)
                return new FunctionWrapperType();

            return new FunctionWrapperType(UnaryFunctionAdapter<typename boost::function_traits<FunctionType>::result_type,
                                                                typename boost::function_traits<FunctionType>::arg1_type>(callable));
        }

        static void convConstruct(PyObject* obj_ptr, boost::python::converter::rvalue_from_python_stage1_data* data)
        {
            using namespace boost;

            void* storage = ((python::converter::rvalue_from_python_storage<FunctionWrapperType>*)data)->storage.bytes;

            if (obj_ptr == Py_None)
                new (storage) FunctionWrapperType();
            else
                new (storage) FunctionWrapperType(UnaryFunctionAdapter<typename boost::function_traits<FunctionType>::result_type,
                                                                       typename boost::function_traits<FunctionType>::arg1_type>(
                    python::object(python::handle<>(boost::python::borrowed(obj_ptr)))));

            data->convertible = storage;
        }
    };

    template <typename FunctionType,
              typename RetValPolicy = boost::python::return_value_policy<boost::python::return_by_value> >
    struct Function0Export : private FunctionExportBase<FunctionType>
    {

        typedef std::function<FunctionType> FunctionWrapperType;

        Function0Export(const char* name)
        {
            using namespace boost;

            python::class_<FunctionWrapperType, boost::noncopyable>(name, python::no_init)
                .def(python::init<>(python::arg("self")))
                .def(python::init<const FunctionWrapperType&>((python::arg("self"), python::arg("func"))))
                .def("__init__", python::make_constructor(&construct, python::default_call_policies(),
                                                          (python::arg("callable"))))
                .def("__call__", &callOperator, python::arg("self"), RetValPolicy())
                .def("__bool__", &this->nonZero, python::arg("self"))
                .def("__nonzero__", &this->nonZero, python::arg("self"));

            python::converter::registry::push_back(&this->convertible, &convConstruct, python::type_id<FunctionWrapperType>());
        }

        static typename boost::function_traits<FunctionType>::result_type
        callOperator(FunctionWrapperType& func)
        {
            return func();
        }

        static FunctionWrapperType* construct(const boost::python::object& callable)
        {
            if (callable.ptr() == Py_None)
                return new FunctionWrapperType();

            return new FunctionWrapperType(NoArgFunctionAdapter<typename boost::function_traits<FunctionType>::result_type>(callable));
        }

        static void convConstruct(PyObject* obj_ptr, boost::python::converter::rvalue_from_python_stage1_data* data)
        {
            using namespace boost;

            void* storage = ((python::converter::rvalue_from_python_storage<FunctionWrapperType>*)data)->storage.bytes;

            if (obj_ptr == Py_None)
                new (storage) FunctionWrapperType();
            else
                new (storage) FunctionWrapperType(NoArgFunctionAdapter<typename boost::function_traits<FunctionType>::result_type>(
                    python::object(python::handle<>(boost::python::borrowed(obj_ptr)))));

            data->convertible = storage;
        }
    };
} // namespace CDPLPythonBase

#endif // CDPL_PYTHON_BASE_FUNCTIONWRAPPEREXPORT_HPP
