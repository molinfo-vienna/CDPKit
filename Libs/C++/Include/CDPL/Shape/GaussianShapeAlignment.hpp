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
 * \brief Definition of class CDPL::Shape::GaussianShapeAlignment.
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

        /**
         * \brief High-level driver for the alignment of Gaussian shapes against a set of reference shapes.
         *
         * The class manages a list of reference Gaussian shapes (organised into reference sets), runs
         * the underlying Shape::GaussianShapeFunctionAlignment for each (reference, aligned) pair, and
         * collects the Shape::AlignmentResult instances filtered according to the configured selection
         * mode and comparator/scoring functions.
         */
        class CDPL_SHAPE_API GaussianShapeAlignment
        {

            typedef std::vector<AlignmentResult>        ResultList;
            typedef std::vector<GaussianShapeFunction*> ShapeFunctionList;

            typedef const GaussianShape& (*GetShapeFunction)(const GaussianShapeFunction*);

          public:
            /** \brief Default gradient norm at which the overlap optimization is stopped. */
            static constexpr double DEF_OPTIMIZATION_STOP_GRADIENT       = 1.0;
            /** \brief Default maximum number of overlap-optimization iterations. */
            static constexpr std::size_t DEF_MAX_OPTIMIZATION_ITERATIONS = 20;
            /** \brief Default maximum order of the Gaussian-product expansion. */
            static constexpr std::size_t  DEF_MAX_PRODUCT_ORDER          = 1;
            /** \brief Default alignment-result selection mode. */
            static constexpr unsigned int DEF_RESULT_SELECTION_MODE      = AlignmentResultSelectionMode::BEST_PER_REFERENCE_SET;
            /** \brief Default distance cutoff for pruning negligible overlap contributions. */
            static constexpr double       DEF_DISTANCE_CUTOFF            = 0.0;

            /** \brief A reference-counted smart pointer [\ref SHPTR] for dynamically allocated \c %GaussianShapeAlignment instances. */
            typedef std::shared_ptr<GaussianShapeAlignment> SharedPointer;

            /** \brief A constant iterator over the alignment results. */
            typedef ResultList::const_iterator                                                     ConstResultIterator;
            /** \brief A mutable iterator over the alignment results. */
            typedef ResultList::iterator                                                           ResultIterator;
            /** \brief A constant iterator over the reference shapes. */
            typedef boost::transform_iterator<GetShapeFunction, ShapeFunctionList::const_iterator> ConstShapeIterator;

            /** \brief Type of the function used to filter color (pharmacophore) features by type. */
            typedef GaussianShapeFunctionAlignment::ColorFilterFunction                 ColorFilterFunction;
            /** \brief Type of the function used to decide whether two color features match. */
            typedef GaussianShapeFunctionAlignment::ColorMatchFunction                  ColorMatchFunction;
            /** \brief Type of the function used to score an alignment result. */
            typedef std::function<double(const AlignmentResult&)>                       ScoringFunction;
            /** \brief Type of the function used to compare two alignment results. */
            typedef std::function<bool(const AlignmentResult&, const AlignmentResult&)> ResultCompareFunction;

            /** \brief Constructs the \c %GaussianShapeAlignment instance. */
            GaussianShapeAlignment();

            /** \brief Constructs the \c %GaussianShapeAlignment instance with \a ref_shape as the single reference shape. */
            GaussianShapeAlignment(const GaussianShape& ref_shape);

            /** \brief Constructs the \c %GaussianShapeAlignment instance with the shapes in \a ref_shapes as the reference set. */
            GaussianShapeAlignment(const GaussianShapeSet& ref_shapes);

            GaussianShapeAlignment(const GaussianShapeAlignment& alignment) = delete;

            /** \brief Destructor. */
            ~GaussianShapeAlignment();

            GaussianShapeAlignment& operator=(const GaussianShapeAlignment& alignment) = delete;

            /** \brief Specifies the Gaussian-shape overlap function used during alignment. */
            void setOverlapFunction(GaussianShapeOverlapFunction& func);

            /** \brief Returns the currently configured overlap function. */
            GaussianShapeOverlapFunction& getOverlapFunction() const;

            /** \brief Returns the built-in default overlap function. */
            const FastGaussianShapeOverlapFunction& getDefaultOverlapFunction() const;

            /** \brief Returns the built-in default overlap function. */
            FastGaussianShapeOverlapFunction& getDefaultOverlapFunction();

            /** \brief Specifies the alignment-start generator used to seed the overlap optimization. */
            void setStartGenerator(GaussianShapeAlignmentStartGenerator& gen);

            /** \brief Returns the currently configured alignment-start generator. */
            GaussianShapeAlignmentStartGenerator& getStartGenerator() const;

            /** \brief Returns the built-in principal-axes alignment-start generator. */
            const PrincipalAxesAlignmentStartGenerator& getDefaultStartGenerator() const;

            /** \brief Returns the built-in principal-axes alignment-start generator. */
            PrincipalAxesAlignmentStartGenerator& getDefaultStartGenerator();

            /** \brief Specifies the function used to decide whether two color features match. */
            void setColorMatchFunction(const ColorMatchFunction& func);

            /** \brief Returns the currently configured color-match function. */
            const ColorMatchFunction& getColorMatchFunction() const;

            /** \brief Specifies the function used to filter color features by type. */
            void setColorFilterFunction(const ColorFilterFunction& func);

            /** \brief Returns the currently configured color-filter function. */
            const ColorFilterFunction& getColorFilterFunction() const;

            /** \brief Specifies the function used to compare two alignment results for sorting and filtering. */
            void setResultCompareFunction(const ResultCompareFunction& func);

            /** \brief Returns the currently configured result-compare function. */
            const ResultCompareFunction& getResultCompareFunction() const;

            /** \brief Specifies the function used to score an alignment result. */
            void setScoringFunction(const ScoringFunction& func);

            /** \brief Returns the currently configured scoring function. */
            const ScoringFunction& getScoringFunction() const;

            /** \brief Sets the alignment-result selection mode (see namespace Shape::AlignmentResultSelectionMode). */
            void setResultSelectionMode(unsigned int mode);

            /** \brief Returns the currently configured alignment-result selection mode. */
            unsigned int getResultSelectionMode() const;

            /** \brief Specifies whether shape self-overlaps shall be computed for the involved shapes. */
            void calcSelfOverlaps(bool calc);

            /** \brief Tells whether shape self-overlaps are computed for the involved shapes. */
            bool calcSelfOverlaps() const;

            /** \brief Specifies whether color self-overlaps shall be computed for the involved shapes. */
            void calcColorSelfOverlaps(bool calc);

            /** \brief Tells whether color self-overlaps are computed for the involved shapes. */
            bool calcColorSelfOverlaps() const;

            /** \brief Specifies whether color overlaps shall be computed in addition to shape overlaps. */
            void calcColorOverlaps(bool calc);

            /** \brief Tells whether color overlaps are computed in addition to shape overlaps. */
            bool calcColorOverlaps() const;

            /** \brief Specifies whether the actual alignment shall be performed (vs. only computing overlaps in the initial pose). */
            void performAlignment(bool perf_align);

            /** \brief Tells whether the actual alignment is performed. */
            bool performAlignment() const;

            /** \brief Specifies whether the overlap shall be optimized iteratively after the initial alignment. */
            void optimizeOverlap(bool optimize);

            /** \brief Tells whether the overlap is optimized iteratively. */
            bool optimizeOverlap() const;

            /** \brief Specifies whether the overlap optimization shall use a greedy strategy that stops at the first local maximum. */
            void greedyOptimization(bool greedy);

            /** \brief Tells whether the overlap optimization uses a greedy strategy. */
            bool greedyOptimization() const;

            /** \brief Sets the maximum number of overlap-optimization iterations. */
            void setMaxNumOptimizationIterations(std::size_t max_iter);

            /** \brief Returns the currently configured maximum number of overlap-optimization iterations. */
            std::size_t getMaxNumOptimizationIterations() const;

            /** \brief Sets the gradient norm at which the overlap optimization is stopped. */
            void setOptimizationStopGradient(double grad_norm);

            /** \brief Returns the currently configured overlap-optimization stop gradient. */
            double getOptimizationStopGradient() const;

            /** \brief Sets the maximum order of the Gaussian-product expansion used by the overlap function. */
            void setMaxOrder(std::size_t max_order);

            /** \brief Returns the currently configured maximum order of the Gaussian-product expansion. */
            std::size_t getMaxOrder() const;

            /** \brief Sets the distance cutoff for pruning negligible overlap contributions. */
            void setDistanceCutoff(double cutoff);

            /** \brief Returns the currently configured distance cutoff. */
            double getDistanceCutoff() const;

            /** \brief Removes all reference shapes and reference shape sets. */
            void clearReferenceShapes();

            /**
             * \brief Adds \a shape to the reference shapes.
             * \param shape The reference shape.
             * \param new_set If \c true, \a shape is added to a new reference set; otherwise it is appended to the most recent reference set.
             */
            void addReferenceShape(const GaussianShape& shape, bool new_set = true);

            /**
             * \brief Adds the shapes in \a shapes to the reference shapes.
             * \param shapes The reference shapes.
             * \param new_set If \c true, the shapes are added to a new reference set; otherwise they are appended to the most recent reference set.
             */
            void addReferenceShapes(const GaussianShapeSet& shapes, bool new_set = true);

            /** \brief Returns the total number of reference shapes. */
            std::size_t getNumReferenceShapes() const;

            /** \brief Returns the reference shape at index \a idx. */
            const GaussianShape& getReferenceShape(std::size_t idx) const;

            /** \brief Returns a constant iterator pointing to the first reference shape. */
            ConstShapeIterator getReferenceShapesBegin() const;

            /** \brief Returns a constant iterator pointing one past the last reference shape. */
            ConstShapeIterator getReferenceShapesEnd() const;

            /**
             * \brief Aligns \a shape against all reference shapes.
             * \param shape The shape to align.
             * \return \c true if at least one alignment result was produced, and \c false otherwise.
             */
            bool align(const GaussianShape& shape);

            /**
             * \brief Aligns each shape in \a shapes against all reference shapes.
             * \param shapes The shapes to align.
             * \return \c true if at least one alignment result was produced, and \c false otherwise.
             */
            bool align(const GaussianShapeSet& shapes);

            /** \brief Returns the number of stored alignment results. */
            std::size_t getNumResults() const;

            /** \brief Returns the alignment result at index \a idx. */
            const AlignmentResult& getResult(std::size_t idx) const;

            /** \brief Returns the alignment result at index \a idx. */
            AlignmentResult& getResult(std::size_t idx);

            /** \brief Returns a constant iterator pointing to the first alignment result. */
            ConstResultIterator getResultsBegin() const;

            /** \brief Returns a constant iterator pointing one past the last alignment result. */
            ConstResultIterator getResultsEnd() const;

            /** \brief Returns a mutable iterator pointing to the first alignment result. */
            ResultIterator getResultsBegin();

            /** \brief Returns a mutable iterator pointing one past the last alignment result. */
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

            void prepareForAlignment(GaussianShapeFunction& func, ShapeMetaData& data, bool ref);

            void processResults(std::size_t ref_idx, std::size_t al_idx);

            bool getResultIndex(const ResultID& res_id, std::size_t& res_idx);

            GaussianShapeFunction* allocShapeFunction(const GaussianShape& shape);

            typedef Util::ObjectStack<GaussianShapeFunction>                          ShapeFunctionCache;
            typedef std::vector<ShapeMetaData>                                        ShapeMetaDataArray;
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
    } // namespace Shape
} // namespace CDPL

#endif // CDPL_SHAPE_GAUSSIANSHAPEALIGNMENT_HPP
