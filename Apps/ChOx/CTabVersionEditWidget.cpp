/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * CTabVersionEditWidget.cpp 
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

#include "CDPL/Chem/MDLDataFormatVersion.hpp"

#include "CTabVersionEditWidget.hpp"


using namespace ChOx;


CTabVersionEditWidget::CTabVersionEditWidget(QWidget* parent, unsigned int& ctab_version):
	QWidget(parent), ctabVersion(ctab_version)
{
	init();
}

void CTabVersionEditWidget::updateGUI()
{
	ctabVersionComboBox->blockSignals(true);

	switch (ctabVersion) {

		case CDPL::Chem::MDLDataFormatVersion::V2000:
			ctabVersionComboBox->setCurrentIndex(1);
			break;

		case CDPL::Chem::MDLDataFormatVersion::V3000:
			ctabVersionComboBox->setCurrentIndex(2);
			break;

		default:
			ctabVersionComboBox->setCurrentIndex(0);
	}

	ctabVersionComboBox->blockSignals(false);
}

void CTabVersionEditWidget::handleVersionSelection(int idx)
{
	switch (idx) {

		case 1:
			ctabVersion = CDPL::Chem::MDLDataFormatVersion::V2000;
			break;

		case 2:
			ctabVersion = CDPL::Chem::MDLDataFormatVersion::V3000;
			break;

		default:
			ctabVersion = 0;
	}

	emit versionChanged();
}

void CTabVersionEditWidget::init()
{
	QBoxLayout* main_layout = new QHBoxLayout(this);

	main_layout->setMargin(0);

	ctabVersionComboBox = new QComboBox(this);

	connect(ctabVersionComboBox, SIGNAL(activated(int)), this, SLOT(handleVersionSelection(int)));

	setFocusProxy(ctabVersionComboBox);

	ctabVersionComboBox->addItem(tr("Auto Select"));
	ctabVersionComboBox->addItem(tr("V2000"));
	ctabVersionComboBox->addItem(tr("V3000"));

	main_layout->addWidget(ctabVersionComboBox);

	updateGUI();
}
