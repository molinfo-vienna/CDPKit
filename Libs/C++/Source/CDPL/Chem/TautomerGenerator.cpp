/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * TautomerGenerator.cpp 
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

#include <boost/bind.hpp>

#include "CDPL/Chem/TautomerGenerator.hpp"
#include "CDPL/Chem/BasicMolecule.hpp"
#include "CDPL/Chem/AtomFunctions.hpp"
#include "CDPL/Chem/MoleculeFunctions.hpp"
#include "CDPL/Chem/MolecularGraphFunctions.hpp"
#include "CDPL/Chem/BondFunctions.hpp"
#include "CDPL/Chem/AtomType.hpp"
#include "CDPL/Internal/SHA1.hpp"


using namespace CDPL;


class Chem::TautomerGenerator::SafeMoleculePtr
{

public:
	SafeMoleculePtr(Molecule* mol, TautomerGenerator* gen): mol(mol), gen(gen) {}

	~SafeMoleculePtr() {
		if (mol)
			gen->freeMolecule(mol);
	}

	Molecule* release() {
        Molecule* tmp = mol;
		mol = 0;
        return tmp;
	}

	Molecule* get() const {
		return mol;
	}

private:
	SafeMoleculePtr(const SafeMoleculePtr&);
	SafeMoleculePtr& operator=(const SafeMoleculePtr&);

	Molecule*          mol;
	TautomerGenerator* gen;
};


Chem::TautomerGenerator::TautomerGenerator(): mode(TOPOLOGICALLY_UNIQUE) 
{
	hashCalculator.setAtomHashSeedFunction(HashCodeCalculator::DefAtomHashSeedFunctor(hashCalculator,
																					  AtomPropertyFlag::TYPE | 
																					  AtomPropertyFlag::ISOTOPE |
																					  AtomPropertyFlag::FORMAL_CHARGE));
	hashCalculator.setBondHashSeedFunction(HashCodeCalculator::DefBondHashSeedFunctor(hashCalculator, BondPropertyFlag::ORDER));
	hashCalculator.includeGlobalStereoFeatures(false);
}

Chem::TautomerGenerator::TautomerGenerator(const TautomerGenerator& gen):
	callbackFunc(gen.callbackFunc), mode(gen.mode)
{
	std::transform(gen.tautRules.begin(), gen.tautRules.end(), std::back_inserter(tautRules), boost::bind(&TautomerizationRule::clone, _1));
}

Chem::TautomerGenerator& Chem::TautomerGenerator::operator=(const TautomerGenerator& gen) 
{
	if (this == &gen)
		return *this;

	callbackFunc = gen.callbackFunc;
	mode = gen.mode;

	tautRules.clear();

	std::transform(gen.tautRules.begin(), gen.tautRules.end(), std::back_inserter(tautRules), boost::bind(&TautomerizationRule::clone, _1));

	return *this;
}

void Chem::TautomerGenerator::addTautomerizationRule(const TautomerizationRule::SharedPointer& rule)
{
	tautRules.push_back(rule);
}

const Chem::TautomerizationRule::SharedPointer& Chem::TautomerGenerator::getTautomerizationRule(std::size_t idx) const
{
	if (idx >= tautRules.size())
		throw Base::IndexError("TautomerGenerator: rule index out of bounds");

	return tautRules[idx];
}

void Chem::TautomerGenerator::removeTautomerizationRule(std::size_t idx)
{
	if (idx >= tautRules.size())
		throw Base::IndexError("TautomerGenerator: rule index out of bounds");

	tautRules.erase(tautRules.begin() + idx);
}

std::size_t Chem::TautomerGenerator::getNumTautomerizationRules() const
{
	return tautRules.size();
}

void Chem::TautomerGenerator::setCallbackFunction(const CallbackFunction& func)
{
    callbackFunc = func;
}

const Chem::TautomerGenerator::CallbackFunction& Chem::TautomerGenerator::getCallbackFunction() const
{
    return callbackFunc;
}

void Chem::TautomerGenerator::setMode(Mode mode)
{
	this->mode = mode;
}

Chem::TautomerGenerator::Mode Chem::TautomerGenerator::getMode() const
{
	return mode;
}

