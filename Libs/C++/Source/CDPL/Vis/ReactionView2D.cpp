/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * ReactionView2D.cpp 
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

#include <algorithm>
#include <utility>
#include <cmath>
#include <cassert>
#include <functional>

#include "CDPL/Vis/ReactionView2D.hpp"
#include "CDPL/Vis/Renderer2D.hpp"
#include "CDPL/Vis/Pen.hpp"
#include "CDPL/Vis/Brush.hpp"
#include "CDPL/Vis/SizeAdjustment.hpp"
#include "CDPL/Vis/Alignment.hpp"
#include "CDPL/Vis/LayoutDirection.hpp"
#include "CDPL/Vis/LayoutStyle.hpp"
#include "CDPL/Vis/ArrowStyle.hpp"
#include "CDPL/Vis/ReactionFunctions.hpp"
#include "CDPL/Vis/ControlParameterFunctions.hpp"
#include "CDPL/Chem/Reaction.hpp"
#include "CDPL/Chem/Molecule.hpp"
#include "CDPL/Chem/ReactionRole.hpp"

#include "ReactionView2DParameters.hpp"


namespace
{

	const std::size_t MAX_COMP_VIEW_CACHE_SIZE     = 100;
	const std::size_t MAX_POLYGON_CACHE_SIZE       = 100;
	const std::size_t MAX_LINE_SEG_LIST_CACHE_SIZE = 100;
}


using namespace CDPL;


Vis::ReactionView2D::ReactionView2D(const Chem::Reaction* rxn): 
	parameters(new ReactionView2DParameters(*this)), fontMetrics(0), fontMetricsChanged(true),
	compViewCache(MAX_COMP_VIEW_CACHE_SIZE), polygonCache(MAX_POLYGON_CACHE_SIZE), 
	lineSegListCache(MAX_LINE_SEG_LIST_CACHE_SIZE)
{
	compViewCache.setCleanupFunction(std::bind(&StructureView2D::setParent, std::placeholders::_1, 
											   static_cast<const CDPL::Base::ControlParameterContainer*>(0)));
	setReaction(rxn);
}

Vis::ReactionView2D::~ReactionView2D() {}

void Vis::ReactionView2D::render(Renderer2D& renderer)
{
	if (!reaction)
		return;

	init();

	paintBackground(renderer);

	renderer.saveState();

	renderComponents(renderer);
	renderGraphicsPrimitives(renderer);

	renderer.restoreState();
}

void Vis::ReactionView2D::setReaction(const Chem::Reaction* rxn)
{
	reaction = rxn;
	reactionChanged = true;
}

const Chem::Reaction* Vis::ReactionView2D::getReaction() const
{
	return reaction;
}

void Vis::ReactionView2D::setFontMetrics(FontMetrics* font_metrics)
{
	fontMetrics = font_metrics;

	ComponentViewList::iterator views_end = componentViews.end();

	for (ComponentViewList::iterator it = componentViews.begin(); it != views_end; ++it) { 
		View2D* view = *it;

		view->setFontMetrics(font_metrics);
	}

	fontMetricsChanged = true;
}

Vis::FontMetrics* Vis::ReactionView2D::getFontMetrics() const
{
	return fontMetrics;
}

void Vis::ReactionView2D::getModelBounds(Rectangle2D& bounds)
{
	if (!reaction) { 
		bounds.reset();
		return;
	}

	init();

	bounds = totalReactionBounds;

	bounds.scale(outputScalingFactor);
	bounds.translate(outputTranslation);
}

void Vis::ReactionView2D::init()
{	
	if (!(reactionChanged || fontMetricsChanged || parameters->componentBoundsChanged() 
		  || parameters->viewportChanged() || parameters->alignmentChanged() 
		  || parameters->sizeAdjustmentChanged() || parameters->layoutChanged() 
		  || parameters->plusSignSizeChanged() || parameters->plusSignAttributeChanged()
		  || parameters->arrowSizeChanged() || parameters->arrowAttributeChanged() 
		  || parameters->componentVisibilityChanged()))
		return;

	initComponentLayout();
	initComponentLayoutDirection();
	initComponentMargin();
	initComponentVisibility();

	initAgentAlignment();
	initAgentLayout();
	initAgentLayoutDirection();

	initArrowStyle();
	initArrowLength();

	initPlusSignVisibility();

	if (reactionChanged || parameters->componentVisibilityChanged()) {
		freeComponentViews();
		initComponentViews();
	}

	if (reactionChanged || fontMetricsChanged || parameters->componentBoundsChanged()
		|| parameters->componentVisibilityChanged())
		initComponentBoundsTable();

	if (reactionChanged || parameters->arrowSizeChanged() || parameters->componentVisibilityChanged() 
		|| parameters->plusSignSizeChanged() || parameters->layoutChanged())
		calcArrowDimensions();

	if (reactionChanged || parameters->plusSignSizeChanged())
		calcPlusSignDimensions();

	if (reactionChanged || fontMetricsChanged || parameters->componentBoundsChanged()
		|| parameters->arrowSizeChanged() || parameters->plusSignSizeChanged() 
		|| parameters->layoutChanged() || parameters->componentVisibilityChanged())
		layoutReaction();

	if (reactionChanged || fontMetricsChanged || parameters->componentBoundsChanged()
		|| parameters->arrowSizeChanged() || parameters->plusSignSizeChanged()
		|| parameters->layoutChanged() || parameters->viewportChanged()
		|| parameters->alignmentChanged() || parameters->sizeAdjustmentChanged()
		|| parameters->componentVisibilityChanged()) {

		calcOutputTransforms();
		initComponentViewViewports();
	}

	if (reactionChanged || fontMetricsChanged || parameters->componentBoundsChanged()
		|| parameters->arrowSizeChanged() || parameters->plusSignSizeChanged() 
		|| parameters->layoutChanged() || parameters->viewportChanged() 
		|| parameters->alignmentChanged() || parameters->sizeAdjustmentChanged()
		|| parameters->componentVisibilityChanged() || parameters->plusSignAttributeChanged()
		|| parameters->arrowAttributeChanged()) {

		freeGraphicsPrimitives();
		createPlusSignPrimitives();
		createArrowPrimitives();
	}

	reactionChanged    = false;
	fontMetricsChanged = false;

	parameters->clearChangeFlags();
}

