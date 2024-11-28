/* 
 * OtherIOSettingsEditWidget.cpp 
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
#include <QGroupBox>
#include <QCheckBox>
#include <QLabel>
#include <QLineEdit>
#include <QDoubleSpinBox>

#include "CDPL/Chem/ControlParameterFunctions.hpp"
#include "CDPL/Vis/ControlParameterFunctions.hpp"
#include "CDPL/Vis/ControlParameterDefault.hpp"
#include "CDPL/Vis/Brush.hpp"

#include "OtherIOSettingsEditWidget.hpp"
#include "ColorEditWidget.hpp"
#include "RecordSeparatorEditWidget.hpp"
#include "ControlParameterFunctions.hpp"
#include "ControlParameterDefault.hpp"
#include "Settings.hpp"


using namespace ChOX;


OtherIOSettingsEditWidget::OtherIOSettingsEditWidget(QWidget* parent, Settings& settings): 
    SettingsEditWidget(parent), settings(settings)
{
    init();
}

bool OtherIOSettingsEditWidget::haveChangedSettings() const
{
    return haveChanges;
}

void OtherIOSettingsEditWidget::apply()
{
    using namespace CDPL;
    using namespace Chem;
    using namespace Vis;

    SettingsContainer& jme_rparams = settings.getReaderControlParameters("JME");

    setStrictErrorCheckingParameter(jme_rparams, jmeIptStrictErrorCheckingCheckBox->isChecked());

    SettingsContainer& jme_wparams = settings.getWriterControlParameters("JME");

    setStrictErrorCheckingParameter(jme_wparams, jmeOptStrictErrorCheckingCheckBox->isChecked());
    setOutputSingleRecordFilesParameter(jme_wparams, !jmeOptConcatenateRecordsCheckBox->isChecked());
    setRecordSeparatorParameter(jme_wparams, jmeOptRecordSeparator);

    SettingsContainer& inchi_rparams = settings.getReaderControlParameters("INCHI");

    setStrictErrorCheckingParameter(inchi_rparams, inchiIptStrictErrorCheckingCheckBox->isChecked());
    setINCHIInputOptionsParameter(inchi_rparams, inchiIptOptionsLineEdit->text().toStdString());

    SettingsContainer& inchi_wparams = settings.getWriterControlParameters("INCHI");

    setStrictErrorCheckingParameter(inchi_wparams, inchiOptStrictErrorCheckingCheckBox->isChecked());
    setOutputSingleRecordFilesParameter(inchi_wparams, !inchiOptConcatenateRecordsCheckBox->isChecked());
    setRecordSeparatorParameter(inchi_wparams, inchiOptRecordSeparator);
    setINCHIOutputOptionsParameter(inchi_wparams, inchiOptOptionsLineEdit->text().toStdString());

    SettingsContainer& smarts_rparams = settings.getReaderControlParameters("SMARTS");

    setStrictErrorCheckingParameter(smarts_rparams, smartsIptStrictErrorCheckingCheckBox->isChecked());

    SettingsContainer& smarts_wparams = settings.getWriterControlParameters("SMARTS");

    setStrictErrorCheckingParameter(smarts_wparams, smartsOptStrictErrorCheckingCheckBox->isChecked());
    setOutputSingleRecordFilesParameter(smarts_wparams, !smartsOptConcatenateRecordsCheckBox->isChecked());
    setRecordSeparatorParameter(smarts_wparams, smartsOptRecordSeparator);

    SettingsContainer& img_params = settings.getWriterControlParameters("img");

    setBackgroundBrushParameter(img_params, Brush(imgOptBackgroundColor,
                                                  imgOptEraseBackgroundCheckBox->isChecked() ?
                                                  Brush::SOLID_PATTERN : Brush::NO_PATTERN));

    setOutputScalingFactorParameter(img_params, imgOptOutputScalingFactorSpinBox->value());
}

void OtherIOSettingsEditWidget::reset()
{
    using namespace CDPL;
    using namespace Chem;
    using namespace Vis;

    blockSignals(true);

    const SettingsContainer& jme_rparams = settings.getReaderControlParameters("JME");

    jmeIptStrictErrorCheckingCheckBox->setChecked(getStrictErrorCheckingParameter(jme_rparams)); 

    const SettingsContainer& jme_wparams = settings.getWriterControlParameters("JME");

    jmeOptStrictErrorCheckingCheckBox->setChecked(getStrictErrorCheckingParameter(jme_wparams)); 
    jmeOptConcatenateRecordsCheckBox->setChecked(!getOutputSingleRecordFilesParameter(jme_wparams)); 
    jmeOptRecordSeparator = getRecordSeparatorParameter(jme_wparams); 

    const SettingsContainer& inchi_rparams = settings.getReaderControlParameters("INCHI");

    inchiIptStrictErrorCheckingCheckBox->setChecked(getStrictErrorCheckingParameter(inchi_rparams)); 
    inchiIptOptionsLineEdit->setText(QString::fromStdString(getINCHIInputOptionsParameter(inchi_rparams))); 

    const SettingsContainer& inchi_wparams = settings.getWriterControlParameters("INCHI");

    inchiOptStrictErrorCheckingCheckBox->setChecked(getStrictErrorCheckingParameter(inchi_wparams)); 
    inchiOptConcatenateRecordsCheckBox->setChecked(!getOutputSingleRecordFilesParameter(inchi_wparams)); 
    inchiOptOptionsLineEdit->setText(QString::fromStdString(getINCHIOutputOptionsParameter(inchi_wparams))); 
    inchiOptRecordSeparator = getRecordSeparatorParameter(inchi_wparams); 

    const SettingsContainer& smarts_rparams = settings.getReaderControlParameters("SMARTS");

    smartsIptStrictErrorCheckingCheckBox->setChecked(getStrictErrorCheckingParameter(smarts_rparams)); 

    const SettingsContainer& smarts_wparams = settings.getWriterControlParameters("SMARTS");

    smartsOptStrictErrorCheckingCheckBox->setChecked(getStrictErrorCheckingParameter(smarts_wparams)); 
    smartsOptConcatenateRecordsCheckBox->setChecked(!getOutputSingleRecordFilesParameter(smarts_wparams)); 
    smartsOptRecordSeparator = getRecordSeparatorParameter(smarts_wparams); 

    const SettingsContainer& img_params = settings.getWriterControlParameters("img");

    imgOptEraseBackgroundCheckBox->setChecked(getBackgroundBrushParameter(img_params).getStyle() != Brush::NO_PATTERN);
    imgOptBackgroundColor = getBackgroundBrushParameter(img_params).getColor(); 
    imgOptOutputScalingFactorSpinBox->setValue(getOutputScalingFactorParameter(img_params)); 

    blockSignals(false);

    haveChanges = false;

    handleImgBackgroundSettingsChange(false);

    emit updateGUI();
}

void OtherIOSettingsEditWidget::setDefaults()
{
    using namespace ControlParameterDefault;

    jmeIptStrictErrorCheckingCheckBox->setChecked(JME_INPUT_STRICT_ERROR_CHECKING);

    jmeOptStrictErrorCheckingCheckBox->setChecked(JME_OUTPUT_STRICT_ERROR_CHECKING);
    jmeOptConcatenateRecordsCheckBox->setChecked(!JME_OUTPUT_SINGLE_RECORD_FILES);
    jmeOptRecordSeparator = JME_OUTPUT_RECORD_SEPARATOR;

    inchiIptStrictErrorCheckingCheckBox->setChecked(INCHI_INPUT_STRICT_ERROR_CHECKING);
    inchiIptOptionsLineEdit->setText(QString::fromStdString(INCHI_INPUT_OPTIONS));

    inchiOptStrictErrorCheckingCheckBox->setChecked(INCHI_OUTPUT_STRICT_ERROR_CHECKING);
    inchiOptConcatenateRecordsCheckBox->setChecked(!INCHI_OUTPUT_SINGLE_RECORD_FILES);
    inchiOptOptionsLineEdit->setText(QString::fromStdString(INCHI_OUTPUT_OPTIONS));
    inchiOptRecordSeparator = INCHI_OUTPUT_RECORD_SEPARATOR;

    smartsIptStrictErrorCheckingCheckBox->setChecked(SMARTS_INPUT_STRICT_ERROR_CHECKING);

    smartsOptStrictErrorCheckingCheckBox->setChecked(SMARTS_OUTPUT_STRICT_ERROR_CHECKING);
    smartsOptConcatenateRecordsCheckBox->setChecked(!SMARTS_OUTPUT_SINGLE_RECORD_FILES);
    smartsOptRecordSeparator = SMARTS_OUTPUT_RECORD_SEPARATOR;

    imgOptEraseBackgroundCheckBox->setChecked(CDPL::Vis::ControlParameterDefault::BACKGROUND_BRUSH.getStyle() != CDPL::Vis::Brush::NO_PATTERN);
    imgOptBackgroundColor = CDPL::Vis::ControlParameterDefault::BACKGROUND_BRUSH.getColor();
    imgOptOutputScalingFactorSpinBox->setValue(CDPL::Vis::ControlParameterDefault::OUTPUT_SCALING_FACTOR); 

    haveChanges = true;

    handleImgBackgroundSettingsChange(false);

    emit updateGUI();
    emit settingsChanged();
}

void OtherIOSettingsEditWidget::handleSettingsChange()
{
    haveChanges = true;

    emit SettingsEditWidget::settingsChanged();
}

void OtherIOSettingsEditWidget::handleSettingsChange(bool)
{
    haveChanges = true;

    emit SettingsEditWidget::settingsChanged();
}

void OtherIOSettingsEditWidget::handleSettingsChange(const QString&)
{
    haveChanges = true;

    emit SettingsEditWidget::settingsChanged();
}

void OtherIOSettingsEditWidget::handleImgBackgroundSettingsChange(bool)
{
    imgBackgroundColorWidget->setEnabled(imgOptEraseBackgroundCheckBox->isChecked());
}

void OtherIOSettingsEditWidget::init()
{
    QGridLayout* main_layout = new QGridLayout(this);

// --------------------------------------------

    QGroupBox* group_box = new QGroupBox(tr("JME Input"), this);
    QBoxLayout* v_box_layout = new QVBoxLayout(group_box);

// +++

    jmeIptStrictErrorCheckingCheckBox = new QCheckBox(tr("&Perform strict Error Checking"), group_box);

    v_box_layout->addWidget(jmeIptStrictErrorCheckingCheckBox);
    v_box_layout->addStretch();

    connect(jmeIptStrictErrorCheckingCheckBox, SIGNAL(toggled(bool)), this, SLOT(handleSettingsChange(bool)));

// +++

    main_layout->addWidget(group_box, 0, 0);

// ---------

    group_box = new QGroupBox(tr("JME Output"), this);
    v_box_layout = new QVBoxLayout(group_box);

// +++

    jmeOptStrictErrorCheckingCheckBox = new QCheckBox(tr("Per&form strict Error Checking"), group_box);

    v_box_layout->addWidget(jmeOptStrictErrorCheckingCheckBox);

    connect(jmeOptStrictErrorCheckingCheckBox, SIGNAL(toggled(bool)), this, SLOT(handleSettingsChange(bool)));

    setFocusProxy(jmeOptStrictErrorCheckingCheckBox);

// +++

    jmeOptConcatenateRecordsCheckBox = new QCheckBox(tr("Concatenate Records to a single F&ile"), group_box);

    v_box_layout->addWidget(jmeOptConcatenateRecordsCheckBox);

    connect(jmeOptConcatenateRecordsCheckBox, SIGNAL(toggled(bool)), this, SLOT(handleSettingsChange(bool)));

// +++

    QFrame* frame = new QFrame(group_box);

    frame->setFrameStyle(QFrame::HLine | QFrame::Sunken);

    v_box_layout->addWidget(frame);

// xxx

    QBoxLayout* h_box_layout = new QHBoxLayout();

    v_box_layout->addLayout(h_box_layout);

    QLabel* label = new QLabel(tr("Record Separator:"), group_box);

    h_box_layout->addWidget(label);

// xxx

    RecordSeparatorEditWidget* sep_edit_widget = new RecordSeparatorEditWidget(group_box, jmeOptRecordSeparator);

    label->setBuddy(sep_edit_widget);

    connect(this, SIGNAL(updateGUI()), sep_edit_widget, SLOT(updateGUI()));
    connect(sep_edit_widget, SIGNAL(recordSeparatorChanged()), this, SLOT(handleSettingsChange()));

    h_box_layout->addWidget(sep_edit_widget);
    h_box_layout->addStretch();

// +++

    main_layout->addWidget(group_box, 0, 1);

// --------------------------------------------

    group_box = new QGroupBox(tr("INCHI Input"), this);
    v_box_layout = new QVBoxLayout(group_box);

// +++

    inchiIptStrictErrorCheckingCheckBox = new QCheckBox(tr("Perform strict Error Checki&ng"), group_box);

    v_box_layout->addWidget(inchiIptStrictErrorCheckingCheckBox);
    v_box_layout->addStretch();

    connect(inchiIptStrictErrorCheckingCheckBox, SIGNAL(toggled(bool)), this, SLOT(handleSettingsChange(bool)));

// +++

    frame = new QFrame(group_box);

    frame->setFrameStyle(QFrame::HLine | QFrame::Sunken);

    v_box_layout->addWidget(frame);

// xxx

    h_box_layout = new QHBoxLayout();

    v_box_layout->addLayout(h_box_layout);

    label = new QLabel(tr("INCHI Options:"), group_box);

    h_box_layout->addWidget(label);

// xxx

    inchiIptOptionsLineEdit = new QLineEdit(group_box);

    connect(inchiIptOptionsLineEdit, SIGNAL(textChanged(const QString&)), this, SLOT(handleSettingsChange(const QString&)));

    h_box_layout->addWidget(inchiIptOptionsLineEdit);

// +++

    v_box_layout->addStretch();

    main_layout->addWidget(group_box, 1, 0);

// ---------

    group_box = new QGroupBox(tr("INCHI Output"), this);
    v_box_layout = new QVBoxLayout(group_box);

// +++

    inchiOptStrictErrorCheckingCheckBox = new QCheckBox(tr("Perform strict &Error Checking"), group_box);

    v_box_layout->addWidget(inchiOptStrictErrorCheckingCheckBox);

    connect(inchiOptStrictErrorCheckingCheckBox, SIGNAL(toggled(bool)), this, SLOT(handleSettingsChange(bool)));

// +++

    inchiOptConcatenateRecordsCheckBox = new QCheckBox(tr("Concatenate Records to a sin&gle File"), group_box);

    v_box_layout->addWidget(inchiOptConcatenateRecordsCheckBox);

    connect(inchiOptConcatenateRecordsCheckBox, SIGNAL(toggled(bool)), this, SLOT(handleSettingsChange(bool)));

// +++

    frame = new QFrame(group_box);

    frame->setFrameStyle(QFrame::HLine | QFrame::Sunken);

    v_box_layout->addWidget(frame);

// xxx

    QGridLayout* grid_layout = new QGridLayout();

    v_box_layout->addLayout(grid_layout);

    label = new QLabel(tr("Record Separator:"), group_box);

    grid_layout->addWidget(label, 1, 0);

// xxx

    sep_edit_widget = new RecordSeparatorEditWidget(group_box, inchiOptRecordSeparator);

    label->setBuddy(sep_edit_widget);

    connect(this, SIGNAL(updateGUI()), sep_edit_widget, SLOT(updateGUI()));
    connect(sep_edit_widget, SIGNAL(recordSeparatorChanged()), this, SLOT(handleSettingsChange()));

    grid_layout->addWidget(sep_edit_widget, 1, 1);

// xxx

    label = new QLabel(tr("INCHI Options:"), group_box);

    grid_layout->addWidget(label, 0, 0);

// xxx

    inchiOptOptionsLineEdit = new QLineEdit(group_box);

    connect(inchiOptOptionsLineEdit, SIGNAL(textChanged(const QString&)), this, SLOT(handleSettingsChange(const QString&)));

    grid_layout->addWidget(inchiOptOptionsLineEdit, 0, 1);

// +++

    main_layout->addWidget(group_box, 1, 1);

// -----------------------------------------

    group_box = new QGroupBox(tr("SMARTS Input"), this);
    v_box_layout = new QVBoxLayout(group_box);

// +++

    smartsIptStrictErrorCheckingCheckBox = new QCheckBox(tr("Perfor&m strict Error Checking"), group_box);

    v_box_layout->addWidget(smartsIptStrictErrorCheckingCheckBox);
    v_box_layout->addStretch();

    connect(smartsIptStrictErrorCheckingCheckBox, SIGNAL(toggled(bool)), this, SLOT(handleSettingsChange(bool)));

// +++

    main_layout->addWidget(group_box, 2, 0);

// ---------

    group_box = new QGroupBox(tr("SMARTS Output"), this);
    v_box_layout = new QVBoxLayout(group_box);

// +++

    smartsOptStrictErrorCheckingCheckBox = new QCheckBox(tr("Perform strict Error-C&hecking"), group_box);

    v_box_layout->addWidget(smartsOptStrictErrorCheckingCheckBox);

    connect(smartsOptStrictErrorCheckingCheckBox, SIGNAL(toggled(bool)), this, SLOT(handleSettingsChange(bool)));

// +++

    smartsOptConcatenateRecordsCheckBox = new QCheckBox(tr("Concatenate Records to a &single File"), group_box);

    v_box_layout->addWidget(smartsOptConcatenateRecordsCheckBox);

    connect(smartsOptConcatenateRecordsCheckBox, SIGNAL(toggled(bool)), this, SLOT(handleSettingsChange(bool)));

// +++

    frame = new QFrame(group_box);

    frame->setFrameStyle(QFrame::HLine | QFrame::Sunken);

    v_box_layout->addWidget(frame);

// +++

    h_box_layout = new QHBoxLayout();

    v_box_layout->addLayout(h_box_layout);

    label = new QLabel(tr("Record Separator:"), group_box);

    h_box_layout->addWidget(label);

// +++

    sep_edit_widget = new RecordSeparatorEditWidget(group_box, smartsOptRecordSeparator);

    label->setBuddy(sep_edit_widget);

    connect(this, SIGNAL(updateGUI()), sep_edit_widget, SLOT(updateGUI()));
    connect(sep_edit_widget, SIGNAL(recordSeparatorChanged()), this, SLOT(handleSettingsChange()));

    h_box_layout->addWidget(sep_edit_widget);
    h_box_layout->addStretch();

// +++

    main_layout->addWidget(group_box, 2, 1);

// --------------------------------------------

    group_box = new QGroupBox(tr("Image Output"), this);
    v_box_layout = new QVBoxLayout(group_box);

// +++

    imgOptEraseBackgroundCheckBox = new QCheckBox(tr("Fill Bac&kground"), group_box);

    v_box_layout->addWidget(imgOptEraseBackgroundCheckBox);

    connect(imgOptEraseBackgroundCheckBox, SIGNAL(toggled(bool)), this, SLOT(handleSettingsChange(bool)));
    connect(imgOptEraseBackgroundCheckBox, SIGNAL(toggled(bool)), this, SLOT(handleImgBackgroundSettingsChange(bool)));

// +++

    frame = new QFrame(group_box);

    frame->setFrameStyle(QFrame::HLine | QFrame::Sunken);

    v_box_layout->addWidget(frame);

// +++

    grid_layout = new QGridLayout();

    v_box_layout->addLayout(grid_layout);

    label = new QLabel(tr("Background Color:"), group_box);

    grid_layout->addWidget(label, 0, 0);

    imgBackgroundColorWidget = new ColorEditWidget(group_box, imgOptBackgroundColor);

    label->setBuddy(imgBackgroundColorWidget);

    grid_layout->addWidget(imgBackgroundColorWidget, 0, 1);

    connect(imgBackgroundColorWidget, SIGNAL(colorChanged()), this, SLOT(handleSettingsChange()));
    connect(this, SIGNAL(updateGUI()), imgBackgroundColorWidget, SLOT(updateGUI()));

// +++

    label = new QLabel(tr("Scaling Factor:"), group_box);

    grid_layout->addWidget(label, 1, 0);

    imgOptOutputScalingFactorSpinBox = new QDoubleSpinBox(group_box);

    imgOptOutputScalingFactorSpinBox->setMinimumWidth(80);
    imgOptOutputScalingFactorSpinBox->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

    label->setBuddy(imgOptOutputScalingFactorSpinBox);

    grid_layout->addWidget(imgOptOutputScalingFactorSpinBox, 1, 1);

    connect(imgOptOutputScalingFactorSpinBox, SIGNAL(valueChanged(double)), this, SLOT(handleSettingsChange()));

// +++

    main_layout->addWidget(group_box, 3, 0, 1, 2);
    main_layout->setRowStretch(4, 1);

// ---------

    reset();
}
