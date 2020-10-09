/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * FastGaussianShapeAlignment.cpp 
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


#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wstrict-aliasing" // fastexp causes annoying aliasing warnings!

#include "StaticInit.hpp"

#include <cmath>
#include <algorithm>

#include "FastExp/fastexp.h"

#include "CDPL/Shape/FastGaussianShapeAlignment.hpp"
#include "CDPL/Shape/ScoringFunctions.hpp"
#include "CDPL/Shape/UtilityFunctions.hpp"
#include "CDPL/Shape/SymmetryClass.hpp"
#include "CDPL/Math/Matrix.hpp"
#include "CDPL/Math/JacobiDiagonalization.hpp"
#include "CDPL/Math/MatrixProxy.hpp"
#include "CDPL/Math/AffineTransform.hpp"
#include "CDPL/Base/Exceptions.hpp"

#include "Utilities.hpp"


using namespace CDPL;


namespace
{

	bool compareScore(const Shape::AlignmentResult& res1, const Shape::AlignmentResult& res2)
	{
		return (res1.getScore() >= res2.getScore());
	}

    const double RADIUS_SCALING_FACTOR = 1.3;
}


const double       Shape::FastGaussianShapeAlignment::DEF_OPTIMIZATION_STOP_GRADIENT = 1.0;
const unsigned int Shape::FastGaussianShapeAlignment::DEF_RESULT_SELECTION_MODE;
const std::size_t  Shape::FastGaussianShapeAlignment::DEF_MAX_OPTIMIZATION_ITERATIONS;


Shape::FastGaussianShapeAlignment::FastGaussianShapeAlignment():
	perfAlignment(true), optOverlap(true), greedyOpt(false), maxNumOptIters(DEF_MAX_OPTIMIZATION_ITERATIONS), 
	optStopGrad(DEF_OPTIMIZATION_STOP_GRADIENT), resultSelMode(DEF_RESULT_SELECTION_MODE), resultCmpFunc(&compareScore), 
	scoringFunc(&calcTotalOverlapTanimotoScore), currSetIndex(0), currShapeIndex(0)
{}

Shape::FastGaussianShapeAlignment::FastGaussianShapeAlignment(const GaussianShape& ref_shape):
	perfAlignment(true), optOverlap(true), greedyOpt(false), maxNumOptIters(DEF_MAX_OPTIMIZATION_ITERATIONS), 
	optStopGrad(DEF_OPTIMIZATION_STOP_GRADIENT), resultSelMode(DEF_RESULT_SELECTION_MODE), resultCmpFunc(&compareScore), 
	scoringFunc(&calcTotalOverlapTanimotoScore), currSetIndex(0), currShapeIndex(0)
{
	addReferenceShape(ref_shape);
}

Shape::FastGaussianShapeAlignment::FastGaussianShapeAlignment(const GaussianShapeSet& ref_shapes):
	perfAlignment(true), optOverlap(true), greedyOpt(false), maxNumOptIters(DEF_MAX_OPTIMIZATION_ITERATIONS), 
	optStopGrad(DEF_OPTIMIZATION_STOP_GRADIENT), resultSelMode(DEF_RESULT_SELECTION_MODE), resultCmpFunc(&compareScore), 
	scoringFunc(&calcTotalOverlapTanimotoScore), currSetIndex(0), currShapeIndex(0)
{
	addReferenceShapes(ref_shapes);
}

Shape::FastGaussianShapeAlignment::~FastGaussianShapeAlignment() 
{}

void Shape::FastGaussianShapeAlignment::setResultCompareFunction(const ResultCompareFunction& func)
{
	if (!func)
		resultCmpFunc = &compareScore;
	else
		resultCmpFunc = func;
}

const Shape::FastGaussianShapeAlignment::ResultCompareFunction& Shape::FastGaussianShapeAlignment::getResultCompareFunction() const
{
	return resultCmpFunc;
}

void Shape::FastGaussianShapeAlignment::setScoringFunction(const ScoringFunction& func)
{
	if (!func)
		scoringFunc = &calcTotalOverlapTanimotoScore;
	else
		scoringFunc = func;
}

const Shape::FastGaussianShapeAlignment::ScoringFunction& Shape::FastGaussianShapeAlignment::getScoringFunction() const
{
	return scoringFunc;
}

void Shape::FastGaussianShapeAlignment::setResultSelectionMode(unsigned int mode)
{
	resultSelMode = mode;
}

unsigned int Shape::FastGaussianShapeAlignment::getResultSelectionMode() const
{
	return resultSelMode;
}

