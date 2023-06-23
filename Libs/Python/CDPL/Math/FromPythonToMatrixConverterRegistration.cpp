/* 
 * FromPythonToMatrixConverterRegistration.cpp 
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
#include "CDPL/Math/Matrix.hpp"

#include "ConverterRegistration.hpp"

#ifdef HAVE_NUMPY
# include "NumPy.hpp"
#endif


namespace
{

    template <typename MatrixType>
    struct MatrixFromPySequenceConverter 
    {

        MatrixFromPySequenceConverter() {
            using namespace boost;

            python::converter::registry::insert(&convertible, &construct, python::type_id<MatrixType>());
        }

        static void* convertible(PyObject* obj_ptr) {
            using namespace boost;

            if (!obj_ptr)
                return 0;

            if (!PyList_Check(obj_ptr) && !PyTuple_Check(obj_ptr))
                return 0;

            python::ssize_t num_rows = PySequence_Size(obj_ptr);
            python::ssize_t num_cols = 0;

            for (python::ssize_t i = 0; i < num_rows; i++) {
                PyObject* row_ptr = PySequence_GetItem(obj_ptr, i);

                if (!PySequence_Check(row_ptr))
                    return 0;

                if (i == 0) 
                    num_cols = PySequence_Size(row_ptr);

                else if (num_cols != PySequence_Size(row_ptr))
                    return 0;

                for (python::ssize_t j = 0; j < num_cols; j++) 
                    if (!python::extract<typename MatrixType::ValueType>(PySequence_GetItem(row_ptr, j)).check())
                        return 0;
            }

            return obj_ptr;
        }

        static void construct(PyObject* obj_ptr, boost::python::converter::rvalue_from_python_stage1_data* data) {
            using namespace boost;

            MatrixType mtx;

            python::ssize_t num_rows = PySequence_Size(obj_ptr);
            python::ssize_t num_cols = 0;

            for (python::ssize_t i = 0; i < num_rows; i++) {
                PyObject* row_ptr = PySequence_GetItem(obj_ptr, i);

                if (i == 0) {
                    num_cols = PySequence_Size(row_ptr);
                    mtx.resize(num_rows, num_cols);
                }

                for (python::ssize_t j = 0; j < num_cols; j++)
                    mtx(i, j) = python::extract<typename MatrixType::ValueType>(PySequence_GetItem(row_ptr, j));
            }

            void* storage = ((python::converter::rvalue_from_python_storage<MatrixType>*)data)->storage.bytes;

            new (storage) MatrixType();

            static_cast<MatrixType*>(storage)->swap(mtx);

            data->convertible = storage;
        }
    };

#ifdef HAVE_NUMPY
    template <typename MatrixType>
    struct MatrixFromNDArrayConverter 
    {

        MatrixFromNDArrayConverter() {
            using namespace boost;

            python::converter::registry::insert(&convertible, &construct, python::type_id<MatrixType>());
        }

        static void* convertible(PyObject* obj_ptr) {
            using namespace boost;
            using namespace CDPLPythonMath;

            if (!obj_ptr)
                return 0;

            PyArrayObject* arr = NumPy::castToNDArray(obj_ptr);

            if (!arr)
                return 0;

            if (!NumPy::checkDim(arr, 2))
                return 0;

            if (!NumPy::checkDataType<typename MatrixType::ValueType>(arr))
                return 0;
            
            return obj_ptr;
        }

        static void construct(PyObject* obj_ptr, boost::python::converter::rvalue_from_python_stage1_data* data) {
            using namespace boost;
            using namespace CDPLPythonMath;

            void* storage = ((python::converter::rvalue_from_python_storage<MatrixType>*)data)->storage.bytes;

            new (storage) MatrixType();

            MatrixType& mtx = *static_cast<MatrixType*>(storage);
            PyArrayObject* arr = reinterpret_cast<PyArrayObject*>(obj_ptr);

            NumPy::resizeTarget2(mtx, arr);
            NumPy::copyArray2(mtx, arr);

            data->convertible = storage;
        }
    };
#endif
}


void CDPLPythonMath::registerFromPythonToMatrixConverters()
{
    using namespace CDPL;

    MatrixFromPySequenceConverter<Math::FMatrix>();
    MatrixFromPySequenceConverter<Math::DMatrix>();
    MatrixFromPySequenceConverter<Math::LMatrix>();
    MatrixFromPySequenceConverter<Math::ULMatrix>();

#ifdef HAVE_NUMPY
    MatrixFromNDArrayConverter<Math::FMatrix>();
    MatrixFromNDArrayConverter<Math::DMatrix>();
    MatrixFromNDArrayConverter<Math::LMatrix>();
    MatrixFromNDArrayConverter<Math::ULMatrix>();
#endif
}
