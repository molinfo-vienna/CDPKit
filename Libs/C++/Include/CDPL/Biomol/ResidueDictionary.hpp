/* 
 * ResidueDictionary.hpp 
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
 * \brief Definition of class CDPL::Biomol::ResidueDictionary. 
 */

#ifndef CDPL_BIOMOL_RESIDUEDICTIONARY_HPP
#define CDPL_BIOMOL_RESIDUEDICTIONARY_HPP

#include <string>
#include <unordered_map>
#include <memory>
#include <functional>

#include <boost/iterator/transform_iterator.hpp>

#include "CDPL/Biomol/APIPrefix.hpp"
#include "CDPL/Chem/MolecularGraph.hpp"


namespace CDPL
{

    namespace Biomol
    {

        /**
         * \brief A global dictionary for the lookup of meta-data associated with the residues
         *        in biological macromolecules.
         */
        class CDPL_BIOMOL_API ResidueDictionary
        {

          public:
            /**
             * \brief A single residue dictionary entry.
             */
            class CDPL_BIOMOL_API Entry
            {

              public:
                /** \brief A generic wrapper for storing a user-defined function that retrieves the residue structure for a given three-letter code. */
                typedef std::function<Chem::MolecularGraph::SharedPointer(const std::string&)> StructureRetrievalFunction;

                /**
                 * \brief Constructs and initializes an \c %Entry instance with the given data.
                 * \param code The three-letter code (TLC) of the residue.
                 * \param rep_code The TLC of the residue this entry replaces (or an empty string if it does not replace any other residue).
                 * \param rep_by_code The TLC of the residue that replaces this one (or an empty string if it has not been replaced).
                 * \param parent_code The TLC of the parent residue (or an empty string if there is no parent).
                 * \param one_letter_code The one-letter residue code (or an empty string if not defined).
                 * \param obsolete \c true if the residue type is obsolete, and \c false otherwise.
                 * \param name The full residue name.
                 * \param type The residue type (see Biomol::ResidueType).
                 * \param struc_ret_func The function used to retrieve the residue structure on demand.
                 */
                Entry(const std::string& code, const std::string& rep_code, const std::string& rep_by_code, const std::string& parent_code,
                      const std::string& one_letter_code,bool obsolete, const std::string& name, unsigned int type,
                      const StructureRetrievalFunction& struc_ret_func);

                /**
                 * \brief Constructs an empty (default-initialized) \c %Entry instance.
                 */
                Entry();

                /**
                 * \brief Returns the three-letter code (TLC) of the residue.
                 * \return A \c const reference to the three-letter residue code.
                 */
                const std::string& getCode() const;

                /**
                 * \brief Returns the TLC of the residue this entry replaces.
                 * \return A \c const reference to the replaced-residue code (or an empty string if this entry does not replace any other residue).
                 */
                const std::string& getReplacedCode() const;

                /**
                 * \brief Returns the TLC of the residue that replaces this one.
                 * \return A \c const reference to the replacing-residue code (or an empty string if this entry has not been replaced).
                 */
                const std::string& getReplacedByCode() const;

                /**
                 * \brief Returns the TLC of the parent residue.
                 * \return A \c const reference to the parent-residue code (or an empty string if there is no parent).
                 * \since 1.2
                 */
                const std::string& getParentCode() const;

                /**
                 * \brief Returns the one-letter residue code.
                 * \return A \c const reference to the one-letter residue code (or an empty string if not defined).
                 * \since 1.2
                 */
                const std::string& getOneLetterCode() const;

                /**
                 * \brief Tells whether the residue type described by this entry is obsolete.
                 * \return \c true if the residue type is obsolete, and \c false otherwise.
                 */
                bool isObsolete() const;

                /**
                 * \brief Returns the full residue name.
                 * \return A \c const reference to the residue name.
                 */
                const std::string& getName() const;

                /**
                 * \brief Returns the residue type (see Biomol::ResidueType).
                 * \return The residue type identifier.
                 */
                unsigned int getType() const;

                /**
                 * \brief Retrieves the residue structure via the configured structure-retrieval function.
                 * \return A shared pointer to the residue structure (or an empty pointer if no structure could be retrieved).
                 */
                Chem::MolecularGraph::SharedPointer getStructure() const;

              private:
                std::string                code;
                std::string                replacesCode;
                std::string                replacedByCode;
                std::string                parentCode;
                std::string                oneLetterCode;
                bool                       obsolete;
                std::string                name;
                unsigned int               type;
                StructureRetrievalFunction structRetrievalFunc;
            };

          private:
            struct CIStringHashFunc
            {

                std::size_t operator()(const std::string& str) const;
            };

            struct CIStringCmpFunc
            {

                bool operator()(const std::string& str1, const std::string& str2) const;
            };
              
            typedef std::unordered_map<std::string, Entry, CIStringHashFunc, CIStringCmpFunc> EntryLookupTable;

          public:
            /** \brief A reference-counted smart pointer [\ref SHPTR] for dynamically allocated \c %ResidueDictionary instances. */
            typedef std::shared_ptr<ResidueDictionary> SharedPointer;

