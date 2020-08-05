/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * ScoringFunctorsExport.cpp 
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

#include "CDPL/Shape/ScoringFunctors.hpp"
#include "CDPL/Shape/AlignmentResult.hpp"

#include "Base/ObjectIdentityCheckVisitor.hpp"
#include "Base/CopyAssOp.hpp"

#include "ClassExports.hpp"


void CDPLPythonShape::exportScoringFunctors()
{
    using namespace boost;
    using namespace CDPL;

    python::class_<Shape::TotalOverlapTanimotoScore>("TotalOverlapTanimotoScore", python::no_init)
		.def(python::init<>(python::arg("self")))
		.def(python::init<const Shape::TotalOverlapTanimotoScore&>((python::arg("self"), python::arg("score"))))
		.def(CDPLPythonBase::ObjectIdentityCheckVisitor<Shape::TotalOverlapTanimotoScore>())
		.def("assign", CDPLPythonBase::copyAssOp(&Shape::TotalOverlapTanimotoScore::operator=),
			 (python::arg("self"), python::arg("score")), python::return_self<>())
		.def("__call__", &Shape::TotalOverlapTanimotoScore::operator(), (python::arg("self"), python::arg("res")));

   python::class_<Shape::ShapeTanimotoScore>("ShapeTanimotoScore", python::no_init)
		.def(python::init<>(python::arg("self")))
		.def(python::init<const Shape::ShapeTanimotoScore&>((python::arg("self"), python::arg("score"))))
		.def(CDPLPythonBase::ObjectIdentityCheckVisitor<Shape::ShapeTanimotoScore>())
		.def("assign", CDPLPythonBase::copyAssOp(&Shape::ShapeTanimotoScore::operator=),
			 (python::arg("self"), python::arg("score")), python::return_self<>())
		.def("__call__", &Shape::ShapeTanimotoScore::operator(), (python::arg("self"), python::arg("res")));

   python::class_<Shape::ColorTanimotoScore>("ColorTanimotoScore", python::no_init)
		.def(python::init<>(python::arg("self")))
		.def(python::init<const Shape::ColorTanimotoScore&>((python::arg("self"), python::arg("score"))))
		.def(CDPLPythonBase::ObjectIdentityCheckVisitor<Shape::ColorTanimotoScore>())
		.def("assign", CDPLPythonBase::copyAssOp(&Shape::ColorTanimotoScore::operator=),
			 (python::arg("self"), python::arg("score")), python::return_self<>())
		.def("__call__", &Shape::ColorTanimotoScore::operator(), (python::arg("self"), python::arg("res")));
}
