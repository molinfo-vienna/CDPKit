/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * GaussianShapeOverlapFunction.hpp 
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
 * \brief Definition of the class CDPL::Shape::GaussianShapeOverlapFunction.
 */

#ifndef CDPL_SHAPE_GAUSSIANSHAPEOVERLAPFUNCTION_HPP
#define CDPL_SHAPE_GAUSSIANSHAPEOVERLAPFUNCTION_HPP

#include <cstddef>

#include <boost/shared_ptr.hpp>
#include <boost/function.hpp>

#include "CDPL/Shape/APIPrefix.hpp"
#include "CDPL/Math/VectorArray.hpp"


namespace CDPL 
{

    namespace Shape
    {

		class GaussianShapeFunction;
		
		/**
		 * \addtogroup CDPL_SHAPE_FUNCTORS
		 * @{
		 */

		class CDPL_SHAPE_API GaussianShapeOverlapFunction
		{
			
		  public:
			typedef boost::shared_ptr<GaussianShapeOverlapFunction> SharedPointer;

			typedef boost::function1<bool, std::size_t> ColorFilterFunction;
			typedef boost::function2<bool, std::size_t, std::size_t> ColorMatchFunction;

			virtual ~GaussianShapeOverlapFunction() {}

			virtual void setShapeFunction(const GaussianShapeFunction& func, bool is_ref) = 0;

			virtual const GaussianShapeFunction* getShapeFunction(bool ref) const = 0;

			virtual void setColorMatchFunction(const ColorMatchFunction& func) = 0;

			virtual const ColorMatchFunction& getColorMatchFunction() const = 0;

			virtual void setColorFilterFunction(const ColorFilterFunction& func) = 0;

			virtual const ColorFilterFunction& getColorFilterFunction() const = 0;

			virtual double calcSelfOverlap(bool ref) const = 0;

			virtual double calcColorSelfOverlap(bool ref) const = 0;
			
			virtual double calcOverlap() const = 0;

			virtual double calcColorOverlap() const = 0;

			virtual double calcOverlap(const Math::Vector3DArray& coords) const = 0;

			virtual double calcColorOverlap(const Math::Vector3DArray& coords) const = 0;

			virtual double calcOverlapGradient(const Math::Vector3DArray& coords, Math::Vector3DArray& grad) const = 0;

		  protected:
			GaussianShapeOverlapFunction() {}

			GaussianShapeOverlapFunction(const GaussianShapeOverlapFunction& func) {}

			GaussianShapeOverlapFunction& operator=(const GaussianShapeOverlapFunction& func) {
				return *this;
			}
		};

		/**
		 * @}
		 */
    }
}

#endif // CDPL_SHAPE_GAUSSIANSHAPEOVERLAPFUNCTION_HPP
