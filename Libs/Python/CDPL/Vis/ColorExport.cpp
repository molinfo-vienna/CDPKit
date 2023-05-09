/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * ColorExport.cpp 
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

#include <boost/python.hpp>

#include "CDPL/Vis/Color.hpp"

#include "Base/ObjectIdentityCheckVisitor.hpp"
#include "Base/CopyAssOp.hpp"

#include "ClassExports.hpp"


namespace
{

	std::string toString(const CDPL::Vis::Color& col)
	{
		std::ostringstream oss;

		oss << "CDPL.Vis.Color(";
		
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
}


void CDPLPythonVis::exportColor()
{
	using namespace boost;
	using namespace CDPL;

	python::class_<Vis::Color>("Color", python::no_init)
		.def(python::init<>(python::arg("self")))    
		.def(python::init<const Vis::Color&>((python::arg("self"), python::arg("color"))))
		.def(python::init<double, double, double, double>(
				 (python::arg("self"), python::arg("red"), python::arg("green"), 
				  python::arg("blue"), python::arg("alpha") = 1.0)))   
		.def(CDPLPythonBase::ObjectIdentityCheckVisitor<Vis::Color>())	
		.def("assign", CDPLPythonBase::copyAssOp(&Vis::Color::operator=), (python::arg("self"), python::arg("color")), 
			 python::return_self<>())
        .def("getAlpha", &Vis::Color::getAlpha, python::arg("self"))    
        .def("setAlpha", &Vis::Color::setAlpha, (python::arg("self"), python::arg("alpha")))
        .def("getBlue", &Vis::Color::getBlue, python::arg("self"))    
        .def("setBlue", &Vis::Color::setBlue, (python::arg("self"), python::arg("blue")))
        .def("getGreen", &Vis::Color::getGreen, python::arg("self"))    
        .def("setGreen", &Vis::Color::setGreen, (python::arg("self"), python::arg("green")))
        .def("getRed", &Vis::Color::getRed, python::arg("self"))    
        .def("setRed", &Vis::Color::setRed, (python::arg("self"), python::arg("red")))
        .def("setRGBA", &Vis::Color::setRGBA, 
			 (python::arg("self"), python::arg("red"), python::arg("green"), 
			  python::arg("blue"), python::arg("alpha") = 1.0))    
        .def("__eq__", &Vis::Color::operator==, (python::arg("self"), python::arg("color")))
		.def("__ne__", &Vis::Color::operator!=, (python::arg("self"), python::arg("color")))
		.def("__str__", &toString, python::arg("self"))
		.add_property("red", &Vis::Color::getRed, &Vis::Color::setRed)
		.add_property("green", &Vis::Color::getGreen, &Vis::Color::setGreen)
		.add_property("blue", &Vis::Color::getBlue, &Vis::Color::setBlue)
		.add_property("alpha", &Vis::Color::getAlpha, &Vis::Color::setAlpha)
        .def_readonly("BLACK", Vis::Color::BLACK)    
        .def_readonly("BLUE", Vis::Color::BLUE)    
        .def_readonly("CYAN", Vis::Color::CYAN)    
        .def_readonly("DARK_BLUE", Vis::Color::DARK_BLUE)    
        .def_readonly("DARK_CYAN", Vis::Color::DARK_CYAN)    
        .def_readonly("DARK_GRAY", Vis::Color::DARK_GRAY)    
        .def_readonly("DARK_GREEN", Vis::Color::DARK_GREEN)    
        .def_readonly("DARK_MAGENTA", Vis::Color::DARK_MAGENTA)    
        .def_readonly("DARK_RED", Vis::Color::DARK_RED)    
        .def_readonly("DARK_YELLOW", Vis::Color::DARK_YELLOW)    
        .def_readonly("GRAY", Vis::Color::GRAY)    
        .def_readonly("GREEN", Vis::Color::GREEN)    
        .def_readonly("LIGHT_GRAY", Vis::Color::LIGHT_GRAY)    
        .def_readonly("MAGENTA", Vis::Color::MAGENTA)    
        .def_readonly("RED", Vis::Color::RED)    
        .def_readonly("TRANSPARENT", Vis::Color::TRANSPARENT)    
        .def_readonly("WHITE", Vis::Color::WHITE)    
        .def_readonly("YELLOW", Vis::Color::YELLOW);
}