void Shape::FastGaussianShapeAlignment::performAlignment(bool perf_align)
{
	perfAlignment = perf_align;
}

bool Shape::FastGaussianShapeAlignment::performAlignment() const
{
	return perfAlignment;
}

void Shape::FastGaussianShapeAlignment::optimizeOverlap(bool optimize)
{
	optOverlap = optimize;
}

bool Shape::FastGaussianShapeAlignment::optimizeOverlap() const
{
	return optOverlap;
}

void Shape::FastGaussianShapeAlignment::greedyOptimization(bool greedy)
{
	greedyOpt = greedy;
}

bool Shape::FastGaussianShapeAlignment::greedyOptimization() const
{
	return greedyOpt;
}

void Shape::FastGaussianShapeAlignment::setMaxNumOptimizationIterations(std::size_t max_iter)
{
	maxNumOptIters = max_iter;
}

std::size_t Shape::FastGaussianShapeAlignment::getMaxNumOptimizationIterations() const
{
	return maxNumOptIters;
}

void Shape::FastGaussianShapeAlignment::setOptimizationStopGradient(double grad_norm)
{
	optStopGrad = grad_norm;
}

double Shape::FastGaussianShapeAlignment::getOptimizationStopGradient() const
{
	return optStopGrad;
}

void Shape::FastGaussianShapeAlignment::clearReferenceShapes()
{
	refShapeData.clear();
}

void Shape::FastGaussianShapeAlignment::addReferenceShape(const GaussianShape& shape, bool new_set)
{
// TODO
}

void Shape::FastGaussianShapeAlignment::addReferenceShapes(const GaussianShapeSet& shapes, bool new_set)
{
// TODO
}

std::size_t Shape::FastGaussianShapeAlignment::getNumReferenceShapes() const
{
	return refShapeData.size();
}

bool Shape::FastGaussianShapeAlignment::align(const GaussianShape& shape)
{
	results.clear();
	resIndexMap.clear();
// TODO
	return !results.empty();
}

bool Shape::FastGaussianShapeAlignment::align(const GaussianShapeSet& shapes)
{
	results.clear();
	resIndexMap.clear();
// TODO
	return !results.empty();
}

std::size_t Shape::FastGaussianShapeAlignment::getNumResults() const
{
	return results.size();
}

const Shape::AlignmentResult& Shape::FastGaussianShapeAlignment::getResult(std::size_t idx) const
{
	if (idx >= results.size())
		throw Base::IndexError("FastGaussianShapeAlignment: result index out of bounds");

	return results[idx];
}

Shape::AlignmentResult& Shape::FastGaussianShapeAlignment::getResult(std::size_t idx)
{
	if (idx >= results.size())
		throw Base::IndexError("FastGaussianShapeAlignment: result index out of bounds");

	return results[idx];
}

Shape::FastGaussianShapeAlignment::ConstResultIterator Shape::FastGaussianShapeAlignment::getResultsBegin() const
{
	return results.begin();
}

Shape::FastGaussianShapeAlignment::ConstResultIterator Shape::FastGaussianShapeAlignment::getResultsEnd() const
{
	return results.end();
}

Shape::FastGaussianShapeAlignment::ResultIterator Shape::FastGaussianShapeAlignment::getResultsBegin()
{
	return results.begin();
}

Shape::FastGaussianShapeAlignment::ResultIterator Shape::FastGaussianShapeAlignment::getResultsEnd()
{
	return results.end();
}
	
