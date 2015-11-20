/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * CanonicalNumberingGenerator.cpp 
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
#include <iterator>
#include <cassert>

#include <boost/bind.hpp>

#include "CDPL/Chem/CanonicalNumberingGenerator.hpp"
#include "CDPL/Chem/Atom.hpp"
#include "CDPL/Chem/Bond.hpp"
#include "CDPL/Chem/AtomConfiguration.hpp"
#include "CDPL/Chem/BondConfiguration.hpp"
#include "CDPL/Chem/AtomFunctions.hpp"
#include "CDPL/Chem/BondFunctions.hpp"
#include "CDPL/Chem/MolecularGraphFunctions.hpp"
#include "CDPL/Chem/AtomType.hpp"
#include "CDPL/Chem/StereoDescriptor.hpp"
#include "CDPL/Util/Permutation.hpp"


using namespace CDPL;


const unsigned int Chem::CanonicalNumberingGenerator::DEF_ATOM_PROPERTY_FLAGS;
const unsigned int Chem::CanonicalNumberingGenerator::DEF_BOND_PROPERTY_FLAGS;


Chem::CanonicalNumberingGenerator::CanonicalNumberingGenerator():
	atomPropertyFlags(DEF_ATOM_PROPERTY_FLAGS), bondPropertyFlags(DEF_BOND_PROPERTY_FLAGS) {}

Chem::CanonicalNumberingGenerator::CanonicalNumberingGenerator(const MolecularGraph& molgraph):
	atomPropertyFlags(DEF_ATOM_PROPERTY_FLAGS), bondPropertyFlags(DEF_BOND_PROPERTY_FLAGS)
{
	generate(molgraph);
}

void Chem::CanonicalNumberingGenerator::setAtomPropertyFlags(unsigned int flags)
{
	atomPropertyFlags = flags;
}

unsigned int Chem::CanonicalNumberingGenerator::getAtomPropertyFlags() const
{
	return atomPropertyFlags;
}

void Chem::CanonicalNumberingGenerator::setBondPropertyFlags(unsigned int flags)
{
	bondPropertyFlags = flags;
}

unsigned int Chem::CanonicalNumberingGenerator::getBondPropertyFlags() const
{
	return bondPropertyFlags;
}

const Util::STArray& Chem::CanonicalNumberingGenerator::generate(const MolecularGraph& molgraph)
{
	init(molgraph);
	canonicalize(molgraph);	

	return canonNumbering;
}

const Util::STArray& Chem::CanonicalNumberingGenerator::getResult() const
{
	return canonNumbering;
}

