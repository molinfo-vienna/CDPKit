/* 
 * MMFF94BondChargeIncrementTable.hpp 
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
 * \brief Definition of the class CDPL::ForceField::MMFF94BondChargeIncrementTable.
 */

#ifndef CDPL_FORCEFIELD_MMFF94BONDCHARGEINCREMENTTABLE_HPP
#define CDPL_FORCEFIELD_MMFF94BONDCHARGEINCREMENTTABLE_HPP

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

        class CDPL_FORCEFIELD_API MMFF94BondChargeIncrementTable
        {

          public:
            class Entry;

          private:
            typedef std::unordered_map<std::uint32_t, Entry> DataStorage;

          public:
            typedef std::shared_ptr<MMFF94BondChargeIncrementTable> SharedPointer;

            class CDPL_FORCEFIELD_API Entry
            {

              public:
                Entry();

                Entry(unsigned int bond_type_idx, unsigned int atom1_type, unsigned int atom2_type, double bond_chg_inc);

                unsigned int getBondTypeIndex() const;

                unsigned int getAtom1Type() const;

                unsigned int getAtom2Type() const;

                double getChargeIncrement() const;

                operator bool() const;

              private:
                unsigned int bondTypeIdx;
                unsigned int atom1Type;
                unsigned int atom2Type;
                double       chargeIncr;
                bool         initialized;
            };

            typedef boost::transform_iterator<std::function<const Entry&(const DataStorage::value_type&)>,
                                              DataStorage::const_iterator>
                ConstEntryIterator;

            typedef boost::transform_iterator<std::function<Entry&(DataStorage::value_type&)>,
                                              DataStorage::iterator>
                EntryIterator;

            MMFF94BondChargeIncrementTable();

            void addEntry(unsigned int bond_type_idx, unsigned int atom1_type, unsigned int atom2_type, double bond_chg_inc);

            const Entry& getEntry(unsigned int bond_type_idx, unsigned int atom1_type, unsigned int atom2_type) const;

            std::size_t getNumEntries() const;

            void clear();

            bool removeEntry(unsigned int bond_type_idx, unsigned int atom1_type, unsigned int atom2_type);

            EntryIterator removeEntry(const EntryIterator& it);

            ConstEntryIterator getEntriesBegin() const;

            ConstEntryIterator getEntriesEnd() const;

            EntryIterator getEntriesBegin();

            EntryIterator getEntriesEnd();

            ConstEntryIterator begin() const;

            ConstEntryIterator end() const;

            EntryIterator begin();

            EntryIterator end();

            void load(std::istream& is);

            void loadDefaults();

            static void set(const SharedPointer& table);

            static const SharedPointer& get();

          private:
            static SharedPointer defaultTable;
            DataStorage          entries;
        };
    } // namespace ForceField
} // namespace CDPL

#endif // CDPL_FORCEFIELD_MMFF94BONDCHARGEINCREMENTTABLE_HPP
