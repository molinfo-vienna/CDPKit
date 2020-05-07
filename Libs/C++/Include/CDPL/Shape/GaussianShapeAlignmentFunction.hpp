/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * GaussianShapeAlignmentFunction.hpp 
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
 * \brief Definition of the class CDPL::Shape::GaussianShapeAlignmentFunction.
 */

#ifndef CDPL_SHAPE_GAUSSIANSHAPEALIGNMENTFUNCTION_HPP
#define CDPL_SHAPE_GAUSSIANSHAPEALIGNMENTFUNCTION_HPP

#include "CDPL/Shape/APIPrefix.hpp"
#include "CDPL/Shape/QuaternionTransformation.hpp"
#include "CDPL/Math/VectorArray.hpp"


namespace CDPL 
{

    namespace Shape
    {

		class GaussianShapeOverlapFunction;
		
		/**
		 * \addtogroup CDPL_SHAPE_HELPERS
		 * @{
		 */

		class CDPL_SHAPE_API GaussianShapeAlignmentFunction
		{
			
		  public:
			static const double DEF_QUATERNION_UNITY_DEVIATION_PENALTY_FACTOR;
				
			GaussianShapeAlignmentFunction();

			GaussianShapeAlignmentFunction(GaussianShapeOverlapFunction& func);

			void setOverlapFunction(GaussianShapeOverlapFunction& func);

			GaussianShapeOverlapFunction* getOverlapFunction() const;
			
			void setQuaternionUnityDeviationPenaltyFactor(double factor);
						
			double getQuaternionUnityDeviationPenaltyFactor() const;
			
			double operator()(const QuaternionTransformation& xform_quat) const;

			double operator()(const QuaternionTransformation& xform_quat, QuaternionTransformation& grad);

		  private:
			GaussianShapeOverlapFunction* overlapFunc;
			Math::Vector3DArray           coordsGradient;
			double                        quatPenaltyFactor;
		};

		/**
		 * @}
		 */
    }
}

#endif // CDPL_SHAPE_GAUSSIANSHAPEALIGNMENTFUNCTION_HPP
