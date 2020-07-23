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

#include "CDPL/Shape/GaussianShapeAlignment.hpp"
#include "CDPL/Shape/SimilarityScores.hpp"
#include "CDPL/Base/Exceptions.hpp"


using namespace CDPL;


namespace
{

	bool compareScore(const Shape::AlignmentResult& res1, const Shape::AlignmentResult& res2)
	{
		return (res1.getScore() >= res2.getScore());
	}

	const Shape::GaussianShape& getShape(const Shape::GaussianShapeFunction* func)
	{
		return *func->getShape();
	}

	const std::size_t MAX_SHAPE_FUNC_CACHE_SIZE = 200;
}


Shape::GaussianShapeAlignment::GaussianShapeAlignment():
	shapeFuncCache(MAX_SHAPE_FUNC_CACHE_SIZE), calcSlfOverlaps(true), calcColSlfOverlaps(true),
	calcColOverlaps(true), resultSelMode(BEST_RESULT_PAIR), resultCmpFunc(&compareScore), 
	scoringFunc(TotalOverlapTanimotoScore())
{
	algdShapeFunc.setMaxOrder(1);
}

Shape::GaussianShapeAlignment::GaussianShapeAlignment(const GaussianShape& ref_shape):
	shapeFuncCache(MAX_SHAPE_FUNC_CACHE_SIZE), calcSlfOverlaps(true), calcColSlfOverlaps(true),
	calcColOverlaps(true), resultSelMode(BEST_RESULT_PAIR), resultCmpFunc(&compareScore), 
	scoringFunc(TotalOverlapTanimotoScore())
{
	algdShapeFunc.setMaxOrder(1);

	setReference(ref_shape);
}

Shape::GaussianShapeAlignment::GaussianShapeAlignment(const GaussianShapeSet& ref_shapes):
	shapeFuncCache(MAX_SHAPE_FUNC_CACHE_SIZE), calcSlfOverlaps(true), calcColSlfOverlaps(true),
	calcColOverlaps(true), resultSelMode(BEST_RESULT_PAIR), resultCmpFunc(&compareScore), 
	scoringFunc(TotalOverlapTanimotoScore())
{
	algdShapeFunc.setMaxOrder(1);

	setReferenceSet(ref_shapes);
}

Shape::GaussianShapeAlignment::~GaussianShapeAlignment() 
{}

void Shape::GaussianShapeAlignment::setOverlapFunction(GaussianShapeOverlapFunction& func)
{
	shapeFuncAlmnt.setOverlapFunction(func);
}
			
Shape::GaussianShapeOverlapFunction& Shape::GaussianShapeAlignment::getOverlapFunction() const
{
	return shapeFuncAlmnt.getOverlapFunction();
}

const Shape::FastGaussianShapeOverlapFunction& Shape::GaussianShapeAlignment::getDefaultOverlapFunction() const
{
	return shapeFuncAlmnt.getDefaultOverlapFunction();
}

Shape::FastGaussianShapeOverlapFunction& Shape::GaussianShapeAlignment::getDefaultOverlapFunction()
{
	return shapeFuncAlmnt.getDefaultOverlapFunction();
}

void Shape::GaussianShapeAlignment::setStartGenerator(GaussianShapeAlignmentStartGenerator& gen)
{
	shapeFuncAlmnt.setStartGenerator(gen);
}
			
Shape::GaussianShapeAlignmentStartGenerator& Shape::GaussianShapeAlignment::getStartGenerator() const
{
	return shapeFuncAlmnt.getStartGenerator();
}

const Shape::PrincipalAxesAlignmentStartGenerator& Shape::GaussianShapeAlignment::getDefaultStartGenerator() const
{
	return shapeFuncAlmnt.getDefaultStartGenerator();
}

Shape::PrincipalAxesAlignmentStartGenerator& Shape::GaussianShapeAlignment::getDefaultStartGenerator()
{
	return shapeFuncAlmnt.getDefaultStartGenerator();
}

