/* 
 * ArrowStyleEditWidget.cpp 
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
#include <QComboBox>

#include "CDPL/Vis/ArrowStyle.hpp"

#include "ArrowStyleEditWidget.hpp"


using namespace ChOX;


ArrowStyleEditWidget::ArrowStyleEditWidget(QWidget* parent, unsigned int& arrow_style):
	QWidget(parent), arrowStyle(arrow_style)
{
	init();
}

void ArrowStyleEditWidget::updateGUI()
{
	using namespace CDPL;
	using namespace Vis;

	arrowStyleComboBox->blockSignals(true);

	switch (arrowStyle) {

		case ArrowStyle::NONE:
			arrowStyleComboBox->setCurrentIndex(0);
			break;

		case ArrowStyle::REACTION_HOLLOW:
			arrowStyleComboBox->setCurrentIndex(2);
			break;

		default:
			arrowStyleComboBox->setCurrentIndex(1);
	}

	arrowStyleComboBox->blockSignals(false);
}

void ArrowStyleEditWidget::handleArrowStyleSelection(int idx)
{
	using namespace CDPL;
	using namespace Vis;

	switch (idx) {

		case 0:
			arrowStyle = ArrowStyle::NONE;
			break;

		case 2:
			arrowStyle = ArrowStyle::REACTION_HOLLOW;
			break;

		default:
			arrowStyle = ArrowStyle::REACTION_SOLID;
	}

	emit arrowStyleChanged();
}

void ArrowStyleEditWidget::init()
{
	QBoxLayout* main_layout = new QHBoxLayout(this);

	main_layout->setMargin(0);

	arrowStyleComboBox = new QComboBox(this);

	connect(arrowStyleComboBox, SIGNAL(activated(int)), this, SLOT(handleArrowStyleSelection(int)));

	setFocusProxy(arrowStyleComboBox);

	arrowStyleComboBox->addItem(tr("No Arrow"));
	arrowStyleComboBox->addItem(tr("Solid"));
	arrowStyleComboBox->addItem(tr("Hollow"));

	main_layout->addWidget(arrowStyleComboBox);

	updateGUI();
}
