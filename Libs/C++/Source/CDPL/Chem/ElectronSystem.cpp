/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * ElectronSystem.cpp 
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
#include <cassert>

#include <boost/bind.hpp>

#include "CDPL/Chem/ElectronSystem.hpp"
#include "CDPL/Chem/Atom.hpp"
#include "CDPL/Chem/Bond.hpp"
#include "CDPL/Chem/BondContainer.hpp"
#include "CDPL/Base/Exceptions.hpp"
#include "CDPL/Util/Dereferencer.hpp"


using namespace CDPL;


Chem::ElectronSystem::ElectronSystem(): numElectrons(0) {}

std::size_t Chem::ElectronSystem::getNumAtoms() const
{
    return atoms.size();
}

std::size_t Chem::ElectronSystem::getAtomIndex(const Atom& atom) const
{
    AtomIdxAndElecContribMap::const_iterator it = atomIndsAndElecContribs.find(&atom);

    if (it != atomIndsAndElecContribs.end())
		return it->second.first;

    throw Base::ItemNotFound("ElectronSystem: argument atom not part of the electron system");
}

bool Chem::ElectronSystem::containsAtom(const Atom& atom) const 
{
    return (atomIndsAndElecContribs.find(&atom) != atomIndsAndElecContribs.end());
}

Chem::ElectronSystem::ConstAtomIterator Chem::ElectronSystem::getAtomsBegin() const 
{
    return atoms.begin();
}

Chem::ElectronSystem::ConstAtomIterator Chem::ElectronSystem::getAtomsEnd() const 
{
    return atoms.end();
}

Chem::ElectronSystem::AtomIterator Chem::ElectronSystem::getAtomsBegin() 
{
    return atoms.begin();
}

Chem::ElectronSystem::AtomIterator Chem::ElectronSystem::getAtomsEnd() 
{
    return atoms.end();
}

const Chem::Atom& Chem::ElectronSystem::getAtom(std::size_t idx) const 
{
    if (idx >= atoms.size())
		throw Base::IndexError("ElectronSystem: atom index out of bounds");

    return *atoms[idx];
}

Chem::Atom& Chem::ElectronSystem::getAtom(std::size_t idx)
{
    if (idx >= atoms.size())
		throw Base::IndexError("ElectronSystem: atom index out of bounds");

    return *atoms[idx];
}

bool Chem::ElectronSystem::addAtom(const Atom& atom, std::size_t elec_contrib) 
{
    atoms.reserve(atoms.size() + 1);

    if (!atomIndsAndElecContribs.insert(AtomIdxAndElecContribMap::value_type(&atom, UIPair(atoms.size(), elec_contrib))).second)
		return false;

    atoms.push_back(const_cast<Atom*>(&atom));
    
    numElectrons += elec_contrib;
    
    return true;
}

bool Chem::ElectronSystem::addAtoms(const ElectronSystem& elec_sys)
{
	bool atoms_added = false;

	atoms.reserve(atoms.size() + elec_sys.atoms.size());

	for (AtomIdxAndElecContribMap::const_iterator it = elec_sys.atomIndsAndElecContribs.begin(), end = elec_sys.atomIndsAndElecContribs.end(); it != end; ++it) {
		const Atom* atom = it->first;
		std::size_t elec_contrib = it->second.second;
		
		if (!atomIndsAndElecContribs.insert(AtomIdxAndElecContribMap::value_type(atom, UIPair(atoms.size(), elec_contrib))).second)
			continue;
		
		numElectrons += elec_contrib;
		atoms_added = true;
		
		atoms.push_back(const_cast<Atom*>(atom));
	}

	return atoms_added;
}

void Chem::ElectronSystem::removeAtom(std::size_t idx) 
{
    std::size_t num_atoms = atoms.size();

    if (idx >= num_atoms)
		throw Base::IndexError("ElectronSystem: atom index out of bounds");

    const Atom& atom = *atoms[idx];
    AtomList::iterator it = atoms.begin() + idx;
	AtomIdxAndElecContribMap::iterator idx_it = atomIndsAndElecContribs.find(&atom);

	assert(idx_it != atomIndsAndElecContribs.end());
	assert(numElectrons >= idx_it->second.second);
	
	numElectrons -= idx_it->second.second;

	atomIndsAndElecContribs.erase(idx_it);
	
    it = atoms.erase(it);
	
    for (num_atoms--; idx < num_atoms; idx++, ++it)
		atomIndsAndElecContribs[*it].first = idx;
}

Chem::ElectronSystem::AtomIterator Chem::ElectronSystem::removeAtom(const AtomIterator& it) 
{
    const AtomList::iterator& base = it.base();

    if (base < atoms.begin() || base >= atoms.end())
		throw Base::RangeError("ElectronSystem: atom iterator out of valid range");

    const Atom* atom = *base;
    AtomList::iterator rit = atoms.erase(base);
   	AtomIdxAndElecContribMap::iterator idx_it = atomIndsAndElecContribs.find(atom);

	assert(idx_it != atomIndsAndElecContribs.end());
	assert(numElectrons >= idx_it->second.second);
	
	numElectrons -= idx_it->second.second;

	atomIndsAndElecContribs.erase(idx_it); 
		
    for (std::size_t num_atoms = atoms.size(), i = rit - atoms.begin(); i < num_atoms; i++)
		atomIndsAndElecContribs[atoms[i]].first = i;

    return rit;
}

