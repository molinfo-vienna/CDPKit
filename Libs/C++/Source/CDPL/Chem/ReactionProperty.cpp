/* 
 * ReactionProperty.cpp 
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


#include "StaticInit.hpp"

#include "CDPL/Chem/ReactionProperty.hpp"
#include "CDPL/Base/LookupKeyDefinition.hpp"


namespace CDPL 
{

    namespace Chem
    {

        namespace ReactionProperty
        {

            CDPL_DEFINE_LOOKUP_KEY(NAME);
            CDPL_DEFINE_LOOKUP_KEY(COMMENT);
            CDPL_DEFINE_LOOKUP_KEY(TIMESTAMP);

            CDPL_DEFINE_LOOKUP_KEY(MATCH_EXPRESSION);
            CDPL_DEFINE_LOOKUP_KEY(MATCH_CONSTRAINTS);
            CDPL_DEFINE_LOOKUP_KEY(COMPONENT_GROUPS);
            CDPL_DEFINE_LOOKUP_KEY(ATOM_MAPPING);

            CDPL_DEFINE_LOOKUP_KEY(REACTION_DATA);

            CDPL_DEFINE_LOOKUP_KEY(MDL_USER_INITIALS);
            CDPL_DEFINE_LOOKUP_KEY(MDL_PROGRAM_NAME);
            CDPL_DEFINE_LOOKUP_KEY(MDL_REGISTRY_NUMBER);
            CDPL_DEFINE_LOOKUP_KEY(MDL_MOLECULE_RECORD);
            CDPL_DEFINE_LOOKUP_KEY(MDL_INTERNAL_REGISTRY_NUMBER);
            CDPL_DEFINE_LOOKUP_KEY(MDL_EXTERNAL_REGISTRY_NUMBER);
            CDPL_DEFINE_LOOKUP_KEY(MDL_RXN_FILE_VERSION);
        }
    
        void initReactionProperties() {}
    }
}
