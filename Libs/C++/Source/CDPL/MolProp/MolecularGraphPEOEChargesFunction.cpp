/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * MolecularGraphPEOEChargesFunction.cpp 
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

#include "CDPL/MolProp/MolecularGraphFunctions.hpp"
#include "CDPL/MolProp/PEOEChargeCalculator.hpp"
#include "CDPL/MolProp/AtomFunctions.hpp"
#include "CDPL/Chem/Atom.hpp"
#include "CDPL/Chem/MolecularGraph.hpp"


using namespace CDPL; 


void MolProp::calcPEOECharges(Chem::MolecularGraph& molgraph, bool overwrite, std::size_t num_iter, 
							  double damping)
{
	if (!overwrite) {
		Chem::MolecularGraph::ConstAtomIterator it = molgraph.getAtomsBegin(), end = molgraph.getAtomsEnd();
		
		for ( ; it != end; ++it) {
			const Chem::Atom& atom = *it;

			if (!hasPEOECharge(atom) || !hasPEOEElectronegativity(atom))
				break;
		}
		
		if (it == end)
			return;
	}

	Util::DArray charges;
	Util::DArray el_negs;
	PEOEChargeCalculator calculator;

	calculator.setNumIterations(num_iter);
	calculator.setDampingFactor(damping);
	calculator.calculate(molgraph, charges);
	calculator.getElectronegativities(el_negs);
	
	std::size_t num_atoms = molgraph.getNumAtoms();

	for (std::size_t i = 0; i < num_atoms; i++) {
		Chem::Atom& atom = molgraph.getAtom(i);
		
		setPEOECharge(atom, charges[i]);
		setPEOEElectronegativity(atom, el_negs[i]);
	}
}
