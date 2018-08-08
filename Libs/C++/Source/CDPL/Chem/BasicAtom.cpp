/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * BasicAtom.cpp 
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

#include <boost/bind.hpp>

#include "CDPL/Chem/BasicAtom.hpp"
#include "CDPL/Chem/BasicBond.hpp"
#include "CDPL/Chem/BasicMolecule.hpp"
#include "CDPL/Base/Exceptions.hpp"
#include "CDPL/Internal/AddressOf.hpp"


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
	return atoms.size();
}

std::size_t Chem::BasicAtom::getNumBonds() const
{
	return bonds.size();
}

const Chem::Bond& Chem::BasicAtom::getBond(std::size_t idx) const
{
	if (idx >= bonds.size())
		throw Base::IndexError("BasicAtom: bond index out of bounds");

	return *bonds[idx];
}

Chem::Bond& Chem::BasicAtom::getBond(std::size_t idx)
{
	if (idx >= bonds.size())
		throw Base::IndexError("BasicAtom: bond index out of bounds");

	return *bonds[idx];
}

const Chem::Bond& Chem::BasicAtom::getBondToAtom(const Atom& atom) const
{
	BondList::const_iterator it = std::find_if(bonds.begin(), bonds.end(),
											   boost::bind(std::equal_to<const Atom*>(), 
														   &atom, boost::bind(Internal::AddressOf<const Atom>(),
																			  boost::bind(static_cast<const Atom& (Bond::*)(const Atom&) const>(&Bond::getNeighbor), _1, boost::ref(*this)))));
	if (it == bonds.end())
		throw Base::ItemNotFound("BasicAtom: argument atom is not a bonded neighbor");

	return **it;
}

Chem::Bond& Chem::BasicAtom::getBondToAtom(const Atom& atom)
{
	BondList::iterator it = std::find_if(bonds.begin(), bonds.end(),
											 boost::bind(std::equal_to<const Atom*>(), 
														 &atom, boost::bind(Internal::AddressOf<const Atom>(),
																			boost::bind(static_cast<const Atom& (Bond::*)(const Atom&) const>(&Bond::getNeighbor), _1, boost::ref(*this)))));
	if (it == bonds.end())
		throw Base::ItemNotFound("BasicAtom: argument atom is not a bonded neighbor");

	return **it;
}

const Chem::Bond* Chem::BasicAtom::findBondToAtom(const Atom& atom) const
{
	BondList::const_iterator it = std::find_if(bonds.begin(), bonds.end(),
											   boost::bind(std::equal_to<const Atom*>(), 
														   &atom, boost::bind(Internal::AddressOf<const Atom>(),
																			  boost::bind(static_cast<const Atom& (Bond::*)(const Atom&) const>(&Bond::getNeighbor), _1, boost::ref(*this)))));
	return (it == bonds.end() ? 0 : *it);
}

Chem::Bond* Chem::BasicAtom::findBondToAtom(const Atom& atom)
{
	BondList::iterator it = std::find_if(bonds.begin(), bonds.end(),
											 boost::bind(std::equal_to<const Atom*>(), 
														 &atom, boost::bind(Internal::AddressOf<const Atom>(),
																			boost::bind(static_cast<const Atom& (Bond::*)(const Atom&) const>(&Bond::getNeighbor), _1, boost::ref(*this)))));
	return (it == bonds.end() ? 0 : *it);
}

const Chem::Atom& Chem::BasicAtom::getAtom(std::size_t idx) const
{
	if (idx >= atoms.size())
		throw Base::IndexError("BasicAtom: atom index out of bounds");

	return *atoms[idx];
}

Chem::Atom& Chem::BasicAtom::getAtom(std::size_t idx)
{
	if (idx >= atoms.size())
		throw Base::IndexError("BasicAtom: atom index out of bounds");

	return *atoms[idx];
}

Chem::BasicAtom::ConstAtomIterator Chem::BasicAtom::getAtomsBegin() const
{
	return atoms.begin();
}

Chem::BasicAtom::ConstAtomIterator Chem::BasicAtom::getAtomsEnd() const
{
	return atoms.end();
}

Chem::BasicAtom::ConstBondIterator Chem::BasicAtom::getBondsBegin() const
{
	return bonds.begin();
}

Chem::BasicAtom::ConstBondIterator Chem::BasicAtom::getBondsEnd() const
{
	return bonds.end();
}

Chem::BasicAtom::AtomIterator Chem::BasicAtom::getAtomsBegin() 
{
	return atoms.begin();
}

Chem::BasicAtom::AtomIterator Chem::BasicAtom::getAtomsEnd() 
{
	return atoms.end();
}

Chem::BasicAtom::BondIterator Chem::BasicAtom::getBondsBegin() 
{
	return bonds.begin();
}

Chem::BasicAtom::BondIterator Chem::BasicAtom::getBondsEnd() 
{
	return bonds.end();
}

bool Chem::BasicAtom::containsAtom(const Atom& atom) const
{
	return (std::find(atoms.begin(), atoms.end(), &atom) != atoms.end());
}

bool Chem::BasicAtom::containsBond(const Bond& bond) const
{
	return (std::find(bonds.begin(), bonds.end(), &bond) != bonds.end());
}

std::size_t Chem::BasicAtom::getAtomIndex(const Atom& atom) const
{
	AtomList::const_iterator it = std::find(atoms.begin(), atoms.end(), &atom);

	if (it != atoms.end())
		return (it - atoms.begin());

	throw Base::ItemNotFound("BasicAtom: argument atom not found");
}

std::size_t Chem::BasicAtom::getBondIndex(const Bond& bond) const
{
	BondList::const_iterator it = std::find(bonds.begin(), bonds.end(), &bond);

	if (it != bonds.end())
		return (it - bonds.begin());

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
	atoms.clear();
	bonds.clear();
}

void Chem::BasicAtom::reserveMemForNewBond(BasicAtom& atom1, BasicAtom& atom2)
{
	std::size_t new_atom1_bnd_cnt = atom1.bonds.size() + 1;

	atom1.bonds.reserve(new_atom1_bnd_cnt);
	atom1.atoms.reserve(new_atom1_bnd_cnt);

	if (&atom1 != &atom2) {
		std::size_t new_atom2_bnd_cnt = atom2.bonds.size() + 1;

		atom2.bonds.reserve(new_atom2_bnd_cnt);
		atom2.atoms.reserve(new_atom2_bnd_cnt);
	}
}

void Chem::BasicAtom::connectAtoms(BasicAtom& atom1, BasicAtom& atom2, BasicBond& bond)
{
	atom1.atoms.push_back(&atom2);
	atom1.bonds.push_back(&bond);

	if (&atom1 != &atom2) {
		atom2.atoms.push_back(&atom1);
		atom2.bonds.push_back(&bond);
	}
}

void Chem::BasicAtom::disconnectAtoms(BasicBond& bond)
{
	BasicAtom& atom1 = *bond.atoms[0];
	BasicAtom& atom2 = *bond.atoms[1];

	atom1.bonds.erase(std::remove(atom1.bonds.begin(), atom1.bonds.end(), &bond), atom1.bonds.end());
	atom1.atoms.erase(std::remove(atom1.atoms.begin(), atom1.atoms.end(), &atom2), atom1.atoms.end());

	if (&atom1 != &atom2) {
		atom2.bonds.erase(std::remove(atom2.bonds.begin(), atom2.bonds.end(), &bond), atom2.bonds.end());
		atom2.atoms.erase(std::remove(atom2.atoms.begin(), atom2.atoms.end(), &atom1), atom2.atoms.end());
	}
}
