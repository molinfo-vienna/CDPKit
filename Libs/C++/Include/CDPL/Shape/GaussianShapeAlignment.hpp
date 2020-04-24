/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * GaussianShapeAlignment.hpp 
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
 * \brief Definition of the class CDPL::Shape::GaussianShapeAlignment.
 */

#ifndef CDPL_SHAPE_GAUSSIANSHAPEALIGNMENT_HPP
#define CDPL_SHAPE_GAUSSIANSHAPEALIGNMENT_HPP

#include <boost/shared_ptr.hpp>

#include "CDPL/Shape/APIPrefix.hpp"
#include "CDPL/Shape/GaussianShapeOverlapFunction.hpp"
#include "CDPL/Shape/GaussianShapeAlignmentFunction.hpp"
#include "CDPL/Shape/QuaternionTransformation.hpp"
#include "CDPL/Math/BFGSMinimizer.hpp"


namespace CDPL 
{

    namespace Shape
    {
		
		/**
		 * \addtogroup CDPL_SHAPE_ALIGNMENT
		 * @{
		 */

		class CDPL_SHAPE_API GaussianShapeAlignment
		{
			
		  public:
			typedef boost::shared_ptr<GaussianShapeAlignment> SharedPointer;
			
			GaussianShapeAlignment();

			GaussianShapeAlignment(const GaussianShapeAlignment& alignment);
			
			GaussianShapeAlignment(const GaussianShapeFunction& func);

			~GaussianShapeAlignment();

			void setReferenceShapeFunction(const GaussianShapeFunction& func);

			const GaussianShapeFunction* getReferenceShapeFunction() const;
		
			void align(const GaussianShapeFunction& func);
			
			GaussianShapeAlignment& operator=(const GaussianShapeAlignment& alignment);
			
		  private:
			typedef Math::BFGSMinimizer<QuaternionTransformation> BFGSMinimizer;
			
			GaussianShapeOverlapFunction   overlapFunc;
			GaussianShapeAlignmentFunction alignmentFunc;
			BFGSMinimizer                  minimizer;
		};

		/**
		 * @}
		 */
    }
}

#endif // CDPL_SHAPE_GAUSSIANSHAPEALIGNMENT_HPP
