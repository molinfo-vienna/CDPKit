/* 
 * CompressedDataWriter.hpp 
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
 * \brief Definition of class CDPL::Util::CompressedDataWriter.
 */

#ifndef CDPL_UTIL_COMPRESSEDDATAWRITER_HPP
#define CDPL_UTIL_COMPRESSEDDATAWRITER_HPP

#include <iosfwd>
#include <functional>

#include "CDPL/Base/DataWriter.hpp"
#include "CDPL/Util/CompressionStreams.hpp"


namespace CDPL
{

    namespace Util
    {

        /**
         * \brief Convenience wrapper that combines a Util::CompressionOStream of type \a CompStream with a stream-based
         *        writer \a WriterImpl so that data written via this Base::DataWriter is automatically compressed on the fly.
         *
         * \tparam WriterImpl The underlying stream-based writer implementation type.
         * \tparam CompStream The Util::CompressionOStream specialization to use (e.g. Util::GZipOStream).
         * \tparam DataType The data type written by \a WriterImpl.
         */
        template <typename WriterImpl, typename CompStream, typename DataType = typename WriterImpl::DataType>
        class CompressedDataWriter : public Base::DataWriter<DataType>
        {

          public:
            /**
             * \brief Constructs the \c %CompressedDataWriter instance that compresses output written to \a os via \a CompStream
             *        and forwards the resulting stream to a freshly constructed \a WriterImpl.
             * \param os The output stream that will receive the compressed data.
             */
            CompressedDataWriter(std::ostream& os);

            /**
             * \brief Writes \a obj via the wrapped writer.
             * \param obj The object to write.
             * \return A reference to itself.
             */
            CompressedDataWriter& write(const DataType& obj);

            /**
             * \brief Closes the wrapped writer and finalizes the compression stream.
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
            CompStream stream;
            WriterImpl writer;
        };
    } // namespace Util
} // namespace CDPL


// Implementation

template <typename WriterImpl, typename DecompStream, typename DataType>
CDPL::Util::CompressedDataWriter<WriterImpl, DecompStream, DataType>::CompressedDataWriter(std::ostream& os):
    stream(os), writer(stream)
{
    writer.setParent(this);
    writer.registerIOCallback(std::bind(&Base::DataIOBase::invokeIOCallbacks, this, std::placeholders::_2));
}

template <typename WriterImpl, typename DecompStream, typename DataType>
CDPL::Util::CompressedDataWriter<WriterImpl, DecompStream, DataType>&
CDPL::Util::CompressedDataWriter<WriterImpl, DecompStream, DataType>::write(const DataType& obj)
{
    writer.write(obj);

    return *this;
}

template <typename WriterImpl, typename DecompStream, typename DataType>
void CDPL::Util::CompressedDataWriter<WriterImpl, DecompStream, DataType>::close()
{
    writer.close();
    stream.close();
}

template <typename WriterImpl, typename DecompStream, typename DataType>
CDPL::Util::CompressedDataWriter<WriterImpl, DecompStream, DataType>::operator const void*() const
{
    return writer.operator const void*();
}

template <typename WriterImpl, typename DecompStream, typename DataType>
bool CDPL::Util::CompressedDataWriter<WriterImpl, DecompStream, DataType>::operator!() const
{
    return writer.operator!();
}

#endif // CDPL_UTIL_COMPRESSEDDATAWRITER_HPP
