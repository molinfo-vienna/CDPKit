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
         * \brief HierarchyViewModel.
         */
        class CDPL_BIOMOL_API HierarchyViewModel : public HierarchyViewNode
        {

            friend class HierarchyView;

            typedef std::shared_ptr<HierarchyViewChain> ChainPtr;
            typedef std::vector<ChainPtr>               ChainList;

          public:
            typedef boost::indirect_iterator<ChainList::const_iterator, const HierarchyViewChain> ConstChainIterator;

            std::size_t getNumChains() const;

            const HierarchyViewChain& getChain(std::size_t idx) const;

            bool hasChainWithID(const std::string& id) const;

            const HierarchyViewChain& getChainByID(const std::string& id) const;

            ConstChainIterator getChainsBegin() const;

            ConstChainIterator getChainsEnd() const;

            ConstChainIterator begin() const;

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
