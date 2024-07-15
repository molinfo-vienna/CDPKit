/* 
 * SubstructSearchResultDialog.cpp 
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
#include <QRadioButton>
#include <QGroupBox>
#include <QButtonGroup>

#include "SubstructSearchResultDialog.hpp"


using namespace ChOX;


SubstructSearchResultDialog::SubstructSearchResultDialog(QWidget* parent, Qt::WindowFlags f):
    QDialog(parent, f), haveMatchesIcon(":/Icons/success.svg"), noMatchesIcon(":/Icons/nosuccess.svg")
{
    init();
}

void SubstructSearchResultDialog::setup(int num_matches)
{
    if (num_matches == 0) {
        infoIconLabel->setPixmap(noMatchesIcon);
        infoTextLabel->setText(tr("<b>No</b> matching Records found!"));
        return;
    }

    infoIconLabel->setPixmap(haveMatchesIcon);
    infoTextLabel->setText("<b>" + QString::number(num_matches) + "</b>" +
                           (num_matches == 1 ? tr(" Matching Record found") : tr(" Matching Records found")));
}

SubstructSearchResultDialog::ViewAction SubstructSearchResultDialog::getViewAction() const
{
    int btn_id = viewActionGroup->checkedId();

    if (btn_id == -1)
        return NONE;
    
    return ViewAction(btn_id);
}

void SubstructSearchResultDialog::init()
{
    setWindowTitle(tr("ChOX - Substructure Search Result"));
    setMinimumWidth(450);
    
    auto main_layout = new QVBoxLayout(this);

    // --------

    auto frame = new QFrame();

    main_layout->addWidget(frame);
    
    frame->setFrameStyle(QFrame::StyledPanel | QFrame::Plain);

    auto h_box_layout = new QHBoxLayout(frame);
    
    infoIconLabel = new QLabel(this);
    infoTextLabel = new QLabel(this);

    h_box_layout->addWidget(infoIconLabel, 0);
    h_box_layout->addWidget(infoTextLabel, 1);
    
    // --------

    auto group_box = new QGroupBox(tr("Action"), this);
    auto v_box_layout = new QVBoxLayout();

    main_layout->addWidget(group_box);
    group_box->setLayout(v_box_layout);

    viewActionGroup = new QButtonGroup(this);
    
    // +++

    auto radio_btn = new QRadioButton(tr("&None"), group_box);

    radio_btn->setChecked(true);
    
    viewActionGroup->addButton(radio_btn, NONE);
    v_box_layout->addWidget(radio_btn);
    
    radio_btn = new QRadioButton(tr("&Select Matches"), group_box);

    viewActionGroup->addButton(radio_btn, SEL_MATCHING);
    v_box_layout->addWidget(radio_btn);
    
    radio_btn = new QRadioButton(tr("Select Non-&Matches"), group_box);

    viewActionGroup->addButton(radio_btn, SEL_NON_MATCHING);
    v_box_layout->addWidget(radio_btn);

    radio_btn = new QRadioButton(tr("&Delete Matches"), group_box);

    viewActionGroup->addButton(radio_btn, DEL_MATCHING);
    v_box_layout->addWidget(radio_btn);
    
    radio_btn = new QRadioButton(tr("D&elete Non-Matches"), group_box);

    viewActionGroup->addButton(radio_btn, DEL_NON_MATCHING);
    v_box_layout->addWidget(radio_btn);

    // +++

    h_box_layout = new QHBoxLayout();

    v_box_layout->addLayout(h_box_layout);
    
    auto button = new QPushButton(tr("S&ave Matches As..."), group_box);

    connect(button, SIGNAL(clicked()), this, SIGNAL(saveMatchingRequested()));
    
    h_box_layout->addWidget(button);
    
    button = new QPushButton(tr("Sa&ve Non-Matches As..."), group_box);

    connect(button, SIGNAL(clicked()), this, SIGNAL(saveNonMatchingRequested()));
    
    h_box_layout->addWidget(button);
    h_box_layout->addStretch();
    
    // --------
    
    h_box_layout = new QHBoxLayout();

    main_layout->addLayout(h_box_layout);

    // +++

    button = new QPushButton(tr("&OK"), this);

    button->setDefault(true);

    connect(button, SIGNAL(clicked()), this, SLOT(accept()));

    h_box_layout->addStretch();
    h_box_layout->addWidget(button);

    // +++

    button = new QPushButton(tr("&Cancel"), this);

    connect(button, SIGNAL(clicked()), this, SLOT(reject()));

    h_box_layout->addWidget(button);
}
