/* 
 * FragmentLibraryEntry.hpp 
 *
 * This file is part of the ConfGenical Data Processing Toolkit
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
 * \brief Definition of class CDPL::ConfGen::FragmentLibraryEntry.
 */

#ifndef CDPL_CONFGEN_FRAGMENTLIBRARYENTRY_HPP
#define CDPL_CONFGEN_FRAGMENTLIBRARYENTRY_HPP

#include <string>
#include <cstddef>
#include <cstdint>
#include <memory>

#include <boost/iterator/indirect_iterator.hpp>

#include "CDPL/ConfGen/APIPrefix.hpp"
#include "CDPL/ConfGen/ConformerDataArray.hpp"


namespace CDPL
{

    namespace ConfGen
    {

        /**
         * \brief Data structure representing a single entry of a conformer generation fragment library.
         *
         * Each entry is identified by the hash code of the associated ConfGen::CanonicalFragment and stores
         * the canonical \e SMILES string plus a list of ConformerData instances (one per stored conformer).
         */
        class CDPL_CONFGEN_API FragmentLibraryEntry
        {

          public:
            /**
             * \brief A reference-counted smart pointer [\ref SHPTR] for dynamically allocated \c %FragmentLibraryEntry instances.
             */
            typedef std::shared_ptr<FragmentLibraryEntry> SharedPointer;

            /**
             * \brief A constant iterator over the stored conformers (dereferences to \c const ConformerData).
             */
            typedef boost::indirect_iterator<ConformerDataArray::const_iterator, const ConformerData> ConstConformerIterator;

            /**
             * \brief A mutable iterator over the stored conformers (dereferences to ConformerData).
             */
            typedef boost::indirect_iterator<ConformerDataArray::iterator, ConformerData>             ConformerIterator;

            /**
             * \brief Constructs an empty \c %FragmentLibraryEntry instance.
             */
            FragmentLibraryEntry();

            /**
             * \brief Sets the hash code identifying the entry within the FragmentLibrary.
             * \param hash_code The new hash code.
             */
            void setHashCode(std::uint64_t hash_code);

            /**
             * \brief Returns the hash code identifying the entry within the FragmentLibrary.
             * \return The hash code.
             */
            std::uint64_t getHashCode() const;

            /**
             * \brief Sets the canonical \e SMILES string describing the stored fragment.
             * \param smiles The new \e SMILES string.
             */
            void setSMILES(const std::string& smiles);

            /**
             * \brief Returns the canonical \e SMILES string describing the stored fragment.
             * \return A \c const reference to the \e SMILES string.
             */
            const std::string& getSMILES() const;

            /**
             * \brief Removes all stored conformers from the entry.
             */
            void clearConformers();

            /**
             * \brief Returns the number of atoms of the stored fragment.
             * \return The number of atoms (zero if no conformer has been added yet).
             */
            std::size_t getNumAtoms() const;

            /**
             * \brief Returns the number of stored conformers.
             * \return The number of stored conformers.
             */
            std::size_t getNumConformers() const;

            /**
             * \brief Appends the given conformer to the entry.
             * \param conf_data A smart pointer to the conformer data to add.
             */
            void addConformer(const ConformerData::SharedPointer& conf_data);

            /**
             * \brief Returns a \c const reference to the stored conformer at index \a idx.
             * \param idx The zero-based conformer index.
             * \return A \c const reference to the conformer.
             * \throw Base::IndexError if \a idx is not in the range [0, getNumConformers()).
             */
            const ConformerData& getConformer(std::size_t idx) const;

            /**
             * \brief Returns a reference to the stored conformer at index \a idx.
             * \param idx The zero-based conformer index.
             * \return A reference to the conformer.
             * \throw Base::IndexError if \a idx is not in the range [0, getNumConformers()).
             */
            ConformerData& getConformer(std::size_t idx);

            /**
             * \brief Returns a constant iterator pointing to the first stored conformer.
             * \return A constant iterator pointing to the first conformer.
             */
            ConstConformerIterator getConformersBegin() const;

            /**
             * \brief Returns a constant iterator pointing one past the last stored conformer.
             * \return A constant iterator pointing one past the last conformer.
             */
            ConstConformerIterator getConformersEnd() const;

            /**
             * \brief Returns a mutable iterator pointing to the first stored conformer.
             * \return A mutable iterator pointing to the first conformer.
             */
            ConformerIterator getConformersBegin();

            /**
             * \brief Returns a mutable iterator pointing one past the last stored conformer.
             * \return A mutable iterator pointing one past the last conformer.
             */
            ConformerIterator getConformersEnd();

            /**
             * \brief Returns a constant iterator pointing to the first stored conformer (range-based for support).
             * \return A constant iterator pointing to the first conformer.
             */
            ConstConformerIterator begin() const;

            /**
             * \brief Returns a constant iterator pointing one past the last stored conformer (range-based for support).
             * \return A constant iterator pointing one past the last conformer.
             */
            ConstConformerIterator end() const;

            /**
             * \brief Returns a mutable iterator pointing to the first stored conformer (range-based for support).
             * \return A mutable iterator pointing to the first conformer.
             */
            ConformerIterator begin();

            /**
             * \brief Returns a mutable iterator pointing one past the last stored conformer (range-based for support).
             * \return A mutable iterator pointing one past the last conformer.
             */
            ConformerIterator end();

            /**
             * \brief Returns a \c const reference to the underlying array of conformer-data smart pointers.
             * \return A \c const reference to the conformer-data array.
             */
            const ConformerDataArray& getData() const;

          private:
            std::uint64_t      hashCode;
            std::string        smiles;
            ConformerDataArray conformers;
        };
    } // namespace ConfGen
} // namespace CDPL

#endif // CDPL_CONFGEN_FRAGMENTLIBRARYENTRY_HPP
