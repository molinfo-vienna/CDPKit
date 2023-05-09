/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * PrincipalAxesAlignmentStartGeneratorExport.cpp 
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

#include "CDPL/Shape/PrincipalAxesAlignmentStartGenerator.hpp"

#include "Base/CopyAssOp.hpp"

#include "ClassExports.hpp"


void CDPLPythonShape::exportPrincipalAxesAlignmentStartGenerator()
{
    using namespace boost;
    using namespace CDPL;

	typedef void (Shape::PrincipalAxesAlignmentStartGenerator::*SetBoolFunc)(bool);
    typedef bool (Shape::PrincipalAxesAlignmentStartGenerator::*GetBoolFunc)() const;

	python::class_<Shape::PrincipalAxesAlignmentStartGenerator, python::bases<Shape::GaussianShapeAlignmentStartGenerator> >
		("PrincipalAxesAlignmentStartGenerator", python::no_init)
		.def(python::init<>(python::arg("self")))
		.def(python::init<const Shape::PrincipalAxesAlignmentStartGenerator&>((python::arg("self"), python::arg("gen"))))
		.def("setSymmetryThreshold", &Shape::PrincipalAxesAlignmentStartGenerator::setSymmetryThreshold,
			 (python::arg("self"), python::arg("thresh")))
		.def("getSymmetryThreshold", &Shape::PrincipalAxesAlignmentStartGenerator::getSymmetryThreshold, python::arg("self"))
		.def("genShapeCenterStarts", SetBoolFunc(&Shape::PrincipalAxesAlignmentStartGenerator::genShapeCenterStarts),
			 (python::arg("self"), python::arg("generate")))
		.def("genShapeCenterStarts", GetBoolFunc(&Shape::PrincipalAxesAlignmentStartGenerator::genShapeCenterStarts),
			 python::arg("self"))
		.def("genColorCenterStarts", SetBoolFunc(&Shape::PrincipalAxesAlignmentStartGenerator::genColorCenterStarts),
			 (python::arg("self"), python::arg("generate")))
		.def("genColorCenterStarts", GetBoolFunc(&Shape::PrincipalAxesAlignmentStartGenerator::genColorCenterStarts),
			 python::arg("self"))
		.def("genNonColorCenterStarts", SetBoolFunc(&Shape::PrincipalAxesAlignmentStartGenerator::genNonColorCenterStarts),
			 (python::arg("self"), python::arg("generate")))
		.def("genNonColorCenterStarts", GetBoolFunc(&Shape::PrincipalAxesAlignmentStartGenerator::genNonColorCenterStarts),
			 python::arg("self"))
		.def("genRandomStarts", SetBoolFunc(&Shape::PrincipalAxesAlignmentStartGenerator::genRandomStarts),
			 (python::arg("self"), python::arg("generate")))
		.def("genRandomStarts", GetBoolFunc(&Shape::PrincipalAxesAlignmentStartGenerator::genRandomStarts),
			 python::arg("self"))
		.def("genForAlignedShapeCenters", SetBoolFunc(&Shape::PrincipalAxesAlignmentStartGenerator::genForAlignedShapeCenters),
			 (python::arg("self"), python::arg("generate")))
		.def("genForAlignedShapeCenters", GetBoolFunc(&Shape::PrincipalAxesAlignmentStartGenerator::genForAlignedShapeCenters),
			 python::arg("self"))
		.def("genForReferenceShapeCenters", SetBoolFunc(&Shape::PrincipalAxesAlignmentStartGenerator::genForReferenceShapeCenters),
			 (python::arg("self"), python::arg("generate")))
		.def("genForReferenceShapeCenters", GetBoolFunc(&Shape::PrincipalAxesAlignmentStartGenerator::genForReferenceShapeCenters),
			 python::arg("self"))
		.def("genForLargerShapeCenters", SetBoolFunc(&Shape::PrincipalAxesAlignmentStartGenerator::genForLargerShapeCenters),
			 (python::arg("self"), python::arg("generate")))
		.def("genForLargerShapeCenters", GetBoolFunc(&Shape::PrincipalAxesAlignmentStartGenerator::genForLargerShapeCenters),
			 python::arg("self"))
		.def("setMaxRandomTranslation", &Shape::PrincipalAxesAlignmentStartGenerator::setMaxRandomTranslation,
			 (python::arg("self"), python::arg("max_trans")))
		.def("getMaxRandomTranslation", &Shape::PrincipalAxesAlignmentStartGenerator::getMaxRandomTranslation, python::arg("self"))
		.def("setNumRandomStarts", &Shape::PrincipalAxesAlignmentStartGenerator::setNumRandomStarts,
			 (python::arg("self"), python::arg("num_starts")))
		.def("getNumRandomStarts", &Shape::PrincipalAxesAlignmentStartGenerator::getNumRandomStarts, python::arg("self"))
		.def("setRandomSeed", &Shape::PrincipalAxesAlignmentStartGenerator::setRandomSeed,
			 (python::arg("self"), python::arg("seed")))
		.def("assign", CDPLPythonBase::copyAssOp(&Shape::PrincipalAxesAlignmentStartGenerator::operator=),
			 (python::arg("self"), python::arg("gen")), python::return_self<>())
		.def_readonly("DEF_SYMMETRY_THRESHOLD", Shape::PrincipalAxesAlignmentStartGenerator::DEF_SYMMETRY_THRESHOLD)
		.def_readonly("DEF_NUM_RANDOM_STARTS", Shape::PrincipalAxesAlignmentStartGenerator::DEF_NUM_RANDOM_STARTS)
		.def_readonly("DEF_MAX_RANDOM_TRANSLATION", Shape::PrincipalAxesAlignmentStartGenerator::DEF_MAX_RANDOM_TRANSLATION)
		.add_property("symmetryThreshold", &Shape::PrincipalAxesAlignmentStartGenerator::getSymmetryThreshold,
					  &Shape::PrincipalAxesAlignmentStartGenerator::setSymmetryThreshold)
		.add_property("maxRandomTranslation", &Shape::PrincipalAxesAlignmentStartGenerator::getMaxRandomTranslation,
					  &Shape::PrincipalAxesAlignmentStartGenerator::setMaxRandomTranslation)
		.add_property("numRandomStarts", &Shape::PrincipalAxesAlignmentStartGenerator::getNumRandomStarts,
					  &Shape::PrincipalAxesAlignmentStartGenerator::setNumRandomStarts)
		.add_property("shapeCenterStarts", GetBoolFunc(&Shape::PrincipalAxesAlignmentStartGenerator::genShapeCenterStarts),
					  SetBoolFunc(&Shape::PrincipalAxesAlignmentStartGenerator::genShapeCenterStarts))
		.add_property("colorCenterStarts", GetBoolFunc(&Shape::PrincipalAxesAlignmentStartGenerator::genColorCenterStarts),
					  SetBoolFunc(&Shape::PrincipalAxesAlignmentStartGenerator::genColorCenterStarts))
		.add_property("nonColorCenterStarts", GetBoolFunc(&Shape::PrincipalAxesAlignmentStartGenerator::genNonColorCenterStarts),
					  SetBoolFunc(&Shape::PrincipalAxesAlignmentStartGenerator::genNonColorCenterStarts))
		.add_property("randomStarts", GetBoolFunc(&Shape::PrincipalAxesAlignmentStartGenerator::genRandomStarts),
					  SetBoolFunc(&Shape::PrincipalAxesAlignmentStartGenerator::genRandomStarts))
		.add_property("genForAlignedShapeCtrs", GetBoolFunc(&Shape::PrincipalAxesAlignmentStartGenerator::genForAlignedShapeCenters),
					  SetBoolFunc(&Shape::PrincipalAxesAlignmentStartGenerator::genForAlignedShapeCenters))
		.add_property("genForReferenceShapeCrs", GetBoolFunc(&Shape::PrincipalAxesAlignmentStartGenerator::genForReferenceShapeCenters),
					  SetBoolFunc(&Shape::PrincipalAxesAlignmentStartGenerator::genForReferenceShapeCenters))
		.add_property("genForLargerShapeCtrs", GetBoolFunc(&Shape::PrincipalAxesAlignmentStartGenerator::genForLargerShapeCenters),
					  SetBoolFunc(&Shape::PrincipalAxesAlignmentStartGenerator::genForLargerShapeCenters));
}
