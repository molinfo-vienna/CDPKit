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
            /** \brief Default scaling factor applied to Van der Waals radii for the proximity-check pruning. */
            static constexpr double DEF_RADIUS_SCALING_FACTOR = 1.4;

            /** \brief A reference-counted smart pointer [\ref SHPTR] for dynamically allocated \c %FastGaussianShapeOverlapFunction instances. */
            typedef std::shared_ptr<FastGaussianShapeOverlapFunction> SharedPointer;

            /**
             * \brief Constructs the \c %FastGaussianShapeOverlapFunction instance without associated shape functions.
             */
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

            /**
             * \brief Destructor.
             */
            ~FastGaussianShapeOverlapFunction();

            /**
             * \brief Enables or disables the proximity-check pruning of Gaussian-product pair contributions.
             * \param enable \c true to enable the proximity check, and \c false to disable it.
             */
            void proximityOptimization(bool enable);

            /**
             * \brief Tells whether the proximity-check pruning is enabled.
             * \return \c true if the proximity check is enabled, and \c false otherwise.
             */
            bool proximityOptimization() const;

            /**
             * \brief Sets the scaling factor applied to Van der Waals radii during the proximity check.
             * \param factor The new radius scaling factor.
             */
            void setRadiusScalingFactor(double factor);

            /**
             * \brief Returns the currently configured radius scaling factor.
             * \return The radius scaling factor.
             */
            double getRadiusScalingFactor() const;

            /**
             * \brief Enables or disables the use of a fast approximation for the exponential function.
             * \param enable \c true to enable the fast-exponential approximation, and \c false to use the standard exponential.
             */
            void fastExpFunction(bool enable);

            /**
             * \brief Tells whether the fast-exponential approximation is enabled.
             * \return \c true if the fast-exponential approximation is enabled, and \c false otherwise.
             */
            bool fastExpFunction() const;

            /**
             * \brief Specifies the reference or aligned shape function used by the overlap evaluation.
             * \param func The shape function.
             * \param is_ref If \c true, \a func is the reference shape function; otherwise the aligned shape function.
             */
            void setShapeFunction(const GaussianShapeFunction& func, bool is_ref);

            /**
             * \brief Returns the reference or aligned shape function.
             * \param ref If \c true, the reference shape function is returned; otherwise the aligned shape function.
             * \return A pointer to the requested shape function (or \c nullptr if none is associated).
             */
            const GaussianShapeFunction* getShapeFunction(bool ref) const;

            /**
             * \brief Specifies the function used to decide whether two color features match.
             * \param func The color-match function.
             */
            void setColorMatchFunction(const ColorMatchFunction& func);

            /**
             * \brief Returns the currently configured color-match function.
             * \return A \c const reference to the color-match function.
             */
            const ColorMatchFunction& getColorMatchFunction() const;

            /**
             * \brief Specifies the function used to filter color features by type.
             * \param func The color-filter function.
             */
            void setColorFilterFunction(const ColorFilterFunction& func);

            /**
             * \brief Returns the currently configured color-filter function.
             * \return A \c const reference to the color-filter function.
             */
            const ColorFilterFunction& getColorFilterFunction() const;

            /**
             * \brief Calculates the shape-only self-overlap of the reference or aligned shape function.
             * \param ref If \c true, the reference self-overlap is returned; otherwise the aligned self-overlap.
             * \return The self-overlap value.
             */
            double calcSelfOverlap(bool ref) const;

            /**
             * \brief Calculates the color self-overlap of the reference or aligned shape function.
             * \param ref If \c true, the reference color self-overlap is returned; otherwise the aligned color self-overlap.
             * \return The color self-overlap value.
             */
            double calcColorSelfOverlap(bool ref) const;

            /**
             * \brief Calculates the shape-only overlap of the reference and aligned shape functions.
             * \return The shape overlap value.
             */
            double calcOverlap() const;

            /**
             * \brief Calculates the color overlap of the reference and aligned shape functions.
             * \return The color overlap value.
             */
            double calcColorOverlap() const;

            /**
             * \brief Calculates the shape-only overlap with the aligned shape element positions taken from \a coords.
             * \param coords The element 3D positions of the aligned shape.
             * \return The shape overlap value.
             */
            double calcOverlap(const Math::Vector3DArray& coords) const;

            /**
             * \brief Calculates the color overlap with the aligned shape element positions taken from \a coords.
             * \param coords The element 3D positions of the aligned shape.
             * \return The color overlap value.
             */
            double calcColorOverlap(const Math::Vector3DArray& coords) const;

            /**
             * \brief Calculates the shape overlap with the aligned shape element positions taken from \a coords and returns the gradient with respect to those positions.
             * \param coords The element 3D positions of the aligned shape.
             * \param grad The output element-wise gradient of the overlap.
             * \return The shape overlap value.
             */
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
