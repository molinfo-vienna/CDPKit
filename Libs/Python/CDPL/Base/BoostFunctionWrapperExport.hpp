/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * BoostFunctionWrapperExport.hpp 
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


#ifndef CDPL_PYTHON_BASE_BOOSTFUNCTIONWRAPPEREXPORT_HPP
#define CDPL_PYTHON_BASE_BOOSTFUNCTIONWRAPPEREXPORT_HPP

#include <boost/python.hpp>

#include "CallableObjectAdapter.hpp"


namespace CDPLPythonBase 
{

	template <typename FunctionType> 
    struct BoostFunctionExportBase
	{

		static void* convertible(PyObject* obj_ptr) {
			return obj_ptr;
		}

		static bool nonZero(FunctionType& func) {
			return !func.empty();
		}
	};

    template <typename FunctionType, 
			  typename Arg1Type = typename FunctionType::arg1_type, 
			  typename Arg2Type = typename FunctionType::arg2_type, 
			  typename Arg3Type = typename FunctionType::arg3_type, 
			  typename Arg4Type = typename FunctionType::arg4_type,
			  typename RetValPolicy = boost::python::return_value_policy<boost::python::return_by_value> >
    struct BoostFunction4Export : private BoostFunctionExportBase<FunctionType>
    {

		BoostFunction4Export(const char* name) {
			using namespace boost;

			python::class_<FunctionType, boost::noncopyable>(name, python::no_init)
				.def(python::init<>(python::arg("self")))
				.def(python::init<const FunctionType&>((python::arg("self"), python::arg("func"))))
				.def("__init__", python::make_constructor(&construct, python::default_call_policies(), 
														  python::arg("callable")))
				.def("__call__", &callOperator, 
					 (python::arg("self"), python::arg("arg1"), python::arg("arg2"), 
					  python::arg("arg3"), python::arg("arg4")), RetValPolicy())
				.def("__nonzero__", &this->nonZero, python::arg("self"));

			python::converter::registry::push_back(&this->convertible, &convConstruct, python::type_id<FunctionType>());
		}

		static typename FunctionType::result_type callOperator(FunctionType& func, Arg1Type& a1, Arg2Type& a2, Arg3Type& a3, Arg4Type& a4) {
			return func(a1, a2, a3, a4);
		}

		static FunctionType* construct(const boost::python::object& callable) {
			if (callable.ptr() == Py_None)
				return new FunctionType();

			return new FunctionType(QuarternaryFunctionAdapter<typename FunctionType::result_type, 
									typename FunctionType::arg1_type, typename FunctionType::arg2_type, 
									typename FunctionType::arg3_type, typename FunctionType::arg4_type>(callable));
		}

		static void convConstruct(PyObject* obj_ptr, boost::python::converter::rvalue_from_python_stage1_data* data) {
			using namespace boost;
			using namespace CDPL;

			void* storage = ((python::converter::rvalue_from_python_storage<FunctionType>*)data)->storage.bytes;

			if (obj_ptr == Py_None)
				new (storage) FunctionType();
			else
				new (storage) FunctionType(QuarternaryFunctionAdapter<typename FunctionType::result_type, 
										   typename FunctionType::arg1_type, typename FunctionType::arg2_type, 
										   typename FunctionType::arg3_type, typename FunctionType::arg4_type
										   >(python::object(python::handle<>(boost::python::borrowed(obj_ptr)))));

			data->convertible = storage;
		}
    };

    template <typename FunctionType, 
			  typename Arg1Type = typename FunctionType::arg1_type, 
			  typename Arg2Type = typename FunctionType::arg2_type, 
			  typename Arg3Type = typename FunctionType::arg3_type,
			  typename RetValPolicy = boost::python::return_value_policy<boost::python::return_by_value> > 
    struct BoostFunction3Export : private BoostFunctionExportBase<FunctionType>
    {

