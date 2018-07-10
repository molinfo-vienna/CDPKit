/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * MolecularGraphTpologicalDistanceFunctions.cpp 
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

#include <algorithm>
#include <limits>
#include <vector>

#include "CDPL/Chem/MolecularGraphFunctions.hpp"
#include "CDPL/Chem/MolecularGraphProperty.hpp"
#include "CDPL/Chem/Atom.hpp"
#include "CDPL/Chem/Bond.hpp"
#include "CDPL/Util/BitSet.hpp"


using namespace CDPL; 


namespace
{

	template <typename Mtx>
	void calcTopologicalDistances(const Chem::MolecularGraph& molgraph, Mtx& mtx, std::size_t max_dist)
	{
		using namespace Chem;

		std::size_t num_atoms = molgraph.getNumAtoms();

        mtx.resize(num_atoms, num_atoms, false);
        mtx.clear();

		Util::BitSet vis_atoms(molgraph.getNumAtoms());

		typedef std::vector<const Atom*> AtomList;
		typedef AtomList::const_iterator AtomListIterator;

		AtomList atoms;
		AtomList next_atoms;

		std::size_t i = 0;

		MolecularGraph::ConstAtomIterator molgraph_atoms_end = molgraph.getAtomsEnd();

		for (MolecularGraph::ConstAtomIterator it1 = molgraph.getAtomsBegin(); it1 != molgraph_atoms_end; ++it1, i++) {
			atoms.push_back(&*it1);
			vis_atoms.set(i);

			for (std::size_t path_len = 1; !atoms.empty() && (max_dist == 0 || path_len <= max_dist); path_len++) {
				AtomListIterator atoms_end = atoms.end(); 

				for (AtomListIterator it2 = atoms.begin(); it2 != atoms_end; ++it2) {
					const Atom* atom = *it2;

					Atom::ConstAtomIterator nbr_atoms_end = atom->getAtomsEnd();
					Atom::ConstBondIterator b_it = atom->getBondsBegin();
		
					for (Atom::ConstAtomIterator it3 = atom->getAtomsBegin(); it3 != nbr_atoms_end; ++it3, ++b_it) {
						const Atom* nbr_atom = &*it3;

						if (!molgraph.containsAtom(*nbr_atom))
							continue;
	
						if (!molgraph.containsBond(*b_it))
							continue;

						std::size_t nbr_atom_idx = molgraph.getAtomIndex(*nbr_atom);

						if (!vis_atoms.test(nbr_atom_idx)) {
							next_atoms.push_back(nbr_atom);
							vis_atoms.set(nbr_atom_idx);

							mtx(i, nbr_atom_idx) = path_len;
						}
					}		
				}

				atoms.swap(next_atoms);
				next_atoms.clear();
			}

			atoms.clear();
			vis_atoms.reset();
		}
	}
}


std::size_t Chem::calcTopologicalRadius(const MolecularGraph& molgraph)
{
	const Math::ULMatrix& dist_mtx = *getTopologicalDistanceMatrix(molgraph);

	std::size_t radius = std::numeric_limits<std::size_t>::max();

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

std::size_t Chem::calcTopologicalDiameter(const MolecularGraph& molgraph)
{
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

Math::ULMatrix::SharedPointer Chem::calcTopologicalDistanceMatrix(MolecularGraph& molgraph, bool overwrite, std::size_t max_dist)
{
	if (!overwrite) {
		Base::Variant mtx_prop = molgraph.getProperty(MolecularGraphProperty::TOPOLOGICAL_DISTANCE_MATRIX);

		if (!mtx_prop.isEmpty())
			return mtx_prop.getData<Math::ULMatrix::SharedPointer>();
	}

	Math::ULMatrix::SharedPointer mtx_ptr(new Math::ULMatrix());

	calcTopologicalDistanceMatrix(molgraph, *mtx_ptr, max_dist);

	molgraph.setProperty(MolecularGraphProperty::TOPOLOGICAL_DISTANCE_MATRIX, mtx_ptr);

	return mtx_ptr;
}

void Chem::calcTopologicalDistanceMatrix(const MolecularGraph& molgraph, Math::ULMatrix& mtx, std::size_t max_dist)
{
	calcTopologicalDistances(molgraph, mtx, max_dist);
}

void Chem::calcTopologicalDistanceMatrix(const MolecularGraph& molgraph, Math::SparseULMatrix& mtx, std::size_t max_dist)
{
	calcTopologicalDistances(molgraph, mtx, max_dist);
}
