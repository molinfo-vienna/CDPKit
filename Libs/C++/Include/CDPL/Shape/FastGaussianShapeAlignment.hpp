/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * FastGaussianShapeAlignment.hpp 
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
 * \brief Definition of the class CDPL::Shape::FastGaussianShapeAlignment.
 */

#ifndef CDPL_SHAPE_FASTGAUSSIANSHAPEALIGNMENT_HPP
#define CDPL_SHAPE_FASTGAUSSIANSHAPEALIGNMENT_HPP

#include <vector>
#include <cstddef>
#include <utility>

#include <boost/shared_ptr.hpp>
#include <boost/function.hpp>
#include <boost/unordered_map.hpp>
#include <boost/random/mersenne_twister.hpp>

#include "CDPL/Shape/APIPrefix.hpp"
#include "CDPL/Shape/GaussianShapeSet.hpp"
#include "CDPL/Shape/AlignmentResult.hpp"
#include "CDPL/Shape/AlignmentResultSelectionMode.hpp"
#include "CDPL/Shape/QuaternionTransformation.hpp"
#include "CDPL/Math/Matrix.hpp"
#include "CDPL/Math/VectorArray.hpp"
#include "CDPL/Math/QuaternionExpression.hpp"
#include "CDPL/Math/BFGSMinimizer.hpp"


namespace CDPL 
{

    namespace Shape
    {
		
		class CDPL_SHAPE_API FastGaussianShapeAlignment
		{

			typedef std::vector<AlignmentResult> ResultList;

		  public:
			static const double       DEF_OPTIMIZATION_STOP_GRADIENT;
			static const std::size_t  DEF_MAX_OPTIMIZATION_ITERATIONS = 20;
			static const unsigned int DEF_RESULT_SELECTION_MODE       = AlignmentResultSelectionMode::BEST_PER_REFERENCE_SET;
			static const double       DEF_SYMMETRY_THRESHOLD;
			static const std::size_t  DEF_NUM_RANDOM_STARTS           = 4;
			static const double       DEF_MAX_RANDOM_TRANSLATION;

			typedef boost::shared_ptr<FastGaussianShapeAlignment> SharedPointer;

			typedef ResultList::const_iterator ConstResultIterator;
			typedef ResultList::iterator ResultIterator;
		
			typedef boost::function1<double, const AlignmentResult&> ScoringFunction;
			typedef boost::function2<bool, const AlignmentResult&, const AlignmentResult&> ResultCompareFunction;

			FastGaussianShapeAlignment();

			FastGaussianShapeAlignment(const GaussianShape& ref_shape);

			FastGaussianShapeAlignment(const GaussianShapeSet& ref_shapes);

			~FastGaussianShapeAlignment();
			
			void setResultCompareFunction(const ResultCompareFunction& func);

			const ResultCompareFunction& getResultCompareFunction() const;

			void setScoringFunction(const ScoringFunction& func);

			const ScoringFunction& getScoringFunction() const;

			void setResultSelectionMode(unsigned int mode);

			unsigned int getResultSelectionMode() const;

			void performAlignment(bool perf_align);

			bool performAlignment() const;

			void optimizeOverlap(bool optimize);

			bool optimizeOverlap() const;

			void greedyOptimization(bool greedy);

			bool greedyOptimization() const;

			void setMaxNumOptimizationIterations(std::size_t max_iter);

			std::size_t getMaxNumOptimizationIterations() const;

			void setOptimizationStopGradient(double grad_norm);

			double getOptimizationStopGradient() const;

			void clearReferenceShapes();

			void addReferenceShape(const GaussianShape& shape, bool new_set = true);

			void addReferenceShapes(const GaussianShapeSet& shapes, bool new_set = true);

			std::size_t getNumReferenceShapes() const;

			void genShapeCenterStarts(bool generate);

			bool genShapeCenterStarts() const;
			
			void genColorCenterStarts(bool generate);

			bool genColorCenterStarts() const;

			void genNonColorCenterStarts(bool generate);

			bool genNonColorCenterStarts() const;
			
			void genRandomStarts(bool generate);

			bool genRandomStarts() const;

			void genForAlignedShapeCenters(bool generate);

			bool genForAlignedShapeCenters() const;

			void genForReferenceShapeCenters(bool generate);

			bool genForReferenceShapeCenters() const;

			void genForLargerShapeCenters(bool generate);

			bool genForLargerShapeCenters() const;
			
			void setSymmetryThreshold(double thresh);

			double getSymmetryThreshold();

			void setMaxRandomTranslation(double max_trans);

			double getMaxRandomTranslation() const;

