/* 
 * MolecularGraphTopDiameterAndRadiusFunctions.cpp 
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

#include <algorithm>

#include "CDPL/Descr/MolecularGraphFunctions.hpp"
#include "CDPL/Chem/MolecularGraphFunctions.hpp"
#include "CDPL/Chem/Atom.hpp"


using namespace CDPL; 


std::size_t Descr::calcTopologicalRadius(const Chem::MolecularGraph& molgraph)
{
	using namespace Chem;
	
	const Math::ULMatrix& dist_mtx = *getTopologicalDistanceMatrix(molgraph);
	std::size_t radius = molgraph.getNumBonds() + 1;

	MolecularGraph::ConstAtomIterator atoms_end = molgraph.getAtomsEnd();

	for (MolecularGraph::ConstAtomIterator it1 = molgraph.getAtomsBegin(); it1 != atoms_end; ) {
		const Atom& atom1 = *it1;
		std::size_t atom1_idx = molgraph.getAtomIndex(atom1);

		std::size_t max_atom_dist = 0;

		for (MolecularGraph::ConstAtomIterator it2 = ++it1; it2 != atoms_end; ++it2) {
			const Atom& atom2 = *it2;
			std::size_t atom2_idx = molgraph.getAtomIndex(atom2);

			max_atom_dist = std::max(std::size_t(dist_mtx(atom1_idx, atom2_idx)), max_atom_dist);
		}

		radius = std::min(max_atom_dist, radius);
	}

	return (radius == std::numeric_limits<std::size_t>::max() ? 0 : radius);
}

std::size_t Descr::calcTopologicalDiameter(const Chem::MolecularGraph& molgraph)
{
	using namespace Chem;
	
	const Math::ULMatrix& dist_mtx = *getTopologicalDistanceMatrix(molgraph);
	std::size_t diameter = 0;

	MolecularGraph::ConstAtomIterator atoms_end = molgraph.getAtomsEnd();

	for (MolecularGraph::ConstAtomIterator it1 = molgraph.getAtomsBegin(); it1 != atoms_end; ) {
		const Atom& atom1 = *it1;
		std::size_t atom1_idx = molgraph.getAtomIndex(atom1);

		for (MolecularGraph::ConstAtomIterator it2 = ++it1; it2 != atoms_end; ++it2) {
			const Atom& atom2 = *it2;
			std::size_t atom2_idx = molgraph.getAtomIndex(atom2);

			diameter = std::max(std::size_t(dist_mtx(atom1_idx, atom2_idx)), diameter);
		}
	}

	return diameter;
}
