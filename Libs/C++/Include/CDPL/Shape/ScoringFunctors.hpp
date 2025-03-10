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

#include "CDPL/Shape/APIPrefix.hpp"
#include "CDPL/Shape/ScoringFunctions.hpp"


namespace CDPL
{

    namespace Shape
    {

        class CDPL_SHAPE_API TotalOverlapTanimotoScore
        {

          public:
            double operator()(const AlignmentResult& res) const
            {
                return calcTotalOverlapTanimotoScore(res);
            }
        };

        class CDPL_SHAPE_API ShapeTanimotoScore
        {

          public:
            double operator()(const AlignmentResult& res) const
            {
                return calcShapeTanimotoScore(res);
            }
        };

        class CDPL_SHAPE_API ColorTanimotoScore
        {

          public:
            double operator()(const AlignmentResult& res) const
            {
                return calcColorTanimotoScore(res);
            }
        };

        class CDPL_SHAPE_API TanimotoComboScore
        {

          public:
            double operator()(const AlignmentResult& res) const
            {
                return calcTanimotoComboScore(res);
            }
        };

        class CDPL_SHAPE_API TotalOverlapTverskyScore
        {

          public:
            TotalOverlapTverskyScore(double alpha = 0.95, double beta = 0.05):
                alpha(alpha), beta(beta) {}

            double operator()(const AlignmentResult& res) const
            {
                return calcTotalOverlapTverskyScore(res, alpha, beta);
            }

          private:
            double alpha;
            double beta;
        };

        class CDPL_SHAPE_API ShapeTverskyScore
        {

          public:
            ShapeTverskyScore(double alpha = 0.95, double beta = 0.05):
                alpha(alpha), beta(beta) {}

            double operator()(const AlignmentResult& res) const
            {
                return calcShapeTverskyScore(res, alpha, beta);
            }

          private:
            double alpha;
            double beta;
        };

        class CDPL_SHAPE_API ColorTverskyScore
        {

          public:
            ColorTverskyScore(double alpha = 0.95, double beta = 0.05):
                alpha(alpha), beta(beta) {}

            double operator()(const AlignmentResult& res) const
            {
                return calcColorTverskyScore(res, alpha, beta);
            }

          private:
            double alpha;
            double beta;
        };

        class CDPL_SHAPE_API TverskyComboScore
        {

          public:
            TverskyComboScore(double alpha = 0.95, double beta = 0.05):
                alpha(alpha), beta(beta) {}

            double operator()(const AlignmentResult& res) const
            {
                return calcTverskyComboScore(res, alpha, beta);
            }

          private:
            double alpha;
            double beta;
        };

        class CDPL_SHAPE_API ReferenceTotalOverlapTverskyScore
        {

          public:
            ReferenceTotalOverlapTverskyScore(double alpha = 0.95):
                alpha(alpha) {}

            double operator()(const AlignmentResult& res) const
            {
                return calcReferenceTotalOverlapTverskyScore(res, alpha);
            }

          private:
            double alpha;
        };

        class CDPL_SHAPE_API ReferenceShapeTverskyScore
        {

          public:
            ReferenceShapeTverskyScore(double alpha = 0.95):
                alpha(alpha) {}

            double operator()(const AlignmentResult& res) const
            {
                return calcReferenceShapeTverskyScore(res, alpha);
            }

          private:
            double alpha;
        };

        class CDPL_SHAPE_API ReferenceColorTverskyScore
        {

          public:
            ReferenceColorTverskyScore(double alpha = 0.95):
                alpha(alpha) {}

            double operator()(const AlignmentResult& res) const
            {
                return calcReferenceColorTverskyScore(res, alpha);
            }

          private:
            double alpha;
        };

        class CDPL_SHAPE_API ReferenceTverskyComboScore
        {

          public:
            ReferenceTverskyComboScore(double alpha = 0.95):
                alpha(alpha) {}

            double operator()(const AlignmentResult& res) const
            {
                return calcReferenceTverskyComboScore(res, alpha);
            }

          private:
            double alpha;
        };

        class CDPL_SHAPE_API AlignedTotalOverlapTverskyScore
        {

          public:
            AlignedTotalOverlapTverskyScore(double beta = 0.95):
                beta(beta) {}

            double operator()(const AlignmentResult& res) const
            {
                return calcAlignedTotalOverlapTverskyScore(res, beta);
            }

          private:
            double beta;
        };

        class CDPL_SHAPE_API AlignedShapeTverskyScore
        {

          public:
            AlignedShapeTverskyScore(double beta = 0.95):
                beta(beta) {}

            double operator()(const AlignmentResult& res) const
            {
                return calcAlignedShapeTverskyScore(res, beta);
            }

          private:
            double beta;
        };

        class CDPL_SHAPE_API AlignedColorTverskyScore
        {

          public:
            AlignedColorTverskyScore(double beta = 0.95):
                beta(beta) {}

            double operator()(const AlignmentResult& res) const
            {
                return calcAlignedColorTverskyScore(res, beta);
            }

          private:
            double beta;
        };

        class CDPL_SHAPE_API AlignedTverskyComboScore
        {

          public:
            AlignedTverskyComboScore(double beta = 0.95):
                beta(beta) {}

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
