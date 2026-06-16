/* 
 * GaussianShapeFunctions.hpp 
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
 * \brief Declaration of functions operating on object of type Shape::GaussianShape.
 */

#ifndef CDPL_SHAPE_GAUSSIANSHAPEFUNCTIONS_HPP
#define CDPL_SHAPE_GAUSSIANSHAPEFUNCTIONS_HPP

#include "CDPL/Shape/APIPrefix.hpp"
#include "CDPL/Chem/Atom3DCoordinatesFunction.hpp"
#include "CDPL/Math/Matrix.hpp"


namespace CDPL
{

    namespace Chem
    {

        class AtomContainer;
    }

    namespace Pharm
    {

        class FeatureContainer;
    }

    namespace Shape
    {

        class GaussianShape;
        class GaussianShapeFunction;

        /**
         * \brief Builds a Gaussian shape from the atoms of \a atoms (using the default atom 3D coordinates accessor).
         * \param atoms The atom container.
         * \param shape The output Gaussian shape.
         * \param append If \c true, the new elements are appended to \a shape. Otherwise, \a shape is cleared first.
         * \param radius The sphere radius to use for all atoms, or a negative value to use atom-specific Van der Waals radii.
         * \param inc_h If \c true, hydrogen atoms are also included in the shape.
         * \param p The Gaussian hardness used for all generated spheres.
         */
        CDPL_SHAPE_API void generateGaussianShape(const Chem::AtomContainer& atoms, GaussianShape& shape,
                                                  bool append = false, double radius = -1.0, bool inc_h = false, double p = 2.7);

        /**
         * \brief Builds a Gaussian shape from the atoms of \a atoms using \a coords_func to retrieve atom positions.
         * \param atoms The atom container.
         * \param shape The output Gaussian shape.
         * \param coords_func The function used to retrieve atom 3D-coordinates.
         * \param append If \c true, the new elements are appended to \a shape. Otherwise, \a shape is cleared first.
         * \param radius The sphere radius to use for all atoms, or a negative value to use atom-specific Van der Waals radii.
         * \param inc_h If \c true, hydrogen atoms are also included in the shape.
         * \param p The Gaussian hardness used for all generated spheres.
         */
        CDPL_SHAPE_API void generateGaussianShape(const Chem::AtomContainer& atoms, GaussianShape& shape, const Chem::Atom3DCoordinatesFunction& coords_func,
                                                  bool append = false, double radius = -1.0, bool inc_h = false, double p = 2.7);

        /**
         * \brief Builds a Gaussian shape from the pharmacophore features of \a features.
         * \param features The feature container.
         * \param shape The output Gaussian shape.
         * \param append If \c true, the new elements are appended to \a shape. Otherwise, \a shape is cleared first.
         * \param radius The sphere radius to use for all features, or a negative value to use feature-specific tolerances.
         * \param inc_xv If \c true, exclusion-volume features are also included in the shape.
         * \param p The Gaussian hardness used for all generated spheres.
         */
        CDPL_SHAPE_API void generateGaussianShape(const Pharm::FeatureContainer& features, GaussianShape& shape,
                                                  bool append = false, double radius = -1.0, bool inc_xv = false, double p = 5.0);

        /**
         * \brief Applies an affine transformation to the element positions of \a shape.
         * \param shape The Gaussian shape to transform (modified in place).
         * \param xform The 4x4 transformation matrix.
         */
        CDPL_SHAPE_API void transform(GaussianShape& shape, const Math::Matrix4D& xform);

        /**
         * \brief Centers \a shape at its centroid and aligns its principal axes with the coordinate axes.
         * \param shape The Gaussian shape to align (modified in place).
         * \param func The associated Shape::GaussianShapeFunction used to compute the principal axes.
         * \param back_xform The output transformation that maps the aligned shape back to its original frame.
         * \param mom_eq_thresh The relative threshold below which two principal moments are considered equal.
         * \return The perceived symmetry class of the shape (see namespace Shape::SymmetryClass).
         */
        CDPL_SHAPE_API unsigned int centerAndAlignPrincipalAxes(GaussianShape& shape, const GaussianShapeFunction& func, Math::Matrix4D& back_xform,
                                                                double mom_eq_thresh = 0.15);
    } // namespace Shape
} // namespace CDPL

#endif // CDPL_SHAPE_GAUSSIANSHAPEFUNCTIONS_HPP
