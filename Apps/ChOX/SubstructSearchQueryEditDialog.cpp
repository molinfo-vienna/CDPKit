/* 
 * SubstructSearchQueryEditDialog.cpp 
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


#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGroupBox>
#include <QFrame>
#include <QLineEdit>
#include <QLabel>
#include <QPushButton>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QHeaderView>

#include "CDPL/Chem/MultiSubstructureSearch.hpp"

#include "SubstructSearchQueryEditDialog.hpp"
#include "ControlParameterFunctions.hpp"
#include "Settings.hpp"
#include "Utilities.hpp"


using namespace ChOX;


SubstructSearchQueryEditDialog::SubstructSearchQueryEditDialog(QWidget* parent, Settings& settings, Qt::WindowFlags f):
    QDialog(parent, f), settings(settings)
{
    init();
}

int SubstructSearchQueryEditDialog::exec()
{
    resetChanges();
    
    return QDialog::exec();
}

void SubstructSearchQueryEditDialog::init()
{
    setWindowTitle(tr("Substructure Query Settings"));

    auto main_layout = new QVBoxLayout(this);
    
    // --------

    auto group_box = new QGroupBox(tr("Query Definition"), this);
    
    main_layout->addWidget(group_box);

    // +++

    auto v_box_layout = new QVBoxLayout();

    group_box->setLayout(v_box_layout);
    
    substructList = new QTableWidget(group_box);

    substructList->setColumnCount(1);
    substructList->horizontalHeader()->setStretchLastSection(true);
    substructList->setHorizontalHeaderItem(0, new QTableWidgetItem(tr("Substructure SMARTS")));
    
    v_box_layout->addWidget(substructList);

    connect(substructList, SIGNAL(itemChanged(QTableWidgetItem*)), this, SLOT(validatePattern(QTableWidgetItem*)));
   
    // +++
    
    auto h_box_layout = new QHBoxLayout(group_box);

    v_box_layout->addLayout(h_box_layout);

    auto button = new QPushButton(tr("&Add"), group_box);

    h_box_layout->addStretch();
    h_box_layout->addWidget(button);

    connect(button, SIGNAL(clicked()), this, SLOT(addSubstructure()));
   
    // +++
    
    button = new QPushButton(tr("R&emove"), group_box);

    h_box_layout->addWidget(button);

    connect(button, SIGNAL(clicked()), this, SLOT(removeSubstructure()));
  
    // +++
    
    button = new QPushButton(tr("C&lear"), group_box);

    h_box_layout->addWidget(button);
    h_box_layout->addStretch();

    connect(button, SIGNAL(clicked()), this, SLOT(clearSubstructures()));
    connect(button, &QPushButton::clicked, button, [=]() { button->setDisabled(true); });
    connect(this, SIGNAL(haveData(bool)), button, SLOT(setEnabled(bool)));
 
    // +++
    
    auto frame = new QFrame(group_box);

    frame->setFrameStyle(QFrame::HLine | QFrame::Sunken);

    v_box_layout->addWidget(frame);

    // +++
   
    auto label = new QLabel(tr("Query Expression:"), group_box);

    v_box_layout->addWidget(label);

    // +++

    exprLineEdit = new QLineEdit(group_box);

    exprLineEdit->setClearButtonEnabled(true);
    
    v_box_layout->addWidget(exprLineEdit);

    connect(exprLineEdit, SIGNAL(editingFinished()), this, SLOT(validateExpression()));

    exprTextColor = exprLineEdit->palette().color(QPalette::Active, exprLineEdit->foregroundRole());
    
    // --------
    
    h_box_layout = new QHBoxLayout();
    
    main_layout->addLayout(h_box_layout);

    // +++

    button = new QPushButton(tr("&Reset"), this);

    h_box_layout->addStretch();
    h_box_layout->addWidget(button);

    connect(button, SIGNAL(clicked()), this, SLOT(resetChanges()));

    // +++

    button = new QPushButton(tr("&OK"), this);

    button->setDefault(true);
  
    h_box_layout->addWidget(button);
  
    connect(button, SIGNAL(clicked()), this, SLOT(acceptChanges()));

    // +++

    button = new QPushButton(tr("&Cancel"), this);
  
    h_box_layout->addWidget(button);
      
    connect(button, SIGNAL(clicked()), this, SLOT(reject()));

    // +++

    setMinimumWidth(450);
    setMinimumHeight(450);
}

void SubstructSearchQueryEditDialog::acceptChanges()
{
    QStringList query;

    for (int i = 0; i < substructList->rowCount(); i++)
        query << substructList->item(i, 0)->text();

    query << exprLineEdit->text();
   
    setSubstructSearchQueryParameter(settings, query);
    accept();
}

void SubstructSearchQueryEditDialog::resetChanges()
{
    substructList->setRowCount(0);
    
    auto& query = getSubstructSearchQueryParameter(settings);
    
    for (int i = 0; i < int(query.count()) - 1; i++) {
        auto item = new QTableWidgetItem(query[i]);

        item->setFlags(item->flags() | Qt::ItemIsEditable | Qt::ItemIsUserCheckable);
        
        cellTextBrush = item->foreground();

        substructList->setRowCount(substructList->rowCount() + 1);
        substructList->setItem(substructList->rowCount() - 1, 0, item);
    }

    if (query.count() > 0)
        exprLineEdit->setText(query.back());
    else
        exprLineEdit->setText("");
    
    emit(haveData(substructList->rowCount() > 0));
}

void SubstructSearchQueryEditDialog::addSubstructure()
{
    substructList->setRowCount(substructList->rowCount() + 1);
    
    auto item = new QTableWidgetItem();

    item->setFlags(item->flags() | Qt::ItemIsEditable | Qt::ItemIsUserCheckable);

    cellTextBrush = item->foreground();
    
    emit(haveData(true));

    substructList->setItem(substructList->rowCount() - 1, 0, item);
    substructList->editItem(item);

    validateExpression();
}

void SubstructSearchQueryEditDialog::clearSubstructures()
{
    substructList->setRowCount(0);

    emit(haveData(false));
}

void SubstructSearchQueryEditDialog::validatePattern(QTableWidgetItem* item)
{
    QString error = validateSMARTS(item->text());
   
    if (!error.isEmpty()) {
        item->setForeground(Qt::red);
        item->setToolTip(error);

    } else {
        item->setForeground(cellTextBrush);
        item->setToolTip("");
    }
}

void SubstructSearchQueryEditDialog::validateExpression()
{
    std::string error = CDPL::Chem::MultiSubstructureSearch().validate(exprLineEdit->text().toStdString(), substructList->rowCount());
    auto palette = exprLineEdit->palette();
    
    if (!error.empty()) {
        palette.setColor(QPalette::Active, exprLineEdit->foregroundRole(), Qt::red);
        exprLineEdit->setToolTip(tr(error.c_str()));

    } else {
        palette.setColor(QPalette::Active, exprLineEdit->foregroundRole(), exprTextColor);
        exprLineEdit->setToolTip("");
    }

    exprLineEdit->setPalette(palette);
}

void SubstructSearchQueryEditDialog::removeSubstructure()
{
    substructList->removeRow(substructList->currentRow());

    validateExpression();
    
    emit(haveData(substructList->rowCount() > 0));
}
