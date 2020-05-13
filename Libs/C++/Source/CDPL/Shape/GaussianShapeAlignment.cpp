/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * GaussianShapeAlignment.cpp 
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

#include <boost/math/special_functions/fpclassify.hpp>
#include <boost/bind.hpp>

#include "CDPL/Shape/GaussianShapeAlignment.hpp"
#include "CDPL/Shape/GaussianShapeFunction.hpp"
#include "CDPL/Shape/GaussianShape.hpp"
#include "CDPL/Shape/UtilityFunctions.hpp"
#include "CDPL/Base/Exceptions.hpp"

#include "Utilities.hpp"


using namespace CDPL;


namespace
{
	const double QUATERNION_UNITY_DEVIATION_PENALTY_FACTOR = 10000.0;

}


Shape::GaussianShapeAlignment::GaussianShapeAlignment():
	overlapFunc(&defOverlapFunc), startGen(&defStartGen), refShapeFunc(0),
	minimizer(boost::bind(&GaussianShapeAlignment::calcAlignmentFunctionValue, this, _1),
			  boost::bind(&GaussianShapeAlignment::calcAlignmentFunctionGradient, this, _1, _2))
{}

Shape::GaussianShapeAlignment::GaussianShapeAlignment(GaussianShapeFunction& ref_shape_func):
	overlapFunc(&defOverlapFunc), startGen(&defStartGen),
	minimizer(boost::bind(&GaussianShapeAlignment::calcAlignmentFunctionValue, this, _1),
			  boost::bind(&GaussianShapeAlignment::calcAlignmentFunctionGradient, this, _1, _2))
{
   setReferenceShapeFunction(ref_shape_func);
}

Shape::GaussianShapeAlignment::GaussianShapeAlignment(GaussianShapeOverlapFunction& overlap_func):
	overlapFunc(&overlap_func), startGen(&defStartGen), refShapeFunc(0),
	minimizer(boost::bind(&GaussianShapeAlignment::calcAlignmentFunctionValue, this, _1),
			  boost::bind(&GaussianShapeAlignment::calcAlignmentFunctionGradient, this, _1, _2))
{}

Shape::GaussianShapeAlignment::GaussianShapeAlignment(GaussianShapeOverlapFunction& overlap_func, GaussianShapeFunction& ref_shape_func):
	overlapFunc(&overlap_func), startGen(&defStartGen),
	minimizer(boost::bind(&GaussianShapeAlignment::calcAlignmentFunctionValue, this, _1),
			  boost::bind(&GaussianShapeAlignment::calcAlignmentFunctionGradient, this, _1, _2))
{
   setReferenceShapeFunction(ref_shape_func);
}

Shape::GaussianShapeAlignment::~GaussianShapeAlignment() {}

void Shape::GaussianShapeAlignment::setOverlapFunction(GaussianShapeOverlapFunction& func)
{
	overlapFunc = &func;

	if (refShapeFunc)
		overlapFunc->setShapeFunction(*refShapeFunc, true);
}
			
Shape::GaussianShapeOverlapFunction& Shape::GaussianShapeAlignment::getOverlapFunction() const
{
	return *overlapFunc;
}

void Shape::GaussianShapeAlignment::setStartGenerator(PrincipalAxesAlignmentStartGenerator& gen)
{
	startGen = &gen;

	if (refShapeFunc)
		startGen->setup(*refShapeFunc, toRefPoseXForm);
}
			
Shape::GaussianShapeAlignmentStartGenerator& Shape::GaussianShapeAlignment::getStartGenerator() const
{
	return *startGen;
}

void Shape::GaussianShapeAlignment::setReferenceShapeFunction(GaussianShapeFunction& func)
{
	refShapeFunc = &func;
	
    overlapFunc->setShapeFunction(func, true);
	startGen->setup(func, toRefPoseXForm);
}

Shape::GaussianShapeFunction* Shape::GaussianShapeAlignment::getReferenceShapeFunction() const
{
    return refShapeFunc;
}

