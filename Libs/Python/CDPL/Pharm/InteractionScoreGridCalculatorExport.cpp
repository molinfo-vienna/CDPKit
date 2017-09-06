/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * InteractionScoreGridCalculatorExport.cpp 
 *
 * This file is part of the Chemical Data Processing Toolkit
 *
 * Copyright (C) 2003-2010 Thomas A. Seidel <thomas.seidel@univie.ac.at>
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

#include "CDPL/Pharm/InteractionScoreGridCalculator.hpp"
#include "CDPL/Pharm/InteractionScoreGridSet.hpp"
#include "CDPL/Chem/MolecularGraph.hpp"

#include "Base/CopyAssOp.hpp"
#include "Base/ObjectIdentityCheckVisitor.hpp"

#include "ClassExports.hpp"


void CDPLPythonPharm::exportInteractionScoreGridCalculator()
{
    using namespace boost;
	using namespace CDPL;

	python::class_<Pharm::InteractionScoreGridCalculator, boost::noncopyable>("InteractionScoreGridCalculator", python::no_init)
		.def(python::init<>(python::arg("self")))
		.def(python::init<double, std::size_t, std::size_t, std::size_t>(
				 (python::arg("self"), python::arg("step_size"), python::arg("x_size"), python::arg("y_size"), python::arg("z_size"))))
		.def(python::init<double, double, double, std::size_t, std::size_t, std::size_t>(
				 (python::arg("self"), python::arg("x_step_size"), python::arg("y_step_size"), python::arg("z_step_size"), 
				  python::arg("x_size"), python::arg("y_size"), python::arg("z_size"))))
		.def(python::init<const Pharm::InteractionScoreGridCalculator&>((python::arg("self"), python::arg("calculator"))))
		.def(CDPLPythonBase::ObjectIdentityCheckVisitor<Pharm::InteractionScoreGridCalculator>())	
		.def("assign", CDPLPythonBase::copyAssOp(&Pharm::InteractionScoreGridCalculator::operator=), 
			 (python::arg("self"), python::arg("calculator")), python::return_self<>())
		.def("getXStepSize", &Pharm::InteractionScoreGridCalculator::getXStepSize, python::arg("self"))
		.def("setXStepSize", &Pharm::InteractionScoreGridCalculator::setXStepSize, (python::arg("self"), python::arg("size")))
		.def("getYStepSize", &Pharm::InteractionScoreGridCalculator::getYStepSize, python::arg("self"))
		.def("setYStepSize", &Pharm::InteractionScoreGridCalculator::setYStepSize, (python::arg("self"), python::arg("size")))
		.def("getZStepSize", &Pharm::InteractionScoreGridCalculator::getZStepSize, python::arg("self"))
		.def("setZStepSize", &Pharm::InteractionScoreGridCalculator::setZStepSize, (python::arg("self"), python::arg("size")))
		.def("getGridXSize", &Pharm::InteractionScoreGridCalculator::getGridXSize, python::arg("self"))
		.def("setGridXSize", &Pharm::InteractionScoreGridCalculator::setGridXSize, (python::arg("self"), python::arg("size")))
		.def("getGridYSize", &Pharm::InteractionScoreGridCalculator::getGridYSize, python::arg("self"))
		.def("setGridYSize", &Pharm::InteractionScoreGridCalculator::setGridYSize, (python::arg("self"), python::arg("size")))
		.def("getGridZSize", &Pharm::InteractionScoreGridCalculator::getGridZSize, python::arg("self"))
		.def("setGridZSize", &Pharm::InteractionScoreGridCalculator::setGridZSize, (python::arg("self"), python::arg("size")))
		.def("getCoordinatesTransform", &Pharm::InteractionScoreGridCalculator::getCoordinatesTransform, python::arg("self"),
			 python::return_internal_reference<>())
		.def("setCoordinatesTransform", &Pharm::InteractionScoreGridCalculator::setCoordinatesTransform<Math::Matrix4D>, 
			 (python::arg("self"), python::arg("xform")))
		.def("setAtom3DCoordinatesFunction", &Pharm::InteractionScoreGridCalculator::setAtom3DCoordinatesFunction,
			 (python::arg("self"), python::arg("func")))
		.def("setFinalInteractionScoreFunction", &Pharm::InteractionScoreGridCalculator::setFinalInteractionScoreFunction,
			 (python::arg("self"), python::arg("func")))
		.def("setStericClashFactorFunction", &Pharm::InteractionScoreGridCalculator::setStericClashFactorFunction,
			 (python::arg("self"), python::arg("func")))
		.def("setInteractionScoringFunction", &Pharm::InteractionScoreGridCalculator::setInteractionScoringFunction, 
			 (python::arg("self"), python::arg("ftr_type"), python::arg("tgt_ftr_type"), python::arg("func")))
		.def("removeInteractionScoringFunction", &Pharm::InteractionScoreGridCalculator::removeInteractionScoringFunction, 
			 (python::arg("self"), python::arg("ftr_type"), python::arg("tgt_ftr_type")))
		.def("getInteractionScoringFunction", &Pharm::InteractionScoreGridCalculator::getInteractionScoringFunction, 
			 (python::arg("self"), python::arg("ftr_type"), python::arg("tgt_ftr_type")),
			 python::return_internal_reference<>())
		.def("enableInteraction", &Pharm::InteractionScoreGridCalculator::enableInteraction, 
			 (python::arg("self"), python::arg("ftr_type"), python::arg("tgt_ftr_type"), python::arg("enable")))
		.def("isInteractionEnabled", &Pharm::InteractionScoreGridCalculator::isInteractionEnabled, 
			 (python::arg("self"), python::arg("ftr_type"), python::arg("tgt_ftr_type")))
		.def("clearEnabledInteractions", &Pharm::InteractionScoreGridCalculator::isInteractionEnabled, python::arg("self"))
		.def("calculate", 
			 static_cast<void (Pharm::InteractionScoreGridCalculator::*)(const Chem::MolecularGraph& molgraph, Pharm::InteractionScoreGridSet& grid_set)>
			 (&Pharm::InteractionScoreGridCalculator::calculate),
			 (python::arg("self"), python::arg("molgraph"), python::arg("grid_set")))
		.def("calculate", 
			 static_cast<void (Pharm::InteractionScoreGridCalculator::*)(const Chem::MolecularGraph& molgraph, const Pharm::FeatureContainer&, Pharm::InteractionScoreGridSet& grid_set)>
			 (&Pharm::InteractionScoreGridCalculator::calculate),
			 (python::arg("self"), python::arg("molgraph"), python::arg("features"), python::arg("grid_set")))
		.def("calculate", 
			 static_cast<void (Pharm::InteractionScoreGridCalculator::*)(const Pharm::FeatureContainer&, Pharm::InteractionScoreGridSet& grid_set)>
			 (&Pharm::InteractionScoreGridCalculator::calculate),
			 (python::arg("self"), python::arg("features"), python::arg("grid_set")))
		.add_property("xStepSize", &Pharm::InteractionScoreGridCalculator::getXStepSize, &Pharm::InteractionScoreGridCalculator::setXStepSize)
		.add_property("yStepSize", &Pharm::InteractionScoreGridCalculator::getYStepSize, &Pharm::InteractionScoreGridCalculator::setYStepSize)
		.add_property("zStepSize", &Pharm::InteractionScoreGridCalculator::getZStepSize, &Pharm::InteractionScoreGridCalculator::setZStepSize)
		.add_property("gridXSize", &Pharm::InteractionScoreGridCalculator::getGridXSize, &Pharm::InteractionScoreGridCalculator::setGridXSize)
		.add_property("gridYSize", &Pharm::InteractionScoreGridCalculator::getGridYSize, &Pharm::InteractionScoreGridCalculator::setGridYSize)
		.add_property("gridZSize", &Pharm::InteractionScoreGridCalculator::getGridZSize, &Pharm::InteractionScoreGridCalculator::setGridZSize)
		.add_property("coordinatesTransform", 
					  python::make_function(&Pharm::InteractionScoreGridCalculator::getCoordinatesTransform, python::return_internal_reference<>()),
					  &Pharm::InteractionScoreGridCalculator::setCoordinatesTransform<Math::Matrix4D>)
		.add_property("atom3DCoordinatesFunction", &Pharm::InteractionScoreGridCalculator::setAtom3DCoordinatesFunction)
		.add_property("finalInteractionScoreFunction", &Pharm::InteractionScoreGridCalculator::setFinalInteractionScoreFunction)
		.add_property("stericClashFactorFunction", &Pharm::InteractionScoreGridCalculator::setStericClashFactorFunction);
}
