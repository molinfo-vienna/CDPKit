/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * DefaultInteractionScoreGridSetCalculatorExport.cpp 
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

#include "CDPL/GRAILS/DefaultInteractionScoreGridSetCalculator.hpp"
#include "CDPL/Pharm/FeatureContainer.hpp"

#include "Base/CopyAssOp.hpp"

#include "ClassExports.hpp"


void CDPLPythonGRAILS::exportDefaultInteractionScoreGridSetCalculator()
{
    using namespace boost;
	using namespace CDPL;
  
	python::class_<GRAILS::DefaultInteractionScoreGridSetCalculator, python::bases<GRAILS::InteractionScoreGridSetCalculator>,
				   boost::noncopyable>("DefaultInteractionScoreGridSetCalculator", python::no_init)
		.def(python::init<>(python::arg("self")))
		.def(python::init<double, std::size_t, std::size_t, std::size_t>(
				 (python::arg("self"), python::arg("step_size"), python::arg("x_size"), python::arg("y_size"), python::arg("z_size"))))
		.def(python::init<double, double, double, std::size_t, std::size_t, std::size_t>(
				 (python::arg("self"), python::arg("x_step_size"), python::arg("y_step_size"), python::arg("z_step_size"), 
				  python::arg("x_size"), python::arg("y_size"), python::arg("z_size"))))
		.def(python::init<const GRAILS::DefaultInteractionScoreGridSetCalculator&>((python::arg("self"), python::arg("calculator"))))
		.def("assign", CDPLPythonBase::copyAssOp(&GRAILS::DefaultInteractionScoreGridSetCalculator::operator=), 
			 (python::arg("self"), python::arg("calculator")), python::return_self<>())
		.def("getXStepSize", &GRAILS::DefaultInteractionScoreGridSetCalculator::getXStepSize, python::arg("self"))
		.def("setXStepSize", &GRAILS::DefaultInteractionScoreGridSetCalculator::setXStepSize, (python::arg("self"), python::arg("size")))
		.def("getYStepSize", &GRAILS::DefaultInteractionScoreGridSetCalculator::getYStepSize, python::arg("self"))
		.def("setYStepSize", &GRAILS::DefaultInteractionScoreGridSetCalculator::setYStepSize, (python::arg("self"), python::arg("size")))
		.def("getZStepSize", &GRAILS::DefaultInteractionScoreGridSetCalculator::getZStepSize, python::arg("self"))
		.def("setZStepSize", &GRAILS::DefaultInteractionScoreGridSetCalculator::setZStepSize, (python::arg("self"), python::arg("size")))
		.def("getGridXSize", &GRAILS::DefaultInteractionScoreGridSetCalculator::getGridXSize, python::arg("self"))
		.def("setGridXSize", &GRAILS::DefaultInteractionScoreGridSetCalculator::setGridXSize, (python::arg("self"), python::arg("size")))
		.def("getGridYSize", &GRAILS::DefaultInteractionScoreGridSetCalculator::getGridYSize, python::arg("self"))
		.def("setGridYSize", &GRAILS::DefaultInteractionScoreGridSetCalculator::setGridYSize, (python::arg("self"), python::arg("size")))
		.def("getGridZSize", &GRAILS::DefaultInteractionScoreGridSetCalculator::getGridZSize, python::arg("self"))
		.def("setGridZSize", &GRAILS::DefaultInteractionScoreGridSetCalculator::setGridZSize, (python::arg("self"), python::arg("size")))
		.def("getCoordinatesTransform", &GRAILS::DefaultInteractionScoreGridSetCalculator::getCoordinatesTransform, python::arg("self"),
			 python::return_internal_reference<>())
		.def("setCoordinatesTransform", &GRAILS::DefaultInteractionScoreGridSetCalculator::setCoordinatesTransform<Math::Matrix4D>, 
			 (python::arg("self"), python::arg("xform")))
		.def("calculate", &GRAILS::DefaultInteractionScoreGridSetCalculator::calculate,
			 (python::arg("self"), python::arg("features"), python::arg("grid_set")))
		.add_property("xStepSize", &GRAILS::DefaultInteractionScoreGridSetCalculator::getXStepSize, &GRAILS::DefaultInteractionScoreGridSetCalculator::setXStepSize)
		.add_property("yStepSize", &GRAILS::DefaultInteractionScoreGridSetCalculator::getYStepSize, &GRAILS::DefaultInteractionScoreGridSetCalculator::setYStepSize)
		.add_property("zStepSize", &GRAILS::DefaultInteractionScoreGridSetCalculator::getZStepSize, &GRAILS::DefaultInteractionScoreGridSetCalculator::setZStepSize)
		.add_property("gridXSize", &GRAILS::DefaultInteractionScoreGridSetCalculator::getGridXSize, &GRAILS::DefaultInteractionScoreGridSetCalculator::setGridXSize)
		.add_property("gridYSize", &GRAILS::DefaultInteractionScoreGridSetCalculator::getGridYSize, &GRAILS::DefaultInteractionScoreGridSetCalculator::setGridYSize)
		.add_property("gridZSize", &GRAILS::DefaultInteractionScoreGridSetCalculator::getGridZSize, &GRAILS::DefaultInteractionScoreGridSetCalculator::setGridZSize)
		.add_property("coordinatesTransform", 
					  python::make_function(&GRAILS::DefaultInteractionScoreGridSetCalculator::getCoordinatesTransform, python::return_internal_reference<>()),
					  &GRAILS::DefaultInteractionScoreGridSetCalculator::setCoordinatesTransform<Math::Matrix4D>);
}
