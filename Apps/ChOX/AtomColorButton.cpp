/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * AtomColorButton.cpp 
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


#include <QColorDialog>
#include <QPalette>
#include <QColor>
#include <QMenu>
#include <QMouseEvent>
#include <QContextMenuEvent>

#include "CDPL/Chem/AtomDictionary.hpp"
#include "CDPL/Vis/QtObjectFactory.hpp"

#include "AtomColorButton.hpp"


using namespace ChOX;


AtomColorButton::AtomColorButton(QWidget* parent, CDPL::Vis::ColorTable& color_tab, const CDPL::Vis::Color& def_color, std::size_t atom_type): 
	QLabel(parent), atomType(atom_type), atomColors(color_tab), defaultColor(def_color)
{
	init();
}

void AtomColorButton::updateGUI()
{	
	QPalette p = palette();

	p.setColor(foregroundRole(), CDPL::Vis::QtObjectFactory::createQColor(atomColors.getValue(atomType, defaultColor)));

	setPalette(p);
}

void AtomColorButton::editColor()
{
	bool ok;
	QColor new_col;

	setFrameStyle(Panel | Sunken);

	new_col.setRgba(QColorDialog::getRgba(CDPL::Vis::QtObjectFactory::createQColor(atomColors.getValue(atomType, defaultColor)).rgba(), 
										  &ok, this));
	setFrameStyle(Panel | Raised);

	if (!ok)
		return;

	atomColors.setEntry(atomType, CDPL::Vis::Color(new_col.redF(), new_col.greenF(), new_col.blueF(), new_col.alphaF()));
	updateGUI();

	emit colorChanged();
}

void AtomColorButton::useDefaultColor()
{
	atomColors.removeEntry(atomType);

	updateGUI();

	emit colorChanged();
}

void AtomColorButton::mousePressEvent(QMouseEvent* e)
{
	QLabel::mousePressEvent(e);

	if (e->button() != Qt::LeftButton)
		return;

	editColor();
}

void AtomColorButton::contextMenuEvent(QContextMenuEvent* e)
{
	e->accept();

	contextMenu->actions().first()->setEnabled(atomColors.containsEntry(atomType));
	contextMenu->popup(e->globalPos());
}

void AtomColorButton::init()
{
	setText(QString::fromStdString(CDPL::Chem::AtomDictionary::getSymbol(atomType)));
	setFrameStyle(Panel | Raised);
	setAlignment(Qt::AlignCenter);

	setToolTip(QString::fromStdString(CDPL::Chem::AtomDictionary::getName(atomType)));

	contextMenu = new QMenu(this);

	contextMenu->addAction(tr("Use Default Color"), this, SLOT(useDefaultColor()));
	contextMenu->addAction(tr("Edit Color..."), this, SLOT(editColor()));

	updateGUI();
}
