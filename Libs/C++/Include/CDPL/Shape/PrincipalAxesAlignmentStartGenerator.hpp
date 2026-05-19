/* 
 * PrincipalAxesAlignmentStartGenerator.hpp 
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
 * \brief Definition of class CDPL::Shape::PrincipalAxesAlignmentStartGenerator.
 */

#ifndef CDPL_SHAPE_PRINCIPALAXESALIGNMENTSTARTGENERATOR_HPP
#define CDPL_SHAPE_PRINCIPALAXESALIGNMENTSTARTGENERATOR_HPP

#include <vector>

#include <boost/random/mersenne_twister.hpp>

#include "CDPL/Shape/APIPrefix.hpp"
#include "CDPL/Shape/GaussianShapeAlignmentStartGenerator.hpp"
#include "CDPL/Math/Vector.hpp"
#include "CDPL/Math/QuaternionExpression.hpp"


namespace CDPL
{

    namespace Shape
    {

        /**
         * \brief Generator that produces alignment starting transformations by aligning the
         *        principal axes of the aligned shape to those of the reference shape.
         *
         * Starting transformations can be derived from any combination of (a) the shape centroid,
         * (b) shape element (atom) centers, (c) color (pharmacophore) feature centers, and
         * (d) random rotations applied to translated centers. The exact combination of starts is
         * configured via the various \c gen* setter methods.
         */
        class CDPL_SHAPE_API PrincipalAxesAlignmentStartGenerator : public GaussianShapeAlignmentStartGenerator
        {

          public:
            /** \brief Default relative threshold for treating two principal moments as equal. */
            static constexpr double DEF_SYMMETRY_THRESHOLD          = 0.15;

            /** \brief Default number of random starting transformations. */
            static constexpr std::size_t DEF_NUM_RANDOM_STARTS      = 4;

            /** \brief Default maximum random translation magnitude applied to random starts. */
            static constexpr double      DEF_MAX_RANDOM_TRANSLATION = 2.0;

            /** \brief Constructs the \c %PrincipalAxesAlignmentStartGenerator instance. */
            PrincipalAxesAlignmentStartGenerator();

            unsigned int setupReference(GaussianShapeFunction& func, Math::Matrix4D& xform) const;

            unsigned int setupAligned(GaussianShapeFunction& func, Math::Matrix4D& xform) const;

            /** \brief Enables or disables the generation of a starting transformation at the shape centroid. */
            void genShapeCenterStarts(bool generate);

            /** \brief Tells whether a starting transformation at the shape centroid is generated. */
            bool genShapeCenterStarts() const;

            /** \brief Enables or disables the generation of starting transformations at color (pharmacophore) feature centers. */
            void genColorCenterStarts(bool generate);

            /** \brief Tells whether starting transformations at color (pharmacophore) feature centers are generated. */
            bool genColorCenterStarts() const;

            /** \brief Enables or disables the generation of starting transformations at non-color (shape) element centers. */
            void genNonColorCenterStarts(bool generate);

            /** \brief Tells whether starting transformations at non-color (shape) element centers are generated. */
            bool genNonColorCenterStarts() const;

            /** \brief Enables or disables the generation of random starting transformations. */
            void genRandomStarts(bool generate);

            /** \brief Tells whether random starting transformations are generated. */
            bool genRandomStarts() const;

            /** \brief Specifies whether element-/color-center starts shall be generated for centers of the aligned shape. */
            void genForAlignedShapeCenters(bool generate);

            /** \brief Tells whether element-/color-center starts are generated for centers of the aligned shape. */
            bool genForAlignedShapeCenters() const;

            /** \brief Specifies whether element-/color-center starts shall be generated for centers of the reference shape. */
            void genForReferenceShapeCenters(bool generate);

            /** \brief Tells whether element-/color-center starts are generated for centers of the reference shape. */
            bool genForReferenceShapeCenters() const;

            /** \brief Specifies whether element-/color-center starts shall be generated for centers of the shape with more elements (instead of both shapes). */
            void genForLargerShapeCenters(bool generate);

            /** \brief Tells whether element-/color-center starts are generated for centers of the shape with more elements (instead of both shapes). */
            bool genForLargerShapeCenters() const;

            /** \brief Sets the relative threshold for treating two principal moments as equal. */
            void setSymmetryThreshold(double thresh);

            /** \brief Returns the currently configured symmetry threshold. */
            double getSymmetryThreshold();

            /** \brief Sets the maximum random translation magnitude applied to random starts. */
            void setMaxRandomTranslation(double max_trans);

            /** \brief Returns the currently configured maximum random translation. */
            double getMaxRandomTranslation() const;

            /** \brief Sets the number of random starting transformations. */
            void setNumRandomStarts(std::size_t num_starts);

            /** \brief Returns the currently configured number of random starts. */
            std::size_t getNumRandomStarts() const;

            /** \brief Sets the seed used by the random number generator that produces the random starts. */
            void setRandomSeed(unsigned int seed);

            void setReference(const GaussianShapeFunction& func, unsigned int sym_class);

            bool generate(const GaussianShapeFunction& func, unsigned int sym_class);

            std::size_t getNumStartTransforms() const;

            std::size_t getNumStartSubTransforms() const;

            /**
             * \brief Returns the starting transformation at index \a idx.
             * \param idx The zero-based index of the starting transformation.
             * \return A \c const reference to the starting transformation.
             * \throw Base::IndexError if the number of starting transformations is zero or \a idx is not in the range [0, getNumStartTransforms() - 1].
             */
            const QuaternionTransformation& getStartTransform(std::size_t idx) const;

          private:
            void generateForElementCenters(const GaussianShapeFunction& func, unsigned int axes_swap_flags, bool ref_shape);
            void generate(const Math::Vector3D& ctr_trans, unsigned int axes_swap_flags);

            template <typename QE>
            void addStartTransform(Math::Vector3D::ConstPointer ctr_trans_data, const Math::QuaternionExpression<QE>& rot_quat);

            typedef std::vector<QuaternionTransformation> StartTransformList;
            typedef boost::random::mt11213b               RandomEngine;

            bool                         shapeCtrStarts;
            bool                         colCtrStarts;
            bool                         nonColCtrStarts;
            bool                         randomStarts;
            bool                         genForAlgdShape;
            bool                         genForRefShape;
            bool                         genForLargerShape;
            StartTransformList           startTransforms;
            const GaussianShapeFunction* refShapeFunc;
            double                       symThreshold;
            double                       maxRandomTrans;
            std::size_t                  numRandomStarts;
            unsigned int                 refAxesSwapFlags;
            std::size_t                  numSubTransforms;
            RandomEngine                 randomEngine;
        };
    } // namespace Shape
} // namespace CDPL

#endif // CDPL_SHAPE_PRINCIPALAXESALIGNMENTSTARTGENERATOR_HPP
