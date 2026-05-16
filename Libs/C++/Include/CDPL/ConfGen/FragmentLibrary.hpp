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

        /**
         * \brief A library of pre-generated conformations for rigid molecular fragments, indexed by
         *        canonical-fragment hash code.
         *
         * Entries are FragmentLibraryEntry instances keyed by the hash code of the
         * associated ConfGen::CanonicalFragment. The library is iterable, supports
         * lookup/insertion/removal, can be serialized to and from a stream, and provides a
         * process-wide default instance via the static set() / get() accessors. A built-in
         * mutex is exposed via getMutex() to allow callers to coordinate concurrent access.
         */
        class CDPL_CONFGEN_API FragmentLibrary
        {

            typedef std::unordered_map<std::uint64_t, FragmentLibraryEntry::SharedPointer> HashToEntryMap;

          public:
            /**
             * \brief A reference-counted smart pointer [\ref SHPTR] for dynamically allocated \c %FragmentLibrary instances.
             */
            typedef std::shared_ptr<FragmentLibrary> SharedPointer;

            /**
             * \brief The type of a stored hash-code-to-entry pair.
             */
            typedef HashToEntryMap::value_type     Entry;

            /**
             * \brief A constant iterator over the stored entries.
             */
            typedef HashToEntryMap::const_iterator ConstEntryIterator;

            /**
             * \brief A mutable iterator over the stored entries.
             */
            typedef HashToEntryMap::iterator       EntryIterator;

            /**
             * \brief Constructs an empty \c %FragmentLibrary instance.
             */
            FragmentLibrary();

            /**
             * \brief Constructs a copy of the \c %FragmentLibrary instance \a lib.
             * \param lib The \c %FragmentLibrary to copy.
             */
            FragmentLibrary(const FragmentLibrary& lib);

            /**
             * \brief Destructor.
             */
            ~FragmentLibrary();

            /**
             * \brief Replaces the contents of this library with a copy of the contents of \a lib.
             * \param lib The source \c %FragmentLibrary.
             * \return A reference to itself.
             */
            FragmentLibrary& operator=(const FragmentLibrary& lib);

            /**
             * \brief Adds all entries from \a lib to this library.
             * \param lib The source \c %FragmentLibrary.
             */
            void addEntries(const FragmentLibrary& lib);

            /**
             * \brief Adds the given entry to the library.
             * \param entry The entry to add.
             * \return \c true if the entry was added, and \c false if an entry with the same hash code was already present.
             */
            bool addEntry(const FragmentLibraryEntry::SharedPointer& entry);

            /**
             * \brief Returns the entry with the specified hash code.
             * \param hash_code The hash code of the queried entry.
             * \return A \c const reference to the matching entry's smart pointer, or to an empty
             *         smart pointer if no entry with \a hash_code exists.
             */
            const FragmentLibraryEntry::SharedPointer& getEntry(std::uint64_t hash_code) const;

            /**
             * \brief Tells whether the library contains an entry with the specified hash code.
             * \param hash_code The hash code of the queried entry.
             * \return \c true if the entry exists, and \c false otherwise.
             */
            bool containsEntry(std::uint64_t hash_code) const;

            /**
             * \brief Returns the number of entries stored in the library.
             * \return The number of entries.
             */
            std::size_t getNumEntries() const;

            /**
             * \brief Removes all entries from the library.
             */
            void clear();

            /**
             * \brief Removes the entry with the specified hash code.
             * \param hash_code The hash code of the entry to remove.
             * \return \c true if the entry was removed, and \c false if no matching entry existed.
             */
            bool removeEntry(std::uint64_t hash_code);

            /**
             * \brief Removes the entry referenced by the given iterator.
             * \param it Iterator referencing the entry to remove.
             * \return An iterator pointing to the entry following the removed one.
             */
            EntryIterator removeEntry(const EntryIterator& it);

            /**
             * \brief Returns a constant iterator pointing to the first entry of the library.
             * \return A constant iterator pointing to the first entry.
             */
            ConstEntryIterator getEntriesBegin() const;

            /**
             * \brief Returns a constant iterator pointing one past the last entry of the library.
             * \return A constant iterator pointing one past the last entry.
             */
            ConstEntryIterator getEntriesEnd() const;

            /**
             * \brief Returns a mutable iterator pointing to the first entry of the library.
             * \return A mutable iterator pointing to the first entry.
             */
            EntryIterator getEntriesBegin();

            /**
             * \brief Returns a mutable iterator pointing one past the last entry of the library.
             * \return A mutable iterator pointing one past the last entry.
             */
            EntryIterator getEntriesEnd();

            /**
             * \brief Returns a constant iterator pointing to the first entry of the library (range-based for support).
             * \return A constant iterator pointing to the first entry.
             */
            ConstEntryIterator begin() const;

            /**
             * \brief Returns a constant iterator pointing one past the last entry of the library (range-based for support).
             * \return A constant iterator pointing one past the last entry.
             */
            ConstEntryIterator end() const;

            /**
             * \brief Returns a mutable iterator pointing to the first entry of the library (range-based for support).
             * \return A mutable iterator pointing to the first entry.
             */
            EntryIterator begin();

            /**
             * \brief Returns a mutable iterator pointing one past the last entry of the library (range-based for support).
             * \return A mutable iterator pointing one past the last entry.
             */
            EntryIterator end();

            /**
             * \brief Loads the contents of the library from the input stream \a is.
             * \param is The input stream to read from.
             */
            void load(std::istream& is);

            /**
             * \brief Writes the contents of the library to the output stream \a os.
             * \param os The output stream to write to.
             */
            void save(std::ostream& os) const;

            /**
             * \brief Loads the default fragment library bundled with CDPKit.
             */
            void loadDefaults();

            /**
             * \brief Returns the mutex protecting the library state for use by external multi-threaded callers.
             * \return A reference to the protecting mutex.
             */
            std::mutex& getMutex();

            /**
             * \brief Sets the process-wide default fragment library used by ConfGen routines.
             * \param lib The new default fragment library.
             */
            static void set(const SharedPointer& lib);

            /**
             * \brief Returns the process-wide default fragment library.
             * \return The current default fragment library.
             */
            static const SharedPointer& get();

          private:
            static SharedPointer   defaultLib;
            mutable HashToEntryMap hashToEntryMap;
            mutable std::mutex     mutex;
        };
    } // namespace ConfGen
} // namespace CDPL

#endif // CDPL_CONFGEN_FRAGMENTLIBRARY_HPP
