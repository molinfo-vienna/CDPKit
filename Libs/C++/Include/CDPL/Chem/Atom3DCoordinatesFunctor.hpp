/* 
 * Atom3DCoordinatesFunctor.hpp 
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
 * \brief Definition of class CDPL::Chem::Atom3DCoordinatesFunctor.
 */

#ifndef CDPL_CHEM_ATOM3DCOORDINATESFUNCTOR_HPP
#define CDPL_CHEM_ATOM3DCOORDINATESFUNCTOR_HPP

#include "CDPL/Chem/APIPrefix.hpp"
#include "CDPL/Math/Vector.hpp"


namespace CDPL
{

    namespace Chem
    {

        class Atom;

        /**
         * \brief Atom3DCoordinatesFunctor.
         */
        struct CDPL_CHEM_API Atom3DCoordinatesFunctor
        {

          public:
            /**
             * \brief Returns the 3D-coordinates of the argument atom.
             * \param atom The atom.
             * \return The 3D-coordinates of the atom.
             * \see Chem::get3DCoordinates(const Atom&)
             */
            const Math::Vector3D& operator()(const Atom& atom) const;
        };
    } // namespace Chem
} // namespace CDPL

#endif // CDPL_CHEM_ATOM3DCOORDINATESFUNCTOR_HPP
