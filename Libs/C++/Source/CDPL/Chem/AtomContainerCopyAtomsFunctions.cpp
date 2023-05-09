/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * AtomContainerCopyAtomsFunctions.cpp 
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

#include "CDPL/Chem/AtomContainerFunctions.hpp"
#include "CDPL/Chem/Atom.hpp"
#include "CDPL/Chem/Fragment.hpp"
#include "CDPL/Chem/Molecule.hpp"


using namespace CDPL; 


void Chem::copyAtomsIf(const AtomContainer& cntnr, Molecule& mol, const AtomPredicate& pred, bool append)
{
	if (!append)
		mol.clear();

    for (AtomContainer::ConstAtomIterator it = cntnr.getAtomsBegin(), end = cntnr.getAtomsEnd(); it != end; ++it) {
		const Atom& atom = *it;

		if (pred(atom))
			mol.addAtom().copyProperties(atom);
    }
}

void Chem::copyAtomsIf(const AtomContainer& cntnr, Fragment& frag, const AtomPredicate& pred, bool append)
{
 	if (!append)
		frag.clear();

   for (AtomContainer::ConstAtomIterator it = cntnr.getAtomsBegin(), end = cntnr.getAtomsEnd(); it != end; ++it) {
		const Atom& atom = *it;

		if (pred(atom))
			frag.addAtom(atom);
    }  
}

void Chem::copyAtomsIfNot(const AtomContainer& cntnr, Molecule& mol, const AtomPredicate& pred, bool append)
{
 	if (!append)
		mol.clear();

	for (AtomContainer::ConstAtomIterator it = cntnr.getAtomsBegin(), end = cntnr.getAtomsEnd(); it != end; ++it) {
		const Atom& atom = *it;

		if (!pred(atom))
			mol.addAtom().copyProperties(atom);
    }
}

void Chem::copyAtomsIfNot(const AtomContainer& cntnr, Fragment& frag, const AtomPredicate& pred, bool append)
{
	if (!append)
		frag.clear();

    for (AtomContainer::ConstAtomIterator it = cntnr.getAtomsBegin(), end = cntnr.getAtomsEnd(); it != end; ++it) {
		const Atom& atom = *it;

		if (!pred(atom))
			frag.addAtom(atom);
    }  
}
