/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * DataSet.cpp 
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


#include <algorithm>

#include "DataSet.hpp"


using namespace ChOX;


namespace
{

	const std::size_t MAX_NUM_SAVED_STATES = 10;
}


DataSet::DataSet(QObject* parent): 
	QObject(parent), states(MAX_NUM_SAVED_STATES), currStateIdx(0), numSavedStates(1) {}

DataSet::~DataSet() {}

int DataSet::getSize() const
{
	return int(states[currStateIdx].records.size());
}

const DataRecord& DataSet::getRecord(int index) const
{
	return *states[currStateIdx].records.at(index);
}

const QStringList& DataSet::getFileNames() const
{
	return states[currStateIdx].fileNames;
}

bool DataSet::isRecordSelected(int index) const
{
	return states[currStateIdx].selectionMask.test(index);
}

bool DataSet::hasSelectedRecords() const
{
	return states[currStateIdx].selectionMask.any();
}

int DataSet::getNumSelectedRecords() const
{
	return int(states[currStateIdx].selectionMask.count());
}

void DataSet::setRecordSelected(int index, bool select)
{
	if (states[currStateIdx].selectionMask.test(index) == select) 
		return;

	workingState = states[currStateIdx];

	workingState.selectionMask.set(index, select);

	commitNewState();

	if (select)
		emit selectionStatusChanged(true);
	else
		emit selectionStatusChanged(states[currStateIdx].selectionMask.any());
}

void DataSet::selectRecordRange(int start, int end, bool select, bool xor_selection)
{
	if (states[currStateIdx].records.empty())
		return;

	if (!xor_selection && !select && !states[currStateIdx].selectionMask.any()) 
		return;

	if (end < start)
		std::swap(end, start);

	start = std::max(0, start);
	end = std::max(0, end);

	workingState = states[currStateIdx];

	start = std::min(int(workingState.records.size()) - 1, start);
	end = std::min(int(workingState.records.size()) - 1, end);

	for (int i = start; i <= end; i++) {
		if (!xor_selection)
			workingState.selectionMask.set(i, select);
		else
			workingState.selectionMask.set(i, !workingState.selectionMask.test(i));
	}

	commitNewState();

	if (select)
		emit selectionStatusChanged(states[currStateIdx].records.empty() ? false : true);
	else
		emit selectionStatusChanged(states[currStateIdx].selectionMask.any());
}

void DataSet::selectAll()
{
	workingState = states[currStateIdx];

	workingState.selectionMask.set();

	commitNewState();

	emit selectionStatusChanged(states[currStateIdx].records.empty() ? false : true);
}

void DataSet::unselectAll()
{
	if (!states[currStateIdx].selectionMask.any())
		return;

	workingState = states[currStateIdx];

	workingState.selectionMask.reset();

	commitNewState();

	emit selectionStatusChanged(false);
}

void DataSet::invertSelection()
{
	workingState = states[currStateIdx];

	workingState.selectionMask.flip();

	commitNewState();

	emit selectionStatusChanged(states[currStateIdx].selectionMask.any());
}

void DataSet::removeSelected()
{
	const DataSetState& curr_state = states[currStateIdx];

	if (!curr_state.selectionMask.any())
		return;

	workingState.records.clear();

	workingState.selectionMask.resize(curr_state.selectionMask.size());
	workingState.selectionMask.reset();

	workingState.fileNames = curr_state.fileNames;

	std::size_t num_records = curr_state.records.size();

	for (std::size_t i = 0; i < num_records; i++) {
		if (curr_state.selectionMask.test(i))
			continue;

		workingState.records.push_back(curr_state.records[i]);
	}

	commitNewState();

	emit sizeChanged(int(states[currStateIdx].records.size()));
	emit selectionStatusChanged(false);
}

void DataSet::clear()
{
	if (states[currStateIdx].fileNames.empty())
		return;

	workingState.records.clear();
	workingState.fileNames.clear();
	workingState.selectionMask.clear();

	commitNewState();

	emit sizeChanged(0);
	emit selectionStatusChanged(false);
	emit fileListChanged();
}

void DataSet::undo()
{
	if (currStateIdx == 0)
		return;

	emit undoStatusChanged(--currStateIdx > 0);
	emit redoStatusChanged(true);

	emit sizeChanged(int(states[currStateIdx].records.size()));
	emit selectionStatusChanged(states[currStateIdx].selectionMask.any());
	emit fileListChanged();
}

void DataSet::redo()
{
	if (currStateIdx == numSavedStates - 1)
		return;

	emit undoStatusChanged(true);
	emit redoStatusChanged(++currStateIdx < numSavedStates - 1);	

	emit sizeChanged(int(states[currStateIdx].records.size()));
	emit selectionStatusChanged(states[currStateIdx].selectionMask.any());
	emit fileListChanged();
}

void DataSet::commitNewState()
{
	if (currStateIdx == MAX_NUM_SAVED_STATES - 1) {
		for (std::size_t i = 0; i < MAX_NUM_SAVED_STATES - 1; i++)
			states[i].swap(states[i + 1]);

		workingState.swap(states[currStateIdx]);
	
	} else {
		workingState.swap(states[++currStateIdx]);
	
		numSavedStates = currStateIdx + 1;
	}

	emit undoStatusChanged(true);
	emit redoStatusChanged(false);	
}

void DataSet::DataSetState::swap(DataSetState& other)
{
	std::swap(fileNames, other.fileNames);
	std::swap(records, other.records);
	std::swap(selectionMask, other.selectionMask);
}
