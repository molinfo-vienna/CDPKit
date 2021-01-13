/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * Atom2DCoordinatesGenerator.cpp 
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

#include <functional>
#include <algorithm>
#include <numeric>
#include <iterator>
#include <cmath>
#include <limits>
#include <cassert>

#include <boost/random/linear_congruential.hpp>

#define BOOST_BIND_GLOBAL_PLACEHOLDERS
#include <boost/bind.hpp>

#include "CDPL/Chem/Atom2DCoordinatesGenerator.hpp"
#include "CDPL/Chem/Atom.hpp"
#include "CDPL/Chem/Bond.hpp"
#include "CDPL/Chem/StereoDescriptor.hpp"
#include "CDPL/Chem/MolecularGraphFunctions.hpp"
#include "CDPL/Chem/AtomFunctions.hpp"
#include "CDPL/Chem/BondFunctions.hpp"
#include "CDPL/Chem/HybridizationState.hpp"
#include "CDPL/Chem/BondConfiguration.hpp"
#include "CDPL/Chem/AtomType.hpp"
#include "CDPL/Math/SpecialFunctions.hpp"
#include "CDPL/Internal/AddressOf.hpp"


using namespace CDPL;


namespace
{

	class PriorityCountPred : std::unary_function<std::size_t, bool>
	{

	public:
		PriorityCountPred(): currPriority(0) {}

		bool operator()(std::size_t priority) {
			if (priority != currPriority) {
				currPriority = priority;

				return true;
			}

			return false;
		}
		 
	private:
		std::size_t currPriority;
	};


	double calcAngle(const Math::Vector2D& v)
	{
		double ang = std::acos(v(0) / norm2(v));

		return (v(1) >= 0.0 ? ang : 2.0 * M_PI - ang);
	}

	Math::Vector2D& calcPosition(const Math::Vector2D& org, double r, double angle, Math::Vector2D& res)
	{
		res(0) = r * std::cos(angle) + org(0);
		res(1) = r * std::sin(angle) + org(1);

		return res;
	}

	int ccw(const Math::Vector2D& p0, const Math::Vector2D& p1, const Math::Vector2D& p2)
	{
		double dx1 = p1(0) - p0(0);
		double dy1 = p1(1) - p0(1);
		double dx2 = p2(0) - p0(0);
		double dy2 = p2(1) - p0(1);

		if (dy1 * dx2 < dy2 * dx1)
			return 1;

		if (dy1 * dx2 > dy2 * dx1)
			return -1;

		if (dx1 * dx2 < 0 || dy1 * dy2 < 0)
			return -1;

		if ((dx1 * dx1 + dy1 * dy1) >= (dx2 * dx2 + dy2 * dy2))
			return 0;
		else
			return 1;
	}

	const double      DEF_BOND_LENGTH               = 25.0;
	const double      H_BOND_LENGTH                 = DEF_BOND_LENGTH * 0.7;
	const double      BOND_LENGTH_DELTA             = DEF_BOND_LENGTH * 0.26;
	const double      ANGLE_BENDING_DELTA           = 20.0 * M_PI / 180.0;
	const double      ATOM_COLLISION_TEST_DIST      = DEF_BOND_LENGTH * 0.3;
	const double      ATOM_BOND_COLLISION_TEST_DIST = DEF_BOND_LENGTH * 0.2;
	const double      COMPONENT_X_SPACING           = DEF_BOND_LENGTH;
	const double      COMPONENT_Y_SPACING           = DEF_BOND_LENGTH;
	const std::size_t BACKTRACKING_LIMIT            = 200;

	const std::size_t MAX_EDGE_CACHE_SIZE          = 5000;
	const std::size_t MAX_ATOM_NODE_CACHE_SIZE     = 5000;
	const std::size_t MAX_RING_SYS_NODE_CACHE_SIZE = 100;
	const std::size_t MAX_RING_INFO_CACHE_SIZE     = 200;
}


class Chem::Atom2DCoordinatesGenerator::AtomNode::EdgePriorityGreaterCmpFunc : 
	public std::binary_function<const LGEdge*, const LGEdge*, bool>
{

public:
	EdgePriorityGreaterCmpFunc(const LGNode* org): origin(org), chainID(org->getChainID()) {}

	bool operator()(const LGEdge* lhs_edge, const LGEdge* rhs_edge) const {
		std::size_t lhs_chain_id = lhs_edge->otherNode(origin)->getChainID();
		std::size_t rhs_chain_id = rhs_edge->otherNode(origin)->getChainID();

		if (lhs_chain_id == rhs_chain_id)
			return false;

		if (chainID == lhs_chain_id)
			return true;

		if (chainID == rhs_chain_id)
			return false;

		return (lhs_chain_id < rhs_chain_id);
	} 
		 
private:
	const LGNode* origin;
	std::size_t   chainID;
};


class Chem::Atom2DCoordinatesGenerator::AtomNode::LinkedNodePriorityLessCmpFunc : 
	public std::binary_function<const LGEdge*, const LGEdge*, bool>
{

public:
	LinkedNodePriorityLessCmpFunc(const LGNode* org): origin(org) {}

	bool operator()(const LGEdge* lhs_edge, const LGEdge* rhs_edge) const {
		return (lhs_edge->otherNode(origin)->getPriority() < rhs_edge->otherNode(origin)->getPriority());
	} 
		 
private:
	const LGNode* origin;
};


class Chem::Atom2DCoordinatesGenerator::AtomNode::LinkedNodePriorityEqualCmpFunc : 
	public std::binary_function<const LGEdge*, const LGEdge*, bool>
{

public:
	LinkedNodePriorityEqualCmpFunc(const LGNode* org): origin(org) {}

	bool operator()(const LGEdge* lhs_edge, const LGEdge* rhs_edge) const {
		return (lhs_edge->otherNode(origin)->getPriority() == rhs_edge->otherNode(origin)->getPriority());
	} 
		 
private:
	const LGNode* origin;
};


class Chem::Atom2DCoordinatesGenerator::LGNode::NodeLayoutInfoListEqualCmpFunc : 
	public std::unary_function<Chem::Atom2DCoordinatesGenerator::LGNode::NodeLayoutInfoList, bool>
{

public:
	NodeLayoutInfoListEqualCmpFunc(const LGNode* org, const NodeLayoutInfoList& lhs_list): 
		origin(org), lhsList(lhs_list) {}

	bool operator()(const NodeLayoutInfoList& rhs_list) const {
		assert(rhs_list.size() == lhsList.size());

		return std::equal(lhsList.begin(), lhsList.end(), rhs_list.begin(),
						  boost::bind(LinkedNodePriorityEqualCmpFunc(origin), 
									  boost::bind(&NodeLayoutInfo::edge, _1),
									  boost::bind(&NodeLayoutInfo::edge, _2)));
	}
		 
private:
	const LGNode*             origin;
	const NodeLayoutInfoList& lhsList;
};


Chem::Atom2DCoordinatesGenerator::Atom2DCoordinatesGenerator():
	ringInfoCache(MAX_RING_INFO_CACHE_SIZE), ringSysNodeCache(MAX_RING_SYS_NODE_CACHE_SIZE), 
	atomNodeCache(MAX_ATOM_NODE_CACHE_SIZE), edgeCache(MAX_EDGE_CACHE_SIZE)
{
}

Chem::Atom2DCoordinatesGenerator::Atom2DCoordinatesGenerator(const MolecularGraph& molgraph, Math::Vector2DArray& coords):
	ringInfoCache(MAX_RING_INFO_CACHE_SIZE), ringSysNodeCache(MAX_RING_SYS_NODE_CACHE_SIZE), 
	atomNodeCache(MAX_ATOM_NODE_CACHE_SIZE), edgeCache(MAX_EDGE_CACHE_SIZE)
{
	generate(molgraph, coords);
}

void Chem::Atom2DCoordinatesGenerator::generate(const MolecularGraph& molgraph, Math::Vector2DArray& coords)
{
	init(molgraph, coords);

	extractRingInformation();
	calcAtomPriorities();
	calcRingPriorities();

	layoutComponents(coords);
	alignComponents(coords);
}

void Chem::Atom2DCoordinatesGenerator::init(const MolecularGraph& molgraph, Math::Vector2DArray& coords)
{
	molGraph = &molgraph;

	numAtoms = molgraph.getNumAtoms();
	numBonds = molgraph.getNumBonds();
	
	coords.resize(numAtoms);

	atomMask.resize(numAtoms);
	atomMask.reset();

	atomNodeTable.assign(numAtoms, 0);
}

void Chem::Atom2DCoordinatesGenerator::extractRingInformation()
{
	freeAllocRingInfos();

	if (numAtoms > ringAtomMask.size())
		ringAtomMask.resize(numAtoms);

	ringAtomMask.reset();

	const FragmentList& sssr = *getSSSR(*molGraph);
	FragmentList::ConstElementIterator sssr_end = sssr.getElementsEnd();

	for (FragmentList::ConstElementIterator it = sssr.getElementsBegin(); it != sssr_end; ++it) {
		const RingInfo* ring_info = allocRingInfo(*it);

		ringAtomMask |= ring_info->getAtomMask();
	}
}

void Chem::Atom2DCoordinatesGenerator::calcAtomPriorities()
{
	if (numAtoms > atomPriorityTable.size())
		atomPriorityTable.resize(numAtoms);

	for (std::size_t i = 0; i < numAtoms; i++)
		atomPriorityTable[i] = (ringAtomMask.test(i) ? 3 : 1);

	MolecularGraph::ConstAtomIterator atoms_beg = molGraph->getAtomsBegin();
	MolecularGraph::ConstAtomIterator atoms_end = molGraph->getAtomsEnd();

	AtomPriorityTable new_priorities(numAtoms);

	std::size_t num_classes = 0;

	while (true) {
		std::size_t i = 0;

		for (MolecularGraph::ConstAtomIterator a_it1 = atoms_beg; a_it1 != atoms_end; ++a_it1, i++) {
			const Atom& atom = *a_it1;
			std::size_t new_priority = 3 * atomPriorityTable[i];

			Atom::ConstAtomIterator nbr_atoms_end = atom.getAtomsEnd();
			Atom::ConstBondIterator b_it = atom.getBondsBegin();

			for (Atom::ConstAtomIterator a_it2 = atom.getAtomsBegin(); a_it2 != nbr_atoms_end; ++a_it2, ++b_it) {
				if (!molGraph->containsAtom(*a_it2) || !molGraph->containsBond(*b_it))
					continue;

				new_priority += atomPriorityTable[molGraph->getAtomIndex(*a_it2)];
			}

			new_priorities[i] = new_priority;
		}

		atomPriorityTable = new_priorities;

		std::sort(new_priorities.begin(), new_priorities.end());

		std::size_t new_num_classes = std::count_if(new_priorities.begin(), new_priorities.end(), PriorityCountPred());

		if (new_num_classes <= num_classes)
			break;

		num_classes = new_num_classes;
	}
}

void Chem::Atom2DCoordinatesGenerator::calcRingPriorities()
{
	RingInfoList::iterator rings_end = ringList.end();

	for (RingInfoList::iterator it = ringList.begin(); it != rings_end; ++it) {
		RingInfo& ring_info = **it;
		const Fragment& ring_frag = ring_info.getFragment();

		double priority = 0.0;

		Fragment::ConstAtomIterator atoms_end = ring_frag.getAtomsEnd();

		for (Fragment::ConstAtomIterator a_it = ring_frag.getAtomsBegin(); a_it != atoms_end; ++a_it)
			priority += atomPriorityTable[molGraph->getAtomIndex(*a_it)];

		ring_info.setPriority(priority/* / ring_info->getSize()*/);
	}
}

void Chem::Atom2DCoordinatesGenerator::layoutComponents(Math::Vector2DArray& coords)
{
	const FragmentList& components = *getComponents(*molGraph);

	std::for_each(components.getElementsBegin(), components.getElementsEnd(), 
				  boost::bind(&Atom2DCoordinatesGenerator::layoutComponent, this, _1, boost::ref(coords)));
}

void Chem::Atom2DCoordinatesGenerator::alignComponents(Math::Vector2DArray& coords)
{
	const FragmentList& components = *getComponents(*molGraph);

	std::size_t row_size = std::size_t(std::ceil(std::sqrt(double(components.getSize()))));

	std::vector<BoundingBox> comp_bounds(row_size);
	double row_y_pos = 0.0;

	FragmentList::ConstElementIterator comps_end = components.getElementsEnd();

	for (FragmentList::ConstElementIterator it = components.getElementsBegin(); it != comps_end; ) {
		double row_x_dim = 0.0;
		double row_y_dim = 0.0; 

		std::size_t i = 0;

		for (FragmentList::ConstElementIterator it2 = it; i < row_size && it2 != comps_end; i++, ++it2) {
			BoundingBox& bbox = comp_bounds[i];

			calcBounds(bbox, *it2, coords);

			row_x_dim += bbox.second[0] - bbox.first[0] + COMPONENT_X_SPACING;
			row_y_dim = std::max(row_y_dim, bbox.second[1] - bbox.first[1]);
		}

		double comp_x_pos = -0.5 * (row_x_dim - COMPONENT_X_SPACING);
		double comp_y_pos = row_y_pos + 0.5 * row_y_dim;

		for (std::size_t j = 0; j < i; j++, ++it) {
			const BoundingBox& bbox = comp_bounds[j];
			double x_dim = bbox.second[0] - bbox.first[0];

			moveComponent(bbox, comp_x_pos + 0.5 * x_dim, comp_y_pos, *it, coords);

			comp_x_pos += x_dim + COMPONENT_X_SPACING;
		}

		row_y_pos += row_y_dim + COMPONENT_Y_SPACING;
	}
}

void Chem::Atom2DCoordinatesGenerator::addPoint(BoundingBox& bbox, const Math::Vector2D& pt) const
{
	bbox.first[0] = std::min(pt[0], bbox.first[0]);
	bbox.first[1] = std::min(pt[1], bbox.first[1]);

	bbox.second[0] = std::max(pt[0], bbox.second[0]);
	bbox.second[1] = std::max(pt[1], bbox.second[1]);
}

void Chem::Atom2DCoordinatesGenerator::calcBounds(BoundingBox& bbox, const Fragment& comp, Math::Vector2DArray& coords) const
{
	bbox.first.clear();
	bbox.second.clear();

	Fragment::ConstAtomIterator atoms_end = comp.getAtomsEnd();

	for (Fragment::ConstAtomIterator it = comp.getAtomsBegin(); it != atoms_end; ++it)
		addPoint(bbox, coords[molGraph->getAtomIndex(*it)]);
}

void Chem::Atom2DCoordinatesGenerator::moveComponent(const BoundingBox& bbox, double x_pos, double y_pos, const Fragment& comp, Math::Vector2DArray& coords)
{
	Math::Vector2D t;
	
	t[0] = x_pos - 0.5 * (bbox.first[0] + bbox.second[0]);
	t[1] = y_pos - 0.5 * (bbox.first[1] + bbox.second[1]);

	Fragment::ConstAtomIterator atoms_end = comp.getAtomsEnd();

	for (Fragment::ConstAtomIterator it = comp.getAtomsBegin(); it != atoms_end; ++it)
		coords[molGraph->getAtomIndex(*it)] += t;
}

