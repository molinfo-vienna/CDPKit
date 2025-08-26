/* 
 * ControlParameterDefaultExport.cpp 
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


#include <boost/python.hpp>

#include "CDPL/Vis/ControlParameterDefault.hpp"
#include "CDPL/Vis/Color.hpp"
#include "CDPL/Vis/Brush.hpp"
#include "CDPL/Vis/Pen.hpp"
#include "CDPL/Vis/Font.hpp"
#include "CDPL/Vis/SizeSpecification.hpp"
#include "CDPL/Vis/Rectangle2D.hpp"

#include "NamespaceExports.hpp"


namespace 
{

    struct ControlParameterDefault {};
}


void CDPLPythonVis::exportControlParameterDefaults()
{
    using namespace boost;
    using namespace CDPL;

    python::class_<ControlParameterDefault, boost::noncopyable>("ControlParameterDefault", python::no_init)
        .def_readonly("OUTPUT_SCALING_FACTOR", &Vis::ControlParameterDefault::OUTPUT_SCALING_FACTOR)
        .def_readonly("VIEWPORT", &Vis::ControlParameterDefault::VIEWPORT)
        .def_readonly("SIZE_ADJUSTMENT", &Vis::ControlParameterDefault::SIZE_ADJUSTMENT)
        .def_readonly("ALIGNMENT", &Vis::ControlParameterDefault::ALIGNMENT)
        .def_readonly("BACKGROUND_BRUSH", &Vis::ControlParameterDefault::BACKGROUND_BRUSH)
        .def_readonly("REACTION_ARROW_STYLE", &Vis::ControlParameterDefault::REACTION_ARROW_STYLE)
        .def_readonly("REACTION_ARROW_COLOR", &Vis::ControlParameterDefault::REACTION_ARROW_COLOR)
        .def_readonly("REACTION_ARROW_LENGTH", &Vis::ControlParameterDefault::REACTION_ARROW_LENGTH)
        .def_readonly("REACTION_ARROW_HEAD_LENGTH", &Vis::ControlParameterDefault::REACTION_ARROW_HEAD_LENGTH)
        .def_readonly("REACTION_ARROW_HEAD_WIDTH", &Vis::ControlParameterDefault::REACTION_ARROW_HEAD_WIDTH)
        .def_readonly("REACTION_ARROW_SHAFT_WIDTH", &Vis::ControlParameterDefault::REACTION_ARROW_SHAFT_WIDTH)
        .def_readonly("REACTION_ARROW_LINE_WIDTH", &Vis::ControlParameterDefault::REACTION_ARROW_LINE_WIDTH)
        .def_readonly("REACTION_COMPONENT_LAYOUT", &Vis::ControlParameterDefault::REACTION_COMPONENT_LAYOUT)
        .def_readonly("REACTION_COMPONENT_LAYOUT_DIRECTION", &Vis::ControlParameterDefault::REACTION_COMPONENT_LAYOUT_DIRECTION)
        .def_readonly("REACTION_COMPONENT_MARGIN", &Vis::ControlParameterDefault::REACTION_COMPONENT_MARGIN)
        .def_readonly("SHOW_REACTION_REACTANTS", &Vis::ControlParameterDefault::SHOW_REACTION_REACTANTS)    
        .def_readonly("SHOW_REACTION_AGENTS", &Vis::ControlParameterDefault::SHOW_REACTION_AGENTS)    
        .def_readonly("SHOW_REACTION_PRODUCTS", &Vis::ControlParameterDefault::SHOW_REACTION_PRODUCTS)    
        .def_readonly("REACTION_AGENT_ALIGNMENT", &Vis::ControlParameterDefault::REACTION_AGENT_ALIGNMENT)
        .def_readonly("REACTION_AGENT_LAYOUT", &Vis::ControlParameterDefault::REACTION_AGENT_LAYOUT)
        .def_readonly("REACTION_AGENT_LAYOUT_DIRECTION", &Vis::ControlParameterDefault::REACTION_AGENT_LAYOUT_DIRECTION)
        .def_readonly("REACTION_PLUS_SIGN_COLOR", &Vis::ControlParameterDefault::REACTION_PLUS_SIGN_COLOR)
        .def_readonly("REACTION_PLUS_SIGN_SIZE", &Vis::ControlParameterDefault::REACTION_PLUS_SIGN_SIZE)
        .def_readonly("REACTION_PLUS_SIGN_LINE_WIDTH", &Vis::ControlParameterDefault::REACTION_PLUS_SIGN_LINE_WIDTH)
        .def_readonly("SHOW_REACTION_PLUS_SIGNS", &Vis::ControlParameterDefault::SHOW_REACTION_PLUS_SIGNS)
        .def_readonly("USE_CALCULATED_ATOM_COORDINATES", &Vis::ControlParameterDefault::USE_CALCULATED_ATOM_COORDINATES)
        .def_readonly("HIGHLIGHT_AREA_OUTLINE_WIDTH", &Vis::ControlParameterDefault::HIGHLIGHT_AREA_OUTLINE_WIDTH)
        .def_readonly("ATOM_COLOR", &Vis::ControlParameterDefault::ATOM_COLOR)
        .def_readonly("ATOM_LABEL_FONT", &Vis::ControlParameterDefault::ATOM_LABEL_FONT)
        .def_readonly("ATOM_LABEL_SIZE", &Vis::ControlParameterDefault::ATOM_LABEL_SIZE)
        .def_readonly("SECONDARY_ATOM_LABEL_FONT", &Vis::ControlParameterDefault::SECONDARY_ATOM_LABEL_FONT)
        .def_readonly("SECONDARY_ATOM_LABEL_SIZE", &Vis::ControlParameterDefault::SECONDARY_ATOM_LABEL_SIZE)
        .def_readonly("ATOM_LABEL_MARGIN", &Vis::ControlParameterDefault::ATOM_LABEL_MARGIN)
        .def_readonly("ATOM_HIGHLIGHT_AREA_SIZE", &Vis::ControlParameterDefault::ATOM_HIGHLIGHT_AREA_SIZE)
        .def_readonly("ATOM_HIGHLIGHT_AREA_BRUSH", &Vis::ControlParameterDefault::ATOM_HIGHLIGHT_AREA_BRUSH)
        .def_readonly("ATOM_HIGHLIGHT_AREA_OUTLINE_PEN", &Vis::ControlParameterDefault::ATOM_HIGHLIGHT_AREA_OUTLINE_PEN)
        .def_readonly("BREAK_ATOM_HIGHLIGHT_AREA_OUTLINE", &Vis::ControlParameterDefault::BREAK_ATOM_HIGHLIGHT_AREA_OUTLINE)
        .def_readonly("RADICAL_ELECTRON_DOT_SIZE", &Vis::ControlParameterDefault::RADICAL_ELECTRON_DOT_SIZE)
        .def_readonly("SHOW_CARBONS", &Vis::ControlParameterDefault::SHOW_CARBONS)
        .def_readonly("SHOW_EXPLICIT_HYDROGENS", &Vis::ControlParameterDefault::SHOW_EXPLICIT_HYDROGENS)
        .def_readonly("SHOW_CHARGES", &Vis::ControlParameterDefault::SHOW_CHARGES)
        .def_readonly("SHOW_ISOTOPES", &Vis::ControlParameterDefault::SHOW_ISOTOPES)
        .def_readonly("SHOW_HYDROGEN_COUNTS", &Vis::ControlParameterDefault::SHOW_HYDROGEN_COUNTS)
        .def_readonly("SHOW_NON_CARBON_HYDROGEN_COUNTS", &Vis::ControlParameterDefault::SHOW_NON_CARBON_HYDROGEN_COUNTS)
        .def_readonly("SHOW_ATOM_QUERY_INFOS", &Vis::ControlParameterDefault::SHOW_ATOM_QUERY_INFOS)
        .def_readonly("SHOW_ATOM_REACTION_INFOS", &Vis::ControlParameterDefault::SHOW_ATOM_REACTION_INFOS)
        .def_readonly("SHOW_RADICAL_ELECTRONS", &Vis::ControlParameterDefault::SHOW_RADICAL_ELECTRONS)
        .def_readonly("SHOW_BOND_REACTION_INFOS", &Vis::ControlParameterDefault::SHOW_BOND_REACTION_INFOS)
        .def_readonly("SHOW_BOND_QUERY_INFOS", &Vis::ControlParameterDefault::SHOW_BOND_QUERY_INFOS)
        .def_readonly("SHOW_STEREO_BONDS", &Vis::ControlParameterDefault::SHOW_STEREO_BONDS)
        .def_readonly("SHOW_ATOM_CONFIGURATION_LABELS", &Vis::ControlParameterDefault::SHOW_ATOM_CONFIGURATION_LABELS)
        .def_readonly("SHOW_ATOM_CUSTOM_LABELS", &Vis::ControlParameterDefault::SHOW_ATOM_CUSTOM_LABELS)
        .def_readonly("SHOW_BOND_CONFIGURATION_LABELS", &Vis::ControlParameterDefault::SHOW_BOND_CONFIGURATION_LABELS)
        .def_readonly("SHOW_BOND_CUSTOM_LABELS", &Vis::ControlParameterDefault::SHOW_BOND_CUSTOM_LABELS)
        .def_readonly("ENABLE_ATOM_HIGHLIGHTING", &Vis::ControlParameterDefault::ENABLE_ATOM_HIGHLIGHTING)
        .def_readonly("ENABLE_BOND_HIGHLIGHTING", &Vis::ControlParameterDefault::ENABLE_BOND_HIGHLIGHTING)
        .def_readonly("BOND_COLOR", &Vis::ControlParameterDefault::BOND_COLOR)
        .def_readonly("BOND_LENGTH", &Vis::ControlParameterDefault::BOND_LENGTH)
        .def_readonly("BOND_LINE_WIDTH", &Vis::ControlParameterDefault::BOND_LINE_WIDTH)
        .def_readonly("BOND_LINE_SPACING", &Vis::ControlParameterDefault::BOND_LINE_SPACING)
        .def_readonly("STEREO_BOND_WEDGE_WIDTH", &Vis::ControlParameterDefault::STEREO_BOND_WEDGE_WIDTH)
        .def_readonly("STEREO_BOND_HASH_SPACING", &Vis::ControlParameterDefault::STEREO_BOND_HASH_SPACING)
        .def_readonly("REACTION_CENTER_LINE_LENGTH", &Vis::ControlParameterDefault::REACTION_CENTER_LINE_LENGTH)
        .def_readonly("REACTION_CENTER_LINE_SPACING", &Vis::ControlParameterDefault::REACTION_CENTER_LINE_SPACING)
        .def_readonly("DOUBLE_BOND_TRIM_LENGTH", &Vis::ControlParameterDefault::DOUBLE_BOND_TRIM_LENGTH)
        .def_readonly("TRIPLE_BOND_TRIM_LENGTH", &Vis::ControlParameterDefault::TRIPLE_BOND_TRIM_LENGTH)
        .def_readonly("BOND_LABEL_FONT", &Vis::ControlParameterDefault::BOND_LABEL_FONT)
        .def_readonly("BOND_LABEL_SIZE", &Vis::ControlParameterDefault::BOND_LABEL_SIZE)
        .def_readonly("BOND_LABEL_MARGIN", &Vis::ControlParameterDefault::BOND_LABEL_MARGIN)
        .def_readonly("ATOM_CONFIGURATION_LABEL_FONT", &Vis::ControlParameterDefault::ATOM_CONFIGURATION_LABEL_FONT)
        .def_readonly("ATOM_CONFIGURATION_LABEL_SIZE", &Vis::ControlParameterDefault::ATOM_CONFIGURATION_LABEL_SIZE)
        .def_readonly("ATOM_CONFIGURATION_LABEL_COLOR", &Vis::ControlParameterDefault::ATOM_CONFIGURATION_LABEL_COLOR)
        .def_readonly("ATOM_CUSTOM_LABEL_FONT", &Vis::ControlParameterDefault::ATOM_CUSTOM_LABEL_FONT)
        .def_readonly("ATOM_CUSTOM_LABEL_SIZE", &Vis::ControlParameterDefault::ATOM_CUSTOM_LABEL_SIZE)
        .def_readonly("ATOM_CUSTOM_LABEL_COLOR", &Vis::ControlParameterDefault::ATOM_CUSTOM_LABEL_COLOR)
        .def_readonly("BOND_CONFIGURATION_LABEL_FONT", &Vis::ControlParameterDefault::BOND_CONFIGURATION_LABEL_FONT)
        .def_readonly("BOND_CONFIGURATION_LABEL_SIZE", &Vis::ControlParameterDefault::BOND_CONFIGURATION_LABEL_SIZE)
        .def_readonly("BOND_CONFIGURATION_LABEL_COLOR", &Vis::ControlParameterDefault::BOND_CONFIGURATION_LABEL_COLOR)
        .def_readonly("BOND_CUSTOM_LABEL_FONT", &Vis::ControlParameterDefault::BOND_CUSTOM_LABEL_FONT)
        .def_readonly("BOND_CUSTOM_LABEL_SIZE", &Vis::ControlParameterDefault::BOND_CUSTOM_LABEL_SIZE)
        .def_readonly("BOND_CUSTOM_LABEL_COLOR", &Vis::ControlParameterDefault::BOND_CUSTOM_LABEL_COLOR)
        .def_readonly("BOND_HIGHLIGHT_AREA_WIDTH", &Vis::ControlParameterDefault::BOND_HIGHLIGHT_AREA_WIDTH)
        .def_readonly("BOND_HIGHLIGHT_AREA_BRUSH", &Vis::ControlParameterDefault::BOND_HIGHLIGHT_AREA_BRUSH)
        .def_readonly("BOND_HIGHLIGHT_AREA_OUTLINE_PEN", &Vis::ControlParameterDefault::BOND_HIGHLIGHT_AREA_OUTLINE_PEN)
        .def_readonly("GRID_VIEW_BORDER_PEN", &Vis::ControlParameterDefault::GRID_VIEW_BORDER_PEN)
        .def_readonly("GRID_VIEW_ROW_SEPARATOR_PEN", &Vis::ControlParameterDefault::GRID_VIEW_ROW_SEPARATOR_PEN)
        .def_readonly("GRID_VIEW_COLUMN_SEPARATOR_PEN", &Vis::ControlParameterDefault::GRID_VIEW_COLUMN_SEPARATOR_PEN)
        .def_readonly("GRID_VIEW_MARGIN", &Vis::ControlParameterDefault::GRID_VIEW_MARGIN)
        .def_readonly("GRID_VIEW_CELL_PADDING", &Vis::ControlParameterDefault::GRID_VIEW_CELL_PADDING)
        .def_readonly("GRID_VIEW_TEXT_FONT", &Vis::ControlParameterDefault::GRID_VIEW_TEXT_FONT)
        .def_readonly("GRID_VIEW_TEXT_COLOR", &Vis::ControlParameterDefault::GRID_VIEW_TEXT_COLOR)
        .def_readonly("FEATURE_COLOR_TABLE", &Vis::ControlParameterDefault::FEATURE_COLOR_TABLE)
        ;
}
