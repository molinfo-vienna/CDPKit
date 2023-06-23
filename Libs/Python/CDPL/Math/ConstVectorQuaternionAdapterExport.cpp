/* 
 * ConstVectorQuaternionAdapterExport.cpp 
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

#include "CDPL/Math/VectorAdapter.hpp"
#include "CDPL/Math/Quaternion.hpp"
#include "CDPL/Math/VectorExpression.hpp"
#include "CDPL/Math/IO.hpp"

#include "Base/ObjectIdentityCheckVisitor.hpp"

#include "ExpressionAdapterWrapper.hpp"
#include "VectorExpression.hpp"
#include "QuaternionExpression.hpp"
#include "QuaternionVisitor.hpp"
#include "WrappedDataVisitor.hpp"
#include "ClassExports.hpp"


namespace
{

    template <typename ExpressionType>
    struct ConstVectorQuaternionAdapterExport
    {
    
        typedef CDPL::Math::VectorQuaternionAdapter<const ExpressionType> VectorAdapterType;
        typedef CDPLPythonMath::ExpressionAdapterWrapper<ExpressionType, VectorAdapterType> VectorAdapterWrapper;
        typedef typename VectorAdapterWrapper::ExpressionPointerType ExpressionPointerType;
        typedef typename VectorAdapterWrapper::SharedPointer WrapperPointerType;

        ConstVectorQuaternionAdapterExport(const char* name) {
            using namespace boost;
            using namespace CDPLPythonMath;
        
            python::class_<VectorAdapterWrapper, WrapperPointerType, boost::noncopyable>(name, python::no_init)
                .def(python::init<const VectorAdapterWrapper&>((python::arg("self"), python::arg("a"))))
                .def(python::init<const ExpressionPointerType&>((python::arg("self"), python::arg("e"))))
                .def(CDPLPythonBase::ObjectIdentityCheckVisitor<VectorAdapterType>())
                .def(ConstQuaternionVisitor<VectorAdapterType>("a"))
                .def(WrappedDataVisitor<VectorAdapterWrapper>());

            python::def("quat", &quat, python::arg("e"));
        }

        static WrapperPointerType quat(const ExpressionPointerType& e) {
            return WrapperPointerType(new VectorAdapterWrapper(e));
        }
    };
}


void CDPLPythonMath::exportConstVectorQuaternionAdapterTypes()
{
    ConstVectorQuaternionAdapterExport<ConstVectorExpression<float> >("ConstFVectorQuaternionAdapter");
    ConstVectorQuaternionAdapterExport<ConstVectorExpression<double> >("ConstDVectorQuaternionAdapter");
    ConstVectorQuaternionAdapterExport<ConstVectorExpression<long> >("ConstLVectorQuaternionAdapter");
    ConstVectorQuaternionAdapterExport<ConstVectorExpression<unsigned long> >("ConstULVectorQuaternionAdapter");
}
