/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * MainWindowList.cpp 
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


#include <algorithm>

#include "MainWindowList.hpp"
#include "MainWindow.hpp"


using namespace ChOX;


MainWindowList::MainWindowList() {} 

MainWindowList::~MainWindowList() {}

MainWindowList& MainWindowList::instance()
{
	static MainWindowList inst;

	return inst;
}

void MainWindowList::addWindow(MainWindow* win)
{
	connect(win, SIGNAL(destroyed(QObject*)), this, SLOT(removeWindow(QObject*)));

	windows.push_back(win);
}

MainWindowList::ConstIterator MainWindowList::getBegin() const
{
	return windows.begin();
}

MainWindowList::ConstIterator MainWindowList::getEnd() const
{
	return windows.end();
}

MainWindow* MainWindowList::getWindow(int idx) const
{
	return windows.at(idx);
}

void MainWindowList::removeWindow(QObject* win)
{
	windows.erase(std::remove(windows.begin(), windows.end(), win), windows.end());
}

int MainWindowList::getNumWindows() const
{
	return int(windows.size());
}
