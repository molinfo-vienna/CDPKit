/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * CompoundDataReader.hpp 
 *
 * This file is part of the Chemical Data Processing Toolkit
 *
 * Copyright (C) 2003-2020 Thomas A. Seidel <thomas.seidel@univie.ac.at>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this library; see the file COPYING. If not, write to
 * the Free Software Foundation, Inc., 59 Temple Place - Suite 330,
 * Boston, MA 02111-1307, USA.
 */

/**
 * \file
 * \brief Definition of the class CDPL::Util::CompoundDataReader.
 */

#ifndef CDPL_UTIL_COMPOUNDDATAREADER_HPP
#define CDPL_UTIL_COMPOUNDDATAREADER_HPP

#include <vector>
#include <algorithm>

#ifndef BOOST_BIND_GLOBAL_PLACEHOLDERS
# define BOOST_BIND_GLOBAL_PLACEHOLDERS
#endif

#include <boost/bind.hpp>

#include "CDPL/Base/DataReader.hpp"
#include "CDPL/Base/Exceptions.hpp"


namespace CDPL 
{

    namespace Util
    {

		/**
		 * \brief CompoundDataReader.
		 */
		template <typename DataType>
		class CompoundDataReader : public Base::DataReader<DataType>
		{

		public:
			typedef boost::shared_ptr<CompoundDataReader> SharedPointer;

			typedef Base::DataReader<DataType> ReaderType;
			typedef typename ReaderType::SharedPointer ReaderPointer;

			CompoundDataReader(); 

			~CompoundDataReader(); 

			void addReader(const ReaderPointer& reader);

			void removeReader(std::size_t idx);

			std::size_t getNumReaders();

			void clear();

			std::size_t getReaderIDForRecordIndex(std::size_t idx) const;

			const ReaderPointer& getReader(std::size_t idx) const;

			CompoundDataReader& read(DataType& obj, bool overwrite = true);
			CompoundDataReader& read(std::size_t idx, DataType& obj, bool overwrite = true);

			CompoundDataReader& skip();

			bool hasMoreData();

			std::size_t getRecordIndex() const;
			void setRecordIndex(std::size_t idx);

			std::size_t getNumRecords();

			operator const void*() const;
			bool operator!() const;

		private:
			ReaderType* getReaderForRecordIndex(std::size_t& idx) const;

			typedef std::vector<ReaderPointer> ReaderArray;
			typedef std::vector<std::size_t> RecordIndexArray;

			ReaderArray        readers;
			bool               state;
			RecordIndexArray   recordIdxBounds;
			std::size_t        recordIdx;
			std::size_t        numRecords;
		};
    }
}


// Implementation

template <typename DataType>
CDPL::Util::CompoundDataReader<DataType>::CompoundDataReader(): 
    state(false), recordIdx(0), numRecords(0) 
{}

template <typename DataType>
CDPL::Util::CompoundDataReader<DataType>::~CompoundDataReader()
{
	clear();
}

template <typename DataType>
void CDPL::Util::CompoundDataReader<DataType>::clear()
{
	std::for_each(readers.begin(), readers.end(),
				  boost::bind(&ReaderType::setParent, _1, static_cast<CompoundDataReader*>(0)));

	readers.clear();
	recordIdxBounds.clear();

	numRecords = 0;
	state = false;
	recordIdx = 0;
}

template <typename DataType>
void CDPL::Util::CompoundDataReader<DataType>::addReader(const ReaderPointer& reader)
{
	readers.reserve(readers.size() + 1);
	recordIdxBounds.reserve(readers.size() + 1);

	reader->setParent(this);

	std::size_t num_recs = reader->getNumRecords();

	readers.push_back(reader);
	numRecords += num_recs;
	recordIdxBounds.push_back(numRecords);

	state |= static_cast<bool>(reader->operator const void*());
}

