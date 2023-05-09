/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * DataOutputHandler.hpp 
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
 * \brief Definition of the class CDPL::Base::DataOutputHandler.
 */

#ifndef CDPL_BASE_DATAOUTPUTHANDLER_HPP
#define CDPL_BASE_DATAOUTPUTHANDLER_HPP

#include <ios>

#include <boost/shared_ptr.hpp>

#include "CDPL/Base/DataWriter.hpp"


namespace CDPL 
{

	namespace Base
	{

		class DataFormat;

		/**
		 * \brief A factory interface providing methods for the creation of Base::DataWriter instances handling a particular
		 *        object type and storage format.
		 * \tparam T The type of objects handled by the created Base::DataWriter instances.
		 */
		template <typename T>
		class DataOutputHandler 
		{

		public:
			typedef DataWriter<T> WriterType;

			typedef boost::shared_ptr<DataOutputHandler> SharedPointer;

			/**
			 * \brief Virtual destructor.
			 */
			virtual ~DataOutputHandler() {}

			/**
			 * \brief Returns a Base::DataFormat object that provides information about the handled output data format.
			 * \return A Base::DataFormat object that provides information about the handled data format.
			 */
			virtual const DataFormat& getDataFormat() const = 0;

			/**
			 * \brief Creates a Base::DataWriter instance that will write the data to the I/O stream \a ios.
			 * \param ios The I/O stream to write to.
			 * \return A shared pointer to the created Base::DataWriter instance.
			 */
			virtual typename WriterType::SharedPointer createWriter(std::iostream& ios) const = 0;

			/**
			 * \brief Creates a Base::DataWriter instance that will write the data to the I/O stream \a ios.
			 * \param file_name The name of the file to write to.
			 * \param mode Flags specifying the file open-mode.
			 * \return A shared pointer to the created Base::DataWriter instance.
			 */
			virtual typename WriterType::SharedPointer createWriter(const std::string& file_name, 
																	std::ios_base::openmode mode = 
																	std::ios_base::in | std::ios_base::out | std::ios_base::trunc | std::ios_base::binary) const = 0;
		};
	}
}

#endif // CDPL_BASE_DATAOUTPUTHANDLER_HPP
