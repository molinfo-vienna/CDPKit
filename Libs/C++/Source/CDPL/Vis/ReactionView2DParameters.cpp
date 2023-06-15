/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * ReactionView2DParameters.cpp 
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

#include <functional>

#include "CDPL/Vis/View2D.hpp"
#include "CDPL/Vis/ControlParameter.hpp"
#include "CDPL/Vis/ControlParameterDefault.hpp"

#include "ReactionView2DParameters.hpp"


using namespace CDPL;


Vis::ReactionView2DParameters::ReactionView2DParameters(View2D& view): 
	view(view),
	viewport(ControlParameterDefault::VIEWPORT),
	sizeAdjustment(ControlParameterDefault::SIZE_ADJUSTMENT),
	alignment(ControlParameterDefault::ALIGNMENT),
	backgroundColor(Color::WHITE),
	eraseBackgroundFlag(false),
	arrowStyle(ControlParameterDefault::REACTION_ARROW_STYLE),
	arrowColor(ControlParameterDefault::REACTION_ARROW_COLOR),
	arrowLength(ControlParameterDefault::REACTION_ARROW_LENGTH),
	arrowHeadLength(ControlParameterDefault::REACTION_ARROW_HEAD_LENGTH),
	arrowHeadWidth(ControlParameterDefault::REACTION_ARROW_HEAD_WIDTH),
	arrowShaftWidth(ControlParameterDefault::REACTION_ARROW_SHAFT_WIDTH),
	arrowLineWidth(ControlParameterDefault::REACTION_ARROW_LINE_WIDTH),
	componentLayout(ControlParameterDefault::REACTION_COMPONENT_LAYOUT),
	componentLayoutDirection(ControlParameterDefault::REACTION_COMPONENT_LAYOUT_DIRECTION),
	componentMargin(ControlParameterDefault::REACTION_COMPONENT_MARGIN),
	showReactantsFlag(ControlParameterDefault::SHOW_REACTION_REACTANTS), 
	showAgentsFlag(ControlParameterDefault::SHOW_REACTION_AGENTS), 
	showProductsFlag(ControlParameterDefault::SHOW_REACTION_PRODUCTS), 
	agentAlignment(ControlParameterDefault::REACTION_AGENT_ALIGNMENT),
	plusSignColor(ControlParameterDefault::REACTION_PLUS_SIGN_COLOR),
	plusSignSize(ControlParameterDefault::REACTION_PLUS_SIGN_SIZE),
	plusSignLineWidth(ControlParameterDefault::REACTION_PLUS_SIGN_LINE_WIDTH),
	showPlusSignsFlag(ControlParameterDefault::SHOW_REACTION_PLUS_SIGNS),
	viewportChangedFlag(true),
	alignmentChangedFlag(true),
	sizeAdjustmentChangedFlag(true),
	componentBoundsChangedFlag(true),
	layoutChangedFlag(true),
	plusSignSizeChangedFlag(true),
	plusSignAttributeChangedFlag(true),
	arrowSizeChangedFlag(true),
	arrowAttributeChangedFlag(true),
	componentVisibilityChangedFlag(true) 
{
	using namespace std::placeholders;
		
	view.registerParameterRemovedCallback(std::bind(&ReactionView2DParameters::parameterRemoved, this, _1));
	view.registerParameterChangedCallback(std::bind(&ReactionView2DParameters::parameterChanged, this, _1, _2));
	view.registerParentChangedCallback(std::bind(&ReactionView2DParameters::parentChanged, this));
}

Vis::ReactionView2DParameters::~ReactionView2DParameters() {}

const Vis::Rectangle2D& Vis::ReactionView2DParameters::getViewport() const
{
	return viewport;
}

unsigned int Vis::ReactionView2DParameters::getAlignment() const
{
	return alignment;
}

unsigned int Vis::ReactionView2DParameters::getSizeAdjustment() const
{
	return sizeAdjustment;
}

bool Vis::ReactionView2DParameters::eraseBackground() const
{
	return eraseBackgroundFlag;
}

const Vis::Color& Vis::ReactionView2DParameters::getBackgroundColor() const
{
	return backgroundColor;
}

unsigned int Vis::ReactionView2DParameters::getArrowStyle() const
{
	return arrowStyle;
}

