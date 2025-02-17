/* 
 * ControlParameter.cpp 
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

#include "CDPL/Base/LookupKeyDefinition.hpp"

#include "CDPL/Vis/ControlParameter.hpp"


namespace CDPL 
{

    namespace Vis
    {
        
        namespace ControlParameter
        {

            CDPL_DEFINE_LOOKUP_KEY(OUTPUT_SCALING_FACTOR);
            
            CDPL_DEFINE_LOOKUP_KEY(VIEWPORT);
            CDPL_DEFINE_LOOKUP_KEY(SIZE_ADJUSTMENT);
            CDPL_DEFINE_LOOKUP_KEY(ALIGNMENT);

            CDPL_DEFINE_LOOKUP_KEY(BACKGROUND_BRUSH);

            CDPL_DEFINE_LOOKUP_KEY(REACTION_ARROW_STYLE);
            CDPL_DEFINE_LOOKUP_KEY(REACTION_ARROW_COLOR);
            CDPL_DEFINE_LOOKUP_KEY(REACTION_ARROW_LENGTH);
            CDPL_DEFINE_LOOKUP_KEY(REACTION_ARROW_HEAD_LENGTH);
            CDPL_DEFINE_LOOKUP_KEY(REACTION_ARROW_HEAD_WIDTH);
            CDPL_DEFINE_LOOKUP_KEY(REACTION_ARROW_SHAFT_WIDTH);
            CDPL_DEFINE_LOOKUP_KEY(REACTION_ARROW_LINE_WIDTH);

            CDPL_DEFINE_LOOKUP_KEY(REACTION_COMPONENT_LAYOUT);
            CDPL_DEFINE_LOOKUP_KEY(REACTION_COMPONENT_LAYOUT_DIRECTION);
            CDPL_DEFINE_LOOKUP_KEY(REACTION_COMPONENT_MARGIN);

            CDPL_DEFINE_LOOKUP_KEY(REACTION_AGENT_ALIGNMENT);
            CDPL_DEFINE_LOOKUP_KEY(REACTION_AGENT_LAYOUT);
            CDPL_DEFINE_LOOKUP_KEY(REACTION_AGENT_LAYOUT_DIRECTION);

            CDPL_DEFINE_LOOKUP_KEY(REACTION_PLUS_SIGN_COLOR);
            CDPL_DEFINE_LOOKUP_KEY(REACTION_PLUS_SIGN_SIZE);
            CDPL_DEFINE_LOOKUP_KEY(REACTION_PLUS_SIGN_LINE_WIDTH);

            CDPL_DEFINE_LOOKUP_KEY(SHOW_REACTION_REACTANTS);
            CDPL_DEFINE_LOOKUP_KEY(SHOW_REACTION_AGENTS);
            CDPL_DEFINE_LOOKUP_KEY(SHOW_REACTION_PRODUCTS);
            CDPL_DEFINE_LOOKUP_KEY(SHOW_REACTION_PLUS_SIGNS);

            CDPL_DEFINE_LOOKUP_KEY(ATOM_COLOR);
            CDPL_DEFINE_LOOKUP_KEY(ATOM_COLOR_TABLE);
            CDPL_DEFINE_LOOKUP_KEY(USE_CALCULATED_ATOM_COORDINATES);
            CDPL_DEFINE_LOOKUP_KEY(ATOM_LABEL_FONT);
            CDPL_DEFINE_LOOKUP_KEY(ATOM_LABEL_SIZE);
            CDPL_DEFINE_LOOKUP_KEY(SECONDARY_ATOM_LABEL_FONT);
            CDPL_DEFINE_LOOKUP_KEY(SECONDARY_ATOM_LABEL_SIZE);
            CDPL_DEFINE_LOOKUP_KEY(ATOM_LABEL_MARGIN);
            CDPL_DEFINE_LOOKUP_KEY(RADICAL_ELECTRON_DOT_SIZE);
            CDPL_DEFINE_LOOKUP_KEY(SHOW_EXPLICIT_HYDROGENS);
            CDPL_DEFINE_LOOKUP_KEY(SHOW_CARBONS);
            CDPL_DEFINE_LOOKUP_KEY(SHOW_CHARGES);
            CDPL_DEFINE_LOOKUP_KEY(SHOW_ISOTOPES);
            CDPL_DEFINE_LOOKUP_KEY(SHOW_HYDROGEN_COUNTS);
            CDPL_DEFINE_LOOKUP_KEY(SHOW_NON_CARBON_HYDROGEN_COUNTS);
            CDPL_DEFINE_LOOKUP_KEY(SHOW_ATOM_QUERY_INFOS);
            CDPL_DEFINE_LOOKUP_KEY(SHOW_ATOM_REACTION_INFOS);
            CDPL_DEFINE_LOOKUP_KEY(SHOW_RADICAL_ELECTRONS);
            CDPL_DEFINE_LOOKUP_KEY(SHOW_ATOM_CONFIGURATION_LABELS);
            CDPL_DEFINE_LOOKUP_KEY(SHOW_ATOM_CUSTOM_LABELS);
            CDPL_DEFINE_LOOKUP_KEY(ENABLE_ATOM_HIGHLIGHTING);
            CDPL_DEFINE_LOOKUP_KEY(ATOM_CONFIGURATION_LABEL_FONT);
            CDPL_DEFINE_LOOKUP_KEY(ATOM_CONFIGURATION_LABEL_SIZE);
            CDPL_DEFINE_LOOKUP_KEY(ATOM_CONFIGURATION_LABEL_COLOR);
            CDPL_DEFINE_LOOKUP_KEY(ATOM_CUSTOM_LABEL_FONT);
            CDPL_DEFINE_LOOKUP_KEY(ATOM_CUSTOM_LABEL_SIZE);
            CDPL_DEFINE_LOOKUP_KEY(ATOM_CUSTOM_LABEL_COLOR);
            CDPL_DEFINE_LOOKUP_KEY(ATOM_HIGHLIGHT_AREA_SIZE);
            CDPL_DEFINE_LOOKUP_KEY(ATOM_HIGHLIGHT_AREA_BRUSH);
            CDPL_DEFINE_LOOKUP_KEY(ATOM_HIGHLIGHT_AREA_OUTLINE_PEN);
            CDPL_DEFINE_LOOKUP_KEY(BREAK_ATOM_HIGHLIGHT_AREA_OUTLINE);

            CDPL_DEFINE_LOOKUP_KEY(HIGHLIGHT_AREA_OUTLINE_WIDTH);
            
            CDPL_DEFINE_LOOKUP_KEY(BOND_LENGTH);
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
            CDPL_DEFINE_LOOKUP_KEY(SHOW_BOND_REACTION_INFOS);
            CDPL_DEFINE_LOOKUP_KEY(SHOW_BOND_QUERY_INFOS);
            CDPL_DEFINE_LOOKUP_KEY(SHOW_STEREO_BONDS);
            CDPL_DEFINE_LOOKUP_KEY(SHOW_BOND_CONFIGURATION_LABELS);
            CDPL_DEFINE_LOOKUP_KEY(SHOW_BOND_CUSTOM_LABELS);
            CDPL_DEFINE_LOOKUP_KEY(ENABLE_BOND_HIGHLIGHTING);
            CDPL_DEFINE_LOOKUP_KEY(BOND_CONFIGURATION_LABEL_FONT);
            CDPL_DEFINE_LOOKUP_KEY(BOND_CONFIGURATION_LABEL_SIZE);
            CDPL_DEFINE_LOOKUP_KEY(BOND_CONFIGURATION_LABEL_COLOR);
            CDPL_DEFINE_LOOKUP_KEY(BOND_CUSTOM_LABEL_FONT);
            CDPL_DEFINE_LOOKUP_KEY(BOND_CUSTOM_LABEL_SIZE);
            CDPL_DEFINE_LOOKUP_KEY(BOND_CUSTOM_LABEL_COLOR);
            CDPL_DEFINE_LOOKUP_KEY(BOND_HIGHLIGHT_AREA_WIDTH);
            CDPL_DEFINE_LOOKUP_KEY(BOND_HIGHLIGHT_AREA_BRUSH);
            CDPL_DEFINE_LOOKUP_KEY(BOND_HIGHLIGHT_AREA_OUTLINE_PEN);

            CDPL_DEFINE_LOOKUP_KEY(GRID_VIEW_BORDER_PEN);
            CDPL_DEFINE_LOOKUP_KEY(GRID_VIEW_ROW_SEPARATOR_PEN);
            CDPL_DEFINE_LOOKUP_KEY(GRID_VIEW_COLUMN_SEPARATOR_PEN);
            CDPL_DEFINE_LOOKUP_KEY(GRID_VIEW_MARGIN);
            CDPL_DEFINE_LOOKUP_KEY(GRID_VIEW_CELL_PADDING);
            CDPL_DEFINE_LOOKUP_KEY(GRID_VIEW_TEXT_FONT);
            CDPL_DEFINE_LOOKUP_KEY(GRID_VIEW_TEXT_COLOR);
        }

        void initControlParameters() {}
    }
}
