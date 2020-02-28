/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * Line2DExport.cpp 
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

#include "CDPL/Vis/Line2D.hpp"
#include "CDPL/Vis/Rectangle2D.hpp"

#include "Base/ObjectIdentityCheckVisitor.hpp"

#include "ClassExports.hpp"


namespace
{

	boost::python::object getIntersectionPoint(const CDPL::Vis::Line2D& line, const CDPL::Vis::Line2D& other_line) 
	{
		using namespace boost;
		using namespace CDPL;

		Math::Vector2D inters_pt;

		if (line.getIntersectionPoint(other_line, inters_pt))
			return python::object(inters_pt);

		return python::object();
	}
}


void CDPLPythonVis::exportLine2D()
{
	using namespace boost;
	using namespace CDPL;

	typedef void (Vis::Line2D::*SetPointFuncType1)(const Math::Vector2D&);
	typedef void (Vis::Line2D::*SetPointFuncType2)(double, double);
	typedef Math::Vector2D (Vis::Line2D::*CalcPointFuncType1)() const;
	typedef void (Vis::Line2D::*CalcPointFuncType2)(Math::Vector2D&) const;

	void (Vis::Line2D::*setPointsFunc1)(const Math::Vector2D&, const Math::Vector2D&) = &Vis::Line2D::setPoints;
	void (Vis::Line2D::*setPointsFunc2)(double, double, double, double) = &Vis::Line2D::setPoints;

	python::class_<Vis::Line2D>("Line2D", python::no_init)
		.def(python::init<>(python::arg("self")))
		.def(python::init<const Vis::Line2D&>((python::arg("self"), python::arg("line"))))   
		.def(python::init<const Math::Vector2D&, const Math::Vector2D&>((python::arg("self"),
																		 python::arg("beg"), 
																		 python::arg("end"))))   
		.def(python::init<double, double, double, double>
			 ((python::arg("self"), python::arg("beg_x"), python::arg("beg_y"), 
			   python::arg("end_x"), python::arg("end_y"))))    
		.def(CDPLPythonBase::ObjectIdentityCheckVisitor<Vis::Line2D>())	
		.def("assign", &Vis::Line2D::operator=, (python::arg("self"), python::arg("line")),
			 python::return_self<>())
		.def("setBegin", SetPointFuncType1(&Vis::Line2D::setBegin), 
			 (python::arg("self"), python::arg("pt")))
		.def("setBegin", SetPointFuncType2(&Vis::Line2D::setBegin), 
			 (python::arg("self"), python::arg("x"), python::arg("y")))
		.def("getBegin", &Vis::Line2D::getBegin, python::arg("self"), 
			 python::return_internal_reference<>())
		.def("setEnd", SetPointFuncType1(&Vis::Line2D::setEnd), 
			 (python::arg("self"), python::arg("pt")))
		.def("setEnd", SetPointFuncType2(&Vis::Line2D::setEnd), 
			 (python::arg("self"), python::arg("x"), python::arg("y")))
		.def("getEnd", &Vis::Line2D::getEnd, python::arg("self"), 
			 python::return_internal_reference<>())
		.def("setPoints", setPointsFunc1, 
			 (python::arg("self"), python::arg("beg"), python::arg("end")))
		.def("setPoints", setPointsFunc2, 
			 (python::arg("self"), python::arg("beg_x"), python::arg("beg_y"),
			  python::arg("end_x"), python::arg("end_y")))
		.def("swapPoints", &Vis::Line2D::swapPoints, python::arg("self"))
		.def("getDirection", CalcPointFuncType1(&Vis::Line2D::getDirection), 
			 python::arg("self"))
		.def("getDirection", CalcPointFuncType2(&Vis::Line2D::getDirection), 
			 (python::arg("self"), python::arg("dir")))
		.def("getCCWPerpDirection", CalcPointFuncType1(&Vis::Line2D::getCCWPerpDirection),
			 python::arg("self"))
		.def("getCCWPerpDirection", CalcPointFuncType2(&Vis::Line2D::getCCWPerpDirection), 
			 (python::arg("self"), python::arg("dir")))
		.def("getCWPerpDirection", CalcPointFuncType1(&Vis::Line2D::getCWPerpDirection), 
			 python::arg("self"))
		.def("getCWPerpDirection", CalcPointFuncType2(&Vis::Line2D::getCWPerpDirection), 
			 (python::arg("self"), python::arg("dir")))
		.def("getCenter", CalcPointFuncType1(&Vis::Line2D::getCenter), 
			 python::arg("self"))
		.def("getCenter", CalcPointFuncType2(&Vis::Line2D::getCenter), 
			 (python::arg("self"), python::arg("ctr")))
		.def("getLength", &Vis::Line2D::getLength, python::arg("self"))
		.def("translate", &Vis::Line2D::translate, 
			 (python::arg("self"), python::arg("vec")))
		.def("translateBegin", &Vis::Line2D::translateBegin, 
			 (python::arg("self"), python::arg("vec")))
		.def("translateEnd", &Vis::Line2D::translateEnd, 
			 (python::arg("self"), python::arg("vec")))
		.def("containsPoint", &Vis::Line2D::containsPoint, 
			 (python::arg("self"), python::arg("pt")))
		.def("getIntersectionPoint", &getIntersectionPoint, 
			 (python::arg("self"), python::arg("pt")))
		.def("clipBeginAgainstLineSeg", &Vis::Line2D::clipBeginAgainstLineSeg, 
			 (python::arg("self"), python::arg("line")))
		.def("clipEndAgainstLineSeg", &Vis::Line2D::clipEndAgainstLineSeg, 
			 (python::arg("self"), python::arg("line")))
		.def("setBeginToLineSegIntersection", &Vis::Line2D::setBeginToLineSegIntersection, 
			 (python::arg("self"), python::arg("line")))
		.def("setEndToLineSegIntersection", &Vis::Line2D::setEndToLineSegIntersection, 
			 (python::arg("self"), python::arg("line")))
		.def("clipBeginAgainstRectangle", &Vis::Line2D::clipBeginAgainstRectangle, 
			 (python::arg("self"), python::arg("rect")))
		.def("clipEndAgainstRectangle", &Vis::Line2D::clipEndAgainstRectangle, 
			 (python::arg("self"), python::arg("rect")))
		.def("getDistance", &Vis::Line2D::getDistance, (python::arg("self"), python::arg("pt")))
		.def("__eq__", &Vis::Line2D::operator==, (python::arg("self"), python::arg("line")))
		.def("__ne__", &Vis::Line2D::operator!=, (python::arg("self"), python::arg("line")))
		.def("__contains__", &Vis::Line2D::containsPoint, (python::arg("self"), python::arg("pt")))
		.add_property("length", &Vis::Line2D::getLength)
		.add_property("begin", python::make_function(&Vis::Line2D::getBegin, 
													  python::return_internal_reference<>()),
					  SetPointFuncType2(&Vis::Line2D::setBegin))
		.add_property("end", python::make_function(&Vis::Line2D::getEnd, 
													  python::return_internal_reference<>()),
					  SetPointFuncType2(&Vis::Line2D::setEnd))
		.add_property("direction", CalcPointFuncType1(&Vis::Line2D::getDirection))
		.add_property("ccwPerpDirection", CalcPointFuncType1(&Vis::Line2D::getCCWPerpDirection))
		.add_property("cwPerpDirection", CalcPointFuncType1(&Vis::Line2D::getCWPerpDirection))
		.add_property("center", CalcPointFuncType1(&Vis::Line2D::getCenter));
}
