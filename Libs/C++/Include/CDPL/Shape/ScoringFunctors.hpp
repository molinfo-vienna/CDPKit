/* 
 * ScoringFunctors.hpp 
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
 * \brief Definition of shape alignment scoring functors.
 */

#ifndef CDPL_SHAPE_SCORINGFUNCTORS_HPP
#define CDPL_SHAPE_SCORINGFUNCTORS_HPP

#include "CDPL/Shape/ScoringFunctions.hpp"


namespace CDPL
{

    namespace Shape
    {

        /** \brief Functor wrapping Shape::calcTotalOverlapTanimotoScore(). */
        class TotalOverlapTanimotoScore
        {

          public:
            /**
             * \brief Returns the (shape + color) total-overlap Tanimoto score of \a res.
             * \param res The alignment result.
             * \return The total-overlap Tanimoto score.
             */
            double operator()(const AlignmentResult& res) const
            {
                return calcTotalOverlapTanimotoScore(res);
            }
        };

        /** \brief Functor wrapping Shape::calcShapeTanimotoScore(). */
        class ShapeTanimotoScore
        {

          public:
            /**
             * \brief Returns the shape-only Tanimoto score of \a res.
             * \param res The alignment result.
             * \return The shape-only Tanimoto score.
             */
            double operator()(const AlignmentResult& res) const
            {
                return calcShapeTanimotoScore(res);
            }
        };

        /** \brief Functor wrapping Shape::calcColorTanimotoScore(). */
        class ColorTanimotoScore
        {

          public:
            /**
             * \brief Returns the color (pharmacophore) Tanimoto score of \a res.
             * \param res The alignment result.
             * \return The color Tanimoto score.
             */
            double operator()(const AlignmentResult& res) const
            {
                return calcColorTanimotoScore(res);
            }
        };

        /** \brief Functor wrapping Shape::calcTanimotoComboScore(). */
        class TanimotoComboScore
        {

          public:
            /**
             * \brief Returns the combined shape + color Tanimoto score of \a res.
             * \param res The alignment result.
             * \return The Tanimoto combo score.
             */
            double operator()(const AlignmentResult& res) const
            {
                return calcTanimotoComboScore(res);
            }
        };

        /** \brief Functor wrapping Shape::calcTotalOverlapTverskyScore(). */
        class TotalOverlapTverskyScore
        {

          public:
            /**
             * \brief Constructs the functor with the given Tversky weighting factors.
             * \param alpha The reference-side Tversky weight.
             * \param beta The aligned-side Tversky weight.
             */
            TotalOverlapTverskyScore(double alpha = 0.95, double beta = 0.05):
                alpha(alpha), beta(beta) {}

            /**
             * \brief Returns the (shape + color) total-overlap symmetric Tversky score of \a res.
             * \param res The alignment result.
             * \return The total-overlap symmetric Tversky score.
             */
            double operator()(const AlignmentResult& res) const
            {
                return calcTotalOverlapTverskyScore(res, alpha, beta);
            }

          private:
            double alpha;
            double beta;
        };

        /** \brief Functor wrapping Shape::calcShapeTverskyScore(). */
        class ShapeTverskyScore
        {

          public:
            /**
             * \brief Constructs the functor with the given Tversky weighting factors.
             * \param alpha The reference-side Tversky weight.
             * \param beta The aligned-side Tversky weight.
             */
            ShapeTverskyScore(double alpha = 0.95, double beta = 0.05):
                alpha(alpha), beta(beta) {}

            /**
             * \brief Returns the shape-only symmetric Tversky score of \a res.
             * \param res The alignment result.
             * \return The shape-only symmetric Tversky score.
             */
            double operator()(const AlignmentResult& res) const
            {
                return calcShapeTverskyScore(res, alpha, beta);
            }

          private:
            double alpha;
            double beta;
        };

        /** \brief Functor wrapping Shape::calcColorTverskyScore(). */
        class ColorTverskyScore
        {

          public:
            /**
             * \brief Constructs the functor with the given Tversky weighting factors.
             * \param alpha The reference-side Tversky weight.
             * \param beta The aligned-side Tversky weight.
             */
            ColorTverskyScore(double alpha = 0.95, double beta = 0.05):
                alpha(alpha), beta(beta) {}

            /**
             * \brief Returns the color symmetric Tversky score of \a res.
             * \param res The alignment result.
             * \return The color symmetric Tversky score.
             */
            double operator()(const AlignmentResult& res) const
            {
                return calcColorTverskyScore(res, alpha, beta);
            }

          private:
            double alpha;
            double beta;
        };

        /** \brief Functor wrapping Shape::calcTverskyComboScore(). */
        class TverskyComboScore
        {

          public:
            /**
             * \brief Constructs the functor with the given Tversky weighting factors.
             * \param alpha The reference-side Tversky weight.
             * \param beta The aligned-side Tversky weight.
             */
            TverskyComboScore(double alpha = 0.95, double beta = 0.05):
                alpha(alpha), beta(beta) {}

            /**
             * \brief Returns the combined shape + color symmetric Tversky score of \a res.
             * \param res The alignment result.
             * \return The symmetric Tversky combo score.
             */
            double operator()(const AlignmentResult& res) const
            {
                return calcTverskyComboScore(res, alpha, beta);
            }

          private:
            double alpha;
            double beta;
        };

        /** \brief Functor wrapping Shape::calcReferenceTotalOverlapTverskyScore(). */
        class ReferenceTotalOverlapTverskyScore
        {

