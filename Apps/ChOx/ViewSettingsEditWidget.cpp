/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * ViewSettingsEditWidget.cpp 
 *
 * This file is part of the Chemical Data Processing Toolkit
 *
 * Copyright (C) 2003-2010 Thomas A. Seidel <thomas.seidel@univie.ac.at>
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


#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QGroupBox>
#include <QLabel>
#include <QCheckBox>

#include "CDPL/Vis/ControlParameterFunctions.hpp"
#include "CDPL/Vis/ControlParameterDefault.hpp"

#include "ViewSettingsEditWidget.hpp"
#include "FontEditWidget.hpp"
#include "ColorEditWidget.hpp"
#include "SizeSpecEditWidget.hpp"
#include "LineStyleEditWidget.hpp"
#include "AlignmentEditWidget.hpp"
#include "SizeAdjustmentEditWidget.hpp"
#include "ControlParameterFunctions.hpp"
#include "ControlParameterDefault.hpp"
#include "Settings.hpp"


using namespace ChOx;


ViewSettingsEditWidget::ViewSettingsEditWidget(QWidget* parent, Settings& settings): 
	SettingsEditWidget(parent), settings(settings)
{
	init();
}

bool ViewSettingsEditWidget::haveChangedSettings() const
{
	return haveChanges;
}

void ViewSettingsEditWidget::apply()
{
	using namespace CDPL;
	using namespace Vis;

	setViewBackgroundColorParameter(settings, backgroundColor);
	setViewSelectionColorParameter(settings, selectionColor);

	setViewportMarginParameter(settings, viewportMargin);

	setRecordNumberLabelFontParameter(settings, recordNumberFont);
	setRecordNumberLabelSizeParameter(settings, recordNumberSize);
	setRecordNumberLabelColorParameter(settings, recordNumberColor);
	setRecordNumberLabelAlignmentParameter(settings, recordNumberAlignment);

	setRecordNameLabelFontParameter(settings, recordNameFont);
	setRecordNameLabelSizeParameter(settings, recordNameSize);
	setRecordNameLabelColorParameter(settings, recordNameColor);
	setRecordNameLabelAlignmentParameter(settings, recordNameAlignment);

	setGridLineWidthParameter(settings, gridLineWidth);
	setGridLineColorParameter(settings, gridColor);
	setGridLineStyleParameter(settings, gridLineStyle);

	setSizeAdjustmentParameter(settings, recordSizeAdjustment);
	setAlignmentParameter(settings, recordAlignment);

	setShowGridParameter(settings, showGridCheckBox->isChecked());
	setShowRecordNumbersParameter(settings, showRecordNumbersCheckBox->isChecked());
	setShowRecordNamesParameter(settings, showRecordNamesCheckBox->isChecked());
}

void ViewSettingsEditWidget::reset()
{
	using namespace CDPL;
	using namespace Vis;

	blockSignals(true);

	backgroundColor = getViewBackgroundColorParameter(settings); 
	selectionColor = getViewSelectionColorParameter(settings); 

	viewportMargin = getViewportMarginParameter(settings); 

	recordNumberFont = getRecordNumberLabelFontParameter(settings); 
	recordNumberSize = getRecordNumberLabelSizeParameter(settings); 
	recordNumberColor = getRecordNumberLabelColorParameter(settings); 
	recordNumberAlignment = getRecordNumberLabelAlignmentParameter(settings); 

	recordNameFont = getRecordNameLabelFontParameter(settings); 
	recordNameSize = getRecordNameLabelSizeParameter(settings); 
	recordNameColor = getRecordNameLabelColorParameter(settings); 
	recordNameAlignment = getRecordNameLabelAlignmentParameter(settings); 

	gridLineWidth = getGridLineWidthParameter(settings); 
	gridColor = getGridLineColorParameter(settings); 
	gridLineStyle = getGridLineStyleParameter(settings); 

	recordSizeAdjustment = getSizeAdjustmentParameter(settings); 
	recordAlignment = getAlignmentParameter(settings); 

	showGridCheckBox->setChecked(getShowGridParameter(settings)); 
	showRecordNumbersCheckBox->setChecked(getShowRecordNumbersParameter(settings)); 
	showRecordNamesCheckBox->setChecked(getShowRecordNamesParameter(settings)); 

	blockSignals(false);

	haveChanges = false;

	emit updateGUI();
}

