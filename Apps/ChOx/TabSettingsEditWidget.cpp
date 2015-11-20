/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * TabSettingsEditWidget.cpp 
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


#include <algorithm>

#include <boost/bind.hpp>

#include <QTabWidget>
#include <QVBoxLayout>

#include "TabSettingsEditWidget.hpp"


using namespace ChOx;


TabSettingsEditWidget::TabSettingsEditWidget(QWidget* parent): 
	SettingsEditWidget(parent)
{
	init();
}

bool TabSettingsEditWidget::haveChangedSettings() const
{
	return (std::find_if(editWidgetList.begin(), editWidgetList.end(), 
						 boost::bind(&SettingsEditWidget::haveChangedSettings, _1)) != editWidgetList.end());
}

void TabSettingsEditWidget::addEditWidget(SettingsEditWidget* widget, const QString& label)
{
	editWidgetList.push_back(widget);

	connect(widget, SIGNAL(settingsChanged()), this, SIGNAL(settingsChanged()));

	tabWidget->addTab(widget, label);
}

void TabSettingsEditWidget::apply()
{
	std::for_each(editWidgetList.begin(), editWidgetList.end(), 
				  boost::bind(&SettingsEditWidget::apply, _1));
}

void TabSettingsEditWidget::reset()
{
	if (!editWidgetList.empty())
		editWidgetList.at(tabWidget->currentIndex())->reset();
}

void TabSettingsEditWidget::setDefaults()
{
	if (!editWidgetList.empty())
		editWidgetList.at(tabWidget->currentIndex())->setDefaults();
}

void TabSettingsEditWidget::init()
{
	QBoxLayout* main_layout = new QVBoxLayout(this);

	main_layout->setMargin(0);

	tabWidget = new QTabWidget(this);

	tabWidget->setContentsMargins(5, 5, 5, 5);

	main_layout->addWidget(tabWidget);
}
