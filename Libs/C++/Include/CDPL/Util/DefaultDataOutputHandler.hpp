/* 
 * DefaultDataOutputHandler.hpp 
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
 * \brief Definition of class CDPL::Util::DefaultDataOutputHandler.
 */

#ifndef CDPL_UTIL_DEFAULTDATAOUTPUTHANDLER_HPP
#define CDPL_UTIL_DEFAULTDATAOUTPUTHANDLER_HPP

#include "CDPL/Base/DataOutputHandler.hpp"
#include "CDPL/Util/FileDataWriter.hpp"


namespace CDPL
{

    namespace Util
    {

        /**
         * \brief Default Base::DataOutputHandler implementation that exposes a fixed Base::DataFormat and instantiates
         *        writers of the supplied stream-based \a WriterImpl type (file-based writers are produced by wrapping it
         *        in Util::FileDataWriter).
         *
         * \tparam WriterImpl The underlying stream-based writer implementation type.
         * \tparam FORMAT A reference to the Base::DataFormat constant advertised by the handler.
         * \tparam DataType The data type written by \a WriterImpl.
         */
        template <typename WriterImpl, const Base::DataFormat& FORMAT, typename DataType = typename WriterImpl::DataType>
        class DefaultDataOutputHandler : public Base::DataOutputHandler<DataType>
        {

          public:
            /**
             * \brief Type of the Base::DataWriter specialization produced by this handler.
             */
            typedef typename Base::DataOutputHandler<DataType>::WriterType WriterType;

            /**
             * \brief Returns the data format advertised by this handler.
             * \return A \c const reference to the fixed Base::DataFormat \a FORMAT.
             */
            const Base::DataFormat& getDataFormat() const
            {
                return FORMAT;
            }

            /**
             * \brief Creates a writer that writes to the output stream \a os.
             * \param os The output stream to wrap.
             * \return A shared pointer to a freshly constructed \a WriterImpl.
             */
            typename WriterType::SharedPointer createWriter(std::ostream& os) const
            {
                return typename WriterType::SharedPointer(new WriterImpl(os));
            }

            /**
             * \brief Creates a writer that writes to the file \a file_name (opened in mode \a mode).
             * \param file_name The path of the output file.
             * \param mode The open mode of the underlying file stream.
             * \return A shared pointer to a freshly constructed Util::FileDataWriter wrapping a \a WriterImpl.
             */
            typename WriterType::SharedPointer createWriter(const std::string& file_name, std::ios_base::openmode mode) const
            {
                return typename WriterType::SharedPointer(new Util::FileDataWriter<WriterImpl>(file_name, mode));
            }
        };
    } // namespace Util
} // namespace CDPL

#endif // CDPL_UTIL_DEFAULTDATAOUTPUTHANDLER_HPP
