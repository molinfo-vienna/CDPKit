/* 
 * CompoundDataReader.hpp 
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
 * \brief Definition of class CDPL::Util::CompoundDataReader.
 */

#ifndef CDPL_UTIL_COMPOUNDDATAREADER_HPP
#define CDPL_UTIL_COMPOUNDDATAREADER_HPP

#include <vector>
#include <algorithm>
#include <functional>

#include "CDPL/Base/DataReader.hpp"
#include "CDPL/Base/Exceptions.hpp"


namespace CDPL
{

    namespace Util
    {

        /**
         * \brief Composite Base::DataReader that aggregates several underlying readers and presents their records
         *        as one contiguous record stream.
         *
         * \tparam DataType The data type read by the contained Base::DataReader instances.
         */
        template <typename DataType>
        class CompoundDataReader : public Base::DataReader<DataType>
        {

          public:
            /** \brief A reference-counted smart pointer [\ref SHPTR] for dynamically allocated \c %CompoundDataReader instances. */
            typedef std::shared_ptr<CompoundDataReader> SharedPointer;

            /** \brief Type of the underlying Base::DataReader specialization. */
            typedef Base::DataReader<DataType>         ReaderType;
            /** \brief Shared-pointer type for the underlying readers. */
            typedef typename ReaderType::SharedPointer ReaderPointer;

            /**
             * \brief Constructs an empty \c %CompoundDataReader instance.
             */
            CompoundDataReader();

            /**
             * \brief Destructor.
             */
            ~CompoundDataReader();

            CompoundDataReader(const CompoundDataReader&) = delete;

            CompoundDataReader& operator=(const CompoundDataReader&) = delete;

            /**
             * \brief Appends \a reader to the list of underlying readers.
             * \param reader The reader to add.
             */
            void addReader(const ReaderPointer& reader);

            /**
             * \brief Removes the reader at index \a idx from the list of underlying readers.
             * \param idx The zero-based reader index.
             * \throw Base::IndexError if the number of readers is zero or \a idx is not in the range [0, getNumReaders() - 1].
             */
            void removeReader(std::size_t idx);

            /**
             * \brief Returns the number of underlying readers.
             * \return The reader count.
             */
            std::size_t getNumReaders();

            /**
             * \brief Removes all underlying readers.
             */
            void clear();

            /**
             * \brief Returns the index of the underlying reader that owns the global record index \a idx.
             * \param idx The zero-based global record index.
             * \return The zero-based reader index.
             */
            std::size_t getReaderIDForRecordIndex(std::size_t idx) const;

            /**
             * \brief Returns the underlying reader at index \a idx.
             * \param idx The zero-based reader index.
             * \return A \c const reference to the reader shared pointer.
             * \throw Base::IndexError if the number of readers is zero or \a idx is not in the range [0, getNumReaders() - 1].
             */
            const ReaderPointer& getReader(std::size_t idx) const;

            /**
             * \brief Reads the next record into \a obj.
             * \param obj The output object.
             * \param overwrite If \c true, the output object is cleared before the record is copied into it.
             * \return A reference to itself.
             */
            CompoundDataReader& read(DataType& obj, bool overwrite = true);

            /**
             * \brief Reads the record at the global index \a idx into \a obj.
             * \param idx The zero-based global record index.
             * \param obj The output object.
             * \param overwrite If \c true, the output object is cleared before the record is copied into it.
             * \return A reference to itself.
             * \throw Base::IndexError if the number of records is zero or \a idx is not in the range [0, getNumRecords() - 1].
             */
            CompoundDataReader& read(std::size_t idx, DataType& obj, bool overwrite = true);

            /**
             * \brief Skips the next record.
             * \return A reference to itself.
             */
            CompoundDataReader& skip();

            /**
             * \brief Tells whether more records are available.
             * \return \c true if at least one more record is available, and \c false otherwise.
             */
            bool hasMoreData();

            /**
             * \brief Returns the current global record index.
             * \return The zero-based global record index of the next record to read.
             */
            std::size_t getRecordIndex() const;

            /**
             * \brief Sets the current global record index.
             * \param idx The new zero-based global record index (may equal getNumRecords() to position past the last record).
             * \throw Base::IndexError if \a idx is strictly greater than getNumRecords().
             */
            void setRecordIndex(std::size_t idx);

            /**
             * \brief Returns the total number of records across all underlying readers.
             * \return The combined record count.
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

          private:
            ReaderType* getReaderForRecordIndex(std::size_t& idx) const;

            typedef std::vector<ReaderPointer> ReaderArray;
            typedef std::vector<std::size_t>   RecordIndexArray;

            ReaderArray      readers;
            bool             state;
            RecordIndexArray recordIdxBounds;
            std::size_t      recordIdx;
            std::size_t      numRecords;
        };
    } // namespace Util
} // namespace CDPL


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
                  std::bind(&ReaderType::setParent, std::placeholders::_1,
                            static_cast<CompoundDataReader*>(0)));
    readers.clear();
    recordIdxBounds.clear();

    numRecords = 0;
    state      = false;
    recordIdx  = 0;
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

    if (recordIdx >= numRecords)
        return *this;
   
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
    state = false;

    if (idx >= numRecords)
        throw Base::IndexError("CompoundDataReader: record index out of bounds");

    std::size_t tmp_idx = idx;
    ReaderType* reader = getReaderForRecordIndex(tmp_idx);

    if (reader) {
        recordIdx = idx;
    
        if ((state = reader->read(tmp_idx, obj, overwrite))) {
            recordIdx++;
            this->invokeIOCallbacks(1.0);
        }
    }

    return *this;
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
    if (idx > numRecords)
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
