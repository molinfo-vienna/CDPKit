/* 
 * MMFF94StretchBendInteractionParameterizer.hpp 
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
 * \brief Definition of class CDPL::ForceField::MMFF94StretchBendInteractionParameterizer.
 */

#ifndef CDPL_FORCEFIELD_MMFF94STRETCHBENDINTERACTIONPARAMETERIZER_HPP
#define CDPL_FORCEFIELD_MMFF94STRETCHBENDINTERACTIONPARAMETERIZER_HPP

#include <utility>
#include <cstddef>
#include <unordered_map>
#include <memory>

#include <boost/functional/hash.hpp>

#include "CDPL/ForceField/APIPrefix.hpp"
#include "CDPL/ForceField/MMFF94StretchBendInteractionList.hpp"
#include "CDPL/ForceField/MMFF94BondStretchingInteractionList.hpp"
#include "CDPL/ForceField/MMFF94AngleBendingInteractionList.hpp"
#include "CDPL/ForceField/MMFF94PropertyFunctions.hpp"
#include "CDPL/ForceField/InteractionFilterFunctions.hpp"
#include "CDPL/ForceField/MMFF94StretchBendParameterTable.hpp"
#include "CDPL/ForceField/MMFF94DefaultStretchBendParameterTable.hpp"
#include "CDPL/ForceField/MMFF94AtomTypePropertyTable.hpp"


namespace CDPL
{

    namespace Chem
    {

        class MolecularGraph;
        class Atom;
    } // namespace Chem

    namespace ForceField
    {

        /**
         * \brief Detects and parameterizes the MMFF94 stretch-bend interactions of a molecular graph.
         *
         * Stretch-bend interactions couple the bending of an \e i-\e j-\e k bond angle to the stretching of the
         * two participating bonds \e i-\e j and \e j-\e k. For every non-filtered atom triplet the parameterizer
         * derives the stretch-bend type index from the bond type indices and angle type index of the
         * already-parameterized bond-stretching and angle-bending interactions, looks up the matching
         * stretch-bend force constants (falling back to the periodic-table-row-based default parameter table
         * when no exact entry is available) and appends an MMFF94StretchBendInteraction instance to the output list.
         *
         * \see [\ref MMFF94]
         */
        class CDPL_FORCEFIELD_API MMFF94StretchBendInteractionParameterizer
        {

          public:
            /**
             * \brief A reference-counted smart pointer [\ref SHPTR] for dynamically allocated \c %MMFF94StretchBendInteractionParameterizer instances.
             */
            typedef std::shared_ptr<MMFF94StretchBendInteractionParameterizer> SharedPointer;

            /**
             * \brief Constructs an \c %MMFF94StretchBendInteractionParameterizer instance using the default MMFF94 parameter tables.
             */
            MMFF94StretchBendInteractionParameterizer();

            /**
             * \brief Constructs the parameterizer and processes the molecular graph \a molgraph.
             * \param molgraph The molecular graph for which to parameterize the stretch-bend interactions.
             * \param bs_ia_list The list of already-parameterized MMFF94 bond-stretching interactions (provides per-bond type indices and reference lengths).
             * \param ab_ia_list The list of already-parameterized MMFF94 angle-bending interactions (provides per-angle type indices and reference angles).
             * \param ia_list Output list receiving the generated MMFF94StretchBendInteraction instances.
             * \param strict If \c true, missing/ambiguous parameters cause a parameterization failure.
             *               Otherwise, in case of parameterization problems, suitable fallback parameters will be used.
             */
            MMFF94StretchBendInteractionParameterizer(const Chem::MolecularGraph& molgraph, const MMFF94BondStretchingInteractionList& bs_ia_list,
                                                      const MMFF94AngleBendingInteractionList& ab_ia_list, MMFF94StretchBendInteractionList& ia_list,
                                                      bool strict);

            /**
             * \brief Sets the filter function used to skip atom triplets during parameterization.
             * \param func The new three-atom filter function (when it returns \c false, the triplet is skipped).
             */
            void setFilterFunction(const InteractionFilterFunction3& func);

            /**
             * \brief Sets the function used to look up the MMFF94 numeric atom type of an atom.
             * \param func The new numeric atom type lookup function.
             */
            void setAtomTypeFunction(const MMFF94NumericAtomTypeFunction& func);

            /**
             * \brief Sets the primary table providing stretch-bend type-specific stretch-bend parameters.
             * \param table The new stretch-bend parameter table.
             */
            void setStretchBendParameterTable(const MMFF94StretchBendParameterTable::SharedPointer& table);

            /**
             * \brief Sets the fallback table providing periodic-table-row-based default stretch-bend parameters.
             * \param table The new default stretch-bend parameter table.
             */
            void setDefaultStretchBendParameterTable(const MMFF94DefaultStretchBendParameterTable::SharedPointer& table);

