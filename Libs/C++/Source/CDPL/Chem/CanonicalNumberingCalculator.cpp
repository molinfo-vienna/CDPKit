/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * CanonicalNumberingCalculator.cpp 
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
#include <cassert>

#include <boost/bind.hpp>

#include "CDPL/Chem/CanonicalNumberingCalculator.hpp"
#include "CDPL/Chem/Atom.hpp"
#include "CDPL/Chem/Bond.hpp"
#include "CDPL/Chem/AtomConfiguration.hpp"
#include "CDPL/Chem/BondConfiguration.hpp"
#include "CDPL/Chem/AtomFunctions.hpp"
#include "CDPL/Chem/BondFunctions.hpp"
#include "CDPL/Chem/MolecularGraphFunctions.hpp"
#include "CDPL/Chem/AtomType.hpp"
#include "CDPL/Internal/AtomFunctions.hpp"


namespace
{

	const std::size_t MAX_NODE_CACHE_SIZE = 1000;
	const std::size_t MAX_EDGE_CACHE_SIZE = 1000;
}


using namespace CDPL;


const unsigned int Chem::CanonicalNumberingCalculator::DEF_ATOM_PROPERTY_FLAGS;
const unsigned int Chem::CanonicalNumberingCalculator::DEF_BOND_PROPERTY_FLAGS;


Chem::CanonicalNumberingCalculator::CanonicalNumberingCalculator():
	nodeCache(MAX_NODE_CACHE_SIZE), edgeCache(MAX_EDGE_CACHE_SIZE), 
	atomPropertyFlags(DEF_ATOM_PROPERTY_FLAGS), bondPropertyFlags(DEF_BOND_PROPERTY_FLAGS), 
	hCountFunc(boost::bind(&Internal::getBondCount, _1, _2, 1, AtomType::H, true)) 
{}

Chem::CanonicalNumberingCalculator::CanonicalNumberingCalculator(const MolecularGraph& molgraph, Util::STArray& numbering):
	nodeCache(MAX_NODE_CACHE_SIZE), edgeCache(MAX_EDGE_CACHE_SIZE), 
	atomPropertyFlags(DEF_ATOM_PROPERTY_FLAGS), bondPropertyFlags(DEF_BOND_PROPERTY_FLAGS), 
	hCountFunc(boost::bind(&Internal::getBondCount, _1, _2, 1, AtomType::H, true))
{
	calculate(molgraph, numbering);
}

void Chem::CanonicalNumberingCalculator::setAtomPropertyFlags(unsigned int flags)
{
	atomPropertyFlags = flags;
}

unsigned int Chem::CanonicalNumberingCalculator::getAtomPropertyFlags() const
{
	return atomPropertyFlags;
}

void Chem::CanonicalNumberingCalculator::setBondPropertyFlags(unsigned int flags)
{
	bondPropertyFlags = flags;
}

unsigned int Chem::CanonicalNumberingCalculator::getBondPropertyFlags() const
{
	return bondPropertyFlags;
}

void Chem::CanonicalNumberingCalculator::setHydrogenCountFunction(const HydrogenCountFunction& func)
{
	hCountFunc = func;
}

const Chem::CanonicalNumberingCalculator::HydrogenCountFunction& 
Chem::CanonicalNumberingCalculator::getHydrogenCountFunction()
{
	return hCountFunc;
}

void Chem::CanonicalNumberingCalculator::calculate(const MolecularGraph& molgraph, Util::STArray& numbering)
{
	init(molgraph, numbering);
	canonicalize(molgraph, numbering);	
}

