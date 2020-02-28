/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * ReactionSettingsEditWidget.cpp 
 *
 * This file is part of the Chemical Data Processing Toolkit
 *
 * Copyright (C) 2003-2020 Thomas A. Seidel <thomas.seidel@univie.ac.at>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program; see the file COPYING. If not, write to
 * the Free Software Foundation, Inc., 59 Temple Place - Suite 330,
 * Boston, MA 02111-1307, USA.
 */


#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QLabel>
#include <QGroupBox>
#include <QCheckBox>

#include "CDPL/Vis/ControlParameterFunctions.hpp"
#include "CDPL/Vis/ControlParameterDefault.hpp"

#include "ReactionSettingsEditWidget.hpp"
#include "FontEditWidget.hpp"
#include "ColorEditWidget.hpp"
#include "SizeSpecEditWidget.hpp"
#include "LayoutEditWidget.hpp"
#include "AlignmentEditWidget.hpp"
#include "ArrowStyleEditWidget.hpp"
#include "Settings.hpp"


using namespace ChOx;


ReactionSettingsEditWidget::ReactionSettingsEditWidget(QWidget* parent, Settings& settings): 
	SettingsEditWidget(parent), settings(settings)
{
	init();
}

bool ReactionSettingsEditWidget::haveChangedSettings() const
{
	return haveChanges;
}

void ReactionSettingsEditWidget::apply()
{
	using namespace CDPL;
	using namespace Vis;

	setReactionPlusSignSizeParameter(settings, plusSignSize);
	setReactionPlusSignLineWidthParameter(settings, plusSignLineWidth);

	setShowReactionPlusSignsParameter(settings, showPlusSignsCheckBox->isChecked());

	setReactionComponentMarginParameter(settings, componentMargin);

	setReactionArrowColorParameter(settings, arrowColor);
	setReactionPlusSignColorParameter(settings, plusSignColor);

	setReactionArrowLengthParameter(settings, arrowLength);
	setReactionArrowHeadLengthParameter(settings, arrowHeadLength);
	setReactionArrowHeadWidthParameter(settings, arrowHeadWidth);
	setReactionArrowShaftWidthParameter(settings, arrowShaftWidth);
	setReactionArrowLineWidthParameter(settings, arrowLineWidth);

	setReactionArrowStyleParameter(settings, arrowStyle);
	
	setReactionAgentAlignmentParameter(settings, agentAlignment);
	setReactionAgentLayoutParameter(settings, agentLayoutStyle);
	setReactionAgentLayoutDirectionParameter(settings, agentLayoutDir);

	setReactionComponentLayoutParameter(settings, componentLayoutStyle);
	setReactionComponentLayoutDirectionParameter(settings, componentLayoutDir);

	setShowReactionReactantsParameter(settings, showReactantsCheckBox->isChecked());
	setShowReactionAgentsParameter(settings, showAgentsCheckBox->isChecked());
	setShowReactionProductsParameter(settings, showProductsCheckBox->isChecked());
}

void ReactionSettingsEditWidget::reset()
{
	using namespace CDPL;
	using namespace Vis;

	blockSignals(true);

	plusSignSize = getReactionPlusSignSizeParameter(settings);
	plusSignLineWidth = getReactionPlusSignLineWidthParameter(settings);

	showPlusSignsCheckBox->setChecked(getShowReactionPlusSignsParameter(settings));

	componentMargin = getReactionComponentMarginParameter(settings);

	plusSignColor = getReactionPlusSignColorParameter(settings);
	arrowColor = getReactionArrowColorParameter(settings);

	arrowLength = getReactionArrowLengthParameter(settings);
	arrowHeadLength = getReactionArrowHeadLengthParameter(settings);
	arrowHeadWidth = getReactionArrowHeadWidthParameter(settings);
	arrowShaftWidth = getReactionArrowShaftWidthParameter(settings);
	arrowLineWidth = getReactionArrowLineWidthParameter(settings);
	arrowStyle = getReactionArrowStyleParameter(settings);
	
	agentAlignment = getReactionAgentAlignmentParameter(settings);
	agentLayoutStyle = getReactionAgentLayoutParameter(settings);
	agentLayoutDir = getReactionAgentLayoutDirectionParameter(settings);

	componentLayoutStyle = getReactionComponentLayoutParameter(settings);
	componentLayoutDir = getReactionComponentLayoutDirectionParameter(settings);

	showReactantsCheckBox->setChecked(getShowReactionReactantsParameter(settings));
	showAgentsCheckBox->setChecked(getShowReactionAgentsParameter(settings));
	showProductsCheckBox->setChecked(getShowReactionProductsParameter(settings));

	blockSignals(false);

	haveChanges = false;

	emit updateGUI();
}

