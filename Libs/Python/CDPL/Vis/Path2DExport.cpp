/* 
 * Path2DExport.cpp 
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

#include "CDPL/Vis/Path2D.hpp"
#include "CDPL/Vis/Path2DConverter.hpp"
#include "CDPL/Vis/Rectangle2D.hpp"

#include "Base/ObjectIdentityCheckVisitor.hpp"

#include "ClassExports.hpp"


namespace
{

    bool isNonEmpty(const CDPL::Vis::Path2D& path)
    {
        return !path.isEmpty();
    }
}


void CDPLPythonVis::exportPath2D()
{
    using namespace boost;
    using namespace CDPL;

    python::class_<Vis::Path2D> path_class("Path2D", python::no_init);
    python::scope scope = path_class;

    python::enum_<Vis::Path2D::FillRule>("FillRule")
        .value("EVEN_ODD", Vis::Path2D::EVEN_ODD)
        .value("WINDING", Vis::Path2D::WINDING)
        .export_values();
    
    path_class
        .def(python::init<>(python::arg("self")))
        .def(python::init<const Vis::Path2D&>((python::arg("self"), python::arg("path"))))   
        .def(CDPLPythonBase::ObjectIdentityCheckVisitor<Vis::Path2D>())    
        .def("assign", &Vis::Path2D::operator=, (python::arg("self"), python::arg("path")),
             python::return_self<>())
        .def("isEmpty", &Vis::Path2D::isEmpty, python::arg("self"))
        .def("hasDrawingElements", &Vis::Path2D::hasDrawingElements, python::arg("self"))
        .def("clear", &Vis::Path2D::clear, python::arg("self"))
        .def("setFillRule", &Vis::Path2D::setFillRule, (python::arg("self"), python::arg("rule")))
        .def("getFillRule", &Vis::Path2D::getFillRule, python::arg("self"))
        .def("moveTo", static_cast<void (Vis::Path2D::*)(double, double)>(&Vis::Path2D::moveTo),
             (python::arg("self"), python::arg("x"), python::arg("y")))
        .def("moveTo", static_cast<void (Vis::Path2D::*)(const Math::Vector2D&)>(&Vis::Path2D::moveTo)
             , (python::arg("self"), python::arg("pos")))
        .def("arc", static_cast<void (Vis::Path2D::*)(double, double, double, double, double, double)>(&Vis::Path2D::arc),
             (python::arg("self"), python::arg("cx"), python::arg("cy"), python::arg("rx"),
              python::arg("ry"), python::arg("start_ang"), python::arg("sweep")))
        .def("arc", static_cast<void (Vis::Path2D::*)(const Math::Vector2D&, double, double, double, double)>(&Vis::Path2D::arc),
             (python::arg("self"), python::arg("ctr"), python::arg("rx"), python::arg("ry"),
              python::arg("start_ang"), python::arg("sweep")))
        .def("arcTo", static_cast<void (Vis::Path2D::*)(double, double, double, double, double, double)>(&Vis::Path2D::arcTo),
             (python::arg("self"), python::arg("cx"), python::arg("cy"), python::arg("rx"),
              python::arg("ry"), python::arg("start_ang"), python::arg("sweep")))
        .def("arcTo", static_cast<void (Vis::Path2D::*)(const Math::Vector2D&, double, double, double, double)>(&Vis::Path2D::arcTo),
             (python::arg("self"), python::arg("ctr"), python::arg("rx"), python::arg("ry"),
              python::arg("start_ang"), python::arg("sweep")))
        .def("lineTo", static_cast<void (Vis::Path2D::*)(double, double)>(&Vis::Path2D::lineTo),
             (python::arg("self"), python::arg("x"), python::arg("y")))
        .def("lineTo", static_cast<void (Vis::Path2D::*)(const Math::Vector2D&)>(&Vis::Path2D::lineTo),
             (python::arg("self"), python::arg("pos")))
        .def("closePath", &Vis::Path2D::closePath, python::arg("self"))
        .def("getBounds", &Vis::Path2D::getBounds, (python::arg("self"), python::arg("bounds")))
        .def("convert", &Vis::Path2D::convert, (python::arg("self"), python::arg("conv")))
        .def("addEllipse", static_cast<void (Vis::Path2D::*)(double, double, double, double)>(&Vis::Path2D::addEllipse),
             (python::arg("self"), python::arg("x"), python::arg("y"), python::arg("width"), python::arg("height")))
        .def("addEllipse", static_cast<void (Vis::Path2D::*)(const Math::Vector2D&, double, double)>(&Vis::Path2D::addEllipse),
             (python::arg("self"), python::arg("pos"), python::arg("width"), python::arg("height")))
        .def("addRectangle", static_cast<void (Vis::Path2D::*)(double, double, double, double)>(&Vis::Path2D::addRectangle),
             (python::arg("self"), python::arg("x"), python::arg("y"), python::arg("width"), python::arg("height")))
        .def("addRectangle", static_cast<void (Vis::Path2D::*)(const Math::Vector2D&, double, double)>(&Vis::Path2D::addRectangle),
             (python::arg("self"), python::arg("pos"), python::arg("width"), python::arg("height")))
        .def("__iadd__", &Vis::Path2D::operator+=, (python::arg("self"), python::arg("path")),
             python::return_self<>())
        .def("__eq__", &Vis::Path2D::operator==, (python::arg("self"), python::arg("path")))
        .def("__ne__", &Vis::Path2D::operator!=, (python::arg("self"), python::arg("path")))
        .def("__bool__", &isNonEmpty, python::arg("self"))
        .add_property("empty", &Vis::Path2D::isEmpty)
        .add_property("hasDrawingElem", &Vis::Path2D::hasDrawingElements)
        .add_property("fillRule", &Vis::Path2D::getFillRule, &Vis::Path2D::setFillRule);
}
