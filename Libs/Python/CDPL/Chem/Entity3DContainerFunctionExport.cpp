/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * Entity3DContainerFunctionExport.cpp 
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

#include "CDPL/Chem/Entity3DContainer.hpp"
#include "CDPL/Chem/Entity3DContainerFunctions.hpp"
#include "CDPL/Math/VectorArray.hpp"
#include "CDPL/Math/Matrix.hpp"

#include "FunctionExports.hpp"
#include "FunctionWrapper.hpp"


namespace
{

	MAKE_FUNCTION_WRAPPER1(double, calcGeometricalRadius, CDPL::Chem::Entity3DContainer&);
	MAKE_FUNCTION_WRAPPER1(double, calcGeometricalDiameter, CDPL::Chem::Entity3DContainer&);

	MAKE_FUNCTION_WRAPPER2(bool, calcCentroid, CDPL::Chem::Entity3DContainer&, CDPL::Math::Vector3D&);
	MAKE_FUNCTION_WRAPPER2(void, get3DCoordinates, CDPL::Chem::Entity3DContainer&, CDPL::Math::Vector3DArray&);
	MAKE_FUNCTION_WRAPPER2(void, calcGeometricalDistanceMatrix, CDPL::Chem::Entity3DContainer&, CDPL::Math::DMatrix&);
}


void CDPLPythonChem::exportEntity3DContainerFunctions()
{
	using namespace boost;
	using namespace CDPL;

	python::def("calcGeometricalDistanceMatrix", &calcGeometricalDistanceMatrixWrapper2, (python::arg("cntnr"), python::arg("mtx")));
	python::def("calcGeometricalRadius", &calcGeometricalRadiusWrapper1, python::arg("cntnr"));
	python::def("calcGeometricalDiameter", &calcGeometricalDiameterWrapper1, python::arg("cntnr"));

	python::def("get3DCoordinates", &get3DCoordinatesWrapper2, (python::arg("cntnr"),  python::arg("coords")));
	python::def("set3DCoordinates", &Chem::set3DCoordinates, (python::arg("cntnr"), python::arg("coords")));

	python::def("calcCentroid", &calcCentroidWrapper2, (python::arg("cntnr"), python::arg("ctr")));
}
