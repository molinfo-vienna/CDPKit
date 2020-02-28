/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * StreamDataReader.hpp 
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
 * \brief Definition of the class CDPL::Util::StreamDataReader.
 */

#ifndef CDPL_UTIL_STREAMDATAREADER_HPP
#define CDPL_UTIL_STREAMDATAREADER_HPP

#include <istream>
#include <vector>

#include "CDPL/Base/DataReader.hpp"
#include "CDPL/Base/Exceptions.hpp"


namespace CDPL 
{

	namespace Util
	{

		/**
		 * \addtogroup CDPL_UTIL_MISCELLANEOUS
		 * @{
		 */

		/**
		 * \brief A helper class that implements Base::DataReader for \c std::istream based data readers.
		 *
		 * \c %StreamDataReader implements common operations for readers which retrieve the input data
		 * from a \c std::istream instance. However, since \c %StreamDataReader does not know anything
		 * about the underlying storage format, the actual decoding of a data object record has to be 
		 * implemented by a class which has enough knowledge to deal with the given data format.
		 * \c %StreamDataReader is designed to be used as a base class and requires the derived class
		 * (whose type has to be specified as the second template parameter \a ReaderImpl) to provide
		 * three methods which perform the actual data decoding.
		 *
		 * These methods must have the following signatures and semantics:
		 *  - \c bool \c readData(std::istream& is, DataType& obj, bool overwrite) \n
		 *   Reads the next data record from the input stream \a is into the data object \a obj of
		 *   type \c DataType. Returns \c true if the read operation was successful, and \c false
		 *   if the end of input has already been reached.
		 *  - \c bool \c skipData(std::istream& is) \n
		 *   Skips the next data record. Returns \c true if the operation was successful, and
		 *   \c false if the end of input has already been reached.
		 *  - \c bool \c moreData(std::istream& is) \n
		 *   Tells if more data records are available to read. Returns \c true if data records are available,
		 *   and \c false otherwise.
		 *
		 * \tparam DataType The type of the objects holding the read data.
		 * \tparam ReaderImpl The type of the subclass implementing the basic input operations.
		 */
		template <typename DataType, typename ReaderImpl>
		class StreamDataReader : public Base::DataReader<DataType>
		{

		public:
			Base::DataReader<DataType>& read(DataType& obj, bool overwrite = true);
			Base::DataReader<DataType>& read(std::size_t idx, DataType& obj, bool overwrite = true);

			Base::DataReader<DataType>& skip();

			bool hasMoreData();

			std::size_t getRecordIndex() const;
			void setRecordIndex(std::size_t idx);

			std::size_t getNumRecords();

			operator const void*() const;
			bool operator!() const;

		protected:
			/**
			 * \brief Constructs a \c %StreamDataReader instance that will read from the input stream \a is.
			 * \param is The input stream to read from.
			 */
			StreamDataReader(std::istream& is): 
				input(is), recordIndex(0), initStreamPos(is.tellg()), state(is.good()), streamScanned(false) {} 

		private:
			StreamDataReader(const StreamDataReader& reader); 

			StreamDataReader& operator=(const StreamDataReader& reader);

			void scanDataStream();

			typedef std::vector<std::istream::pos_type> RecordStreamPosTable;

			std::istream&          input;
			std::size_t            recordIndex;
			std::istream::pos_type initStreamPos;
			bool                   state;
			bool                   streamScanned;
			RecordStreamPosTable   recordPositions;
		};

		/**
		 * @}
		 */
	}
}


// Implementation

template <typename DataType, typename ReaderImpl>
CDPL::Base::DataReader<DataType>&
CDPL::Util::StreamDataReader<DataType, ReaderImpl>::read(DataType& obj, bool overwrite)
{
	state = false;

	if ((state = static_cast<ReaderImpl*>(this)->readData(input, obj, overwrite))) {
		recordIndex++;
		this->invokeIOCallbacks(1.0);
	}

	return *this;
}

template <typename DataType, typename ReaderImpl>
CDPL::Base::DataReader<DataType>&
CDPL::Util::StreamDataReader<DataType, ReaderImpl>::read(std::size_t idx, DataType& obj, bool overwrite)
{
	setRecordIndex(idx);

	return read(obj, overwrite);
}

template <typename DataType, typename ReaderImpl>
CDPL::Base::DataReader<DataType>&
CDPL::Util::StreamDataReader<DataType, ReaderImpl>::skip()
{
	state = false;

	if ((state = static_cast<ReaderImpl*>(this)->skipData(input))) {
		recordIndex++;
		this->invokeIOCallbacks(1.0);
	}

	return *this;
}

template <typename DataType, typename ReaderImpl>
bool CDPL::Util::StreamDataReader<DataType, ReaderImpl>::hasMoreData()
{
	return static_cast<ReaderImpl*>(this)->moreData(input);
}

template <typename DataType, typename ReaderImpl>
std::size_t CDPL::Util::StreamDataReader<DataType, ReaderImpl>::getRecordIndex() const
{	
	return recordIndex;
}

template <typename DataType, typename ReaderImpl>
void CDPL::Util::StreamDataReader<DataType, ReaderImpl>::setRecordIndex(std::size_t idx)
{
	scanDataStream();

	if (idx >= recordPositions.size())
		throw Base::IndexError("StreamDataReader: record index out of bounds");

	input.clear();
	input.seekg(recordPositions[idx]);

	recordIndex = idx;
}

template <typename DataType, typename ReaderImpl>
std::size_t CDPL::Util::StreamDataReader<DataType, ReaderImpl>::getNumRecords()
{
	scanDataStream();

	return recordPositions.size();
}

template <typename DataType, typename ReaderImpl>
CDPL::Util::StreamDataReader<DataType, ReaderImpl>::operator const void*() const
{
	return (state ? this : 0);
}

template <typename DataType, typename ReaderImpl>
bool CDPL::Util::StreamDataReader<DataType, ReaderImpl>::operator!() const
{
	return !state;
}

template <typename DataType, typename ReaderImpl>
void CDPL::Util::StreamDataReader<DataType, ReaderImpl>::scanDataStream()
{
	if (streamScanned)
		return;

	streamScanned = true;

	std::size_t saved_rec_index = recordIndex;

	recordIndex = 0;

	input.clear();
	input.seekg(0, std::ios_base::end);

	std::istream::pos_type end_pos = input.tellg();

	input.seekg(initStreamPos);

	while (hasMoreData()) {
		std::istream::pos_type record_pos = input.tellg();
		state = false;

		if (!(state = static_cast<ReaderImpl*>(this)->skipData(input)))
			break;
 
		recordPositions.push_back(record_pos);
		recordIndex++;

		this->invokeIOCallbacks(record_pos / double(end_pos));
	}

	this->invokeIOCallbacks(1.0);

	if (saved_rec_index < recordPositions.size()) {
		recordIndex = saved_rec_index;

		input.clear();
		input.seekg(recordPositions[recordIndex]);
	}
}

#endif // CDPL_UTIL_STREAMDATAREADER_HPP