          public:
            /**
             * \brief Constructs the functor with the given Tversky weighting factor.
             * \param alpha The reference-side Tversky weight.
             */
            ReferenceTotalOverlapTverskyScore(double alpha = 0.95):
                alpha(alpha) {}

            /**
             * \brief Returns the (shape + color) total-overlap reference-normalized Tversky score of \a res.
             * \param res The alignment result.
             * \return The total-overlap reference-normalized Tversky score.
             */
            double operator()(const AlignmentResult& res) const
            {
                return calcReferenceTotalOverlapTverskyScore(res, alpha);
            }

          private:
            double alpha;
        };

        /** \brief Functor wrapping Shape::calcReferenceShapeTverskyScore(). */
        class ReferenceShapeTverskyScore
        {

          public:
            /**
             * \brief Constructs the functor with the given Tversky weighting factor.
             * \param alpha The reference-side Tversky weight.
             */
            ReferenceShapeTverskyScore(double alpha = 0.95):
                alpha(alpha) {}

            /**
             * \brief Returns the shape-only reference-normalized Tversky score of \a res.
             * \param res The alignment result.
             * \return The shape-only reference-normalized Tversky score.
             */
            double operator()(const AlignmentResult& res) const
            {
                return calcReferenceShapeTverskyScore(res, alpha);
            }

          private:
            double alpha;
        };

        /** \brief Functor wrapping Shape::calcReferenceColorTverskyScore(). */
        class ReferenceColorTverskyScore
        {

          public:
            /**
             * \brief Constructs the functor with the given Tversky weighting factor.
             * \param alpha The reference-side Tversky weight.
             */
            ReferenceColorTverskyScore(double alpha = 0.95):
                alpha(alpha) {}

            /**
             * \brief Returns the color reference-normalized Tversky score of \a res.
             * \param res The alignment result.
             * \return The color reference-normalized Tversky score.
             */
            double operator()(const AlignmentResult& res) const
            {
                return calcReferenceColorTverskyScore(res, alpha);
            }

          private:
            double alpha;
        };

        /** \brief Functor wrapping Shape::calcReferenceTverskyComboScore(). */
        class ReferenceTverskyComboScore
        {

          public:
            /**
             * \brief Constructs the functor with the given Tversky weighting factor.
             * \param alpha The reference-side Tversky weight.
             */
            ReferenceTverskyComboScore(double alpha = 0.95):
                alpha(alpha) {}

            /**
             * \brief Returns the combined shape + color reference-normalized Tversky score of \a res.
             * \param res The alignment result.
             * \return The reference-normalized Tversky combo score.
             */
            double operator()(const AlignmentResult& res) const
            {
                return calcReferenceTverskyComboScore(res, alpha);
            }

          private:
            double alpha;
        };

        /** \brief Functor wrapping Shape::calcAlignedTotalOverlapTverskyScore(). */
        class AlignedTotalOverlapTverskyScore
        {

          public:
            /**
             * \brief Constructs the functor with the given Tversky weighting factor.
             * \param beta The aligned-side Tversky weight.
             */
            AlignedTotalOverlapTverskyScore(double beta = 0.95):
                beta(beta) {}

            /**
             * \brief Returns the (shape + color) total-overlap aligned-normalized Tversky score of \a res.
             * \param res The alignment result.
             * \return The total-overlap aligned-normalized Tversky score.
             */
            double operator()(const AlignmentResult& res) const
            {
                return calcAlignedTotalOverlapTverskyScore(res, beta);
            }

          private:
            double beta;
        };

        /** \brief Functor wrapping Shape::calcAlignedShapeTverskyScore(). */
        class AlignedShapeTverskyScore
        {

          public:
            /**
             * \brief Constructs the functor with the given Tversky weighting factor.
             * \param beta The aligned-side Tversky weight.
             */
            AlignedShapeTverskyScore(double beta = 0.95):
                beta(beta) {}

            /**
             * \brief Returns the shape-only aligned-normalized Tversky score of \a res.
             * \param res The alignment result.
             * \return The shape-only aligned-normalized Tversky score.
             */
            double operator()(const AlignmentResult& res) const
            {
                return calcAlignedShapeTverskyScore(res, beta);
            }

          private:
            double beta;
        };

        /** \brief Functor wrapping Shape::calcAlignedColorTverskyScore(). */
        class AlignedColorTverskyScore
        {

          public:
            /**
             * \brief Constructs the functor with the given Tversky weighting factor.
             * \param beta The aligned-side Tversky weight.
             */
            AlignedColorTverskyScore(double beta = 0.95):
                beta(beta) {}

            /**
             * \brief Returns the color aligned-normalized Tversky score of \a res.
             * \param res The alignment result.
             * \return The color aligned-normalized Tversky score.
             */
            double operator()(const AlignmentResult& res) const
            {
                return calcAlignedColorTverskyScore(res, beta);
            }

          private:
            double beta;
        };

        /** \brief Functor wrapping Shape::calcAlignedTverskyComboScore(). */
        class AlignedTverskyComboScore
        {

          public:
            /**
             * \brief Constructs the functor with the given Tversky weighting factor.
             * \param beta The aligned-side Tversky weight.
             */
            AlignedTverskyComboScore(double beta = 0.95):
                beta(beta) {}

            /**
             * \brief Returns the combined shape + color aligned-normalized Tversky score of \a res.
             * \param res The alignment result.
             * \return The aligned-normalized Tversky combo score.
             */
            double operator()(const AlignmentResult& res) const
            {
                return calcAlignedTverskyComboScore(res, beta);
            }

          private:
            double beta;
        };
    } // namespace Shape
} // namespace CDPL

#endif // CDPL_SHAPE_SCORINGFUNCTORS_HPP
