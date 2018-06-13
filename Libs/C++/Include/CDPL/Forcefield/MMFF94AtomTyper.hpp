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
 * \brief Definition of the class CDPL::Forcefield::MMFF94AtomTyper.
 */

#ifndef CDPL_FORCEFIELD_MMFF94ATOMTYPER_HPP
#define CDPL_FORCEFIELD_MMFF94ATOMTYPER_HPP

#include <vector>
#include <string>
#include <cstddef>

#include "CDPL/Forcefield/APIPrefix.hpp"
#include "CDPL/Chem/PatternAtomTyper.hpp"
#include "CDPL/Util/Array.hpp"


namespace CDPL 
{

	namespace Chem
	{

		class MolecularGraph;
	}

    namespace Forcefield 
    {

		class MMFF94SymbolicAtomTypePatternTable;
		class MMFF94HeavyToHydrogenAtomTypeMap;
		class MMFF94SymbolicToNumericAtomTypeMap;

		/**
		 * \addtogroup CDPL_FORCEFIELD_ATOM_TYPE_PERCEPTION
		 * @{
		 */

		class CDPL_FORCEFIELD_API MMFF94AtomTyper
		{

		  public:
			MMFF94AtomTyper();

			void setSymbolicAtomTypePatternTable(const MMFF94SymbolicAtomTypePatternTable& table);

			void setHeavyToHydrogenAtomTypeMap(const MMFF94HeavyToHydrogenAtomTypeMap& map);

			void setSymbolicToNumericAtomTypeMap(const MMFF94SymbolicToNumericAtomTypeMap& map);

			void strictAtomTyping(bool strict);

			bool strictAtomTyping() const;

			void perceiveTypes(const Chem::MolecularGraph& molgraph);

			const std::string& getSymbolicType(std::size_t idx);

			unsigned int getNumericType(std::size_t idx);

		  private:
			void init(const Chem::MolecularGraph& molgraph);

			void perceiveInitialAtomTypes();
			void assignAromaticAtomTypes();
			void assignHydrogenAtomTypes();
			void assignNumericAtomTypes();

			typedef std::vector<std::string> SymbolicTypeTable;
			typedef std::vector<unsigned int> NumericTypeTable;

			bool                                         strictMode;
			const MMFF94SymbolicAtomTypePatternTable*    symTypePatternTable;
			const MMFF94HeavyToHydrogenAtomTypeMap*      hydTypeMap;
			const MMFF94SymbolicToNumericAtomTypeMap*    numTypeMap;
			const Chem::MolecularGraph*                  molGraph;
			Chem::PatternAtomTyper                       atomTyper;
			SymbolicTypeTable                            symTypes;
			NumericTypeTable                             numTypes;
		};
    
		/**
		 * @}
		 */
    }
}

#endif // CDPL_FORCEFIELD_MMFF94ATOMTYPER_HPP
