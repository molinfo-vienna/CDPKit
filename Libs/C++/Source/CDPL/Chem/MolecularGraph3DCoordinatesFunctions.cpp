/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * MolecularGraph3DCoordinatesFunctions.cpp 
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
#include <limits>
#include <vector>

#include "CDPL/Chem/Atom.hpp"
#include "CDPL/Chem/MolecularGraphFunctions.hpp"
#include "CDPL/Chem/AtomFunctions.hpp"
#include "CDPL/Chem/AtomType.hpp"
#include "CDPL/Chem/Entity3DContainerFunctions.hpp"
#include "CDPL/Chem/AtomContainerFunctions.hpp"
#include "CDPL/Chem/Hydrogen3DCoordinatesCalculator.hpp"
#include "CDPL/Chem/AtomConformer3DCoordinatesFunctor.hpp"
#include "CDPL/Math/VectorArray.hpp"


using namespace CDPL; 


namespace
{

	bool hasConformers(const Chem::Atom& atom)
	{
		return (get3DCoordinatesArray(atom)->getSize() > 0);
	}
}


void Chem::calcHydrogen3DCoordinates(MolecularGraph& molgraph, bool undef_only)
{
  	Math::Vector3DArray coords;
	Hydrogen3DCoordinatesCalculator calculator;

	calculator.undefinedOnly(undef_only);
	calculator.setup(molgraph);
	calculator.calculate(coords, true);

	set3DCoordinates(molgraph, coords);

	std::vector<std::size_t> undef_atoms;
	std::size_t num_confs = std::numeric_limits<std::size_t>::max();
	std::size_t i = 0;

	for (MolecularGraph::AtomIterator it = molgraph.getAtomsBegin(), end = molgraph.getAtomsEnd(); it != end; ++it, i++) {
		Atom& atom = *it;

		if (has3DCoordinatesArray(atom)) {
			if (!undef_only && getType(atom) == AtomType::H) {
				get3DCoordinatesArray(atom)->clear();
				undef_atoms.push_back(i);
				continue;
			}

			num_confs = std::min(num_confs, get3DCoordinatesArray(atom)->getSize());
			continue;

		} else if (getType(atom) != AtomType::H)
			return;

		set3DCoordinatesArray(atom, Math::Vector3DArray::SharedPointer(new Math::Vector3DArray()));
		undef_atoms.push_back(i);
	}

	if (num_confs == 0 || num_confs == std::numeric_limits<std::size_t>::max())
		return;

	calculator.setAtom3DCoordinatesCheckFunction(&hasConformers);
	calculator.setup(molgraph);

	for (i = 0; i < num_confs; i++) {
		calculator.setAtom3DCoordinatesFunction(AtomConformer3DCoordinatesFunctor(i));
		calculator.calculate(coords, true);

		for (std::vector<std::size_t>::const_iterator it = undef_atoms.begin(), end = undef_atoms.end(); it != end; ++it) {
			std::size_t atom_idx = *it;

			get3DCoordinatesArray(molgraph.getAtom(atom_idx))->addElement(coords[atom_idx]);
		}
	}
}
