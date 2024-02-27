/* 
 * BondSettingsEditWidget.cpp 
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
#include <QHBoxLayout>
#include <QGridLayout>
#include <QLabel>
#include <QFrame>
#include <QGroupBox>
#include <QCheckBox>

#include "CDPL/Vis/ControlParameterFunctions.hpp"
#include "CDPL/Vis/ControlParameterDefault.hpp"

#include "BondSettingsEditWidget.hpp"
#include "FontEditWidget.hpp"
#include "ColorEditWidget.hpp"
#include "SizeSpecEditWidget.hpp"
#include "Settings.hpp"


using namespace ChOX;


BondSettingsEditWidget::BondSettingsEditWidget(QWidget* parent, Settings& settings): 
    SettingsEditWidget(parent), settings(settings), color(0.5, 0.6, 0.7, 1.0)
{
    init();
}

bool BondSettingsEditWidget::haveChangedSettings() const
{
    return haveChanges;
}

void BondSettingsEditWidget::apply()
{
    using namespace CDPL;
    using namespace Vis;

    setBondLabelFontParameter(settings, labelFont);
    setBondConfigurationLabelFontParameter(settings, configLabelFont);

    setBondLabelSizeParameter(settings, labelSize);
    setBondLabelMarginParameter(settings, labelMargin);
    setBondConfigurationLabelSizeParameter(settings, configLabelSize);
    
    setBondColorParameter(settings, color);
    setBondConfigurationLabelColorParameter(settings, configLabelColor);
    
    setBondLengthParameter(settings, bondLength);

    setBondLineWidthParameter(settings, bondLineWidth);
    setBondLineSpacingParameter(settings, bondLineSpacing);
    setStereoBondWedgeWidthParameter(settings, wedgeWidth);
    setStereoBondHashSpacingParameter(settings, hashSpacing);
    setReactionCenterLineLengthParameter(settings, rxnCenterLineLength);
    setReactionCenterLineSpacingParameter(settings, rxnCenterLineSpacing);
    setDoubleBondTrimLengthParameter(settings, doubleBondTrimLength);
    setTripleBondTrimLengthParameter(settings, tripleBondTrimLength);

    setShowBondQueryInfosParameter(settings, showQueryInfosCheckBox->isChecked());
    setShowBondReactionInfosParameter(settings, showReactionInfosCheckBox->isChecked());
    setShowStereoBondsParameter(settings, showBondStereoCheckBox->isChecked());
    setShowBondConfigurationLabelsParameter(settings, showBondConfigLabelsCheckBox->isChecked());
}

void BondSettingsEditWidget::reset()
{
    using namespace CDPL;
    using namespace Vis;

    blockSignals(true);

    labelFont = getBondLabelFontParameter(settings);
    configLabelFont = getBondConfigurationLabelFontParameter(settings);

    labelSize = getBondLabelSizeParameter(settings);
    labelMargin = getBondLabelMarginParameter(settings);
    configLabelSize = getBondConfigurationLabelSizeParameter(settings);
    
    color = getBondColorParameter(settings);
    configLabelColor = getBondConfigurationLabelColorParameter(settings);
    
    bondLength = getBondLengthParameter(settings);
    bondLineWidth = getBondLineWidthParameter(settings);
    bondLineSpacing = getBondLineSpacingParameter(settings);
    wedgeWidth = getStereoBondWedgeWidthParameter(settings);
    hashSpacing = getStereoBondHashSpacingParameter(settings);
    rxnCenterLineLength = getReactionCenterLineLengthParameter(settings);
    rxnCenterLineSpacing = getReactionCenterLineSpacingParameter(settings);
    doubleBondTrimLength = getDoubleBondTrimLengthParameter(settings);
    tripleBondTrimLength = getTripleBondTrimLengthParameter(settings);

    showQueryInfosCheckBox->setChecked(getShowBondQueryInfosParameter(settings));
    showReactionInfosCheckBox->setChecked(getShowBondReactionInfosParameter(settings));
    showBondStereoCheckBox->setChecked(getShowStereoBondsParameter(settings));
    showBondConfigLabelsCheckBox->setChecked(getShowBondConfigurationLabelsParameter(settings));

    blockSignals(false);

    haveChanges = false;

    emit updateGUI();
}

void BondSettingsEditWidget::setDefaults()
{
    using namespace CDPL;
    using namespace Vis;
    using namespace ControlParameterDefault;

    labelFont = BOND_LABEL_FONT;
    configLabelFont = BOND_CONFIGURATION_LABEL_FONT;

    labelSize = BOND_LABEL_SIZE;
    labelMargin = BOND_LABEL_MARGIN;
    configLabelSize = BOND_CONFIGURATION_LABEL_SIZE;
    
    color = BOND_COLOR;
    configLabelColor = BOND_CONFIGURATION_LABEL_COLOR;
    
    bondLength = BOND_LENGTH;
    bondLineWidth = BOND_LINE_WIDTH;
    bondLineSpacing = BOND_LINE_SPACING;
    wedgeWidth = STEREO_BOND_WEDGE_WIDTH;
    hashSpacing = STEREO_BOND_HASH_SPACING;
    rxnCenterLineLength = REACTION_CENTER_LINE_LENGTH;
    rxnCenterLineSpacing = REACTION_CENTER_LINE_SPACING;
    doubleBondTrimLength = DOUBLE_BOND_TRIM_LENGTH;
    tripleBondTrimLength = TRIPLE_BOND_TRIM_LENGTH;

    showQueryInfosCheckBox->setChecked(SHOW_BOND_QUERY_INFOS);
    showReactionInfosCheckBox->setChecked(SHOW_BOND_REACTION_INFOS);
    showBondStereoCheckBox->setChecked(SHOW_STEREO_BONDS);
    showBondConfigLabelsCheckBox->setChecked(SHOW_BOND_CONFIGURATION_LABELS);

    haveChanges = true;

    emit updateGUI();
    emit settingsChanged();
}

void BondSettingsEditWidget::handleSettingsChange()
{
    haveChanges = true;

    emit SettingsEditWidget::settingsChanged();
}

void BondSettingsEditWidget::handleSettingsChange(bool)
{
    haveChanges = true;

    emit SettingsEditWidget::settingsChanged();
}

void BondSettingsEditWidget::init()
{
    QBoxLayout* main_layout= new QVBoxLayout(this);

// --------

    QGroupBox* group_box = new QGroupBox(tr("Show"), this);
    QGridLayout* grid_layout = new QGridLayout(group_box);

// +++

    showQueryInfosCheckBox = new QCheckBox(tr("&Query Information"), group_box);
    grid_layout->addWidget(showQueryInfosCheckBox, 0, 0);

    connect(showQueryInfosCheckBox, SIGNAL(toggled(bool)), this, SLOT(handleSettingsChange(bool)));

// +++

    showReactionInfosCheckBox = new QCheckBox(tr("Reaction-Center &Marks"), group_box);
    grid_layout->addWidget(showReactionInfosCheckBox, 0, 1);

    connect(showReactionInfosCheckBox, SIGNAL(toggled(bool)), this, SLOT(handleSettingsChange(bool)));

// +++

    showBondStereoCheckBox = new QCheckBox(tr("Bond &Stereo"), group_box);
    grid_layout->addWidget(showBondStereoCheckBox, 1, 0);

    connect(showBondStereoCheckBox, SIGNAL(toggled(bool)), this, SLOT(handleSettingsChange(bool)));

// +++

    showBondConfigLabelsCheckBox = new QCheckBox(tr("CIP &Configuration Labels"), group_box);
    grid_layout->addWidget(showBondConfigLabelsCheckBox, 1, 1);

    connect(showBondConfigLabelsCheckBox, SIGNAL(toggled(bool)), this, SLOT(handleSettingsChange(bool)));

// +++

    setFocusProxy(showQueryInfosCheckBox);

    main_layout->addWidget(group_box);

// --------

    group_box = new QGroupBox(tr("Fonts"), this);
    grid_layout = new QGridLayout(group_box);

// +++

    FontEditWidget* font_edit_widget = new FontEditWidget(group_box, labelFont, labelSize, 0, false);
    QLabel* font_label = new QLabel(tr("Label &Font:"), group_box);

    font_label->setBuddy(font_edit_widget);

    grid_layout->addWidget(font_label, 0, 0);
    grid_layout->addWidget(font_edit_widget, 0, 1);
    
    connect(this, SIGNAL(updateGUI()), font_edit_widget, SLOT(updateGUI()));
    connect(font_edit_widget, SIGNAL(fontChanged()), this, SLOT(handleSettingsChange()));

// +++

    font_edit_widget = new FontEditWidget(group_box, configLabelFont, configLabelSize, 0, false);
    font_label = new QLabel(tr("CI&P Config. Label Font:"), group_box);

    font_label->setBuddy(font_edit_widget);

    grid_layout->addWidget(font_label, 1, 0);
    grid_layout->addWidget(font_edit_widget, 1, 1);
    
    connect(this, SIGNAL(updateGUI()), font_edit_widget, SLOT(updateGUI()));
    connect(font_edit_widget, SIGNAL(fontChanged()), this, SLOT(handleSettingsChange()));

// +++
    
    main_layout->addWidget(group_box);

// --------

    group_box = new QGroupBox(tr("Colors"), this);
    grid_layout = new QGridLayout(group_box);

// +++

    ColorEditWidget* color_edit_widget = new ColorEditWidget(group_box, color);
    QLabel* label = new QLabel(tr("Co&lor:"), group_box);

    label->setBuddy(color_edit_widget);

    label->setMinimumWidth(font_label->sizeHint().width());

    grid_layout->addWidget(label, 0, 0);
    grid_layout->addWidget(color_edit_widget, 0, 1);

    connect(this, SIGNAL(updateGUI()), color_edit_widget, SLOT(updateGUI()));
    connect(color_edit_widget, SIGNAL(colorChanged()), this, SLOT(handleSettingsChange()));

// +++

    color_edit_widget = new ColorEditWidget(group_box, configLabelColor);
    label = new QLabel(tr("C&IP Config. Label Color:"), group_box);

    label->setBuddy(color_edit_widget);

    label->setMinimumWidth(font_label->sizeHint().width());

    grid_layout->addWidget(label, 1, 0);
    grid_layout->addWidget(color_edit_widget, 1, 1);

    connect(this, SIGNAL(updateGUI()), color_edit_widget, SLOT(updateGUI()));
    connect(color_edit_widget, SIGNAL(colorChanged()), this, SLOT(handleSettingsChange()));

// +++

    main_layout->addWidget(group_box);

// --------

    group_box = new QGroupBox(tr("Metrics"), this);
    grid_layout = new QGridLayout(group_box);

// +++

    label = new QLabel(tr("Standard Bond Le&ngth:"), group_box);

    SizeSpecEditWidget* size_edit_widget = new SizeSpecEditWidget(group_box, bondLength, false, false, false);

    label->setBuddy(size_edit_widget);

    grid_layout->addWidget(label, 0, 0);
    grid_layout->addWidget(size_edit_widget, 0, 1);

    connect(this, SIGNAL(updateGUI()), size_edit_widget, SLOT(updateGUI()));
    connect(size_edit_widget, SIGNAL(sizeSpecChanged()), this, SLOT(handleSettingsChange()));

// +++

    label = new QLabel(tr("Line &Thickness:"), group_box);

    size_edit_widget = new SizeSpecEditWidget(group_box, bondLineWidth, true, false);

    label->setBuddy(size_edit_widget);

    grid_layout->addWidget(label, 1, 0);
    grid_layout->addWidget(size_edit_widget, 1, 1);

    connect(this, SIGNAL(updateGUI()), size_edit_widget, SLOT(updateGUI()));
    connect(size_edit_widget, SIGNAL(sizeSpecChanged()), this, SLOT(handleSettingsChange()));

// +++

    label = new QLabel(tr("Line S&pacing:"), group_box);

    size_edit_widget = new SizeSpecEditWidget(group_box, bondLineSpacing, true, false);

    label->setBuddy(size_edit_widget);

    grid_layout->addWidget(label, 2, 0);
    grid_layout->addWidget(size_edit_widget, 2, 1);

    connect(this, SIGNAL(updateGUI()), size_edit_widget, SLOT(updateGUI()));
    connect(size_edit_widget, SIGNAL(sizeSpecChanged()), this, SLOT(handleSettingsChange()));

// +++

    label = new QLabel(tr("Reaction-Center Mar&k Length:"), group_box);

    size_edit_widget = new SizeSpecEditWidget(group_box, rxnCenterLineLength, true, false);

    label->setBuddy(size_edit_widget);

    grid_layout->addWidget(label, 3, 0);
    grid_layout->addWidget(size_edit_widget, 3, 1);

    connect(this, SIGNAL(updateGUI()), size_edit_widget, SLOT(updateGUI()));
    connect(size_edit_widget, SIGNAL(sizeSpecChanged()), this, SLOT(handleSettingsChange()));

// +++

    label = new QLabel(tr("Reaction-Center Mark Spacin&g:"), group_box);

    size_edit_widget = new SizeSpecEditWidget(group_box, rxnCenterLineSpacing, true, false);

    label->setBuddy(size_edit_widget);

    grid_layout->addWidget(label, 4, 0);
    grid_layout->addWidget(size_edit_widget, 4, 1);

    connect(this, SIGNAL(updateGUI()), size_edit_widget, SLOT(updateGUI()));
    connect(size_edit_widget, SIGNAL(sizeSpecChanged()), this, SLOT(handleSettingsChange()));

// +++

    label = new QLabel(tr("&Wedge Width:"), group_box);

    size_edit_widget = new SizeSpecEditWidget(group_box, wedgeWidth, true, false);

    label->setBuddy(size_edit_widget);

    grid_layout->addWidget(label, 5, 0);
    grid_layout->addWidget(size_edit_widget, 5, 1);

    connect(this, SIGNAL(updateGUI()), size_edit_widget, SLOT(updateGUI()));
    connect(size_edit_widget, SIGNAL(sizeSpecChanged()), this, SLOT(handleSettingsChange()));

// +++

    label = new QLabel(tr("&Hash Spacing:"), group_box);

    size_edit_widget = new SizeSpecEditWidget(group_box, hashSpacing, true, false);

    label->setBuddy(size_edit_widget);

    grid_layout->addWidget(label, 6, 0);
    grid_layout->addWidget(size_edit_widget, 6, 1);

    connect(this, SIGNAL(updateGUI()), size_edit_widget, SLOT(updateGUI()));
    connect(size_edit_widget, SIGNAL(sizeSpecChanged()), this, SLOT(handleSettingsChange()));

// +++

    label = new QLabel(tr("La&bel Margin:"), group_box);

    size_edit_widget = new SizeSpecEditWidget(group_box, labelMargin, true, false);

    label->setBuddy(size_edit_widget);

    grid_layout->addWidget(label, 7, 0);
    grid_layout->addWidget(size_edit_widget, 7, 1);

    connect(this, SIGNAL(updateGUI()), size_edit_widget, SLOT(updateGUI()));
    connect(size_edit_widget, SIGNAL(sizeSpecChanged()), this, SLOT(handleSettingsChange()));

// --------

    main_layout->addWidget(group_box);
    main_layout->addStretch();

    reset();
}
