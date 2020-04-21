/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * GaussianShapeFunction.hpp 
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
 * \brief Definition of the class CDPL::Shape::GaussianShapeFunction.
 */

#ifndef CDPL_SHAPE_GAUSSIANSHAPEFUNCTION_HPP
#define CDPL_SHAPE_GAUSSIANSHAPEFUNCTION_HPP

#include <cstddef>
#include <memory>

#include <boost/shared_ptr.hpp>

#include "CDPL/Shape/APIPrefix.hpp"
#include "CDPL/Math/Vector.hpp"
#include "CDPL/Math/Matrix.hpp"


namespace CDPL 
{

    namespace Shape
    {

		class GaussianShape;
		class GaussianProductList;
		class GaussianShapeOverlapFunction;
		
		/**
		 * \addtogroup CDPL_SHAPE_FUNCTORS
		 * @{
		 */

		class CDPL_SHAPE_API GaussianShapeFunction
		{
			
		  public:
			static const std::size_t DEF_MAX_PRODUCT_ORDER = 6;
			static const double      DEF_DISTANCE_CUTOFF;
			
			typedef boost::shared_ptr<GaussianShapeFunction> SharedPointer;

			GaussianShapeFunction();

			GaussianShapeFunction(const GaussianShapeFunction& func);

			GaussianShapeFunction(const GaussianShape& shape);

			~GaussianShapeFunction();

			void setMaxOrder(std::size_t max_order);

			std::size_t getMaxOrder() const;

			void setDistanceCutoff(double cutoff);

			double getDistanceCutoff() const;
			
			void setShape(const GaussianShape& shape);

			const GaussianShape* getShape() const;
			
			double calcDensity(const Math::Vector3D& pos) const;
			
			double calcVolume() const;

			double calcSurfaceArea() const;

			double calcSurfaceArea(std::size_t elem_idx) const;

			void calcCentroid(Math::Vector3D& ctr) const;

			void calcQuadrupoleTensor(const Math::Vector3D& ctr, Math::Matrix3D& quad_tensor) const;
			
			GaussianShapeFunction& operator=(const GaussianShapeFunction& func);
			
		  private:
			friend class GaussianShapeOverlapFunction;
			
			const GaussianProductList* getProductList() const;
			
			typedef std::auto_ptr<GaussianProductList> ProductListPtr;

			const GaussianShape* shape;
			double               volume;
			ProductListPtr       prodList;
		};

		/**
		 * @}
		 */
    }
}

#endif // CDPL_SHAPE_GAUSSIANSHAPEFUNCTION_HPP