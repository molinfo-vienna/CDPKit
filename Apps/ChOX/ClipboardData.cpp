/* 
 * ClipboardData.cpp 
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


#include <sstream>
#include <exception>

#include <QUrl>

#include "ClipboardData.hpp"
#include "DataSet.hpp"
#include "MainWindow.hpp"
#include "MemoryDataRecord.hpp"
#include "Utilities.hpp"

#include "CDPL/Chem/BasicMolecule.hpp"
#include "CDPL/Chem/BasicReaction.hpp"
#include "CDPL/Chem/ControlParameterFunctions.hpp"
#include "CDPL/Biomol/ControlParameterFunctions.hpp"
#include "CDPL/Pharm/ControlParameterFunctions.hpp"
#include "CDPL/ConfGen/ControlParameterFunctions.hpp"
#include "CDPL/Base/DataIOManager.hpp"


using namespace ChOX;


ClipboardData::ClipboardData() {}

bool ClipboardData::canHandle(const QMimeData* data)
{
    using namespace CDPL;
    
    if (!data)
        return false;
  
    if (qobject_cast<const ClipboardData*>(data))
        return true;

    if (data->hasUrls() && !getChemDataFiles(data).isEmpty())
        return true;

    if (canHandleMimeTypes<Chem::Molecule>(data) || canHandleMimeTypes<Chem::Reaction>(data))
        return true;

    if (data->hasText())
        return (canProcessText<Chem::Molecule, Chem::BasicMolecule>(data) ||
                canProcessText<Chem::Reaction, Chem::BasicReaction>(data));
    
    return false;
}

void ClipboardData::extract(MainWindow* main_win, const QMimeData* data, DataSet& data_set, int insert_idx)
{
    using namespace CDPL;

    if (!data)
        return;
      
    auto chox_cpd = qobject_cast<const ClipboardData*>(data);

    if (chox_cpd) {
        data_set.insertRecords(chox_cpd->records.begin(), chox_cpd->records.end(), insert_idx, "");
        return;
    }
    
    if (data->hasUrls()) {
        auto files = getChemDataFiles(data);

        if (!files.isEmpty()) {
            main_win->openFiles(files);
            return;
        }
    }

    if (readMimeTypeData<Chem::Molecule, Chem::BasicMolecule>(data, data_set, insert_idx))
        return;

    if (readMimeTypeData<Chem::Reaction, Chem::BasicReaction>(data, data_set, insert_idx))
        return;

    if (!data->hasText())
        return;

    if (readTextData<Chem::Molecule, Chem::BasicMolecule>(data, data_set, insert_idx))
        return;

    readTextData<Chem::Reaction, Chem::BasicReaction>(data, data_set, insert_idx);
}

void ClipboardData::addRecord(const DataRecord::SharedPointer& record)
{
    records.push_back(record);
}

QStringList ClipboardData::getChemDataFiles(const QMimeData* data)
{
    using namespace CDPL;
    
    QStringList files;

    for (auto& url : data->urls()) {
        if (!url.isLocalFile())
            continue;

        auto file_name = url.fileName().toStdString();

        if (Base::DataIOManager<Chem::Molecule>::getInputHandlerByFileName(file_name) ||
            Base::DataIOManager<Chem::Reaction>::getInputHandlerByFileName(file_name)) {
            files.append(url.path());
        }
    }

    return files;
}

template <typename DataType>
bool ClipboardData::canHandleMimeTypes(const QMimeData* data)
{
    using namespace CDPL;
    
    for (auto it = Base::DataIOManager<DataType>::getInputHandlersBegin(), end = Base::DataIOManager<DataType>::getInputHandlersEnd();
         it != end; ++it)

        if (data->hasFormat((*it)->getDataFormat().getMimeType().c_str()))
            return true;

    return false;
}

template <typename DataType, typename StorageDataType>
bool ClipboardData::canProcessText(const QMimeData* data)
{
    using namespace CDPL;

    auto text = data->text().toStdString();
    StorageDataType obj;

    for (auto it = Base::DataIOManager<DataType>::getInputHandlersBegin(), end = Base::DataIOManager<DataType>::getInputHandlersEnd();
         it != end; ++it) {

        try {
            std::istringstream iss(text, std::ios_base::in | std::ios_base::binary);
            auto reader = (*it)->createReader(iss);

            Chem::setStrictErrorCheckingParameter(*reader, true);
            Biomol::setStrictErrorCheckingParameter(*reader, true);
            Pharm::setStrictErrorCheckingParameter(*reader, true);
            ConfGen::setStrictErrorCheckingParameter(*reader, true);

            if (reader->read(obj))
                return checkReadData(obj);

        } catch (std::exception& e) {}
    }

    return false;
}

bool ClipboardData::checkReadData(const CDPL::Chem::Molecule& mol)
{
    return (mol.getNumAtoms() > 0);
}

bool ClipboardData::checkReadData(const CDPL::Chem::Reaction& rxn)
{
    return (rxn.getNumComponents() > 0);
}

template <typename DataType, typename StorageDataType>
bool ClipboardData::readMimeTypeData(const QMimeData* data, DataSet& data_set, int insert_idx)
{
    using namespace CDPL;
    
    for (auto it = Base::DataIOManager<DataType>::getInputHandlersBegin(), end = Base::DataIOManager<DataType>::getInputHandlersEnd();
         it != end; ++it) {

        QString mime_type((*it)->getDataFormat().getMimeType().c_str());
        
        if (!data->hasFormat(mime_type))
            continue;

        auto raw_data = data->data(mime_type);
        std::string str_data(raw_data.data(), raw_data.length());
        
        if (readData<DataType, StorageDataType>(**it, str_data, data_set, insert_idx, false))
            return true;
    }

    return false;
}

template <typename DataType, typename StorageDataType>
bool ClipboardData::readTextData(const QMimeData* data, DataSet& data_set, int insert_idx)
{
    using namespace CDPL;

    auto text = data->text().toStdString();
 
    for (auto it = Base::DataIOManager<DataType>::getInputHandlersBegin(), end = Base::DataIOManager<DataType>::getInputHandlersEnd();
         it != end; ++it) {

        if (readData<DataType, StorageDataType>(**it, text, data_set, insert_idx, true))
            return true;
    }

    return false;
}

template <typename DataType, typename StorageDataType>
bool ClipboardData::readData(const CDPL::Base::DataInputHandler<DataType>& handler, const std::string& data, DataSet& data_set, int insert_idx, bool strict)
{
    using namespace CDPL;

    typedef MemoryDataRecord<DataType, StorageDataType> RecordType;
    typedef std::shared_ptr<RecordType> RecordPtr;
    typedef std::vector<RecordPtr> RecordList;

    RecordList records;

    try {
        std::istringstream iss(data, std::ios_base::in | std::ios_base::binary); 

        auto reader = handler.createReader(iss);

        Chem::setStrictErrorCheckingParameter(*reader, strict);
        Biomol::setStrictErrorCheckingParameter(*reader, strict);
        Pharm::setStrictErrorCheckingParameter(*reader, strict);
        ConfGen::setStrictErrorCheckingParameter(*reader, strict);

        while (true) {
            RecordPtr rec_ptr(new RecordType());

            if (reader->read(*rec_ptr->getData())) {
                initData(*rec_ptr->getData());
                records.push_back(rec_ptr);
                
            } else
                break;
        }
        
    } catch (std::exception& e) {}

    if (!records.empty()) {
        data_set.insertRecords(records.begin(), records.end(), insert_idx, "");
        return true;
    }
    
    return false;
}