void Chem::Atom2DCoordinatesGenerator::layoutComponent(const Fragment& comp, Math::Vector2DArray& coords)
{
	createLayoutTree(comp, coords);

	layoutNodes();
}

void Chem::Atom2DCoordinatesGenerator::createLayoutTree(const Fragment& comp, Math::Vector2DArray& coords)
{
	createRingSysNodes(comp, coords);
	createAtomNodes(comp, coords);

	freeAllocEdges();
	createBondEdges(comp);
	createSpiroEdges(comp);

	setAtomNodeChainIDs();
	initNodes();
	createBFSNodeList();
}

void Chem::Atom2DCoordinatesGenerator::createRingSysNodes(const Fragment& comp, Math::Vector2DArray& coords)
{
	freeAllocRingSysNodes();
	tmpRingList.clear();

	std::for_each(comp.getAtomsBegin(), comp.getAtomsEnd(), 
				  boost::bind(&Util::BitSet::set, &atomMask, 
							  boost::bind(&MolecularGraph::getAtomIndex, molGraph, _1), true));

	RingInfoList::iterator rings_end = ringList.end();

	for (RingInfoList::iterator it = ringList.begin(); it != rings_end; ) {
		tmpBitMask = (*it)->getAtomMask();
		tmpBitMask &= atomMask;

		if (tmpBitMask.any()) {
			tmpRingList.push_back(*it);
			ringList.erase(it++);

		} else
			++it;
	}

	RingInfoList::iterator comp_rings_end = tmpRingList.end();

	for (RingInfoList::iterator it = tmpRingList.begin(); it != comp_rings_end; ) {
		RingSysNode* rsys_node = allocRingSysNode(*it, coords);

		tmpRingList.erase(it++);		

		while (true) {
			bool added_ring = false;

			for (RingInfoList::iterator it2 = it; it2 != comp_rings_end; ) {
				if (rsys_node->addRing(*it2)) {
					if (it == it2) {
						tmpRingList.erase(it2++);
						it = it2;

					} else
						tmpRingList.erase(it2++);

					added_ring = true;

				} else
					++it2;
			}
			
			if (!added_ring)
				break;
		}
	}
}

void Chem::Atom2DCoordinatesGenerator::createAtomNodes(const Fragment& comp, Math::Vector2DArray& coords)
{
	freeAllocAtomNodes();

	Fragment::ConstAtomIterator atoms_end = comp.getAtomsEnd();

	for (Fragment::ConstAtomIterator it = comp.getAtomsBegin(); it != atoms_end; ++it) {
		const Atom& atom = *it;
		std::size_t atom_idx = molGraph->getAtomIndex(atom);

		if (ringAtomMask.test(atom_idx))
			continue;

		atomNodeTable[atom_idx] = allocAtomNode(&atom, coords);
	}
}

void Chem::Atom2DCoordinatesGenerator::createBondEdges(const Fragment& comp)
{
	std::size_t num_mol_atoms = molGraph->getNumAtoms();

	if (tmpBitMask.size() < num_mol_atoms * num_mol_atoms)
		tmpBitMask.resize(num_mol_atoms * num_mol_atoms);

	tmpBitMask.reset();

	Fragment::ConstBondIterator bonds_end = comp.getBondsEnd();

	RingSysNodeList::iterator rsys_list_beg = ringSysNodeList.begin();
	RingSysNodeList::iterator rsys_list_end = ringSysNodeList.end();

	for (Fragment::ConstBondIterator it = comp.getBondsBegin(); it != bonds_end; ++it) {
		const Bond* bond = &*it;
		const Atom* atom1 = &bond->getBegin();
		const Atom* atom2 = &bond->getEnd();

		if (atom1 == atom2) // satity check
			continue;

		std::size_t atom1_idx = molGraph->getAtomIndex(*atom1);
		std::size_t atom2_idx = molGraph->getAtomIndex(*atom2);

		if (tmpBitMask.test(atom1_idx * num_mol_atoms + atom2_idx))
			continue;

		tmpBitMask.set(atom1_idx * num_mol_atoms + atom2_idx);
		tmpBitMask.set(atom2_idx * num_mol_atoms + atom1_idx);

		if (atomNodeTable[atom1_idx]) {
			if (atomNodeTable[atom2_idx]) {
				const LGEdge* edge = allocEdge(bond, atomNodeTable[atom1_idx], atomNodeTable[atom2_idx]);

				atomNodeTable[atom1_idx]->addEdge(atom1, edge);
				atomNodeTable[atom2_idx]->addEdge(atom2, edge);

			} else {
				RingSysNodeList::iterator rsys_it = std::find_if(rsys_list_beg, rsys_list_end, 
																	boost::bind(&RingSysNode::containsAtom, _1, atom2_idx));
				if (rsys_it == rsys_list_end)
					continue;

				LGNode* rsys = *rsys_it;
				const LGEdge* edge = allocEdge(bond, atomNodeTable[atom1_idx], rsys);

				rsys->addEdge(atom2, edge);
				atomNodeTable[atom1_idx]->addEdge(atom1, edge);
	
				while ((rsys_it = std::find_if(++rsys_it, rsys_list_end, 
											   boost::bind(&RingSysNode::containsAtom, _1, atom2_idx))) != rsys_list_end) {
					rsys = *rsys_it;
					edge = allocEdge(bond, atomNodeTable[atom1_idx], rsys);

					rsys->addEdge(atom2, edge);
				} 
			}

		} else if (atomNodeTable[atom2_idx]) {
			RingSysNodeList::iterator rsys_it = std::find_if(rsys_list_beg, rsys_list_end, 
																boost::bind(&RingSysNode::containsAtom, _1, atom1_idx));
			if (rsys_it == rsys_list_end)
				continue;

			LGNode* rsys = *rsys_it;
			const LGEdge* edge = allocEdge(bond, atomNodeTable[atom2_idx], rsys);

			rsys->addEdge(atom1, edge);
			atomNodeTable[atom2_idx]->addEdge(atom2, edge);

			while ((rsys_it = std::find_if(++rsys_it, rsys_list_end, 
										   boost::bind(&RingSysNode::containsAtom, _1, atom1_idx))) != rsys_list_end) {
				rsys = *rsys_it;
				edge = allocEdge(bond, atomNodeTable[atom2_idx], rsys);

				rsys->addEdge(atom1, edge);
			} 

		} else if (!getRingFlag(*bond)) {
			RingSysNodeList::iterator rsys_it1 = std::find_if(rsys_list_beg, rsys_list_end, 
																 boost::bind(&RingSysNode::containsAtom, _1, atom1_idx));
			if (rsys_it1 == rsys_list_end)
				continue;

			RingSysNodeList::iterator rsys_it2 = std::find_if(rsys_list_beg, rsys_list_end, 
																 boost::bind(&RingSysNode::containsAtom, _1, atom2_idx));
			if (rsys_it2 == rsys_list_end)
				continue;

			RingSysNode* rsys1 = *rsys_it1;
			RingSysNode* rsys2 = *rsys_it2;

			const LGEdge* edge = allocEdge(bond, rsys1, rsys2);

			rsys1->addEdge(atom1, edge);
			rsys2->addEdge(atom2, edge);

			while ((rsys_it1 = std::find_if(++rsys_it1, rsys_list_end, 
											boost::bind(&RingSysNode::containsAtom, _1, atom1_idx))) != rsys_list_end) {
				RingSysNode* rsys = *rsys_it1;
				edge = allocEdge(bond, rsys, rsys2);

				rsys->addEdge(atom1, edge);
			} 

			while ((rsys_it2 = std::find_if(++rsys_it2, rsys_list_end, 
											boost::bind(&RingSysNode::containsAtom, _1, atom2_idx))) != rsys_list_end) {
				RingSysNode* rsys = *rsys_it2;
				edge = allocEdge(bond, rsys1, rsys);

				rsys->addEdge(atom2, edge);
			} 
		}
	}
}

void Chem::Atom2DCoordinatesGenerator::createSpiroEdges(const Fragment& comp)
{
	RingSysNodeList::iterator rsys_list_end = ringSysNodeList.end();

	for (RingSysNodeList::iterator it1 = ringSysNodeList.begin(); it1 != rsys_list_end; ) {
		RingSysNode* rsys1 = *it1;
		const Util::BitSet& atom_mask1 = rsys1->getAtomMask();

		for (RingSysNodeList::iterator it2 = ++it1; it2 != rsys_list_end; ++it2) {
			RingSysNode* rsys2 = *it2;

			tmpBitMask = rsys2->getAtomMask();
			tmpBitMask &= atom_mask1;

			if (!tmpBitMask.any())
				continue;

			for (std::size_t i = 0; i < numAtoms; i++) {
				if (!tmpBitMask.test(i))
					continue;

				const Atom* spiro_ctr = &molGraph->getAtom(i);
				const LGEdge* edge = allocEdge(spiro_ctr, rsys1, rsys2);

				rsys1->addEdge(spiro_ctr, edge);
				rsys2->addEdge(spiro_ctr, edge);

				break;
			}
		}
	}
}

void Chem::Atom2DCoordinatesGenerator::setAtomNodeChainIDs()
{
	AtomNodeList::const_iterator atom_nodes_beg = atomNodeList.begin();
	AtomNodeList::const_iterator atom_nodes_end = atomNodeList.end();

	currAtomNodePath.clear();

	for (std::size_t chain_id = 0; true; chain_id++) {
		longestAtomNodePath.clear();

		for (AtomNodeList::const_iterator it = atom_nodes_beg; it != atom_nodes_end; ++it)
			findLongestNodePath(*it, 0);

		if (longestAtomNodePath.empty())
			return;

		AtomNodeList::const_iterator path_nodes_end = longestAtomNodePath.end();

		for (AtomNodeList::const_iterator pn_it = longestAtomNodePath.begin(); pn_it != path_nodes_end; ++pn_it) {
			AtomNode* node = *pn_it;

			node->setChainID(chain_id);

			atomNodeTable[node->getAtomIndex()] = 0;
		}
	}
}

void Chem::Atom2DCoordinatesGenerator::findLongestNodePath(AtomNode* node, const AtomNode* parent_node)
{
	if (!atomNodeTable[node->getAtomIndex()])
		return;

	if (node->getType() == LGNode::END_ATOM)
		return;

	currAtomNodePath.push_back(node);

	const Atom* atom = node->getAtom();
	
	Atom::ConstAtomIterator nbr_atoms_end = atom->getAtomsEnd();
	Atom::ConstBondIterator b_it = atom->getBondsBegin();

	for (Atom::ConstAtomIterator a_it = atom->getAtomsBegin(); a_it != nbr_atoms_end; ++a_it) {
		if (!molGraph->containsAtom(*a_it) || !molGraph->containsBond(*b_it))
			continue;

		AtomNode* nbr_node = atomNodeTable[molGraph->getAtomIndex(*a_it)];

		if (!nbr_node || nbr_node == parent_node)
			continue;
		
		findLongestNodePath(nbr_node, node);
	}

	if (currAtomNodePath.size() > longestAtomNodePath.size()) 
		longestAtomNodePath = currAtomNodePath;

	else if (currAtomNodePath.size() == longestAtomNodePath.size()) {
		if (std::accumulate(currAtomNodePath.begin(), currAtomNodePath.end(), double(0),
							boost::bind(std::plus<double>(), _1,
										boost::bind(&LGNode::getPriority, _2))) 
			>
			std::accumulate(longestAtomNodePath.begin(), longestAtomNodePath.end(), double(0),
							boost::bind(std::plus<double>(), _1,
										boost::bind(&LGNode::getPriority, _2))))

			longestAtomNodePath = currAtomNodePath;
	}

	currAtomNodePath.pop_back();
}

void Chem::Atom2DCoordinatesGenerator::createBFSNodeList()
{
	bfsNodeList.clear();

	if (!ringSysNodeList.empty()) 
		bfsNodeList.push_back(*std::max_element(ringSysNodeList.begin(), ringSysNodeList.end(), 
												boost::bind(std::less<double>(), 
															boost::bind(&LGNode::getPriority, _1), 
															boost::bind(&LGNode::getPriority, _2))));
	else if (!atomNodeList.empty())  
		bfsNodeList.push_back(*std::max_element(atomNodeList.begin(), atomNodeList.end(), 
												boost::bind(std::less<double>(), 
															boost::bind(&LGNode::getPriority, _1), 
															boost::bind(&LGNode::getPriority, _2))));
	else 
		return;

	bfsNodeList.front()->createChildLayouts();

	for (std::size_t i = 0, cycle_end_idx = 1; i < cycle_end_idx; cycle_end_idx = bfsNodeList.size()) 
		for ( ; i < cycle_end_idx; i++) 
			bfsNodeList[i]->getChildNodes(bfsNodeList);
}

void Chem::Atom2DCoordinatesGenerator::initNodes() const
{
	std::for_each(atomNodeList.begin(), atomNodeList.end(), boost::bind(&LGNode::init, _1));
	std::for_each(ringSysNodeList.begin(), ringSysNodeList.end(), boost::bind(&LGNode::init, _1));
}

void Chem::Atom2DCoordinatesGenerator::layoutNodes()
{
	if (bfsNodeList.empty())
		return;

	procAtomList.clear();
	procBondList.clear();

	bfsNodeList.front()->layout();

	strictLayoutGeometry = true;
	numLayoutCollisions = 0;
	maxNumLayoutCollisions = 0;
	backtrackingCount = 0;

	while (!layoutChildNodes(0)) 
		backtrackingCount += BACKTRACKING_LIMIT;
}

bool Chem::Atom2DCoordinatesGenerator::layoutChildNodes(std::size_t depth)
{
	if (depth == bfsNodeList.size())
		return true;

	if (backtrackingCount > BACKTRACKING_LIMIT) {
		backtrackingCount = 0;

		if (strictLayoutGeometry) 
			strictLayoutGeometry = false;

		else if (maxNumLayoutCollisions == 0) 
			maxNumLayoutCollisions = 1;

		else
			maxNumLayoutCollisions *= 2;
	}

	LGNode* node = bfsNodeList[depth];

	for (std::size_t saved_num_colls = numLayoutCollisions, saved_alist_size = procAtomList.size(), 
			 saved_blist_size = procBondList.size(); 
		 node->layoutChildNodes(numLayoutCollisions, maxNumLayoutCollisions, strictLayoutGeometry); 
		 numLayoutCollisions = saved_num_colls, procAtomList.resize(saved_alist_size), procBondList.resize(saved_blist_size)) {
		
		if (layoutChildNodes(depth + 1))
			return true;
	}

	backtrackingCount++;

	return false;
}

