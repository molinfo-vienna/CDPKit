/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

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
 * \brief Definition of the class CDPL::Util::FileDataWriter.
 */

#ifndef CDPL_UTIL_FILEDATAWRITER_HPP
#define CDPL_UTIL_FILEDATAWRITER_HPP

#include <fstream>
#include <string>

#include <boost/bind.hpp>

#include "CDPL/Base/DataWriter.hpp"
#include "CDPL/Base/Exceptions.hpp"


namespace CDPL 
{

    namespace Util
    {

		/**
		 * \brief FileDataWriter.
		 */
		template <typename WriterImpl, typename DataType = typename WriterImpl::DataType>
		class FileDataWriter : public Base::DataWriter<DataType>
		{

		public:
			FileDataWriter(const std::string& file_name, 
						   std::ios_base::openmode mode = std::ios_base::in | std::ios_base::out | std::ios_base::trunc | std::ios_base::binary); 

			FileDataWriter& write(const DataType& obj);
		
			void close();
		
			operator const void*() const;
		
			bool operator!() const;

		private:
			std::fstream  stream;
			std::string   fileName;
			WriterImpl    writer;
		};
    }
}


// Implementation

template <typename WriterImpl, typename DataType>
CDPL::Util::FileDataWriter<WriterImpl, DataType>::FileDataWriter(const std::string& file_name, std::ios_base::openmode mode): 
    stream(file_name.c_str(), mode), fileName(file_name), writer(stream) 
{
    writer.setParent(this);
	writer.registerIOCallback(boost::bind(&Base::DataIOBase::invokeIOCallbacks, this, _2));
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
