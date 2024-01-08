/* 
 * FontExport.cpp 
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

#include "CDPL/Vis/Font.hpp"

#include "Base/ObjectIdentityCheckVisitor.hpp"
#include "Base/CopyAssOp.hpp"

#include "ClassExports.hpp"


namespace
{

    std::string toString(const CDPL::Vis::Font& font)
    {
        std::ostringstream oss;

        if (font == CDPL::Vis::Font()) 
            oss << "CDPL.Vis.Font()";

        else {
            oss << std::boolalpha;
            oss << "CDPL.Vis.Font(family='" << font.getFamily() << "', size=" << font.getSize() << ", bold=" << font.isBold() 
                << ", italic=" << font.isItalic() << ", ulined=" << font.isUnderlined() <<  ", olined=" << font.isOverlined() 
                << ", strkdout=" << font.isStrikedOut() << ", fxdpitch=" << font.hasFixedPitch() << ')';
        }
        
        return oss.str();
    }
}


void CDPLPythonVis::exportFont()
{
    using namespace boost;
    using namespace CDPL;

    python::class_<Vis::Font>("Font", python::no_init)
        .def(python::init<>(python::arg("self")))
        .def(python::init<const Vis::Font&>((python::arg("self"), python::arg("font"))))
        .def(python::init<const std::string, double, bool, bool>((python::arg("self"), python::arg("family"), 
                                                                  python::arg("size") = 12.0, python::arg("bold") = false,
                                                                  python::arg("italic") = false)))    
        .def(CDPLPythonBase::ObjectIdentityCheckVisitor<Vis::Font>())    
        .def("assign", CDPLPythonBase::copyAssOp<Vis::Font>(),
             (python::arg("self"), python::arg("font")),
             python::return_self<>())
        .def("setFamily", &Vis::Font::setFamily, (python::arg("self"), python::arg("family")))
        .def("getFamily", &Vis::Font::getFamily, python::arg("self"), 
             python::return_value_policy<python::copy_const_reference>())
        .def("setSize", &Vis::Font::setSize, (python::arg("self"), python::arg("size")))
        .def("getSize", &Vis::Font::getSize, python::arg("self"))
        .def("setBold", &Vis::Font::setBold, (python::arg("self"), python::arg("flag")))
        .def("isBold", &Vis::Font::isBold, python::arg("self"))
        .def("setItalic", &Vis::Font::setItalic, (python::arg("self"), python::arg("flag")))
        .def("isItalic", &Vis::Font::isItalic, python::arg("self"))
        .def("setUnderlined", &Vis::Font::setUnderlined, (python::arg("self"), python::arg("flag")))
        .def("isUnderlined", &Vis::Font::isUnderlined, python::arg("self"))
        .def("setOverlined", &Vis::Font::setOverlined, (python::arg("self"), python::arg("flag")))
        .def("isOverlined", &Vis::Font::isOverlined, python::arg("self"))
        .def("setStrikedOut", &Vis::Font::setStrikedOut, (python::arg("self"), python::arg("flag")))
        .def("isStrikedOut", &Vis::Font::isStrikedOut, python::arg("self"))
        .def("setFixedPitch", &Vis::Font::setFixedPitch, (python::arg("self"), python::arg("flag")))
        .def("hasFixedPitch", &Vis::Font::hasFixedPitch, python::arg("self"))
        .def("__eq__", &Vis::Font::operator==, (python::arg("self"), python::arg("font")))    
        .def("__ne__", &Vis::Font::operator!=, (python::arg("self"), python::arg("font")))
        .def("__str__", &toString, python::arg("self"))
        .add_property("family", 
                      python::make_function(&Vis::Font::getFamily, 
                                            python::return_value_policy<python::copy_const_reference>()),
                      &Vis::Font::setFamily)
        .add_property("size", &Vis::Font::getSize, &Vis::Font::setSize)
        .add_property("bold", &Vis::Font::isBold, &Vis::Font::setBold)
        .add_property("italic", &Vis::Font::isItalic, &Vis::Font::setItalic)
        .add_property("underlined", &Vis::Font::isUnderlined, &Vis::Font::setUnderlined)
        .add_property("overlined", &Vis::Font::isOverlined, &Vis::Font::setOverlined)
        .add_property("strikedOut", &Vis::Font::isStrikedOut, &Vis::Font::setStrikedOut)
        .add_property("fixedPitch", &Vis::Font::hasFixedPitch, &Vis::Font::setFixedPitch);
}
