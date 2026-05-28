/* 
 * HierarchyViewNode.hpp 
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
 * \brief Definition of class CDPL::Biomol::HierarchyViewNode.
 */

#ifndef CDPL_BIOMOL_HIERARCHYVIEWNODE_HPP
#define CDPL_BIOMOL_HIERARCHYVIEWNODE_HPP

#include <mutex>

#include "CDPL/Biomol/APIPrefix.hpp"
#include "CDPL/Biomol/ResidueList.hpp"


namespace CDPL
{

    namespace Biomol
    {

        /**
         * \brief Abstract base class for nodes of the Biomol::HierarchyView tree (models, chains, residues).
         */
        class CDPL_BIOMOL_API HierarchyViewNode : public Chem::Fragment
        {

          public:
            /**
             * \brief Returns the list of residues belonging to this node (lazily perceived on first access).
             * \return A \c const reference to the residue list.
             */
            const ResidueList& getResidues() const;

          protected:
            /**
             * \brief Constructs the \c %HierarchyViewNode instance.
             */
            HierarchyViewNode():
                initResidues(true) {}

            /**
             * \brief Virtual destructor.
             */
            virtual ~HierarchyViewNode() {}

            /**
             * \brief Returns a \c std::mutex instance for the thread-safe
             *        lazy initialization of data in this and any derived classes.
             * \return A reference to the stored \c std::mutex instance.
             */
            std::mutex& getMutex() const;

          private:
            mutable ResidueList residues;
            mutable bool        initResidues;
            mutable std::mutex  initMutex;
        };
    } // namespace Biomol
} // namespace CDPL

#endif // CDPL_BIOMOL_HIERARCHYVIEWNODE_HPP
