/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * AboutDialog.cpp 
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
#include <QLabel>
#include <QPushButton>

#include "AboutDialog.hpp"


namespace
{

	const char* ABOUT_TEXT =
	"<h2 align=center><b>- ChOX -</b></h2>"
	"<h3 align=center><b><u>Ch</u>emical <u>O</u>bject E<u>x</u>plorer</b></h2>"
	"<p align=center><i>An Application for the Visualization and Manipulation of Chemical Datasets</i></p>"
	"<p align=center>&copy; Thomas Seidel (thomas.seidel@univie.ac.at)</p>"
	"<p align=justify>This program is free software; you can redistribute it and/or modify it under "
	"the terms<br>of the GNU Lesser General Public License as published by the Free Software "
	"Foundation;<br>either version 2 of the License, or (at your option) any later version.</p>"
	"<p align=justify>This program is distributed in the hope that it will be useful, but WITHOUT "
	"ANY WARRANTY;<br>without even the implied warranty of MERCHANTABILITY or FITNESS FOR A "
	"PARTICULAR<br>PURPOSE. See the GNU Lesser General Public License for more details.</p>";
}


using namespace ChOX;


AboutDialog::AboutDialog(QWidget* parent, Qt::WindowFlags f):
	QDialog(parent, f)
{
	init();
}

void AboutDialog::init()
{
	setAttribute(Qt::WA_DeleteOnClose);
	setWindowTitle(tr("ChOX - About"));

// -------

	QBoxLayout* main_layout = new QVBoxLayout(this);

// -------

	QBoxLayout* h_box_layout = new QHBoxLayout();

	main_layout->addLayout(h_box_layout);

	h_box_layout->addSpacing(30);

	h_box_layout->addWidget(new QLabel(tr(ABOUT_TEXT), this));

	h_box_layout->addSpacing(30);

// -------

	h_box_layout = new QHBoxLayout();

	main_layout->addLayout(h_box_layout);

	h_box_layout->addStretch();

// +++

	QPushButton* ok_button = new QPushButton(tr("OK"), this);

	ok_button->setDefault(true);

	connect(ok_button, SIGNAL(clicked()), this, SLOT(accept()));

	h_box_layout->addWidget(ok_button);

	h_box_layout->addStretch();

}