Chem::Atom2DCoordinatesGenerator::LGEdge* Chem::Atom2DCoordinatesGenerator::allocEdge(const Atom* spiro_ctr, LGNode* n1, LGNode* n2)
{
	LGEdge* edge_ptr = edgeCache.getRaw();

	edge_ptr->init(molGraph, spiro_ctr, n1, n2);

	edgeList.push_back(edge_ptr);

	return edge_ptr;
}

Chem::Atom2DCoordinatesGenerator::LGEdge* Chem::Atom2DCoordinatesGenerator::allocEdge(const Bond* bond, LGNode* n1, LGNode* n2)
{
	LGEdge* edge_ptr = edgeCache.getRaw();

	edge_ptr->init(molGraph, bond, n1, n2);

	edgeList.push_back(edge_ptr);

	return edge_ptr;
}

Chem::Atom2DCoordinatesGenerator::RingInfo* Chem::Atom2DCoordinatesGenerator::allocRingInfo(const Fragment& ring)
{
	RingInfo* ring_info_ptr = ringInfoCache.getRaw();

	ring_info_ptr->init(molGraph, ring, numAtoms, numBonds);
	
	ringList.push_back(ring_info_ptr);	

	return ring_info_ptr;
}

Chem::Atom2DCoordinatesGenerator::RingSysNode* 
Chem::Atom2DCoordinatesGenerator::allocRingSysNode(const RingInfo* ring_info, Math::Vector2DArray& coords)
{
	RingSysNode* node_ptr = ringSysNodeCache.getRaw();

	node_ptr->init(molGraph, ring_info, coords, procAtomList, procBondList);
	
	ringSysNodeList.push_back(node_ptr);

	return node_ptr;
}

Chem::Atom2DCoordinatesGenerator::AtomNode* Chem::Atom2DCoordinatesGenerator::allocAtomNode(const Atom* atom, Math::Vector2DArray& coords)
{
	AtomNode* node_ptr = atomNodeCache.getRaw();

	node_ptr->init(molGraph, atom, atomPriorityTable[molGraph->getAtomIndex(*atom)],
				   coords, procAtomList, procBondList);

	atomNodeList.push_back(node_ptr);

	return node_ptr;
}

void Chem::Atom2DCoordinatesGenerator::freeAllocEdges()
{
	edgeList.clear();
	edgeCache.putAll();
}

void Chem::Atom2DCoordinatesGenerator::freeAllocRingInfos()
{
	ringList.clear();
	ringInfoCache.putAll();
}

void Chem::Atom2DCoordinatesGenerator::freeAllocRingSysNodes()
{
	ringSysNodeList.clear();
	ringSysNodeCache.putAll();
}

void Chem::Atom2DCoordinatesGenerator::freeAllocAtomNodes()
{
	atomNodeList.clear();
	atomNodeCache.putAll();
}

// - RingInfo -

void Chem::Atom2DCoordinatesGenerator::RingInfo::init(const MolecularGraph* molgraph, const Fragment& ring_frag, 
													  std::size_t num_atoms, std::size_t num_bonds) 
{
	fragment = &ring_frag;

	atomMask.resize(num_atoms);
	bondMask.resize(num_bonds);

	atomMask.reset();
	bondMask.reset();
	
	std::for_each(ring_frag.getAtomsBegin(), ring_frag.getAtomsEnd(), 
				  boost::bind(&Util::BitSet::set, &atomMask, boost::bind(&MolecularGraph::getAtomIndex, molgraph, _1), true));

	std::for_each(ring_frag.getBondsBegin(), ring_frag.getBondsEnd(), 
				  boost::bind(&Util::BitSet::set, &bondMask, boost::bind(&MolecularGraph::getBondIndex, molgraph, _1), true));
}

const Chem::Fragment& Chem::Atom2DCoordinatesGenerator::RingInfo::getFragment() const
{
	return *fragment;
}

const Util::BitSet& Chem::Atom2DCoordinatesGenerator::RingInfo::getAtomMask() const
{
	return atomMask;
}

const Util::BitSet& Chem::Atom2DCoordinatesGenerator::RingInfo::getBondMask() const
{
	return bondMask;
}

double Chem::Atom2DCoordinatesGenerator::RingInfo::getPriority() const
{
	return priority;
}

void Chem::Atom2DCoordinatesGenerator::RingInfo::setPriority(double p)
{
	priority = p;
}

std::size_t Chem::Atom2DCoordinatesGenerator::RingInfo::getSize() const
{
	return fragment->getNumBonds();
}

// - LGEdge -

void Chem::Atom2DCoordinatesGenerator::LGEdge::init(const MolecularGraph* molgraph, const Atom* spiro_ctr, LGNode* n1, LGNode* n2)
{
	molGraph = molgraph; 
	spiroCenter = spiro_ctr; 
	bond = 0; 
	node1 = n1; 
	node2 = n2; 
	type = SPIRO_EDGE; 
	hasConfig = false; 
}

void Chem::Atom2DCoordinatesGenerator::LGEdge::init(const MolecularGraph* molgraph, const Bond* bnd, LGNode* n1, LGNode* n2)
{
	molGraph = molgraph; 
	spiroCenter = 0; 
	bond = bnd; 
	node1 = n1; 
	node2 = n2; 
	type = BOND_EDGE; 
	hasConfig = initConfigInfo(); 
}	

const Chem::Atom* Chem::Atom2DCoordinatesGenerator::LGEdge::getSpiroCenter() const
{
	return spiroCenter;
}

const Chem::Bond* Chem::Atom2DCoordinatesGenerator::LGEdge::getBond() const
{
	return bond;
}

Chem::Atom2DCoordinatesGenerator::LGNode* Chem::Atom2DCoordinatesGenerator::LGEdge::otherNode(const LGNode* node) const
{
	assert(node1 == node || node2 == node);

	return (node1 == node ? node2 : node1);
}

Chem::Atom2DCoordinatesGenerator::LGEdge::Type Chem::Atom2DCoordinatesGenerator::LGEdge::getType() const
{
	return type;
}	

bool Chem::Atom2DCoordinatesGenerator::LGEdge::hasConfigConstraint() const
{
	return hasConfig;
}

bool Chem::Atom2DCoordinatesGenerator::LGEdge::configConstraintFulfilled(const Math::Vector2DArray& coords) const
{
	if (!hasConfig)
		return true;

	const Math::Vector2D& ligand1_coords = coords[molGraph->getAtomIndex(*configRefAtoms[0])];
	const Math::Vector2D& ligand2_coords = coords[molGraph->getAtomIndex(*configRefAtoms[1])];
	const Math::Vector2D& atom1_coords = coords[molGraph->getAtomIndex(bond->getBegin())];
	const Math::Vector2D& atom2_coords = coords[molGraph->getAtomIndex(bond->getEnd())];
		
	double tmp = ((atom2_coords[0] - ligand1_coords[0]) * (atom1_coords[1] - ligand1_coords[1])
				  - (atom2_coords[1] - ligand1_coords[1]) * (atom1_coords[0] - ligand1_coords[0]))
		* ((atom1_coords[0] - ligand2_coords[0]) * (atom2_coords[1] - ligand2_coords[1])
		   - (atom1_coords[1] - ligand2_coords[1]) * (atom2_coords[0] - ligand2_coords[0]));

	return (tmp >= 0.0 ? BondConfiguration::TRANS == configuration : BondConfiguration::CIS == configuration);  
}

bool Chem::Atom2DCoordinatesGenerator::LGEdge::initConfigInfo()
{
	const StereoDescriptor& stereo_desc = calcStereoDescriptor(*bond, *molGraph, 0);

	configuration = stereo_desc.getConfiguration();

	if (configuration != BondConfiguration::CIS && configuration != BondConfiguration::TRANS)
		return false;

	const Atom* const* sto_ref_atoms = stereo_desc.getReferenceAtoms();

	if (sto_ref_atoms[1] == &bond->getEnd() && sto_ref_atoms[2] == &bond->getBegin()) {
		configRefAtoms[0] = sto_ref_atoms[3];
		configRefAtoms[1] = sto_ref_atoms[0];

	} else {
		configRefAtoms[0] = sto_ref_atoms[0];
		configRefAtoms[1] = sto_ref_atoms[3];
	}

	return true;
}

// - LGNode -

void Chem::Atom2DCoordinatesGenerator::LGNode::init(const MolecularGraph* molgraph)
{
	molGraph = molgraph;
}

double Chem::Atom2DCoordinatesGenerator::LGNode::getAngularDemand(const Atom*) const
{
	return 0.0;
}

std::size_t Chem::Atom2DCoordinatesGenerator::LGNode::countAtomCollisions(const AtomIndexList& atoms, const AtomIndexList& proc_atoms, 
																		  const Math::Vector2DArray& coords)
{
	return std::accumulate(atoms.begin(), atoms.end(), std::size_t(0),
						   boost::bind(std::plus<std::size_t>(), _1, 
									   boost::bind(&LGNode::countAtomCollisionsForAtom, this, _2, 
												   boost::ref(proc_atoms), boost::ref(coords))));
}

std::size_t Chem::Atom2DCoordinatesGenerator::LGNode::countAtomCollisionsForAtom(std::size_t atom_idx, 
																				 const AtomIndexList& proc_atoms, 
																				 const Math::Vector2DArray& coords)
{
	const double SQRD_TEST_DIST = ATOM_COLLISION_TEST_DIST * ATOM_COLLISION_TEST_DIST;

	const Math::Vector2D& atom_pos = coords[atom_idx];
	Math::Vector2D pos_diff;

	std::size_t count = 0;

	AtomIndexList::const_iterator proc_atoms_end = proc_atoms.end();

	for (AtomIndexList::const_iterator it = proc_atoms.begin(); it != proc_atoms_end; ++it) {
		std::size_t proc_atom_idx = *it;

		if (atom_idx == proc_atom_idx)
			continue;

		pos_diff = atom_pos - coords[proc_atom_idx];

		if (innerProd(pos_diff, pos_diff) <= SQRD_TEST_DIST)
			count++;
	}

	return count;
}

std::size_t Chem::Atom2DCoordinatesGenerator::LGNode::countBondCollisions(const BondList& bonds, const BondList& proc_bonds, 
																		  const Math::Vector2DArray& coords)
{
	return std::accumulate(bonds.begin(), bonds.end(), std::size_t(0),
						   boost::bind(std::plus<std::size_t>(), _1, 
									   boost::bind(&LGNode::countBondCollisionsForBond, this, _2, 
												   boost::ref(proc_bonds), boost::ref(coords))));
}

std::size_t Chem::Atom2DCoordinatesGenerator::LGNode::countBondCollisionsForBond(const Bond* bond, const BondList& proc_bonds, 
																				 const Math::Vector2DArray& coords)
{
	std::size_t atom1_idx = molGraph->getAtomIndex(bond->getBegin());
	std::size_t atom2_idx = molGraph->getAtomIndex(bond->getEnd());

	const Math::Vector2D& atom1_pos = coords[atom1_idx];
	const Math::Vector2D& atom2_pos = coords[atom2_idx];

	std::size_t count = 0;

	BondList::const_iterator proc_bonds_end = proc_bonds.end();

	for (BondList::const_iterator it = proc_bonds.begin(); it != proc_bonds_end; ++it) {
		const Bond* proc_bond = *it;

		if (bond == proc_bond) // should not happen!
			continue;

		std::size_t proc_atom1_idx = molGraph->getAtomIndex(proc_bond->getBegin());

		if (proc_atom1_idx == atom1_idx || proc_atom1_idx == atom2_idx)
			continue;

		std::size_t proc_atom2_idx = molGraph->getAtomIndex(proc_bond->getEnd());

		if (proc_atom2_idx == atom1_idx || proc_atom2_idx == atom2_idx)
			continue;

		const Math::Vector2D& proc_atom1_pos = coords[proc_atom1_idx];
		const Math::Vector2D& proc_atom2_pos = coords[proc_atom2_idx];

		if (ccw(atom1_pos, atom2_pos, proc_atom1_pos) * ccw(atom1_pos, atom2_pos, proc_atom2_pos) <= 0 
			&& ccw(proc_atom1_pos, proc_atom2_pos, atom1_pos) * ccw(proc_atom1_pos, proc_atom2_pos, atom2_pos) <= 0)
			count++;
	}

	return count;
}

std::size_t Chem::Atom2DCoordinatesGenerator::LGNode::countAtomBondCollisions(const AtomIndexList& atoms, const BondList& proc_bonds, 
																			  const Math::Vector2DArray& coords)
{
	return std::accumulate(atoms.begin(), atoms.end(), std::size_t(0),
						   boost::bind(std::plus<std::size_t>(), _1, 
									   boost::bind(&LGNode::countBondCollisionsForAtom, this, _2, 
												   boost::ref(proc_bonds), boost::ref(coords))));
}

std::size_t Chem::Atom2DCoordinatesGenerator::LGNode::countBondCollisionsForAtom(std::size_t atom_idx, const BondList& proc_bonds, 
																				 const Math::Vector2DArray& coords)
{
	return std::count_if(proc_bonds.begin(), proc_bonds.end(), 
						 boost::bind(&LGNode::testAtomBondCollision, this, atom_idx, _1, boost::ref(coords)));
}

std::size_t Chem::Atom2DCoordinatesGenerator::LGNode::countBondAtomCollisions(const BondList& bonds, const AtomIndexList& proc_atoms, 
																			  const Math::Vector2DArray& coords)
{
	return std::accumulate(bonds.begin(), bonds.end(), std::size_t(0),
						   boost::bind(std::plus<std::size_t>(), _1, 
									   boost::bind(&LGNode::countAtomCollisionsForBond, this, _2, 
												   boost::ref(proc_atoms), boost::ref(coords))));
}

std::size_t Chem::Atom2DCoordinatesGenerator::LGNode::countAtomCollisionsForBond(const Bond* bond, const AtomIndexList& proc_atoms, 
																				 const Math::Vector2DArray& coords)
{
	return std::count_if(proc_atoms.begin(), proc_atoms.end(), 
						 boost::bind(&LGNode::testAtomBondCollision, this, _1, bond, boost::ref(coords)));
}

bool Chem::Atom2DCoordinatesGenerator::LGNode::testAtomBondCollision(std::size_t atom_idx, const Bond* bond, 
																	 const Math::Vector2DArray& coords)
{
	const double SQRD_TEST_DIST = ATOM_BOND_COLLISION_TEST_DIST * ATOM_BOND_COLLISION_TEST_DIST;

	std::size_t atom1_idx = molGraph->getAtomIndex(bond->getBegin());

	if (atom1_idx == atom_idx)
		return false;

	std::size_t atom2_idx = molGraph->getAtomIndex(bond->getEnd());

	if (atom2_idx == atom_idx)
		return false;

	const Math::Vector2D& atom1_pos = coords[atom1_idx];
	const Math::Vector2D& atom2_pos = coords[atom2_idx];

	Math::Vector2D bond_vec = atom2_pos - atom1_pos;

	const Math::Vector2D& atom_pos = coords[atom_idx];

	double u = (((atom_pos(0) - atom1_pos(0)) * bond_vec(0)) + ((atom_pos(1) - atom1_pos(1)) * bond_vec(1))) 
		/ innerProd(bond_vec, bond_vec);

	if (u < 0.0 || u > 1.0)
		return false;

	Math::Vector2D inters_pt = atom1_pos + (bond_vec * u);
	Math::Vector2D inters_pt_vec = atom_pos - inters_pt;
	
	return (innerProd(inters_pt_vec, inters_pt_vec) <= SQRD_TEST_DIST);
}

