/* 
 * FastGaussianShapeOverlapFunction.hpp 
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
 * \brief Definition of class CDPL::Shape::FastGaussianShapeOverlapFunction.
 */

#ifndef CDPL_SHAPE_FASTGAUSSIANSHAPEOVERLAPFUNCTION_HPP
#define CDPL_SHAPE_FASTGAUSSIANSHAPEOVERLAPFUNCTION_HPP

#include <memory>

#include "CDPL/Shape/APIPrefix.hpp"
#include "CDPL/Shape/GaussianShapeOverlapFunction.hpp"


namespace CDPL
{

    namespace Shape
    {

        class GaussianProductList;

        /**
         * \brief Shape::GaussianShapeOverlapFunction implementation that uses two approximation
         *        techniques to trade some accuracy for a substantial speedup compared to
         *        Shape::ExactGaussianShapeOverlapFunction.
         *
         * Two independent acceleration features can be enabled:
         *   - **Proximity optimization** prunes Gaussian-product pair contributions based on a
         *     scaled van-der-Waals proximity test (see setRadiusScalingFactor()).
         *   - **Fast exponential function** replaces the expensive \c std::exp call with a fast
         *     approximation that is accurate enough for screening-style overlap evaluation.
         */
        class CDPL_SHAPE_API FastGaussianShapeOverlapFunction : public GaussianShapeOverlapFunction
        {

          public:
            /** \brief Default scaling factor applied to van der Waals radii for the proximity-check pruning. */
            static constexpr double DEF_RADIUS_SCALING_FACTOR = 1.4;

            /** \brief A reference-counted smart pointer [\ref SHPTR] for dynamically allocated \c %FastGaussianShapeOverlapFunction instances. */
            typedef std::shared_ptr<FastGaussianShapeOverlapFunction> SharedPointer;

            /** \brief Constructs the \c %FastGaussianShapeOverlapFunction instance without associated shape functions. */
            FastGaussianShapeOverlapFunction();

            /**
             * \brief Constructs a copy of the \c %FastGaussianShapeOverlapFunction instance \a func.
             * \param func The \c %FastGaussianShapeOverlapFunction to copy.
             */
            FastGaussianShapeOverlapFunction(const FastGaussianShapeOverlapFunction& func);

            /**
             * \brief Constructs the \c %FastGaussianShapeOverlapFunction instance with the given reference and aligned shape functions.
             * \param ref_shape_func The reference shape function.
             * \param ovl_shape_func The aligned shape function.
             */
            FastGaussianShapeOverlapFunction(const GaussianShapeFunction& ref_shape_func,
                                             const GaussianShapeFunction& ovl_shape_func);

            /** \brief Destructor. */
            ~FastGaussianShapeOverlapFunction();

            /** \brief Enables or disables the proximity-check pruning of Gaussian-product pair contributions. */
            void proximityOptimization(bool enable);

            /** \brief Tells whether the proximity-check pruning is enabled. */
            bool proximityOptimization() const;

            /** \brief Sets the scaling factor applied to van der Waals radii during the proximity check. */
            void setRadiusScalingFactor(double factor);

            /** \brief Returns the currently configured radius scaling factor. */
            double getRadiusScalingFactor() const;

            /** \brief Enables or disables the use of a fast approximation for the exponential function. */
            void fastExpFunction(bool enable);

            /** \brief Tells whether the fast-exponential approximation is enabled. */
            bool fastExpFunction() const;

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
             * \param func The other \c %FastGaussianShapeOverlapFunction instance.
             * \return A reference to itself.
             */
            FastGaussianShapeOverlapFunction& operator=(const FastGaussianShapeOverlapFunction& func);

          private:
            bool checkShapeFuncsNotNull() const;

            double calcOverlap(const GaussianProductList* ref_prod_list, const GaussianProductList* ovl_prod_list,
                               bool color) const;
            double calcOverlapExact(const GaussianProductList* ref_prod_list, const GaussianProductList* ovl_prod_list,
                                    bool color) const;
            double calcOverlapFastExp(const GaussianProductList* ref_prod_list, const GaussianProductList* ovl_prod_list,
                                      bool color) const;
            double calcOverlapProxCheck(const GaussianProductList* ref_prod_list, const GaussianProductList* ovl_prod_list,
                                        bool color) const;
            double calcOverlapFastExpProxCheck(const GaussianProductList* ref_prod_list, const GaussianProductList* ovl_prod_list,
                                               bool color) const;

            double calcOverlap(const GaussianProductList* ref_prod_list, const GaussianProductList* ovl_prod_list,
                               const Math::Vector3DArray& coords, bool color) const;
            double calcOverlapExact(const GaussianProductList* ref_prod_list, const GaussianProductList* ovl_prod_list,
                                    const Math::Vector3DArray& coords, bool color) const;
            double calcOverlapFastExp(const GaussianProductList* ref_prod_list, const GaussianProductList* ovl_prod_list,
                                      const Math::Vector3DArray& coords, bool color) const;
            double calcOverlapProxCheck(const GaussianProductList* ref_prod_list, const GaussianProductList* ovl_prod_list,
                                        const Math::Vector3DArray& coords, bool color) const;
            double calcOverlapFastExpProxCheck(const GaussianProductList* ref_prod_list, const GaussianProductList* ovl_prod_list,
                                               const Math::Vector3DArray& coords, bool color) const;

            double calcOverlapGradient(const GaussianProductList* ref_prod_list, const GaussianProductList* ovl_prod_list,
                                       const Math::Vector3DArray& coords, Math::Vector3DArray& grad) const;
            double calcOverlapGradientExact(const GaussianProductList* ref_prod_list, const GaussianProductList* ovl_prod_list,
                                            const Math::Vector3DArray& coords, Math::Vector3DArray& grad) const;
            double calcOverlapGradientFastExp(const GaussianProductList* ref_prod_list, const GaussianProductList* ovl_prod_list,
                                              const Math::Vector3DArray& coords, Math::Vector3DArray& grad) const;
            double calcOverlapGradientProxCheck(const GaussianProductList* ref_prod_list, const GaussianProductList* ovl_prod_list,
                                                const Math::Vector3DArray& coords, Math::Vector3DArray& grad) const;
            double calcOverlapGradientFastExpProxCheck(const GaussianProductList* ref_prod_list, const GaussianProductList* ovl_prod_list,
                                                       const Math::Vector3DArray& coords, Math::Vector3DArray& grad) const;

            const GaussianShapeFunction* refShapeFunc;
            const GaussianShapeFunction* ovlShapeFunc;
            ColorMatchFunction           colorMatchFunc;
            ColorFilterFunction          colorFilterFunc;
            bool                         proximityOpt;
            bool                         fastExpFunc;
            double                       radScalingFact;
        };
    } // namespace Shape
} // namespace CDPL

#endif // CDPL_SHAPE_FASTGAUSSIANSHAPEOVERLAPFUNCTION_HPP
