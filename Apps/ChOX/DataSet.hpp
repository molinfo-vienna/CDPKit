/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

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

		const DataRecord& getRecord(int) const;

		const QStringList& getFileNames() const;

		void setRecordSelected(int, bool = true);
		void selectRecordRange(int, int, bool = true, bool = false);

		bool isRecordSelected(int) const;

		bool hasSelectedRecords() const;
		int getNumSelectedRecords() const;

		template <typename InputIter>
		void appendRecords(InputIter begin, InputIter end, const QString& file_name) {
			workingState = states[currStateIdx];

			workingState.records.insert(workingState.records.end(), begin, end);
			workingState.selectionMask.resize(workingState.records.size());

			workingState.fileNames.append(file_name);

			commitNewState();

			emit sizeChanged(int(states[currStateIdx].records.size()));
			emit fileListChanged();
		}

	signals:	
		void sizeChanged(int);
		void selectionStatusChanged(bool);
		void fileListChanged();

		void undoStatusChanged(bool);
		void redoStatusChanged(bool);

	public slots:
		void clear();

		void undo();
		void redo();

		void selectAll();
		void unselectAll();
		void invertSelection();
		void removeSelected();

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
}

#endif // CHOX_DATASET_HPP