// - RingSysNode -

void Chem::Atom2DCoordinatesGenerator::RingSysNode::init(const MolecularGraph* molgraph, 
														 const RingInfo* ring_info, 
														 Math::Vector2DArray& out_coords, AtomIndexList& proc_atoms, 
														 BondList& proc_bonds)
{
	LGNode::init(molgraph);

	atomMask = ring_info->getAtomMask(); 
	bondMask = ring_info->getBondMask(); 
	priority = ring_info->getPriority(); 
	procAtomList = &proc_atoms; 
	procBondList = &proc_bonds;
	outputCoords = &out_coords; 
	parentEdge = 0; 
	rsysLayoutIndex = 0; 

	ringList.clear();
	ringLayoutQueue.clear();
	ringSegment.clear();
	edgeListMap.clear();
	freeSweepMap.clear();
	atomList.clear();
	bondList.clear();
	parentEdgeAtomEdges.clear();
	childLayouts.clear();
	childLayoutIndexTable.clear();
	edgeAtomTable.clear();
	layoutWeightFactors.clear();
	layoutEnergyDerivatives.clear();

	ringList.push_back(ring_info);
	ringLayoutQueue.push_back(ring_info);

	const Fragment& ring_frag = ring_info->getFragment();

	std::transform(ring_frag.getBondsBegin(), ring_frag.getBondsEnd(), std::back_inserter(bondList),
				   Internal::AddressOf<const Bond>());
}

const Util::BitSet& Chem::Atom2DCoordinatesGenerator::RingSysNode::getAtomMask() const
{
	return atomMask;
}

const Util::BitSet& Chem::Atom2DCoordinatesGenerator::RingSysNode::getBondMask() const
{
	return bondMask;
}

bool Chem::Atom2DCoordinatesGenerator::RingSysNode::containsAtom(std::size_t idx) const
{
	return atomMask.test(idx);
}

bool Chem::Atom2DCoordinatesGenerator::RingSysNode::addRing(const RingInfo* ring_info)
{
	tmpBitMask = bondMask;
	tmpBitMask &= ring_info->getBondMask();

	if (!tmpBitMask.any())
		return false;

	const Fragment& ring_frag = ring_info->getFragment();
	Fragment::ConstBondIterator bonds_end = ring_frag.getBondsEnd();

	for (Fragment::ConstBondIterator it = ring_frag.getBondsBegin(); it != bonds_end; ++it) {
		const Bond* bond = &*it;

		if (!bondMask.test(molGraph->getBondIndex(*bond)))
			bondList.push_back(bond);
	}

	bondMask |= ring_info->getBondMask();
	atomMask |= ring_info->getAtomMask();

	ringList.push_back(ring_info);
	ringLayoutQueue.push_back(ring_info);

	priority += ring_info->getPriority();

	return true;
}

void Chem::Atom2DCoordinatesGenerator::RingSysNode::addEdge(const Atom* atom, const LGEdge* edge)
{
	edgeListMap[atom].push_back(edge);
}

void Chem::Atom2DCoordinatesGenerator::RingSysNode::init()
{
	calcCoords();
	refineLayout();
	calcFreeSweeps();
}	

double Chem::Atom2DCoordinatesGenerator::RingSysNode::getPriority() const
{
	return priority;
}

std::size_t Chem::Atom2DCoordinatesGenerator::RingSysNode::getChainID() const
{
	return (std::numeric_limits<std::size_t>::max() - 1);
}

void Chem::Atom2DCoordinatesGenerator::RingSysNode::getChildNodes(NodeList& child_nodes) const
{
	EdgeListMap::const_iterator edge_map_end = edgeListMap.end();

	for (EdgeListMap::const_iterator lm_it = edgeListMap.begin(); lm_it != edge_map_end; ++lm_it) {
		const EdgeList& edges = lm_it->second;	
			
		EdgeList::const_iterator edges_end = edges.end();

		for (EdgeList::const_iterator e_it = edges.begin(); e_it != edges_end; ++e_it) {
			const LGEdge* edge = *e_it;
			LGNode* child_node = edge->otherNode(this);

			if (child_node->setParentEdge(edge, UP))
				child_nodes.push_back(child_node);
		}
	}

	if (!parentEdge || parentEdge->getType() == LGEdge::SPIRO_EDGE)
		return;

	EdgeList::const_iterator edges_end = parentEdgeAtomEdges.end();

	for (EdgeList::const_iterator e_it = parentEdgeAtomEdges.begin(); e_it != edges_end; ++e_it) {
		const LGEdge* edge = *e_it;

		if (parentEdge->getBond() == edge->getBond())
			continue;

		LGNode* child_node = edge->otherNode(this);

		if (child_node->setParentEdge(edge, UP))
			child_nodes.push_back(child_node);
	}
}

void Chem::Atom2DCoordinatesGenerator::RingSysNode::layout()
{
	copyCoords();

	commitAtomAndBondList();
}

bool Chem::Atom2DCoordinatesGenerator::RingSysNode::layout(double edge_angle, const Math::Vector2D& parent_pos, 
														   std::size_t& num_colls, std::size_t max_num_colls, bool strict)
{
	assert(parentEdge);

	if (parentEdge->getType() == LGEdge::BOND_EDGE)
		calcPosition(parent_pos, DEF_BOND_LENGTH, edge_angle, (*outputCoords)[molGraph->getAtomIndex(*parentEdgeAtom)]);

	parentEdgeAngle = edge_angle;
	parentPos = parent_pos;

	return true;
}

bool Chem::Atom2DCoordinatesGenerator::RingSysNode::layoutChildNodes(std::size_t& num_colls, std::size_t max_num_colls, bool strict)
{
	if (!parentEdge)
		return layoutChildNodes(0, num_colls, max_num_colls, strict);

	if (parentEdge->getType() == LGEdge::SPIRO_EDGE) {
		const Atom* spiro_ctr = parentEdge->getSpiroCenter();
		
		const AngleRange& free_sweep = freeSweepMap[spiro_ctr];

		std::size_t spiro_ctr_atom_idx = molGraph->getAtomIndex(*spiro_ctr);

		double rsys_axis_angle = 0.5 * (free_sweep.first + free_sweep.second);
		double rsys_rot_angle = parentEdgeAngle - rsys_axis_angle + M_PI;

		for (std::size_t saved_num_colls = num_colls, saved_alist_size = procAtomList->size(), saved_blist_size = procBondList->size();
			 rsysLayoutIndex < 6; 
			 rsysLayoutIndex++) { 

			bool success = false;

			switch (rsysLayoutIndex) {

				case 0:
				case 1:
					success = layout(spiro_ctr_atom_idx, parentPos, rsys_rot_angle, rsysLayoutIndex & 0x1, 
									 rsys_axis_angle, num_colls, max_num_colls);
					break;

				case 2:
				case 3:
					success = layout(spiro_ctr_atom_idx, parentPos, rsys_rot_angle + ANGLE_BENDING_DELTA,
									 rsysLayoutIndex & 0x1, rsys_axis_angle, num_colls, max_num_colls);
					break;

				case 4:
				case 5:
					success = layout(spiro_ctr_atom_idx, parentPos, rsys_rot_angle - ANGLE_BENDING_DELTA, 
									 rsysLayoutIndex & 0x1, rsys_axis_angle, num_colls, max_num_colls);
				default:
					break;
			}

			if (success) {
				if (childLayouts.empty()) {
					rsysLayoutIndex++;
					return true;
				}

				if (layoutChildNodes(0, num_colls, max_num_colls, strict))
					return true;

				num_colls = saved_num_colls;
				
				procAtomList->resize(saved_alist_size);
				procBondList->resize(saved_blist_size); 
			}
		}

		rsysLayoutIndex = 0;

		return false;
	}

	const AngleRange& free_sweep = freeSweepMap[parentEdgeAtom];

	double rsys_axis_angle = 0.5 * (free_sweep.first + free_sweep.second);

	std::size_t num_rsys_layouts = (strict ? 2 : 18);

	for ( ; rsysLayoutIndex < num_rsys_layouts; rsysLayoutIndex++) { 
		bool success = false;

		switch (rsysLayoutIndex) {

			case 0:
			case 1:
				success = layoutChildNodes(parentEdgeAngle, DEF_BOND_LENGTH, rsysLayoutIndex & 0x1,
										   rsys_axis_angle, num_colls, max_num_colls, strict);
				break;

			case 2:
			case 3:
				success = layoutChildNodes(parentEdgeAngle + ANGLE_BENDING_DELTA, DEF_BOND_LENGTH, rsysLayoutIndex & 0x1,
										   rsys_axis_angle, num_colls, max_num_colls, strict);
				break;

			case 4:
			case 5:
				success = layoutChildNodes(parentEdgeAngle - ANGLE_BENDING_DELTA, DEF_BOND_LENGTH, rsysLayoutIndex & 0x1, 
										   rsys_axis_angle, num_colls, max_num_colls, strict);
				break;

			case 6:
			case 7:
				success = layoutChildNodes(parentEdgeAngle, DEF_BOND_LENGTH + BOND_LENGTH_DELTA, rsysLayoutIndex & 0x1,
										   rsys_axis_angle, num_colls, max_num_colls, strict);
				break;

			case 8:
			case 9:
				success = layoutChildNodes(parentEdgeAngle + ANGLE_BENDING_DELTA, DEF_BOND_LENGTH + BOND_LENGTH_DELTA, 
										   rsysLayoutIndex & 0x1, rsys_axis_angle, num_colls, max_num_colls, strict);
				break;

			case 10:
			case 11:
				success = layoutChildNodes(parentEdgeAngle - ANGLE_BENDING_DELTA, DEF_BOND_LENGTH + BOND_LENGTH_DELTA, 
										   rsysLayoutIndex & 0x1, rsys_axis_angle, num_colls, max_num_colls, strict);
				break;

			case 12:
			case 13:
				success = layoutChildNodes(parentEdgeAngle, DEF_BOND_LENGTH - BOND_LENGTH_DELTA, rsysLayoutIndex & 0x1,
										   rsys_axis_angle, num_colls, max_num_colls, strict);
				break;

			case 14:
			case 15:
				success = layoutChildNodes(parentEdgeAngle + ANGLE_BENDING_DELTA, DEF_BOND_LENGTH - BOND_LENGTH_DELTA, 
										   rsysLayoutIndex & 0x1, rsys_axis_angle, num_colls, max_num_colls, strict);
				break;
	
			case 16:
			case 17:
				success = layoutChildNodes(parentEdgeAngle - ANGLE_BENDING_DELTA, DEF_BOND_LENGTH - BOND_LENGTH_DELTA, 
										   rsysLayoutIndex & 0x1, rsys_axis_angle, num_colls, max_num_colls, strict);
			default:
				break;
		}

		if (success)
			return true;
	}

	rsysLayoutIndex = 0;

	return false;
}

Chem::Atom2DCoordinatesGenerator::LGNode::Type Chem::Atom2DCoordinatesGenerator::RingSysNode::getType() const
{
	return RING_SYS;
}

double Chem::Atom2DCoordinatesGenerator::RingSysNode::getAngularDemand(const Atom* atom) const
{
	AngleRangeMap::const_iterator it = freeSweepMap.find(atom);

	return (it == freeSweepMap.end() ? 0.0 : 2.0 * M_PI - (it->second.second - it->second.first));
}

bool Chem::Atom2DCoordinatesGenerator::RingSysNode::setParentEdge(const LGEdge* parent_edge, Direction)
{
	assert(!parentEdge);

	parentEdge = parent_edge;

	if (parentEdge->getType() == LGEdge::SPIRO_EDGE)  
		edgeListMap.erase(parentEdge->getSpiroCenter());

	else {
		const Bond* bond = parentEdge->getBond();

		parentEdgeAtom = &bond->getBegin();

		if (!atomMask.test(molGraph->getAtomIndex(*parentEdgeAtom)))
			parentEdgeAtom = &bond->getEnd();

		EdgeListMap::iterator it = edgeListMap.find(parentEdgeAtom);
		
		assert(it != edgeListMap.end());

		createChildLayouts(it->first, it->second);

		parentEdgeAtomEdges.swap(it->second);

		edgeListMap.erase(it);
	}

	createChildLayouts();

	return true;
}

bool Chem::Atom2DCoordinatesGenerator::RingSysNode::layout(std::size_t ctr_atom_idx, const Math::Vector2D& final_ctr_atom_pos, 
														   double rsys_rot_angle, bool flip, double rsys_axis_angle, 
														   std::size_t& num_colls, std::size_t max_num_colls)
{
	transformCoords(ctr_atom_idx, final_ctr_atom_pos, rsys_rot_angle, flip, rsys_axis_angle);

	std::size_t new_num_colls = num_colls
		+ countAtomCollisions(atomList, *procAtomList, *outputCoords)
		+ countBondCollisions(bondList, *procBondList, *outputCoords) * 2
		+ countAtomBondCollisions(atomList, *procBondList, *outputCoords)
		+ countBondAtomCollisions(bondList, *procAtomList, *outputCoords);

	if (new_num_colls > max_num_colls)
		return false;

	assert(parentEdge);

	if (parentEdge->getType() == LGEdge::BOND_EDGE) {
		const Bond* bond = parentEdge->getBond();

		new_num_colls += countBondCollisionsForBond(bond, *procBondList, *outputCoords) * 2
			+ countAtomCollisionsForBond(bond, *procAtomList, *outputCoords);

		if (new_num_colls > max_num_colls)
			return false;
	}

	num_colls = new_num_colls;

	commitAtomAndBondList();

	return true;
}

