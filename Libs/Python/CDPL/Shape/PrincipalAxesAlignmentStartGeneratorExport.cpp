/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * PrincipalAxesAlignmentStartGeneratorExport.cpp 
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

#include "CDPL/Shape/PrincipalAxesAlignmentStartGenerator.hpp"

#include "Base/CopyAssOp.hpp"

#include "ClassExports.hpp"


void CDPLPythonShape::exportPrincipalAxesAlignmentStartGenerator()
{
    using namespace boost;
    using namespace CDPL;

	python::scope scope = python::class_<Shape::PrincipalAxesAlignmentStartGenerator, python::bases<Shape::GaussianShapeAlignmentStartGenerator> >
		("PrincipalAxesAlignmentStartGenerator", python::no_init)
		.def(python::init<>(python::arg("self")))
		.def(python::init<const Shape::PrincipalAxesAlignmentStartGenerator&>((python::arg("self"), python::arg("gen"))))
		.def("setSymmetryThreshold", &Shape::PrincipalAxesAlignmentStartGenerator::setSymmetryThreshold,
			 (python::arg("self"), python::arg("thresh")))
		.def("getSymmetryThreshold", &Shape::PrincipalAxesAlignmentStartGenerator::getSymmetryThreshold, python::arg("self"))
		.def("setCenterAlignmentMode", &Shape::PrincipalAxesAlignmentStartGenerator::setCenterAlignmentMode,
			 (python::arg("self"), python::arg("mode")))
		.def("getCenterAlignmentMode", &Shape::PrincipalAxesAlignmentStartGenerator::getCenterAlignmentMode, python::arg("self"))
		.def("assign", CDPLPythonBase::copyAssOp(&Shape::PrincipalAxesAlignmentStartGenerator::operator=),
			 (python::arg("self"), python::arg("gen")), python::return_self<>())
		.add_property("symmetryThreshold", &Shape::PrincipalAxesAlignmentStartGenerator::getSymmetryThreshold,
					  &Shape::PrincipalAxesAlignmentStartGenerator::setSymmetryThreshold)
		.add_property("centerAlignmentMode", &Shape::PrincipalAxesAlignmentStartGenerator::getCenterAlignmentMode,
					  &Shape::PrincipalAxesAlignmentStartGenerator::setCenterAlignmentMode);

	python::enum_<Shape::PrincipalAxesAlignmentStartGenerator::CenterAlignmentMode>("CenterAlignmentMode")
		.value("SHAPE_CENTROID", Shape::PrincipalAxesAlignmentStartGenerator::SHAPE_CENTROID)
		.value("NON_COLOR_ELEMENT_CENTERS", Shape::PrincipalAxesAlignmentStartGenerator::NON_COLOR_ELEMENT_CENTERS)
		.value("COLOR_ELEMENT_CENTERS", Shape::PrincipalAxesAlignmentStartGenerator::COLOR_ELEMENT_CENTERS)
		.export_values();
}
