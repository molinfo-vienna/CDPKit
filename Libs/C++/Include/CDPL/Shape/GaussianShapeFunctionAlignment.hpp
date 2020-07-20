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
				Result(const Math::Matrix4D& xform, double overlap, double col_overlap):
					transform(xform), overlap(overlap), colOverlap(col_overlap) {}

				const Math::Matrix4D& getTransform() const {
					return transform;
				}

				double getOverlap() const {
					return overlap;
				}

				double getColorOverlap() const {
					return colOverlap;
				}
				
			private:
				Math::Matrix4D transform;
				double         overlap;
				double         colOverlap;
			};

		  private:
			typedef std::vector<Result> ResultList;
			
		  public:
			static const double      DEF_REFINEMENT_STOP_GRADIENT;
			static const std::size_t DEF_MAX_REFINEMENT_ITERATIONS = 200;

			typedef boost::shared_ptr<GaussianShapeFunctionAlignment> SharedPointer;

			typedef ResultList::const_iterator ConstResultIterator;

			typedef GaussianShapeOverlapFunction::ColorFilterFunction ColorFilterFunction;
			typedef GaussianShapeOverlapFunction::ColorMatchFunction ColorMatchFunction;

			GaussianShapeFunctionAlignment();

			GaussianShapeFunctionAlignment(const GaussianShapeFunction& ref_func, unsigned int sym_class);

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
	
			void setColorFilterFunction(const ColorFilterFunction& func);

			const ColorFilterFunction& getColorFilterFunction() const;

			void refineStartingPoses(bool refine);

			bool refineStartingPoses() const;

			void setMaxNumRefinementIterations(std::size_t max_iter);

			std::size_t getMaxNumRefinementIterations() const;

			void setRefinementStopGradient(double grad_norm);

			double getRefinementStopGradient() const;

			unsigned int setupReference(GaussianShapeFunction& func, Math::Matrix4D& xform) const;

			unsigned int setupAligned(GaussianShapeFunction& func, Math::Matrix4D& xform) const; 

			void setReference(const GaussianShapeFunction& func, unsigned int sym_class);

			const GaussianShapeFunction* getReference() const;
		
			double calcSelfOverlap(const GaussianShapeFunction& func);

			double calcColorSelfOverlap(const GaussianShapeFunction& func);

			bool align(const GaussianShapeFunction& func, unsigned int sym_class, bool calc_col_overlap = false);

			std::size_t getNumResults() const;

			const Result& getResult(std::size_t idx) const;

			ConstResultIterator getResultsBegin() const;

			ConstResultIterator getResultsEnd() const;
						
		  private:
			GaussianShapeFunctionAlignment(const GaussianShapeFunctionAlignment& alignment);

			GaussianShapeFunctionAlignment& operator=(const GaussianShapeFunctionAlignment& alignment);

			bool checkValidity(const GaussianShapeFunction& func) const;

			double calcAlignmentFunctionValue(const QuaternionTransformation& xform_quat);
			double calcAlignmentFunctionGradient(const QuaternionTransformation& xform_quat, QuaternionTransformation& xform_grad);
			
			typedef Math::BFGSMinimizer<QuaternionTransformation> BFGSMinimizer;

			FastGaussianShapeOverlapFunction      defOverlapFunc;
			PrincipalAxesAlignmentStartGenerator  defStartGen;
			GaussianShapeOverlapFunction*         overlapFunc;
			GaussianShapeAlignmentStartGenerator* startGen;
			const GaussianShapeFunction*          refShapeFunc;
			unsigned int                          refShapeSymClass;
			bool                                  refStartPoses;
			std::size_t                           maxNumRefIters;
			double                                refStopGrad;
			ColorFilterFunction                   colFilterFunc;
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
