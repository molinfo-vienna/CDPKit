/* 
 * Object3DExport.cpp 
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


#include <memory>

#include <boost/python.hpp>

#include "CDPL/Vis/Object3D.hpp"

#include "Base/PropertyContainerVisitor.hpp"

#include "ClassExports.hpp"


namespace
{

    struct Object3DWrapper : CDPL::Vis::Object3D, boost::python::wrapper<CDPL::Vis::Object3D> 
    {

        typedef std::shared_ptr<Object3DWrapper> SharedPointer;
    };
}


void CDPLPythonVis::exportObject3D()
{
    using namespace boost;
    using namespace CDPL;

    python::class_<Object3DWrapper, Object3DWrapper::SharedPointer, python::bases<Base::PropertyContainer>, boost::noncopyable>("Object3D", python::no_init)
    .def(python::init<>(python::arg("self")))
    .def(CDPLPythonBase::PropertyContainerSpecialFunctionsVisitor());

    python::register_ptr_to_python<Vis::Object3D::SharedPointer>();
}
