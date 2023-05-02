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

#include "CDPL/GRAIL/DefaultInteractionScoreGridSetCalculator.hpp"
#include "CDPL/Pharm/FeatureContainer.hpp"

#include "Base/CopyAssOp.hpp"

#include "ClassExports.hpp"


void CDPLPythonGRAIL::exportDefaultInteractionScoreGridSetCalculator()
{
    using namespace boost;
	using namespace CDPL;
  
	python::class_<GRAIL::DefaultInteractionScoreGridSetCalculator, python::bases<GRAIL::InteractionScoreGridSetCalculator>,
				   boost::noncopyable>("DefaultInteractionScoreGridSetCalculator", python::no_init)
		.def(python::init<>(python::arg("self")))
		.def(python::init<double, std::size_t, std::size_t, std::size_t>(
				 (python::arg("self"), python::arg("step_size"), python::arg("x_size"), python::arg("y_size"), python::arg("z_size"))))
		.def(python::init<double, double, double, std::size_t, std::size_t, std::size_t>(
				 (python::arg("self"), python::arg("x_step_size"), python::arg("y_step_size"), python::arg("z_step_size"), 
				  python::arg("x_size"), python::arg("y_size"), python::arg("z_size"))))
		.def(python::init<const GRAIL::DefaultInteractionScoreGridSetCalculator&>((python::arg("self"), python::arg("calculator"))))
		.def("assign", CDPLPythonBase::copyAssOp(&GRAIL::DefaultInteractionScoreGridSetCalculator::operator=), 
			 (python::arg("self"), python::arg("calculator")), python::return_self<>())
		.def("getXStepSize", &GRAIL::DefaultInteractionScoreGridSetCalculator::getXStepSize, python::arg("self"))
		.def("setXStepSize", &GRAIL::DefaultInteractionScoreGridSetCalculator::setXStepSize, (python::arg("self"), python::arg("size")))
		.def("getYStepSize", &GRAIL::DefaultInteractionScoreGridSetCalculator::getYStepSize, python::arg("self"))
		.def("setYStepSize", &GRAIL::DefaultInteractionScoreGridSetCalculator::setYStepSize, (python::arg("self"), python::arg("size")))
		.def("getZStepSize", &GRAIL::DefaultInteractionScoreGridSetCalculator::getZStepSize, python::arg("self"))
		.def("setZStepSize", &GRAIL::DefaultInteractionScoreGridSetCalculator::setZStepSize, (python::arg("self"), python::arg("size")))
		.def("getGridXSize", &GRAIL::DefaultInteractionScoreGridSetCalculator::getGridXSize, python::arg("self"))
		.def("setGridXSize", &GRAIL::DefaultInteractionScoreGridSetCalculator::setGridXSize, (python::arg("self"), python::arg("size")))
		.def("getGridYSize", &GRAIL::DefaultInteractionScoreGridSetCalculator::getGridYSize, python::arg("self"))
		.def("setGridYSize", &GRAIL::DefaultInteractionScoreGridSetCalculator::setGridYSize, (python::arg("self"), python::arg("size")))
		.def("getGridZSize", &GRAIL::DefaultInteractionScoreGridSetCalculator::getGridZSize, python::arg("self"))
		.def("setGridZSize", &GRAIL::DefaultInteractionScoreGridSetCalculator::setGridZSize, (python::arg("self"), python::arg("size")))
		.def("getCoordinatesTransform", &GRAIL::DefaultInteractionScoreGridSetCalculator::getCoordinatesTransform, python::arg("self"),
			 python::return_internal_reference<>())
		.def("setCoordinatesTransform", &GRAIL::DefaultInteractionScoreGridSetCalculator::setCoordinatesTransform<Math::Matrix4D>, 
			 (python::arg("self"), python::arg("xform")))
		.def("calculate", &GRAIL::DefaultInteractionScoreGridSetCalculator::calculate,
			 (python::arg("self"), python::arg("tgt_ftrs"), python::arg("grid_set")))
		.add_property("xStepSize", &GRAIL::DefaultInteractionScoreGridSetCalculator::getXStepSize, &GRAIL::DefaultInteractionScoreGridSetCalculator::setXStepSize)
		.add_property("yStepSize", &GRAIL::DefaultInteractionScoreGridSetCalculator::getYStepSize, &GRAIL::DefaultInteractionScoreGridSetCalculator::setYStepSize)
		.add_property("zStepSize", &GRAIL::DefaultInteractionScoreGridSetCalculator::getZStepSize, &GRAIL::DefaultInteractionScoreGridSetCalculator::setZStepSize)
		.add_property("gridXSize", &GRAIL::DefaultInteractionScoreGridSetCalculator::getGridXSize, &GRAIL::DefaultInteractionScoreGridSetCalculator::setGridXSize)
		.add_property("gridYSize", &GRAIL::DefaultInteractionScoreGridSetCalculator::getGridYSize, &GRAIL::DefaultInteractionScoreGridSetCalculator::setGridYSize)
		.add_property("gridZSize", &GRAIL::DefaultInteractionScoreGridSetCalculator::getGridZSize, &GRAIL::DefaultInteractionScoreGridSetCalculator::setGridZSize)
		.add_property("coordinatesTransform", 
					  python::make_function(&GRAIL::DefaultInteractionScoreGridSetCalculator::getCoordinatesTransform, python::return_internal_reference<>()),
					  &GRAIL::DefaultInteractionScoreGridSetCalculator::setCoordinatesTransform<Math::Matrix4D>);
}
