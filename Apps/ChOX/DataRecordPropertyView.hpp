/* 
 * DataRecordPropertyView.hpp 
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


#ifndef CHOX_DATARECORDPROPERTYVIEW_HPP
#define CHOX_DATARECORDPROPERTYVIEW_HPP

#include <vector>
#include <unordered_map>

#include <QTableWidget>
#include <QStringList>

#include "CDPL/Chem/StringDataBlock.hpp"

#include "RecordDataVisitor.hpp"


namespace ChOX
{

    class DataSetPageView;
    class Settings;

    class DataRecordPropertyView : public QTableWidget, public RecordDataVisitor
    {

        Q_OBJECT

      public:
        DataRecordPropertyView(QWidget* parent);

        void update(DataSetPageView& page_view);
        
      private:
        void init();
        
        void visit(CDPL::Chem::Reaction& rxn);
        void visit(CDPL::Chem::Molecule& mol);

        void contextMenuEvent(QContextMenuEvent* event);
    
        typedef std::vector<CDPL::Chem::StringDataBlock::SharedPointer> PropertyData;
        typedef std::unordered_map<std::string, int>                    NameToIndexMap;

        PropertyData   propData;
        NameToIndexMap propColIndices;
        QStringList    colHeaders;
        QStringList    rowHeaders;
    };
} // namespace ChOX

#endif // CHOX_DATARECORDPROPERTYVIEW_HPP
