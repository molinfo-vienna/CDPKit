/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * InteractionScoreGridExport.cpp 
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

#include "CDPL/Pharm/InteractionScoreGrid.hpp"

#include "ClassExports.hpp"
#include "Base/ObjectIdentityCheckVisitor.hpp"
#include "Base/CopyAssOp.hpp"


void CDPLPythonPharm::exportInteractionScoreGrid()
{
    using namespace boost;
    using namespace CDPL;

    python::class_<Pharm::InteractionScoreGrid, Pharm::InteractionScoreGrid::SharedPointer, 
				   python::bases<Math::UniformSpatialGrid<double> > >("InteractionScoreGrid", python::no_init)
		.def(python::init<const Pharm::InteractionScoreGrid&>((python::arg("self"), python::arg("grid"))))
		.def(python::init<unsigned int, unsigned int>((python::arg("self"), (python::arg("ftr_type") = Pharm::FeatureType::UNKNOWN), 
													   (python::arg("tgt_ftr_type") = Pharm::FeatureType::UNKNOWN))))
		.def("assign", CDPLPythonBase::copyAssOp(&Pharm::InteractionScoreGrid::operator=), (python::arg("self"), python::arg("grid")), 
			 python::return_self<>())
		.def(CDPLPythonBase::ObjectIdentityCheckVisitor<Pharm::InteractionScoreGrid>())
		.def("getFeatureType", &Pharm::InteractionScoreGrid::getFeatureType, python::arg("self"))
		.def("getTargetFeatureType", &Pharm::InteractionScoreGrid::getTargetFeatureType, python::arg("self"))
		.def("setFeatureType", &Pharm::InteractionScoreGrid::setFeatureType, (python::arg("self"), python::arg("type")))
		.def("setTargetFeatureType", &Pharm::InteractionScoreGrid::setTargetFeatureType, (python::arg("self"), python::arg("type")))
		.add_property("featureType", &Pharm::InteractionScoreGrid::getFeatureType,
					  &Pharm::InteractionScoreGrid::setFeatureType)
		.add_property("targetFeatureType", &Pharm::InteractionScoreGrid::getTargetFeatureType,
					  &Pharm::InteractionScoreGrid::setTargetFeatureType);
}
