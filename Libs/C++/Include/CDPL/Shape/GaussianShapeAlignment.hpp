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

#include <vector>
#include <cstddef>

#include <boost/shared_ptr.hpp>
#include <boost/function.hpp>

#include "CDPL/Shape/APIPrefix.hpp"
#include "CDPL/Shape/GaussianShapeFunctionAlignment.hpp"
#include "CDPL/Shape/GaussianShapeFunction.hpp"
#include "CDPL/Shape/GaussianShapeSet.hpp"
#include "CDPL/Math/Matrix.hpp"
#include "CDPL/Util/ObjectStack.hpp"


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
				Result();

				const Math::Matrix4D& getTransform() const {
					return transform;
				}

				std::size_t getReferenceShapeIndex() const {
					return refShapeIdx;
				}

				std::size_t getAlignedShapeIndex() const {
					return algdShapeIdx;
				}

				std::size_t getStartingPoseID() const {
					return startPoseID;
				}
				
				double getReferenceSelfOverlap() const {
					return refSelfOverlap;
				}

				double getReferenceColorSelfOverlap() const {
					return refColSelfOverlap;
				}

				double getAlignedSelfOverlap() const {
					return algdSelfOverlap;
				}

				double getAlignedColorSelfOverlap() const {
					return algdColSelfOverlap;
				}

				double getOverlap() const {
					return overlap;
				}

				double getColorOverlap() const {
					return colOverlap;
				}
				
			private:
				Math::Matrix4D transform;
				std::size_t    refShapeIdx;
				std::size_t    algdShapeIdx;
				std::size_t    startPoseID;
				double         refSelfOverlap;
				double         refColSelfOverlap;
				double         algdSelfOverlap;
				double         algdColSelfOverlap;
				double         overlap;
				double         colOverlap;
			};

			enum ResultSelectionMode
			{

			    ALL,
				BEST_RESULT_FOR_EACH_PAIR,
				BEST_RESULT_FOR_EACH_REF,
				BEST_RESULT_PAIR
			};

		  private:
			typedef std::vector<Result> ResultList;
			
		  public:
			typedef boost::shared_ptr<GaussianShapeAlignment> SharedPointer;

			typedef ResultList::const_iterator ConstResultIterator;

			typedef GaussianShapeFunctionAlignment::ColorFilterFunction ColorFilterFunction;
			typedef GaussianShapeFunctionAlignment::ColorMatchFunction ColorMatchFunction;
			typedef boost::function2<bool, const Result&, const Result&> ResultCompareFunction;

			GaussianShapeAlignment();

			GaussianShapeAlignment(const GaussianShape& ref_shape);

			GaussianShapeAlignment(const GaussianShapeSet& ref_shapes);

			~GaussianShapeAlignment();

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

			void setResultCompareFunction(const ResultCompareFunction& func);

			const ResultCompareFunction& getResultCompareFunction() const;

			void setResultSelectionMode(ResultSelectionMode mode);

			ResultSelectionMode getResultSelectionMode() const;

			void calcSelfOverlaps(bool calc);

			bool calcSelfOverlaps() const;

			void calcColorSelfOverlaps(bool calc);

			bool calcColorSelfOverlaps() const;

			void calcColorOverlaps(bool calc);

			bool calcColorOverlaps() const;

			void refineStartingPoses(bool refine);

			bool refineStartingPoses() const;

			void setMaxNumRefinementIterations(std::size_t max_iter);

			std::size_t getMaxNumRefinementIterations() const;

			void setRefinementStopGradient(double grad_norm);

			double getRefinementStopGradient() const;

			void setMaxOrder(std::size_t max_order);

			std::size_t getMaxOrder() const;

			void setDistanceCutoff(double cutoff);

			double getDistanceCutoff() const;

			void setReferenceShape(const GaussianShape& shape);

			void setReferenceShapes(const GaussianShapeSet& shapes);

			const GaussianShapeSet& getReferenceShapes() const;
		
			bool align(const GaussianShape& shape);

			bool align(const GaussianShapeSet& shapes);

			std::size_t getNumResults() const;

			const Result& getResult(std::size_t idx) const;

			ConstResultIterator getResultsBegin() const;

			ConstResultIterator getResultsEnd() const;
						
		  private:
			GaussianShapeAlignment(const GaussianShapeAlignment& alignment);

			GaussianShapeAlignment& operator=(const GaussianShapeAlignment& alignment);

			typedef Util::ObjectStack<GaussianShape> ShapeCache;
			typedef Util::ObjectStack<GaussianShapeFunction> ShapeFunctionCache;
			typedef std::vector<GaussianShape*> ShapeList;
			typedef std::vector<GaussianShapeFunction*> ShapeFunctionList;

			ShapeFunctionCache             shapeFuncCache;
			ShapeCache                     shapeCache;
			bool                           calcSlfOverlaps;
			bool                           calcColSlfOverlaps;
			bool                           calcColOverlaps;
			ResultSelectionMode            resultSelMode;
			ResultCompareFunction          resultCmpFunc;
			std::size_t                    maxOrder;
			double                         distCutoff;
			GaussianShapeFunctionAlignment shapeFuncAlmnt;
			ShapeList                      refShapes;
			ShapeFunctionList              refShapeFuncs;
			GaussianShape                  algdShape;
			GaussianShapeFunction          algdShapeFunc;
			ResultList                     results;
		};

		/**
		 * @}
		 */
    }
}

#endif // CDPL_SHAPE_GAUSSIANSHAPEALIGNMENT_HPP
