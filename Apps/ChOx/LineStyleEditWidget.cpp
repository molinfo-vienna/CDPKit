/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * LineStyleEditWidget.cpp 
 *
 * This file is part of the Chemical Data Processing Toolkit
 *
 * Copyright (C) 2003-2020 Thomas A. Seidel <thomas.seidel@univie.ac.at>
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

#include "LineStyleEditWidget.hpp"


using namespace ChOx;


LineStyleEditWidget::LineStyleEditWidget(QWidget* parent, CDPL::Vis::Pen::LineStyle& line_style):
	QWidget(parent), lineStyle(line_style)
{
	init();
}

void LineStyleEditWidget::updateGUI()
{
	using namespace CDPL;
	using namespace Vis;

	lineStyleComboBox->blockSignals(true);

	switch (lineStyle) {

		case Pen::NO_LINE:
			lineStyleComboBox->setCurrentIndex(0);
			break;

		case Pen::DASH_LINE:
			lineStyleComboBox->setCurrentIndex(2);
			break;

		case Pen::DOT_LINE:
			lineStyleComboBox->setCurrentIndex(3);
			break;

		case Pen::DASH_DOT_LINE:
			lineStyleComboBox->setCurrentIndex(4);
			break;

		case Pen::DASH_DOT_DOT_LINE:
			lineStyleComboBox->setCurrentIndex(5);
			break;

		default:
			lineStyleComboBox->setCurrentIndex(1);
	}
 
	lineStyleComboBox->blockSignals(false);
}

void LineStyleEditWidget::handleLineStyleSelection(int idx)
{
	using namespace CDPL;
	using namespace Vis;

	switch (idx) {

		case 0:
			lineStyle = Pen::NO_LINE;
			break;

		case 2:
			lineStyle = Pen::DASH_LINE;
			break;

		case 3:
			lineStyle = Pen::DOT_LINE;
			break;

		case 4:
			lineStyle = Pen::DASH_DOT_LINE;
			break;

		case 5:
			lineStyle = Pen::DASH_DOT_DOT_LINE;
			break;

		default:
			lineStyle = Pen::SOLID_LINE;
	}

	emit lineStyleChanged();
}

void LineStyleEditWidget::init()
{
	QBoxLayout* main_layout = new QHBoxLayout(this);

	main_layout->setMargin(0);

	lineStyleComboBox = new QComboBox(this);

	connect(lineStyleComboBox, SIGNAL(activated(int)), this, SLOT(handleLineStyleSelection(int)));

	setFocusProxy(lineStyleComboBox);

	lineStyleComboBox->addItem(tr("No Line"));
	lineStyleComboBox->addItem(tr("Solid"));
	lineStyleComboBox->addItem(tr("Dashed"));
	lineStyleComboBox->addItem(tr("Dot"));
	lineStyleComboBox->addItem(tr("Dash Dot"));
	lineStyleComboBox->addItem(tr("Dash Dot Dot"));

	main_layout->addWidget(lineStyleComboBox);

	updateGUI();
}
