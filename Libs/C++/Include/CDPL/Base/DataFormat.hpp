/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * DataFormat.hpp 
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
 * \brief Definition of the class CDPL::Base::DataFormat.
 */

#ifndef CDPL_BASE_DATAFORMAT_HPP
#define CDPL_BASE_DATAFORMAT_HPP

#include <cstddef>
#include <string>
#include <vector>

#include "CDPL/Base/APIPrefix.hpp"


namespace CDPL 
{

	namespace Base
	{

		/**
		 * \addtogroup CDPL_BASE_IO
		 * @{
		 */

		/**
		 * \brief Provides meta-information about a particular data storage format.
		 */
		class CDPL_BASE_API DataFormat 
		{

			typedef std::vector<std::string> FileExtensionList;

		public:
			/**
			 * \brief A constant random access iterator used to iterate over the
			 *        list of file extensions.
			 */
			typedef FileExtensionList::const_iterator ConstFileExtensionIterator;

			/**
			 * \brief A mutable random access iterator used to iterate over the
			 *        list of file extensions.
			 */
			typedef FileExtensionList::iterator FileExtensionIterator;

			/**
			 * \brief Constructs and initializes a \c %DataFormat object with the given attributes.
			 * \param name The short-name of the data format, e.g. "PNG".
			 * \param descr A string providing a brief human readable description of the data format, e.g. "Portable Network Graphics".
			 * \param mime_type The mime-type associated with the data format (e.g. "image/png"), or an empty string if the mime-type
			 *                  is not available.
			 * \param file_ext_begin An iterator pointing to the beginning of the file extension list.
			 * \param file_ext_end An iterator pointing to the end of the file extension list.
			 * \param multi_rec \c true if the data format supports the storage of multiple data records, and \c false otherwise.
			 */
			template <typename Iter>
			DataFormat(const std::string& name, const std::string& descr, const std::string& mime_type, 
					   Iter file_ext_begin, Iter file_ext_end, bool multi_rec)
				: name(name), description(descr), mimeType(mime_type), fileExtensions(file_ext_begin, file_ext_end),
				  multiRecordFormat(multi_rec) {}

			/**
			 * \brief Default constructor.
			 *
			 * All string attributes are initialized to an empty string, and the multi record format flag is set to \c false.
			 */
			DataFormat(): multiRecordFormat(false) {}

			/**
			 * \brief Returns the description of the data format.
			 * \return The data format description.
			 */
			const std::string& getDescription() const;

			/**
			 * \brief Sets the description of the data format.
			 * \param descr The data format description.
			 */
			void setDescription(const std::string& descr);

			/**
			 * \brief Returns the short-name of the data format.
			 * \return The short-name of the data format.
			 */
			const std::string& getName() const;

			/**
			 * \brief Sets the short-name of the data format.
			 * \param name The short-name of the data format.
			 */
			void setName(const std::string& name);

			/**
			 * \brief Returns the mime-type of the data format.
			 * \return The mime-type of the data format.
			 */
			const std::string& getMimeType() const;

			/**
			 * \brief Sets the mime-type of the data format.
			 * \param mime_type The mime-type of the data format.
			 */
			void setMimeType(const std::string& mime_type);

			/**
			 * \brief Returns the number of registered file extensions.
			 * \return The number of registered file extensions.
			 */
			std::size_t getNumFileExtensions() const;

			/**
			 * \brief Returns a constant iterator pointing to the beginning of the file extension list.
			 * \return A constant iterator pointing to the beginning of the file extension list.
			 */
			ConstFileExtensionIterator getFileExtensionsBegin() const;

			/**
			 * \brief Returns a constant iterator pointing to the end of the file extension list.
			 * \return A constant iterator pointing to the end of the file extension list.
			 */
			ConstFileExtensionIterator getFileExtensionsEnd() const;

			/**
			 * \brief Returns a mutable iterator pointing to the beginning of the file extension list.
			 * \return A mutable iterator pointing to the beginning of the file extension list.
			 */
			FileExtensionIterator getFileExtensionsBegin();

