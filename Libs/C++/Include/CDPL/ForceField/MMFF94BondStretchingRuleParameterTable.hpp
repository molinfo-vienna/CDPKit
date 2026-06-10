/* 
 * MMFF94BondStretchingRuleParameterTable.hpp 
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
 * \brief Definition of class CDPL::ForceField::MMFF94BondStretchingRuleParameterTable.
 */

#ifndef CDPL_FORCEFIELD_MMFF94BONDSTRETCHINGRULEPARAMETERTABLE_HPP
#define CDPL_FORCEFIELD_MMFF94BONDSTRETCHINGRULEPARAMETERTABLE_HPP

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
         * \brief Data structure for the storage and lookup of MMFF94 bond-stretching interaction fallback parameters.
         */
        class CDPL_FORCEFIELD_API MMFF94BondStretchingRuleParameterTable
        {

          public:
            class Entry;

          private:
            typedef std::unordered_map<std::uint32_t, Entry> DataStorage;

          public:
            /** \brief A reference-counted smart pointer [\ref SHPTR] for dynamically allocated \c %MMFF94BondStretchingRuleParameterTable instances. */
            typedef std::shared_ptr<MMFF94BondStretchingRuleParameterTable> SharedPointer;

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
                 * \param atomic_no1 The atomic number of the first bonded atom.
                 * \param atomic_no2 The atomic number of the second bonded atom.
                 * \param force_const The bond-stretching force constant.
                 * \param ref_length The reference bond length.
                 */
                Entry(unsigned int atomic_no1, unsigned int atomic_no2, double force_const, double ref_length);

                /**
                 * \brief Returns the atomic number of the first bonded atom.
                 * \return The first atom's atomic number.
                 */
                unsigned int getAtomicNumber1() const;

                /**
                 * \brief Returns the atomic number of the second bonded atom.
                 * \return The second atom's atomic number.
                 */
                unsigned int getAtomicNumber2() const;

                /**
                 * \brief Returns the bond-stretching force constant.
                 * \return The force constant.
                 */
                double getForceConstant() const;

                /**
                 * \brief Returns the reference bond length.
                 * \return The reference bond length.
                 */
                double getReferenceLength() const;

                /**
                 * \brief Tells whether the entry holds initialized data.
                 * \return \c true if the entry was constructed with explicit values, and \c false if it is the empty default.
                 */
                operator bool() const;

              private:
                unsigned int atomicNo1;
                unsigned int atomicNo2;
                double       forceConst;
                double       refLength;
                bool         initialized;
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
             * \brief Constructs an empty \c %MMFF94BondStretchingRuleParameterTable instance.
             */
            MMFF94BondStretchingRuleParameterTable();

            /**
             * \brief Adds a new (or overwrites an existing) entry for the given query and parameter values.
             * \param atomic_no1 The atomic number of the first bonded atom.
             * \param atomic_no2 The atomic number of the second bonded atom.
             * \param force_const The bond-stretching force constant.
             * \param ref_length The reference bond length.
             */
            void addEntry(unsigned int atomic_no1, unsigned int atomic_no2, double force_const, double ref_length);

            /**
             * \brief Returns a reference to the entry matching the specified query values.
             * \param atomic_no1 The atomic number of the first bonded atom.
             * \param atomic_no2 The atomic number of the second bonded atom.
             * \return A \c const reference to the matching entry or to an uninitialized entry if no matching entry exists.
             */
            const Entry& getEntry(unsigned int atomic_no1, unsigned int atomic_no2) const;

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
             * \param atomic_no1 The atomic number of the first bonded atom.
             * \param atomic_no2 The atomic number of the second bonded atom.
             * \return \c true if a matching entry was removed, and \c false if no such entry existed.
             */
            bool removeEntry(unsigned int atomic_no1, unsigned int atomic_no2);

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
             * \brief Loads the built-in default MMFF94 bond-stretching rule parameter entries.
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

#endif // CDPL_FORCEFIELD_MMFF94BONDSTRETCHINGRULEPARAMETERTABLE_HPP
