/* 
 * ReactionProperty.hpp 
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
 * \brief Definition of constants in namespace CDPL::Chem::ReactionProperty.
 */

#ifndef CDPL_CHEM_REACTIONPROPERTY_HPP
#define CDPL_CHEM_REACTIONPROPERTY_HPP

#include "CDPL/Chem/APIPrefix.hpp"


namespace CDPL
{

    namespace Base
    {

        class LookupKey;
    }

    namespace Chem
    {

        /**
         * \brief Provides keys for built-in Chem::Reaction properties.
         */
        namespace ReactionProperty
        {

            extern CDPL_CHEM_API const Base::LookupKey NAME;
            extern CDPL_CHEM_API const Base::LookupKey COMMENT;
            extern CDPL_CHEM_API const Base::LookupKey TIMESTAMP;

            extern CDPL_CHEM_API const Base::LookupKey MATCH_EXPRESSION;
            extern CDPL_CHEM_API const Base::LookupKey MATCH_CONSTRAINTS;
            extern CDPL_CHEM_API const Base::LookupKey COMPONENT_GROUPS;
            extern CDPL_CHEM_API const Base::LookupKey ATOM_MAPPING;

            extern CDPL_CHEM_API const Base::LookupKey REACTION_DATA;

            extern CDPL_CHEM_API const Base::LookupKey MDL_USER_INITIALS;
            extern CDPL_CHEM_API const Base::LookupKey MDL_PROGRAM_NAME;
            extern CDPL_CHEM_API const Base::LookupKey MDL_REGISTRY_NUMBER;
            extern CDPL_CHEM_API const Base::LookupKey MDL_MOLECULE_RECORD;
            extern CDPL_CHEM_API const Base::LookupKey MDL_INTERNAL_REGISTRY_NUMBER;
            extern CDPL_CHEM_API const Base::LookupKey MDL_EXTERNAL_REGISTRY_NUMBER;
            extern CDPL_CHEM_API const Base::LookupKey MDL_RXN_FILE_VERSION;
        } // namespace ReactionProperty
    } // namespace Chem
} // namespace CDPL

#endif // CDPL_CHEM_REACTIONPROPERTY_HPP
