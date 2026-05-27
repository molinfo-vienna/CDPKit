/* 
 * MMFF94AtomTyper.hpp 
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
 * \brief Definition of class CDPL::ForceField::MMFF94AtomTyper.
 */

#ifndef CDPL_FORCEFIELD_MMFF94ATOMTYPER_HPP
#define CDPL_FORCEFIELD_MMFF94ATOMTYPER_HPP

#include <vector>
#include <string>
#include <cstddef>
#include <memory>

#include "CDPL/ForceField/APIPrefix.hpp"
#include "CDPL/ForceField/MMFF94SymbolicAtomTypePatternTable.hpp"
#include "CDPL/ForceField/MMFF94AromaticAtomTypeDefinitionTable.hpp"
#include "CDPL/ForceField/MMFF94HeavyToHydrogenAtomTypeMap.hpp"
#include "CDPL/ForceField/MMFF94SymbolicToNumericAtomTypeMap.hpp"
#include "CDPL/ForceField/MMFF94AtomTypePropertyTable.hpp"
#include "CDPL/ForceField/MMFF94PropertyFunctions.hpp"
#include "CDPL/Chem/PatternAtomTyper.hpp"
#include "CDPL/Util/Array.hpp"


namespace CDPL
{

    namespace Chem
    {

        class Fragment;
    }

    namespace ForceField
    {

        /**
         * \brief Assigns MMFF94 symbolic and numeric atom types to the atoms of a molecular graph.
         *
         * Typing is performed in four stages: provisional symbolic types are assigned by SMARTS pattern matching,
         * aromatic atom types are then reassigned according to the MMFF94 aromatic-ring rules, hydrogen atoms
         * receive types derived from their heavy-atom neighbors, and finally the symbolic types are translated
         * to the corresponding numeric type indices used by the rest of the MMFF94 parameter tables.
         */
        class CDPL_FORCEFIELD_API MMFF94AtomTyper
        {

          public:
            /** \brief A reference-counted smart pointer [\ref SHPTR] for dynamically allocated \c %MMFF94AtomTyper instances. */
            typedef std::shared_ptr<MMFF94AtomTyper> SharedPointer;

            /**
             * \brief Constructs an empty \c %MMFF94AtomTyper instance using the default MMFF94 parameter tables.
             */
            MMFF94AtomTyper();

            /**
             * \brief Constructs an \c %MMFF94AtomTyper instance and immediately perceives the atom types of \a molgraph.
             * \param molgraph The molecular graph to be typed.
             * \param sym_types Output array receiving the perceived MMFF94 symbolic atom type strings.
             * \param num_types Output array receiving the perceived MMFF94 numeric atom type indices.
             * \param strict If \c true, atoms for which no MMFF94 type could be perceived cause an error to be reported.
             *               Otherwise, perception never fails and problematic atoms get assigned a suitable fallback type.
             */
            MMFF94AtomTyper(const Chem::MolecularGraph& molgraph, Util::SArray& sym_types, Util::UIArray& num_types, bool strict);

            /**
             * \brief Sets the SMARTS-pattern table used for provisional symbolic atom type assignment.
             * \param table The new symbolic atom type pattern table.
             */
            void setSymbolicAtomTypePatternTable(const MMFF94SymbolicAtomTypePatternTable::SharedPointer& table);

            /**
             * \brief Sets the table used for the reassignment of aromatic atom types.
             * \param table The new aromatic atom type definition table.
             */
            void setAromaticAtomTypeDefinitionTable(const MMFF94AromaticAtomTypeDefinitionTable::SharedPointer& table);

            /**
             * \brief Sets the map used to derive hydrogen atom types from heavy-atom neighbor types.
             * \param map The new heavy-to-hydrogen atom type map.
             */
            void setHeavyToHydrogenAtomTypeMap(const MMFF94HeavyToHydrogenAtomTypeMap::SharedPointer& map);

            /**
             * \brief Sets the map used to translate symbolic into numeric atom types.
             * \param map The new symbolic-to-numeric atom type map.
             */
            void setSymbolicToNumericAtomTypeMap(const MMFF94SymbolicToNumericAtomTypeMap::SharedPointer& map);

            /**
             * \brief Sets the table providing the per-numeric-type atom property data.
             * \param table The new atom type property table.
             */
            void setAtomTypePropertyTable(const MMFF94AtomTypePropertyTable::SharedPointer& table);

            /**
             * \brief Sets the function used to obtain the set of MMFF94 aromatic rings for the input molecular graph.
             * \param func The new aromatic ring set retrieval function.
             */
            void setAromaticRingSetFunction(const MMFF94RingSetFunction& func);

            /**
             * \brief Perceives the MMFF94 atom types of \a molgraph and writes them to \a sym_types and \a num_types.
             * \param molgraph The molecular graph to be typed.
             * \param sym_types Output array receiving the perceived MMFF94 symbolic atom type strings.
             * \param num_types Output array receiving the perceived MMFF94 numeric atom type indices.
             * \param strict If \c true, atoms for which no MMFF94 type could be perceived cause an error to be reported.
             *               Otherwise, perception never fails and problematic atoms get assigned a suitable fallback type.
             */
            void perceiveTypes(const Chem::MolecularGraph& molgraph, Util::SArray& sym_types, Util::UIArray& num_types, bool strict);

          private:
            typedef MMFF94AromaticAtomTypeDefinitionTable::Entry AromTypeDefEntry;

            void init(const Chem::MolecularGraph& molgraph, Util::SArray& sym_types, Util::UIArray& num_types);

            void assignProvisionalSymbolicAtomTypes(bool strict);
            void assignAromaticAtomTypes();
            void assignHydrogenAtomTypes();
            void assignNumericAtomTypes(Util::UIArray& num_types);

            void assignAromaticAtomTypes(const Chem::Fragment* ring);

            std::size_t getUniqueHeteroAtomIndex(const Chem::Fragment& ring) const;
            std::size_t calcHeteroAtomDistance(std::size_t r_size, std::size_t het_atom_idx, std::size_t from_atom_idx) const;

            bool isN5Anion(const Chem::Fragment& ring) const;
            bool isImidazoliumCation(const Chem::Fragment& ring) const;

            bool matchesAromTypeDefEntry(bool wc_match, const std::string& sym_type, unsigned int atomic_no,
                                         std::size_t r_size, std::size_t het_dist, bool im_cat, bool n5_anion,
                                         const AromTypeDefEntry& entry) const;

            typedef std::vector<const Chem::Fragment*> RingList;

            MMFF94SymbolicAtomTypePatternTable::SharedPointer    symTypePatternTable;
            MMFF94AromaticAtomTypeDefinitionTable::SharedPointer aromTypeDefTable;
            MMFF94HeavyToHydrogenAtomTypeMap::SharedPointer      hydTypeMap;
            MMFF94SymbolicToNumericAtomTypeMap::SharedPointer    numTypeMap;
            MMFF94AtomTypePropertyTable::SharedPointer           atomTypePropTable;
            MMFF94RingSetFunction                                aromRingSetFunc;
            const Chem::MolecularGraph*                          molGraph;
            Util::SArray*                                        symTypes;
            RingList                                             aromRings;
            Chem::PatternAtomTyper                               atomTyper;
        };
    } // namespace ForceField
} // namespace CDPL

#endif // CDPL_FORCEFIELD_MMFF94ATOMTYPER_HPP
