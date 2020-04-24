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

#include "CDPL/Shape/GaussianShapeAlignmentFunction.hpp"
#include "CDPL/Shape/GaussianShapeOverlapFunction.hpp"
#include "CDPL/Shape/UtilityFunctions.hpp"
#include "CDPL/Math/Matrix.hpp"


using namespace CDPL;


namespace
{

	const double QUAT_UNITY_DEV_PENALTY_FACTOR = 10.0;
}


Shape::GaussianShapeAlignmentFunction::GaussianShapeAlignmentFunction(GaussianShapeOverlapFunction& func):
	overlapFunc(&func)
{}

double Shape::GaussianShapeAlignmentFunction::operator()(const QuaternionTransformation& xform_quat) const
{
	QuaternionTransformation::ConstPointer xform_quat_data = xform_quat.getData();
	Math::Matrix4D xform_mtx;
	
	double quat_non_unity_pen = 1.0 - (xform_quat_data[0] * xform_quat_data[0] + xform_quat_data[1] * xform_quat_data[1] + 
								 xform_quat_data[2] * xform_quat_data[2] + xform_quat_data[3] * xform_quat_data[3]);

	quat_non_unity_pen *= 0.5 * QUAT_UNITY_DEV_PENALTY_FACTOR * quat_non_unity_pen;
		
	quaternionToMatrix(xform_quat, xform_mtx);

	return (quat_non_unity_pen - overlapFunc->calcOverlap(xform_mtx));
}

double Shape::GaussianShapeAlignmentFunction::operator()(const QuaternionTransformation& xform_quat, QuaternionTransformation& grad)
{
	QuaternionTransformation::ConstPointer xform_quat_data = xform_quat.getData();
	QuaternionTransformation::Pointer grad_data = grad.getData();

	grad.clear();
	
	double ret_val = calcQuaternionNonUnityPenalityGradient(xform_quat_data, grad_data);

	ret_val += calcShapeOverlapGradient(xform_quat, grad_data);
	
	return ret_val;
}

double Shape::GaussianShapeAlignmentFunction::calcShapeOverlapGradient(const QuaternionTransformation& xform_quat,
																	   QuaternionTransformation::Pointer grad_data)
{
	Math::Matrix4D xform_mtx;

	quaternionToMatrix(xform_quat, xform_mtx);

	double overlap = overlapFunc->calcOverlapGradient(xform_mtx, coordsGradient);
	
	return -overlap;
}

double Shape::GaussianShapeAlignmentFunction::calcQuaternionNonUnityPenalityGradient(QuaternionTransformation::ConstPointer xform_quat_data,
																					 QuaternionTransformation::Pointer grad_data) const
{
	double quat_non_unity_pen = 1.0 - (xform_quat_data[0] * xform_quat_data[0] + xform_quat_data[1] * xform_quat_data[1] + 
									   xform_quat_data[2] * xform_quat_data[2] + xform_quat_data[3] * xform_quat_data[3]);
	double grad_factor = -2.0 * QUAT_UNITY_DEV_PENALTY_FACTOR * quat_non_unity_pen;

	for (std::size_t i = 0; i < 4; i++)
		grad_data[i] += grad_factor * xform_quat_data[i];
	
	quat_non_unity_pen *= 0.5 * QUAT_UNITY_DEV_PENALTY_FACTOR * quat_non_unity_pen;

	return quat_non_unity_pen;
}
