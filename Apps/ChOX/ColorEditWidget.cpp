/* 
 * ColorEditWidget.cpp 
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


#include <QFrame>
#include <QColor>
#include <QPushButton>
#include <QBoxLayout>
#include <QColorDialog>

#include "CDPL/Vis/Color.hpp"
#include "CDPL/Vis/QtObjectFactory.hpp"

#include "ColorEditWidget.hpp"


using namespace ChOX;


ColorEditWidget::ColorEditWidget(QWidget* parent, CDPL::Vis::Color& color, bool v_layout):
	QWidget(parent), color(color)
{
	init(v_layout);
}

void ColorEditWidget::updateGUI()
{
	QPalette palette = colorLabel->palette();
	palette.setColor(colorLabel->backgroundRole(), CDPL::Vis::QtObjectFactory::createQColor(color));

	colorLabel->setPalette(palette);
}

void ColorEditWidget::editColor()
{
	bool ok;
	QColor new_col;

	new_col.setRgba(QColorDialog::getRgba(CDPL::Vis::QtObjectFactory::createQColor(color).rgba(), &ok, this));

	if (!ok)
		return;

	color.setRed(new_col.redF());
	color.setGreen(new_col.greenF());
	color.setBlue(new_col.blueF());
	color.setAlpha(new_col.alphaF());

	updateGUI();

	emit colorChanged();
}

void ColorEditWidget::init(bool v_layout)
{
	QBoxLayout* main_layout = new QBoxLayout(v_layout ? QBoxLayout::TopToBottom : QBoxLayout::LeftToRight, this);

	main_layout->setMargin(0);

	colorLabel = new QFrame(this);

	colorLabel->setFrameStyle(QFrame::StyledPanel);
	colorLabel->setMinimumWidth(80);
	colorLabel->setFixedHeight(25);
	colorLabel->setAutoFillBackground(true);

	main_layout->addWidget(colorLabel);
	main_layout->addStretch();

	QPushButton* button = new QPushButton(tr("Change..."), this);

	setFocusProxy(button);

	button->setMinimumHeight(30);

	connect(button, SIGNAL(clicked()), this, SLOT(editColor()));

	main_layout->addWidget(button);

	updateGUI();
}
