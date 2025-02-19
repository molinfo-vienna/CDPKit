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


#include <QHeaderView>

#include "CDPL/Chem/MolecularGraphFunctions.hpp"
#include "CDPL/Chem/ReactionFunctions.hpp"

#include "DataRecordPropertyView.hpp"
#include "DataSetPageView.hpp"
#include "DataSet.hpp"


using namespace ChOX;


DataRecordPropertyView::DataRecordPropertyView(QWidget* parent): 
    QTableWidget(parent)
{
    init();
}

void DataRecordPropertyView::update(DataSetPageView& page_view)
{
    if (page_view.getDataSet().getSize() == 0) {
        clear();
        setRowCount(0);
        setColumnCount(0);
        colHeaders.clear();
        propColIndices.clear();
        return;
    }

    propData.clear();

    for (int i = page_view.getPageOffset(),
             end_idx = std::min(page_view.getDataSet().getSize(),
                                page_view.getPageOffset() +
                                page_view.getNumRows() * page_view.getNumColumns()); i < end_idx; i++) {

        page_view.accept(i, *this);
    }

    auto old_num_cols = colHeaders.count();
    auto num_rows = propData.size();

    setSortingEnabled(false);
    setRowCount(num_rows);
    clearContents();
    
    for (std::size_t i = 0; i < num_rows; i++) {
        if (columnCount() == 0) {
            colHeaders = QStringList("#");
            setColumnCount(1);
        }
        
        setItem(i, 0, new QTableWidgetItem(QString::number(page_view.getPageOffset() + i + 1)));
                
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

    if (colHeaders.count() != old_num_cols)
        setHorizontalHeaderLabels(colHeaders);
    
    setSortingEnabled(true);
}

void DataRecordPropertyView::init()
{
    setContextMenuPolicy(Qt::DefaultContextMenu);
    setVerticalScrollMode(ScrollPerItem);
    setSelectionMode(NoSelection);

    verticalHeader()->hide();

    colHeaders = QStringList("Rec. No.");
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

void DataRecordPropertyView::contextMenuEvent(QContextMenuEvent* event)
{
    QTableWidget::contextMenuEvent(event);
}
