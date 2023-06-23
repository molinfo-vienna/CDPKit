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


#include <boost/python.hpp>

#include "CDPL/Vis/Brush.hpp"

#include "Base/ObjectIdentityCheckVisitor.hpp"
#include "Base/CopyAssOp.hpp"

#include "ClassExports.hpp"


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
		.def("assign", CDPLPythonBase::copyAssOp(&Vis::Brush::operator=),
			 (python::arg("self"), python::arg("brush")), python::return_self<>())
        .def("getColor", &Vis::Brush::getColor, python::arg("self"), python::return_internal_reference<1>())
        .def("setColor", &Vis::Brush::setColor, (python::arg("self"), python::arg("color")))
        .def("getStyle", &Vis::Brush::getStyle, python::arg("self"))    
        .def("setStyle", &Vis::Brush::setStyle, (python::arg("self"), python::arg("style")))
		.def("__eq__", &Vis::Brush::operator==, (python::arg("self"), python::arg("brush")))
		.def("__ne__", &Vis::Brush::operator!=, (python::arg("self"), python::arg("brush")))
		.add_property("color", python::make_function(&Vis::Brush::getColor, python::return_internal_reference<1>()),
					  &Vis::Brush::setColor)
		.add_property("style", &Vis::Brush::getStyle, &Vis::Brush::setStyle);

    python::implicitly_convertible<Vis::Brush::Style, Vis::Brush>();
    python::implicitly_convertible<Vis::Color, Vis::Brush>();
}
