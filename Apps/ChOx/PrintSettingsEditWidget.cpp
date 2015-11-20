/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * PrintSettingsEditWidget.cpp 
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
#include <QLabel>
#include <QFrame>
#include <QGroupBox>
#include <QCheckBox>

#include "PrintSettingsEditWidget.hpp"
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


PrintSettingsEditWidget::PrintSettingsEditWidget(QWidget* parent, Settings& settings): 
	SettingsEditWidget(parent), settings(settings)
{
	init();
}

bool PrintSettingsEditWidget::haveChangedSettings() const
{
	return haveChanges;
}

void PrintSettingsEditWidget::apply()
{
	setPrintingTextLabelFontParameter(settings, textLabelFont);
	setPrintingTextLabelSizeParameter(settings, textLabelSize);
	setPrintingTextLabelSpacingParameter(settings, textLabelSpacing);
	setPrintingTextLabelColorParameter(settings, textLabelColor);

	setFrameLineWidthParameter(settings, frameLineWidth);
	setFrameLineColorParameter(settings, frameColor);
	setFrameLineStyleParameter(settings, frameLineStyle);

	setPageNumberLabelAlignmentParameter(settings, pageNumberAlignment);
	setDateLabelAlignmentParameter(settings, dateAlignment);
	setFileNameLabelAlignmentParameter(settings, fileNameAlignment);

	setPrintFrameParameter(settings, printFrameCheckBox->isChecked());
	setPrintDateParameter(settings, printDateCheckBox->isChecked());
	setPrintPageNumberParameter(settings, printPageNumberCheckBox->isChecked());
	setPrintFileNameParameter(settings, printFileNameCheckBox->isChecked());
}

void PrintSettingsEditWidget::reset()
{
	blockSignals(true);

	textLabelFont = getPrintingTextLabelFontParameter(settings); 
	textLabelSize = getPrintingTextLabelSizeParameter(settings); 
	textLabelSpacing = getPrintingTextLabelSpacingParameter(settings); 
	textLabelColor = getPrintingTextLabelColorParameter(settings); 

	frameLineWidth = getFrameLineWidthParameter(settings); 
	frameColor = getFrameLineColorParameter(settings); 
	frameLineStyle = getFrameLineStyleParameter(settings); 

	pageNumberAlignment = getPageNumberLabelAlignmentParameter(settings); 
	dateAlignment = getDateLabelAlignmentParameter(settings); 
	fileNameAlignment = getFileNameLabelAlignmentParameter(settings); 

	printFrameCheckBox->setChecked(getPrintFrameParameter(settings)); 
	printDateCheckBox->setChecked(getPrintDateParameter(settings)); 
	printPageNumberCheckBox->setChecked(getPrintPageNumberParameter(settings)); 
	printFileNameCheckBox->setChecked(getPrintFileNameParameter(settings)); 

	blockSignals(false);

	haveChanges = false;

	emit updateGUI();
}

void PrintSettingsEditWidget::setDefaults()
{
	textLabelSize = ControlParameterDefault::PRINTING_TEXT_LABEL_SIZE;
	textLabelSpacing = ControlParameterDefault::PRINTING_TEXT_LABEL_SPACING;
	textLabelColor = ControlParameterDefault::PRINTING_TEXT_LABEL_COLOR;

	frameLineWidth = ControlParameterDefault::FRAME_LINE_WIDTH;
	frameColor = ControlParameterDefault::FRAME_LINE_COLOR;
	frameLineStyle = ControlParameterDefault::FRAME_LINE_STYLE;

	pageNumberAlignment = ControlParameterDefault::PAGE_NUMBER_LABEL_ALIGNMENT;
	dateAlignment = ControlParameterDefault::DATE_LABEL_ALIGNMENT;
	fileNameAlignment = ControlParameterDefault::FILE_NAME_LABEL_ALIGNMENT;

	printFrameCheckBox->setChecked(ControlParameterDefault::PRINT_FRAME);
	printDateCheckBox->setChecked(ControlParameterDefault::PRINT_DATE);
	printPageNumberCheckBox->setChecked(ControlParameterDefault::PRINT_PAGE_NUMBER);
	printFileNameCheckBox->setChecked(ControlParameterDefault::PRINT_FILE_NAME);

	haveChanges = true;

	emit updateGUI();
	emit settingsChanged();
}

void PrintSettingsEditWidget::handleSettingsChange()
{
	haveChanges = true;

	emit SettingsEditWidget::settingsChanged();
}

void PrintSettingsEditWidget::handleSettingsChange(bool)
{
	haveChanges = true;

	emit SettingsEditWidget::settingsChanged();
}

