/* 
 * HierarchyViewModel.hpp 
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
 * \brief Definition of class CDPL::Biomol::HierarchyViewModel.
 */

#ifndef CDPL_BIOMOL_HIERARCHYVIEWMODEL_HPP
#define CDPL_BIOMOL_HIERARCHYVIEWMODEL_HPP

#include <cstddef>
#include <vector>
#include <string>
#include <unordered_map>
#include <memory>

#include <boost/iterator/indirect_iterator.hpp>

#include "CDPL/Biomol/APIPrefix.hpp"
#include "CDPL/Biomol/HierarchyViewChain.hpp"


namespace CDPL
{

    namespace Biomol
    {

        class HierarchyView;

        /**
         * \brief Data structure for the representation of individual biological macromolecule models.
         * \see Biomol::HierarchyView
         */
        class CDPL_BIOMOL_API HierarchyViewModel : public HierarchyViewNode
        {

            friend class HierarchyView;

            typedef std::shared_ptr<HierarchyViewChain> ChainPtr;
            typedef std::vector<ChainPtr>               ChainList;

          public:
            /**
             * \brief A constant iterator over the contained chains.
             */
            typedef boost::indirect_iterator<ChainList::const_iterator, const HierarchyViewChain> ConstChainIterator;

            /**
             * \brief Returns the number of chains in this model.
             * \return The number of chains.
             */
            std::size_t getNumChains() const;

            /**
             * \brief Returns the chain at index \a idx.
             * \param idx The zero-based chain index.
             * \return A \c const reference to the chain.
             * \throw Base::IndexError if \a idx is not in the range [0, getNumChains()).
             */
            const HierarchyViewChain& getChain(std::size_t idx) const;

            /**
             * \brief Tells whether this model contains a chain with the given chain ID.
             * \param id The chain ID.
             * \return \c true if such a chain exists, and \c false otherwise.
             */
            bool hasChainWithID(const std::string& id) const;

            /**
             * \brief Returns the chain identified by the given chain ID.
             * \param id The chain ID.
             * \return A \c const reference to the chain.
             * \throw Base::ItemNotFound if no chain with the requested ID exists.
             */
            const HierarchyViewChain& getChainByID(const std::string& id) const;

            /**
             * \brief Returns a constant iterator pointing to the first chain.
             * \return A constant iterator pointing to the first chain.
             */
            ConstChainIterator getChainsBegin() const;

            /**
             * \brief Returns a constant iterator pointing one past the last chain.
             * \return A constant iterator pointing one past the last chain.
             */
            ConstChainIterator getChainsEnd() const;

            /**
             * \brief Returns a constant iterator pointing to the first chain (range-based for support).
             * \return A constant iterator pointing to the first chain.
             */
            ConstChainIterator begin() const;

            /**
             * \brief Returns a constant iterator pointing one past the last chain (range-based for support).
             * \return A constant iterator pointing one past the last chain.
             */
            ConstChainIterator end() const;

          private:
            HierarchyViewModel():
                initChains(true) {}

            void initChainList() const;

            typedef std::unordered_map<std::string, ChainPtr> IDToChainMap;

            mutable ChainList    chains;
            mutable IDToChainMap idToChainMap;
            mutable bool         initChains;
        };
    } // namespace Biomol
} // namespace CDPL

#endif // CDPL_BIOMOL_HIERARCHYVIEWMODEL_HPP