			void setNumRandomStarts(std::size_t num_starts);

			std::size_t getNumRandomStarts() const;

			void setRandomSeed(unsigned int seed);

			bool align(const GaussianShape& shape);

			bool align(const GaussianShapeSet& shapes);

			std::size_t getNumResults() const;

			const AlignmentResult& getResult(std::size_t idx) const;

			AlignmentResult& getResult(std::size_t idx);

			ConstResultIterator getResultsBegin() const;

			ConstResultIterator getResultsEnd() const;

			ResultIterator getResultsBegin();

			ResultIterator getResultsEnd();
						
		  private:
			struct ShapeData
			{

				struct Element
				{

					std::size_t    color;
					Math::Vector3D center;
					double         radius;
					double         delta;
					double         weightFactor;
					double         volume;				
				};

				typedef std::vector<Element> ElementArray;

				ElementArray     elements;
				std::size_t      colElemOffs;
				std::size_t      setIndex;
				std::size_t      index;
				unsigned int     symClass;
				Math::Matrix4D   transform;
				double           selfOverlap;
				double           colSelfOverlap;
				bool             equalNonColDelta;
			};

			typedef std::pair<std::size_t, std::size_t> ResultID;
	
			FastGaussianShapeAlignment(const FastGaussianShapeAlignment& alignment);

			FastGaussianShapeAlignment& operator=(const FastGaussianShapeAlignment& alignment);

			void alignAndProcessResults(std::size_t ref_idx, std::size_t al_idx);
			void processResult(AlignmentResult& res, std::size_t ref_idx, std::size_t al_idx);

			void setupShapeData(const GaussianShape& shape, ShapeData& data, bool ref);
			void setupShapeDataElement(const GaussianShape::Element& gs_elem, ShapeData::Element& sd_elem) const;

			void prepareForAlignment();

			bool generateStartTransforms(const ShapeData& ref_data);

			void generateTransformsForElementCenters(const ShapeData& data, unsigned int axes_swap_flags, bool ref_shape);
			void generateTransforms(const Math::Vector3D& ctr_trans, unsigned int axes_swap_flags);

			template <typename QE>
			void addStartTransform(Math::Vector3D::ConstPointer ctr_trans_data, const Math::QuaternionExpression<QE>& rot_quat);

			void transformAlignedShape();

			double calcAlignmentFunctionValue(const QuaternionTransformation& xform_quat);
			double calcAlignmentFunctionGradient(const QuaternionTransformation& xform_quat, QuaternionTransformation& xform_grad);

			double calcOverlap(const ShapeData& ref_data, const ShapeData& ovl_data, bool color) const;
			double calcOverlapGradient(const ShapeData& ref_data, Math::Vector3DArray& grad) const;

			bool getResultIndex(const ResultID& res_id, std::size_t& res_idx);

			typedef std::vector<ShapeData> ShapeDataArray;
			typedef boost::unordered_map<ResultID, std::size_t> ResultIndexMap;
			typedef std::vector<QuaternionTransformation> StartTransformList;
			typedef boost::random::mt11213b RandomEngine;
			typedef Math::BFGSMinimizer<QuaternionTransformation> BFGSMinimizer;

			bool                           perfAlignment;
			bool                           optOverlap;
			bool                           greedyOpt;
			std::size_t                    maxNumOptIters;
			double                         optStopGrad;
			unsigned int                   resultSelMode;
			ResultCompareFunction          resultCmpFunc;
			ScoringFunction                scoringFunc;
			ShapeDataArray                 refShapeData;
			ShapeData                      algdShapeData;
			ResultIndexMap                 resIndexMap;
			ResultList                     results;
			std::size_t                    currSetIndex;
			std::size_t                    currShapeIndex;
			bool                           shapeCtrStarts;
			bool                           colCtrStarts;
			bool                           nonColCtrStarts;
			bool                           randomStarts;
			bool                           genForAlgdShape;
			bool                           genForRefShape;
			bool                           genForLargerShape;
			double                         symThreshold;
			double                         maxRandomTrans;
			std::size_t                    numRandomStarts;
			std::size_t                    numSubTransforms;
			RandomEngine                   randomEngine;
			StartTransformList             startTransforms;
			Math::Vector3DArray            startPoseCoords;
			Math::Vector3DArray            optPoseCoordsGrad;
			BFGSMinimizer                  minimizer;
			Math::Matrix4D                 xformMatrix;
			QuaternionTransformation       normXformQuat;
			std::size_t                    currRefShapeIdx;
		};
    }
}

#endif // CDPL_SHAPE_FASTGAUSSIANSHAPEALIGNMENT_HPP
