/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * RegularSpatialGridFunctionExport.cpp 
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

#include "CDPL/Math/RegularSpatialGrid.hpp"
#include "CDPL/Math/Vector.hpp"

#include "FunctionExports.hpp"


namespace
{

	template <typename T>
	T interpolateTrilinear(const CDPL::Math::RegularSpatialGrid<T>& grid, const CDPL::Math::CVector<T, 3>& pos, bool local_pos)
	{
		return CDPL::Math::interpolateTrilinear(grid, pos, local_pos);
	}
}


void CDPLPythonMath::exportRegularSpatialGridFunctions()
{
	using namespace boost;

	python::def("interpolateTrilinear", &interpolateTrilinear<float>, (python::arg("grid"), python::arg("pos"), python::arg("local_pos")));
	python::def("interpolateTrilinear", &interpolateTrilinear<double>, (python::arg("grid"), python::arg("pos"), python::arg("local_pos")));
}
