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


using namespace CDPL;


Shape::GaussianShapeAlignment::GaussianShapeAlignment(GaussianShapeOverlapFunction& overlap_func):
	overlapFunc(&overlap_func), alignmentFunc(overlap_func), minimizer(boost::ref(alignmentFunc), boost::ref(alignmentFunc))
{}

Shape::GaussianShapeAlignment::GaussianShapeAlignment(GaussianShapeOverlapFunction& overlap_func, const GaussianShapeFunction& ref_shape_func):
	overlapFunc(&overlap_func), alignmentFunc(overlap_func), minimizer(boost::ref(alignmentFunc), boost::ref(alignmentFunc))
{
   setReferenceShapeFunction(ref_shape_func);
}

Shape::GaussianShapeAlignment::~GaussianShapeAlignment() {}

void Shape::GaussianShapeAlignment::setReferenceShapeFunction(const GaussianShapeFunction& func)
{
    overlapFunc->setShapeFunction(func, true);
}

const Shape::GaussianShapeFunction* Shape::GaussianShapeAlignment::getReferenceShapeFunction() const
{
    return overlapFunc->getShapeFunction(true);
}

void Shape::GaussianShapeAlignment::align(const GaussianShapeFunction& func)
{
}