const Vis::Color& Vis::ReactionView2DParameters::getArrowColor() const
{
	return arrowColor;
}

const Vis::SizeSpecification& Vis::ReactionView2DParameters::getArrowLength() const
{
	return arrowLength;
}

const Vis::SizeSpecification& Vis::ReactionView2DParameters::getArrowHeadLength() const
{
	return arrowHeadLength;
}

const Vis::SizeSpecification& Vis::ReactionView2DParameters::getArrowHeadWidth() const
{
	return arrowHeadWidth;
}

const Vis::SizeSpecification& Vis::ReactionView2DParameters::getArrowShaftWidth() const
{
	return arrowShaftWidth;
}

const Vis::SizeSpecification& Vis::ReactionView2DParameters::getArrowLineWidth() const
{
	return arrowLineWidth;
}

unsigned int Vis::ReactionView2DParameters::getComponentLayout() const
{
	return componentLayout;
}

unsigned int Vis::ReactionView2DParameters::getComponentLayoutDirection() const
{
	return componentLayoutDirection;
}

const Vis::SizeSpecification& Vis::ReactionView2DParameters::getComponentMargin() const
{
	return componentMargin;
}

bool Vis::ReactionView2DParameters::showReactants() const
{
	return showReactantsFlag;
}

bool Vis::ReactionView2DParameters::showAgents() const
{
	return showAgentsFlag;
}

bool Vis::ReactionView2DParameters::showProducts() const
{
	return showProductsFlag;
}

unsigned int Vis::ReactionView2DParameters::getAgentAlignment() const
{
	return agentAlignment;
}

unsigned int Vis::ReactionView2DParameters::getAgentLayout() const
{
	return agentLayout;
}

unsigned int Vis::ReactionView2DParameters::getAgentLayoutDirection() const
{
	return agentLayoutDirection;
}

const Vis::Color& Vis::ReactionView2DParameters::getPlusSignColor() const
{
	return plusSignColor;
}

const Vis::SizeSpecification& Vis::ReactionView2DParameters::getPlusSignSize() const
{
	return plusSignSize;
}

const Vis::SizeSpecification& Vis::ReactionView2DParameters::getPlusSignLineWidth() const
{
	return plusSignLineWidth;
}

bool Vis::ReactionView2DParameters::showPlusSigns() const
{
	return showPlusSignsFlag; 
}

bool Vis::ReactionView2DParameters::viewportChanged() const
{
	return viewportChangedFlag;
}

bool Vis::ReactionView2DParameters::alignmentChanged() const
{
	return alignmentChangedFlag;
}

bool Vis::ReactionView2DParameters::sizeAdjustmentChanged() const
{
	return sizeAdjustmentChangedFlag;
}

bool Vis::ReactionView2DParameters::componentBoundsChanged() const
{
	return componentBoundsChangedFlag;
}

bool Vis::ReactionView2DParameters::layoutChanged() const
{
	return layoutChangedFlag;
}

bool Vis::ReactionView2DParameters::plusSignSizeChanged() const
{
	return plusSignSizeChangedFlag;
}

bool Vis::ReactionView2DParameters::plusSignAttributeChanged() const
{
	return plusSignAttributeChangedFlag;
}

bool Vis::ReactionView2DParameters::arrowSizeChanged() const
{
	return arrowSizeChangedFlag;
}

bool Vis::ReactionView2DParameters::arrowAttributeChanged() const
{
	return arrowAttributeChangedFlag;
}

bool Vis::ReactionView2DParameters::componentVisibilityChanged() const
{
	return componentVisibilityChangedFlag;
}

void Vis::ReactionView2DParameters::clearChangeFlags()
{
	viewportChangedFlag            = false;
	alignmentChangedFlag           = false;
	sizeAdjustmentChangedFlag      = false;
	componentBoundsChangedFlag     = false;
	layoutChangedFlag              = false;
	plusSignSizeChangedFlag        = false;
	plusSignAttributeChangedFlag   = false;
	arrowSizeChangedFlag           = false;
	arrowAttributeChangedFlag      = false;
	componentVisibilityChangedFlag = false;
}

