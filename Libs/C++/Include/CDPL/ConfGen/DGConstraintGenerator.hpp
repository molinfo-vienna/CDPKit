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

        /**
         * \brief Constructs geometric constraints (distance, planarity, volume) for distance-geometry-based
         *        3D structure generation.
         *
         * Given a molecular graph (and optionally an MMFF94 force field interaction parameter set) the
         * generator derives ideal bond lengths, bond angles and 1,4-distances, identifies atom and bond
         * stereo centers and emits the corresponding constraints into a Util::DG3DCoordinatesGenerator.
         * The constraint set is used by ConfGen::DGStructureGenerator to produce a 3D embedding of the
         * molecular graph.
         */
        class CDPL_CONFGEN_API DGConstraintGenerator
        {

          public:
            /**
             * \brief Pair holding an atom or bond index plus the associated stereo descriptor.
             */
            typedef std::pair<std::size_t, Chem::StereoDescriptor> StereoCenterData;

          private:
            typedef std::vector<StereoCenterData> StereoCenterDataArray;

          public:
            /**
             * \brief A constant iterator over StereoCenterData entries.
             */
            typedef StereoCenterDataArray::const_iterator ConstStereoCenterDataIterator;

            /**
             * \brief Constructs the \c %DGConstraintGenerator instance.
             */
            DGConstraintGenerator();

            /**
             * \brief Returns a reference to the constraint-generation settings.
             * \return A reference to the settings.
             */
            DGConstraintGeneratorSettings& getSettings();

            /**
             * \brief Returns a \c const reference to the constraint-generation settings.
             * \return A \c const reference to the settings.
             */
            const DGConstraintGeneratorSettings& getSettings() const;

            /**
             * \brief Registers an atom stereo center to be constrained.
             * \param atom The stereogenic atom.
             * \param descr The stereo descriptor specifying the desired configuration.
             */
            void addAtomStereoCenter(const Chem::Atom& atom, const Chem::StereoDescriptor& descr);

            /**
             * \brief Registers a bond stereo center to be constrained.
             * \param bond The stereogenic bond.
             * \param descr The stereo descriptor specifying the desired configuration.
             */
            void addBondStereoCenter(const Chem::Bond& bond, const Chem::StereoDescriptor& descr);

            /**
             * \brief Initializes the generator for the molecular graph \a molgraph using default geometry data.
             * \param molgraph The molecular graph to process.
             */
            void setup(const Chem::MolecularGraph& molgraph);

            /**
             * \brief Initializes the generator for the molecular graph \a molgraph using bond lengths and angles obtained from \a ia_data.
             * \param molgraph The molecular graph to process.
             * \param ia_data MMFF94 interaction data providing the reference bond lengths and angles.
             */
            void setup(const Chem::MolecularGraph& molgraph, const ForceField::MMFF94InteractionData& ia_data);

            /**
             * \brief Returns the bit mask of hydrogen atoms that have been excluded from constraint generation.
             * \return A \c const reference to the excluded-hydrogen bit mask.
             */
            const Util::BitSet& getExcludedHydrogenMask() const;

            /**
             * \brief Returns the number of registered atom stereo centers.
             * \return The number of atom stereo centers.
             */
            std::size_t getNumAtomStereoCenters() const;

            /**
             * \brief Returns the number of registered bond stereo centers.
             * \return The number of bond stereo centers.
             */
            std::size_t getNumBondStereoCenters() const;

            /**
             * \brief Returns the stereo-center data for the atom stereo center at index \a idx.
             * \param idx The zero-based stereo-center index.
             * \return A \c const reference to the stereo-center data.
             * \throw Base::IndexError if the number of atom stereo centers is zero or \a idx is not in the range [0, getNumAtomStereoCenters() - 1].
             */
            const StereoCenterData& getAtomStereoCenterData(std::size_t idx) const;

            /**
             * \brief Returns the stereo-center data for the bond stereo center at index \a idx.
             * \param idx The zero-based stereo-center index.
             * \return A \c const reference to the stereo-center data.
             * \throw Base::IndexError if the number of bond stereo centers is zero or \a idx is not in the range [0, getNumBondStereoCenters() - 1].
             */
            const StereoCenterData& getBondStereoCenterData(std::size_t idx) const;

            /**
             * \brief Returns a constant iterator pointing to the first atom stereo center.
             * \return A constant iterator pointing to the first atom stereo center.
             */
            ConstStereoCenterDataIterator getAtomStereoCenterDataBegin() const;

            /**
             * \brief Returns a constant iterator pointing one past the last atom stereo center.
             * \return A constant iterator pointing one past the last atom stereo center.
             */
            ConstStereoCenterDataIterator getAtomStereoCenterDataEnd() const;

            /**
             * \brief Returns a constant iterator pointing to the first bond stereo center.
             * \return A constant iterator pointing to the first bond stereo center.
             */
            ConstStereoCenterDataIterator getBondStereoCenterDataBegin() const;

            /**
             * \brief Returns a constant iterator pointing one past the last bond stereo center.
             * \return A constant iterator pointing one past the last bond stereo center.
             */
            ConstStereoCenterDataIterator getBondStereoCenterDataEnd() const;

            /**
             * \brief Adds distance and volume constraints that fix the supplied substructure to the given coordinates.
             * \param atoms The atoms whose positions shall be fixed.
             * \param coords The 3D coordinates to fix the atoms to.
             * \param coords_gen The coordinates generator to add the constraints to.
             * \since 1.1
             */
            void addFixedSubstructureConstraints(const Chem::AtomContainer& atoms, const Math::Vector3DArray& coords,
                                                 Util::DG3DCoordinatesGenerator& coords_gen);

            /**
             * \brief Adds bond-length distance constraints to \a coords_gen.
             * \param coords_gen The coordinates generator to add the constraints to.
             */
            void addBondLengthConstraints(Util::DG3DCoordinatesGenerator& coords_gen);

            /**
             * \brief Adds bond-angle (1,3) distance constraints to \a coords_gen.
             * \param coords_gen The coordinates generator to add the constraints to.
             */
            void addBondAngleConstraints(Util::DG3DCoordinatesGenerator& coords_gen);

            /**
             * \brief Adds 1,4-distance constraints (cis/trans bounds) to \a coords_gen.
             * \param coords_gen The coordinates generator to add the constraints to.
             */
            void add14DistanceConstraints(Util::DG3DCoordinatesGenerator& coords_gen);

            /**
             * \brief Adds default (Van der Waals-derived) lower/upper distance constraints between all
             *        non-bonded atom pairs to \a coords_gen.
             * \param coords_gen The coordinates generator to add the constraints to.
             */
            void addDefaultDistanceConstraints(Util::DG3DCoordinatesGenerator& coords_gen);

            /**
             * \brief Adds volume constraints enforcing the registered atom stereo-center configurations to \a coords_gen.
             * \param coords_gen The coordinates generator to add the constraints to.
             */
            void addAtomConfigurationConstraints(Util::DG3DCoordinatesGenerator& coords_gen);

            /**
             * \brief Adds distance and volume constraints enforcing the registered bond stereo-center configurations to \a coords_gen.
             * \param coords_gen The coordinates generator to add the constraints to.
             */
            void addBondConfigurationConstraints(Util::DG3DCoordinatesGenerator& coords_gen);

            /**
             * \brief Adds planarity (zero-volume) constraints for sp2-hybridized / aromatic atoms to \a coords_gen.
             * \param coords_gen The coordinates generator to add the constraints to.
             */
            void addAtomPlanarityConstraints(Util::DG3DCoordinatesGenerator& coords_gen);

            /**
             * \brief Adds planarity (zero-volume) constraints for double and aromatic bonds to \a coords_gen.
             * \param coords_gen The coordinates generator to add the constraints to.
             */
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