void Chem::CanonicalNumberingGenerator::init(const MolecularGraph& molgraph)
{
	molGraph = &molgraph;

	std::size_t num_atoms = molgraph.getNumAtoms();
	std::size_t num_bonds = molgraph.getNumBonds();

	allocNodes.clear();
	allocNodes.reserve(num_atoms);

	allocEdges.clear();
	allocEdges.reserve(num_bonds);

	compConnectionTables.clear();
	canonComponentList.clear();

	canonNumbering.assign(num_atoms, 0);

	equivNodeStack.clear();
	nodeLabelingStack.clear();

	if ((atomPropertyFlags & AtomPropertyFlag::CONFIGURATION) || (bondPropertyFlags & BondPropertyFlag::CONFIGURATION))
		visitedEdgeMask.reset();

	MolecularGraph::ConstAtomIterator atoms_end = molgraph.getAtomsEnd();

	for (MolecularGraph::ConstAtomIterator it = molgraph.getAtomsBegin(); it != atoms_end; ++it) {
		const Atom& atom = *it;
		Base::uint64 atom_label = 0;

		if (atomPropertyFlags & AtomPropertyFlag::TYPE)
			atom_label = getType(atom);
		
		if (atomPropertyFlags & AtomPropertyFlag::ISOTOPE)
			atom_label = atom_label * AtomType::MAX_TYPE * 3 + getIsotope(atom);

		if (atomPropertyFlags & AtomPropertyFlag::H_COUNT)
			atom_label = atom_label * 10 + (getExplicitBondCount(atom, molgraph, 1, AtomType::H) + calcImplicitHydrogenCount(atom, molgraph));

		if (atomPropertyFlags & AtomPropertyFlag::FORMAL_CHARGE) {
			long charge = getFormalCharge(atom);

			if (charge < 0)
				charge = -(-charge % 50);
			else
				charge = charge % 50;

			atom_label = atom_label * 100 + std::size_t(charge + 50);
		}

		if (atomPropertyFlags & AtomPropertyFlag::AROMATICITY)
			atom_label = atom_label * 2 + getAromaticityFlag(atom);

		if (atomPropertyFlags & AtomPropertyFlag::CONFIGURATION) {
			atom_label *= 3;

			switch (getCIPConfiguration(atom)) {

				case AtomConfiguration::R:
					atom_label += 1;
					break;

				case AtomConfiguration::S:
					atom_label += 2;

				default:
					break;
			}
		}

		AtomNode::SharedPointer atom_node_ptr(new AtomNode(this, &atom, atom_label, allocNodes.size()));
		allocNodes.push_back(atom_node_ptr);
	}

	std::size_t edge_id = allocEdges.size() / 2;

	MolecularGraph::ConstBondIterator bonds_end = molgraph.getBondsEnd();

	for (MolecularGraph::ConstBondIterator it = molgraph.getBondsBegin(); it != bonds_end; ++it) {
		const Bond& bond = *it;

		if (!molgraph.containsAtom(bond.getBegin()) || !molgraph.containsAtom(bond.getEnd()))
			continue;

		Base::uint64 bond_label = 0;

		AtomNode* atom_node1 = allocNodes[molgraph.getAtomIndex(bond.getBegin())].get();
		AtomNode* atom_node2 = allocNodes[molgraph.getAtomIndex(bond.getEnd())].get();

		if (bondPropertyFlags & BondPropertyFlag::AROMATICITY)
			bond_label = getAromaticityFlag(bond);

		if (bond_label == 0 && (bondPropertyFlags & BondPropertyFlag::ORDER))
			bond_label = getOrder(bond) + 2;
	
		if (bondPropertyFlags & BondPropertyFlag::CONFIGURATION) {
			bond_label *= 3;

			switch (getCIPConfiguration(bond)) {

				case BondConfiguration::E:
					bond_label += 1;
					break;

				case BondConfiguration::Z:
					bond_label += 2;

				default:
					break;
			}
		}
	
		Edge::SharedPointer edge1_ptr(new Edge(this, &bond, bond_label, atom_node2, edge_id));
		Edge::SharedPointer edge2_ptr(new Edge(this, &bond, bond_label, atom_node1, edge_id++));

		allocEdges.push_back(edge1_ptr);
		allocEdges.push_back(edge2_ptr);

		atom_node1->addEdge(edge1_ptr.get());
		atom_node2->addEdge(edge2_ptr.get());
	}
}

void Chem::CanonicalNumberingGenerator::setup(const MolecularGraph& comp)
{
	nodeList.clear();
	nodeList.reserve(comp.getNumAtoms());

	compConnectionTables.push_back(ConnectionTable());
	levelConnectionTables.clear();

	MolecularGraph::ConstAtomIterator atoms_end = comp.getAtomsEnd();

	std::size_t edge_id = allocEdges.size() / 2;

	for (MolecularGraph::ConstAtomIterator it = comp.getAtomsBegin(); it != atoms_end; ++it) {
		const Atom& atom = *it;
		AtomNode* atom_node = allocNodes[molGraph->getAtomIndex(atom)].get();

		nodeList.push_back(atom_node);
	}

	if ((atomPropertyFlags & AtomPropertyFlag::CONFIGURATION) ||
		(bondPropertyFlags & BondPropertyFlag::CONFIGURATION)) {
		
		assert(!visitedEdgeMask.any());

		if (visitedEdgeMask.size() < edge_id)
			visitedEdgeMask.resize(edge_id);

		visitedEdgeMask.reset();
	}
}

