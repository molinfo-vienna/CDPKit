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
 * \brief Definition of class CDPL::Util::CompressedDataReader.
 */

#ifndef CDPL_UTIL_COMPRESSEDDATAREADER_HPP
#define CDPL_UTIL_COMPRESSEDDATAREADER_HPP

#include <iosfwd>
#include <functional>

#include "CDPL/Base/DataReader.hpp"
#include "CDPL/Util/CompressionStreams.hpp"


namespace CDPL
{

    namespace Util
    {

        /**
         * \brief Adapter that wraps a stream-based reader with a decompression stream to read records
         *        from a compressed data stream.
         *
         * \c %CompressedDataReader is a thin template wrapper around an existing
         * Base::DataReader implementation \a ReaderImpl. It constructs a decompression stream of type
         * \a DecompStream around the supplied input stream and forwards all read operations to the
         * inner reader. The reader exposes the standard Base::DataReader interface.
         *
         * \tparam ReaderImpl   The wrapped reader implementation type.
         * \tparam DecompStream The decompression stream type to wrap around the input stream.
         * \tparam DataType     The data record type produced by the reader.
         */
        template <typename ReaderImpl, typename DecompStream, typename DataType = typename ReaderImpl::DataType>
        class CompressedDataReader : public Base::DataReader<DataType>
        {

          public:
            /**
             * \brief Constructs a \c %CompressedDataReader instance reading from the input stream \a is.
             * \param is The input stream providing the compressed data.
             */
            CompressedDataReader(std::istream& is);

            /**
             * \brief Reads the next data record into \a obj.
             * \param obj The output data object.
             * \param overwrite If \c true, any pre-existing content of \a obj is replaced; otherwise the new data is merged.
             * \return A reference to itself.
             */
            CompressedDataReader& read(DataType& obj, bool overwrite = true);

            /**
             * \brief Reads the data record at index \a idx into \a obj.
             * \param idx The zero-based index of the record to read.
             * \param obj The output data object.
             * \param overwrite If \c true, any pre-existing content of \a obj is replaced; otherwise the new data is merged.
             * \return A reference to itself.
             */
            CompressedDataReader& read(std::size_t idx, DataType& obj, bool overwrite = true);

            /**
             * \brief Skips the next data record.
             * \return A reference to itself.
             */
            CompressedDataReader& skip();

            /**
             * \brief Tells whether more records are available.
             * \return \c true if more records are available, and \c false otherwise.
             */
            bool hasMoreData();

            /**
             * \brief Returns the index of the current data record.
             * \return The zero-based index of the current record.
             */
            std::size_t getRecordIndex() const;

            /**
             * \brief Sets the index of the next data record to be read.
             * \param idx The zero-based record index.
             */
            void setRecordIndex(std::size_t idx);

            /**
             * \brief Returns the total number of records in the input stream.
             * \return The number of records.
             */
            std::size_t getNumRecords();

            /**
             * \brief Returns a non-zero value if the reader is in a good state, and zero otherwise.
             * \return A non-zero value if the reader is operational, zero otherwise.
             */
            operator const void*() const;

            /**
             * \brief Tells whether the reader is in a bad state.
             * \return \c true if the reader is in a bad state, and \c false otherwise.
             */
            bool operator!() const;

            /**
             * \brief Closes the wrapped reader and the decompression stream.
             */
            void close();

          private:
            DecompStream stream;
            ReaderImpl   reader;
        };
    } // namespace Util
} // namespace CDPL


// Implementation

template <typename ReaderImpl, typename DecompStream, typename DataType>
CDPL::Util::CompressedDataReader<ReaderImpl, DecompStream, DataType>::CompressedDataReader(std::istream& is):
    stream(is), reader(stream)
{
    reader.setParent(this);
    reader.registerIOCallback(std::bind(&Base::DataIOBase::invokeIOCallbacks, this, std::placeholders::_2));
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
