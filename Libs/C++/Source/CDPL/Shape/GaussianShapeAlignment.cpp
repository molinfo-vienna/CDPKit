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
#include "CDPL/Base/Exceptions.hpp"


using namespace CDPL;


namespace
{

	bool compareOverlap(const Shape::GaussianShapeAlignment::Result& res1, const Shape::GaussianShapeAlignment::Result& res2)
	{
		return (res1.getOverlap() >= res2.getOverlap());
	}

	const std::size_t MAX_SHAPE_FUNC_CACHE_SIZE = 200;
}


Shape::GaussianShapeAlignment::Result::Result():
	transform(), refShapeIdx(0), algdShapeIdx(0), startPoseID(0), refSelfOverlap(0.0),
	refColSelfOverlap(0.0), algdSelfOverlap(0.0), algdColSelfOverlap(0.0), overlap(0.0),
	colOverlap(0.0)
{}

const Math::Matrix4D& Shape::GaussianShapeAlignment::Result::getTransform() const
{
	return transform;
}

void Shape::GaussianShapeAlignment::Result::setTransform(const Math::Matrix4D& xform)
{
	transform = xform;
}

std::size_t Shape::GaussianShapeAlignment::Result::getReferenceShapeIndex() const 
{
	return refShapeIdx;
}

void Shape::GaussianShapeAlignment::Result::setReferenceShapeIndex(std::size_t idx)
{
	refShapeIdx = idx;
}

std::size_t Shape::GaussianShapeAlignment::Result::getAlignedShapeIndex() const 
{
	return algdShapeIdx;
}

void Shape::GaussianShapeAlignment::Result::setAlignedShapeIndex(std::size_t idx)
{
	algdShapeIdx = idx;
}

std::size_t Shape::GaussianShapeAlignment::Result::getStartingPoseID() const 
{
	return startPoseID;
}
			
void Shape::GaussianShapeAlignment::Result::setStartingPoseID(std::size_t id)
{
	startPoseID = id;
}
		
double Shape::GaussianShapeAlignment::Result::getReferenceSelfOverlap() const 
{
	return refSelfOverlap;
}

void Shape::GaussianShapeAlignment::Result::setReferenceSelfOverlap(double overlap)
{
	refSelfOverlap = overlap;
}

double Shape::GaussianShapeAlignment::Result::getReferenceColorSelfOverlap() const 
{
	return refColSelfOverlap;
}

void Shape::GaussianShapeAlignment::Result::setReferenceColorSelfOverlap(double overlap)
{
	refColSelfOverlap = overlap;
}

double Shape::GaussianShapeAlignment::Result::getAlignedSelfOverlap() const 
{
	return algdSelfOverlap;
}

void Shape::GaussianShapeAlignment::Result::setAlignedSelfOverlap(double overlap)
{
	algdSelfOverlap = overlap;
}

double Shape::GaussianShapeAlignment::Result::getAlignedColorSelfOverlap() const 
{
	return algdColSelfOverlap;
}

void Shape::GaussianShapeAlignment::Result::setAlignedColorSelfOverlap(double overlap)
{
	algdColSelfOverlap = overlap;
}

double Shape::GaussianShapeAlignment::Result::getOverlap() const 
{
	return overlap;
}

void Shape::GaussianShapeAlignment::Result::setOverlap(double overlap)
{
	this->overlap = overlap;
}

double Shape::GaussianShapeAlignment::Result::getColorOverlap() const 
{
	return colOverlap;
}
				
void Shape::GaussianShapeAlignment::Result::setColorOverlap(double overlap)
{
	colOverlap = overlap;
}

//------

Shape::GaussianShapeAlignment::GaussianShapeAlignment():
	shapeFuncCache(MAX_SHAPE_FUNC_CACHE_SIZE), calcSlfOverlaps(false), calcColSlfOverlaps(false),
	calcColOverlaps(false), resultSelMode(BEST_RESULT_PAIR), resultCmpFunc(&compareOverlap)
{
	algdShapeFunc.setMaxOrder(1);
}

Shape::GaussianShapeAlignment::GaussianShapeAlignment(const GaussianShape& ref_shape):
	shapeFuncCache(MAX_SHAPE_FUNC_CACHE_SIZE), calcSlfOverlaps(false), calcColSlfOverlaps(false),
	calcColOverlaps(false), resultSelMode(BEST_RESULT_PAIR), resultCmpFunc(&compareOverlap)
{
	algdShapeFunc.setMaxOrder(1);

	setReference(ref_shape);
}

Shape::GaussianShapeAlignment::GaussianShapeAlignment(const GaussianShapeSet& ref_shapes):
	shapeFuncCache(MAX_SHAPE_FUNC_CACHE_SIZE), calcSlfOverlaps(false), calcColSlfOverlaps(false),
	calcColOverlaps(false), resultSelMode(BEST_RESULT_PAIR), resultCmpFunc(&compareOverlap)
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
	resultCmpFunc = func;
}

const Shape::GaussianShapeAlignment::ResultCompareFunction& Shape::GaussianShapeAlignment::getResultCompareFunction() const
{
	return resultCmpFunc;
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
	// TODO
}

void Shape::GaussianShapeAlignment::setReferenceSet(const GaussianShapeSet& shapes)
{
	// TODO
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
		
bool Shape::GaussianShapeAlignment::align(const GaussianShape& shape)
{
	return false; // TODO
}

bool Shape::GaussianShapeAlignment::align(const GaussianShapeSet& shapes)
{
	return false; // TODO
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
