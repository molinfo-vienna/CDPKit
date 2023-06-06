/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * AtomFunctions.hpp 
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

#ifndef CDPL_INTERNAL_ATOMFUNCTIONS_HPP
#define CDPL_INTERNAL_ATOMFUNCTIONS_HPP

#include <cstddef>

#include "CDPL/Chem/AtomPropertyFlag.hpp"


namespace CDPL 
{

    namespace Chem 
    {
	
		class Atom;
		class MolecularGraph;
    }
    
    namespace Internal
    {
		
		inline double getVdWRadius(const Chem::Atom& atom);

		inline std::size_t getAtomCount(const Chem::Atom& atom, const Chem::MolecularGraph& molgraph, unsigned int type, bool strict = true);
		inline std::size_t getExplicitAtomCount(const Chem::Atom& atom, const Chem::MolecularGraph& molgraph, unsigned int type, bool strict = true);
		inline std::size_t getHeavyAtomCount(const Chem::Atom& atom, const Chem::MolecularGraph& molgraph);
		inline std::size_t getOrdinaryHydrogenCount(const Chem::Atom& atom, const Chem::MolecularGraph& molgraph, 
											 unsigned int flags = Chem::AtomPropertyFlag::DEFAULT);
		
		inline std::size_t getBondCount(const Chem::Atom& atom, const Chem::MolecularGraph& molgraph);
		inline std::size_t getBondCount(const Chem::Atom& atom, const Chem::MolecularGraph& molgraph, std::size_t order);
		inline std::size_t getBondCount(const Chem::Atom& atom, const Chem::MolecularGraph& molgraph, std::size_t order, unsigned int type, bool strict = true);
		inline std::size_t getExplicitBondCount(const Chem::Atom& atom, const Chem::MolecularGraph& molgraph, std::size_t order);
		inline std::size_t getExplicitBondCount(const Chem::Atom& atom, const Chem::MolecularGraph& molgraph);
		inline std::size_t getExplicitBondCount(const Chem::Atom& atom, const Chem::MolecularGraph& molgraph, std::size_t order, unsigned int type, bool strict = true);
		inline std::size_t getHeavyBondCount(const Chem::Atom& atom, const Chem::MolecularGraph& molgraph);
		inline std::size_t getRingBondCount(const Chem::Atom& atom, const Chem::MolecularGraph& molgraph);
		
		inline std::size_t calcExplicitValence(const Chem::Atom& atom, const Chem::MolecularGraph& molgraph);
		inline std::size_t calcValence(const Chem::Atom& atom, const Chem::MolecularGraph& molgraph);
		inline std::size_t calcValenceElectronCount(const Chem::Atom& atom);
		inline std::size_t calcFreeValenceElectronCount(const Chem::Atom& atom, const Chem::MolecularGraph& molgraph);
		
		inline bool isUnsaturated(const Chem::Atom& atom, const Chem::MolecularGraph& molgraph);
		inline bool isOrdinaryHydrogen(const Chem::Atom& atom, const Chem::MolecularGraph& molgraph, 
									   unsigned int flags = Chem::AtomPropertyFlag::DEFAULT);
		inline bool isAmideNitrogen(const Chem::Atom& atom, const Chem::MolecularGraph& molgraph, bool c_only = false, bool db_o_only = false);
		inline bool isInvertibleNitrogen(const Chem::Atom& atom, const Chem::MolecularGraph& molgraph);
		inline bool isPlanarNitrogen(const Chem::Atom& atom, const Chem::MolecularGraph& molgraph);
		inline bool isCarbonylLikeAtom(const Chem::Atom& atom, const Chem::MolecularGraph& molgraph, bool c_only, bool db_o_only);
		
		inline std::size_t getNumContainingSSSRRings(const Chem::Atom& atom, const Chem::MolecularGraph& molgraph);
    }
}

#include "AtomFunctionsImpl.hpp"

#endif // CDPL_INTERNAL_ATOMFUNCTIONS_HPP
