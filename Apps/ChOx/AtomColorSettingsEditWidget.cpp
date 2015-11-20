/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * AtomColorSettingsEditWidget.cpp 
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


#include <cstddef>

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QLabel>
#include <QGroupBox>
#include <QFrame>
#include <QCheckBox>
#include <QSizePolicy>

#include "CDPL/Vis/ControlParameterFunctions.hpp"
#include "CDPL/Vis/ControlParameterDefault.hpp"

#include "AtomColorSettingsEditWidget.hpp"
#include "AtomColorButton.hpp"
#include "ColorEditWidget.hpp"
#include "Settings.hpp"
#include "ControlParameterFunctions.hpp"
#include "ControlParameterDefault.hpp"


namespace
{

	struct ElementPos
	{

		std::size_t atomicNo;
		int         row;
		int         col;
	};

	struct LabelPos
	{

		const char* text;
		int         row;
		int         col;
		int         size;
	};

	const ElementPos elementPositions[] = {
		{ 1, 1, 1 }, { 2, 1, 18 },
		{ 3, 2, 1 }, { 4, 2, 2 },
		{ 5, 2, 13 }, { 6, 2, 14 }, { 7, 2, 15 }, { 8, 2, 16 }, { 9, 2, 17 }, { 10, 2, 18 },
		{ 11, 3, 1 }, { 12, 3, 2 }, { 13, 3, 13 }, { 14, 3, 14 }, { 15, 3, 15 }, { 16, 3, 16 }, { 17, 3, 17 }, { 18, 3, 18 },
		{ 19, 4, 1 }, { 20, 4, 2 }, { 21, 4, 3 }, { 22, 4, 4 }, { 23, 4, 5 }, { 24, 4, 6 }, { 25, 4, 7 }, { 26, 4, 8 }, { 27, 4, 9 },
		{ 28, 4, 10 }, { 29, 4, 11 }, { 30, 4, 12 }, { 31, 4, 13 }, { 32, 4, 14 }, { 33, 4, 15 }, { 34, 4, 16 }, { 35, 4, 17 }, 
		{ 36, 4, 18 }, { 37, 5, 1 }, { 38, 5, 2 }, { 39, 5, 3 }, { 40, 5, 4 }, { 41, 5, 5 }, { 42, 5, 6 }, { 43, 5, 7 }, { 44, 5, 8 },
		{ 45, 5, 9 }, { 46, 5, 10 }, { 47, 5, 11 }, { 48, 5, 12 }, { 49, 5, 13 }, { 50, 5, 14 }, { 51, 5, 15 }, { 52, 5, 16 }, 
		{ 53, 5, 17 }, { 54, 5, 18 }, { 55, 6, 1 }, { 56, 6, 2 }, { 72, 6, 4 }, { 73, 6, 5 }, { 74, 6, 6 }, { 75, 6, 7 }, { 76, 6, 8 },
		{ 77, 6, 9 }, { 78, 6, 10 }, { 79, 6, 11 }, { 80, 6, 12 }, { 81, 6, 13 }, { 82, 6, 14 }, { 83, 6, 15 }, { 84, 6, 16 }, 
		{ 85, 6, 17 }, { 86, 6, 18 }, { 87, 7, 1 }, { 88, 7, 2 }, { 104, 7, 4 }, { 105, 7, 5 }, { 106, 7, 6 }, { 107, 7, 7 }, 
		{ 108, 7, 8 }, { 109, 7, 9 }, { 57, 9, 4 }, { 58, 9, 5 }, { 59, 9, 6 }, { 60, 9, 7 }, { 61, 9, 8 }, { 62, 9, 9 }, { 63, 9, 10 },
		{ 64, 9, 11 }, { 65, 9, 12 }, { 66, 9, 13 }, { 67, 9, 14 }, { 68, 9, 15 }, { 69, 9, 16 }, { 70, 9, 17 }, { 71, 9, 18 },
		{ 89, 10, 4 }, { 90, 10, 5 }, { 91, 10, 6 }, { 92, 10, 7 }, { 93, 10, 8 }, { 94, 10, 9 }, { 95, 10, 10 }, { 96, 10, 11 },
		{ 97, 10, 12 }, { 98, 10, 13 }, { 99, 10, 14 }, { 100, 10, 15 }, { 101, 10, 16 }, { 102, 10, 17 }, { 103, 10, 18 }
	}; 

	const LabelPos labelPositions[] = {
		{ "1", 0, 1, 1 }, { "2", 0, 2, 1 }, { "3", 0, 3, 1 }, { "4", 0, 4, 1 }, { "5", 0, 5, 1 }, { "6", 0, 6, 1 }, { "7", 0, 7, 1 }, 
		{ "8", 0, 8, 1 }, { "9", 0, 9, 1 }, { "10", 0, 10, 1 }, { "11", 0, 11, 1 }, { "12", 0, 12, 1 }, { "13", 0, 13, 1 }, 
		{ "14", 0, 14, 1 }, { "15", 0, 15, 1 }, { "16", 0, 16, 1 }, { "17", 0, 17, 1 }, { "18", 0, 18, 1 }, { "1", 1, 0, 1 }, 
		{ "2", 2, 0, 1 }, { "3", 3, 0, 1 }, { "4", 4, 0, 1 }, { "5", 5, 0, 1 }, { "6", 6, 0, 1 }, { "7", 7, 0, 1 }, { "*", 6, 3, 1 }, 
		{ "**", 7, 3, 1 }, { "* Lanthanides:", 9, 0, 4 }, { "** Actinides:", 10, 0, 4 }
	};
}


using namespace ChOx;