void Vis::ReactionView2DParameters::parentChanged()
{
	parameterChanged(ControlParameter::VIEWPORT, view.getParameter(ControlParameter::VIEWPORT));
	parameterChanged(ControlParameter::SIZE_ADJUSTMENT, view.getParameter(ControlParameter::SIZE_ADJUSTMENT));
	parameterChanged(ControlParameter::ALIGNMENT, view.getParameter(ControlParameter::ALIGNMENT));

	parameterChanged(ControlParameter::BACKGROUND_COLOR, view.getParameter(ControlParameter::BACKGROUND_COLOR));

	parameterChanged(ControlParameter::REACTION_ARROW_STYLE, view.getParameter(ControlParameter::REACTION_ARROW_STYLE));
	parameterChanged(ControlParameter::REACTION_ARROW_COLOR, view.getParameter(ControlParameter::REACTION_ARROW_COLOR));
	parameterChanged(ControlParameter::REACTION_ARROW_LENGTH, view.getParameter(ControlParameter::REACTION_ARROW_LENGTH));
	parameterChanged(ControlParameter::REACTION_ARROW_HEAD_LENGTH, view.getParameter(ControlParameter::REACTION_ARROW_HEAD_LENGTH));
	parameterChanged(ControlParameter::REACTION_ARROW_HEAD_WIDTH, view.getParameter(ControlParameter::REACTION_ARROW_HEAD_WIDTH));
	parameterChanged(ControlParameter::REACTION_ARROW_SHAFT_WIDTH, view.getParameter(ControlParameter::REACTION_ARROW_SHAFT_WIDTH));
	parameterChanged(ControlParameter::REACTION_ARROW_LINE_WIDTH, view.getParameter(ControlParameter::REACTION_ARROW_LINE_WIDTH));

	parameterChanged(ControlParameter::REACTION_COMPONENT_LAYOUT, view.getParameter(ControlParameter::REACTION_COMPONENT_LAYOUT));
	parameterChanged(ControlParameter::REACTION_COMPONENT_LAYOUT_DIRECTION, view.getParameter(ControlParameter::REACTION_COMPONENT_LAYOUT_DIRECTION));
	parameterChanged(ControlParameter::REACTION_COMPONENT_MARGIN, view.getParameter(ControlParameter::REACTION_COMPONENT_MARGIN));

	parameterChanged(ControlParameter::SHOW_REACTION_REACTANTS, view.getParameter(ControlParameter::SHOW_REACTION_REACTANTS));
	parameterChanged(ControlParameter::SHOW_REACTION_AGENTS, view.getParameter(ControlParameter::SHOW_REACTION_AGENTS));
	parameterChanged(ControlParameter::SHOW_REACTION_PRODUCTS, view.getParameter(ControlParameter::SHOW_REACTION_PRODUCTS));

	parameterChanged(ControlParameter::REACTION_AGENT_ALIGNMENT, view.getParameter(ControlParameter::REACTION_AGENT_ALIGNMENT));
	parameterChanged(ControlParameter::REACTION_AGENT_LAYOUT, view.getParameter(ControlParameter::REACTION_AGENT_LAYOUT));
	parameterChanged(ControlParameter::REACTION_AGENT_LAYOUT_DIRECTION, view.getParameter(ControlParameter::REACTION_AGENT_LAYOUT_DIRECTION));

	parameterChanged(ControlParameter::REACTION_PLUS_SIGN_COLOR, view.getParameter(ControlParameter::REACTION_PLUS_SIGN_COLOR));
	parameterChanged(ControlParameter::REACTION_PLUS_SIGN_SIZE, view.getParameter(ControlParameter::REACTION_PLUS_SIGN_SIZE));
	parameterChanged(ControlParameter::REACTION_PLUS_SIGN_LINE_WIDTH, view.getParameter(ControlParameter::REACTION_PLUS_SIGN_LINE_WIDTH));
	parameterChanged(ControlParameter::SHOW_REACTION_PLUS_SIGNS, view.getParameter(ControlParameter::SHOW_REACTION_PLUS_SIGNS));

	componentBoundsChangedFlag = true;
}

