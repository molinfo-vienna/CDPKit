/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * DataSetView.cpp 
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


#include <QWheelEvent>
#include <QPainter>
#include <QShortcut>
#include <QScrollBar>
#include <QHBoxLayout>

#include "DataSetView.hpp"
#include "DataSetPageView.hpp"
#include "DataSet.hpp"


using namespace ChOx;


DataSetView::DataSetView(QWidget* parent, Settings& settings, DataSet& data_set): 
	QFrame(parent), dataSet(data_set), settings(settings)
{
	init();
}

DataSetPageView& DataSetView::getPageView() const
{
	return *pageView;
}

DataSet& DataSetView::getDataSet() const
{
	return dataSet;
}

void DataSetView::wheelEvent(QWheelEvent* e)
{
	e->accept();

	if (e->delta() > 0)
		pageView->toPrevRow();
	else
		pageView->toNextRow();
}

void DataSetView::init()
{
	QHBoxLayout* main_layout = new QHBoxLayout();

	setLayout(main_layout);

	main_layout->setSpacing(0);
	main_layout->setMargin(2);

	scrollBar = new QScrollBar(this);

	scrollBar->hide();
	scrollBar->setPageStep(1);
	scrollBar->setSingleStep(1);
	scrollBar->setMinimum(0);
	scrollBar->setMaximum(0);

	pageView = new DataSetPageView(this, settings, dataSet);

	main_layout->addWidget(pageView);
	main_layout->addWidget(scrollBar);

	connect(scrollBar, SIGNAL(valueChanged(int)), pageView, SLOT(setPageOffset(int)));

	connect(&dataSet, SIGNAL(sizeChanged(int)), this, SLOT(adjustScrollBar(int)));
	connect(pageView, SIGNAL(numRowsChanged(int)), this, SLOT(adjustScrollBar(int)));
	connect(pageView, SIGNAL(numColumnsChanged(int)), this, SLOT(adjustScrollBar(int)));
	connect(pageView, SIGNAL(pageOffsetChanged(int)), this, SLOT(adjustScrollBar(int)));

	QShortcut* shortcut = new QShortcut(Qt::Key_PageDown, this);
	shortcut->setContext(Qt::WidgetShortcut);

	connect(shortcut, SIGNAL(activated()), pageView, SLOT(toNextPage()));

	shortcut = new QShortcut(Qt::Key_PageUp, this);
	shortcut->setContext(Qt::WidgetShortcut);

	connect(shortcut, SIGNAL(activated()), pageView, SLOT(toPrevPage()));

	shortcut = new QShortcut(Qt::Key_Down, this);
	shortcut->setContext(Qt::WidgetShortcut);

	connect(shortcut, SIGNAL(activated()), pageView, SLOT(toNextRow()));

	shortcut = new QShortcut(Qt::Key_Up, this);
	shortcut->setContext(Qt::WidgetShortcut);

	connect(shortcut, SIGNAL(activated()), pageView, SLOT(toPrevRow()));

	shortcut = new QShortcut(Qt::Key_Home, this);
	shortcut->setContext(Qt::WidgetShortcut);

	connect(shortcut, SIGNAL(activated()), pageView, SLOT(toFirstRecord()));

	shortcut = new QShortcut(Qt::Key_End, this);
	shortcut->setContext(Qt::WidgetShortcut);

	connect(shortcut, SIGNAL(activated()), pageView, SLOT(toLastRecord()));

	setFocusPolicy(Qt::StrongFocus);

	setFrameStyle(StyledPanel);
}

void DataSetView::adjustScrollBar(int)
{
	scrollBar->blockSignals(true);
	
	int num_recs = dataSet.getSize();
	int num_cols = pageView->getNumColumns();
	int num_recs_per_page = num_cols * pageView->getNumRows();

	if (num_recs_per_page <= num_recs) {
		scrollBar->setMaximum(num_recs - num_recs_per_page);
		scrollBar->setPageStep(num_recs_per_page);
		scrollBar->setSingleStep(num_cols);	
		scrollBar->setValue(pageView->getPageOffset());
		scrollBar->show();

	} else {
		scrollBar->hide();
		scrollBar->setValue(0);
	}

	scrollBar->blockSignals(false);
}
