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
#include <vector>

#include <boost/shared_ptr.hpp>

#include "CDPL/Shape/APIPrefix.hpp"
#include "CDPL/Shape/GaussianShapeFunction.hpp"
#include "CDPL/Math/Vector.hpp"
#include "CDPL/Math/VectorArray.hpp"
#include "CDPL/Math/Matrix.hpp"


namespace CDPL 
{

    namespace Shape
    {

		class GaussianProductList;
		
		/**
		 * \addtogroup CDPL_SHAPE_FUNCTORS
		 * @{
		 */

		class CDPL_SHAPE_API GaussianShapeOverlapFunction
		{
			
		  public:
			typedef boost::shared_ptr<GaussianShapeOverlapFunction> SharedPointer;

			GaussianShapeOverlapFunction();

			GaussianShapeOverlapFunction(const GaussianShapeOverlapFunction& func);
			
			GaussianShapeOverlapFunction(const GaussianShape& ref_shape, const GaussianShape& ovl_shape);

			~GaussianShapeOverlapFunction();

			void setShape(const GaussianShape& shape, bool is_ref);

			const GaussianShapeFunction& getShapeFunction(bool ref) const;
		
			void setMaxOrder(std::size_t max_order);

			std::size_t getMaxOrder() const;

			void setDistanceCutoff(double cutoff);

			double getDistanceCutoff() const;

			void exactCalculations(bool exact);

			bool exactCalculations() const;
			
			double calcOverlap() const;

			double calcOverlap(const Math::Matrix4D& xform);

			double calcOverlapGradient(const Math::Matrix4D& xform, Math::Vector3DArray& grad);
			
			GaussianShapeOverlapFunction& operator=(const GaussianShapeOverlapFunction& func);
			
		  private:
			void prepareOverlapCalc(const Math::Matrix4D& xform);
			void prepareGradientCalc(const Math::Matrix4D& xform, Math::Vector3DArray& grad);
			
			double calcOverlap(const GaussianProductList* prod_list1, const GaussianProductList* prod_list2,
							   bool orig_centers) const;
			double calcOverlapGradient(Math::Vector3DArray& grad) const;

			typedef std::vector<Math::Vector3D> GaussianProductCenterArray; 
			
			GaussianShapeFunction        refShapeFunc;
			GaussianShapeFunction        ovlShapeFunc;
			GaussianProductCenterArray   prodCenters;
			bool                         exact;
		};

		/**
		 * @}
		 */
    }
}

#endif // CDPL_SHAPE_GAUSSIANSHAPEOVERLAPFUNCTION_HPP
