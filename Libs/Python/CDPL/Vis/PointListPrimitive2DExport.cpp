/* 
 * PointListPrimitive2DExport.cpp 
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

#include "CDPL/Vis/PointListPrimitive2D.hpp"

#include "Base/CopyAssOp.hpp"

#include "ClassExports.hpp"


void CDPLPythonVis::exportPointListPrimitive2D()
{
    using namespace boost;
    using namespace CDPL;

    python::class_<Vis::PointListPrimitive2D, 
        python::bases<Vis::PointArray2D, Vis::GraphicsPrimitive2D> >("PointListPrimitive2D", python::no_init)
        .def(python::init<>(python::arg("self")))    
        .def(python::init<const Vis::PointListPrimitive2D&>((python::arg("self"), python::arg("prim"))))
        .def("assign", CDPLPythonBase::copyAssOp(&Vis::PointListPrimitive2D::operator=),
             (python::arg("self"),  python::arg("prim")),
             python::return_self<>())
        .def("setPen", &Vis::PointListPrimitive2D::setPen, (python::arg("self"), python::arg("pen")))
        .def("getPen", &Vis::PointListPrimitive2D::getPen, python::arg("self"), 
             python::return_internal_reference<1>())
        .add_property("pen", python::make_function(&Vis::PointListPrimitive2D::getPen, 
                                                   python::return_internal_reference<1>()),
                      &Vis::PointListPrimitive2D::setPen);
}
