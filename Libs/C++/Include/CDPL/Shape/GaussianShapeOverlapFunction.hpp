/* 
 * GaussianShapeOverlapFunction.hpp 
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
 * \brief Definition of class CDPL::Shape::GaussianShapeOverlapFunction.
 */

#ifndef CDPL_SHAPE_GAUSSIANSHAPEOVERLAPFUNCTION_HPP
#define CDPL_SHAPE_GAUSSIANSHAPEOVERLAPFUNCTION_HPP

#include <cstddef>
#include <memory>
#include <functional>

#include "CDPL/Shape/APIPrefix.hpp"
#include "CDPL/Math/VectorArray.hpp"


namespace CDPL
{

    namespace Shape
    {

        class GaussianShapeFunction;

        /**
         * \brief Abstract base class for functions evaluating the overlap between two Gaussian shape functions.
         *
         * Concrete subclasses (e.g. Shape::ExactGaussianShapeOverlapFunction,
         * Shape::FastGaussianShapeOverlapFunction) implement the overlap evaluation using different
         * trade-offs of accuracy vs. speed.
         */
        class CDPL_SHAPE_API GaussianShapeOverlapFunction
        {

          public:
            /** \brief A reference-counted smart pointer [\ref SHPTR] for dynamically allocated \c %GaussianShapeOverlapFunction instances. */
            typedef std::shared_ptr<GaussianShapeOverlapFunction> SharedPointer;

            /** \brief Type of the function used to filter color (pharmacophore) features by type. */
            typedef std::function<bool(std::size_t)>              ColorFilterFunction;

            /** \brief Type of the function used to decide whether two color features match. */
            typedef std::function<bool(std::size_t, std::size_t)> ColorMatchFunction;

            /** \brief Virtual destructor. */
            virtual ~GaussianShapeOverlapFunction() {}

            /**
             * \brief Specifies the reference or aligned shape function used by the overlap evaluation.
             * \param func The shape function.
             * \param is_ref If \c true, \a func is the reference shape function; otherwise the aligned shape function.
             */
            virtual void setShapeFunction(const GaussianShapeFunction& func, bool is_ref) = 0;

            /**
             * \brief Returns the reference or aligned shape function.
             * \param ref If \c true, the reference shape function is returned; otherwise the aligned shape function.
             * \return A pointer to the requested shape function (or \c nullptr if none is associated).
             */
            virtual const GaussianShapeFunction* getShapeFunction(bool ref) const = 0;

            /**
             * \brief Specifies the function used to decide whether two color features match.
             * \param func The color-match function.
             */
            virtual void setColorMatchFunction(const ColorMatchFunction& func) = 0;

            /**
             * \brief Returns the currently configured color-match function.
             * \return A \c const reference to the color-match function.
             */
            virtual const ColorMatchFunction& getColorMatchFunction() const = 0;

            /**
             * \brief Specifies the function used to filter color features by type.
             * \param func The color-filter function.
             */
            virtual void setColorFilterFunction(const ColorFilterFunction& func) = 0;

            /**
             * \brief Returns the currently configured color-filter function.
             * \return A \c const reference to the color-filter function.
             */
            virtual const ColorFilterFunction& getColorFilterFunction() const = 0;

            /**
             * \brief Calculates the shape-only self-overlap of the reference or aligned shape function.
             * \param ref If \c true, the reference self-overlap is returned; otherwise the aligned self-overlap.
             * \return The self-overlap value.
             */
            virtual double calcSelfOverlap(bool ref) const = 0;

            /**
             * \brief Calculates the color self-overlap of the reference or aligned shape function.
             * \param ref If \c true, the reference color self-overlap is returned; otherwise the aligned color self-overlap.
             * \return The color self-overlap value.
             */
            virtual double calcColorSelfOverlap(bool ref) const = 0;

            /**
             * \brief Calculates the shape-only overlap of the reference and aligned shape functions.
             * \return The shape overlap value.
             */
            virtual double calcOverlap() const = 0;

            /**
             * \brief Calculates the color overlap of the reference and aligned shape functions.
             * \return The color overlap value.
             */
            virtual double calcColorOverlap() const = 0;

            /**
             * \brief Calculates the shape-only overlap with the aligned shape element positions taken from \a coords.
             * \param coords The element 3D positions of the aligned shape.
             * \return The shape overlap value.
             */
            virtual double calcOverlap(const Math::Vector3DArray& coords) const = 0;

            /**
             * \brief Calculates the color overlap with the aligned shape element positions taken from \a coords.
             * \param coords The element 3D positions of the aligned shape.
             * \return The color overlap value.
             */
            virtual double calcColorOverlap(const Math::Vector3DArray& coords) const = 0;

            /**
             * \brief Calculates the shape overlap with the aligned shape element positions taken from \a coords and returns the gradient with respect to those positions.
             * \param coords The element 3D positions of the aligned shape.
             * \param grad The output element-wise gradient of the overlap.
             * \return The shape overlap value.
             */
            virtual double calcOverlapGradient(const Math::Vector3DArray& coords, Math::Vector3DArray& grad) const = 0;

          protected:
            GaussianShapeOverlapFunction() {}

            GaussianShapeOverlapFunction(const GaussianShapeOverlapFunction& func) {}

            GaussianShapeOverlapFunction& operator=(const GaussianShapeOverlapFunction& func)
            {
                return *this;
            }
        };
    } // namespace Shape
} // namespace CDPL

#endif // CDPL_SHAPE_GAUSSIANSHAPEOVERLAPFUNCTION_HPP
