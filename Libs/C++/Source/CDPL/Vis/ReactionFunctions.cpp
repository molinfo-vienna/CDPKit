/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * ReactionFunctions.cpp 
 *
 * This file is part of the Chemical Data Processing Toolkit
 *
 * Copyright (C) 2003-2010 Thomas A. Seidel <thomas.seidel@univie.ac.at>
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
#include "CDPL/Vis/ControlParameterDefault.hpp"
#include "CDPL/Vis/Color.hpp"
#include "CDPL/Vis/SizeSpecification.hpp"
#include "CDPL/Chem/Reaction.hpp"


using namespace CDPL; 


#define MAKE_RXN_PROPERTY_FUNCTIONS(PROP_NAME, TYPE, FUNC_SUFFIX, PROP_DEFAULT)         \
TYPE Vis::get##FUNC_SUFFIX(const Chem::Reaction& rxn)                                   \
{                                                                                       \
	return rxn.getPropertyOrDefault<TYPE>(ReactionProperty::PROP_NAME,                  \
										  ControlParameterDefault::PROP_DEFAULT);       \
}                                                                                       \
                                                                                        \
void Vis::set##FUNC_SUFFIX(Chem::Reaction& rxn, TYPE arg)                               \
{                                                                                       \
	rxn.setProperty(ReactionProperty::PROP_NAME, arg);                                  \
}                                                                                       \
                                                                                        \
bool Vis::has##FUNC_SUFFIX(const Chem::Reaction& rxn)                                   \
{                                                                                       \
	return rxn.isPropertySet(ReactionProperty::PROP_NAME);                              \
}                                                                                       \
                                                                                        \
void Vis::clear##FUNC_SUFFIX(Chem::Reaction& rxn)                                       \
{                                                                                       \
	rxn.removeProperty(ReactionProperty::PROP_NAME);                                    \
}


MAKE_RXN_PROPERTY_FUNCTIONS(ARROW_STYLE, unsigned int, ArrowStyle, REACTION_ARROW_STYLE)
MAKE_RXN_PROPERTY_FUNCTIONS(ARROW_COLOR, const Vis::Color&, ArrowColor, REACTION_ARROW_COLOR)
MAKE_RXN_PROPERTY_FUNCTIONS(ARROW_LENGTH, const Vis::SizeSpecification&, ArrowLength, REACTION_ARROW_LENGTH)
MAKE_RXN_PROPERTY_FUNCTIONS(ARROW_HEAD_LENGTH, const Vis::SizeSpecification&, ArrowHeadLength, REACTION_ARROW_HEAD_LENGTH)
MAKE_RXN_PROPERTY_FUNCTIONS(ARROW_HEAD_WIDTH, const Vis::SizeSpecification&, ArrowHeadWidth, REACTION_ARROW_HEAD_WIDTH)
MAKE_RXN_PROPERTY_FUNCTIONS(ARROW_SHAFT_WIDTH, const Vis::SizeSpecification&, ArrowShaftWidth, REACTION_ARROW_SHAFT_WIDTH)
MAKE_RXN_PROPERTY_FUNCTIONS(ARROW_LINE_WIDTH, const Vis::SizeSpecification&, ArrowLineWidth, REACTION_ARROW_LINE_WIDTH)
MAKE_RXN_PROPERTY_FUNCTIONS(COMPONENT_LAYOUT, unsigned int, ComponentLayout, REACTION_COMPONENT_LAYOUT)
MAKE_RXN_PROPERTY_FUNCTIONS(COMPONENT_LAYOUT_DIRECTION, unsigned int, ComponentLayoutDirection, REACTION_COMPONENT_LAYOUT_DIRECTION)
MAKE_RXN_PROPERTY_FUNCTIONS(COMPONENT_MARGIN, const Vis::SizeSpecification&, ComponentMargin, REACTION_COMPONENT_MARGIN)
MAKE_RXN_PROPERTY_FUNCTIONS(SHOW_REACTANTS, bool, ShowReactants, SHOW_REACTION_REACTANTS)
MAKE_RXN_PROPERTY_FUNCTIONS(SHOW_AGENTS, bool, ShowAgents, SHOW_REACTION_AGENTS)
MAKE_RXN_PROPERTY_FUNCTIONS(SHOW_PRODUCTS, bool, ShowProducts, SHOW_REACTION_PRODUCTS)
MAKE_RXN_PROPERTY_FUNCTIONS(AGENT_ALIGNMENT, unsigned int, AgentAlignment, REACTION_AGENT_ALIGNMENT)
MAKE_RXN_PROPERTY_FUNCTIONS(AGENT_LAYOUT, unsigned int, AgentLayout, REACTION_AGENT_LAYOUT)
MAKE_RXN_PROPERTY_FUNCTIONS(AGENT_LAYOUT_DIRECTION, unsigned int, AgentLayoutDirection, REACTION_AGENT_LAYOUT_DIRECTION)
MAKE_RXN_PROPERTY_FUNCTIONS(PLUS_SIGN_COLOR, const Vis::Color&, PlusSignColor, REACTION_PLUS_SIGN_COLOR)
MAKE_RXN_PROPERTY_FUNCTIONS(PLUS_SIGN_SIZE, const Vis::SizeSpecification&, PlusSignSize, REACTION_PLUS_SIGN_SIZE)
MAKE_RXN_PROPERTY_FUNCTIONS(PLUS_SIGN_LINE_WIDTH, const Vis::SizeSpecification&, PlusSignLineWidth, REACTION_PLUS_SIGN_LINE_WIDTH)
MAKE_RXN_PROPERTY_FUNCTIONS(SHOW_PLUS_SIGNS, bool, ShowPlusSigns, SHOW_REACTION_PLUS_SIGNS)
