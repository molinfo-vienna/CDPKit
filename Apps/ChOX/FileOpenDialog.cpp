/* 
 * FileOpenDialog.cpp 
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

#include <QFileDialog>

#include "FileOpenDialog.hpp"
#include "InputFileFilterList.hpp"


using namespace ChOX;


namespace
{

    std::unique_ptr<QFileDialog> dialogInstance;
}


QFileDialog& FileOpenDialog::get(const DataSet& data_set, bool all_file_types)
{
    if (!dialogInstance) {
        dialogInstance.reset(new QFileDialog(nullptr));

        dialogInstance->setFileMode(QFileDialog::ExistingFiles);
        dialogInstance->setAcceptMode(QFileDialog::AcceptOpen);
        dialogInstance->setNameFilterDetailsVisible(true);
        dialogInstance->setOptions(QFileDialog::DontUseNativeDialog);
    }

    QString prev_filter = dialogInstance->selectedNameFilter();

    dialogInstance->setNameFilters(all_file_types ? InputFileFilterList() : InputFileFilterList(data_set));
    dialogInstance->selectNameFilter(prev_filter);
    
    return *dialogInstance;
}

void FileOpenDialog::free()
{
    dialogInstance.reset(nullptr);
}
