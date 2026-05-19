/* 
 * GaussianShapeFunction.hpp 
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
 * \brief Definition of class CDPL::Shape::GaussianShapeFunction.
 */

#ifndef CDPL_SHAPE_GAUSSIANSHAPEFUNCTION_HPP
#define CDPL_SHAPE_GAUSSIANSHAPEFUNCTION_HPP

#include <cstddef>
#include <memory>

#include "CDPL/Shape/APIPrefix.hpp"
#include "CDPL/Math/Vector.hpp"
#include "CDPL/Math/Matrix.hpp"
#include "CDPL/Math/VectorArray.hpp"


namespace CDPL
{

    namespace Shape
    {

        class GaussianShape;
        class GaussianProductList;
        class ExactGaussianShapeOverlapFunction;
        class FastGaussianShapeOverlapFunction;

        /**
         * \brief Function representation of a Gaussian shape, used to evaluate the shape's density,
         *        volume, surface area and related quantities at arbitrary 3D positions.
         *
         * Internally the function maintains a list of Gaussian products (up to a configurable order)
         * derived from the underlying Shape::GaussianShape. The list is built when the shape is
         * supplied via setShape() (or one of the corresponding constructors).
         */
        class CDPL_SHAPE_API GaussianShapeFunction
        {

          public:
            /** \brief Default maximum order of the Gaussian-product expansion. */
            static constexpr std::size_t DEF_MAX_PRODUCT_ORDER = 6;

            /** \brief Default distance cutoff for pruning negligible Gaussian-product contributions. */
            static constexpr double      DEF_DISTANCE_CUTOFF   = 0.0;

            /** \brief A reference-counted smart pointer [\ref SHPTR] for dynamically allocated \c %GaussianShapeFunction instances. */
            typedef std::shared_ptr<GaussianShapeFunction> SharedPointer;

            /** \brief Constructs the \c %GaussianShapeFunction instance without an associated shape. */
            GaussianShapeFunction();

            /**
             * \brief Constructs a copy of the \c %GaussianShapeFunction instance \a func.
             * \param func The \c %GaussianShapeFunction to copy.
             */
            GaussianShapeFunction(const GaussianShapeFunction& func);

            /**
             * \brief Constructs the \c %GaussianShapeFunction instance associated with \a shape.
             * \param shape The Gaussian shape.
             */
            GaussianShapeFunction(const GaussianShape& shape);

            /** \brief Destructor. */
            ~GaussianShapeFunction();

            /**
             * \brief Sets the maximum order of the Gaussian-product expansion.
             * \param max_order The maximum order.
             */
            void setMaxOrder(std::size_t max_order);

            /**
             * \brief Returns the currently configured maximum order of the Gaussian-product expansion.
             * \return The configured maximum order.
             */
            std::size_t getMaxOrder() const;

            /**
             * \brief Sets the distance cutoff for pruning negligible Gaussian-product contributions.
             * \param cutoff The cutoff distance.
             */
            void setDistanceCutoff(double cutoff);

            /**
             * \brief Returns the currently configured distance cutoff.
             * \return The configured distance cutoff.
             */
            double getDistanceCutoff() const;

            /**
             * \brief Associates the function with the Gaussian shape \a shape.
             * \param shape The Gaussian shape.
             */
            void setShape(const GaussianShape& shape);

            /**
             * \brief Returns a pointer to the associated Gaussian shape (or \c nullptr if none is associated).
             * \return A pointer to the associated Gaussian shape.
             */
            const GaussianShape* getShape() const;

            /** \brief Resets the function by discarding the cached Gaussian-product expansion. */
            void reset();

            /**
             * \brief Applies an affine transformation to the element positions of the associated shape.
             * \param xform The 4x4 transformation matrix.
             */
            void transform(const Math::Matrix4D& xform);

            /**
             * \brief Returns the 3D position of the element at index \a idx.
             * \param idx The element index.
             * \return A \c const reference to the element 3D position.
             * \throw Base::IndexError if no shape is associated with this function or \a idx is not in the range [0, getShape()->getNumElements() - 1].
             */
            const Math::Vector3D& getElementPosition(std::size_t idx) const;

            /**
             * \brief Returns the 3D positions of all elements of the associated shape.
             * \param coords The output array of 3D positions.
             */
            void getElementPositions(Math::Vector3DArray& coords) const;

            /**
             * \brief Evaluates the Gaussian density of the shape at the 3D position \a pos.
             * \param pos The 3D position.
             * \return The Gaussian density value.
             */
            double calcDensity(const Math::Vector3D& pos) const;

            /**
             * \brief Calculates the total volume enclosed by the Gaussian shape.
             * \return The volume.
             */
            double calcVolume() const;

            /**
             * \brief Calculates the total surface area of the Gaussian shape.
             * \return The total surface area.
             */
            double calcSurfaceArea() const;

            /**
             * \brief Calculates the surface area contribution of the single element at index \a elem_idx.
             * \param elem_idx The element index.
             * \return The element surface area.
             */
            double calcSurfaceArea(std::size_t elem_idx) const;

            /**
             * \brief Calculates the centroid of the Gaussian shape.
             * \param ctr The output centroid position.
             */
            void calcCentroid(Math::Vector3D& ctr) const;

            /**
             * \brief Calculates the quadrupole tensor of the Gaussian shape with respect to the reference point \a ctr.
             * \param ctr The reference point (typically the shape centroid).
             * \param quad_tensor The output 3x3 quadrupole tensor.
             */
            void calcQuadrupoleTensor(const Math::Vector3D& ctr, Math::Matrix3D& quad_tensor) const;

            /**
             * \brief Copy assignment operator.
             * \param func The other \c %GaussianShapeFunction instance.
             * \return A reference to itself.
             */
            GaussianShapeFunction& operator=(const GaussianShapeFunction& func);

          private:
            friend class FastGaussianShapeOverlapFunction;
            friend class ExactGaussianShapeOverlapFunction;

            const GaussianProductList* getProductList() const;

            typedef std::unique_ptr<GaussianProductList> ProductListPtr;

            const GaussianShape* shape;
            double               volume;
            ProductListPtr       prodList;
        };
    } // namespace Shape
} // namespace CDPL

#endif // CDPL_SHAPE_GAUSSIANSHAPEFUNCTION_HPP
