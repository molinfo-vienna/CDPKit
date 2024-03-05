/* 
 * BondPropertyFunctions.cpp 
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

#include "CDPL/Vis/BondFunctions.hpp"
#include "CDPL/Vis/BondProperty.hpp"
#include "CDPL/Vis/BondPropertyDefault.hpp"
#include "CDPL/Chem/Bond.hpp"


using namespace CDPL;


#define MAKE_BOND_PROPERTY_FUNCTIONS(PROP_NAME, TYPE, FUNC_SUFFIX)              \
    TYPE Vis::get##FUNC_SUFFIX(const Chem::Bond& bond)                          \
    {                                                                           \
        return bond.getPropertyOrDefault<TYPE>(BondProperty::PROP_NAME,         \
                                               BondPropertyDefault::PROP_NAME); \
    }                                                                           \
                                                                                \
    void Vis::set##FUNC_SUFFIX(Chem::Bond& bond, TYPE arg)                      \
    {                                                                           \
        bond.setProperty(BondProperty::PROP_NAME, arg);                         \
    }                                                                           \
                                                                                \
    bool Vis::has##FUNC_SUFFIX(const Chem::Bond& bond)                          \
    {                                                                           \
        return bond.isPropertySet(BondProperty::PROP_NAME);                     \
    }                                                                           \
                                                                                \
    void Vis::clear##FUNC_SUFFIX(Chem::Bond& bond)                              \
    {                                                                           \
        bond.removeProperty(BondProperty::PROP_NAME);                           \
    }


MAKE_BOND_PROPERTY_FUNCTIONS(COLOR, const Vis::Color&, Color)
MAKE_BOND_PROPERTY_FUNCTIONS(LINE_WIDTH, const Vis::SizeSpecification&, LineWidth)
MAKE_BOND_PROPERTY_FUNCTIONS(LINE_SPACING, const Vis::SizeSpecification&, LineSpacing)
MAKE_BOND_PROPERTY_FUNCTIONS(STEREO_BOND_WEDGE_WIDTH, const Vis::SizeSpecification&, StereoBondWedgeWidth)
MAKE_BOND_PROPERTY_FUNCTIONS(STEREO_BOND_HASH_SPACING, const Vis::SizeSpecification&, StereoBondHashSpacing)
MAKE_BOND_PROPERTY_FUNCTIONS(REACTION_CENTER_LINE_LENGTH, const Vis::SizeSpecification&, ReactionCenterLineLength)
MAKE_BOND_PROPERTY_FUNCTIONS(REACTION_CENTER_LINE_SPACING, const Vis::SizeSpecification&, ReactionCenterLineSpacing)
MAKE_BOND_PROPERTY_FUNCTIONS(DOUBLE_BOND_TRIM_LENGTH, const Vis::SizeSpecification&, DoubleBondTrimLength)
MAKE_BOND_PROPERTY_FUNCTIONS(TRIPLE_BOND_TRIM_LENGTH, const Vis::SizeSpecification&, TripleBondTrimLength)
MAKE_BOND_PROPERTY_FUNCTIONS(LABEL_FONT, const Vis::Font&, LabelFont)
MAKE_BOND_PROPERTY_FUNCTIONS(LABEL_SIZE, const Vis::SizeSpecification&, LabelSize)
MAKE_BOND_PROPERTY_FUNCTIONS(LABEL_MARGIN, const Vis::SizeSpecification&, LabelMargin)
MAKE_BOND_PROPERTY_FUNCTIONS(CONFIGURATION_LABEL_FONT, const Vis::Font&, ConfigurationLabelFont)
MAKE_BOND_PROPERTY_FUNCTIONS(CONFIGURATION_LABEL_COLOR, const Vis::Color&, ConfigurationLabelColor)
MAKE_BOND_PROPERTY_FUNCTIONS(CONFIGURATION_LABEL_SIZE, const Vis::SizeSpecification&, ConfigurationLabelSize)
MAKE_BOND_PROPERTY_FUNCTIONS(CUSTOM_LABEL_FONT, const Vis::Font&, CustomLabelFont)
MAKE_BOND_PROPERTY_FUNCTIONS(CUSTOM_LABEL_COLOR, const Vis::Color&, CustomLabelColor)
MAKE_BOND_PROPERTY_FUNCTIONS(CUSTOM_LABEL_SIZE, const Vis::SizeSpecification&, CustomLabelSize)
MAKE_BOND_PROPERTY_FUNCTIONS(CUSTOM_LABEL, const std::string&, CustomLabel)
MAKE_BOND_PROPERTY_FUNCTIONS(HIGHLIGHTED_FLAG, bool, HighlightedFlag)
MAKE_BOND_PROPERTY_FUNCTIONS(HIGHLIGHT_AREA_BRUSH, const Vis::Brush&, HighlightAreaBrush)
MAKE_BOND_PROPERTY_FUNCTIONS(HIGHLIGHT_AREA_OUTLINE_PEN, const Vis::Pen&, HighlightAreaOutlinePen)
