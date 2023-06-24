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


        CDPL_CHEM_API void calcGeometricalDistanceMatrix(const Entity3DContainer& cntnr, Math::DMatrix& mtx);


        CDPL_CHEM_API void get3DCoordinates(const Entity3DContainer& cntnr, Math::Vector3DArray& coords, bool append = false);

        CDPL_CHEM_API void set3DCoordinates(Entity3DContainer& cntnr, const Math::Vector3DArray& coords);

        CDPL_CHEM_API void transform3DCoordinates(Entity3DContainer& cntnr, const Math::Matrix4D& mtx);


        CDPL_CHEM_API bool calcCentroid(const Entity3DContainer& cntnr, Math::Vector3D& ctr);

        CDPL_CHEM_API void calcBoundingBox(const Entity3DContainer& cntnr, Math::Vector3D& min, Math::Vector3D& max, bool reset = true);

        CDPL_CHEM_API bool insideBoundingBox(const Entity3DContainer& cntnr, const Math::Vector3D& min, const Math::Vector3D& max);

        CDPL_CHEM_API bool intersectsBoundingBox(const Entity3DContainer& cntnr, const Math::Vector3D& min, const Math::Vector3D& max);
    } // namespace Chem
} // namespace CDPL

#endif // CDPL_CHEM_ENTITY3DCONTAINERFUNCTIONS_HPP
