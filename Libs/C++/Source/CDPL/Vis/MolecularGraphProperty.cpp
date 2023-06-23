/* 
 * MolecularGraphProperty.cpp 
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

#include "CDPL/Vis/MolecularGraphProperty.hpp"

#include "CDPL/Base/LookupKeyDefinition.hpp"


namespace CDPL
{

    namespace Vis
    {
    
        namespace MolecularGraphProperty
        {

            CDPL_DEFINE_LOOKUP_KEY(ATOM_COLOR_TABLE);
            CDPL_DEFINE_LOOKUP_KEY(ATOM_COLOR);
            CDPL_DEFINE_LOOKUP_KEY(ATOM_LABEL_FONT);
            CDPL_DEFINE_LOOKUP_KEY(ATOM_LABEL_SIZE);
            CDPL_DEFINE_LOOKUP_KEY(SECONDARY_ATOM_LABEL_FONT);
            CDPL_DEFINE_LOOKUP_KEY(SECONDARY_ATOM_LABEL_SIZE);
            CDPL_DEFINE_LOOKUP_KEY(ATOM_LABEL_MARGIN);
            CDPL_DEFINE_LOOKUP_KEY(RADICAL_ELECTRON_DOT_SIZE);
            CDPL_DEFINE_LOOKUP_KEY(BOND_COLOR);
            CDPL_DEFINE_LOOKUP_KEY(BOND_LINE_WIDTH);
            CDPL_DEFINE_LOOKUP_KEY(BOND_LINE_SPACING);
            CDPL_DEFINE_LOOKUP_KEY(STEREO_BOND_WEDGE_WIDTH);
            CDPL_DEFINE_LOOKUP_KEY(STEREO_BOND_HASH_SPACING);
            CDPL_DEFINE_LOOKUP_KEY(REACTION_CENTER_LINE_LENGTH);
            CDPL_DEFINE_LOOKUP_KEY(REACTION_CENTER_LINE_SPACING);
            CDPL_DEFINE_LOOKUP_KEY(DOUBLE_BOND_TRIM_LENGTH);
            CDPL_DEFINE_LOOKUP_KEY(TRIPLE_BOND_TRIM_LENGTH);
            CDPL_DEFINE_LOOKUP_KEY(BOND_LABEL_FONT);
            CDPL_DEFINE_LOOKUP_KEY(BOND_LABEL_SIZE);
            CDPL_DEFINE_LOOKUP_KEY(BOND_LABEL_MARGIN);
        }

        void initMolecularGraphProperties() {}
    }
}
