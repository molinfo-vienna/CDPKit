/* 
 * SubstructSearchProcessor.cpp 
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


#include <exception>

#include <QProgressDialog>
#include <QFileDialog>

#include "CDPL/Chem/MultiSubstructureSearch.hpp"
#include "CDPL/Chem/Reaction.hpp"
#include "CDPL/Chem/MolecularGraphFunctions.hpp"

#include "SubstructSearchProcessor.hpp"
#include "SubstructSearchResultDialog.hpp"
#include "Settings.hpp"
#include "DataSet.hpp"
#include "DataSetWriter.hpp"
#include "FileSaveDialog.hpp"
#include "ConcreteDataRecord.hpp"
#include "ControlParameter.hpp"
#include "ControlParameterFunctions.hpp"
#include "Utilities.hpp"


using namespace ChOX;


SubstructSearchProcessor::SubstructSearchProcessor(QWidget* parent, DataSet& data_set, Settings& settings):
    QObject(parent), parent(parent), dataSet(data_set), settings(settings),
    queryValid(false), resultDialog(nullptr)
{
    connect(&settings, SIGNAL(controlParamChanged(const CDPL::Base::LookupKey&, const CDPL::Base::Any&)),
            this, SLOT(handleControlParamChanged(const CDPL::Base::LookupKey&, const CDPL::Base::Any&)));
    connect(&dataSet, SIGNAL(sizeChanged(int)), this, SLOT(handelDataSetSizeChange(int)));
}

SubstructSearchProcessor::~SubstructSearchProcessor()
{}

void SubstructSearchProcessor::handleControlParamChanged(const CDPL::Base::LookupKey& key, const CDPL::Base::Any& value)
{
    using namespace CDPL::Chem;
    
    if (key != ControlParameter::SUBSTRUCT_SEARCH_QUERY)
        return;
  
    auto& query = getSubstructSearchQueryParameter(settings);

    if (query.count() <= 1) {
        queryValid = false;
        emit(substructSearchEnabled(false));
        return;
    }
    
    queryValid = true;
    
    if (!subSearch)
        subSearch.reset(new MultiSubstructureSearch());
    else
        subSearch->clear();

    for (int i = 0; i < int(query.count()) - 1; i++) {
        Molecule::SharedPointer mol_ptr = parseSMARTS(query[i]);

        if (!mol_ptr) {
            queryValid = false;
            break;
        }

        subSearch->addSubstructure(mol_ptr);
    }

    if (queryValid) {
        try {
            subSearch->setup(query.last().toStdString());
            
        } catch (const std::exception& e) {
            queryValid = false;
        }
    }

    emit(substructSearchEnabled(queryValid && dataSet.getSize() > 0));
}

void SubstructSearchProcessor::handelDataSetSizeChange(int size)
{
    emit(substructSearchEnabled(queryValid && size > 0));
}

void SubstructSearchProcessor::performSubstructSearch()
{
    if (!queryValid)
        return;

    int num_records = dataSet.getSize();
    int num_matches = 0;
    QProgressDialog progress(tr("Searching for Matches ..."), tr("Stop Search"), 0, num_records, parent);

    progress.setWindowModality(Qt::WindowModal);

    recordMatchMask.resize(num_records);
    recordMatchMask.reset();
    
    for (int i = 0; i < num_records; i++) {
        progress.setValue(i);

        if (progress.wasCanceled())
            break;

        foundHit = false;
        dataSet.getRecord(i).accept(*this);

        if (foundHit) {
            recordMatchMask.set(i);
            num_matches++;
            
            progress.setLabelText(tr("Searching for Matches ... (") + QString::number(num_matches) + tr(" found)"));
        }
    }
    
    progress.setValue(num_records);

    if (!resultDialog) {
        resultDialog = new SubstructSearchResultDialog(parent);

        connect(resultDialog, SIGNAL(saveMatchingRequested()), this, SLOT(saveMatches()));
        connect(resultDialog, SIGNAL(saveNonMatchingRequested()), this, SLOT(saveNonMatches()));
    }
    
    resultDialog->setup(num_matches);

    if (resultDialog->exec() != QDialog::Accepted)
        return;

    switch (resultDialog->getViewAction()) {

        case SubstructSearchResultDialog::SEL_MATCHING:
            dataSet.setRecordSelection(recordMatchMask);
            return;
            
        case SubstructSearchResultDialog::SEL_NON_MATCHING:
            dataSet.setRecordSelection(~recordMatchMask);
            return;
            
        case SubstructSearchResultDialog::DEL_MATCHING:
            dataSet.removeRecords(recordMatchMask);
            return;
            
        case SubstructSearchResultDialog::DEL_NON_MATCHING:
            dataSet.removeRecords(~recordMatchMask);
            
        default:
            return;
    }
}

void SubstructSearchProcessor::visit(const ConcreteDataRecord<CDPL::Chem::Reaction>& record)
{
    auto rxn_ptr = record.getData();

    for (auto& comp : *rxn_ptr) {
        if (subSearch->matches(comp)) {
            initSubstructureSearchTarget(comp, false);
            foundHit = true;
            break;
        }
    }
}

void SubstructSearchProcessor::visit(const ConcreteDataRecord<CDPL::Chem::Molecule>& record)
{
    auto mol_ptr = record.getData();

    initSubstructureSearchTarget(*mol_ptr, false);
    
    if (subSearch->matches(*mol_ptr))
        foundHit = true;
}

void SubstructSearchProcessor::saveMatches()
{
    DataSet matches(nullptr);
  
    matches.appendRecords(dataSet, recordMatchMask);

    auto& file_dialog = FileSaveDialog::get(matches);

    file_dialog.setWindowTitle(tr("ChOX - Save Matching Records As"));

    if (file_dialog.exec() == QDialog::Accepted && !file_dialog.selectedFiles().isEmpty()) {
        DataSetWriter data_writer(matches, resultDialog, file_dialog.selectedFiles().first(),
                                  file_dialog.selectedNameFilter(), settings, false);

        connect(&data_writer, SIGNAL(errorMessage(const QString&)), parent, SLOT(showErrorMessage(const QString&)));
        connect(&data_writer, SIGNAL(errorMessage(const QString&)), parent, SLOT(showStatusMessage(const QString&)));
        connect(&data_writer, SIGNAL(statusMessage(const QString&)), parent, SLOT(showStatusMessage(const QString&)));

        data_writer.write();
    }
}

void SubstructSearchProcessor::saveNonMatches()
{
    DataSet non_matches(nullptr);

    non_matches.appendRecords(dataSet, ~recordMatchMask);

    auto& file_dialog = FileSaveDialog::get(non_matches);

    file_dialog.setWindowTitle(tr("ChOX - Save Non-Matching Records As"));

    if (file_dialog.exec() == QDialog::Accepted && !file_dialog.selectedFiles().isEmpty()) {
        DataSetWriter data_writer(non_matches, resultDialog, file_dialog.selectedFiles().first(),
                                  file_dialog.selectedNameFilter(), settings, false);

        connect(&data_writer, SIGNAL(errorMessage(const QString&)), parent, SLOT(showErrorMessage(const QString&)));
        connect(&data_writer, SIGNAL(errorMessage(const QString&)), parent, SLOT(showStatusMessage(const QString&)));
        connect(&data_writer, SIGNAL(statusMessage(const QString&)), parent, SLOT(showStatusMessage(const QString&)));

        data_writer.write();
    }
}
