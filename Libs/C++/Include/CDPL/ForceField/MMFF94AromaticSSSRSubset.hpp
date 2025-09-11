/* 
 * MMFF94AromaticSSSRSubset.hpp 
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
 * \brief Definition of class CDPL::ForceField::MMFF94AromaticSSSRSubset.
 */

#ifndef CDPL_FORCEFIELD_AROMATICSSSRSUBSET_HPP
#define CDPL_FORCEFIELD_AROMATICSSSRSUBSET_HPP

#include <vector>
#include <memory>

#include "CDPL/ForceField/APIPrefix.hpp"
#include "CDPL/Chem/FragmentList.hpp"
#include "CDPL/Chem/Fragment.hpp"
#include "CDPL/Util/BitSet.hpp"


namespace CDPL
{

    namespace Chem
    {

        class MolecularGraph;
    }

    namespace ForceField
    {

        /**
         * \brief Implements the extraction of all rings in the SSSR of a molecular graph that 
         *        are aromatic according to MMFF94 conventions.
         */
        class CDPL_FORCEFIELD_API MMFF94AromaticSSSRSubset : public Chem::FragmentList
        {

          public:
            /**    
             * \brief A reference-counted smart pointer [\ref SHPTR] for dynamically allocated \c %MMFF94AromaticSSSRSubset instances.
             */
            typedef std::shared_ptr<MMFF94AromaticSSSRSubset> SharedPointer;

            /**
             * \brief Constructs an empty \c %MMFF94AromaticSSSRSubset instance.
             */
            MMFF94AromaticSSSRSubset() {}

            /**
             * \brief Construct a \c %MMFF94AromaticSSSRSubset instance that contains all aromatic rings of the
             *        SSSR of the molecular graph \a molgraph.
             * \param molgraph The molecular graph for which to extract the aromatic rings.
             */
            MMFF94AromaticSSSRSubset(const Chem::MolecularGraph& molgraph);

            MMFF94AromaticSSSRSubset(const MMFF94AromaticSSSRSubset&) = delete;

            MMFF94AromaticSSSRSubset& operator=(const MMFF94AromaticSSSRSubset&) = delete;

            /**
             * \brief Replaces the current set of rings by the aromatic rings in the SSSR of the molecular graph \a molgraph.
             * \param molgraph The molecular graph for which to extract the aromatic rings.
             */
            void extract(const Chem::MolecularGraph& molgraph);

            /**
             * \brief Replaces the current set of rings by the aromatic rings in the SSSR of the molecular graph \a molgraph.
             * \param molgraph The molecular graph for which to extract the aromatic rings.
             * \param sssr The SSSR of the molecular graph \a molgraph.
             */
            void extract(const Chem::MolecularGraph& molgraph, const Chem::FragmentList& sssr);

          private:
            void init(const Chem::MolecularGraph& molgraph);

            void perceiveAromaticRings(const Chem::FragmentList& sssr);
            void addToAromaticBondMask(const Chem::Fragment& ring);

            const char* getClassName() const
            {
                return "MMFF94AromaticSSSRSubset";
            }

            typedef std::vector<Chem::Fragment::SharedPointer> RingList;

            const Chem::MolecularGraph* molGraph;
            RingList                    candidateRings;
            Util::BitSet                aromBondMask;
        };
    } // namespace ForceField
} // namespace CDPL

#endif // CDPL_FORCEFIELD_AROMATICSSSRSUBSET_HPP
