/* 
 * DataSet.hpp 
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


#ifndef CHOX_DATASET_HPP
#define CHOX_DATASET_HPP

#include <vector>
#include <cstddef>

#include <QObject>
#include <QStringList>

#include "CDPL/Util/BitSet.hpp"

#include "DataRecord.hpp"


namespace ChOX
{

    class DataSet : public QObject
    {

        Q_OBJECT

      public:
        DataSet(QObject*);

        ~DataSet();

        int getSize() const;

        const DataRecord& getRecord(int index) const;

        const DataRecord::SharedPointer& getRecordPointer(int index) const;

        const QStringList& getFileNames() const;

        void setRecordSelected(int index, bool select = true);
        void selectRecordRange(int start, int end, bool select = true, bool xor_selection = false);
        void setRecordSelection(const CDPL::Util::BitSet& mask);
        
        bool isRecordSelected(int index) const;

        bool hasSelectedRecords() const;
        int  getNumSelectedRecords() const;

        template <typename InputIter>
        void appendRecords(InputIter begin, InputIter end, const QString& file_name)
        {
            workingState = states[currStateIdx];

            workingState.records.insert(workingState.records.end(), begin, end);
            workingState.selectionMask.resize(workingState.records.size());

            if (!file_name.isEmpty())
                workingState.fileNames.append(file_name);

            commitNewState();

            emit sizeChanged(int(states[currStateIdx].records.size()));

            if (!file_name.isEmpty())
                emit fileListChanged();
        }

        template <typename InputIter>
        void insertRecords(InputIter begin, InputIter end, int index, const QString& file_name)
        {
            workingState.records.clear();
            
            if (index > int(states[currStateIdx].records.size()))
                index = states[currStateIdx].records.size();
            else if (index < 0)
                index = 0;
            
            workingState.records.insert(workingState.records.end(), states[currStateIdx].records.begin(), states[currStateIdx].records.begin() + index);
            workingState.records.insert(workingState.records.end(), begin, end);
            workingState.records.insert(workingState.records.end(), states[currStateIdx].records.begin() + index, states[currStateIdx].records.end());

            workingState.selectionMask.resize(workingState.records.size());

            int num_ins_records = workingState.records.size() - states[currStateIdx].records.size();
            
            for (int i = 0; i < index; i++)
                workingState.selectionMask.set(i, states[currStateIdx].selectionMask.test(i));

            for (int i = index, end = index + num_ins_records; i < end; i++)
                workingState.selectionMask.set(i, false);
     
            for (int i = index; i < int(states[currStateIdx].records.size()); i++)
                workingState.selectionMask.set(i + num_ins_records, states[currStateIdx].selectionMask.test(i));
            
            workingState.fileNames = states[currStateIdx].fileNames;
            
            if (!file_name.isEmpty())
                workingState.fileNames.append(file_name);

            commitNewState();

            emit sizeChanged(int(states[currStateIdx].records.size()));

            if (!file_name.isEmpty())
                emit fileListChanged();
        }

        void appendRecords(const DataSet& other, const CDPL::Util::BitSet& mask);

        void removeRecords(const CDPL::Util::BitSet& mask);
        
      signals:
        void sizeChanged(int);
        void selectionStatusChanged(bool);
        void fileListChanged();

        void undoStatusChanged(bool);
        void redoStatusChanged(bool);

      public slots:
        void clear();
        void removeSelected();
        
        void undo();
        void redo();

        void selectAll();
        void unselectAll();
        void invertSelection();

      private:
        typedef std::vector<DataRecord::SharedPointer> DataRecordList;

        struct DataSetState
        {

            void swap(DataSetState&);

            QStringList        fileNames;
            DataRecordList     records;
            CDPL::Util::BitSet selectionMask;
        };

        typedef std::vector<DataSetState> DataSetStateList;

        void commitNewState();

        DataSetStateList states;
        DataSetState     workingState;
        std::size_t      currStateIdx;
        std::size_t      numSavedStates;
    };
} // namespace ChOX

#endif // CHOX_DATASET_HPP