void Vis::ReactionView2DParameters::parameterChanged(const Base::LookupKey& key, Base::Any val)
{
	using namespace ControlParameterDefault;

	if (key == ControlParameter::VIEWPORT) {
		setViewport(val.isEmpty() ? VIEWPORT : val.getData<Rectangle2D>());
		return;
	}

	if (key == ControlParameter::SIZE_ADJUSTMENT) {
		setSizeAdjustment(val.isEmpty() ? SIZE_ADJUSTMENT : val.getData<unsigned int>());
		return;
	}

	if (key == ControlParameter::ALIGNMENT) {
		setAlignment(val.isEmpty() ? ALIGNMENT : val.getData<unsigned int>());
		return;
	}

	if (key == ControlParameter::BACKGROUND_COLOR) {
		if (val.isEmpty())
			eraseBackground(false);

		else {
			eraseBackground(true);
			setBackgroundColor(val.getData<Color>());
		}

		return;
	}

	if (key == ControlParameter::REACTION_ARROW_STYLE) {
		setArrowStyle(val.isEmpty() ? REACTION_ARROW_STYLE : val.getData<unsigned int>());
		return;
	}

	if (key == ControlParameter::REACTION_ARROW_COLOR) {
		setArrowColor(val.isEmpty() ? REACTION_ARROW_COLOR : val.getData<Color>());
		return;
	}

	if (key == ControlParameter::REACTION_ARROW_LENGTH) {
		setArrowLength(val.isEmpty() ? REACTION_ARROW_LENGTH : val.getData<SizeSpecification>());
		return;
	}

	if (key == ControlParameter::REACTION_ARROW_HEAD_LENGTH) {
		setArrowHeadLength(val.isEmpty() ? REACTION_ARROW_HEAD_LENGTH : val.getData<SizeSpecification>());
		return;
	}

	if (key == ControlParameter::REACTION_ARROW_HEAD_WIDTH) {
		setArrowHeadWidth(val.isEmpty() ? REACTION_ARROW_HEAD_WIDTH : val.getData<SizeSpecification>());
		return;
	}

	if (key == ControlParameter::REACTION_ARROW_SHAFT_WIDTH) {
		setArrowShaftWidth(val.isEmpty() ? REACTION_ARROW_SHAFT_WIDTH : val.getData<SizeSpecification>());
		return;
	}

	if (key == ControlParameter::REACTION_ARROW_LINE_WIDTH) {
		setArrowLineWidth(val.isEmpty() ? REACTION_ARROW_LINE_WIDTH : val.getData<SizeSpecification>());
		return;
	}

	if (key == ControlParameter::REACTION_COMPONENT_LAYOUT) {
		setComponentLayout(val.isEmpty() ? REACTION_COMPONENT_LAYOUT : val.getData<unsigned int>());
		return;
	}

	if (key == ControlParameter::REACTION_COMPONENT_LAYOUT_DIRECTION) {
		setComponentLayoutDirection(val.isEmpty() ? REACTION_COMPONENT_LAYOUT_DIRECTION : val.getData<unsigned int>());
		return;
	}

	if (key == ControlParameter::REACTION_COMPONENT_MARGIN) {
		setComponentMargin(val.isEmpty() ? REACTION_COMPONENT_MARGIN : val.getData<SizeSpecification>());
		return;
	}

	if (key == ControlParameter::SHOW_REACTION_REACTANTS) {
		showReactants(val.isEmpty() ? SHOW_REACTION_REACTANTS : val.getData<bool>());
		return;
	}

	if (key == ControlParameter::SHOW_REACTION_AGENTS) {
		showAgents(val.isEmpty() ? SHOW_REACTION_AGENTS : val.getData<bool>());
		return;
	}

	if (key == ControlParameter::SHOW_REACTION_PRODUCTS) {
		showProducts(val.isEmpty() ? SHOW_REACTION_PRODUCTS : val.getData<bool>());
		return;
	}

	if (key == ControlParameter::REACTION_AGENT_ALIGNMENT) {
		setAgentAlignment(val.isEmpty() ? REACTION_AGENT_ALIGNMENT : val.getData<unsigned int>());
		return;
	}

	if (key == ControlParameter::REACTION_AGENT_LAYOUT) {
		setAgentLayout(val.isEmpty() ? REACTION_AGENT_LAYOUT : val.getData<unsigned int>());
		return;
	}

	if (key == ControlParameter::REACTION_AGENT_LAYOUT_DIRECTION) {
		setAgentLayoutDirection(val.isEmpty() ? REACTION_AGENT_LAYOUT_DIRECTION : val.getData<unsigned int>());
		return;
	}

	if (key == ControlParameter::REACTION_PLUS_SIGN_COLOR) {
		setPlusSignColor(val.isEmpty() ? REACTION_PLUS_SIGN_COLOR : val.getData<Color>());
		return;
	}

	if (key == ControlParameter::REACTION_PLUS_SIGN_SIZE) {
		setPlusSignSize(val.isEmpty() ? REACTION_PLUS_SIGN_SIZE : val.getData<SizeSpecification>());
		return;
	}

	if (key == ControlParameter::REACTION_PLUS_SIGN_LINE_WIDTH) {
		setPlusSignLineWidth(val.isEmpty() ? REACTION_PLUS_SIGN_LINE_WIDTH : val.getData<SizeSpecification>());
		return;
	}

	if (key == ControlParameter::SHOW_REACTION_PLUS_SIGNS) {
		showPlusSigns(val.isEmpty() ? SHOW_REACTION_PLUS_SIGNS : val.getData<bool>());
		return;
	}

	if (key == ControlParameter::ATOM_LABEL_FONT 
		|| key == ControlParameter::USE_CALCULATED_ATOM_COORDINATES 
		|| key == ControlParameter::ATOM_LABEL_SIZE 
		|| key == ControlParameter::SECONDARY_ATOM_LABEL_FONT 
		|| key == ControlParameter::SECONDARY_ATOM_LABEL_SIZE 
		|| key == ControlParameter::ATOM_LABEL_MARGIN 
		|| key == ControlParameter::RADICAL_ELECTRON_DOT_SIZE 
		|| key == ControlParameter::SHOW_CARBONS 
		|| key == ControlParameter::SHOW_CHARGES 
		|| key == ControlParameter::SHOW_ISOTOPES 
		|| key == ControlParameter::SHOW_EXPLICIT_HYDROGENS 
		|| key == ControlParameter::SHOW_HYDROGEN_COUNTS 
		|| key == ControlParameter::SHOW_NON_CARBON_HYDROGEN_COUNTS 
		|| key == ControlParameter::SHOW_ATOM_QUERY_INFOS 
		|| key == ControlParameter::SHOW_ATOM_REACTION_INFOS 
		|| key == ControlParameter::SHOW_RADICAL_ELECTRONS 
		|| key == ControlParameter::BOND_LABEL_FONT 
		|| key == ControlParameter::BOND_LABEL_SIZE 
		|| key == ControlParameter::BOND_LABEL_MARGIN 
		|| key == ControlParameter::SHOW_BOND_REACTION_INFOS 
		|| key == ControlParameter::SHOW_BOND_QUERY_INFOS 
		|| key == ControlParameter::BOND_LENGTH)

		componentBoundsChangedFlag = true;
}

