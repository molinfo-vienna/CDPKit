/* 
 * ChEMBLStandardizer.hpp 
 *
 * Implementation of the ChEMBL molecule standardization and parent compound extraction procedure
 * (A. P. Bento et al., An open source chemical structure curation pipeline using RDKit, J. Cheminformatics 2020, 12, 51) 
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
 * \brief Definition of class CDPL::Chem::ChEMBLStandardizer.
 */

#ifndef CDPL_CHEM_CHEMBLSTANDARDIZER_HPP
#define CDPL_CHEM_CHEMBLSTANDARDIZER_HPP

#include <vector>
#include <cstdint>
#include <utility>
#include <unordered_set>
#include <memory>

#include <boost/functional/hash.hpp>

#include "CDPL/Chem/APIPrefix.hpp"
#include "CDPL/Chem/BasicMolecule.hpp"
#include "CDPL/Chem/Fragment.hpp"
#include "CDPL/Chem/KekuleStructureCalculator.hpp"
#include "CDPL/Chem/SubstructureSearch.hpp"
#include "CDPL/Chem/HashCodeCalculator.hpp"
#include "CDPL/Chem/ProtonationStateStandardizer.hpp"
#include "CDPL/Util/BitSet.hpp"
#include "CDPL/Math/VectorArray.hpp"


namespace CDPL
{

    namespace Chem
    {

        /**
         * \brief Implementation of the ChEMBL structure preprocessing pipeline.
         * \see [\ref CSCP]
         */
        class CDPL_CHEM_API ChEMBLStandardizer
        {

          public:
            /**
             * \brief A reference-counted smart pointer [\ref SHPTR] for dynamically allocated \c %ChEMBLStandardizer instances.
             */
            typedef std::shared_ptr<ChEMBLStandardizer> SharedPointer;

            /**
             * \brief Bitwise-OR-combined flags reporting which standardization steps modified the input molecule.
             */
            enum ChangeFlags
            {

                /**
                 * \brief No changes were applied.
                 */
                NONE = 0x0,

                /**
                 * \brief The molecule matched a ChEMBL exclusion criterion and was not processed further.
                 */
                EXCLUDED = 0x1,

                /**
                 * \brief Removable explicit hydrogen atoms were removed.
                 */
                EXPLICIT_HYDROGENS_REMOVED = 0x2,

                /**
                 * \brief Atoms/bonds with unknown stereo descriptors were standardized.
                 */
                UNKNOWN_STEREO_STANDARDIZED = 0x4,

                /**
                 * \brief Aromatic bonds were kekulized to alternating single/double bonds.
                 */
                BONDS_KEKULIZED = 0x8,

                /**
                 * \brief Functional-group structure normalizations were applied.
                 */
                STRUCTURE_NORMALIZED = 0x10,

                /**
                 * \brief Atom formal charges were removed where possible.
                 */
                CHARGES_REMOVED = 0x20,

                /**
                 * \brief Defined stereo at tartrate-like substructures was cleared.
                 */
                TARTRATE_STEREO_CLEARED = 0x40,

                /**
                 * \brief 2D bond-angle artefacts were corrected.
                 */
                STRUCTURE_2D_CORRECTED = 0x80,

                /**
                 * \brief Atom isotope information was cleared.
                 */
                ISOTOPE_INFO_CLEARED = 0x100,

                /**
                 * \brief Salt components were removed (parent extraction only).
                 */
                SALT_COMPONENTS_REMOVED = 0x200,

                /**
                 * \brief Common solvent components were removed (parent extraction only).
                 */
                SOLVENT_COMPONENTS_REMOVED = 0x400,

                /**
                 * \brief Duplicate disconnected components were collapsed (parent extraction only).
                 */
                DUPLICATE_COMPONENTS_REMOVED = 0x800
            };

            /**
             * \brief Constructs the \c %ChEMBLStandardizer instance.
             */
            ChEMBLStandardizer();

            /**
             * \brief Constructs a copy of the \c %ChEMBLStandardizer instance \a standardizer.
             * \param standardizer The \c %ChEMBLStandardizer to copy.
             */
            ChEMBLStandardizer(const ChEMBLStandardizer& standardizer);

            /**
             * \brief Standardizes \a mol in place.
             * \param mol The molecule to standardize (modified in place).
             * \param proc_excld If \c true, ChEMBL exclusion criteria are ignored and the molecule is processed regardless.
             * \return A bitwise-OR combination of ChangeFlags reporting which standardization steps modified the molecule.
             */
            ChangeFlags standardize(Molecule& mol, bool proc_excld = false);

