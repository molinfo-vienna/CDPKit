/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * AtomContainerGeometricalDistanceMatrixFunction.cpp 
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

#include "CDPL/Chem/AtomContainerFunctions.hpp"
#include "CDPL/Chem/AtomFunctions.hpp"
#include "CDPL/Chem/AtomContainer.hpp"
#include "CDPL/Chem/Atom.hpp"


using namespace CDPL; 


void Chem::calcGeometricalDistanceMatrix(const AtomContainer& cntnr, Math::DMatrix& mtx)
{
	std::size_t num_atoms = cntnr.getNumAtoms();

	mtx.resize(num_atoms, num_atoms, false);
	mtx.clear();

	AtomContainer::ConstAtomIterator atoms_end = cntnr.getAtomsEnd();

	for (AtomContainer::ConstAtomIterator it1 = cntnr.getAtomsBegin(); it1 != atoms_end; ) {
		const Atom& atom1 = *it1;
		std::size_t atom1_idx = cntnr.getAtomIndex(atom1);
		const Math::Vector3D& coords1 = get3DCoordinates(atom1);

		for (AtomContainer::ConstAtomIterator it2 = ++it1; it2 != atoms_end; ++it2) {
			const Atom& atom2 = *it2;
			std::size_t atom2_idx = cntnr.getAtomIndex(atom2);
			const Math::Vector3D& coords2 = get3DCoordinates(atom2);

			double dist = norm2(coords1 - coords2);

			mtx(atom1_idx, atom2_idx) = dist;
			mtx(atom2_idx, atom1_idx) = dist;
		}
	}
}
