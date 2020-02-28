/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * ControlParameterFunctions.cpp 
 *
 * This file is part of the Chemical Data Processing Toolkit
 *
 * Copyright (C) 2003-2020 Thomas A. Seidel <thomas.seidel@univie.ac.at>
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

#include "CDPL/Vis/ControlParameterFunctions.hpp"
#include "CDPL/Vis/ControlParameter.hpp"
#include "CDPL/Vis/ControlParameterDefault.hpp"
#include "CDPL/Vis/Color.hpp"
#include "CDPL/Vis/Font.hpp"
#include "CDPL/Vis/Rectangle2D.hpp"
#include "CDPL/Vis/SizeSpecification.hpp"
#include "CDPL/Base/ControlParameterContainer.hpp"


using namespace CDPL; 


#define MAKE_CONTROL_PARAM_FUNCTIONS(PARAM_NAME, TYPE, FUNC_INFIX)		\
	TYPE Vis::get##FUNC_INFIX##Parameter(const Base::ControlParameterContainer& cntnr) \
	{																	\
		return cntnr.getParameterOrDefault<TYPE>(ControlParameter::PARAM_NAME, \
												 ControlParameterDefault::PARAM_NAME); \
	}																	\
																		\
	void Vis::set##FUNC_INFIX##Parameter(Base::ControlParameterContainer& cntnr, TYPE arg) \
	{																	\
		cntnr.setParameter(ControlParameter::PARAM_NAME, arg);			\
	}																	\
																		\
	bool Vis::has##FUNC_INFIX##Parameter(const Base::ControlParameterContainer& cntnr) \
	{																	\
		return cntnr.isParameterSet(ControlParameter::PARAM_NAME);		\
	}																	\
																		\
	void Vis::clear##FUNC_INFIX##Parameter(Base::ControlParameterContainer& cntnr) \
	{																	\
		cntnr.removeParameter(ControlParameter::PARAM_NAME);			\
	}


MAKE_CONTROL_PARAM_FUNCTIONS(VIEWPORT, const Vis::Rectangle2D&, Viewport)
MAKE_CONTROL_PARAM_FUNCTIONS(SIZE_ADJUSTMENT, unsigned int, SizeAdjustment)
MAKE_CONTROL_PARAM_FUNCTIONS(ALIGNMENT, unsigned int, Alignment)
MAKE_CONTROL_PARAM_FUNCTIONS(BACKGROUND_COLOR, const Vis::Color&, BackgroundColor)

MAKE_CONTROL_PARAM_FUNCTIONS(REACTION_ARROW_STYLE, unsigned int, ReactionArrowStyle)
MAKE_CONTROL_PARAM_FUNCTIONS(REACTION_ARROW_COLOR, const Vis::Color&, ReactionArrowColor)
MAKE_CONTROL_PARAM_FUNCTIONS(REACTION_ARROW_LENGTH, const Vis::SizeSpecification&, ReactionArrowLength)
MAKE_CONTROL_PARAM_FUNCTIONS(REACTION_ARROW_HEAD_LENGTH, const Vis::SizeSpecification&, ReactionArrowHeadLength)
MAKE_CONTROL_PARAM_FUNCTIONS(REACTION_ARROW_HEAD_WIDTH, const Vis::SizeSpecification&, ReactionArrowHeadWidth)
MAKE_CONTROL_PARAM_FUNCTIONS(REACTION_ARROW_SHAFT_WIDTH, const Vis::SizeSpecification&, ReactionArrowShaftWidth)
MAKE_CONTROL_PARAM_FUNCTIONS(REACTION_ARROW_LINE_WIDTH, const Vis::SizeSpecification&, ReactionArrowLineWidth)
MAKE_CONTROL_PARAM_FUNCTIONS(REACTION_COMPONENT_LAYOUT, unsigned int, ReactionComponentLayout)
MAKE_CONTROL_PARAM_FUNCTIONS(REACTION_COMPONENT_LAYOUT_DIRECTION, unsigned int, ReactionComponentLayoutDirection)
MAKE_CONTROL_PARAM_FUNCTIONS(REACTION_COMPONENT_MARGIN, const Vis::SizeSpecification&, ReactionComponentMargin)
MAKE_CONTROL_PARAM_FUNCTIONS(SHOW_REACTION_REACTANTS, bool, ShowReactionReactants)
MAKE_CONTROL_PARAM_FUNCTIONS(SHOW_REACTION_AGENTS, bool, ShowReactionAgents)
MAKE_CONTROL_PARAM_FUNCTIONS(SHOW_REACTION_PRODUCTS, bool, ShowReactionProducts)
MAKE_CONTROL_PARAM_FUNCTIONS(REACTION_AGENT_ALIGNMENT, unsigned int, ReactionAgentAlignment)
MAKE_CONTROL_PARAM_FUNCTIONS(REACTION_AGENT_LAYOUT, unsigned int, ReactionAgentLayout)
MAKE_CONTROL_PARAM_FUNCTIONS(REACTION_AGENT_LAYOUT_DIRECTION, unsigned int, ReactionAgentLayoutDirection)
MAKE_CONTROL_PARAM_FUNCTIONS(REACTION_PLUS_SIGN_COLOR, const Vis::Color&, ReactionPlusSignColor)
MAKE_CONTROL_PARAM_FUNCTIONS(REACTION_PLUS_SIGN_SIZE, const Vis::SizeSpecification&, ReactionPlusSignSize)
MAKE_CONTROL_PARAM_FUNCTIONS(REACTION_PLUS_SIGN_LINE_WIDTH, const Vis::SizeSpecification&, ReactionPlusSignLineWidth)
MAKE_CONTROL_PARAM_FUNCTIONS(SHOW_REACTION_PLUS_SIGNS, bool, ShowReactionPlusSigns)

