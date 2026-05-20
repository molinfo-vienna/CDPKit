/* 
 * DefaultDataInputHandler.hpp 
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
 * \brief Definition of class CDPL::Util::DefaultDataInputHandler.
 */

#ifndef CDPL_UTIL_DEFAULTDATAINPUTHANDLER_HPP
#define CDPL_UTIL_DEFAULTDATAINPUTHANDLER_HPP

#include "CDPL/Base/DataInputHandler.hpp"
#include "CDPL/Util/FileDataReader.hpp"


namespace CDPL
{

    namespace Util
    {

        /**
         * \brief Default Base::DataInputHandler implementation that exposes a fixed Base::DataFormat and instantiates
         *        readers of the supplied stream-based \a ReaderImpl type (file-based readers are produced by wrapping it
         *        in Util::FileDataReader).
         *
         * \tparam ReaderImpl The underlying stream-based reader implementation type.
         * \tparam Format A reference to the Base::DataFormat constant advertised by the handler.
         * \tparam DataType The data type read by \a ReaderImpl.
         */
        template <typename ReaderImpl, const Base::DataFormat& Format, typename DataType = typename ReaderImpl::DataType>
        class DefaultDataInputHandler : public Base::DataInputHandler<DataType>
        {

          public:
            /** \brief Type of the Base::DataReader specialization produced by this handler. */
            typedef typename Base::DataInputHandler<DataType>::ReaderType ReaderType;

            /**
             * \brief Returns the data format advertised by this handler.
             * \return A \c const reference to the fixed Base::DataFormat \a Format.
             */
            const Base::DataFormat& getDataFormat() const
            {
                return Format;
            }

            /**
             * \brief Creates a reader that reads from the input stream \a is.
             * \param is The input stream to wrap.
             * \return A shared pointer to a freshly constructed \a ReaderImpl.
             */
            typename ReaderType::SharedPointer createReader(std::istream& is) const
            {
                return typename ReaderType::SharedPointer(new ReaderImpl(is));
            }

            /**
             * \brief Creates a reader that reads from the file \a file_name (opened in mode \a mode).
             * \param file_name The path of the input file.
             * \param mode The open mode of the underlying file stream.
             * \return A shared pointer to a freshly constructed Util::FileDataReader wrapping a \a ReaderImpl.
             */
            typename ReaderType::SharedPointer createReader(const std::string& file_name, std::ios_base::openmode mode) const
            {
                return typename ReaderType::SharedPointer(new Util::FileDataReader<ReaderImpl>(file_name, mode));
            }
        };
    } // namespace Util
} // namespace CDPL

#endif // CDPL_UTIL_DEFAULTDATAINPUTHANDLER_HPP