void Chem::CanonicalNumberingGenerator::canonicalize(const MolecularGraph& molgraph)
{
	if (getComponents(molgraph)->getSize() <= 1) {
		if (molgraph.getNumAtoms() == 0)
			return ;

		setup(molgraph);
		canonicalize(0);
		establishCanonNumbering();
		return;
	}

	const FragmentList& components = *getComponents(molgraph);

	FragmentList::ConstElementIterator comps_end = components.getElementsEnd();

	for (FragmentList::ConstElementIterator it = components.getElementsBegin(); it != comps_end; ++it) {
		const Fragment& comp = *it;

		if (comp.getNumAtoms() == 0)
			continue;

		setup(comp);
		canonicalize(0);
		establishCanonNumbering();
	}

	ConnectionTableList::const_iterator ctab_it = compConnectionTables.begin();

	for (FragmentList::ConstElementIterator comp_it = components.getElementsBegin(); comp_it != comps_end;
		 ++comp_it, ++ctab_it) {
		
		const Fragment& comp = *comp_it;

		if (comp.getNumAtoms() == 0)
			continue;

		canonComponentList.push_back(CanonComponentInfo(&comp, &(*ctab_it)));
	}

	std::sort(canonComponentList.begin(), canonComponentList.end(), ComponentCmpFunc());

	CanonComponentList::const_iterator canon_comps_end = canonComponentList.end();
	std::size_t comp_offset = 0;

	for (CanonComponentList::const_iterator c_it = canonComponentList.begin(); c_it != canon_comps_end; ++c_it) {
		const Fragment* comp = c_it->first;

		Fragment::ConstAtomIterator atoms_end = comp->getAtomsEnd();

		for (Fragment::ConstAtomIterator a_it = comp->getAtomsBegin(); a_it != atoms_end; ++a_it) {
			const Atom& atom = *a_it;

			canonNumbering[molgraph.getAtomIndex(atom)] += comp_offset;
		}

		comp_offset += comp->getNumAtoms();
	}
}

void Chem::CanonicalNumberingGenerator::canonicalize(std::size_t depth)
{
	if (levelConnectionTables.size() <= depth)
		levelConnectionTables.resize(depth + 1);

	NodeList::iterator nodes_begin = nodeList.begin();
	NodeList::iterator nodes_end = nodeList.end();

	std::size_t eq_range_begin = 0;
	std::size_t eq_range_end = 0;

	AtomNode::LessCmpFunc node_cmp_func;

	std::size_t max_num_cells = 0;

	while (true) {
		std::for_each(nodes_begin, nodes_end, std::mem_fun(&AtomNode::sortEdges));
		std::sort(nodes_begin, nodes_end, node_cmp_func);

		std::size_t num_cells = 0;
		std::size_t label = 0;

		for (NodeList::iterator it = nodes_begin; it != nodes_end; num_cells++) {
			NodeList::iterator ub = std::upper_bound(it, nodes_end, *it, node_cmp_func);

			std::size_t eq_range_len = ub - it;

			label += eq_range_len;

			if (eq_range_len > 1) {
				std::for_each(it, ub, std::bind2nd(std::mem_fun(&AtomNode::setNewLabel), label));

				if (eq_range_begin == eq_range_end || (eq_range_end - eq_range_begin > eq_range_len)) {
					eq_range_begin = it - nodes_begin;
					eq_range_end = ub - nodes_begin;
				}

			} else
				(*it)->setNewLabel(label);

			it = ub;
		}

		assert(num_cells >= max_num_cells);

		if (num_cells == max_num_cells)
			break;
		
		max_num_cells = num_cells;
		eq_range_begin = eq_range_end = 0;

		std::for_each(nodes_begin, nodes_end, std::mem_fun(&AtomNode::updateLabel));
	}

	buildConnectionTable(testConnectionTable);

	bool backtrack = (!levelConnectionTables[depth].empty() &&
					  std::lexicographical_compare(levelConnectionTables[depth].begin(), levelConnectionTables[depth].end(),
												   testConnectionTable.begin(), testConnectionTable.end()));
	if (backtrack)
		return;

	levelConnectionTables[depth].swap(testConnectionTable);

	if (eq_range_begin == eq_range_end) {
		processNewSolution();
		return;
	}

	if (depth == 0) {
		bool with_stereo = false;

		if ((atomPropertyFlags & AtomPropertyFlag::CONFIGURATION) || (bondPropertyFlags & BondPropertyFlag::CONFIGURATION)) {
			for (NodeList::iterator it = nodes_begin; it != nodes_end; ++it) {
				if ((*it)->involvedInStereocenter()) {
					with_stereo = true;
					break;
				}
			}

			if (with_stereo) {
				for (NodeList::iterator it = nodes_begin; it != nodes_end; ) {
					NodeList::iterator ub = std::upper_bound(it, nodes_end, *it, node_cmp_func);

					if ((ub - it) > 1) {
						while (it != ub) {
							AtomNode* node1 = *it;

							for (NodeList::iterator it1 = ++it ; it1 != ub; ++it1) {
								AtomNode* node2 = *it1;

								if (AtomNode::terminalAndOnCommonNonStereoNode(node1, node2)) {
									node1->addToEquivalenceSet(node2);
									node2->addToEquivalenceSet(node1);
									continue;
								}

								if (!node1->reachesNodeViaStereocenter(node2, false))
									continue;

								node1->addToNonEquivalenceSet(node2);
								node2->addToNonEquivalenceSet(node1);
							}
						}

					} else
						++it;
				}
			}
		}

		if (!with_stereo) {
			for (NodeList::iterator it = nodes_begin; it != nodes_end; ) {
				NodeList::iterator ub = std::upper_bound(it, nodes_end, *it, node_cmp_func);

				if ((ub - it) > 1) {
					while (it != ub) {
						AtomNode* node1 = *it;

						for (NodeList::iterator it1 = ++it ; it1 != ub; ++it1) {
							AtomNode* node2 = *it1;

							if (!AtomNode::terminalAndOnCommonNonStereoNode(node1, node2))
								continue;

							node1->addToEquivalenceSet(node2);
							node2->addToEquivalenceSet(node1);
						}
					}

				} else
					++it;
			}
		}
	}

	std::size_t old_stack_size = equivNodeStack.size();

	equivNodeStack.insert(equivNodeStack.end(), nodes_begin + eq_range_begin, nodes_begin + eq_range_end);

	std::size_t new_stack_size = equivNodeStack.size();

	for (std::size_t i = old_stack_size; i < new_stack_size; i++) {
		AtomNode* node = equivNodeStack[i];
		bool skip = false;

		for (std::size_t j = old_stack_size; j < i; j++) {
			if (equivNodeStack[j]->isEquivalent(node)) {
				skip = true;
				break;
			}
		}

		if (skip)
			continue;

		saveState();
		
		node->setLabel(node->getLabel() - 1);

		canonicalize(depth + 1);

		restoreState();
	}

	equivNodeStack.erase(equivNodeStack.begin() + old_stack_size, equivNodeStack.end());
}

