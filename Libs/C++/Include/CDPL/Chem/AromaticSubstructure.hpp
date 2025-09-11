/* 
 * AromaticSubstructure.hpp 
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
 * \brief Definition of class CDPL::Chem::AromaticSubstructure.
 */

#ifndef CDPL_CHEM_AROMATICSUBSTRUCTURE_HPP
#define CDPL_CHEM_AROMATICSUBSTRUCTURE_HPP

#include <vector>
#include <set>
#include <utility>
#include <memory>

#include "CDPL/Chem/APIPrefix.hpp"
#include "CDPL/Chem/Fragment.hpp"
#include "CDPL/Util/BitSet.hpp"


namespace CDPL
{

    namespace Chem
    {

        /**
         * \brief Implements the perception of aromatic atoms and bonds in a molecular graph.
         */
        class CDPL_CHEM_API AromaticSubstructure : public Fragment
        {

          public:
            /**    
             * \brief A reference-counted smart pointer [\ref SHPTR] for dynamically allocated \c %AromaticSubstructure instances.
             */
            typedef std::shared_ptr<AromaticSubstructure> SharedPointer;

            /**
             * \brief Constructs an empty \c %AromaticSubstructure instance.
             */
            AromaticSubstructure() {}

            /**
             * \brief Construct a \c %AromaticSubstructure instance that consists of the aromatic atoms and bonds of the
             *        molecular graph \a molgraph.
             * \param molgraph The molecular graph for which to perceive aromatic atoms and bonds.
             */
            AromaticSubstructure(const MolecularGraph& molgraph);

            AromaticSubstructure(const AromaticSubstructure&) = delete;

            AromaticSubstructure& operator=(const AromaticSubstructure&) = delete;

            /**
             * \brief Replaces the currently stored atoms and bonds by the set of aromatic atoms and bonds of the
             *        molecular graph \a molgraph.
             * \param molgraph The molecular graph for which to perceive aromatic atoms and bonds.
             */
            void perceive(const MolecularGraph& molgraph);

          private:
            class RingDescriptor
            {

              public:
                typedef std::shared_ptr<RingDescriptor> SharedPointer;

                RingDescriptor(const Fragment::SharedPointer&, const MolecularGraph&);
                RingDescriptor(const Fragment::SharedPointer&, Util::BitSet&, const RingDescriptor&, const RingDescriptor&);

                const Fragment& getRing() const;

                const Util::BitSet& getBondMask() const;

                bool containsSubRing(const RingDescriptor&) const;

              private:
                Fragment::SharedPointer ringPtr;
                const RingDescriptor*   subRing1;
                const RingDescriptor*   subRing2;
                Util::BitSet            bondMask;
            };

            void freeMemory();

            typedef std::vector<RingDescriptor::SharedPointer>               RingDescriptorList;
            typedef std::vector<std::pair<RingDescriptorList, std::size_t> > RingDescriptorListTable;
            typedef std::set<Util::BitSet>                                   BondMaskSet;

            void init(const MolecularGraph&);

            void findAromaticSubstructure();
            bool findAromaticRings(RingDescriptorListTable::value_type&);

            void fuseRings();
            void fuseRings(const RingDescriptor&, const RingDescriptor&, RingDescriptorList&);

            bool isAromatic(const RingDescriptor::SharedPointer&);

            Util::BitSet            aromBondMask;
            Util::BitSet            ringBondMask;
            Util::BitSet            tmpBondMask;
            const MolecularGraph*   molGraph;
            RingDescriptorListTable ringDescrListTable;
            BondMaskSet             uniqueRingSet;
            bool                    finished;
        };
    } // namespace Chem
} // namespace CDPL

#endif // CDPL_CHEM_AROMATICSUBSTRUCTURE_HPP
