/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * ScoringFunctionExport.cpp 
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

#include "CDPL/Shape/ScoringFunctions.hpp"
#include "CDPL/Shape/AlignmentResult.hpp"

#include "FunctionExports.hpp"


void CDPLPythonShape::exportScoringFunctions()
{
	using namespace boost;
	using namespace CDPL;

	python::def("calcTotalOverlapTanimotoScore", &Shape::calcTotalOverlapTanimotoScore, python::arg("res"));
	python::def("calcShapeTanimotoScore", &Shape::calcShapeTanimotoScore, python::arg("res"));
	python::def("calcColorTanimotoScore", &Shape::calcColorTanimotoScore, python::arg("res"));
	python::def("calcTanimotoComboScore", &Shape::calcTanimotoComboScore, python::arg("res"));

	python::def("calcTotalOverlapTverskyScore", &Shape::calcTotalOverlapTverskyScore, 
				(python::arg("res"), python::arg("alpha") = 0.95, python::arg("beta") = 0.05));
	python::def("calcShapeTverskyScore", &Shape::calcShapeTverskyScore, 
				(python::arg("res"), python::arg("alpha") = 0.95, python::arg("beta") = 0.05));
	python::def("calcColorTverskyScore", &Shape::calcColorTverskyScore, 
				(python::arg("res"), python::arg("alpha") = 0.95, python::arg("beta") = 0.05));
	python::def("calcTverskyComboScore", &Shape::calcTverskyComboScore, 
				(python::arg("res"), python::arg("alpha") = 0.95, python::arg("beta") = 0.05));

	python::def("calcReferenceTotalOverlapTverskyScore", &Shape::calcReferenceTotalOverlapTverskyScore, 
				(python::arg("res"), python::arg("alpha") = 0.95));
	python::def("calcReferenceShapeTverskyScore", &Shape::calcReferenceShapeTverskyScore, 
				(python::arg("res"), python::arg("alpha") = 0.95));
	python::def("calcReferenceColorTverskyScore", &Shape::calcReferenceColorTverskyScore, 
				(python::arg("res"), python::arg("alpha") = 0.95));
	python::def("calcReferenceTverskyComboScore", &Shape::calcReferenceTverskyComboScore, 
				(python::arg("res"), python::arg("alpha") = 0.95));

	python::def("calcAlignedTotalOverlapTverskyScore", &Shape::calcAlignedTotalOverlapTverskyScore, 
				(python::arg("res"), python::arg("beta") = 0.95));
	python::def("calcAlignedShapeTverskyScore", &Shape::calcAlignedShapeTverskyScore, 
				(python::arg("res"), python::arg("beta") = 0.95));
	python::def("calcAlignedColorTverskyScore", &Shape::calcAlignedColorTverskyScore, 
				(python::arg("res"), python::arg("beta") = 0.95));
	python::def("calcAlignedTverskyComboScore", &Shape::calcAlignedTverskyComboScore, 
				(python::arg("res"), python::arg("beta") = 0.95));
}
