/* 
 * LinePrimitive2DExport.cpp 
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

#include "CDPL/Vis/LinePrimitive2D.hpp"

#include "Base/CopyAssOp.hpp"

#include "ClassExports.hpp"


void CDPLPythonVis::exportLinePrimitive2D()
{
    using namespace boost;
    using namespace CDPL;

    python::class_<Vis::LinePrimitive2D, 
        python::bases<Vis::Line2D, Vis::GraphicsPrimitive2D> >("LinePrimitive2D", python::no_init)
        .def(python::init<>(python::arg("self"))) 
        .def(python::init<const Vis::LinePrimitive2D&>((python::arg("self"), python::arg("prim")))) 
        .def(python::init<const Vis::Line2D&>((python::arg("self"), python::arg("line"))))
        .def(python::init<const Math::Vector2D&, const Math::Vector2D&>((python::arg("self"), 
                                                                         python::arg("beg"), 
                                                                         python::arg("end"))))    
        .def("assign", CDPLPythonBase::copyAssOp<Vis::LinePrimitive2D>(),
             (python::arg("self"), python::arg("prim")), 
             python::return_self<>())
        .def("setPen", &Vis::LinePrimitive2D::setPen, (python::arg("self"), python::arg("pen")))
        .def("getPen", &Vis::LinePrimitive2D::getPen, python::arg("self"), 
             python::return_internal_reference<1>())
        .add_property("pen", python::make_function(&Vis::LinePrimitive2D::getPen, 
                                                   python::return_internal_reference<1>()),
                      &Vis::LinePrimitive2D::setPen);
}
