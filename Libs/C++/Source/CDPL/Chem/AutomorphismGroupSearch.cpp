/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * AutomorphismGroupSearch.cpp 
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
#include <functional>

#include <boost/bind.hpp>

#include "CDPL/Chem/AutomorphismGroupSearch.hpp"
#include "CDPL/Chem/AtomFunctions.hpp"
#include "CDPL/Chem/BondFunctions.hpp"
#include "CDPL/Chem/AtomType.hpp"
#include "CDPL/Chem/AtomConfigurationMatchExpression.hpp"
#include "CDPL/Chem/BondConfigurationMatchExpression.hpp"


using namespace CDPL;


const unsigned int Chem::AutomorphismGroupSearch::DEF_ATOM_PROPERTY_FLAGS;
const unsigned int Chem::AutomorphismGroupSearch::DEF_BOND_PROPERTY_FLAGS;


Chem::AutomorphismGroupSearch::AutomorphismGroupSearch(unsigned int atom_flags, unsigned int bond_flags):
    incIdentityMapping(true), atomPropFlags(atom_flags), bondPropFlags(bond_flags),
	atomMatchExpr(new AtomMatchExpression(this)),
    bondMatchExpr(new BondMatchExpression(this)),
    molGraphMatchExpr(new MolGraphMatchExpression(this))

{
    substructSearch.setAtomMatchExpressionFunction(boost::bind(&AutomorphismGroupSearch::getAtomMatchExpression, this, _1));
    substructSearch.setBondMatchExpressionFunction(boost::bind(&AutomorphismGroupSearch::getBondMatchExpression, this, _1));
    substructSearch.setMolecularGraphMatchExpressionFunction(boost::bind(&AutomorphismGroupSearch::getMolGraphMatchExpression, this, _1));

    substructSearch.uniqueMappingsOnly(false);
    substructSearch.setMaxNumMappings(0);
}

void Chem::AutomorphismGroupSearch::setAtomPropertyFlags(unsigned int flags)
{
    atomPropFlags = flags;
}

unsigned int Chem::AutomorphismGroupSearch::getAtomPropertyFlags() const
{
	return atomPropFlags;
}

void Chem::AutomorphismGroupSearch::setBondPropertyFlags(unsigned int flags)
{
    bondPropFlags = flags;
}

unsigned int Chem::AutomorphismGroupSearch::getBondPropertyFlags() const
{
	return bondPropFlags;
}

void Chem::AutomorphismGroupSearch::includeIdentityMapping(bool include)
{
	incIdentityMapping = include;
}

bool Chem::AutomorphismGroupSearch::identityMappingIncluded() const
{
	return incIdentityMapping;
}

bool Chem::AutomorphismGroupSearch::findMappings(const MolecularGraph& molgraph)
{
	lastQueryAtom = 0;
	lastQueryBond = 0;

	substructSearch.setQuery(molgraph);

    return substructSearch.findMappings(molgraph);
}

std::size_t Chem::AutomorphismGroupSearch::getNumMappings() const
{
    return substructSearch.getNumMappings();
}

Chem::AtomBondMapping& Chem::AutomorphismGroupSearch::getMapping(std::size_t idx)
{
    return substructSearch.getMapping(idx);
}

const Chem::AtomBondMapping& Chem::AutomorphismGroupSearch::getMapping(std::size_t idx) const
{
    return substructSearch.getMapping(idx);
}

Chem::AutomorphismGroupSearch::MappingIterator Chem::AutomorphismGroupSearch::getMappingsBegin()
{
    return substructSearch.getMappingsBegin();
}

Chem::AutomorphismGroupSearch::ConstMappingIterator Chem::AutomorphismGroupSearch::getMappingsBegin() const
{
    return substructSearch.getMappingsBegin();
}

Chem::AutomorphismGroupSearch::MappingIterator Chem::AutomorphismGroupSearch::getMappingsEnd()
{
    return substructSearch.getMappingsEnd();
}

Chem::AutomorphismGroupSearch::ConstMappingIterator Chem::AutomorphismGroupSearch::getMappingsEnd() const
{
    return substructSearch.getMappingsEnd();
}

