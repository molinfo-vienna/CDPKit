/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * MOLFileIOSettingsEditWidget.cpp 
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
#include <QLabel>
#include <QGroupBox>
#include <QCheckBox>

#include "CDPL/Chem/ControlParameterFunctions.hpp"

#include "MOLFileIOSettingsEditWidget.hpp"
#include "CTabVersionEditWidget.hpp"
#include "ControlParameterFunctions.hpp"
#include "ControlParameterDefault.hpp"
#include "Settings.hpp"


using namespace ChOX;


MOLFileIOSettingsEditWidget::MOLFileIOSettingsEditWidget(QWidget* parent, Settings& settings): 
	SettingsEditWidget(parent), settings(settings)
{
	init();
}

bool MOLFileIOSettingsEditWidget::haveChangedSettings() const
{
	return haveChanges;
}

void MOLFileIOSettingsEditWidget::apply()
{
	using namespace CDPL;
	using namespace Chem;

	SettingsContainer& reader_params = settings.getReaderControlParameters("MOL");

	setStrictErrorCheckingParameter(reader_params, iptStrictErrorCheckingCheckBox->isChecked());
	setMDLIgnoreParityParameter(reader_params, iptIgnoreParityCheckBox->isChecked());
	setMDLTrimStringsParameter(reader_params, iptTrimStringsCheckBox->isChecked());
	setMDLTrimLinesParameter(reader_params, iptTrimLinesCheckBox->isChecked());
	setCheckLineLengthParameter(reader_params, iptCheckLineLengthCheckBox->isChecked());
	setMultiConfImportParameter(reader_params, iptMultiConfImportCheckBox->isChecked());

	SettingsContainer& writer_params = settings.getWriterControlParameters("MOL");

	setStrictErrorCheckingParameter(writer_params, optStrictErrorCheckingCheckBox->isChecked());
	setMDLIgnoreParityParameter(writer_params, optIgnoreParityCheckBox->isChecked());
	setMDLTrimStringsParameter(writer_params, optTrimStringsCheckBox->isChecked());
	setMDLTrimLinesParameter(writer_params, optTrimLinesCheckBox->isChecked());
	setCheckLineLengthParameter(writer_params, optCheckLineLengthCheckBox->isChecked());
	setMDLUpdateTimestampParameter(writer_params, optUpdateTimeStampCheckBox->isChecked());
	setMDLTruncateStringsParameter(writer_params, optTruncateStringsCheckBox->isChecked());
	setMDLTruncateLinesParameter(writer_params, optTruncateLinesCheckBox->isChecked());
	setWriteSingleRecordFilesParameter(writer_params, !optConcatenateRecordsCheckBox->isChecked());
	setMultiConfExportParameter(writer_params, optMultiConfExportCheckBox->isChecked());

	setMDLCTABVersionParameter(writer_params, optCTabVersion);
}

void MOLFileIOSettingsEditWidget::reset()
{
	using namespace CDPL;
	using namespace Chem;

	blockSignals(true);

	const SettingsContainer& reader_params = settings.getReaderControlParameters("MOL");

	iptStrictErrorCheckingCheckBox->setChecked(getStrictErrorCheckingParameter(reader_params)); 
	iptIgnoreParityCheckBox->setChecked(getMDLIgnoreParityParameter(reader_params)); 
	iptTrimStringsCheckBox->setChecked(getMDLTrimStringsParameter(reader_params)); 
	iptTrimLinesCheckBox->setChecked(getMDLTrimLinesParameter(reader_params)); 
	iptCheckLineLengthCheckBox->setChecked(getCheckLineLengthParameter(reader_params)); 
	iptMultiConfImportCheckBox->setChecked(getMultiConfImportParameter(reader_params)); 

	const SettingsContainer& writer_params = settings.getWriterControlParameters("MOL");

	optStrictErrorCheckingCheckBox->setChecked(getStrictErrorCheckingParameter(writer_params)); 
	optIgnoreParityCheckBox->setChecked(getMDLIgnoreParityParameter(writer_params)); 
	optTrimStringsCheckBox->setChecked(getMDLTrimStringsParameter(writer_params)); 
	optTrimLinesCheckBox->setChecked(getMDLTrimLinesParameter(writer_params)); 
	optCheckLineLengthCheckBox->setChecked(getCheckLineLengthParameter(writer_params)); 
	optUpdateTimeStampCheckBox->setChecked(getMDLUpdateTimestampParameter(writer_params)); 
	optTruncateStringsCheckBox->setChecked(getMDLTruncateStringsParameter(writer_params)); 
	optTruncateLinesCheckBox->setChecked(getMDLTruncateLinesParameter(writer_params)); 
	optConcatenateRecordsCheckBox->setChecked(!getWriteSingleRecordFilesParameter(writer_params)); 
	optMultiConfExportCheckBox->setChecked(getMultiConfExportParameter(writer_params)); 

	optCTabVersion = getMDLCTABVersionParameter(writer_params); 

	blockSignals(false);

	haveChanges = false;

	emit updateGUI();
}

