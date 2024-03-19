/* 
 * ControlParameterExport.cpp 
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

#include "CDPL/Vis/ControlParameter.hpp"
#include "CDPL/Base/LookupKey.hpp"

#include "NamespaceExports.hpp"


namespace 
{

    struct ControlParameter {};
}


void CDPLPythonVis::exportControlParameters()
{
    using namespace boost;
    using namespace CDPL;

    python::class_<ControlParameter, boost::noncopyable>("ControlParameter", python::no_init)
        .def_readonly("ALIGNMENT", &Vis::ControlParameter::ALIGNMENT)
        .def_readonly("ATOM_COLOR", &Vis::ControlParameter::ATOM_COLOR)
        .def_readonly("ATOM_COLOR_TABLE", &Vis::ControlParameter::ATOM_COLOR_TABLE)
        .def_readonly("RADICAL_ELECTRON_DOT_SIZE", &Vis::ControlParameter::RADICAL_ELECTRON_DOT_SIZE)
        .def_readonly("ATOM_LABEL_FONT", &Vis::ControlParameter::ATOM_LABEL_FONT)
        .def_readonly("ATOM_LABEL_MARGIN", &Vis::ControlParameter::ATOM_LABEL_MARGIN)
        .def_readonly("ATOM_LABEL_SIZE", &Vis::ControlParameter::ATOM_LABEL_SIZE)
        .def_readonly("SECONDARY_ATOM_LABEL_FONT", &Vis::ControlParameter::SECONDARY_ATOM_LABEL_FONT)
        .def_readonly("SECONDARY_ATOM_LABEL_SIZE", &Vis::ControlParameter::SECONDARY_ATOM_LABEL_SIZE)
        .def_readonly("ATOM_HIGHLIGHT_AREA_SIZE", &Vis::ControlParameter::ATOM_HIGHLIGHT_AREA_SIZE)
        .def_readonly("ATOM_HIGHLIGHT_AREA_BRUSH", &Vis::ControlParameter::ATOM_HIGHLIGHT_AREA_BRUSH)
        .def_readonly("ATOM_HIGHLIGHT_AREA_OUTLINE_PEN", &Vis::ControlParameter::ATOM_HIGHLIGHT_AREA_OUTLINE_PEN)
        .def_readonly("BREAK_ATOM_HIGHLIGHT_AREA_OUTLINE", &Vis::ControlParameter::BREAK_ATOM_HIGHLIGHT_AREA_OUTLINE)
        .def_readonly("BACKGROUND_COLOR", &Vis::ControlParameter::BACKGROUND_COLOR)
        .def_readonly("BOND_COLOR", &Vis::ControlParameter::BOND_COLOR)
        .def_readonly("BOND_LABEL_FONT", &Vis::ControlParameter::BOND_LABEL_FONT)
        .def_readonly("BOND_LABEL_MARGIN", &Vis::ControlParameter::BOND_LABEL_MARGIN)
        .def_readonly("BOND_LABEL_SIZE", &Vis::ControlParameter::BOND_LABEL_SIZE)
        .def_readonly("BOND_LENGTH", &Vis::ControlParameter::BOND_LENGTH)
        .def_readonly("BOND_LINE_SPACING", &Vis::ControlParameter::BOND_LINE_SPACING)
        .def_readonly("BOND_LINE_WIDTH", &Vis::ControlParameter::BOND_LINE_WIDTH)
        .def_readonly("REACTION_CENTER_LINE_LENGTH", &Vis::ControlParameter::REACTION_CENTER_LINE_LENGTH)
        .def_readonly("REACTION_CENTER_LINE_SPACING", &Vis::ControlParameter::REACTION_CENTER_LINE_SPACING)
        .def_readonly("STEREO_BOND_HASH_SPACING", &Vis::ControlParameter::STEREO_BOND_HASH_SPACING)
        .def_readonly("STEREO_BOND_WEDGE_WIDTH", &Vis::ControlParameter::STEREO_BOND_WEDGE_WIDTH)
        .def_readonly("DOUBLE_BOND_TRIM_LENGTH", &Vis::ControlParameter::DOUBLE_BOND_TRIM_LENGTH)
        .def_readonly("REACTION_AGENT_ALIGNMENT", &Vis::ControlParameter::REACTION_AGENT_ALIGNMENT)
        .def_readonly("REACTION_AGENT_LAYOUT", &Vis::ControlParameter::REACTION_AGENT_LAYOUT)
        .def_readonly("REACTION_AGENT_LAYOUT_DIRECTION", &Vis::ControlParameter::REACTION_AGENT_LAYOUT_DIRECTION)
        .def_readonly("REACTION_ARROW_COLOR", &Vis::ControlParameter::REACTION_ARROW_COLOR)
        .def_readonly("REACTION_ARROW_HEAD_LENGTH", &Vis::ControlParameter::REACTION_ARROW_HEAD_LENGTH)
        .def_readonly("REACTION_ARROW_HEAD_WIDTH", &Vis::ControlParameter::REACTION_ARROW_HEAD_WIDTH)
        .def_readonly("REACTION_ARROW_LENGTH", &Vis::ControlParameter::REACTION_ARROW_LENGTH)
        .def_readonly("REACTION_ARROW_LINE_WIDTH", &Vis::ControlParameter::REACTION_ARROW_LINE_WIDTH)
        .def_readonly("REACTION_ARROW_SHAFT_WIDTH", &Vis::ControlParameter::REACTION_ARROW_SHAFT_WIDTH)
        .def_readonly("REACTION_ARROW_STYLE", &Vis::ControlParameter::REACTION_ARROW_STYLE)
        .def_readonly("REACTION_COMPONENT_LAYOUT", &Vis::ControlParameter::REACTION_COMPONENT_LAYOUT)
        .def_readonly("REACTION_COMPONENT_LAYOUT_DIRECTION", &Vis::ControlParameter::REACTION_COMPONENT_LAYOUT_DIRECTION)
        .def_readonly("REACTION_COMPONENT_MARGIN", &Vis::ControlParameter::REACTION_COMPONENT_MARGIN)
        .def_readonly("REACTION_PLUS_SIGN_COLOR", &Vis::ControlParameter::REACTION_PLUS_SIGN_COLOR)
        .def_readonly("REACTION_PLUS_SIGN_LINE_WIDTH", &Vis::ControlParameter::REACTION_PLUS_SIGN_LINE_WIDTH)
        .def_readonly("REACTION_PLUS_SIGN_SIZE", &Vis::ControlParameter::REACTION_PLUS_SIGN_SIZE)
        .def_readonly("SHOW_REACTION_REACTANTS", &Vis::ControlParameter::SHOW_REACTION_REACTANTS)
        .def_readonly("SHOW_REACTION_AGENTS", &Vis::ControlParameter::SHOW_REACTION_AGENTS)
        .def_readonly("SHOW_REACTION_PRODUCTS", &Vis::ControlParameter::SHOW_REACTION_PRODUCTS)
        .def_readonly("SHOW_CHARGES", &Vis::ControlParameter::SHOW_CHARGES)
        .def_readonly("SHOW_HYDROGEN_COUNTS", &Vis::ControlParameter::SHOW_HYDROGEN_COUNTS)
        .def_readonly("SHOW_ISOTOPES", &Vis::ControlParameter::SHOW_ISOTOPES)
        .def_readonly("SHOW_NON_CARBON_HYDROGEN_COUNTS", &Vis::ControlParameter::SHOW_NON_CARBON_HYDROGEN_COUNTS)
        .def_readonly("SHOW_ATOM_QUERY_INFOS", &Vis::ControlParameter::SHOW_ATOM_QUERY_INFOS)
        .def_readonly("SHOW_RADICAL_ELECTRONS", &Vis::ControlParameter::SHOW_RADICAL_ELECTRONS)
        .def_readonly("SHOW_ATOM_REACTION_INFOS", &Vis::ControlParameter::SHOW_ATOM_REACTION_INFOS)
        .def_readonly("SHOW_BOND_QUERY_INFOS", &Vis::ControlParameter::SHOW_BOND_QUERY_INFOS)
        .def_readonly("SHOW_BOND_REACTION_INFOS", &Vis::ControlParameter::SHOW_BOND_REACTION_INFOS)
        .def_readonly("SHOW_STEREO_BONDS", &Vis::ControlParameter::SHOW_STEREO_BONDS)
        .def_readonly("SHOW_CARBONS", &Vis::ControlParameter::SHOW_CARBONS)
        .def_readonly("SHOW_EXPLICIT_HYDROGENS", &Vis::ControlParameter::SHOW_EXPLICIT_HYDROGENS)
        .def_readonly("SHOW_BOND_CONFIGURATION_LABELS", &Vis::ControlParameter::SHOW_BOND_CONFIGURATION_LABELS)
        .def_readonly("SHOW_BOND_CUSTOM_LABELS", &Vis::ControlParameter::SHOW_BOND_CUSTOM_LABELS)
        .def_readonly("SHOW_ATOM_CONFIGURATION_LABELS", &Vis::ControlParameter::SHOW_ATOM_CONFIGURATION_LABELS)
        .def_readonly("SHOW_ATOM_CUSTOM_LABELS", &Vis::ControlParameter::SHOW_ATOM_CUSTOM_LABELS)
        .def_readonly("ENABLE_ATOM_HIGHLIGHTING", &Vis::ControlParameter::ENABLE_ATOM_HIGHLIGHTING)
        .def_readonly("ENABLE_BOND_HIGHLIGHTING", &Vis::ControlParameter::ENABLE_BOND_HIGHLIGHTING)
        .def_readonly("SIZE_ADJUSTMENT", &Vis::ControlParameter::SIZE_ADJUSTMENT)
        .def_readonly("TRIPLE_BOND_TRIM_LENGTH", &Vis::ControlParameter::TRIPLE_BOND_TRIM_LENGTH)
        .def_readonly("USE_CALCULATED_ATOM_COORDINATES", &Vis::ControlParameter::USE_CALCULATED_ATOM_COORDINATES)
        .def_readonly("VIEWPORT", &Vis::ControlParameter::VIEWPORT)
        .def_readonly("HIGHLIGHT_AREA_OUTLINE_WIDTH", &Vis::ControlParameter::HIGHLIGHT_AREA_OUTLINE_WIDTH)
        .def_readonly("ATOM_CONFIGURATION_LABEL_FONT", &Vis::ControlParameter::ATOM_CONFIGURATION_LABEL_FONT)
        .def_readonly("ATOM_CONFIGURATION_LABEL_SIZE", &Vis::ControlParameter::ATOM_CONFIGURATION_LABEL_SIZE)
        .def_readonly("ATOM_CONFIGURATION_LABEL_COLOR", &Vis::ControlParameter::ATOM_CONFIGURATION_LABEL_COLOR)
        .def_readonly("ATOM_CUSTOM_LABEL_FONT", &Vis::ControlParameter::ATOM_CUSTOM_LABEL_FONT)
        .def_readonly("ATOM_CUSTOM_LABEL_SIZE", &Vis::ControlParameter::ATOM_CUSTOM_LABEL_SIZE)
        .def_readonly("ATOM_CUSTOM_LABEL_COLOR", &Vis::ControlParameter::ATOM_CUSTOM_LABEL_COLOR)
        .def_readonly("BOND_HIGHLIGHT_AREA_WIDTH", &Vis::ControlParameter::BOND_HIGHLIGHT_AREA_WIDTH)
        .def_readonly("BOND_HIGHLIGHT_AREA_BRUSH", &Vis::ControlParameter::BOND_HIGHLIGHT_AREA_BRUSH)
        .def_readonly("BOND_HIGHLIGHT_AREA_OUTLINE_PEN", &Vis::ControlParameter::BOND_HIGHLIGHT_AREA_OUTLINE_PEN)
        .def_readonly("BOND_CONFIGURATION_LABEL_FONT", &Vis::ControlParameter::BOND_CONFIGURATION_LABEL_FONT)
        .def_readonly("BOND_CONFIGURATION_LABEL_SIZE", &Vis::ControlParameter::BOND_CONFIGURATION_LABEL_SIZE)
        .def_readonly("BOND_CONFIGURATION_LABEL_COLOR", &Vis::ControlParameter::BOND_CONFIGURATION_LABEL_COLOR)
        .def_readonly("BOND_CUSTOM_LABEL_FONT", &Vis::ControlParameter::BOND_CUSTOM_LABEL_FONT)
        .def_readonly("BOND_CUSTOM_LABEL_SIZE", &Vis::ControlParameter::BOND_CUSTOM_LABEL_SIZE)
        .def_readonly("BOND_CUSTOM_LABEL_COLOR", &Vis::ControlParameter::BOND_CUSTOM_LABEL_COLOR)
        ;
}