bool Chem::ElectronSystem::removeAtom(const Atom& atom) 
{
    AtomIdxAndElecContribMap::iterator idx_it = atomIndsAndElecContribs.find(&atom);

    if (idx_it == atomIndsAndElecContribs.end())
		return false;

    std::size_t idx = idx_it->second.first;
    AtomList::iterator it = atoms.begin() + idx;

	assert(numElectrons >= idx_it->second.second);
	
    numElectrons -= idx_it->second.second;
	
    it = atoms.erase(it);
    
    atomIndsAndElecContribs.erase(idx_it);
	
    for (std::size_t num_atoms = atoms.size(); idx < num_atoms; idx++, ++it)
		atomIndsAndElecContribs[*it].first = idx;

    return true;
}

void Chem::ElectronSystem::orderAtoms(const AtomCompareFunction& func)
{
    std::sort(atoms.begin(), atoms.end(), 
			  boost::bind(func, boost::bind(Util::Dereferencer<const Atom*, const Atom&>(), _1), 
						  boost::bind(Util::Dereferencer<const Atom*, const Atom&>(), _2)));

    for (std::size_t i = 0, num_atoms = atoms.size(); i < num_atoms; i++)
		atomIndsAndElecContribs[atoms[i]].first = i;
}

void Chem::ElectronSystem::swap(ElectronSystem& elec_sys)
{
    atoms.swap(elec_sys.atoms);
    atomIndsAndElecContribs.swap(elec_sys.atomIndsAndElecContribs);

    std::swap(numElectrons, elec_sys.numElectrons);
}

void Chem::ElectronSystem::clear()
{
    atoms.clear();
    atomIndsAndElecContribs.clear();

    numElectrons = 0;
}

std::size_t Chem::ElectronSystem::getNumElectrons() const
{
	return numElectrons;
}

std::size_t Chem::ElectronSystem::getElectronContrib(const Atom& atom) const
{
	AtomIdxAndElecContribMap::const_iterator it = atomIndsAndElecContribs.find(&atom);

    if (it != atomIndsAndElecContribs.end())
		return it->second.second;

    throw Base::ItemNotFound("ElectronSystem: argument atom not part of the electron system");
}

std::size_t Chem::ElectronSystem::getElectronContrib(std::size_t idx) const
{
	AtomIdxAndElecContribMap::const_iterator it = atomIndsAndElecContribs.find(&getAtom(idx));

    assert(it != atomIndsAndElecContribs.end());
	
	return it->second.second;
}

void Chem::ElectronSystem::setElectronContrib(const Atom& atom, std::size_t elec_contrib)
{
	AtomIdxAndElecContribMap::iterator it = atomIndsAndElecContribs.find(&atom);

    if (it == atomIndsAndElecContribs.end())
		throw Base::ItemNotFound("ElectronSystem: argument atom not part of the electron system");
	
	assert(numElectrons >= idx_it->second.second);

	numElectrons -= it->second.second;
	numElectrons += elec_contrib;

	it->second.second = elec_contrib;
}

void Chem::ElectronSystem::setElectronContrib(std::size_t idx, std::size_t elec_contrib)
{
	AtomIdxAndElecContribMap::iterator it = atomIndsAndElecContribs.find(&getAtom(idx));

    assert(it != atomIndsAndElecContribs.end());
	assert(numElectrons >= idx_it->second.second);

	numElectrons -= it->second.second;
	numElectrons += elec_contrib;

	it->second.second = elec_contrib;
}

void Chem::ElectronSystem::merge(const ElectronSystem& elec_sys)
{
	atoms.reserve(atoms.size() + elec_sys.atoms.size());

	for (AtomIdxAndElecContribMap::const_iterator it = elec_sys.atomIndsAndElecContribs.begin(), end = elec_sys.atomIndsAndElecContribs.end(); it != end; ++it) {
		const Atom* atom = it->first;
		std::size_t elec_contrib = it->second.second;

		numElectrons += elec_contrib;
				
		if (atomIndsAndElecContribs.insert(AtomIdxAndElecContribMap::value_type(atom, UIPair(atoms.size(), elec_contrib))).second)
			atoms.push_back(const_cast<Atom*>(atom));
		else
			atomIndsAndElecContribs[atom].second += numElectrons;
	}
}

bool Chem::ElectronSystem::overlaps(const ElectronSystem& elec_sys) const
{
	const ElectronSystem* sys1 = this;
	const ElectronSystem* sys2 = &elec_sys;
	
	if (sys1->atoms.size() > sys2->atoms.size())
		std::swap(sys1, sys2);

	for (AtomList::const_iterator it = sys1->atoms.begin(), end = sys1->atoms.end(); it != end; ++it)
		if (sys2->containsAtom(**it))
			return true;

	return false;
}

bool Chem::ElectronSystem::contains(const ElectronSystem& elec_sys) const
{
	for (AtomList::const_iterator it = elec_sys.atoms.begin(), end = elec_sys.atoms.end(); it != end; ++it) 
		if (!containsAtom(**it))
			return false;
	
	return true;
}

bool Chem::ElectronSystem::connected(const ElectronSystem& elec_sys, const BondContainer& bonds) const
{
	const ElectronSystem* sys1 = this;
	const ElectronSystem* sys2 = &elec_sys;
	
	if (sys1->atoms.size() > sys2->atoms.size())
		std::swap(sys1, sys2);

	for (AtomList::const_iterator it = sys1->atoms.begin(), end = sys1->atoms.end(); it != end; ++it)
		if (sys2->containsAtom(**it))
			return false;

	for (AtomList::const_iterator it = sys1->atoms.begin(), end = sys1->atoms.end(); it != end; ++it) {
		const Atom& atom = **it;
		Atom::ConstBondIterator nb_it = atom.getBondsBegin();

		for (Atom::ConstAtomIterator na_it = atom.getAtomsBegin(), na_end = atom.getAtomsEnd(); na_it != na_end; ++na_it, ++nb_it) 
			if (sys2->containsAtom(*na_it) && bonds.containsBond(*nb_it))
				return true;
	}
	
	return false;
}
