/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * RecentFilesList.cpp 
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


#include <QSettings>

#include "RecentFilesList.hpp"


using namespace ChOX;


RecentFilesList::RecentFilesList() 
{ 
	QSettings settings;

	fileNames = settings.value("/General/RecentFiles").toStringList();
}

RecentFilesList::~RecentFilesList()
{
	QSettings settings;

	settings.setValue("/General/RecentFiles", fileNames);
}

RecentFilesList& RecentFilesList::instance()
{
	static RecentFilesList inst;

	return inst;
}

void RecentFilesList::clear()
{
	fileNames.clear();

	emit entriesChanged();
}

void RecentFilesList::addEntry(const QString& file_name)
{
	int idx = fileNames.indexOf(file_name);

	if (idx == -1) {
		fileNames.push_front(file_name);

		if (fileNames.size() > 15)
			fileNames.pop_back();

	} else {
		fileNames.removeAt(idx);
		fileNames.push_front(file_name);
	}

	emit entriesChanged();
}

const QStringList& RecentFilesList::getEntries() const
{
	return fileNames;
}
