/* 
 * AtomPropertyDefault.hpp 
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
 * \brief Definition of constants in namespace CDPL::Chem::AtomPropertyDefault.
 */

#ifndef CDPL_CHEM_ATOMPROPERTYDEFAULT_HPP
#define CDPL_CHEM_ATOMPROPERTYDEFAULT_HPP

#include <string>
#include <cstddef>

#include "CDPL/Chem/APIPrefix.hpp"
#include "CDPL/Chem/StereoDescriptor.hpp"
#include "CDPL/Chem/MatchConstraintList.hpp"


namespace CDPL
{

    namespace Chem
    {

        /**
         * \brief Provides default values for built-in Chem::Atom properties.
         */
        namespace AtomPropertyDefault
        {

            /** \brief Default value for the Chem::AtomProperty::SYMBOL property. */
            extern CDPL_CHEM_API const std::string                        SYMBOL;
            /** \brief Default value for the Chem::AtomProperty::NAME property. */
            extern CDPL_CHEM_API const std::string                        NAME;
            /** \brief Default value for the Chem::AtomProperty::FORMAL_CHARGE property. */
            extern CDPL_CHEM_API const long                               FORMAL_CHARGE;
            /** \brief Default value for the Chem::AtomProperty::ISOTOPE property. */
            extern CDPL_CHEM_API const std::size_t                        ISOTOPE;
            /** \brief Default value for the Chem::AtomProperty::UNPAIRED_ELECTRON_COUNT property. */
            extern CDPL_CHEM_API const std::size_t                        UNPAIRED_ELECTRON_COUNT;
            /** \brief Default value for the Chem::AtomProperty::TYPE property. */
            extern CDPL_CHEM_API const unsigned int                       TYPE;
            /** \brief Default value for the Chem::AtomProperty::RADICAL_TYPE property. */
            extern CDPL_CHEM_API const unsigned int                       RADICAL_TYPE;
            /** \brief Default value for the Chem::AtomProperty::SYBYL_TYPE property. */
            extern CDPL_CHEM_API const unsigned int                       SYBYL_TYPE;
            /** \brief Default value for the Chem::AtomProperty::REACTION_CENTER_STATUS property. */
            extern CDPL_CHEM_API const unsigned int                       REACTION_CENTER_STATUS;
            /** \brief Default value for the Chem::AtomProperty::STEREO_DESCRIPTOR property. */
            extern CDPL_CHEM_API const StereoDescriptor                   STEREO_DESCRIPTOR;
            /** \brief Default value for the Chem::AtomProperty::COMPONENT_GROUP_ID property. */
            extern CDPL_CHEM_API const std::size_t                        COMPONENT_GROUP_ID;
            /** \brief Default value for the Chem::AtomProperty::ATOM_MAPPING_ID property. */
            extern CDPL_CHEM_API const std::size_t                        ATOM_MAPPING_ID;
            /** \brief Default value for the Chem::AtomProperty::MATCH_CONSTRAINTS property. */
            extern CDPL_CHEM_API const MatchConstraintList::SharedPointer MATCH_CONSTRAINTS;
            /** \brief Default value for the Chem::AtomProperty::MOL2_CHARGE property. */
            extern CDPL_CHEM_API const double                             MOL2_CHARGE;
            /** \brief Default value for the Chem::AtomProperty::MOL2_NAME property. */
            extern CDPL_CHEM_API const std::string                        MOL2_NAME;
            /** \brief Default value for the Chem::AtomProperty::MDL_DB_STEREO_CARE_FLAG property. */
            extern CDPL_CHEM_API const bool                               MDL_DB_STEREO_CARE_FLAG;
        } // namespace AtomPropertyDefault
    } // namespace Chem
} // namespace CDPL

#endif // CDPL_CHEM_ATOMPROPERTYDEFAULT_HPP
