/* 
 * MMFF94HeavyToHydrogenAtomTypeMap.hpp 
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
 * \brief Definition of class CDPL::ForceField::MMFF94HeavyToHydrogenAtomTypeMap.
 */

#ifndef CDPL_FORCEFIELD_MMFF94HEAVYTOHYDROGENATOMTYPEMAP_HPP
#define CDPL_FORCEFIELD_MMFF94HEAVYTOHYDROGENATOMTYPEMAP_HPP

#include <string>
#include <iosfwd>
#include <cstddef>
#include <unordered_map>
#include <memory>

#include "CDPL/ForceField/APIPrefix.hpp"


namespace CDPL
{

    namespace ForceField
    {

        /**
         * \brief Lookup table mapping each heavy atom symbolic MMFF94 type to the symbolic MMFF94 type
         *        used for hydrogen atoms bonded to it.
         */
        class CDPL_FORCEFIELD_API MMFF94HeavyToHydrogenAtomTypeMap
        {

            typedef std::unordered_map<std::string, std::string> DataStorage;

          public:
            /** \brief A reference-counted smart pointer [\ref SHPTR] for dynamically allocated \c %MMFF94HeavyToHydrogenAtomTypeMap instances. */
            typedef std::shared_ptr<MMFF94HeavyToHydrogenAtomTypeMap> SharedPointer;

            /** \brief A constant iterator over the entries of the map. */
            typedef DataStorage::const_iterator ConstEntryIterator;
            /** \brief A mutable iterator over the entries of the map. */
            typedef DataStorage::iterator       EntryIterator;
            /** \brief The map entry type (a (parent type, hydrogen type) key/value pair). */
            typedef DataStorage::value_type     Entry;

            /**
             * \brief Constructs an empty \c %MMFF94HeavyToHydrogenAtomTypeMap instance.
             */
            MMFF94HeavyToHydrogenAtomTypeMap();

            /**
             * \brief Adds (or overwrites) the heavy atom-to-hydrogen-type mapping for \a parent_type.
             * \param parent_type The symbolic MMFF94 type of the heavy parent atom.
             * \param hyd_type The symbolic MMFF94 type to assign to hydrogen atoms bonded to such parents.
             */
            void addEntry(const std::string& parent_type, const std::string& hyd_type);

            /**
             * \brief Returns the hydrogen MMFF94 type associated with the heavy atom type \a parent_type.
             * \param parent_type The symbolic MMFF94 type of the heavy parent atom.
             * \return A \c const reference to the symbolic hydrogen type, or to an empty string if no mapping exists.
             */
            const std::string& getEntry(const std::string& parent_type) const;

            /**
             * \brief Returns the number of mappings stored in the map.
             * \return The entry count.
             */
            std::size_t getNumEntries() const;

            /**
             * \brief Removes all entries from the map.
             */
            void clear();

            /**
             * \brief Removes the mapping for the heavy atom type \a parent_type.
             * \param parent_type The symbolic MMFF94 type of the heavy parent atom.
             * \return \c true if a matching entry was removed, and \c false if no such entry existed.
             */
            bool removeEntry(const std::string& parent_type);

            /**
             * \brief Removes the entry pointed to by the iterator \a it.
             * \param it An iterator pointing to the entry to remove.
             * \return An iterator pointing to the entry immediately following the removed one.
             */
            EntryIterator removeEntry(const EntryIterator& it);

            /**
             * \brief Returns a constant iterator pointing to the beginning of the entry list.
             * \return A constant iterator to the first entry.
             */
            ConstEntryIterator getEntriesBegin() const;

            /**
             * \brief Returns a constant iterator pointing one past the last entry.
             * \return A constant iterator to the end of the entry list.
             */
            ConstEntryIterator getEntriesEnd() const;

            /**
             * \brief Returns a mutable iterator pointing to the beginning of the entry list.
             * \return A mutable iterator to the first entry.
             */
            EntryIterator getEntriesBegin();

            /**
             * \brief Returns a mutable iterator pointing one past the last entry.
             * \return A mutable iterator to the end of the entry list.
             */
            EntryIterator getEntriesEnd();

            /**
             * \brief Returns a constant iterator pointing to the beginning of the entry list (alias of getEntriesBegin()).
             * \return A constant iterator to the first entry.
             */
            ConstEntryIterator begin() const;

            /**
             * \brief Returns a constant iterator pointing one past the last entry (alias of getEntriesEnd()).
             * \return A constant iterator to the end of the entry list.
             */
            ConstEntryIterator end() const;

            /**
             * \brief Returns a mutable iterator pointing to the beginning of the entry list (alias of getEntriesBegin()).
             * \return A mutable iterator to the first entry.
             */
            EntryIterator begin();

            /**
             * \brief Returns a mutable iterator pointing one past the last entry (alias of getEntriesEnd()).
             * \return A mutable iterator to the end of the entry list.
             */
            EntryIterator end();

            /**
             * \brief Loads map entries from the input stream \a is.
             * \param is The input stream to read from.
             */
            void load(std::istream& is);

            /**
             * \brief Loads the built-in default heavy-to-hydrogen atom type mappings.
             */
            void loadDefaults();

            /**
             * \brief Replaces the process-wide default map by \a map.
             * \param map The new default map (a \c nullptr resets to the built-in default).
             */
            static void set(const SharedPointer& map);

            /**
             * \brief Returns the process-wide default map (lazily initialized on first call).
             * \return A \c const reference to the default-map shared pointer.
             */
            static const SharedPointer& get();

          private:
            static SharedPointer defaultMap;
            DataStorage          entries;
        };
    } // namespace ForceField
} // namespace CDPL

#endif // CDPL_FORCEFIELD_MMFF94HEAVYTOHYDROGENATOMTYPEMAP_HPP
