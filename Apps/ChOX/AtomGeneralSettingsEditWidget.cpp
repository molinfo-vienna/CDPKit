/* 
 * AtomGeneralSettingsEditWidget.cpp 
 *
 * This file is part of the Chemical Data Processing Toolkit
 *
 * Copyright (C) 2003 Thomas Seidel <thomas.seidel@univie.ac.at>
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
#include <QGridLayout>
#include <QLabel>
#include <QGroupBox>
#include <QCheckBox>

#include "CDPL/Vis/ControlParameterFunctions.hpp"
#include "CDPL/Vis/ControlParameterDefault.hpp"

#include "AtomGeneralSettingsEditWidget.hpp"
#include "FontEditWidget.hpp"
#include "SizeSpecEditWidget.hpp"
#include "Settings.hpp"


using namespace ChOX;


AtomGeneralSettingsEditWidget::AtomGeneralSettingsEditWidget(QWidget* parent, Settings& settings): 
	SettingsEditWidget(parent), settings(settings)
{
	init();
}

bool AtomGeneralSettingsEditWidget::haveChangedSettings() const
{
	return haveChanges;
}

void AtomGeneralSettingsEditWidget::apply()
{
	using namespace CDPL;
	using namespace Vis;

	setAtomLabelFontParameter(settings, labelFont);
	setSecondaryAtomLabelFontParameter(settings, secondaryLabelFont);

	setAtomLabelSizeParameter(settings, labelSize);
	setSecondaryAtomLabelSizeParameter(settings, secondaryLabelSize);

	setAtomLabelMarginParameter(settings, labelMargin);
	setRadicalElectronDotSizeParameter(settings, electronDotSize);

	setShowCarbonsParameter(settings, showCarbonsCheckBox->isChecked());
	setShowChargesParameter(settings, showChargesCheckBox->isChecked());
	setShowIsotopesParameter(settings, showIsotopesCheckBox->isChecked());
	setShowHydrogenCountsParameter(settings, showHCountsCheckBox->isChecked());
	setShowExplicitHydrogensParameter(settings, showExplicitHsCheckBox->isChecked());
	setShowNonCarbonHydrogenCountsParameter(settings, showNonCarbonHCountsCheckBox->isChecked());
	setShowAtomQueryInfosParameter(settings, showQueryInfosCheckBox->isChecked());
	setShowAtomReactionInfosParameter(settings, showReactionInfosCheckBox->isChecked());
	setShowRadicalElectronsParameter(settings, showRadicalElectronsCheckBox->isChecked());
	setUseCalculatedAtomCoordinatesParameter(settings, useCalcAtomCoordsCheckBox->isChecked());
}

void AtomGeneralSettingsEditWidget::reset()
{
	using namespace CDPL;
	using namespace Vis;

	blockSignals(true);

	labelFont = getAtomLabelFontParameter(settings);
	secondaryLabelFont = getSecondaryAtomLabelFontParameter(settings);

	labelSize = getAtomLabelSizeParameter(settings);
	secondaryLabelSize = getSecondaryAtomLabelSizeParameter(settings);

	labelMargin = getAtomLabelMarginParameter(settings);
	electronDotSize = getRadicalElectronDotSizeParameter(settings);

	showCarbonsCheckBox->setChecked(getShowCarbonsParameter(settings));
	showChargesCheckBox->setChecked(getShowChargesParameter(settings));
	showIsotopesCheckBox->setChecked(getShowIsotopesParameter(settings));
	showHCountsCheckBox->setChecked(getShowHydrogenCountsParameter(settings));
	showExplicitHsCheckBox->setChecked(getShowExplicitHydrogensParameter(settings));
	showNonCarbonHCountsCheckBox->setChecked(getShowNonCarbonHydrogenCountsParameter(settings));
	showQueryInfosCheckBox->setChecked(getShowAtomQueryInfosParameter(settings));
	showReactionInfosCheckBox->setChecked(getShowAtomReactionInfosParameter(settings));
	showRadicalElectronsCheckBox->setChecked(getShowRadicalElectronsParameter(settings));
	useCalcAtomCoordsCheckBox->setChecked(getUseCalculatedAtomCoordinatesParameter(settings));

	blockSignals(false);

	haveChanges = false;

	emit updateGUI();
}

void AtomGeneralSettingsEditWidget::setDefaults()
{
	using namespace CDPL;
	using namespace Vis;
	using namespace ControlParameterDefault;

	labelFont = ATOM_LABEL_FONT;
	secondaryLabelFont = SECONDARY_ATOM_LABEL_FONT;

	labelSize = ATOM_LABEL_SIZE;
	secondaryLabelSize = SECONDARY_ATOM_LABEL_SIZE;

	labelMargin = ATOM_LABEL_MARGIN;
	electronDotSize = RADICAL_ELECTRON_DOT_SIZE;

	showCarbonsCheckBox->setChecked(SHOW_CARBONS);
	showChargesCheckBox->setChecked(SHOW_CHARGES);
	showIsotopesCheckBox->setChecked(SHOW_ISOTOPES);
	showHCountsCheckBox->setChecked(SHOW_HYDROGEN_COUNTS);
	showExplicitHsCheckBox->setChecked(SHOW_EXPLICIT_HYDROGENS);
	showNonCarbonHCountsCheckBox->setChecked(SHOW_NON_CARBON_HYDROGEN_COUNTS);
	showQueryInfosCheckBox->setChecked(SHOW_ATOM_QUERY_INFOS);
	showReactionInfosCheckBox->setChecked(SHOW_ATOM_REACTION_INFOS);
	showRadicalElectronsCheckBox->setChecked(SHOW_RADICAL_ELECTRONS);
	useCalcAtomCoordsCheckBox->setChecked(USE_CALCULATED_ATOM_COORDINATES);

	haveChanges = true;

	emit updateGUI();
	emit settingsChanged();
}

void AtomGeneralSettingsEditWidget::handleSettingsChange()
{
	haveChanges = true;

	emit SettingsEditWidget::settingsChanged();
}

void AtomGeneralSettingsEditWidget::handleSettingsChange(bool)
{
	haveChanges = true;

	emit SettingsEditWidget::settingsChanged();
}

void AtomGeneralSettingsEditWidget::handleHCountVisibilityChange(bool visible)
{
	showNonCarbonHCountsCheckBox->setEnabled(!visible);
}

void AtomGeneralSettingsEditWidget::init()
{
	QBoxLayout* main_layout= new QVBoxLayout(this);

// ---------

	QGroupBox* group_box = new QGroupBox(tr("Show"), this);
	QGridLayout* grid_layout = new QGridLayout(group_box);

// +++

	showCarbonsCheckBox = new QCheckBox(tr("Car&bon Symbols"), group_box);
	grid_layout->addWidget(showCarbonsCheckBox, 0, 0);

	connect(showCarbonsCheckBox, SIGNAL(toggled(bool)), this, SLOT(handleSettingsChange(bool)));

// +++

	showChargesCheckBox = new QCheckBox(tr("&Formal Charges"), group_box);
	grid_layout->addWidget(showChargesCheckBox, 0, 1);

	connect(showChargesCheckBox, SIGNAL(toggled(bool)), this, SLOT(handleSettingsChange(bool)));

// +++

	showIsotopesCheckBox = new QCheckBox(tr("Iso&topic Mass"), group_box);
	grid_layout->addWidget(showIsotopesCheckBox, 1, 0);

	connect(showIsotopesCheckBox, SIGNAL(toggled(bool)), this, SLOT(handleSettingsChange(bool)));

// +++

	showHCountsCheckBox = new QCheckBox(tr("&Hydrogen Counts"), group_box);
	grid_layout->addWidget(showHCountsCheckBox, 1, 1);

	connect(showHCountsCheckBox, SIGNAL(toggled(bool)), this, SLOT(handleSettingsChange(bool)));

// +++

	showExplicitHsCheckBox = new QCheckBox(tr("E&xplicit Hydrogens"), group_box);
	grid_layout->addWidget(showExplicitHsCheckBox, 2, 0);

	connect(showExplicitHsCheckBox, SIGNAL(toggled(bool)), this, SLOT(handleSettingsChange(bool)));

// +++

	showNonCarbonHCountsCheckBox = new QCheckBox(tr("&Non-Carbon Hydrogen Counts"), group_box);
	grid_layout->addWidget(showNonCarbonHCountsCheckBox, 2, 1);

	connect(showNonCarbonHCountsCheckBox, SIGNAL(toggled(bool)), this, SLOT(handleHCountVisibilityChange(bool)));
	connect(showNonCarbonHCountsCheckBox, SIGNAL(toggled(bool)), this, SLOT(handleSettingsChange(bool)));

// +++

	showQueryInfosCheckBox = new QCheckBox(tr("&Query Information"), group_box);
	grid_layout->addWidget(showQueryInfosCheckBox, 3, 0);

	connect(showQueryInfosCheckBox, SIGNAL(toggled(bool)), this, SLOT(handleSettingsChange(bool)));

// +++

	showReactionInfosCheckBox = new QCheckBox(tr("Sho&w Atom-Atom-Mappings"), group_box);
	grid_layout->addWidget(showReactionInfosCheckBox, 3, 1);

	connect(showReactionInfosCheckBox, SIGNAL(toggled(bool)), this, SLOT(handleSettingsChange(bool)));

// +++

	showRadicalElectronsCheckBox = new QCheckBox(tr("Unpaired &Electrons"), group_box);
	grid_layout->addWidget(showRadicalElectronsCheckBox, 4, 0);

	connect(showRadicalElectronsCheckBox, SIGNAL(toggled(bool)), this, SLOT(handleSettingsChange(bool)));

// +++

	useCalcAtomCoordsCheckBox = new QCheckBox(tr("Calc&ulated Coordinates"), group_box);
	grid_layout->addWidget(useCalcAtomCoordsCheckBox, 4, 1);

	connect(useCalcAtomCoordsCheckBox, SIGNAL(toggled(bool)), this, SLOT(handleSettingsChange(bool)));

// +++

	setFocusProxy(showCarbonsCheckBox);

	main_layout->addWidget(group_box);

// ---------

	group_box = new QGroupBox(tr("Label Fonts"), this);
	grid_layout = new QGridLayout(group_box);

// +++

	QLabel* label = new QLabel(tr("&Primary Font:"), group_box);

	grid_layout->addWidget(label, 0, 0);

	FontEditWidget* font_edit_widget = new FontEditWidget(group_box, labelFont, labelSize, 0, false);

	grid_layout->addWidget(font_edit_widget, 0, 1);

	label->setBuddy(font_edit_widget);

	connect(this, SIGNAL(updateGUI()), font_edit_widget, SLOT(updateGUI()));
	connect(font_edit_widget, SIGNAL(fontChanged()), this, SIGNAL(updateGUI()));
	connect(font_edit_widget, SIGNAL(fontChanged()), this, SLOT(handleSettingsChange()));

// +++

	label = new QLabel(tr("Secondar&y Font:"), group_box);

	grid_layout->addWidget(label, 1, 0);

	font_edit_widget = new FontEditWidget(group_box, secondaryLabelFont, secondaryLabelSize, &labelSize, true);

	grid_layout->addWidget(font_edit_widget, 1, 1);

	label->setBuddy(font_edit_widget);

	connect(font_edit_widget, SIGNAL(fontChanged()), this, SLOT(handleSettingsChange()));

	connect(this, SIGNAL(updateGUI()), font_edit_widget, SLOT(updateGUI()));

// +++

	main_layout->addWidget(group_box);

// +++

	group_box = new QGroupBox(tr("Metrics"), this);
	grid_layout = new QGridLayout(group_box);

	label = new QLabel(tr("Label &Margin:"), group_box);

	SizeSpecEditWidget* size_edit_widget = new SizeSpecEditWidget(group_box, labelMargin, true, false);

	label->setBuddy(size_edit_widget);

	grid_layout->addWidget(label, 0, 0);
	grid_layout->addWidget(size_edit_widget, 0, 1);

	connect(this, SIGNAL(updateGUI()), size_edit_widget, SLOT(updateGUI()));
	connect(size_edit_widget, SIGNAL(sizeSpecChanged()), this, SLOT(handleSettingsChange()));

// +++

	label = new QLabel(tr("Electron Dot Si&ze:"), group_box);

	size_edit_widget = new SizeSpecEditWidget(group_box, electronDotSize, true, false);

	label->setBuddy(size_edit_widget);

	grid_layout->addWidget(label, 1, 0);
	grid_layout->addWidget(size_edit_widget, 1, 1);

	connect(this, SIGNAL(updateGUI()), size_edit_widget, SLOT(updateGUI()));
	connect(size_edit_widget, SIGNAL(sizeSpecChanged()), this, SLOT(handleSettingsChange()));

	main_layout->addWidget(group_box);

// ---------

	main_layout->addStretch();

	reset();
}
