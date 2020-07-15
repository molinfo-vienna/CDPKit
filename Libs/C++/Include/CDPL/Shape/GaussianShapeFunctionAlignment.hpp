/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * GaussianShapeFunctionAlignment.hpp 
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
 * \brief Definition of the class CDPL::Shape::GaussianShapeFunctionAlignment.
 */

#ifndef CDPL_SHAPE_GAUSSIANSHAPEFUNCTIONALIGNMENT_HPP
#define CDPL_SHAPE_GAUSSIANSHAPEFUNCTIONALIGNMENT_HPP

#include <cstddef>
#include <vector>

#include <boost/shared_ptr.hpp>

#include "CDPL/Shape/APIPrefix.hpp"
#include "CDPL/Shape/FastGaussianShapeOverlapFunction.hpp"
#include "CDPL/Shape/PrincipalAxesAlignmentStartGenerator.hpp"
#include "CDPL/Shape/QuaternionTransformation.hpp"
#include "CDPL/Math/Matrix.hpp"
#include "CDPL/Math/VectorArray.hpp"
#include "CDPL/Math/BFGSMinimizer.hpp"


namespace CDPL 
{

    namespace Shape
    {
		
		/**
		 * \addtogroup CDPL_SHAPE_ALIGNMENT
		 * @{
		 */

		class CDPL_SHAPE_API GaussianShapeFunctionAlignment
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
			typedef boost::shared_ptr<GaussianShapeFunctionAlignment> SharedPointer;
			typedef ResultList::const_iterator ConstResultIterator;
			typedef GaussianShapeOverlapFunction::ColorMatchFunction ColorMatchFunction;

			GaussianShapeFunctionAlignment();

			GaussianShapeFunctionAlignment(const GaussianShapeFunction& ref_shape_func, unsigned int sym_class);

			~GaussianShapeFunctionAlignment();

			void setOverlapFunction(GaussianShapeOverlapFunction& func);
			
			GaussianShapeOverlapFunction& getOverlapFunction() const;

			const FastGaussianShapeOverlapFunction& getDefaultOverlapFunction() const;

			FastGaussianShapeOverlapFunction& getDefaultOverlapFunction();

			void setStartGenerator(GaussianShapeAlignmentStartGenerator& gen);
			
			GaussianShapeAlignmentStartGenerator& getStartGenerator() const;

			const PrincipalAxesAlignmentStartGenerator& getDefaultStartGenerator() const;

			PrincipalAxesAlignmentStartGenerator& getDefaultStartGenerator();

			void setColorMatchFunction(const ColorMatchFunction& func);

			const ColorMatchFunction& getColorMatchFunction() const;

			unsigned int setupReferenceShape(GaussianShape& shape, GaussianShapeFunction& shape_func, Math::Matrix4D& xform) const;

			unsigned int setupAlignedShape(GaussianShape& shape, GaussianShapeFunction& shape_func, Math::Matrix4D& xform) const; 

			void setReferenceShapeFunction(const GaussianShapeFunction& func, unsigned int sym_class);

			const GaussianShapeFunction* getReferenceShapeFunction() const;
		
			bool align(const GaussianShapeFunction& func, unsigned int sym_class);

			std::size_t getNumResults() const;

			const Result& getResult(std::size_t idx) const;

			ConstResultIterator getResultsBegin() const;

			ConstResultIterator getResultsEnd() const;
						
		  private:
			GaussianShapeFunctionAlignment(const GaussianShapeFunctionAlignment& alignment);

			GaussianShapeFunctionAlignment& operator=(const GaussianShapeFunctionAlignment& alignment);

			double calcAlignmentFunctionValue(const QuaternionTransformation& xform_quat);
			double calcAlignmentFunctionGradient(const QuaternionTransformation& xform_quat, QuaternionTransformation& xform_grad);
			
			typedef Math::BFGSMinimizer<QuaternionTransformation> BFGSMinimizer;

			FastGaussianShapeOverlapFunction      defOverlapFunc;
			PrincipalAxesAlignmentStartGenerator  defStartGen;
			GaussianShapeOverlapFunction*         overlapFunc;
			GaussianShapeAlignmentStartGenerator* startGen;
			const GaussianShapeFunction*          refShapeFunc;
			unsigned int                          refShapeSymClass;
			Math::Vector3DArray                   startPoseCoords;
			Math::Vector3DArray                   optPoseCoords;
			Math::Vector3DArray                   optPoseCoordsGrad;
			BFGSMinimizer                         minimizer;
			ResultList                            results;
		};

		/**
		 * @}
		 */
    }
}

#endif // CDPL_SHAPE_GAUSSIANSHAPEFUNCTIONALIGNMENT_HPP
