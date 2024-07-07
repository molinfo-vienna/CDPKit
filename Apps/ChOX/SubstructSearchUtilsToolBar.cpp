/* 
 * SubstructSearchUtilsToolBar.cpp 
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


#include <QMenu>
#include <QToolButton>
#include <QAction>

#include "SubstructSearchUtilsToolBar.hpp"
#include "SubstructHighlightingPatternsEditAction.hpp"
#include "SubstructSearchQueryEditDialog.hpp"


using namespace ChOX;


SubstructSearchUtilsToolBar::SubstructSearchUtilsToolBar(QWidget* parent, Settings& settings):
    QToolBar(parent), settings(settings), subSearchQueryDialog(nullptr)
{
    init();
}

void SubstructSearchUtilsToolBar::init()
{
    setObjectName("substructSearchUtilsToolBar");
    setWindowTitle(tr("Substructure Search Utilities Toolbar"));

    //------
    
    auto button = new QToolButton(this);
    
    button->setIcon(QIcon(":/Icons/sshighlighting.svg"));
    button->setToolTip(tr("Edit Substructure Highlighting Patterns"));
    
    auto menu = new QMenu(this);
    QAction* action = new SubstructHighlightingPatternsEditAction(menu, settings);

    menu->addAction(action);
    
    connect(action, SIGNAL(triggered()), menu, SLOT(close()));

    button->setMenu(menu);
    button->setPopupMode(QToolButton::InstantPopup);

    addWidget(button);

    //------

    menu = new QMenu(this);
    action = new QAction(tr("Edit &Query..."), menu);

    menu->addAction(action);

    connect(action, SIGNAL(triggered()), this, SLOT(editSubSearchQuery()));

    action = new QAction(tr("&Search..."), menu);

    action->setEnabled(false); // TODO
    
    menu->addAction(action);

    connect(action, SIGNAL(triggered()), this, SLOT(performSubSearch()));

    //------
    
    button = new QToolButton(this);
    
    button->setIcon(QIcon(":/Icons/subsearch.svg"));
    button->setToolTip(tr("Perform Substructure Search"));
    button->setMenu(menu);
    button->setPopupMode(QToolButton::InstantPopup);

    addWidget(button);
}

void SubstructSearchUtilsToolBar::editSubSearchQuery()
{
    if (!subSearchQueryDialog)
        subSearchQueryDialog = new SubstructSearchQueryEditDialog(this, settings);

    subSearchQueryDialog->exec();
}

void SubstructSearchUtilsToolBar::performSubSearch()
{
    // TODO
}