		BoostFunction3Export(const char* name) {
			using namespace boost;

			python::class_<FunctionType, boost::noncopyable>(name, python::no_init)
				.def(python::init<>(python::arg("self")))
				.def(python::init<const FunctionType&>((python::arg("self"), python::arg("func"))))
				.def("__init__", python::make_constructor(&construct, python::default_call_policies(), 
														  python::arg("callable")))
				.def("__call__", &callOperator, 
					 (python::arg("self"), python::arg("arg1"), python::arg("arg2"), python::arg("arg3")),
					 RetValPolicy())
				.def("__nonzero__", &this->nonZero, python::arg("self"));

			python::converter::registry::push_back(&this->convertible, &convConstruct, python::type_id<FunctionType>());
		}

		static typename FunctionType::result_type callOperator(FunctionType& func, Arg1Type& a1, Arg2Type& a2, Arg3Type& a3) {
			return func(a1, a2, a3);
		}

		static FunctionType* construct(const boost::python::object& callable) {
			if (callable.ptr() == Py_None)
				return new FunctionType();

			return new FunctionType(TernaryFunctionAdapter<typename FunctionType::result_type, 
									typename FunctionType::arg1_type, typename FunctionType::arg2_type, 
									typename FunctionType::arg3_type>(callable));
		}

		static void convConstruct(PyObject* obj_ptr, boost::python::converter::rvalue_from_python_stage1_data* data) {
			using namespace boost;
			using namespace CDPL;

			void* storage = ((python::converter::rvalue_from_python_storage<FunctionType>*)data)->storage.bytes;

			if (obj_ptr == Py_None)
				new (storage) FunctionType();
			else
				new (storage) FunctionType(TernaryFunctionAdapter<typename FunctionType::result_type, 
										   typename FunctionType::arg1_type, typename FunctionType::arg2_type, 
										   typename FunctionType::arg3_type>(python::object(python::handle<>(boost::python::borrowed(obj_ptr)))));

			data->convertible = storage;
		}
    };

    template <typename FunctionType, 
			  typename Arg1Type = typename FunctionType::arg1_type, 
			  typename Arg2Type = typename FunctionType::arg2_type,
			  typename RetValPolicy = boost::python::return_value_policy<boost::python::return_by_value> >
    struct BoostFunction2Export : private BoostFunctionExportBase<FunctionType>
    {

		BoostFunction2Export(const char* name) {
			using namespace boost;

			python::class_<FunctionType, boost::noncopyable>(name, python::no_init)
				.def(python::init<>(python::arg("self")))
				.def(python::init<const FunctionType&>((python::arg("self"), python::arg("func"))))
				.def("__init__", python::make_constructor(&construct, python::default_call_policies(), 
														  python::arg("callable")))
				.def("__call__", &callOperator, 
					 (python::arg("self"), python::arg("arg1"), python::arg("arg2")), 
					 RetValPolicy())
				.def("__nonzero__", &this->nonZero, python::arg("self"));

			python::converter::registry::push_back(&this->convertible, &convConstruct, python::type_id<FunctionType>());
		}

		static typename FunctionType::result_type callOperator(FunctionType& func, Arg1Type& a1, Arg2Type& a2) {
			return func(a1, a2);
		}

		static FunctionType* construct(const boost::python::object& callable) {
			if (callable.ptr() == Py_None)
				return new FunctionType();

			return new FunctionType(BinaryFunctionAdapter<typename FunctionType::result_type, 
									typename FunctionType::arg1_type, 
									typename FunctionType::arg2_type>(callable));
		}

		static void convConstruct(PyObject* obj_ptr, boost::python::converter::rvalue_from_python_stage1_data* data) {
			using namespace boost;
			using namespace CDPL;

			void* storage = ((python::converter::rvalue_from_python_storage<FunctionType>*)data)->storage.bytes;

			if (obj_ptr == Py_None)
				new (storage) FunctionType();
			else
				new (storage) FunctionType(BinaryFunctionAdapter<typename FunctionType::result_type, 
										   typename FunctionType::arg1_type, typename FunctionType::arg2_type
										   >(python::object(python::handle<>(boost::python::borrowed(obj_ptr)))));

			data->convertible = storage;
		}
    };

