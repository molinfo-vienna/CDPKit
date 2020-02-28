/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * ExceptionTranslatorRegistration.cpp 
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

#include "CDPL/Base/Exceptions.hpp"

#include "ExceptionTranslatorRegistration.hpp"


namespace
{

	struct ExceptionMapping {};

	template <typename T>
	struct ExceptionTranslator
	{
	
		void operator()(const T& ex) const {
			using namespace boost;

			boost::python::object& mapped_ex_type = getMappedExceptionType();

			if (mapped_ex_type.ptr() != Py_None) {
				python::object trans_ex_inst = mapped_ex_type(ex.what());
			
				PyErr_SetObject(mapped_ex_type.ptr(), trans_ex_inst.ptr());

			} else
				throw ex;
		}

		static boost::python::object& getMappedExceptionType() {
			static boost::python::object mappedExceptionType;

			return mappedExceptionType;
		}
	};
}


void CDPLPythonBase::registerExceptionTranslators()
{
	using namespace boost;
	using namespace CDPL;

	python::class_<ExceptionMapping, boost::noncopyable>("_ExceptionMapping", python::no_init)
		.def_readwrite("Exception", ExceptionTranslator<Base::Exception>::getMappedExceptionType())
		.def_readwrite("ValueError", ExceptionTranslator<Base::ValueError>::getMappedExceptionType())
		.def_readwrite("NullPointerException", ExceptionTranslator<Base::NullPointerException>::getMappedExceptionType())
		.def_readwrite("SizeError", ExceptionTranslator<Base::SizeError>::getMappedExceptionType())
		.def_readwrite("RangeError", ExceptionTranslator<Base::RangeError>::getMappedExceptionType())
		.def_readwrite("IndexError", ExceptionTranslator<Base::IndexError>::getMappedExceptionType())
		.def_readwrite("ItemNotFound", ExceptionTranslator<Base::ItemNotFound>::getMappedExceptionType())
		.def_readwrite("BadCast", ExceptionTranslator<Base::BadCast>::getMappedExceptionType())
		.def_readwrite("OperationFailed", ExceptionTranslator<Base::OperationFailed>::getMappedExceptionType())
		.def_readwrite("CalculationFailed", ExceptionTranslator<Base::CalculationFailed>::getMappedExceptionType())
		.def_readwrite("IOError", ExceptionTranslator<Base::IOError>::getMappedExceptionType());

	python::register_exception_translator<Base::Exception>(ExceptionTranslator<Base::Exception>());
	python::register_exception_translator<Base::ValueError>(ExceptionTranslator<Base::ValueError>());
	python::register_exception_translator<Base::SizeError>(ExceptionTranslator<Base::SizeError>());
	python::register_exception_translator<Base::ItemNotFound>(ExceptionTranslator<Base::ItemNotFound>());
	python::register_exception_translator<Base::BadCast>(ExceptionTranslator<Base::BadCast>());
	python::register_exception_translator<Base::OperationFailed>(ExceptionTranslator<Base::OperationFailed>());
	python::register_exception_translator<Base::NullPointerException>(ExceptionTranslator<Base::NullPointerException>());
	python::register_exception_translator<Base::RangeError>(ExceptionTranslator<Base::RangeError>());
	python::register_exception_translator<Base::CalculationFailed>(ExceptionTranslator<Base::CalculationFailed>());
	python::register_exception_translator<Base::IOError>(ExceptionTranslator<Base::IOError>());
	python::register_exception_translator<Base::IndexError>(ExceptionTranslator<Base::IndexError>());
}
