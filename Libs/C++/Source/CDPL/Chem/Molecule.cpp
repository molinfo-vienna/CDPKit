/* 
 * Molecule.cpp 
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

#include "CDPL/Chem/Molecule.hpp"
#include "CDPL/Chem/Atom.hpp"
#include "CDPL/Chem/Bond.hpp"
#include "CDPL/Base/Exceptions.hpp"


using namespace CDPL;


Chem::Molecule::AtomIterator Chem::Molecule::removeAtom(const AtomIterator& it)
{
	if (it.getIndex() >= getNumAtoms())
		throw Base::RangeError("Molecule: atom iterator out of valid range");

	removeAtom(it.getIndex());

	return it;
}

Chem::Molecule::BondIterator Chem::Molecule::removeBond(const BondIterator& it)
{
	if (it.getIndex() >= getNumBonds())
		throw Base::RangeError("Molecule: bond iterator out of valid range");

	removeBond(it.getIndex());

	return it;
}

Chem::Molecule& Chem::Molecule::operator=(const Molecule& mol) 
{
	if (this == &mol)
		return *this;

	copy(mol);

	return *this;
}

Chem::Molecule& Chem::Molecule::operator+=(const Molecule& mol) 
{
	append(mol);

	return *this;
}

Chem::Molecule& Chem::Molecule::operator=(const MolecularGraph& molgraph)
{   
	if (this == &molgraph)
		return *this;

	copy(molgraph);

	return *this;
}

Chem::Molecule& Chem::Molecule::operator+=(const MolecularGraph& molgraph)
{   
	append(molgraph);

	return *this;
}

Chem::Molecule& Chem::Molecule::operator-=(const MolecularGraph& molgraph)
{
	remove(molgraph);

	return *this;
}
