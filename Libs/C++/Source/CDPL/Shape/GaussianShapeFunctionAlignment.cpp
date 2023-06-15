/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * GaussianShapeFunctionAlignment.cpp 
 *
 * This file is part of the Chemical Data Processing Toolkit
 *
 * Copyright (C) 2003 Thomas Seidel <thomas.seidel@univie.ac.at>
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

#include <cmath>
#include <functional>

#include "CDPL/Shape/GaussianShapeFunctionAlignment.hpp"
#include "CDPL/Shape/GaussianShapeFunction.hpp"
#include "CDPL/Shape/UtilityFunctions.hpp"
#include "CDPL/Shape/SymmetryClass.hpp"
#include "CDPL/Math/Matrix.hpp"
#include "CDPL/Base/Exceptions.hpp"

#include "Utilities.hpp"


using namespace CDPL;


namespace
{

	const double QUATERNION_UNITY_DEVIATION_PENALTY_FACTOR = 10000.0;
	const double BFGS_MINIMIZER_STEP_SIZE                  = 0.1;
	const double BFGS_MINIMIZER_TOLERANCE                  = 0.5;
}


constexpr double      Shape::GaussianShapeFunctionAlignment::DEF_OPTIMIZATION_STOP_GRADIENT;
constexpr std::size_t Shape::GaussianShapeFunctionAlignment::DEF_MAX_OPTIMIZATION_ITERATIONS;
				

Shape::GaussianShapeFunctionAlignment::GaussianShapeFunctionAlignment():
	overlapFunc(&defOverlapFunc), startGen(&defStartGen), refShapeFunc(0), refShapeSymClass(SymmetryClass::UNDEF), perfAlignment(true),
	calcColOverlaps(true), optOverlap(true), greedyOpt(false), maxNumOptIters(DEF_MAX_OPTIMIZATION_ITERATIONS), optStopGrad(DEF_OPTIMIZATION_STOP_GRADIENT),
	minimizer(std::bind(&GaussianShapeFunctionAlignment::calcAlignmentFunctionValue, this, std::placeholders::_1),
			  std::bind(&GaussianShapeFunctionAlignment::calcAlignmentFunctionGradient, this, std::placeholders::_1, std::placeholders::_2))
{}

Shape::GaussianShapeFunctionAlignment::GaussianShapeFunctionAlignment(const GaussianShapeFunction& ref_func, unsigned int sym_class):
	overlapFunc(&defOverlapFunc), startGen(&defStartGen), perfAlignment(true), calcColOverlaps(true),
	optOverlap(true), greedyOpt(false), maxNumOptIters(DEF_MAX_OPTIMIZATION_ITERATIONS), optStopGrad(DEF_OPTIMIZATION_STOP_GRADIENT),
	minimizer(std::bind(&GaussianShapeFunctionAlignment::calcAlignmentFunctionValue, this, std::placeholders::_1),
			  std::bind(&GaussianShapeFunctionAlignment::calcAlignmentFunctionGradient, this, std::placeholders::_1, std::placeholders::_2))
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
	overlapFunc->setColorFilterFunction(func);
}

const Shape::GaussianShapeFunctionAlignment::ColorFilterFunction& Shape::GaussianShapeFunctionAlignment::getColorFilterFunction() const
{
	return overlapFunc->getColorFilterFunction();
}

void Shape::GaussianShapeFunctionAlignment::performAlignment(bool perf_align)
{
	perfAlignment = perf_align;
}

bool Shape::GaussianShapeFunctionAlignment::performAlignment() const
{
	return perfAlignment;
}

void Shape::GaussianShapeFunctionAlignment::optimizeOverlap(bool optimize)
{
	optOverlap = optimize;
}

bool Shape::GaussianShapeFunctionAlignment::optimizeOverlap() const
{
	return optOverlap;
}

void Shape::GaussianShapeFunctionAlignment::greedyOptimization(bool greedy)
{
	greedyOpt = greedy;
}

bool Shape::GaussianShapeFunctionAlignment::greedyOptimization() const
{
	return greedyOpt;
}

void Shape::GaussianShapeFunctionAlignment::setMaxNumOptimizationIterations(std::size_t max_iter)
{
	maxNumOptIters = max_iter;
}

std::size_t Shape::GaussianShapeFunctionAlignment::getMaxNumOptimizationIterations() const
{
	return maxNumOptIters;
}

void Shape::GaussianShapeFunctionAlignment::setOptimizationStopGradient(double grad_norm)
{
	optStopGrad = grad_norm;
}

double Shape::GaussianShapeFunctionAlignment::getOptimizationStopGradient() const
{
	return optStopGrad;
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

	return overlapFunc->calcColorSelfOverlap(false);
}

void Shape::GaussianShapeFunctionAlignment::calcColorOverlaps(bool calc)
{
	calcColOverlaps = calc;
}

