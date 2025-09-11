/* 
 * MMFF94TorsionInteractionParameterizer.hpp 
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
 * \brief Definition of class CDPL::ForceField::MMFF94TorsionInteractionParameterizer.
 */

#ifndef CDPL_FORCEFIELD_MMFF94TORSIONINTERACTIONPARAMETERIZER_HPP
#define CDPL_FORCEFIELD_MMFF94TORSIONINTERACTIONPARAMETERIZER_HPP

#include <vector>
#include <memory>

#include "CDPL/ForceField/APIPrefix.hpp"
#include "CDPL/ForceField/MMFF94TorsionInteractionList.hpp"
#include "CDPL/ForceField/MMFF94PropertyFunctions.hpp"
#include "CDPL/ForceField/InteractionFilterFunctions.hpp"
#include "CDPL/ForceField/MMFF94TorsionParameterTable.hpp"
#include "CDPL/ForceField/MMFF94AtomTypePropertyTable.hpp"
#include "CDPL/ForceField/MMFF94PrimaryToParameterAtomTypeMap.hpp"


namespace CDPL
{

    namespace Chem
    {

        class MolecularGraph;
        class Atom;
        class Bond;
    } // namespace Chem

    namespace ForceField
    {

        class CDPL_FORCEFIELD_API MMFF94TorsionInteractionParameterizer
        {

          public:
            typedef std::shared_ptr<MMFF94TorsionInteractionParameterizer> SharedPointer;

            MMFF94TorsionInteractionParameterizer();

            MMFF94TorsionInteractionParameterizer(const Chem::MolecularGraph&   molgraph,
                                                  MMFF94TorsionInteractionList& ia_list,
                                                  bool                          strict);

            void setFilterFunction(const InteractionFilterFunction4& func);

            void setAtomTypeFunction(const MMFF94NumericAtomTypeFunction& func);

            void setBondTypeIndexFunction(const MMFF94BondTypeIndexFunction& func);

            void setAromaticRingSetFunction(const MMFF94RingSetFunction& func);

            void setTorsionParameterTable(const MMFF94TorsionParameterTable::SharedPointer& table);

            void setAtomTypePropertyTable(const MMFF94AtomTypePropertyTable::SharedPointer& table);

            void setParameterAtomTypeMap(const MMFF94PrimaryToParameterAtomTypeMap::SharedPointer& map);

            void parameterize(const Chem::MolecularGraph& molgraph, MMFF94TorsionInteractionList& ia_list, bool strict);

          private:
            typedef MMFF94AtomTypePropertyTable::Entry AtomTypePropEntry;
            typedef std::vector<const Chem::Atom*>     AtomList;
            typedef std::vector<const Chem::Bond*>     BondList;

            bool getParameters(const Chem::MolecularGraph& molgraph, const Chem::Atom& term_atom1, const Chem::Atom& ctr_atom1,
                               const Chem::Atom& ctr_atom2, const Chem::Atom& term_atom2, const Chem::Bond& ctr_bond,
                               unsigned int term_atom1_type, unsigned int ctr_atom1_type, unsigned int ctr_atom2_type,
                               unsigned int term_atom2_type, unsigned int tor_type_idx, const AtomTypePropEntry& ctr_atom1_prop_entry,
                               const AtomTypePropEntry& ctr_atom2_prop_entry, double& tor_param1, double& tor_param2,
                               double& tor_param3) const;

            unsigned int getTorsionTypeIndex(const Chem::MolecularGraph& molgraph, const Chem::Atom& term_atom1, const Chem::Atom& ctr_atom1,
                                             const Chem::Atom& ctr_atom2, const Chem::Atom& term_atom2, const Chem::Bond& ctr_bond,
                                             unsigned int term_atom1_type, unsigned int ctr_atom1_type, unsigned int ctr_atom2_type,
                                             unsigned int term_atom2_type, unsigned int term_bond1_type_idx, unsigned int ctr_bond_type_idx,
                                             unsigned int term_bond2_type_idx) const;

            bool isInSecondPTERow(unsigned int atomic_no) const;

            InteractionFilterFunction4                         filterFunc;
            MMFF94NumericAtomTypeFunction                      atomTypeFunc;
            MMFF94BondTypeIndexFunction                        bondTypeIdxFunc;
            MMFF94RingSetFunction                              aromRingSetFunc;
            MMFF94TorsionParameterTable::SharedPointer         paramTable;
            MMFF94AtomTypePropertyTable::SharedPointer         typePropTable;
            MMFF94PrimaryToParameterAtomTypeMap::SharedPointer paramTypeMap;
            AtomList                                           nbrAtoms1;
            AtomList                                           nbrAtoms2;
            BondList                                           nbrBonds1;
            BondList                                           nbrBonds2;
        };
    } // namespace ForceField
} // namespace CDPL

#endif // CDPL_FORCEFIELD_MMFF94TORSIONINTERACTIONPARAMETERIZER_HPP
