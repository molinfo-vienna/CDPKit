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
 * \brief Definition of class CDPL::Util::MultiFormatDataWriter.
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
         * \brief Base::DataWriter front-end that automatically selects a concrete handler from Base::DataIOManager
         *        based on the output file name or an explicitly supplied format identifier.
         *
         * \tparam DataType The data type to write.
         */
        template <typename DataType>
        class MultiFormatDataWriter : public Base::DataWriter<DataType>
        {

          public:
            /** \brief A reference-counted smart pointer [\ref SHPTR] for dynamically allocated \c %MultiFormatDataWriter instances. */
            typedef std::shared_ptr<MultiFormatDataWriter> SharedPointer;

            /**
             * \brief Constructs a \c %MultiFormatDataWriter that opens \a file_name and deduces the output format from its name.
             * \param file_name The output-file name.
             * \param mode The open mode of the underlying file stream.
             * \throw Base::IOError if no matching output handler was found.
             */
            MultiFormatDataWriter(const std::string& file_name,
                                  std::ios_base::openmode mode = std::ios_base::in | std::ios_base::out |
                                  std::ios_base::trunc | std::ios_base::binary);

            /**
             * \brief Constructs a \c %MultiFormatDataWriter that opens \a file_name and uses the output handler matching the file-extension/format name \a fmt.
             * \param file_name The output-file name.
             * \param fmt A file-extension or format name resolvable via Base::DataIOManager.
             * \param mode The open mode of the underlying file stream.
             * \throw Base::IOError if no matching output handler was found.
             */
            MultiFormatDataWriter(const std::string& file_name, const std::string& fmt,
                                  std::ios_base::openmode mode = std::ios_base::in | std::ios_base::out |
                                  std::ios_base::trunc | std::ios_base::binary);

            /**
             * \brief Constructs a \c %MultiFormatDataWriter that opens \a file_name and uses the output handler matching the Base::DataFormat \a fmt.
             * \param file_name The output-file name.
             * \param fmt The output format identifier.
             * \param mode The open mode of the underlying file stream.
             * \throw Base::IOError if no matching output handler was found.
             */
            MultiFormatDataWriter(const std::string& file_name, const Base::DataFormat& fmt,
                                  std::ios_base::openmode mode = std::ios_base::in | std::ios_base::out |
                                  std::ios_base::trunc | std::ios_base::binary);

            /**
             * \brief Constructs a \c %MultiFormatDataWriter that wraps \a ios and uses the output handler matching the file-extension/format name \a fmt.
             * \param ios The output stream to wrap.
             * \param fmt A file-extension or format name resolvable via Base::DataIOManager.
             * \throw Base::IOError if no matching output handler was found.
             */
            MultiFormatDataWriter(std::iostream& ios, const std::string& fmt);

            /**
             * \brief Constructs a \c %MultiFormatDataWriter that wraps \a ios and uses the output handler matching the Base::DataFormat \a fmt.
             * \param ios The output stream to wrap.
             * \param fmt The output format identifier.
             * \throw Base::IOError if no matching output handler was found.
             */
            MultiFormatDataWriter(std::iostream& ios, const Base::DataFormat& fmt);

            MultiFormatDataWriter(const MultiFormatDataWriter&) = delete;

            MultiFormatDataWriter& operator=(const MultiFormatDataWriter&) = delete;

            /**
             * \brief Returns the data format actually used by the wrapped output handler.
             * \return A \c const reference to the resolved Base::DataFormat.
             */
            const Base::DataFormat& getDataFormat() const;

            /**
             * \brief Writes \a obj via the wrapped writer.
             * \param obj The object to write.
             * \return A reference to itself.
             */
            MultiFormatDataWriter& write(const DataType& obj);

            /**
             * \brief Closes the wrapped writer (and the underlying file stream if owned).
             */
            void close();

            /**
             * \brief Tells whether the writer is in a good (writable) state.
             * \return A non-\c nullptr pointer if the writer is in a good state, and \c nullptr otherwise.
             */
            operator const void*() const;

            /**
             * \brief Tells whether the writer is in a bad (non-writable) state.
             * \return \c true if the writer is in a bad state, and \c false otherwise.
             */
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

    const auto& handler = Base::DataIOManager<DataType>::getOutputHandlerByFileName(file_name);

    if (!handler)
        throw Base::IOError("MultiFormatDataWriter: could not deduce data format of '" + file_name + "'");

    writerPtr = handler->createWriter(file_name, mode);
    dataFormat = handler->getDataFormat();

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