void Shape::GaussianShapeAlignment::setColorMatchFunction(const ColorMatchFunction& func)
{
	shapeFuncAlmnt.setColorMatchFunction(func);
}

const Shape::GaussianShapeAlignment::ColorMatchFunction& Shape::GaussianShapeAlignment::getColorMatchFunction() const
{
	return shapeFuncAlmnt.getColorMatchFunction();
}
	
void Shape::GaussianShapeAlignment::setColorFilterFunction(const ColorFilterFunction& func)
{
	shapeFuncAlmnt.setColorFilterFunction(func);
}

const Shape::GaussianShapeAlignment::ColorFilterFunction& Shape::GaussianShapeAlignment::getColorFilterFunction() const
{
	return shapeFuncAlmnt.getColorFilterFunction();
}

void Shape::GaussianShapeAlignment::setResultCompareFunction(const ResultCompareFunction& func)
{
	if (!func)
		resultCmpFunc = &compareScore;
	else
		resultCmpFunc = func;
}

const Shape::GaussianShapeAlignment::ResultCompareFunction& Shape::GaussianShapeAlignment::getResultCompareFunction() const
{
	return resultCmpFunc;
}

void Shape::GaussianShapeAlignment::setScoringFunction(const ScoringFunction& func)
{
	if (!func)
		scoringFunc = TotalOverlapTanimotoScore();
	else
		scoringFunc = func;
}

const Shape::GaussianShapeAlignment::ScoringFunction& Shape::GaussianShapeAlignment::getScoringFunction() const
{
	return scoringFunc;
}

void Shape::GaussianShapeAlignment::setResultSelectionMode(ResultSelectionMode mode)
{
	resultSelMode = mode;
}

Shape::GaussianShapeAlignment::ResultSelectionMode Shape::GaussianShapeAlignment::getResultSelectionMode() const
{
	return resultSelMode;
}

void Shape::GaussianShapeAlignment::calcSelfOverlaps(bool calc)
{
	calcSlfOverlaps = calc;
}

bool Shape::GaussianShapeAlignment::calcSelfOverlaps() const
{
	return calcSlfOverlaps;
}

void Shape::GaussianShapeAlignment::calcColorSelfOverlaps(bool calc)
{
	calcColSlfOverlaps = calc;
}

bool Shape::GaussianShapeAlignment::calcColorSelfOverlaps() const
{
	return calcColSlfOverlaps;
}

void Shape::GaussianShapeAlignment::calcColorOverlaps(bool calc)
{
	calcColOverlaps = calc;
}

bool Shape::GaussianShapeAlignment::calcColorOverlaps() const
{
	return calcColOverlaps;
}

void Shape::GaussianShapeAlignment::refineStartingPoses(bool refine)
{
	shapeFuncAlmnt.refineStartingPoses(refine);
}

bool Shape::GaussianShapeAlignment::refineStartingPoses() const
{
	return shapeFuncAlmnt.refineStartingPoses();
}

void Shape::GaussianShapeAlignment::setMaxNumRefinementIterations(std::size_t max_iter)
{
	shapeFuncAlmnt.setMaxNumRefinementIterations(max_iter);
}

std::size_t Shape::GaussianShapeAlignment::getMaxNumRefinementIterations() const
{
	return shapeFuncAlmnt.getMaxNumRefinementIterations();
}

void Shape::GaussianShapeAlignment::setRefinementStopGradient(double grad_norm)
{
	shapeFuncAlmnt.setRefinementStopGradient(grad_norm);
}

double Shape::GaussianShapeAlignment::getRefinementStopGradient() const
{
	return shapeFuncAlmnt.getRefinementStopGradient();
}

void Shape::GaussianShapeAlignment::setMaxOrder(std::size_t max_order)
{
	algdShapeFunc.setMaxOrder(max_order);
}

std::size_t Shape::GaussianShapeAlignment::getMaxOrder() const
{
	return algdShapeFunc.getMaxOrder();
}

