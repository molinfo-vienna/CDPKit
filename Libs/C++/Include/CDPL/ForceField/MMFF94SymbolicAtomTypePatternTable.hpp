/* 
 * MMFF94SymbolicAtomTypePatternTable.hpp 
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
 * \brief Definition of class CDPL::ForceField::MMFF94SymbolicAtomTypePatternTable.
 */

#ifndef CDPL_FORCEFIELD_MMFF94SYMBOLICATOMTYPEPATTERNTABLE_HPP
#define CDPL_FORCEFIELD_MMFF94SYMBOLICATOMTYPEPATTERNTABLE_HPP

#include <cstddef>
#include <vector>
#include <string>
#include <iosfwd>
#include <memory>

#include "CDPL/ForceField/APIPrefix.hpp"
#include "CDPL/Chem/MolecularGraph.hpp"


namespace CDPL
{

    namespace ForceField
    {

        /**
         * \brief Data structure storing \e SMARTS substructure patterns used to assign symbolic MMFF94 atom types
         *        during atom typing.
         *
         * Each entry pairs a pattern with the symbolic MMFF94 type to assign on a match. Patterns marked as
         * fallback are only considered after no non-fallback pattern matches.
         *
         * \see [\ref MMFF94]
         */
        class CDPL_FORCEFIELD_API MMFF94SymbolicAtomTypePatternTable
        {

          public:
            class Entry;

          private:
            typedef std::vector<Entry> DataStorage;

          public:
            /**
             * \brief A reference-counted smart pointer [\ref SHPTR] for dynamically allocated \c %MMFF94SymbolicAtomTypePatternTable instances.
             */
            typedef std::shared_ptr<MMFF94SymbolicAtomTypePatternTable> SharedPointer;

            /**
             * \brief A constant iterator over the entries of the table.
             */
            typedef DataStorage::const_iterator ConstEntryIterator;

            /**
             * \brief A mutable iterator over the entries of the table.
             */
            typedef DataStorage::iterator       EntryIterator;

            /**
             * \brief A single atom type pattern record.
             */
            class CDPL_FORCEFIELD_API Entry
            {

              public:
                /**
                 * \brief Constructs an \c %Entry pairing the pattern \a ptn with the symbolic type \a sym_type.
                 * \param ptn The substructure pattern.
                 * \param sym_type The symbolic MMFF94 atom type to assign on a match.
                 * \param fallback \c true if the pattern is only to be tried after all non-fallback patterns failed.
                 */
                Entry(const Chem::MolecularGraph::SharedPointer& ptn, const std::string& sym_type, bool fallback);

                /**
                 * \brief Tells whether the pattern is a fallback pattern.
                 * \return \c true if the pattern is a fallback pattern, and \c false otherwise.
                 */
                bool isFallbackType() const;

                /**
                 * \brief Returns the substructure pattern.
                 * \return A \c const reference to the pattern shared pointer.
                 */
                const Chem::MolecularGraph::SharedPointer& getPattern() const;

                /**
                 * \brief Returns the symbolic MMFF94 atom type assigned on a match.
                 * \return A \c const reference to the symbolic atom type.
                 */
                const std::string& getSymbolicType() const;

              private:
                Chem::MolecularGraph::SharedPointer pattern;
                std::string                         symType;
                bool                                fallback;
            };

            /**
             * \brief Constructs an empty \c %MMFF94SymbolicAtomTypePatternTable instance.
             */
            MMFF94SymbolicAtomTypePatternTable();

            /**
             * \brief Returns the number of entries in the table.
             * \return The entry count.
             */
            std::size_t getNumEntries() const;

            /**
             * \brief Appends a new pattern entry to the table.
             * \param ptn The substructure pattern.
             * \param sym_type The symbolic MMFF94 atom type to assign on a match.
             * \param fallback \c true if the pattern is only to be tried after all non-fallback patterns failed.
             */
            void addEntry(const Chem::MolecularGraph::SharedPointer& ptn, const std::string& sym_type, bool fallback);

            /**
             * \brief Returns the entry at the zero-based index \a idx.
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
             * \brief Removes the entry at the zero-based index \a idx.
             * \param idx The zero-based entry index.
             * \throw Base::IndexError if \a idx is not in the range [0, getNumEntries()).
             */
            void removeEntry(std::size_t idx);

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
             * \brief Loads table entries from the input stream \a is.
             * \param is The input stream to read from.
             */
            void load(std::istream& is);

            /**
             * \brief Loads the built-in default MMFF94 atom type patterns.
             */
            void loadDefaults();

            /**
             * \brief Replaces the process-wide default table by \a table.
             * \param table The new default table (a \c nullptr resets to the built-in default).
             */
            static void set(const SharedPointer& table);

            /**
             * \brief Returns the process-wide default table (lazily initialized on first call).
             * \return A \c const reference to the default table shared pointer.
             */
            static const SharedPointer& get();

          private:
            static SharedPointer defaultTable;
            DataStorage          entries;
        };
    } // namespace ForceField
} // namespace CDPL

#endif // CDPL_FORCEFIELD_MMFF94SYMBOLICATOMTYPEPATTERNTABLE_HPP