void Chem::CanonicalNumberingGenerator::processNewSolution()
{
	switch (testNewSolution()) {

		case -1:
			compConnectionTables.back().swap(testConnectionTable);
			minNodeList = nodeList;
			return;
			
		case 0: {
			std::size_t num_nodes = nodeList.size();

			for (std::size_t i = 0; i < num_nodes; i++) {
				AtomNode* node1 = nodeList[i];
				AtomNode* node2 = minNodeList[i];

				if (node1 == node2)
					continue;

				node1->addToEquivalenceSet(node2);
				node2->addToEquivalenceSet(node1);
			}

			return;
		}
	}
}

int Chem::CanonicalNumberingGenerator::testNewSolution()
{
	buildConnectionTable(testConnectionTable);
	
	ConnectionTable& min_ctab = compConnectionTables.back();

	if (min_ctab.empty() || 
		std::lexicographical_compare(testConnectionTable.begin(), testConnectionTable.end(), 
									 min_ctab.begin(), min_ctab.begin() + testConnectionTable.size())) {

		if (atomPropertyFlags & AtomPropertyFlag::CONFIGURATION)
			appendAtomConfigs(testConnectionTable);

		if (bondPropertyFlags & BondPropertyFlag::CONFIGURATION)
			appendBondConfigs(testConnectionTable);

		return -1;
	}

	if (std::equal(testConnectionTable.begin(), testConnectionTable.end(), min_ctab.begin())) {
		if ((atomPropertyFlags & AtomPropertyFlag::CONFIGURATION) && foundStereogenicAtoms) {
			std::size_t parities_beg = testConnectionTable.size();

			appendAtomConfigs(testConnectionTable);

			std::size_t parities_end = testConnectionTable.size();

			if (std::lexicographical_compare(testConnectionTable.begin() + parities_beg, testConnectionTable.end(), 
											 min_ctab.begin() + parities_beg, min_ctab.begin() + parities_end)) {

				if ((bondPropertyFlags & BondPropertyFlag::CONFIGURATION) && foundStereogenicBonds)
					appendBondConfigs(testConnectionTable);

				return -1;
			}

			if (!std::equal(testConnectionTable.begin() + parities_beg, testConnectionTable.end(), 
							min_ctab.begin() + parities_beg))
				return 1;
		}

		if ((bondPropertyFlags & BondPropertyFlag::CONFIGURATION) && foundStereogenicBonds) {
			std::size_t geometries_beg = testConnectionTable.size();

			appendBondConfigs(testConnectionTable);

			if (std::lexicographical_compare(testConnectionTable.begin() + geometries_beg, testConnectionTable.end(), 
											 min_ctab.begin() + geometries_beg, min_ctab.end()))
				return -1;

			if (!std::equal(testConnectionTable.begin() + geometries_beg, testConnectionTable.end(), 
							min_ctab.begin() + geometries_beg))
				return 1;
		}

		return 0;
	}

	return 1;
}

