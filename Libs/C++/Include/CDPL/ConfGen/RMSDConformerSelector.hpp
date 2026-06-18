/* 
 * RMSDConformerSelector.hpp 
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
 * \brief Definition of class CDPL::ConfGen::RMSDConformerSelector.
 */

#ifndef CDPL_CONFGEN_RMSDCONFORMERSELECTOR_HPP
#define CDPL_CONFGEN_RMSDCONFORMERSELECTOR_HPP

#include <vector>
#include <cstddef>
#include <unordered_map>

#include "CDPL/ConfGen/APIPrefix.hpp"
#include "CDPL/ConfGen/CallbackFunction.hpp"
#include "CDPL/Chem/Fragment.hpp"
#include "CDPL/Chem/StereoDescriptor.hpp"
#include "CDPL/Chem/AutomorphismGroupSearch.hpp"
#include "CDPL/Util/BitSet.hpp"
#include "CDPL/Util/ObjectStack.hpp"
#include "CDPL/Util/ObjectPool.hpp"
#include "CDPL/Math/VectorArray.hpp"
#include "CDPL/Math/VectorArrayAlignmentCalculator.hpp"


namespace CDPL
{

    namespace ConfGen
    {

        /**
         * \brief Greedy RMSD-based conformer-diversity filter.
         *
         * For each candidate conformer the selector computes the minimum symmetry-equivalent RMSD against the set of
         * already-selected conformers. A new conformer is accepted (added to the selected set) only if its minimum
         * RMSD exceeds the configured threshold.
         */
        class CDPL_CONFGEN_API RMSDConformerSelector
        {

          public:
            /**
             * \brief Default maximum number of considered automorphism (symmetry) mappings per setup() call.
             */
            static constexpr std::size_t DEF_MAX_NUM_SYMMETRY_MAPPINGS = 32768;

            /**
             * \brief Constructs the \c %RMSDConformerSelector instance.
             */
            RMSDConformerSelector();

            RMSDConformerSelector(const RMSDConformerSelector&) = delete;

            RMSDConformerSelector& operator=(const RMSDConformerSelector&) = delete;

            /**
             * \brief Sets the minimum RMSD that a candidate conformer must keep from every already-selected conformer to be accepted.
             * \param min_rmsd The new minimum RMSD.
             */
            void setMinRMSD(double min_rmsd);

            /**
             * \brief Returns the currently configured minimum RMSD threshold.
             * \return The minimum RMSD threshold.
             */
            double getMinRMSD() const;

            /**
             * \brief Sets the callback invoked periodically to allow the selection to be aborted by the user.
             * \param func The abort-check callback.
             */
            void setAbortCallback(const CallbackFunction& func);

            /**
             * \brief Returns the currently configured abort-check callback.
             * \return A \c const reference to the abort-check callback.
             */
            const CallbackFunction& getAbortCallback() const;

            /**
             * \brief Returns the number of symmetry (automorphism) mappings enumerated during the last setup() call.
             * \return The symmetry-mapping count.
             */
            std::size_t getNumSymmetryMappings() const;

            /**
             * \brief Sets the maximum number of symmetry mappings to enumerate per setup() call.
             * \param max_num The new maximum number of mappings.
             */
            void setMaxNumSymmetryMappings(std::size_t max_num);

            /**
             * \brief Returns the currently configured maximum number of symmetry mappings.
             * \return The maximum number of mappings.
             */
            std::size_t getMaxNumSymmetryMappings() const;

            /**
             * \brief Sets up the selector for the subgraph of \a molgraph defined by \a atom_mask.
             * \param molgraph The parent molecular graph.
             * \param atom_mask The bit mask selecting atoms considered during RMSD computation.
             */
            void setup(const Chem::MolecularGraph& molgraph, const Util::BitSet& atom_mask);

            /**
             * \brief Sets up the selector for the subgraph of \a molgraph defined by \a atom_mask while restricting the
             *        enumerated automorphisms to those that preserve the chirality of atoms in \a stable_config_atom_mask
             *        with respect to the supplied 3D coordinates \a coords.
             * \param molgraph The parent molecular graph.
             * \param atom_mask The bit mask selecting atoms considered during RMSD computation.
             * \param stable_config_atom_mask The bit mask of atoms whose stereo-configuration must be preserved.
             * \param coords The 3D coordinates used to determine the stereo-configurations.
             */
            void setup(const Chem::MolecularGraph& molgraph, const Util::BitSet& atom_mask,
                       const Util::BitSet& stable_config_atom_mask, const Math::Vector3DArray& coords);

            /**
             * \brief Tests whether \a conf_coords is sufficiently different from already-selected conformers and, if so, adds it to the selected set.
             * \param conf_coords The candidate conformer's 3D coordinates.
             * \return \c true if the conformer was selected, and \c false otherwise.
             */
            bool selected(const Math::Vector3DArray& conf_coords);

          private:
            typedef std::vector<std::size_t>              IndexArray;
            typedef Util::ObjectPool<Math::Vector3DArray> VectorArrayCache;
            typedef VectorArrayCache::SharedObjectPointer VectorArrayPtr;

            void buildSymMappingSearchMolGraph(const Util::BitSet& atom_mask);
            void setupSymMappingValidationData(const Util::BitSet& stable_config_atom_mask,
                                               const Math::Vector3DArray& conf_coords);

            bool processSymMapping(const Chem::MolecularGraph&  molgraph,
                                   const Chem::AtomBondMapping& mapping);
            bool isValidSymMapping(const Chem::AtomBondMapping& mapping) const;

            VectorArrayPtr buildCoordsArrayForMapping(const IndexArray& mapping,
                                                      const Math::Vector3DArray& conf_coords);

            typedef std::unordered_map<const Chem::Atom*, Chem::StereoDescriptor> AtomStereoDescriptorMap;
            typedef std::vector<const Chem::Atom*>                                AtomList;
            typedef Util::ObjectStack<IndexArray>                                 IndexArrayCache;
            typedef std::vector<IndexArray*>                                      IndexArrayList;
            typedef std::vector<VectorArrayPtr>                                   VectorArrayList;
            typedef Math::VectorArrayAlignmentCalculator<Math::Vector3DArray>     AlignmentCalculator;

            IndexArrayCache               idxArrayCache;
            VectorArrayCache              vecArrayCache;
            const Chem::MolecularGraph*   molGraph;
            Chem::AutomorphismGroupSearch symMappingSearch;
            Chem::Fragment                symMappingSearchMolGraph;
            IndexArrayList                symMappings;
            AtomStereoDescriptorMap       atomStereoDescrs;
            AlignmentCalculator           alignmentCalc;
            VectorArrayList               confAlignCoords;
            VectorArrayList               selectedConfAlignCoords;
            AtomList                      atomNeighbors;
            double                        minRMSD;
            std::size_t                   maxNumSymMappings;
            CallbackFunction              abortCallback;
        };
    } // namespace ConfGen
} // namespace CDPL

#endif // CDPL_CONFGEN_RMSDCONFORMERSELECTOR_HPP
