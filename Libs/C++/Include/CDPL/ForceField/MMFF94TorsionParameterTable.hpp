/* 
 * MMFF94TorsionParameterTable.hpp 
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
 * \brief Definition of class CDPL::ForceField::MMFF94TorsionParameterTable.
 */

#ifndef CDPL_FORCEFIELD_MMFF94TORSIONPARAMETERTABLE_HPP
#define CDPL_FORCEFIELD_MMFF94TORSIONPARAMETERTABLE_HPP

#include <cstddef>
#include <cstdint>
#include <iosfwd>
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
         * \brief Data structure for the storage and lookup of MMFF94 torsion interaction parameters.
         * \see [\ref MMFF94]
         */
        class CDPL_FORCEFIELD_API MMFF94TorsionParameterTable
        {

          public:
            class Entry;

          private:
            typedef std::unordered_map<std::uint64_t, Entry> DataStorage;

          public:
            /**
             * \brief A reference-counted smart pointer [\ref SHPTR] for dynamically allocated \c %MMFF94TorsionParameterTable instances.
             */
            typedef std::shared_ptr<MMFF94TorsionParameterTable> SharedPointer;

            /**
             * \brief Data structure for the storage of values associated with a single table entry.
             */
            class CDPL_FORCEFIELD_API Entry
            {

              public:
                /**
                 * \brief Constructs an empty (uninitialized) \c %Entry instance.
                 */
                Entry();

                /**
                 * \brief Constructs an \c %Entry instance storing the given query and parameter values.
                 * \param tor_type_idx The MMFF94 torsion type index.
                 * \param term_atom1_type The numeric MMFF94 atom type of the first terminal atom.
                 * \param ctr_atom1_type The numeric MMFF94 atom type of the first center atom.
                 * \param ctr_atom2_type The numeric MMFF94 atom type of the second center atom.
                 * \param term_atom2_type The numeric MMFF94 atom type of the second terminal atom.
                 * \param tor_param1 The torsion-energy parameter \c V1.
                 * \param tor_param2 The torsion-energy parameter \c V2.
                 * \param tor_param3 The torsion-energy parameter \c V3.
                 */
                Entry(unsigned int tor_type_idx, unsigned int term_atom1_type, unsigned int ctr_atom1_type, unsigned int ctr_atom2_type,
                      unsigned int term_atom2_type, double tor_param1, double tor_param2, double tor_param3);

                /**
                 * \brief Returns the MMFF94 torsion type index.
                 * \return The torsion type index.
                 */
                unsigned int getTorsionTypeIndex() const;

                /**
                 * \brief Returns the numeric MMFF94 atom type of the first terminal atom.
                 * \return The first terminal atom's numeric MMFF94 type.
                 */
                unsigned int getTerminalAtom1Type() const;

                /**
                 * \brief Returns the numeric MMFF94 atom type of the first center atom.
                 * \return The first center atom's numeric MMFF94 type.
                 */
                unsigned int getCenterAtom1Type() const;

                /**
                 * \brief Returns the numeric MMFF94 atom type of the second center atom.
                 * \return The second center atom's numeric MMFF94 type.
                 */
                unsigned int getCenterAtom2Type() const;

                /**
                 * \brief Returns the numeric MMFF94 atom type of the second terminal atom.
                 * \return The second terminal atom's numeric MMFF94 type.
                 */
                unsigned int getTerminalAtom2Type() const;

                /**
                 * \brief Returns the torsion-energy parameter \c V1.
                 * \return The \c V1 parameter.
                 */
                double getTorsionParameter1() const;

                /**
                 * \brief Returns the torsion-energy parameter \c V2.
                 * \return The \c V2 parameter.
                 */
                double getTorsionParameter2() const;

                /**
                 * \brief Returns the torsion-energy parameter \c V3.
                 * \return The \c V3 parameter.
                 */
                double getTorsionParameter3() const;

                /**
                 * \brief Tells whether the entry holds initialized data.
                 * \return \c true if the entry was constructed with explicit values, and \c false if it is the empty default.
                 */
                operator bool() const;

              private:
                unsigned int torTypeIdx;
                unsigned int termAtom1Type;
                unsigned int ctrAtom1Type;
                unsigned int ctrAtom2Type;
                unsigned int termAtom2Type;
                double       torParam1;
                double       torParam2;
                double       torParam3;
                bool         initialized;
            };

            /**
             * \brief A constant iterator over the entries of the table.
             */
            typedef boost::transform_iterator<std::function<const Entry&(const DataStorage::value_type&)>,
                                              DataStorage::const_iterator>
                ConstEntryIterator;

            /**
             * \brief A mutable iterator over the entries of the table.
             */
            typedef boost::transform_iterator<std::function<Entry&(DataStorage::value_type&)>,
                                              DataStorage::iterator>
                EntryIterator;

            /**
             * \brief Constructs an empty \c %MMFF94TorsionParameterTable instance.
             */
            MMFF94TorsionParameterTable();

            /**
             * \brief Adds a new (or overwrites an existing) entry for the given query and parameter values.
             * \param tor_type_idx The MMFF94 torsion type index.
             * \param term_atom1_type The numeric MMFF94 atom type of the first terminal atom.
             * \param ctr_atom1_type The numeric MMFF94 atom type of the first center atom.
             * \param ctr_atom2_type The numeric MMFF94 atom type of the second center atom.
             * \param term_atom2_type The numeric MMFF94 atom type of the second terminal atom.
             * \param tor_param1 The torsion-energy parameter \c V1.
             * \param tor_param2 The torsion-energy parameter \c V2.
             * \param tor_param3 The torsion-energy parameter \c V3.
             */
            void addEntry(unsigned int tor_type_idx, unsigned int term_atom1_type, unsigned int ctr_atom1_type, unsigned int ctr_atom2_type,
                          unsigned int term_atom2_type, double tor_param1, double tor_param2, double tor_param3);

            /**
             * \brief Returns a reference to the entry matching the specified query values.
             * \param tor_type_idx The MMFF94 torsion type index.
             * \param term_atom1_type The numeric MMFF94 atom type of the first terminal atom.
             * \param ctr_atom1_type The numeric MMFF94 atom type of the first center atom.
             * \param ctr_atom2_type The numeric MMFF94 atom type of the second center atom.
             * \param term_atom2_type The numeric MMFF94 atom type of the second terminal atom.
             * \return A \c const reference to the matching entry or to an uninitialized entry if no matching entry exists.
             */
            const Entry& getEntry(unsigned int tor_type_idx, unsigned int term_atom1_type, unsigned int ctr_atom1_type, unsigned int ctr_atom2_type,
                                  unsigned int term_atom2_type) const;

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
             * \brief Removes the entry matching the specified query values.
             * \param tor_type_idx The MMFF94 torsion type index.
             * \param term_atom1_type The numeric MMFF94 atom type of the first terminal atom.
             * \param ctr_atom1_type The numeric MMFF94 atom type of the first center atom.
             * \param ctr_atom2_type The numeric MMFF94 atom type of the second center atom.
             * \param term_atom2_type The numeric MMFF94 atom type of the second terminal atom.
             * \return \c true if a matching entry was removed, and \c false if no such entry existed.
             */
            bool removeEntry(unsigned int tor_type_idx, unsigned int term_atom1_type, unsigned int ctr_atom1_type, unsigned int ctr_atom2_type,
                             unsigned int term_atom2_type);

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
             * \brief Loads the built-in default torsion parameter entries for the specified MMFF94 parameter set.
             * \param param_set The parameter set identifier (see namespace ForceField::MMFF94ParameterSet) selecting which built-in defaults to load.
             */
            void loadDefaults(unsigned int param_set);

            /**
             * \brief Replaces the process-wide default table for \a param_set by \a table.
             * \param table The new default table (a \c nullptr resets to the built-in default).
             * \param param_set The parameter set identifier (see namespace ForceField::MMFF94ParameterSet) selecting which default slot to replace.
             */
            static void set(const SharedPointer& table, unsigned int param_set);

            /**
             * \brief Returns the process-wide default table for \a param_set (lazily initialized on first call).
             * \param param_set The parameter set identifier (see namespace ForceField::MMFF94ParameterSet) selecting which default slot to return.
             * \return A shared pointer to the selected default table.
             */
            static const SharedPointer& get(unsigned int param_set);

          private:
            static SharedPointer defaultDynTable;
            static SharedPointer defaultStatTable;
            static SharedPointer defaultStatRefTable;
            DataStorage          entries;
        };
    } // namespace ForceField
} // namespace CDPL

#endif // CDPL_FORCEFIELD_MMFF94TORSIONPARAMETERTABLE_HPP