bool Shape::GaussianShapeFunctionAlignment::calcColorOverlaps() const
{
	return calcColOverlaps;
}

bool Shape::GaussianShapeFunctionAlignment::align(const GaussianShapeFunction& func, unsigned int sym_class)
{
	results.clear();

	if (!refShapeFunc || !checkValidity(*refShapeFunc)) 
		return false;

	if (!checkValidity(func)) 
		return false;

	if (!perfAlignment) {
		overlapFunc->setShapeFunction(func, false);

		Result res;

		res.overlap = overlapFunc->calcOverlap();
		res.colOverlap = (calcColOverlaps ? overlapFunc->calcColorOverlap() : 0.0);
		res.transform = Math::IdentityMatrix<double>(4, 4);

		results.push_back(res);
		return true;
	}

	if (!startGen->generate(func, sym_class))
		return false;

	std::size_t num_starts = startGen->getNumStartTransforms();
	std::size_t num_sub_xforms = startGen->getNumStartSubTransforms();

	if (num_starts == 0 || num_sub_xforms == 0) 
		return false;

	func.getElementPositions(startPoseCoords);
	optPoseCoords.resize(startPoseCoords.getSize());

	overlapFunc->setShapeFunction(func, false);
	
	Result curr_res;
	QuaternionTransformation opt_xform;
	QuaternionTransformation opt_xform_grad;

	for (std::size_t i = 0; i < num_starts; ) {
		if (optOverlap && greedyOpt) {
			std::size_t best_start_xform = 0;
			double highest_ovlp = 0.0;
			
			for (std::size_t j = 0; j < num_sub_xforms && i < num_starts; j++, i++) {
				quaternionToMatrix(startGen->getStartTransform(i), curr_res.transform);
				Shape::transform(optPoseCoords, curr_res.transform, startPoseCoords);

				double overlap = overlapFunc->calcOverlap(optPoseCoords);

				if (j == 0 || overlap > highest_ovlp) {
					best_start_xform = i;
					highest_ovlp = overlap;
				}
			}

			opt_xform = startGen->getStartTransform(best_start_xform);

			minimizer.setup(opt_xform, opt_xform_grad, BFGS_MINIMIZER_STEP_SIZE, BFGS_MINIMIZER_TOLERANCE);
			minimizer.minimize(opt_xform, opt_xform_grad, maxNumOptIters, optStopGrad, -1.0, false);
		
			if (!std::isfinite(minimizer.getFunctionValue())) // sanity check 
				continue;

			normalize(opt_xform);
			quaternionToMatrix(opt_xform, curr_res.transform);
			Shape::transform(optPoseCoords, curr_res.transform, startPoseCoords);

			curr_res.overlap = overlapFunc->calcOverlap(optPoseCoords);
			curr_res.colOverlap = (calcColOverlaps ? overlapFunc->calcColorOverlap(optPoseCoords) : 0.0);

			results.push_back(curr_res);
			continue;
		}

		bool have_sol = false;

		for (std::size_t j = 0; j < num_sub_xforms && i < num_starts; j++, i++) {
			if (!optOverlap) {
				quaternionToMatrix(startGen->getStartTransform(i), curr_res.transform);
				Shape::transform(optPoseCoords, curr_res.transform, startPoseCoords);

				curr_res.overlap = overlapFunc->calcOverlap(optPoseCoords);

			} else {
				opt_xform = startGen->getStartTransform(i);

				minimizer.setup(opt_xform, opt_xform_grad, BFGS_MINIMIZER_STEP_SIZE, BFGS_MINIMIZER_TOLERANCE);
				minimizer.minimize(opt_xform, opt_xform_grad, maxNumOptIters, optStopGrad, -1.0, false);
		
				if (!std::isfinite(minimizer.getFunctionValue()))  // sanity check
					continue;

				normalize(opt_xform);
				quaternionToMatrix(opt_xform, curr_res.transform);
				Shape::transform(optPoseCoords, curr_res.transform, startPoseCoords);

				curr_res.overlap = overlapFunc->calcOverlap(optPoseCoords);
			}

			if (!have_sol) {
				curr_res.colOverlap = (calcColOverlaps ? overlapFunc->calcColorOverlap(optPoseCoords) : 0.0);

				results.push_back(curr_res);
				have_sol = true;

			} else if (curr_res.overlap > results.back().overlap) {
				curr_res.colOverlap = (calcColOverlaps ? overlapFunc->calcColorOverlap(optPoseCoords) : 0.0);

				results.back() = curr_res;
			}
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
	Shape::transform(optPoseCoords, xform_mtx, startPoseCoords);

	return (quat_non_unity_pen - overlapFunc->calcOverlap(optPoseCoords));
}

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
	Shape::transform(optPoseCoords, xform_mtx, startPoseCoords);

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
