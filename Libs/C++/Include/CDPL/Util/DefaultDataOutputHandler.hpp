/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * DefaultDataOutputHandler.hpp 
 *
 * This file is part of the Chemical Data Processing Toolkit
 *
 * Copyright (C) 2003-2020 Thomas A. Seidel <thomas.seidel@univie.ac.at>
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
 * \brief Definition of the class CDPL::Util::DefaultDataOutputHandler.
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
		 * \brief DefaultDataOutputHandler.
		 */
		template <typename WriterImpl, const Base::DataFormat& FORMAT, typename DataType = typename WriterImpl::DataType>
		class DefaultDataOutputHandler : public Base::DataOutputHandler<DataType>
		{

		public:
			typedef typename Base::DataOutputHandler<DataType>::WriterType WriterType;

			const Base::DataFormat& getDataFormat() const {
				return FORMAT;
			}
		
			typename WriterType::SharedPointer createWriter(std::iostream& ios) const {
				return typename WriterType::SharedPointer(new WriterImpl(ios));
			}

			typename WriterType::SharedPointer createWriter(const std::string& file_name, std::ios_base::openmode mode) const {
				return typename WriterType::SharedPointer(new Util::FileDataWriter<WriterImpl>(file_name, mode));
			}
		};
    }
}

#endif // CDPL_UTIL_DEFAULTDATAOUTPUTHANDLER_HPP