            /**
             * \brief Writes a standardized copy of \a molgraph to \a std_mol.
             * \param molgraph The input molecular graph.
             * \param std_mol The output molecule receiving the standardized copy.
             * \param proc_excluded If \c true, ChEMBL exclusion criteria are ignored and the molecule is processed regardless.
             * \return A bitwise-OR combination of ChangeFlags reporting which standardization steps modified the molecule.
             */
            ChangeFlags standardize(const MolecularGraph& molgraph, Molecule& std_mol, bool proc_excluded = false);

            /**
             * \brief Extracts the parent compound of \a mol in place (removing salt/solvent components).
             * \param mol The molecule from which to extract the parent (modified in place).
             * \param neutralize If \c true, charges of the extracted parent are subsequently neutralized.
             * \param check_exclusion If \c true, ChEMBL exclusion criteria are checked before processing.
             * \return A bitwise-OR combination of ChangeFlags reporting which steps modified the molecule.
             */
            ChangeFlags getParent(Molecule& mol, bool neutralize = true, bool check_exclusion = true);

            /**
             * \brief Extracts the parent compound of \a molgraph into \a parent_mol.
             * \param molgraph The input molecular graph.
             * \param parent_mol The output molecule receiving the parent compound.
             * \param neutralize If \c true, charges of the extracted parent are subsequently neutralized.
             * \param check_exclusion If \c true, ChEMBL exclusion criteria are checked before processing.
             * \return A bitwise-OR combination of ChangeFlags reporting which steps modified the molecule.
             */
            ChangeFlags getParent(const MolecularGraph& molgraph, Molecule& parent_mol, bool neutralize = true, bool check_exclusion = true);

            /**
             * \brief Replaces the state of this standardizer by a copy of the state of \a standardizer.
             * \param standardizer The source \c %ChEMBLStandardizer.
             * \return A reference to itself.
             */
            ChEMBLStandardizer& operator=(const ChEMBLStandardizer& standardizer);

          private:
            typedef std::vector<Atom*> AtomList;

            void copyMolecularGraph(const MolecularGraph& molgraph, Molecule& mol_copy) const;

            bool checkExclusionCriterions(const Molecule& mol) const;
            bool checkExclusionCriterions(const MolecularGraph& molgraph, std::size_t& boron_cnt) const;

            bool standardizeUnknownStereochemistry(Molecule& mol) const;

            bool kekulizeBonds(Molecule& mol);

            bool removeExplicitHydrogens(Molecule& mol) const;
            bool isRemovableHydrogen(const Atom& atom) const;

            bool              normalizeStructure(Molecule& mol);
            const Chem::Atom* getAtomWithMappingID(const Molecule& ptn, std::size_t id) const;

            bool removeCharges(Molecule& mol);

            bool removeTartrateStereochemistry(Molecule& mol);

            bool   cleanup2DStructure(Molecule& mol);
            double calc2DBondAngle(const Molecule& mol, const Atom& ctr_atom, const Atom& nbr_atom1, const Atom& nbr_atom2);
            void   rotateSubstituent(const Molecule& mol, const Atom& ctr_atom, const Atom& subst_atom, double rot_ang);

            void clearMatchConstraints(Molecule& mol) const;

            typedef std::pair<std::uint64_t, std::uint64_t>                    StructureID;
            typedef std::pair<const Fragment*, StructureID>                    MoleculeComponent;
            typedef std::vector<MoleculeComponent>                             MoleculeComponentList;
            typedef std::unordered_set<StructureID, boost::hash<StructureID> > StructureIDSet;

            HashCodeCalculator           hashCodeCalc;
            KekuleStructureCalculator    kekuleStructureCalc;
            Util::STArray                kekulizedBondOrders;
            SubstructureSearch           substructSearch;
            ProtonationStateStandardizer chargeStandardizer;
            Math::Vector2DArray          atom2DCoords;
            Util::BitSet                 markedAtomSet;
            Fragment                     tmpFragment;
            BasicMolecule                tmpMolecule;
            MoleculeComponentList        molCompList1;
            MoleculeComponentList        molCompList2;
            StructureIDSet               uniqueMolComps;
        };
    } // namespace Chem
} // namespace CDPL

#endif // CDPL_CHEM_CHEMBLSTANDARDIZER_HPP
