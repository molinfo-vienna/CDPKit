/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * Fragment.cpp 
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

#include "CDPL/Chem/Fragment.hpp"
#include "CDPL/Chem/Atom.hpp"
#include "CDPL/Chem/Bond.hpp"
#include "CDPL/Util/Dereferencer.hpp"
#include "CDPL/Base/Exceptions.hpp"


using namespace CDPL;


Chem::Fragment::Fragment() {}

Chem::Fragment::Fragment(const Fragment& frag): 
	MolecularGraph(frag),
	atoms(frag.atoms), bonds(frag.bonds),
	atomIndices(frag.atomIndices), bondIndices(frag.bondIndices) {}

Chem::Fragment::Fragment(const MolecularGraph& molgraph): 
	MolecularGraph(molgraph)
{
	std::for_each(molgraph.getAtomsBegin(), molgraph.getAtomsEnd(), 
				  boost::bind(&Fragment::addAtom, this, _1));

	std::for_each(molgraph.getBondsBegin(), molgraph.getBondsEnd(),  
				  boost::bind(&Fragment::addBond, this, _1));
}

Chem::Fragment::~Fragment() {} 

std::size_t Chem::Fragment::getNumAtoms() const
{
	return atoms.size();
}

std::size_t Chem::Fragment::getNumBonds() const 
{
	return bonds.size();
}

std::size_t Chem::Fragment::getAtomIndex(const Atom& atom) const
{
	AtomIndexMap::const_iterator it = atomIndices.find(&atom);

	if (it != atomIndices.end())
		return it->second;

	throw Base::ItemNotFound("Fragment: argument atom not part of the fragment");
}

std::size_t Chem::Fragment::getBondIndex(const Bond& bond) const
{
	BondIndexMap::const_iterator it = bondIndices.find(&bond);

	if (it != bondIndices.end())
		return it->second;

	throw Base::ItemNotFound("Fragment: argument bond not part of the fragment");
}

bool Chem::Fragment::containsAtom(const Atom& atom) const 
{
	return (atomIndices.find(&atom) != atomIndices.end());
}

bool Chem::Fragment::containsBond(const Bond& bond) const 
{
	return (bondIndices.find(&bond) != bondIndices.end());
}

Chem::Fragment::ConstAtomIterator Chem::Fragment::getAtomsBegin() const 
{
	return atoms.begin();
}

Chem::Fragment::ConstAtomIterator Chem::Fragment::getAtomsEnd() const 
{
	return atoms.end();
}

Chem::Fragment::AtomIterator Chem::Fragment::getAtomsBegin() 
{
	return atoms.begin();
}

Chem::Fragment::AtomIterator Chem::Fragment::getAtomsEnd() 
{
	return atoms.end();
}

Chem::Fragment::ConstBondIterator Chem::Fragment::getBondsBegin() const 
{
	return bonds.begin();
}

Chem::Fragment::ConstBondIterator Chem::Fragment::getBondsEnd() const 
{
	return bonds.end();
}

Chem::Fragment::BondIterator Chem::Fragment::getBondsBegin() 
{
	return bonds.begin();
}

Chem::Fragment::BondIterator Chem::Fragment::getBondsEnd() 
{
	return bonds.end();
}

const Chem::Atom& Chem::Fragment::getAtom(std::size_t idx) const 
{
	if (idx >= atoms.size())
		throw Base::IndexError("Fragment: atom index out of bounds");

	return *atoms[idx];
}

Chem::Atom& Chem::Fragment::getAtom(std::size_t idx)
{
	if (idx >= atoms.size())
		throw Base::IndexError("Fragment: atom index out of bounds");

	return *atoms[idx];
}

bool Chem::Fragment::addAtom(const Atom& atom) 
{
	atoms.reserve(atoms.size() + 1);

	if (!atomIndices.insert(AtomIndexMap::value_type(&atom, atoms.size())).second)
		return false;

	atoms.push_back(const_cast<Atom*>(&atom));

	return true;
}

