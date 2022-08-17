/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * GaussianShapeAlignmentStartGenerator.hpp 
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

/**
 * \file
 * \brief Definition of the class CDPL::Shape::GaussianShapeAlignmentStartGenerator.
 */

#ifndef CDPL_SHAPE_GAUSSIANSHAPEALIGNMENTSTARTGENERATOR_HPP
#define CDPL_SHAPE_GAUSSIANSHAPEALIGNMENTSTARTGENERATOR_HPP

#include <cstddef>

#include "CDPL/Shape/APIPrefix.hpp"
#include "CDPL/Shape/QuaternionTransformation.hpp"
#include "CDPL/Math/Matrix.hpp"


namespace CDPL 
{

    namespace Shape
    {

		class GaussianShape;
		class GaussianShapeFunction;
		
		class CDPL_SHAPE_API GaussianShapeAlignmentStartGenerator
		{
			
		  public:
			virtual ~GaussianShapeAlignmentStartGenerator() {}

			virtual unsigned int setupReference(GaussianShapeFunction& func, Math::Matrix4D& xform) const; 

			virtual unsigned int setupAligned(GaussianShapeFunction& func, Math::Matrix4D& xform) const; 

			virtual void setReference(const GaussianShapeFunction& ref_shape_func, unsigned int sym_class) = 0;

			virtual bool generate(const GaussianShapeFunction& func, unsigned int sym_class) = 0;
			
			virtual std::size_t getNumStartTransforms() const = 0;

			virtual std::size_t getNumStartSubTransforms() const = 0;

			virtual const QuaternionTransformation& getStartTransform(std::size_t idx) const = 0;
		};
    }
}

#endif // CDPL_SHAPE_GAUSSIANSHAPEALIGNMENTSTARTGENERATOR_HPP