void Vis::ReactionView2DParameters::parameterRemoved(const Base::LookupKey& key)
{
	parameterChanged(key, view.getParameter(key));
}

void Vis::ReactionView2DParameters::setViewport(const Rectangle2D& vp)
{
	if (viewport != vp) {
		viewport = vp;
		viewportChangedFlag = true;
	}
}

void Vis::ReactionView2DParameters::setAlignment(unsigned int alignmnt)
{
	if (alignment != alignmnt) {
		alignment = alignmnt;
		alignmentChangedFlag = true;
	}
}

void Vis::ReactionView2DParameters::setSizeAdjustment(unsigned int adjustment)
{
	if (sizeAdjustment != adjustment) {
		sizeAdjustment = adjustment;
		sizeAdjustmentChangedFlag = true;
	}
}

void Vis::ReactionView2DParameters::eraseBackground(bool erase)
{
	if (eraseBackgroundFlag != erase)
		eraseBackgroundFlag = erase;
}

void Vis::ReactionView2DParameters::setBackgroundColor(const Color& color)
{
	if (color != backgroundColor)
		backgroundColor = color;
}

void Vis::ReactionView2DParameters::setArrowStyle(unsigned int style)
{
	if (arrowStyle != style) {
		arrowStyle = style;
		arrowSizeChangedFlag = true;
	}
}

