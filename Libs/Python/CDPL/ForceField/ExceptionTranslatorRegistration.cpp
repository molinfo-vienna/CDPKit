/* 
 * ExceptionTranslatorRegistration.cpp 
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


#include <boost/python.hpp>

#include "CDPL/ForceField/Exceptions.hpp"

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


void CDPLPythonForceField::registerExceptionTranslators()
{
	using namespace boost;
	using namespace CDPL;

	python::class_<ExceptionMapping, boost::noncopyable>("_ExceptionMapping", python::no_init)
		.def_readwrite("Error", ExceptionTranslator<ForceField::Error>::getMappedExceptionType())
		.def_readwrite("ParameterizationFailed", ExceptionTranslator<ForceField::ParameterizationFailed>::getMappedExceptionType());

	python::register_exception_translator<ForceField::Error>(ExceptionTranslator<ForceField::Error>());
	python::register_exception_translator<ForceField::ParameterizationFailed>(ExceptionTranslator<ForceField::ParameterizationFailed>());
}