bool Chem::Atom2DCoordinatesGenerator::RingSysNode::layoutChildNodes(double parent_edge_angle, double bond_length, 
																	 bool flip, double rsys_axis_angle, 
																	 std::size_t& num_colls, std::size_t max_num_colls, 
																	 bool strict) 
{
	assert(parentEdge);

	std::size_t num_child_layouts = childLayouts[0].size();
	std::size_t& layout_idx = childLayoutIndexTable.front();

	if (layout_idx < num_child_layouts) {
		std::size_t atom_idx = molGraph->getAtomIndex(*parentEdgeAtom);

		Math::Vector2D& atom_pos = (*outputCoords)[atom_idx];

		const Bond* parent_edge_bond = parentEdge->getBond();	

		calcPosition(parentPos, bond_length, parent_edge_angle, atom_pos);

		for (std::size_t saved_num_colls = num_colls, saved_alist_size = procAtomList->size(), saved_blist_size = procBondList->size();
			 layout_idx < num_child_layouts; 
			 num_colls = saved_num_colls, procAtomList->resize(saved_alist_size), 
				 procBondList->resize(saved_blist_size), layout_idx++) {

			NodeLayoutInfoList::const_iterator layout_infos_beg = childLayouts[0][layout_idx].begin();
			NodeLayoutInfoList::const_iterator layout_infos_end = childLayouts[0][layout_idx].end();

			NodeLayoutInfoList::const_iterator it = std::find_if(layout_infos_beg, layout_infos_end,
																 boost::bind(std::equal_to<const Bond*>(), 
																			 boost::bind(&LGEdge::getBond, 
																						 boost::bind(&NodeLayoutInfo::edge, _1)), 
																			 parent_edge_bond));
			assert(it != layout_infos_end);

			double rsys_rot_angle = parent_edge_angle - it->angle + M_PI;

			if (!layout(atom_idx, atom_pos, rsys_rot_angle, flip, rsys_axis_angle, num_colls, max_num_colls))
				continue;

			if (!parentEdge->configConstraintFulfilled(*outputCoords))
				continue;

			for (it = layout_infos_beg; it != layout_infos_end; ++it) {
				const NodeLayoutInfo& layout_info = *it;
				const LGEdge* edge = layout_info.edge;
			
				if (edge->getBond() == parent_edge_bond)
					continue;

				LGNode* child_node = edge->otherNode(this);

				if (!child_node->layout(transformEdgeAngle(layout_info.angle), atom_pos, num_colls, max_num_colls, strict))
					break;
			}

			if (it == layout_infos_end) {
				if (childLayouts.size() == 1) {
					layout_idx++;
					return true;
				}

				if (layoutChildNodes(1, num_colls, max_num_colls, strict)) 
					return true;
			}
		}
	}

	layout_idx = 0;

	return false;
}

bool Chem::Atom2DCoordinatesGenerator::RingSysNode::layoutChildNodes(std::size_t depth, std::size_t& num_colls,
																	 std::size_t max_num_colls, bool strict)
{
	if (depth == childLayouts.size())
		return true;

	const Atom* atom = edgeAtomTable[depth];

	const Math::Vector2D& atom_pos = (*outputCoords)[molGraph->getAtomIndex(*atom)];

	std::size_t num_child_layouts = childLayouts[depth].size();
	std::size_t& layout_idx = childLayoutIndexTable[depth];

	for (std::size_t saved_num_colls = num_colls, saved_alist_size = procAtomList->size(), saved_blist_size = procBondList->size();
		 layout_idx < num_child_layouts; 
		 num_colls = saved_num_colls, procAtomList->resize(saved_alist_size), procBondList->resize(saved_blist_size), layout_idx++) {

		NodeLayoutInfoList::const_iterator layout_infos_end = childLayouts[depth][layout_idx].end();
		NodeLayoutInfoList::const_iterator it = childLayouts[depth][layout_idx].begin();

		for ( ; it != layout_infos_end; ++it) {
			const NodeLayoutInfo& layout_info = *it;
			const LGEdge* edge = layout_info.edge;

			LGNode* child_node = edge->otherNode(this);

			if (!child_node->layout(transformEdgeAngle(layout_info.angle), atom_pos, num_colls, max_num_colls, strict))
				break;
		}

		if (it == layout_infos_end) {
			if (depth + 1 == childLayouts.size()) {
				layout_idx++;
				return true;
			}

			if (layoutChildNodes(depth + 1, num_colls, max_num_colls, strict))
				return true;
		}
	}

	layout_idx = 0;
	
	return false;
}

void Chem::Atom2DCoordinatesGenerator::RingSysNode::createChildLayouts()
{
	EdgeListMap::iterator edge_map_end = edgeListMap.end();

	for (EdgeListMap::iterator it = edgeListMap.begin(); it != edge_map_end; ++it)
		createChildLayouts(it->first, it->second);
}

void Chem::Atom2DCoordinatesGenerator::RingSysNode::createChildLayouts(const Atom* atom, EdgeList& edges)
{
	std::size_t num_edges = edges.size();

	childLayouts.resize(childLayouts.size() + 1);

	childLayoutIndexTable.push_back(0);
	edgeAtomTable.push_back(atom);
	
	NodeLayoutInfoListTable::value_type& layout_list = childLayouts.back();

	std::size_t num_perms = Math::factorial<std::size_t>(num_edges);

	layout_list.resize(num_perms);

	EdgeList::iterator edges_beg = edges.begin();
	EdgeList::iterator edges_end = edges.end();

	const AngleRange& free_sweep = freeSweepMap[atom];

	double tot_ang_demand = 0.0;

	for (EdgeList::const_iterator it = edges_beg; it != edges_end; ++it) {
		const LGEdge* edge = *it;
   		
		tot_ang_demand += edge->otherNode(this)->getAngularDemand(atom);
	}

	double edge_spacing = (free_sweep.second - free_sweep.first - tot_ang_demand) / (num_edges + 1);

	for (std::size_t i = 0; i < num_perms; i++) {
		layout_list[i].reserve(num_edges);

		double angle_offs = free_sweep.first + edge_spacing;

		for (EdgeList::const_iterator it = edges_beg; it != edges_end; ++it) {
			const LGEdge* edge = *it;
   		
			double ang_demand = edge->otherNode(this)->getAngularDemand(atom);

			layout_list[i].push_back(NodeLayoutInfo(edge, 0.5 * ang_demand + angle_offs));

			angle_offs += ang_demand + edge_spacing;
		}

		std::next_permutation(edges_beg, edges_end);
	}

	NodeLayoutInfoListTable::value_type::iterator layouts_end = layout_list.end();

	for (NodeLayoutInfoListTable::value_type::iterator it = layout_list.begin(); it != layouts_end; ) {
		const NodeLayoutInfoList& layout_infos = *it;

		layouts_end = std::remove_if(++it, layouts_end, NodeLayoutInfoListEqualCmpFunc(this, layout_infos));
	}

	layout_list.erase(layouts_end, layout_list.end());
}

void Chem::Atom2DCoordinatesGenerator::RingSysNode::transformCoords(std::size_t ctr_atom_idx, 
																	const Math::Vector2D& final_ctr_atom_pos, 
																	double rsys_rot_angle, bool flip, double rsys_axis_angle)
{
	flipped = flip;
	rsysRotAngle = rsys_rot_angle;

	Math::Vector2D ctr_atom_pos = localCoords[ctr_atom_idx];
	Math::Vector2D trans_atom_pos;

	AtomIndexList::const_iterator atoms_end = atomList.end();

	if (flip) {
		double flip_rot_angle = 2.0 * rsys_axis_angle + rsys_rot_angle;

		double flip_rot_sin = std::sin(flip_rot_angle);
		double flip_rot_cos = std::cos(flip_rot_angle);

		for (AtomIndexList::const_iterator it = atomList.begin(); it != atoms_end; ++it) {
			std::size_t atom_idx = *it;

			trans_atom_pos = localCoords[atom_idx] - ctr_atom_pos;
		
			double x = trans_atom_pos(0);
			double y = trans_atom_pos(1);

			trans_atom_pos(0) = x * flip_rot_cos + y * flip_rot_sin;
			trans_atom_pos(1) = x * flip_rot_sin - y * flip_rot_cos;

			trans_atom_pos += final_ctr_atom_pos;

			(*outputCoords)[atom_idx] = trans_atom_pos;
		}		

		rsysAxisAngle = rsys_axis_angle;

		return;
	}

	double rsys_rot_sin = std::sin(rsys_rot_angle);
	double rsys_rot_cos = std::cos(rsys_rot_angle);

	for (AtomIndexList::const_iterator it = atomList.begin(); it != atoms_end; ++it) {
		std::size_t atom_idx = *it;

		trans_atom_pos = localCoords[atom_idx] - ctr_atom_pos;
		
		double x = trans_atom_pos(0);
		double y = trans_atom_pos(1);

		trans_atom_pos(0) = x * rsys_rot_cos - y * rsys_rot_sin;
		trans_atom_pos(1) = x * rsys_rot_sin + y * rsys_rot_cos;

		trans_atom_pos += final_ctr_atom_pos;

		(*outputCoords)[atom_idx] = trans_atom_pos;
	}		
}

double Chem::Atom2DCoordinatesGenerator::RingSysNode::transformEdgeAngle(double edge_angle) const
{
	if (flipped) 
		return (2.0 * rsysAxisAngle - edge_angle + rsysRotAngle);

	return (edge_angle + rsysRotAngle);
}

void Chem::Atom2DCoordinatesGenerator::RingSysNode::copyCoords()
{
	rsysRotAngle = 0.0;
	flipped = false;

	AtomIndexList::const_iterator atoms_end = atomList.end();

	for (AtomIndexList::const_iterator it = atomList.begin(); it != atoms_end; ++it) {
		std::size_t atom_idx = *it;

		(*outputCoords)[atom_idx] = localCoords[atom_idx];
	}
}

void Chem::Atom2DCoordinatesGenerator::RingSysNode::commitAtomAndBondList() const
{
	procAtomList->insert(procAtomList->end(), atomList.begin(), atomList.end());
	procBondList->insert(procBondList->end(), bondList.begin(), bondList.end());

	if (parentEdge && parentEdge->getType() == LGEdge::BOND_EDGE)
		procBondList->push_back(parentEdge->getBond());
}

void Chem::Atom2DCoordinatesGenerator::RingSysNode::calcCoords()
{
	localCoords.resize(outputCoords->getSize());

	procAtomMask.resize(atomMask.size());

	if (ringLayoutQueue.size() == 1) {
		calcCoordsForRing(ringLayoutQueue.front());
		return;
	} 

	ringLayoutQueue.sort(boost::bind(std::greater<double>(), 
									 boost::bind(&RingInfo::getPriority, _1), 
									 boost::bind(&RingInfo::getPriority, _2)));

	typedef std::vector<const RingInfo*> RingInfoList;

	RingInfoList next_rings;
	RingInfoList curr_rings;
	
	curr_rings.push_back(ringLayoutQueue.front());
	ringLayoutQueue.pop_front();

	bool first_ring = true;

	while (!curr_rings.empty()) {
		for (RingInfoList::const_iterator it = curr_rings.begin(); it != curr_rings.end(); ++it) {
			const RingInfo* ring_info = *it;

			if (first_ring) {
				calcCoordsForRing(ring_info);	
				first_ring = false;

			} else
				calcCoordsForRingSegment(ring_info);

			for (RingLayoutQueue::iterator it2 = ringLayoutQueue.begin(); it2 != ringLayoutQueue.end(); ) {
				const RingInfo* next_ring = *it2;

				tmpBitMask = ring_info->getBondMask();
				tmpBitMask &= next_ring->getBondMask(); 

				if (!tmpBitMask.any()) {
					++it2;
					continue;
				}

				next_rings.push_back(next_ring);
				ringLayoutQueue.erase(it2++);
			}
		}

		curr_rings.swap(next_rings);
		next_rings.clear();
	}
}

void Chem::Atom2DCoordinatesGenerator::RingSysNode::calcCoordsForRing(const RingInfo* ring_info)
{
	std::size_t ring_size = ring_info->getSize();

	double sec_angle = M_PI * 2.0 / ring_size;
	double r = DEF_BOND_LENGTH * 0.5 / std::sin(sec_angle * 0.5);
	double angle = M_PI * 0.5;

	const Fragment& ring_frag = ring_info->getFragment();

	Math::Vector2D ring_ctr;

	Fragment::ConstAtomIterator it = ring_frag.getAtomsBegin();

	for (std::size_t i = 0; i < ring_size; i++, ++it, angle += sec_angle) {
		std::size_t atom_idx = molGraph->getAtomIndex(*it);

		calcPosition(ring_ctr, r, angle, localCoords[atom_idx]);

		procAtomMask.set(atom_idx);
		atomList.push_back(atom_idx);
	}
}

void Chem::Atom2DCoordinatesGenerator::RingSysNode::calcCoordsForRingSegment(const RingInfo* ring_info)
{	
	std::size_t ring_size = ring_info->getSize();

	double sec_angle = M_PI * 2.0 / ring_size;

	while (getNextRingSegment(ring_info)) {
		std::size_t seg_atom_count = ringSegment.size();
		std::size_t head_atom1_idx = ringSegment.front();
		std::size_t head_atom2_idx = ringSegment.back();

		const Math::Vector2D& head_atom1_pos = localCoords[head_atom1_idx];
		const Math::Vector2D& head_atom2_pos = localCoords[head_atom2_idx];

		Math::Vector2D head_atom_vec = head_atom2_pos - head_atom1_pos;

		double head_atom_dist = norm2(head_atom_vec);
		double seg_angle = sec_angle * (seg_atom_count - 1) * 0.5;
		double r = 0.5 * head_atom_dist / std::sin(seg_angle);
		double ctr_offs = -r * std::cos(seg_angle);
		double seg_size = r + ctr_offs;

		Math::Vector2D perp_head_atom_vec;

		perp_head_atom_vec(0) = -head_atom_vec(1) / head_atom_dist;
		perp_head_atom_vec(1) = head_atom_vec(0) / head_atom_dist;

		Math::Vector2D head_atom_ctr_pos = head_atom_vec * 0.5 + head_atom1_pos;
		Math::Vector2D max_seg_point_vec = perp_head_atom_vec * seg_size;

		Math::Vector2D max_seg_point1 = head_atom_ctr_pos + max_seg_point_vec;
		Math::Vector2D max_seg_point2 = head_atom_ctr_pos - max_seg_point_vec;

		double cf1 = calcCongestionFactor(max_seg_point1);
		double cf2 = calcCongestionFactor(max_seg_point2);
		
		if (cf2 < cf1) {
			max_seg_point1 = max_seg_point2;
			ctr_offs *= -1.0;
		}

		Math::Vector2D max_seg_point_head1_vec = head_atom1_pos - max_seg_point1;
		Math::Vector2D max_seg_point_head2_vec = head_atom2_pos - max_seg_point1;

		double angle_inc = (max_seg_point_head1_vec(0) * max_seg_point_head2_vec(1) 
							- max_seg_point_head1_vec(1) * max_seg_point_head2_vec(0) > 0.0 ? -1.0 : 1.0) * sec_angle;

		Math::Vector2D ring_ctr = perp_head_atom_vec * ctr_offs + head_atom_ctr_pos; 

		double angle = calcAngle(head_atom1_pos - ring_ctr) + angle_inc;

		seg_atom_count--;

		for (std::size_t i = 1; i < seg_atom_count; i++, angle += angle_inc) {
			std::size_t atom_idx = ringSegment[i];

			calcPosition(ring_ctr, r, angle, localCoords[atom_idx]);

			procAtomMask.set(atom_idx);
			atomList.push_back(atom_idx);
		} 
	}
}

