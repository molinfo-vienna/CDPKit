/* 
 * GaussianShapeAlignmentStartGenerator.hpp 
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
 * \brief Definition of class CDPL::Shape::GaussianShapeAlignmentStartGenerator.
 */

#ifndef CDPL_SHAPE_GAUSSIANSHAPEALIGNMENTSTARTGENERATOR_HPP
#define CDPL_SHAPE_GAUSSIANSHAPEALIGNMENTSTARTGENERATOR_HPP

#include <cstddef>

#include "CDPL/Shape/APIPrefix.hpp"
#include "CDPL/Shape/QuaternionTransformation.hpp"
#include "CDPL/Math/Matrix.hpp"


namespace CDPL
{

    namespace Shape
    {

        class GaussianShape;
        class GaussianShapeFunction;

        /**
         * \brief Abstract base class for generators of starting transformations used to seed
         *        Gaussian-shape overlap optimization.
         *
         * Concrete subclasses (e.g. Shape::PrincipalAxesAlignmentStartGenerator) implement the
         * pure virtual member functions to provide a set of candidate transformations placing
         * the aligned shape relative to the reference shape.
         */
        class CDPL_SHAPE_API GaussianShapeAlignmentStartGenerator
        {

          public:
            /** 
             * \brief Virtual destructor. 
             */
            virtual ~GaussianShapeAlignmentStartGenerator() {}

            /**
             * \brief Prepares the reference shape function for use by the start generator.
             * \param func The reference shape function (may be modified, e.g. centered).
             * \param xform The output transformation that maps the reference shape from its prepared frame back to its original frame.
             * \return The perceived symmetry class of the reference shape (see namespace Shape::SymmetryClass).
             */
            virtual unsigned int setupReference(GaussianShapeFunction& func, Math::Matrix4D& xform) const;

            /**
             * \brief Prepares the aligned shape function for use by the start generator.
             * \param func The aligned shape function (may be modified, e.g. centered).
             * \param xform The output transformation that maps the aligned shape from its prepared frame back to its original frame.
             * \return The perceived symmetry class of the aligned shape (see namespace Shape::SymmetryClass).
             */
            virtual unsigned int setupAligned(GaussianShapeFunction& func, Math::Matrix4D& xform) const;

            /**
             * \brief Specifies the reference shape function and its symmetry class.
             * \param ref_shape_func The reference shape function.
             * \param sym_class The symmetry class of the reference shape (see namespace Shape::SymmetryClass).
             */
            virtual void setReference(const GaussianShapeFunction& ref_shape_func, unsigned int sym_class) = 0;

            /**
             * \brief Generates the set of starting transformations for the alignment of \a func.
             * \param func The aligned shape function.
             * \param sym_class The symmetry class of the aligned shape (see namespace Shape::SymmetryClass).
             * \return \c true if at least one starting transformation was produced, and \c false otherwise.
             */
            virtual bool generate(const GaussianShapeFunction& func, unsigned int sym_class) = 0;

            /**
             * \brief Returns the number of starting transformations produced by the last generate() call.
             * \return The number of starting transformations.
             */
            virtual std::size_t getNumStartTransforms() const = 0;

            /**
             * \brief Returns the number of sub-transformations sharing the same starting transformation index space.
             *
             * Subclasses that produce multiple sub-transforms per logical start (e.g. for symmetry-related variants)
             * use this method to expose the secondary count.
             *
             * \return The number of sub-transformations per starting transformation.
             */
            virtual std::size_t getNumStartSubTransforms() const = 0;

            /**
             * \brief Returns the starting transformation at index \a idx.
             * \param idx The zero-based index of the starting transformation.
             * \return A \c const reference to the starting transformation.
             * \throw Base::IndexError if the number of starting transformations is zero or \a idx is not in the range [0, getNumStartTransforms() - 1].
             */
            virtual const QuaternionTransformation& getStartTransform(std::size_t idx) const = 0;
        };
    } // namespace Shape
} // namespace CDPL

#endif // CDPL_SHAPE_GAUSSIANSHAPEALIGNMENTSTARTGENERATOR_HPP
