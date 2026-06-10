/* 
 * UFFAtomTypePropertyTable.hpp 
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
 * \brief Definition of class CDPL::ForceField::UFFAtomTypePropertyTable.
 */

#ifndef CDPL_FORCEFIELD_UFFATOMTYPEPROPERTYTABLE_HPP
#define CDPL_FORCEFIELD_UFFATOMTYPEPROPERTYTABLE_HPP

#include <cstddef>
#include <string>
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
         * \brief Data structure for the storage and lookup of various properties associated with numeric UFF atom types.
         *
         * Each entry provides the natural bond radius and bond angle of the atom type, its Van der Waals
         * parameters (well distance, well depth, and scaling factor), and the effective atomic charge used
         * by the UFF electrostatic terms.
         *
         * \see [\ref UFF]
         */
        class CDPL_FORCEFIELD_API UFFAtomTypePropertyTable
        {

          public:
            class Entry;

          private:
            typedef std::unordered_map<unsigned int, Entry> DataStorage;

          public:
            /** \brief A reference-counted smart pointer [\ref SHPTR] for dynamically allocated \c %UFFAtomTypePropertyTable instances. */
            typedef std::shared_ptr<UFFAtomTypePropertyTable> SharedPointer;

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
                 * \param atom_type The numeric UFF atom type.
                 * \param atom_type_sym The UFF atom type symbol.
                 * \param atomic_no The atomic number of atoms of this type.
                 * \param bond_rad The natural bond radius.
                 * \param bond_ang The natural bond angle.
                 * \param vdw_dist The Van der Waals distance parameter (well distance).
                 * \param vdw_energy The Van der Waals energy parameter (well depth).
                 * \param vdw_scale The Van der Waals scaling factor.
                 * \param eff_charge The effective atomic charge used by the UFF electrostatic terms.
                 */
                Entry(unsigned int atom_type, const std::string& atom_type_sym, unsigned int atomic_no, double bond_rad,
                      double bond_ang, double vdw_dist, double vdw_energy, double vdw_scale, double eff_charge);

                /**
                 * \brief Returns the numeric UFF atom type of the entry.
                 * \return The numeric atom type.
                 */
                unsigned int getAtomType() const;

                /**
                 * \brief Returns the UFF atom type symbol.
                 * \return A \c const reference to the atom type symbol.
                 */
                const std::string& getAtomTypeSymbol() const;

                /**
                 * \brief Returns the atomic number of atoms of this type.
                 * \return The atomic number.
                 */
                unsigned int getAtomicNumber() const;

                /**
                 * \brief Returns the natural bond radius of the atom type.
                 * \return The bond radius.
                 */
                double getBondRadius() const;

                /**
                 * \brief Returns the natural bond angle of the atom type.
                 * \return The bond angle.
                 */
                double getBondAngle() const;

                /**
                 * \brief Returns the Van der Waals well distance of the atom type.
                 * \return The Van der Waals distance parameter.
                 */
                double getVdWDistance() const;

                /**
                 * \brief Returns the Van der Waals well depth of the atom type.
                 * \return The Van der Waals energy parameter.
                 */
                double getVdWEnergy() const;

                /**
                 * \brief Returns the Van der Waals scaling factor of the atom type.
                 * \return The Van der Waals scaling factor.
                 */
                double getVdWScale() const;

                /**
                 * \brief Returns the effective atomic charge used by the UFF electrostatic terms.
                 * \return The effective atomic charge.
                 */
                double getEffectiveCharge() const;

                /**
                 * \brief Tells whether the entry holds initialized data.
                 * \return \c true if the entry was constructed with explicit values, and \c false if it is the empty default.
                 */
                operator bool() const;

              private:
                unsigned int atomType;
                std::string  atomTypeSym;
                unsigned int atomicNo;
                double       bondRadius;
                double       bondAngle;
                double       vdwDistance;
                double       vdwEnergy;
                double       vdwScale;
                double       effCharge;
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
             * \brief Constructs an empty \c %UFFAtomTypePropertyTable instance.
             */
            UFFAtomTypePropertyTable();

            /**
             * \brief Adds a new (or overwrites an existing) entry for the numeric UFF atom type \a atom_type that stores the given property values.
             * \param atom_type The numeric UFF atom type.
             * \param atom_type_sym The UFF atom type symbol.
             * \param atomic_no The atomic number of atoms of this type.
             * \param bond_rad The natural bond radius.
             * \param bond_ang The natural bond angle.
             * \param vdw_dist The Van der Waals distance parameter (well distance).
             * \param vdw_energy The Van der Waals energy parameter (well depth).
             * \param vdw_scale The Van der Waals scaling factor.
             * \param eff_charge The effective atomic charge used by the UFF electrostatic terms.
             */
            void addEntry(unsigned int atom_type, const std::string& atom_type_sym, unsigned int atomic_no, double bond_rad,
                          double bond_ang, double vdw_dist, double vdw_energy, double vdw_scale, double eff_charge);

            /**
             * \brief Returns the entry for the numeric UFF atom type \a atom_type.
             * \param atom_type The numeric UFF atom type.
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
             * \brief Removes the entry for the numeric UFF atom type \a atom_type.
             * \param atom_type The numeric UFF atom type.
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
             * \brief Loads the built-in default UFF atom type property entries.
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

#endif // CDPL_FORCEFIELD_UFFATOMTYPEPROPERTYTABLE_HPP
