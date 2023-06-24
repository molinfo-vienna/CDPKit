/* 
 * AlignmentResult.hpp 
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
 * \brief Definition of the class CDPL::Shape::AlignmentResult.
 */

#ifndef CDPL_SHAPE_ALIGNMENTRESULT_HPP
#define CDPL_SHAPE_ALIGNMENTRESULT_HPP

#include <cstddef>

#include "CDPL/Shape/APIPrefix.hpp"
#include "CDPL/Math/Matrix.hpp"


namespace CDPL
{

    namespace Shape
    {

        class CDPL_SHAPE_API AlignmentResult
        {

          public:
            AlignmentResult();

            const Math::Matrix4D& getTransform() const;

            void setTransform(const Math::Matrix4D& xform);

            double getScore() const;

            void setScore(double score);

            std::size_t getReferenceShapeSetIndex() const;

            void setReferenceShapeSetIndex(std::size_t idx);

            std::size_t getReferenceShapeIndex() const;

            void setReferenceShapeIndex(std::size_t idx);

            std::size_t getAlignedShapeIndex() const;

            void setAlignedShapeIndex(std::size_t idx);

            double getReferenceSelfOverlap() const;

            void setReferenceSelfOverlap(double overlap);

            double getReferenceColorSelfOverlap() const;

            void setReferenceColorSelfOverlap(double overlap);

            double getAlignedSelfOverlap() const;

            void setAlignedSelfOverlap(double overlap);

            double getAlignedColorSelfOverlap() const;

            void setAlignedColorSelfOverlap(double overlap);

            double getOverlap() const;

            void setOverlap(double overlap);

            double getColorOverlap() const;

            void setColorOverlap(double overlap);

          private:
            Math::Matrix4D transform;
            double         score;
            std::size_t    refShapeSetIdx;
            std::size_t    refShapeIdx;
            std::size_t    algdShapeIdx;
            double         refSelfOverlap;
            double         refColSelfOverlap;
            double         algdSelfOverlap;
            double         algdColSelfOverlap;
            double         overlap;
            double         colOverlap;
        };
    } // namespace Shape
} // namespace CDPL

#endif // CDPL_SHAPE_ALIGNMENTRESULT_HPP
