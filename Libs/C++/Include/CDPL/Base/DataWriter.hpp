/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * DataWriter.hpp 
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
 * \brief Definition of the class CDPL::Base::DataWriter.
 */

#ifndef CDPL_BASE_DATAWRITER_HPP
#define CDPL_BASE_DATAWRITER_HPP

#include <boost/shared_ptr.hpp>

#include "CDPL/Base/DataIOBase.hpp"


namespace CDPL 
{

	namespace Base
	{

		/**
		 * \brief An interface for writing data objects of a given type to an arbitrary data sink.
		 *
		 * \c %DataWriter is the common interface of classes which write objects of a given type 
		 * (specified by the template parameter \a T) to some data sink (e.g. a file) that expects
		 * the data to be encoded in a particular storage format.
		 *
		 * From the \c %DataWriter interface point of view, the data sink is continuous output stream
		 * in which the data objects are written as data records. For the output of a given data object
		 * the method write() has to be called with the object passed as an argument. 
		 *		 
		 * If the write() operation fails, the writer instance is set into an error state that can be
		 * queried by the operators operator const void*() and bool operator!(). Additionally, a 
		 * \c %DataWriter implementation may decide to throw an exception of type Base::IOError to
		 * report the error condition.
		 * 
		 * \tparam T The type of the written data objects.
		 */
		template <typename T>
		class DataWriter : virtual public DataIOBase
		{

		public:
			/**
			 * \brief A reference-counted smart pointer [\ref BSHPTR] for dynamically allocated \c %DataWriter instances.
			 */
			typedef boost::shared_ptr<DataWriter> SharedPointer;

			/**
			 * \brief The type of the written data objects.
			 */
			typedef T DataType;

			/**
			 * \brief Writes the data object \a obj.
			 * \param obj The data object to write.
			 * \return A reference to itself.
			 * \throw Base::IOError if an I/O error occurred.
			 */
			virtual DataWriter& write(const DataType& obj) = 0;

			/**
			 * \brief Writes format dependent data (if required) to mark the end of output.
			 * \throw Base::IOError if an I/O error occurred.
			 */
			virtual void close() {}

			/**
			 * \brief Returns a pointer whose value indicates the error state of the writer.
			 *
			 * The operator allows to write expressions like:
			 * \code
			 * if (writer) { ... 
			 * if (writer.write(...)) { ...
			 * \endcode
			 *
			 * \return A non-\e null pointer if the writer is in a good state, a \e null pointer otherwise.
			 * \note The returned pointer is not meant to be dereferenced, it is just a state indicator.
			 * \see operator!()
			 */
			virtual operator const void*() const = 0;

			/**
			 * \brief Tells whether the writer is in a bad state.
			 *
			 * The operator allows to write expressions like:
			 * \code
			 * if (!writer) { ... 
			 * if (!writer.write(...)) { ...
			 * \endcode
			 *
			 * \return \c false if the writer is in a good state, and \c true otherwise.
			 * \see operator const void*()
			 */
			virtual bool operator!() const = 0;

		protected:
			/**
			 * \brief Assignment operator.
			 * \param writer The \c %DataWriter instance to copy.
			 * \return A reference to itself.
			 */
			DataWriter& operator=(const DataWriter& writer);
		};

		/**
		 * \brief An output operator that outputs the data object \a obj by means of the Base::DataWriter instance 
		 *        \a writer.
		 * \param writer The Base::DataWriter instance to use for data output.
		 * \param obj The object storing the data to write.
		 * \return A reference to \a writer.
		 * \throw Base::IOError if an I/O error occurred.
		 */
		template <typename T>
		DataWriter<T>& operator<<(DataWriter<T>& writer, const T& obj);
	}
}


// Implementation

template <typename T>
CDPL::Base::DataWriter<T>& CDPL::Base::DataWriter<T>::operator=(const DataWriter& writer)
{
	if (this == &writer)
		return *this;

	DataIOBase::operator=(writer);

	return *this;
}

// \cond UNHIDE_DETAILS

template <typename T>
CDPL::Base::DataWriter<T>& CDPL::Base::operator<<(DataWriter<T>& writer, const T& obj)
{
	return writer.write(obj);
}

// \endcond

#endif // CDPL_BASE_DATAWRITER_HPP
