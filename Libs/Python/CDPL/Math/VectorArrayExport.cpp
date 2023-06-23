/* 
 * VectorArrayExport.cpp 
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

#include "CDPL/Config.hpp"
#include "CDPL/Math/VectorArray.hpp"

#include "Util/ArrayVisitor.hpp"

#include "ClassExports.hpp"

#ifdef HAVE_NUMPY
# include "NumPy.hpp"
#endif


namespace
{

	template <typename ArrayType, std::size_t Dim>
	struct VectorArrayExport
	{

		VectorArrayExport(const char* name) {
			using namespace boost;
			using namespace CDPL;

			python::class_<ArrayType, typename ArrayType::SharedPointer>(name, python::no_init)
				.def(python::init<>(python::arg("self")))
				.def(python::init<const ArrayType&>((python::arg("self"), python::arg("array"))))
				.def(CDPLPythonUtil::ArrayVisitor<ArrayType, 
					 python::return_internal_reference<>, python::default_call_policies, 
					 python::default_call_policies, python::default_call_policies>())
				.def("__eq__", &ArrayType::operator==, (python::arg("self"), python::arg("array")))
				.def("__ne__", &ArrayType::operator!=, (python::arg("self"), python::arg("array")))
#ifdef HAVE_NUMPY
				.def("__init__", python::make_constructor(&construct, python::default_call_policies(), (python::arg("a"))))
				.def("toArray", &toArray, (python::arg("self"), python::arg("as_vec")))
				.def("assign", &assign, (python::arg("self"), python::arg("a")))
#endif
				;
		}
#ifdef HAVE_NUMPY
		static boost::python::object toArray(const ArrayType& va, bool as_vec) {
			using namespace boost;
			using namespace CDPLPythonMath;

			if (!NumPy::available())
				python::object();			

			typedef typename ArrayType::ValueType::ValueType ValueType;

			if (as_vec) {
				npy_intp shape[] = { npy_intp(va.getSize() * Dim) };
				PyObject* array = PyArray_SimpleNew(1, shape, NumPy::DataTypeNum<ValueType>::Value);

				if (array) {
					ValueType* data = static_cast<ValueType*>(PyArray_GETPTR1(reinterpret_cast<PyArrayObject*>(array), 0));

					for (std::size_t i = 0, size = va.getSize(); i < size; i++) 
						for (std::size_t j = 0; j < Dim; j++, data++) 
						*data = va[i][j];

					return python::object(python::handle<>(array));
				}

			} else {
				npy_intp shape[] = { npy_intp(va.getSize()), npy_intp(Dim) };
				PyObject* py_obj = PyArray_SimpleNew(2, shape, NumPy::DataTypeNum<ValueType>::Value);
				PyArrayObject* array = reinterpret_cast<PyArrayObject*>(py_obj);

				if (array) {
					for (std::size_t i = 0, size = va.getSize(); i < size; i++)
						for (std::size_t j = 0; j < Dim; j++)
							*static_cast<ValueType*>(PyArray_GETPTR2(array, i, j)) = va[i][j];

					return python::object(python::handle<>(py_obj));
				}
			}

			return python::object();			
		}

		static void assign(ArrayType& va, PyArrayObject* arr) {
			using namespace CDPL;
			using namespace boost;
			using namespace CDPLPythonMath;

			typedef typename ArrayType::ValueType::ValueType ElemValueType;

			if (!NumPy::checkDataType<ElemValueType>(arr)) {
				PyErr_SetString(PyExc_TypeError, "VectorArray: NumPy.NDArray of incompatible type");

				python::throw_error_already_set();
			}

			if (NumPy::checkDim(arr, 2)) {
				npy_intp* dims = PyArray_DIMS(arr);

				if (std::size_t(dims[1]) != ArrayType::ValueType::Size) {
					PyErr_SetString(PyExc_ValueError, "VectorArray: NumPy.NDArray dimension error");

					python::throw_error_already_set();
				}

				va.resize(dims[0]);

				for (npy_intp i = 0; i < dims[0]; i++)
					for (std::size_t j = 0; j < ArrayType::ValueType::Size; j++)
						va[i][j] = *reinterpret_cast<ElemValueType*>(PyArray_GETPTR2(arr, i, j));

			} else if (NumPy::checkDim(arr, 1)) {
				npy_intp* dims = PyArray_DIMS(arr);
	
				if ((std::size_t(dims[0]) % ArrayType::ValueType::Size) != 0) {
					PyErr_SetString(PyExc_ValueError, "VectorArray: NumPy.NDArray dimension error");

					python::throw_error_already_set();
				}

				va.resize(dims[0] / ArrayType::ValueType::Size);

				for (npy_intp i = 0; i < dims[0]; i++)
					va[i / ArrayType::ValueType::Size][i % ArrayType::ValueType::Size] = *reinterpret_cast<ElemValueType*>(PyArray_GETPTR1(arr, i));

			} else {
				PyErr_SetString(PyExc_ValueError, "VectorArray: NumPy.NDArray dimension error");
				
				python::throw_error_already_set();
			}
		}

		static ArrayType* construct(PyArrayObject* arr) {
			using namespace CDPL;
			using namespace boost;
			using namespace CDPLPythonMath;

			typedef typename ArrayType::ValueType::ValueType ElemValueType;

			if (!NumPy::checkDataType<ElemValueType>(arr)) {
				PyErr_SetString(PyExc_TypeError, "VectorArray: NumPy.NDArray of incompatible type");

				python::throw_error_already_set();
			}

			if (NumPy::checkDim(arr, 2)) {
				npy_intp* dims = PyArray_DIMS(arr);

				if (std::size_t(dims[1]) != ArrayType::ValueType::Size) {
					PyErr_SetString(PyExc_ValueError, "VectorArray: NumPy.NDArray dimension error");

					python::throw_error_already_set();
				}

				std::auto_ptr<ArrayType> va_ptr(new ArrayType());
				ArrayType& va = *va_ptr;

				va.resize(dims[0]);

				for (npy_intp i = 0; i < dims[0]; i++)
					for (std::size_t j = 0; j < ArrayType::ValueType::Size; j++)
						va[i][j] = *reinterpret_cast<ElemValueType*>(PyArray_GETPTR2(arr, i, j));

				return va_ptr.release();
			} 

			if (NumPy::checkDim(arr, 1)) {
				npy_intp* dims = PyArray_DIMS(arr);
	
				if ((std::size_t(dims[0]) % ArrayType::ValueType::Size) != 0) {
					PyErr_SetString(PyExc_ValueError, "VectorArray: NumPy.NDArray dimension error");

					python::throw_error_already_set();
				}

				std::auto_ptr<ArrayType> va_ptr(new ArrayType());
				ArrayType& va = *va_ptr;

				va.resize(dims[0] / ArrayType::ValueType::Size);

				for (npy_intp i = 0; i < dims[0]; i++)
					va[i / ArrayType::ValueType::Size][i % ArrayType::ValueType::Size] = *reinterpret_cast<ElemValueType*>(PyArray_GETPTR1(arr, i));

				return va_ptr.release();
			} 

			PyErr_SetString(PyExc_ValueError, "VectorArray: NumPy.NDArray dimension error");

			python::throw_error_already_set();

			return 0;
		}
#endif
	};
}


void CDPLPythonMath::exportVectorArrayTypes()
{
	using namespace CDPL;
	
	VectorArrayExport<Math::Vector2FArray, 2>("Vector2FArray");
	VectorArrayExport<Math::Vector3FArray, 3>("Vector3FArray");

	VectorArrayExport<Math::Vector2DArray, 2>("Vector2DArray");
	VectorArrayExport<Math::Vector3DArray, 3>("Vector3DArray");

	VectorArrayExport<Math::Vector2LArray, 2>("Vector2LArray");
	VectorArrayExport<Math::Vector3LArray, 3>("Vector3LArray");

	VectorArrayExport<Math::Vector2ULArray, 2>("Vector2ULArray");
	VectorArrayExport<Math::Vector3ULArray, 3>("Vector3ULArray");
}
