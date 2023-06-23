/* 
 * FromPythonToGridConverterRegistration.cpp 
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
#include "CDPL/Math/Grid.hpp"

#include "ConverterRegistration.hpp"

#ifdef HAVE_NUMPY
# include "NumPy.hpp"
#endif


namespace
{

	template <typename GridType>
	struct GridFromPySequenceConverter 
	{

		GridFromPySequenceConverter() {
			using namespace boost;

			python::converter::registry::insert(&convertible, &construct, python::type_id<GridType>());
		}

		static void* convertible(PyObject* obj_ptr) {
			using namespace boost;

			if (!obj_ptr)
				return 0;

			if (!PyList_Check(obj_ptr) && !PyTuple_Check(obj_ptr))
				return 0;

			python::ssize_t num_xelems = PySequence_Size(obj_ptr);
			python::ssize_t num_yelems = 0;
			python::ssize_t num_zelems = 0;

			for (python::ssize_t i = 0; i < num_xelems; i++) {
				PyObject* yseq_ptr = PySequence_GetItem(obj_ptr, i);

				if (!PySequence_Check(yseq_ptr))
					return 0;

				if (i == 0) 
					num_yelems = PySequence_Size(yseq_ptr);

				else if (num_yelems != PySequence_Size(yseq_ptr))
					return 0;

				for (python::ssize_t j = 0; j < num_yelems; j++) {
					PyObject* zseq_ptr = PySequence_GetItem(yseq_ptr, j);

					if (!PySequence_Check(zseq_ptr))
						return 0;

					if (i == 0 && j == 0) 
						num_zelems = PySequence_Size(zseq_ptr);

					else if (num_zelems != PySequence_Size(zseq_ptr))
						return 0;

					for (python::ssize_t k = 0; k < num_zelems; k++)
						if (!python::extract<typename GridType::ValueType>(PySequence_GetItem(zseq_ptr, k)).check())
							return 0;
				}

			}

			return obj_ptr;
		}

		static void construct(PyObject* obj_ptr, boost::python::converter::rvalue_from_python_stage1_data* data) {
			using namespace boost;

			GridType grd;

			python::ssize_t num_xelems = PySequence_Size(obj_ptr);
			python::ssize_t num_yelems = 0;
			python::ssize_t num_zelems = 0;

			for (python::ssize_t i = 0; i < num_xelems; i++) {
				PyObject* yseq_ptr = PySequence_GetItem(obj_ptr, i);

				if (i == 0) 
					num_yelems = PySequence_Size(yseq_ptr);

				for (python::ssize_t j = 0; j < num_yelems; j++) {
					PyObject* zseq_ptr = PySequence_GetItem(yseq_ptr, j);

					if (i == 0 && j == 0) { 
						num_zelems = PySequence_Size(zseq_ptr);
						grd.resize(num_xelems, num_yelems, num_zelems);
					}

					for (python::ssize_t k = 0; k < num_zelems; k++)
						grd(i, j, k) = python::extract<typename GridType::ValueType>(PySequence_GetItem(zseq_ptr, k));
				}
			}

			void* storage = ((python::converter::rvalue_from_python_storage<GridType>*)data)->storage.bytes;

			new (storage) GridType();

			static_cast<GridType*>(storage)->swap(grd);

			data->convertible = storage;
		}
	};

#ifdef HAVE_NUMPY
	template <typename GridType>
	struct GridFromNDArrayConverter 
	{

		GridFromNDArrayConverter() {
			using namespace boost;

			python::converter::registry::insert(&convertible, &construct, python::type_id<GridType>());
		}

		static void* convertible(PyObject* obj_ptr) {
			using namespace boost;
			using namespace CDPLPythonMath;

			if (!obj_ptr)
				return 0;

			PyArrayObject* arr = NumPy::castToNDArray(obj_ptr);

			if (!arr)
				return 0;

			if (!NumPy::checkDim(arr, 3))
				return 0;

			if (!NumPy::checkDataType<typename GridType::ValueType>(arr))
				return 0;
			
			return obj_ptr;
		}

		static void construct(PyObject* obj_ptr, boost::python::converter::rvalue_from_python_stage1_data* data) {
			using namespace boost;
			using namespace CDPLPythonMath;

			void* storage = ((python::converter::rvalue_from_python_storage<GridType>*)data)->storage.bytes;

			new (storage) GridType();

			GridType& grd = *static_cast<GridType*>(storage);
			PyArrayObject* arr = reinterpret_cast<PyArrayObject*>(obj_ptr);

			NumPy::resizeTarget3(grd, arr);
			NumPy::copyArray3(grd, arr);

			data->convertible = storage;
		}
	};
#endif
}


void CDPLPythonMath::registerFromPythonToGridConverters()
{
	using namespace CDPL;

	GridFromPySequenceConverter<Math::FGrid>();
	GridFromPySequenceConverter<Math::DGrid>();

#ifdef HAVE_NUMPY	
	GridFromNDArrayConverter<Math::FGrid>();
	GridFromNDArrayConverter<Math::DGrid>();
#endif
}
