/* 
 * SubstructSearchHitsActionDialog.cpp 
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
#include <QLabel>
#include <QPushButton>

#include "SubstructSearchHitsActionDialog.hpp"


using namespace ChOX;


SubstructSearchHitsActionDialog::SubstructSearchHitsActionDialog(QWidget* parent, Qt::WindowFlags f):
    QDialog(parent, f)
{
    init();
}

void SubstructSearchHitsActionDialog::init()
{
    setAttribute(Qt::WA_DeleteOnClose);
    setWindowTitle(tr("ChOX - Substructure Search Result"));

    auto main_layout = new QVBoxLayout(this);
    auto h_box_layout = new QHBoxLayout();

    main_layout->addLayout(h_box_layout);

// +++

    auto button = new QPushButton(tr("Close"), this);

    button->setDefault(true);

    connect(button, SIGNAL(clicked()), this, SLOT(accept()));

    h_box_layout->addWidget(button);

    h_box_layout->addStretch();

}
