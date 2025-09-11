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

        class CDPL_FORCEFIELD_API MMFF94FormalAtomChargeDefinitionTable
        {

          public:
            class Entry;

          private:
            typedef std::unordered_map<std::string, Entry> DataStorage;

          public:
            typedef std::shared_ptr<MMFF94FormalAtomChargeDefinitionTable> SharedPointer;

            class CDPL_FORCEFIELD_API Entry
            {

              public:
                Entry();

                Entry(const std::string& atom_type, std::size_t ass_mode, double charge, const std::string& type_list);

                const std::string& getAtomType() const;

                std::size_t getAssignmentMode() const;

                double getFormalCharge() const;

                const std::string& getAtomTypeList() const;

                operator bool() const;

              private:
                std::string atomType;
                std::size_t assMode;
                double      charge;
                std::string typeList;
                bool        initialized;
            };

            typedef boost::transform_iterator<std::function<const Entry&(const DataStorage::value_type&)>,
                                              DataStorage::const_iterator>
                ConstEntryIterator;

            typedef boost::transform_iterator<std::function<Entry&(DataStorage::value_type&)>,
                                              DataStorage::iterator>
                EntryIterator;

            MMFF94FormalAtomChargeDefinitionTable();

            void addEntry(const std::string& atom_type, std::size_t ass_mode, double charge, const std::string& nbr_types);

            const Entry& getEntry(const std::string& atom_type) const;

            std::size_t getNumEntries() const;

            void clear();

            bool removeEntry(const std::string& atom_type);

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

#endif // CDPL_FORCEFIELD_MMFF94FORMALATOMCHARGEDEFINITIONTABLE_HPP