    template <typename FunctionType, typename Arg1Type = typename FunctionType::arg1_type,
			  typename RetValPolicy = boost::python::return_value_policy<boost::python::return_by_value> > 
    struct BoostFunction1Export : private BoostFunctionExportBase<FunctionType>
    {

		BoostFunction1Export(const char* name) {
			using namespace boost;

			python::class_<FunctionType, boost::noncopyable>(name, python::no_init)
				.def(python::init<>(python::arg("self")))
				.def(python::init<const FunctionType&>((python::arg("self"), python::arg("func"))))
				.def("__init__", python::make_constructor(&construct, python::default_call_policies(), 
														  python::arg("callable")))
				.def("__call__", &callOperator, (python::arg("self"), python::arg("arg1")),
					 RetValPolicy())
				.def("__nonzero__", &this->nonZero, python::arg("self"));

			python::converter::registry::push_back(&this->convertible, &convConstruct, python::type_id<FunctionType>());
		}

		static typename FunctionType::result_type callOperator(FunctionType& func, Arg1Type& a1) {
			return func(a1);
		}

		static FunctionType* construct(const boost::python::object& callable) {
			if (callable.ptr() == Py_None)
				return new FunctionType();

			return new FunctionType(UnaryFunctionAdapter<typename FunctionType::result_type, 
									typename FunctionType::arg1_type>(callable));
		}

		static void convConstruct(PyObject* obj_ptr, boost::python::converter::rvalue_from_python_stage1_data* data) {
			using namespace boost;
			using namespace CDPL;

			void* storage = ((python::converter::rvalue_from_python_storage<FunctionType>*)data)->storage.bytes;

			if (obj_ptr == Py_None) 
				new (storage) FunctionType();
			 else
				new (storage) FunctionType(UnaryFunctionAdapter<typename FunctionType::result_type, 
										   typename FunctionType::arg1_type>(python::object(python::handle<>(boost::python::borrowed(obj_ptr)))));

			data->convertible = storage;
		}
    };

	template <typename FunctionType,
			  typename RetValPolicy = boost::python::return_value_policy<boost::python::return_by_value> > 
    struct BoostFunction0Export : private BoostFunctionExportBase<FunctionType>
    {

		BoostFunction0Export(const char* name) {
			using namespace boost;

			python::class_<FunctionType, boost::noncopyable>(name, python::no_init)
				.def(python::init<>(python::arg("self")))
				.def(python::init<const FunctionType&>((python::arg("self"), python::arg("func"))))
				.def("__init__", python::make_constructor(&construct, python::default_call_policies(), 
														  python::arg("callable")))
				.def("__call__", &callOperator, python::arg("self"), RetValPolicy())
				.def("__nonzero__", &this->nonZero, python::arg("self"));

			python::converter::registry::push_back(&this->convertible, &convConstruct, python::type_id<FunctionType>());
		}

		static typename FunctionType::result_type callOperator(FunctionType& func) {
			return func();
		}

		static FunctionType* construct(const boost::python::object& callable) {
			if (callable.ptr() == Py_None)
				return new FunctionType();

			return new FunctionType(NoArgFunctionAdapter<typename FunctionType::result_type>(callable));
		}

		static void convConstruct(PyObject* obj_ptr, boost::python::converter::rvalue_from_python_stage1_data* data) {
			using namespace boost;
			using namespace CDPL;

			void* storage = ((python::converter::rvalue_from_python_storage<FunctionType>*)data)->storage.bytes;

			if (obj_ptr == Py_None)
				new (storage) FunctionType();
			else
				new (storage) FunctionType(NoArgFunctionAdapter<typename FunctionType::result_type>(python::object(python::handle<>(boost::python::borrowed(obj_ptr)))));
			
			data->convertible = storage;
		}
	};
}

#endif // CDPL_PYTHON_BASE_BOOSTFUNCTIONWRAPPEREXPORT_HPP
