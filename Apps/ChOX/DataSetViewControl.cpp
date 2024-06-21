/* 
 * DataSetViewControl.cpp 
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


#include <QToolButton>
#include <QLabel>
#include <QSpinBox>
#include <QLineEdit>
#include <QValidator>
#include <QIcon>
#include <QMainWindow>

#include "DataSetViewControl.hpp"
#include "DataSetView.hpp"
#include "DataSetPageView.hpp"
#include "DataSet.hpp"


using namespace ChOX;


DataSetViewControl::DataSetViewControl(QMainWindow* parent, DataSetView& view): 
    QToolBar(parent), dataSetView(view)
{
    init();
}

void DataSetViewControl::handlePageOffsetInput()
{
    dataSetView.getPageView().setPageOffset(pageOffsetLineEdit->text().toInt() - 1);
}

void DataSetViewControl::handleNextPageButtonClick()
{
    DataSetPageView& page_view = dataSetView.getPageView();

    page_view.setPageOffset(page_view.getPageOffset() + page_view.getNumRows() * page_view.getNumColumns());
}

void DataSetViewControl::handlePrevPageButtonClick()
{
    DataSetPageView& page_view = dataSetView.getPageView();

    page_view.setPageOffset(page_view.getPageOffset() - page_view.getNumRows() * page_view.getNumColumns());
}

void DataSetViewControl::handleNextLineButtonClick()
{
    DataSetPageView& page_view = dataSetView.getPageView();

    page_view.setPageOffset(page_view.getPageOffset() + page_view.getNumColumns());
}

void DataSetViewControl::handlePrevLineButtonClick()
{
    DataSetPageView& page_view = dataSetView.getPageView();

    page_view.setPageOffset(page_view.getPageOffset() - page_view.getNumColumns());
}

void DataSetViewControl::updateGUI(int)
{
    int num_records = dataSetView.getDataSet().getSize();
    int page_offs = dataSetView.getPageView().getPageOffset();
    
    if (num_records > 0) {
        pageOffsetValidator->setRange(1, num_records);
        pageOffsetLineEdit->setText(QString().setNum(page_offs + 1));
        pageOffsetLineEdit->setEnabled(true);

        prevPageButton->setEnabled(page_offs > 0);
        nextPageButton->setEnabled(page_offs < num_records - 1);

        prevLineButton->setEnabled(page_offs > 0);
        nextLineButton->setEnabled(page_offs < num_records - 1);

    } else {
        pageOffsetLineEdit->setEnabled(false);
        pageOffsetLineEdit->setText("1");
        pageOffsetValidator->setRange(1, 1);

        prevPageButton->setEnabled(false);
        nextPageButton->setEnabled(false);
        prevLineButton->setEnabled(false);
        nextLineButton->setEnabled(false);
    }
}

void DataSetViewControl::init()
{
    setObjectName("dataSetViewControl");
    setWindowTitle(tr("Navigation Toolbar"));

    addWidget(new QLabel(tr("Rows") + ":", this));

    rowCountSpinBox = new QSpinBox(this);

    rowCountSpinBox->setMinimum(1);
    rowCountSpinBox->setValue(1);
    rowCountSpinBox->setToolTip(tr("Set Number of Rows"));

    addWidget(rowCountSpinBox);

    addWidget(new QLabel(tr("Columns") + ":", this));

    columnCountSpinBox = new QSpinBox(this);

    columnCountSpinBox->setMinimum(1);
    columnCountSpinBox->setValue(1);
    columnCountSpinBox->setToolTip(tr("Set Number of Columns"));

    addWidget(columnCountSpinBox);

    prevPageButton = new QToolButton(this);

    prevPageButton->setIcon(QIcon(":/Icons/2leftarrow.png"));
    prevPageButton->setToolTip(tr("Previous Page"));

    addWidget(prevPageButton);

    prevLineButton = new QToolButton(this);

    prevLineButton->setIcon(QIcon(":/Icons/1leftarrow.png"));
    prevLineButton->setToolTip(tr("Previous Row"));

    addWidget(prevLineButton);

    pageOffsetLineEdit = new QLineEdit("1", this);
    pageOffsetValidator = new QIntValidator(pageOffsetLineEdit);

    pageOffsetLineEdit->setValidator(pageOffsetValidator);
    pageOffsetLineEdit->setToolTip(tr("Go to Record"));
    pageOffsetLineEdit->setSizePolicy(QSizePolicy(QSizePolicy::Preferred, 
                                                  pageOffsetLineEdit->sizePolicy().verticalPolicy()));

    addWidget(pageOffsetLineEdit);

    nextLineButton = new QToolButton(this);

    nextLineButton->setIcon(QIcon(":/Icons/1rightarrow.png"));
    nextLineButton->setToolTip(tr("Next Row"));

    addWidget(nextLineButton);

    nextPageButton = new QToolButton(this);

    nextPageButton->setIcon(QIcon(":/Icons/2rightarrow.png"));
    nextPageButton->setToolTip(tr("Next Page"));

    addWidget(nextPageButton);

    updateGUI(0);

    DataSetPageView* page_view = &dataSetView.getPageView();

    connect(page_view, SIGNAL(numRowsChanged(int)), rowCountSpinBox, SLOT(setValue(int)));
    connect(rowCountSpinBox, SIGNAL(valueChanged(int)), page_view, SLOT(setNumRows(int)));

    connect(page_view, SIGNAL(numColumnsChanged(int)), columnCountSpinBox, SLOT(setValue(int)));
    connect(columnCountSpinBox, SIGNAL(valueChanged(int)), page_view, SLOT(setNumColumns(int)));

    connect(page_view, SIGNAL(pageOffsetChanged(int)), this, SLOT(updateGUI(int)));
    connect(page_view, SIGNAL(numRowsChanged(int)), this, SLOT(updateGUI(int)));
    connect(page_view, SIGNAL(numColumnsChanged(int)), this, SLOT(updateGUI(int)));
    connect(&dataSetView.getDataSet(), SIGNAL(sizeChanged(int)), this, SLOT(updateGUI(int)));

    connect(prevPageButton, SIGNAL(clicked()), this, SLOT(handlePrevPageButtonClick()));
    connect(nextPageButton, SIGNAL(clicked()), this, SLOT(handleNextPageButtonClick()));
    connect(prevLineButton, SIGNAL(clicked()), this, SLOT(handlePrevLineButtonClick()));
    connect(nextLineButton, SIGNAL(clicked()), this, SLOT(handleNextLineButtonClick()));

    connect(pageOffsetLineEdit, SIGNAL(returnPressed()), this, SLOT(handlePageOffsetInput()));
}
