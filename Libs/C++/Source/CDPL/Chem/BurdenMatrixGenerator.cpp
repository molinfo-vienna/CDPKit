/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * BurdenMatrixGenerator.cpp 
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

#include "CDPL/Chem/BurdenMatrixGenerator.hpp"
#include "CDPL/Chem/Atom.hpp"
#include "CDPL/Chem/Bond.hpp"
#include "CDPL/Chem/AtomFunctions.hpp"
#include "CDPL/Chem/BondFunctions.hpp"


using namespace CDPL;


Chem::BurdenMatrixGenerator::BurdenMatrixGenerator(): 
	atomWeightFunc(&getType) {}

Chem::BurdenMatrixGenerator::BurdenMatrixGenerator(const MolecularGraph& molgraph, Math::DMatrix& mtx): 
	atomWeightFunc(&getType)
{
	generate(molgraph, mtx);
}

void Chem::BurdenMatrixGenerator::generate(const MolecularGraph& molgraph, Math::DMatrix& mtx)
{
	std::size_t num_atoms = molgraph.getNumAtoms();

	mtx = Math::ScalarMatrix<double>(num_atoms, num_atoms, 0.001);

	MolecularGraph::ConstAtomIterator atoms_end = molgraph.getAtomsEnd();

	for (MolecularGraph::ConstAtomIterator it = molgraph.getAtomsBegin(); it != atoms_end; ++it) {
		const Atom& atom = *it;
		std::size_t atom_idx = molgraph.getAtomIndex(atom);

		mtx(atom_idx, atom_idx) = atomWeightFunc(atom);
	}

	MolecularGraph::ConstBondIterator bonds_end = molgraph.getBondsEnd();

	for (MolecularGraph::ConstBondIterator it = molgraph.getBondsBegin(); it != bonds_end; ++it) {
		const Bond& bond = *it;
		const Atom* atoms[2];

		atoms[0] = &bond.getBegin();

		if (!molgraph.containsAtom(*atoms[0]))
			continue;

		atoms[1] = &bond.getEnd();

		if (!molgraph.containsAtom(*atoms[1]))
			continue;

		std::size_t atom_idx1 = molgraph.getAtomIndex(*atoms[0]);
		std::size_t atom_idx2 = molgraph.getAtomIndex(*atoms[1]);

		double bond_val;

		if (getAromaticityFlag(bond)) 
			bond_val = 0.15;

		else
			switch (getOrder(bond)) {

				case 1:
					bond_val = 0.1;
					break;

				case 2:
					bond_val = 0.2;
					break;

				case 3:
					bond_val = 0.3;
					break;
					
				default:
					continue;
			}
		
		for (std::size_t i = 0; i < 2; i++) {
			if (getExplicitBondCount(*atoms[i], molgraph) == 1) {
				bond_val += 0.01;
				break;
			}
		}

		mtx(atom_idx2, atom_idx1) = bond_val;
		mtx(atom_idx1, atom_idx2) = bond_val;
	}
}

void Chem::BurdenMatrixGenerator::setAtomWeightFunction(const AtomWeightFunction& func)
{
	atomWeightFunc = func;
}