void Chem::AutomorphismGroupSearch::setMaxNumMappings(std::size_t max_num_mappings)
{
    substructSearch.setMaxNumMappings(max_num_mappings);
}

std::size_t Chem::AutomorphismGroupSearch::getMaxNumMappings() const
{
    return substructSearch.getMaxNumMappings();
}

const Chem::MatchExpression<Chem::Atom, Chem::MolecularGraph>::SharedPointer&
Chem::AutomorphismGroupSearch::getAtomMatchExpression(const Atom& atom) const
{
    return atomMatchExpr;
}

const Chem::MatchExpression<Chem::Bond, Chem::MolecularGraph>::SharedPointer& 
Chem::AutomorphismGroupSearch::getBondMatchExpression(const Bond& bond) const
{
    return bondMatchExpr;
}

const Chem::MatchExpression<Chem::MolecularGraph>::SharedPointer&  
Chem::AutomorphismGroupSearch::getMolGraphMatchExpression(const MolecularGraph& molgraph) const
{
    return molGraphMatchExpr;
}


bool Chem::AutomorphismGroupSearch::AtomMatchExpression::requiresAtomBondMapping() const
{
	return (parent->atomPropFlags & AtomPropertyFlag::CONFIGURATION);
}

bool Chem::AutomorphismGroupSearch::AtomMatchExpression::operator()(const Atom& query_atom, const MolecularGraph& query_molgraph, 
																	const Atom& target_atom, const MolecularGraph& target_molgraph,
																	const Base::Variant& aux_data) const
{
	
	if (parent->lastQueryAtom != &query_atom) {
		if (parent->atomPropFlags & AtomPropertyFlag::TYPE)
			type = getType(query_atom);
	
		if (parent->atomPropFlags & AtomPropertyFlag::HYBRIDIZATION_STATE)
			hybState = getHybridizationState(query_atom);

		if (parent->atomPropFlags & AtomPropertyFlag::ISOTOPE)
			isotope = getIsotope(query_atom);
 
		if (parent->atomPropFlags & AtomPropertyFlag::H_COUNT)
			hCount = getBondCount(query_atom, query_molgraph, 1, AtomType::H);

		if (parent->atomPropFlags & AtomPropertyFlag::FORMAL_CHARGE)
			charge = getFormalCharge(query_atom);

		if (parent->atomPropFlags & AtomPropertyFlag::AROMATICITY)
			aromatic = getAromaticityFlag(query_atom);

		if (parent->atomPropFlags & AtomPropertyFlag::EXPLICIT_BOND_COUNT)
			expBondCount = getExplicitBondCount(query_atom, query_molgraph);

		if (parent->atomPropFlags & AtomPropertyFlag::CONFIGURATION)
			stereoDescr = getStereoDescriptor(query_atom);

		parent->lastQueryAtom = &query_atom;
	}

	if ((parent->atomPropFlags & AtomPropertyFlag::TYPE) && (type != getType(target_atom)))
		return false;

	if ((parent->atomPropFlags & AtomPropertyFlag::TYPE) && (hybState != getHybridizationState(target_atom)))
		return false;

	if ((parent->atomPropFlags & AtomPropertyFlag::ISOTOPE) && (isotope != getIsotope(target_atom)))
		return false;
 
	if ((parent->atomPropFlags & AtomPropertyFlag::FORMAL_CHARGE) && (charge != getFormalCharge(target_atom)))
		return false;

	if ((parent->atomPropFlags & AtomPropertyFlag::AROMATICITY) && (aromatic != getAromaticityFlag(target_atom)))
		return false;

	if ((parent->atomPropFlags & AtomPropertyFlag::EXPLICIT_BOND_COUNT) && (expBondCount != getExplicitBondCount(target_atom, target_molgraph)))
		return false;

	if ((parent->atomPropFlags & AtomPropertyFlag::H_COUNT) && (hCount != getBondCount(target_atom, target_molgraph, 1, AtomType::H)))
		return false;

    return true;
}

