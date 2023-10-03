/* 
 * GRAILDescriptorCalculator.hpp 
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
 * \brief Definition of the class CDPL::GRAIL::GRAILDescriptorCalculator.
 */

#ifndef CDPL_GRAIL_GRAILDESCRIPTORCALCULATORIMPL_HPP
#define CDPL_GRAIL_GRAILDESCRIPTORCALCULATORIMPL_HPP

#include <vector>
#include <utility>
#include <cstddef>
#include <memory>
#include <functional>

#include "CDPL/Pharm/DefaultPharmacophoreGenerator.hpp"
#include "CDPL/Pharm/BasicPharmacophore.hpp"
#include "CDPL/Pharm/FeatureInteractionScore.hpp"
#include "CDPL/Chem/Atom3DCoordinatesFunction.hpp"
#include "CDPL/MolProp/TPSACalculator.hpp"
#include "CDPL/Math/VectorArray.hpp"
#include "CDPL/Math/Vector.hpp"
#include "CDPL/Util/BitSet.hpp"


namespace CDPL
{

    namespace Internal
    {

        template <typename PT, typename CT, typename ST>
        class Octree;
    }

    namespace GRAIL
    {

        class GRAILDescriptorCalculatorImpl
        {

          public:
            struct FeatureInteractionFuncData
            {

                typedef Pharm::FeatureInteractionScore::SharedPointer ScoringFuncPtr;

                unsigned int   ligFtrType;
                unsigned int   tgtFtrType;
                ScoringFuncPtr scoringFunc;
            };

            typedef std::vector<FeatureInteractionFuncData> FeatureInteractionFuncList;

            struct FeatureTypeInfo
            {

                unsigned int type;
                bool         isHBD;
            };

            typedef std::vector<FeatureTypeInfo> FeatureTypeInfoList;

            typedef std::function<unsigned int(const Pharm::Feature&, bool)> FeatureTypeFunc;

            GRAILDescriptorCalculatorImpl(const FeatureInteractionFuncList& ftr_ia_funcs,
                                          const FeatureTypeInfoList& lig_descr_ftr_types,
                                          const FeatureTypeInfoList& tgt_env_hba_hbd_ftr_types,
                                          const FeatureTypeFunc& ftr_type_func);

            GRAILDescriptorCalculatorImpl(const GRAILDescriptorCalculatorImpl& calc);

            GRAILDescriptorCalculatorImpl& operator=(const GRAILDescriptorCalculatorImpl& calc);

            void initTargetData(const Chem::MolecularGraph& tgt_env, const Chem::Atom3DCoordinatesFunction& coords_func,
                                bool tgt_env_changed = true);

            void initLigandData(const Chem::MolecularGraph& ligand);

            void calculate(const Math::Vector3DArray& atom_coords, Math::DVector& descr, bool update_lig_part = true);

          private:
            void calcLigFtrCoordinates(const Math::Vector3DArray::StorageType& atom_coords);

            void calcTgtEnvHBAHBDOccupations(const Math::Vector3DArray::StorageType& atom_coords,
                                             Math::DVector& descr, std::size_t& idx);
            void calcTgtEnvHBAHBDOccupation(const Math::Vector3DArray::StorageType& atom_coords,
                                            Math::DVector& descr, unsigned int tgt_ftr_type, bool is_hba_type,
                                            std::size_t& idx);

            void calcFeatureInteractionScores(Math::DVector& descr, std::size_t& idx);

            void calcElectrostaticInteractionEnergy(const Math::Vector3DArray::StorageType& atom_coords,
                                                    Math::DVector& descr, std::size_t& idx);

            void calcVdWInteractionEnergy(const Math::Vector3DArray::StorageType& atom_coords,
                                          Math::DVector& descr, std::size_t idx);

            typedef std::vector<std::size_t>                                    IndexList;
            typedef std::vector<const Pharm::Feature*>                          FeatureList;
            typedef std::vector<double>                                         DoubleArray;
            typedef std::vector<IndexList>                                      IndexListArray;
            typedef std::vector<Math::Vector3D>                                 FastVector3DArray;
            typedef Internal::Octree<Math::Vector3D, FastVector3DArray, double> Octree;
            typedef std::shared_ptr<Octree>                                     OctreePtr;

            struct FeatureSubset
            {

                FeatureList       features;
                OctreePtr         octree;
                FastVector3DArray ftrCoords;
            };

            struct TargetAtomCoordsFunc
            {

                TargetAtomCoordsFunc(const Chem::MolecularGraph& tgt_env, const FastVector3DArray& coords):
                    tgtEnv(&tgt_env), coords(&coords) {}

                const Math::Vector3D& operator()(const Chem::Atom& atom) const;

                const Chem::MolecularGraph* tgtEnv;
                const FastVector3DArray*    coords;
            };

            typedef std::vector<FeatureSubset> FeatureSubsetList;
            typedef std::pair<double, double>  DoublePair;
            typedef std::vector<DoublePair>    DoublePairArray;

            void getVdWParameters(const Chem::Atom& atom, const Chem::MolecularGraph& molgraph, DoublePair& params) const;
            bool isPolarHydrogen(const Chem::Atom& atom, const Chem::MolecularGraph& molgraph) const;

            void initPharmGenerators();

            void copyTgtFtrSubsets(const FeatureSubsetList& ftr_ss_list);

            FeatureInteractionFuncList           ftrInteractionFuncList;
            FeatureTypeInfoList                  ligDescrFtrTypes;
            FeatureTypeInfoList                  tgtEnvOccupHBAHBDTypes;
            FeatureTypeFunc                      ftrTypeFunc;
            Pharm::DefaultPharmacophoreGenerator tgtPharmGenerator;
            Pharm::BasicPharmacophore            tgtPharmacophore;
            DoubleArray                          tgtAtomCharges;
            DoublePairArray                      tgtAtomVdWParams;
            FastVector3DArray                    tgtAtomCoords;
            OctreePtr                            tgtAtomOctree;
            FeatureSubsetList                    tgtFtrSubsets;
            Pharm::DefaultPharmacophoreGenerator ligPharmGenerator;
            Pharm::BasicPharmacophore            ligPharmacophore;
            DoubleArray                          ligAtomCharges;
            DoublePairArray                      ligAtomVdWParams;
            IndexList                            ligHeavyAtoms;
            IndexListArray                       ligFtrSubsets;
            IndexListArray                       ligFtrAtoms;
            DoubleArray                          ligFtrWeights;
            FastVector3DArray                    ligFtrCoords;
            MolProp::TPSACalculator              ligTPSACalculator;
            DoubleArray                          ligDescriptor;
            Util::BitSet                         ligHBAAtomMask;
            Util::BitSet                         ligHBDAtomMask;
            std::size_t                          numLigAtoms;
            IndexList                            tmpIndexList;
        };
    } // namespace GRAIL
} // namespace CDPL

#endif // CDPL_GRAIL_GRAILDESCRIPTORCALCULATORIMPL_HPP
