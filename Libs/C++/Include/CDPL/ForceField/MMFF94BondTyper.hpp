/* 
 * MMFF94BondTyper.hpp 
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
 * \brief Definition of class CDPL::ForceField::MMFF94BondTyper.
 */

#ifndef CDPL_FORCEFIELD_MMFF94BONDTYPER_HPP
#define CDPL_FORCEFIELD_MMFF94BONDTYPER_HPP

#include "CDPL/ForceField/APIPrefix.hpp"
#include "CDPL/ForceField/MMFF94AtomTypePropertyTable.hpp"
#include "CDPL/ForceField/MMFF94PropertyFunctions.hpp"
#include "CDPL/Util/Array.hpp"


namespace CDPL
{

    namespace Chem
    {

        class MolecularGraph;
    }

    namespace ForceField
    {

        class CDPL_FORCEFIELD_API MMFF94BondTyper
        {

          public:
            MMFF94BondTyper();

            MMFF94BondTyper(const Chem::MolecularGraph& molgraph, Util::UIArray& types, bool strict);

            void setAtomTypePropertyTable(const MMFF94AtomTypePropertyTable::SharedPointer& table);

            void setAromaticRingSetFunction(const MMFF94RingSetFunction& func);

            void setAtomTypeFunction(const MMFF94NumericAtomTypeFunction& func);

            /**
             * \brief Determines MMFF94 bond type indicies for the bonds of a molecular graph.
             *
             * Specifically, an nonstandard bond type index of \e "1" is assigned
             * whenever a single bond (formal bond order 1) is found a) between
             * non-aromatic atoms \e i and \e j of types \e I and \e J for which \e "sbmb" entries in
             * of \e "1" appear in the "MMFFPROP.PAR" file or b) between aromatic atoms
             * belonging to different aromatic rings (as in the case of the central
             * C-C bond in biphenyl).
             * 
             * \param molgraph The molecular graph for which to assign bond type indices
             * \param types The output array storing the determined bond type indices.
             * \param strict If \c true, strict parameterization will be peformed that might fail.
             */
            void perceiveTypes(const Chem::MolecularGraph& molgraph, Util::UIArray& types, bool strict);

          private:
            typedef MMFF94AtomTypePropertyTable::Entry TypePropertyEntry;

            MMFF94AtomTypePropertyTable::SharedPointer atomTypePropTable;
            MMFF94RingSetFunction                      aromRingSetFunc;
            MMFF94NumericAtomTypeFunction              atomTypeFunc;
        };
    } // namespace ForceField
} // namespace CDPL

#endif // CDPL_FORCEFIELD_MMFF94BONDTYPER_HPP
