/* 
 * TextBlockPrimitive2DExport.cpp 
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

#include "CDPL/Vis/TextBlockPrimitive2D.hpp"
#include "CDPL/Vis/FontMetrics.hpp"

#include "Base/CopyAssOp.hpp"

#include "ClassExports.hpp"


void CDPLPythonVis::exportTextBlockPrimitive2D()
{
    using namespace boost;
    using namespace CDPL;

    void (Vis::TextBlockPrimitive2D::*setPositionFunc1)(const Math::Vector2D&) = &Vis::TextBlockPrimitive2D::setPosition;
    void (Vis::TextBlockPrimitive2D::*setPositionFunc2)(double, double) = &Vis::TextBlockPrimitive2D::setPosition;

    python::class_<Vis::TextBlockPrimitive2D, Vis::TextBlockPrimitive2D::SharedPointer,
        python::bases<Vis::GraphicsPrimitive2D> >("TextBlockPrimitive2D", python::no_init)
        .def(python::init<>(python::arg("self")))    
        .def(python::init<const Vis::TextBlockPrimitive2D&>((python::arg("self"), python::arg("prim"))))
        .def("assign", CDPLPythonBase::copyAssOp<Vis::TextBlockPrimitive2D>(),
             (python::arg("self"), python::arg("prim")), 
             python::return_self<>())
        .def("setText", &Vis::TextBlockPrimitive2D::setText, (python::arg("self"), python::arg("text")))
        .def("getText", &Vis::TextBlockPrimitive2D::getText, python::arg("self"), 
             python::return_value_policy<python::copy_const_reference>())
        .def("setPosition", setPositionFunc1, (python::arg("self"), python::arg("pos")))
        .def("setPosition", setPositionFunc2, (python::arg("self"), python::arg("x"), python::arg("y")))
        .def("getPosition", &Vis::TextBlockPrimitive2D::getPosition, python::arg("self"), 
             python::return_value_policy<python::copy_const_reference>())
        .def("setPen", &Vis::TextBlockPrimitive2D::setPen, (python::arg("self"), python::arg("pen")))
        .def("getPen", &Vis::TextBlockPrimitive2D::getPen, python::arg("self"), 
             python::return_internal_reference<1>())
        .def("setFont", &Vis::TextBlockPrimitive2D::setFont, (python::arg("self"), python::arg("font")))
        .def("getFont", &Vis::TextBlockPrimitive2D::getFont, python::arg("self"), 
             python::return_internal_reference<1>())
        .def("setAlignment", &Vis::TextBlockPrimitive2D::setAlignment, (python::arg("self"), python::arg("alignment")))
        .def("getAlignment", &Vis::TextBlockPrimitive2D::getAlignment, python::arg("self"))
        .def("setLineSpacing", &Vis::TextBlockPrimitive2D::setLineSpacing, (python::arg("self"), python::arg("spacing")))
        .def("getLineSpacing", &Vis::TextBlockPrimitive2D::getLineSpacing, python::arg("self"))
        .def("layout", &Vis::TextBlockPrimitive2D::layout, (python::arg("self"), python::arg("font_metrics")))
        .add_property("text", python::make_function(&Vis::TextBlockPrimitive2D::getText, 
                                                   python::return_value_policy<python::copy_const_reference>()),
                      &Vis::TextBlockPrimitive2D::setText)
        .add_property("position", python::make_function(&Vis::TextBlockPrimitive2D::getPosition, 
                                                   python::return_value_policy<python::copy_const_reference>()),
                      setPositionFunc1)
        .add_property("pen", python::make_function(&Vis::TextBlockPrimitive2D::getPen, 
                                                   python::return_internal_reference<1>()),
                      &Vis::TextBlockPrimitive2D::setPen)
        .add_property("font", python::make_function(&Vis::TextBlockPrimitive2D::getFont, 
                                                   python::return_internal_reference<1>()),
                      &Vis::TextBlockPrimitive2D::setFont)
        .add_property("alignment", &Vis::TextBlockPrimitive2D::getAlignment, &Vis::TextBlockPrimitive2D::setAlignment)
        .add_property("lineSpacing", &Vis::TextBlockPrimitive2D::getLineSpacing, &Vis::TextBlockPrimitive2D::setLineSpacing);
}
