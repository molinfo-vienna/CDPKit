/* 
 * ScoringFunctions.hpp 
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
 * \brief Definition of shape alignment scoring functions.
 */

#ifndef CDPL_SHAPE_SCORINGFUNCTIONS_HPP
#define CDPL_SHAPE_SCORINGFUNCTIONS_HPP

#include "CDPL/Shape/APIPrefix.hpp"


namespace CDPL
{

    namespace Shape
    {

        class AlignmentResult;

        CDPL_SHAPE_API double calcTotalOverlapTanimotoScore(const AlignmentResult& res);

        CDPL_SHAPE_API double calcShapeTanimotoScore(const AlignmentResult& res);

        CDPL_SHAPE_API double calcColorTanimotoScore(const AlignmentResult& res);

        CDPL_SHAPE_API double calcTanimotoComboScore(const AlignmentResult& res);


        CDPL_SHAPE_API double calcTotalOverlapTverskyScore(const AlignmentResult& res, double alpha = 0.95, double beta = 0.05);

        CDPL_SHAPE_API double calcShapeTverskyScore(const AlignmentResult& res, double alpha = 0.95, double beta = 0.05);

        CDPL_SHAPE_API double calcColorTverskyScore(const AlignmentResult& res, double alpha = 0.95, double beta = 0.05);

        CDPL_SHAPE_API double calcTverskyComboScore(const AlignmentResult& res, double alpha = 0.95, double beta = 0.05);


        CDPL_SHAPE_API double calcReferenceTotalOverlapTverskyScore(const AlignmentResult& res, double alpha = 0.95);

        CDPL_SHAPE_API double calcReferenceShapeTverskyScore(const AlignmentResult& res, double alpha = 0.95);

        CDPL_SHAPE_API double calcReferenceColorTverskyScore(const AlignmentResult& res, double alpha = 0.95);

        CDPL_SHAPE_API double calcReferenceTverskyComboScore(const AlignmentResult& res, double alpha = 0.95);


        CDPL_SHAPE_API double calcAlignedTotalOverlapTverskyScore(const AlignmentResult& res, double beta = 0.95);

        CDPL_SHAPE_API double calcAlignedShapeTverskyScore(const AlignmentResult& res, double beta = 0.95);

        CDPL_SHAPE_API double calcAlignedColorTverskyScore(const AlignmentResult& res, double beta = 0.95);

        CDPL_SHAPE_API double calcAlignedTverskyComboScore(const AlignmentResult& res, double beta = 0.95);
    } // namespace Shape
} // namespace CDPL

#endif // CDPL_SHAPE_SCORINGFUNCTIONS_HPP
