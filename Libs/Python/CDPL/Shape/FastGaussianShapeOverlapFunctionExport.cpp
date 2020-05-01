/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * FastGaussianShapeOverlapFunctionExport.cpp 
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

#include "CDPL/Shape/FastGaussianShapeOverlapFunction.hpp"
#include "CDPL/Shape/GaussianShapeFunction.hpp"

#include "ClassExports.hpp"


void CDPLPythonShape::exportFastGaussianShapeOverlapFunction()
{
    using namespace boost;
    using namespace CDPL;

	typedef void (Shape::FastGaussianShapeOverlapFunction::*SetBoolFunc)(bool);
	typedef bool (Shape::FastGaussianShapeOverlapFunction::*GetBoolFunc)() const;

    python::class_<Shape::FastGaussianShapeOverlapFunction, Shape::FastGaussianShapeOverlapFunction::SharedPointer,
				   python::bases<Shape::GaussianShapeOverlapFunction> >("FastGaussianShapeOverlapFunction", python::no_init)
		.def(python::init<>(python::arg("self")))
		.def(python::init<const Shape::GaussianShapeFunction&, const Shape::GaussianShapeFunction&>
			 ((python::arg("self"), python::arg("ref_shape_func"), python::arg("ovl_shape_func")))
			 [python::with_custodian_and_ward<1, 2, python::with_custodian_and_ward<1, 3> >()])
		.def(python::init<const Shape::FastGaussianShapeOverlapFunction&>((python::arg("self"), python::arg("func")))[python::with_custodian_and_ward<1, 2>()])
		.def("assign", &Shape::FastGaussianShapeOverlapFunction::operator=, (python::arg("self"), python::arg("func")),
			 python::return_self<python::with_custodian_and_ward<1, 2> >())
		.def("proximityOptimization", SetBoolFunc(&Shape::FastGaussianShapeOverlapFunction::proximityOptimization),
			 (python::arg("self"), python::arg("enable")))
		.def("proximityOptimization", GetBoolFunc(&Shape::FastGaussianShapeOverlapFunction::proximityOptimization), python::arg("self"))
		.def("setRadiusScalingFactor", &Shape::FastGaussianShapeOverlapFunction::setRadiusScalingFactor,
			 (python::arg("self"), python::arg("factor")))
		.def("getRadiusScalingFactor", &Shape::FastGaussianShapeOverlapFunction::getRadiusScalingFactor,
			 python::arg("self"))
		.def("fastExpFunction", SetBoolFunc(&Shape::FastGaussianShapeOverlapFunction::fastExpFunction),
			 (python::arg("self"), python::arg("enable")))
		.def("fastExpFunction", GetBoolFunc(&Shape::FastGaussianShapeOverlapFunction::fastExpFunction), python::arg("self"))
		.def_readonly("DEF_RADIUS_SCALING_FACTOR", Shape::FastGaussianShapeOverlapFunction::DEF_RADIUS_SCALING_FACTOR)
		.add_property("proximityOpt", GetBoolFunc(&Shape::FastGaussianShapeOverlapFunction::proximityOptimization),
					  SetBoolFunc(&Shape::FastGaussianShapeOverlapFunction::proximityOptimization))
		.add_property("radiusScalingFactor", &Shape::FastGaussianShapeOverlapFunction::getRadiusScalingFactor,
					  &Shape::FastGaussianShapeOverlapFunction::setRadiusScalingFactor)
		.add_property("fastExpFunc", GetBoolFunc(&Shape::FastGaussianShapeOverlapFunction::fastExpFunction),
					  SetBoolFunc(&Shape::FastGaussianShapeOverlapFunction::fastExpFunction));
}
