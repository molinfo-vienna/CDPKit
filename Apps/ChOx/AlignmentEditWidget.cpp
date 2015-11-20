/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * AlignmentEditWidget.cpp 
 *
 * This file is part of the Chemical Data Processing Toolkit
 *
 * Copyright (C) 2003-2010 Thomas A. Seidel <thomas.seidel@univie.ac.at>
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

#include "CDPL/Vis/Alignment.hpp"

#include "AlignmentEditWidget.hpp"


using namespace ChOx;


AlignmentEditWidget::AlignmentEditWidget(QWidget* parent, unsigned int& alignment, bool hor_dir, bool allow_center):
	QWidget(parent), alignment(alignment), horDirection(hor_dir), allowCenter(allow_center)
{
	init();
}

void AlignmentEditWidget::updateGUI()
{
	using namespace CDPL;
	using namespace Vis;

	alignmentComboBox->blockSignals(true);

	if (horDirection) {
		switch (alignment & Alignment::H_ALIGNMENT_MASK) {

			case Alignment::LEFT:
				alignmentComboBox->setCurrentIndex(0);
				break;

			case Alignment::RIGHT:
				alignmentComboBox->setCurrentIndex(1);
				break;

			default:
				alignmentComboBox->setCurrentIndex(allowCenter ? 2 : 0);
		}

	} else {
		switch (alignment & Alignment::V_ALIGNMENT_MASK) {

			case Alignment::TOP:
				alignmentComboBox->setCurrentIndex(0);
				break;

			case Alignment::BOTTOM:
				alignmentComboBox->setCurrentIndex(1);
				break;

			default:
				alignmentComboBox->setCurrentIndex(allowCenter ? 2 : 0);
		}
	}

	alignmentComboBox->blockSignals(false);
}

void AlignmentEditWidget::handleAlignmentSelection(int idx)
{
	using namespace CDPL;
	using namespace Vis;

	if (horDirection) {
		alignment &= ~Alignment::H_ALIGNMENT_MASK;

		switch (idx) {

			case 0:
				alignment |= Alignment::LEFT;
				break;

			case 1:
				alignment |= Alignment::RIGHT;
				break;

			default:
				alignment |= Alignment::H_CENTER;
		}

	} else {
		alignment &= ~Alignment::V_ALIGNMENT_MASK;

		switch (idx) {

			case 0:
				alignment |= Alignment::TOP;
				break;

			case 1:
				alignment |= Alignment::BOTTOM;
				break;

			default:
				alignment |= Alignment::V_CENTER;
		}
	}

	emit alignmentChanged();
}

void AlignmentEditWidget::init()
{
	QBoxLayout* main_layout = new QHBoxLayout(this);

	main_layout->setMargin(0);

	alignmentComboBox = new QComboBox(this);

	connect(alignmentComboBox, SIGNAL(activated(int)), this, SLOT(handleAlignmentSelection(int)));

	setFocusProxy(alignmentComboBox);

	if (horDirection) {
		alignmentComboBox->addItem(tr("Left"));
		alignmentComboBox->addItem(tr("Right"));

	} else {
		alignmentComboBox->addItem(tr("Top"));
		alignmentComboBox->addItem(tr("Bottom"));
	}

	if (allowCenter)
		alignmentComboBox->addItem(tr("Center"));

	main_layout->addWidget(alignmentComboBox);

	updateGUI();
}
