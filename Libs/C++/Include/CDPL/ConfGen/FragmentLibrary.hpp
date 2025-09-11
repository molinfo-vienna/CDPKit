/* 
 * FragmentLibrary.hpp 
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
 * \brief Definition of class CDPL::ConfGen::FragmentLibrary.
 */

#ifndef CDPL_CONFGEN_FRAGMENTLIBRARY_HPP
#define CDPL_CONFGEN_FRAGMENTLIBRARY_HPP

#include <iosfwd>
#include <cstddef>
#include <unordered_map>
#include <mutex>
#include <memory>

#include "CDPL/ConfGen/APIPrefix.hpp"
#include "CDPL/ConfGen/FragmentLibraryEntry.hpp"


namespace CDPL
{

    namespace ConfGen
    {

        class CDPL_CONFGEN_API FragmentLibrary
        {

            typedef std::unordered_map<std::uint64_t, FragmentLibraryEntry::SharedPointer> HashToEntryMap;

          public:
            typedef std::shared_ptr<FragmentLibrary> SharedPointer;

            typedef HashToEntryMap::value_type     Entry;
            typedef HashToEntryMap::const_iterator ConstEntryIterator;
            typedef HashToEntryMap::iterator       EntryIterator;

            FragmentLibrary();

            FragmentLibrary(const FragmentLibrary& lib);

            ~FragmentLibrary();

            FragmentLibrary& operator=(const FragmentLibrary& lib);

            void addEntries(const FragmentLibrary& lib);

            bool addEntry(const FragmentLibraryEntry::SharedPointer& entry);

            const FragmentLibraryEntry::SharedPointer& getEntry(std::uint64_t hash_code) const;

            bool containsEntry(std::uint64_t hash_code) const;

            std::size_t getNumEntries() const;

            void clear();

            bool removeEntry(std::uint64_t hash_code);

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

            void save(std::ostream& os) const;

            void loadDefaults();

            std::mutex& getMutex();

            static void set(const SharedPointer& lib);

            static const SharedPointer& get();

          private:
            static SharedPointer   defaultLib;
            mutable HashToEntryMap hashToEntryMap;
            mutable std::mutex     mutex;
        };
    } // namespace ConfGen
} // namespace CDPL

#endif // CDPL_CONFGEN_FRAGMENTLIBRARY_HPP
