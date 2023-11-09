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

#include "CDPL/Chem/APIPrefix.hpp"
#include "CDPL/Chem/StereoDescriptor.hpp"
#include "CDPL/Chem/AtomPredicate.hpp"
#include "CDPL/Chem/BondPredicate.hpp"
#include "CDPL/Util/Array.hpp"


namespace CDPL
{

    namespace Chem
    {

        class MolecularGraph;
        class BondContainer;
        
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

            void enumerateAtomCenters(bool enumerate);

            bool atomCentersEnumerated() const;

            void enumerateBondCenters(bool enumerate);

            bool bondCentersEnumerated() const;

            void enumerateSpecifiedCenters(bool enumerate);

            bool specifiedCentersEnumerated() const;
  
            void enumerateSymmetricCenters(bool enumerate);

            bool symmetricCentersEnumerated() const;

            void excludeBridgeheadAtoms(bool exclude);

            bool bridgeheadAtomsExcluded() const;

            void excludeNitrogens(bool exclude);

            bool nitrogensExcluded() const;

            void excludeRingBonds(bool exclude);

            bool ringBondsExcluded() const;

            void setMinRingSize(std::size_t min_size);

            std::size_t getMinRingSize() const;

            void setup(const MolecularGraph& molgraph);

            bool generate();

            const StereoDescriptorArray& getAtomDescriptors();

            const StereoDescriptorArray& getBondDescriptors();
            
          private:
            typedef std::vector<std::size_t> IndexList;

            bool isExcluded(const Atom& atom, const MolecularGraph& molgraph, bool has_config);
            bool isExcluded(const Bond& bond, const MolecularGraph& molgraph, bool has_config) const;

            bool isBridgehead(const Atom& atom, const MolecularGraph& molgraph);
            bool haveCommonBond(const BondContainer& r1, const BondContainer& r2) const;

            AtomPredicate         atomPred;
            BondPredicate         bondPred;
            bool                  enumAtomCtrs{true};
            bool                  enumBondCtrs{true};
            bool                  enumSpecifiedCtrs{false};
            bool                  enumSymmetricCtrs{false};
            bool                  exclBridgeheads{true};
            bool                  exclNitrogens{true};
            bool                  exclRingBonds{true};
            std::size_t           minRingSize{10};
            StereoDescriptorArray atomDescrs;
            IndexList             atomCtrs;
            StereoDescriptorArray bondDescrs;
            IndexList             bondCtrs;
            IndexList             atomRingSet;
        };
    } // namespace Chem
} // namespace CDPL

#endif // CDPL_CHEM_STEREOISOMERGENERATOR_HPP