void Chem::CanonicalNumberingCalculator::init(const MolecularGraph& molgraph, Util::STArray& numbering)
{
	molGraph = &molgraph;

	std::size_t num_atoms = molgraph.getNumAtoms();
	std::size_t num_bonds = molgraph.getNumBonds();

	nodeCache.putAll();
	edgeCache.putAll();

	allocNodes.clear();
	allocNodes.reserve(num_atoms);

	allocEdges.clear();
	allocEdges.reserve(num_bonds * 2);

	compConnectionTables.clear();
	canonComponentList.clear();

	numbering.assign(num_atoms, 0);

	equivNodeStack.clear();
	nodeLabelingStack.clear();

	if ((atomPropertyFlags & AtomPropertyFlag::CONFIGURATION) || (bondPropertyFlags & BondPropertyFlag::CONFIGURATION))
		visitedEdgeMask.reset();

	MolecularGraph::ConstAtomIterator atoms_end = molgraph.getAtomsEnd();

	for (MolecularGraph::ConstAtomIterator it = molgraph.getAtomsBegin(); it != atoms_end; ++it) {
		const Atom& atom = *it;
		std::uint64_t atom_label = 0;

		if (atomPropertyFlags & AtomPropertyFlag::TYPE)
			atom_label = getType(atom);
		
		if (atomPropertyFlags & AtomPropertyFlag::ISOTOPE)
			atom_label = atom_label * AtomType::MAX_TYPE * 3 + getIsotope(atom);

		if (atomPropertyFlags & AtomPropertyFlag::H_COUNT)
			atom_label = atom_label * 10 + hCountFunc(atom, molgraph);

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

		if ((atomPropertyFlags & AtomPropertyFlag::CONFIGURATION) && hasCIPConfiguration(atom)) {
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

		allocNodes.push_back(allocNode(this, &atom, atom_label, allocNodes.size()));
	}

	std::size_t edge_id = allocEdges.size() / 2;

	MolecularGraph::ConstBondIterator bonds_end = molgraph.getBondsEnd();

	for (MolecularGraph::ConstBondIterator it = molgraph.getBondsBegin(); it != bonds_end; ++it) {
		const Bond& bond = *it;

		if (!molgraph.containsAtom(bond.getBegin()) || !molgraph.containsAtom(bond.getEnd()))
			continue;

		std::uint64_t bond_label = 0;

		AtomNode* atom_node1 = allocNodes[molgraph.getAtomIndex(bond.getBegin())];
		AtomNode* atom_node2 = allocNodes[molgraph.getAtomIndex(bond.getEnd())];

		if (bondPropertyFlags & BondPropertyFlag::AROMATICITY)
			bond_label = getAromaticityFlag(bond);

		if (bond_label == 0 && (bondPropertyFlags & BondPropertyFlag::ORDER))
			bond_label = getOrder(bond) + 2;
	
		if ((bondPropertyFlags & BondPropertyFlag::CONFIGURATION) && hasCIPConfiguration(bond)) {
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
	
		Edge* edge1 = allocEdge(this, &bond, bond_label, atom_node2, edge_id);
		Edge* edge2 = allocEdge(this, &bond, bond_label, atom_node1, edge_id++);

		allocEdges.push_back(edge1);
		allocEdges.push_back(edge2);

		atom_node1->addEdge(edge1);
		atom_node2->addEdge(edge2);
	}
}

void Chem::CanonicalNumberingCalculator::setup(const MolecularGraph& comp)
{
	nodeList.clear();
	nodeList.reserve(comp.getNumAtoms());

	compConnectionTables.push_back(ConnectionTable());
	levelConnectionTables.clear();

	MolecularGraph::ConstAtomIterator atoms_end = comp.getAtomsEnd();

	std::size_t edge_id = allocEdges.size() / 2;

	for (MolecularGraph::ConstAtomIterator it = comp.getAtomsBegin(); it != atoms_end; ++it) {
		const Atom& atom = *it;
		AtomNode* atom_node = allocNodes[molGraph->getAtomIndex(atom)];

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

void Chem::CanonicalNumberingCalculator::canonicalize(const MolecularGraph& molgraph, Util::STArray& numbering)
{
	if (!hasComponents(molgraph) || getComponents(molgraph)->getSize() <= 1) {
		if (molgraph.getNumAtoms() == 0)
			return;

		setup(molgraph);
		canonicalize(0);
		establishCanonNumbering(numbering);
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
		establishCanonNumbering(numbering);
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

			numbering[molgraph.getAtomIndex(atom)] += comp_offset;
		}

		comp_offset += comp->getNumAtoms();
	}
}

void Chem::CanonicalNumberingCalculator::canonicalize(std::size_t depth)
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

void Chem::CanonicalNumberingCalculator::processNewSolution()
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

int Chem::CanonicalNumberingCalculator::testNewSolution()
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

void Chem::CanonicalNumberingCalculator::buildConnectionTable(ConnectionTable& ctab) const
{
	ctab.clear();

	std::for_each(nodeList.begin(), nodeList.end(), 
				  boost::bind(&AtomNode::appendConnectivityData, _1, boost::ref(ctab)));
}

void Chem::CanonicalNumberingCalculator::appendAtomConfigs(ConnectionTable& ctab)
{
	std::size_t old_ctab_size = ctab.size();

	std::for_each(nodeList.begin(), nodeList.end(), 
				  boost::bind(&AtomNode::appendAtomConfigData, _1, boost::ref(ctab)));

	foundStereogenicAtoms = (old_ctab_size != ctab.size());
}

void Chem::CanonicalNumberingCalculator::appendBondConfigs(ConnectionTable& ctab)
{
	std::size_t old_ctab_size = ctab.size();

	std::for_each(nodeList.begin(), nodeList.end(), 
				  boost::bind(&AtomNode::appendBondConfigData, _1, boost::ref(ctab)));

	foundStereogenicBonds = (old_ctab_size != ctab.size());
}

void Chem::CanonicalNumberingCalculator::establishCanonNumbering(Util::STArray& numbering)
{
	NodeList::const_iterator nodes_end = minNodeList.end();
	std::size_t canon_number = 1;

	for (NodeList::const_iterator n_it = minNodeList.begin(); n_it != nodes_end; ++n_it) {
		const Atom* atom = (*n_it)->getAtom();

		numbering[molGraph->getAtomIndex(*atom)] = canon_number++;
	}
}

void Chem::CanonicalNumberingCalculator::saveState()
{
	nodeLabelingStack.reserve(nodeLabelingStack.size() + nodeList.size());

	for (NodeList::const_iterator it = nodeList.begin(), end = nodeList.end(); it != end; ++it)
		nodeLabelingStack.push_back(std::make_pair(*it, (*it)->getLabel()));
}

void Chem::CanonicalNumberingCalculator::restoreState()
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

Chem::CanonicalNumberingCalculator::AtomNode* 
Chem::CanonicalNumberingCalculator::allocNode(Calculator* calculator, const Atom* atom, std::uint64_t label, std::size_t id)
{
	AtomNode* node = nodeCache.getRaw();

	node->init(calculator, atom, label, id);

	return node;
}

Chem::CanonicalNumberingCalculator::Edge* 
Chem::CanonicalNumberingCalculator::allocEdge(const Calculator* calculator, const Bond* bond, std::uint64_t label,
											 AtomNode* nbr_node, std::size_t id)
{
	Edge* edge = edgeCache.getRaw();

	edge->init(calculator, bond, label, nbr_node, id);

	return edge;
}


bool Chem::CanonicalNumberingCalculator::ComponentCmpFunc::operator()(const CanonComponentInfo& info1, 
																	 const CanonComponentInfo& info2) const
{
	if (info1.second->size() == info2.second->size())
		return std::lexicographical_compare(info1.second->begin(), info1.second->end(),
											info2.second->begin(), info2.second->end());

	return (info1.second->size() > info2.second->size());
}


//---------

Chem::CanonicalNumberingCalculator::AtomNode::AtomNode(): 
	stereoDescr(AtomConfiguration::NONE) 
{}

void Chem::CanonicalNumberingCalculator::AtomNode::init(Calculator* calculator, const Atom* atom, std::uint64_t label, std::size_t id)
{
	this->calculator = calculator;
	this->atom = atom;
	initialLabel = label;
	this->label = label;
	newLabel = label;
	this->id = id;
	stereoDescr = StereoDescriptor(AtomConfiguration::NONE);
	configDataValid = false;
	partOfStereocenterValid = false;

	equivNodeMask.clear();
	edges.clear();
}

const Chem::Atom* Chem::CanonicalNumberingCalculator::AtomNode::getAtom() const
{
	return atom;
}

void Chem::CanonicalNumberingCalculator::AtomNode::addEdge(Edge* edge)
{
	edges.push_back(edge);
}

void Chem::CanonicalNumberingCalculator::AtomNode::setLabel(std::uint64_t l)
{
	label = l;
}

std::uint64_t Chem::CanonicalNumberingCalculator::AtomNode::getLabel() const
{
	return label;
}

void Chem::CanonicalNumberingCalculator::AtomNode::setNewLabel(std::size_t l)
{
	newLabel = l;
}

void Chem::CanonicalNumberingCalculator::AtomNode::updateLabel()
{
	label = newLabel;
}

std::size_t Chem::CanonicalNumberingCalculator::AtomNode::getID() const
{
	return id;
}

void Chem::CanonicalNumberingCalculator::AtomNode::sortEdges()
{
	std::sort(edges.begin(), edges.end(), Edge::LessCmpFunc());
}

std::size_t Chem::CanonicalNumberingCalculator::AtomNode::getNumEdges() const
{
	return edges.size();
}

Chem::CanonicalNumberingCalculator::AtomNode::EdgeIterator 
Chem::CanonicalNumberingCalculator::AtomNode::getEdgesBegin() const
{
	return edges.begin();
}

Chem::CanonicalNumberingCalculator::AtomNode::EdgeIterator 
Chem::CanonicalNumberingCalculator::AtomNode::getEdgesEnd() const
{
	return edges.end();
}

void Chem::CanonicalNumberingCalculator::AtomNode::appendConnectivityData(ConnectionTable& ctab) const
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

void Chem::CanonicalNumberingCalculator::AtomNode::appendAtomConfigData(ConnectionTable& ctab)
{
	if (!initConfigurationData())
		return;

	std::size_t num_edges = edges.size();

	assert(num_edges == 3 || num_edges == 4);

	std::size_t perm_pty = (num_edges == 3 ? stereoDescr.getPermutationParity(*edges[0]->getNeighborNode()->atom, *edges[1]->getNeighborNode()->atom, *edges[2]->getNeighborNode()->atom) :
							stereoDescr.getPermutationParity(*edges[0]->getNeighborNode()->atom, *edges[1]->getNeighborNode()->atom, *edges[2]->getNeighborNode()->atom, *edges[3]->getNeighborNode()->atom));

	if (perm_pty != 1 && perm_pty != 2) {
		hasConfiguration = false;
		return;
	}

	ctab.push_back(label);

	if (perm_pty == 2) 
		ctab.push_back(stereoDescr.getConfiguration());
	else
		ctab.push_back(stereoDescr.getConfiguration() == AtomConfiguration::R ? AtomConfiguration::S : AtomConfiguration::R);
}

void Chem::CanonicalNumberingCalculator::AtomNode::appendBondConfigData(ConnectionTable& ctab) const
{
	EdgeList::const_iterator edges_end = edges.end();

	for (EdgeList::const_iterator it = edges.begin(); it != edges_end; ++it) {
		Edge* edge = *it;
		
		if (edge->getNeighborNode()->getLabel() > label)
			edge->appendConfigurationData(this, ctab);
	}
}

bool Chem::CanonicalNumberingCalculator::AtomNode::terminalAndOnCommonNonStereoNode(const AtomNode* node1, const AtomNode* node2)
{
	if (node1->edges.size() == 1 && node2->edges.size() == 1) { // special treatment for terminal nodes -> speedup
		AtomNode* node1_nbr = node1->edges.front()->getNeighborNode();
		AtomNode* node2_nbr = node2->edges.front()->getNeighborNode();

		return (node1_nbr == node2_nbr && !node1_nbr->involvedInStereocenter());
	}

	return false;
}

bool Chem::CanonicalNumberingCalculator::AtomNode::isEquivalent(const AtomNode* node) const
{
	if (equivNodeMask.size() <= node->id)
		return false;

	return equivNodeMask.test(node->id);
}

void Chem::CanonicalNumberingCalculator::AtomNode::addToEquivalenceSet(const AtomNode* node)
{
	if (equivNodeMask.size() <= node->id)
		equivNodeMask.resize(node->id + 1);

	equivNodeMask.set(node->id);
}

bool Chem::CanonicalNumberingCalculator::AtomNode::involvedInStereocenter() 
{
	if (partOfStereocenterValid)
		return partOfStereocenter;

	partOfStereocenterValid = true;
	partOfStereocenter = false;

	if (calculator->bondPropertyFlags & BondPropertyFlag::CONFIGURATION) {
		EdgeList::const_iterator edges_end = edges.end();

		for (EdgeList::const_iterator it = edges.begin(); it != edges_end; ++it) {
			if ((*it)->representsStereoBond(this)) {
				partOfStereocenter = true;
				return true;
			}
		}
	}

	if (calculator->atomPropertyFlags & AtomPropertyFlag::CONFIGURATION)
		partOfStereocenter = initConfigurationData();

	return partOfStereocenter;
}

bool Chem::CanonicalNumberingCalculator::AtomNode::initConfigurationData()
{
	if (configDataValid)
		return hasConfiguration;

	configDataValid = true;
	hasConfiguration = false;

	std::size_t num_edges = edges.size();

	if (num_edges < 3 || num_edges > 4)
		return false;

	stereoDescr = getStereoDescriptor(*atom);

	if (stereoDescr.getConfiguration() != AtomConfiguration::R && stereoDescr.getConfiguration() != AtomConfiguration::S)
		return false;

	if (!stereoDescr.isValid(*atom))
		return false;

	hasConfiguration = true;
	return true;
}


bool Chem::CanonicalNumberingCalculator::AtomNode::LessCmpFunc::operator()(const AtomNode* node1, 
																		  const AtomNode* node2) const
{
	if (node1->label == node2->label)
		return std::lexicographical_compare(node1->edges.begin(), node1->edges.end(),
											node2->edges.begin(), node2->edges.end(),
											Edge::LessCmpFunc());
	return (node1->label < node2->label);
}


//---------

Chem::CanonicalNumberingCalculator::Edge::Edge(): 
	stereoDescr(BondConfiguration::NONE) 
{}

void Chem::CanonicalNumberingCalculator::Edge::init(const Calculator* calculator, const Bond* bond, std::uint64_t label, 
												   AtomNode* nbr_node, std::size_t id)
{
	this->calculator = calculator; 
	this->bond = bond; 
	nbrNode = nbr_node; 
	this->label = label; 
	this->id = id; 
	stereoDescr = StereoDescriptor(BondConfiguration::NONE);
	configDataValid = false;
}

Chem::CanonicalNumberingCalculator::AtomNode* Chem::CanonicalNumberingCalculator::Edge::getNeighborNode() const
{
	return nbrNode;
}

void Chem::CanonicalNumberingCalculator::Edge::appendBondData(ConnectionTable& ctab) const
{
	ctab.push_back(nbrNode->getLabel());
	ctab.push_back(label);
}

void Chem::CanonicalNumberingCalculator::Edge::appendConfigurationData(const AtomNode* node, ConnectionTable& ctab)
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

	if ((ref_atoms[0] == stereoDescr.getReferenceAtoms()[0]) ^ (ref_atoms[1] == stereoDescr.getReferenceAtoms()[3]))
		ctab.push_back(stereoDescr.getConfiguration() == BondConfiguration::CIS ? BondConfiguration::TRANS : BondConfiguration::CIS);
	else
		ctab.push_back(stereoDescr.getConfiguration());
}

bool Chem::CanonicalNumberingCalculator::Edge::representsStereoBond(const AtomNode* node)
{
	return initConfigurationData(node);
}

std::size_t Chem::CanonicalNumberingCalculator::Edge::getID() const
{
	return id;
}

bool Chem::CanonicalNumberingCalculator::Edge::initConfigurationData(const AtomNode* node)
{
	if (configDataValid)
		return hasConfiguration;

	configDataValid = true;
	hasConfiguration = false;

	if (node->getNumEdges() < 2 || node->getNumEdges() > 3)
		return false;

	if (nbrNode->getNumEdges() < 2 || nbrNode->getNumEdges() > 3)
		return false;

	stereoDescr = getStereoDescriptor(*bond);

	if (stereoDescr.getConfiguration() != BondConfiguration::CIS && stereoDescr.getConfiguration() != BondConfiguration::TRANS)
		return false;

	if (!stereoDescr.isValid(*bond))
		return false;

	const Atom* const* sto_ref_atoms = stereoDescr.getReferenceAtoms();

	if (sto_ref_atoms[1] == nbrNode->getAtom() && sto_ref_atoms[2] == node->getAtom()) 
		stereoDescr = StereoDescriptor(stereoDescr.getConfiguration(), *sto_ref_atoms[3], *sto_ref_atoms[2], *sto_ref_atoms[1], *sto_ref_atoms[0]);

	hasConfiguration = true;

	return true;
}


bool Chem::CanonicalNumberingCalculator::Edge::LessCmpFunc::operator()(const Edge* edge1, const Edge* edge2) const
{
	std::size_t edge1_node_label = edge1->nbrNode->getLabel();
	std::size_t edge2_node_label = edge2->nbrNode->getLabel();

	if (edge1_node_label == edge2_node_label)
		return (edge1->label < edge2->label);

	return (edge1_node_label < edge2_node_label);
}
