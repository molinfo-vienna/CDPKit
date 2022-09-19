/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * MolecularGraphSymmetryClassesFunction.cpp 
 *
 * This file is part of the Chemical Data Processing Toolkit
 *
 * Copyright (C) 2003-2020 Thomas A. Seidel <thomas.seidel@univie.ac.at>
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

#include <algorithm>
#include <functional>

#include <boost/bind.hpp>

#include "CDPL/Chem/MolecularGraphFunctions.hpp"
#include "CDPL/Chem/AtomFunctions.hpp"
#include "CDPL/Chem/Atom.hpp"
#include "CDPL/Chem/SymmetryClassCalculator.hpp"
#include "CDPL/Util/SequenceFunctions.hpp"


using namespace CDPL; 


void Chem::perceiveSymmetryClasses(MolecularGraph& molgraph, bool overwrite,
								   unsigned int atom_flags, unsigned int bond_flags, bool inc_impl_h)
{
	if (!overwrite && std::find_if(molgraph.getAtomsBegin(), molgraph.getAtomsEnd(),
								   boost::bind(std::equal_to<bool>(), false,
											   boost::bind(&hasSymmetryClass, _1))) == molgraph.getAtomsEnd())
		return;

	Util::STArray sym_classes;
	SymmetryClassCalculator calculator;

	if (atom_flags == AtomPropertyFlag::DEFAULT)
		atom_flags = SymmetryClassCalculator::DEF_ATOM_PROPERTY_FLAGS;

	if (bond_flags == BondPropertyFlag::DEFAULT)
		bond_flags = SymmetryClassCalculator::DEF_BOND_PROPERTY_FLAGS;

	calculator.setAtomPropertyFlags(atom_flags);
	calculator.setBondPropertyFlags(bond_flags);
	calculator.includeImplicitHydrogens(inc_impl_h);
	calculator.calculate(molgraph, sym_classes);

	Util::forEachPair(molgraph.getAtomsBegin(), molgraph.getAtomsEnd(), sym_classes.getElementsBegin(), &setSymmetryClass);
}
