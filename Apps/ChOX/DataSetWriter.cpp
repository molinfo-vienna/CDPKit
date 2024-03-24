/* 
 * DataSetWriter.cpp 
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


#include <fstream>
#include <iostream>

#include <QFileInfo>
#include <QDir>
#include <QProgressDialog>
#include <QApplication>

#include "CDPL/Base/DataIOManager.hpp"
#include "CDPL/Base/DataFormat.hpp"
#include "CDPL/Base/DataInputHandler.hpp"
#include "CDPL/Base/DataOutputHandler.hpp"
#include "CDPL/Base/DataWriter.hpp"
#include "CDPL/Base/Exceptions.hpp"

#include "CDPL/Chem/Molecule.hpp"
#include "CDPL/Chem/Reaction.hpp"
#include "CDPL/Vis/ControlParameterFunctions.hpp"

#include "DataSetWriter.hpp"
#include "DataSet.hpp"
#include "ConcreteDataRecord.hpp"
#include "Settings.hpp"
#include "Utilities.hpp"
#include "ControlParameterFunctions.hpp"


using namespace ChOX;


namespace
{
    
    template <typename T>
    class RecordWriter;

    template <>
    class RecordWriter<CDPL::Chem::MolecularGraph> : public DataRecordVisitor 
    {

    public:
        typedef CDPL::Base::DataWriter<CDPL::Chem::MolecularGraph>::SharedPointer WriterPointer;

        RecordWriter(const WriterPointer& writer_ptr, const CDPL::Base::DataFormat& fmt): writerPointer(writer_ptr), format(fmt) {}

    private:
        void visit(const ConcreteDataRecord<CDPL::Chem::Molecule>& mol_record) {
            try {
                CDPL::Chem::Molecule::SharedPointer mol_ptr = mol_record.getData();

                prepareOutputData(*mol_ptr, format, *writerPointer);

                writerPointer->write(*mol_ptr);

            } catch (const CDPL::Base::Exception& e) {
                std::cerr << "Error while writing: " << e.what() << std::endl;
            }
        }

        void visit(const ConcreteDataRecord<CDPL::Chem::Reaction>& rxn_record) {}

        WriterPointer writerPointer;
        const CDPL::Base::DataFormat& format;
    };

    template <>
    class RecordWriter<CDPL::Chem::Reaction> : public DataRecordVisitor 
    {

    public:
        typedef CDPL::Base::DataWriter<CDPL::Chem::Reaction>::SharedPointer WriterPointer;

        RecordWriter(const WriterPointer& writer_ptr, const CDPL::Base::DataFormat& fmt): writerPointer(writer_ptr), format(fmt) {}

    private:
        void visit(const ConcreteDataRecord<CDPL::Chem::Molecule>& mol_record) {}

        void visit(const ConcreteDataRecord<CDPL::Chem::Reaction>& rxn_record) {
            try {
                CDPL::Chem::Reaction::SharedPointer rxn_ptr = rxn_record.getData();

                prepareOutputData(*rxn_ptr, format, *writerPointer);

                writerPointer->write(*rxn_ptr);

            } catch (const CDPL::Base::Exception& e) {
                 std::cerr << " while writing: " << e.what() << std::endl;
            }
        }

        WriterPointer writerPointer;
        const CDPL::Base::DataFormat& format;
    };
}


DataSetWriter::DataSetWriter(const DataSet& data_set, QWidget* parent, const QString& file_name, 
                             const QString& filter, const Settings& settings, bool selection):
    QObject(), dataSet(data_set), parent(parent), fileName(file_name), filter(filter), settings(settings), 
    writeSelection(selection) {}

DataSetWriter::~DataSetWriter() {}

void DataSetWriter::write()
{
    if (dataSet.getSize() == 0)
        return;

    dataSet.getRecord(0).accept(*this);
}

void DataSetWriter::visit(const ConcreteDataRecord<CDPL::Chem::Reaction>&)
{
    writeRecords<CDPL::Chem::Reaction>(getDefaultRxnOutputFormatParameter(settings));
}
    
void DataSetWriter::visit(const ConcreteDataRecord<CDPL::Chem::Molecule>&)
{
    writeRecords<CDPL::Chem::MolecularGraph>(getDefaultMolOutputFormatParameter(settings));
}

template <typename T>
void DataSetWriter::writeRecords(const std::string& def_format)
{
    using namespace CDPL;
    using namespace Base;
    using namespace Vis;

    QFileInfo file_info(fileName);
    QString file_ext = file_info.completeSuffix();
    QString base_name;

    typename DataOutputHandler<T>::SharedPointer handler;

    if (file_ext.isEmpty() || !(handler = DataIOManager<T>::getOutputHandlerByFileExtension(file_ext.toStdString()))) {
        typename DataIOManager<T>::OutputHandlerIterator handlers_end = DataIOManager<T>::getOutputHandlersEnd();

        for (typename DataIOManager<T>::OutputHandlerIterator h_it = DataIOManager<T>::getOutputHandlersBegin(); 
             h_it != handlers_end; ++h_it) {

            handler = *h_it;

            const DataFormat& fmt_descr = handler->getDataFormat();

            if (filter.startsWith(QString::fromStdString(fmt_descr.getDescription()))) 
                break;

            handler = 0;
        }

        if (!handler)  
            handler = DataIOManager<T>::getOutputHandlerByName(def_format);

        file_ext = QString::fromStdString(*handler->getDataFormat().getFileExtensionsBegin());        
        base_name = fileName;

    } else
        base_name = file_info.absolutePath() + QDir::separator() + file_info.baseName();    

    const DataFormat& fmt_descr = handler->getDataFormat();
    const SettingsContainer& params = settings.getWriterControlParameters(fmt_descr.getName());
    bool single_rec_files = getWriteSingleRecordFilesParameter(params) || !fmt_descr.isMultiRecordFormat();

    QProgressDialog progress_dlg(tr("Please wait ..."), tr("Abort"), 0, 100, parent);

    progress_dlg.setWindowTitle(tr("ChOX - Writing Data"));
    progress_dlg.setAutoClose(true);
    progress_dlg.setAutoReset(true);
    progress_dlg.setWindowModality(Qt::ApplicationModal);

    qApp->processEvents();

    if (writeSelection) {
        progress_dlg.setMaximum(dataSet.getNumSelectedRecords());

        if (!single_rec_files) {
            QString fileName = base_name + "." + file_ext;
        
            emit statusMessage(tr("Writing data to file '%1', please wait ...").arg(QFileInfo(fileName).fileName()));

            typename RecordWriter<T>::WriterPointer writer_ptr(handler->createWriter(fileName.toStdString()));

            RecordWriter<T> record_writer(writer_ptr, handler->getDataFormat());

            writer_ptr->setParent(&params);

            for (int i = 0, j = 0; i < dataSet.getSize(); i++) {
                if (progress_dlg.wasCanceled()) {
                    emit statusMessage(tr("Writing aborted."));
                    return;
                }

                if (!dataSet.isRecordSelected(i))
                    continue;

                const DataRecord& data_record = dataSet.getRecord(i);

                data_record.accept(record_writer);
                j++;

                if (!(*writer_ptr)) {
                    emit errorMessage(tr("Error while writing to file '%1'!").arg(QFileInfo(fileName).fileName()));
                    return;
                }

                progress_dlg.setValue(j);

                qApp->processEvents();
            }
        
        } else {
            emit statusMessage(tr("Writing data, please wait ..."));

            for (int i = 0, j = 0; i < dataSet.getSize(); i++) {
                if (progress_dlg.wasCanceled()) {
                    emit statusMessage(tr("Writing aborted."));
                    return;
                }

                if (!dataSet.isRecordSelected(i))
                    continue;

                QString fileName = QString("%1_%2.%3").arg(base_name).arg(i + 1).arg(file_ext);
        
                typename RecordWriter<T>::WriterPointer writer_ptr(handler->createWriter(fileName.toStdString()));
                RecordWriter<T> record_writer(writer_ptr, handler->getDataFormat());

                writer_ptr->setParent(&params);

                const DataRecord& data_record = dataSet.getRecord(i);

                data_record.accept(record_writer);
                j++;

                if (!(*writer_ptr)) {
                    emit errorMessage(tr("Error while writing to file '%1'!").arg(QFileInfo(fileName).fileName()));
                    return;
                }

                progress_dlg.setValue(j++);

                qApp->processEvents();
            }
        }

    } else {
        progress_dlg.setMaximum(dataSet.getSize());

        if (!single_rec_files) {
            QString fileName = base_name + "." + file_ext;

            emit statusMessage(tr("Writing data to file '%1', please wait ...").arg(QFileInfo(fileName).fileName()));
            typename RecordWriter<T>::WriterPointer writer_ptr(handler->createWriter(fileName.toStdString()));

            RecordWriter<T> record_writer(writer_ptr, handler->getDataFormat());
            
            writer_ptr->setParent(&params);

            for (int i = 0; i < dataSet.getSize(); i++) {
                if (progress_dlg.wasCanceled()) {
                    emit statusMessage(tr("Writing aborted."));
                    return;
                }

                const DataRecord& data_record = dataSet.getRecord(i);

                data_record.accept(record_writer);

                if (!(*writer_ptr)) {
                    emit errorMessage(tr("Error while writing to file '%1'!").arg(QFileInfo(fileName).fileName()));
                    return;
                }

                progress_dlg.setValue(i);

                qApp->processEvents();
            }
        
        } else {
            emit statusMessage(tr("Writing data, please wait ..."));

            for (int i = 0; i < dataSet.getSize(); i++) {
                if (progress_dlg.wasCanceled()) {
                    emit statusMessage(tr("Writing aborted."));
                    return;
                }

                QString fileName = QString("%1_%2.%3").arg(base_name).arg(i + 1).arg(file_ext);
        
                typename RecordWriter<T>::WriterPointer writer_ptr(handler->createWriter(fileName.toStdString()));

                RecordWriter<T> record_writer(writer_ptr, handler->getDataFormat());

                writer_ptr->setParent(&params);
    
                const DataRecord& data_record = dataSet.getRecord(i);

                data_record.accept(record_writer);

                if (!(*writer_ptr)) {
                    emit errorMessage(tr("Error while writing to file '%1'!").arg(QFileInfo(fileName).fileName()));
                    return;
                }

                progress_dlg.setValue(i);

                qApp->processEvents();
            }
        }
    }

    emit statusMessage(QString());
}
