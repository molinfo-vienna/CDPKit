/* 
 * MultiFormatDataReader.hpp 
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
 * \brief Definition of class CDPL::Util::MultiFormatDataReader.
 */

#ifndef CDPL_UTIL_MULTIFORMATDATAREADER_HPP
#define CDPL_UTIL_MULTIFORMATDATAREADER_HPP

#include <string>
#include <functional>
#include <memory>

#include "CDPL/Base/DataIOManager.hpp"
#include "CDPL/Base/Exceptions.hpp"


namespace CDPL
{

    namespace Util
    {

        /**
         * \brief MultiFormatDataReader.
         */
        template <typename DataType>
        class MultiFormatDataReader : public Base::DataReader<DataType>
        {

          public:
            typedef std::shared_ptr<MultiFormatDataReader> SharedPointer;
            
            MultiFormatDataReader(const std::string& file_name, 
                                  std::ios_base::openmode mode = std::ios_base::in | std::ios_base::binary);

            MultiFormatDataReader(const std::string& file_name, const std::string& fmt,
                                  std::ios_base::openmode mode = std::ios_base::in | std::ios_base::binary);

            MultiFormatDataReader(const std::string& file_name, const Base::DataFormat& fmt,
                                  std::ios_base::openmode mode = std::ios_base::in | std::ios_base::binary);

            MultiFormatDataReader(std::istream& is, const std::string& fmt);

            MultiFormatDataReader(std::istream& is, const Base::DataFormat& fmt);

            MultiFormatDataReader(const MultiFormatDataReader&) = delete;

            MultiFormatDataReader& operator=(const MultiFormatDataReader&) = delete;

            const Base::DataFormat& getDataFormat() const;
            
            MultiFormatDataReader& read(DataType& obj, bool overwrite = true);
            
            MultiFormatDataReader& read(std::size_t idx, DataType& obj, bool overwrite = true);

            MultiFormatDataReader& skip();

            bool hasMoreData();

            std::size_t getRecordIndex() const;

            void setRecordIndex(std::size_t idx);

            std::size_t getNumRecords();

            operator const void*() const;
            
            bool operator!() const;

            void close();

          private:
            void init();
            
            typedef typename Base::DataReader<DataType>::SharedPointer ReaderPtr;

            ReaderPtr        readerPtr;
            Base::DataFormat dataFormat;
        };
    } // namespace Util
} // namespace CDPL


// Implementation

template <typename DataType>
CDPL::Util::MultiFormatDataReader<DataType>::MultiFormatDataReader(const std::string& file_name, std::ios_base::openmode mode)
{
    const auto& handler = Base::DataIOManager<DataType>::getInputHandlerByFileName(file_name);

    if (!handler)
        throw Base::IOError("MultiFormatDataReader: could not deduce data format of '" + file_name + "'");

    readerPtr = handler->createReader(file_name, mode);
    dataFormat = handler->getDataFormat();

    init();
}

template <typename DataType>
CDPL::Util::MultiFormatDataReader<DataType>::MultiFormatDataReader(const std::string& file_name, const std::string& fmt,
                                                                   std::ios_base::openmode mode)
{
    const auto& handler = Base::DataIOManager<DataType>::getInputHandlerByFileExtension(fmt);

    if (!handler)
        throw Base::IOError("MultiFormatDataReader: could not find handler for format '" + fmt + "'");

    readerPtr = handler->createReader(file_name, mode);
    dataFormat = handler->getDataFormat();
    
    init();
}

template <typename DataType>
CDPL::Util::MultiFormatDataReader<DataType>::MultiFormatDataReader(const std::string& file_name, const Base::DataFormat& fmt,
                                                                   std::ios_base::openmode mode):
    dataFormat(fmt)
{
    const auto& handler = Base::DataIOManager<DataType>::getInputHandlerByFormat(fmt);

    if (!handler)
        throw Base::IOError("MultiFormatDataReader: could not find handler for format '" + fmt.getName() + "'");

    readerPtr = handler->createReader(file_name, mode);
    
    init();
}

template <typename DataType>
CDPL::Util::MultiFormatDataReader<DataType>::MultiFormatDataReader(std::istream& is, const std::string& fmt)
{
    const auto& handler = Base::DataIOManager<DataType>::getInputHandlerByFileExtension(fmt);

    if (!handler)
        throw Base::IOError("MultiFormatDataReader: could not find handler for format '" + fmt + "'");

    readerPtr = handler->createReader(is);
    dataFormat = handler->getDataFormat();

    init();
}

template <typename DataType>
CDPL::Util::MultiFormatDataReader<DataType>::MultiFormatDataReader(std::istream& is, const Base::DataFormat& fmt):
    dataFormat(fmt)
{
    const auto& handler = Base::DataIOManager<DataType>::getInputHandlerByFormat(fmt);

    if (!handler)
        throw Base::IOError("MultiFormatDataReader: could not find handler for format '" + fmt.getName() + "'");

    readerPtr = handler->createReader(is);

    init();
}

template <typename DataType>
const CDPL::Base::DataFormat& CDPL::Util::MultiFormatDataReader<DataType>::getDataFormat() const
{
    return dataFormat;
}

template <typename DataType>
CDPL::Util::MultiFormatDataReader<DataType>&
CDPL::Util::MultiFormatDataReader<DataType>::read(DataType& obj, bool overwrite)
{
    readerPtr->read(obj, overwrite);
    return *this;
}

template <typename DataType>
CDPL::Util::MultiFormatDataReader<DataType>&
CDPL::Util::MultiFormatDataReader<DataType>::read(std::size_t idx, DataType& obj, bool overwrite)
{
    readerPtr->read(idx, obj, overwrite);
    return *this;
}

template <typename DataType>
CDPL::Util::MultiFormatDataReader<DataType>&
CDPL::Util::MultiFormatDataReader<DataType>::skip()
{
    readerPtr->skip();
    return *this;
}

template <typename DataType>
bool CDPL::Util::MultiFormatDataReader<DataType>::hasMoreData()
{
    return readerPtr->hasMoreData();
}

template <typename DataType>
std::size_t CDPL::Util::MultiFormatDataReader<DataType>::getRecordIndex() const
{
    return readerPtr->getRecordIndex();
}

template <typename DataType>
void CDPL::Util::MultiFormatDataReader<DataType>::setRecordIndex(std::size_t idx)
{
    readerPtr->setRecordIndex(idx);
}

template <typename DataType>
std::size_t CDPL::Util::MultiFormatDataReader<DataType>::getNumRecords()
{
    return readerPtr->getNumRecords();
}

template <typename DataType>
CDPL::Util::MultiFormatDataReader<DataType>::operator const void*() const
{
    return readerPtr->operator const void*();
}

template <typename DataType>
bool CDPL::Util::MultiFormatDataReader<DataType>::operator!() const
{
    return readerPtr->operator!();
}

template <typename DataType>
void CDPL::Util::MultiFormatDataReader<DataType>::close()
{
    readerPtr->close();
}

template <typename DataType>
void CDPL::Util::MultiFormatDataReader<DataType>::init()
{
    readerPtr->setParent(this);
    readerPtr->registerIOCallback(std::bind(&Base::DataIOBase::invokeIOCallbacks, this, std::placeholders::_2));
}

#endif // CDPL_UTIL_MULTIFORMATDATAREADER_HPP