void Vis::ReactionView2D::paintBackground(Renderer2D& renderer) const
{
	if (!parameters->eraseBackground())
		return;

	renderer.setPen(Pen::NO_LINE);
	renderer.setBrush(parameters->getBackgroundColor());

	Rectangle2D rect = (parameters->getViewport().isDefined() ? parameters->getViewport() : totalReactionBounds);

	renderer.drawRectangle(rect.getMin()(0), rect.getMin()(1), rect.getWidth(), rect.getHeight());
}

void Vis::ReactionView2D::renderComponents(Renderer2D& renderer) const
{
	std::for_each(componentViews.begin(), componentViews.end(),
				  std::bind(&StructureView2D::render, std::placeholders::_1, std::ref(renderer)));
}

void Vis::ReactionView2D::renderGraphicsPrimitives(Renderer2D& renderer) const
{
	std::for_each(drawList.begin(), drawList.end(),
				  std::bind(&GraphicsPrimitive2D::render, std::placeholders::_1, std::ref(renderer)));
}

void Vis::ReactionView2D::initComponentViews()
{
	using namespace Chem;

	componentViews.clear();

	if (showReactants) {
		Reaction::ConstComponentIterator comps_end = reaction->getComponentsEnd(ReactionRole::REACTANT);

		for (Reaction::ConstComponentIterator it = reaction->getComponentsBegin(ReactionRole::REACTANT); it != comps_end; ++it)
			componentViews.push_back(allocComponentView(*it));
	}

	if (showAgents) {
		Reaction::ConstComponentIterator comps_end = reaction->getComponentsEnd(ReactionRole::AGENT);

		for (Reaction::ConstComponentIterator it = reaction->getComponentsBegin(ReactionRole::AGENT); it != comps_end; ++it)
			componentViews.push_back(allocComponentView(*it));
	}

	if (showProducts) {
		Reaction::ConstComponentIterator comps_end = reaction->getComponentsEnd(ReactionRole::PRODUCT);

		for (Reaction::ConstComponentIterator it = reaction->getComponentsBegin(ReactionRole::PRODUCT); it != comps_end; ++it)
			componentViews.push_back(allocComponentView(*it));
	}
}

void Vis::ReactionView2D::initComponentBoundsTable()
{
	componentBounds.clear();

	ComponentViewList::const_iterator views_end = componentViews.end();

	for (ComponentViewList::const_iterator it = componentViews.begin(); it != views_end; ++it) {
		StructureView2D* view = *it;

		setViewportParameter(*view, Rectangle2D());
		view->getModelBounds(componentBounds[view->getStructure()]);
	}
}