void Chem::CanonicalNumberingGenerator::buildConnectionTable(ConnectionTable& ctab) const
{
	ctab.clear();

	std::for_each(nodeList.begin(), nodeList.end(), 
				  boost::bind(&AtomNode::appendConnectivityData, _1, boost::ref(ctab)));
}

void Chem::CanonicalNumberingGenerator::appendAtomConfigs(ConnectionTable& ctab)
{
	std::size_t old_ctab_size = ctab.size();

	std::for_each(nodeList.begin(), nodeList.end(), 
				  boost::bind(&AtomNode::appendAtomConfigData, _1, boost::ref(ctab)));

	foundStereogenicAtoms = (old_ctab_size != ctab.size());
}

void Chem::CanonicalNumberingGenerator::appendBondConfigs(ConnectionTable& ctab)
{
	std::size_t old_ctab_size = ctab.size();

	std::for_each(nodeList.begin(), nodeList.end(), 
				  boost::bind(&AtomNode::appendBondConfigData, _1, boost::ref(ctab)));

	foundStereogenicBonds = (old_ctab_size != ctab.size());
}

void Chem::CanonicalNumberingGenerator::establishCanonNumbering()
{
	NodeList::const_iterator nodes_end = minNodeList.end();
	std::size_t canon_number = 1;

	for (NodeList::const_iterator n_it = minNodeList.begin(); n_it != nodes_end; ++n_it) {
		const Atom* atom = (*n_it)->getAtom();

		canonNumbering[molGraph->getAtomIndex(*atom)] = canon_number++;
	}
}

void Chem::CanonicalNumberingGenerator::saveState()
{
	nodeLabelingStack.reserve(nodeLabelingStack.size() + nodeList.size());

	std::transform(nodeList.begin(), nodeList.end(), std::back_inserter(nodeLabelingStack), 
				   boost::bind(&std::make_pair<AtomNode*, Base::uint64>, _1, 
							   boost::bind(&AtomNode::getLabel, _1)));
}

void Chem::CanonicalNumberingGenerator::restoreState()
{
	assert(!nodeLabelingStack.empty());

	std::size_t num_nodes = nodeList.size();

	assert(nodeLabelingStack.size() >= num_nodes);

	NodeLabelingStack::iterator node_label_stack_end = nodeLabelingStack.end();

	std::for_each(node_label_stack_end - num_nodes, node_label_stack_end,
				  boost::bind(&AtomNode::setLabel, 
							  boost::bind(&NodeLabelingState::first, _1),
							  boost::bind(&NodeLabelingState::second, _1)));

	nodeLabelingStack.erase(node_label_stack_end - num_nodes, node_label_stack_end);
}


bool Chem::CanonicalNumberingGenerator::ComponentCmpFunc::operator()(const CanonComponentInfo& info1, 
																	 const CanonComponentInfo& info2) const
{
	if (info1.second->size() == info2.second->size())
		return std::lexicographical_compare(info1.second->begin(), info1.second->end(),
											info2.second->begin(), info2.second->end());

	return (info1.second->size() > info2.second->size());
}


