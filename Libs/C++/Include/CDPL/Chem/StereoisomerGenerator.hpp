/* 
 * StereoisomerGenerator.hpp 
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
 * \brief Definition of the class CDPL::Chem::StereoisomerGenerator.
 */

#ifndef CDPL_CHEM_STEREOISOMERGENERATOR_HPP
#define CDPL_CHEM_STEREOISOMERGENERATOR_HPP

#include <memory>
#include <vector>
#include <cstddef>
#include <utility>

#include "CDPL/Chem/APIPrefix.hpp"
#include "CDPL/Chem/StereoDescriptor.hpp"
#include "CDPL/Chem/AtomPredicate.hpp"
#include "CDPL/Chem/BondPredicate.hpp"
#include "CDPL/Util/Array.hpp"
#include "CDPL/Util/BitSet.hpp"


namespace CDPL
{

    namespace Chem
    {

        class MolecularGraph;
        
        /**
         * \brief StereoisomerGenerator.
         * \since 1.1
         */
        class CDPL_CHEM_API StereoisomerGenerator
        {

          public:
            typedef std::shared_ptr<StereoisomerGenerator> SharedPointer;

            typedef Util::Array<StereoDescriptor> StereoDescriptorArray;

            void setAtomPredicate(const AtomPredicate& pred);
            
            const AtomPredicate& getAtomPredicate() const;

            void setBondPredicate(const BondPredicate& pred);
            
            const BondPredicate& getBondPredicate() const;

            void enumerateAtomConfig(bool enumerate);

            bool atomConfigEnumerated() const;

            void enumerateBondConfig(bool enumerate);

            bool bondConfigEnumerated() const;

            void includeSpecifiedCenters(bool include);

            bool specifiedCentersIncluded() const;
  
            void includeSymmetricCenters(bool include);

            bool symmetricCentersIncluded() const;

            void includeBridgeheadAtoms(bool include);

            bool bridgeheadAtomsIncluded() const;

            void includeInvertibleNitrogens(bool include);

            bool invertibleNitrogensIncluded() const;

            void includeRingBonds(bool include);

            bool ringBondsIncluded() const;

            void setMinRingSize(std::size_t min_size);

            std::size_t getMinRingSize() const;

            void setup(const MolecularGraph& molgraph);

            bool generate();

            const StereoDescriptorArray& getAtomDescriptors();

            const StereoDescriptorArray& getBondDescriptors();
            
          private:
            typedef std::pair<bool, std::size_t> StereoCenterID;

            bool isExcluded(const Atom& atom, const MolecularGraph& molgraph, bool has_config);
            bool isExcluded(const Bond& bond, const MolecularGraph& molgraph, bool has_config) const;

            void findBridgeheadAtoms(const MolecularGraph& molgraph);
           
            void flipConfiguration(const StereoCenterID& ctr_id);

            typedef std::vector<StereoCenterID> StereoCenterIDList;

            AtomPredicate         atomPred;
            BondPredicate         bondPred;
            bool                  enumAtomConfig{true};
            bool                  enumBondConfig{true};
            bool                  incSpecifiedCtrs{false};
            bool                  incSymmetricCtrs{false};
            bool                  incBridgeheads{false};
            bool                  incInvNitrogens{false};
            bool                  incRingBonds{false};
            std::size_t           minRingSize{8};
            StereoDescriptorArray atomDescrs;
            StereoDescriptorArray bondDescrs;
            StereoCenterIDList    procCtrs;
            Util::BitSet          flipStates;
        };
    } // namespace Chem
} // namespace CDPL

#endif // CDPL_CHEM_STEREOISOMERGENERATOR_HPP