void Shape::FastGaussianShapeAlignment::setupShapeData(const GaussianShape& shape, ShapeData& data, bool ref)
{
	std::size_t num_elem = shape.getNumElements();

	data.elements.resize(num_elem);
	data.colElemOffs = 0;

	for (std::size_t i = 0; i < num_elem; i++) {
		const GaussianShape::Element& gs_elem = shape.getElement(i);

		if (gs_elem.getColor() > 0)
			continue;

		setupShapeDataElement(gs_elem, data.elements[data.colElemOffs++]);
	}

	for (std::size_t i = 0, j = data.colElemOffs; i < num_elem; i++) {
		const GaussianShape::Element& gs_elem = shape.getElement(i);

		if (gs_elem.getColor() == 0)
			continue;

		setupShapeDataElement(gs_elem, data.elements[j++]);
	}

	data.selfOverlap = calcOverlap(data, data, false);
	data.colSelfOverlap = calcOverlap(data, data, true);

	if (!perfAlignment) 
		return;

	Math::Vector3D shape_ctr;
	Math::Vector3D::Pointer shape_ctr_data = shape_ctr.getData();
	double shape_vol = 0.0;

	for (std::size_t i = 0; i < num_elem; i++) {
		const ShapeData::Element& elem = data.elements[i];
		Math::Vector3D::ConstPointer elem_ctr = elem.center.getData();

		shape_ctr_data[0] += elem.volume * elem_ctr[0];
		shape_ctr_data[1] += elem.volume * elem_ctr[1];
		shape_ctr_data[2] += elem.volume * elem_ctr[2];

		shape_vol += elem.volume;
	}

	shape_ctr /= shape_vol;

	Math::Matrix3D quad_tensor;
	Math::Matrix3D::ArrayPointer tensor_data = quad_tensor.getData();

	for (std::size_t i = 0; i < num_elem; i++) {
		const ShapeData::Element& elem = data.elements[i];
		Math::Vector3D::ConstPointer elem_ctr = elem.center.getData();

		double diag_const = 1.0 / (2.0 * elem.delta);
		double trans_elem_ctr[3] = { elem_ctr[0] - shape_ctr_data[0], elem_ctr[1] - shape_ctr_data[1], elem_ctr[2] - shape_ctr_data[2] };

		tensor_data[0][1] += trans_elem_ctr[0] * trans_elem_ctr[1] * elem.volume;
		tensor_data[0][2] += trans_elem_ctr[0] * trans_elem_ctr[2] * elem.volume;
		tensor_data[1][2] += trans_elem_ctr[1] * trans_elem_ctr[2] * elem.volume;

		tensor_data[0][0] += (trans_elem_ctr[0] * trans_elem_ctr[0] + diag_const) * elem.volume;
		tensor_data[1][1] += (trans_elem_ctr[1] * trans_elem_ctr[1] + diag_const) * elem.volume;
		tensor_data[2][2] += (trans_elem_ctr[2] * trans_elem_ctr[2] + diag_const) * elem.volume;
	}

	tensor_data[1][0] = tensor_data[0][1];
	tensor_data[2][0] = tensor_data[0][2];
	tensor_data[2][1] = tensor_data[1][2];

	quad_tensor /= shape_vol;

	Math::Matrix3D eigen_vecs;
	Math::Vector3D x_axis, y_axis, z_axis, moments;
    Math::Vector3D::Pointer moments_data = moments.getData();
	
    jacobiDiagonalize(quad_tensor, moments, eigen_vecs);

    std::pair<double, int> ordered_moments[3] = {
	    std::make_pair(moments_data[0], 0),
		std::make_pair(moments_data[1], 1),
		std::make_pair(moments_data[2], 2)
	};

    std::sort(ordered_moments, ordered_moments + 3);

    moments_data[0] = ordered_moments[2].first;
    moments_data[1] = ordered_moments[1].first;
    moments_data[2] = ordered_moments[0].first;
	
    x_axis.assign(column(eigen_vecs, ordered_moments[2].second));
    y_axis.assign(column(eigen_vecs, ordered_moments[1].second));
    z_axis.assign(crossProd(x_axis, y_axis));
    y_axis.assign(crossProd(z_axis, x_axis));

    x_axis /= length(x_axis);
    y_axis /= length(y_axis);
    z_axis /= length(z_axis);
	
	Math::Matrix4D::ArrayPointer xform_data = data.transform.getData();

	xform_data[0][0] = x_axis(0);
	xform_data[0][1] = x_axis(1);
	xform_data[0][2] = x_axis(2);
	xform_data[0][3] = 0.0;
	
	xform_data[1][0] = y_axis(0);
	xform_data[1][1] = y_axis(1);
	xform_data[1][2] = y_axis(2);
	xform_data[1][3] = 0.0;
	
	xform_data[2][0] = z_axis(0);
	xform_data[2][1] = z_axis(1);
	xform_data[2][2] = z_axis(2);
	xform_data[2][3] = 0.0;

	xform_data[3][0] = 0.0;
	xform_data[3][1] = 0.0;
	xform_data[3][2] = 0.0;
	xform_data[3][3] = 1.0;

	data.transform = data.transform * Math::TranslationMatrix<double>(4, -shape_ctr_data[0], -shape_ctr_data[1], -shape_ctr_data[2]);
	
	Math::Vector3D tmp_vec;
	Math::Vector3D::Pointer tmp_vec_data = tmp_vec.getData();

	for (std::size_t i = 0; i < num_elem; i++) {
		ShapeData::Element& elem = data.elements[i];

		transform(tmp_vec_data, xform_data, elem.center.getData());

		elem.center.assign(tmp_vec);
	}
	
	if (ref) {
		xform_data[0][0] = x_axis(0);
		xform_data[1][0] = x_axis(1);
		xform_data[2][0] = x_axis(2);
	
		xform_data[0][1] = y_axis(0);
		xform_data[1][1] = y_axis(1);
		xform_data[2][1] = y_axis(2);
	
		xform_data[0][2] = z_axis(0);
		xform_data[1][2] = z_axis(1);
		xform_data[2][2] = z_axis(2);

		xform_data[0][3] = shape_ctr_data[0];
		xform_data[1][3] = shape_ctr_data[1];
		xform_data[2][3] = shape_ctr_data[2];

		xform_data[3][0] = 0.0;
		xform_data[3][1] = 0.0;
		xform_data[3][2] = 0.0;
		xform_data[3][3] = 1.0;
	}

	data.symClass = perceiveSymmetryClass(moments);
}

