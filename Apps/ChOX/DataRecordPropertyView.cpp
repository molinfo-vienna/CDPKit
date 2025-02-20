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
#include <QFontMetrics>
#include <QMenu>
#include <QContextMenuEvent>

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

        for (auto& p : colVisActionToIndexMap)
            contextMenu->removeAction(p.first);

        colVisActionToIndexMap.clear();
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

            auto action = new QAction("#", contextMenu);

            action->setCheckable(true);
            contextMenu->addAction(action);
            
            colVisActionToIndexMap[action] = 0;
        }
        
        setItem(i, 0, new TableItem(this, QString::number(page_view.getPageOffset() + i + 1)));
                
        if (!propData[i])
            continue;
        
        for (auto& item : *propData[i]) {
            auto it = propColIndices.find(item.getHeader());

            if (it != propColIndices.end()) {
                setItem(i, it->second, new TableItem(this, QString::fromStdString(item.getData())));
                continue;
            }

            propColIndices[item.getHeader()] = colHeaders.count();

            setColumnCount(colHeaders.count() + 1);
            setItem(i, colHeaders.count(), new TableItem(this, QString::fromStdString(item.getData())));

            auto header = QString::fromStdString(item.getHeader()).trimmed();

            if ((header.length() > 2) && (header.front() == '<') && (header.back() == '>')) {
                header.chop(1);
                header.remove(0, 1);
            }

            auto action = new QAction(header, contextMenu);

            action->setCheckable(true);
            contextMenu->addAction(action);
            
            colVisActionToIndexMap[action] = colHeaders.count();

            colHeaders << header;
        }
    }

    auto num_cols = colHeaders.count();
    
    if (num_cols != old_num_cols) {
        setHorizontalHeaderLabels(colHeaders);

        if (old_num_cols == 0) {
            auto max_width = QFontMetrics(item(0, 0)->font(), this).
                horizontalAdvance("0" + QString::number(page_view.getDataSet().getSize() + 1) + "0");

            horizontalHeader()->resizeSection(0, max_width);
        }
    }

    for (std::size_t i = 0; i < num_rows; i++)
        for (int j = 0; j < num_cols; j++)
            if (!item(i, j))
                setItem(i, j, new TableItem(this, QString()));

    numColumns.resize(num_cols);
    
    for (int i = 0; i < num_cols; i++) {
        bool is_num_col = true;

        for (std::size_t j = 0; j < num_rows; j++) {
            auto text = item(j, i)->text();

            if (text.isEmpty())
                continue;

            text.toDouble(&is_num_col);

            if (!is_num_col)
                break;
        }
        
        numColumns.set(i, is_num_col);
    }
    
    setSortingEnabled(true);
}

void DataRecordPropertyView::hideAllColumns()
{
    for (int i = 0, count = horizontalHeader()->count(); i < count; i++)
        setColumnHidden(i, true);
}

void DataRecordPropertyView::showAllColumns()
{
    for (int i = 0, count = horizontalHeader()->count(); i < count; i++)
        setColumnHidden(i, false);
}

void DataRecordPropertyView::contextMenuRequested(const QPoint& pos)
{
   if (colVisActionToIndexMap.empty())
       return;

   for (auto& p : colVisActionToIndexMap)
       p.first->setChecked(!isColumnHidden(p.second));
   
   contextMenu->popup(mapToGlobal(pos));
}

void DataRecordPropertyView::colVisActionTriggered(QAction* action)
{
    auto it = colVisActionToIndexMap.find(action);

    if (it == colVisActionToIndexMap.end())
        return;

    setColumnHidden(it->second, !it->first->isChecked());
}

void DataRecordPropertyView::init()
{
    setContextMenuPolicy(Qt::CustomContextMenu);
    setSelectionMode(NoSelection);
    setEditTriggers(NoEditTriggers);
    setFrameStyle(StyledPanel);
    
    verticalHeader()->hide();
    horizontalHeader()->setContextMenuPolicy(Qt::CustomContextMenu);
    
    // ----------
    
    contextMenu = new QMenu(this);

    connect(contextMenu, SIGNAL(triggered(QAction*)), this, SLOT(colVisActionTriggered(QAction*)));
    
    auto action = new QAction(tr("&Hide All"), contextMenu);

    connect(action, SIGNAL(triggered()), this, SLOT(hideAllColumns()));
    
    contextMenu->addAction(action);

    action = new QAction(tr("&Show All"), contextMenu);

    connect(action, SIGNAL(triggered()), this, SLOT(showAllColumns()));
    
    contextMenu->addAction(action);
    contextMenu->addSeparator();
    
    // ----------

    connect(this, SIGNAL(customContextMenuRequested(const QPoint&)), this, SLOT(contextMenuRequested(const QPoint&)));
    connect(horizontalHeader(), SIGNAL(customContextMenuRequested(const QPoint&)), this, SLOT(contextMenuRequested(const QPoint&)));
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

// ----

DataRecordPropertyView::TableItem::TableItem(const DataRecordPropertyView* parent, const QString& value):
    QTableWidgetItem(value), parent(parent)
{}

bool DataRecordPropertyView::TableItem::operator<(const QTableWidgetItem& rhs) const
{
    if (!parent->numColumns.test(column()))
        return QTableWidgetItem::operator<(rhs);

    auto lhs_text = text();
    auto lhs_val = (lhs_text.isEmpty() ? 0.0 : lhs_text.toDouble());
    auto rhs_text = rhs.text();
    auto rhs_val = (rhs_text.isEmpty() ? 0.0 : rhs_text.toDouble());

    return (lhs_val < rhs_val);
}
