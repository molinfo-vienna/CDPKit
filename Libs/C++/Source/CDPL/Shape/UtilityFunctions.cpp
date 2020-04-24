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
#include <algorithm>

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
			
void Shape::matrixToQuaternion(const Math::Matrix4D& mtx, QuaternionTransformation& quat)
{
    Math::Matrix4D::ConstArrayPointer mtx_data = mtx.getData();
    QuaternionTransformation::Pointer quat_data = quat.getData();
    Math::Matrix4D tmp;
    Math::Matrix4D::ArrayPointer tmp_data = tmp.getData();
    Math::Vector4D eigen_vals;
    Math::Vector4D::ConstPointer eigen_vals_data = eigen_vals.getData();
    Math::Matrix4D eigen_vecs;
    Math::Matrix4D::ConstArrayPointer eigen_vecs_data = eigen_vecs.getData();

	tmp_data[0][0] = (mtx_data[0][0] - mtx_data[1][1] - mtx_data[2][2]) / 3.0;
    tmp_data[0][1] = (mtx_data[0][1] + mtx_data[1][0]) / 3.0;
    tmp_data[0][2] = (mtx_data[0][2] + mtx_data[2][0]) / 3.0;
    tmp_data[0][3] = (mtx_data[2][1] - mtx_data[1][2]) / 3.0;
	
    tmp_data[1][0] = tmp_data[0][1];
    tmp_data[1][1] = (mtx_data[1][1] - mtx_data[0][0] - mtx_data[2][2]) / 3.0;
    tmp_data[1][2] = (mtx_data[1][2] + mtx_data[2][1]) / 3.0;
    tmp_data[1][3] = (mtx_data[0][2] - mtx_data[2][0]) / 3.0;
	
    tmp_data[2][0] = tmp_data[0][2];
	tmp_data[2][1] = tmp_data[1][2];
    tmp_data[2][2] = (mtx_data[2][2] - mtx_data[0][0] - mtx_data[1][1]) / 3.0;
    tmp_data[2][3] = (mtx_data[1][0] - mtx_data[0][1]) / 3.0;

	tmp_data[3][0] = tmp_data[0][3];
    tmp_data[3][1] = tmp_data[1][3];
    tmp_data[3][2] = tmp_data[2][3];
	tmp_data[3][3] = (mtx_data[0][0] + mtx_data[1][1] + mtx_data[2][2]) / 3.0;
    
    jacobiDiagonalize(tmp, eigen_vals, eigen_vecs);

    std::size_t largest_eval_idx = 0;

    for (std::size_t i = 1; i < 4; i++)
		if (eigen_vals_data[i] > eigen_vals_data[largest_eval_idx])
			largest_eval_idx = i;

    quat_data[0] = eigen_vecs_data[3][largest_eval_idx];
    quat_data[1] = eigen_vecs_data[0][largest_eval_idx];
    quat_data[2] = eigen_vecs_data[1][largest_eval_idx];
    quat_data[3] = eigen_vecs_data[2][largest_eval_idx];
    quat_data[4] = mtx_data[0][3];
    quat_data[5] = mtx_data[1][3];
    quat_data[6] = mtx_data[2][3];
}

void Shape::quaternionToMatrix(const QuaternionTransformation& quat, Math::Matrix4D& mtx)
{
    Math::Matrix4D::ArrayPointer mtx_data = mtx.getData();
    QuaternionTransformation::ConstPointer quat_data = quat.getData();

    mtx_data[0][0] = (quat_data[0] * quat_data[0] + quat_data[1] * quat_data[1] - quat_data[2] * quat_data[2] - quat_data[3] * quat_data[3]); // a^2 + b^2 - c^2 - d^2
    mtx_data[0][1] = 2.0 * (quat_data[1] * quat_data[2] - quat_data[0] * quat_data[3]); // 2(bc - ad)
    mtx_data[0][2] = 2.0 * (quat_data[1] * quat_data[3] + quat_data[0] * quat_data[2]); // 2(bd + ac)
    mtx_data[0][3] = quat_data[4];
    mtx_data[1][0] = 2.0 * (quat_data[1] * quat_data[2] + quat_data[0] * quat_data[3]); // 2(bc + ad)
    mtx_data[1][1] = (quat_data[0] * quat_data[0] - quat_data[1] * quat_data[1] + quat_data[2] * quat_data[2] - quat_data[3] * quat_data[3]); // a^2 - b^2 + c^2 - d^2
    mtx_data[1][2] = 2.0 * (quat_data[2] * quat_data[3] - quat_data[0] * quat_data[1]); // 2(cd - ab)
    mtx_data[1][3] = quat_data[5];
    mtx_data[2][0] = 2.0 * (quat_data[1] * quat_data[3] - quat_data[0] * quat_data[2]); // 2(bd - ac)
    mtx_data[2][1] = 2.0 * (quat_data[2] * quat_data[3] + quat_data[0] * quat_data[1]); // 2(cd + ab)
    mtx_data[2][2] = (quat_data[0] * quat_data[0] - quat_data[1] * quat_data[1] - quat_data[2] * quat_data[2] + quat_data[3] * quat_data[3]); // a^2 - b^2 - c^2 + d^2
    mtx_data[2][3] = quat_data[6];
    mtx_data[3][0] = 0.0;
    mtx_data[3][1] = 0.0;
    mtx_data[3][2] = 0.0;
    mtx_data[3][3] = 1.0;
}
