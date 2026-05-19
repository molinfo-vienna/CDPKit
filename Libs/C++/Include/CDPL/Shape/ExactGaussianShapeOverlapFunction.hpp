/* 
 * ExactGaussianShapeOverlapFunction.hpp 
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
 * \brief Definition of class CDPL::Shape::ExactGaussianShapeOverlapFunction.
 */

#ifndef CDPL_SHAPE_EXACTGAUSSIANSHAPEOVERLAPFUNCTION_HPP
#define CDPL_SHAPE_EXACTGAUSSIANSHAPEOVERLAPFUNCTION_HPP

#include <memory>

#include "CDPL/Shape/APIPrefix.hpp"
#include "CDPL/Shape/GaussianShapeOverlapFunction.hpp"


namespace CDPL
{

    namespace Shape
    {

        class GaussianProductList;

        /**
         * \brief Shape::GaussianShapeOverlapFunction implementation that evaluates the overlap
         *        analytically using the full Gaussian-product expansion (no approximations).
         *
         * The exact evaluation is more accurate but typically slower than
         * Shape::FastGaussianShapeOverlapFunction.
         */
        class CDPL_SHAPE_API ExactGaussianShapeOverlapFunction : public GaussianShapeOverlapFunction
        {

          public:
            /** \brief A reference-counted smart pointer [\ref SHPTR] for dynamically allocated \c %ExactGaussianShapeOverlapFunction instances. */
            typedef std::shared_ptr<ExactGaussianShapeOverlapFunction> SharedPointer;

            /** \brief Constructs the \c %ExactGaussianShapeOverlapFunction instance without associated shape functions. */
            ExactGaussianShapeOverlapFunction();

            /**
             * \brief Constructs a copy of the \c %ExactGaussianShapeOverlapFunction instance \a func.
             * \param func The \c %ExactGaussianShapeOverlapFunction to copy.
             */
            ExactGaussianShapeOverlapFunction(const ExactGaussianShapeOverlapFunction& func);

            /**
             * \brief Constructs the \c %ExactGaussianShapeOverlapFunction instance with the given reference and aligned shape functions.
             * \param ref_shape_func The reference shape function.
             * \param ovl_shape_func The aligned shape function.
             */
            ExactGaussianShapeOverlapFunction(const GaussianShapeFunction& ref_shape_func,
                                              const GaussianShapeFunction& ovl_shape_func);

            /** \brief Destructor. */
            ~ExactGaussianShapeOverlapFunction();

            void setShapeFunction(const GaussianShapeFunction& func, bool is_ref);

            const GaussianShapeFunction* getShapeFunction(bool ref) const;

            void setColorMatchFunction(const ColorMatchFunction& func);

            const ColorMatchFunction& getColorMatchFunction() const;

            void setColorFilterFunction(const ColorFilterFunction& func);

            const ColorFilterFunction& getColorFilterFunction() const;

            double calcSelfOverlap(bool ref) const;

            double calcColorSelfOverlap(bool ref) const;

            double calcOverlap() const;

            double calcColorOverlap() const;

            double calcOverlap(const Math::Vector3DArray& coords) const;

            double calcColorOverlap(const Math::Vector3DArray& coords) const;

            double calcOverlapGradient(const Math::Vector3DArray& coords, Math::Vector3DArray& grad) const;

            /**
             * \brief Copy assignment operator.
             * \param func The other \c %ExactGaussianShapeOverlapFunction instance.
             * \return A reference to itself.
             */
            ExactGaussianShapeOverlapFunction& operator=(const ExactGaussianShapeOverlapFunction& func);

          private:
            bool checkShapeFuncsNotNull() const;

            double calcOverlap(const GaussianProductList* ref_prod_list, const GaussianProductList* ovl_prod_list,
                               bool color) const;
            double calcOverlap(const GaussianProductList* ref_prod_list, const GaussianProductList* ovl_prod_list,
                               const Math::Vector3DArray& coords,
                               bool                       color) const;
            double calcOverlapGradient(const GaussianProductList* ref_prod_list, const GaussianProductList* ovl_prod_list,
                                       const Math::Vector3DArray& coords, Math::Vector3DArray& grad) const;

            const GaussianShapeFunction* refShapeFunc;
            const GaussianShapeFunction* ovlShapeFunc;
            ColorMatchFunction           colorMatchFunc;
            ColorFilterFunction          colorFilterFunc;
        };
    } // namespace Shape
} // namespace CDPL

#endif // CDPL_SHAPE_EXACTGAUSSIANSHAPEOVERLAPFUNCTION_HPP