void Shape::FastGaussianShapeAlignment::setupShapeDataElement(const GaussianShape::Element& gs_elem, ShapeData::Element& sd_elem) const
{
	sd_elem.center.assign(gs_elem.getPosition());
	sd_elem.color = gs_elem.getColor();
	sd_elem.weightFactor = gs_elem.getHardness();
	sd_elem.radius = gs_elem.getRadius();

	double lambda = 4.0 * M_PI / (3.0 * sd_elem.weightFactor);

	sd_elem.delta = (M_PI / std::pow(lambda, 2.0 / 3.0)) / (sd_elem.radius * sd_elem.radius);

	double vol_factor = M_PI / sd_elem.delta;

	sd_elem.volume = sd_elem.weightFactor * vol_factor * std::sqrt(vol_factor);
}

double Shape::FastGaussianShapeAlignment::calcOverlap(const ShapeData& ref_data, const ShapeData& ovl_data, bool color) const
{
	double overlap = 0.0;

	for (std::size_t i = (color ? ovl_data.colElemOffs : 0), num_ovl_elem = ovl_data.elements.size(); i < num_ovl_elem; i++) {
		const ShapeData::Element& elem1 = ovl_data.elements[i];
		Math::Vector3D::ConstPointer elem1_ctr = elem1.center.getData();

		for (std::size_t j = (color ? ref_data.colElemOffs : 0), num_ref_elem = ref_data.elements.size(); j < num_ref_elem; j++) {
			const ShapeData::Element& elem2 = ref_data.elements[j];

			if (elem1.color != elem2.color)
				continue;
		
			double sqrd_ctr_dist = calcSquaredDistance(elem1_ctr, elem2.center.getData());
			double max_dist = (elem1.radius + elem2.radius) * RADIUS_SCALING_FACTOR;

			if (sqrd_ctr_dist > (max_dist * max_dist))
				continue;

			double delta = elem1.delta + elem2.delta;
			double vol_factor = M_PI / delta;
			double prod_fact_exp = -elem1.delta * elem2.delta * sqrd_ctr_dist / delta;

			overlap += elem1.weightFactor * elem2.weightFactor * vol_factor *
				std::sqrt(vol_factor) * fastexp::IEEE<double, 3>::evaluate(prod_fact_exp);
		}
	}
		
	return overlap;
}