bool Chem::Atom2DCoordinatesGenerator::RingSysNode::getNextRingSegment(const RingInfo* ring_info)
{
	const Util::BitSet& ring_atom_mask = ring_info->getAtomMask();

	tmpBitMask = procAtomMask;
	tmpBitMask &= ring_atom_mask;

	if (tmpBitMask == ring_atom_mask)
		return false;

	ringSegment.clear();

	const Fragment& ring_frag = ring_info->getFragment();

	std::size_t ring_size = ring_info->getSize();
	std::size_t first_atom_idx = molGraph->getAtomIndex(ring_frag.getAtom(0));

	if (procAtomMask.test(first_atom_idx)) {
		std::size_t last_atom_idx = first_atom_idx;
		std::size_t i = 1;

		for ( ; i < ring_size; i++) {
			std::size_t atom_idx = molGraph->getAtomIndex(ring_frag.getAtom(i));

			if (!procAtomMask.test(atom_idx)) {
				ringSegment.push_back(last_atom_idx);
				ringSegment.push_back(atom_idx);
				
				break;
			}

			last_atom_idx = atom_idx;
		}

		for (i++; i < ring_size; i++) {
			std::size_t atom_idx = molGraph->getAtomIndex(ring_frag.getAtom(i));

			ringSegment.push_back(atom_idx);

			if (procAtomMask.test(atom_idx))
				break;
		}

		if (i == ring_size) 
			ringSegment.push_back(first_atom_idx);

	} else {
		ringSegment.push_back(first_atom_idx);

		for (std::size_t i = 1; i < ring_size; i++) {
			std::size_t atom_idx = molGraph->getAtomIndex(ring_frag.getAtom(i));

			ringSegment.push_back(atom_idx);

			if (procAtomMask.test(atom_idx))
				break;
		}

		for (std::size_t i = ring_size; i > 0; i--) {
			std::size_t atom_idx = molGraph->getAtomIndex(ring_frag.getAtom(i - 1));

			ringSegment.push_front(atom_idx);

			if (procAtomMask.test(atom_idx))
				break;
		}
	}

	return (!ringSegment.empty());
}

void Chem::Atom2DCoordinatesGenerator::RingSysNode::refineLayout()
{
	if (ringList.size() == 1)
		return;

	initSpringLayoutParams();
	performSpringLayout();
}

void Chem::Atom2DCoordinatesGenerator::RingSysNode::initSpringLayoutParams()
{
	const double SPRING_CONSTANT                 = 100.0 * DEF_BOND_LENGTH;
	const double SPRING_LAYOUT_MIN_WEIGHT_FACTOR = 0.1;
	const std::size_t REFERENCE_RING_SIZE        = 4;

	std::size_t num_atoms = outputCoords->getSize();

	layoutWeightFactors.assign(num_atoms, 0.0);
	layoutEnergyDerivatives.resize(num_atoms);

	layoutAtomDistances.resize(num_atoms, num_atoms, false);
	layoutAtomDistances.clear();

	layoutSpringStrengths.resize(num_atoms, num_atoms, false);
	layoutSpringStrengths.clear();

	const Math::ULMatrix& top_distances = *getTopologicalDistanceMatrix(*molGraph);
	BondList::const_iterator bonds_end = bondList.end();

	for (BondList::const_iterator it = bondList.begin(); it != bonds_end; ++it) {
		const Bond& bond = **it;
		std::size_t atom1_idx = molGraph->getAtomIndex(bond.getBegin());
		std::size_t atom2_idx = molGraph->getAtomIndex(bond.getEnd());

		const Math::Vector2D& atom1_pos = localCoords[atom1_idx];
		const Math::Vector2D& atom2_pos = localCoords[atom2_idx];

		double delta_x = atom1_pos(0) - atom2_pos(0);
		double delta_y = atom1_pos(1) - atom2_pos(1);

		double diff_ratio = std::abs(std::sqrt(delta_x * delta_x + delta_y * delta_y) - DEF_BOND_LENGTH) / DEF_BOND_LENGTH;
		
		distributeWeightFactors(atom1_idx, diff_ratio, top_distances);
		distributeWeightFactors(atom2_idx, diff_ratio, top_distances);

		layoutAtomDistances(atom1_idx, atom2_idx) = DEF_BOND_LENGTH;
		layoutAtomDistances(atom2_idx, atom1_idx) = DEF_BOND_LENGTH;

		layoutSpringStrengths(atom1_idx, atom2_idx) = 2.0 * SPRING_CONSTANT;
		layoutSpringStrengths(atom2_idx, atom1_idx) = 2.0 * SPRING_CONSTANT;
	}

	RingInfoList::const_iterator rings_end = ringList.end();

	for (RingInfoList::const_iterator it = ringList.begin(); it != rings_end; ++it) {
		const RingInfo& ring_info = **it;
		std::size_t ring_size = ring_info.getSize();

		double sec_angle = M_PI * 2.0 / ring_size;
		double r = DEF_BOND_LENGTH * 0.5 / std::sin(sec_angle * 0.5);

		const Fragment& ring_frag = ring_info.getFragment();

		for (std::size_t i = 0; i < ring_size - 2; i++) {
			std::size_t atom1_idx = molGraph->getAtomIndex(ring_frag.getAtom(i));
			const Math::Vector2D& atom1_pos = localCoords[atom1_idx];

			for (std::size_t j = i + 2, k = 0; j < ring_size && k < (ring_size - 3); j++, k++) {
				std::size_t atom2_idx = molGraph->getAtomIndex(ring_frag.getAtom(j));

				double opt_dist = 2.0 * r * std::sin((j - i) * sec_angle * 0.5);

				const Math::Vector2D& atom2_pos = localCoords[atom2_idx];

				double delta_x = atom1_pos(0) - atom2_pos(0);
				double delta_y = atom1_pos(1) - atom2_pos(1);

				double diff_ratio = std::abs(std::sqrt(delta_x * delta_x + delta_y * delta_y) - opt_dist) / opt_dist;
		
				distributeWeightFactors(atom1_idx, diff_ratio, top_distances);
				distributeWeightFactors(atom2_idx, diff_ratio, top_distances);

				layoutAtomDistances(atom1_idx, atom2_idx) = opt_dist;
				layoutAtomDistances(atom2_idx, atom1_idx) = opt_dist;

				double strength = (SPRING_CONSTANT * REFERENCE_RING_SIZE) / ring_size;

				layoutSpringStrengths(atom1_idx, atom2_idx) = strength;
				layoutSpringStrengths(atom2_idx, atom1_idx) = strength;
			}
		}
	}

	AtomIndexList::const_iterator atoms_end = atomList.end();

	for (AtomIndexList::const_iterator it1 = atomList.begin(); it1 != atoms_end; ) {
		std::size_t atom1_idx = *it1;
		const Math::Vector2D& atom1_pos = localCoords[atom1_idx];

		for (AtomIndexList::const_iterator it2 = ++it1; it2 != atoms_end; ++it2) {
			std::size_t atom2_idx = *it2;
			const Math::Vector2D& atom2_pos = localCoords[atom2_idx];

			double delta_x = atom1_pos(0) - atom2_pos(0);
			double delta_y = atom1_pos(1) - atom2_pos(1);

			double squared_dist = delta_x * delta_x + delta_y * delta_y;
		
			if (squared_dist < ATOM_COLLISION_TEST_DIST * ATOM_COLLISION_TEST_DIST) {
				distributeWeightFactors(atom1_idx, 1.0, top_distances);
				distributeWeightFactors(atom2_idx, 1.0, top_distances);
			}
		}
	}

	double max_factor = *std::max_element(layoutWeightFactors.begin(), layoutWeightFactors.end());

	if (max_factor <= SPRING_LAYOUT_MIN_WEIGHT_FACTOR)
		return;

	if (max_factor > 1.0)
		std::transform(layoutWeightFactors.begin(), layoutWeightFactors.end(), layoutWeightFactors.begin(),
					   boost::bind(std::divides<double>(), _1, max_factor));

	for (AtomIndexList::const_iterator it1 = atomList.begin(); it1 != atoms_end; ) {
		std::size_t atom1_idx = *it1;

		for (AtomIndexList::const_iterator it2 = ++it1; it2 != atoms_end; ++it2) {
			std::size_t atom2_idx = *it2;

			if (layoutSpringStrengths(atom1_idx, atom2_idx) != 0.0) 
				continue;

			double top_dist = top_distances(atom1_idx, atom2_idx);
	
			layoutAtomDistances(atom1_idx, atom2_idx) = DEF_BOND_LENGTH * top_dist * std::cos(M_PI / 180.0 * 30.0);
			layoutAtomDistances(atom2_idx, atom1_idx) = layoutAtomDistances(atom1_idx, atom2_idx);

			layoutSpringStrengths(atom1_idx, atom2_idx) = layoutWeightFactors[atom1_idx] * SPRING_CONSTANT / top_dist;
			layoutSpringStrengths(atom2_idx, atom1_idx) = layoutWeightFactors[atom2_idx] * SPRING_CONSTANT / top_dist;
		} 
	} 
}

/*
 *  Kamada-Kawai Spring-Layout (based on the boost graph library implementation)
 */

void Chem::Atom2DCoordinatesGenerator::RingSysNode::performSpringLayout()
{
	const std::size_t MAX_NUM_OUTER_ITERATIONS = 2000;
	const std::size_t MAX_NUM_INNER_ITERATIONS = 500;

	AtomIndexList::const_iterator atoms_beg = atomList.begin();
	AtomIndexList::const_iterator atoms_end = atomList.end();

	std::size_t p = 0;
	double delta_p = 0.0;

	// Compute Delta_i and find max

	for (AtomIndexList::const_iterator it = atoms_beg; it != atoms_end; ++it) {
		Math::Vector2D deriv = computePartialDerivatives(*it);

		layoutEnergyDerivatives[*it] = deriv;

		double delta = std::sqrt(deriv(0) * deriv(0) + deriv(1) * deriv(1));

		if (delta > delta_p) {
            p = *it;
            delta_p = delta;
		}
	}

	double last_energy = std::numeric_limits<double>::max();
	double last_local_energy = std::numeric_limits<double>::max();

	EnergyDerivativeTable p_partials(outputCoords->getSize());

    for (std::size_t num_outer_iter = 0; 
		 num_outer_iter < MAX_NUM_OUTER_ITERATIONS && !layoutFinished(true, delta_p, last_energy, last_local_energy); 
		 num_outer_iter++) {

		// The contribution p makes to the partial derivatives of
		// each atom. Computing this (at O(n) cost) allows us to
		// update the delta_i values in O(n) time instead of O(n^2)
		// time.

		for (AtomIndexList::const_iterator it = atoms_beg; it != atoms_end; ++it) 
            p_partials[*it] = computePartialDerivative(*it, p);

		std::size_t num_inner_iter = 0;

		do {
            // Compute the 4 elements of the Jacobian

            double dE_dx_dx = 0.0, dE_dx_dy = 0.0, dE_dy_dx = 0.0, dE_dy_dy = 0.0;

			for (AtomIndexList::const_iterator it = atoms_beg; it != atoms_end; ++it) {
				std::size_t i = *it;

				if (i != p) {
					double x_diff = localCoords[p](0) - localCoords[i](0);
					double y_diff = localCoords[p](1) - localCoords[i](1);

					if (x_diff == 0.0)
						x_diff = 0.001;

					if (y_diff == 0.0)
						y_diff = 0.001;

					double dist = std::sqrt(x_diff * x_diff + y_diff * y_diff);
					double dist_cubed = dist * dist * dist;

					double k_mi = layoutSpringStrengths(p, i);
					double l_mi = layoutAtomDistances(p, i);
				
					dE_dx_dx += k_mi * (1.0 - (l_mi * y_diff * y_diff) / dist_cubed);
					dE_dx_dy += k_mi * l_mi * x_diff * y_diff / dist_cubed;
					dE_dy_dx += k_mi * l_mi * x_diff * y_diff / dist_cubed;
					dE_dy_dy += k_mi * (1.0 - (l_mi * x_diff * x_diff) / dist_cubed);
				}
			}

            // Solve for delta_x and delta_y

            double dE_dx = layoutEnergyDerivatives[p](0);
            double dE_dy = layoutEnergyDerivatives[p](1);

            double delta_x = (dE_dx_dy * dE_dy - dE_dy_dy * dE_dx) / (dE_dx_dx * dE_dy_dy - dE_dx_dy * dE_dy_dx);
            double delta_y = (dE_dx_dx * dE_dy - dE_dy_dx * dE_dx) / (dE_dy_dx * dE_dx_dy - dE_dx_dx * dE_dy_dy);

			// Move p by (delta_x, delta_y)

            localCoords[p](0) += delta_x;
            localCoords[p](1) += delta_y;

            // Recompute partial derivatives and delta_p

            Math::Vector2D deriv = computePartialDerivatives(p);

			layoutEnergyDerivatives[p] = deriv;

            delta_p = std::sqrt(deriv(0) * deriv(0) + deriv(1) * deriv(1));

			num_inner_iter++;

		} while (num_inner_iter < MAX_NUM_INNER_ITERATIONS && !layoutFinished(false, delta_p, last_energy, last_local_energy));

		// Select new p by updating each partial derivative and delta

        std::size_t old_p = p;

		for (AtomIndexList::const_iterator it = atoms_beg; it != atoms_end; ++it) {
            Math::Vector2D old_deriv_p = p_partials[*it];
            Math::Vector2D old_p_partial = computePartialDerivative(*it, old_p);

            Math::Vector2D deriv = layoutEnergyDerivatives[*it];

            deriv += old_p_partial - old_deriv_p;

			layoutEnergyDerivatives[*it] = deriv;

            double delta = std::sqrt(deriv(0) * deriv(0) + deriv(1) * deriv(1));

            if (delta > delta_p) {
				p = *it;
				delta_p = delta;
            }
		}
	}
}

/**
 * Computes partial derivatives dE/dx_m and dE/dy_m
 */

Math::Vector2D Chem::Atom2DCoordinatesGenerator::RingSysNode::computePartialDerivatives(std::size_t m) const
{
	Math::Vector2D result;

	AtomIndexList::const_iterator atoms_end = atomList.end();

	for (AtomIndexList::const_iterator it = atomList.begin(); it != atoms_end; ++it) 
		result += computePartialDerivative(m, *it);

	return result;
}

/** 
 * Computes contribution of atom i to the first partial
 * derivatives (dE/dx_m, dE/dy_m) (for atom m)
 */