            /**
             * \brief Sets the table providing MMFF94 numeric atom type property data (used to look up the periodic table row of an atom for the default-parameter fallback).
             * \param table The new atom type property table.
             */
            void setAtomTypePropertyTable(const MMFF94AtomTypePropertyTable::SharedPointer& table);

            /**
             * \brief Perceives the MMFF94 stretch-bend interactions for \a molgraph and outputs the
             *        corresponding parameter data into \a ia_list.
             * \param molgraph The molecular graph for which to parameterize the stretch-bend interactions.
             * \param bs_ia_list The list of already-parameterized MMFF94 bond-stretching interactions (provides per-bond type indices and reference lengths).
             * \param ab_ia_list The list of already-parameterized MMFF94 angle-bending interactions (provides per-angle type indices and reference angles).
             * \param ia_list Output list receiving the generated MMFF94StretchBendInteraction instances.
             * \param strict If \c true, missing/ambiguous parameters cause a parameterization failure.
             *               Otherwise, in case of parameterization problems, suitable fallback parameters will be used.
             */
            void parameterize(const Chem::MolecularGraph& molgraph, const MMFF94BondStretchingInteractionList& bs_ia_list,
                              const MMFF94AngleBendingInteractionList& ab_ia_list, MMFF94StretchBendInteractionList& ia_list, bool strict);

          private:
            void initBondStretchingParamLookupTable(const MMFF94BondStretchingInteractionList& bs_ia_list);

            void getBondStretchingParameters(std::size_t atom1_idx, std::size_t atom2_idx, unsigned int& bond_type_idx, double& ref_length) const;

            void getStretchBendParameters(const Chem::MolecularGraph& molgraph, const Chem::Atom& term_atom1, unsigned int term_atom1_type, const Chem::Atom& ctr_atom, unsigned int ctr_atom_type,
                                          const Chem::Atom& term_atom2, unsigned int term_atom2_type, unsigned int bond_type_idx1, unsigned int bond_type_idx2,
                                          unsigned int angle_type_idx, unsigned int& sb_type_idx, double& ijk_force_const, double& kji_force_const) const;

            void getStretchBendParameters(const Chem::MolecularGraph& molgraph, const Chem::Atom& term_atom1, const Chem::Atom& ctr_atom,
                                          const Chem::Atom& term_atom2, unsigned int bond_type_idx1, unsigned int bond_type_idx2,
                                          unsigned int angle_type_idx, unsigned int& sb_type_idx, double& ijk_force_const, double& kji_force_const, bool strict) const;

            /**
             * \brief Returns the stretch bend type index SBT[IJK].
             *
             * SBT[IJK] is derived from the bond type indices BT[IJ] and BT[JK] and the angle type index AT[IJK] as follows:
             * 
             * SBT[IJK] AT[IJK] BT[IJ] BT[JK]
             * -------------------------------------------------------------
             * 0        0       0      0
             * 1        1       1      0
             * 2        1       0      1
             * 3        2       1      1
             * 4        4       0      0
             * 5        3       0      0
             * 6        5       1      0
             * 7        5       0      1
             * 8        6       1      1
             * 9        7       1      0
             * 10       7       0      1
             * 11       8       1      1
             * 
             * If \a symmetric is \c true, then the lower SBT[IJK] value for a given AT[IJK] is returned when there are two possibilities.
             *
             * \param symmetric Tells whether the terminal atom types are identical.
             * \param bond_type_idx1 The bond type index of the bond IJ.
             * \param bond_type_idx2 The bond type index of the bond JK.
             * \param angle_type_idx The angle type index.
             * \return The stretch bend type index.
             */
            unsigned int getStretchBendTypeIndex(bool symmetric, unsigned int bond_type_idx1, unsigned int bond_type_idx2, unsigned int angle_type_idx) const;

            unsigned int getPTERow(const Chem::MolecularGraph& molgraph, const Chem::Atom& atom, unsigned int atom_type) const;

            typedef std::unordered_map<std::pair<std::size_t, std::size_t>, const MMFF94BondStretchingInteraction*, boost::hash<std::pair<std::size_t, std::size_t> > > BondStretchingParamLookupTable;

            InteractionFilterFunction3                            filterFunc;
            MMFF94NumericAtomTypeFunction                         atomTypeFunc;
            MMFF94StretchBendParameterTable::SharedPointer        paramTable;
            MMFF94DefaultStretchBendParameterTable::SharedPointer defParamTable;
            MMFF94AtomTypePropertyTable::SharedPointer            typePropTable;
            BondStretchingParamLookupTable                        bsParamTable;
        };
    } // namespace ForceField
} // namespace CDPL

#endif // CDPL_FORCEFIELD_MMFF94STRETCHBENDINTERACTIONPARAMETERIZER_HPP