void Shape::GaussianShapeAlignment::setDistanceCutoff(double cutoff)
{
	algdShapeFunc.setDistanceCutoff(cutoff);
}

double Shape::GaussianShapeAlignment::getDistanceCutoff() const
{
	return algdShapeFunc.getDistanceCutoff();
}

void Shape::GaussianShapeAlignment::setReference(const GaussianShape& shape)
{
	if (refShapeMetaData.empty())
		refShapeMetaData.resize(1);

	refShapeFuncs.clear();
	refShapeFuncs.push_back(allocShapeFunction(shape));

	prepareForAlignment(*refShapeFuncs[0], refShapeMetaData[0], true);
}

void Shape::GaussianShapeAlignment::setReferenceSet(const GaussianShapeSet& shapes)
{
	std::size_t num_shapes = shapes.getSize();

	if (refShapeMetaData.size() < num_shapes)
		refShapeMetaData.resize(num_shapes);

	refShapeFuncs.clear();

	for (std::size_t i = 0; i < num_shapes; i++) {
		GaussianShapeFunction* func = allocShapeFunction(shapes[i]);

		refShapeFuncs.push_back(func);

		prepareForAlignment(*func, refShapeMetaData[i], true);
	}
}

std::size_t Shape::GaussianShapeAlignment::getReferenceSetSize() const
{
	return refShapeFuncs.size();
}

const Shape::GaussianShape& Shape::GaussianShapeAlignment::getReference(std::size_t idx) const
{
	if (idx >= refShapeFuncs.size())
		throw Base::IndexError("GaussianShapeAlignment: reference shape index out of bounds");

	return *refShapeFuncs[idx]->getShape();
}

Shape::GaussianShapeAlignment::ConstShapeIterator Shape::GaussianShapeAlignment::getReferencesBegin() const
{
	return ConstShapeIterator(refShapeFuncs.begin(), &getShape);
}

Shape::GaussianShapeAlignment::ConstShapeIterator Shape::GaussianShapeAlignment::getReferencesEnd() const
{
	return ConstShapeIterator(refShapeFuncs.end(), &getShape);
}

bool Shape::GaussianShapeAlignment::align(const GaussianShape& shape)
{
	results.clear();
	shapeToResIndexMap.clear();

	algdShapeFunc.setShape(shape);

	prepareForAlignment(algdShapeFunc, algdShapeMetaData, false);

	for (std::size_t i = 0, num_ref_shapes = refShapeFuncs.size(); i < num_ref_shapes; i++) {
		shapeFuncAlmnt.setReference(*refShapeFuncs[i], refShapeMetaData[i].symClass);

		if (!shapeFuncAlmnt.align(algdShapeFunc, algdShapeMetaData.symClass, calcColOverlaps)) 
			continue;

		for (std::size_t j = 0, num_res = shapeFuncAlmnt.getNumResults(); j < num_res; j++)
			processResult(i, 0, j, shapeFuncAlmnt.getResult(j));
	}

	return !results.empty();
}

bool Shape::GaussianShapeAlignment::align(const GaussianShapeSet& shapes)
{
	results.clear();
	shapeToResIndexMap.clear();

	for (std::size_t i = 0, num_algd_shapes = shapes.getSize(), num_ref_shapes = refShapeFuncs.size(); i < num_algd_shapes; i++) {
		algdShapeFunc.setShape(shapes.getElement(i));

		prepareForAlignment(algdShapeFunc, algdShapeMetaData, false);

		for (std::size_t j = 0; j < num_ref_shapes; j++) {
			if (num_ref_shapes > 1 || i == 0)
				shapeFuncAlmnt.setReference(*refShapeFuncs[j], refShapeMetaData[j].symClass);

			if (!shapeFuncAlmnt.align(algdShapeFunc, algdShapeMetaData.symClass, calcColOverlaps))
				continue;

			for (std::size_t k = 0, num_res = shapeFuncAlmnt.getNumResults(); k < num_res; k++)
				processResult(j, i, k, shapeFuncAlmnt.getResult(k));
		}
	}

	return !results.empty();
}

