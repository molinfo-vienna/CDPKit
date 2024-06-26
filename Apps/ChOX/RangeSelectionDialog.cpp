/* 
 * RangeSelectionDialog.cpp 
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
#include <QLabel>
#include <QPushButton>
#include <QSpinBox>

#include "RangeSelectionDialog.hpp"
#include "DataSet.hpp"


using namespace ChOX;


RangeSelectionDialog::RangeSelectionDialog(QWidget* parent, DataSet& data_set, Qt::WindowFlags f):
    QDialog(parent, f), dataSet(data_set)
{
    init();
}

int RangeSelectionDialog::exec()
{
    if (dataSet.getSize() == 0) {
        rangeStartSpinBox->setEnabled(false);
        rangeEndSpinBox->setEnabled(false);

    } else {
        rangeStartSpinBox->setEnabled(true);
        rangeEndSpinBox->setEnabled(true);

        rangeEndSpinBox->setMaximum(int(dataSet.getSize()));
        rangeStartSpinBox->setMaximum(rangeEndSpinBox->value());
        rangeEndSpinBox->setMinimum(rangeStartSpinBox->value());
    }

    return QDialog::exec();
}

void RangeSelectionDialog::select()
{
    if (dataSet.getSize() > 0) 
        dataSet.selectRecordRange(rangeStartSpinBox->value() - 1, rangeEndSpinBox->value() - 1, true);
    
    QDialog::accept();
}

void RangeSelectionDialog::unselect()
{
    if (dataSet.getSize() > 0) 
        dataSet.selectRecordRange(rangeStartSpinBox->value() - 1, rangeEndSpinBox->value() - 1, false);
    
    QDialog::accept();
}

void RangeSelectionDialog::handleRangeStartChange(int start)
{
    rangeEndSpinBox->setMinimum(start);
}

void RangeSelectionDialog::handleRangeEndChange(int end)
{
    rangeStartSpinBox->setMaximum(end);
}

void RangeSelectionDialog::init()
{
    setWindowTitle(tr("ChOX - Select/Unselect Record Range"));

// ------

    QBoxLayout* main_layout = new QVBoxLayout(this);

    main_layout->addStretch();

// ------

    QLabel* label = new QLabel(tr("Select/Unselect Records"), this);

    label->setAlignment(Qt::AlignCenter);
    
    main_layout->addWidget(label);

// ------

    QGridLayout* grid_layout = new QGridLayout();
    
    main_layout->addLayout(grid_layout);

    grid_layout->setColumnStretch(1, 1);

// ++++

    label = new QLabel(tr("From:"), this);
    
    grid_layout->addWidget(label, 0, 0);

// ++++

    rangeStartSpinBox = new QSpinBox(this);

    rangeStartSpinBox->setMinimum(1);
    rangeStartSpinBox->setValue(1);

    label->setBuddy(rangeStartSpinBox);

    grid_layout->addWidget(rangeStartSpinBox, 0, 1);

    connect(rangeStartSpinBox, SIGNAL(valueChanged(int)), this, SLOT(handleRangeStartChange(int)));

// ++++

    label = new QLabel(tr("To:"), this);
    
    grid_layout->addWidget(label, 1, 0);

// ++++

    rangeEndSpinBox = new QSpinBox(this);

    rangeEndSpinBox->setValue(1);

    label->setBuddy(rangeEndSpinBox);

    grid_layout->addWidget(rangeEndSpinBox, 1, 1);

    connect(rangeEndSpinBox, SIGNAL(valueChanged(int)), this, SLOT(handleRangeEndChange(int)));

// ------

    main_layout->addStretch();

    QFrame* frame = new QFrame(this);

    frame->setFrameStyle(QFrame::HLine | QFrame::Sunken);

    main_layout->addWidget(frame);

// ------

    QBoxLayout* h_box_layout = new QHBoxLayout();

    main_layout->addLayout(h_box_layout);

// ++++

    QPushButton* button = new QPushButton(tr("&Select"), this);

    connect(button, SIGNAL(clicked()), this, SLOT(select()));

    h_box_layout->addStretch();
    h_box_layout->addWidget(button);

// ++++

    button = new QPushButton(tr("&Unselect"), this);

    connect(button, SIGNAL(clicked()), this, SLOT(unselect()));

    h_box_layout->addWidget(button);

// ++++

    button = new QPushButton(tr("&Cancel"), this);

    connect(button, SIGNAL(clicked()), this, SLOT(reject()));

    h_box_layout->addWidget(button);
    h_box_layout->addStretch();
}

