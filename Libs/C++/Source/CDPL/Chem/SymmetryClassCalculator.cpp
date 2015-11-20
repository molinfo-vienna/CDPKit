/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * SymmetryClassCalculator.cpp 
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
#include <numeric>

#include <boost/bind.hpp>

#include "CDPL/Chem/SymmetryClassCalculator.hpp"
#include "CDPL/Chem/Atom.hpp"
#include "CDPL/Chem/Bond.hpp"
#include "CDPL/Chem/AtomFunctions.hpp"
#include "CDPL/Chem/BondFunctions.hpp"
#include "CDPL/Chem/AtomType.hpp"
#include "CDPL/Math/PrimeNumberTable.hpp"


using namespace CDPL;


const unsigned int Chem::SymmetryClassCalculator::DEF_ATOM_PROPERTY_FLAGS;
const unsigned int Chem::SymmetryClassCalculator::DEF_BOND_PROPERTY_FLAGS;


Chem::SymmetryClassCalculator::SymmetryClassCalculator(): 
	atomPropertyFlags(DEF_ATOM_PROPERTY_FLAGS), bondPropertyFlags(DEF_BOND_PROPERTY_FLAGS), hComplete(true) {}

Chem::SymmetryClassCalculator::SymmetryClassCalculator(const MolecularGraph& molgraph):
	atomPropertyFlags(DEF_ATOM_PROPERTY_FLAGS), bondPropertyFlags(DEF_BOND_PROPERTY_FLAGS), hComplete(true)
{
	calculate(molgraph);
}

void Chem::SymmetryClassCalculator::setAtomPropertyFlags(unsigned int flags)
{
	atomPropertyFlags = flags;
}

void Chem::SymmetryClassCalculator::setBondPropertyFlags(unsigned int flags)
{
	bondPropertyFlags = flags;
}

void Chem::SymmetryClassCalculator::includeImplicitHydrogens(bool include)
{
	hComplete = include;
}

unsigned int Chem::SymmetryClassCalculator::getAtomPropertyFlags() const
{
	return atomPropertyFlags;
}

unsigned int Chem::SymmetryClassCalculator::getBondPropertyFlags() const
{
	return bondPropertyFlags;
}

bool Chem::SymmetryClassCalculator::implicitHydrogensIncluded() const
{
	return hComplete;
}

const Util::STArray& Chem::SymmetryClassCalculator::calculate(const MolecularGraph& molgraph)
{
	init(molgraph);

	calcSVMNumbers();
	perceiveSymClasses(molgraph);

	return symClassIDs;
}

const Util::STArray& Chem::SymmetryClassCalculator::getResult() const
{
	return symClassIDs;
}

