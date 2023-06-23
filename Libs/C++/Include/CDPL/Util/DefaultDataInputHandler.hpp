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
 * \brief Definition of the class CDPL::Util::DefaultDataInputHandler.
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
         * \brief DefaultDataInputHandler.
         */
        template <typename ReaderImpl, const Base::DataFormat& Format, typename DataType = typename ReaderImpl::DataType>
        class DefaultDataInputHandler : public Base::DataInputHandler<DataType>
        {

        public:
            typedef typename Base::DataInputHandler<DataType>::ReaderType ReaderType;

            const Base::DataFormat& getDataFormat() const {
                return Format;
            }
        
            typename ReaderType::SharedPointer createReader(std::istream& is) const {
                return typename ReaderType::SharedPointer(new ReaderImpl(is));
            }

            typename ReaderType::SharedPointer createReader(const std::string& file_name, std::ios_base::openmode mode) const {
                return typename ReaderType::SharedPointer(new Util::FileDataReader<ReaderImpl>(file_name, mode));
            }
        };
    }
}

#endif // CDPL_UTIL_DEFAULTDATAINPUTHANDLER_HPP