MAKE_CONTROL_PARAM_FUNCTIONS(ATOM_COLOR_TABLE, const Vis::ColorTable::SharedPointer&, AtomColorTable)
MAKE_CONTROL_PARAM_FUNCTIONS(ATOM_COLOR, const Vis::Color&, AtomColor)
MAKE_CONTROL_PARAM_FUNCTIONS(USE_CALCULATED_ATOM_COORDINATES, bool, UseCalculatedAtomCoordinates)
MAKE_CONTROL_PARAM_FUNCTIONS(ATOM_LABEL_FONT, const Vis::Font&, AtomLabelFont)
MAKE_CONTROL_PARAM_FUNCTIONS(ATOM_LABEL_SIZE, const Vis::SizeSpecification&, AtomLabelSize)
MAKE_CONTROL_PARAM_FUNCTIONS(SECONDARY_ATOM_LABEL_FONT, const Vis::Font&, SecondaryAtomLabelFont)
MAKE_CONTROL_PARAM_FUNCTIONS(SECONDARY_ATOM_LABEL_SIZE, const Vis::SizeSpecification&, SecondaryAtomLabelSize)
MAKE_CONTROL_PARAM_FUNCTIONS(ATOM_LABEL_MARGIN, const Vis::SizeSpecification&, AtomLabelMargin)
MAKE_CONTROL_PARAM_FUNCTIONS(RADICAL_ELECTRON_DOT_SIZE, const Vis::SizeSpecification&, RadicalElectronDotSize)
MAKE_CONTROL_PARAM_FUNCTIONS(SHOW_EXPLICIT_HYDROGENS, bool, ShowExplicitHydrogens)
MAKE_CONTROL_PARAM_FUNCTIONS(SHOW_CARBONS, bool, ShowCarbons)
MAKE_CONTROL_PARAM_FUNCTIONS(SHOW_CHARGES, bool, ShowCharges)
MAKE_CONTROL_PARAM_FUNCTIONS(SHOW_ISOTOPES, bool, ShowIsotopes)
MAKE_CONTROL_PARAM_FUNCTIONS(SHOW_HYDROGEN_COUNTS, bool, ShowHydrogenCounts)
MAKE_CONTROL_PARAM_FUNCTIONS(SHOW_NON_CARBON_HYDROGEN_COUNTS, bool, ShowNonCarbonHydrogenCounts)
MAKE_CONTROL_PARAM_FUNCTIONS(SHOW_ATOM_QUERY_INFOS, bool, ShowAtomQueryInfos)
MAKE_CONTROL_PARAM_FUNCTIONS(SHOW_ATOM_REACTION_INFOS, bool, ShowAtomReactionInfos)
MAKE_CONTROL_PARAM_FUNCTIONS(SHOW_RADICAL_ELECTRONS, bool, ShowRadicalElectrons)

MAKE_CONTROL_PARAM_FUNCTIONS(BOND_LENGTH, const Vis::SizeSpecification&, BondLength)
MAKE_CONTROL_PARAM_FUNCTIONS(BOND_COLOR, const Vis::Color&, BondColor)
MAKE_CONTROL_PARAM_FUNCTIONS(BOND_LINE_WIDTH, const Vis::SizeSpecification&, BondLineWidth)
MAKE_CONTROL_PARAM_FUNCTIONS(BOND_LINE_SPACING, const Vis::SizeSpecification&, BondLineSpacing)
MAKE_CONTROL_PARAM_FUNCTIONS(STEREO_BOND_WEDGE_WIDTH, const Vis::SizeSpecification&, StereoBondWedgeWidth)
MAKE_CONTROL_PARAM_FUNCTIONS(STEREO_BOND_HASH_SPACING, const Vis::SizeSpecification&, StereoBondHashSpacing)
MAKE_CONTROL_PARAM_FUNCTIONS(REACTION_CENTER_LINE_LENGTH, const Vis::SizeSpecification&, ReactionCenterLineLength)
MAKE_CONTROL_PARAM_FUNCTIONS(REACTION_CENTER_LINE_SPACING, const Vis::SizeSpecification&, ReactionCenterLineSpacing)
MAKE_CONTROL_PARAM_FUNCTIONS(DOUBLE_BOND_TRIM_LENGTH, const Vis::SizeSpecification&, DoubleBondTrimLength)
MAKE_CONTROL_PARAM_FUNCTIONS(TRIPLE_BOND_TRIM_LENGTH, const Vis::SizeSpecification&, TripleBondTrimLength)
MAKE_CONTROL_PARAM_FUNCTIONS(BOND_LABEL_FONT, const Vis::Font&, BondLabelFont)
MAKE_CONTROL_PARAM_FUNCTIONS(BOND_LABEL_SIZE, const Vis::SizeSpecification&, BondLabelSize)
MAKE_CONTROL_PARAM_FUNCTIONS(BOND_LABEL_MARGIN, const Vis::SizeSpecification&, BondLabelMargin)
MAKE_CONTROL_PARAM_FUNCTIONS(SHOW_BOND_REACTION_INFOS, bool, ShowBondReactionInfos)
MAKE_CONTROL_PARAM_FUNCTIONS(SHOW_BOND_QUERY_INFOS, bool, ShowBondQueryInfos)
MAKE_CONTROL_PARAM_FUNCTIONS(SHOW_STEREO_BONDS, bool, ShowStereoBonds)
