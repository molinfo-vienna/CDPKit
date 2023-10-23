/* 
 * Path2DConverterExport.cpp 
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

#include "CDPL/Vis/Path2DConverter.hpp"

#include "Base/ObjectIdentityCheckVisitor.hpp"

#include "ClassExports.hpp"


namespace
{

    struct Path2DConverterWrapper : CDPL::Vis::Path2DConverter, boost::python::wrapper<CDPL::Vis::Path2DConverter>
    {

        void moveTo(double x, double y)
        {
            this->get_override("moveTo")(x, y);
        }

        void arcTo(double cx, double cy, double rx, double ry, double start_ang, double sweep)
        {
            this->get_override("arcTo")(cx, cy, rx, ry, start_ang, sweep);
        }

        void lineTo(double x, double y)
        {
            this->get_override("lineTo")(x, y);
        }

        void closePath()
        {
            this->get_override("closePath")();
        }
    };
}


void CDPLPythonVis::exportPath2DConverter()
{
    using namespace boost;
    using namespace CDPL;

    python::class_<Path2DConverterWrapper, boost::noncopyable>("Path2DConverter", python::no_init)
        .def(python::init<>(python::arg("self")))
        .def(CDPLPythonBase::ObjectIdentityCheckVisitor<Vis::Path2DConverter>())
        .def("moveTo", python::pure_virtual(&Vis::Path2DConverter::moveTo),
             (python::arg("self"), python::arg("x"), python::arg("y")))
        .def("arcTo", python::pure_virtual(&Vis::Path2DConverter::arcTo),
             (python::arg("self"), python::arg("cx"), python::arg("cy"), python::arg("rx"),
              python::arg("ry"), python::arg("start_ang"), python::arg("sweep")))
        .def("lineTo", python::pure_virtual(&Vis::Path2DConverter::lineTo),
             (python::arg("self"), python::arg("x"), python::arg("y")))
        .def("closePath", &Vis::Path2DConverter::closePath, python::arg("self"));
}
