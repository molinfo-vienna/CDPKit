/* 
 * ControlParameterDefault.cpp 
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

#include "CDPL/Vis/ControlParameterDefault.hpp"
#include "CDPL/Vis/Color.hpp"
#include "CDPL/Vis/Font.hpp"
#include "CDPL/Vis/Pen.hpp"
#include "CDPL/Vis/Brush.hpp"
#include "CDPL/Vis/Rectangle2D.hpp"
#include "CDPL/Vis/Alignment.hpp"
#include "CDPL/Vis/SizeSpecification.hpp"
#include "CDPL/Vis/SizeAdjustment.hpp"
#include "CDPL/Vis/LayoutDirection.hpp"
#include "CDPL/Vis/LayoutStyle.hpp"
#include "CDPL/Vis/ArrowStyle.hpp"


namespace CDPL
{

    namespace Vis
    {

        namespace ControlParameterDefault
        {

            const Rectangle2D               VIEWPORT                             = Rectangle2D();
            const unsigned int              SIZE_ADJUSTMENT                      = SizeAdjustment::IF_REQUIRED;
            const unsigned int              ALIGNMENT                            = Alignment::CENTER;
            const Color                     BACKGROUND_COLOR                     = Color(0, 0, 0, 0);

            const unsigned int              REACTION_ARROW_STYLE                 = ArrowStyle::REACTION_SOLID;
            const Color                     REACTION_ARROW_COLOR                 = Color(0, 0, 0);
            const SizeSpecification         REACTION_ARROW_LENGTH                = SizeSpecification(35.0, true, true, true);
            const SizeSpecification         REACTION_ARROW_HEAD_LENGTH           = SizeSpecification(8.0, false, true, true);
            const SizeSpecification         REACTION_ARROW_HEAD_WIDTH            = SizeSpecification(5.0, false, true, true);
            const SizeSpecification         REACTION_ARROW_SHAFT_WIDTH           = SizeSpecification(0.0, false, true, true);
            const SizeSpecification         REACTION_ARROW_LINE_WIDTH            = SizeSpecification(1.0, false, true, true);
            const unsigned int              REACTION_COMPONENT_LAYOUT            = LayoutStyle::PACKED;
            const unsigned int              REACTION_COMPONENT_LAYOUT_DIRECTION  = LayoutDirection::HORIZONTAL;
            const SizeSpecification         REACTION_COMPONENT_MARGIN            = SizeSpecification(5.0, false, true, true);
            const bool                      SHOW_REACTION_REACTANTS              = true;
            const bool                      SHOW_REACTION_AGENTS                 = true;
            const bool                      SHOW_REACTION_PRODUCTS               = true;
            const unsigned int              REACTION_AGENT_ALIGNMENT             = Alignment::V_CENTER;
            const unsigned int              REACTION_AGENT_LAYOUT                = LayoutStyle::LINEAR;
            const unsigned int              REACTION_AGENT_LAYOUT_DIRECTION      = LayoutDirection::HORIZONTAL;
            const Color                     REACTION_PLUS_SIGN_COLOR             = Color(0, 0, 0);
            const SizeSpecification         REACTION_PLUS_SIGN_SIZE              = SizeSpecification(10.0, false, true, true);
            const SizeSpecification         REACTION_PLUS_SIGN_LINE_WIDTH        = SizeSpecification(3.0, false, true, true);
            const bool                      SHOW_REACTION_PLUS_SIGNS             = true;

            const Color                     ATOM_COLOR                           = Color(0, 0, 0);        
            const ColorTable::SharedPointer ATOM_COLOR_TABLE                     = ColorTable::SharedPointer(new ColorTable());
            const bool                      USE_CALCULATED_ATOM_COORDINATES      = false;
            const Font                      ATOM_LABEL_FONT                      = Font();
            const SizeSpecification         ATOM_LABEL_SIZE                      = SizeSpecification(10.0, false, false, true);
            const Font                      SECONDARY_ATOM_LABEL_FONT            = Font();
            const SizeSpecification         SECONDARY_ATOM_LABEL_SIZE            = SizeSpecification(6.0, false, false, true);
            const SizeSpecification         ATOM_LABEL_MARGIN                    = SizeSpecification(2.0, false, false, true);
            const SizeSpecification         RADICAL_ELECTRON_DOT_SIZE            = SizeSpecification(1.0, false, false, true);
            const SizeSpecification         ATOM_HIGHLIGHT_AREA_SIZE             = SizeSpecification(16.0, false, false, true);
            const Brush                     ATOM_HIGHLIGHT_AREA_BRUSH            = Brush(Color(0.8, 0.8, 1.0));
            const Pen                       ATOM_HIGHLIGHT_AREA_OUTLINE_PEN      = Pen(Color(0.6, 0.6, 0.75));
            const bool                      BREAK_ATOM_HIGHLIGHT_AREA_OUTLINE    = false;
            const bool                      SHOW_CARBONS                         = false;
            const bool                      SHOW_EXPLICIT_HYDROGENS              = false;
            const bool                      SHOW_CHARGES                         = true;
            const bool                      SHOW_ISOTOPES                        = true;
            const bool                      SHOW_HYDROGEN_COUNTS                 = false;
            const bool                      SHOW_NON_CARBON_HYDROGEN_COUNTS      = true;
            const bool                      SHOW_ATOM_QUERY_INFOS                = true;
            const bool                      SHOW_ATOM_REACTION_INFOS             = true;
            const bool                      SHOW_RADICAL_ELECTRONS               = true;
            const bool                      SHOW_ATOM_CONFIGURATION_LABELS       = false;
            const bool                      SHOW_ATOM_CUSTOM_LABELS              = true;
            const bool                      ENABLE_ATOM_HIGHLIGHTING             = true;
            const Font                      ATOM_CONFIGURATION_LABEL_FONT        = Font("", 8.0, false, true);
            const SizeSpecification         ATOM_CONFIGURATION_LABEL_SIZE        = SizeSpecification(8.0, false, false, true);
            const Color                     ATOM_CONFIGURATION_LABEL_COLOR       = Color(0, 0, 0);
            const Font                      ATOM_CUSTOM_LABEL_FONT               = Font("", 8.0, false, false);
            const SizeSpecification         ATOM_CUSTOM_LABEL_SIZE               = SizeSpecification(8.0, false, false, true);
            const Color                     ATOM_CUSTOM_LABEL_COLOR              = Color(0, 0, 0);

            const SizeSpecification HIGHLIGHT_AREA_OUTLINE_WIDTH    = SizeSpecification(1.0, false, false, true);
            
            const Color             BOND_COLOR                      = Color(0, 0, 0);
            const SizeSpecification BOND_LENGTH                     = SizeSpecification(30.0);
            const SizeSpecification BOND_LINE_WIDTH                 = SizeSpecification(1.0, false, false, true);
            const SizeSpecification BOND_LINE_SPACING               = SizeSpecification(0.15, true, true, true);
            const SizeSpecification STEREO_BOND_WEDGE_WIDTH         = SizeSpecification(0.15, true, true, true);
            const SizeSpecification STEREO_BOND_HASH_SPACING        = SizeSpecification(0.1, true, true, true);
            const SizeSpecification REACTION_CENTER_LINE_LENGTH     = SizeSpecification(0.4, true, true, true);
            const SizeSpecification REACTION_CENTER_LINE_SPACING    = SizeSpecification(0.1, true, true, true);
            const SizeSpecification DOUBLE_BOND_TRIM_LENGTH         = SizeSpecification(0.1, true, true, true);
            const SizeSpecification TRIPLE_BOND_TRIM_LENGTH         = SizeSpecification(0.1, true, true, true);
            const Font              BOND_LABEL_FONT                 = Font();
            const SizeSpecification BOND_LABEL_SIZE                 = SizeSpecification(8.0, false, false, true);
            const SizeSpecification BOND_LABEL_MARGIN               = SizeSpecification(2.0, false, false, true);
            const SizeSpecification BOND_HIGHLIGHT_AREA_WIDTH       = SizeSpecification(12.0, false, false, true);
            const Brush             BOND_HIGHLIGHT_AREA_BRUSH       = Brush(Color(0.8, 0.8, 1.0));
            const Pen               BOND_HIGHLIGHT_AREA_OUTLINE_PEN = Pen(Color(0.6, 0.6, 0.75));
            const bool              SHOW_BOND_REACTION_INFOS        = true;
            const bool              SHOW_BOND_QUERY_INFOS           = true;
            const bool              SHOW_STEREO_BONDS               = true;
            const bool              SHOW_BOND_CONFIGURATION_LABELS  = false;
            const bool              SHOW_BOND_CUSTOM_LABELS         = true;
            const bool              ENABLE_BOND_HIGHLIGHTING        = true;
            const Font              BOND_CONFIGURATION_LABEL_FONT   = Font("", 8.0, false, true);
            const SizeSpecification BOND_CONFIGURATION_LABEL_SIZE   = SizeSpecification(8.0, false, false, true);
            const Color             BOND_CONFIGURATION_LABEL_COLOR  = Color(0, 0, 0);
            const Font              BOND_CUSTOM_LABEL_FONT          = Font("", 8.0, false, false);
            const SizeSpecification BOND_CUSTOM_LABEL_SIZE          = SizeSpecification(8.0, false, false, true);
            const Color             BOND_CUSTOM_LABEL_COLOR         = Color(0, 0, 0);

        } // namespace ControlParameterDefault

        void initControlParameterDefaults() {}
    }
}
