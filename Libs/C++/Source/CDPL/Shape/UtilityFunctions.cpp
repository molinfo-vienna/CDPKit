/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * UtilityFunctions.cpp 
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

 
#include "StaticInit.hpp"

#include <utility>

#include "CDPL/Shape/UtilityFunctions.hpp"
#include "CDPL/Math/JacobiDiagonalization.hpp"
#include "CDPL/Math/MatrixProxy.hpp"


using namespace CDPL;


void Shape::calcQuadrupoleTensorEigenDecomposition(const Math::Matrix3D& quad_tensor, Math::Matrix3D& eigen_vecs,
						   Math::Vector3D& eigen_vals)
{
    Math::Matrix3D tmp_tensor(quad_tensor);
	
    jacobiDiagonalize(tmp_tensor, eigen_vals, eigen_vecs);
}

void Shape::calcPrincipalAxes(const Math::Matrix3D& quad_tensor, Math::Vector3D& x_axis, Math::Vector3D& y_axis,
			      Math::Vector3D& z_axis, Math::Vector3D& shape_dims)
{
    Math::Matrix3D eigen_vecs;
	
    calcQuadrupoleTensorEigenDecomposition(quad_tensor, eigen_vecs, shape_dims);

    Math::Vector3D::Pointer shape_dims_data = shape_dims.getData();
    std::pair<double, int> ordered_shape_dims[3] = { std::make_pair(shape_dims_data[0], 0),
						     std::make_pair(shape_dims_data[1], 1),
						     std::make_pair(shape_dims_data[2], 2) };

    std::sort(ordered_shape_dims, ordered_shape_dims + 3);

    shape_dims_data[0] = ordered_shape_dims[2].first;
    shape_dims_data[1] = ordered_shape_dims[1].first;
    shape_dims_data[2] = ordered_shape_dims[0].first;
	
    x_axis.assign(column(eigen_vecs, ordered_shape_dims[2].second));
    y_axis.assign(column(eigen_vecs, ordered_shape_dims[1].second));
    z_axis.assign(crossProd(x_axis, y_axis));
    y_axis.assign(crossProd(z_axis, x_axis));

    x_axis /= length(x_axis);
    y_axis /= length(y_axis);
    z_axis /= length(z_axis);
}
