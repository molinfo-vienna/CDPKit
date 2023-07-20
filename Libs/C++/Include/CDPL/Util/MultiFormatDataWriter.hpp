/* 
 * MultiFormatDataWriter.hpp 
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
 * \brief Definition of the class CDPL::Util::MultiFormatDataWriter.
 */

#ifndef CDPL_UTIL_MULTIFORMATDATAWRITER_HPP
#define CDPL_UTIL_MULTIFORMATDATAWRITER_HPP

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
         * \brief MultiFormatDataWriter.
         */
        template <typename DataType>
        class MultiFormatDataWriter : public Base::DataWriter<DataType>
        {

          public:
            typedef std::shared_ptr<MultiFormatDataWriter> SharedPointer;
            
            MultiFormatDataWriter(const std::string& file_name,
                                  std::ios_base::openmode mode = std::ios_base::in | std::ios_base::out |
                                  std::ios_base::trunc | std::ios_base::binary);

            MultiFormatDataWriter(const std::string& file_name, const std::string& fmt,
                                  std::ios_base::openmode mode = std::ios_base::in | std::ios_base::out |
                                  std::ios_base::trunc | std::ios_base::binary);

            MultiFormatDataWriter(const std::string& file_name, const Base::DataFormat& fmt,
                                  std::ios_base::openmode mode = std::ios_base::in | std::ios_base::out |
                                  std::ios_base::trunc | std::ios_base::binary);

            MultiFormatDataWriter(std::iostream& ios, const std::string& fmt);

            MultiFormatDataWriter(std::iostream& ios, const Base::DataFormat& fmt);

            MultiFormatDataWriter(const MultiFormatDataWriter&) = delete;

            MultiFormatDataWriter& operator=(const MultiFormatDataWriter&) = delete;

            const Base::DataFormat& getDataFormat() const;
 
            MultiFormatDataWriter& write(const DataType& obj);

            void close();

            operator const void*() const;

            bool operator!() const;

          private:
            void init();

            typedef typename Base::DataWriter<DataType>::SharedPointer WriterPtr;

            WriterPtr        writerPtr;
            Base::DataFormat dataFormat;
        };
    } // namespace Util
} // namespace CDPL


// Implementation

template <typename DataType>
CDPL::Util::MultiFormatDataWriter<DataType>::MultiFormatDataWriter(const std::string& file_name, std::ios_base::openmode mode)
{
    for (std::string::size_type i = file_name.find_first_of('.', 0); i != std::string::npos; i = file_name.find_first_of('.', i)) {
        const auto& handler = Base::DataIOManager<DataType>::getOutputHandlerByFileExtension(file_name.substr(++i));

        if (!handler)
            continue;

        writerPtr = handler->createWriter(file_name, mode);
        dataFormat = handler->getDataFormat();
        break;
    }

    if (!writerPtr)
        throw Base::IOError("MultiFormatDataWriter: could not deduce data format of '" + file_name + "'");

    init();
}

template <typename DataType>
CDPL::Util::MultiFormatDataWriter<DataType>::MultiFormatDataWriter(const std::string& file_name, const std::string& fmt,
                                                                   std::ios_base::openmode mode)
{
    const auto& handler = Base::DataIOManager<DataType>::getOutputHandlerByFileExtension(fmt);

    if (!handler)
        throw Base::IOError("MultiFormatDataWriter: could not find handler for format '" + fmt + "'");

    writerPtr = handler->createWriter(file_name, mode);
    dataFormat = handler->getDataFormat();
    
    init();
}

template <typename DataType>
CDPL::Util::MultiFormatDataWriter<DataType>::MultiFormatDataWriter(const std::string& file_name, const Base::DataFormat& fmt,
                                                                   std::ios_base::openmode mode):
    dataFormat(fmt)
{
    const auto& handler = Base::DataIOManager<DataType>::getOutputHandlerByFormat(fmt);

    if (!handler)
        throw Base::IOError("MultiFormatDataWriter: could not find handler for format '" + fmt.getName() + "'");

    writerPtr = handler->createWriter(file_name, mode);
    
    init();
}

template <typename DataType>
CDPL::Util::MultiFormatDataWriter<DataType>::MultiFormatDataWriter(std::iostream& ios, const std::string& fmt)
{
    const auto& handler = Base::DataIOManager<DataType>::getOutputHandlerByFileExtension(fmt);

    if (!handler)
        throw Base::IOError("MultiFormatDataWriter: could not find handler for format '" + fmt + "'");

    writerPtr = handler->createWriter(ios);
    dataFormat = handler->getDataFormat();

    init();
}

template <typename DataType>
CDPL::Util::MultiFormatDataWriter<DataType>::MultiFormatDataWriter(std::iostream& ios, const Base::DataFormat& fmt):
    dataFormat(fmt)
{
    const auto& handler = Base::DataIOManager<DataType>::getOutputHandlerByFormat(fmt);

    if (!handler)
        throw Base::IOError("MultiFormatDataWriter: could not find handler for format '" + fmt.getName() + "'");

    writerPtr = handler->createWriter(ios);

    init();
}

template <typename DataType>
const CDPL::Base::DataFormat& CDPL::Util::MultiFormatDataWriter<DataType>::getDataFormat() const
{
    return dataFormat;
}

template <typename DataType>
CDPL::Util::MultiFormatDataWriter<DataType>&
CDPL::Util::MultiFormatDataWriter<DataType>::write(const DataType& obj)
{
    writerPtr->write(obj);
    return *this;
}

template <typename DataType>
void CDPL::Util::MultiFormatDataWriter<DataType>::close()
{
    writerPtr->close();
}

template <typename DataType>
CDPL::Util::MultiFormatDataWriter<DataType>::operator const void*() const
{
    return writerPtr->operator const void*();
}

template <typename DataType>
bool CDPL::Util::MultiFormatDataWriter<DataType>::operator!() const
{
    return writerPtr->operator!();
}

template <typename DataType>
void CDPL::Util::MultiFormatDataWriter<DataType>::init()
{
    writerPtr->setParent(this);
    writerPtr->registerIOCallback(std::bind(&Base::DataIOBase::invokeIOCallbacks, this, std::placeholders::_2));
}

#endif // CDPL_UTIL_MULTIFORMATDATAWRITER_HPP