double Shape::FastGaussianShapeAlignment::calcOverlapGradient(const ShapeData& ref_data, const ShapeData& ovl_data, Math::Vector3DArray& grad) const
{
	Math::Vector3DArray::StorageType& grad_data = grad.getData();
	Math::Vector3D inters_prod_ctr;
	Math::Vector3D::Pointer inters_prod_ctr_data = inters_prod_ctr.getData();
	double overlap = 0.0;

	for (std::size_t i = 0, num_ovl_elem = ovl_data.colElemOffs; i < num_ovl_elem; i++) {
		const ShapeData::Element& elem1 = ovl_data.elements[i];
		Math::Vector3D::ConstPointer elem1_ctr = elem1.center.getData();

		for (std::size_t j = 0, num_ref_elem = ref_data.colElemOffs; j < num_ref_elem; j++) {
			const ShapeData::Element& elem2 = ref_data.elements[j];
			Math::Vector3D::ConstPointer elem2_ctr = elem2.center.getData();
			double sqrd_ctr_dist = calcSquaredDistance(elem1_ctr, elem2_ctr);
			double max_dist = (elem1.radius + elem2.radius) * RADIUS_SCALING_FACTOR;

			if (sqrd_ctr_dist > (max_dist * max_dist))
				continue;

			double delta = elem1.delta + elem2.delta;
			double vol_factor = M_PI / delta;
			double prod_fact_exp = -elem1.delta * elem2.delta * sqrd_ctr_dist / delta;

			double overlap_contrib = elem1.weightFactor * elem2.weightFactor * vol_factor *
				std::sqrt(vol_factor) * fastexp::IEEE<double, 3>::evaluate(prod_fact_exp);

			overlap += overlap_contrib;

			inters_prod_ctr_data[0] = (elem1_ctr[0] * elem1.delta + elem2_ctr[0] * elem2.delta) / delta;
			inters_prod_ctr_data[1] = (elem1_ctr[1] * elem1.delta + elem2_ctr[1] * elem2.delta) / delta;
			inters_prod_ctr_data[2] = (elem1_ctr[2] * elem1.delta + elem2_ctr[2] * elem2.delta) / delta;

			Math::Vector3D::Pointer elem1_grad = grad_data[i].getData();
			double grad_factor = -elem1.delta * 2.0 * overlap_contrib;
			
			elem1_grad[0] += grad_factor * (elem1_ctr[0] - inters_prod_ctr_data[0]);
			elem1_grad[1] += grad_factor * (elem1_ctr[1] - inters_prod_ctr_data[1]);
			elem1_grad[2] += grad_factor * (elem1_ctr[2] - inters_prod_ctr_data[2]);
		}
	}
	
	for (std::size_t i = ovl_data.colElemOffs, num_ovl_elem = ovl_data.elements.size(); i < num_ovl_elem; i++) {
		const ShapeData::Element& elem1 = ovl_data.elements[i];
		Math::Vector3D::ConstPointer elem1_ctr = elem1.center.getData();

		for (std::size_t j = ref_data.colElemOffs, num_ref_elem = ref_data.elements.size(); j < num_ref_elem; j++) {
			const ShapeData::Element& elem2 = ref_data.elements[j];

			if (elem2.color != elem1.color)
				continue;
	
			Math::Vector3D::ConstPointer elem2_ctr = elem2.center.getData();
			double sqrd_ctr_dist = calcSquaredDistance(elem1_ctr, elem2_ctr);
			double max_dist = (elem1.radius + elem2.radius) * RADIUS_SCALING_FACTOR;

			if (sqrd_ctr_dist > (max_dist * max_dist))
				continue;

			double delta = elem1.delta + elem2.delta;
			double vol_factor = M_PI / delta;
			double prod_fact_exp = -elem1.delta * elem2.delta * sqrd_ctr_dist / delta;

			double overlap_contrib = elem1.weightFactor * elem2.weightFactor * vol_factor *
				std::sqrt(vol_factor) * fastexp::IEEE<double, 3>::evaluate(prod_fact_exp);

			overlap += overlap_contrib;

			inters_prod_ctr_data[0] = (elem1_ctr[0] * elem1.delta + elem2_ctr[0] * elem2.delta) / delta;
			inters_prod_ctr_data[1] = (elem1_ctr[1] * elem1.delta + elem2_ctr[1] * elem2.delta) / delta;
			inters_prod_ctr_data[2] = (elem1_ctr[2] * elem1.delta + elem2_ctr[2] * elem2.delta) / delta;

			Math::Vector3D::Pointer elem1_grad = grad_data[i].getData();
			double grad_factor = -elem1.delta * 2.0 * overlap_contrib;
			
			elem1_grad[0] += grad_factor * (elem1_ctr[0] - inters_prod_ctr_data[0]);
			elem1_grad[1] += grad_factor * (elem1_ctr[1] - inters_prod_ctr_data[1]);
			elem1_grad[2] += grad_factor * (elem1_ctr[2] - inters_prod_ctr_data[2]);
		}
	}
	
	return overlap;
}

void Shape::FastGaussianShapeAlignment::processResults(std::size_t ref_idx, std::size_t al_idx)
{
	using namespace AlignmentResultSelectionMode;

	AlignmentResult curr_res;

// TODO
}

bool Shape::FastGaussianShapeAlignment::getResultIndex(const ResultID& res_id, std::size_t& res_idx)
{
	ResultIndexMap::const_iterator it = resIndexMap.find(res_id);

	if (it == resIndexMap.end()) {
		res_idx = results.size();

		results.resize(res_idx + 1);
		resIndexMap.insert(ResultIndexMap::value_type(res_id, res_idx));

		return true;
	}

	res_idx = it->second;
	return false;
}

#pragma GCC diagnostic pop
