/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * GenericVariantFromPythonConverter.hpp 
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


#ifndef CDPL_PYTHON_BASE_GENERICVARIANTFROMPYTHONCONVERTER_HPP
#define CDPL_PYTHON_BASE_GENERICVARIANTFROMPYTHONCONVERTER_HPP

#include <boost/python.hpp>

#include "CDPL/Base/Variant.hpp"


namespace CDPLPythonBase
{

	template <typename T>
	struct GenericVariantFromPythonConverter 
	{

		GenericVariantFromPythonConverter() {
			using namespace boost;

			python::converter::registry::insert(&convertible, &construct, python::type_id<CDPL::Base::Variant>());
		}

		static void* convertible(PyObject* obj_ptr) {
			using namespace boost;

			if (!obj_ptr)
				return 0;

			if (!python::extract<T>(obj_ptr).check())
				return 0;

			return obj_ptr;
		}

		static void construct(PyObject* obj_ptr, boost::python::converter::rvalue_from_python_stage1_data* data) {
			using namespace boost;
			using namespace CDPL;

			void* storage = ((python::converter::rvalue_from_python_storage<Base::Variant>*)data)->storage.bytes;

			new (storage) Base::Variant(python::extract<T>(obj_ptr)());

			data->convertible = storage;
		}
	};
}

#endif // CDPL_PYTHON_BASE_GENERICVARIANTFROMPYTHONCONVERTER_HPP
