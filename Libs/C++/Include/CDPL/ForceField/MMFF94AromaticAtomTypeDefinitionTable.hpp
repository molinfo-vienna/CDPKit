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

        class CDPL_FORCEFIELD_API MMFF94AromaticAtomTypeDefinitionTable
        {

          public:
            class Entry;

          private:
            typedef std::vector<Entry> DataStorage;

          public:
            typedef std::shared_ptr<MMFF94AromaticAtomTypeDefinitionTable> SharedPointer;

            typedef DataStorage::const_iterator ConstEntryIterator;
            typedef DataStorage::iterator       EntryIterator;

            class CDPL_FORCEFIELD_API Entry
            {

              public:
                Entry(const std::string& old_type, const std::string& aro_type, unsigned int atomic_no,
                      std::size_t ring_size, std::size_t het_atom_dist, bool im_cation, bool n5_anion);

                const std::string& getOldAtomType() const;

                const std::string& getAromAtomType() const;

                unsigned int getAtomicNumber() const;

                std::size_t getRingSize() const;

                std::size_t getHeteroAtomDistance() const;

                bool isImidazoliumCation() const;

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

            MMFF94AromaticAtomTypeDefinitionTable();

            std::size_t getNumEntries() const;

            void addEntry(const std::string& old_type, const std::string& aro_type, unsigned int atomic_no,
                          std::size_t ring_size, std::size_t het_atom_dist, bool im_cation, bool n5_anion);

            const Entry& getEntry(std::size_t idx) const;

            void clear();

            void removeEntry(std::size_t idx);

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

#endif // CDPL_FORCEFIELD_MMFF94AROMATICATOMTYPEDEFINITIONTABLE_HPP