void ReactionSettingsEditWidget::setDefaults()
{
	using namespace CDPL;
	using namespace Vis;
	using namespace ControlParameterDefault;

	plusSignSize = REACTION_PLUS_SIGN_SIZE;
	plusSignLineWidth = REACTION_PLUS_SIGN_LINE_WIDTH;

	componentMargin = REACTION_COMPONENT_MARGIN;

	plusSignColor = REACTION_PLUS_SIGN_COLOR;
	arrowColor = REACTION_ARROW_COLOR;

	arrowLength = REACTION_ARROW_LENGTH;
	arrowHeadLength = REACTION_ARROW_HEAD_LENGTH;
	arrowHeadWidth = REACTION_ARROW_HEAD_WIDTH;
	arrowShaftWidth = REACTION_ARROW_SHAFT_WIDTH;
	arrowLineWidth = REACTION_ARROW_LINE_WIDTH;

	agentAlignment = REACTION_AGENT_ALIGNMENT;
	agentLayoutStyle = REACTION_AGENT_LAYOUT;
	agentLayoutDir = REACTION_AGENT_LAYOUT_DIRECTION;

	componentLayoutStyle = REACTION_COMPONENT_LAYOUT;
	componentLayoutDir = REACTION_COMPONENT_LAYOUT_DIRECTION;

	showPlusSignsCheckBox->setChecked(SHOW_REACTION_PLUS_SIGNS);

	showReactantsCheckBox->setChecked(SHOW_REACTION_REACTANTS);
	showAgentsCheckBox->setChecked(SHOW_REACTION_AGENTS);
	showProductsCheckBox->setChecked(SHOW_REACTION_PRODUCTS);

	haveChanges = true;

	emit updateGUI();
	emit settingsChanged();
}

void ReactionSettingsEditWidget::handleSettingsChange()
{
	haveChanges = true;

	emit SettingsEditWidget::settingsChanged();
}

void ReactionSettingsEditWidget::handleSettingsChange(int)
{
	haveChanges = true;

	emit SettingsEditWidget::settingsChanged();
}

void ReactionSettingsEditWidget::handleSettingsChange(bool)
{
	haveChanges = true;

	emit SettingsEditWidget::settingsChanged();
}

