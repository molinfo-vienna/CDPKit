/* 
 * TriangularMatrixAdapterExport.hpp 
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


#ifndef CDPL_PYTHON_MATH_TRIANGULARMATRIXADAPTEREXPORT_HPP
#define CDPL_PYTHON_MATH_TRIANGULARMATRIXADAPTEREXPORT_HPP

#include <boost/python.hpp>

#include "CDPL/Math/MatrixAdapter.hpp"
#include "CDPL/Math/IO.hpp"

#include "Base/ObjectIdentityCheckVisitor.hpp"

#include "ExpressionAdapterWrapper.hpp"
#include "MatrixExpression.hpp"
#include "MatrixVisitor.hpp"
#include "WrappedDataVisitor.hpp"
#include "ClassExports.hpp"


namespace CDPLPythonMath
{

    template <typename ExpressionType, typename TriangType>
    struct TriangularAdapterExport
    {
    
        typedef CDPL::Math::TriangularAdapter<const ExpressionType, TriangType> TriangularAdapterType;
        typedef CDPLPythonMath::ExpressionAdapterWrapper<ExpressionType, TriangularAdapterType> TriangularAdapterWrapper;
        typedef typename TriangularAdapterWrapper::ExpressionPointerType ExpressionPointerType;
        typedef typename TriangularAdapterWrapper::SharedPointer WrapperPointerType;

        TriangularAdapterExport(const char* name) {
            using namespace boost;
            using namespace CDPLPythonMath;
    
            python::class_<TriangularAdapterWrapper, WrapperPointerType, boost::noncopyable>(name, python::no_init)
                .def(python::init<const TriangularAdapterWrapper&>((python::arg("self"), python::arg("a"))))
                .def(python::init<const ExpressionPointerType&>((python::arg("self"), python::arg("e"))))
                .def(CDPLPythonBase::ObjectIdentityCheckVisitor<TriangularAdapterType>())
                .def(ConstMatrixVisitor<TriangularAdapterType>("a"))
                .def(WrappedDataVisitor<TriangularAdapterWrapper>());

            python::def("triang", &triang, (python::arg("e"), python::arg("type")));
        }

        static WrapperPointerType triang(const ExpressionPointerType& e, const TriangType&) {
            return WrapperPointerType(new TriangularAdapterWrapper(e));
        }
    };
}

#endif // CDPL_PYTHON_MATH_TRIANGULARMATRIXADAPTEREXPORT_HPP

