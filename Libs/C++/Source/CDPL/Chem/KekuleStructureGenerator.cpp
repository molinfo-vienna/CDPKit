/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * KekuleStructureGenerator.cpp 
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
#include <functional>

#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/max_cardinality_matching.hpp>

#include "CDPL/Chem/KekuleStructureGenerator.hpp"
#include "CDPL/Chem/MolecularGraph.hpp"
#include "CDPL/Chem/Bond.hpp"
#include "CDPL/Chem/Atom.hpp"
#include "CDPL/Chem/AtomFunctions.hpp"
#include "CDPL/Chem/BondFunctions.hpp"
#include "CDPL/Chem/AtomType.hpp"
#include "CDPL/Chem/AtomDictionary.hpp"


using namespace CDPL; 


Chem::KekuleStructureGenerator::KekuleStructureGenerator() {}

Chem::KekuleStructureGenerator::KekuleStructureGenerator(const MolecularGraph& molgraph, Util::STArray& orders) 
{
	generate(molgraph, orders);
}

void Chem::KekuleStructureGenerator::generate(const MolecularGraph& molgraph, Util::STArray& orders)
{
	init(molgraph, orders);

	std::size_t num_atoms = molgraph.getNumAtoms();

	if (startAtomIdx == num_atoms)
		return;

	for (std::size_t i = startAtomIdx; i < num_atoms; i++) {
		const Atom& atom = molgraph.getAtom(i);
		
		unsigned int atom_type = getType(atom);
		const Util::STArray& valence_states = AtomDictionary::getValenceStates(atom_type);		

		if (valence_states.getSize() == 0) {
			defineNbrBondOrders(atom);
			continue;
		}

		long charge = getFormalCharge(atom);

		if (atom_type == AtomType::C)
			charge = std::min(charge, -charge);

		long free_valence = valence_states[0] + charge;

		if (hasImplicitHydrogenCount(atom))
			free_valence -= getImplicitHydrogenCount(atom);

		std::size_t num_undef_nbr_bonds = 0;
		Atom::ConstBondIterator bonds_end = atom.getBondsEnd();
		Atom::ConstAtomIterator a_it = atom.getAtomsBegin();

		for (Atom::ConstBondIterator b_it = atom.getBondsBegin(); b_it != bonds_end; ++b_it, ++a_it) {
			const Bond& bond = *b_it;

			if (!molgraph.containsBond(bond) || !molgraph.containsAtom(*a_it))
				continue;

			std::size_t bond_idx = molgraph.getBondIndex(bond);

			if (!defOrderMask.test(bond_idx))
				num_undef_nbr_bonds++;
			else
				free_valence -= orders[bond_idx];
		}

		if (free_valence < 0 || long(num_undef_nbr_bonds) >= free_valence)
			defineNbrBondOrders(atom);
	}

	typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::undirectedS> BondGraph; 
	typedef boost::property_map<BondGraph, boost::vertex_index_t>::type AtomIndexMap;
	typedef boost::graph_traits<BondGraph>::vertex_descriptor VertexDescriptor;
	typedef std::vector<VertexDescriptor> VertexList;

	std::size_t num_verts = num_atoms - startAtomIdx;

	BondGraph bond_graph(num_verts);
	VertexList max_match(num_verts);
	std::size_t i = 0;

	for (MolecularGraph::ConstBondIterator it = molGraph->getBondsBegin(), end = molGraph->getBondsEnd(); it != end; ++it, i++) {
		if (defOrderMask.test(i))
			continue;

		const Bond& bond = *it;

		if (&bond.getBegin() == &bond.getEnd())
			continue;

		conctdUndefBonds.clear();

		getConnectedUndefBonds(bond.getEnd());

		bond_graph.clear();

		BondList::iterator bonds_beg = conctdUndefBonds.begin();
		BondList::iterator bonds_end = conctdUndefBonds.end();

		for (BondList::iterator it = bonds_beg; it != bonds_end; ++it) {
			const Bond* bond = *it;

			boost::add_edge(molgraph.getAtomIndex(bond->getBegin()) - startAtomIdx, 
							molgraph.getAtomIndex(bond->getEnd()) - startAtomIdx,
							bond_graph);
		}

		max_match.assign(num_verts, boost::graph_traits<BondGraph>::null_vertex());

		boost::edmonds_maximum_cardinality_matching(bond_graph, &max_match[0]);

		AtomIndexMap atom_index_map = boost::get(boost::vertex_index, bond_graph);
		boost::graph_traits<BondGraph>::vertex_iterator vi, vi_end;
  
		for (boost::tie(vi, vi_end) = boost::vertices(bond_graph); vi != vi_end; ++vi) {
			if (max_match[*vi] != boost::graph_traits<BondGraph>::null_vertex() && *vi < max_match[*vi]) {
				std::size_t atom_idx1 = atom_index_map[*vi] + startAtomIdx;
				std::size_t atom_idx2 = atom_index_map[max_match[*vi]] + startAtomIdx;
				std::size_t bond_idx = molgraph.getBondIndex(molgraph.getAtom(atom_idx1).getBondToAtom(molgraph.getAtom(atom_idx2)));

				orders[bond_idx] = 2;
			}
		}
	}
}