void Vis::ReactionView2D::layoutReaction()
{
	using namespace Chem;

	std::size_t num_comps = 0;
	std::size_t num_plus_signs = 0;

	componentPositions.clear();
	plusSignPositions.clear();

	double next_x_pos = 0.0;
	double min_y_pos = 0.0;
	double max_y_pos = 0.0;

	if (showReactants) {
		std::size_t num_reactants = reaction->getNumComponents(ReactionRole::REACTANT);

		layoutComponents(ReactionRole::REACTANT, 0, num_reactants);
	
		num_plus_signs = plusSignPositions.size();

		double y_dim_2 = totalComponentBounds.getHeight() * 0.5;
		double x_dim = totalComponentBounds.getWidth();

		Math::Vector2D pos_shift;
		totalComponentBounds.getCenter(pos_shift);

		pos_shift(0) = x_dim * 0.5 - pos_shift(0);
		pos_shift(1) = -pos_shift(1);

		shiftComponentPositions(0, num_reactants, pos_shift);
		shiftPlusSignPositions(0, num_plus_signs, pos_shift);

		num_comps = num_reactants;

		min_y_pos = -y_dim_2;
		max_y_pos = y_dim_2;

		next_x_pos = x_dim;
	}

	if (showAgents) {
		std::size_t num_agents = reaction->getNumComponents(ReactionRole::AGENT);

		if (arrowStyle == ArrowStyle::NONE || (agentAlignment & Alignment::V_ALIGNMENT_MASK) != Alignment::V_CENTER) {
			Math::Vector2D pos_shift;

			layoutComponents(Chem::ReactionRole::AGENT, 0, num_agents);

			double y_dim_2 = totalComponentBounds.getHeight() * 0.5;
			double x_dim = totalComponentBounds.getWidth();

			totalComponentBounds.getCenter(pos_shift);

			if (arrowStyle == ArrowStyle::NONE) { 
				pos_shift(0) = next_x_pos + x_dim * 0.5 - pos_shift(0);
				pos_shift(1) = -pos_shift(1);

				min_y_pos = std::min(-y_dim_2, min_y_pos);
				max_y_pos = std::max(y_dim_2, max_y_pos);

				next_x_pos += x_dim;

			} else {
				double arrow_width_2 = (maxUnscaledArrowWidth + unscaledArrowLineWidth) * 0.5;
				double products_x_offs;

				if (arrowLength.isRelative() && x_dim > unscaledArrowLength) {
					products_x_offs = x_dim;
					unscaledArrowLength = products_x_offs - unscaledArrowLineWidth;

				} else
					products_x_offs = std::max(x_dim, unscaledArrowLength + unscaledArrowLineWidth);
			
				double x_pos = next_x_pos + products_x_offs * 0.5;

				pos_shift(0) = x_pos - pos_shift(0);

				if ((agentAlignment & Alignment::V_ALIGNMENT_MASK) == Alignment::TOP) {
					pos_shift(1) = -y_dim_2 - arrow_width_2 - pos_shift(1);

					min_y_pos = std::min(-2.0 * y_dim_2 - arrow_width_2, min_y_pos);
					max_y_pos = std::max(arrow_width_2, max_y_pos);

				} else { 
					pos_shift(1) = y_dim_2 + arrow_width_2 - pos_shift(1);				

					min_y_pos = std::min(-arrow_width_2, min_y_pos);
					max_y_pos = std::max(2.0 * y_dim_2 + arrow_width_2, max_y_pos);
				}

				next_x_pos += products_x_offs;				

				arrowPosition(0) = x_pos;
				arrowPosition(1) = 0.0;
			}

			shiftComponentPositions(num_comps, componentPositions.size(), pos_shift);
			shiftPlusSignPositions(num_plus_signs, plusSignPositions.size(), pos_shift);

			num_comps += num_agents;
			num_plus_signs = plusSignPositions.size();

		} else {
			Math::Vector2D pos_shift1;
			Math::Vector2D pos_shift2;

			layoutComponents(Chem::ReactionRole::AGENT, 0, num_agents / 2);
			totalComponentBounds.getCenter(pos_shift1);

			std::size_t saved_num_plus_signs = plusSignPositions.size();
			std::size_t saved_num_comps = componentPositions.size();

			double x_dim1 = totalComponentBounds.getWidth();
			double y_dim1_2 = totalComponentBounds.getHeight() * 0.5;

			layoutComponents(Chem::ReactionRole::AGENT, num_agents / 2, num_agents);
			totalComponentBounds.getCenter(pos_shift2);

			double x_dim2 = totalComponentBounds.getWidth();
			double y_dim2_2 = totalComponentBounds.getHeight() * 0.5;

			double arrow_width_2 = (maxUnscaledArrowWidth + unscaledArrowLineWidth) * 0.5;

			double max_x_dim = std::max(x_dim1, x_dim2);
			double products_x_offs;

			if (arrowLength.isRelative() && max_x_dim > unscaledArrowLength) {
				products_x_offs = max_x_dim;
				unscaledArrowLength = products_x_offs - unscaledArrowLineWidth;

			} else
				products_x_offs = std::max(max_x_dim, unscaledArrowLength + unscaledArrowLineWidth);
			
			double x_pos = next_x_pos + products_x_offs * 0.5;

			pos_shift1(0) = x_pos - pos_shift1(0);
			pos_shift1(1) = -y_dim1_2 - arrow_width_2 - pos_shift1(1);

			pos_shift2(0) = x_pos - pos_shift2(0);
			pos_shift2(1) = y_dim2_2 + arrow_width_2 - pos_shift2(1);				

			shiftComponentPositions(num_comps, saved_num_comps, pos_shift1);

			num_comps = componentPositions.size();

			shiftComponentPositions(saved_num_comps, num_comps, pos_shift2);

			shiftPlusSignPositions(num_plus_signs, saved_num_plus_signs, pos_shift1);

			num_plus_signs = plusSignPositions.size();

			shiftPlusSignPositions(saved_num_plus_signs, num_plus_signs, pos_shift2);

			min_y_pos = std::min(-2.0 * y_dim1_2 - arrow_width_2, min_y_pos);
			max_y_pos = std::max(2.0 * y_dim2_2 + arrow_width_2, max_y_pos);

			next_x_pos += products_x_offs;				

			arrowPosition(0) = x_pos;
			arrowPosition(1) = 0.0;
		}

	} else if (arrowStyle != ArrowStyle::NONE) { 
		arrowPosition(0) = next_x_pos + unscaledArrowLength * 0.5;
		arrowPosition(1) = 0.0;

		double arrow_width_2 = (maxUnscaledArrowWidth + unscaledArrowLineWidth) * 0.5;

		min_y_pos = std::min(-arrow_width_2, min_y_pos);
		max_y_pos = std::max(arrow_width_2, max_y_pos);

		next_x_pos += unscaledArrowLength;
	}

	if (showProducts) {
		std::size_t num_products = reaction->getNumComponents(ReactionRole::PRODUCT);

		layoutComponents(ReactionRole::PRODUCT, 0, num_products);

		double y_dim_2 = totalComponentBounds.getHeight() * 0.5;
		double x_dim = totalComponentBounds.getWidth();

		Math::Vector2D pos_shift;
		totalComponentBounds.getCenter(pos_shift);

		pos_shift(0) = next_x_pos + x_dim * 0.5 - pos_shift(0);
		pos_shift(1) = -pos_shift(1);

		shiftComponentPositions(num_comps, componentPositions.size(), pos_shift);
		shiftPlusSignPositions(num_plus_signs, plusSignPositions.size(), pos_shift);

		min_y_pos = std::min(-y_dim_2, min_y_pos);
		max_y_pos = std::max(y_dim_2, max_y_pos);

		next_x_pos += x_dim;
	}

	totalReactionBounds.setBounds(0.0, min_y_pos, next_x_pos, max_y_pos);
}

