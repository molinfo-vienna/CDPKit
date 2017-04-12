/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * FromPythonToVectorConverterRegistration.cpp 
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


#include <boost/python.hpp>
#include <boost/python/ssize_t.hpp>

#include "CDPL/Math/Vector.hpp"

#include "ConverterRegistration.hpp"


namespace
{

	template <typename VectorType>
	struct VectorFromPySequenceConverter 
	{

		VectorFromPySequenceConverter() {
			using namespace boost;

			python::converter::registry::insert(&convertible, &construct, python::type_id<VectorType>());
		}

		static void* convertible(PyObject* obj_ptr) {
			using namespace boost;

			if (!obj_ptr)
				return 0;

			if (!PyList_Check(obj_ptr) && !PyTuple_Check(obj_ptr))
				return 0;

			python::ssize_t size = PySequence_Size(obj_ptr);

			for (python::ssize_t i = 0; i < size; i++) 
				if (!python::extract<typename VectorType::ValueType>(PySequence_GetItem(obj_ptr, i)).check())
					return 0;

			return obj_ptr;
		}

		static void construct(PyObject* obj_ptr, boost::python::converter::rvalue_from_python_stage1_data* data) {
			using namespace boost;

			python::ssize_t size = PySequence_Size(obj_ptr);

			VectorType vec(size);

			for (python::ssize_t i = 0; i < size; i++)
				vec(i) = python::extract<typename VectorType::ValueType>(PySequence_GetItem(obj_ptr, i));

			void* storage = ((python::converter::rvalue_from_python_storage<VectorType>*)data)->storage.bytes;

			new (storage) VectorType();

			static_cast<VectorType*>(storage)->swap(vec);

			data->convertible = storage;
		}
	};
}


void CDPLPythonMath::registerFromPythonToVectorConverters()
{
	using namespace CDPL;

	VectorFromPySequenceConverter<Math::FVector>();
	VectorFromPySequenceConverter<Math::DVector>();
	VectorFromPySequenceConverter<Math::LVector>();
	VectorFromPySequenceConverter<Math::ULVector>();
}
