/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * GaussianShapeFunctionsExport.cpp 
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

#include "CDPL/Shape/GaussianShapeFunctions.hpp"
#include "CDPL/Shape/GaussianShape.hpp"
#include "CDPL/Shape/GaussianShapeFunction.hpp"
#include "CDPL/Chem/AtomContainer.hpp"
#include "CDPL/Pharm/FeatureContainer.hpp"

#include "FunctionExports.hpp"


namespace
{
	
	void generateGaussianShapeForAtoms1(CDPL::Chem::AtomContainer& atoms, CDPL::Shape::GaussianShape& shape,
										bool append, double radius, bool inc_h, double p)
	{
		CDPL::Shape::generateGaussianShape(atoms, shape, append, radius, inc_h, p);
	}

	void generateGaussianShapeForAtoms2(CDPL::Chem::AtomContainer& atoms, CDPL::Shape::GaussianShape& shape,
										const CDPL::Chem::Atom3DCoordinatesFunction& coords_func,
										bool append, double radius, bool inc_h, double p)
	{
		CDPL::Shape::generateGaussianShape(atoms, shape, coords_func, append, radius, inc_h, p);
	}

	void generateGaussianShapeForFeatures(CDPL::Pharm::FeatureContainer& features, CDPL::Shape::GaussianShape& shape,
										  bool append, double radius, bool inc_xv, double p)
	{
		CDPL::Shape::generateGaussianShape(features, shape, append, radius, inc_xv, p);
	}
}


void CDPLPythonShape::exportGaussianShapeFunctions()
{
	using namespace boost;
	using namespace CDPL;

	python::def("generateGaussianShape", &generateGaussianShapeForAtoms1,
				(python::arg("atoms"), python::arg("shape"), python::arg("append") = false,
				 python::arg("radius") = -1.0, python::arg("inc_h") = false, python::arg("p") = 2.7));
	python::def("generateGaussianShape", &generateGaussianShapeForAtoms2,
				(python::arg("atoms"), python::arg("shape"), python::arg("coords_func"), python::arg("append") = false,
				 python::arg("radius") = -1.0, python::arg("inc_h") = false, python::arg("p") = 2.7));
	python::def("generateGaussianShape", &generateGaussianShapeForFeatures,
				(python::arg("features"), python::arg("shape"), python::arg("append") = false,
				 python::arg("radius") = -1.0, python::arg("inc_xv") = false, python::arg("p") = 5.0));
	python::def("transform", &Shape::transform, (python::arg("shape"), python::arg("xform")));
	python::def("centerAndAlignPrincipalAxes", &Shape::centerAndAlignPrincipalAxes,
				(python::arg("shape"), python::arg("func"), python::arg("back_xform"), python::arg("mom_eq_thresh") = 0.15));
}
