/* 
 * GaussianShapeFunctionAlignment.hpp 
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
 * \brief Definition of class CDPL::Shape::GaussianShapeFunctionAlignment.
 */

#ifndef CDPL_SHAPE_GAUSSIANSHAPEFUNCTIONALIGNMENT_HPP
#define CDPL_SHAPE_GAUSSIANSHAPEFUNCTIONALIGNMENT_HPP

#include <cstddef>
#include <vector>
#include <memory>

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
         * \brief Driver for the alignment of one Shape::GaussianShapeFunction (the aligned shape)
         *        against a fixed reference Shape::GaussianShapeFunction.
         *
         * The alignment iterates over starting transformations produced by a configurable
         * Shape::GaussianShapeAlignmentStartGenerator, optionally refines each start via BFGS
         * minimization (Math::BFGSMinimizer) of the overlap function, and collects the resulting
         * transformations and overlap values in Result instances.
         *
         * \see Math::BFGSMinimizer
         */
        class CDPL_SHAPE_API GaussianShapeFunctionAlignment
        {

          public:
            class Result;

          private:
            typedef std::vector<Result> ResultList;

          public:
            /**
             * \brief Default gradient norm at which the overlap optimization is stopped.
             */
            static constexpr double DEF_OPTIMIZATION_STOP_GRADIENT       = 1.0;

            /**
             * \brief Default maximum number of overlap-optimization iterations.
             */
            static constexpr std::size_t DEF_MAX_OPTIMIZATION_ITERATIONS = 20;

            /**
             * \brief A reference-counted smart pointer [\ref SHPTR] for dynamically allocated \c %GaussianShapeFunctionAlignment instances.
             */
            typedef std::shared_ptr<GaussianShapeFunctionAlignment> SharedPointer;

            /**
             * \brief A constant iterator over the alignment results.
             */
            typedef ResultList::const_iterator ConstResultIterator;

            /**
             * \brief Type of the function used to filter color (pharmacophore) features by type.
             */
            typedef GaussianShapeOverlapFunction::ColorFilterFunction ColorFilterFunction;

            /**
             * \brief Type of the function used to decide whether two color features match.
             */
            typedef GaussianShapeOverlapFunction::ColorMatchFunction  ColorMatchFunction;

            /**
             * \brief A single alignment result: rigid-body transformation plus shape and color overlap values.
             */
            class Result
            {

              public:
                /**
                 * \brief Constructs a \c %Result with the given values.
                 * \param xform The rigid-body transformation.
                 * \param overlap The shape overlap value.
                 * \param col_overlap The color overlap value.
                 */
                Result(const Math::Matrix4D& xform, double overlap, double col_overlap):
                    transform(xform), overlap(overlap), colOverlap(col_overlap) {}

                /**
                 * \brief Returns the rigid-body transformation that maps the aligned shape onto the reference shape.
                 * \return A \c const reference to the rigid-body transformation matrix.
                 */
                const Math::Matrix4D& getTransform() const
                {
                    return transform;
                }

                /**
                 * \brief Returns the shape overlap value of the alignment.
                 * \return The shape overlap value.
                 */
                double getOverlap() const
                {
                    return overlap;
                }

                /**
                 * \brief Returns the color overlap value of the alignment.
                 * \return The color overlap value.
                 */
                double getColorOverlap() const
                {
                    return colOverlap;
                }

              private:
                friend class GaussianShapeFunctionAlignment;

                Result():
                    transform(), overlap(0.0), colOverlap(0.0) {}

                Math::Matrix4D transform;
                double         overlap;
                double         colOverlap;
            };

            /**
             * \brief Constructs the \c %GaussianShapeFunctionAlignment instance without a reference shape.
             */
            GaussianShapeFunctionAlignment();

            /**
             * \brief Constructs the \c %GaussianShapeFunctionAlignment instance with the given reference shape function.
             * \param ref_func The reference shape function.
             * \param sym_class The symmetry class of the reference shape (see namespace Shape::SymmetryClass).
             */
            GaussianShapeFunctionAlignment(const GaussianShapeFunction& ref_func, unsigned int sym_class);

            GaussianShapeFunctionAlignment(const GaussianShapeFunctionAlignment& alignment) = delete;

            /**
             * \brief Destructor.
             */
            ~GaussianShapeFunctionAlignment();

            GaussianShapeFunctionAlignment& operator=(const GaussianShapeFunctionAlignment& alignment) = delete;

            /**
             * \brief Specifies the Gaussian-shape overlap function used during alignment.
             * \param func The overlap function.
             */
            void setOverlapFunction(GaussianShapeOverlapFunction& func);

            /**
             * \brief Returns the currently configured overlap function.
             * \return A reference to the overlap function.
             */
            GaussianShapeOverlapFunction& getOverlapFunction() const;

            /**
             * \brief Returns the built-in default overlap function (Shape::FastGaussianShapeOverlapFunction).
             * \return A \c const reference to the default overlap function.
             */
            const FastGaussianShapeOverlapFunction& getDefaultOverlapFunction() const;

            /**
             * \brief Returns the built-in default overlap function (Shape::FastGaussianShapeOverlapFunction).
             * \return A reference to the default overlap function.
             */
            FastGaussianShapeOverlapFunction& getDefaultOverlapFunction();

            /**
             * \brief Specifies the alignment-start generator used to seed the overlap optimization.
             * \param gen The alignment-start generator.
             */
            void setStartGenerator(GaussianShapeAlignmentStartGenerator& gen);

            /**
             * \brief Returns the currently configured alignment-start generator.
             * \return A reference to the alignment-start generator.
             */
            GaussianShapeAlignmentStartGenerator& getStartGenerator() const;

            /**
             * \brief Returns the built-in default principal-axes alignment-start generator.
             * \return A \c const reference to the default alignment-start generator.
             */
            const PrincipalAxesAlignmentStartGenerator& getDefaultStartGenerator() const;

            /**
             * \brief Returns the built-in default principal-axes alignment-start generator.
             * \return A reference to the default alignment-start generator.
             */
            PrincipalAxesAlignmentStartGenerator& getDefaultStartGenerator();

            /**
             * \brief Specifies the function used to decide whether two color features match.
             * \param func The color-match function.
             */
            void setColorMatchFunction(const ColorMatchFunction& func);

            /**
             * \brief Returns the currently configured color-match function.
             * \return A \c const reference to the color-match function.
             */
            const ColorMatchFunction& getColorMatchFunction() const;

            /**
             * \brief Specifies the function used to filter color features by type.
             * \param func The color-filter function.
             */
            void setColorFilterFunction(const ColorFilterFunction& func);

            /**
             * \brief Returns the currently configured color-filter function.
             * \return A \c const reference to the color-filter function.
             */
            const ColorFilterFunction& getColorFilterFunction() const;

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
             * \brief Delegates the reference-shape preparation to the configured start generator.
             * \param func The reference shape function (may be modified).
             * \param xform The output transformation that maps the prepared frame back to the original frame.
             * \return The perceived symmetry class of the reference shape (see namespace Shape::SymmetryClass).
             */
            unsigned int setupReference(GaussianShapeFunction& func, Math::Matrix4D& xform) const;

            /**
             * \brief Delegates the aligned-shape preparation to the configured start generator.
             * \param func The aligned shape function (may be modified).
             * \param xform The output transformation that maps the prepared frame back to the original frame.
             * \return The perceived symmetry class of the aligned shape (see namespace Shape::SymmetryClass).
             */
            unsigned int setupAligned(GaussianShapeFunction& func, Math::Matrix4D& xform) const;

            /**
             * \brief Sets the reference shape function used by subsequent align() calls.
             * \param func The reference shape function.
             * \param sym_class The symmetry class of the reference shape (see namespace Shape::SymmetryClass).
             */
            void setReference(const GaussianShapeFunction& func, unsigned int sym_class);

            /**
             * \brief Returns the current reference shape function (or \c nullptr if none is set).
             * \return A pointer to the reference shape function.
             */
            const GaussianShapeFunction* getReference() const;

            /**
             * \brief Calculates the shape-only self-overlap of \a func using the configured overlap function.
             * \param func The shape function.
             * \return The self-overlap value.
             */
            double calcSelfOverlap(const GaussianShapeFunction& func);

            /**
             * \brief Calculates the color self-overlap of \a func using the configured overlap function.
             * \param func The shape function.
             * \return The color self-overlap value.
             */
            double calcColorSelfOverlap(const GaussianShapeFunction& func);

            /**
             * \brief Specifies whether color overlaps shall be evaluated in addition to shape overlaps.
             * \param calc \c true to evaluate color overlaps, and \c false to skip them.
             */
            void calcColorOverlaps(bool calc);

            /**
             * \brief Tells whether color overlaps are evaluated.
             * \return \c true if color overlaps are evaluated, and \c false otherwise.
             */
            bool calcColorOverlaps() const;

            /**
             * \brief Aligns the shape function \a func against the configured reference shape.
             * \param func The aligned shape function.
             * \param sym_class The symmetry class of the aligned shape (see namespace Shape::SymmetryClass).
             * \return \c true if at least one alignment result was produced, and \c false otherwise.
             */
            bool align(const GaussianShapeFunction& func, unsigned int sym_class);

            /**
             * \brief Returns the number of alignment results produced by the last align() call.
             * \return The number of alignment results.
             */
            std::size_t getNumResults() const;

            /**
             * \brief Returns the alignment result at index \a idx.
             * \param idx The zero-based result index.
             * \return A \c const reference to the result.
             * \throw Base::IndexError if the number of results is zero or \a idx is not in the range [0, getNumResults() - 1].
             */
            const Result& getResult(std::size_t idx) const;

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
             * \brief Returns a constant iterator pointing to the first alignment result (range-based for support).
             * \return A constant iterator pointing to the first alignment result.
             */
            ConstResultIterator begin() const;

            /**
             * \brief Returns a constant iterator pointing one past the last alignment result (range-based for support).
             * \return A constant iterator pointing one past the last alignment result.
             */
            ConstResultIterator end() const;

          private:
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
            bool                                  perfAlignment;
            bool                                  calcColOverlaps;
            bool                                  optOverlap;
            bool                                  greedyOpt;
            std::size_t                           maxNumOptIters;
            double                                optStopGrad;
            Math::Vector3DArray                   startPoseCoords;
            Math::Vector3DArray                   optPoseCoords;
            Math::Vector3DArray                   optPoseCoordsGrad;
            BFGSMinimizer                         minimizer;
            ResultList                            results;
        };
    } // namespace Shape
} // namespace CDPL

#endif // CDPL_SHAPE_GAUSSIANSHAPEFUNCTIONALIGNMENT_HPP
