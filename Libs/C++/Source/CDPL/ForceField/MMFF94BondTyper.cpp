/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * MMFF94BondTyper.cpp 
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

 
#include "StaticInit.hpp"

#include <string>
#include <algorithm>

#include <boost/lexical_cast.hpp>
#include <boost/bind.hpp>

#include "CDPL/ForceField/MMFF94BondTyper.hpp"
#include "CDPL/ForceField/MolecularGraphFunctions.hpp"
#include "CDPL/ForceField/AtomFunctions.hpp"
#include "CDPL/Chem/FragmentList.hpp"
#include "CDPL/Chem/Fragment.hpp"
#include "CDPL/Chem/Bond.hpp"
#include "CDPL/Chem/BondFunctions.hpp"


using namespace CDPL; 


ForceField::MMFF94BondTyper::MMFF94BondTyper(const Chem::MolecularGraph& molgraph, Util::UIArray& types):
    aromRingSetFunc(&getMMFF94AromaticRings), atomTypeFunc(&getMMFF94NumericType) 
{
    setAtomTypePropertyTable(MMFF94AtomTypePropertyTable::get());

    perceiveTypes(molgraph, types);
}

ForceField::MMFF94BondTyper::MMFF94BondTyper(): 
    aromRingSetFunc(&getMMFF94AromaticRings), atomTypeFunc(&getMMFF94NumericType) 
{
    setAtomTypePropertyTable(MMFF94AtomTypePropertyTable::get());
}

void ForceField::MMFF94BondTyper::setAtomTypePropertyTable(const MMFF94AtomTypePropertyTable::SharedPointer& table)
{
    atomTypePropTable = table;
}

void ForceField::MMFF94BondTyper::setAromaticRingSetFunction(const MMFF94AromaticRingSetFunction& func)
{
    aromRingSetFunc = func;
}
	
void ForceField::MMFF94BondTyper::setNumericAtomTypeFunction(const MMFF94NumericAtomTypeFunction& func)
{
    atomTypeFunc = func;
}
		
void ForceField::MMFF94BondTyper::perceiveTypes(const Chem::MolecularGraph& molgraph, Util::UIArray& types)
{
    using namespace Chem;

	const FragmentList::SharedPointer& arom_rings = aromRingSetFunc(molgraph);
	std::size_t num_bonds = molgraph.getNumBonds();

	types.resize(num_bonds);

	for (std::size_t i = 0; i < num_bonds; i++) {
		const Bond& bond = molgraph.getBond(i);

		if (getOrder(bond) == 1) {
			const TypePropertyEntry& atom1_props = atomTypePropTable->getEntry(atomTypeFunc(bond.getBegin()));

			if (!atom1_props)
				throw Base::ItemNotFound("MMFF94BondTyper: could not find MMFF94 atom type properties for atom #" + 
										 boost::lexical_cast<std::string>(molgraph.getAtomIndex(bond.getBegin())));

			const TypePropertyEntry& atom2_props = atomTypePropTable->getEntry(atomTypeFunc(bond.getEnd()));

			if (!atom2_props)
				throw Base::ItemNotFound("MMFF94BondTyper: could not find MMFF94 atom type properties for atom #" + 
										 boost::lexical_cast<std::string>(molgraph.getAtomIndex(bond.getEnd())));

			if (!atom1_props.isAromaticAtomType() || !atom2_props.isAromaticAtomType()) {
				if (atom1_props.formsMultiOrSingleBonds() && atom2_props.formsMultiOrSingleBonds()) {
					types[i] = 1;
					continue;
				}

			} else {
				if (std::find_if(arom_rings->getElementsBegin(), arom_rings->getElementsEnd(), 
								 boost::bind(&Fragment::containsBond, _1, boost::ref(bond))) == arom_rings->getElementsEnd())  {
					types[i] = 1;
					continue;
				}
			}
		}

		types[i] = 0;
	}
}
