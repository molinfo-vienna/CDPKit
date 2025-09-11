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

        class CDPL_CONFGEN_API RMSDConformerSelector
        {

          public:
            static constexpr std::size_t DEF_MAX_NUM_SYMMETRY_MAPPINGS = 32768;

            RMSDConformerSelector();

            RMSDConformerSelector(const RMSDConformerSelector&) = delete;

            RMSDConformerSelector& operator=(const RMSDConformerSelector&) = delete;

            void setMinRMSD(double min_rmsd);

            double getMinRMSD() const;

            void setAbortCallback(const CallbackFunction& func);

            const CallbackFunction& getAbortCallback() const;

            std::size_t getNumSymmetryMappings() const;

            void setMaxNumSymmetryMappings(std::size_t max_num);

            std::size_t getMaxNumSymmetryMappings() const;

            void setup(const Chem::MolecularGraph& molgraph, const Util::BitSet& atom_mask);

            void setup(const Chem::MolecularGraph& molgraph, const Util::BitSet& atom_mask,
                       const Util::BitSet& stable_config_atom_mask, const Math::Vector3DArray& coords);

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