std::size_t Shape::GaussianShapeAlignment::getNumResults() const
{
	return results.size();
}

const Shape::AlignmentResult& Shape::GaussianShapeAlignment::getResult(std::size_t idx) const
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
	
void Shape::GaussianShapeAlignment::prepareForAlignment(GaussianShapeFunction& func, ShapeMetaData& data, bool ref)
{
	data.selfOverlap = (calcSlfOverlaps ? shapeFuncAlmnt.calcSelfOverlap(func) : 0.0);
	data.colSelfOverlap = (calcColSlfOverlaps ? shapeFuncAlmnt.calcColorSelfOverlap(func) : 0.0);
	data.symClass = (ref ? shapeFuncAlmnt.setupReference(func, data.transform) : shapeFuncAlmnt.setupAligned(func, data.transform));
}

void Shape::GaussianShapeAlignment::processResult(std::size_t ref_idx, std::size_t al_idx, std::size_t start_idx, 
												  const GaussianShapeFunctionAlignment::Result& res)
{
	AlignmentResult curr_res;
	std::size_t out_res_idx = 0;

	curr_res.setOverlap(res.getOverlap());
	curr_res.setColorOverlap(res.getColorOverlap());
	curr_res.setReferenceSelfOverlap(refShapeMetaData[ref_idx].selfOverlap);
	curr_res.setReferenceColorSelfOverlap(refShapeMetaData[ref_idx].colSelfOverlap);
	curr_res.setAlignedSelfOverlap(algdShapeMetaData.selfOverlap);
	curr_res.setAlignedColorSelfOverlap(algdShapeMetaData.colSelfOverlap);
	curr_res.setScore(scoringFunc(curr_res));

	switch (resultSelMode) {

		case ALL:
			out_res_idx = results.size();
			results.resize(out_res_idx + 1);
			break;

		case BEST_RESULT_FOR_EACH_PAIR:
			if (getResultIndex(ref_idx, al_idx, out_res_idx))
				break;

			if (resultCmpFunc(curr_res, results[out_res_idx]))
				break;

			return;

		case BEST_RESULT_FOR_EACH_REF:
			if (getResultIndex(ref_idx, 0, out_res_idx))
				break;

			if (resultCmpFunc(curr_res, results[out_res_idx]))
				break;

			return;

		case BEST_RESULT_PAIR:
			if (results.empty()) {
				results.resize(1);
				break;
			} 

			if (resultCmpFunc(curr_res, results[0]))
				break;

		default:
			return;
	}

	Math::Matrix4D tmp(prod(refShapeMetaData[ref_idx].transform, res.getTransform()));

	curr_res.setTransform(prod(tmp, algdShapeMetaData.transform));
	curr_res.setReferenceShapeIndex(ref_idx);
	curr_res.setAlignedShapeIndex(al_idx);
	curr_res.setStartingPoseID(start_idx);

	results[out_res_idx] = curr_res;
}

bool Shape::GaussianShapeAlignment::getResultIndex(std::size_t ref_idx, std::size_t al_idx, std::size_t& res_idx)
{
	std::pair<std::size_t, std::size_t> idx_pair(ref_idx, al_idx); 
	ShapePairToResultIndexMap::const_iterator it = shapeToResIndexMap.find(idx_pair);

	if (it == shapeToResIndexMap.end()) {
		res_idx = results.size();

		results.resize(res_idx + 1);
		shapeToResIndexMap.insert(ShapePairToResultIndexMap::value_type(idx_pair, res_idx));

		return true;
	}

	res_idx = it->second;
	return false;
}

Shape::GaussianShapeFunction* Shape::GaussianShapeAlignment::allocShapeFunction(const GaussianShape& shape)
{
	GaussianShapeFunction* func = shapeFuncCache.getRaw();

	func->setMaxOrder(algdShapeFunc.getMaxOrder());
	func->setDistanceCutoff(algdShapeFunc.getDistanceCutoff());
	func->setShape(shape);

	return func;
}