//---------

Chem::CanonicalNumberingGenerator::AtomNode::AtomNode(Generator* generator, const Atom* atom, 
													  Base::uint64 label, std::size_t id):
	generator(generator), atom(atom), initialLabel(label), label(label), newLabel(label), 
	id(id), configDataValid(false), partOfStereocenterValid(false) {}

const Chem::Atom* Chem::CanonicalNumberingGenerator::AtomNode::getAtom() const
{
	return atom;
}

void Chem::CanonicalNumberingGenerator::AtomNode::addEdge(Edge* edge)
{
	edges.push_back(edge);
}

void Chem::CanonicalNumberingGenerator::AtomNode::setLabel(Base::uint64 l)
{
	label = l;
}

Base::uint64 Chem::CanonicalNumberingGenerator::AtomNode::getLabel() const
{
	return label;
}

void Chem::CanonicalNumberingGenerator::AtomNode::setNewLabel(std::size_t l)
{
	newLabel = l;
}

void Chem::CanonicalNumberingGenerator::AtomNode::updateLabel()
{
	label = newLabel;
}

std::size_t Chem::CanonicalNumberingGenerator::AtomNode::getID() const
{
	return id;
}

void Chem::CanonicalNumberingGenerator::AtomNode::sortEdges()
{
	std::sort(edges.begin(), edges.end(), Edge::LessCmpFunc());
}

std::size_t Chem::CanonicalNumberingGenerator::AtomNode::getNumEdges() const
{
	return edges.size();
}

Chem::CanonicalNumberingGenerator::AtomNode::EdgeIterator 
Chem::CanonicalNumberingGenerator::AtomNode::getEdgesBegin() const
{
	return edges.begin();
}

Chem::CanonicalNumberingGenerator::AtomNode::EdgeIterator 
Chem::CanonicalNumberingGenerator::AtomNode::getEdgesEnd() const
{
	return edges.end();
}

void Chem::CanonicalNumberingGenerator::AtomNode::appendConnectivityData(ConnectionTable& ctab) const
{
	ctab.push_back(label);
	ctab.push_back(initialLabel);

	EdgeList::const_iterator edges_end = edges.end();

	for (EdgeList::const_iterator it = edges.begin(); it != edges_end; ++it) {
		const Edge* edge = *it;
		
		if (edge->getNeighborNode()->getLabel() < label)
			edge->appendBondData(ctab);
	}
}

void Chem::CanonicalNumberingGenerator::AtomNode::appendAtomConfigData(ConnectionTable& ctab)
{
	if (!initConfigurationData())
		return;

	const Atom* nbr_atoms[4];

	std::transform(edges.begin(), edges.end(), nbr_atoms,
				   boost::bind(&AtomNode::atom, boost::bind(&Edge::getNeighborNode, _1)));

	std::size_t num_edges = edges.size();

	assert(num_edges == 3 || num_edges == 4);

	std::size_t num_perms = 0;
	std::size_t num_swaps = 0;

	while (!std::equal(nbr_atoms, nbr_atoms + num_edges, refNbrAtoms) && (++num_perms < (num_edges == 3 ? 6 : 24)))
		num_swaps += Util::nextPermutation(nbr_atoms, nbr_atoms + num_edges);

	if (num_perms >= (num_edges == 3 ? 6 : 24)) {  // a matching permutation should have been found
		hasConfiguration = false;
		return;
	}

	ctab.push_back(label);

	if ((num_swaps % 2) == 0) 
		ctab.push_back(configuration);
	else
		ctab.push_back(configuration == AtomConfiguration::R ? AtomConfiguration::S : AtomConfiguration::R);
}

void Chem::CanonicalNumberingGenerator::AtomNode::appendBondConfigData(ConnectionTable& ctab) const
{
	EdgeList::const_iterator edges_end = edges.end();

	for (EdgeList::const_iterator it = edges.begin(); it != edges_end; ++it) {
		Edge* edge = *it;
		
		if (edge->getNeighborNode()->getLabel() > label)
			edge->appendConfigurationData(this, ctab);
	}
}