            /** \brief A constant iterator over the entries of the dictionary. */
            typedef boost::transform_iterator<std::function<const Entry&(const EntryLookupTable::value_type&)>,
                                              EntryLookupTable::const_iterator>   ConstEntryIterator;

            /**
             * \brief Tells whether the residue with three-letter code \a code is a standard biopolymer residue (amino acid or nucleotide).
             * \param code The residue three-letter code.
             * \return \c true if the residue is a standard biopolymer residue, and \c false otherwise.
             */
            static bool isStdResidue(const std::string& code);

            /**
             * \brief Adds (or overwrites) the dictionary entry \a entry.
             * \param entry The entry to add.
             */
            void addEntry(const Entry& entry);

            /**
             * \brief Adds (or overwrites) the dictionary entry \a entry by moving its data.
             * \param entry The entry to add.
             * \since 1.2
             */
            void addEntry(Entry&& entry);

            /**
             * \brief Tells whether the dictionary contains an entry for the residue with three-letter code \a code.
             * \param code The residue three-letter code.
             * \return \c true if a matching entry exists, and \c false otherwise.
             */
            bool containsEntry(const std::string& code) const;

            /**
             * \brief Removes the dictionary entry for the residue with three-letter code \a code.
             * \param code The residue three-letter code.
             */
            void removeEntry(const std::string& code);

            /**
             * \brief Returns the dictionary entry for the residue with three-letter code \a code.
             * \param code The residue three-letter code.
             * \return A \c const reference to the matching entry (or to an empty default-constructed entry if no matching entry exists).
             */
            const Entry& getEntry(const std::string& code) const;

            /**
             * \brief Removes all entries from the dictionary.
             */
            void clear();

            /**
             * \brief Returns the number of entries in the dictionary.
             * \return The entry count.
             */
            std::size_t getNumEntries() const;

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
             * \brief Returns the TLC of the residue replaced by the residue with three-letter code \a code.
             * \param code The residue three-letter code.
             * \return A \c const reference to the replaced-residue code (or an empty string if no matching entry exists or the entry does not replace any other residue).
             */
            const std::string& getReplacedCode(const std::string& code) const;

            /**
             * \brief Returns the TLC of the residue that replaces the residue with three-letter code \a code.
             * \param code The residue three-letter code.
             * \return A \c const reference to the replacing-residue code (or an empty string if no matching entry exists or the entry has not been replaced).
             */
            const std::string& getReplacedByCode(const std::string& code) const;

            /**
             * \brief Returns the TLC of the parent residue of the residue with three-letter code \a code.
             * \param code The residue three-letter code.
             * \return A \c const reference to the parent-residue code (or an empty string if no matching entry exists or the residue has no parent).
             * \since 1.2
             */
            const std::string& getParentCode(const std::string& code) const;

            /**
             * \brief Returns the one-letter code of the residue with three-letter code \a code.
             * \param code The residue three-letter code.
             * \return A \c const reference to the one-letter residue code (or an empty string if not defined or no matching entry exists).
             * \since 1.2
             */
            const std::string& getOneLetterCode(const std::string& code) const;

            /**
             * \brief Tells whether the residue type with three-letter code \a code is obsolete.
             * \param code The residue three-letter code.
             * \return \c true if the residue type is obsolete, and \c false otherwise (also if no matching entry exists).
             */
            bool isObsolete(const std::string& code) const;

            /**
             * \brief Returns the full name of the residue with three-letter code \a code.
             * \param code The residue three-letter code.
             * \return A \c const reference to the residue name (or an empty string if no matching entry exists).
             */
            const std::string& getName(const std::string& code) const;

            /**
             * \brief Returns the residue type (see Biomol::ResidueType) of the residue with three-letter code \a code.
             * \param code The residue three-letter code.
             * \return The residue type identifier (or Biomol::ResidueType::UNKNOWN if no matching entry exists).
             */
            unsigned int getType(const std::string& code) const;

            /**
             * \brief Retrieves the structure of the residue with three-letter code \a code.
             * \param code The residue three-letter code.
             * \return A shared pointer to the residue structure (or an empty pointer if the structure could not be retrieved).
             */
            Chem::MolecularGraph::SharedPointer getStructure(const std::string& code) const;

            /**
             * \brief Loads the built-in default residue dictionary entries.
             */
            void loadDefaults();

            /**
             * \brief Replaces the process-wide default dictionary by \a dict.
             * \param dict The new default dictionary (a \c nullptr resets to the built-in default).
             */
            static void set(const SharedPointer& dict);

            /**
             * \brief Returns the process-wide default dictionary (lazily initialized on first call).
             * \return A \c const reference to the default-dictionary shared pointer.
             */
            static const SharedPointer& get();

          private:
            static SharedPointer defaultDict;
            EntryLookupTable     entries;
        };
    } // namespace Biomol
} // namespace CDPL

#endif // CDPL_BIOMOL_RESIDUEDICTIONARY_HPP
