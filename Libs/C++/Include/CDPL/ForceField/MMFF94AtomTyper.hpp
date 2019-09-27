/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * MMFF94AtomTyper.hpp 
 *
 * This file is part of the Chemical Data Processing Toolkit
 *
 * Copyright (C) 2003-2010 Thomas A. Seidel <thomas.seidel@univie.ac.at>
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
 * \brief Definition of the class CDPL::ForceField::MMFF94AtomTyper.
 */

#ifndef CDPL_FORCEFIELD_MMFF94ATOMTYPER_HPP
#define CDPL_FORCEFIELD_MMFF94ATOMTYPER_HPP

#include <vector>
#include <string>
#include <cstddef>

#include <boost/shared_ptr.hpp>

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

		class MolecularGraph;
		class Fragment;
	}

    namespace ForceField 
    {

		/**
		 * \addtogroup CDPL_FORCEFIELD_ATOM_TYPE_PERCEPTION
		 * @{
		 */

		class CDPL_FORCEFIELD_API MMFF94AtomTyper
		{

		  public:
			typedef boost::shared_ptr<MMFF94AtomTyper> SharedPointer;

			MMFF94AtomTyper();

			MMFF94AtomTyper(const Chem::MolecularGraph& molgraph, Util::SArray& sym_types, Util::UIArray& num_types, bool strict = true);

			void setSymbolicAtomTypePatternTable(const MMFF94SymbolicAtomTypePatternTable::SharedPointer& table);

			void setAromaticAtomTypeDefinitionTable(const MMFF94AromaticAtomTypeDefinitionTable::SharedPointer& table);

			void setHeavyToHydrogenAtomTypeMap(const MMFF94HeavyToHydrogenAtomTypeMap::SharedPointer& map);

			void setSymbolicToNumericAtomTypeMap(const MMFF94SymbolicToNumericAtomTypeMap::SharedPointer& map);

			void setAtomTypePropertyTable(const MMFF94AtomTypePropertyTable::SharedPointer& table);

			void setAromaticRingSetFunction(const MMFF94AromaticRingSetFunction& func);
		
			void perceiveTypes(const Chem::MolecularGraph& molgraph, Util::SArray& sym_types, Util::UIArray& num_types, bool strict = true);

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
			MMFF94AromaticRingSetFunction                        aromRingSetFunc;
			const Chem::MolecularGraph*                          molGraph;
			Util::SArray*                                        symTypes;
			RingList                                             aromRings;
			Chem::PatternAtomTyper                               atomTyper;
		};
    
		/**
		 * @}
		 */
    }
}

#endif // CDPL_FORCEFIELD_MMFF94ATOMTYPER_HPP
