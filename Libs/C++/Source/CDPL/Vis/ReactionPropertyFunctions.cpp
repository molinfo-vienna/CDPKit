/* 
 * ReactionPropertyFunctions.cpp 
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

#include "CDPL/Vis/ReactionFunctions.hpp"
#include "CDPL/Vis/ReactionProperty.hpp"
#include "CDPL/Vis/ReactionPropertyDefault.hpp"
#include "CDPL/Chem/Reaction.hpp"


using namespace CDPL;


#define MAKE_RXN_PROPERTY_FUNCTIONS(PROP_NAME, TYPE, FUNC_SUFFIX)                  \
    TYPE Vis::get##FUNC_SUFFIX(const Chem::Reaction& rxn)                          \
    {                                                                              \
        return rxn.getPropertyOrDefault<TYPE>(ReactionProperty::PROP_NAME,         \
                                              ReactionPropertyDefault::PROP_NAME); \
    }                                                                              \
                                                                                   \
    void Vis::set##FUNC_SUFFIX(Chem::Reaction& rxn, TYPE arg)                      \
    {                                                                              \
        rxn.setProperty(ReactionProperty::PROP_NAME, arg);                         \
    }                                                                              \
                                                                                   \
    bool Vis::has##FUNC_SUFFIX(const Chem::Reaction& rxn)                          \
    {                                                                              \
        return rxn.isPropertySet(ReactionProperty::PROP_NAME);                     \
    }                                                                              \
                                                                                   \
    void Vis::clear##FUNC_SUFFIX(Chem::Reaction& rxn)                              \
    {                                                                              \
        rxn.removeProperty(ReactionProperty::PROP_NAME);                           \
    }


MAKE_RXN_PROPERTY_FUNCTIONS(ARROW_STYLE, unsigned int, ArrowStyle)
MAKE_RXN_PROPERTY_FUNCTIONS(ARROW_COLOR, const Vis::Color&, ArrowColor)
MAKE_RXN_PROPERTY_FUNCTIONS(ARROW_LENGTH, const Vis::SizeSpecification&, ArrowLength)
MAKE_RXN_PROPERTY_FUNCTIONS(ARROW_HEAD_LENGTH, const Vis::SizeSpecification&, ArrowHeadLength)
MAKE_RXN_PROPERTY_FUNCTIONS(ARROW_HEAD_WIDTH, const Vis::SizeSpecification&, ArrowHeadWidth)
MAKE_RXN_PROPERTY_FUNCTIONS(ARROW_SHAFT_WIDTH, const Vis::SizeSpecification&, ArrowShaftWidth)
MAKE_RXN_PROPERTY_FUNCTIONS(ARROW_LINE_WIDTH, const Vis::SizeSpecification&, ArrowLineWidth)
MAKE_RXN_PROPERTY_FUNCTIONS(COMPONENT_LAYOUT, unsigned int, ComponentLayout)
MAKE_RXN_PROPERTY_FUNCTIONS(COMPONENT_LAYOUT_DIRECTION, unsigned int, ComponentLayoutDirection)
MAKE_RXN_PROPERTY_FUNCTIONS(COMPONENT_MARGIN, const Vis::SizeSpecification&, ComponentMargin)
MAKE_RXN_PROPERTY_FUNCTIONS(SHOW_REACTANTS, bool, ShowReactants)
MAKE_RXN_PROPERTY_FUNCTIONS(SHOW_AGENTS, bool, ShowAgents)
MAKE_RXN_PROPERTY_FUNCTIONS(SHOW_PRODUCTS, bool, ShowProducts)
MAKE_RXN_PROPERTY_FUNCTIONS(AGENT_ALIGNMENT, unsigned int, AgentAlignment)
MAKE_RXN_PROPERTY_FUNCTIONS(AGENT_LAYOUT, unsigned int, AgentLayout)
MAKE_RXN_PROPERTY_FUNCTIONS(AGENT_LAYOUT_DIRECTION, unsigned int, AgentLayoutDirection)
MAKE_RXN_PROPERTY_FUNCTIONS(PLUS_SIGN_COLOR, const Vis::Color&, PlusSignColor)
MAKE_RXN_PROPERTY_FUNCTIONS(PLUS_SIGN_SIZE, const Vis::SizeSpecification&, PlusSignSize)
MAKE_RXN_PROPERTY_FUNCTIONS(PLUS_SIGN_LINE_WIDTH, const Vis::SizeSpecification&, PlusSignLineWidth)
MAKE_RXN_PROPERTY_FUNCTIONS(SHOW_PLUS_SIGNS, bool, ShowPlusSigns)
