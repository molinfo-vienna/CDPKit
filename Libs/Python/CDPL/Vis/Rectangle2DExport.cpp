/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * Rectangle2DExport.cpp 
 *
 * This file is part of the Chemical Data Processing Toolkit
 *
 * Copyright (C) 2003-2020 Thomas A. Seidel <thomas.seidel@univie.ac.at>
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

#include "CDPL/Vis/Rectangle2D.hpp"

#include "Base/ObjectIdentityCheckVisitor.hpp"

#include "ClassExports.hpp"


void CDPLPythonVis::exportRectangle2D()
{
	using namespace boost;
	using namespace CDPL;

	typedef Math::Vector2D (Vis::Rectangle2D::*CalcPointFuncType1)() const;
	typedef void (Vis::Rectangle2D::*CalcPointFuncType2)(Math::Vector2D&) const;

	typedef void (Vis::Rectangle2D::*PointFuncType1)(const Math::Vector2D&);
	typedef void (Vis::Rectangle2D::*PointFuncType2)(double, double);

	bool (Vis::Rectangle2D::*containsPointFunc1)(const Math::Vector2D&) const = &Vis::Rectangle2D::containsPoint;
	bool (Vis::Rectangle2D::*containsPointFunc2)(double, double) const = &Vis::Rectangle2D::containsPoint;

	void (Vis::Rectangle2D::*setBoundsFunc1)(const Math::Vector2D&, const Math::Vector2D&) = &Vis::Rectangle2D::setBounds;
	void (Vis::Rectangle2D::*setBoundsFunc2)(double, double, double, double) = &Vis::Rectangle2D::setBounds;

	python::class_<Vis::Rectangle2D>("Rectangle2D", python::no_init)
		.def(python::init<>(python::arg("self")))
		.def(python::init<const Vis::Rectangle2D&>((python::arg("self"), python::arg("rect"))))
		.def(python::init<const Math::Vector2D&, const Math::Vector2D&>
			 ((python::arg("self"), python::arg("min"), python::arg("max"))))    
		.def(python::init<double, double, double, double>
			 ((python::arg("self"), python::arg("min_x"), python::arg("min_y"), python::arg("max_x"), python::arg("max_y"))))    
		.def(CDPLPythonBase::ObjectIdentityCheckVisitor<Vis::Rectangle2D>())	
		.def("assign", &Vis::Rectangle2D::operator=, (python::arg("self"), python::arg("rect")),
			 python::return_self<>())
		.def("isDefined", &Vis::Rectangle2D::isDefined, python::arg("self"))
		.def("addPoint", PointFuncType1(&Vis::Rectangle2D::addPoint), (python::arg("self"), python::arg("pt")))
		.def("addPoint", PointFuncType2(&Vis::Rectangle2D::addPoint), (python::arg("self"), python::arg("x"), python::arg("y")))
		.def("addMargin", &Vis::Rectangle2D::addMargin, (python::arg("self"), python::arg("width"), python::arg("height")))
		.def("addRectangle", &Vis::Rectangle2D::addRectangle, (python::arg("self"), python::arg("rect")))
		.def("containsPoint", containsPointFunc1, (python::arg("self"), python::arg("pt")))
		.def("containsPoint", containsPointFunc2, (python::arg("self"), python::arg("x"), python::arg("y")))
		.def("containsRectangle", &Vis::Rectangle2D::containsRectangle, (python::arg("self"), python::arg("rect")))
		.def("intersectsRectangle", &Vis::Rectangle2D::intersectsRectangle, (python::arg("self"), python::arg("rect")))
		.def("setMin", PointFuncType1(&Vis::Rectangle2D::setMin), (python::arg("self"), python::arg("pt")))
		.def("setMin", PointFuncType2(&Vis::Rectangle2D::setMin), (python::arg("self"), python::arg("x"), python::arg("y")))
		.def("setMax", PointFuncType1(&Vis::Rectangle2D::setMax), (python::arg("self"), python::arg("pt")))
		.def("setMax", PointFuncType2(&Vis::Rectangle2D::setMax), (python::arg("self"), python::arg("x"), python::arg("y")))
		.def("setBounds", setBoundsFunc1, (python::arg("self"), python::arg("min"), python::arg("max")))
		.def("setBounds", setBoundsFunc2, (python::arg("self"), python::arg("min_x"), python::arg("min_y"), 
										   python::arg("max_x"), python::arg("max_y")))
		.def("getMin", &Vis::Rectangle2D::getMin, python::arg("self"), python::return_internal_reference<>())
		.def("getMax", &Vis::Rectangle2D::getMax, python::arg("self"), python::return_internal_reference<>())
		.def("getCenter", CalcPointFuncType1(&Vis::Rectangle2D::getCenter), python::arg("self"))
		.def("getCenter", CalcPointFuncType2(&Vis::Rectangle2D::getCenter), (python::arg("self"), python::arg("ctr")))
		.def("getArea", &Vis::Rectangle2D::getArea, python::arg("self"))
		.def("getWidth", &Vis::Rectangle2D::getWidth, python::arg("self"))
		.def("getHeight", &Vis::Rectangle2D::getHeight, python::arg("self"))
		.def("reset", &Vis::Rectangle2D::reset, python::arg("self"))
		.def("scale", &Vis::Rectangle2D::scale, (python::arg("self"), python::arg("factor")))
		.def("translate", PointFuncType1(&Vis::Rectangle2D::translate), (python::arg("self"), python::arg("vec")))
		.def("__eq__", &Vis::Rectangle2D::operator==, (python::arg("self"), python::arg("rect")))
		.def("__ne__", &Vis::Rectangle2D::operator!=, (python::arg("self"), python::arg("rect")))
		.def("__contains__", containsPointFunc1, (python::arg("self"), python::arg("pt")))
		.def("__contains__", &Vis::Rectangle2D::containsRectangle, (python::arg("self"), python::arg("rect")))
		.add_property("defined", &Vis::Rectangle2D::isDefined)
		.add_property("min", python::make_function(&Vis::Rectangle2D::getMin,
												   python::return_internal_reference<>()),
					  PointFuncType1(&Vis::Rectangle2D::setMin))
		.add_property("max", python::make_function(&Vis::Rectangle2D::getMax,
												   python::return_internal_reference<>()),
					  PointFuncType1(&Vis::Rectangle2D::setMax))
		.add_property("center", CalcPointFuncType1(&Vis::Rectangle2D::getCenter))
		.add_property("width", &Vis::Rectangle2D::getWidth)
		.add_property("height", &Vis::Rectangle2D::getHeight)
		.add_property("area", &Vis::Rectangle2D::getArea);
}
