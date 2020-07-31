/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * GaussianShapeFunctionAlignment.cpp 
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

#include "CDPL/Shape/GaussianShapeFunctionAlignment.hpp"
#include "CDPL/Shape/GaussianShapeFunction.hpp"
#include "CDPL/Shape/UtilityFunctions.hpp"
#include "CDPL/Shape/SymmetryClass.hpp"
#include "CDPL/Base/Exceptions.hpp"

#include "Utilities.hpp"

//#include <iostream>
using namespace CDPL;


namespace
{

	const double QUATERNION_UNITY_DEVIATION_PENALTY_FACTOR = 10000.0;
	const double BFGS_MINIMIZER_STEP_SIZE                  = 0.01;
	const double BFGS_MINIMIZER_TOLERANCE                  = 0.1;

	bool defColorFilterFunc(std::size_t col) 
	{
		return (col != 0);
	}
}


const double      Shape::GaussianShapeFunctionAlignment::DEF_REFINEMENT_STOP_GRADIENT = 1.0;
const std::size_t Shape::GaussianShapeFunctionAlignment::DEF_MAX_REFINEMENT_ITERATIONS;


Shape::GaussianShapeFunctionAlignment::GaussianShapeFunctionAlignment():
	overlapFunc(&defOverlapFunc), startGen(&defStartGen), refShapeFunc(0), refShapeSymClass(SymmetryClass::UNDEF),
	refStartPoses(true), maxNumRefIters(DEF_MAX_REFINEMENT_ITERATIONS), refStopGrad(DEF_REFINEMENT_STOP_GRADIENT),
	colFilterFunc(&defColorFilterFunc), minimizer(boost::bind(&GaussianShapeFunctionAlignment::calcAlignmentFunctionValue, this, _1),
												  boost::bind(&GaussianShapeFunctionAlignment::calcAlignmentFunctionGradient, this, _1, _2))
{}

Shape::GaussianShapeFunctionAlignment::GaussianShapeFunctionAlignment(const GaussianShapeFunction& ref_func, unsigned int sym_class):
	overlapFunc(&defOverlapFunc), startGen(&defStartGen),
	refStartPoses(true), maxNumRefIters(DEF_MAX_REFINEMENT_ITERATIONS), refStopGrad(DEF_REFINEMENT_STOP_GRADIENT),
	colFilterFunc(&defColorFilterFunc), minimizer(boost::bind(&GaussianShapeFunctionAlignment::calcAlignmentFunctionValue, this, _1),
												  boost::bind(&GaussianShapeFunctionAlignment::calcAlignmentFunctionGradient, this, _1, _2))
{
   setReference(ref_func,  sym_class);
}

Shape::GaussianShapeFunctionAlignment::~GaussianShapeFunctionAlignment() {}

void Shape::GaussianShapeFunctionAlignment::setOverlapFunction(GaussianShapeOverlapFunction& func)
{
	overlapFunc = &func;
}
			
Shape::GaussianShapeOverlapFunction& Shape::GaussianShapeFunctionAlignment::getOverlapFunction() const
{
	return *overlapFunc;
}

const Shape::FastGaussianShapeOverlapFunction& Shape::GaussianShapeFunctionAlignment::getDefaultOverlapFunction() const
{
	return defOverlapFunc;
}

Shape::FastGaussianShapeOverlapFunction& Shape::GaussianShapeFunctionAlignment::getDefaultOverlapFunction()
{
	return defOverlapFunc;
}

void Shape::GaussianShapeFunctionAlignment::setStartGenerator(GaussianShapeAlignmentStartGenerator& gen)
{
	startGen = &gen;
}
			
Shape::GaussianShapeAlignmentStartGenerator& Shape::GaussianShapeFunctionAlignment::getStartGenerator() const
{
	return *startGen;
}

const Shape::PrincipalAxesAlignmentStartGenerator& Shape::GaussianShapeFunctionAlignment::getDefaultStartGenerator() const
{
	return defStartGen;
}

Shape::PrincipalAxesAlignmentStartGenerator& Shape::GaussianShapeFunctionAlignment::getDefaultStartGenerator()
{
	return defStartGen;
}

void Shape::GaussianShapeFunctionAlignment::setColorMatchFunction(const ColorMatchFunction& func)
{
	overlapFunc->setColorMatchFunction(func);
}

const Shape::GaussianShapeFunctionAlignment::ColorMatchFunction& Shape::GaussianShapeFunctionAlignment::getColorMatchFunction() const
{
	return overlapFunc->getColorMatchFunction();
}