void PrintSettingsEditWidget::init()
{
	QBoxLayout* main_layout= new QVBoxLayout(this);

	// --------

	QGroupBox* group_box = new QGroupBox(tr("Print"), this);
	QGridLayout* grid_layout = new QGridLayout(group_box);

	// +++

	printFrameCheckBox = new QCheckBox(tr("Fra&me"), group_box);

	grid_layout->addWidget(printFrameCheckBox, 0, 0);

	connect(printFrameCheckBox, SIGNAL(toggled(bool)), this, SLOT(handleSettingsChange(bool)));

	// +++

	printDateCheckBox = new QCheckBox(tr("C&urrent Date"), group_box);

	grid_layout->addWidget(printDateCheckBox, 0, 1);

	connect(printDateCheckBox, SIGNAL(toggled(bool)), this, SLOT(handleSettingsChange(bool)));

	// +++

	printFileNameCheckBox = new QCheckBox(tr("File Name&(s)"), group_box);

	grid_layout->addWidget(printFileNameCheckBox, 1, 0);

	connect(printFileNameCheckBox, SIGNAL(toggled(bool)), this, SLOT(handleSettingsChange(bool)));

	// +++

	printPageNumberCheckBox = new QCheckBox(tr("Pa&ge Number"), group_box);

	grid_layout->addWidget(printPageNumberCheckBox, 1, 1);

	connect(printPageNumberCheckBox, SIGNAL(toggled(bool)), this, SLOT(handleSettingsChange(bool)));

	// +++

	main_layout->addWidget(group_box);

	// --------

	group_box = new QGroupBox(tr("Colors"), this);

	grid_layout = new QGridLayout(group_box);

	// +++

	QLabel* label = new QLabel(tr("&Frame Color:"), group_box);

	ColorEditWidget* color_edit_widget = new ColorEditWidget(group_box, frameColor);

	label->setBuddy(color_edit_widget);

	grid_layout->addWidget(label, 0, 0);
	grid_layout->addWidget(color_edit_widget, 0, 1);

	connect(this, SIGNAL(updateGUI()), color_edit_widget, SLOT(updateGUI()));
	connect(color_edit_widget, SIGNAL(colorChanged()), this, SLOT(handleSettingsChange()));

	// +++

	label = new QLabel(tr("Te&xt Color:"), group_box);

	color_edit_widget = new ColorEditWidget(group_box, textLabelColor);

	label->setBuddy(color_edit_widget);

	grid_layout->addWidget(label, 1, 0);
	grid_layout->addWidget(color_edit_widget, 1, 1);

	connect(this, SIGNAL(updateGUI()), color_edit_widget, SLOT(updateGUI()));
	connect(color_edit_widget, SIGNAL(colorChanged()), this, SLOT(handleSettingsChange()));

	// +++

	main_layout->addWidget(group_box);

	// --------

	QFrame* frame = new QFrame(this);

	frame->setFrameStyle(QFrame::StyledPanel);

	QBoxLayout* h_box_layout = new QHBoxLayout(frame);

	// +++

	FontEditWidget* font_edit_widget = new FontEditWidget(frame, textLabelFont, textLabelSize, 0, false, false);

	QLabel* font_label = new QLabel(tr("T&ext Font:"), frame);

	font_label->setBuddy(font_edit_widget);

	h_box_layout->addWidget(font_label);

	connect(this, SIGNAL(updateGUI()), font_edit_widget, SLOT(updateGUI()));
	connect(font_edit_widget, SIGNAL(fontChanged()), this, SLOT(handleSettingsChange()));

	h_box_layout->addWidget(font_edit_widget);

	// +++

	main_layout->addWidget(frame);

	// --------

	h_box_layout = new QHBoxLayout();

	main_layout->addLayout(h_box_layout);

	// +++

	group_box = new QGroupBox(tr("Text/Frame Spacing"), this);

	QBoxLayout* h_box_layout2 = new QHBoxLayout(group_box);

	SizeSpecEditWidget* size_edit_widget = new SizeSpecEditWidget(group_box, textLabelSpacing, false, false, false);

	h_box_layout2->addWidget(size_edit_widget);

	connect(this, SIGNAL(updateGUI()), size_edit_widget, SLOT(updateGUI()));
	connect(size_edit_widget, SIGNAL(sizeSpecChanged()), this, SLOT(handleSettingsChange()));

	h_box_layout->addWidget(group_box, 1);

	// +++

	group_box = new QGroupBox(tr("Frame Line Thickness"), this);

	h_box_layout2 = new QHBoxLayout(group_box);

	size_edit_widget = new SizeSpecEditWidget(group_box, frameLineWidth, false, false, false);

	h_box_layout2->addWidget(size_edit_widget);

	connect(this, SIGNAL(updateGUI()), size_edit_widget, SLOT(updateGUI()));
	connect(size_edit_widget, SIGNAL(sizeSpecChanged()), this, SLOT(handleSettingsChange()));

	h_box_layout->addWidget(group_box, 1);

	// +++

	group_box = new QGroupBox(tr("Frame Line Style"), this);

	h_box_layout2 = new QHBoxLayout(group_box);

	LineStyleEditWidget* style_edit_widget = new LineStyleEditWidget(group_box, frameLineStyle);

	h_box_layout2->addWidget(style_edit_widget);

	connect(this, SIGNAL(updateGUI()), style_edit_widget, SLOT(updateGUI()));
	connect(style_edit_widget, SIGNAL(lineStyleChanged()), this, SLOT(handleSettingsChange()));

	h_box_layout->addWidget(group_box, 1);

	// --------

	h_box_layout = new QHBoxLayout();

	main_layout->addLayout(h_box_layout);

	// +++

	group_box = new QGroupBox(tr("Date Alignment"), this);

	QVBoxLayout* v_box_layout = new QVBoxLayout(group_box);

	// +++

	label = new QLabel(tr("&Horizontal:"), group_box);

	AlignmentEditWidget* alignment_edit_widget = new AlignmentEditWidget(group_box, dateAlignment, true);

	label->setBuddy(alignment_edit_widget);

	v_box_layout->addWidget(label);
	v_box_layout->addWidget(alignment_edit_widget);

	connect(this, SIGNAL(updateGUI()), alignment_edit_widget, SLOT(updateGUI()));
	connect(alignment_edit_widget, SIGNAL(alignmentChanged()), this, SLOT(handleSettingsChange()));

	// +++

	label = new QLabel(tr("&Vertical:"), group_box);

	alignment_edit_widget = new AlignmentEditWidget(group_box, dateAlignment, false, false);

	label->setBuddy(alignment_edit_widget);

	v_box_layout->addWidget(label);
	v_box_layout->addWidget(alignment_edit_widget);

	connect(this, SIGNAL(updateGUI()), alignment_edit_widget, SLOT(updateGUI()));
	connect(alignment_edit_widget, SIGNAL(alignmentChanged()), this, SLOT(handleSettingsChange()));

	// +++

	h_box_layout->addWidget(group_box);

	// +++

	group_box = new QGroupBox(tr("Page Number Alignment"), this);

	v_box_layout = new QVBoxLayout(group_box);

	// +++

	label = new QLabel(tr("Hori&zontal:"), group_box);

	alignment_edit_widget = new AlignmentEditWidget(group_box, pageNumberAlignment, true);

	label->setBuddy(alignment_edit_widget);

	v_box_layout->addWidget(label);
	v_box_layout->addWidget(alignment_edit_widget);

	connect(this, SIGNAL(updateGUI()), alignment_edit_widget, SLOT(updateGUI()));
	connect(alignment_edit_widget, SIGNAL(alignmentChanged()), this, SLOT(handleSettingsChange()));

	// +++

	label = new QLabel(tr("Ver&tical:"), group_box);

	alignment_edit_widget = new AlignmentEditWidget(group_box, pageNumberAlignment, false, false);

	label->setBuddy(alignment_edit_widget);

	v_box_layout->addWidget(label);
	v_box_layout->addWidget(alignment_edit_widget);

	connect(this, SIGNAL(updateGUI()), alignment_edit_widget, SLOT(updateGUI()));
	connect(alignment_edit_widget, SIGNAL(alignmentChanged()), this, SLOT(handleSettingsChange()));

	// +++

	h_box_layout->addWidget(group_box);

	// +++

	group_box = new QGroupBox(tr("File Name Alignment"), this);

	v_box_layout = new QVBoxLayout(group_box);

	// +++

	label = new QLabel(tr("Horizo&ntal:"), group_box);

	alignment_edit_widget = new AlignmentEditWidget(group_box, fileNameAlignment, true);

	label->setBuddy(alignment_edit_widget);

	v_box_layout->addWidget(label);
	v_box_layout->addWidget(alignment_edit_widget);

	connect(this, SIGNAL(updateGUI()), alignment_edit_widget, SLOT(updateGUI()));
	connect(alignment_edit_widget, SIGNAL(alignmentChanged()), this, SLOT(handleSettingsChange()));

	// +++

	label = new QLabel(tr("Vertica&l:"), group_box);

	alignment_edit_widget = new AlignmentEditWidget(group_box, fileNameAlignment, false, false);

	label->setBuddy(alignment_edit_widget);

	v_box_layout->addWidget(label);
	v_box_layout->addWidget(alignment_edit_widget);

	connect(this, SIGNAL(updateGUI()), alignment_edit_widget, SLOT(updateGUI()));
	connect(alignment_edit_widget, SIGNAL(alignmentChanged()), this, SLOT(handleSettingsChange()));

	// +++

	h_box_layout->addWidget(group_box);

	// --------

	main_layout->addStretch();

	reset();
}

