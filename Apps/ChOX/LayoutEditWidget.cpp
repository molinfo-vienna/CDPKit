/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * LayoutEditWidget.cpp 
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
#include <QVBoxLayout>
#include <QComboBox>
#include <QLabel>

#include "CDPL/Vis/LayoutStyle.hpp"
#include "CDPL/Vis/LayoutDirection.hpp"

#include "LayoutEditWidget.hpp"


using namespace ChOX;


LayoutEditWidget::LayoutEditWidget(QWidget* parent, unsigned int& layout_style, unsigned int& layout_dir):
	QWidget(parent), layoutStyle(layout_style), layoutDirection(layout_dir)
{
	init();
}

void LayoutEditWidget::updateGUI()
{
	using namespace CDPL;
	using namespace Vis;

	layoutStyleComboBox->blockSignals(true);
	layoutDirComboBox->blockSignals(true);

	if (layoutStyle == LayoutStyle::PACKED) {
		layoutStyleComboBox->setCurrentIndex(0);
		layoutDirComboBox->setEnabled(false);

	} else {
		layoutStyleComboBox->setCurrentIndex(1);

		layoutDirComboBox->setEnabled(true);
		layoutDirComboBox->setCurrentIndex(layoutDirection == LayoutDirection::HORIZONTAL ? 0 : 1);
	}

	layoutStyleComboBox->blockSignals(false);
	layoutDirComboBox->blockSignals(false);
}

void LayoutEditWidget::handleStyleChange(int idx)
{
	using namespace CDPL;
	using namespace Vis;

	if (idx == 0) {
		layoutStyle = LayoutStyle::PACKED;
		layoutDirComboBox->setEnabled(false);

	} else {
		layoutStyle = LayoutStyle::LINEAR;
		layoutDirComboBox->setEnabled(true);
	}

	emit layoutChanged();
}

void LayoutEditWidget::handleDirectionChange(int idx)
{
	using namespace CDPL;
	using namespace Vis;

	layoutDirection = (idx == 0 ? LayoutDirection::HORIZONTAL : LayoutDirection::VERTICAL);

	emit layoutChanged();
}

void LayoutEditWidget::init()
{
	QBoxLayout* main_layout = new QHBoxLayout(this);

	main_layout->setMargin(0);

	QBoxLayout* v_box_layout = new QVBoxLayout();

	main_layout->addLayout(v_box_layout);

	layoutStyleComboBox = new QComboBox(this);

	connect(layoutStyleComboBox, SIGNAL(activated(int)), this, SLOT(handleStyleChange(int)));

	setFocusProxy(layoutStyleComboBox);

	layoutStyleComboBox->addItem(tr("Packed"));
	layoutStyleComboBox->addItem(tr("Linear"));

	QLabel* label = new QLabel(tr("Style:"), this);

	v_box_layout->addWidget(label);

	label->setBuddy(layoutStyleComboBox);

	v_box_layout->addWidget(layoutStyleComboBox);

	v_box_layout = new QVBoxLayout();

	main_layout->addLayout(v_box_layout);

	layoutDirComboBox = new QComboBox(this);

	connect(layoutDirComboBox, SIGNAL(activated(int)), this, SLOT(handleDirectionChange(int)));

	layoutDirComboBox->addItem(tr("Horizontal"));
	layoutDirComboBox->addItem(tr("Vertical"));

	label = new QLabel(tr("Direction:"), this);

	label->setBuddy(layoutDirComboBox);

	v_box_layout->addWidget(label);
	v_box_layout->addWidget(layoutDirComboBox);

	updateGUI();
}
