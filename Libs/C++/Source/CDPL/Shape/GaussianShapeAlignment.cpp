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

#include "CDPL/Shape/GaussianShapeAlignment.hpp"
#include "CDPL/Shape/GaussianShapeFunction.hpp"
#include "CDPL/Shape/GaussianShape.hpp"
#include "CDPL/Shape/UtilityFunctions.hpp"
#include "CDPL/Base/Exceptions.hpp"


using namespace CDPL;


Shape::GaussianShapeAlignment::GaussianShapeAlignment():
	overlapFunc(&defOverlapFunc), startGen(&defStartGen), refShapeFunc(0), alignmentFunc(defOverlapFunc),
	minimizer(boost::ref(alignmentFunc), boost::ref(alignmentFunc))
{}

Shape::GaussianShapeAlignment::GaussianShapeAlignment(const GaussianShapeFunction& ref_shape_func):
	overlapFunc(&defOverlapFunc), startGen(&defStartGen), alignmentFunc(defOverlapFunc),
	minimizer(boost::ref(alignmentFunc), boost::ref(alignmentFunc))
{
   setReferenceShapeFunction(ref_shape_func);
}

Shape::GaussianShapeAlignment::GaussianShapeAlignment(GaussianShapeOverlapFunction& overlap_func):
	overlapFunc(&overlap_func), startGen(&defStartGen), refShapeFunc(0), alignmentFunc(overlap_func),
	minimizer(boost::ref(alignmentFunc), boost::ref(alignmentFunc))
{}

Shape::GaussianShapeAlignment::GaussianShapeAlignment(GaussianShapeOverlapFunction& overlap_func, const GaussianShapeFunction& ref_shape_func):
	overlapFunc(&overlap_func), startGen(&defStartGen), alignmentFunc(overlap_func),
	minimizer(boost::ref(alignmentFunc), boost::ref(alignmentFunc))
{
   setReferenceShapeFunction(ref_shape_func);
}

Shape::GaussianShapeAlignment::~GaussianShapeAlignment() {}

void Shape::GaussianShapeAlignment::setOverlapFunction(GaussianShapeOverlapFunction& func)
{
	overlapFunc = &func;

	alignmentFunc.setOverlapFunction(func);

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
		startGen->setup(*refShapeFunc);
}
			
Shape::GaussianShapeAlignmentStartGenerator& Shape::GaussianShapeAlignment::getStartGenerator() const
{
	return *startGen;
}

void Shape::GaussianShapeAlignment::setReferenceShapeFunction(const GaussianShapeFunction& func)
{
	refShapeFunc = &func;
	
    overlapFunc->setShapeFunction(func, true);
	startGen->setup(func);
}

const Shape::GaussianShapeFunction* Shape::GaussianShapeAlignment::getReferenceShapeFunction() const
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

	if (!startGen->generate(func))
		return false;

	std::size_t num_starts = startGen->getNumStartTransforms();
	
	results.reserve(num_starts);

	QuaternionTransformation opt_xform;
	QuaternionTransformation opt_xform_grad;
	Math::Matrix4D opt_xform_mtx;

	overlapFunc->setShapeFunction(func, false);
	
	for (std::size_t i = 0; i < num_starts; i++) {
		opt_xform = startGen->getStartTransform(i);
		quaternionToMatrix(opt_xform, opt_xform_mtx);

		//std::cerr << "start overlap: " << overlapFunc->calcOverlap(opt_xform_mtx, true) << std::endl;
			
		minimizer.setup(opt_xform, opt_xform_grad, 0.01, 0.15);
		minimizer.minimize(opt_xform, opt_xform_grad, 200, 0.01, -1.0, false);
	
		//std::cerr << "num iter = " << minimizer.getNumIterations() << ", gnorm = " << minimizer.getGradientNorm() << std::endl;
		
	    if (boost::math::isfinite(minimizer.getFunctionValue())) {  // sanity check
			quaternionToMatrix(opt_xform, opt_xform_mtx);

			double opt_overlap = overlapFunc->calcOverlap(opt_xform_mtx, true);

			//std::cerr << "opt overlap: " <<  opt_overlap << std::endl;
						
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
