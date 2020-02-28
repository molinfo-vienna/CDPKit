/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * FontChooserDialog.cpp 
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


#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGroupBox>
#include <QPushButton>

#include "FontChooserDialog.hpp"
#include "FontChooserWidget.hpp"


using namespace ChOx;


FontChooserDialog::FontChooserDialog(QWidget* parent, CDPL::Vis::Font& font, CDPL::Vis::SizeSpecification& size_spec, 
									 const CDPL::Vis::SizeSpecification* parent_size_spec,
									 bool size_type_editable, bool policy_editable, 
									 Qt::WindowFlags f):
	QDialog(parent, f), font(font), tmpFont(font), sizeSpec(size_spec), 
	tmpSizeSpec(size_spec), parentSizeSpec(parent_size_spec)
{
	init(size_type_editable, policy_editable);
}

void FontChooserDialog::applyChanges()
{
	font = tmpFont;
	sizeSpec = tmpSizeSpec;

	accept();
}

void FontChooserDialog::init(bool size_type_editable, bool policy_editable)
{
	setWindowTitle(tr("ChOx - Choose Font"));

// ---------

	QBoxLayout* main_layout = new QVBoxLayout(this);

// ---------

	QGroupBox* group_box = new QGroupBox(tr("Select Font"), this);
	QVBoxLayout* v_box_layout = new QVBoxLayout(group_box);
	
	v_box_layout->addWidget(new FontChooserWidget(group_box, tmpFont, tmpSizeSpec, parentSizeSpec, size_type_editable, policy_editable));

	main_layout->addWidget(group_box);

// ---------

	QBoxLayout* h_box_layout = new QHBoxLayout();

	main_layout->addLayout(h_box_layout);

	h_box_layout->addStretch();

// +++

	QPushButton* button = new QPushButton(tr("&OK"), this);

	button->setDefault(true);

	connect(button, SIGNAL(clicked()), this, SLOT(applyChanges()));

	h_box_layout->addWidget(button);

	button = new QPushButton(tr("&Cancel"), this);

	connect(button, SIGNAL(clicked()), this, SLOT(reject()));

	h_box_layout->addWidget(button);
}

