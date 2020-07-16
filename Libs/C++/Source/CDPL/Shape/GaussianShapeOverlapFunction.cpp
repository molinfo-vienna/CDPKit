/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * GaussianShapeOverlapFunction.cpp 
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

#include "CDPL/Shape/GaussianShapeOverlapFunction.hpp"


using namespace CDPL;


namespace
{

	const Shape::GaussianShapeOverlapFunction::ColorFilterFunction VOID_FILTER;
}


double Shape::GaussianShapeOverlapFunction::calcSelfOverlap(bool ref) const
{
	return calcSelfOverlap(ref, VOID_FILTER);
}

double Shape::GaussianShapeOverlapFunction::calcOverlap() const
{
	return calcOverlap(VOID_FILTER);
}

double Shape::GaussianShapeOverlapFunction::calcOverlap(const Math::Vector3DArray& coords) const
{
	return calcOverlap(coords, VOID_FILTER);
}

double Shape::GaussianShapeOverlapFunction::calcOverlapGradient(const Math::Vector3DArray& coords, Math::Vector3DArray& grad) const
{
	return calcOverlapGradient(coords, grad, VOID_FILTER);
}