void Vis::ReactionView2D::calcOutputTransforms()
{
	outputScalingFactor = 1.0;

	const Rectangle2D& viewport = parameters->getViewport();

	if (!viewport.isDefined()) {
		outputTranslation.clear();
		return;
	}

	double vp_x_dim = viewport.getWidth();
	double vp_y_dim = viewport.getHeight();
	
	double op_x_dim = totalReactionBounds.getWidth();
	double op_y_dim = totalReactionBounds.getHeight();

	switch (parameters->getSizeAdjustment()) {

		case SizeAdjustment::IF_REQUIRED: {
			double x_dim_ratio = vp_x_dim / op_x_dim;
			double y_dim_ratio = vp_y_dim / op_y_dim;

			if (x_dim_ratio >= 1.0 && y_dim_ratio >= 1.0)
				break;
			
			outputScalingFactor = std::min(x_dim_ratio, y_dim_ratio); 
			break;
		}

		case SizeAdjustment::BEST_FIT: {
			double x_dim_ratio = vp_x_dim / op_x_dim;
			double y_dim_ratio = vp_y_dim / op_y_dim;

			outputScalingFactor = std::min(x_dim_ratio, y_dim_ratio); 
		}

		default:
			break;
	}

	Math::Vector2D op_brect_ctr;
	totalReactionBounds.getCenter(op_brect_ctr);

	op_brect_ctr *= outputScalingFactor;

	Math::Vector2D vp_ctr;
	viewport.getCenter(vp_ctr);

	switch (parameters->getAlignment() & Alignment::H_ALIGNMENT_MASK) {

		case Alignment::H_CENTER:
			outputTranslation(0) = vp_ctr(0) - op_brect_ctr(0);
			break;

		case Alignment::LEFT:
			outputTranslation(0) = viewport.getMin()(0) + op_x_dim * outputScalingFactor * 0.5 - op_brect_ctr(0);
			break;

		case Alignment::RIGHT:
			outputTranslation(0) = viewport.getMax()(0) - op_x_dim * outputScalingFactor * 0.5 - op_brect_ctr(0);
			break;

		default:
			outputTranslation(0) = 0.0;
	}

	switch (parameters->getAlignment() & Alignment::V_ALIGNMENT_MASK) {

		case Alignment::V_CENTER:
			outputTranslation(1) = vp_ctr(1) - op_brect_ctr(1);
			return;

		case Alignment::TOP:
			outputTranslation(1) = viewport.getMin()(1) + op_y_dim * outputScalingFactor * 0.5 - op_brect_ctr(1);
			return;

		case Alignment::BOTTOM:
			outputTranslation(1) = viewport.getMax()(1) - op_y_dim * outputScalingFactor * 0.5 - op_brect_ctr(1);
			return;

		default:
			outputTranslation(1) = 0.0;
	}
}

void Vis::ReactionView2D::initComponentViewViewports()
{
	assert(componentViews.size() == componentPositions.size());

	Rectangle2D view_vp;
	Math::Vector2D view_vp_min;

	ComponentViewList::const_iterator views_end = componentViews.end();
	Vector2DArray::const_iterator p_it = componentPositions.begin();

	for (ComponentViewList::const_iterator r_it = componentViews.begin(); r_it != views_end; ++r_it, ++p_it) {
		StructureView2D* view = *r_it;
		const Rectangle2D& comp_brect = componentBounds[view->getStructure()];

		view_vp_min = *p_it * outputScalingFactor + outputTranslation;
 
		view_vp.setMin(view_vp_min);
		view_vp.setMax(view_vp_min(0) + comp_brect.getWidth() * outputScalingFactor,
						  view_vp_min(1) + comp_brect.getHeight() * outputScalingFactor);

		setViewportParameter(*view, view_vp);
	}
}