AtomColorSettingsEditWidget::AtomColorSettingsEditWidget(QWidget* parent, Settings& settings): 
	SettingsEditWidget(parent), settings(settings)
{
	init();
}

bool AtomColorSettingsEditWidget::haveChangedSettings() const
{
	return haveChanges;
}

void AtomColorSettingsEditWidget::apply()
{
	using namespace CDPL;

	Vis::ColorTable::SharedPointer color_tab_ptr(new Vis::ColorTable(atomColors));

	Vis::setAtomColorParameter(settings, defaultColor);
	ChOx::setAtomColorTableParameter(settings, color_tab_ptr);
	setUseAtomColorTableParameter(settings, enableColorTabCheckBox->isChecked());

	if (enableColorTabCheckBox->isChecked())
		Vis::setAtomColorTableParameter(settings, color_tab_ptr);
	else
		Vis::clearAtomColorTableParameter(settings);
}

void AtomColorSettingsEditWidget::reset()
{
	using namespace CDPL;

	blockSignals(true);

	atomColors = *getAtomColorTableParameter(settings);
	defaultColor = Vis::getAtomColorParameter(settings);

	enableColorTabCheckBox->setChecked(getUseAtomColorTableParameter(settings));
	colorTabWidget->setEnabled(enableColorTabCheckBox->isChecked());

	blockSignals(false);

	haveChanges = false;

	emit updateGUI();
}

void AtomColorSettingsEditWidget::setDefaults()
{
	using namespace CDPL;
	
	atomColors = *ControlParameterDefault::ATOM_COLOR_TABLE;
	defaultColor = Vis::ControlParameterDefault::ATOM_COLOR;

	enableColorTabCheckBox->setChecked(ControlParameterDefault::USE_ATOM_COLOR_TABLE);
	colorTabWidget->setEnabled(enableColorTabCheckBox->isChecked());

	haveChanges = true;

	emit updateGUI();
	emit settingsChanged();
}

void AtomColorSettingsEditWidget::handleSettingsChange()
{
	haveChanges = true;

	emit SettingsEditWidget::settingsChanged();
}

void AtomColorSettingsEditWidget::handleSettingsChange(bool)
{
	haveChanges = true;

	emit SettingsEditWidget::settingsChanged();
}

void AtomColorSettingsEditWidget::init()
{
	QVBoxLayout* main_layout = new QVBoxLayout(this);

// ---------

	QFrame* frame = new QFrame(this);

	frame->setFrameStyle(QFrame::StyledPanel);

	QHBoxLayout* h_box_layout = new QHBoxLayout(frame);

// +++

	ColorEditWidget* color_edit_widget = new ColorEditWidget(frame, defaultColor);

	QLabel* label = new QLabel(tr("De&fault Color:"), frame);

	label->setBuddy(color_edit_widget);

	h_box_layout->addWidget(label);
	
	setFocusProxy(color_edit_widget);

	h_box_layout->addWidget(color_edit_widget);

	connect(color_edit_widget, SIGNAL(colorChanged()), this, SIGNAL(updateGUI()));
	connect(color_edit_widget, SIGNAL(colorChanged()), this, SLOT(handleSettingsChange()));
	connect(this, SIGNAL(updateGUI()), color_edit_widget, SLOT(updateGUI()));

// +++

	main_layout->addWidget(frame);

// ---------

	QGroupBox* group_box = new QGroupBox(tr("Element Colors"), this);
	QVBoxLayout* v_box_layout = new QVBoxLayout(group_box);

	colorTabWidget = new QWidget(group_box);

	v_box_layout->addWidget(colorTabWidget);

	colorTabWidget->setSizePolicy(QSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding));

// +++

	QGridLayout* grid_layout = new QGridLayout(colorTabWidget);

	grid_layout->setSpacing(1);
	grid_layout->setMargin(0);

// +++

	for (std::size_t i = 0; i < sizeof(elementPositions) / sizeof(ElementPos); i++) {
		AtomColorButton* button = new AtomColorButton(colorTabWidget, atomColors, defaultColor, elementPositions[i].atomicNo);

		button->setMinimumSize(35, 30);

		connect(this, SIGNAL(updateGUI()), button, SLOT(updateGUI()));
		connect(button, SIGNAL(colorChanged()), this, SLOT(handleSettingsChange()));

		grid_layout->addWidget(button, elementPositions[i].row, elementPositions[i].col);
	}

// +++

	for (std::size_t i = 0; i < sizeof(labelPositions) / sizeof(LabelPos); i++) {
		QLabel* label = new QLabel(tr(labelPositions[i].text), colorTabWidget);

		label->setFrameStyle(QLabel::Panel | QLabel::Raised);
		label->setAlignment(Qt::AlignCenter);

		QFont font = label->font();

		font.setBold(true);

		label->setFont(font);
		label->setMinimumSize(35, 30);

		grid_layout->addWidget(label, labelPositions[i].row, labelPositions[i].col, 1, labelPositions[i].size);
	}

	grid_layout->setRowMinimumHeight(8, 10);

// ---------

	frame = new QFrame(group_box);

	frame->setFrameStyle(QFrame::HLine | QFrame::Sunken);

	v_box_layout->addWidget(frame);

// +++

	enableColorTabCheckBox = new QCheckBox(tr("&Enable Color Table"), group_box);

	v_box_layout->addWidget(enableColorTabCheckBox);

	connect(enableColorTabCheckBox, SIGNAL(toggled(bool)), colorTabWidget, SLOT(setEnabled(bool)));
	connect(enableColorTabCheckBox, SIGNAL(toggled(bool)), this, SLOT(handleSettingsChange(bool)));

// +++

	main_layout->addWidget(group_box);
	main_layout->addStretch();

// ---------

	reset();
}
