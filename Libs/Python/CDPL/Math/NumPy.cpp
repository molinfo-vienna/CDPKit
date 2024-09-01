/* 
 * NumPy.cpp 
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


#include <mutex>

#include <boost/python.hpp>

#include "CDPL/Base/Exceptions.hpp"

#define ENABLE_IMPORT_ARRAY_FUNCTION

#include "NumPy.hpp"


namespace
{

    bool numPyImported = false;

    void* checkNDArrayObject(PyObject* obj) 
    {
        if (PyArray_Check(obj))
            return obj;

        return 0;
    }

    void importNumPy()
    {
        if (_import_array() < 0) {
            PyErr_Print();
            return;
        }
        
        boost::python::converter::registry::insert(&checkNDArrayObject, boost::python::type_id<PyArrayObject>());
        numPyImported = true;
    }

    std::once_flag initOnceFlag;
} // namespace


namespace CDPLPythonMath
{
    
    namespace NumPy
    {

        void import()
        {
            std::call_once(initOnceFlag, &importNumPy);

            if (!numPyImported)
                throw CDPL::Base::OperationFailed("CDPL.Math: import of NumPy module failed");
        }

        PyArrayObject* castToNDArray(PyObject* obj) 
        {
            if (PyArray_Check(obj))
                return reinterpret_cast<PyArrayObject*>(obj);

            return 0;
        }

        bool checkDim(PyArrayObject* arr, std::size_t dim) 
        {
            return (std::size_t(PyArray_NDIM(arr)) == dim);
        }

        bool checkSize(PyArrayObject* arr, std::size_t size1) 
        {
            if (!checkDim(arr, 1))
                return false;

            return (std::size_t(PyArray_DIMS(arr)[0]) == size1);
        }

        bool checkSize(PyArrayObject* arr, std::size_t size1, std::size_t size2) 
        {
            if (!checkDim(arr, 2))
                return false;

            npy_intp* dims = PyArray_DIMS(arr);

            return (std::size_t(dims[0]) == size1 && std::size_t(dims[1]) == size2);
        }

        bool checkSize(PyArrayObject* arr, std::size_t size1, std::size_t size2, std::size_t size3) 
        {
            if (!checkDim(arr, 3))
                return false;

            npy_intp* dims = PyArray_DIMS(arr);

            return (std::size_t(dims[0]) == size1 && std::size_t(dims[1]) == size2 && std::size_t(dims[2]) == size3);
        }
    }
}