void Vis::ReactionView2D::createPlusSignPrimitives()
{
	if (!plusSignsVisible || plusSignPositions.empty())
		return;

	std::size_t num_plus_signs = plusSignPositions.size();

	LineSegmentListPrimitive2D* plus_sign_template = allocLineSegListPrimitive();

	plus_sign_template->setPen(Pen(getPlusSignColor(), unscaledPlusSignLineWidth * outputScalingFactor, 
								   Pen::SOLID_LINE, Pen::SQUARE_CAP, Pen::ROUND_JOIN));

	double size_2 = unscaledPlusSignSize * outputScalingFactor * 0.5;

	plus_sign_template->addElement(Math::vec(0.0, size_2));
	plus_sign_template->addElement(Math::vec(0.0, -size_2));
	plus_sign_template->addElement(Math::vec(size_2, 0.0));
	plus_sign_template->addElement(Math::vec(-size_2, 0.0));

	for (std::size_t i = 0; i < num_plus_signs; i++) {
		LineSegmentListPrimitive2D* plus_sign;

		if (i == num_plus_signs - 1)
			plus_sign = plus_sign_template;

		else {
			plus_sign = allocLineSegListPrimitive();
			*plus_sign = *plus_sign_template;
		}

		plus_sign->translate(plusSignPositions[i] * outputScalingFactor + outputTranslation);

		drawList.push_back(plus_sign);
	}
}

void Vis::ReactionView2D::createArrowPrimitives()
{
	switch (arrowStyle) {
		
		case ArrowStyle::NONE:
			return;

		case ArrowStyle::REACTION_HOLLOW:
			createStdReactionArrow(true);
			return;

		default:
			createStdReactionArrow(false);
	}
}

void Vis::ReactionView2D::createStdReactionArrow(bool hollow)
{
	double length_2 = unscaledArrowLength * 0.5 * outputScalingFactor;
	double head_length = unscaledArrowHeadLength * outputScalingFactor;
	double head_width_2 = unscaledArrowHeadWidth * 0.5 * outputScalingFactor;
	double shaft_width_2 = unscaledArrowShaftWidth * 0.5 * outputScalingFactor;

	PolygonPrimitive2D* arrow = allocPolygonPrimitive();

	arrow->addElement(Math::vec(-length_2, shaft_width_2));
	arrow->addElement(Math::vec(length_2 - head_length, shaft_width_2));
	arrow->addElement(Math::vec(length_2 - head_length, head_width_2));
	arrow->addElement(Math::vec(length_2, 0.0));
	arrow->addElement(Math::vec(length_2 - head_length, -head_width_2));
	arrow->addElement(Math::vec(length_2 - head_length, -shaft_width_2));
	arrow->addElement(Math::vec(-length_2, -shaft_width_2));

	const Color& color = getArrowColor();

	arrow->setPen(Pen(color, unscaledArrowLineWidth * outputScalingFactor, Pen::SOLID_LINE, Pen::ROUND_CAP, Pen::MITER_JOIN));
	arrow->setBrush(hollow ? Brush() : Brush(color));

	arrow->translate(arrowPosition * outputScalingFactor + outputTranslation);

	drawList.push_back(arrow);
}

void Vis::ReactionView2D::layoutComponents(unsigned int rxn_role, std::size_t start_idx, std::size_t end_idx)
{
	if (getComponentLayout(rxn_role) == LayoutStyle::PACKED)
		createPackedComponentLayout(rxn_role, start_idx, end_idx);
	else
		createLinearComponentLayout(rxn_role, start_idx, end_idx);
}

