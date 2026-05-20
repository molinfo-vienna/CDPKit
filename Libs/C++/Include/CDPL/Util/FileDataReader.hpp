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
 * \brief Definition of class CDPL::Util::FileDataReader.
 */

#ifndef CDPL_UTIL_FILEDATAREADER_HPP
#define CDPL_UTIL_FILEDATAREADER_HPP

#include <fstream>
#include <string>
#include <functional>

#include "CDPL/Base/DataReader.hpp"
#include "CDPL/Base/Exceptions.hpp"


namespace CDPL
{

    namespace Util
    {

        /**
         * \brief Convenience wrapper that adapts a stream-based reader implementation \a ReaderImpl into a file-based
         *        Base::DataReader by opening an \c std::ifstream and forwarding all read operations to the wrapped reader.
         *
         * \tparam ReaderImpl The underlying stream-based reader implementation type.
         * \tparam DataType The data type read by \a ReaderImpl.
         */
        template <typename ReaderImpl, typename DataType = typename ReaderImpl::DataType>
        class FileDataReader : public Base::DataReader<DataType>
        {

          public:
            /**
             * \brief Constructs a \c %FileDataReader instance that opens the file \a file_name in the given mode and
             *        forwards all read operations to a freshly constructed \a ReaderImpl wrapping the file stream.
             * \param file_name The path of the input file to open.
             * \param mode The open mode of the underlying \c std::ifstream.
             * \throw Base::IOError if the file could not be opened.
             */
            FileDataReader(const std::string&      file_name,
                           std::ios_base::openmode mode = std::ios_base::in | std::ios_base::binary);

            /**
             * \brief Reads the next record into \a obj via the wrapped reader.
             * \param obj The output object.
             * \param overwrite If \c true, the output object is cleared before the record is copied into it.
             * \return A reference to itself.
             * \throw Base::IOError on read failure.
             */
            FileDataReader& read(DataType& obj, bool overwrite = true);

            /**
             * \brief Reads the record at index \a idx into \a obj via the wrapped reader.
             * \param idx The zero-based record index.
             * \param obj The output object.
             * \param overwrite If \c true, the output object is cleared before the record is copied into it.
             * \return A reference to itself.
             * \throw Base::IOError on read failure.
             */
            FileDataReader& read(std::size_t idx, DataType& obj, bool overwrite = true);

            /**
             * \brief Skips the next record via the wrapped reader.
             * \return A reference to itself.
             * \throw Base::IOError on read failure.
             */
            FileDataReader& skip();

            /**
             * \brief Tells whether the wrapped reader has more records to read.
             * \return \c true if at least one more record is available, and \c false otherwise.
             */
            bool hasMoreData();

            /**
             * \brief Returns the current record index of the wrapped reader.
             * \return The zero-based record index of the next record to read.
             */
            std::size_t getRecordIndex() const;

            /**
             * \brief Sets the current record index of the wrapped reader.
             * \param idx The new zero-based record index.
             */
            void setRecordIndex(std::size_t idx);

            /**
             * \brief Returns the total number of records as reported by the wrapped reader.
             * \return The record count.
             */
            std::size_t getNumRecords();

            /**
             * \brief Tells whether the reader is in a good (readable) state.
             * \return A non-\c nullptr pointer if the reader is in a good state, and \c nullptr otherwise.
             */
            operator const void*() const;

            /**
             * \brief Tells whether the reader is in a bad (non-readable) state.
             * \return \c true if the reader is in a bad state, and \c false otherwise.
             */
            bool operator!() const;

            /**
             * \brief Closes the wrapped reader and the underlying file stream.
             */
            void close();

          private:
            std::ifstream stream;
            std::string   fileName;
            ReaderImpl    reader;
        };
    } // namespace Util
} // namespace CDPL


// Implementation

template <typename ReaderImpl, typename DataType>
CDPL::Util::FileDataReader<ReaderImpl, DataType>::FileDataReader(const std::string& file_name, std::ios_base::openmode mode):
    stream(file_name.c_str(), mode), fileName(file_name), reader(stream)
{
    if (!stream.good())
        throw Base::IOError("FileDataReader: could not open file");

    reader.setParent(this);
    reader.registerIOCallback(std::bind(&Base::DataIOBase::invokeIOCallbacks, this, std::placeholders::_2));
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