void Chem::KekuleStructureGenerator::init(const MolecularGraph& molgraph, Util::STArray& orders)
{
	std::size_t num_bonds = molgraph.getNumBonds();
	molGraph = &molgraph;

	orders.assign(num_bonds, 0);
	defOrderMask.resize(num_bonds);
	defOrderMask.set();

	startAtomIdx = molgraph.getNumAtoms();

	for (std::size_t i = 0; i < num_bonds; i++) {
		const Bond& bond = molgraph.getBond(i);

		if (!molgraph.containsAtom(bond.getBegin()) || !molgraph.containsAtom(bond.getEnd()))
			continue;

		if (hasOrder(bond)) {
			orders[i] = getOrder(bond);

		} else {
			orders[i] = 1;
			defOrderMask.reset(i);

			startAtomIdx = std::min(startAtomIdx, molgraph.getAtomIndex(bond.getBegin()));
			startAtomIdx = std::min(startAtomIdx, molgraph.getAtomIndex(bond.getEnd()));
		}
	}
}

void Chem::KekuleStructureGenerator::defineNbrBondOrders(const Atom& atom)
{
	Atom::ConstBondIterator bonds_end = atom.getBondsEnd();
	Atom::ConstAtomIterator a_it = atom.getAtomsBegin();

	for (Atom::ConstBondIterator b_it = atom.getBondsBegin(); b_it != bonds_end; ++b_it, ++a_it) {
		const Bond& bond = *b_it;

		if (!molGraph->containsBond(bond) || !molGraph->containsAtom(*a_it))
			continue;

		defOrderMask.set(molGraph->getBondIndex(bond));
	}
}

void Chem::KekuleStructureGenerator::getConnectedUndefBonds(const Chem::Atom& atom)
{
	Atom::ConstBondIterator bonds_end = atom.getBondsEnd();
	Atom::ConstAtomIterator a_it = atom.getAtomsBegin();

	for (Atom::ConstBondIterator b_it = atom.getBondsBegin(); b_it != bonds_end; ++b_it, ++a_it) {
		const Atom& nbr_atom = *a_it;

		if (!molGraph->containsAtom(nbr_atom))
			continue;

		const Bond& bond = *b_it;

		if (!molGraph->containsBond(bond))
			continue;

		std::size_t bond_idx = molGraph->getBondIndex(bond);

		if (defOrderMask.test(bond_idx))
			continue;

		defOrderMask.set(bond_idx);
		conctdUndefBonds.push_back(&bond);

		getConnectedUndefBonds(nbr_atom);
	}
}
