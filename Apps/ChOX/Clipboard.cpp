/* 
 * Clipboard.cpp 
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


#include <memory>

#include <QClipboard>
#include <QApplication>

#include "Clipboard.hpp"
#include "ClipboardData.hpp"
#include "DataSet.hpp"


using namespace ChOX;


Clipboard& Clipboard::get()
{
    static Clipboard instance;
    static bool init = true;

    if (init) {
        connect(QApplication::clipboard(), SIGNAL(dataChanged()), &instance, SLOT(handleClipboardChange()));
        init = false;
    }
    
    return instance;
}

void Clipboard::putSelectedData(const DataSet& data_set) const
{
    std::unique_ptr<ClipboardData> cp_data(new ClipboardData());

    for (int i = 0; i < data_set.getSize(); i++)
        if (data_set.isRecordSelected(i))
            cp_data->addRecord(data_set.getRecordPointer(i));
    
    QApplication::clipboard()->setMimeData(cp_data.release());
}

void Clipboard::getData(MainWindow* main_win, DataSet& data_set, int insert_idx) const
{
    ClipboardData::extract(main_win, QApplication::clipboard()->mimeData(), data_set, insert_idx);
}

bool Clipboard::checkDataAvailability() const
{
    return ClipboardData::canHandle(QApplication::clipboard()->mimeData());
}

void Clipboard::handleClipboardChange()
{
    emit(dataAvailable(ClipboardData::canHandle(QApplication::clipboard()->mimeData())));
}