void Chem::TautomerGenerator::generate(const MolecularGraph& molgraph)
{
    if (!callbackFunc)
		return;

	if (!init(molgraph))
		return;

	TautRuleList::const_iterator rules_beg = tautRules.begin();
	TautRuleList::const_iterator rules_end = tautRules.end();

	while (!nextGeneration.empty()) {
		currGeneration.swap(nextGeneration);

		while (!currGeneration.empty()) {
			SafeMoleculePtr mol(currGeneration.back(), this);
			currGeneration.pop_back();

			for (TautRuleList::const_iterator r_it = rules_beg; r_it != rules_end; ++r_it) {
				TautomerizationRule& rule = **r_it;

				if (!rule.setup(*mol.get()))
					continue;

				while (true) {
					SafeMoleculePtr tautomer(allocMolecule(), this);

					if (rule.generate(*tautomer.get())) {
						if (!addNewTautomer(tautomer.get())) 
							continue;

						if (!callbackFunc(*tautomer.release()))
							return;
					} else
						break;
				}
			}
		}
	}
}

bool Chem::TautomerGenerator::init(const MolecularGraph& molgraph)
{
	freeCurrentGenTautomers();
	freeNextGenTautomers();

	tautHashCodes.clear();

	SafeMoleculePtr mol(allocMolecule(), this);

	mol.get()->copy(molgraph);

    calcImplicitHydrogenCounts(*mol.get(), false);
	makeHydrogenComplete(*mol.get());
    calcImplicitHydrogenCounts(*mol.get(), true);

	if (!addNewTautomer(mol.get()))
		return false;

	return callbackFunc(*mol.release());
}

bool Chem::TautomerGenerator::addNewTautomer(Molecule* mol)
{
	Base::uint64 hash = calcTautomerHashCode(*mol);

	if (tautHashCodes.insert(hash).second) {
		nextGeneration.push_back(mol);
		return true;
	}

	return false;
}

Base::uint64 Chem::TautomerGenerator::calcTautomerHashCode(const Molecule& tautomer)
{
	if (mode == TOPOLOGICALLY_UNIQUE)
		return hashCalculator.calculate(tautomer);

	BondDescriptor bond_desc;

	tautomerBonds.clear();

	for (Molecule::ConstBondIterator it = tautomer.getBondsBegin(), end = tautomer.getBondsEnd(); it != end; ++it) {
		const Bond& bond = *it;

		if (mode == GEOMETRICALLY_UNIQUE && 
			(isOrdinaryHydrogen(bond.getBegin(), tautomer) || isOrdinaryHydrogen(bond.getEnd(), tautomer)))
			continue;

		std::size_t atom1_idx = bond.getBegin().getIndex();
		std::size_t atom2_idx = bond.getEnd().getIndex();

		if (atom2_idx > atom1_idx)
			std::swap(atom1_idx, atom2_idx);

		bond_desc[0] = atom1_idx;
		bond_desc[1] = atom2_idx;
		bond_desc[2] = getOrder(bond);

		tautomerBonds.push_back(bond_desc);
	}

	std::sort(tautomerBonds.begin(), tautomerBonds.end());

	shaInput.clear();

	for (BondDescrArray::const_iterator it = tautomerBonds.begin(), end = tautomerBonds.end(); it != end; ++it) {
		const BondDescriptor& descr = *it;

		shaInput.push_back(descr[0]);
		shaInput.push_back(descr[1]);
		shaInput.push_back(descr[2]);
	}

	Internal::SHA1 sha;
	Base::uint8 sha_hash[Internal::SHA1::HASH_SIZE];

	sha.input(shaInput.begin(), shaInput.end());
	sha.getResult(&sha_hash[0]);

	Base::uint64 hash_code = 0;

	for (std::size_t i = 0; i < Internal::SHA1::HASH_SIZE; i++) 
		hash_code = hash_code ^ (Base::uint64(sha_hash[i]) << ((i % 8) * 8));

	return hash_code;
}

void Chem::TautomerGenerator::freeCurrentGenTautomers()
{
	std::for_each(currGeneration.begin(), currGeneration.end(), boost::bind(&TautomerGenerator::freeMolecule, this, _1));	

	currGeneration.clear();
}

void Chem::TautomerGenerator::freeNextGenTautomers()
{
	std::for_each(nextGeneration.begin(), nextGeneration.end(), boost::bind(&TautomerGenerator::freeMolecule, this, _1));	

	nextGeneration.clear();
}

Chem::Molecule* Chem::TautomerGenerator::allocMolecule()
{
    if (!freeMolecules.empty()) {
		Molecule* mol = freeMolecules.back();

		freeMolecules.pop_back();

		return mol;
    }

    BasicMolecule::SharedPointer mol_ptr(new BasicMolecule());

    allocMolecules.push_back(mol_ptr);
	freeMolecules.reserve(allocMolecules.size());

    return mol_ptr.get();
}
			
void Chem::TautomerGenerator::freeMolecule(Molecule* mol)
{
    freeMolecules.push_back(mol);
}