void ViewSettingsEditWidget::setDefaults()
{
	using namespace CDPL;

	backgroundColor = ControlParameterDefault::VIEW_BACKGROUND_COLOR;
	selectionColor = ControlParameterDefault::VIEW_SELECTION_COLOR;

	viewportMargin = ControlParameterDefault::VIEWPORT_MARGIN;

	recordNumberFont = ControlParameterDefault::RECORD_NUMBER_LABEL_FONT;
	recordNumberSize = ControlParameterDefault::RECORD_NUMBER_LABEL_SIZE;
	recordNumberColor = ControlParameterDefault::RECORD_NUMBER_LABEL_COLOR;
	recordNumberAlignment = ControlParameterDefault::RECORD_NUMBER_LABEL_ALIGNMENT;

	recordNameFont = ControlParameterDefault::RECORD_NAME_LABEL_FONT;
	recordNameSize = ControlParameterDefault::RECORD_NAME_LABEL_SIZE;
	recordNameColor = ControlParameterDefault::RECORD_NAME_LABEL_COLOR;
	recordNameAlignment = ControlParameterDefault::RECORD_NAME_LABEL_ALIGNMENT;

	gridLineWidth = ControlParameterDefault::GRID_LINE_WIDTH;
	gridColor = ControlParameterDefault::GRID_LINE_COLOR;
	gridLineStyle = ControlParameterDefault::GRID_LINE_STYLE;

	recordSizeAdjustment = Vis::ControlParameterDefault::SIZE_ADJUSTMENT;
	recordAlignment = Vis::ControlParameterDefault::ALIGNMENT;

	showGridCheckBox->setChecked(ControlParameterDefault::SHOW_GRID);
	showRecordNumbersCheckBox->setChecked(ControlParameterDefault::SHOW_RECORD_NUMBERS);
	showRecordNamesCheckBox->setChecked(ControlParameterDefault::SHOW_RECORD_NAMES);

	haveChanges = true;

	emit updateGUI();
	emit settingsChanged();
}

void ViewSettingsEditWidget::handleSettingsChange()
{
	haveChanges = true;

	emit SettingsEditWidget::settingsChanged();
}

void ViewSettingsEditWidget::handleSettingsChange(bool)
{
	haveChanges = true;

	emit SettingsEditWidget::settingsChanged();
}

