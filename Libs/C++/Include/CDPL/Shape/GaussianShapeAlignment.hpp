/* 
 * GaussianShapeAlignment.hpp 
 *
 * This file is part of the Chemical Data Processing Toolkit
 *
 * Copyright (C) 2003 Thomas Seidel <thomas.seidel@univie.ac.at>
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
#include <utility>
#include <unordered_map>
#include <memory>
#include <functional>

#include <boost/functional/hash.hpp>
#include <boost/iterator/transform_iterator.hpp>

#include "CDPL/Shape/APIPrefix.hpp"
#include "CDPL/Shape/GaussianShapeFunctionAlignment.hpp"
#include "CDPL/Shape/GaussianShapeFunction.hpp"
#include "CDPL/Shape/GaussianShapeSet.hpp"
#include "CDPL/Shape/AlignmentResult.hpp"
#include "CDPL/Shape/AlignmentResultSelectionMode.hpp"
#include "CDPL/Math/Matrix.hpp"
#include "CDPL/Util/ObjectStack.hpp"


namespace CDPL 
{

    namespace Shape
    {
        
        class CDPL_SHAPE_API GaussianShapeAlignment
        {

            typedef std::vector<AlignmentResult> ResultList;
            typedef std::vector<GaussianShapeFunction*> ShapeFunctionList;

            typedef const GaussianShape& (*GetShapeFunction)(const GaussianShapeFunction*);

          public:
            static constexpr double       DEF_OPTIMIZATION_STOP_GRADIENT  = 1.0;
            static constexpr std::size_t  DEF_MAX_OPTIMIZATION_ITERATIONS = 20;
            static constexpr std::size_t  DEF_MAX_PRODUCT_ORDER           = 1;
            static constexpr unsigned int DEF_RESULT_SELECTION_MODE       = AlignmentResultSelectionMode::BEST_PER_REFERENCE_SET;
            static constexpr double       DEF_DISTANCE_CUTOFF             = 0.0;

            typedef std::shared_ptr<GaussianShapeAlignment> SharedPointer;

            typedef ResultList::const_iterator ConstResultIterator;
            typedef ResultList::iterator ResultIterator;
            typedef boost::transform_iterator<GetShapeFunction, ShapeFunctionList::const_iterator> ConstShapeIterator;

            typedef GaussianShapeFunctionAlignment::ColorFilterFunction ColorFilterFunction;
            typedef GaussianShapeFunctionAlignment::ColorMatchFunction ColorMatchFunction;
            typedef std::function<double(const AlignmentResult&)> ScoringFunction;
            typedef std::function<bool(const AlignmentResult&, const AlignmentResult&)> ResultCompareFunction;

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

            void setScoringFunction(const ScoringFunction& func);

            const ScoringFunction& getScoringFunction() const;

            void setResultSelectionMode(unsigned int mode);

            unsigned int getResultSelectionMode() const;

            void calcSelfOverlaps(bool calc);

            bool calcSelfOverlaps() const;

            void calcColorSelfOverlaps(bool calc);

            bool calcColorSelfOverlaps() const;

            void calcColorOverlaps(bool calc);

            bool calcColorOverlaps() const;

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

            void setMaxOrder(std::size_t max_order);

            std::size_t getMaxOrder() const;

            void setDistanceCutoff(double cutoff);

            double getDistanceCutoff() const;

            void clearReferenceShapes();

            void addReferenceShape(const GaussianShape& shape, bool new_set = true);

            void addReferenceShapes(const GaussianShapeSet& shapes, bool new_set = true);

            std::size_t getNumReferenceShapes() const;

            const GaussianShape& getReferenceShape(std::size_t idx) const;
        
            ConstShapeIterator getReferenceShapesBegin() const;

            ConstShapeIterator getReferenceShapesEnd() const;

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
            typedef GaussianShape::SharedPointer GaussianShapePtr;

            struct ShapeMetaData 
            {

                std::size_t      setIndex;
                std::size_t      index;
                unsigned int     symClass;
                Math::Matrix4D   transform;
                double           selfOverlap;
                double           colSelfOverlap;
                GaussianShapePtr shape;
            };

            typedef std::pair<std::size_t, std::size_t> ResultID;
    
            GaussianShapeAlignment(const GaussianShapeAlignment& alignment);

            GaussianShapeAlignment& operator=(const GaussianShapeAlignment& alignment);

            void prepareForAlignment(GaussianShapeFunction& func, ShapeMetaData& data, bool ref);

            void processResults(std::size_t ref_idx, std::size_t al_idx);

            bool getResultIndex(const ResultID& res_id, std::size_t& res_idx);

            GaussianShapeFunction* allocShapeFunction(const GaussianShape& shape);

            typedef Util::ObjectStack<GaussianShapeFunction> ShapeFunctionCache;
            typedef std::vector<ShapeMetaData> ShapeMetaDataArray;
             typedef std::unordered_map<ResultID, std::size_t, boost::hash<ResultID> > ResultIndexMap;

            ShapeFunctionCache             shapeFuncCache;
            bool                           calcSlfOverlaps;
            bool                           calcColSlfOverlaps;
            unsigned int                   resultSelMode;
            ResultCompareFunction          resultCmpFunc;
            ScoringFunction                scoringFunc;
            GaussianShapeFunctionAlignment shapeFuncAlmnt;
            ShapeFunctionList              refShapeFuncs;
            ShapeMetaDataArray             refShapeMetaData;
            GaussianShapeFunction          algdShapeFunc;
            ShapeMetaData                  algdShapeMetaData;
            ResultIndexMap                 resIndexMap;
            ResultList                     results;
            std::size_t                    currSetIndex;
            std::size_t                    currShapeIndex;
        };
    }
}

#endif // CDPL_SHAPE_GAUSSIANSHAPEALIGNMENT_HPP
