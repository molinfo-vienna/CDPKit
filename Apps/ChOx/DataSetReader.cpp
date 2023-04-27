/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * DataSetWriter.cpp 
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


#include <vector>
#include <cstddef>
#include <iostream>

#include <QFileInfo>
#include <QDir>
#include <QProgressDialog>
#include <QApplication>

#include "CDPL/Base/DataIOManager.hpp"
#include "CDPL/Base/DataFormat.hpp"
#include "CDPL/Base/DataInputHandler.hpp"
#include "CDPL/Base/Exceptions.hpp"

#include "CDPL/Chem/BasicMolecule.hpp"
#include "CDPL/Chem/BasicReaction.hpp"

#include "DataSetReader.hpp"
#include "DataSet.hpp"
#include "Settings.hpp"


using namespace ChOX;


namespace
{

	struct IndexingAborted {};

	template <typename T>
	class IndexingProgressCallback : public QObject
	{
	
	public:
		typedef typename CDPL::Base::DataReader<T>::SharedPointer ReaderPointer;

		IndexingProgressCallback(const ReaderPointer& reader_ptr, QWidget* parent): 
			QObject(), reader(reader_ptr), progressDlg(tr("Please wait ..."), tr("Abort"), 0, 1000, parent) {
			progressDlg.setWindowTitle(tr("ChOX - Indexing File"));
			progressDlg.setAutoClose(true);
			progressDlg.setAutoReset(true);
            progressDlg.setWindowModality(Qt::ApplicationModal);

			callbackID = reader->registerIOCallback(boost::ref(*this));
		}

		~IndexingProgressCallback() {
			reader->unregisterIOCallback(callbackID);
		}

		void operator()(const CDPL::Base::DataIOBase&, double progress) {
     		if (progressDlg.wasCanceled())
				throw IndexingAborted();
					
			progressDlg.setValue(progress * 1000);

            qApp->processEvents();
		}

	private:
		ReaderPointer   reader;
		QProgressDialog progressDlg;
        std::size_t     callbackID;
	};
}


DataSetReader::DataSetReader(DataSet& data_set, QWidget* parent, const QString& file_name, 
							 const Settings& settings):
	QObject(), dataSet(data_set), settings(settings), parent(parent), fileName(file_name), 
	isMoleculeDataSet(false) {}

DataSetReader::~DataSetReader() {}

bool DataSetReader::read()
{
	using namespace CDPL;

	QFileInfo file_info(fileName);

	if (!file_info.exists()) {
		emit errorMessage(tr("File '%1' does not exist!").arg(file_info.fileName()));
		return false;
	}

	if (file_info.isDir()) {
		emit errorMessage(tr("File '%1' is a directory!").arg(file_info.fileName()));
		return false;
	}

	try {
		if (dataSet.getSize() == 0) {
			if (appendRecords<Chem::Reaction, Chem::BasicReaction>(true))
				return true;

			if (appendRecords<Chem::Molecule, Chem::BasicMolecule>(true))
				return true;

			if (appendRecords<Chem::Reaction, Chem::BasicReaction>(false))
				return true;

			if (appendRecords<Chem::Molecule, Chem::BasicMolecule>(false))
				return true;

			emit errorMessage(tr("Unknown file format for '%1'").arg(file_info.fileName()));
			return false;
		}

		dataSet.getRecord(0).accept(*this);

		if (isMoleculeDataSet) {
			if (!(appendRecords<Chem::Molecule, Chem::BasicMolecule>(true)
				  || appendRecords<Chem::Molecule, Chem::BasicMolecule>(false))) {

				emit errorMessage(tr("Unknown or invalid molecule file format for '%1'!").arg(file_info.fileName()));
				return false;
			}
		} else {
			if (!(appendRecords<Chem::Reaction, Chem::BasicReaction>(true)
				  || appendRecords<Chem::Reaction, Chem::BasicReaction>(false))) {
			
				emit errorMessage(tr("Unknown or invalid reaction file format for '%1'!").arg(file_info.fileName()));
				return false;
			}
		}

	} catch (const IndexingAborted&) {
		emit statusMessage(tr("Reading aborted."));
		return false;
	}

	return true;
}

void DataSetReader::visit(const ConcreteDataRecord<CDPL::Chem::Reaction>&)
{
	isMoleculeDataSet = false;
}
	
void DataSetReader::visit(const ConcreteDataRecord<CDPL::Chem::Molecule>&)
{
	isMoleculeDataSet = true;
}

template <typename T, typename ImplT>
bool DataSetReader::appendRecords(bool use_file_ext)
{
	using namespace CDPL;
	using namespace Base;

	QFileInfo file_info(fileName);

	typename FileDataRecord<T, ImplT>::ReaderPointer reader_ptr;

	if (use_file_ext) {
		typename DataInputHandler<T>::SharedPointer handler =
			DataIOManager<T>::getInputHandlerByFileExtension(file_info.completeSuffix().toStdString().c_str());

		if (!handler) {
			handler =
				DataIOManager<T>::getInputHandlerByFileExtension(file_info.suffix().toStdString().c_str());

			if (!handler)
				return false;
		}

		try {
			ImplT data;

			reader_ptr = handler->createReader(fileName.toStdString().c_str(), std::ios_base::binary | std::ios_base::in);

			reader_ptr->setParent(&settings.getReaderControlParameters(handler->getDataFormat().getName()));

			if (!reader_ptr->read(data))
				return false;

		} catch (const Exception& e) {
			std::cerr << "Reader (using file ext.): " << e.what() << std::endl;
			return false;
		}

	} else {
		typename DataIOManager<T>::InputHandlerIterator handlers_end = DataIOManager<T>::getInputHandlersEnd();

		bool found_reader = false;

		for (typename DataIOManager<T>::InputHandlerIterator h_it = DataIOManager<T>::getInputHandlersBegin();
			 h_it != handlers_end && !found_reader; ++h_it) {

			try {
				ImplT data;

				reader_ptr = (*h_it)->createReader(fileName.toStdString().c_str(), std::ios_base::binary | std::ios_base::in);

				reader_ptr->setParent(&settings.getReaderControlParameters((*h_it)->getDataFormat().getName()));
				
				if (reader_ptr->read(data))
					found_reader = true;

			} catch (const Exception& e) {
				std::cerr << "Reader: " << e.what() << std::endl;
			}
		}

		if (!found_reader) 
			return false;
	}

	emit statusMessage(tr("Indexing records in '%1', please wait ...").arg(file_info.fileName()));

	IndexingProgressCallback<T> progress_rep(reader_ptr, parent);

	try {
		reader_ptr->getNumRecords();

	} catch (const Exception& e) {
		emit errorMessage(QString(tr("File '%1' contains errors:\n") + e.what()).arg(file_info.fileName()));
	}

	std::size_t num_records = reader_ptr->getNumRecords();
	std::vector<DataRecord::SharedPointer> records;

	records.reserve(num_records);

	for (std::size_t i = 0; i < num_records; i++) 
		records.push_back(DataRecord::SharedPointer(new FileDataRecord<T, ImplT>(reader_ptr, i)));

	dataSet.appendRecords(records.begin(), records.end(), fileName);

	emit statusMessage(QString());

	return true;
}
