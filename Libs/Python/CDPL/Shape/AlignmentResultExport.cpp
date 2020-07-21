/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * AlignmentResultExport.cpp 
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

#include "CDPL/Shape/AlignmentResult.hpp"

#include "Base/ObjectIdentityCheckVisitor.hpp"
#include "Base/CopyAssOp.hpp"

#include "ClassExports.hpp"


void CDPLPythonShape::exportAlignmentResult()
{
    using namespace boost;
    using namespace CDPL;

	python::class_<Shape::AlignmentResult>("AlignmentResult", python::no_init)
		.def(python::init<>(python::arg("self")))
		.def(python::init<const Shape::AlignmentResult&>((python::arg("self"), python::arg("res"))))
		.def(CDPLPythonBase::ObjectIdentityCheckVisitor<Shape::AlignmentResult>())
		.def("assign", CDPLPythonBase::copyAssOp(&Shape::AlignmentResult::operator=),
			 (python::arg("self"), python::arg("res")), python::return_self<>())
		.def("getTransform", &Shape::AlignmentResult::getTransform, 
			 python::arg("self"), python::return_internal_reference<>())
		.def("setTransform", &Shape::AlignmentResult::setTransform, 
			 (python::arg("self"), python::arg("xform")))
		.def("getScore", &Shape::AlignmentResult::getScore, 
			 python::arg("self"))
		.def("setScore", &Shape::AlignmentResult::setScore, 
			 (python::arg("self"), python::arg("score")))
		.def("getReferenceShapeIndex", &Shape::AlignmentResult::getReferenceShapeIndex, 
			 python::arg("self"))
		.def("setReferenceShapeIndex", &Shape::AlignmentResult::setReferenceShapeIndex, 
			 (python::arg("self"), python::arg("idx")))
		.def("getAlignedShapeIndex", &Shape::AlignmentResult::getAlignedShapeIndex, 
			 python::arg("self"))
		.def("setAlignedShapeIndex", &Shape::AlignmentResult::setAlignedShapeIndex, 
			 (python::arg("self"), python::arg("idx")))
		.def("getStartingPoseID", &Shape::AlignmentResult::getStartingPoseID, 
			 python::arg("self"))
		.def("setStartingPoseID", &Shape::AlignmentResult::setStartingPoseID, 
			 (python::arg("self"), python::arg("id")))
		.def("getOverlap", &Shape::AlignmentResult::getOverlap, 
			 python::arg("self"))
		.def("setOverlap", &Shape::AlignmentResult::setOverlap, 
			 (python::arg("self"), python::arg("overlap")))
		.def("getColorOverlap", &Shape::AlignmentResult::getColorOverlap, 
			 python::arg("self"))
		.def("setColorOverlap", &Shape::AlignmentResult::setColorOverlap, 
			 (python::arg("self"), python::arg("overlap")))
		.def("getReferenceSelfOverlap", &Shape::AlignmentResult::getReferenceSelfOverlap, 
			 python::arg("self"))
		.def("setReferenceSelfOverlap", &Shape::AlignmentResult::setReferenceSelfOverlap, 
			 (python::arg("self"), python::arg("overlap")))
		.def("getReferenceColorSelfOverlap", &Shape::AlignmentResult::getReferenceColorSelfOverlap, 
			 python::arg("self"))
		.def("setReferenceColorSelfOverlap", &Shape::AlignmentResult::setReferenceColorSelfOverlap, 
			 (python::arg("self"), python::arg("overlap")))
		.def("getAlignedSelfOverlap", &Shape::AlignmentResult::getAlignedSelfOverlap, 
			 python::arg("self"))
		.def("setAlignedSelfOverlap", &Shape::AlignmentResult::setAlignedSelfOverlap, 
			 (python::arg("self"), python::arg("overlap")))
		.def("getAlignedColorSelfOverlap", &Shape::AlignmentResult::getAlignedColorSelfOverlap, 
			 python::arg("self"))
		.def("setAlignedColorSelfOverlap", &Shape::AlignmentResult::setAlignedColorSelfOverlap, 
			 (python::arg("self"), python::arg("overlap")))
		.add_property("transform", 
					  python::make_function(&Shape::AlignmentResult::getTransform, python::return_internal_reference<>()),
					  &Shape::AlignmentResult::setTransform)
		.add_property("score", 
					  &Shape::AlignmentResult::getScore, 
					  &Shape::AlignmentResult::setScore)
		.add_property("referenceShapeIndex", 
					  &Shape::AlignmentResult::getReferenceShapeIndex, 
					  &Shape::AlignmentResult::setReferenceShapeIndex)
		.add_property("alignedShapeIndex", 
					  &Shape::AlignmentResult::getAlignedShapeIndex, 
					  &Shape::AlignmentResult::setAlignedShapeIndex)
		.add_property("startingPoseID", 
					  &Shape::AlignmentResult::getStartingPoseID, 
					  &Shape::AlignmentResult::setStartingPoseID)
		.add_property("overlap", 
					  &Shape::AlignmentResult::getOverlap, 
					  &Shape::AlignmentResult::setOverlap)
		.add_property("colorOverlap", 
					  &Shape::AlignmentResult::getColorOverlap, 
					  &Shape::AlignmentResult::setColorOverlap)
		.add_property("referenceSelfOverlap", 
					  &Shape::AlignmentResult::getReferenceSelfOverlap, 
					  &Shape::AlignmentResult::setReferenceSelfOverlap)
		.add_property("referenceColorSelfOverlap", 
					  &Shape::AlignmentResult::getReferenceColorSelfOverlap, 
					  &Shape::AlignmentResult::setReferenceColorSelfOverlap)
		.add_property("alignedSelfOverlap", 
					  &Shape::AlignmentResult::getAlignedSelfOverlap, 
					  &Shape::AlignmentResult::setAlignedSelfOverlap)
		.add_property("alignedColorSelfOverlap", 
					  &Shape::AlignmentResult::getAlignedColorSelfOverlap, 
					  &Shape::AlignmentResult::setAlignedColorSelfOverlap);
}