void Vis::ReactionView2D::createPackedComponentLayout(unsigned int rxn_role, std::size_t start_idx, std::size_t end_idx)
{
	using namespace Chem;

	std::size_t tot_num_comps = end_idx - start_idx;

	if (tot_num_comps == 0) {
		totalComponentBounds.setBounds(0.0, 0.0, 0.0, 0.0);
		return;
	}

	double margin = componentMargin.getValue();
	double plus_sign_dim = unscaledPlusSignSize + unscaledPlusSignLineWidth;
	double tot_linear_dim = tot_num_comps * margin * 2.0 + (tot_num_comps > 0 && plusSignsVisible ? (tot_num_comps - 1) * plus_sign_dim : 0.0);

	Reaction::ConstComponentIterator comps_beg = reaction->getComponentsBegin(rxn_role) + start_idx;
	Reaction::ConstComponentIterator comps_end = reaction->getComponentsBegin(rxn_role) + end_idx;

	for (Reaction::ConstComponentIterator it = comps_beg; it != comps_end; ++it) 
		tot_linear_dim += componentBounds[&*it].getWidth();

	double tgt_row_length = tot_linear_dim / std::sqrt(double(tot_num_comps));

	typedef std::vector<const Molecule*> ComponentRow;
	typedef std::pair<double, double> RowDimension;

	std::vector<ComponentRow> layout;
	std::vector<RowDimension> row_dimensions;

	double max_y_dim = 0.0;
	double row_length = 0.0;
	double max_row_length = 0.0;

	std::size_t row_idx = 0;

	for (Reaction::ConstComponentIterator it = comps_beg; it != comps_end; ) {
		if (row_idx >= layout.size())
			layout.resize(row_idx + 1);

		const Molecule* comp = &*it;
		const Rectangle2D& brect = componentBounds[comp];

		bool last_comp = !(++it != comps_end);

		row_length += margin * 2.0;

		if (plusSignsVisible && !last_comp) 
			row_length += plus_sign_dim;

		layout[row_idx].push_back(comp);

		row_length += brect.getWidth();
		max_y_dim = std::max(max_y_dim, brect.getHeight());
		
		if (last_comp || row_length >= tgt_row_length) {
			row_dimensions.push_back(RowDimension(row_length, max_y_dim + 2.0 * margin));
			
			max_row_length = std::max(max_row_length, row_length);

			max_y_dim = 0.0;
			row_length = 0.0;

			row_idx++;
		}
	}

	double row_y_offs = 0.0;
	double plus_sign_size_inc = plus_sign_dim * 0.5;

	Math::Vector2D comp_pos;
	Math::Vector2D plus_sign_pos;

	std::size_t num_rows = layout.size();

	for (std::size_t i = 0; i < num_rows; i++) {
		const ComponentRow& layout_row = layout[i];
		const RowDimension& row_dim = row_dimensions[i];

		std::size_t row_size = layout_row.size();
		double x_pos = (max_row_length - row_dim.first) * 0.5;

		plus_sign_pos(1) = row_y_offs + row_dim.second * 0.5;

		for (std::size_t j = 0; j < row_size; j++) {
			const Molecule* comp = layout_row[j];
			const Rectangle2D& brect = componentBounds[comp];
		
			x_pos += margin;

			comp_pos(0) = x_pos;
			comp_pos(1) = plus_sign_pos(1) - brect.getHeight() * 0.5;

			componentPositions.push_back(comp_pos);

			x_pos += brect.getWidth() + margin;

			if (plusSignsVisible && (i < num_rows - 1 || j < row_size - 1)) {
				x_pos += plus_sign_size_inc;

				plus_sign_pos(0) = x_pos;

				plusSignPositions.push_back(plus_sign_pos);

				x_pos += plus_sign_size_inc;
			}
		}

		row_y_offs += row_dim.second;
	}

	totalComponentBounds.setBounds(0.0, 0.0, max_row_length, row_y_offs);
}

void Vis::ReactionView2D::createLinearComponentLayout(unsigned int rxn_role, std::size_t start_idx, std::size_t end_idx)
{
	if (getComponentLayoutDirection(rxn_role) == LayoutDirection::VERTICAL)
		createVLinearComponentLayout(rxn_role, start_idx, end_idx);
	else
		createHLinearComponentLayout(rxn_role, start_idx, end_idx);
}

void Vis::ReactionView2D::createHLinearComponentLayout(unsigned int rxn_role, std::size_t start_idx, std::size_t end_idx)
{
	using namespace Chem;

	double max_y_dim = 0.0;
	double margin = componentMargin.getValue();
	double x_pos = 0.0;
	double plus_sign_size_inc = (unscaledPlusSignSize + unscaledPlusSignLineWidth) * 0.5;

	Math::Vector2D plus_sign_pos;
	Math::Vector2D comp_pos;

	bool first_comp = true;

	Reaction::ConstComponentIterator comps_end = reaction->getComponentsBegin(rxn_role) + end_idx;
	
	for (Reaction::ConstComponentIterator it = reaction->getComponentsBegin(rxn_role) + start_idx; it != comps_end; ++it) {
		const Molecule* comp = &*it;
		const Rectangle2D& brect = componentBounds[comp];

		double y_dim = brect.getHeight();
		max_y_dim = std::max(max_y_dim, y_dim);

		if (plusSignsVisible && !first_comp) {
			x_pos += plus_sign_size_inc;

			plus_sign_pos(0) = x_pos;

			plusSignPositions.push_back(plus_sign_pos);

			x_pos += plus_sign_size_inc;
		}

		x_pos += margin;

		comp_pos(0) = x_pos;
		comp_pos(1) = -y_dim * 0.5;

		componentPositions.push_back(comp_pos);

		x_pos += brect.getWidth() + margin;
		first_comp = false;
	}

	totalComponentBounds.setBounds(0.0, -max_y_dim * 0.5 - margin, x_pos, max_y_dim * 0.5 + margin);
}

