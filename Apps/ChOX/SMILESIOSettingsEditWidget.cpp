/* 
 * SMILESIOSettingsEditWidget.cpp 
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


#include <QGridLayout>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QGroupBox>
#include <QCheckBox>
#include <QSpinBox>

#include "CDPL/Chem/ControlParameterFunctions.hpp"

#include "SMILESIOSettingsEditWidget.hpp"
#include "SMILESRecordFormatEditWidget.hpp"
#include "ControlParameterFunctions.hpp"
#include "ControlParameterDefault.hpp"
#include "Settings.hpp"


using namespace ChOX;


SMILESIOSettingsEditWidget::SMILESIOSettingsEditWidget(QWidget* parent, Settings& settings): 
	SettingsEditWidget(parent), settings(settings)
{
	init();
}

bool SMILESIOSettingsEditWidget::haveChangedSettings() const
{
	return haveChanges;
}

void SMILESIOSettingsEditWidget::apply()
{
	using namespace CDPL;
	using namespace Chem;

	SettingsContainer& reader_params = settings.getReaderControlParameters("SMILES");

	setStrictErrorCheckingParameter(reader_params, iptStrictErrorCheckingCheckBox->isChecked());
	setSMILESRecordFormatParameter(reader_params, iptRecordFormat);

	SettingsContainer& writer_params = settings.getWriterControlParameters("SMILES");

	setStrictErrorCheckingParameter(writer_params, optStrictErrorCheckingCheckBox->isChecked());
	setOrdinaryHydrogenDepleteParameter(writer_params, optOrdinaryHDepleteCheckBox->isChecked());
	setSMILESWriteCanonicalFormParameter(writer_params, optCanonicalFormCheckBox->isChecked());
	setSMILESWriteKekuleFormParameter(writer_params, optKekuleFormCheckBox->isChecked());
	setSMILESWriteIsotopeParameter(writer_params, optIsotopeCheckBox->isChecked());
	setSMILESWriteAtomStereoParameter(writer_params, optAtomStereoCheckBox->isChecked());
	setSMILESWriteBondStereoParameter(writer_params, optBondStereoCheckBox->isChecked());
	setSMILESWriteRingBondStereoParameter(writer_params, optRingBondStereoCheckBox->isChecked());
	setSMILESMolWriteAtomMappingIDParameter(writer_params, optAtomAtomMappingsCheckBox->isChecked());
	setSMILESRxnWriteAtomMappingIDParameter(writer_params, optAtomAtomMappingsCheckBox->isChecked());
	setSMILESWriteSingleBondsParameter(writer_params, optExplicitSingleBondsCheckBox->isChecked());
	setSMILESWriteAromaticBondsParameter(writer_params, optExplicitAromaticBondsCheckBox->isChecked());
	setSMILESNoOrganicSubsetParameter(writer_params, optNoOrganicSubsetCheckBox->isChecked());
	setSMILESMinStereoBondRingSizeParameter(writer_params, std::size_t(optMinRingSizeSpinBox->value()));
	setWriteSingleRecordFilesParameter(writer_params, !optConcatenateRecordsCheckBox->isChecked());
	setSMILESRecordFormatParameter(writer_params, optRecordFormat);
}

void SMILESIOSettingsEditWidget::reset()
{
	using namespace CDPL;
	using namespace Chem;

	blockSignals(true);

	const SettingsContainer& reader_params = settings.getReaderControlParameters("SMILES");

	iptStrictErrorCheckingCheckBox->setChecked(getStrictErrorCheckingParameter(reader_params));
	iptRecordFormat = getSMILESRecordFormatParameter(reader_params);

	const SettingsContainer& writer_params = settings.getWriterControlParameters("SMILES");

	optStrictErrorCheckingCheckBox->setChecked(getStrictErrorCheckingParameter(writer_params));
	optOrdinaryHDepleteCheckBox->setChecked(getOrdinaryHydrogenDepleteParameter(writer_params));
	optCanonicalFormCheckBox->setChecked(getSMILESWriteCanonicalFormParameter(writer_params));
	optKekuleFormCheckBox->setChecked(getSMILESWriteKekuleFormParameter(writer_params));
	optIsotopeCheckBox->setChecked(getSMILESWriteIsotopeParameter(writer_params));
	optAtomStereoCheckBox->setChecked(getSMILESWriteAtomStereoParameter(writer_params));
	optBondStereoCheckBox->setChecked(getSMILESWriteBondStereoParameter(writer_params));
	optRingBondStereoCheckBox->setChecked(getSMILESWriteRingBondStereoParameter(writer_params));
	optAtomAtomMappingsCheckBox->setChecked(getSMILESMolWriteAtomMappingIDParameter(writer_params) ||
											getSMILESRxnWriteAtomMappingIDParameter(writer_params));
	optExplicitSingleBondsCheckBox->setChecked(getSMILESWriteSingleBondsParameter(writer_params));
	optExplicitAromaticBondsCheckBox->setChecked(getSMILESWriteAromaticBondsParameter(writer_params));
	optNoOrganicSubsetCheckBox->setChecked(getSMILESNoOrganicSubsetParameter(writer_params));
	optConcatenateRecordsCheckBox->setChecked(!getWriteSingleRecordFilesParameter(writer_params));

	optMinRingSizeSpinBox->setValue(getSMILESMinStereoBondRingSizeParameter(writer_params));

	optRecordFormat = getSMILESRecordFormatParameter(writer_params);

	blockSignals(false);

	haveChanges = false;

	handleBondStereoSettingsChange(false);
	handleKekuleFormSettingChange(false);

	emit updateGUI();
}

void SMILESIOSettingsEditWidget::setDefaults()
{
	using namespace ControlParameterDefault;

	iptStrictErrorCheckingCheckBox->setChecked(SMILES_INPUT_STRICT_ERROR_CHECKING);
	iptRecordFormat = SMILES_INPUT_RECORD_FORMAT;

	optStrictErrorCheckingCheckBox->setChecked(SMILES_OUTPUT_STRICT_ERROR_CHECKING);
	optOrdinaryHDepleteCheckBox->setChecked(SMILES_OUTPUT_ORDINARY_H_DEPLETE);
	optCanonicalFormCheckBox->setChecked(SMILES_OUTPUT_WRITE_CANONICAL_FORM);
	optKekuleFormCheckBox->setChecked(SMILES_OUTPUT_WRITE_KEKULE_FORM);
	optIsotopeCheckBox->setChecked(SMILES_OUTPUT_WRITE_ISOTOPE);
	optAtomStereoCheckBox->setChecked(SMILES_OUTPUT_WRITE_ATOM_STEREO);
	optBondStereoCheckBox->setChecked(SMILES_OUTPUT_WRITE_BOND_STEREO);
	optRingBondStereoCheckBox->setChecked(SMILES_OUTPUT_WRITE_RING_BOND_STEREO);
	optAtomAtomMappingsCheckBox->setChecked(SMILES_OUTPUT_WRITE_ATOM_MAPPING_ID);
	optExplicitSingleBondsCheckBox->setChecked(SMILES_OUTPUT_WRITE_SINGLE_BONDS);
	optExplicitAromaticBondsCheckBox->setChecked(SMILES_OUTPUT_WRITE_AROMATIC_BONDS);
	optNoOrganicSubsetCheckBox->setChecked(SMILES_OUTPUT_NO_ORGANIC_SUBSET);
	optConcatenateRecordsCheckBox->setChecked(!SMILES_OUTPUT_WRITE_SINGLE_RECORD_FILES);
	optRecordFormat = SMILES_OUTPUT_RECORD_FORMAT;

	optMinRingSizeSpinBox->setValue(SMILES_OUTPUT_MIN_STEREO_BOND_RING_SIZE);

	haveChanges = true;

	handleBondStereoSettingsChange(false);
	handleKekuleFormSettingChange(false);

	emit updateGUI();
	emit settingsChanged();
}

void SMILESIOSettingsEditWidget::handleSettingsChange()
{
	haveChanges = true;

	emit SettingsEditWidget::settingsChanged();
}

void SMILESIOSettingsEditWidget::handleSettingsChange(bool)
{
	haveChanges = true;

	emit SettingsEditWidget::settingsChanged();
}

void SMILESIOSettingsEditWidget::handleSettingsChange(int)
{
	haveChanges = true;

	emit SettingsEditWidget::settingsChanged();
}

void SMILESIOSettingsEditWidget::handleBondStereoSettingsChange(bool)
{
	optRingBondStereoCheckBox->setEnabled(optBondStereoCheckBox->isChecked());
	optMinRingSizeSpinBox->setEnabled(optBondStereoCheckBox->isChecked() && optRingBondStereoCheckBox->isChecked());
}

void SMILESIOSettingsEditWidget::handleKekuleFormSettingChange(bool)
{
	optExplicitAromaticBondsCheckBox->setEnabled(!optKekuleFormCheckBox->isChecked());
}

void SMILESIOSettingsEditWidget::init()
{
	QBoxLayout* main_layout = new QVBoxLayout(this);

// ---------

	QGroupBox* group_box = new QGroupBox(tr("Input"), this);
	QVBoxLayout* v_box_layout = new QVBoxLayout(group_box);

// +++

	iptStrictErrorCheckingCheckBox = new QCheckBox(tr("&Perform strict Error Checking"), group_box);

	v_box_layout->addWidget(iptStrictErrorCheckingCheckBox);

	connect(iptStrictErrorCheckingCheckBox, SIGNAL(toggled(bool)), this, SLOT(handleSettingsChange(bool)));

// +++

	setFocusProxy(iptStrictErrorCheckingCheckBox);

	main_layout->addWidget(group_box);

// +++

	QFrame* frame = new QFrame(group_box);

	frame->setFrameStyle(QFrame::HLine | QFrame::Sunken);

	v_box_layout->addWidget(frame);

// xxx

	QHBoxLayout* h_box_layout = new QHBoxLayout();

	v_box_layout->addLayout(h_box_layout);

	QLabel* label = new QLabel(tr("Record Format:"), group_box);

	h_box_layout->addWidget(label);

// xxx

	SMILESRecordFormatEditWidget* format_edit_widget = new SMILESRecordFormatEditWidget(group_box, iptRecordFormat);

	label->setBuddy(format_edit_widget);

	connect(this, SIGNAL(updateGUI()), format_edit_widget, SLOT(updateGUI()));
	connect(format_edit_widget, SIGNAL(recordFormatChanged()), this, SLOT(handleSettingsChange()));

	h_box_layout->addWidget(format_edit_widget);
	h_box_layout->addStretch();

// ---------

	group_box = new QGroupBox(tr("Output"), this);
	v_box_layout = new QVBoxLayout(group_box);

// +++

	optStrictErrorCheckingCheckBox = new QCheckBox(tr("Perform strict Error Checki&ng"), group_box);

	v_box_layout->addWidget(optStrictErrorCheckingCheckBox);

	connect(optStrictErrorCheckingCheckBox, SIGNAL(toggled(bool)), this, SLOT(handleSettingsChange(bool)));

// +++

	optOrdinaryHDepleteCheckBox = new QCheckBox(tr("Don't write explicit &Hydrogens"), group_box);

	v_box_layout->addWidget(optOrdinaryHDepleteCheckBox);

	connect(optOrdinaryHDepleteCheckBox, SIGNAL(toggled(bool)), this, SLOT(handleSettingsChange(bool)));

// +++

	optCanonicalFormCheckBox = new QCheckBox(tr("Write canonical &SMILES"), group_box);

	v_box_layout->addWidget(optCanonicalFormCheckBox);

	connect(optCanonicalFormCheckBox, SIGNAL(toggled(bool)), this, SLOT(handleSettingsChange(bool)));

// +++

	optKekuleFormCheckBox = new QCheckBox(tr("Write aromatic Bonds in localized (&Kekule) Form"), group_box);

	v_box_layout->addWidget(optKekuleFormCheckBox);

	connect(optKekuleFormCheckBox, SIGNAL(toggled(bool)), this, SLOT(handleSettingsChange(bool)));
	connect(optKekuleFormCheckBox, SIGNAL(toggled(bool)), this, SLOT(handleKekuleFormSettingChange(bool)));

// +++

	optExplicitAromaticBondsCheckBox = new QCheckBox(tr("Write &explicit aromatic Bonds"), group_box);

	v_box_layout->addWidget(optExplicitAromaticBondsCheckBox);

	connect(optExplicitAromaticBondsCheckBox, SIGNAL(toggled(bool)), this, SLOT(handleSettingsChange(bool)));

// +++

	optExplicitSingleBondsCheckBox = new QCheckBox(tr("Write e&xplicit Single-Bonds"), group_box);

	v_box_layout->addWidget(optExplicitSingleBondsCheckBox);

	connect(optExplicitSingleBondsCheckBox, SIGNAL(toggled(bool)), this, SLOT(handleSettingsChange(bool)));

// +++

	optAtomAtomMappingsCheckBox = new QCheckBox(tr("Write Reaction Atom-Atom-&Mappings"), group_box);

	v_box_layout->addWidget(optAtomAtomMappingsCheckBox);

	connect(optAtomAtomMappingsCheckBox, SIGNAL(toggled(bool)), this, SLOT(handleSettingsChange(bool)));

// +++

	optIsotopeCheckBox = new QCheckBox(tr("Write Is&otopic Mass"), group_box);

	v_box_layout->addWidget(optIsotopeCheckBox);

	connect(optIsotopeCheckBox, SIGNAL(toggled(bool)), this, SLOT(handleSettingsChange(bool)));

// +++

	optNoOrganicSubsetCheckBox = new QCheckBox(tr("Don't make use of organic Subset Short-&Forms"), group_box);

	v_box_layout->addWidget(optNoOrganicSubsetCheckBox);

	connect(optNoOrganicSubsetCheckBox, SIGNAL(toggled(bool)), this, SLOT(handleSettingsChange(bool)));

// +++

	optConcatenateRecordsCheckBox = new QCheckBox(tr("Concatenate Records to a single F&ile"), group_box);

	v_box_layout->addWidget(optConcatenateRecordsCheckBox);

	connect(optConcatenateRecordsCheckBox, SIGNAL(toggled(bool)), this, SLOT(handleSettingsChange(bool)));

// +++

	optAtomStereoCheckBox = new QCheckBox(tr("Write Atom Chiralit&y"), group_box);

	v_box_layout->addWidget(optAtomStereoCheckBox);

	connect(optAtomStereoCheckBox, SIGNAL(toggled(bool)), this, SLOT(handleSettingsChange(bool)));

// +++

	optBondStereoCheckBox = new QCheckBox(tr("Write Bond Geome&try"), group_box);

	v_box_layout->addWidget(optBondStereoCheckBox);

	connect(optBondStereoCheckBox, SIGNAL(toggled(bool)), this, SLOT(handleSettingsChange(bool)));
	connect(optBondStereoCheckBox, SIGNAL(toggled(bool)), this, SLOT(handleBondStereoSettingsChange(bool)));

// +++

	optRingBondStereoCheckBox = new QCheckBox(tr("Write Geometry of Rin&g-Bonds"), group_box);

	v_box_layout->addWidget(optRingBondStereoCheckBox);

	connect(optRingBondStereoCheckBox, SIGNAL(toggled(bool)), this, SLOT(handleSettingsChange(bool)));
	connect(optRingBondStereoCheckBox, SIGNAL(toggled(bool)), this, SLOT(handleBondStereoSettingsChange(bool)));

// +++

	frame = new QFrame(group_box);

	frame->setFrameStyle(QFrame::HLine | QFrame::Sunken);

	v_box_layout->addWidget(frame);

// +++

	QGridLayout* grid_layout = new QGridLayout();

	v_box_layout->addLayout(grid_layout);

	grid_layout->setColumnStretch(2, 1);

// xxx

	label = new QLabel(tr("Minimum Ring Si&ze for Ring-Bond Geometry Output:"), group_box);

	grid_layout->addWidget(label, 0, 0);

// xxx

	optMinRingSizeSpinBox = new QSpinBox(group_box);

	optMinRingSizeSpinBox->setRange(3, 1000);

	label->setBuddy(optMinRingSizeSpinBox);

	connect(optMinRingSizeSpinBox, SIGNAL(valueChanged(int)), this, SLOT(handleSettingsChange()));

	grid_layout->addWidget(optMinRingSizeSpinBox, 0, 1);

// xxx

	label = new QLabel(tr("Record Format:"), group_box);

	grid_layout->addWidget(label, 1, 0);

// xxx

	format_edit_widget = new SMILESRecordFormatEditWidget(group_box, optRecordFormat);

	label->setBuddy(format_edit_widget);

	connect(this, SIGNAL(updateGUI()), format_edit_widget, SLOT(updateGUI()));
	connect(format_edit_widget, SIGNAL(recordFormatChanged()), this, SLOT(handleSettingsChange()));

	grid_layout->addWidget(format_edit_widget, 1, 1);

// ---------

	main_layout->addWidget(group_box);
	main_layout->addStretch();

// ---------

	reset();
}
