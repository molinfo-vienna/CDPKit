/* 
 * SettingsEditDialog.cpp 
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


#include <algorithm>
#include <functional>

#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QListWidget>
#include <QListWidgetItem>
#include <QLabel>
#include <QPushButton>
#include <QStackedWidget>
#include <QScrollArea>

#include "SettingsEditDialog.hpp"
#include "AtomSettingsEditWidget.hpp"
#include "BondSettingsEditWidget.hpp"
#include "ReactionSettingsEditWidget.hpp"
#include "ViewSettingsEditWidget.hpp"
#include "PrintSettingsEditWidget.hpp"
#include "IOSettingsEditWidget.hpp"
#include "Settings.hpp"


using namespace ChOX;


SettingsEditDialog::SettingsEditDialog(QWidget* parent, Settings& settings, Qt::WindowFlags f):
    QDialog(parent, f), settings(settings)
{
    init();
}

int SettingsEditDialog::exec()
{
    std::for_each(categoryEditWidgetList.begin(), categoryEditWidgetList.end(),
                  std::bind(&SettingsEditWidget::reset, std::placeholders::_1));

    applyChangesButton->setEnabled(false);

    return QDialog::exec();
}

void SettingsEditDialog::acceptChanges()
{
    std::for_each(categoryEditWidgetList.begin(), categoryEditWidgetList.end(),
                  std::bind(&SettingsEditWidget::apply, std::placeholders::_1));
    accept();
}

void SettingsEditDialog::resetChanges()
{
    categoryEditWidgetList.at(categoryEditWidgetStack->currentIndex())->reset();    

    applyChangesButton->setEnabled(std::find_if(categoryEditWidgetList.begin(), categoryEditWidgetList.end(),
                                                std::bind(&SettingsEditWidget::haveChangedSettings, std::placeholders::_1)) != 
                                   categoryEditWidgetList.end());
}

void SettingsEditDialog::applyChanges()
{
    applyChangesButton->setEnabled(false);
}

void SettingsEditDialog::setDefaults()
{
    categoryEditWidgetList.at(categoryEditWidgetStack->currentIndex())->setDefaults();    

    applyChangesButton->setEnabled(true);
}

void SettingsEditDialog::handleCategorySelection(QListWidgetItem* item)
{
    item->setSelected(true);

    categoryEditWidgetStack->setCurrentIndex(categoryMenu->row(item));
    categoryDescrLabel->setText(categoryDescriptions.at(categoryMenu->row(item)));
}

void SettingsEditDialog::handleSettingsChange()
{
    applyChangesButton->setEnabled(true);
}

void SettingsEditDialog::addCategoryEditWidget(SettingsEditWidget* widget, const QString& menu_text, const QString& description)
{
    categoryEditWidgetStack->addWidget(widget);

    connect(widget, SIGNAL(settingsChanged()), this, SLOT(handleSettingsChange()));

    new QListWidgetItem(menu_text, categoryMenu);

    connect(applyChangesButton, SIGNAL(clicked()), widget, SLOT(apply()));

    categoryDescriptions.append(description);

    categoryEditWidgetList.push_back(widget);

    categoryMenu->setMinimumWidth(categoryMenu->sizeHint().width());
}

void SettingsEditDialog::init()
{
    setWindowTitle(tr("ChOX - Settings"));

// --------

    QVBoxLayout* main_layout = new QVBoxLayout(this);
    QHBoxLayout* h_box_layout = new QHBoxLayout();
    
    main_layout->addLayout(h_box_layout);

// --------

    categoryMenu = new QListWidget(this);

    QFont font = categoryMenu->font();

    font.setBold(true);
    font.setPointSize(font.pointSize() + 1);

    categoryMenu->setFont(font);
    categoryMenu->setSelectionMode(QAbstractItemView::SingleSelection);

    connect(categoryMenu, SIGNAL(currentItemChanged(QListWidgetItem*, QListWidgetItem*)), 
            this, SLOT(handleCategorySelection(QListWidgetItem*))); 

    h_box_layout->addWidget(categoryMenu);

// +++

    QVBoxLayout* v_box_layout = new QVBoxLayout();

    h_box_layout->addLayout(v_box_layout);
    h_box_layout->setStretchFactor(v_box_layout, 1);

// --------

    categoryDescrLabel = new QLabel(this);
    
    font = categoryDescrLabel->font();

    font.setBold(true);

    categoryDescrLabel->setFont(font);

    v_box_layout->addWidget(categoryDescrLabel);

// +++

    QFrame* frame = new QFrame(this);

    frame->setFrameStyle(QFrame::HLine | QFrame::Sunken);

    v_box_layout->addWidget(frame);

// +++

    QScrollArea* scroll_area = new QScrollArea(this);

    scroll_area->setWidgetResizable(true);
    scroll_area->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    scroll_area->setFrameStyle(QFrame::StyledPanel);

    categoryEditWidgetStack = new QStackedWidget(this);

    v_box_layout->addWidget(scroll_area, 1);

// +++

    frame = new QFrame(this);

    frame->setFrameStyle(QFrame::HLine | QFrame::Sunken);

    main_layout->addWidget(frame);

// --------

    h_box_layout = new QHBoxLayout();
    
    main_layout->addLayout(h_box_layout);

    h_box_layout->setSpacing(5);

// +++

    QPushButton* button = new QPushButton(tr("&Defaults"), this);

    connect(button, SIGNAL(clicked()), this, SLOT(setDefaults()));
    
    h_box_layout->addWidget(button);
    h_box_layout->addStretch();
    /*
// +++

    button = new QPushButton(tr("Sa&ve"), this);

    connect(button, SIGNAL(clicked()), &settings, SLOT(save()));

    h_box_layout->addWidget(button);
    */
// +++

    button = new QPushButton(tr("&Reset"), this);

    connect(button, SIGNAL(clicked()), this, SLOT(resetChanges()));
    
    h_box_layout->addWidget(button);

// +++

    button = new QPushButton(tr("&OK"), this);

    button->setDefault(true);
    
    connect(button, SIGNAL(clicked()), this, SLOT(acceptChanges()));

    h_box_layout->addWidget(button);

// +++

    applyChangesButton = new QPushButton(tr("&Apply"), this);

    connect(applyChangesButton, SIGNAL(clicked()), this, SLOT(applyChanges()));

    h_box_layout->addWidget(applyChangesButton);

// +++

    button = new QPushButton(tr("&Cancel"), this);
    
    connect(button, SIGNAL(clicked()), this, SLOT(reject()));

    h_box_layout->addWidget(button);

// ------------

    addCategoryEditWidget(new ViewSettingsEditWidget(this, settings), tr("View"), tr("General View Settings"));
    addCategoryEditWidget(new AtomSettingsEditWidget(this, settings), tr("Atoms"), tr("Atom Appearance Settings"));
    addCategoryEditWidget(new BondSettingsEditWidget(this, settings), tr("Bonds"), tr("Bond Appearance Settings"));
    addCategoryEditWidget(new ReactionSettingsEditWidget(this, settings), tr("Reactions"), tr("Reaction Appearance Settings"));
    addCategoryEditWidget(new PrintSettingsEditWidget(this, settings), tr("Printing"), tr("Printer Output Settings"));
    addCategoryEditWidget(new IOSettingsEditWidget(this, settings), tr("File I/O"), tr("File I/O Settings"));

// ------------

    handleCategorySelection(categoryMenu->item(0));

    scroll_area->setWidget(categoryEditWidgetStack);
    scroll_area->setMinimumWidth(categoryEditWidgetStack->width() + 20);
    scroll_area->setMinimumHeight(600);
}
