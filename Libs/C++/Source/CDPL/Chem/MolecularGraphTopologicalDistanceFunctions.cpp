/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * MolecularGraphTpologicalDistanceFunctions.cpp 
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

#include "CDPL/Chem/MolecularGraphFunctions.hpp"
#include "CDPL/Chem/MolecularGraphProperty.hpp"
#include "CDPL/Chem/Atom.hpp"
#include "CDPL/Chem/Bond.hpp"
#include "CDPL/Base/Exceptions.hpp"
#include "CDPL/Util/BitSet.hpp"


using namespace CDPL; 


namespace
{

/*
	// Floyd-Warshall Algorithm
	// appears to be rather slow for macromolecules with mainly chains

	template <typename Mtx>
	void calcTopologicalDistancesFW(const Chem::MolecularGraph& molgraph, Mtx& mtx)
	{
		using namespace Chem;

		std::size_t num_atoms = molgraph.getNumAtoms();

        mtx.resize(num_atoms, num_atoms, false);
        mtx.clear();

		for (MolecularGraph::ConstBondIterator it = molgraph.getBondsBegin(), end = molgraph.getBondsEnd(); it != end; ++it) {
			const Bond& bond = *it;

			try {
				std::size_t i = molgraph.getAtomIndex(bond.getBegin());
				std::size_t j = molgraph.getAtomIndex(bond.getEnd());

				mtx(i, j) = 1;
				mtx(j, i) = 1;

			} catch (const Base::ItemNotFound& e) {}
		}

		for (std::size_t k = 0; k < num_atoms; k++) {
			for (std::size_t i = 0; i < num_atoms; i++) {
				for (std::size_t j = i + 1; j < num_atoms; j++) {
					typename Mtx::ValueType dist_ik =  mtx(i, k);

					if (dist_ik == 0)
						continue;

					typename Mtx::ValueType dist_kj =  mtx(k, j);

					if (dist_kj == 0)
						continue;

					typename Mtx::ValueType dist_ij = mtx(i, j);
					typename Mtx::ValueType dist_ikj = dist_ik + dist_kj;

					if (dist_ij == 0 || dist_ij > dist_ikj) {
						mtx(i, j) = dist_ikj;
						mtx(j, i) = dist_ikj;
					}
				}
			}
		}
	}
*/
	template <typename Mtx>
	void calcTopologicalDistances(const Chem::MolecularGraph& molgraph, Mtx& mtx)
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

			for (std::size_t path_len = 1; !atoms.empty(); path_len++) {
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

	template <typename Mtx>
	void extractTopologicalDistances(const Chem::MolecularGraph& src_molgraph, const Chem::MolecularGraph& tgt_molgraph, Mtx& mtx)
	{
		using namespace Chem;

		const Math::ULMatrix& src_mtx = *getTopologicalDistanceMatrix(src_molgraph);
		std::size_t num_atoms = tgt_molgraph.getNumAtoms();

        mtx.resize(num_atoms, num_atoms, false);
        mtx.clear();

		for (std::size_t i = 0; i < num_atoms; i++) {
			std::size_t src_idx1 = src_molgraph.getAtomIndex(tgt_molgraph.getAtom(i));

			for (std::size_t j = i + 1; j < num_atoms; j++) {
				std::size_t dist = src_mtx(src_idx1, src_molgraph.getAtomIndex(tgt_molgraph.getAtom(j)));

				mtx(i, j) = dist;
				mtx(j, i) = dist;
			}
		}
	}
}


Math::ULMatrix::SharedPointer Chem::calcTopologicalDistanceMatrix(MolecularGraph& molgraph, bool overwrite)
{
	if (!overwrite) {
		Base::Variant mtx_prop = molgraph.getProperty(MolecularGraphProperty::TOPOLOGICAL_DISTANCE_MATRIX);

		if (!mtx_prop.isEmpty())
			return mtx_prop.getData<Math::ULMatrix::SharedPointer>();
	}

	Math::ULMatrix::SharedPointer mtx_ptr(new Math::ULMatrix());

	calcTopologicalDistances(molgraph, *mtx_ptr);
	setTopologicalDistanceMatrix(molgraph, mtx_ptr);

	return mtx_ptr;
}

Math::ULMatrix::SharedPointer Chem::extractTopologicalDistanceSubMatrix(const MolecularGraph& src_molgraph, MolecularGraph& tgt_molgraph, bool overwrite)
{
	if (!overwrite) {
		Base::Variant mtx_prop = tgt_molgraph.getProperty(MolecularGraphProperty::TOPOLOGICAL_DISTANCE_MATRIX);

		if (!mtx_prop.isEmpty())
			return mtx_prop.getData<Math::ULMatrix::SharedPointer>();
	}

	Math::ULMatrix::SharedPointer mtx_ptr(new Math::ULMatrix());

	extractTopologicalDistances(src_molgraph, tgt_molgraph, *mtx_ptr);
	setTopologicalDistanceMatrix(tgt_molgraph, mtx_ptr);

	return mtx_ptr;
}

void Chem::calcTopologicalDistanceMatrix(const MolecularGraph& molgraph, Math::ULMatrix& mtx)
{
	calcTopologicalDistances(molgraph, mtx);
}

void Chem::extractTopologicalDistanceSubMatrix(const MolecularGraph& src_molgraph, const MolecularGraph& tgt_molgraph, Math::ULMatrix& mtx)
{
	extractTopologicalDistances(src_molgraph, tgt_molgraph, mtx);
}

void Chem::calcTopologicalDistanceMatrix(const MolecularGraph& molgraph, Math::SparseULMatrix& mtx)
{
	calcTopologicalDistances(molgraph, mtx);
}

void Chem::extractTopologicalDistanceSubMatrix(const MolecularGraph& src_molgraph, const MolecularGraph& tgt_molgraph, Math::SparseULMatrix& mtx)
{
	extractTopologicalDistances(src_molgraph, tgt_molgraph, mtx);
}