void Chem::SymmetryClassCalculator::init(const MolecularGraph& molgraph)
{
	const std::size_t ATOMIC_NO_PRIME_TAB_IDX = 0;
	const std::size_t ISO_PRIME_TAB_IDX = ATOMIC_NO_PRIME_TAB_IDX + AtomType::MAX_TYPE + 1; 
	const std::size_t CHARGE_PRIME_TAB_IDX = ISO_PRIME_TAB_IDX + 3 * AtomType::MAX_TYPE; 
	const std::size_t AROMATICITY_PRIME_TAB_IDX = CHARGE_PRIME_TAB_IDX + 20; 

	const Base::uint64 IMPL_H_INIT_SYM_CLASS_ID = 1 
		* (atomPropertyFlags & AtomPropertyFlag::TYPE ? Math::PrimeNumberTable::getPrimeNumber(ATOMIC_NO_PRIME_TAB_IDX + 1) : 1)
		* (atomPropertyFlags & AtomPropertyFlag::ISOTOPE ? Math::PrimeNumberTable::getPrimeNumber(ISO_PRIME_TAB_IDX) : 1)
		* (atomPropertyFlags & AtomPropertyFlag::FORMAL_CHARGE ? Math::PrimeNumberTable::getPrimeNumber(CHARGE_PRIME_TAB_IDX + 10) : 1);

	std::size_t num_atoms = molgraph.getNumAtoms();

	allocAtomNodes.clear();
	allocAtomNodes.reserve(num_atoms * 2);

	allocImplHNodes.clear();
	allocImplHNodes.reserve(num_atoms);

	sortedAtomNodes.clear();
	sortedAtomNodes.reserve(num_atoms * 2);

	symClassIDs.clear();
	symClassIDs.reserve(num_atoms);

	MolecularGraph::ConstAtomIterator atoms_end = molgraph.getAtomsEnd();

	for (MolecularGraph::ConstAtomIterator it = molgraph.getAtomsBegin(); it != atoms_end; ++it) {
		const Atom& atom = *it;

		Base::uint64 init_sym_class_id = 1;
		
		if (atomPropertyFlags & AtomPropertyFlag::TYPE) {
			unsigned int atom_type = getType(atom) % (AtomType::MAX_TYPE + 1);

			init_sym_class_id = Math::PrimeNumberTable::getPrimeNumber(atom_type);
		}

		if (atomPropertyFlags & AtomPropertyFlag::ISOTOPE) {
			std::size_t isotope = getIsotope(atom) % (AtomType::MAX_TYPE * 3);
			
			init_sym_class_id *= Math::PrimeNumberTable::getPrimeNumber(ISO_PRIME_TAB_IDX + isotope);
		}

		if (atomPropertyFlags & AtomPropertyFlag::FORMAL_CHARGE) {
			long charge = getFormalCharge(atom);
			
			if (charge < 0)
				init_sym_class_id *= Math::PrimeNumberTable::getPrimeNumber(CHARGE_PRIME_TAB_IDX + 10 - std::size_t(-charge % 10));
			else
				init_sym_class_id *= Math::PrimeNumberTable::getPrimeNumber(CHARGE_PRIME_TAB_IDX + 10 + std::size_t(charge % 10));
		}
	
		if (atomPropertyFlags & AtomPropertyFlag::AROMATICITY) {
			if (getAromaticityFlag(atom))
				init_sym_class_id *= Math::PrimeNumberTable::getPrimeNumber(AROMATICITY_PRIME_TAB_IDX);
		}

		AtomNode::SharedPointer atom_node_ptr(new AtomNode(init_sym_class_id));
		allocAtomNodes.push_back(atom_node_ptr);

		AtomNode* atom_node = atom_node_ptr.get();

		if (hComplete) {
			std::size_t impl_h_count = getImplicitHydrogenCount(atom);

			if (impl_h_count > 0) {
				AtomNode::SharedPointer h_node_ptr(new AtomNode(IMPL_H_INIT_SYM_CLASS_ID));
				allocImplHNodes.push_back(h_node_ptr);

				AtomNode* h_node = h_node_ptr.get();

				for (std::size_t i = 0; i < impl_h_count; i++)
					atom_node->addNbrNode(h_node);

				h_node->addNbrNode(atom_node);

				sortedAtomNodes.push_back(h_node);
			}
		}

		sortedAtomNodes.push_back(atom_node);
	}

	MolecularGraph::ConstBondIterator bonds_end = molgraph.getBondsEnd();

	for (MolecularGraph::ConstBondIterator it = molgraph.getBondsBegin(); it != bonds_end; ++it) {
		const Bond& bond = *it;

		if (!molgraph.containsAtom(bond.getBegin()) || !molgraph.containsAtom(bond.getEnd()))
			continue;

		AtomNode* atom_node1 = allocAtomNodes[molgraph.getAtomIndex(bond.getBegin())].get();
		AtomNode* atom_node2 = allocAtomNodes[molgraph.getAtomIndex(bond.getEnd())].get();

		std::size_t bond_order = 1;

		if (bondPropertyFlags & BondPropertyFlag::ORDER)
			if (!(bondPropertyFlags & BondPropertyFlag::AROMATICITY) || !getAromaticityFlag(bond))
				bond_order = getOrder(bond);

		for (std::size_t i = 0; i < bond_order; i++) {
			atom_node1->addNbrNode(atom_node2);
			atom_node2->addNbrNode(atom_node1);
		}
	}

	allocAtomNodes.insert(allocAtomNodes.end(), allocImplHNodes.begin(), allocImplHNodes.end());
}

void Chem::SymmetryClassCalculator::calcSVMNumbers()
{
	NodeList::iterator sorted_nodes_begin = sortedAtomNodes.begin();
	NodeList::iterator sorted_nodes_end = sortedAtomNodes.end();

	AtomNode::SVMNumberCmpFunc cmp_func;

	AllocNodeList::iterator nodes_begin = allocAtomNodes.begin();
	AllocNodeList::iterator nodes_end = allocAtomNodes.end();

	for (AllocNodeList::iterator it = nodes_begin; it != nodes_end; ) {
		AtomNode& node = *it->get();

		std::for_each(nodes_begin, it, boost::bind(&AtomNode::setSVMNumber, _1, 0)); 
		std::for_each(++it, nodes_end, boost::bind(&AtomNode::setSVMNumber, _1, 0)); 

		node.setSVMNumber(1);

		std::size_t max_num_classes = 0;	

		while (true) {
			std::for_each(sorted_nodes_begin, sorted_nodes_end, std::mem_fun(&AtomNode::calcNextSVMNumber));
			std::for_each(sorted_nodes_begin, sorted_nodes_end, std::mem_fun(&AtomNode::updateSVMNumber));

			std::sort(sorted_nodes_begin, sorted_nodes_end, cmp_func);

			std::size_t num_classes = 0;

			for (NodeList::iterator it2 = sorted_nodes_begin; it2 != sorted_nodes_end; num_classes++)
				it2 = std::upper_bound(it2, sorted_nodes_end, *it2, cmp_func);

			if (num_classes <= max_num_classes)
				break;

			node.updateSVMHistory();

			max_num_classes = num_classes;
		}
	}
}

