/* 
 * ExtendedSSSR.hpp 
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
 * \brief Definition of the class CDPL::Chem::ExtendedSSSR.
 */

#ifndef CDPL_CHEM_EXTENDEDSSSR_HPP
#define CDPL_CHEM_EXTENDEDSSSR_HPP

#include <memory>
#include <vector>
#include <utility>

#include "CDPL/Chem/APIPrefix.hpp"
#include "CDPL/Chem/FragmentList.hpp"
#include "CDPL/Util/BitSet.hpp"


namespace CDPL
{

    namespace Chem
    {

        /**
         * \brief Implements the perception of the <em>Extended Smallest Set of Smallest Rings (ESSSR)</em> of a molecular graph.
         */
        class CDPL_CHEM_API ExtendedSSSR : public FragmentList
        {

          public:
            /**    
             * \brief A reference-counted smart pointer [\ref SHPTR] for dynamically allocated \c %ExtendedSSSR instances.
             */
            typedef std::shared_ptr<ExtendedSSSR> SharedPointer;

            /**
             * \brief Constructs an empty \c %ExtendedSSSR instance.
             */
            ExtendedSSSR() {}

            /**
             * \brief Construct a \c %ExtendedSSSR instance that represents the ESSSR of the molecular graph \a molgraph.
             * \param molgraph The molecular graph for which to perceive the ESSSR.
             */
            ExtendedSSSR(const MolecularGraph& molgraph);

            /**
             * \brief Replaces the current set of rings by the ESSSR of the molecular graph \a molgraph.
             * \param molgraph The molecular graph for which to perceive the ESSSR.
             */
            void perceive(const MolecularGraph& molgraph);

          private:
            void init(const MolecularGraph& molgraph);

            bool findRingContainingBonds(const Bond& bond1, const Bond& bond2) const;

            void perceiveRings(const MolecularGraph& molgraph, const Atom& curr_atom, const Atom& start_atom);
            void processFoundRing(const MolecularGraph& molgraph);
            
            const char* getClassName() const
            {
                return "ExtendedSSSR";
            }

            typedef std::vector<std::pair<const Atom*, const Bond*> > AtomBondList;

            Util::BitSet ringBonds;
            AtomBondList atomRingNbrs;
            Util::BitSet currBondPath;
            Util::BitSet currAtomPath;
            Util::BitSet smallestRingBonds;
            std::size_t  smallestRingSize;
        };
    } // namespace Chem
} // namespace CDPL

#endif // CDPL_CHEM_EXTENDEDSSSR_HPP
