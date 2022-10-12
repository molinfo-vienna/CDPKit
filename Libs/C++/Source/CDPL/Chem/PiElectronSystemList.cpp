/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * PiElectronSystemList.cpp 
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

#include <iterator>

#include "CDPL/Chem/PiElectronSystemList.hpp"
#include "CDPL/Chem/Atom.hpp"
#include "CDPL/Chem/Bond.hpp"
#include "CDPL/Chem/AtomFunctions.hpp"
#include "CDPL/Chem/BondFunctions.hpp"
#include "CDPL/Chem/AtomDictionary.hpp"


using namespace CDPL;


Chem::PiElectronSystemList::PiElectronSystemList() {}

Chem::PiElectronSystemList::PiElectronSystemList(const MolecularGraph& molgraph)
{
    perceive(molgraph);
}

void Chem::PiElectronSystemList::perceive(const MolecularGraph& molgraph)
{
    clear();
	
	initStartElecSystems(molgraph);
	mergeElecSystems(molgraph);

	insertElements(0, workingElecSystems.begin(), workingElecSystems.end());
}

void Chem::PiElectronSystemList::initStartElecSystems(const MolecularGraph& molgraph)
{
	workingElecSystems.clear();

	for (MolecularGraph::ConstAtomIterator it = molgraph.getAtomsBegin(), end = molgraph.getAtomsEnd(); it != end; ++it) {
		const Atom& atom = *it;
		unsigned int type = getType(atom);
		std::size_t iupac_grp = AtomDictionary::getIUPACGroup(type);

		if (iupac_grp < 13 || iupac_grp > 17)
			continue;

		std::size_t num_bonds = getImplicitHydrogenCount(atom);
		Atom::ConstBondIterator nb_it = atom.getBondsBegin();

		for (Atom::ConstAtomIterator na_it = atom.getAtomsBegin(), na_end = atom.getAtomsEnd(); na_it != na_end; ++na_it, ++nb_it) {
			const Bond& bond = *nb_it;

			if (!molgraph.containsBond(bond))
				continue;

			if (!molgraph.containsAtom(*na_it))
				continue;

			num_bonds++;
		}

		long form_chg = getFormalCharge(atom);
	}
}

void Chem::PiElectronSystemList::mergeElecSystems(const MolecularGraph& molgraph)
{
}
