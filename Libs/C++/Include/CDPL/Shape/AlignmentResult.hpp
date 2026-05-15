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
 * \brief Definition of class CDPL::Shape::AlignmentResult.
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

        /**
         * \brief Result of a Gaussian-shape alignment between a reference and an aligned shape.
         *
         * Bundles the rigid-body transformation that brings the aligned shape onto the reference shape
         * together with the resulting overlap-based score values, source/destination shape indices,
         * and the self-overlap values used for normalization.
         */
        class CDPL_SHAPE_API AlignmentResult
        {

          public:
            /**
             * \brief Constructs the \c %AlignmentResult instance.
             */
            AlignmentResult();

            /**
             * \brief Returns the rigid-body transformation matrix that maps the aligned shape onto the reference shape.
             * \return The transformation matrix.
             */
            const Math::Matrix4D& getTransform() const;

            /**
             * \brief Sets the rigid-body transformation matrix.
             * \param xform The transformation matrix.
             */
            void setTransform(const Math::Matrix4D& xform);

            /**
             * \brief Returns the score of the alignment.
             * \return The alignment score.
             */
            double getScore() const;

            /**
             * \brief Sets the score of the alignment.
             * \param score The alignment score.
             */
            void setScore(double score);

            /**
             * \brief Returns the index of the reference shape set the aligned shape was matched against.
             * \return The reference shape set index.
             */
            std::size_t getReferenceShapeSetIndex() const;

            /**
             * \brief Sets the index of the reference shape set.
             * \param idx The reference shape set index.
             */
            void setReferenceShapeSetIndex(std::size_t idx);

            /**
             * \brief Returns the index of the reference shape within its shape set.
             * \return The reference shape index.
             */
            std::size_t getReferenceShapeIndex() const;

            /**
             * \brief Sets the index of the reference shape within its shape set.
             * \param idx The reference shape index.
             */
            void setReferenceShapeIndex(std::size_t idx);

            /**
             * \brief Returns the index of the aligned shape.
             * \return The aligned shape index.
             */
            std::size_t getAlignedShapeIndex() const;

            /**
             * \brief Sets the index of the aligned shape.
             * \param idx The aligned shape index.
             */
            void setAlignedShapeIndex(std::size_t idx);

            /**
             * \brief Returns the self-overlap of the reference shape (shape-only contribution).
             * \return The reference shape self-overlap value.
             */
            double getReferenceSelfOverlap() const;

            /**
             * \brief Sets the self-overlap of the reference shape (shape-only contribution).
             * \param overlap The reference shape self-overlap value.
             */
            void setReferenceSelfOverlap(double overlap);

            /**
             * \brief Returns the self-overlap of the reference shape (color/pharmacophore contribution).
             * \return The reference shape color self-overlap value.
             */
            double getReferenceColorSelfOverlap() const;

            /**
             * \brief Sets the self-overlap of the reference shape (color/pharmacophore contribution).
             * \param overlap The reference shape color self-overlap value.
             */
            void setReferenceColorSelfOverlap(double overlap);

            /**
             * \brief Returns the self-overlap of the aligned shape (shape-only contribution).
             * \return The aligned shape self-overlap value.
             */
            double getAlignedSelfOverlap() const;

            /**
             * \brief Sets the self-overlap of the aligned shape (shape-only contribution).
             * \param overlap The aligned shape self-overlap value.
             */
            void setAlignedSelfOverlap(double overlap);

            /**
             * \brief Returns the self-overlap of the aligned shape (color/pharmacophore contribution).
             * \return The aligned shape color self-overlap value.
             */
            double getAlignedColorSelfOverlap() const;

            /**
             * \brief Sets the self-overlap of the aligned shape (color/pharmacophore contribution).
             * \param overlap The aligned shape color self-overlap value.
             */
            void setAlignedColorSelfOverlap(double overlap);

            /**
             * \brief Returns the calculated overlap between the reference and the aligned shape (shape-only contribution).
             * \return The shape overlap value.
             */
            double getOverlap() const;

            /**
             * \brief Sets the overlap between the reference and the aligned shape (shape-only contribution).
             * \param overlap The shape overlap value.
             */
            void setOverlap(double overlap);

            /**
             * \brief Returns the calculated overlap between the reference and the aligned shape (color/pharmacophore contribution).
             * \return The color overlap value.
             */
            double getColorOverlap() const;

            /**
             * \brief Sets the overlap between the reference and the aligned shape (color/pharmacophore contribution).
             * \param overlap The color overlap value.
             */
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