void Shape::GaussianShapeFunctionAlignment::setColorFilterFunction(const ColorFilterFunction& func)
{
	if (!func)
		colFilterFunc = &defColorFilterFunc;
	else
		colFilterFunc = func;
}

const Shape::GaussianShapeFunctionAlignment::ColorFilterFunction& Shape::GaussianShapeFunctionAlignment::getColorFilterFunction() const
{
	return colFilterFunc;
}

void Shape::GaussianShapeFunctionAlignment::refineStartingPoses(bool refine)
{
	refStartPoses = refine;
}

bool Shape::GaussianShapeFunctionAlignment::refineStartingPoses() const
{
	return refStartPoses;
}

void Shape::GaussianShapeFunctionAlignment::setMaxNumRefinementIterations(std::size_t max_iter)
{
	maxNumRefIters = max_iter;
}

std::size_t Shape::GaussianShapeFunctionAlignment::getMaxNumRefinementIterations() const
{
	return maxNumRefIters;
}

void Shape::GaussianShapeFunctionAlignment::setRefinementStopGradient(double grad_norm)
{
	refStopGrad = grad_norm;
}

double Shape::GaussianShapeFunctionAlignment::getRefinementStopGradient() const
{
	return refStopGrad;
}

unsigned int Shape::GaussianShapeFunctionAlignment::setupReference(GaussianShapeFunction& func, Math::Matrix4D& xform) const
{
	return startGen->setupReference(func, xform);
}

unsigned int Shape::GaussianShapeFunctionAlignment::setupAligned(GaussianShapeFunction& func, Math::Matrix4D& xform) const
{
	return startGen->setupAligned(func, xform);
}

void Shape::GaussianShapeFunctionAlignment::setReference(const GaussianShapeFunction& func, unsigned int sym_class)
{
	refShapeFunc = &func;
	refShapeSymClass = sym_class;
	
    overlapFunc->setShapeFunction(func, true);
	startGen->setReference(*refShapeFunc, refShapeSymClass);
}

const Shape::GaussianShapeFunction* Shape::GaussianShapeFunctionAlignment::getReference() const
{
    return refShapeFunc;
}
			
double Shape::GaussianShapeFunctionAlignment::calcSelfOverlap(const GaussianShapeFunction& func)
{
	overlapFunc->setShapeFunction(func, false);

	return overlapFunc->calcSelfOverlap(false);
}

double Shape::GaussianShapeFunctionAlignment::calcColorSelfOverlap(const GaussianShapeFunction& func)
{
	overlapFunc->setShapeFunction(func, false);

	return overlapFunc->calcSelfOverlap(false, colFilterFunc);
}

bool Shape::GaussianShapeFunctionAlignment::align(const GaussianShapeFunction& func, unsigned int sym_class, bool calc_col_overlap)
{
	results.clear();

	if (!refShapeFunc || !checkValidity(*refShapeFunc))
		return false;

	if (!checkValidity(func))
		return false;

	if (!startGen->generate(func, sym_class))
		return false;

	func.getElementPositions(startPoseCoords);
	optPoseCoords.resize(startPoseCoords.getSize());
	
	std::size_t num_starts = startGen->getNumStartTransforms();
	
	results.reserve(num_starts);

	QuaternionTransformation opt_xform;
	QuaternionTransformation opt_xform_grad;
	Math::Matrix4D opt_xform_mtx;

	overlapFunc->setShapeFunction(func, false);
//	std::cerr << "--------- Num Starts: " << num_starts << std::endl; 
	for (std::size_t i = 0; i < num_starts; i++) {
		if (!refStartPoses) {
			quaternionToMatrix(startGen->getStartTransform(i), opt_xform_mtx);
			transform(optPoseCoords, opt_xform_mtx, startPoseCoords);

			results.push_back(Result(opt_xform_mtx, overlapFunc->calcOverlap(optPoseCoords), 
									 calc_col_overlap ? overlapFunc->calcOverlap(optPoseCoords, colFilterFunc) : 0.0));
			continue;
		}

		opt_xform = startGen->getStartTransform(i);

		minimizer.setup(opt_xform, opt_xform_grad, BFGS_MINIMIZER_STEP_SIZE, BFGS_MINIMIZER_TOLERANCE);

//		double start_val = calcAlignmentFunctionValue(opt_xform);

		minimizer.minimize(opt_xform, opt_xform_grad, maxNumRefIters, refStopGrad, -1.0, false);
		
	    if (boost::math::isfinite(minimizer.getFunctionValue())) {  // sanity check
			normalize(opt_xform);
			quaternionToMatrix(opt_xform, opt_xform_mtx);
			transform(optPoseCoords, opt_xform_mtx, startPoseCoords);

//			std::cerr << "Minimized from " << start_val << " to " << minimizer.getFunctionValue() << " in " << minimizer.getNumIterations() << " iterations" << std::endl;

			results.push_back(Result(opt_xform_mtx, overlapFunc->calcOverlap(optPoseCoords), 
									 calc_col_overlap ? overlapFunc->calcOverlap(optPoseCoords, colFilterFunc) : 0.0));
		}
	}
	
	return !results.empty();
}

