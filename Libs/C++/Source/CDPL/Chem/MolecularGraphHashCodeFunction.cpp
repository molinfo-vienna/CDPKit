/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * MolecularGraphHashCodeFunction.cpp 
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


#include "StaticInit.hpp"

#include "CDPL/Chem/MolecularGraphFunctions.hpp"
#include "CDPL/Chem/FragmentFunctions.hpp"
#include "CDPL/Chem/HashCodeCalculator.hpp"


using namespace CDPL; 


Base::uint64 Chem::calcHashCode(const MolecularGraph& molgraph, unsigned int atom_flags, unsigned int bond_flags, bool global_stereo, bool ord_h_deplete)
{
	HashCodeCalculator hash_calc;

	if (atom_flags == AtomPropertyFlag::DEFAULT)
		atom_flags = HashCodeCalculator::DEF_ATOM_PROPERTY_FLAGS;

	if (bond_flags == BondPropertyFlag::DEFAULT)
		bond_flags = HashCodeCalculator::DEF_BOND_PROPERTY_FLAGS;

	hash_calc.setAtomHashSeedFunction(HashCodeCalculator::DefAtomHashSeedFunctor(hash_calc, atom_flags));
	hash_calc.setBondHashSeedFunction(HashCodeCalculator::DefBondHashSeedFunctor(bond_flags));
	hash_calc.includeGlobalStereoFeatures(global_stereo);

	Base::uint64 hash_code;

	if (ord_h_deplete) {
		Fragment tmp(molgraph);

		makeOrdinaryHydrogenDeplete(tmp, AtomPropertyFlag::ISOTOPE | AtomPropertyFlag::H_COUNT |
									AtomPropertyFlag::FORMAL_CHARGE);

		hash_code = hash_calc.calculate(tmp);

	} else
		hash_code = hash_calc.calculate(molgraph);

	return hash_code;
}