void Vis::ReactionView2D::createVLinearComponentLayout(unsigned int rxn_role, std::size_t start_idx, std::size_t end_idx)
{
	using namespace Chem;

	double max_x_dim = 0.0;
	double margin = componentMargin.getValue();
	double y_pos = 0.0;
	double plus_sign_size_inc = (unscaledPlusSignSize + unscaledPlusSignLineWidth) * 0.5;

	Math::Vector2D plus_sign_pos;
	Math::Vector2D comp_pos;

	bool first_comp = true;

	Reaction::ConstComponentIterator comps_end = reaction->getComponentsBegin(rxn_role) + end_idx;
	
	for (Reaction::ConstComponentIterator it = reaction->getComponentsBegin(rxn_role) + start_idx; it != comps_end; ++it) {
		const Molecule* comp = &*it;
		const Rectangle2D& brect = componentBounds[comp];

		double x_dim = brect.getWidth();
		max_x_dim = std::max(max_x_dim, x_dim);

		if (plusSignsVisible && !first_comp) {
			y_pos += plus_sign_size_inc;

			plus_sign_pos(1) = y_pos;
			plusSignPositions.push_back(plus_sign_pos);

			y_pos += plus_sign_size_inc;
		}

		y_pos += margin;

		comp_pos(0) = -x_dim * 0.5;
		comp_pos(1) = y_pos;

		componentPositions.push_back(comp_pos);

		y_pos += brect.getHeight() + margin;
		first_comp = false;
	}

	totalComponentBounds.setBounds(-max_x_dim * 0.5 - margin, 0.0, max_x_dim * 0.5 + margin, y_pos);
}

unsigned int Vis::ReactionView2D::getComponentLayout(unsigned int rxn_role) const
{
	return (rxn_role == Chem::ReactionRole::AGENT ? agentLayout : componentLayout);
}

unsigned int Vis::ReactionView2D::getComponentLayoutDirection(unsigned int rxn_role) const
{
	return (rxn_role == Chem::ReactionRole::AGENT ? agentLayoutDirection : componentLayoutDirection);
}

void Vis::ReactionView2D::shiftComponentPositions(std::size_t start_idx, std::size_t end_idx, const Math::Vector2D& shift)
{
	while (start_idx < end_idx)
		componentPositions[start_idx++] += shift;
}

void Vis::ReactionView2D::shiftPlusSignPositions(std::size_t start_idx, std::size_t end_idx, const Math::Vector2D& shift)
{
	while (start_idx < end_idx)
		plusSignPositions[start_idx++] += shift;
}

void Vis::ReactionView2D::calcArrowDimensions()
{
	if (arrowStyle == ArrowStyle::NONE) 
		return;

	unscaledArrowLength = arrowLength.getValue();

	const SizeSpecification& head_length = getArrowHeadLength();

	if (!head_length.isRelative()) 
		unscaledArrowHeadLength = head_length.getValue();
	else
		unscaledArrowHeadLength = head_length.getValue() * unscaledArrowLength;

	const SizeSpecification& head_width = getArrowHeadWidth();

	if (!head_width.isRelative()) 
		unscaledArrowHeadWidth = head_width.getValue();
	else
		unscaledArrowHeadWidth = head_width.getValue() * unscaledArrowLength;

	const SizeSpecification& shaft_width = getArrowShaftWidth();

	if (!shaft_width.isRelative()) 
		unscaledArrowShaftWidth = shaft_width.getValue();
	else
		unscaledArrowShaftWidth = shaft_width.getValue() * unscaledArrowLength;

	const SizeSpecification& line_width = getArrowLineWidth();

	if (!line_width.isRelative()) 
		unscaledArrowLineWidth = line_width.getValue();
	else
		unscaledArrowLineWidth = line_width.getValue() * unscaledArrowLength;

	maxUnscaledArrowWidth = std::max(unscaledArrowShaftWidth, unscaledArrowHeadWidth);
}

void Vis::ReactionView2D::calcPlusSignDimensions()
{
	if (!plusSignsVisible) 
		return;

	unscaledPlusSignSize = getPlusSignSize().getValue();

	const SizeSpecification& line_width = getPlusSignLineWidth();

	if (!line_width.isRelative()) 
		unscaledPlusSignLineWidth = line_width.getValue();
	else
		unscaledPlusSignLineWidth = line_width.getValue() * unscaledPlusSignSize;
}

void Vis::ReactionView2D::initArrowStyle()
{
	if (!hasArrowStyle(*reaction))
		arrowStyle = parameters->getArrowStyle();
	else
		arrowStyle = getArrowStyle(*reaction);
}

const Vis::Color& Vis::ReactionView2D::getArrowColor() const
{
	if (!hasArrowColor(*reaction))
		return parameters->getArrowColor();

	return Vis::getArrowColor(*reaction);
}

void Vis::ReactionView2D::initArrowLength()
{
	if (!hasArrowLength(*reaction))
		arrowLength = parameters->getArrowLength();
	else
		arrowLength = getArrowLength(*reaction);
}

const Vis::SizeSpecification& Vis::ReactionView2D::getArrowHeadLength() const
{
	if (!hasArrowHeadLength(*reaction))
		return parameters->getArrowHeadLength();

	return Vis::getArrowHeadLength(*reaction);
}

