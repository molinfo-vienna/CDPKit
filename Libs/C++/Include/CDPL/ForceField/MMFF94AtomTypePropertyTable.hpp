/* 
 * MMFF94AtomTypePropertyTable.hpp 
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
 * \brief Definition of class CDPL::ForceField::MMFF94AtomTypePropertyTable.
 */

#ifndef CDPL_FORCEFIELD_MMFF94ATOMTYPEPROPERTYTABLE_HPP
#define CDPL_FORCEFIELD_MMFF94ATOMTYPEPROPERTYTABLE_HPP

#include <cstddef>
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
         * \brief Data structure for the storage and lookup of structural and chemical
         *        property data associated with numeric MMFF94 atom types.
         *
         * Each entry provides the corresponding atomic number, the standard neighbour count and valence,
         * and flags describing pi lone pair character, aromaticity, linear bond angle geometry, and the
         * ability to form multi bond or single bond patterns.
         */
        class CDPL_FORCEFIELD_API MMFF94AtomTypePropertyTable
        {

          public:
            class Entry;

          private:
            typedef std::unordered_map<unsigned int, Entry> DataStorage;

          public:
            /** \brief A reference-counted smart pointer [\ref SHPTR] for dynamically allocated \c %MMFF94AtomTypePropertyTable instances. */
            typedef std::shared_ptr<MMFF94AtomTypePropertyTable> SharedPointer;

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
                 * \brief Constructs an \c %Entry instance storing the given values.
                 * \param atom_type The numeric MMFF94 atom type.
                 * \param atomic_no The atomic number of atoms of this type.
                 * \param num_nbrs The standard number of explicit neighbour atoms.
                 * \param valence The standard valence.
                 * \param has_pi_lp \c true if the atom type carries a pi lone pair.
                 * \param mltb_desig The MMFF94 multi bond designator.
                 * \param is_arom \c true if the atom type is aromatic.
                 * \param lin_bnd_ang \c true if the atom type forms linear bond angles.
                 * \param has_mb_or_sb \c true if the atom type can form multi bond or single bond patterns.
                 */
                Entry(unsigned int atom_type, unsigned int atomic_no, std::size_t num_nbrs, std::size_t valence,
                      bool has_pi_lp, unsigned int mltb_desig, bool is_arom, bool lin_bnd_ang, bool has_mb_or_sb);

                /**
                 * \brief Returns the numeric MMFF94 atom type of the entry.
                 * \return The numeric atom type.
                 */
                unsigned int getAtomType() const;

                /**
                 * \brief Returns the atomic number of atoms of this type.
                 * \return The atomic number.
                 */
                unsigned int getAtomicNumber() const;

                /**
                 * \brief Returns the standard number of explicit neighbour atoms.
                 * \return The neighbour count.
                 */
                std::size_t getNumNeighbors() const;

                /**
                 * \brief Returns the standard valence of atoms of this type.
                 * \return The valence.
                 */
                std::size_t getValence() const;

                /**
                 * \brief Tells whether the atom type carries a pi lone pair.
                 * \return \c true if the atom type carries a pi lone pair, and \c false otherwise.
                 */
                bool hasPiLonePair() const;

                /**
                 * \brief Returns the MMFF94 multi bond designator.
                 * \return The multi bond designator.
                 */
                unsigned int getMultiBondDesignator() const;

                /**
                 * \brief Tells whether the atom type is aromatic.
                 * \return \c true if the atom type is aromatic, and \c false otherwise.
                 */
                bool isAromaticAtomType() const;

                /**
                 * \brief Tells whether the atom type forms linear bond angles.
                 * \return \c true if the atom type forms linear bond angles, and \c false otherwise.
                 */
                bool formsLinearBondAngle() const;

                /**
                 * \brief Tells whether the atom type can form multi bond or single bond patterns.
                 * \return \c true if such patterns are allowed, and \c false otherwise.
                 */
                bool formsMultiOrSingleBonds() const;

                /**
                 * \brief Tells whether the entry holds initialized data.
                 * \return \c true if the entry was constructed with explicit values, and \c false if it is the empty default.
                 */
                operator bool() const;

              private:
                unsigned int atomType;
                unsigned int atomicNo;
                std::size_t  numNeighbors;
                std::size_t  valence;
                bool         hasPiLonePr;
                unsigned int mltbDesig;
                bool         isAroType;
                bool         hasLinBondAng;
                bool         hasMultiOrSingleBonds;
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
             * \brief Constructs an empty \c %MMFF94AtomTypePropertyTable instance.
             */
            MMFF94AtomTypePropertyTable();

            /**
             * \brief Adds a new (or overwrites an existing) entry for the numeric MMFF94 atom type \a atom_type that stores the given property values.
             * \param atom_type The numeric MMFF94 atom type. 
             * \param atomic_no The atomic number of atoms of this type.
             * \param num_nbrs The standard number of explicit neighbour atoms.
             * \param valence The standard valence.
             * \param has_pi_lp \c true if the atom type carries a pi lone pair.
             * \param mltb_desig The MMFF94 multi bond designator.
             * \param is_arom \c true if the atom type is aromatic.
             * \param lin_bnd_ang \c true if the atom type forms linear bond angles.
             * \param has_mb_or_sb \c true if the atom type can form multi bond or single bond patterns.
             */
            void addEntry(unsigned int atom_type, unsigned int atomic_no, std::size_t num_nbrs, std::size_t valence,
                          bool has_pi_lp, unsigned int mltb_desig, bool is_arom, bool lin_bnd_ang, bool has_mb_or_sb);

            /**
             * \brief Returns the entry for the numeric MMFF94 atom type \a atom_type.
             * \param atom_type The numeric MMFF94 atom type.
             * \return A \c const reference to the matching entry or to an uninitialized entry if no matching entry exists.
             */
            const Entry& getEntry(unsigned int atom_type) const;

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
             * \brief Removes the entry for the numeric MMFF94 atom type \a atom_type.
             * \param atom_type The numeric MMFF94 atom type.
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
             * \brief Loads table entries from the input stream \a is.
             * \param is The input stream to read from.
             */
            void load(std::istream& is);

            /**
             * \brief Loads the built-in default MMFF94 atom type property entries.
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

#endif // CDPL_FORCEFIELD_MMFF94ATOMTYPEPROPERTYTABLE_HPP
