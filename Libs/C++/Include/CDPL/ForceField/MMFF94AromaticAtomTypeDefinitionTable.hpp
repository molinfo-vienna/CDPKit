/* 
 * MMFF94AromaticAtomTypeDefinitionTable.hpp 
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
 * \brief Definition of class CDPL::ForceField::MMFF94AromaticAtomTypeDefinitionTable.
 */

#ifndef CDPL_FORCEFIELD_MMFF94AROMATICATOMTYPEDEFINITIONTABLE_HPP
#define CDPL_FORCEFIELD_MMFF94AROMATICATOMTYPEDEFINITIONTABLE_HPP

#include <cstddef>
#include <vector>
#include <string>
#include <iosfwd>
#include <memory>

#include "CDPL/ForceField/APIPrefix.hpp"


namespace CDPL
{

    namespace ForceField
    {

        /**
         * \brief Data structure for the storage and lookup of MMFF94 aromatic atom type definitions.
         *
         * After the initial pattern-based typing has produced provisional atom types, this table
         * is consulted to upgrade aromatic-ring atoms to their proper MMFF94 aromatic types based on
         * atomic number, ring size, distance to the next heteroatom in the ring, and special-case flags
         * for imidazolium-like cations and 5-ring anions.
         *
         * \see [\ref MMFF94]
         */
        class CDPL_FORCEFIELD_API MMFF94AromaticAtomTypeDefinitionTable
        {

          public:
            class Entry;

          private:
            typedef std::vector<Entry> DataStorage;

          public:
            /**
             * \brief A reference-counted smart pointer [\ref SHPTR] for dynamically allocated \c %MMFF94AromaticAtomTypeDefinitionTable instances.
             */
            typedef std::shared_ptr<MMFF94AromaticAtomTypeDefinitionTable> SharedPointer;

            /**
             * \brief A constant iterator over the entries of the table.
             */
            typedef DataStorage::const_iterator ConstEntryIterator;

            /**
             * \brief A mutable iterator over the entries of the table.
             */
            typedef DataStorage::iterator       EntryIterator;

            /**
             * \brief Data structure for the storage of values associated with a single table entry.
             */
            class CDPL_FORCEFIELD_API Entry
            {

              public:
                /**
                 * \brief Constructs an \c %Entry instance storing the given values.
                 * \param old_type The symbolic provisional atom type assigned by initial typing.
                 * \param aro_type The symbolic MMFF94 aromatic atom type to assign on a match.
                 * \param atomic_no The atomic number required for the match.
                 * \param ring_size The ring size required for the match.
                 * \param het_atom_dist The required topological distance (along the ring) to the next heteroatom.
                 * \param im_cation \c true to restrict the match to imidazolium-like cations.
                 * \param n5_anion \c true to restrict the match to 5-ring anion centers.
                 */
                Entry(const std::string& old_type, const std::string& aro_type, unsigned int atomic_no,
                      std::size_t ring_size, std::size_t het_atom_dist, bool im_cation, bool n5_anion);

                /**
                 * \brief Returns the provisional (input) atom type of the entry.
                 * \return A \c const reference to the provisional atom type.
                 */
                const std::string& getOldAtomType() const;

                /**
                 * \brief Returns the aromatic MMFF94 atom type assigned on a match.
                 * \return A \c const reference to the aromatic atom type.
                 */
                const std::string& getAromAtomType() const;

                /**
                 * \brief Returns the atomic number required for a match.
                 * \return The atomic number.
                 */
                unsigned int getAtomicNumber() const;

                /**
                 * \brief Returns the ring size required for a match.
                 * \return The ring size.
                 */
                std::size_t getRingSize() const;

                /**
                 * \brief Returns the required topological distance (along the ring) to the next heteroatom.
                 * \return The heteroatom distance.
                 */
                std::size_t getHeteroAtomDistance() const;

                /**
                 * \brief Tells whether the match is restricted to imidazolium-like cations.
                 * \return \c true if the match is restricted to imidazolium-like cations, and \c false otherwise.
                 */
                bool isImidazoliumCation() const;

                /**
                 * \brief Tells whether the match is restricted to 5-ring anion centers.
                 * \return \c true if the match is restricted to 5-ring anion centers, and \c false otherwise.
                 */
                bool isN5RingAnion() const;

              private:
                std::string  oldType;
                std::string  aroType;
                unsigned int atomicNumber;
                std::size_t  ringSize;
                std::size_t  hetAtomDist;
                bool         imCation;
                bool         n5Anion;
            };

            /**
             * \brief Constructs an empty \c %MMFF94AromaticAtomTypeDefinitionTable instance.
             */
            MMFF94AromaticAtomTypeDefinitionTable();

            /**
             * \brief Returns the number of entries in the table.
             * \return The entry count.
             */
            std::size_t getNumEntries() const;

            /**
             * \brief Adds a new (or overwrites an existing) entry to the table that stores the given values.
             * \param old_type The symbolic provisional atom type assigned by initial typing.
             * \param aro_type The symbolic MMFF94 aromatic atom type to assign on a match.
             * \param atomic_no The atomic number required for the match.
             * \param ring_size The ring size required for the match.
             * \param het_atom_dist The required topological distance (along the ring) to the next heteroatom.
             * \param im_cation \c true to restrict the match to imidazolium-like cations.
             * \param n5_anion \c true to restrict the match to 5-ring anion centers.
             */
            void addEntry(const std::string& old_type, const std::string& aro_type, unsigned int atomic_no,
                          std::size_t ring_size, std::size_t het_atom_dist, bool im_cation, bool n5_anion);

            /**
             * \brief Returns the entry at index \a idx.
             * \param idx The zero-based entry index.
             * \return A \c const reference to the entry.
             * \throw Base::IndexError if \a idx is not in the range [0, getNumEntries()).
             */
            const Entry& getEntry(std::size_t idx) const;

            /**
             * \brief Removes all entries from the table.
             */
            void clear();

            /**
             * \brief Removes the entry at index \a idx.
             * \param idx The zero-based entry index.
             * \throw Base::IndexError if \a idx is not in the range [0, getNumEntries()).
             */
            void removeEntry(std::size_t idx);

            /**
             * \brief Removes the entry pointed to by the iterator \a it.
             * \param it An iterator pointing to the entry to remove.
             * \return An iterator pointing to the entry immediately following the removed one.
             * \throw Base::RangeError if \a it is not in the range [getEntriesBegin(), getEntriesEnd()).
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
             * \brief Loads table entries from the input stream \a is.
             * \param is The input stream to read from.
             */
            void load(std::istream& is);

            /**
             * \brief Loads the built-in default MMFF94 aromatic atom type definitions.
             */
            void loadDefaults();

            /**
             * \brief Replaces the process-wide default table by \a table.
             * \param table The new default table (a \c nullptr resets to the built-in default).
             */
            static void set(const SharedPointer& table);

            /**
             * \brief Returns the process-wide default table (lazily initialized on first call).
             * \return A shared pointer to the default table.
             */
            static const SharedPointer& get();

          private:
            static SharedPointer defaultTable;
            DataStorage          entries;
        };
    } // namespace ForceField
} // namespace CDPL

#endif // CDPL_FORCEFIELD_MMFF94AROMATICATOMTYPEDEFINITIONTABLE_HPP
