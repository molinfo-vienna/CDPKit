/* 
 * SMILESRecordFormatEditWidget.cpp 
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

#include "SMILESRecordFormatEditWidget.hpp"


using namespace ChOX;


SMILESRecordFormatEditWidget::SMILESRecordFormatEditWidget(QWidget* parent, std::string& format):
	QWidget(parent), recordFormat(format)
{
	init();
}

void SMILESRecordFormatEditWidget::updateGUI()
{
	recordFormatComboBox->blockSignals(true);

	if (recordFormat == "S") 
		recordFormatComboBox->setCurrentIndex(0);
	else if (recordFormat == "SN")
		recordFormatComboBox->setCurrentIndex(1);
	else if (recordFormat == "NS")
		recordFormatComboBox->setCurrentIndex(2);
	else
		recordFormatComboBox->setCurrentIndex(0);

	recordFormatComboBox->blockSignals(false);
}

void SMILESRecordFormatEditWidget::handleFormatSelection(int idx)
{
	switch (idx) {

		case 1:
			recordFormat = "SN";
			break;

		case 2:
			recordFormat = "NS";
			break;

		default:
			recordFormat = "S";
	}

	emit recordFormatChanged();
}

void SMILESRecordFormatEditWidget::init()
{
	QHBoxLayout* main_layout = new QHBoxLayout(this);

	main_layout->setMargin(0);

	recordFormatComboBox = new QComboBox(this);

	connect(recordFormatComboBox, SIGNAL(activated(int)), this, SLOT(handleFormatSelection(int)));

	setFocusProxy(recordFormatComboBox);

	recordFormatComboBox->addItem(tr("SMILES"));
	recordFormatComboBox->addItem(tr("SMILES:Name"));
	recordFormatComboBox->addItem(tr("Name:SMILES"));

	main_layout->addWidget(recordFormatComboBox);

	updateGUI();
}
