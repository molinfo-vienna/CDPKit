/* 
 * BrushExport.cpp 
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



#include <sstream>
#include <iomanip>

#include <boost/python.hpp>

#include "CDPL/Vis/Brush.hpp"

#include "Base/ObjectIdentityCheckVisitor.hpp"
#include "Base/CopyAssOp.hpp"

#include "ClassExports.hpp"


namespace
{

    const char* toString(CDPL::Vis::Brush::Style style)
    {
        using namespace CDPL;
        
        switch (style) {

            case Vis::Brush::NO_PATTERN:
              return "NO_PATTERN";

            case Vis::Brush::SOLID_PATTERN:
                return "SOLID_PATTERN";

            case Vis::Brush::DENSE1_PATTERN:
                return "DENSE1_PATTERN";

            case Vis::Brush::DENSE2_PATTERN:
                return "DENSE2_PATTERN";

            case Vis::Brush::DENSE3_PATTERN:
                return "DENSE3_PATTERN";

            case Vis::Brush::DENSE4_PATTERN:
                return "DENSE4_PATTERN";

            case Vis::Brush::DENSE5_PATTERN:
                return "DENSE5_PATTERN";

            case Vis::Brush::DENSE6_PATTERN:
                return "DENSE6_PATTERN";

            case Vis::Brush::DENSE7_PATTERN:
                return "DENSE7_PATTERN";

            case Vis::Brush::H_PATTERN:
                return "H_PATTERN";

            case Vis::Brush::V_PATTERN:
                return "V_PATTERN";

            case Vis::Brush::CROSS_PATTERN:
                return "CROSS_PATTERN";

            case Vis::Brush::LEFT_DIAG_PATTERN:
                return "LEFT_DIAG_PATTERN";

            case Vis::Brush::RIGHT_DIAG_PATTERN:
                return "RIGHT_DIAG_PATTERN";

            case Vis::Brush::DIAG_CROSS_PATTERN:
                return "DIAG_CROSS_PATTERN";
                
            default:
                return "?";
        }
    }
    
    std::string toString(const CDPL::Vis::Color& col)
    {
        std::ostringstream oss;

        oss << "Color(";
        
        if (col == CDPL::Vis::Color())
            oss << ')';
        
        else {
            oss << "r=" << col.getRed() << ", g=" << col.getGreen() << ", b=" << col.getBlue();

            if (col.getAlpha() != 1.0)
                oss << ", a=" << col.getAlpha();

            oss << ')';
        }
        
        return oss.str();
    }

    std::string brushToString(const CDPL::Vis::Brush& brush)
    {
        std::ostringstream oss;

        oss << "CDPL.Vis.Brush(";
        
        if (brush == CDPL::Vis::Brush())
            oss << ')';
        
        else {
            oss << "color=" << toString(brush.getColor()) << ", style=" << toString(brush.getStyle()) << ')';
        }
        
        return oss.str();
    }
}


void CDPLPythonVis::exportBrush()
{
    using namespace boost;
    using namespace CDPL;

    python::class_<Vis::Brush> brush_class("Brush", python::no_init);
    python::scope scope = brush_class;

    python::enum_<Vis::Brush::Style>("Style")
        .value("NO_PATTERN", Vis::Brush::NO_PATTERN)
        .value("SOLID_PATTERN", Vis::Brush::SOLID_PATTERN)
        .value("DENSE1_PATTERN", Vis::Brush::DENSE1_PATTERN)
        .value("DENSE2_PATTERN", Vis::Brush::DENSE2_PATTERN)
        .value("DENSE3_PATTERN", Vis::Brush::DENSE3_PATTERN)
        .value("DENSE4_PATTERN", Vis::Brush::DENSE4_PATTERN)
        .value("DENSE5_PATTERN", Vis::Brush::DENSE5_PATTERN)
        .value("DENSE6_PATTERN", Vis::Brush::DENSE6_PATTERN)
        .value("DENSE7_PATTERN", Vis::Brush::DENSE7_PATTERN)
        .value("H_PATTERN", Vis::Brush::H_PATTERN)
        .value("V_PATTERN", Vis::Brush::V_PATTERN)
        .value("CROSS_PATTERN", Vis::Brush::CROSS_PATTERN)
        .value("LEFT_DIAG_PATTERN", Vis::Brush::LEFT_DIAG_PATTERN)
        .value("RIGHT_DIAG_PATTERN", Vis::Brush::RIGHT_DIAG_PATTERN)
        .value("DIAG_CROSS_PATTERN", Vis::Brush::DIAG_CROSS_PATTERN)
        .export_values();

    brush_class
        .def(python::init<>(python::arg("self")))   
        .def(python::init<const Vis::Brush&>((python::arg("self"), python::arg("brush"))))   
        .def(python::init<Vis::Brush::Style>((python::arg("self"), python::arg("style"))))
        .def(python::init<const Vis::Color&, Vis::Brush::Style>((python::arg("self"), python::arg("color"), 
                                                                 python::arg("style") = Vis::Brush::SOLID_PATTERN)))
        .def(CDPLPythonBase::ObjectIdentityCheckVisitor<Vis::Brush>())    
        .def("assign", CDPLPythonBase::copyAssOp<Vis::Brush>(),
             (python::arg("self"), python::arg("brush")), python::return_self<>())
        .def("getColor", &Vis::Brush::getColor, python::arg("self"), python::return_internal_reference<1>())
        .def("setColor", &Vis::Brush::setColor, (python::arg("self"), python::arg("color")))
        .def("getStyle", &Vis::Brush::getStyle, python::arg("self"))    
        .def("setStyle", &Vis::Brush::setStyle, (python::arg("self"), python::arg("style")))
        .def("__str__", &brushToString, python::arg("self"))
        .def("__eq__", &Vis::Brush::operator==, (python::arg("self"), python::arg("brush")))
        .def("__ne__", &Vis::Brush::operator!=, (python::arg("self"), python::arg("brush")))
        .add_property("color", python::make_function(&Vis::Brush::getColor, python::return_internal_reference<1>()),
                      &Vis::Brush::setColor)
        .add_property("style", &Vis::Brush::getStyle, &Vis::Brush::setStyle);

    python::implicitly_convertible<Vis::Brush::Style, Vis::Brush>();
    python::implicitly_convertible<Vis::Color, Vis::Brush>();
}