const Vis::SizeSpecification& Vis::ReactionView2D::getArrowHeadWidth() const
{
	if (!hasArrowHeadWidth(*reaction))
		return parameters->getArrowHeadWidth();

	return Vis::getArrowHeadWidth(*reaction);
}

const Vis::SizeSpecification& Vis::ReactionView2D::getArrowShaftWidth() const
{
	if (!hasArrowShaftWidth(*reaction))
		return parameters->getArrowShaftWidth();

	return Vis::getArrowShaftWidth(*reaction);
}

const Vis::SizeSpecification& Vis::ReactionView2D::getArrowLineWidth() const
{
	if (!hasArrowLineWidth(*reaction))
		return parameters->getArrowLineWidth();

	return Vis::getArrowLineWidth(*reaction);
}

void Vis::ReactionView2D::initComponentLayout()
{
	if (!hasComponentLayout(*reaction))
		componentLayout = parameters->getComponentLayout();
	else
		componentLayout = Vis::getComponentLayout(*reaction);
}

void Vis::ReactionView2D::initComponentLayoutDirection()
{
	if (!hasComponentLayoutDirection(*reaction))
		componentLayoutDirection = parameters->getComponentLayoutDirection();
	else
		componentLayoutDirection = Vis::getComponentLayoutDirection(*reaction);
}

void Vis::ReactionView2D::initComponentMargin()
{
	if (!hasComponentMargin(*reaction))
		componentMargin = parameters->getComponentMargin();
	else
		componentMargin = getComponentMargin(*reaction);
}

void Vis::ReactionView2D::initComponentVisibility()
{
	if (!hasShowReactants(*reaction))
		showReactants = parameters->showReactants();
	else
		showReactants = getShowReactants(*reaction);

	if (!hasShowAgents(*reaction))
		showAgents = parameters->showAgents();
	else
		showAgents = getShowAgents(*reaction);
	
	if (!hasShowProducts(*reaction))
		showProducts = parameters->showProducts();
	else
		showProducts = getShowProducts(*reaction);
}

void Vis::ReactionView2D::initAgentAlignment()
{
	if (!hasAgentAlignment(*reaction))
		agentAlignment = parameters->getAgentAlignment();
	else
		agentAlignment = getAgentAlignment(*reaction);
}

void Vis::ReactionView2D::initAgentLayout()
{
	if (!hasAgentLayout(*reaction))
		agentLayout = parameters->getAgentLayout();
	else
		agentLayout = getAgentLayout(*reaction);
}

void Vis::ReactionView2D::initAgentLayoutDirection()
{
	if (!hasAgentLayoutDirection(*reaction))
		agentLayoutDirection = parameters->getAgentLayoutDirection();
	else
		agentLayoutDirection = getAgentLayoutDirection(*reaction);
}

const Vis::Color& Vis::ReactionView2D::getPlusSignColor() const
{
	if (!hasPlusSignColor(*reaction))
		return parameters->getPlusSignColor();

	return Vis::getPlusSignColor(*reaction);
}

const Vis::SizeSpecification& Vis::ReactionView2D::getPlusSignSize() const
{
	if (!hasPlusSignSize(*reaction))
		return parameters->getPlusSignSize();

	return Vis::getPlusSignSize(*reaction);
}

const Vis::SizeSpecification& Vis::ReactionView2D::getPlusSignLineWidth() const
{
	if (!hasPlusSignLineWidth(*reaction))
		return parameters->getPlusSignLineWidth();

	return Vis::getPlusSignLineWidth(*reaction);
}

void Vis::ReactionView2D::initPlusSignVisibility()
{
	if (!hasShowPlusSigns(*reaction))
		plusSignsVisible = parameters->showPlusSigns();
	else
		plusSignsVisible = getShowPlusSigns(*reaction);
}

void Vis::ReactionView2D::freeComponentViews()
{
	compViewCache.putAll();
}

void Vis::ReactionView2D::freeGraphicsPrimitives()
{
	polygonCache.putAll();
	lineSegListCache.putAll();

	drawList.clear();
}

Vis::StructureView2D* Vis::ReactionView2D::allocComponentView(const Chem::Molecule& comp)
{
	StructureView2D* view = compViewCache.getRaw();

	setAlignmentParameter(*view, Alignment::CENTER);
	setSizeAdjustmentParameter(*view, SizeAdjustment::BEST_FIT);
	
	view->setParent(this);
	view->setFontMetrics(fontMetrics);
	view->setStructure(&comp);

	return view;
}

Vis::PolygonPrimitive2D* Vis::ReactionView2D::allocPolygonPrimitive()
{
	PolygonPrimitive2D* prim = polygonCache.getRaw();

	prim->clear();

	return prim;
}

Vis::LineSegmentListPrimitive2D* Vis::ReactionView2D::allocLineSegListPrimitive()
{
	LineSegmentListPrimitive2D* prim = lineSegListCache.getRaw();

	prim->clear();

	return prim;
}