std::size_t Shape::GaussianShapeFunctionAlignment::getNumResults() const
{
	return results.size();
}

const Shape::GaussianShapeFunctionAlignment::Result& Shape::GaussianShapeFunctionAlignment::getResult(std::size_t idx) const
{
	if (idx >= results.size())
		throw Base::IndexError("GaussianShapeFunctionAlignment: result index out of bounds");

	return results[idx];
}

Shape::GaussianShapeFunctionAlignment::ConstResultIterator Shape::GaussianShapeFunctionAlignment::getResultsBegin() const
{
	return results.begin();
}

Shape::GaussianShapeFunctionAlignment::ConstResultIterator Shape::GaussianShapeFunctionAlignment::getResultsEnd() const
{
	return results.end();
}

bool Shape::GaussianShapeFunctionAlignment::checkValidity(const GaussianShapeFunction& func) const
{
	return (func.getShape() && func.getShape()->getNumElements() > 0);
}

/*
double Shape::GaussianShapeFunctionAlignment::calcAlignmentFunctionValue(const QuaternionTransformation& xform_quat)
{
	QuaternionTransformation::ConstPointer xform_quat_data = xform_quat.getData();
	Math::Matrix4D xform_mtx;
	
	double quat_non_unity_pen = 1.0 - (xform_quat_data[0] * xform_quat_data[0] + xform_quat_data[1] * xform_quat_data[1] + 
									   xform_quat_data[2] * xform_quat_data[2] + xform_quat_data[3] * xform_quat_data[3]);

	quat_non_unity_pen *= 0.5 * QUATERNION_UNITY_DEVIATION_PENALTY_FACTOR * quat_non_unity_pen;

	quaternionToMatrix(xform_quat, xform_mtx);
	transform(optPoseCoords, xform_mtx, startPoseCoords);
	
	return (quat_non_unity_pen - overlapFunc->calcOverlap(optPoseCoords));	
}
*/
double Shape::GaussianShapeFunctionAlignment::calcAlignmentFunctionValue(const QuaternionTransformation& xform_quat)
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
	transform(optPoseCoords, xform_mtx, startPoseCoords);

	return (quat_non_unity_pen - overlapFunc->calcOverlap(optPoseCoords));
}
/*
double Shape::GaussianShapeFunctionAlignment::calcAlignmentFunctionGradient(const QuaternionTransformation& xform_quat, QuaternionTransformation& xform_quat_grad)
{
	xform_quat_grad.clear();

	QuaternionTransformation::ConstPointer xform_quat_data = xform_quat.getData();
	QuaternionTransformation::Pointer grad_data = xform_quat_grad.getData();
	Math::Matrix4D xform_mtx;

	quaternionToMatrix(xform_quat, xform_mtx);
	transform(optPoseCoords, xform_mtx, startPoseCoords);

	double neg_overlap = -overlapFunc->calcOverlapGradient(optPoseCoords, optPoseCoordsGrad);

	for (std::size_t i = 0, num_elem = startPoseCoords.getSize(); i < num_elem; i++) {
		const Math::Vector3D::ConstPointer elem_pos = startPoseCoords[i].getData();
		const Math::Vector3D::ConstPointer pos_grad = optPoseCoordsGrad[i].getData();
		
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
double Shape::GaussianShapeFunctionAlignment::calcAlignmentFunctionGradient(const QuaternionTransformation& xform_quat, QuaternionTransformation& xform_quat_grad)
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
	transform(optPoseCoords, xform_mtx, startPoseCoords);

	double neg_overlap = -overlapFunc->calcOverlapGradient(optPoseCoords, optPoseCoordsGrad);

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
	
	for (std::size_t i = 0, num_elem = startPoseCoords.getSize(); i < num_elem; i++) {
		const Math::Vector3D::ConstPointer elem_pos = startPoseCoords[i].getData();
		const Math::Vector3D::ConstPointer pos_grad = optPoseCoordsGrad[i].getData();
		
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
