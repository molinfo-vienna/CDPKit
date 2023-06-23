/* 
 * BasicMolecule.cpp 
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
#include <functional>

#include "CDPL/Chem/BasicMolecule.hpp"
#include "CDPL/Util/Dereferencer.hpp"
#include "CDPL/Base/Exceptions.hpp"


namespace
{

	const std::size_t MAX_ATOM_CACHE_SIZE = 50000;
	const std::size_t MAX_BOND_CACHE_SIZE = 50000;
}


using namespace CDPL;


Chem::BasicMolecule::BasicMolecule():
	atomCache(std::bind(&BasicMolecule::createAtom, this), &BasicMolecule::destroyAtom, MAX_ATOM_CACHE_SIZE),
	bondCache(std::bind(&BasicMolecule::createBond, this), &BasicMolecule::destroyBond, MAX_BOND_CACHE_SIZE)
{
	atomCache.setCleanupFunction(&BasicMolecule::clearAtom);
	bondCache.setCleanupFunction(&BasicMolecule::clearBond);
}

Chem::BasicMolecule::BasicMolecule(const BasicMolecule& mol): 
	Molecule(mol), 
	atomCache(std::bind(&BasicMolecule::createAtom, this), &BasicMolecule::destroyAtom, MAX_ATOM_CACHE_SIZE),
	bondCache(std::bind(&BasicMolecule::createBond, this), &BasicMolecule::destroyBond, MAX_BOND_CACHE_SIZE)
{
	atomCache.setCleanupFunction(&BasicMolecule::clearAtom);
	bondCache.setCleanupFunction(&BasicMolecule::clearBond);

	append(mol);
}

Chem::BasicMolecule::BasicMolecule(const Molecule& mol): 
	Molecule(mol), 
	atomCache(std::bind(&BasicMolecule::createAtom, this), &BasicMolecule::destroyAtom, MAX_ATOM_CACHE_SIZE),
	bondCache(std::bind(&BasicMolecule::createBond, this), &BasicMolecule::destroyBond, MAX_BOND_CACHE_SIZE)
{
	atomCache.setCleanupFunction(&BasicMolecule::clearAtom);
	bondCache.setCleanupFunction(&BasicMolecule::clearBond);

	append(mol);
}

Chem::BasicMolecule::BasicMolecule(const MolecularGraph& molgraph):
	atomCache(std::bind(&BasicMolecule::createAtom, this), &BasicMolecule::destroyAtom, MAX_ATOM_CACHE_SIZE),
	bondCache(std::bind(&BasicMolecule::createBond, this), &BasicMolecule::destroyBond, MAX_BOND_CACHE_SIZE)
{
	atomCache.setCleanupFunction(&BasicMolecule::clearAtom);
	bondCache.setCleanupFunction(&BasicMolecule::clearBond);

	append(molgraph);
	copyProperties(molgraph);
}

Chem::BasicMolecule::~BasicMolecule() {}

void Chem::BasicMolecule::clear()
{
	clearAtomsAndBonds();
	clearProperties();
}

std::size_t Chem::BasicMolecule::getNumAtoms() const
{
	return atoms.size();
}

std::size_t Chem::BasicMolecule::getNumBonds() const
{
	return bonds.size();
}

Chem::BasicMolecule::ConstAtomIterator Chem::BasicMolecule::getAtomsBegin() const
{
	return atoms.begin();
}

Chem::BasicMolecule::ConstAtomIterator Chem::BasicMolecule::getAtomsEnd() const
{
	return atoms.end();
}

Chem::BasicMolecule::ConstBondIterator Chem::BasicMolecule::getBondsBegin() const
{
	return bonds.begin();
}

Chem::BasicMolecule::ConstBondIterator Chem::BasicMolecule::getBondsEnd() const
{
	return bonds.end();
}

Chem::BasicMolecule::AtomIterator Chem::BasicMolecule::getAtomsBegin() 
{
	return atoms.begin();
}

Chem::BasicMolecule::AtomIterator Chem::BasicMolecule::getAtomsEnd() 
{
	return atoms.end();
}

Chem::BasicMolecule::BondIterator Chem::BasicMolecule::getBondsBegin() 
{
	return bonds.begin();
}

Chem::BasicMolecule::BondIterator Chem::BasicMolecule::getBondsEnd() 
{
	return bonds.end();
}

const Chem::BasicAtom& Chem::BasicMolecule::getAtom(std::size_t idx) const
{
	if (idx >= atoms.size())
		throw Base::IndexError("BasicMolecule: atom index out of bounds");

	return *atoms[idx];
}

Chem::BasicAtom& Chem::BasicMolecule::getAtom(std::size_t idx)
{
	if (idx >= atoms.size())
		throw Base::IndexError("BasicMolecule: atom index out of bounds");

	return *atoms[idx];
}

Chem::BasicAtom& Chem::BasicMolecule::addAtom()
{
	AtomPtr atom = atomCache.get();

	atom->setIndex(atoms.size());
	atoms.push_back(atom);

	return *atom;
}

void Chem::BasicMolecule::removeAtom(std::size_t idx)
{
	if (idx >= atoms.size())
		throw Base::IndexError("BasicMolecule: atom index out of bounds");

	const AtomPtr& atom = atoms[idx];

	for (std::size_t i = atom->getNumBonds(); i > 0; i--) 
		removeBond(atom->getBond(i - 1).getIndex());

	assert(atom->getNumBonds() == 0 && atom->getNumAtoms() == 0);

	atoms.erase(atoms.begin() + idx);

	renumberAtoms(idx);
}

Chem::BasicMolecule::AtomIterator Chem::BasicMolecule::removeAtom(const AtomIterator& it)
{
	const AtomList::iterator& base = it.base();

	if (base < atoms.begin() || base >= atoms.end())
		throw Base::RangeError("BasicMolecule: atom iterator out of valid range");

	const AtomPtr& atom = *base;

	for (std::size_t i = atom->getNumBonds(); i > 0; i--) 
		removeBond(atom->getBond(i - 1).getIndex());

	assert(atom->getNumBonds() == 0 && atom->getNumAtoms() == 0);

	AtomList::iterator rit = atoms.erase(base);

	renumberAtoms(rit - atoms.begin());

	return rit;
}

const Chem::BasicBond& Chem::BasicMolecule::getBond(std::size_t idx) const
{
	if (idx >= bonds.size())
		throw Base::IndexError("BasicMolecule: bond index out of bounds");

	return *bonds[idx];
}

Chem::BasicBond& Chem::BasicMolecule::getBond(std::size_t idx)
{
	if (idx >= bonds.size())
		throw Base::IndexError("BasicMolecule: bond index out of bounds");

	return *bonds[idx];
}

Chem::BasicBond& Chem::BasicMolecule::addBond(std::size_t atom1_idx, std::size_t atom2_idx)		
{
	BasicAtom& atom1 = getAtom(atom1_idx);
	BasicAtom& atom2 = getAtom(atom2_idx);
	Bond* ex_bond = atom1.findBondToAtom(atom2);

	if (ex_bond)
		return static_cast<Chem::BasicBond&>(*ex_bond);

	BasicAtom::reserveMemForNewBond(atom1, atom2);

	BondPtr bond = bondCache.get();

	bond->setIndex(bonds.size());
	bond->setBegin(atom1);
	bond->setEnd(atom2);

	BasicAtom::connectAtoms(atom1, atom2, *bond);

	bonds.push_back(bond);

	return *bond;
}

void Chem::BasicMolecule::removeBond(std::size_t idx)
{
	if (idx >= bonds.size())
		throw Base::IndexError("BasicMolecule: bond index out of bounds");

	BasicAtom::disconnectAtoms(*bonds[idx]);

	bonds.erase(bonds.begin() + idx);

	renumberBonds(idx);
}

Chem::BasicMolecule::BondIterator Chem::BasicMolecule::removeBond(const BondIterator& it)
{
	const BondList::iterator& base = it.base();

	if (base < bonds.begin() || base >= bonds.end())
		throw Base::RangeError("BasicMolecule: bond iterator out of valid range");

	BasicAtom::disconnectAtoms(**base);

	BondList::iterator rit = bonds.erase(base);

	renumberBonds(rit - bonds.begin());

	return rit;
}

bool Chem::BasicMolecule::containsAtom(const Atom& atom) const
{
	if (this != &atom.getMolecule())
		return false;

	return (atom.getIndex() < atoms.size());
}

bool Chem::BasicMolecule::containsBond(const Bond& bond) const
{
	if (this != &bond.getMolecule())
		return false;

	return (bond.getIndex() < bonds.size());
}

std::size_t Chem::BasicMolecule::getAtomIndex(const Atom& atom) const
{
	if (this != &atom.getMolecule() || atom.getIndex() >= atoms.size())
		throw Base::ItemNotFound("BasicMolecule: argument atom not part of the molecule");

	return atom.getIndex();
}

std::size_t Chem::BasicMolecule::getBondIndex(const Bond& bond) const
{
	if (this != &bond.getMolecule() || bond.getIndex() >= bonds.size())
		throw Base::ItemNotFound("BasicMolecule: argument bond not part of the molecule");

	return bond.getIndex();
}

void Chem::BasicMolecule::orderAtoms(const AtomCompareFunction& func)
{
	using namespace std::placeholders;
	
	std::sort(atoms.begin(), atoms.end(), 
			  std::bind(func, std::bind(Util::Dereferencer<const AtomPtr, const Atom&>(), _1), 
						std::bind(Util::Dereferencer<const AtomPtr, const Atom&>(), _2)));

	renumberAtoms(0);
}

void Chem::BasicMolecule::orderBonds(const BondCompareFunction& func)
{
	using namespace std::placeholders;
	
	std::sort(bonds.begin(), bonds.end(), 
			  std::bind(func, std::bind(Util::Dereferencer<const BondPtr, const Bond&>(), _1), 
						std::bind(Util::Dereferencer<const BondPtr, const Bond&>(), _2)));

	renumberBonds(0);
}

Chem::MolecularGraph::SharedPointer Chem::BasicMolecule::clone() const
{
	return MolecularGraph::SharedPointer(new BasicMolecule(*this));
}

Chem::BasicMolecule& Chem::BasicMolecule::operator=(const BasicMolecule& mol)
{
	if (this == &mol)
		return *this;

	copy(mol);

	return *this;
}

Chem::BasicMolecule& Chem::BasicMolecule::operator+=(const BasicMolecule& mol)
{
	append(mol);

	return *this;
}

void Chem::BasicMolecule::copy(const BasicMolecule& mol)
{
	if (this == &mol)
		return;

	clearAtomsAndBonds();
	copyProperties(mol);

	if (mol.atoms.size() == 0)
		return;

	reserveMemoryForAtoms(mol.atoms.size());
	reserveMemoryForBonds(mol.bonds.size());
	
	AtomList::const_iterator mol_atoms_end = mol.atoms.end();

	for (AtomList::const_iterator it = mol.atoms.begin(); it != mol_atoms_end; ++it) 
		addAtom().copyProperties(**it); 

	BondList::const_iterator mol_bonds_end = mol.bonds.end();

	for (BondList::const_iterator it = mol.bonds.begin(); it != mol_bonds_end; ++it) {
		const Bond* bond = it->get();		

		addBond(bond->getBegin().getIndex(), bond->getEnd().getIndex()).copyProperties(*bond);
	} 
}

void Chem::BasicMolecule::copy(const Molecule& mol)
{   
	if (this == &mol)
		return;

	doCopy(mol);
	copyProperties(mol);
}

void Chem::BasicMolecule::copy(const MolecularGraph& molgraph)
{   
	if (this == &molgraph)
		return;

	doCopy(molgraph);
	copyProperties(molgraph);
}

void Chem::BasicMolecule::append(const BasicMolecule& mol)
{
	std::size_t mol_num_atoms = mol.atoms.size();

	if (mol_num_atoms == 0)
		return;

	std::size_t old_num_atoms = atoms.size();

	reserveMemoryForAtoms(mol_num_atoms + old_num_atoms);
	reserveMemoryForBonds(mol.bonds.size() + bonds.size());

	AtomList::const_iterator mol_atoms_end = mol.atoms.end();

	for (AtomList::const_iterator it = mol.atoms.begin(); it != mol_atoms_end; ++it) 
		addAtom().copyProperties(**it); 

	BondList::const_iterator mol_bonds_end = mol.bonds.end();
	
	for (BondList::const_iterator it = mol.bonds.begin(); it != mol_bonds_end; ++it) {
		const Bond* bond = it->get();		

		addBond(old_num_atoms + bond->getBegin().getIndex(), old_num_atoms + bond->getEnd().getIndex()).copyProperties(*bond); 
	}
}

void Chem::BasicMolecule::append(const Molecule& mol)
{   
	doAppend(mol);
}

void Chem::BasicMolecule::append(const MolecularGraph& molgraph)
{   
	doAppend(molgraph);
}

void Chem::BasicMolecule::remove(const MolecularGraph& molgraph)
{
	if (this == &molgraph) {
		clear();
		return;
	}
	
	for (MolecularGraph::ConstAtomIterator it = molgraph.getAtomsBegin(), end = molgraph.getAtomsEnd(); it != end; ++it) {
		const Atom& atom = *it;

		if (!containsAtom(atom))
			continue;

		removeAtom(atom.getIndex());
	}

	for (MolecularGraph::ConstBondIterator it = molgraph.getBondsBegin(), end = molgraph.getBondsEnd(); it != end; ++it) {
		const Bond& bond = *it;

		if (!containsBond(bond))
			continue;

		removeBond(bond.getIndex());
	}
}

void Chem::BasicMolecule::reserveMemoryForAtoms(std::size_t num_atoms)
{
	atoms.reserve(num_atoms);
}

void Chem::BasicMolecule::reserveMemoryForBonds(std::size_t num_bonds)
{
	bonds.reserve(num_bonds);
}

template <typename T>
void Chem::BasicMolecule::doCopy(const T& mol)
{   
	clearAtomsAndBonds();

	if (mol.getNumAtoms() == 0)
		return;

	reserveMemoryForAtoms(mol.getNumAtoms());
	reserveMemoryForBonds(mol.getNumBonds());

	typename T::ConstAtomIterator mol_atoms_end = mol.getAtomsEnd();

	for (typename T::ConstAtomIterator it = mol.getAtomsBegin(); it != mol_atoms_end; ++it)  
		addAtom().copyProperties(*it);

	typename T::ConstBondIterator mol_bonds_end = mol.getBondsEnd();

	for (typename T::ConstBondIterator it = mol.getBondsBegin(); it != mol_bonds_end; ++it) {
		const Bond& bond = *it;

		addBond(mol.getAtomIndex(bond.getBegin()), mol.getAtomIndex(bond.getEnd())).copyProperties(bond); 
	}
}

template <typename T>
void Chem::BasicMolecule::doAppend(const T& mol)
{   
	std::size_t mol_num_atoms = mol.getNumAtoms();

	if (mol_num_atoms == 0)
		return;

	std::size_t old_num_atoms = atoms.size();

	reserveMemoryForAtoms(mol_num_atoms + old_num_atoms);
	reserveMemoryForBonds(mol.getNumBonds() + bonds.size());

	typename T::ConstAtomIterator mol_atoms_end = mol.getAtomsEnd();

	for (typename T::ConstAtomIterator it = mol.getAtomsBegin(); it != mol_atoms_end; ++it) 
		addAtom().copyProperties(*it);

	typename T::ConstBondIterator mol_bonds_end = mol.getBondsEnd();

	for (typename T::ConstBondIterator it = mol.getBondsBegin(); it != mol_bonds_end; ++it) {
		const Bond& bond = *it;

		addBond(mol.getAtomIndex(bond.getBegin()) + old_num_atoms, mol.getAtomIndex(bond.getEnd()) + old_num_atoms).copyProperties(bond); 
	}
}

void Chem::BasicMolecule::clearAtomsAndBonds()
{
	atoms.clear();
	bonds.clear();
}
		
void Chem::BasicMolecule::renumberAtoms(std::size_t idx)
{
	assert(idx <= atoms.size());

	AtomList::iterator atoms_end = atoms.end();

	for (AtomList::iterator it = atoms.begin() + idx; it != atoms_end; ++it, idx++)
		(*it)->setIndex(idx);
}

void Chem::BasicMolecule::renumberBonds(std::size_t idx)
{
	assert(idx <= bonds.size());

	BondList::iterator bonds_end = bonds.end();

	for (BondList::iterator it = bonds.begin() + idx; it != bonds_end; ++it, idx++)
		(*it)->setIndex(idx);
}

Chem::BasicAtom* Chem::BasicMolecule::createAtom()
{
	return new BasicAtom(this);
}

void Chem::BasicMolecule::destroyAtom(BasicAtom* atom)
{
	delete atom;
}

void Chem::BasicMolecule::clearAtom(BasicAtom& atom)
{
	atom.setIndex(~std::size_t(0));
	atom.clearProperties();
	atom.clearAdjacencyLists();
}

Chem::BasicBond* Chem::BasicMolecule::createBond()
{
	return new BasicBond(this);
}

void Chem::BasicMolecule::destroyBond(BasicBond* bond)
{
	delete bond;
}

void Chem::BasicMolecule::clearBond(BasicBond& bond)
{
	bond.setIndex(~std::size_t(0));
	bond.clearProperties();
}
