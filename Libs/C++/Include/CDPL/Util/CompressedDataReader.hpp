/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * CompressedDataReader.hpp 
 *
 * This file is part of the Chemical Data Processing Toolkit
 *
 * Copyright (C) 2003 Thomas Seidel <thomas.seidel@univie.ac.at>
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
 * \brief Definition of the class CDPL::Util::CompressedDataReader.
 */

#ifndef CDPL_UTIL_COMPRESSEDDATAREADER_HPP
#define CDPL_UTIL_COMPRESSEDDATAREADER_HPP

#include <iosfwd>

#include <boost/bind.hpp>

#include "CDPL/Base/DataReader.hpp"
#include "CDPL/Util/CompressionStreams.hpp"


namespace CDPL 
{

    namespace Util
    {

		/**
		 * \brief CompressedDataReader.
		 */
		template <typename ReaderImpl, typename DecompStream, typename DataType = typename ReaderImpl::DataType>
		class CompressedDataReader : public Base::DataReader<DataType>
		{

		public:
			CompressedDataReader(std::istream& is); 

			CompressedDataReader& read(DataType& obj, bool overwrite = true);
			CompressedDataReader& read(std::size_t idx, DataType& obj, bool overwrite = true);

			CompressedDataReader& skip();

			bool hasMoreData();

			std::size_t getRecordIndex() const;
			void setRecordIndex(std::size_t idx);

			std::size_t getNumRecords();

			operator const void*() const;
			bool operator!() const;

			void close();
		
		private:
			DecompStream  stream;
			ReaderImpl    reader;
		};
    }
}


// Implementation

template <typename ReaderImpl, typename DecompStream, typename DataType>
CDPL::Util::CompressedDataReader<ReaderImpl, DecompStream, DataType>::CompressedDataReader(std::istream& is): 
    stream(is), reader(stream) 
{
    reader.setParent(this);
	reader.registerIOCallback(boost::bind(&Base::DataIOBase::invokeIOCallbacks, this, _2));
}

template <typename ReaderImpl, typename DecompStream, typename DataType>
CDPL::Util::CompressedDataReader<ReaderImpl, DecompStream, DataType>&
CDPL::Util::CompressedDataReader<ReaderImpl, DecompStream, DataType>::read(DataType& obj, bool overwrite)
{
    reader.read(obj, overwrite);

    return *this;
}

template <typename ReaderImpl, typename DecompStream, typename DataType>
CDPL::Util::CompressedDataReader<ReaderImpl, DecompStream, DataType>&
CDPL::Util::CompressedDataReader<ReaderImpl, DecompStream, DataType>::read(std::size_t idx, DataType& obj, bool overwrite)
{
    reader.read(idx, obj, overwrite);

    return *this;
}

template <typename ReaderImpl, typename DecompStream, typename DataType>
CDPL::Util::CompressedDataReader<ReaderImpl, DecompStream, DataType>&
CDPL::Util::CompressedDataReader<ReaderImpl, DecompStream, DataType>::skip()
{
    reader.skip();

    return *this;
}

template <typename ReaderImpl, typename DecompStream, typename DataType>
bool CDPL::Util::CompressedDataReader<ReaderImpl, DecompStream, DataType>::hasMoreData()
{
    return reader.hasMoreData();
}

template <typename ReaderImpl, typename DecompStream, typename DataType>
std::size_t CDPL::Util::CompressedDataReader<ReaderImpl, DecompStream, DataType>::getRecordIndex() const
{	
    return reader.getRecordIndex();
}

template <typename ReaderImpl, typename DecompStream, typename DataType>
void CDPL::Util::CompressedDataReader<ReaderImpl, DecompStream, DataType>::setRecordIndex(std::size_t idx)
{
    reader.setRecordIndex(idx);
}

template <typename ReaderImpl, typename DecompStream, typename DataType>
std::size_t CDPL::Util::CompressedDataReader<ReaderImpl, DecompStream, DataType>::getNumRecords()
{
    return reader.getNumRecords();
}

template <typename ReaderImpl, typename DecompStream, typename DataType>
CDPL::Util::CompressedDataReader<ReaderImpl, DecompStream, DataType>::operator const void*() const
{
    return reader.operator const void*();
}

template <typename ReaderImpl, typename DecompStream, typename DataType>
bool CDPL::Util::CompressedDataReader<ReaderImpl, DecompStream, DataType>::operator!() const
{
    return reader.operator!();
}

template <typename ReaderImpl, typename DecompStream, typename DataType>
void CDPL::Util::CompressedDataReader<ReaderImpl, DecompStream, DataType>::close()
{
    reader.close();
	stream.close();
}

#endif // CDPL_UTIL_COMPRESSEDDATAREADER_HPP