bool Chem::AutomorphismGroupSearch::AtomMatchExpression::operator()(const Atom& query_atom, const MolecularGraph& query_molgraph, 
																	const Atom& target_atom, const MolecularGraph& target_molgraph, 
																	const AtomBondMapping& mapping, const Base::Variant& aux_data) const
{
	if ((parent->atomPropFlags & AtomPropertyFlag::CONFIGURATION) == 0)
		return true;

	return AtomConfigurationMatchExpression(stereoDescr, query_atom, false, false)(query_atom, query_molgraph, target_atom, target_molgraph, 
																				   mapping, aux_data);
}


bool Chem::AutomorphismGroupSearch::BondMatchExpression::requiresAtomBondMapping() const
{
	return (parent->bondPropFlags & BondPropertyFlag::CONFIGURATION);
}

bool Chem::AutomorphismGroupSearch::BondMatchExpression::operator()(const Bond& query_bond, const MolecularGraph& query_molgraph, 
																	const Bond& target_bond, const MolecularGraph& target_molgraph, 
																	const Base::Variant& aux_data) const
{
 	if (parent->lastQueryBond != &query_bond) {
		if (parent->bondPropFlags & BondPropertyFlag::ORDER)
			order = getOrder(query_bond);

		if (parent->bondPropFlags & BondPropertyFlag::TOPOLOGY)
			inRing = getRingFlag(query_bond);
 
		if (parent->bondPropFlags & (BondPropertyFlag::AROMATICITY | BondPropertyFlag::ORDER))
			aromatic = getAromaticityFlag(query_bond);

		if (parent->bondPropFlags & BondPropertyFlag::CONFIGURATION)
			stereoDescr = getStereoDescriptor(query_bond);

		parent->lastQueryBond = &query_bond;
	}

	if ((parent->bondPropFlags & BondPropertyFlag::TOPOLOGY) && (inRing != getRingFlag(target_bond)))
		return false;

	if ((parent->bondPropFlags & BondPropertyFlag::AROMATICITY) && (aromatic != getAromaticityFlag(target_bond)))
		return false;

	if (parent->bondPropFlags & BondPropertyFlag::ORDER) {
		std::size_t tgt_order = getOrder(target_bond);

		if (aromatic) 
			return (tgt_order == 1 || tgt_order == 2 || tgt_order == 3);

		else switch (order) {

				case 1:
				case 2:
				case 3:
					return (order == tgt_order || getAromaticityFlag(target_bond));

				default:
					return (order == tgt_order);	
			}
	}

	return true;
}

bool Chem::AutomorphismGroupSearch::BondMatchExpression::operator()(const Bond& query_bond, const MolecularGraph& query_molgraph, 
																	const Bond& target_bond, const MolecularGraph& target_molgraph, 
																	const AtomBondMapping& mapping, const Base::Variant& aux_data) const
{
 	if (!(parent->bondPropFlags & BondPropertyFlag::CONFIGURATION) == 0)
		return true;

	return BondConfigurationMatchExpression(stereoDescr, query_bond, false, false)(query_bond, query_molgraph, target_bond, target_molgraph, 
																				   mapping, aux_data);
}


bool Chem::AutomorphismGroupSearch::MolGraphMatchExpression::requiresAtomBondMapping() const
{
	return !parent->incIdentityMapping;
}

bool Chem::AutomorphismGroupSearch::MolGraphMatchExpression::operator()(const MolecularGraph& query_molgraph, 
																		const MolecularGraph& target_molgraph, 
																		const Base::Variant& aux_data) const
{
	return true;
}

bool Chem::AutomorphismGroupSearch::MolGraphMatchExpression::operator()(const MolecularGraph& query_molgraph, 
																		const MolecularGraph& target_molgraph, 
																		const AtomBondMapping& mapping, const Base::Variant& aux_data) const
{
 	if (parent->incIdentityMapping)
		return true;

	const AtomMapping& am = mapping.getAtomMapping();

	return (std::find_if(am.getEntriesBegin(), am.getEntriesEnd(), 
						 boost::bind(std::not_equal_to<const Atom*>(), 
									 boost::bind(&AtomMapping::Entry::first, _1), boost::bind(&AtomMapping::Entry::second, _1))) != 
			am.getEntriesEnd());
}
