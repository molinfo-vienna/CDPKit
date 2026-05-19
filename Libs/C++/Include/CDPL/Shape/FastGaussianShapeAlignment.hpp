/* 
 * FastGaussianShapeAlignment.hpp 
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
 * \brief Definition of class CDPL::Shape::FastGaussianShapeAlignment.
 */

#ifndef CDPL_SHAPE_FASTGAUSSIANSHAPEALIGNMENT_HPP
#define CDPL_SHAPE_FASTGAUSSIANSHAPEALIGNMENT_HPP

#include <vector>
#include <cstddef>
#include <utility>
#include <unordered_map>
#include <memory>
#include <functional>

#include <boost/functional/hash.hpp>
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

        /**
         * \brief High-level driver for the fast alignment of Gaussian shapes against a set of reference shapes.
         *
         * Unlike Shape::GaussianShapeAlignment, which delegates the alignment to a separate
         * Shape::GaussianShapeFunctionAlignment instance, \c %FastGaussianShapeAlignment integrates
         * the entire pipeline (start-transform generation, BFGS overlap optimization, result selection)
         * into one class and operates on a self-contained Gaussian-product representation. The
         * configuration combines settings exposed by Shape::PrincipalAxesAlignmentStartGenerator
         * (start-transform options) and the iterative overlap optimization.
         */
        class CDPL_SHAPE_API FastGaussianShapeAlignment
        {

            typedef std::vector<AlignmentResult> ResultList;

          public:
            /** \brief Default gradient norm at which the overlap optimization is stopped. */
            static constexpr double DEF_OPTIMIZATION_STOP_GRADIENT        = 1.0;
            /** \brief Default maximum number of overlap-optimization iterations. */
            static constexpr std::size_t  DEF_MAX_OPTIMIZATION_ITERATIONS = 20;
            /** \brief Default alignment-result selection mode. */
            static constexpr unsigned int DEF_RESULT_SELECTION_MODE       = AlignmentResultSelectionMode::BEST_PER_REFERENCE_SET;
            /** \brief Default relative threshold for treating two principal moments as equal. */
            static constexpr double       DEF_SYMMETRY_THRESHOLD          = 0.15;
            /** \brief Default number of random starting transformations. */
            static constexpr std::size_t DEF_NUM_RANDOM_STARTS            = 4;
            /** \brief Default maximum random translation magnitude applied to random starts. */
            static constexpr double      DEF_MAX_RANDOM_TRANSLATION       = 2.0;

            /** \brief A reference-counted smart pointer [\ref SHPTR] for dynamically allocated \c %FastGaussianShapeAlignment instances. */
            typedef std::shared_ptr<FastGaussianShapeAlignment> SharedPointer;

            /** \brief A constant iterator over the alignment results. */
            typedef ResultList::const_iterator ConstResultIterator;
            /** \brief A mutable iterator over the alignment results. */
            typedef ResultList::iterator       ResultIterator;

            /** \brief Type of the function used to score an alignment result. */
            typedef std::function<double(const AlignmentResult&)>                       ScoringFunction;
            /** \brief Type of the function used to compare two alignment results. */
            typedef std::function<bool(const AlignmentResult&, const AlignmentResult&)> ResultCompareFunction;

            /**
             * \brief Constructs the \c %FastGaussianShapeAlignment instance.
             */
            FastGaussianShapeAlignment();

            /**
             * \brief Constructs the \c %FastGaussianShapeAlignment instance with \a ref_shape as the single reference shape.
             * \param ref_shape The reference shape.
             */
            FastGaussianShapeAlignment(const GaussianShape& ref_shape);

            /**
             * \brief Constructs the \c %FastGaussianShapeAlignment instance with the shapes in \a ref_shapes as the reference set.
             * \param ref_shapes The reference shapes.
             */
            FastGaussianShapeAlignment(const GaussianShapeSet& ref_shapes);

            FastGaussianShapeAlignment(const FastGaussianShapeAlignment& alignment) = delete;

            /**
             * \brief Destructor.
             */
            ~FastGaussianShapeAlignment();

            FastGaussianShapeAlignment& operator=(const FastGaussianShapeAlignment& alignment) = delete;

            /**
             * \brief Specifies the function used to compare two alignment results for sorting and filtering.
             * \param func The result-compare function.
             */
            void setResultCompareFunction(const ResultCompareFunction& func);

            /**
             * \brief Returns the currently configured result-compare function.
             * \return A \c const reference to the result-compare function.
             */
            const ResultCompareFunction& getResultCompareFunction() const;

            /**
             * \brief Specifies the function used to score an alignment result.
             * \param func The scoring function.
             */
            void setScoringFunction(const ScoringFunction& func);

            /**
             * \brief Returns the currently configured scoring function.
             * \return A \c const reference to the scoring function.
             */
            const ScoringFunction& getScoringFunction() const;

            /**
             * \brief Sets the alignment-result selection mode (see namespace Shape::AlignmentResultSelectionMode).
             * \param mode The new result-selection mode.
             */
            void setResultSelectionMode(unsigned int mode);

            /**
             * \brief Returns the currently configured alignment-result selection mode.
             * \return The result-selection mode (see namespace Shape::AlignmentResultSelectionMode).
             */
            unsigned int getResultSelectionMode() const;

            /**
             * \brief Specifies whether the actual alignment shall be performed (vs. only evaluating overlaps in the initial pose).
             * \param perf_align \c true to perform the alignment, and \c false to only evaluate the initial pose.
             */
            void performAlignment(bool perf_align);

            /**
             * \brief Tells whether the actual alignment is performed.
             * \return \c true if the alignment is performed, and \c false otherwise.
             */
            bool performAlignment() const;

            /**
             * \brief Specifies whether the overlap shall be optimized iteratively after the initial alignment.
             * \param optimize \c true to optimize the overlap, and \c false to skip optimization.
             */
            void optimizeOverlap(bool optimize);

            /**
             * \brief Tells whether the overlap is optimized iteratively.
             * \return \c true if the overlap is optimized, and \c false otherwise.
             */
            bool optimizeOverlap() const;

            /**
             * \brief Specifies whether the overlap optimization shall use a greedy strategy that stops at the first local maximum.
             * \param greedy \c true to use the greedy strategy, and \c false to use the full optimization.
             */
            void greedyOptimization(bool greedy);

            /**
             * \brief Tells whether the overlap optimization uses a greedy strategy.
             * \return \c true if the greedy strategy is used, and \c false otherwise.
             */
            bool greedyOptimization() const;

            /**
             * \brief Sets the maximum number of overlap-optimization iterations.
             * \param max_iter The new maximum number of iterations.
             */
            void setMaxNumOptimizationIterations(std::size_t max_iter);

            /**
             * \brief Returns the currently configured maximum number of overlap-optimization iterations.
             * \return The maximum number of iterations.
             */
            std::size_t getMaxNumOptimizationIterations() const;

            /**
             * \brief Sets the gradient norm at which the overlap optimization is stopped.
             * \param grad_norm The new stop gradient norm.
             */
            void setOptimizationStopGradient(double grad_norm);

            /**
             * \brief Returns the currently configured overlap-optimization stop gradient.
             * \return The stop gradient norm.
             */
            double getOptimizationStopGradient() const;

            /**
             * \brief Removes all reference shapes and reference shape sets.
             */
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

            /**
             * \brief Returns the total number of reference shapes.
             * \return The number of reference shapes.
             */
            std::size_t getNumReferenceShapes() const;

            /**
             * \brief Enables or disables the generation of a starting transformation at the shape centroid.
             * \param generate \c true to enable the shape-centroid start, and \c false to disable it.
             */
            void genShapeCenterStarts(bool generate);

            /**
             * \brief Tells whether a starting transformation at the shape centroid is generated.
             * \return \c true if a shape-centroid start is generated, and \c false otherwise.
             */
            bool genShapeCenterStarts() const;

            /**
             * \brief Enables or disables the generation of starting transformations at color (pharmacophore) feature centers.
             * \param generate \c true to enable the color-center starts, and \c false to disable them.
             */
            void genColorCenterStarts(bool generate);

            /**
             * \brief Tells whether starting transformations at color (pharmacophore) feature centers are generated.
             * \return \c true if color-center starts are generated, and \c false otherwise.
             */
            bool genColorCenterStarts() const;

            /**
             * \brief Enables or disables the generation of starting transformations at non-color (shape) element centers.
             * \param generate \c true to enable the non-color-center starts, and \c false to disable them.
             */
            void genNonColorCenterStarts(bool generate);

            /**
             * \brief Tells whether starting transformations at non-color (shape) element centers are generated.
             * \return \c true if non-color-center starts are generated, and \c false otherwise.
             */
            bool genNonColorCenterStarts() const;

            /**
             * \brief Enables or disables the generation of random starting transformations.
             * \param generate \c true to enable the random starts, and \c false to disable them.
             */
            void genRandomStarts(bool generate);

            /**
             * \brief Tells whether random starting transformations are generated.
             * \return \c true if random starts are generated, and \c false otherwise.
             */
            bool genRandomStarts() const;

            /**
             * \brief Specifies whether element-/color-center starts shall be generated for centers of the aligned shape.
             * \param generate \c true to consider aligned-shape centers, and \c false to ignore them.
             */
            void genForAlignedShapeCenters(bool generate);

            /**
             * \brief Tells whether element-/color-center starts are generated for centers of the aligned shape.
             * \return \c true if aligned-shape centers are considered, and \c false otherwise.
             */
            bool genForAlignedShapeCenters() const;

            /**
             * \brief Specifies whether element-/color-center starts shall be generated for centers of the reference shape.
             * \param generate \c true to consider reference-shape centers, and \c false to ignore them.
             */
            void genForReferenceShapeCenters(bool generate);

            /**
             * \brief Tells whether element-/color-center starts are generated for centers of the reference shape.
             * \return \c true if reference-shape centers are considered, and \c false otherwise.
             */
            bool genForReferenceShapeCenters() const;

            /**
             * \brief Specifies whether element-/color-center starts shall be generated for centers of the shape with more elements (instead of both shapes).
             * \param generate \c true to use only the centers of the larger shape, and \c false to use the centers of all configured shapes.
             */
            void genForLargerShapeCenters(bool generate);

            /**
             * \brief Tells whether element-/color-center starts are generated for centers of the shape with more elements (instead of both shapes).
             * \return \c true if only the centers of the larger shape are used, and \c false otherwise.
             */
            bool genForLargerShapeCenters() const;

            /**
             * \brief Sets the relative threshold for treating two principal moments as equal.
             * \param thresh The new symmetry threshold.
             */
            void setSymmetryThreshold(double thresh);

            /**
             * \brief Returns the currently configured symmetry threshold.
             * \return The symmetry threshold.
             */
            double getSymmetryThreshold();

            /**
             * \brief Sets the maximum random translation magnitude applied to random starts.
             * \param max_trans The new maximum random translation magnitude.
             */
            void setMaxRandomTranslation(double max_trans);

            /**
             * \brief Returns the currently configured maximum random translation.
             * \return The maximum random translation magnitude.
             */
            double getMaxRandomTranslation() const;

            /**
             * \brief Sets the number of random starting transformations.
             * \param num_starts The new number of random starts.
             */
            void setNumRandomStarts(std::size_t num_starts);

            /**
             * \brief Returns the currently configured number of random starts.
             * \return The number of random starts.
             */
            std::size_t getNumRandomStarts() const;

            /**
             * \brief Sets the seed used by the random number generator that produces the random starts.
             * \param seed The new random seed.
             */
            void setRandomSeed(unsigned int seed);

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

            /**
             * \brief Returns the number of stored alignment results.
             * \return The number of alignment results.
             */
            std::size_t getNumResults() const;

            /**
             * \brief Returns the alignment result at index \a idx.
             * \param idx The zero-based result index.
             * \return A \c const reference to the result.
             * \throw Base::IndexError if the number of results is zero or \a idx is not in the range [0, getNumResults() - 1].
             */
            const AlignmentResult& getResult(std::size_t idx) const;

            /**
             * \brief Returns the alignment result at index \a idx.
             * \param idx The zero-based result index.
             * \return A reference to the result.
             * \throw Base::IndexError if the number of results is zero or \a idx is not in the range [0, getNumResults() - 1].
             */
            AlignmentResult& getResult(std::size_t idx);

            /**
             * \brief Returns a constant iterator pointing to the first alignment result.
             * \return A constant iterator pointing to the first alignment result.
             */
            ConstResultIterator getResultsBegin() const;

            /**
             * \brief Returns a constant iterator pointing one past the last alignment result.
             * \return A constant iterator pointing one past the last alignment result.
             */
            ConstResultIterator getResultsEnd() const;

            /**
             * \brief Returns a mutable iterator pointing to the first alignment result.
             * \return A mutable iterator pointing to the first alignment result.
             */
            ResultIterator getResultsBegin();

            /**
             * \brief Returns a mutable iterator pointing one past the last alignment result.
             * \return A mutable iterator pointing one past the last alignment result.
             */
            ResultIterator getResultsEnd();

            /**
             * \brief Returns a constant iterator pointing to the first alignment result (range-based for support).
             * \return A constant iterator pointing to the first alignment result.
             */
            ConstResultIterator begin() const;

            /**
             * \brief Returns a constant iterator pointing one past the last alignment result (range-based for support).
             * \return A constant iterator pointing one past the last alignment result.
             */
            ConstResultIterator end() const;

            /**
             * \brief Returns a mutable iterator pointing to the first alignment result (range-based for support).
             * \return A mutable iterator pointing to the first alignment result.
             */
            ResultIterator begin();

            /**
             * \brief Returns a mutable iterator pointing one past the last alignment result (range-based for support).
             * \return A mutable iterator pointing one past the last alignment result.
             */
            ResultIterator end();

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

                ElementArray   elements;
                std::size_t    colElemOffs;
                std::size_t    setIndex;
                std::size_t    index;
                unsigned int   symClass;
                Math::Matrix4D transform;
                double         selfOverlap;
                double         colSelfOverlap;
                bool           equalNonColDelta;
            };

            typedef std::pair<std::size_t, std::size_t> ResultID;

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

            typedef std::vector<ShapeData>                                            ShapeDataArray;
            typedef std::unordered_map<ResultID, std::size_t, boost::hash<ResultID> > ResultIndexMap;
            typedef std::vector<QuaternionTransformation>                             StartTransformList;
            typedef boost::random::mt11213b                                           RandomEngine;
            typedef Math::BFGSMinimizer<QuaternionTransformation>                     BFGSMinimizer;

            bool                     perfAlignment;
            bool                     optOverlap;
            bool                     greedyOpt;
            std::size_t              maxNumOptIters;
            double                   optStopGrad;
            unsigned int             resultSelMode;
            ResultCompareFunction    resultCmpFunc;
            ScoringFunction          scoringFunc;
            ShapeDataArray           refShapeData;
            ShapeData                algdShapeData;
            ResultIndexMap           resIndexMap;
            ResultList               results;
            std::size_t              currSetIndex;
            std::size_t              currShapeIndex;
            bool                     shapeCtrStarts;
            bool                     colCtrStarts;
            bool                     nonColCtrStarts;
            bool                     randomStarts;
            bool                     genForAlgdShape;
            bool                     genForRefShape;
            bool                     genForLargerShape;
            double                   symThreshold;
            double                   maxRandomTrans;
            std::size_t              numRandomStarts;
            std::size_t              numSubTransforms;
            RandomEngine             randomEngine;
            StartTransformList       startTransforms;
            Math::Vector3DArray      startPoseCoords;
            Math::Vector3DArray      optPoseCoordsGrad;
            BFGSMinimizer            minimizer;
            Math::Matrix4D           xformMatrix;
            QuaternionTransformation normXformQuat;
            std::size_t              currRefShapeIdx;
        };
    } // namespace Shape
} // namespace CDPL

#endif // CDPL_SHAPE_FASTGAUSSIANSHAPEALIGNMENT_HPP