void ViewSettingsEditWidget::init()
{
	QBoxLayout* main_layout= new QVBoxLayout(this);

	// --------

	QGroupBox* group_box = new QGroupBox(tr("Show"), this);
	QHBoxLayout* h_box_layout = new QHBoxLayout(group_box);

	showGridCheckBox = new QCheckBox(tr("&Grid"), group_box);

	h_box_layout->addWidget(showGridCheckBox);

	connect(showGridCheckBox, SIGNAL(toggled(bool)), this, SLOT(handleSettingsChange(bool)));

	// +++

	showRecordNumbersCheckBox = new QCheckBox(tr("Record &Numbers"), group_box);

	h_box_layout->addWidget(showRecordNumbersCheckBox);

	connect(showRecordNumbersCheckBox, SIGNAL(toggled(bool)), this, SLOT(handleSettingsChange(bool)));

	// +++

	showRecordNamesCheckBox = new QCheckBox(tr("Record &Names"), group_box);

	h_box_layout->addWidget(showRecordNamesCheckBox);

	connect(showRecordNamesCheckBox, SIGNAL(toggled(bool)), this, SLOT(handleSettingsChange(bool)));

	main_layout->addWidget(group_box);

	// --------

	group_box = new QGroupBox(tr("Colors"), this);

	QGridLayout* grid_layout = new QGridLayout(group_box);

	// +++

	QLabel* label = new QLabel(tr("&Background Color:"), group_box);

	ColorEditWidget* color_edit_widget = new ColorEditWidget(group_box, backgroundColor);

	label->setBuddy(color_edit_widget);

	grid_layout->addWidget(label, 0, 0);
	grid_layout->addWidget(color_edit_widget, 0, 1);

	connect(this, SIGNAL(updateGUI()), color_edit_widget, SLOT(updateGUI()));
	connect(color_edit_widget, SIGNAL(colorChanged()), this, SLOT(handleSettingsChange()));

	// +++

	label = new QLabel(tr("S&election Color:"), group_box);

	color_edit_widget = new ColorEditWidget(group_box, selectionColor);

	label->setBuddy(color_edit_widget);

	grid_layout->addWidget(label, 1, 0);
	grid_layout->addWidget(color_edit_widget, 1, 1);

	connect(this, SIGNAL(updateGUI()), color_edit_widget, SLOT(updateGUI()));
	connect(color_edit_widget, SIGNAL(colorChanged()), this, SLOT(handleSettingsChange()));

	// +++

	label = new QLabel(tr("Gr&id Color:"), group_box);

	color_edit_widget = new ColorEditWidget(group_box, gridColor);

	label->setBuddy(color_edit_widget);

	grid_layout->addWidget(label, 2, 0);
	grid_layout->addWidget(color_edit_widget, 2, 1);

	connect(this, SIGNAL(updateGUI()), color_edit_widget, SLOT(updateGUI()));
	connect(color_edit_widget, SIGNAL(colorChanged()), this, SLOT(handleSettingsChange()));

	// +++

	label = new QLabel(tr("Record N&umber Color:"), group_box);

	color_edit_widget = new ColorEditWidget(group_box, recordNumberColor);

	label->setBuddy(color_edit_widget);

	grid_layout->addWidget(label, 3, 0);
	grid_layout->addWidget(color_edit_widget, 3, 1);

	connect(this, SIGNAL(updateGUI()), color_edit_widget, SLOT(updateGUI()));
	connect(color_edit_widget, SIGNAL(colorChanged()), this, SLOT(handleSettingsChange()));

	// +++

	label = new QLabel(tr("Record Name Color:"), group_box);

	color_edit_widget = new ColorEditWidget(group_box, recordNameColor);

	label->setBuddy(color_edit_widget);

	grid_layout->addWidget(label, 4, 0);
	grid_layout->addWidget(color_edit_widget, 4, 1);

	connect(this, SIGNAL(updateGUI()), color_edit_widget, SLOT(updateGUI()));
	connect(color_edit_widget, SIGNAL(colorChanged()), this, SLOT(handleSettingsChange()));

	// +++

	main_layout->addWidget(group_box);

	// --------

	h_box_layout = new QHBoxLayout();
	main_layout->addLayout(h_box_layout);

	// --------

	group_box = new QGroupBox(tr("Record Number Font"), this);

	h_box_layout->addWidget(group_box);

	QBoxLayout* h_box_layout2 = new QHBoxLayout(group_box);

	// +++

	FontEditWidget* font_edit_widget = new FontEditWidget(group_box, recordNumberFont, recordNumberSize, 0, false, false);

	connect(this, SIGNAL(updateGUI()), font_edit_widget, SLOT(updateGUI()));
	connect(font_edit_widget, SIGNAL(fontChanged()), this, SLOT(handleSettingsChange()));

	h_box_layout2->addWidget(font_edit_widget);

	// --------

	group_box = new QGroupBox(tr("Record Name Font"), this);

	h_box_layout->addWidget(group_box);

	h_box_layout2 = new QHBoxLayout(group_box);

	// +++

	font_edit_widget = new FontEditWidget(group_box, recordNameFont, recordNameSize, 0, false, false);

	connect(this, SIGNAL(updateGUI()), font_edit_widget, SLOT(updateGUI()));
	connect(font_edit_widget, SIGNAL(fontChanged()), this, SLOT(handleSettingsChange()));

	h_box_layout2->addWidget(font_edit_widget);

	// --------

	h_box_layout = new QHBoxLayout();

	main_layout->addLayout(h_box_layout);

	// +++

	group_box = new QGroupBox(tr("Grid Line Thickness"), this);

	SizeSpecEditWidget* size_edit_widget = new SizeSpecEditWidget(group_box, gridLineWidth, false, false, false);

	h_box_layout2 = new QHBoxLayout(group_box);

	h_box_layout2->addWidget(size_edit_widget);

	connect(this, SIGNAL(updateGUI()), size_edit_widget, SLOT(updateGUI()));
	connect(size_edit_widget, SIGNAL(sizeSpecChanged()), this, SLOT(handleSettingsChange()));

	h_box_layout->addWidget(group_box, 1);

	// +++

	group_box = new QGroupBox(tr("Grid Line Style"), this);

	LineStyleEditWidget* style_edit_widget = new LineStyleEditWidget(group_box, gridLineStyle);
	
	h_box_layout2 = new QHBoxLayout(group_box);

	h_box_layout2->addWidget(style_edit_widget);

	connect(this, SIGNAL(updateGUI()), style_edit_widget, SLOT(updateGUI()));
	connect(style_edit_widget, SIGNAL(lineStyleChanged()), this, SLOT(handleSettingsChange()));

	h_box_layout->addWidget(group_box, 1);

	// --------

	group_box = new QGroupBox(tr("Record Margin"), this);

	size_edit_widget = new SizeSpecEditWidget(group_box, viewportMargin, false, false, false);

	h_box_layout2 = new QHBoxLayout(group_box);

	h_box_layout2->addWidget(size_edit_widget);

	connect(this, SIGNAL(updateGUI()), size_edit_widget, SLOT(updateGUI()));
	connect(size_edit_widget, SIGNAL(sizeSpecChanged()), this, SLOT(handleSettingsChange()));

	h_box_layout->addWidget(group_box, 1);

	// +++	

	group_box = new QGroupBox(tr("Record Size Adjustment"), this);

	SizeAdjustmentEditWidget* adjustment_edit_widget = new SizeAdjustmentEditWidget(group_box, recordSizeAdjustment);

	h_box_layout2 = new QHBoxLayout(group_box);

	h_box_layout2->addWidget(adjustment_edit_widget);

	connect(this, SIGNAL(updateGUI()), adjustment_edit_widget, SLOT(updateGUI()));
	connect(adjustment_edit_widget, SIGNAL(sizeAdjustmentChanged()), this, SLOT(handleSettingsChange()));

	h_box_layout->addWidget(group_box, 1);

	// --------

	h_box_layout2 = new QHBoxLayout();
	main_layout->addLayout(h_box_layout2);

	// --------

	group_box = new QGroupBox(tr("Record Number Alignment"), this);

	h_box_layout2->addWidget(group_box);

	QVBoxLayout* v_box_layout = new QVBoxLayout(group_box);

	// +++

	label = new QLabel(tr("&Horizontal:"), group_box);

	AlignmentEditWidget* alignment_edit_widget = new AlignmentEditWidget(group_box, recordNumberAlignment, true);

	label->setBuddy(alignment_edit_widget);

	v_box_layout->addWidget(label);
	v_box_layout->addWidget(alignment_edit_widget);

	connect(this, SIGNAL(updateGUI()), alignment_edit_widget, SLOT(updateGUI()));
	connect(alignment_edit_widget, SIGNAL(alignmentChanged()), this, SLOT(handleSettingsChange()));

	// +++

	label = new QLabel(tr("&Vertical:"), group_box);

	alignment_edit_widget = new AlignmentEditWidget(group_box, recordNumberAlignment, false, false);

	label->setBuddy(alignment_edit_widget);

	v_box_layout->addWidget(label);
	v_box_layout->addWidget(alignment_edit_widget);

	connect(this, SIGNAL(updateGUI()), alignment_edit_widget, SLOT(updateGUI()));
	connect(alignment_edit_widget, SIGNAL(alignmentChanged()), this, SLOT(handleSettingsChange()));

	// +++

	group_box = new QGroupBox(tr("Record Name Alignment"), this);

	h_box_layout2->addWidget(group_box);

	v_box_layout = new QVBoxLayout(group_box);

	// +++

	label = new QLabel(tr("Horizontal:"), group_box);

	alignment_edit_widget = new AlignmentEditWidget(group_box, recordNameAlignment, true);

	label->setBuddy(alignment_edit_widget);

	v_box_layout->addWidget(label);
	v_box_layout->addWidget(alignment_edit_widget);

	connect(this, SIGNAL(updateGUI()), alignment_edit_widget, SLOT(updateGUI()));
	connect(alignment_edit_widget, SIGNAL(alignmentChanged()), this, SLOT(handleSettingsChange()));

	// +++

	label = new QLabel(tr("Vertical:"), group_box);

	alignment_edit_widget = new AlignmentEditWidget(group_box, recordNameAlignment, false, false);

	label->setBuddy(alignment_edit_widget);

	v_box_layout->addWidget(label);
	v_box_layout->addWidget(alignment_edit_widget);

	connect(this, SIGNAL(updateGUI()), alignment_edit_widget, SLOT(updateGUI()));
	connect(alignment_edit_widget, SIGNAL(alignmentChanged()), this, SLOT(handleSettingsChange()));

	// +++

	group_box = new QGroupBox(tr("Record Alignment"), this);

	h_box_layout2->addWidget(group_box);

	v_box_layout = new QVBoxLayout(group_box);

	// +++

	label = new QLabel(tr("Hori&zontal:"), group_box);

	alignment_edit_widget = new AlignmentEditWidget(group_box, recordAlignment, true);

	label->setBuddy(alignment_edit_widget);

	v_box_layout->addWidget(label);
	v_box_layout->addWidget(alignment_edit_widget);

	connect(this, SIGNAL(updateGUI()), alignment_edit_widget, SLOT(updateGUI()));
	connect(alignment_edit_widget, SIGNAL(alignmentChanged()), this, SLOT(handleSettingsChange()));

	// +++

	label = new QLabel(tr("Ver&tical:"), group_box);

	alignment_edit_widget = new AlignmentEditWidget(group_box, recordAlignment, false);

	label->setBuddy(alignment_edit_widget);

	v_box_layout->addWidget(label);
	v_box_layout->addWidget(alignment_edit_widget);

	connect(this, SIGNAL(updateGUI()), alignment_edit_widget, SLOT(updateGUI()));
	connect(alignment_edit_widget, SIGNAL(alignmentChanged()), this, SLOT(handleSettingsChange()));

	// --------

	main_layout->addStretch();

	reset();
}
