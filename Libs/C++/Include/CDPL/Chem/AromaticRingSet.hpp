/* 
 * AromaticRingSet.hpp 
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
 * \brief Definition of class CDPL::Chem::AromaticRingSet.
 */

#ifndef CDPL_CHEM_AROMATICRINGSET_HPP
#define CDPL_CHEM_AROMATICRINGSET_HPP

#include <memory>

#include "CDPL/Chem/APIPrefix.hpp"
#include "CDPL/Chem/FragmentList.hpp"
#include "CDPL/Util/BitSet.hpp"


namespace CDPL
{

    namespace Chem
    {

        class MolecularGraph;

        /**
         * \brief Implements the perception of aromatic rings in a molecular graph.
         */
        class CDPL_CHEM_API AromaticRingSet : public FragmentList
        {

          public:
            /**    
             * \brief A reference-counted smart pointer [\ref SHPTR] for dynamically allocated \c %AromaticRingSet instances.
             */
            typedef std::shared_ptr<AromaticRingSet> SharedPointer;

            /**
             * \brief Constructs an empty \c %AromaticRingSet instance.
             */
            AromaticRingSet() {}

            AromaticRingSet(const AromaticRingSet&) = delete;
            
            /**
             * \brief Construct a \c %AromaticRingSet instance that contains all aromatic rings of the
             *        molecular graph \a molgraph.
             * \param molgraph The molecular graph for which to perceive the aromatic rings.
             */
            AromaticRingSet(const MolecularGraph& molgraph);

            AromaticRingSet& operator=(const AromaticRingSet&) = delete;

            /**
             * \brief Replaces the current set of rings by the aromatic rings of the molecular graph \a molgraph.
             * \param molgraph The molecular graph for which to perceive the aromatic rings.
             */
            void perceive(const MolecularGraph& molgraph);

          private:
            void init(const MolecularGraph&);

            void findAromaticRings();

            bool isAromatic(const Fragment::SharedPointer&);

            const char* getClassName() const
            {
                return "AromaticRingSet";
            }

            Util::BitSet          aromBondMask;
            const MolecularGraph* molGraph;
        };
    } // namespace Chem
} // namespace CDPL

#endif // CDPL_CHEM_AROMATICRINGSET_HPP
