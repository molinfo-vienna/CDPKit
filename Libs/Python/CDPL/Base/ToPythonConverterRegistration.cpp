/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * ToPythonConverterRegistration.cpp 
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


#include <cstdint>

#include <boost/python.hpp>

#include "CDPL/Base/Any.hpp"

#include "ConverterRegistration.hpp"


namespace CDPLPythonBase
{

	struct AnyToPythonConverter 
	{

		static PyObject* convert(const CDPL::Base::Any& var) {
			using namespace boost;
			using namespace CDPL;

			if (var.isEmpty()) 
				return python::incref(python::object().ptr());

			python::type_info type(var.getTypeID());

			if (type == python::type_id<python::handle<> >()) 
				return python::incref(python::object(var.getData<python::handle<> >()).ptr());

			if (type == python::type_id<char>()) 
				return python::incref(python::object(var.getData<char>()).ptr());

			if (type == python::type_id<unsigned char>()) 
				return python::incref(python::object(var.getData<unsigned char>()).ptr());

			if (type == python::type_id<signed char>()) 
				return python::incref(python::object(var.getData<signed char>()).ptr());

			if (type == python::type_id<unsigned short>()) 
				return python::incref(python::object(var.getData<unsigned short>()).ptr());

			if (type == python::type_id<signed short>()) 
				return python::incref(python::object(var.getData<signed short>()).ptr());

			if (type == python::type_id<unsigned int>()) 
				return python::incref(python::object(var.getData<unsigned int>()).ptr());

			if (type == python::type_id<signed int>()) 
				return python::incref(python::object(var.getData<signed int>()).ptr());

			if (type == python::type_id<unsigned long>()) 
				return python::incref(python::object(var.getData<unsigned long>()).ptr());

			if (type == python::type_id<signed long>()) 
				return python::incref(python::object(var.getData<signed long>()).ptr());

			if (type == python::type_id<bool>()) 
				return python::incref(python::object(var.getData<bool>()).ptr());

			if (type == python::type_id<float>()) 
				return python::incref(python::object(var.getData<float>()).ptr());

			if (type == python::type_id<double>()) 
				return python::incref(python::object(var.getData<double>()).ptr());

			if (type == python::type_id<long double>()) 
				return python::incref(python::object(var.getData<long double>()).ptr());

			if (type == python::type_id<std::uint64_t>()) 
				return python::incref(python::object(var.getData<std::uint64_t>()).ptr());

			if (type == python::type_id<std::int64_t>()) 
				return python::incref(python::object(var.getData<std::int64_t>()).ptr());

			if (type == python::type_id<std::string>()) 
				return python::incref(python::object(var.getData<std::string>()).ptr());
			
			type = python::type_info(var.getTypeID());

			const python::converter::registration* reg = python::converter::registry::query(type);

			if (!reg) {
				python::handle<> msg(PyUnicode_FromFormat("No to_python (by-value) converter found for C++ type: %s" , type.name()));

				PyErr_SetObject(PyExc_TypeError, msg.get());

				python::throw_error_already_set();
            }

			return reg->to_python(var.getDataPointer());
		}
	};
}


void CDPLPythonBase::registerToPythonConverters()
{
	using namespace boost;
	using namespace CDPL;

	python::to_python_converter<Base::Any, AnyToPythonConverter>();         // for Any value to Python conversions

	python::class_<Base::Any, boost::noncopyable>("Any", python::no_init);  // for holding a reference/pointer to Any 
}
