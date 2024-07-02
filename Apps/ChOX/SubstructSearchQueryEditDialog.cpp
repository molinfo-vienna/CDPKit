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
#include <QTableWidget>
#include <QFrame>
#include <QLineEdit>
#include <QLabel>
#include <QPushButton>

#include "SubstructSearchQueryEditDialog.hpp"
#include "Settings.hpp"


using namespace ChOX;


SubstructSearchQueryEditDialog::SubstructSearchQueryEditDialog(QWidget* parent, Settings& settings, Qt::WindowFlags f):
    QDialog(parent, f), settings(settings)
{
    init();
}

int SubstructSearchQueryEditDialog::exec()
{
    return QDialog::exec();
}

void SubstructSearchQueryEditDialog::acceptChanges()
{
    // TODO
    accept();
}

void SubstructSearchQueryEditDialog::resetChanges()
{
    // TODO
}

void SubstructSearchQueryEditDialog::init()
{
    setWindowTitle(tr("Substructure Query Settings"));

    auto main_layout = new QVBoxLayout(this);
    
    // --------

    auto group_box = new QGroupBox(tr("Query Definition"), this);
    auto v_box_layout = new QVBoxLayout(group_box);
    
    main_layout->addWidget(group_box);

    // +++
    
    auto table_widget = new QTableWidget(group_box);

    v_box_layout->addWidget(table_widget);

    // +++
    
    auto h_box_layout = new QHBoxLayout(group_box);

    v_box_layout->addLayout(h_box_layout);

    auto button = new QPushButton(tr("&Add Pattern"), group_box);

    h_box_layout->addWidget(button);

    // +++
    
    button = new QPushButton(tr("C&lear Patterns"), group_box);

    h_box_layout->addWidget(button);

    // +++
    
    auto frame = new QFrame(group_box);

    frame->setFrameStyle(QFrame::HLine | QFrame::Sunken);

    v_box_layout->addWidget(frame);

    // +++
   
    auto label = new QLabel(tr("Query Expression:"), group_box);

    v_box_layout->addWidget(label);

    // +++

    auto line_edit = new QLineEdit(group_box);

    v_box_layout->addWidget(line_edit);
    
    // --------
    
    h_box_layout = new QHBoxLayout();
    
    main_layout->addLayout(h_box_layout);

    // +++

    button = new QPushButton(tr("&Reset"), this);

    connect(button, SIGNAL(clicked()), this, SLOT(resetChanges()));

    h_box_layout->addStretch();
    h_box_layout->addWidget(button);

    // +++

    button = new QPushButton(tr("&OK"), this);

    button->setDefault(true);
    
    connect(button, SIGNAL(clicked()), this, SLOT(acceptChanges()));

    h_box_layout->addWidget(button);

    // +++

    button = new QPushButton(tr("&Cancel"), this);
    
    connect(button, SIGNAL(clicked()), this, SLOT(reject()));

    h_box_layout->addWidget(button);
}