bool Shape::GaussianShapeAlignment::align(const GaussianShapeFunction& func)
{
	results.clear();

	if (!refShapeFunc || !refShapeFunc->getShape() || refShapeFunc->getShape()->getNumElements() == 0)
		return false;

	if (!func.getShape() || func.getShape()->getNumElements() == 0)
		return false;

	Math::Matrix4D ctr_xform;
	
	if (!startGen->generate(func, ctr_xform))
		return false;

	getCoordinates(*func.getShape(), startCoords);

	transCoords.resize(startCoords.getSize());

	transform(transCoords, ctr_xform, startCoords);

	transCoords.swap(startCoords);
	
	std::size_t num_starts = startGen->getNumStartTransforms();
	
	results.reserve(num_starts);

	QuaternionTransformation opt_xform;
	QuaternionTransformation opt_xform_grad;
	Math::Matrix4D opt_xform_mtx;

	overlapFunc->setShapeFunction(func, false);
	
	for (std::size_t i = 0; i < num_starts; i++) {
		opt_xform = startGen->getStartTransform(i);
		
		minimizer.setup(opt_xform, opt_xform_grad, 0.01, 0.1);
		minimizer.minimize(opt_xform, opt_xform_grad, 200, 0.1, -1.0, false);
		
	    if (boost::math::isfinite(minimizer.getFunctionValue())) {  // sanity check
			normalize(opt_xform);
			quaternionToMatrix(opt_xform, opt_xform_mtx);
			transform(transCoords, opt_xform_mtx, startCoords);

			double opt_overlap = overlapFunc->calcOverlap(transCoords);
	
			opt_xform_mtx = toRefPoseXForm * opt_xform_mtx * ctr_xform;
		
			results.push_back(Result(opt_xform_mtx, opt_overlap));
		}
	}
	
	return !results.empty();
}

std::size_t Shape::GaussianShapeAlignment::getNumResults() const
{
	return results.size();
}

const Shape::GaussianShapeAlignment::Result& Shape::GaussianShapeAlignment::getResult(std::size_t idx) const
{
	if (idx >= results.size())
		throw Base::IndexError("GaussianShapeAlignment: result index out of bounds");

	return results[idx];
}

Shape::GaussianShapeAlignment::ConstResultIterator Shape::GaussianShapeAlignment::getResultsBegin() const
{
	return results.begin();
}

