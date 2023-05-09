/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * FromPythonToVectorArrayConverterRegistration.cpp 
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


#include <cstddef>

#include <boost/python.hpp>
#include <boost/python/ssize_t.hpp>

#include "CDPL/Config.hpp"
#include "CDPL/Math/VectorArray.hpp"

#include "ConverterRegistration.hpp"

#ifdef HAVE_NUMPY
# include "NumPy.hpp"
#endif


namespace
{

	template <typename ArrayType>
	struct VectorArrayFromPySequenceConverter 
	{

		VectorArrayFromPySequenceConverter() {
			using namespace boost;

			python::converter::registry::insert(&convertible, &construct, python::type_id<ArrayType>());
		}

		static void* convertible(PyObject* obj_ptr) {
			using namespace boost;

			if (!obj_ptr)
				return 0;

			if (!PyList_Check(obj_ptr) && !PyTuple_Check(obj_ptr))
				return 0;

			python::ssize_t num_rows = PySequence_Size(obj_ptr);
		
			for (python::ssize_t i = 0; i < num_rows; i++) {
				PyObject* row_ptr = PySequence_GetItem(obj_ptr, i);

				if (!PySequence_Check(row_ptr))
					return 0;

				if (PySequence_Size(row_ptr) != ssize_t(ArrayType::ValueType::Size))
					return 0;

				for (python::ssize_t j = 0; j < ssize_t(ArrayType::ValueType::Size); j++) 
					if (!python::extract<typename ArrayType::ValueType>(PySequence_GetItem(row_ptr, j)).check())
						return 0;
			}

			return obj_ptr;
		}

		static void construct(PyObject* obj_ptr, boost::python::converter::rvalue_from_python_stage1_data* data) {
			using namespace boost;
	
			typedef typename ArrayType::ValueType::ValueType ElemValueType;
		
			void* storage = ((python::converter::rvalue_from_python_storage<ArrayType>*)data)->storage.bytes;

			new (storage) ArrayType();

			ArrayType& va = *static_cast<ArrayType*>(storage);
			python::ssize_t num_rows = PySequence_Size(obj_ptr);

			for (python::ssize_t i = 0; i < num_rows; i++) {
				PyObject* row_ptr = PySequence_GetItem(obj_ptr, i);

				for (std::size_t j = 0; j < ArrayType::ValueType::Size; j++)
					va[i][j] = python::extract<ElemValueType>(PySequence_GetItem(row_ptr, j));
			}

			data->convertible = storage;
		}
	};

#ifdef HAVE_NUMPY
	template <typename ArrayType>
	struct VectorArrayFromNDArrayConverter 
	{

		VectorArrayFromNDArrayConverter() {
			using namespace boost;

			python::converter::registry::insert(&convertible, &construct, python::type_id<ArrayType>());
		}

		static void* convertible(PyObject* obj_ptr) {
			using namespace boost;
			using namespace CDPLPythonMath;

			if (!obj_ptr)
				return 0;

			PyArrayObject* arr = NumPy::castToNDArray(obj_ptr);

			if (!arr)
				return 0;

			if (!NumPy::checkDataType<typename ArrayType::ValueType::ValueType>(arr))
				return 0;

			npy_intp* dims = PyArray_DIMS(arr);

			if (NumPy::checkDim(arr, 2)) {
				if (std::size_t(dims[1]) == ArrayType::ValueType::Size) 
					return obj_ptr;
			} 

			if (NumPy::checkDim(arr, 1)) {
				if ((std::size_t(dims[0]) % ArrayType::ValueType::Size) == 0)
					return obj_ptr;
			}

			return 0;
		}

		static void construct(PyObject* obj_ptr, boost::python::converter::rvalue_from_python_stage1_data* data) {
			using namespace boost;
			using namespace CDPLPythonMath;

			typedef typename ArrayType::ValueType::ValueType ElemValueType;
		
			void* storage = ((python::converter::rvalue_from_python_storage<ArrayType>*)data)->storage.bytes;

			new (storage) ArrayType();

			ArrayType& va = *static_cast<ArrayType*>(storage);
			PyArrayObject* arr = reinterpret_cast<PyArrayObject*>(obj_ptr);
			npy_intp* dims = PyArray_DIMS(arr);

			if (NumPy::checkDim(arr, 2)) {
				va.resize(dims[0]);

				for (npy_intp i = 0; i < dims[0]; i++)
					for (std::size_t j = 0; j < ArrayType::ValueType::Size; j++)
						va[i][j] = *reinterpret_cast<ElemValueType*>(PyArray_GETPTR2(arr, i, j));

			} else {
				va.resize(dims[0] / ArrayType::ValueType::Size);

				for (npy_intp i = 0; i < dims[0]; i++)
					va[i / ArrayType::ValueType::Size][i % ArrayType::ValueType::Size] = *reinterpret_cast<ElemValueType*>(PyArray_GETPTR1(arr, i));
			}

			data->convertible = storage;
		}
	};
#endif
}


void CDPLPythonMath::registerFromPythonToVectorArrayConverters()
{
	using namespace CDPL;

	VectorArrayFromPySequenceConverter<Math::Vector2FArray>();
	VectorArrayFromPySequenceConverter<Math::Vector3FArray>();
	VectorArrayFromPySequenceConverter<Math::Vector2DArray>();
	VectorArrayFromPySequenceConverter<Math::Vector3DArray>();
	VectorArrayFromPySequenceConverter<Math::Vector2LArray>();
	VectorArrayFromPySequenceConverter<Math::Vector3LArray>();
	VectorArrayFromPySequenceConverter<Math::Vector2ULArray>();
	VectorArrayFromPySequenceConverter<Math::Vector3ULArray>();

#ifdef HAVE_NUMPY
	VectorArrayFromNDArrayConverter<Math::Vector2FArray>();
	VectorArrayFromNDArrayConverter<Math::Vector3FArray>();
	VectorArrayFromNDArrayConverter<Math::Vector2DArray>();
	VectorArrayFromNDArrayConverter<Math::Vector3DArray>();
	VectorArrayFromNDArrayConverter<Math::Vector2LArray>();
	VectorArrayFromNDArrayConverter<Math::Vector3LArray>();
	VectorArrayFromNDArrayConverter<Math::Vector2ULArray>();
	VectorArrayFromNDArrayConverter<Math::Vector3ULArray>();
#endif
}