void Chem::Fragment::removeAtom(std::size_t idx) 
{
	std::size_t num_atoms = atoms.size();

	if (idx >= num_atoms)
		throw Base::IndexError("Fragment: atom index out of bounds");

	const Atom& atom = *atoms[idx];

	AtomList::iterator it = atoms.begin() + idx;

	atomIndices.erase(*it);
	
	it = atoms.erase(it);
	
	for (num_atoms--; idx < num_atoms; idx++, ++it)
		atomIndices[*it] = idx;

	std::for_each(atom.getBondsBegin(), atom.getBondsEnd(),
				  boost::bind<bool>(&Fragment::removeBond, this, _1));
}

Chem::Fragment::AtomIterator Chem::Fragment::removeAtom(const AtomIterator& it) 
{
	const AtomList::iterator& base = it.base();

	if (base < atoms.begin() || base >= atoms.end())
		throw Base::RangeError("Fragment: atom iterator out of valid range");

	const Atom* atom = *base;

	atomIndices.erase(atom);

	AtomList::iterator rit = atoms.erase(base);
		
	for (std::size_t num_atoms = atoms.size(), i = rit - atoms.begin(); i < num_atoms; i++)
		atomIndices[atoms[i]] = i;

	std::for_each(atom->getBondsBegin(), atom->getBondsEnd(),
				  boost::bind<bool>(&Fragment::removeBond, this, _1));

	return rit;
}

bool Chem::Fragment::removeAtom(const Atom& atom) 
{
	AtomIndexMap::iterator idx_it = atomIndices.find(&atom);

	if (idx_it == atomIndices.end())
		return false;

	std::size_t idx = idx_it->second;

	AtomList::iterator it = atoms.begin() + idx;

	atomIndices.erase(idx_it);
	
	it = atoms.erase(it);
	
	for (std::size_t num_atoms = atoms.size(); idx < num_atoms; idx++, ++it)
		atomIndices[*it] = idx;

	std::for_each(atom.getBondsBegin(), atom.getBondsEnd(),
				  boost::bind<bool>(&Fragment::removeBond, this, _1));

	return true;
}

const Chem::Bond& Chem::Fragment::getBond(std::size_t idx) const 
{
	if (idx >= bonds.size())
		throw Base::IndexError("Fragment: bond index out of bounds");

	return *bonds[idx];
}

Chem::Bond& Chem::Fragment::getBond(std::size_t idx)
{
	if (idx >= bonds.size())
		throw Base::IndexError("Fragment: bond index out of bounds");

	return *bonds[idx];
}

bool Chem::Fragment::addBond(const Bond& bond) 
{
	bonds.reserve(bonds.size() + 1);
	atoms.reserve(atoms.size() + 2);

	if (!bondIndices.insert(BondIndexMap::value_type(&bond, bonds.size())).second)
		return false;

	bonds.push_back(const_cast<Bond*>(&bond));

	addAtom(bond.getBegin());
	addAtom(bond.getEnd());

	return true;
}

void Chem::Fragment::removeBond(std::size_t idx) 
{
	std::size_t num_bonds = bonds.size();

	if (idx >= num_bonds)
		throw Base::IndexError("Fragment: bond index out of bounds");

	BondList::iterator it = bonds.begin() + idx;

	bondIndices.erase(*it);
	
	it = bonds.erase(it);
	
	for (num_bonds--; idx < num_bonds; idx++, ++it)
		bondIndices[*it] = idx;
}

Chem::Fragment::BondIterator Chem::Fragment::removeBond(const BondIterator& it) 
{
	const BondList::iterator& base = it.base();

	if (base < bonds.begin() || base >= bonds.end())
		throw Base::RangeError("Fragment: bond iterator out of valid range");

	bondIndices.erase(*base);

	BondList::iterator rit = bonds.erase(base);
		
	for (std::size_t num_bonds = bonds.size(), i = rit - bonds.begin(); i < num_bonds; i++)
		bondIndices[bonds[i]] = i;

	return rit;
}

