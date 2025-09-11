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

        class CDPL_FORCEFIELD_API MMFF94AtomTypePropertyTable
        {

          public:
            class Entry;

          private:
            typedef std::unordered_map<unsigned int, Entry> DataStorage;

          public:
            typedef std::shared_ptr<MMFF94AtomTypePropertyTable> SharedPointer;

            class CDPL_FORCEFIELD_API Entry
            {

              public:
                Entry();

                Entry(unsigned int atom_type, unsigned int atomic_no, std::size_t num_nbrs, std::size_t valence,
                      bool has_pi_lp, unsigned int mltb_desig, bool is_arom, bool lin_bnd_ang, bool has_mb_or_sb);

                unsigned int getAtomType() const;

                unsigned int getAtomicNumber() const;

                std::size_t getNumNeighbors() const;

                std::size_t getValence() const;

                bool hasPiLonePair() const;

                unsigned int getMultiBondDesignator() const;

                bool isAromaticAtomType() const;

                bool formsLinearBondAngle() const;

                bool formsMultiOrSingleBonds() const;

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

            typedef boost::transform_iterator<std::function<const Entry&(const DataStorage::value_type&)>,
                                              DataStorage::const_iterator>
                ConstEntryIterator;

            typedef boost::transform_iterator<std::function<Entry&(DataStorage::value_type&)>,
                                              DataStorage::iterator>
                EntryIterator;

            MMFF94AtomTypePropertyTable();

            void addEntry(unsigned int atom_type, unsigned int atomic_no, std::size_t num_nbrs, std::size_t valence,
                          bool has_pi_lp, unsigned int mltb_desig, bool is_arom, bool lin_bnd_ang, bool has_mb_or_sb);

            const Entry& getEntry(unsigned int atom_type) const;

            std::size_t getNumEntries() const;

            void clear();

            bool removeEntry(unsigned int atom_type);

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

#endif // CDPL_FORCEFIELD_MMFF94ATOMTYPEPROPERTYTABLE_HPP
