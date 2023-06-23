/* 
 * RecordSeparatorEditWidget.cpp 
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

#include "RecordSeparatorEditWidget.hpp"


using namespace ChOX;


RecordSeparatorEditWidget::RecordSeparatorEditWidget(QWidget* parent, std::string& separator):
	QWidget(parent), recordSeparator(separator)
{
	init();
}

void RecordSeparatorEditWidget::updateGUI()
{
	recordSeparatorComboBox->blockSignals(true);

	if (recordSeparator.empty()) 
		recordSeparatorComboBox->setCurrentIndex(0);
	else if (recordSeparator == " ")
		recordSeparatorComboBox->setCurrentIndex(1);
	else
		recordSeparatorComboBox->setCurrentIndex(2);

	recordSeparatorComboBox->blockSignals(false);
}

void RecordSeparatorEditWidget::handleSeparatorSelection(int idx)
{
	switch (idx) {

		case 1:
			recordSeparator = " ";
			break;

		case 2:
			recordSeparator = "\n";
			break;

		default:
			recordSeparator = "";
	}

	emit recordSeparatorChanged();
}

void RecordSeparatorEditWidget::init()
{
	QBoxLayout* main_layout = new QHBoxLayout(this);

	main_layout->setMargin(0);

	recordSeparatorComboBox = new QComboBox(this);

	connect(recordSeparatorComboBox, SIGNAL(activated(int)), this, SLOT(handleSeparatorSelection(int)));

	setFocusProxy(recordSeparatorComboBox);

	recordSeparatorComboBox->addItem(tr("None"));
	recordSeparatorComboBox->addItem(tr("Space"));
	recordSeparatorComboBox->addItem(tr("Linebreak"));

	main_layout->addWidget(recordSeparatorComboBox);

	updateGUI();
}
