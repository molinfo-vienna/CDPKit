/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * DataReader.hpp 
 *
 * This file is part of the Chemical Data Processing Toolkit
 *
 * Copyright (C) 2003-2010 Thomas A. Seidel <thomas.seidel@univie.ac.at>
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
 * \brief Definition of the class CDPL::Base::DataReader.
 */

#ifndef CDPL_BASE_DATAREADER_HPP
#define CDPL_BASE_DATAREADER_HPP

#include <cstddef>

#include <boost/shared_ptr.hpp>

#include "CDPL/Base/DataIOBase.hpp"


namespace CDPL 
{

	namespace Base
	{

		/**
		 * \addtogroup CDPL_BASE_IO
		 * @{
		 */

		/**
		 * \brief An interface for reading data objects of a given type from an arbitrary data source.
		 *
		 * \c %DataReader is the common interface of classes which read objects of a given type 
		 * (specified by the template parameter \a T) from some data source (e.g. a file) that provides
		 * the data encoded in a particular storage format.
		 *
		 * From the \c %DataReader interface point of view, the data source is organized as an array of logical data records.
		 * Each record is addressed by a zero-based sequential record index and contains the data for exactly \e one data 
		 * object. The total number of available data records (which is equal to the maximum record index plus \e 1) can be
		 * queried by the method getNumRecords(). 
		 *
		 * Similar to low-level file I/O, data records may either be read in a sequential or in a random access manner.
		 * For sequential access the method read(DataType& obj) is provided which will read the data record at the 'current'
		 * record index (similar to a file pointer). The current record index is accessible by the method getRecordIndex()
		 * and can be modified using the method setRecordIndex() (similar to a seek operation). 
		 *
		 * For reading data records in a random access manner, the method read(std::size_t idx, DataType& obj) is available.
		 * In contrast to the former read() method, this method expects the index of the record to read as the first argument. 
		 *
		 * If a read() (or skip()) operation was successful, the current record index is updated to point to the record immediately
		 * following the just read (or skipped) data record. If an operation fails, the reader instance is set into an error
		 * state that can be queried by the operators operator const void*() and bool operator!(). Additionally, a \c %DataReader
		 * implementation may decide to throw an exception of type Base::IOError to report the error condition. 
		 *
		 * \tparam T The type of the read data objects.
		 */
		template <typename T>
		class DataReader : virtual public DataIOBase
		{

		public:
			/**
			 * \brief The type of the read data objects.
			 */
			typedef T DataType;

			/**
			 * \brief A reference-counted smart pointer [\ref BSHPTR] for dynamically allocated \c %DataReader instances.
			 */
			typedef boost::shared_ptr<DataReader> SharedPointer;

			/**
			 * \brief Reads the data record at the current record index and stores the read data in \a obj.
			 *
			 * If the read operation was successful, the record index is incremented by \e 1.
			 *
			 * \param obj The object storing the read data.
			 * \param overwrite Specifies whether any existing data in \a obj shall be replaced by the
			 *                  newly read data or if the read data should be appended (if supported by the
			 *                  reader and data type). 
			 * \return A reference to itself.
			 * \throw Base::IOError if an I/O error occurred.
			 */
			virtual DataReader& read(DataType& obj, bool overwrite = true) = 0;

			/**
			 * \brief Reads the data record at index \a idx and stores the read data in \a obj.
			 *
			 * If the read operation was successful, the record index is set to <em>idx + 1</em>.
			 *
			 * \param idx The zero-based index of the data record to read.
			 * \param obj The object storing the read data.
			 * \param overwrite Specifies whether any existing data in \a obj shall be replaced by the
			 *                  newly read data or if the read data should be appended (if supported by the
			 *                  reader and data type). 
			 * \return A reference to itself.
			 * \throw Base::IndexError if \a idx is greater or equal to the number of records. 
			 *        Base::IOError if an I/O error occurred.
			 */
			virtual DataReader& read(std::size_t idx, DataType& obj, bool overwrite = true) = 0;

			/**
			 * \brief Skips the data record at the current record index.
			 *
			 * If the operation was successful, the record index is incremented by \e 1.
			 *
			 * \return A reference to itself.
			 * \throw Base::IOError if an I/O error occurred.
			 */
			virtual DataReader& skip() = 0;

			/**
			 * \brief Tells if there are any data records left to read.
			 * \return \c true if there are data record left to read, and \c false otherwise.
			 * \throw Base::IOError if an I/O error occurred.
			 */
			virtual bool hasMoreData() = 0;

			/**
			 * \brief Returns the index of the current data record.
			 * \return The zero-based index of the current data record.
			 */
			virtual std::size_t getRecordIndex() const = 0;

			/**
			 * \brief Sets the index of the current data record to \a idx.
			 * \param idx The zero-based index of the data record.
			 * \throw Base::IndexError if \a idx is greater or equal to the number of available data records. 
			 *        Base::IOError if an I/O error occurred.
			 */
			virtual void setRecordIndex(std::size_t idx) = 0;

			/**
			 * \brief Returns the total number of available data records.
			 * \return The total number of available data records.
			 * \throw Base::IOError if an I/O error occurred.
			 */
			virtual std::size_t getNumRecords() = 0;

			/**
			 * \brief Returns a pointer whose value indicates the error state of the reader.
			 *
			 * The operator allows to write expressions like:
			 * \code
			 * if (reader) { ... 
			 * if (reader.skip()) { ...
			 * \endcode
			 *
			 * \return A non-\e null pointer if the reader is in a good state, a \e null pointer otherwise.
			 * \note The returned pointer is not meant to be dereferenced, it is just a state indicator.
			 * \see operator!()
			 */
			virtual operator const void*() const = 0;
			
			/**
			 * \brief Tells whether the reader is in a bad state.
			 *
			 * The operator allows to write expressions like:
			 * \code
			 * if (!reader) { ... 
			 * if (!reader.skip()) { ...
			 * \endcode
			 *
			 * \return \c false if the reader is in a good state, and \c true otherwise.
			 * \see operator const void*()
			 */
			virtual bool operator!() const = 0;

			/**
			 * \brief Performs a reader specific shutdown operation (if required).
			 * \throw Base::IOError if an I/O error occurred.
			 */
			virtual void close() {}

		protected:
			/**
			 * \brief Assignment operator.
			 * \param reader The \c %DataReader instance to copy.
			 * \return A reference to itself.
			 */
			DataReader& operator=(const DataReader& reader);
		};

		/**
		 * \brief An input operator that reads the next data record by means of the Base::DataReader instance \a reader
		 *        into the data object \a obj.
		 * \param reader The Base::DataReader instance to use for data input.
		 * \param obj The object storing the read data.
		 * \return A reference to \a reader.
		 * \throw Base::IOError if an I/O error occurred.
		 */
		template <typename T>
		DataReader<T>& operator>>(DataReader<T>& reader, T& obj);

		/**
		 * @}
		 */
	}
}


// Implementation

template <typename T>
CDPL::Base::DataReader<T>& CDPL::Base::DataReader<T>::operator=(const DataReader& reader)
{
	if (this == &reader)
		return *this;

	DataIOBase::operator=(reader);

	return *this;
}

// \cond UNHIDE_DETAILS

template <typename T>
CDPL::Base::DataReader<T>& CDPL::Base::operator>>(DataReader<T>& reader, T& obj)
{
	return reader.read(obj);
}

// \endcond

#endif // CDPL_BASE_DATAREADER_HPP
