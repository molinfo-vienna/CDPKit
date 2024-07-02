/* 
 * SubstructHighlightingPatternsEditWidget.cpp 
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


#include <sstream>
#include <exception>

#include <QListWidget>
#include <QLabel>
#include <QPushButton>
#include <QCheckBox>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QKeyEvent>

#include "CDPL/Chem/BasicMolecule.hpp"
#include "CDPL/Chem/SMARTSMoleculeReader.hpp"
#include "CDPL/Chem/ControlParameterFunctions.hpp"

#include "SubstructHighlightingPatternsEditWidget.hpp"
#include "ControlParameterFunctions.hpp"
#include "Settings.hpp"


using namespace ChOX;


SubstructHighlightingPatternsEditWidget::SubstructHighlightingPatternsEditWidget(QWidget* parent, Settings& settings):
    QWidget(parent), settings(settings), errorIcon(":/Icons/error.svg")
{
    init();
}

void SubstructHighlightingPatternsEditWidget::init()
{
    auto v_layout = new QVBoxLayout(this);
    auto h_layout = new QHBoxLayout();

    v_layout->addLayout(h_layout);
    
    h_layout->addWidget(new QLabel(tr("SMARTS Patterns:"), this));
    h_layout->addStretch();
    
    hltgCheckBox = new QCheckBox(tr("Enable Highlighting"), this);

    h_layout->addWidget(hltgCheckBox);
    
    ptnList = new QListWidget(this);

    ptnList->setIconSize(QSize(16, 16));
    
    v_layout->addWidget(ptnList);

    connect(ptnList, SIGNAL(itemChanged(QListWidgetItem*)), this, SLOT(validatePattern(QListWidgetItem*)));
    
    h_layout = new QHBoxLayout();

    v_layout->addLayout(h_layout);

    auto button = new QPushButton(tr("Add Pattern"), this);

    h_layout->addWidget(button);

    connect(button, SIGNAL(clicked()), this, SLOT(addPattern()));
    
    clearButton = new QPushButton(tr("Clear Patterns"), this);

    connect(clearButton, SIGNAL(clicked()), this, SLOT(clearPatterns()));
    
    h_layout->addWidget(clearButton);
    h_layout->addStretch();

    button = new QPushButton(tr("OK"), this);

    button->setDefault(true);

    h_layout->addWidget(button);

    connect(button, SIGNAL(clicked()), this, SLOT(acceptChanges()));
    
    button = new QPushButton(tr("Cancel"), this);

    h_layout->addWidget(button);

    connect(button, SIGNAL(clicked()), this, SIGNAL(finished()));
}

void SubstructHighlightingPatternsEditWidget::clearPatterns()
{
    ptnList->clear();
    clearButton->setEnabled(false);
}

void SubstructHighlightingPatternsEditWidget::acceptChanges()
{
    QStringList patterns;

    for (int i = 0; i < ptnList->count(); i++)
        patterns << (ptnList->item(i)->checkState() == Qt::Checked ? "X" : "") << ptnList->item(i)->text();

    setSubstructHighlightingPatternsParameter(settings, patterns);
    setSubstructHighlightingEnabledParameter(settings, hltgCheckBox->isChecked());
    
    emit(finished());
}

void SubstructHighlightingPatternsEditWidget::addPattern()
{
    auto item = new QListWidgetItem(ptnList);

    item->setFlags(item->flags() | Qt::ItemIsEditable | Qt::ItemIsUserCheckable);
    item->setCheckState(Qt::Checked);
    
    clearButton->setEnabled(true);

    ptnList->editItem(item);
}

void SubstructHighlightingPatternsEditWidget::validatePattern(QListWidgetItem* item)
{
    if (item->text().isEmpty())
        return;
    
    try {
        using namespace CDPL::Chem;

        BasicMolecule mol;
        std::istringstream iss(item->text().toStdString());
        SMARTSMoleculeReader reader(iss);

        setStrictErrorCheckingParameter(reader, true);
        
        if (!reader.read(mol))
            item->setIcon(errorIcon);
        else
            item->setIcon(QIcon());

        item->setToolTip("");
        
    } catch (const std::exception& e) {
        item->setIcon(errorIcon);
        item->setToolTip(QString(e.what()).replace("SMARTSMoleculeReader: while reading record 0: SMARTSDataReader", "Error"));
    }
}

void SubstructHighlightingPatternsEditWidget::keyPressEvent(QKeyEvent *event)
{
    if ((event->key() == Qt::Key_Delete || event->key() == Qt::Key_Backspace) && ptnList->count() > 0) {
        ptnList->model()->removeRow(ptnList->currentRow());
        clearButton->setEnabled(ptnList->count());
        return;
    }
    
    QWidget::keyPressEvent(event);
}

void SubstructHighlightingPatternsEditWidget::showEvent(QShowEvent* event)
{
    ptnList->clear();

    auto& patterns = getSubstructHighlightingPatternsParameter(settings);
    
    for (int i = 0; i < (patterns.count() / 2); i++) {
        auto item = new QListWidgetItem(patterns[i * 2 + 1], ptnList);

        item->setFlags(item->flags() | Qt::ItemIsEditable | Qt::ItemIsUserCheckable);
        item->setCheckState(patterns[i * 2] == "X" ? Qt::Checked : Qt::Unchecked);
    }
    
    hltgCheckBox->setChecked(getSubstructHighlightingEnabledParameter(settings));
    clearButton->setEnabled(ptnList->count());
            
    QWidget::showEvent(event);
}
