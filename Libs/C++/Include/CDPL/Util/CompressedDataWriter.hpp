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
         * \brief CompressedDataWriter.
         */
        template <typename WriterImpl, typename CompStream, typename DataType = typename WriterImpl::DataType>
        class CompressedDataWriter : public Base::DataWriter<DataType>
        {

          public:
            CompressedDataWriter(std::ostream& os);

            CompressedDataWriter& write(const DataType& obj);

            void close();

            operator const void*() const;

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
