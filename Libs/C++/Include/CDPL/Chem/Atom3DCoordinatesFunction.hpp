/* 
 * Atom3DCoordinatesFunction.hpp 
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
 * \brief Type declaration of a generic wrapper class for storing user-defined Chem::Atom 3D-coordinates functions.
 */

#ifndef CDPL_CHEM_ATOM3DCOORDINATESFUNCTION_HPP
#define CDPL_CHEM_ATOM3DCOORDINATESFUNCTION_HPP

#include <functional>

#include "CDPL/Math/Vector.hpp"


namespace CDPL
{

    namespace Chem
    {

        class Atom;

        /**
         * \brief A generic wrapper class used to store a user-defined Chem::Atom 3D-coordinates function.
         */
        typedef std::function<const Math::Vector3D&(const Chem::Atom&)> Atom3DCoordinatesFunction;
    } // namespace Chem
} // namespace CDPL

#endif // CDPL_CHEM_ATOM3DCOORDINATESFUNCTION_HPP
