/* 
 * CyclicSubstructure.hpp 
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
 * \brief Definition of class CDPL::Chem::CyclicSubstructure.
 */

#ifndef CDPL_CHEM_CYCLICSUBSTRUCTURE_HPP
#define CDPL_CHEM_CYCLICSUBSTRUCTURE_HPP

#include <vector>
#include <memory>

#include "CDPL/Chem/APIPrefix.hpp"
#include "CDPL/Chem/Fragment.hpp"
#include "CDPL/Util/BitSet.hpp"


namespace CDPL
{

    namespace Chem
    {

        /**
         * \brief Implements the perception of ring atoms and bonds in a molecular graph.
         */
        class CDPL_CHEM_API CyclicSubstructure : public Fragment
        {

          public:
            /**    
             * \brief A reference-counted smart pointer [\ref SHPTR] for dynamically allocated \c %CyclicSubstructure instances.
             */
            typedef std::shared_ptr<CyclicSubstructure> SharedPointer;

            /**
             * \brief Constructs an empty \c %CyclicSubstructure instance.
             */
            CyclicSubstructure() {}

            /**
             * \brief Construct a \c %CyclicSubstructure instance that consists of the ring atoms and bonds of the
             *        molecular graph \a molgraph.
             * \param molgraph The molecular graph for which to perceive ring atoms and bonds.
             */
            CyclicSubstructure(const MolecularGraph& molgraph);

            CyclicSubstructure(const CyclicSubstructure&) = delete;

            CyclicSubstructure& operator=(const CyclicSubstructure&) = delete;

            /**
             * \brief Replaces the currently stored atoms and bonds by the set of ring atoms and bonds of the
             *        molecular graph \a molgraph.
             * \param molgraph The molecular graph for which to perceive ring atoms and bonds.
             */
            void perceive(const MolecularGraph& molgraph);

          private:
            typedef std::vector<const Atom*> AtomStack;
            typedef std::vector<const Bond*> BondStack;

            void init(const MolecularGraph&);

            void findRingAtomsAndBonds();
            void findRingAtomsAndBonds(const Atom* atom);

            Util::BitSet          visAtomMask;
            Util::BitSet          pathAtomMask;
            AtomStack             atomStack;
            BondStack             bondStack;
            const MolecularGraph* molGraph;
        };
    } // namespace Chem
} // namespace CDPL

#endif // CDPL_CHEM_CYCLICSUBSTRUCTURE_HPP