template <typename DataType>
void CDPL::Util::CompoundDataReader<DataType>::removeReader(std::size_t idx)
{
	if (idx >= readers.size())
		throw Base::IndexError("CompoundDataReader: reader index out of bounds");

	std::size_t num_lost_records = readers[idx]->getNumRecords();

	readers[idx]->setParent(0);

	readers.erase(readers.begin() + idx);
	recordIdxBounds.erase(recordIdxBounds.begin() + idx);

	for ( ; idx < readers.size(); idx++)
		recordIdxBounds[idx] -= num_lost_records;

	numRecords -= num_lost_records;
}

template <typename DataType>
std::size_t CDPL::Util::CompoundDataReader<DataType>::getNumReaders()
{
	return readers.size();
}

template <typename DataType>
const typename CDPL::Util::CompoundDataReader<DataType>::ReaderPointer&
CDPL::Util::CompoundDataReader<DataType>::getReader(std::size_t idx) const
{
	if (idx >= readers.size())
		throw Base::IndexError("CompoundDataReader: reader index out of bounds");

	return readers[idx];
}

template <typename DataType>
CDPL::Util::CompoundDataReader<DataType>&
CDPL::Util::CompoundDataReader<DataType>::read(DataType& obj, bool overwrite)
{
	state = false;
	
	std::size_t idx = recordIdx;
	ReaderType* reader = getReaderForRecordIndex(idx);

	if (reader && (state = reader->read(idx, obj, overwrite))) {
		recordIdx++;
		this->invokeIOCallbacks(1.0);
	}

    return *this;
}

template <typename DataType>
CDPL::Util::CompoundDataReader<DataType>&
CDPL::Util::CompoundDataReader<DataType>::read(std::size_t idx, DataType& obj, bool overwrite)
{
 	setRecordIndex(idx);

    return read(obj, overwrite);
}

template <typename DataType>
CDPL::Util::CompoundDataReader<DataType>&
CDPL::Util::CompoundDataReader<DataType>::skip()
{
 	state = false;
	
	if (recordIdx >= numRecords)
		return *this;

	recordIdx++;
	state = true;

	this->invokeIOCallbacks(1.0);

    return *this;
}

template <typename DataType>
bool CDPL::Util::CompoundDataReader<DataType>::hasMoreData()
{
	return (recordIdx < numRecords);
}

template <typename DataType>
std::size_t CDPL::Util::CompoundDataReader<DataType>::getRecordIndex() const
{	
	return recordIdx;
}

template <typename DataType>
void CDPL::Util::CompoundDataReader<DataType>::setRecordIndex(std::size_t idx)
{
	if (idx >= numRecords)
		throw Base::IndexError("CompoundDataReader: record index out of bounds");

	recordIdx = idx;
}

template <typename DataType>
std::size_t CDPL::Util::CompoundDataReader<DataType>::getNumRecords()
{
	return numRecords;
}

template <typename DataType>
CDPL::Util::CompoundDataReader<DataType>::operator const void*() const
{
    return (state ? this : 0);
}

template <typename DataType>
bool CDPL::Util::CompoundDataReader<DataType>::operator!() const
{
    return !state;
}

template <typename DataType>
std::size_t CDPL::Util::CompoundDataReader<DataType>::getReaderIDForRecordIndex(std::size_t idx) const
{
	for (std::size_t i = 0; i < readers.size(); i++) {
		if (idx < recordIdxBounds[i])
			return (i + 1);
	}

	return 0;
}

template <typename DataType>
typename CDPL::Util::CompoundDataReader<DataType>::ReaderType* 
CDPL::Util::CompoundDataReader<DataType>::getReaderForRecordIndex(std::size_t& idx) const
{
	for (std::size_t i = 0; i < readers.size(); i++) {
		if (idx < recordIdxBounds[i]) {
			idx -= (i == 0 ? std::size_t(0) : recordIdxBounds[i - 1]);
			return readers[i].get();
		}
	}

	return 0;
}

#endif // CDPL_UTIL_COMPOUNDDATAREADER_HPP