Math::Vector2D Chem::Atom2DCoordinatesGenerator::RingSysNode::computePartialDerivative(std::size_t m, std::size_t i) const
{
	Math::Vector2D result;

	if (i != m) {
		double x_diff = localCoords[m](0) - localCoords[i](0);
		double y_diff = localCoords[m](1) - localCoords[i](1);

		if (x_diff == 0.0)
			x_diff = 0.001;

		if (y_diff == 0.0)
			y_diff = 0.001;

		double dist = std::sqrt(x_diff * x_diff + y_diff * y_diff);

		result(0) = layoutSpringStrengths(m, i) * (x_diff - layoutAtomDistances(m, i) * x_diff / dist);
		result(1) = layoutSpringStrengths(m, i) * (y_diff - layoutAtomDistances(m, i) * y_diff / dist);
	}

	return result;	
}

/** 
 * Determines when to terminate layout of a particular graph based
 * on a given relative tolerance. 
 */

bool Chem::Atom2DCoordinatesGenerator::RingSysNode::layoutFinished(bool global, double delta_p, double& last_energy, 
																   double& last_local_energy) const
{
	const double TOLERANCE = 0.0001;

	if (global) {
        if (last_energy == std::numeric_limits<double>::max()) {
			last_energy = delta_p;

			return false;
        }
          
        double diff = last_energy - delta_p;

        if (diff < 0.0) 
			diff = -diff;

        bool done = (delta_p == 0.0 || (diff / last_energy) < TOLERANCE);

        last_energy = delta_p;

        return done;

	} else {
        if (last_local_energy == std::numeric_limits<double>::max()) {
			last_local_energy = delta_p;
	  
			return (delta_p == 0.0);
        }
          
        double diff = last_local_energy - delta_p;
        bool done = (delta_p == 0.0 || (diff / last_local_energy) < TOLERANCE);

        last_local_energy = delta_p;

        return done;
	}
}

void Chem::Atom2DCoordinatesGenerator::RingSysNode::distributeWeightFactors(std::size_t ctr_atom_idx, double factor, 
																			const Math::ULMatrix& top_distances)
{
	AtomIndexList::const_iterator atoms_end = atomList.end();

	for (AtomIndexList::const_iterator it = atomList.begin(); it != atoms_end; ++it) {	
		std::size_t atom_idx = *it;
		double dist = top_distances(ctr_atom_idx, atom_idx) + 1;

		layoutWeightFactors[atom_idx] += factor / (dist * dist);
	}
}

void Chem::Atom2DCoordinatesGenerator::RingSysNode::calcFreeSweeps()
{
	std::vector<double> bond_angles;
	
	RingInfoList::const_iterator rings_beg = ringList.begin();
	RingInfoList::const_iterator rings_end = ringList.end();

	tmpBitMask.resize(atomMask.size());
	tmpBitMask.reset();

	EdgeListMap::const_iterator edges_end = edgeListMap.end();

	for (EdgeListMap::const_iterator it = edgeListMap.begin(); it != edges_end; ++it) {
		const Atom* atom = it->first;
		std::size_t atom_idx = molGraph->getAtomIndex(*atom);

		for (RingInfoList::const_iterator r_it = rings_beg; r_it != rings_end; ++r_it) {
			const RingInfo* ring_info = *r_it;
			const Util::BitSet& ring_atom_mask = ring_info->getAtomMask();

			if (!ring_atom_mask.test(atom_idx))
				continue;

			tmpBitMask |= ring_atom_mask;
		}

		const Math::Vector2D& atom_pos = localCoords[atom_idx];

		Atom::ConstAtomIterator nbr_atoms_end = atom->getAtomsEnd();
		Atom::ConstBondIterator b_it = atom->getBondsBegin();

		for (Atom::ConstAtomIterator a_it = atom->getAtomsBegin(); a_it != nbr_atoms_end; ++a_it, ++b_it) {
			if (!molGraph->containsAtom(*a_it) || !molGraph->containsBond(*b_it))
				continue;

			std::size_t nbr_atom_idx = molGraph->getAtomIndex(*a_it);

			if (!atomMask.test(nbr_atom_idx))
				continue;

			bond_angles.push_back(calcAngle(localCoords[nbr_atom_idx] - atom_pos));
		} 

		std::sort(bond_angles.begin(), bond_angles.end());

		std::size_t num_ring_bonds = bond_angles.size();

		double min_cf = std::numeric_limits<double>::max();

		AngleRange free_sweep;

		Math::Vector2D virt_subst_pos;	

		for (std::size_t i = 0; i < num_ring_bonds; i++) {
			double ang_lo = bond_angles[i];
			double ang_hi = (i == num_ring_bonds - 1 ? bond_angles[0] + 2.0 * M_PI : bond_angles[i + 1]);
			double med_ang = 0.5 * (ang_lo + ang_hi);

			calcPosition(atom_pos, DEF_BOND_LENGTH, med_ang, virt_subst_pos);

			double cf = calcCongestionFactor(virt_subst_pos, tmpBitMask) / (ang_hi - ang_lo);

			if (cf >= min_cf)
				continue;

			free_sweep.first = ang_lo;
			free_sweep.second = ang_hi;
			min_cf = cf;
		}

		freeSweepMap.insert(AngleRangeMap::value_type(atom, free_sweep));

		bond_angles.clear();
	}
}

double Chem::Atom2DCoordinatesGenerator::RingSysNode::calcCongestionFactor(const Math::Vector2D& pos) const
{
	double cf = 0.0;

	AtomIndexList::const_iterator atom_list_end = atomList.end();

	for (AtomIndexList::const_iterator it = atomList.begin(); it != atom_list_end; ++it) {
		Math::Vector2D pos_diff = pos - localCoords[*it];

		cf += 1.0 / (innerProd(pos_diff, pos_diff) + 0.001);
	}

	return cf;
}

double Chem::Atom2DCoordinatesGenerator::RingSysNode::calcCongestionFactor(const Math::Vector2D& pos, 
																		   const Util::BitSet& atom_mask) const
{
	double cf = 0.0;

	AtomIndexList::const_iterator atom_list_end = atomList.end();

	for (AtomIndexList::const_iterator it = atomList.begin(); it != atom_list_end; ++it) {
		std::size_t atom_idx = *it;

		if (!atom_mask.test(atom_idx))
			continue;

		Math::Vector2D pos_diff = pos - localCoords[atom_idx];

		cf += 1.0 / (innerProd(pos_diff, pos_diff) + 0.001);
	}

	return cf;
}


// - AtomNode -

void Chem::Atom2DCoordinatesGenerator::AtomNode::init(const MolecularGraph* molgraph, const Atom* atom, double p, 
													  Math::Vector2DArray& out_coords, AtomIndexList& proc_atoms,
													  BondList& proc_bonds)
{
	LGNode::init(molgraph);

	this->atom = atom;
	atomIndex = molgraph->getAtomIndex(*atom);
	isHydrogen = (Chem::getType(*atom) == AtomType::H);
	type = (atom->getNumBonds() > 1 ? CHAIN_ATOM : END_ATOM);
	priority = p;
	chainID = std::numeric_limits<std::size_t>::max();
	procAtomList = &proc_atoms;
	procBondList = &proc_bonds;
	outputCoords = &out_coords;
	chainDirection = UP;
	parentEdgeAngle = 0.0;
	parentEdge = 0;
	childLayoutIndex = 0;

	edges.clear();
	childLayouts.clear();
}

void Chem::Atom2DCoordinatesGenerator::AtomNode::addEdge(const Atom*, const LGEdge* edge)
{
	edges.push_back(edge);
}

const Chem::Atom* Chem::Atom2DCoordinatesGenerator::AtomNode::getAtom() const
{
	return atom;
}

std::size_t Chem::Atom2DCoordinatesGenerator::AtomNode::getAtomIndex() const
{
	return atomIndex;
}

void Chem::Atom2DCoordinatesGenerator::AtomNode::getChildNodes(NodeList& child_nodes) const
{
	std::size_t num_edges = edges.size();

	if (num_edges > 4) {
		EdgeList::const_iterator edges_end = edges.end();

		for (EdgeList::const_iterator e_it = edges.begin(); e_it != edges_end; ++e_it) {
			const LGEdge* edge = *e_it;
			LGNode* child_node = edge->otherNode(this);

			if (child_node->setParentEdge(edge, chainDirection))
				child_nodes.push_back(child_node);
		}

		return;
	}

	for (std::size_t i = 0; i < num_edges; i++) {
		const LGEdge* edge = edges[i];
		LGNode* child_node = edge->otherNode(this);

		if (child_node->setParentEdge(edge, childChainDirections[i]))
			child_nodes.push_back(child_node);
	}
}

void Chem::Atom2DCoordinatesGenerator::AtomNode::init() {}	

double Chem::Atom2DCoordinatesGenerator::AtomNode::getPriority() const
{
	return priority;
}

std::size_t Chem::Atom2DCoordinatesGenerator::AtomNode::getChainID() const
{
	return chainID;
}

void Chem::Atom2DCoordinatesGenerator::AtomNode::setChainID(std::size_t id)
{
	chainID = id;
}

void Chem::Atom2DCoordinatesGenerator::AtomNode::layout()
{
	(*outputCoords)[atomIndex].clear();

	procAtomList->push_back(atomIndex);
}

bool Chem::Atom2DCoordinatesGenerator::AtomNode::layout(double edge_angle, const Math::Vector2D& parent_pos, std::size_t& num_colls,
														std::size_t max_num_colls, bool strict)
{
	assert(parentEdge);

	double bond_length = (isHydrogen ? H_BOND_LENGTH : DEF_BOND_LENGTH);

	LayoutParameters opt_params(max_num_colls + 1);

	layout(edge_angle, bond_length, parent_pos, num_colls, max_num_colls, opt_params);

	if (!strict) {
		layout(edge_angle + ANGLE_BENDING_DELTA, bond_length, parent_pos, num_colls, max_num_colls, opt_params);
		layout(edge_angle - ANGLE_BENDING_DELTA, bond_length, parent_pos, num_colls, max_num_colls, opt_params);
		layout(edge_angle, bond_length - BOND_LENGTH_DELTA, parent_pos, num_colls, max_num_colls, opt_params);
		layout(edge_angle + ANGLE_BENDING_DELTA, bond_length - BOND_LENGTH_DELTA, parent_pos, num_colls, max_num_colls, opt_params);
		layout(edge_angle - ANGLE_BENDING_DELTA, bond_length - BOND_LENGTH_DELTA, parent_pos, num_colls, max_num_colls, opt_params);
		layout(edge_angle, bond_length + BOND_LENGTH_DELTA, parent_pos, num_colls, max_num_colls, opt_params);
		layout(edge_angle + ANGLE_BENDING_DELTA, bond_length + BOND_LENGTH_DELTA, parent_pos, num_colls, max_num_colls, opt_params);
		layout(edge_angle - ANGLE_BENDING_DELTA, bond_length + BOND_LENGTH_DELTA, parent_pos, num_colls, max_num_colls, opt_params);
	}

	if (opt_params.numCollisions > max_num_colls)
		return false;

	procBondList->push_back(parentEdge->getBond());
	procAtomList->push_back(atomIndex);

	parentEdgeAngle = opt_params.edgeAngle;
	num_colls = opt_params.numCollisions;

	calcPosition(parent_pos, opt_params.bondLength, opt_params.edgeAngle, (*outputCoords)[atomIndex]);

	return true;
}

bool Chem::Atom2DCoordinatesGenerator::AtomNode::layoutChildNodes(std::size_t& num_colls, std::size_t max_num_colls, bool strict)
{
	if (childLayouts.empty())
		return true;

	std::size_t num_child_layouts = childLayouts.size();

	const Math::Vector2D& atom_pos = (*outputCoords)[atomIndex];

	for (std::size_t saved_num_colls = num_colls, saved_alist_size = procAtomList->size(), saved_blist_size = procBondList->size();
		 childLayoutIndex < num_child_layouts; 
		 num_colls = saved_num_colls, procAtomList->resize(saved_alist_size), procBondList->resize(saved_blist_size)) {

		const NodeLayoutInfoList& layout_infos = childLayouts[childLayoutIndex++];

		NodeLayoutInfoList::const_iterator layout_infos_end = layout_infos.end();
		NodeLayoutInfoList::const_iterator it = layout_infos.begin();

		for ( ; it != layout_infos_end; ++it) {
			const NodeLayoutInfo& layout_info = *it;
			const LGEdge* edge = layout_info.edge;

			LGNode* child_node = edge->otherNode(this);

			if (!child_node->layout(layout_info.angle + parentEdgeAngle, atom_pos, num_colls, max_num_colls, strict))
				break;
		}

		if (it == layout_infos_end && (!parentEdge || parentEdge->configConstraintFulfilled(*outputCoords)))
			return true;
	}

	childLayoutIndex = 0;

	return false;
}

Chem::Atom2DCoordinatesGenerator::LGNode::Type Chem::Atom2DCoordinatesGenerator::AtomNode::getType() const
{
	return type;
}		

bool Chem::Atom2DCoordinatesGenerator::AtomNode::setParentEdge(const LGEdge* parent_edge, Direction chain_dir)
{
	assert(!parentEdge);

	parentEdge = parent_edge;
	chainDirection = chain_dir;

	createChildLayouts();

	return !edges.empty();
}

void Chem::Atom2DCoordinatesGenerator::AtomNode::layout(double edge_angle, double bond_length, const Math::Vector2D& parent_pos,
														std::size_t num_colls, std::size_t max_num_colls, 
														LayoutParameters& opt_params)
{
	if (opt_params.numCollisions <= num_colls)
		return;

	calcPosition(parent_pos, bond_length, edge_angle, (*outputCoords)[atomIndex]);

	const Bond* parent_edge_bond = parentEdge->getBond();

	num_colls += countAtomCollisionsForAtom(atomIndex, *procAtomList, *outputCoords)
		+ countBondCollisionsForBond(parent_edge_bond, *procBondList, *outputCoords) * 2
		+ countBondCollisionsForAtom(atomIndex, *procBondList, *outputCoords)
		+ countAtomCollisionsForBond(parent_edge_bond, *procAtomList, *outputCoords);

	if (num_colls >= opt_params.numCollisions) 
		return;

	opt_params.numCollisions = num_colls;
	opt_params.edgeAngle = edge_angle;
	opt_params.bondLength = bond_length;
}

std::size_t Chem::Atom2DCoordinatesGenerator::AtomNode::getChildNodeTypePattern() const
{
	assert(edges.size() + (parentEdge ? 1 : 0) <= 4);

	std::size_t pattern = 0;

	if (parentEdge) 
		pattern = std::size_t(parentEdge->otherNode(this)->getType());

	EdgeList::const_iterator edges_end = edges.end();

	for (EdgeList::const_iterator it = edges.begin(); it != edges_end; ++it) 
		pattern = (pattern << 2) | std::size_t((*it)->otherNode(this)->getType());
	
	return pattern;
}

#define NODE_TYPE_PATTERN_D3(t1, t2, t3)     ((std::size_t(t1) << 4) | (std::size_t(t2) << 2) | std::size_t(t3))
#define NODE_TYPE_PATTERN_D4(t1, t2, t3, t4) ((std::size_t(t1) << 6) | (std::size_t(t2) << 4) | (std::size_t(t3) << 2) | \
											  std::size_t(t4))
