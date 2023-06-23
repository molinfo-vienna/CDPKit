/* 
 * VectorArrayFunctionExport.cpp 
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

#include "CDPL/Math/VectorArrayFunctions.hpp"

#include "FunctionExports.hpp"


namespace
{

    template <typename ArrayType, std::size_t Dim>
    struct VectorArrayFunctionExport
    {

        VectorArrayFunctionExport() {
            using namespace boost;
            using namespace CDPL;

            typedef typename ArrayType::ValueType::ValueType VectorValueType;
      
            python::def("transform", static_cast<void (*)(ArrayType&, const Math::CMatrix<VectorValueType, Dim, Dim>&)>(&Math::transform<VectorValueType, Dim, VectorValueType>),
                        (python::arg("va"), python::arg("xform")));
            python::def("transform", static_cast<void (*)(ArrayType&, const Math::CMatrix<VectorValueType, Dim + 1, Dim + 1>&)>(&Math::transform<VectorValueType, Dim, VectorValueType>),
                        (python::arg("va"), python::arg("xform")));
            python::def("calcCentroid", &Math::calcCentroid<VectorValueType, Dim, VectorValueType>,
                        (python::arg("va"), python::arg("ctr")));
            python::def("calcRMSD", &Math::calcRMSD<VectorValueType, Dim>,
                        (python::arg("va1"), python::arg("va2")));
            python::def("calcRMSD", &Math::calcRMSD<VectorValueType, Dim, VectorValueType>,
                        (python::arg("va1"), python::arg("va2"), python::arg("va1_xform")));
        }
    };
}


void CDPLPythonMath::exportVectorArrayFunctions()
{
    using namespace CDPL;
    
    VectorArrayFunctionExport<Math::Vector2FArray, 2>();
    VectorArrayFunctionExport<Math::Vector3FArray, 3>();

    VectorArrayFunctionExport<Math::Vector2DArray, 2>();
    VectorArrayFunctionExport<Math::Vector3DArray, 3>();

    VectorArrayFunctionExport<Math::Vector2LArray, 2>();
    VectorArrayFunctionExport<Math::Vector3LArray, 3>();

    VectorArrayFunctionExport<Math::Vector2ULArray, 2>();
    VectorArrayFunctionExport<Math::Vector3ULArray, 3>();
}
