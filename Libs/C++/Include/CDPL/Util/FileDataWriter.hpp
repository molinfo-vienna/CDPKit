/* 
 * FileDataWriter.hpp 
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
 * \brief Definition of class CDPL::Util::FileDataWriter.
 */

#ifndef CDPL_UTIL_FILEDATAWRITER_HPP
#define CDPL_UTIL_FILEDATAWRITER_HPP

#include <fstream>
#include <string>
#include <functional>

#include "CDPL/Base/DataWriter.hpp"
#include "CDPL/Base/Exceptions.hpp"


namespace CDPL
{

    namespace Util
    {

        /**
         * \brief Convenience wrapper that adapts a stream-based writer implementation \a WriterImpl into a file-based
         *        Base::DataWriter by opening an \c std::fstream and forwarding all write operations to the wrapped writer.
         *
         * \tparam WriterImpl The underlying stream-based writer implementation type.
         * \tparam DataType The data type written by \a WriterImpl.
         */
        template <typename WriterImpl, typename DataType = typename WriterImpl::DataType>
        class FileDataWriter : public Base::DataWriter<DataType>
        {

          public:
            /**
             * \brief Constructs a \c %FileDataWriter instance that opens the file \a file_name in the given mode and
             *        forwards all write operations to a freshly constructed \a WriterImpl wrapping the file stream.
             * \param file_name The path of the output file to open.
             * \param mode The open mode of the underlying \c std::fstream.
             * \throw Base::IOError if the file could not be opened.
             */
            FileDataWriter(const std::string&      file_name,
                           std::ios_base::openmode mode = std::ios_base::in | std::ios_base::out | std::ios_base::trunc | std::ios_base::binary);

            /**
             * \brief Writes \a obj as the next record via the wrapped writer.
             * \param obj The object to write.
             * \return A reference to itself.
             * \throw Base::IOError on write failure.
             */
            FileDataWriter& write(const DataType& obj);

            /**
             * \brief Closes the wrapped writer and the underlying file stream.
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
            std::fstream stream;
            std::string  fileName;
            WriterImpl   writer;
        };
    } // namespace Util
} // namespace CDPL


// Implementation

template <typename WriterImpl, typename DataType>
CDPL::Util::FileDataWriter<WriterImpl, DataType>::FileDataWriter(const std::string& file_name, std::ios_base::openmode mode):
    stream(file_name.c_str(), mode), fileName(file_name), writer(stream)
{
    if (!stream.good())
        throw Base::IOError("FileDataWriter: could not open file");

    writer.setParent(this);
    writer.registerIOCallback(std::bind(&Base::DataIOBase::invokeIOCallbacks, this, std::placeholders::_2));
}

template <typename WriterImpl, typename DataType>
CDPL::Util::FileDataWriter<WriterImpl, DataType>&
CDPL::Util::FileDataWriter<WriterImpl, DataType>::write(const DataType& obj)
{
    try {
        writer.write(obj);

    } catch (const std::exception& e) {
        throw Base::IOError("FileDataWriter: while writing file '" + fileName + "': " + e.what());
    }

    return *this;
}

template <typename WriterImpl, typename DataType>
void CDPL::Util::FileDataWriter<WriterImpl, DataType>::close()
{
    writer.close();
    stream.close();
}

template <typename WriterImpl, typename DataType>
CDPL::Util::FileDataWriter<WriterImpl, DataType>::operator const void*() const
{
    return writer.operator const void*();
}

template <typename WriterImpl, typename DataType>
bool CDPL::Util::FileDataWriter<WriterImpl, DataType>::operator!() const
{
    return writer.operator!();
}

#endif // CDPL_UTIL_FILEDATAWRITER_HPP
