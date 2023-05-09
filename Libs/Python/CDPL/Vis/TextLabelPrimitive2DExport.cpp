/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * TextLabelPrimitive2DExport.cpp 
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

#include "CDPL/Vis/TextLabelPrimitive2D.hpp"

#include "Base/CopyAssOp.hpp"

#include "ClassExports.hpp"


void CDPLPythonVis::exportTextLabelPrimitive2D()
{
	using namespace boost;
	using namespace CDPL;

	void (Vis::TextLabelPrimitive2D::*setPositionFunc1)(const Math::Vector2D&) = &Vis::TextLabelPrimitive2D::setPosition;
	void (Vis::TextLabelPrimitive2D::*setPositionFunc2)(double, double) = &Vis::TextLabelPrimitive2D::setPosition;

	python::class_<Vis::TextLabelPrimitive2D, 
		python::bases<Vis::GraphicsPrimitive2D> >("TextLabelPrimitive2D", python::no_init)
		.def(python::init<>(python::arg("self")))    
		.def(python::init<const Vis::TextLabelPrimitive2D&>((python::arg("self"), python::arg("prim"))))
		.def("assign", CDPLPythonBase::copyAssOp(&Vis::TextLabelPrimitive2D::operator=),
			 (python::arg("self"), python::arg("prim")), 
			 python::return_self<>())
		.def("setText", &Vis::TextLabelPrimitive2D::setText, (python::arg("self"), python::arg("txt")))
		.def("getText", &Vis::TextLabelPrimitive2D::getText, python::arg("self"), 
			 python::return_value_policy<python::copy_const_reference>())
		.def("setPosition", setPositionFunc1, (python::arg("self"), python::arg("pos")))
		.def("setPosition", setPositionFunc2, (python::arg("self"), python::arg("x"), python::arg("y")))
		.def("getPosition", &Vis::TextLabelPrimitive2D::getPosition, python::arg("self"), 
			 python::return_value_policy<python::copy_const_reference>())
		.def("setPen", &Vis::TextLabelPrimitive2D::setPen, (python::arg("self"), python::arg("pen")))
		.def("getPen", &Vis::TextLabelPrimitive2D::getPen, python::arg("self"), 
			 python::return_internal_reference<1>())
		.def("setFont", &Vis::TextLabelPrimitive2D::setFont, (python::arg("self"), python::arg("font")))
		.def("getFont", &Vis::TextLabelPrimitive2D::getFont, python::arg("self"), 
			 python::return_internal_reference<1>())
		.add_property("text", python::make_function(&Vis::TextLabelPrimitive2D::getText, 
												   python::return_value_policy<python::copy_const_reference>()),
					  &Vis::TextLabelPrimitive2D::setText)
		.add_property("position", python::make_function(&Vis::TextLabelPrimitive2D::getPosition, 
												   python::return_value_policy<python::copy_const_reference>()),
					  setPositionFunc1)
		.add_property("pen", python::make_function(&Vis::TextLabelPrimitive2D::getPen, 
												   python::return_internal_reference<1>()),
					  &Vis::TextLabelPrimitive2D::setPen)
		.add_property("font", python::make_function(&Vis::TextLabelPrimitive2D::getFont, 
												   python::return_internal_reference<1>()),
					  &Vis::TextLabelPrimitive2D::setFont);
}
