/* 
 * StringDataBlock.hpp 
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
 * \brief Definition of class CDPL::Chem::StringDataBlockItem and the type CDPL::Chem::StringDataBlock.
 */

#ifndef CDPL_CHEM_STRINGDATABLOCK_HPP
#define CDPL_CHEM_STRINGDATABLOCK_HPP

#include <string>

#include "CDPL/Chem/APIPrefix.hpp"
#include "CDPL/Util/Array.hpp"


namespace CDPL
{

    namespace Chem
    {

        /**
         * \brief Represents a data item consisting of a header and a data payload.
         *
         * Used to represent the individual entries in the structure or reaction data block of an
         * <em>MDL SD-</em> or \e RD-File record (see [\ref CTFILE]).
         */
        class CDPL_CHEM_API StringDataBlockEntry
        {

          public:
            /**
             * \brief Constructs a \c %StringDataBlockEntry object with an empty data header and content.
             */
            StringDataBlockEntry() {}

            /**
             * \brief Constructs a \c %StringDataBlockEntry object with the specified data header and content.
             * \param header The data header.
             * \param data The data content.
             */
            StringDataBlockEntry(const std::string& header, const std::string& data):
                header(header), data(data) {}

            /**
             * \brief Returns the data header.
             * \returns The data header.
             */
            const std::string& getHeader() const;

            /**
             * \brief Sets the data header.
             * \param header The new data header.
             */
            void setHeader(const std::string& header);

            /**
             * \brief Returns the stored data content.
             * \returns The stored data content.
             */
            const std::string& getData() const;

            /**
             * \brief Sets the data content.
             * \param data The new data content.
             */
            void setData(const std::string& data);

            /**
             * \brief Equality comparison operator.
             * \param entry The other \c %StringDataBlockEntry object to be compared with.
             * \return \c true if the data entry headers and values compare equal, and \c false otherwise. 
             */
            bool operator==(const StringDataBlockEntry& entry) const;

            /**
             * \brief Inequality comparison operator.
             *
             * The result is equivalent to <tt>!(*this == entry)</tt>.
             *
             * \param entry The other \c %StringDataBlockEntry object to be compared with.
             * \return \c true if the data headers and/or values compare non-equal, and \c false otherwise. 
             * \see operator==()
             */
            bool operator!=(const StringDataBlockEntry& entry) const;

            /**
             * \brief Less-than comparison operator (lexicographic ordering by header, then data).
             * \param entry The other \c %StringDataBlockEntry object to be compared with.
             * \return \c true if \c *this is less than \a entry, and \c false otherwise.
             */
            bool operator<(const StringDataBlockEntry& entry) const;

            /**
             * \brief Greater-than comparison operator (lexicographic ordering by header, then data).
             * \param entry The other \c %StringDataBlockEntry object to be compared with.
             * \return \c true if \c *this is greater than \a entry, and \c false otherwise.
             */
            bool operator>(const StringDataBlockEntry& entry) const;

            /**
             * \brief Less-than-or-equal comparison operator (lexicographic ordering by header, then data).
             * \param entry The other \c %StringDataBlockEntry object to be compared with.
             * \return \c true if \c *this is less than or equal to \a entry, and \c false otherwise.
             */
            bool operator<=(const StringDataBlockEntry& entry) const;

            /**
             * \brief Greater-than-or-equal comparison operator (lexicographic ordering by header, then data).
             * \param entry The other \c %StringDataBlockEntry object to be compared with.
             * \return \c true if \c *this is greater than or equal to \a entry, and \c false otherwise.
             */
            bool operator>=(const StringDataBlockEntry& entry) const;

          private:
            std::string header;
            std::string data;
        };

        /**
         * \brief Array of Chem::StringDataBlockEntry objects.
         *
         * Used to store the structure or reaction data block of an <em>MDL SD-</em>
         * or \e RD-File record (see [\ref CTFILE]).
         */
        class CDPL_CHEM_API StringDataBlock : public Util::Array<StringDataBlockEntry>
        {

          public:
            /** \brief A reference-counted smart pointer [\ref SHPTR] for dynamically allocated \c %StringDataBlock instances. */
            typedef std::shared_ptr<StringDataBlock> SharedPointer;

            /**
             * \brief Appends a new entry with the supplied data header and content to the block.
             * \param header The data header of the new entry.
             * \param data The data content of the new entry.
             */
            void addEntry(const std::string& header, const std::string& data)
            {
                addElement(StringDataBlockEntry(header, data));
            }

          private:
            const char* getClassName() const
            {
                return "StringDataBlock";
            }
        };
    } // namespace Chem
} // namespace CDPL

#endif // CDPL_CHEM_STRINGDATABLOCK_HPP
