/* 
 * Entity3DContainerFunctions.hpp 
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
 * \brief Declaration of functions that operate on Chem::Entity3DContainer instances.
 */

#ifndef CDPL_CHEM_ENTITY3DCONTAINERFUNCTIONS_HPP
#define CDPL_CHEM_ENTITY3DCONTAINERFUNCTIONS_HPP

#include "CDPL/Chem/APIPrefix.hpp"
#include "CDPL/Math/VectorArray.hpp"
#include "CDPL/Math/Matrix.hpp"


namespace CDPL
{

    namespace Chem
    {

        class Entity3DContainer;


        /**
         * \brief Calculates the inter-entity geometric distance matrix for the entities of \a cntnr.
         * \param cntnr The entity 3D container providing the source coordinates.
         * \param mtx The output matrix receiving the calculated pairwise distances.
         */
        CDPL_CHEM_API void calcGeometricalDistanceMatrix(const Entity3DContainer& cntnr, Math::DMatrix& mtx);


        /**
         * \brief Stores the 3D coordinates of the entities of \a cntnr in \a coords.
         * \param cntnr The entity 3D container providing the source coordinates.
         * \param coords The output coordinates array.
         * \param append If \c true, the entity coordinates are appended to \a coords. If \c false, \a coords is cleared first.
         */
        CDPL_CHEM_API void get3DCoordinates(const Entity3DContainer& cntnr, Math::Vector3DArray& coords, bool append = false);

        /**
         * \brief Sets the 3D coordinates of the entities of \a cntnr from \a coords.
         * \param cntnr The entity 3D container whose coordinates are to be updated.
         * \param coords The input coordinates array (must contain at least one position per entity in \a cntnr).
         */
        CDPL_CHEM_API void set3DCoordinates(Entity3DContainer& cntnr, const Math::Vector3DArray& coords);

        /**
         * \brief Transforms the 3D coordinates of the entities of \a cntnr by the affine matrix \a mtx.
         * \param cntnr The entity 3D container whose coordinates are to be transformed.
         * \param mtx The \f$ 4 \times 4 \f$ affine transformation matrix.
         */
        CDPL_CHEM_API void transform3DCoordinates(Entity3DContainer& cntnr, const Math::Matrix4D& mtx);

        /**
         * \brief Rigid-body aligns the 3D coordinates of \a cntnr to the reference geometry defined by
         *        the entity-coordinate pair (\a ref_entities, \a ref_coords).
         * \param cntnr The entity 3D container whose coordinates are to be aligned.
         * \param ref_entities The reference entity 3D container.
         * \param ref_coords The reference coordinates corresponding to the entities of \a ref_entities.
         * \return \c true if the alignment succeeded, and \c false otherwise.
         * \since 1.1
         */
        CDPL_CHEM_API bool align3DCoordinates(Entity3DContainer& cntnr, const Entity3DContainer& ref_entities, const Math::Vector3DArray& ref_coords);


        /**
         * \brief Calculates the geometric centroid of the entities of \a cntnr.
         * \param cntnr The entity 3D container.
         * \param ctr The output centroid vector.
         * \return \c true if the centroid could be calculated (i.e. \a cntnr is non-empty), and \c false otherwise.
         */
        CDPL_CHEM_API bool calcCentroid(const Entity3DContainer& cntnr, Math::Vector3D& ctr);

        /**
         * \brief Calculates the axis-aligned bounding box of the 3D coordinates of \a cntnr.
         * \param cntnr The entity 3D container.
         * \param min The output vector receiving the per-axis minimum coordinates.
         * \param max The output vector receiving the per-axis maximum coordinates.
         * \param reset If \c true, \a min and \a max are reset before the calculation. If \c false, the box is extended to include the existing range.
         */
        CDPL_CHEM_API void calcBoundingBox(const Entity3DContainer& cntnr, Math::Vector3D& min, Math::Vector3D& max, bool reset = true);

        /**
         * \brief Tells whether all entities of \a cntnr lie within the axis-aligned box defined by \a min and \a max.
         * \param cntnr The entity 3D container.
         * \param min The per-axis minimum coordinates of the box.
         * \param max The per-axis maximum coordinates of the box.
         * \return \c true if every entity coordinate is inside the box, and \c false otherwise.
         */
        CDPL_CHEM_API bool insideBoundingBox(const Entity3DContainer& cntnr, const Math::Vector3D& min, const Math::Vector3D& max);

        /**
         * \brief Tells whether at least one entity of \a cntnr lies within the axis-aligned box defined by \a min and \a max.
         * \param cntnr The entity 3D container.
         * \param min The per-axis minimum coordinates of the box.
         * \param max The per-axis maximum coordinates of the box.
         * \return \c true if any entity coordinate is inside the box, and \c false otherwise.
         */
        CDPL_CHEM_API bool intersectsBoundingBox(const Entity3DContainer& cntnr, const Math::Vector3D& min, const Math::Vector3D& max);
    } // namespace Chem
} // namespace CDPL

#endif // CDPL_CHEM_ENTITY3DCONTAINERFUNCTIONS_HPP
