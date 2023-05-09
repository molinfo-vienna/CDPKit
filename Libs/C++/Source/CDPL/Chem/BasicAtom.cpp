/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * BasicAtom.cpp 
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
#include <functional>

#include <boost/bind.hpp>

#include "CDPL/Chem/BasicAtom.hpp"
#include "CDPL/Chem/BasicBond.hpp"
#include "CDPL/Chem/BasicMolecule.hpp"
#include "CDPL/Base/Exceptions.hpp"


using namespace CDPL;


Chem::BasicAtom::BasicAtom(BasicMolecule* mol): molecule(mol) {}
 
Chem::BasicAtom::~BasicAtom() {}

std::size_t Chem::BasicAtom::getIndex() const
{
	return index;
}

const Chem::Molecule& Chem::BasicAtom::getMolecule() const
{
	return *molecule;
}

Chem::Molecule& Chem::BasicAtom::getMolecule()
{
	return *molecule;
}

std::size_t Chem::BasicAtom::getNumAtoms() const
{
	return neighbors.size();
}

std::size_t Chem::BasicAtom::getNumBonds() const
{
	return neighbors.size();
}

const Chem::Bond& Chem::BasicAtom::getBond(std::size_t idx) const
{
	if (idx >= neighbors.size())
		throw Base::IndexError("BasicAtom: bond index out of bounds");

	return *neighbors[idx].second;
}

Chem::Bond& Chem::BasicAtom::getBond(std::size_t idx)
{
	if (idx >= neighbors.size())
		throw Base::IndexError("BasicAtom: bond index out of bounds");

	return *neighbors[idx].second;
}

const Chem::Bond& Chem::BasicAtom::getBondToAtom(const Atom& atom) const
{
	NeighborList::const_iterator it = std::find_if(neighbors.begin(), neighbors.end(),
												   boost::bind(std::equal_to<const Atom*>(), 
															   &atom, boost::bind(&AtomBondPair::first, _1)));
	if (it == neighbors.end())
		throw Base::ItemNotFound("BasicAtom: argument atom is not a bonded neighbor");

	return *it->second;
}

Chem::Bond& Chem::BasicAtom::getBondToAtom(const Atom& atom)
{
	NeighborList::const_iterator it = std::find_if(neighbors.begin(), neighbors.end(),
												   boost::bind(std::equal_to<const Atom*>(), 
															   &atom, boost::bind(&AtomBondPair::first, _1)));
	if (it == neighbors.end())
		throw Base::ItemNotFound("BasicAtom: argument atom is not a bonded neighbor");

	return *it->second;
}

const Chem::Bond* Chem::BasicAtom::findBondToAtom(const Atom& atom) const
{
	NeighborList::const_iterator it = std::find_if(neighbors.begin(), neighbors.end(),
												   boost::bind(std::equal_to<const Atom*>(), 
															   &atom, boost::bind(&AtomBondPair::first, _1)));
	return (it == neighbors.end() ? 0 : it->second);
}

Chem::Bond* Chem::BasicAtom::findBondToAtom(const Atom& atom)
{
	NeighborList::const_iterator it = std::find_if(neighbors.begin(), neighbors.end(),
												   boost::bind(std::equal_to<const Atom*>(), 
															   &atom, boost::bind(&AtomBondPair::first, _1)));
	return (it == neighbors.end() ? 0 : it->second);
}

const Chem::Atom& Chem::BasicAtom::getAtom(std::size_t idx) const
{
	if (idx >= neighbors.size())
		throw Base::IndexError("BasicAtom: atom index out of bounds");

	return *neighbors[idx].first;
}

Chem::Atom& Chem::BasicAtom::getAtom(std::size_t idx)
{
	if (idx >= neighbors.size())
		throw Base::IndexError("BasicAtom: atom index out of bounds");

	return *neighbors[idx].first;
}

void Chem::BasicAtom::orderAtoms(const AtomCompareFunction& func)
{
	std::sort(neighbors.begin(), neighbors.end(), 
			  boost::bind(func, boost::bind(AtomAccessor<const BasicAtom>(), _1), 
						  boost::bind(AtomAccessor<const BasicAtom>(), _2)));
}

void Chem::BasicAtom::orderBonds(const BondCompareFunction& func)
{
	std::sort(neighbors.begin(), neighbors.end(), 
			  boost::bind(func, boost::bind(BondAccessor<const BasicBond>(), _1), 
						  boost::bind(BondAccessor<const BasicBond>(), _2)));
}

Chem::BasicAtom::ConstAtomIterator Chem::BasicAtom::getAtomsBegin() const
{
	return ConstAtomIterator(neighbors.begin(), AtomAccessor<const BasicAtom>());
}

