/* 
 * MMFF94PrimaryToParameterAtomTypeMap.hpp 
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
 * \brief Definition of class CDPL::ForceField::MMFF94PrimaryToParameterAtomTypeMap.
 */

#ifndef CDPL_FORCEFIELD_MMFF94PRIMARYTOPARAMETERATOMTYPEMAP_HPP
#define CDPL_FORCEFIELD_MMFF94PRIMARYTOPARAMETERATOMTYPEMAP_HPP

#include <iosfwd>
#include <cstddef>
#include <unordered_map>
#include <memory>
#include <functional>

#include <boost/iterator/transform_iterator.hpp>

#include "CDPL/ForceField/APIPrefix.hpp"


namespace CDPL
{

    namespace ForceField
    {

        /**
         * \brief Lookup table mapping each primary numeric MMFF94 atom type to the ordered list of
         *        fallback numeric atom types used when looking up missing interaction parameters.
         */
        class CDPL_FORCEFIELD_API MMFF94PrimaryToParameterAtomTypeMap
        {

          public:
            class Entry;

          private:
            typedef std::unordered_map<unsigned int, Entry> DataStorage;

          public:
            /** \brief A reference-counted smart pointer [\ref SHPTR] for dynamically allocated \c %MMFF94PrimaryToParameterAtomTypeMap instances. */
            typedef std::shared_ptr<MMFF94PrimaryToParameterAtomTypeMap> SharedPointer;

            /**
             * \brief A single primary-to-parameter atom type-map record.
             */
            class CDPL_FORCEFIELD_API Entry
            {

              public:
                /** \brief Number of parameter atom types stored per entry. */
                static constexpr std::size_t NUM_TYPES = 4;

                /**
                 * \brief Constructs an empty (uninitialized) \c %Entry instance.
                 */
                Entry();

                /**
                 * \brief Constructs an \c %Entry for the primary atom type \a atom_type with the fallback list \a param_types.
                 * \param atom_type The primary numeric MMFF94 atom type.
                 * \param param_types A length-\c NUM_TYPES array of fallback parameter atom types.
                 */
                Entry(unsigned int atom_type, unsigned int param_types[]);

                /**
                 * \brief Returns the primary numeric MMFF94 atom type of the entry.
                 * \return The primary atom type.
                 */
                unsigned int getAtomType() const;

                /**
                 * \brief Returns a pointer to the fallback parameter-atom type array of length \c NUM_TYPES.
                 * \return A pointer to the parameter-type array.
                 */
                const unsigned int* getParameterTypes() const;

                /**
                 * \brief Tells whether the entry holds initialized data.
                 * \return \c true if the entry was constructed with explicit values, and \c false if it is the empty default.
                 */
                operator bool() const;

              private:
                unsigned int atomType;
                unsigned int paramTypes[NUM_TYPES];
                bool         initialized;
            };

            /** \brief A constant iterator over the entries of the map. */
            typedef boost::transform_iterator<std::function<const Entry&(const DataStorage::value_type&)>,
                                              DataStorage::const_iterator>
                ConstEntryIterator;

            /** \brief A mutable iterator over the entries of the map. */
            typedef boost::transform_iterator<std::function<Entry&(DataStorage::value_type&)>,
                                              DataStorage::iterator>
                EntryIterator;

            /**
             * \brief Constructs an empty \c %MMFF94PrimaryToParameterAtomTypeMap instance.
             */
            MMFF94PrimaryToParameterAtomTypeMap();

            /**
             * \brief Adds (or overwrites) the entry for the primary atom type \a atom_type.
             * \param atom_type The primary numeric MMFF94 atom type.
             * \param param_types A length-\c Entry::NUM_TYPES array of fallback parameter atom types.
             */
            void addEntry(unsigned int atom_type, unsigned int param_types[]);

            /**
             * \brief Returns the entry for the primary atom type \a atom_type.
             * \param atom_type The primary numeric MMFF94 atom type.
             * \return A \c const reference to the matching entry, or to an uninitialized entry (whose <tt>operator bool()</tt> returns \c false) if no match exists.
             */
            const Entry& getEntry(unsigned int atom_type) const;

            /**
             * \brief Returns the number of entries stored in the map.
             * \return The entry count.
             */
            std::size_t getNumEntries() const;

            /**
             * \brief Removes all entries from the map.
             */
            void clear();

            /**
             * \brief Removes the entry for the primary atom type \a atom_type.
             * \param atom_type The primary numeric MMFF94 atom type.
             * \return \c true if a matching entry was removed, and \c false if no such entry existed.
             */
            bool removeEntry(unsigned int atom_type);

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
             * \brief Loads the built-in default primary-to-parameter atom type mappings.
             */
            void loadDefaults();

            /**
             * \brief Replaces the process-wide default map by \a table.
             * \param table The new default map (a \c nullptr resets to the built-in default).
             */
            static void set(const SharedPointer& table);

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

#endif // CDPL_FORCEFIELD_MMFF94PRIMARYTOPARAMETERATOMTYPEMAP_HPP
