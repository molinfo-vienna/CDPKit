/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * GaussianShapeAlignmentFunction.cpp 
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

#include <cstddef>

#include "CDPL/Shape/GaussianShapeAlignmentFunction.hpp"
#include "CDPL/Shape/GaussianShapeOverlapFunction.hpp"
#include "CDPL/Shape/GaussianShapeFunction.hpp"
#include "CDPL/Shape/GaussianShape.hpp"
#include "CDPL/Shape/UtilityFunctions.hpp"
#include "CDPL/Math/Matrix.hpp"


using namespace CDPL;


const double Shape::GaussianShapeAlignmentFunction::DEF_QUATERNION_UNITY_DEVIATION_PENALTY_FACTOR = 1000.0;


Shape::GaussianShapeAlignmentFunction::GaussianShapeAlignmentFunction(GaussianShapeOverlapFunction& func):
	overlapFunc(&func), quatPenaltyFactor(DEF_QUATERNION_UNITY_DEVIATION_PENALTY_FACTOR)
{}

void Shape::GaussianShapeAlignmentFunction::setQuaternionUnityDeviationPenaltyFactor(double factor)
{
	quatPenaltyFactor = factor;
}
						
double Shape::GaussianShapeAlignmentFunction::getQuaternionUnityDeviationPenaltyFactor() const
{
	return quatPenaltyFactor;
}

double Shape::GaussianShapeAlignmentFunction::operator()(const QuaternionTransformation& xform_quat) const
{
	QuaternionTransformation::ConstPointer xform_quat_data = xform_quat.getData();
	Math::Matrix4D xform_mtx;
	
	double quat_non_unity_pen = 1.0 - (xform_quat_data[0] * xform_quat_data[0] + xform_quat_data[1] * xform_quat_data[1] + 
									   xform_quat_data[2] * xform_quat_data[2] + xform_quat_data[3] * xform_quat_data[3]);

	quat_non_unity_pen *= 0.5 * quatPenaltyFactor * quat_non_unity_pen;

	quaternionToMatrix(xform_quat, xform_mtx);

	return (quat_non_unity_pen - overlapFunc->calcOverlap(xform_mtx, false));
}

double Shape::GaussianShapeAlignmentFunction::operator()(const QuaternionTransformation& xform_quat, QuaternionTransformation& grad)
{
	grad.clear();

	const GaussianShapeFunction* shape_func = overlapFunc->getShapeFunction(false);

	if (!shape_func)
		return 0.0;
	
	const GaussianShape* shape = shape_func->getShape();

	if (!shape)
		return 0.0;

	QuaternionTransformation::ConstPointer xform_quat_data = xform_quat.getData();
	QuaternionTransformation::Pointer grad_data = grad.getData();
	Math::Matrix4D xform_mtx;

	quaternionToMatrix(xform_quat, xform_mtx);
	
	double neg_overlap = -overlapFunc->calcOverlapGradient(xform_mtx, coordsGradient, false);

	for (std::size_t i = 0, num_elem = shape->getNumElements(); i < num_elem; i++) {
		const Math::Vector3D::ConstPointer elem_pos = shape->getElement(i).getPosition().getData();
		const Math::Vector3D::ConstPointer pos_grad = coordsGradient[i].getData();
		
		grad_data[0] +=
			pos_grad[0] * ( xform_quat_data[0] * elem_pos[0] - xform_quat_data[3] * elem_pos[1] + xform_quat_data[2] * elem_pos[2]) +
			pos_grad[1] * ( xform_quat_data[3] * elem_pos[0] + xform_quat_data[0] * elem_pos[1] - xform_quat_data[1] * elem_pos[2]) +
			pos_grad[2] * (-xform_quat_data[2] * elem_pos[0] + xform_quat_data[1] * elem_pos[1] + xform_quat_data[0] * elem_pos[2]);

		grad_data[1] +=
			pos_grad[0] * ( xform_quat_data[1] * elem_pos[0] - xform_quat_data[2] * elem_pos[1] + xform_quat_data[3] * elem_pos[2]) +
			pos_grad[1] * ( xform_quat_data[2] * elem_pos[0] - xform_quat_data[1] * elem_pos[1] - xform_quat_data[0] * elem_pos[2]) +
			pos_grad[2] * ( xform_quat_data[3] * elem_pos[0] + xform_quat_data[0] * elem_pos[1] - xform_quat_data[1] * elem_pos[2]);

		grad_data[2] +=
			pos_grad[0] * (-xform_quat_data[2] * elem_pos[0] + xform_quat_data[1] * elem_pos[1] + xform_quat_data[0] * elem_pos[2]) +
			pos_grad[1] * ( xform_quat_data[1] * elem_pos[0] + xform_quat_data[2] * elem_pos[1] + xform_quat_data[3] * elem_pos[2]) +
			pos_grad[2] * (-xform_quat_data[0] * elem_pos[0] + xform_quat_data[3] * elem_pos[1] - xform_quat_data[2] * elem_pos[2]);

		grad_data[3] +=
			pos_grad[0] * (-xform_quat_data[3] * elem_pos[0] - xform_quat_data[0] * elem_pos[1] + xform_quat_data[1] * elem_pos[2]) +
			pos_grad[1] * ( xform_quat_data[0] * elem_pos[0] - xform_quat_data[3] * elem_pos[1] + xform_quat_data[2] * elem_pos[2]) +
			pos_grad[2] * ( xform_quat_data[1] * elem_pos[0] + xform_quat_data[2] * elem_pos[1] + xform_quat_data[3] * elem_pos[2]);

		grad_data[4] -= pos_grad[0];
		grad_data[5] -= pos_grad[1];
		grad_data[6] -= pos_grad[2];
	}
	
	double quat_non_unity_pen = 1.0 - (xform_quat_data[0] * xform_quat_data[0] + xform_quat_data[1] * xform_quat_data[1] + 
									   xform_quat_data[2] * xform_quat_data[2] + xform_quat_data[3] * xform_quat_data[3]);
	double grad_factor = quatPenaltyFactor * quat_non_unity_pen;

	for (std::size_t i = 0; i < 4; i++)
		grad_data[i] = -2.0 * (grad_data[i] + grad_factor * xform_quat_data[i]);
	
	return (neg_overlap + 0.5 * quatPenaltyFactor * quat_non_unity_pen * quat_non_unity_pen);
}
