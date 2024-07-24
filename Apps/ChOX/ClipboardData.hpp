/* 
 * ClipboardData.hpp 
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


#ifndef CHOX_CLIPBOARDDATA_HPP
#define CHOX_CLIPBOARDDATA_HPP

#include <vector>

#include <QMimeData>

#include "CDPL/Base/DataInputHandler.hpp"

#include "DataRecord.hpp"


namespace ChOX
{

    class DataSet;
    class MainWindow;
    
    class ClipboardData : public QMimeData
    {

        Q_OBJECT
        
      public:
        ClipboardData();
        
        static bool canHandle(const QMimeData* data);

        static void extract(MainWindow* main_win, const QMimeData* data, DataSet& data_set, int insert_idx);
        
        void addRecord(const DataRecord::SharedPointer& record);
        
      private:
        static QStringList getChemDataFiles(const QMimeData* data);

        template <typename DataType>
        static bool canHandleMimeTypes(const QMimeData* data);
        
        template <typename DataType, typename StorageDataType>
        static bool canProcessText(const QMimeData* data);

        template <typename DataType, typename StorageDataType>
        static bool readMimeTypeData(const QMimeData* data, DataSet& data_set, int insert_idx);

        template <typename DataType, typename StorageDataType>
        static bool readTextData(const QMimeData* data, DataSet& data_set, int insert_idx);
        
        template <typename DataType, typename StorageDataType>
        static bool readData(const CDPL::Base::DataInputHandler<DataType>& handler,
                             const std::string& data, DataSet& data_set, int insert_idx, bool strict);
        
        typedef std::vector<DataRecord::SharedPointer> DataRecordList;

        DataRecordList records;
    };
} // namespace ChOX

#endif // CHOX_CLIPBOARDDATA_HPP