void Vis::ReactionView2DParameters::setArrowColor(const Color& color)
{
	if (arrowColor != color) {
		arrowColor = color;
		arrowAttributeChangedFlag = true;
	}
}

void Vis::ReactionView2DParameters::setArrowLength(const SizeSpecification& length)
{
	if (arrowLength != length) {
		arrowLength = length;
		arrowSizeChangedFlag = true;
	}
}

void Vis::ReactionView2DParameters::setArrowHeadLength(const SizeSpecification& length)
{
	if (arrowHeadLength != length) {
		arrowHeadLength = length;
		arrowSizeChangedFlag = true;
	}
}

void Vis::ReactionView2DParameters::setArrowHeadWidth(const SizeSpecification& width)
{
	if (arrowHeadWidth != width) {
		arrowHeadWidth = width;
		arrowSizeChangedFlag = true;
	}
}

void Vis::ReactionView2DParameters::setArrowShaftWidth(const SizeSpecification& width)
{
	if (arrowShaftWidth != width) {
		arrowShaftWidth = width;
		arrowSizeChangedFlag = true;
	}
}

void Vis::ReactionView2DParameters::setArrowLineWidth(const SizeSpecification& width)
{
	if (arrowLineWidth != width) {
		arrowLineWidth = width;
		arrowSizeChangedFlag = true;
	}
}

void Vis::ReactionView2DParameters::setComponentLayout(unsigned int layout)
{
	if (componentLayout != layout) {
		componentLayout = layout;
		layoutChangedFlag = true;
	}
}

void Vis::ReactionView2DParameters::setComponentLayoutDirection(unsigned int dir)
{
	if (componentLayoutDirection != dir) {
		componentLayoutDirection = dir;
		layoutChangedFlag = true;
	}
}

void Vis::ReactionView2DParameters::setComponentMargin(const SizeSpecification& margin)
{
	if (componentMargin != margin) {
		componentMargin = margin;
		layoutChangedFlag = true;
	}
}

void Vis::ReactionView2DParameters::showReactants(bool show)
{
	if (showReactantsFlag != show) {
		showReactantsFlag = show;
		componentVisibilityChangedFlag = true;
	}
}

void Vis::ReactionView2DParameters::showAgents(bool show)
{
	if (showAgentsFlag != show) {
		showAgentsFlag = show;
		componentVisibilityChangedFlag = true;
	}
}

void Vis::ReactionView2DParameters::showProducts(bool show)
{
	if (showProductsFlag != show) {
		showProductsFlag = show;
		componentVisibilityChangedFlag = true;
	}
}

void Vis::ReactionView2DParameters::setAgentAlignment(unsigned int alignment)
{
	if (agentAlignment != alignment) {
		agentAlignment = alignment;
		layoutChangedFlag = true;
	}
}

void Vis::ReactionView2DParameters::setAgentLayout(unsigned int layout)
{
	if (agentLayout != layout) {
		agentLayout = layout;
		layoutChangedFlag = true;
	}
}

void Vis::ReactionView2DParameters::setAgentLayoutDirection(unsigned int dir)
{
	if (agentLayoutDirection != dir) {
		agentLayoutDirection = dir;
		layoutChangedFlag = true;
	}
}

void Vis::ReactionView2DParameters::setPlusSignColor(const Color& color)
{
	if (plusSignColor != color) {
		plusSignColor = color;
		plusSignAttributeChangedFlag = true;
	}	
}

void Vis::ReactionView2DParameters::setPlusSignSize(const SizeSpecification& size)
{
	if (plusSignSize != size) {
		plusSignSize = size;
		plusSignSizeChangedFlag = true;
	}	
}

void Vis::ReactionView2DParameters::setPlusSignLineWidth(const SizeSpecification& width)
{
	if (plusSignLineWidth != width) {
		plusSignLineWidth = width;
		plusSignSizeChangedFlag = true;
	}	
}

void Vis::ReactionView2DParameters::showPlusSigns(bool show)
{
	if (showPlusSignsFlag != show) {
		showPlusSignsFlag = show;
		plusSignSizeChangedFlag = true;
	}	
}