void ReactionSettingsEditWidget::init()
{
	QBoxLayout* main_layout = new QVBoxLayout(this);
	
	// --------

	QGroupBox* group_box = new QGroupBox(tr("Show"), this);
	QGridLayout* grid_layout = new QGridLayout(group_box);

	// +++

	showReactantsCheckBox = new QCheckBox(tr("R&eactants"), group_box);

	grid_layout->addWidget(showReactantsCheckBox, 0, 0);

	connect(showReactantsCheckBox, SIGNAL(toggled(bool)), this, SLOT(handleSettingsChange(bool)));

	// +++

	showAgentsCheckBox = new QCheckBox(tr("A&gents"), group_box);

	grid_layout->addWidget(showAgentsCheckBox, 0, 1);

	connect(showAgentsCheckBox, SIGNAL(toggled(bool)), this, SLOT(handleSettingsChange(bool)));

	// +++

	showProductsCheckBox = new QCheckBox(tr("&Products"), group_box);

	grid_layout->addWidget(showProductsCheckBox, 1, 0);

	connect(showProductsCheckBox, SIGNAL(toggled(bool)), this, SLOT(handleSettingsChange(bool)));

	// +++

	showPlusSignsCheckBox = new QCheckBox(tr("Component Plus &Signs"), group_box);

	grid_layout->addWidget(showPlusSignsCheckBox, 1, 1);

	connect(showPlusSignsCheckBox, SIGNAL(toggled(bool)), this, SLOT(handleSettingsChange(bool)));

	// +++

	setFocusProxy(showReactantsCheckBox);

	main_layout->addWidget(group_box);

	// --------

	group_box = new QGroupBox(tr("Colors"), this);
	grid_layout = new QGridLayout(group_box);

	// +++

	QLabel* label = new QLabel(tr("Arro&w Color:"), group_box);

	ColorEditWidget* color_edit_widget = new ColorEditWidget(group_box, arrowColor);

	label->setBuddy(color_edit_widget);

	grid_layout->addWidget(label, 0, 0);
	grid_layout->addWidget(color_edit_widget, 0, 1);

	connect(this, SIGNAL(updateGUI()), color_edit_widget, SLOT(updateGUI()));
	connect(color_edit_widget, SIGNAL(colorChanged()), this, SLOT(handleSettingsChange()));

	// +++

	label = new QLabel(tr("Plus Sig&n Color:"), group_box);

	color_edit_widget = new ColorEditWidget(group_box, plusSignColor);

	label->setBuddy(color_edit_widget);

	grid_layout->addWidget(label, 1, 0);
	grid_layout->addWidget(color_edit_widget, 1, 1);

	connect(this, SIGNAL(updateGUI()), color_edit_widget, SLOT(updateGUI()));
	connect(color_edit_widget, SIGNAL(colorChanged()), this, SLOT(handleSettingsChange()));

	// +++

	main_layout->addWidget(group_box);

	// --------

	QBoxLayout* h_box_layout = new QHBoxLayout();

	main_layout->addLayout(h_box_layout);

	// +++

	group_box = new QGroupBox(tr("Arrow Style"), this);
	
	QVBoxLayout* v_box_layout = new QVBoxLayout(group_box);

	ArrowStyleEditWidget* arrow_edit_widget = new ArrowStyleEditWidget(group_box, arrowStyle);

	v_box_layout->addWidget(arrow_edit_widget);

	connect(this, SIGNAL(updateGUI()), arrow_edit_widget, SLOT(updateGUI()));
	connect(arrow_edit_widget, SIGNAL(arrowStyleChanged()), this, SLOT(handleSettingsChange()));

	h_box_layout->addWidget(group_box);

	// +++

	group_box = new QGroupBox(tr("Agent Alignment"), this);
	v_box_layout = new QVBoxLayout(group_box);

	AlignmentEditWidget* alignment_edit_widget = new AlignmentEditWidget(group_box, agentAlignment, false);

	v_box_layout->addWidget(alignment_edit_widget);

	connect(this, SIGNAL(updateGUI()), alignment_edit_widget, SLOT(updateGUI()));
	connect(alignment_edit_widget, SIGNAL(alignmentChanged()), this, SLOT(handleSettingsChange()));

	h_box_layout->addWidget(group_box);

	// --------

	h_box_layout = new QHBoxLayout();

	main_layout->addLayout(h_box_layout);

	// +++

	group_box = new QGroupBox(tr("Metrics"), this);

	grid_layout = new QGridLayout(group_box);

	// +++

	label = new QLabel(tr("Plus Sign Si&ze:"), group_box);

	SizeSpecEditWidget* size_edit_widget = new SizeSpecEditWidget(group_box, plusSignSize, false, false, false);	

	label->setBuddy(size_edit_widget);

	grid_layout->addWidget(label, 0, 0);
	grid_layout->addWidget(size_edit_widget, 0, 1);

	connect(this, SIGNAL(updateGUI()), size_edit_widget, SLOT(updateGUI()));
	connect(size_edit_widget, SIGNAL(sizeSpecChanged()), this, SLOT(handleSettingsChange()));

	// +++

	label = new QLabel(tr("Plus Sign &Line Thickness:"), group_box);

	size_edit_widget = new SizeSpecEditWidget(group_box, plusSignLineWidth, true, false, false);

	label->setBuddy(size_edit_widget);

	grid_layout->addWidget(label, 1, 0);
	grid_layout->addWidget(size_edit_widget, 1, 1);

	connect(this, SIGNAL(updateGUI()), size_edit_widget, SLOT(updateGUI()));
	connect(size_edit_widget, SIGNAL(sizeSpecChanged()), this, SLOT(handleSettingsChange()));

	// +++

	label = new QLabel(tr("Component &Margin:"), group_box);

	size_edit_widget = new SizeSpecEditWidget(group_box, componentMargin, false, false, false);

	label->setBuddy(size_edit_widget);

	grid_layout->addWidget(label, 2, 0);
	grid_layout->addWidget(size_edit_widget, 2, 1);

	connect(this, SIGNAL(updateGUI()), size_edit_widget, SLOT(updateGUI()));
	connect(size_edit_widget, SIGNAL(sizeSpecChanged()), this, SLOT(handleSettingsChange()));

	// +++

	label = new QLabel(tr("Minimum Arrow Lengt&h:"), group_box);

	size_edit_widget = new SizeSpecEditWidget(group_box, arrowLength, false, false, false);

	label->setBuddy(size_edit_widget);

	grid_layout->addWidget(label, 3, 0);
	grid_layout->addWidget(size_edit_widget, 3, 1);

	connect(this, SIGNAL(updateGUI()), size_edit_widget, SLOT(updateGUI()));
	connect(size_edit_widget, SIGNAL(sizeSpecChanged()), this, SLOT(handleSettingsChange()));

	// +++

	label = new QLabel(tr("Arrow Head Lengt&h:"), group_box);

	size_edit_widget = new SizeSpecEditWidget(group_box, arrowHeadLength, true, false, false);

	label->setBuddy(size_edit_widget);

	grid_layout->addWidget(label, 4, 0);
	grid_layout->addWidget(size_edit_widget, 4, 1);

	connect(this, SIGNAL(updateGUI()), size_edit_widget, SLOT(updateGUI()));
	connect(size_edit_widget, SIGNAL(sizeSpecChanged()), this, SLOT(handleSettingsChange()));

	// +++

	label = new QLabel(tr("Arrow Head W&idth:"), group_box);

	size_edit_widget = new SizeSpecEditWidget(group_box, arrowHeadWidth, true, false, false);

	label->setBuddy(size_edit_widget);

	grid_layout->addWidget(label, 5, 0);
	grid_layout->addWidget(size_edit_widget, 5, 1);

	connect(this, SIGNAL(updateGUI()), size_edit_widget, SLOT(updateGUI()));
	connect(size_edit_widget, SIGNAL(sizeSpecChanged()), this, SLOT(handleSettingsChange()));

	// +++

	label = new QLabel(tr("Arrow Sha&ft Width:"), group_box);

	size_edit_widget = new SizeSpecEditWidget(group_box, arrowShaftWidth, true, false, false);

	label->setBuddy(size_edit_widget);

	grid_layout->addWidget(label, 6, 0);
	grid_layout->addWidget(size_edit_widget, 6, 1);

	connect(this, SIGNAL(updateGUI()), size_edit_widget, SLOT(updateGUI()));
	connect(size_edit_widget, SIGNAL(sizeSpecChanged()), this, SLOT(handleSettingsChange()));

	// +++

	h_box_layout->addWidget(group_box, 1);

	// --------

	v_box_layout = new QVBoxLayout();

	h_box_layout->addLayout(v_box_layout);
	h_box_layout->setStretchFactor(v_box_layout, 1);

	// +++

	group_box = new QGroupBox(tr("Agent Layout"), this);
	QVBoxLayout* v_box_layout2 = new QVBoxLayout(group_box);

	LayoutEditWidget* layout_edit_widget = new LayoutEditWidget(group_box, agentLayoutStyle, agentLayoutDir);

	v_box_layout2->addWidget(layout_edit_widget);

	connect(this, SIGNAL(updateGUI()), layout_edit_widget, SLOT(updateGUI()));
	connect(layout_edit_widget, SIGNAL(layoutChanged()), this, SLOT(handleSettingsChange()));

	v_box_layout->addWidget(group_box);

	// --------

	group_box = new QGroupBox(tr("Reactant/Product Layout"), this);
	v_box_layout2 = new QVBoxLayout(group_box);

	layout_edit_widget = new LayoutEditWidget(group_box, componentLayoutStyle, componentLayoutDir);

	v_box_layout2->addWidget(layout_edit_widget);

	connect(this, SIGNAL(updateGUI()), layout_edit_widget, SLOT(updateGUI()));
	connect(layout_edit_widget, SIGNAL(layoutChanged()), this, SLOT(handleSettingsChange()));

	v_box_layout->addWidget(group_box);
	v_box_layout->addStretch();

	// --------

	main_layout->addStretch();

	reset();
}
