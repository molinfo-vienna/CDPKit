/* 
 * FromPythonToCVectorConverterRegistration.cpp 
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
#include <boost/python/ssize_t.hpp>

#include "CDPL/Config.hpp"
#include "CDPL/Math/Vector.hpp"

#include "ConverterRegistration.hpp"

#ifdef HAVE_NUMPY
# include "NumPy.hpp"
#endif


namespace
{

	template <typename VectorType>
	struct CVectorFromPySequenceConverter 
	{

		CVectorFromPySequenceConverter() {
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

			if (size != python::ssize_t(VectorType::Size))
				return 0;

			for (python::ssize_t i = 0; i < size; i++)
				if (!python::extract<typename VectorType::ValueType>(PySequence_GetItem(obj_ptr, i)).check())
					return 0;
			
			return obj_ptr;
		}

		static void construct(PyObject* obj_ptr, boost::python::converter::rvalue_from_python_stage1_data* data) {
			using namespace boost;

			void* storage = ((python::converter::rvalue_from_python_storage<VectorType>*)data)->storage.bytes;

			new (storage) VectorType();

			VectorType& vec = *static_cast<VectorType*>(storage);
			python::ssize_t size = PySequence_Size(obj_ptr);

			for (python::ssize_t i = 0; i < size; i++)
				vec(i) = python::extract<typename VectorType::ValueType>(PySequence_GetItem(obj_ptr, i));

			data->convertible = storage;
		}
	};

#ifdef HAVE_NUMPY
	template <typename VectorType>
	struct CVectorFromNDArrayConverter 
	{

		CVectorFromNDArrayConverter() {
			using namespace boost;

			python::converter::registry::insert(&convertible, &construct, python::type_id<VectorType>());
		}

		static void* convertible(PyObject* obj_ptr) {
			using namespace boost;
			using namespace CDPLPythonMath;

			if (!obj_ptr)
				return 0;

			PyArrayObject* arr = NumPy::castToNDArray(obj_ptr);

			if (!arr)
				return 0;

			if (!NumPy::checkSize(arr, VectorType::Size))
				return 0;

			if (!NumPy::checkDataType<typename VectorType::ValueType>(arr))
				return 0;
			
			return obj_ptr;
		}

		static void construct(PyObject* obj_ptr, boost::python::converter::rvalue_from_python_stage1_data* data) {
			using namespace boost;
			using namespace CDPLPythonMath;

			void* storage = ((python::converter::rvalue_from_python_storage<VectorType>*)data)->storage.bytes;

			new (storage) VectorType();

			VectorType& vec = *static_cast<VectorType*>(storage);

			NumPy::copyArray1(vec, NumPy::castToNDArray(obj_ptr));

			data->convertible = storage;
		}
	};
#endif
}


void CDPLPythonMath::registerFromPythonToCVectorConverters()
{
	using namespace CDPL;

	CVectorFromPySequenceConverter<Math::Vector2F>();
	CVectorFromPySequenceConverter<Math::Vector3F>();
	CVectorFromPySequenceConverter<Math::Vector4F>();
	CVectorFromPySequenceConverter<Math::Vector2D>();
	CVectorFromPySequenceConverter<Math::Vector3D>();
	CVectorFromPySequenceConverter<Math::Vector4D>();
	CVectorFromPySequenceConverter<Math::Vector2L>();
	CVectorFromPySequenceConverter<Math::Vector3L>();
	CVectorFromPySequenceConverter<Math::Vector4L>();
	CVectorFromPySequenceConverter<Math::Vector2UL>();
	CVectorFromPySequenceConverter<Math::Vector3UL>();
	CVectorFromPySequenceConverter<Math::Vector4UL>();

#ifdef HAVE_NUMPY
	CVectorFromNDArrayConverter<Math::Vector2F>();
	CVectorFromNDArrayConverter<Math::Vector3F>();
	CVectorFromNDArrayConverter<Math::Vector4F>();
	CVectorFromNDArrayConverter<Math::Vector2D>();
	CVectorFromNDArrayConverter<Math::Vector3D>();
	CVectorFromNDArrayConverter<Math::Vector4D>();
	CVectorFromNDArrayConverter<Math::Vector2L>();
	CVectorFromNDArrayConverter<Math::Vector3L>();
	CVectorFromNDArrayConverter<Math::Vector4L>();
	CVectorFromNDArrayConverter<Math::Vector2UL>();
	CVectorFromNDArrayConverter<Math::Vector3UL>();
	CVectorFromNDArrayConverter<Math::Vector4UL>();
#endif
}