void MOLFileIOSettingsEditWidget::setDefaults()
{
	using namespace ControlParameterDefault;

	iptStrictErrorCheckingCheckBox->setChecked(MOL_INPUT_STRICT_ERROR_CHECKING);
	iptIgnoreParityCheckBox->setChecked(MOL_INPUT_IGNORE_PARITY);
	iptTrimStringsCheckBox->setChecked(MOL_INPUT_TRIM_STRINGS);
	iptTrimLinesCheckBox->setChecked(MOL_INPUT_TRIM_LINES);
	iptCheckLineLengthCheckBox->setChecked(MOL_INPUT_CHECK_LINE_LENGTH);
	iptMultiConfImportCheckBox->setChecked(MOL_INPUT_MULTI_CONF_IMPORT);

	optStrictErrorCheckingCheckBox->setChecked(MOL_OUTPUT_STRICT_ERROR_CHECKING);
	optIgnoreParityCheckBox->setChecked(MOL_OUTPUT_IGNORE_PARITY);
	optTrimStringsCheckBox->setChecked(MOL_OUTPUT_TRIM_STRINGS);
	optTrimLinesCheckBox->setChecked(MOL_OUTPUT_TRIM_LINES);
	optCheckLineLengthCheckBox->setChecked(MOL_OUTPUT_CHECK_LINE_LENGTH);
	optUpdateTimeStampCheckBox->setChecked(MOL_OUTPUT_UPDATE_TIMESTAMP);
	optTruncateStringsCheckBox->setChecked(MOL_OUTPUT_TRUNCATE_STRINGS);
	optTruncateLinesCheckBox->setChecked(MOL_OUTPUT_TRUNCATE_LINES);
	optConcatenateRecordsCheckBox->setChecked(!MOL_OUTPUT_WRITE_SINGLE_RECORD_FILES);
	optMultiConfExportCheckBox->setChecked(MOL_OUTPUT_MULTI_CONF_EXPORT);

	optCTabVersion = MOL_OUTPUT_CTAB_VERSION;

	haveChanges = true;

	emit updateGUI();
	emit settingsChanged();
}

void MOLFileIOSettingsEditWidget::handleSettingsChange()
{
	haveChanges = true;

	emit SettingsEditWidget::settingsChanged();
}

void MOLFileIOSettingsEditWidget::handleSettingsChange(bool)
{
	haveChanges = true;

	emit SettingsEditWidget::settingsChanged();
}

