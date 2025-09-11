/* 
 * DGConstraintGenerator.hpp 
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
 * \brief Definition of class CDPL::ConfGen::DGConstraintGenerator.
 */

#ifndef CDPL_CONFGEN_DGCONSTRAINTGENERATOR_HPP
#define CDPL_CONFGEN_DGCONSTRAINTGENERATOR_HPP

#include <utility>
#include <cstddef>
#include <unordered_map>
#include <tuple>

#include "CDPL/ConfGen/APIPrefix.hpp"
#include "CDPL/ConfGen/DGConstraintGeneratorSettings.hpp"
#include "CDPL/Chem/StereoDescriptor.hpp"
#include "CDPL/Math/VectorArray.hpp"
#include "CDPL/Util/DGCoordinatesGenerator.hpp"
#include "CDPL/Util/BitSet.hpp"


namespace CDPL
{

    namespace ForceField
    {

        class MMFF94InteractionData;
    }

    namespace Chem
    {

        class FragmentList;
        class AtomContainer;
        class MolecularGraph;
        class Atom;
        class Bond;
    } // namespace Chem

    namespace ConfGen
    {

        class CDPL_CONFGEN_API DGConstraintGenerator
        {

          public:
            typedef std::pair<std::size_t, Chem::StereoDescriptor> StereoCenterData;

          private:
            typedef std::vector<StereoCenterData> StereoCenterDataArray;

          public:
            typedef StereoCenterDataArray::const_iterator ConstStereoCenterDataIterator;

            DGConstraintGenerator();

            DGConstraintGeneratorSettings& getSettings();

            const DGConstraintGeneratorSettings& getSettings() const;

            void addAtomStereoCenter(const Chem::Atom& atom, const Chem::StereoDescriptor& descr);
            void addBondStereoCenter(const Chem::Bond& bond, const Chem::StereoDescriptor& descr);

            void setup(const Chem::MolecularGraph& molgraph);
            void setup(const Chem::MolecularGraph& molgraph, const ForceField::MMFF94InteractionData& ia_data);

            const Util::BitSet& getExcludedHydrogenMask() const;

            std::size_t getNumAtomStereoCenters() const;
            std::size_t getNumBondStereoCenters() const;

            const StereoCenterData& getAtomStereoCenterData(std::size_t idx) const;
            const StereoCenterData& getBondStereoCenterData(std::size_t idx) const;

            ConstStereoCenterDataIterator getAtomStereoCenterDataBegin() const;
            ConstStereoCenterDataIterator getAtomStereoCenterDataEnd() const;

            ConstStereoCenterDataIterator getBondStereoCenterDataBegin() const;
            ConstStereoCenterDataIterator getBondStereoCenterDataEnd() const;

            /*
             * \since 1.1
             */
            void addFixedSubstructureConstraints(const Chem::AtomContainer& atoms, const Math::Vector3DArray& coords,
                                                 Util::DG3DCoordinatesGenerator& coords_gen);
            void addBondLengthConstraints(Util::DG3DCoordinatesGenerator& coords_gen);
            void addBondAngleConstraints(Util::DG3DCoordinatesGenerator& coords_gen);
            void add14DistanceConstraints(Util::DG3DCoordinatesGenerator& coords_gen);
            void addDefaultDistanceConstraints(Util::DG3DCoordinatesGenerator& coords_gen);

            void addAtomConfigurationConstraints(Util::DG3DCoordinatesGenerator& coords_gen);
            void addBondConfigurationConstraints(Util::DG3DCoordinatesGenerator& coords_gen);

            void addAtomPlanarityConstraints(Util::DG3DCoordinatesGenerator& coords_gen);
            void addBondPlanarityConstraints(Util::DG3DCoordinatesGenerator& coords_gen);

          private:
            void setup(const Chem::MolecularGraph& molgraph, const ForceField::MMFF94InteractionData* ia_data);

            void addFixedSubstructVolConstraints(const Chem::AtomContainer& atoms, const Math::Vector3DArray& coords,
                                                 Util::DG3DCoordinatesGenerator& coords_gen, std::size_t* ref_atom_inds,
                                                 std::size_t& num_vol_constr, std::size_t level);

            void init(const Chem::MolecularGraph& molgraph);

            void assignBondLengths(const ForceField::MMFF94InteractionData* ia_data);
            void assignBondAngles(const ForceField::MMFF94InteractionData* ia_data);

            void extractAtomStereoCenterData();
            void extractBondStereoCenterData();

            void   setBondLength(std::size_t atom1_idx, std::size_t atom2_idx, double length);
            double getBondLength(std::size_t atom1_idx, std::size_t atom2_idx) const;

            void   setBondAngle(std::size_t atom1_idx, std::size_t atom2_idx, std::size_t atom3_idx, double angle);
            double getBondAngle(std::size_t atom1_idx, std::size_t atom2_idx, std::size_t atom3_idx) const;

            std::size_t getSmallestRingSize(const Chem::FragmentList& sssr, const Chem::Bond& bond1, const Chem::Bond& bond2) const;
            std::size_t getSmallestRingSize(const Chem::FragmentList& sssr, std::size_t atom1_idx, std::size_t atom2_idx) const;

            void markAtomPairProcessed(std::size_t atom1_idx, std::size_t atom2_idx);
            bool atomPairProcessed(std::size_t atom1_idx, std::size_t atom2_idx) const;

            double calc13AtomDistance(double bond1_len, double bond2_len, double angle) const;

            double calcCis14AtomDistance(double bond1_len, double bond2_len, double bond3_len,
                                         double angle_12, double angle_23) const;
            double calcTrans14AtomDistance(double bond1_len, double bond2_len, double bond3_len,
                                           double angle_12, double angle_23) const;

            bool isPlanar(const Chem::Atom& atom) const;
            bool isPlanar(const Chem::Bond& bond) const;

            typedef std::vector<std::size_t> AtomIndexList;

            std::size_t getNeighborAtoms(const Chem::Atom& atom, AtomIndexList& idx_list,
                                         const Chem::Atom* x_atom = 0) const;

            typedef std::pair<std::size_t, std::size_t>               BondLengthKey;
            typedef std::tuple<std::size_t, std::size_t, std::size_t> BondAngleKey;

            struct CDPL_CONFGEN_API BondAngleKeyHash
            {

                std::size_t operator()(const BondAngleKey& k) const;
            };

            struct CDPL_CONFGEN_API BondLengthKeyHash
            {

                std::size_t operator()(const BondLengthKey& k) const;
            };

            typedef std::unordered_map<BondLengthKey, double, BondLengthKeyHash> BondLengthTable;
            typedef std::unordered_map<BondAngleKey, double, BondAngleKeyHash>   BondAngleTable;

            const Chem::MolecularGraph*   molGraph;
            Util::BitSet                  hAtomMask;
            Util::BitSet                  procAtomPairMask;
            Util::BitSet                  stereoAtomMask;
            BondLengthTable               bondLengthTable;
            BondAngleTable                bondAngleTable;
            StereoCenterDataArray         atomStereoData;
            StereoCenterDataArray         bondStereoData;
            std::size_t                   numAtoms;
            AtomIndexList                 atomIndexList1;
            AtomIndexList                 atomIndexList2;
            DGConstraintGeneratorSettings settings;
        };
    } // namespace ConfGen
} // namespace CDPL

#endif // CDPL_CONFGEN_DGCONSTRAINTGENERATOR_HPP
