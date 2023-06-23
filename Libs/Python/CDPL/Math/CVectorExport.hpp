/* 
 * CVectorExport.hpp 
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


#ifndef CDPL_PYTHON_MATH_CVECTOREXPORT_HPP
#define CDPL_PYTHON_MATH_CVECTOREXPORT_HPP

#include <boost/python.hpp>

#include "CDPL/Math/Vector.hpp"
#include "CDPL/Math/IO.hpp"

#include "Base/ObjectIdentityCheckVisitor.hpp"

#include "VectorExpression.hpp"
#include "VectorVisitor.hpp"
#include "AssignFunctionGeneratorVisitor.hpp"
#include "InitFunctionGeneratorVisitor.hpp"
#include "ClassExports.hpp"


namespace CDPLPythonMath
{

    template <typename VectorType>
    struct CVectorExport
    {

        CVectorExport(const char* name) {
            using namespace boost;
            using namespace CDPLPythonMath;

            typedef typename VectorType::ValueType ValueType;
            
            python::class_<VectorType>(name, python::no_init)
                .def(python::init<>(python::arg("self")))
                .def(python::init<const VectorType&>((python::arg("self"), python::arg("v"))))
                .def(python::init<const ValueType&>((python::arg("self"), python::arg("v"))))
                .def("clear", &VectorType::clear, (python::arg("self"), python::arg("v") = ValueType()))
                .def(CDPLPythonBase::ObjectIdentityCheckVisitor<VectorType>())
                .def(InitFunctionGeneratorVisitor<VectorType, ConstVectorExpression>("e"))
                .def(AssignFunctionGeneratorVisitor<VectorType, ConstVectorExpression>("e"))
                .def(ConstVectorVisitor<VectorType>())
                .def(VectorAssignAndSwapVisitor<VectorType>())
                .def(VectorNDArrayInitVisitor<VectorType>())
                .def(VectorNDArrayAssignVisitor<VectorType>())
                .def(VectorVisitor<VectorType>());
        }
    };
}

#endif // CDPL_PYTHON_MATH_CVECTOREXPORT_HPP
