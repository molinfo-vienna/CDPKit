/* 
 * EllipsePrimitive2DExport.cpp 
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

#include "CDPL/Vis/EllipsePrimitive2D.hpp"

#include "Base/CopyAssOp.hpp"

#include "ClassExports.hpp"


void CDPLPythonVis::exportEllipsePrimitive2D()
{
    using namespace boost;
    using namespace CDPL;

    python::class_<Vis::EllipsePrimitive2D, 
                   python::bases<Vis::GraphicsPrimitive2D> >("EllipsePrimitive2D", python::no_init)
        .def(python::init<>(python::arg("self")))  
          .def(python::init<const Math::Vector2D&, double, double>(
                 (python::arg("self"), python::arg("pos"), python::arg("width"), python::arg("height"))))  
        .def(python::init<const Vis::EllipsePrimitive2D&>((python::arg("self"), python::arg("prim"))))
        .def("assign", CDPLPythonBase::copyAssOp(&Vis::EllipsePrimitive2D::operator=),
             (python::arg("self"), python::arg("prim")),
             python::return_self<>())
        .def("setWidth", &Vis::EllipsePrimitive2D::setWidth, (python::arg("self"), python::arg("width")))
        .def("getWidth", &Vis::EllipsePrimitive2D::getWidth, python::arg("self"))
        .def("setHeight", &Vis::EllipsePrimitive2D::setHeight, (python::arg("self"), python::arg("height")))
        .def("getHeight", &Vis::EllipsePrimitive2D::getHeight, python::arg("self"))
        .def("setPosition", &Vis::EllipsePrimitive2D::setPosition, (python::arg("self"), python::arg("pos")))
        .def("getPosition", &Vis::EllipsePrimitive2D::getPosition, python::arg("self"), 
             python::return_internal_reference<1>())
        .def("setPen", &Vis::EllipsePrimitive2D::setPen, (python::arg("self"), python::arg("pen")))
        .def("getPen", &Vis::EllipsePrimitive2D::getPen, python::arg("self"), 
             python::return_internal_reference<1>())
        .def("setBrush", &Vis::EllipsePrimitive2D::setBrush, (python::arg("self"), python::arg("brush")))
        .def("getBrush", &Vis::EllipsePrimitive2D::getBrush, python::arg("self"), 
             python::return_internal_reference<1>())
        .add_property("width", &Vis::EllipsePrimitive2D::getWidth, &Vis::EllipsePrimitive2D::setWidth) 
        .add_property("height", &Vis::EllipsePrimitive2D::getHeight, &Vis::EllipsePrimitive2D::setHeight) 
        .add_property("position", python::make_function(&Vis::EllipsePrimitive2D::getPosition, 
                                                        python::return_internal_reference<1>()),
                      &Vis::EllipsePrimitive2D::setPosition)
        .add_property("pen", python::make_function(&Vis::EllipsePrimitive2D::getPen, 
                                                   python::return_internal_reference<1>()),
                      &Vis::EllipsePrimitive2D::setPen)
        .add_property("brush", python::make_function(&Vis::EllipsePrimitive2D::getBrush, 
                                                   python::return_internal_reference<1>()),
                      &Vis::EllipsePrimitive2D::setBrush);
}
