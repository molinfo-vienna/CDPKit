/* 
 * DataRecordPropertyView.cpp 
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


#include "CDPL/Chem/MolecularGraphFunctions.hpp"
#include "CDPL/Chem/ReactionFunctions.hpp"

#include "DataRecordPropertyView.hpp"
#include "DataSetPageView.hpp"
#include "DataSet.hpp"


using namespace ChOX;


DataRecordPropertyView::DataRecordPropertyView(QWidget* parent): 
    QTableWidget(parent)
{}

void DataRecordPropertyView::update(DataSetPageView& page_view)
{
    propData.clear();
    rowHeaders.clear();
    colHeaders.clear();
    propColIndices.clear();
    
    for (int i = page_view.getPageOffset(),
             end_idx = std::min(page_view.getDataSet().getSize(),
                                page_view.getPageOffset() +
                                page_view.getNumRows() * page_view.getNumColumns()); i < end_idx; i++) {

        page_view.accept(i, *this);
        rowHeaders << QString::number(i + 1);
    }

    setRowCount(propData.size());

    for (int i = 0; i < rowHeaders.count(); i++) {
        if (!propData[i])
            continue;
        
        for (auto& item : *propData[i]) {
            auto it = propColIndices.find(item.getHeader());

            if (it != propColIndices.end()) {
                setItem(i, it->second, new QTableWidgetItem(QString::fromStdString(item.getData())));
                continue;
            }

            propColIndices[item.getHeader()] = colHeaders.count();

            setColumnCount(colHeaders.count() + 1);
            setItem(i, colHeaders.count(), new QTableWidgetItem(QString::fromStdString(item.getData())));
            colHeaders << QString::fromStdString(item.getHeader());
        }
    }
    
    setHorizontalHeaderLabels(colHeaders);
    setVerticalHeaderLabels(rowHeaders);
}

void DataRecordPropertyView::visit(CDPL::Chem::Reaction& rxn)
{
    if (hasReactionData(rxn))
        propData.push_back(getReactionData(rxn));
    else
        propData.push_back(CDPL::Chem::StringDataBlock::SharedPointer());
}

void DataRecordPropertyView::visit(CDPL::Chem::Molecule& mol)
{
    if (hasStructureData(mol))
        propData.push_back(getStructureData(mol));
    else
        propData.push_back(CDPL::Chem::StringDataBlock::SharedPointer());
}
