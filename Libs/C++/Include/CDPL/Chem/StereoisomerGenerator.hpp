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
 * \brief Definition of class CDPL::Chem::StereoisomerGenerator.
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
         * \brief Enumerates the stereoisomers of a molecular graph by flipping the configurations of
         *        selected atom and bond stereocenters.
         *
         * After calling setup() for an input molecular graph, each call to generate() yields the next
         * stereoisomer (encoded as per-atom and per-bond StereoDescriptor arrays accessible via
         * getAtomDescriptors() / getBondDescriptors()); generate() returns \c false when the enumeration
         * is exhausted. Atom and bond predicates plus a number of inclusion flags control which stereocenters
         * are enumerated.
         *
         * \since 1.1
         */
        class CDPL_CHEM_API StereoisomerGenerator
        {

          public:
            /**
             * \brief A reference-counted smart pointer [\ref SHPTR] for dynamically allocated \c %StereoisomerGenerator instances.
             */
            typedef std::shared_ptr<StereoisomerGenerator> SharedPointer;

            /**
             * \brief Array of StereoDescriptor values (one per atom or one per bond of the input molecular graph).
             */
            typedef Util::Array<StereoDescriptor> StereoDescriptorArray;

            /**
             * \brief Sets the predicate used to filter atom stereocenters considered during enumeration.
             * \param pred The new atom predicate.
             */
            void setAtomPredicate(const AtomPredicate& pred);

            /**
             * \brief Returns the currently configured atom predicate.
             * \return A \c const reference to the atom predicate.
             */
            const AtomPredicate& getAtomPredicate() const;

            /**
             * \brief Sets the predicate used to filter bond stereocenters considered during enumeration.
             * \param pred The new bond predicate.
             */
            void setBondPredicate(const BondPredicate& pred);

            /**
             * \brief Returns the currently configured bond predicate.
             * \return A \c const reference to the bond predicate.
             */
            const BondPredicate& getBondPredicate() const;

            /**
             * \brief Specifies whether atom-stereocenter configurations shall be enumerated.
             * \param enumerate If \c true, atom configurations are flipped during enumeration.
             */
            void enumerateAtomConfig(bool enumerate);

            /**
             * \brief Tells whether atom-stereocenter configurations are enumerated.
             * \return \c true if atom configurations are enumerated, and \c false otherwise.
             */
            bool atomConfigEnumerated() const;

            /**
             * \brief Specifies whether bond-stereocenter configurations shall be enumerated.
             * \param enumerate If \c true, bond configurations are flipped during enumeration.
             */
            void enumerateBondConfig(bool enumerate);

            /**
             * \brief Tells whether bond-stereocenter configurations are enumerated.
             * \return \c true if bond configurations are enumerated, and \c false otherwise.
             */
            bool bondConfigEnumerated() const;

            /**
             * \brief Specifies whether stereocenters with explicitly specified configurations shall be enumerated.
             * \param include If \c true, specified stereocenters are also flipped.
             */
            void includeSpecifiedCenters(bool include);

            /**
             * \brief Tells whether specified stereocenters are enumerated.
             * \return \c true if specified stereocenters are included, and \c false otherwise.
             */
            bool specifiedCentersIncluded() const;

            /**
             * \brief Specifies whether topologically-symmetric stereocenters shall be enumerated.
             * \param include If \c true, symmetric stereocenters are also flipped.
             */
            void includeSymmetricCenters(bool include);

            /**
             * \brief Tells whether topologically-symmetric stereocenters are enumerated.
             * \return \c true if symmetric stereocenters are included, and \c false otherwise.
             */
            bool symmetricCentersIncluded() const;

            /**
             * \brief Specifies whether bridgehead atoms in fused ring systems shall be enumerated as stereocenters.
             * \param include If \c true, bridgehead atoms are included.
             */
            void includeBridgeheadAtoms(bool include);

            /**
             * \brief Tells whether bridgehead atoms are enumerated.
             * \return \c true if bridgehead atoms are included, and \c false otherwise.
             */
            bool bridgeheadAtomsIncluded() const;

            /**
             * \brief Specifies whether invertible (pyramidal) nitrogen stereocenters shall be enumerated.
             * \param include If \c true, invertible nitrogens are included.
             */
            void includeInvertibleNitrogens(bool include);

            /**
             * \brief Tells whether invertible nitrogen stereocenters are enumerated.
             * \return \c true if invertible nitrogens are included, and \c false otherwise.
             */
            bool invertibleNitrogensIncluded() const;

            /**
             * \brief Specifies whether ring bonds (large enough to allow cis/trans isomerism) shall be enumerated.
             * \param include If \c true, ring bonds whose ring is at least getMinRingSize() atoms in size are included.
             */
            void includeRingBonds(bool include);

            /**
             * \brief Tells whether ring bonds are enumerated.
             * \return \c true if ring bonds are included, and \c false otherwise.
             */
            bool ringBondsIncluded() const;

            /**
             * \brief Sets the minimum ring size for a ring bond to be eligible as a stereocenter.
             * \param min_size The new minimum ring size (in atoms).
             */
            void setMinRingSize(std::size_t min_size);

            /**
             * \brief Returns the minimum ring size for a ring bond to be eligible as a stereocenter.
             * \return The minimum ring size.
             */
            std::size_t getMinRingSize() const;

            /**
             * \brief Prepares the generator for enumerating the stereoisomers of \a molgraph.
             * \param molgraph The input molecular graph.
             */
            void setup(const MolecularGraph& molgraph);

            /**
             * \brief Advances the enumeration by one step and updates the per-atom/per-bond stereo-descriptor arrays.
             * \return \c true if a new stereoisomer was generated, and \c false if the enumeration is exhausted.
             */
            bool generate();

            /**
             * \brief Returns the per-atom stereo descriptors for the current stereoisomer.
             * \return A \c const reference to the atom-stereo-descriptor array.
             */
            const StereoDescriptorArray& getAtomDescriptors();

            /**
             * \brief Returns the per-bond stereo descriptors for the current stereoisomer.
             * \return A \c const reference to the bond-stereo-descriptor array.
             */
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
