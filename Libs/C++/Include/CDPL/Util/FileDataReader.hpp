/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * FileDataReader.hpp 
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
 * \brief Definition of the class CDPL::Util::FileDataReader.
 */

#ifndef CDPL_UTIL_FILEDATAREADER_HPP
#define CDPL_UTIL_FILEDATAREADER_HPP

#include <fstream>
#include <string>

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
		 * \brief FileDataReader.
		 */
		template <typename ReaderImpl, typename DataType = typename ReaderImpl::DataType>
		class FileDataReader : public Base::DataReader<DataType>
		{

		public:
			FileDataReader(const std::string& file_name, 
						   std::ios_base::openmode mode = std::ios_base::in | std::ios_base::binary); 

			FileDataReader& read(DataType& obj, bool overwrite = true);
			FileDataReader& read(std::size_t idx, DataType& obj, bool overwrite = true);

			FileDataReader& skip();

			bool hasMoreData();

			std::size_t getRecordIndex() const;
			void setRecordIndex(std::size_t idx);

			std::size_t getNumRecords();

			operator const void*() const;
			bool operator!() const;

			void close();

		private:
			std::ifstream stream;
			std::string   fileName;
			ReaderImpl    reader;
		};
    }
}


// Implementation

template <typename ReaderImpl, typename DataType>
CDPL::Util::FileDataReader<ReaderImpl, DataType>::FileDataReader(const std::string& file_name, std::ios_base::openmode mode): 
    stream(file_name.c_str(), mode), fileName(file_name), reader(stream) 
{
    reader.setParent(this);
	reader.registerIOCallback(boost::bind(&Base::DataIOBase::invokeIOCallbacks, this, _2));
}

template <typename ReaderImpl, typename DataType>
CDPL::Util::FileDataReader<ReaderImpl, DataType>&
CDPL::Util::FileDataReader<ReaderImpl, DataType>::read(DataType& obj, bool overwrite)
{
	try {
		reader.read(obj, overwrite);

	} catch (const std::exception& e) {
		throw Base::IOError("FileDataReader: while reading file '" + fileName + "': " + e.what());
	}

    return *this;
}

template <typename ReaderImpl, typename DataType>
CDPL::Util::FileDataReader<ReaderImpl, DataType>&
CDPL::Util::FileDataReader<ReaderImpl, DataType>::read(std::size_t idx, DataType& obj, bool overwrite)
{
	try {
		reader.read(idx, obj, overwrite);

	} catch (const std::exception& e) {
		throw Base::IOError("FileDataReader: while reading file '" + fileName + "': " + e.what());
	}

    return *this;
}

template <typename ReaderImpl, typename DataType>
CDPL::Util::FileDataReader<ReaderImpl, DataType>&
CDPL::Util::FileDataReader<ReaderImpl, DataType>::skip()
{
	try {
		reader.skip();

	} catch (const std::exception& e) {
		throw Base::IOError("FileDataReader: while reading file '" + fileName + "': " + e.what());
	}

    return *this;
}

template <typename ReaderImpl, typename DataType>
bool CDPL::Util::FileDataReader<ReaderImpl, DataType>::hasMoreData()
{
    return reader.hasMoreData();
}

template <typename ReaderImpl, typename DataType>
std::size_t CDPL::Util::FileDataReader<ReaderImpl, DataType>::getRecordIndex() const
{	
    return reader.getRecordIndex();
}

template <typename ReaderImpl, typename DataType>
void CDPL::Util::FileDataReader<ReaderImpl, DataType>::setRecordIndex(std::size_t idx)
{
    reader.setRecordIndex(idx);
}

template <typename ReaderImpl, typename DataType>
std::size_t CDPL::Util::FileDataReader<ReaderImpl, DataType>::getNumRecords()
{
    return reader.getNumRecords();
}

template <typename ReaderImpl, typename DataType>
CDPL::Util::FileDataReader<ReaderImpl, DataType>::operator const void*() const
{
    return reader.operator const void*();
}

template <typename ReaderImpl, typename DataType>
bool CDPL::Util::FileDataReader<ReaderImpl, DataType>::operator!() const
{
    return reader.operator!();
}

template <typename ReaderImpl, typename DataType>
void CDPL::Util::FileDataReader<ReaderImpl, DataType>::close()
{
	reader.close();
    stream.close();
}

#endif // CDPL_UTIL_FILEDATAREADER_HPP