bool Chem::CanonicalNumberingGenerator::AtomNode::terminalAndOnCommonNonStereoNode(const AtomNode* node1, const AtomNode* node2)
{
	if (node1->edges.size() == 1 && node2->edges.size() == 1) { // special treatment for terminal nodes -> speedup
		AtomNode* node1_nbr = node1->edges.front()->getNeighborNode();
		AtomNode* node2_nbr = node2->edges.front()->getNeighborNode();

		return (node1_nbr == node2_nbr && !node1_nbr->involvedInStereocenter());
	}

	return false;
}

bool Chem::CanonicalNumberingGenerator::AtomNode::isEquivalent(const AtomNode* node) const
{
	if (equivNodeMask.size() <= node->id)
		return false;

	return equivNodeMask.test(node->id);
}

bool Chem::CanonicalNumberingGenerator::AtomNode::isNonEquivalent(const AtomNode* node) const
{
	if (nonEquivNodeMask.size() <= node->id)
		return false;

	return nonEquivNodeMask.test(node->id);
}

void Chem::CanonicalNumberingGenerator::AtomNode::addToEquivalenceSet(const AtomNode* node)
{
	if (isNonEquivalent(node))
		return;

	if (equivNodeMask.size() <= node->id)
		equivNodeMask.resize(node->id + 1);

	equivNodeMask.set(node->id);
}

void Chem::CanonicalNumberingGenerator::AtomNode::addToNonEquivalenceSet(const AtomNode* node)
{
	if (nonEquivNodeMask.size() <= node->id)
		nonEquivNodeMask.resize(node->id + 1);

	nonEquivNodeMask.set(node->id);
}

bool Chem::CanonicalNumberingGenerator::AtomNode::reachesNodeViaStereocenter(AtomNode* node, bool found_ctr)
{
	if (!found_ctr)
		found_ctr = involvedInStereocenter();

	if (this == node)
		return found_ctr;

	Util::BitSet& vis_edge_mask = generator->visitedEdgeMask;

	EdgeList::const_iterator edges_end = edges.end();

	for (EdgeList::const_iterator it = edges.begin(); it != edges_end; ++it) {
		Edge* edge = *it;
		std::size_t edge_id = edge->getID();

		if (vis_edge_mask.test(edge_id))
			continue;

		vis_edge_mask.set(edge_id);

		bool found_node = edge->getNeighborNode()->reachesNodeViaStereocenter(node, found_ctr);

		vis_edge_mask.reset(edge_id);

		if (found_node)
			return true;
	}

	return false;
}

bool Chem::CanonicalNumberingGenerator::AtomNode::involvedInStereocenter() 
{
	if (partOfStereocenterValid)
		return partOfStereocenter;

	partOfStereocenterValid = true;
	partOfStereocenter = false;

	if (generator->bondPropertyFlags & BondPropertyFlag::CONFIGURATION) {
		EdgeList::const_iterator edges_end = edges.end();

		for (EdgeList::const_iterator it = edges.begin(); it != edges_end; ++it) {
			if ((*it)->representsStereoBond(this)) {
				partOfStereocenter = true;
				return true;
			}
		}
	}

	if (generator->atomPropertyFlags & AtomPropertyFlag::CONFIGURATION)
		partOfStereocenter = initConfigurationData();

	return partOfStereocenter;
}

bool Chem::CanonicalNumberingGenerator::AtomNode::initConfigurationData()
{
	if (configDataValid)
		return hasConfiguration;

	configDataValid = true;
	hasConfiguration = false;

	std::size_t num_edges = edges.size();

	if (num_edges < 3 || num_edges > 4)
		return false;

	const StereoDescriptor& stereo_desc = calcStereoDescriptor(*atom, *generator->molGraph, 0);
	std::size_t num_ref_atoms = stereo_desc.getNumReferenceAtoms();

	if (num_edges != num_ref_atoms)
		return false;

	configuration = stereo_desc.getConfiguration();

	if (configuration != AtomConfiguration::R && configuration != AtomConfiguration::S)
		return false;

	std::copy(stereo_desc.getReferenceAtoms(), stereo_desc.getReferenceAtoms() + num_ref_atoms, &refNbrAtoms[0]);

	hasConfiguration = true;

	return true;
}


