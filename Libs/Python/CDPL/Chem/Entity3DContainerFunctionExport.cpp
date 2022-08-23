/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * Entity3DContainerFunctionExport.cpp 
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

#include "CDPL/Chem/Entity3DContainer.hpp"
#include "CDPL/Chem/Entity3DContainerFunctions.hpp"
#include "CDPL/Math/VectorArray.hpp"
#include "CDPL/Math/Matrix.hpp"

#include "FunctionExports.hpp"
#include "FunctionWrapper.hpp"


namespace
{

	MAKE_FUNCTION_WRAPPER2(bool, calcCentroid, CDPL::Chem::Entity3DContainer&, CDPL::Math::Vector3D&);
	MAKE_FUNCTION_WRAPPER2(void, calcGeometricalDistanceMatrix, CDPL::Chem::Entity3DContainer&, CDPL::Math::DMatrix&);

	MAKE_FUNCTION_WRAPPER3(void, get3DCoordinates, CDPL::Chem::Entity3DContainer&, CDPL::Math::Vector3DArray&, bool);
	MAKE_FUNCTION_WRAPPER3(bool, insideBoundingBox, CDPL::Chem::Entity3DContainer&, const CDPL::Math::Vector3D&, const CDPL::Math::Vector3D&);
	MAKE_FUNCTION_WRAPPER3(bool, intersectsBoundingBox, CDPL::Chem::Entity3DContainer&, const CDPL::Math::Vector3D&, const CDPL::Math::Vector3D&);

	MAKE_FUNCTION_WRAPPER4(void, calcBoundingBox, CDPL::Chem::Entity3DContainer&, CDPL::Math::Vector3D&, CDPL::Math::Vector3D&, bool);
}


void CDPLPythonChem::exportEntity3DContainerFunctions()
{
	using namespace boost;
	using namespace CDPL;

	python::def("calcGeometricalDistanceMatrix", &calcGeometricalDistanceMatrixWrapper2, (python::arg("cntnr"), python::arg("mtx")));
	
	python::def("get3DCoordinates", &get3DCoordinatesWrapper3, (python::arg("cntnr"), python::arg("coords"), python::arg("append") = false));
	python::def("set3DCoordinates", &Chem::set3DCoordinates, (python::arg("cntnr"), python::arg("coords")));
	python::def("transform3DCoordinates", &Chem::transform3DCoordinates, (python::arg("cntnr"), python::arg("mtx")));

	python::def("calcCentroid", &calcCentroidWrapper2, (python::arg("cntnr"), python::arg("ctr")));
	python::def("calcBoundingBox", &calcBoundingBoxWrapper4, (python::arg("cntnr"), python::arg("min"), 
															  python::arg("max"), (python::arg("reset") = true)));
	python::def("insideBoundingBox", &insideBoundingBoxWrapper3, (python::arg("cntnr"), python::arg("min"), python::arg("max")));
	python::def("intersectsBoundingBox", &intersectsBoundingBoxWrapper3, (python::arg("cntnr"), python::arg("min"), 
																		  python::arg("max")));
}