Chem::BasicAtom::ConstAtomIterator Chem::BasicAtom::getAtomsEnd() const
{
	return ConstAtomIterator(neighbors.end(), AtomAccessor<const BasicAtom>());
}

Chem::BasicAtom::ConstBondIterator Chem::BasicAtom::getBondsBegin() const
{
	return ConstBondIterator(neighbors.begin(), BondAccessor<const BasicBond>());
}

Chem::BasicAtom::ConstBondIterator Chem::BasicAtom::getBondsEnd() const
{
	return ConstBondIterator(neighbors.end(), BondAccessor<const BasicBond>());
}

Chem::BasicAtom::AtomIterator Chem::BasicAtom::getAtomsBegin()
{
	return AtomIterator(neighbors.begin(), AtomAccessor<BasicAtom>());
}

Chem::BasicAtom::AtomIterator Chem::BasicAtom::getAtomsEnd()
{
	return AtomIterator(neighbors.end(), AtomAccessor<BasicAtom>());
}

Chem::BasicAtom::BondIterator Chem::BasicAtom::getBondsBegin()
{
	return BondIterator(neighbors.begin(), BondAccessor<BasicBond>());
}

Chem::BasicAtom::BondIterator Chem::BasicAtom::getBondsEnd()
{
	return BondIterator(neighbors.end(), BondAccessor<BasicBond>());
}

bool Chem::BasicAtom::containsAtom(const Atom& atom) const
{
	return (std::find_if(neighbors.begin(), neighbors.end(), 
						 boost::bind(std::equal_to<const Atom*>(), 
									 &atom, boost::bind(&AtomBondPair::first, _1))) != neighbors.end());
}

bool Chem::BasicAtom::containsBond(const Bond& bond) const
{
	return (std::find_if(neighbors.begin(), neighbors.end(), 
						 boost::bind(std::equal_to<const Bond*>(), 
									 &bond, boost::bind(&AtomBondPair::second, _1))) != neighbors.end());
}

std::size_t Chem::BasicAtom::getAtomIndex(const Atom& atom) const
{
	NeighborList::const_iterator it = std::find_if(neighbors.begin(), neighbors.end(), 
												   boost::bind(std::equal_to<const Atom*>(), 
															   &atom, boost::bind(&AtomBondPair::first, _1)));
	if (it != neighbors.end())
		return (it - neighbors.begin());

	throw Base::ItemNotFound("BasicAtom: argument atom not found");
}

std::size_t Chem::BasicAtom::getBondIndex(const Bond& bond) const
{
	NeighborList::const_iterator it = std::find_if(neighbors.begin(), neighbors.end(), 
												   boost::bind(std::equal_to<const Bond*>(), 
															   &bond, boost::bind(&AtomBondPair::second, _1)));
	if (it != neighbors.end())
		return (it - neighbors.begin());

	throw Base::ItemNotFound("BasicAtom: argument bond not found");
}

void Chem::BasicAtom::setIndex(std::size_t idx)
{
	index = idx;
}

Chem::BasicAtom& Chem::BasicAtom::operator=(const BasicAtom& atom) 
{
	if (this == &atom)
		return *this;

	Atom::operator=(atom);

	return *this;
}

void Chem::BasicAtom::clearAdjacencyLists()
{
	neighbors.clear();
}

void Chem::BasicAtom::reserveMemForNewBond(BasicAtom& atom1, BasicAtom& atom2)
{
	atom1.neighbors.reserve(atom1.neighbors.size() + 1);

	if (&atom1 != &atom2) 
		atom2.neighbors.reserve(atom2.neighbors.size() + 1);
}

void Chem::BasicAtom::connectAtoms(BasicAtom& atom1, BasicAtom& atom2, BasicBond& bond)
{
	atom1.neighbors.push_back(AtomBondPair(&atom2, &bond));

	if (&atom1 != &atom2) 
		atom2.neighbors.push_back(AtomBondPair(&atom1, &bond));
}

void Chem::BasicAtom::disconnectAtoms(BasicBond& bond)
{
	BasicAtom* atom1 = bond.atoms[0];
	BasicAtom* atom2 = bond.atoms[1];

	atom1->neighbors.erase(std::remove(atom1->neighbors.begin(), atom1->neighbors.end(), AtomBondPair(atom2, &bond)), atom1->neighbors.end());

	if (atom1 != atom2)
		atom2->neighbors.erase(std::remove(atom2->neighbors.begin(), atom2->neighbors.end(), AtomBondPair(atom1, &bond)), atom2->neighbors.end());
}