void Chem::SymmetryClassCalculator::perceiveSymClasses(const MolecularGraph& molgraph)
{
	NodeList::iterator sorted_nodes_begin = sortedAtomNodes.begin();
	NodeList::iterator sorted_nodes_end = sortedAtomNodes.end();

	AtomNode::SymClassCmpFunc cmp_func;

	std::size_t max_num_classes = 0;	

	while (true) {
		std::sort(sorted_nodes_begin, sorted_nodes_end, cmp_func);

		std::size_t num_classes = 0;

		for (NodeList::iterator it = sorted_nodes_begin; it != sorted_nodes_end; num_classes++) {
			NodeList::iterator ub = std::upper_bound(it, sorted_nodes_end, *it, cmp_func);

			std::for_each(it, ub, std::bind2nd(std::mem_fun(&AtomNode::setNextSymClassID), 
											   Math::PrimeNumberTable::getPrimeNumber(num_classes)));
			it = ub;
		}

		if (num_classes <= max_num_classes)
			break;

		std::for_each(sorted_nodes_begin, sorted_nodes_end, std::mem_fun(&AtomNode::update));

		max_num_classes = num_classes;
	}

	std::for_each(allocAtomNodes.begin(), allocAtomNodes.end() + molgraph.getNumAtoms(), 
				  boost::bind(&Util::STArray::addElement, boost::ref(symClassIDs), boost::bind(&AtomNode::getSymClassID, _1)));
}


Chem::SymmetryClassCalculator::AtomNode::AtomNode(Base::uint64 class_id): 
	symClassID(class_id), nextSymClassID(0), nbrSymClassIDProd(0) {}

void Chem::SymmetryClassCalculator::AtomNode::addNbrNode(AtomNode* nbr_node)
{
	nbrNodes.push_back(nbr_node);
}

void Chem::SymmetryClassCalculator::AtomNode::setSVMNumber(Base::uint64 no)
{
	svmNumber = no;
}

void Chem::SymmetryClassCalculator::AtomNode::calcNextSVMNumber()
{
	nextSVMNumber = std::accumulate(nbrNodes.begin(), nbrNodes.end(), svmNumber,
									boost::bind(std::plus<Base::uint64>(), _1, 
												boost::bind(&AtomNode::svmNumber, _2)));
}

void Chem::SymmetryClassCalculator::AtomNode::updateSVMNumber()
{
	svmNumber = nextSVMNumber;
}

void Chem::SymmetryClassCalculator::AtomNode::updateSVMHistory()
{
	svmNumberHistory.push_back(svmNumber);
}

void Chem::SymmetryClassCalculator::AtomNode::setNextSymClassID(Base::uint64 class_id)
{
	nextSymClassID = class_id;
}

void Chem::SymmetryClassCalculator::AtomNode::update()
{
	nbrSymClassIDProd = std::accumulate(nbrNodes.begin(), nbrNodes.end(), 1,
										boost::bind(std::multiplies<Base::uint64>(), _1, 
													boost::bind(&AtomNode::nextSymClassID, _2)));
	symClassID = nextSymClassID;
}

std::size_t Chem::SymmetryClassCalculator::AtomNode::getSymClassID() const
{
	return std::size_t(symClassID);
}


inline bool Chem::SymmetryClassCalculator::AtomNode::SymClassCmpFunc::operator()(const AtomNode* node1, 
																				 const AtomNode* node2) const
{
	if (node1->symClassID == node2->symClassID) {
		if (node1->nbrSymClassIDProd == node2->nbrSymClassIDProd)
			return std::lexicographical_compare(node1->svmNumberHistory.rbegin(), node1->svmNumberHistory.rend(),
												node2->svmNumberHistory.rbegin(), node2->svmNumberHistory.rend());

		return (node1->nbrSymClassIDProd < node2->nbrSymClassIDProd);
	}

	return (node1->symClassID < node2->symClassID);
}


inline bool Chem::SymmetryClassCalculator::AtomNode::SVMNumberCmpFunc::operator()(const AtomNode* node1, 
																				  const AtomNode* node2) const
{
	return (node1->svmNumber < node2->svmNumber);
}

