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

            /**
             * \brief Constructs the \c %PrincipalAxesAlignmentStartGenerator instance.
             */
            PrincipalAxesAlignmentStartGenerator();

            /**
             * \brief Prepares the reference shape function for use by the start generator.
             * \param func The reference shape function (may be modified, e.g. centered).
             * \param xform The output transformation that maps the reference shape from its prepared frame back to its original frame.
             * \return The perceived symmetry class of the reference shape (see namespace Shape::SymmetryClass).
             */
            unsigned int setupReference(GaussianShapeFunction& func, Math::Matrix4D& xform) const;

            /**
             * \brief Prepares the aligned shape function for use by the start generator.
             * \param func The aligned shape function (may be modified, e.g. centered).
             * \param xform The output transformation that maps the aligned shape from its prepared frame back to its original frame.
             * \return The perceived symmetry class of the aligned shape (see namespace Shape::SymmetryClass).
             */
            unsigned int setupAligned(GaussianShapeFunction& func, Math::Matrix4D& xform) const;

            /**
             * \brief Enables or disables the generation of a starting transformation at the shape centroid.
             * \param generate \c true to enable the shape-centroid start, and \c false to disable it.
             */
            void genShapeCenterStarts(bool generate);

            /**
             * \brief Tells whether a starting transformation at the shape centroid is generated.
             * \return \c true if a shape-centroid start is generated, and \c false otherwise.
             */
            bool genShapeCenterStarts() const;

            /**
             * \brief Enables or disables the generation of starting transformations at color (pharmacophore) feature centers.
             * \param generate \c true to enable the color-center starts, and \c false to disable them.
             */
            void genColorCenterStarts(bool generate);

            /**
             * \brief Tells whether starting transformations at color (pharmacophore) feature centers are generated.
             * \return \c true if color-center starts are generated, and \c false otherwise.
             */
            bool genColorCenterStarts() const;

            /**
             * \brief Enables or disables the generation of starting transformations at non-color (shape) element centers.
             * \param generate \c true to enable the non-color-center starts, and \c false to disable them.
             */
            void genNonColorCenterStarts(bool generate);

            /**
             * \brief Tells whether starting transformations at non-color (shape) element centers are generated.
             * \return \c true if non-color-center starts are generated, and \c false otherwise.
             */
            bool genNonColorCenterStarts() const;

            /**
             * \brief Enables or disables the generation of random starting transformations.
             * \param generate \c true to enable the random starts, and \c false to disable them.
             */
            void genRandomStarts(bool generate);

            /**
             * \brief Tells whether random starting transformations are generated.
             * \return \c true if random starts are generated, and \c false otherwise.
             */
            bool genRandomStarts() const;

            /**
             * \brief Specifies whether element-/color-center starts shall be generated for centers of the aligned shape.
             * \param generate \c true to consider aligned-shape centers, and \c false to ignore them.
             */
            void genForAlignedShapeCenters(bool generate);

            /**
             * \brief Tells whether element-/color-center starts are generated for centers of the aligned shape.
             * \return \c true if aligned-shape centers are considered, and \c false otherwise.
             */
            bool genForAlignedShapeCenters() const;

            /**
             * \brief Specifies whether element-/color-center starts shall be generated for centers of the reference shape.
             * \param generate \c true to consider reference-shape centers, and \c false to ignore them.
             */
            void genForReferenceShapeCenters(bool generate);

            /**
             * \brief Tells whether element-/color-center starts are generated for centers of the reference shape.
             * \return \c true if reference-shape centers are considered, and \c false otherwise.
             */
            bool genForReferenceShapeCenters() const;

            /**
             * \brief Specifies whether element-/color-center starts shall be generated for centers of the shape with more elements (instead of both shapes).
             * \param generate \c true to use only the centers of the larger shape, and \c false to use the centers of all configured shapes.
             */
            void genForLargerShapeCenters(bool generate);

            /**
             * \brief Tells whether element-/color-center starts are generated for centers of the shape with more elements (instead of both shapes).
             * \return \c true if only the centers of the larger shape are used, and \c false otherwise.
             */
            bool genForLargerShapeCenters() const;

            /**
             * \brief Sets the relative threshold for treating two principal moments as equal.
             * \param thresh The new symmetry threshold.
             */
            void setSymmetryThreshold(double thresh);

            /**
             * \brief Returns the currently configured symmetry threshold.
             * \return The symmetry threshold.
             */
            double getSymmetryThreshold();

            /**
             * \brief Sets the maximum random translation magnitude applied to random starts.
             * \param max_trans The new maximum random translation magnitude.
             */
            void setMaxRandomTranslation(double max_trans);

            /**
             * \brief Returns the currently configured maximum random translation.
             * \return The maximum random translation magnitude.
             */
            double getMaxRandomTranslation() const;

            /**
             * \brief Sets the number of random starting transformations.
             * \param num_starts The new number of random starts.
             */
            void setNumRandomStarts(std::size_t num_starts);

            /**
             * \brief Returns the currently configured number of random starts.
             * \return The number of random starts.
             */
            std::size_t getNumRandomStarts() const;

            /**
             * \brief Sets the seed used by the random number generator that produces the random starts.
             * \param seed The new random seed.
             */
            void setRandomSeed(unsigned int seed);

            /**
             * \brief Specifies the reference shape function and its symmetry class.
             * \param func The reference shape function.
             * \param sym_class The symmetry class of the reference shape (see namespace Shape::SymmetryClass).
             */
            void setReference(const GaussianShapeFunction& func, unsigned int sym_class);

            /**
             * \brief Generates the starting transformations for the alignment of \a func against the previously configured reference shape.
             * \param func The aligned shape function.
             * \param sym_class The symmetry class of the aligned shape (see namespace Shape::SymmetryClass).
             * \return \c true if at least one starting transformation has been generated, and \c false otherwise.
             */
            bool generate(const GaussianShapeFunction& func, unsigned int sym_class);

            /**
             * \brief Returns the total number of starting transformations produced by the last generate() call.
             * \return The number of starting transformations.
             */
            std::size_t getNumStartTransforms() const;

            /**
             * \brief Returns the number of sub-transformations applied per generated starting transformation (e.g. axes-swap variants).
             * \return The number of sub-transformations.
             */
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
