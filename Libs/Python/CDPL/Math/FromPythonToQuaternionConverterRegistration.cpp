/* 
 * FromPythonToQuaternionConverterRegistration.cpp 
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
#include "CDPL/Math/Quaternion.hpp"
#include "CDPL/Math/QuaternionAdapter.hpp"

#include "ConverterRegistration.hpp"

#ifdef HAVE_NUMPY
# include "NumPy.hpp"
#endif


namespace
{

	template <typename QuaternionType>
	struct QuaternionFromPySequenceConverter 
	{

		QuaternionFromPySequenceConverter() {
			using namespace boost;

			python::converter::registry::insert(&convertible, &construct, python::type_id<QuaternionType>());
		}

		static void* convertible(PyObject* obj_ptr) {
			using namespace boost;

			if (!obj_ptr)
				return 0;

			if (!PyList_Check(obj_ptr) && !PyTuple_Check(obj_ptr))
				return 0;

			if (PySequence_Size(obj_ptr) != 4)
				return 0;

			for (std::size_t i = 0; i < 4; i++)
				if (!python::extract<typename QuaternionType::ValueType>(PySequence_GetItem(obj_ptr, i)).check())
					return 0;
			
			return obj_ptr;
		}

		static void construct(PyObject* obj_ptr, boost::python::converter::rvalue_from_python_stage1_data* data) {
			using namespace boost;

			void* storage = ((python::converter::rvalue_from_python_storage<QuaternionType>*)data)->storage.bytes;

			new (storage) QuaternionType();

			QuaternionType& quat = *static_cast<QuaternionType*>(storage);

			quat.getC1() = python::extract<typename QuaternionType::ValueType>(PySequence_GetItem(obj_ptr, 0));
			quat.getC2() = python::extract<typename QuaternionType::ValueType>(PySequence_GetItem(obj_ptr, 1));
			quat.getC3() = python::extract<typename QuaternionType::ValueType>(PySequence_GetItem(obj_ptr, 2));
			quat.getC4() = python::extract<typename QuaternionType::ValueType>(PySequence_GetItem(obj_ptr, 3));

			data->convertible = storage;
		}
	};

#ifdef HAVE_NUMPY
	template <typename QuaternionType>
	struct QuaternionFromNDArrayConverter 
	{

		QuaternionFromNDArrayConverter() {
			using namespace boost;

			python::converter::registry::insert(&convertible, &construct, python::type_id<QuaternionType>());
		}

		static void* convertible(PyObject* obj_ptr) {
			using namespace boost;
			using namespace CDPLPythonMath;

			if (!obj_ptr)
				return 0;

			PyArrayObject* arr = NumPy::castToNDArray(obj_ptr);

			if (!arr)
				return 0;

			if (!NumPy::checkSize(arr, 4))
				return 0;

			if (!NumPy::checkDataType<typename QuaternionType::ValueType>(arr))
				return 0;
			
			return obj_ptr;
		}

		static void construct(PyObject* obj_ptr, boost::python::converter::rvalue_from_python_stage1_data* data) {
			using namespace boost;
			using namespace CDPLPythonMath;
			using namespace CDPL;

			void* storage = ((python::converter::rvalue_from_python_storage<QuaternionType>*)data)->storage.bytes;

			new (storage) QuaternionType();

			QuaternionType& quat = *static_cast<QuaternionType*>(storage);
			Math::QuaternionVectorAdapter<QuaternionType> adapter(quat);

			NumPy::copyArray1(adapter, NumPy::castToNDArray(obj_ptr));

			data->convertible = storage;
		}
	};
#endif
}


void CDPLPythonMath::registerFromPythonToQuaternionConverters()
{
	using namespace CDPL;

	QuaternionFromPySequenceConverter<Math::FQuaternion>();
	QuaternionFromPySequenceConverter<Math::DQuaternion>();
	QuaternionFromPySequenceConverter<Math::LQuaternion>();
	QuaternionFromPySequenceConverter<Math::ULQuaternion>();

#ifdef HAVE_NUMPY
	QuaternionFromNDArrayConverter<Math::FQuaternion>();
	QuaternionFromNDArrayConverter<Math::DQuaternion>();
	QuaternionFromNDArrayConverter<Math::LQuaternion>();
	QuaternionFromNDArrayConverter<Math::ULQuaternion>();
#endif
}