bool Chem::Fragment::removeBond(const Bond& bond) 
{
	BondIndexMap::iterator idx_it = bondIndices.find(&bond);

	if (idx_it == bondIndices.end())
		return false;

	std::size_t idx = idx_it->second;

	BondList::iterator it = bonds.begin() + idx;

	bondIndices.erase(idx_it);
	
	it = bonds.erase(it);
	
	for (std::size_t num_bonds = bonds.size(); idx < num_bonds; idx++, ++it)
		bondIndices[*it] = idx;

	return true;
}

void Chem::Fragment::orderAtoms(const AtomCompareFunction& func)
{
	std::sort(atoms.begin(), atoms.end(), 
			  boost::bind(func, boost::bind(Util::Dereferencer<const Atom*, const Atom&>(), _1), 
						  boost::bind(Util::Dereferencer<const Atom*, const Atom&>(), _2)));

	for (std::size_t i = 0, num_atoms = atoms.size(); i < num_atoms; i++)
		atomIndices[atoms[i]] = i;
}

void Chem::Fragment::orderBonds(const BondCompareFunction& func)
{
	std::sort(bonds.begin(), bonds.end(), 
			  boost::bind(func, boost::bind(Util::Dereferencer<const Bond*, const Bond&>(), _1), 
						  boost::bind(Util::Dereferencer<const Bond*, const Bond&>(), _2)));

	for (std::size_t i = 0, num_bonds = bonds.size(); i < num_bonds; i++)
		bondIndices[bonds[i]] = i;
}

void Chem::Fragment::reserveMemoryForAtoms(std::size_t num_atoms)
{
	atoms.reserve(num_atoms);
}

void Chem::Fragment::swap(Fragment& frag)
{
	Base::PropertyContainer::swap(frag);

	atoms.swap(frag.atoms);
	bonds.swap(frag.bonds);
	atomIndices.swap(frag.atomIndices);
	bondIndices.swap(frag.bondIndices);
}

void Chem::Fragment::reserveMemoryForBonds(std::size_t num_bonds)
{
	bonds.reserve(num_bonds);
}

void Chem::Fragment::clear()
{
	clearProperties();

	atoms.clear();
	bonds.clear();
	atomIndices.clear();
	bondIndices.clear();
}

Chem::Fragment& Chem::Fragment::operator=(const Fragment& frag)
{
	if (this == &frag)
		return *this;

	atomIndices = frag.atomIndices;
	bondIndices = frag.bondIndices;
	atoms = frag.atoms;
	bonds = frag.bonds;

	copyProperties(frag);

	return *this;
}

Chem::Fragment& Chem::Fragment::operator=(const MolecularGraph& molgraph)
{
	atoms.clear();
	bonds.clear();
	atomIndices.clear();
	bondIndices.clear();

	atoms.reserve(molgraph.getNumAtoms());
	bonds.reserve(molgraph.getNumBonds());

	std::for_each(molgraph.getAtomsBegin(), molgraph.getAtomsEnd(), 
				  boost::bind(&Fragment::addAtom, this, _1));

	std::for_each(molgraph.getBondsBegin(), molgraph.getBondsEnd(),  
				  boost::bind(&Fragment::addBond, this, _1));

	copyProperties(molgraph);

	return *this;
}

Chem::Fragment& Chem::Fragment::operator+=(const MolecularGraph& molgraph)
{
	atoms.reserve(atoms.size() + molgraph.getNumAtoms());
	bonds.reserve(bonds.size() + molgraph.getNumBonds());

	std::for_each(molgraph.getAtomsBegin(), molgraph.getAtomsEnd(), 
				  boost::bind(&Fragment::addAtom, this, _1));

	std::for_each(molgraph.getBondsBegin(), molgraph.getBondsEnd(),  
				  boost::bind(&Fragment::addBond, this, _1));

	return *this;
}

Chem::MolecularGraph::SharedPointer Chem::Fragment::clone()  const
{
	return MolecularGraph::SharedPointer(new Fragment(*this));
}
