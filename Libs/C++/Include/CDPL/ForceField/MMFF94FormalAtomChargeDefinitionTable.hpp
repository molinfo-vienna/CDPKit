/* 
 * MMFF94FormalAtomChargeDefinitionTable.hpp 
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
 * \brief Definition of class CDPL::ForceField::MMFF94FormalAtomChargeDefinitionTable.
 */

#ifndef CDPL_FORCEFIELD_MMFF94FORMALATOMCHARGEDEFINITIONTABLE_HPP
#define CDPL_FORCEFIELD_MMFF94FORMALATOMCHARGEDEFINITIONTABLE_HPP

#include <cstddef>
#include <iosfwd>
#include <string>
#include <vector>
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
         * \brief Lookup table mapping symbolic MMFF94 atom types to their formal-charge definitions used
         *        by the MMFF94 charge model.
         *
         * Each entry specifies a formal charge plus an assignment-mode flag that controls how the charge
         * is distributed across the atom and its neighbours of selected types.
         */
        class CDPL_FORCEFIELD_API MMFF94FormalAtomChargeDefinitionTable
        {

          public:
            class Entry;

          private:
            typedef std::unordered_map<std::string, Entry> DataStorage;

          public:
            /** \brief A reference-counted smart pointer [\ref SHPTR] for dynamically allocated \c %MMFF94FormalAtomChargeDefinitionTable instances. */
            typedef std::shared_ptr<MMFF94FormalAtomChargeDefinitionTable> SharedPointer;

            /**
             * \brief A single formal-charge definition.
             */
            class CDPL_FORCEFIELD_API Entry
            {

              public:
                /**
                 * \brief Constructs an empty (uninitialized) \c %Entry instance.
                 */
                Entry();

                /**
                 * \brief Constructs an \c %Entry for the symbolic MMFF94 atom type \a atom_type.
                 * \param atom_type The symbolic MMFF94 atom type.
                 * \param ass_mode The charge-assignment mode flag.
                 * \param charge The formal charge value.
                 * \param type_list A whitespace-separated list of neighbour atom types used by the assignment.
                 */
                Entry(const std::string& atom_type, std::size_t ass_mode, double charge, const std::string& type_list);

                /**
                 * \brief Returns the symbolic MMFF94 atom type of the entry.
                 * \return A \c const reference to the symbolic atom type.
                 */
                const std::string& getAtomType() const;

                /**
                 * \brief Returns the charge-assignment mode flag.
                 * \return The assignment mode.
                 */
                std::size_t getAssignmentMode() const;

                /**
                 * \brief Returns the formal charge of the entry.
                 * \return The formal charge value.
                 */
                double getFormalCharge() const;

                /**
                 * \brief Returns the whitespace-separated list of neighbour atom types used by the assignment.
                 * \return A \c const reference to the neighbour atom-type list.
                 */
                const std::string& getAtomTypeList() const;

                /**
                 * \brief Tells whether the entry holds initialized data.
                 * \return \c true if the entry was constructed with explicit values, and \c false if it is the empty default.
                 */
                operator bool() const;

              private:
                std::string atomType;
                std::size_t assMode;
                double      charge;
                std::string typeList;
                bool        initialized;
            };

            /** \brief A constant iterator over the entries of the table. */
            typedef boost::transform_iterator<std::function<const Entry&(const DataStorage::value_type&)>,
                                              DataStorage::const_iterator>
                ConstEntryIterator;

            /** \brief A mutable iterator over the entries of the table. */
            typedef boost::transform_iterator<std::function<Entry&(DataStorage::value_type&)>,
                                              DataStorage::iterator>
                EntryIterator;

            /**
             * \brief Constructs an empty \c %MMFF94FormalAtomChargeDefinitionTable instance.
             */
            MMFF94FormalAtomChargeDefinitionTable();

            /**
             * \brief Adds (or overwrites) the formal-charge definition for the symbolic atom type \a atom_type.
             * \param atom_type The symbolic MMFF94 atom type.
             * \param ass_mode The charge-assignment mode flag.
             * \param charge The formal charge value.
             * \param nbr_types A whitespace-separated list of neighbour atom types used by the assignment.
             */
            void addEntry(const std::string& atom_type, std::size_t ass_mode, double charge, const std::string& nbr_types);

            /**
             * \brief Returns the entry for the symbolic MMFF94 atom type \a atom_type.
             * \param atom_type The symbolic MMFF94 atom type.
             * \return A \c const reference to the matching entry, or to an uninitialized entry (whose <tt>operator bool()</tt> returns \c false) if no match exists.
             */
            const Entry& getEntry(const std::string& atom_type) const;

            /**
             * \brief Returns the number of entries in the table.
             * \return The entry count.
             */
            std::size_t getNumEntries() const;

            /**
             * \brief Removes all entries from the table.
             */
            void clear();

            /**
             * \brief Removes the entry for the symbolic atom type \a atom_type.
             * \param atom_type The symbolic MMFF94 atom type.
             * \return \c true if a matching entry was removed, and \c false if no such entry existed.
             */
            bool removeEntry(const std::string& atom_type);

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
             * \brief Loads the built-in default formal-charge definitions.
             */
            void loadDefaults();

            /**
             * \brief Replaces the process-wide default table by \a table.
             * \param table The new default table (a \c nullptr resets to the built-in default).
             */
            static void set(const SharedPointer& table);

            /**
             * \brief Returns the process-wide default table (lazily initialized on first call).
             * \return A \c const reference to the default-table shared pointer.
             */
            static const SharedPointer& get();

          private:
            static SharedPointer defaultTable;
            DataStorage          entries;
        };
    } // namespace ForceField
} // namespace CDPL

#endif // CDPL_FORCEFIELD_MMFF94FORMALATOMCHARGEDEFINITIONTABLE_HPP
