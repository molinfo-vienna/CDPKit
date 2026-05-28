/* 
 * MMFF94DefaultStretchBendParameterTable.hpp 
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
 * \brief Definition of class CDPL::ForceField::MMFF94DefaultStretchBendParameterTable.
 */

#ifndef CDPL_FORCEFIELD_MMFF94DEFAULTSTRETCHBENDPARAMETERTABLE_HPP
#define CDPL_FORCEFIELD_MMFF94DEFAULTSTRETCHBENDPARAMETERTABLE_HPP

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
         * \brief Lookup table mapping (terminal-atom-1 PTE row, center-atom PTE row, terminal-atom-2 PTE row) triples
         *        to fallback MMFF94 stretch-bend coupling force constants used when no atom-type-specific entry is available.
         *
         * The PTE row of an atom is the row index in the periodic table of the elements. Two directional force constants
         * are stored per entry (\c IJK and \c KJI) — see Util::MMFF94StretchBendParameterTable for the coupling semantics.
         */
        class CDPL_FORCEFIELD_API MMFF94DefaultStretchBendParameterTable
        {

          public:
            class Entry;

          private:
            typedef std::unordered_map<std::uint32_t, Entry> DataStorage;

          public:
            /** \brief A reference-counted smart pointer [\ref SHPTR] for dynamically allocated \c %MMFF94DefaultStretchBendParameterTable instances. */
            typedef std::shared_ptr<MMFF94DefaultStretchBendParameterTable> SharedPointer;

            /**
             * \brief A single PTE-row-based default stretch-bend parameter record.
             */
            class CDPL_FORCEFIELD_API Entry
            {

              public:
                /**
                 * \brief Constructs an empty (uninitialized) \c %Entry instance.
                 */
                Entry();

                /**
                 * \brief Constructs an \c %Entry for the given (terminal-atom 1 PTE row, center-atom PTE row, terminal-atom 2 PTE row) triple.
                 * \param term_atom1_pte_row The PTE row of the first terminal atom.
                 * \param ctr_atom_pte_row The PTE row of the center atom.
                 * \param term_atom2_pte_row The PTE row of the second terminal atom.
                 * \param ijk_force_const The IJK stretch-bend force constant.
                 * \param kji_force_const The KJI stretch-bend force constant.
                 */
                Entry(unsigned int term_atom1_pte_row, unsigned int ctr_atom_pte_row,
                      unsigned int term_atom2_pte_row, double ijk_force_const, double kji_force_const);

                /**
                 * \brief Returns the PTE row of the first terminal atom.
                 * \return The first terminal atom's PTE row.
                 */
                unsigned int getTerminalAtom1PTERow() const;

                /**
                 * \brief Returns the PTE row of the center atom.
                 * \return The center atom's PTE row.
                 */
                unsigned int getCenterAtomPTERow() const;

                /**
                 * \brief Returns the PTE row of the second terminal atom.
                 * \return The second terminal atom's PTE row.
                 */
                unsigned int getTerminalAtom2PTERow() const;

                /**
                 * \brief Returns the IJK stretch-bend force constant.
                 * \return The IJK force constant.
                 */
                double getIJKForceConstant() const;

                /**
                 * \brief Returns the KJI stretch-bend force constant.
                 * \return The KJI force constant.
                 */
                double getKJIForceConstant() const;

                /**
                 * \brief Tells whether the entry holds initialized data.
                 * \return \c true if the entry was constructed with explicit values, and \c false if it is the empty default.
                 */
                operator bool() const;

              private:
                unsigned int termAtom1PTERow;
                unsigned int ctrAtomPTERow;
                unsigned int termAtom2PTERow;
                double       ijkForceConst;
                double       kjiForceConst;
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
             * \brief Constructs an empty \c %MMFF94DefaultStretchBendParameterTable instance.
             */
            MMFF94DefaultStretchBendParameterTable();

            /**
             * \brief Adds (or overwrites) the entry for the given (terminal-atom 1 PTE row, center-atom PTE row, terminal-atom 2 PTE row) triple.
             * \param term_atom1_pte_row The PTE row of the first terminal atom.
             * \param ctr_atom_pte_row The PTE row of the center atom.
             * \param term_atom2_pte_row The PTE row of the second terminal atom.
             * \param ijk_force_const The IJK stretch-bend force constant.
             * \param kji_force_const The KJI stretch-bend force constant.
             */
            void addEntry(unsigned int term_atom1_pte_row, unsigned int ctr_atom_pte_row,
                          unsigned int term_atom2_pte_row, double ijk_force_const, double kji_force_const);

            /**
             * \brief Returns the entry for the given (terminal-atom 1 PTE row, center-atom PTE row, terminal-atom 2 PTE row) triple.
             * \param term_atom1_pte_row The PTE row of the first terminal atom.
             * \param ctr_atom_pte_row The PTE row of the center atom.
             * \param term_atom2_pte_row The PTE row of the second terminal atom.
             * \return A \c const reference to the matching entry, or to an uninitialized entry (whose <tt>operator bool()</tt> returns \c false) if no match exists.
             */
            const Entry& getEntry(unsigned int term_atom1_pte_row, unsigned int ctr_atom_pte_row,
                                  unsigned int term_atom2_pte_row) const;

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
             * \brief Removes the entry for the given (terminal-atom 1 PTE row, center-atom PTE row, terminal-atom 2 PTE row) triple.
             * \param term_atom1_pte_row The PTE row of the first terminal atom.
             * \param ctr_atom_pte_row The PTE row of the center atom.
             * \param term_atom2_pte_row The PTE row of the second terminal atom.
             * \return \c true if a matching entry was removed, and \c false if no such entry existed.
             */
            bool removeEntry(unsigned int term_atom1_pte_row, unsigned int ctr_atom_pte_row,
                             unsigned int term_atom2_pte_row);

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
             * \brief Loads the built-in default stretch-bend fallback entries.
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

#endif // CDPL_FORCEFIELD_MMFF94DEFAULTSTRETCHBENDPARAMETERTABLE_HPP