bool Chem::CanonicalNumberingGenerator::AtomNode::LessCmpFunc::operator()(const AtomNode* node1, 
																		  const AtomNode* node2) const
{
	if (node1->label == node2->label)
		return std::lexicographical_compare(node1->edges.begin(), node1->edges.end(),
											node2->edges.begin(), node2->edges.end(),
											Edge::LessCmpFunc());
	return (node1->label < node2->label);
}


//---------

Chem::CanonicalNumberingGenerator::Edge::Edge(const Generator* generator, const Bond* bond, Base::uint64 label, 
											  AtomNode* nbr_node, std::size_t id):
	generator(generator), bond(bond), nbrNode(nbr_node), label(label), id(id), configDataValid(false) {}

Chem::CanonicalNumberingGenerator::AtomNode* Chem::CanonicalNumberingGenerator::Edge::getNeighborNode() const
{
	return nbrNode;
}

void Chem::CanonicalNumberingGenerator::Edge::appendBondData(ConnectionTable& ctab) const
{
	ctab.push_back(nbrNode->getLabel());
	ctab.push_back(label);
}

void Chem::CanonicalNumberingGenerator::Edge::appendConfigurationData(const AtomNode* node, ConnectionTable& ctab)
{
	if (!initConfigurationData(node))
		return;

	const Atom* ref_atoms[2] = { 0, 0 };

	for (std::size_t i = 0; i < 2; i++) {
		const AtomNode* cur_node = (i == 0 ? node : nbrNode);

		AtomNode::EdgeIterator edges_end = cur_node->getEdgesEnd();

		for (AtomNode::EdgeIterator it = cur_node->getEdgesBegin(); it != edges_end; ++it) {
			const Edge* edge = *it;

			if (edge->id == id)
				continue;

			ref_atoms[i] = edge->nbrNode->getAtom();
			break;
		}
	}

	ctab.push_back(node->getLabel());
	ctab.push_back(nbrNode->getLabel());

	if ((ref_atoms[0] == configRefAtoms[0]) ^ (ref_atoms[1] == configRefAtoms[1]))
		ctab.push_back(configuration == BondConfiguration::CIS ? BondConfiguration::TRANS : BondConfiguration::CIS);
	else
		ctab.push_back(configuration);
}

bool Chem::CanonicalNumberingGenerator::Edge::representsStereoBond(const AtomNode* node)
{
	return initConfigurationData(node);
}

std::size_t Chem::CanonicalNumberingGenerator::Edge::getID() const
{
	return id;
}

bool Chem::CanonicalNumberingGenerator::Edge::initConfigurationData(const AtomNode* node)
{
	if (configDataValid)
		return hasConfiguration;

	configDataValid = true;
	hasConfiguration = false;

	if (node->getNumEdges() < 2 || node->getNumEdges() > 3)
		return false;

	if (nbrNode->getNumEdges() < 2 || nbrNode->getNumEdges() > 3)
		return false;

	const StereoDescriptor& stereo_desc = getStereoDescriptor(*bond);
	configuration = stereo_desc.getConfiguration();

	if (configuration != BondConfiguration::CIS && configuration != BondConfiguration::TRANS)
		return false;

	if (!stereo_desc.isValid(*bond))
		return false;

	const Atom* const* sto_ref_atoms = stereo_desc.getReferenceAtoms();

	if (sto_ref_atoms[1] == nbrNode->getAtom() && sto_ref_atoms[2] == node->getAtom()) {
		configRefAtoms[0] = sto_ref_atoms[3];
		configRefAtoms[1] = sto_ref_atoms[0];

	} else {
		configRefAtoms[0] = sto_ref_atoms[0];
		configRefAtoms[1] = sto_ref_atoms[3];
	}

	hasConfiguration = true;

	return true;
}


bool Chem::CanonicalNumberingGenerator::Edge::LessCmpFunc::operator()(const Edge* edge1, const Edge* edge2) const
{
	std::size_t edge1_node_label = edge1->nbrNode->getLabel();
	std::size_t edge2_node_label = edge2->nbrNode->getLabel();

	if (edge1_node_label == edge2_node_label)
		return (edge1->label < edge2->label);

	return (edge1_node_label < edge2_node_label);
}