			/**
			 * \brief Returns a mutable iterator pointing to the end of the file extension list.
			 * \return A mutable iterator pointing to the end of the file extension list.
			 */
			FileExtensionIterator getFileExtensionsEnd();

			/**
			 * \brief Adds \a file_ext to the current list of file extensions.
			 * \param file_ext The file extension to add.
			 */
			DataFormat& addFileExtension(const std::string& file_ext);

			/**
			 * \brief Returns the file extension list entry at index \a idx.
			 * \param idx The zero-based index of the requested file extension list entry.
			 * \return The file extension list entry at index \a idx.
			 * \throw Base::IndexError if \a idx is out of bounds.
			 */
			const std::string& getFileExtension(std::size_t idx) const;

			/**
			 * \brief Sets the file extension list entry at index \a idx to \a file_ext.
			 * \param idx The zero-based index of the file extension list entry to set.
			 * \param file_ext The new file extension list entry.
			 * \throw Base::IndexError if \a idx is out of bounds.
			 */
			void setFileExtension(std::size_t idx, const std::string& file_ext);

			/**
			 * \brief Removes the file extension list entry at index \a idx.
			 * \param idx The zero-based index of the file extension list entry to remove.
			 * \throw Base::IndexError if \a idx is out of bounds.
			 */
			void removeFileExtension(std::size_t idx);

			/**
			 * \brief Removes the file extension list entry pointed to by the iterator \a it.
			 * \param it An iterator pointing to the extension list entry to remove.
			 * \throw Base::RangeError if \a it is not in the range [getFileExtensionsBegin(), getFileExtensionsEnd() - 1].
			 */
			FileExtensionIterator removeFileExtension(const FileExtensionIterator& it);

			/**
			 * \brief Clears the file extension list.
			 */
			void clearFileExtensions();

			/**
			 * \brief Tells whether or not the data format supports the storage of multiple data records.
			 * \return \c true if the data format supports the storage of multiple data records, and \c false otherwise.
			 */
			bool isMultiRecordFormat() const;

			/**
			 * \brief Specifies whether or not the data format supports the storage of multiple data records.
			 * \param multi_rec \c true if the data format supports the storage of multiple data records, and
			 *        \c false otherwise.
			 */
			void setMultiRecordFormat(bool multi_rec);

			/**
			 * \brief Tells whether the name of this data format matches the name specified by \a name.
			 * \param name The name to match.
			 * \return \c true if the name of the data format matches the argument, and \c false otherwise.
			 * \note The name matching is case-insensitive.
			 */
			bool matchesName(const std::string& name) const;

			/**
			 * \brief Tells whether the mime-type of this data format matches the mime-type specified by \a mime_type.
			 * \param mime_type The mime-type to match.
			 * \return \c true if the mime-type of the data format matches the argument, and \c false otherwise.
			 * \note The mime-type matching is case-insensitive.
			 */
			bool matchesMimeType(const std::string& mime_type) const;

			/**
			 * \brief Tells whether \a file_ext is contained in the list of file extensions.
			 * \param file_ext The file extension to search for.
			 * \return \c true if \a file_ext is contained in the list of file extensions, and \c false otherwise.
			 * \note The file extension matching is case-insensitive.
			 */
			bool matchesFileExtension(const std::string& file_ext) const;

			/**
			 * \brief Equality comparison operator.
			 * \param fmt The other \c %DataFormat object to be compared with.
			 * \return \c true if the names and mime-types compare equal (case-insensitive!), and \c false otherwise.
			 */
			bool operator==(const DataFormat& fmt) const;

			/**
			 * \brief Inequality comparison operator.
			 *
			 * The result is equivalent to <tt>!(*this == fmt)</tt>.
			 *
			 * \param fmt The other \c %DataFormat object to be compared with.
			 * \return \c true if the names and/or mime-types compare non-equal (case-insensitive!), and \c false otherwise.
			 * \see operator==()
			 */
			bool operator!=(const DataFormat& fmt) const;

		private:
			std::string       name;
			std::string       description;
			std::string       mimeType;
			FileExtensionList fileExtensions;
			bool              multiRecordFormat;
		};

		/**
		 * @}
		 */
	}
}

#endif // CDPL_BASE_DATAFORMAT_HPP
