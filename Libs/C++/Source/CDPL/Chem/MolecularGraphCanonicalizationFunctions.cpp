/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * MolecularGraphCanonicalizationFunctions.cpp 
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
#include "CDPL/Chem/Bond.hpp"


using namespace CDPL; 


namespace
{

	struct BondCompareFunc
	{

		BondCompareFunc(const Chem::AtomCompareFunction& atom_cmp_func): atomCmpFunc(atom_cmp_func) {}

		bool operator()(const Chem::Bond& bond1, const Chem::Bond& bond2) const {
			const Chem::Atom* atoms[2][2] = { { &bond1.getBegin(), &bond1.getEnd() }, { &bond2.getBegin(), &bond2.getEnd() } };

			if (atomCmpFunc(*atoms[0][1], *atoms[0][0]))
				std::swap(atoms[0][0], atoms[0][1]);

			if (atomCmpFunc(*atoms[1][1], *atoms[1][0]))
				std::swap(atoms[1][0], atoms[1][1]);

			if (atomCmpFunc(*atoms[0][0], *atoms[1][0]))
				return true;

			if (atomCmpFunc(*atoms[1][0], *atoms[0][0]))
				return false;

			return atomCmpFunc(*atoms[0][1], *atoms[1][1]);
		}

		const Chem::AtomCompareFunction& atomCmpFunc;
	};
}


void Chem::canonicalize(MolecularGraph& molgraph, const AtomCompareFunction& func, bool atoms, bool atom_nbrs, 
						bool bonds, bool bond_atoms)
{
	if (atoms)
		molgraph.orderAtoms(func);

	if (bonds)
		molgraph.orderBonds(BondCompareFunc(func));

	if (atom_nbrs)
		std::for_each(molgraph.getAtomsBegin(), molgraph.getAtomsEnd(), boost::bind(&Atom::orderAtoms, _1, boost::ref(func)));

	if (bond_atoms)
		std::for_each(molgraph.getBondsBegin(), molgraph.getBondsEnd(), boost::bind(&Bond::orderAtoms, _1, boost::ref(func)));
}

void Chem::canonicalize(MolecularGraph& molgraph, bool atoms, bool atom_nbrs, bool bonds, bool bond_atoms)
{
	canonicalize(molgraph, boost::bind(std::less<std::size_t>(), boost::bind(&getCanonicalNumber, _1), boost::bind(&getCanonicalNumber, _2)),
				 atoms, atom_nbrs, bonds, bond_atoms);
}