void MOLFileIOSettingsEditWidget::init()
{
	QBoxLayout* main_layout = new QVBoxLayout(this);

// ---------

	QGroupBox* group_box = new QGroupBox(tr("Input"), this);
	QBoxLayout* v_box_layout = new QVBoxLayout(group_box);

// +++

	iptStrictErrorCheckingCheckBox = new QCheckBox(tr("&Perform strict Error Checking"), group_box);

	v_box_layout->addWidget(iptStrictErrorCheckingCheckBox);

	connect(iptStrictErrorCheckingCheckBox, SIGNAL(toggled(bool)), this, SLOT(handleSettingsChange(bool)));

// +++

	iptIgnoreParityCheckBox = new QCheckBox(tr("Ignore Ato&m Stereo Parity"), group_box);

	v_box_layout->addWidget(iptIgnoreParityCheckBox);

	connect(iptIgnoreParityCheckBox, SIGNAL(toggled(bool)), this, SLOT(handleSettingsChange(bool)));

// +++

	iptTrimStringsCheckBox = new QCheckBox(tr("R&emove leading/trailing Whitespace from Strings"), group_box);

	v_box_layout->addWidget(iptTrimStringsCheckBox);

	connect(iptTrimStringsCheckBox, SIGNAL(toggled(bool)), this, SLOT(handleSettingsChange(bool)));

// +++

	iptTrimLinesCheckBox = new QCheckBox(tr("Remove &leading/trailing Whitespace from Lines"), group_box);

	v_box_layout->addWidget(iptTrimLinesCheckBox);

	connect(iptTrimLinesCheckBox, SIGNAL(toggled(bool)), this, SLOT(handleSettingsChange(bool)));

// +++

	iptCheckLineLengthCheckBox = new QCheckBox(tr("Check Line Len&gth Limit"), group_box);

	v_box_layout->addWidget(iptCheckLineLengthCheckBox);

	connect(iptCheckLineLengthCheckBox, SIGNAL(toggled(bool)), this, SLOT(handleSettingsChange(bool)));

// +++

	iptMultiConfImportCheckBox = new QCheckBox(tr("&Combine Conformations"), group_box);

	v_box_layout->addWidget(iptMultiConfImportCheckBox);

	connect(iptMultiConfImportCheckBox, SIGNAL(toggled(bool)), this, SLOT(handleSettingsChange(bool)));

// +++

	setFocusProxy(iptStrictErrorCheckingCheckBox);

	main_layout->addWidget(group_box);

// ---------

	group_box = new QGroupBox(tr("Output"), this);
	v_box_layout = new QVBoxLayout(group_box);

// +++

	optStrictErrorCheckingCheckBox = new QCheckBox(tr("Per&form strict Error Checking"), group_box);

	v_box_layout->addWidget(optStrictErrorCheckingCheckBox);

	connect(optStrictErrorCheckingCheckBox, SIGNAL(toggled(bool)), this, SLOT(handleSettingsChange(bool)));

// +++

	optIgnoreParityCheckBox = new QCheckBox(tr("Don't write Atom Stereo Parit&y"), group_box);

	v_box_layout->addWidget(optIgnoreParityCheckBox);

	connect(optIgnoreParityCheckBox, SIGNAL(toggled(bool)), this, SLOT(handleSettingsChange(bool)));

// +++

	optTrimStringsCheckBox = new QCheckBox(tr("Remove leading/trailing W&hitespace from Strings"), group_box);

	v_box_layout->addWidget(optTrimStringsCheckBox);

	connect(optTrimStringsCheckBox, SIGNAL(toggled(bool)), this, SLOT(handleSettingsChange(bool)));

// +++

	optTrimLinesCheckBox = new QCheckBox(tr("Remove Leading/Trailing Whi&tespace from Lines"), group_box);

	v_box_layout->addWidget(optTrimLinesCheckBox);

	connect(optTrimLinesCheckBox, SIGNAL(toggled(bool)), this, SLOT(handleSettingsChange(bool)));

// +++

	optTruncateStringsCheckBox = new QCheckBox(tr("Truncate Strings to fit a&vailable Space"), group_box);

	v_box_layout->addWidget(optTruncateStringsCheckBox);

	connect(optTruncateStringsCheckBox, SIGNAL(toggled(bool)), this, SLOT(handleSettingsChange(bool)));

// +++

	optTruncateLinesCheckBox = new QCheckBox(tr("Tr&uncate Lines to adhere to max. Line Length"), group_box);

	v_box_layout->addWidget(optTruncateLinesCheckBox);

	connect(optTruncateLinesCheckBox, SIGNAL(toggled(bool)), this, SLOT(handleSettingsChange(bool)));

// +++

	optCheckLineLengthCheckBox = new QCheckBox(tr("Check Li&ne Length Limit"), group_box);

	v_box_layout->addWidget(optCheckLineLengthCheckBox);

	connect(optCheckLineLengthCheckBox, SIGNAL(toggled(bool)), this, SLOT(handleSettingsChange(bool)));

// +++

	optUpdateTimeStampCheckBox = new QCheckBox(tr("Update Time&stamps"), group_box);

	v_box_layout->addWidget(optUpdateTimeStampCheckBox);

	connect(optUpdateTimeStampCheckBox, SIGNAL(toggled(bool)), this, SLOT(handleSettingsChange(bool)));

// +++

	optConcatenateRecordsCheckBox = new QCheckBox(tr("Concatenate Records to a single F&ile"), group_box);

	v_box_layout->addWidget(optConcatenateRecordsCheckBox);

	connect(optConcatenateRecordsCheckBox, SIGNAL(toggled(bool)), this, SLOT(handleSettingsChange(bool)));

// +++

	optMultiConfExportCheckBox = new QCheckBox(tr("&Export all Conformations"), group_box);

	v_box_layout->addWidget(optMultiConfExportCheckBox);

	connect(optMultiConfExportCheckBox, SIGNAL(toggled(bool)), this, SLOT(handleSettingsChange(bool)));

// +++

	QFrame* frame = new QFrame(group_box);

	frame->setFrameStyle(QFrame::HLine | QFrame::Sunken);

	v_box_layout->addWidget(frame);

// +++

	QBoxLayout* h_box_layout = new QHBoxLayout();
	v_box_layout->addLayout(h_box_layout);

// xxx

	QLabel* label = new QLabel(tr("Molfile CTab-Version&:"), group_box);

	h_box_layout->addWidget(label, 1);

	CTabVersionEditWidget* version_edit_widget = new CTabVersionEditWidget(group_box, optCTabVersion);

	label->setBuddy(version_edit_widget);

	connect(this, SIGNAL(updateGUI()), version_edit_widget, SLOT(updateGUI()));
	connect(version_edit_widget, SIGNAL(versionChanged()), this, SLOT(handleSettingsChange()));

	h_box_layout->addWidget(version_edit_widget, 0);
	h_box_layout->addStretch(1);

// ---------

	main_layout->addWidget(group_box);
	main_layout->addStretch();

// ---------

	reset();
}