Shape::GaussianShapeAlignment::ConstResultIterator Shape::GaussianShapeAlignment::getResultsEnd() const
{
	return results.end();
}
/*
double Shape::GaussianShapeAlignment::calcAlignmentFunctionValue(const QuaternionTransformation& xform_quat)
{
	QuaternionTransformation::ConstPointer xform_quat_data = xform_quat.getData();
	Math::Matrix4D xform_mtx;
	
	double quat_non_unity_pen = 1.0 - (xform_quat_data[0] * xform_quat_data[0] + xform_quat_data[1] * xform_quat_data[1] + 
									   xform_quat_data[2] * xform_quat_data[2] + xform_quat_data[3] * xform_quat_data[3]);

	quat_non_unity_pen *= 0.5 * QUATERNION_UNITY_DEVIATION_PENALTY_FACTOR * quat_non_unity_pen;

	quaternionToMatrix(xform_quat, xform_mtx);
	transform(transCoords, xform_mtx, startCoords);
	
	return (quat_non_unity_pen - overlapFunc->calcOverlap(transCoords));	
}
*/
double Shape::GaussianShapeAlignment::calcAlignmentFunctionValue(const QuaternionTransformation& xform_quat)
{
	QuaternionTransformation::ConstPointer xform_quat_data = xform_quat.getData();
	Math::Matrix4D xform_mtx;
	double quat_norm_sqrd = xform_quat_data[0] * xform_quat_data[0] + xform_quat_data[1] * xform_quat_data[1] + 
		xform_quat_data[2] * xform_quat_data[2] + xform_quat_data[3] * xform_quat_data[3];
	
	double quat_non_unity_pen = 1.0 - quat_norm_sqrd;

	quat_non_unity_pen *= 0.5 * QUATERNION_UNITY_DEVIATION_PENALTY_FACTOR * quat_non_unity_pen;

	double inv_quat_norm = 1.0 / std::sqrt(quat_norm_sqrd);
	QuaternionTransformation norm_xform_quat;
	QuaternionTransformation::Pointer norm_xform_quat_data = norm_xform_quat.getData();

	for (std::size_t i = 0; i < 4; i++)
		norm_xform_quat_data[i] = xform_quat_data[i] * inv_quat_norm;

	for (std::size_t i = 4; i < 7; i++)
		norm_xform_quat_data[i] = xform_quat_data[i];
		
	quaternionToMatrix(norm_xform_quat, xform_mtx);
	transform(transCoords, xform_mtx, startCoords);

	return (quat_non_unity_pen - overlapFunc->calcOverlap(transCoords));
}
/*
double Shape::GaussianShapeAlignment::calcAlignmentFunctionGradient(const QuaternionTransformation& xform_quat, QuaternionTransformation& xform_quat_grad)
{
	xform_quat_grad.clear();

	QuaternionTransformation::ConstPointer xform_quat_data = xform_quat.getData();
	QuaternionTransformation::Pointer grad_data = xform_quat_grad.getData();
	Math::Matrix4D xform_mtx;

	quaternionToMatrix(xform_quat, xform_mtx);
	transform(transCoords, xform_mtx, startCoords);

	double neg_overlap = -overlapFunc->calcOverlapGradient(transCoords, coordsGradient);

	for (std::size_t i = 0, num_elem = startCoords.getSize(); i < num_elem; i++) {
		const Math::Vector3D::ConstPointer elem_pos = startCoords[i].getData();
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
	double pen_grad_factor = QUATERNION_UNITY_DEVIATION_PENALTY_FACTOR * quat_non_unity_pen;

	for (std::size_t i = 0; i < 4; i++)
		grad_data[i] = -2.0 * (grad_data[i] + pen_grad_factor * xform_quat_data[i]);

	return (neg_overlap + 0.5 * pen_grad_factor * quat_non_unity_pen);
}
*/
double Shape::GaussianShapeAlignment::calcAlignmentFunctionGradient(const QuaternionTransformation& xform_quat, QuaternionTransformation& xform_quat_grad)
{
    xform_quat_grad.clear();

	QuaternionTransformation::ConstPointer xform_quat_data = xform_quat.getData();
	QuaternionTransformation::Pointer grad_data = xform_quat_grad.getData();
	Math::Matrix4D xform_mtx;
	Math::Matrix4D::ConstArrayPointer xform_mtx_data = xform_mtx.getData();

	double quat_norm_sqrd = xform_quat_data[0] * xform_quat_data[0] + xform_quat_data[1] * xform_quat_data[1] + 
		xform_quat_data[2] * xform_quat_data[2] + xform_quat_data[3] * xform_quat_data[3];

	double inv_quat_norm_sqrd = 1.0 / quat_norm_sqrd;
	double inv_quat_norm = std::sqrt(inv_quat_norm_sqrd);
	QuaternionTransformation norm_xform_quat;
	QuaternionTransformation::Pointer norm_xform_quat_data = norm_xform_quat.getData();

	for (std::size_t i = 0; i < 4; i++)
		norm_xform_quat_data[i] = xform_quat_data[i] * inv_quat_norm;

	for (std::size_t i = 4; i < 7; i++)
		norm_xform_quat_data[i] = xform_quat_data[i];
		
	quaternionToMatrix(norm_xform_quat, xform_mtx);
	transform(transCoords, xform_mtx, startCoords);

	double neg_overlap = -overlapFunc->calcOverlapGradient(transCoords, coordsGradient);

	double dq1[3][3] = { { xform_quat_data[0], -xform_quat_data[3],  xform_quat_data[2] },
						 { xform_quat_data[3],  xform_quat_data[0], -xform_quat_data[1] },
						 {-xform_quat_data[2],  xform_quat_data[1],  xform_quat_data[0] } };

	double dq2[3][3] = { { xform_quat_data[1], -xform_quat_data[2],  xform_quat_data[3] },
						 { xform_quat_data[2], -xform_quat_data[1], -xform_quat_data[0] },
						 { xform_quat_data[3],  xform_quat_data[0], -xform_quat_data[1] } };

	double dq3[3][3] = { {-xform_quat_data[2],  xform_quat_data[1],  xform_quat_data[0] },
						 { xform_quat_data[1],  xform_quat_data[2],  xform_quat_data[3] },
						 {-xform_quat_data[0],  xform_quat_data[3], -xform_quat_data[2] } };

	double dq4[3][3] = { {-xform_quat_data[3], -xform_quat_data[0],  xform_quat_data[1] },
						 { xform_quat_data[0], -xform_quat_data[3],  xform_quat_data[2] },
						 { xform_quat_data[1],  xform_quat_data[2],  xform_quat_data[3] } };

	for (std::size_t i = 0; i < 3; i++)
		for (std::size_t j = 0; j < 3; j++) {
			dq1[i][j] = (dq1[i][j] - xform_mtx_data[i][j] * xform_quat_data[0]) * inv_quat_norm_sqrd;
			dq2[i][j] = (dq2[i][j] - xform_mtx_data[i][j] * xform_quat_data[1]) * inv_quat_norm_sqrd;
			dq3[i][j] = (dq3[i][j] - xform_mtx_data[i][j] * xform_quat_data[2]) * inv_quat_norm_sqrd;
			dq4[i][j] = (dq4[i][j] - xform_mtx_data[i][j] * xform_quat_data[3]) * inv_quat_norm_sqrd;
		}
	
	for (std::size_t i = 0, num_elem = startCoords.getSize(); i < num_elem; i++) {
		const Math::Vector3D::ConstPointer elem_pos = startCoords[i].getData();
		const Math::Vector3D::ConstPointer pos_grad = coordsGradient[i].getData();
		
		grad_data[0] +=
			pos_grad[0] * ( dq1[0][0] * elem_pos[0] + dq1[0][1] * elem_pos[1] + dq1[0][2] * elem_pos[2]) +
			pos_grad[1] * ( dq1[1][0] * elem_pos[0] + dq1[1][1] * elem_pos[1] + dq1[1][2] * elem_pos[2]) +
			pos_grad[2] * ( dq1[2][0] * elem_pos[0] + dq1[2][1] * elem_pos[1] + dq1[2][2] * elem_pos[2]);

		grad_data[1] +=
			pos_grad[0] * ( dq2[0][0] * elem_pos[0] + dq2[0][1] * elem_pos[1] + dq2[0][2] * elem_pos[2]) +
			pos_grad[1] * ( dq2[1][0] * elem_pos[0] + dq2[1][1] * elem_pos[1] + dq2[1][2] * elem_pos[2]) +
			pos_grad[2] * ( dq2[2][0] * elem_pos[0] + dq2[2][1] * elem_pos[1] + dq2[2][2] * elem_pos[2]);

		grad_data[2] +=
			pos_grad[0] * ( dq3[0][0] * elem_pos[0] + dq3[0][1] * elem_pos[1] + dq3[0][2] * elem_pos[2]) +
			pos_grad[1] * ( dq3[1][0] * elem_pos[0] + dq3[1][1] * elem_pos[1] + dq3[1][2] * elem_pos[2]) +
			pos_grad[2] * ( dq3[2][0] * elem_pos[0] + dq3[2][1] * elem_pos[1] + dq3[2][2] * elem_pos[2]);

		grad_data[3] +=
			pos_grad[0] * ( dq4[0][0] * elem_pos[0] + dq4[0][1] * elem_pos[1] + dq4[0][2] * elem_pos[2]) +
			pos_grad[1] * ( dq4[1][0] * elem_pos[0] + dq4[1][1] * elem_pos[1] + dq4[1][2] * elem_pos[2]) +
			pos_grad[2] * ( dq4[2][0] * elem_pos[0] + dq4[2][1] * elem_pos[1] + dq4[2][2] * elem_pos[2]);

		grad_data[4] -= pos_grad[0];
		grad_data[5] -= pos_grad[1];
		grad_data[6] -= pos_grad[2];
	}
	
	double quat_non_unity_pen = 1.0 - quat_norm_sqrd;
	double pen_grad_factor = QUATERNION_UNITY_DEVIATION_PENALTY_FACTOR * quat_non_unity_pen;

	for (std::size_t i = 0; i < 4; i++)
		grad_data[i] = -2.0 * (grad_data[i] + pen_grad_factor * xform_quat_data[i]);
	
	return (neg_overlap + 0.5 * pen_grad_factor * quat_non_unity_pen);
}
