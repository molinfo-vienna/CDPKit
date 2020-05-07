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

#include <cstddef>
#include <vector>

#include <boost/shared_ptr.hpp>

#include "CDPL/Shape/APIPrefix.hpp"
#include "CDPL/Shape/ExactGaussianShapeOverlapFunction.hpp"
#include "CDPL/Shape/PrincipalAxesAlignmentStartGenerator.hpp"
#include "CDPL/Shape/GaussianShapeAlignmentFunction.hpp"
#include "CDPL/Math/Matrix.hpp"
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
			class Result
			{

			public:
				Result(const Math::Matrix4D& xform, double overlap):
					transform(xform), overlap(overlap) {}

				const Math::Matrix4D& getTransform() const {
					return transform;
				}

				double getOverlap() const {
					return overlap;
				}
				
			private:
				Math::Matrix4D transform;
				double         overlap;
			};

		  private:
			typedef std::vector<Result> ResultList;
			
		  public:
			typedef ResultList::const_iterator ConstResultIterator;
				
			typedef boost::shared_ptr<GaussianShapeAlignment> SharedPointer;

			GaussianShapeAlignment();

			GaussianShapeAlignment(const GaussianShapeFunction& ref_shape_func);
		
			GaussianShapeAlignment(GaussianShapeOverlapFunction& overlap_func);

			GaussianShapeAlignment(GaussianShapeOverlapFunction& overlap_func, const GaussianShapeFunction& ref_shape_func);

			~GaussianShapeAlignment();

			void setOverlapFunction(GaussianShapeOverlapFunction& func);
			
			GaussianShapeOverlapFunction& getOverlapFunction() const;

			void setStartGenerator(PrincipalAxesAlignmentStartGenerator& gen);
			
			GaussianShapeAlignmentStartGenerator& getStartGenerator() const;
			
			void setReferenceShapeFunction(const GaussianShapeFunction& func);

			const GaussianShapeFunction* getReferenceShapeFunction() const;
		
			bool align(const GaussianShapeFunction& func);

			std::size_t getNumResults() const;

			const Result& getResult(std::size_t idx) const;

			ConstResultIterator getResultsBegin() const;

			ConstResultIterator getResultsEnd() const;
						
		  private:
			GaussianShapeAlignment(const GaussianShapeAlignment& alignment);

			GaussianShapeAlignment& operator=(const GaussianShapeAlignment& alignment);

			typedef Math::BFGSMinimizer<QuaternionTransformation> BFGSMinimizer;

			ExactGaussianShapeOverlapFunction     defOverlapFunc;
			PrincipalAxesAlignmentStartGenerator  defStartGen;
			GaussianShapeOverlapFunction*         overlapFunc;
			GaussianShapeAlignmentStartGenerator* startGen;
			const GaussianShapeFunction*          refShapeFunc;
			GaussianShapeAlignmentFunction        alignmentFunc;
			BFGSMinimizer                         minimizer;
			ResultList                            results;
		};

		/**
		 * @}
		 */
    }
}

#endif // CDPL_SHAPE_GAUSSIANSHAPEALIGNMENT_HPP
