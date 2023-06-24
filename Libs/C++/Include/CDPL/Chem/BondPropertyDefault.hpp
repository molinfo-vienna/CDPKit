/* 
 * BondPropertyDefault.hpp 
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
 * \brief Definition of constants in namespace CDPL::Chem::BondPropertyDefault.
 */

#ifndef CDPL_CHEM_BONDPROPERTYDEFAULT_HPP
#define CDPL_CHEM_BONDPROPERTYDEFAULT_HPP

#include <cstddef>

#include "CDPL/Chem/APIPrefix.hpp"
#include "CDPL/Chem/StereoDescriptor.hpp"
#include "CDPL/Chem/MatchConstraintList.hpp"


namespace CDPL
{

    namespace Chem
    {

        /**
         * \brief Provides default values for built-in Chem::Bond properties.
         */
        namespace BondPropertyDefault
        {

            extern CDPL_CHEM_API const std::size_t      ORDER;
            extern CDPL_CHEM_API const unsigned int     DIRECTION;
            extern CDPL_CHEM_API const unsigned int     STEREO_2D_FLAG;
            extern CDPL_CHEM_API const StereoDescriptor STEREO_DESCRIPTOR;
            extern CDPL_CHEM_API const unsigned int     REACTION_CENTER_STATUS;
            extern CDPL_CHEM_API const unsigned int     SYBYL_TYPE;
            extern CDPL_CHEM_API const MatchConstraintList::SharedPointer MATCH_CONSTRAINTS;
        } // namespace BondPropertyDefault
    } // namespace Chem
} // namespace CDPL

#endif // CDPL_CHEM_BONDPROPERTYDEFAULT_HPP
