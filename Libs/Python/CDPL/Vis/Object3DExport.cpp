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

        Object3DWrapper() = default;
        
        Object3DWrapper(const Object3D& obj): Object3D(obj) {}
    };
}


void CDPLPythonVis::exportObject3D()
{
    using namespace boost;
    using namespace CDPL;

    python::class_<Object3DWrapper, Object3DWrapper::SharedPointer, python::bases<Base::PropertyContainer>, boost::noncopyable>("Object3D", python::no_init)
        .def(python::init<>(python::arg("self")))
        .def(python::init<const Vis::Object3D&>((python::arg("self"), python::arg("obj"))))
        .def("assign", &Vis::Object3D::operator=, python::arg("self"), python::return_self<>())
        .def("clear", &Vis::Object3D::clear, python::arg("self"))
        .def("removeSubObject", static_cast<void (Vis::Object3D::*)(std::size_t)>(&Vis::Object3D::removeSubObject),
             (python::arg("self"), python::arg("idx")))
        .def("getSubObject", static_cast<Vis::Object3D& (Vis::Object3D::*)(std::size_t)>(&Vis::Object3D::getSubObject),
             (python::arg("self"), python::arg("idx")), python::return_internal_reference<1>())
        .def("getNumSubObjects", &Vis::Object3D::getNumSubObjects, python::arg("self"))
        .def("addSubObject", static_cast<Vis::Object3D& (Vis::Object3D::*)()>(&Vis::Object3D::addSubObject),
             python::arg("self"), python::return_internal_reference<1>())
        .def("addSubObject", static_cast<Vis::Object3D& (Vis::Object3D::*)(const Vis::Object3D::SharedPointer&)>(&Vis::Object3D::addSubObject),
             (python::arg("self"), python::arg("obj")), python::return_internal_reference<1>())
        .def(CDPLPythonBase::PropertyContainerSpecialFunctionsVisitor(true))
        .def("__delitem__", static_cast<void (Vis::Object3D::*)(std::size_t)>(&Vis::Object3D::removeSubObject),
             (python::arg("self"), python::arg("idx")))
        .def("__getitem__", static_cast<Vis::Object3D& (Vis::Object3D::*)(std::size_t)>(&Vis::Object3D::getSubObject),
             (python::arg("self"), python::arg("idx")), python::return_internal_reference<1>())
        .def("__len__", &Vis::Object3D::getNumSubObjects, python::arg("self"))
        .add_property("numSubObjects", &Vis::Object3D::getNumSubObjects)
        ;

    python::register_ptr_to_python<Vis::Object3D::SharedPointer>();
}