#define INVERT(dir)                          ((dir) == UP ? DOWN : UP)

void Chem::Atom2DCoordinatesGenerator::AtomNode::createChildLayouts()
{
	switch (edges.size()) {

		case 0:
			return;

		case 1:
			createChildLayoutsD1();
			return;

		case 2:
			createChildLayoutsD2();
			return;

		case 3:
			createChildLayoutsD3();
			return;

		case 4:
			createChildLayoutsD4();
			return;

		default:
			createChildLayoutsDN();
	}
}

void Chem::Atom2DCoordinatesGenerator::AtomNode::createChildLayoutsD1()
{
	if (parentEdge) {
		removeParentEdge();
		return;
	}

	childChainDirections[0] = DOWN; 

	childLayouts.resize(1);

	childLayouts[0].push_back(NodeLayoutInfo(edges[0], 30.0 * M_PI / 180.0));
}

void Chem::Atom2DCoordinatesGenerator::AtomNode::createChildLayoutsD2()
{
	unsigned int hybridization = HybridizationState::UNKNOWN;

	try {
		assert(atom);
		assert(molGraph);

		hybridization = getHybridizationState(*atom);

	} catch (const Base::Exception&) {}

	if (parentEdge) {
		removeParentEdge();

		childChainDirections[0] = INVERT(chainDirection); 

		if (hybridization  == HybridizationState::SP) {
			childLayouts.resize(1);

			childLayouts[0].push_back(NodeLayoutInfo(edges[0], 0.0));

		} else {
			childLayouts.resize(2);

			int sign = (chainDirection == UP ? 1 : -1);

			childLayouts[0].push_back(NodeLayoutInfo(edges[0], sign * 60.0 * M_PI / 180.0));
			childLayouts[1].push_back(NodeLayoutInfo(edges[0], -sign * 60.0 * M_PI / 180.0));
		}

		return;
	}

	childChainDirections[0] = DOWN; 
	childChainDirections[1] = UP; 

	childLayouts.resize(1);

	childLayouts[0].reserve(2);

	if (hybridization != HybridizationState::SP) {
		childLayouts[0].push_back(NodeLayoutInfo(edges[0], 30.0 * M_PI / 180.0));
		childLayouts[0].push_back(NodeLayoutInfo(edges[1], 150.0 * M_PI / 180.0));

	} else {
		childLayouts[0].push_back(NodeLayoutInfo(edges[0], 0.0));
		childLayouts[0].push_back(NodeLayoutInfo(edges[1], M_PI));
	}
}

void Chem::Atom2DCoordinatesGenerator::AtomNode::createChildLayoutsD3()
{
	if (parentEdge) {
		removeParentEdge();
		sortChildEdges();

		childLayouts.resize(2);

		childLayouts[0].reserve(2);
		childLayouts[1].reserve(2);

		int sign = (chainDirection == UP ? 1 : -1);

		childLayouts[0].push_back(NodeLayoutInfo(edges[0], sign * 60.0 * M_PI / 180.0));
		childLayouts[0].push_back(NodeLayoutInfo(edges[1], -sign * 60.0 * M_PI / 180.0));

		childLayouts[1].push_back(NodeLayoutInfo(edges[1], sign * 60.0 * M_PI / 180.0));
		childLayouts[1].push_back(NodeLayoutInfo(edges[0], -sign * 60.0 * M_PI / 180.0));

		removeChildLayoutSymmetryDuplicates();

		switch (getChildNodeTypePattern()) {

			case NODE_TYPE_PATTERN_D3(CHAIN_ATOM, CHAIN_ATOM, CHAIN_ATOM):
				if (edges[0]->otherNode(this)->getChainID() != edges[1]->otherNode(this)->getChainID()) {
					childChainDirections[0] = INVERT(chainDirection);
					childChainDirections[1] = childChainDirections[0];
					return;
				}

			case NODE_TYPE_PATTERN_D3(RING_SYS, CHAIN_ATOM, CHAIN_ATOM):
			case NODE_TYPE_PATTERN_D3(END_ATOM, CHAIN_ATOM, CHAIN_ATOM):
				childChainDirections[0] = chainDirection;
			childChainDirections[1] = INVERT(chainDirection);
			return;

			default:
				childChainDirections[0] = INVERT(chainDirection);
				childChainDirections[1] = chainDirection;
				return;
		}
	}

	sortChildEdges();

	childLayouts.resize(1);

	childLayouts[0].reserve(3);

	childLayouts[0].push_back(NodeLayoutInfo(edges[0], 30.0 * M_PI / 180.0));
	childLayouts[0].push_back(NodeLayoutInfo(edges[1], 150.0 * M_PI / 180.0));
	childLayouts[0].push_back(NodeLayoutInfo(edges[2], 270.0 * M_PI / 180.0));

	childChainDirections[0] = DOWN;
	childChainDirections[1] = UP;
	childChainDirections[2] = UP;
}

void Chem::Atom2DCoordinatesGenerator::AtomNode::createChildLayoutsD4()
{
	std::size_t num_perms = 6;
	double start_angle = 0.5 * M_PI;

	if (parentEdge) {
		removeParentEdge();
		sortChildEdges();

		childChainDirections[0] = chainDirection;
		childChainDirections[1] = chainDirection;
		childChainDirections[2] = chainDirection;

		switch (getChildNodeTypePattern()) {

			case NODE_TYPE_PATTERN_D4(RING_SYS, RING_SYS, END_ATOM, END_ATOM):
			case NODE_TYPE_PATTERN_D4(RING_SYS, CHAIN_ATOM, END_ATOM, END_ATOM):
			case NODE_TYPE_PATTERN_D4(CHAIN_ATOM, RING_SYS, END_ATOM, END_ATOM):
			case NODE_TYPE_PATTERN_D4(CHAIN_ATOM, CHAIN_ATOM, END_ATOM, END_ATOM): { 
				childLayouts.resize(2);

				childLayouts[0].reserve(3);
				childLayouts[1].reserve(3);

				int sign = (chainDirection == UP ? 1 : -1);
				
				childLayouts[0].push_back(NodeLayoutInfo(edges[0], sign * 60.0 * M_PI / 180.0));
				childLayouts[0].push_back(NodeLayoutInfo(edges[1], -sign * 20.0 * M_PI / 180.0));
				childLayouts[0].push_back(NodeLayoutInfo(edges[2], -sign * 100.0 * M_PI / 180.0));

				childLayouts[1].push_back(NodeLayoutInfo(edges[0], -sign * 60.0 * M_PI / 180.0));
				childLayouts[1].push_back(NodeLayoutInfo(edges[1], sign * 20.0 * M_PI / 180.0));
				childLayouts[1].push_back(NodeLayoutInfo(edges[2], sign * 100.0 * M_PI / 180.0));

				childChainDirections[0] = INVERT(chainDirection);
				return;
			}

			case NODE_TYPE_PATTERN_D4(CHAIN_ATOM, CHAIN_ATOM, CHAIN_ATOM, CHAIN_ATOM):
			case NODE_TYPE_PATTERN_D4(CHAIN_ATOM, CHAIN_ATOM, CHAIN_ATOM, END_ATOM):
			case NODE_TYPE_PATTERN_D4(CHAIN_ATOM, CHAIN_ATOM, CHAIN_ATOM, RING_SYS):
				if (edges[0]->otherNode(this)->getChainID() == edges[1]->otherNode(this)->getChainID()) 
					std::swap(edges[1], edges[2]);
				else
					std::swap(edges[0], edges[1]);
			break;

			case NODE_TYPE_PATTERN_D4(CHAIN_ATOM, CHAIN_ATOM, RING_SYS, END_ATOM):
				std::swap(edges[0], edges[1]);
				break;

			case NODE_TYPE_PATTERN_D4(RING_SYS, CHAIN_ATOM, CHAIN_ATOM, CHAIN_ATOM):
			case NODE_TYPE_PATTERN_D4(RING_SYS, CHAIN_ATOM, CHAIN_ATOM, END_ATOM):
			case NODE_TYPE_PATTERN_D4(RING_SYS, CHAIN_ATOM, CHAIN_ATOM, RING_SYS):
			case NODE_TYPE_PATTERN_D4(END_ATOM, CHAIN_ATOM, CHAIN_ATOM, CHAIN_ATOM):
			case NODE_TYPE_PATTERN_D4(END_ATOM, CHAIN_ATOM, CHAIN_ATOM, RING_SYS):
			case NODE_TYPE_PATTERN_D4(END_ATOM, CHAIN_ATOM, RING_SYS, END_ATOM):
				std::swap(edges[1], edges[2]);
			break;

			case NODE_TYPE_PATTERN_D4(END_ATOM, CHAIN_ATOM, CHAIN_ATOM, END_ATOM):
				childLayouts.resize(1);

				childLayouts[0].reserve(3);

				childLayouts[0].push_back(NodeLayoutInfo(edges[2], 100.0 * M_PI / 180.0));
				childLayouts[0].push_back(NodeLayoutInfo(edges[0], 20.0 * M_PI / 180.0));
				childLayouts[0].push_back(NodeLayoutInfo(edges[1], 260.0 * M_PI / 180.0));

				childChainDirections[0] = UP;
				childChainDirections[1] = DOWN;
				return;

			default:
				break;
		}

	} else {
		sortChildEdges();

		childChainDirections[1] = UP;
		childChainDirections[2] = UP;
		childChainDirections[3] = UP;

		switch (getChildNodeTypePattern()) {

			case NODE_TYPE_PATTERN_D4(CHAIN_ATOM, CHAIN_ATOM, END_ATOM, END_ATOM):
				childLayouts.resize(1);

				childLayouts[0].reserve(4);
				
				childLayouts[0].push_back(NodeLayoutInfo(edges[0], 30.0 * M_PI / 180.0));
				childLayouts[0].push_back(NodeLayoutInfo(edges[1], 150.0 * M_PI / 180.0));
				childLayouts[0].push_back(NodeLayoutInfo(edges[2], 230.0 * M_PI / 180.0));
				childLayouts[0].push_back(NodeLayoutInfo(edges[3], 310.0 * M_PI / 180.0));

				childChainDirections[0] = DOWN;
				return;

			case NODE_TYPE_PATTERN_D4(CHAIN_ATOM, CHAIN_ATOM, CHAIN_ATOM, END_ATOM):
			case NODE_TYPE_PATTERN_D4(CHAIN_ATOM, CHAIN_ATOM, CHAIN_ATOM, RING_SYS):
			case NODE_TYPE_PATTERN_D4(CHAIN_ATOM, CHAIN_ATOM, RING_SYS, END_ATOM):
			case NODE_TYPE_PATTERN_D4(CHAIN_ATOM, RING_SYS, END_ATOM, END_ATOM):
			case NODE_TYPE_PATTERN_D4(CHAIN_ATOM, CHAIN_ATOM, CHAIN_ATOM, CHAIN_ATOM):
				std::swap(edges[1], edges[2]);

			default:
				break;
		}

		childChainDirections[0] = UP;

		start_angle = M_PI;
		num_perms = 24;
	}

	childLayouts.resize(num_perms);

	std::size_t num_edges = edges.size();

	EdgeList::iterator edges_beg = edges.begin();
	EdgeList::iterator edges_end = edges.end();

	for (std::size_t i = 0; i < num_perms; i++) {
		double edge_angle = start_angle;

		childLayouts[i].reserve(num_edges);

		for (EdgeList::const_iterator it = edges_beg; it != edges_end; ++it, edge_angle -= 0.5 * M_PI) {
			const LGEdge* edge = *it;

			childLayouts[i].push_back(NodeLayoutInfo(edge, edge_angle));
		}

		std::next_permutation(edges_beg, edges_end);
	}

	removeChildLayoutSymmetryDuplicates();
}

void Chem::Atom2DCoordinatesGenerator::AtomNode::createChildLayoutsDN()
{
	EdgeList::iterator edges_beg = edges.begin();
	EdgeList::iterator edges_end = edges.end();

	bool min_priority = true;

	for (EdgeList::iterator it1 = edges_beg; it1 != edges_end; ++it1, min_priority = !min_priority) {
		EdgeList::iterator it2 = (min_priority ?
								  std::min_element(it1, edges_end, LinkedNodePriorityLessCmpFunc(this)) :
								  std::max_element(it1, edges_end, LinkedNodePriorityLessCmpFunc(this)));

		std::iter_swap(it1, it2);
	}

	std::size_t num_edges = edges.size();
	double angle_inc = 2.0 * M_PI / num_edges;

	if (parentEdge) {
		EdgeList::iterator parent_it = std::find_if(edges_beg, edges_end,
													boost::bind(std::equal_to<const Bond*>(), parentEdge->getBond(),
																boost::bind(&LGEdge::getBond, _1)));
		assert(parent_it != edges_end);

		std::rotate(edges_beg, parent_it, edges_end);

		assert((*edges_beg)->getBond() == parentEdge->getBond());

		std::iter_swap(edges_beg, --edges_end);

		edges.erase(edges_end);
	
		num_edges--;
	}

	std::size_t num_perms = Math::factorial<std::size_t>(num_edges);

	childLayouts.resize(num_perms);

	for (std::size_t i = 0; i < num_perms; i++) {
		double edge_angle = M_PI + angle_inc;

		childLayouts[i].reserve(num_edges);

		for (EdgeList::const_iterator it = edges_beg; it != edges_end; ++it, edge_angle += angle_inc) {
			const LGEdge* edge = *it;

			childLayouts[i].push_back(NodeLayoutInfo(edge, edge_angle));
		}

		std::next_permutation(edges_beg, edges_end);
	}

	removeChildLayoutSymmetryDuplicates();
}

void Chem::Atom2DCoordinatesGenerator::AtomNode::removeChildLayoutSymmetryDuplicates()
{
	if (parentEdge && parentEdge->hasConfigConstraint())
		return;

	NodeLayoutInfoListTable::iterator layouts_end = childLayouts.end();

	for (NodeLayoutInfoListTable::iterator it = childLayouts.begin(); it != layouts_end; ) {
		const NodeLayoutInfoList& layout_infos = *it;
		
		layouts_end = std::remove_if(++it, layouts_end, NodeLayoutInfoListEqualCmpFunc(this, layout_infos));
	}

	childLayouts.erase(layouts_end, childLayouts.end());
}

void Chem::Atom2DCoordinatesGenerator::AtomNode::removeParentEdge()
{
	assert(parentEdge);

	EdgeList::iterator parent_it = std::remove_if(edges.begin(), edges.end(), 
												  boost::bind(std::equal_to<const Bond*>(), parentEdge->getBond(),
															  boost::bind(&LGEdge::getBond, _1)));

	assert(parent_it != edges.end());

	edges.erase(parent_it, edges.end());
}

void Chem::Atom2DCoordinatesGenerator::AtomNode::sortChildEdges()
{
	std::sort(edges.begin(), edges.end(), EdgePriorityGreaterCmpFunc(this));	
}
