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
         * \brief FragmentLibraryEntry.
         */
        class CDPL_CONFGEN_API FragmentLibraryEntry
        {

          public:
            /**    
             * \brief A reference-counted smart pointer [\ref SHPTR] for dynamically allocated \c %FragmentLibraryEntry instances.
             */
            typedef std::shared_ptr<FragmentLibraryEntry> SharedPointer;

            typedef boost::indirect_iterator<ConformerDataArray::const_iterator, const ConformerData> ConstConformerIterator;
            typedef boost::indirect_iterator<ConformerDataArray::iterator, ConformerData>             ConformerIterator;

            /**
             * \brief Constructs an empty \c %FragmentLibraryEntry instance.
             */
            FragmentLibraryEntry();

            void setHashCode(std::uint64_t hash_code);

            std::uint64_t getHashCode() const;

            void setSMILES(const std::string& smiles);

            const std::string& getSMILES() const;

            void clearConformers();

            std::size_t getNumAtoms() const;

            std::size_t getNumConformers() const;

            void addConformer(const ConformerData::SharedPointer& conf_data);

            const ConformerData& getConformer(std::size_t idx) const;

            ConformerData& getConformer(std::size_t idx);

            ConstConformerIterator getConformersBegin() const;

            ConstConformerIterator getConformersEnd() const;

            ConformerIterator getConformersBegin();

            ConformerIterator getConformersEnd();

            ConstConformerIterator begin() const;

            ConstConformerIterator end() const;

            ConformerIterator begin();

            ConformerIterator end();

            const ConformerDataArray& getData() const;

          private:
            std::uint64_t      hashCode;
            std::string        smiles;
            ConformerDataArray conformers;
        };
    } // namespace ConfGen
} // namespace CDPL

#endif // CDPL_CONFGEN_FRAGMENTLIBRARYENTRY_HPP
