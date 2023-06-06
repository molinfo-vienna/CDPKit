/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * Reactor.cpp 
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
#include <mutex>

#include "CDPL/Chem/Reactor.hpp"
#include "CDPL/Chem/Molecule.hpp"
#include "CDPL/Chem/Atom.hpp"
#include "CDPL/Chem/Bond.hpp"
#include "CDPL/Chem/MolecularGraphFunctions.hpp"
#include "CDPL/Chem/AtomFunctions.hpp"
#include "CDPL/Chem/BondFunctions.hpp"
#include "CDPL/Chem/AtomMatchConstraint.hpp"
#include "CDPL/Chem/BondMatchConstraint.hpp"
#include "CDPL/Chem/AtomBondMapping.hpp"
#include "CDPL/Chem/AtomProperty.hpp"
#include "CDPL/Chem/BondProperty.hpp"
#include "CDPL/Chem/ReactionRole.hpp"
#include "CDPL/Chem/StereoDescriptor.hpp"
#include "CDPL/Chem/AtomType.hpp"


using namespace CDPL;


namespace
{

	const Base::Any NULL_PROPERTY;

	typedef std::map<Base::LookupKey, unsigned int> PropertyToConstraintIDMap;

	PropertyToConstraintIDMap propertyToConstraintIDMap;

	std::once_flag initPropertyConstraintIDMapFlag;

	void initPropertyConstraintIDMap() 
	{
		using namespace Chem;

		propertyToConstraintIDMap[AtomProperty::STEREO_DESCRIPTOR] = AtomMatchConstraint::CONFIGURATION;
		propertyToConstraintIDMap[AtomProperty::FORMAL_CHARGE] = AtomMatchConstraint::CHARGE;
		propertyToConstraintIDMap[AtomProperty::TYPE] = AtomMatchConstraint::TYPE;
		propertyToConstraintIDMap[AtomProperty::ISOTOPE] = AtomMatchConstraint::ISOTOPE;
		propertyToConstraintIDMap[AtomProperty::IMPLICIT_HYDROGEN_COUNT] = AtomMatchConstraint::IMPLICIT_H_COUNT;
		propertyToConstraintIDMap[BondProperty::ORDER] = BondMatchConstraint::ORDER;
		propertyToConstraintIDMap[BondProperty::STEREO_DESCRIPTOR] = BondMatchConstraint::CONFIGURATION;
	}

	const Base::Any& extractConstraintValue(unsigned int constr_id, const Chem::MatchConstraintList& constr_list)
	{
		using namespace Chem;

		MatchConstraintList::ConstElementIterator constr_end = constr_list.getElementsEnd();
				
		for (MatchConstraintList::ConstElementIterator it = constr_list.getElementsBegin(); it != constr_end; ++it) {
			const MatchConstraint& constraint = *it;

			if (!constraint.hasValue())
				continue;

			if (constraint.getID() == constr_id) {
				if (constraint.getRelation() == MatchConstraint::EQUAL)
					return constraint.getValue();

				continue;
			}

			if (constraint.getID() == AtomMatchConstraint::CONSTRAINT_LIST || 
				constraint.getID() == BondMatchConstraint::CONSTRAINT_LIST) {
				
				const Base::Any& value = 
					extractConstraintValue(constr_id, *constraint.getValue<MatchConstraintList::SharedPointer>());

				if (!value.isEmpty())
					return value;
			}
		}

		return NULL_PROPERTY;
	}
}


Chem::Reactor::Reactor(): rxnPattern(0), rxnTarget(0)  
{
	rxnSiteSearch.setEnabledReactionRoles(ReactionRole::REACTANT);
}

Chem::Reactor::Reactor(const Reaction& rxn_pattern): rxnTarget(0)  
{
	rxnSiteSearch.setEnabledReactionRoles(ReactionRole::REACTANT);

	setReactionPattern(rxn_pattern);
}

Chem::Reactor::~Reactor() {}

bool Chem::Reactor::findReactionSites(Reaction& rxn_target)
{
	rxnTarget = &rxn_target;

	return rxnSiteSearch.findMappings(rxn_target);
}

void Chem::Reactor::performReaction(const ReactionSite& rxn_site)
{
	if (!rxnTarget)
		return;

	Molecule* tgt_prod = copyReactants(rxn_site);

	createAtoms(tgt_prod);
	createBonds(tgt_prod);

	deleteBonds(rxn_site, tgt_prod);
	deleteAtoms(rxn_site, tgt_prod);

	editAtoms();
	editBonds();

	editStereoProperties();
}

void Chem::Reactor::setReactionPattern(const Reaction& rxn_pattern)
{
	rxnPattern = &rxn_pattern;
	rxnSiteSearch.setQuery(rxn_pattern);

	init();
}

std::size_t Chem::Reactor::getNumReactionSites() const
{
	return rxnSiteSearch.getNumMappings();
}

Chem::Reactor::ReactionSite& Chem::Reactor::getReactionSite(std::size_t idx)
{
	return rxnSiteSearch.getMapping(idx);
}

const Chem::Reactor::ReactionSite& Chem::Reactor::getReactionSite(std::size_t idx) const
{
	return rxnSiteSearch.getMapping(idx);
}

Chem::Reactor::ReactionSiteIterator Chem::Reactor::getReactionSitesBegin()
{
	return rxnSiteSearch.getMappingsBegin();
}

Chem::Reactor::ConstReactionSiteIterator Chem::Reactor::getReactionSitesBegin() const
{
	return rxnSiteSearch.getMappingsBegin();
}

Chem::Reactor::ReactionSiteIterator Chem::Reactor::getReactionSitesEnd()
{
	return rxnSiteSearch.getMappingsEnd();
}

Chem::Reactor::ConstReactionSiteIterator Chem::Reactor::getReactionSitesEnd() const
{
	return rxnSiteSearch.getMappingsEnd();
}

void Chem::Reactor::init()
{
	std::call_once(initPropertyConstraintIDMapFlag, &initPropertyConstraintIDMap);

	reacAtomsToDelete.clear();
	reacBondsToDelete.clear();

	Reaction::ConstComponentIterator reacs_end = rxnPattern->getComponentsEnd(ReactionRole::REACTANT);

	for (Reaction::ConstComponentIterator c_it = rxnPattern->getComponentsBegin(ReactionRole::REACTANT); c_it != reacs_end; ++c_it) {
		const Molecule& reac = *c_it;
		std::size_t num_atoms = reac.getNumAtoms();

		mappedAtomMask.reset();

		if (mappedAtomMask.size() < num_atoms)
			mappedAtomMask.resize(num_atoms);

		Molecule::ConstAtomIterator atoms_end = reac.getAtomsEnd();

		for (Molecule::ConstAtomIterator a_it = reac.getAtomsBegin(); a_it != atoms_end; ++a_it) {
			const Atom& atom = *a_it;
			std::size_t aam_class_id = getAtomMappingID(atom);

			if (aam_class_id > 0) {
				reacAtomsToDelete[aam_class_id] = &atom;
				mappedAtomMask.set(reac.getAtomIndex(atom));
			}
		}

		Molecule::ConstBondIterator bonds_end = reac.getBondsEnd();

		for (Molecule::ConstBondIterator b_it = reac.getBondsBegin(); b_it != bonds_end; ++b_it) {
			const Bond& bond = *b_it;
			const Atom& atom1 = bond.getBegin();

			if (!mappedAtomMask.test(reac.getAtomIndex(atom1)))
				continue;

			const Atom& atom2 = bond.getEnd();

			if (!mappedAtomMask.test(reac.getAtomIndex(atom2)))
				continue;

			IDPair atom_ids(getAtomMappingID(atom1), getAtomMappingID(atom2));

			if (atom_ids.first > atom_ids.second)
				std::swap(atom_ids.first, atom_ids.second);

			reacBondsToDelete[atom_ids] = &bond;
		}
	}

	prodAtomsToCreate.clear();
	prodBondsToCreate.clear();

	Reaction::ConstComponentIterator prods_end = rxnPattern->getComponentsEnd(ReactionRole::PRODUCT);

	for (Reaction::ConstComponentIterator c_it = rxnPattern->getComponentsBegin(ReactionRole::PRODUCT); c_it != prods_end; ++c_it) {
		const Molecule& prod = *c_it;
		std::size_t num_atoms = prod.getNumAtoms();

		mappedAtomMask.reset();

		if (mappedAtomMask.size() < num_atoms)
			mappedAtomMask.resize(num_atoms);

		Molecule::ConstAtomIterator atoms_end = prod.getAtomsEnd();

		for (Molecule::ConstAtomIterator a_it = prod.getAtomsBegin(); a_it != atoms_end; ++a_it) {
			const Atom& atom = *a_it;
			std::size_t aam_class_id = getAtomMappingID(atom);

			if (aam_class_id > 0) {
				prodAtomsToCreate[aam_class_id] = &atom;
				mappedAtomMask.set(prod.getAtomIndex(atom));
			}
		}

		Molecule::ConstBondIterator bonds_end = prod.getBondsEnd();

		for (Molecule::ConstBondIterator b_it = prod.getBondsBegin(); b_it != bonds_end; ++b_it) {
			const Bond& bond = *b_it;
			const Atom& atom1 = bond.getBegin();

			if (!mappedAtomMask.test(prod.getAtomIndex(atom1)))
				continue;

			const Atom& atom2 = bond.getEnd();

			if (!mappedAtomMask.test(prod.getAtomIndex(atom2)))
				continue;

			IDPair atom_ids(getAtomMappingID(atom1), getAtomMappingID(atom2));

			if (atom_ids.first > atom_ids.second)
				std::swap(atom_ids.first, atom_ids.second);

			prodBondsToCreate[atom_ids] = &bond;
		}
	}

	ptnAtomMapping.clear();

	IDAtomMap::iterator deleted_atoms_end = reacAtomsToDelete.end();
	IDAtomMap::iterator created_atoms_end = prodAtomsToCreate.end();

	for (IDAtomMap::iterator it = reacAtomsToDelete.begin(); it != deleted_atoms_end; ) {
		IDAtomMap::iterator prod_map_it = prodAtomsToCreate.find(it->first);

		if (prod_map_it != created_atoms_end) {
			ptnAtomMapping.push_back(AtomPair(it->second, prod_map_it->second));

			reacAtomsToDelete.erase(it++);
			prodAtomsToCreate.erase(prod_map_it);

		} else
			++it;
	}

	ptnBondMapping.clear();

	IDPairBondMap::iterator deleted_bonds_end = reacBondsToDelete.end();
	IDPairBondMap::iterator created_bonds_end = prodBondsToCreate.end();

	for (IDPairBondMap::iterator it = reacBondsToDelete.begin(); it != deleted_bonds_end; ) {
		IDPairBondMap::iterator prod_map_it = prodBondsToCreate.find(it->first);

		if (prod_map_it != created_bonds_end) {
			ptnBondMapping.push_back(BondPair(it->second, prod_map_it->second));

			reacBondsToDelete.erase(it++);
			prodBondsToCreate.erase(prod_map_it);

		} else
			++it;
	}
}

Chem::Molecule* Chem::Reactor::copyReactants(const ReactionSite& rxn_site)
{
	tgtAtomMapping.clear();
	tgtBondMapping.clear();

	Reaction::ConstComponentIterator reacs_end = rxnTarget->getComponentsEnd(ReactionRole::REACTANT);
	Molecule* tgt_prod = 0;

	for (Reaction::ConstComponentIterator c_it = rxnTarget->getComponentsBegin(ReactionRole::REACTANT); c_it != reacs_end; ++c_it) {
		const Molecule& reac = *c_it;

		if (!tgt_prod)
			tgt_prod = &rxnTarget->addComponent(ReactionRole::PRODUCT);

		std::size_t prev_num_atoms = tgt_prod->getNumAtoms();
		std::size_t prev_num_bonds = tgt_prod->getNumBonds();

		*tgt_prod += reac;

		assert(tgt_prod->getNumAtoms() - prev_num_atoms == reac.getNumAtoms());
		assert(tgt_prod->getNumBonds() - prev_num_bonds == reac.getNumBonds());

		copyAtomStereoDescriptors(reac, *tgt_prod, prev_num_atoms);
		copyBondStereoDescriptors(reac, *tgt_prod, prev_num_atoms);

		Molecule::AtomIterator atoms_end = tgt_prod->getAtomsEnd();
		Molecule::ConstAtomIterator ra_it = reac.getAtomsBegin();

		for (Molecule::AtomIterator pa_it = tgt_prod->getAtomsBegin() + prev_num_atoms; pa_it != atoms_end; ++pa_it, ++ra_it) 
			tgtAtomMapping[&*ra_it] = &*pa_it;

		Molecule::BondIterator bonds_end = tgt_prod->getBondsEnd();
		Molecule::ConstBondIterator rb_it = reac.getBondsBegin();

		for (Molecule::BondIterator pb_it = tgt_prod->getBondsBegin() + prev_num_bonds; pb_it != bonds_end; ++pb_it, ++rb_it) 
			tgtBondMapping[&*rb_it] = &*pb_it;
	}

	const AtomMapping& atom_mapping = rxn_site.getAtomMapping();
	const BondMapping& bond_mapping = rxn_site.getBondMapping();

	AtomPairList::const_iterator ptn_atom_mapping_end = ptnAtomMapping.end();
	AtomMap::const_iterator tgt_atom_mapping_end = tgtAtomMapping.end();

	for (AtomPairList::const_iterator it = ptnAtomMapping.begin(); it != ptn_atom_mapping_end; ++it) {
		const Atom* ptn_reac_atom = it->first;
		const Atom* mpd_tgt_reac_atom = atom_mapping[ptn_reac_atom];

		if (!mpd_tgt_reac_atom)
			continue;

		AtomMap::const_iterator mpd_tgt_prod_atom_it = tgtAtomMapping.find(mpd_tgt_reac_atom);

		if (mpd_tgt_prod_atom_it == tgt_atom_mapping_end)
			continue;
		
		const Atom* ptn_prod_atom = it->second;
		Atom* mpd_tgt_prod_atom = mpd_tgt_prod_atom_it->second;

		tgtAtomMapping[ptn_reac_atom] = mpd_tgt_prod_atom;
		tgtAtomMapping[ptn_prod_atom] = mpd_tgt_prod_atom;
	}

	BondPairList::const_iterator ptn_bond_mapping_end = ptnBondMapping.end();
	BondMap::const_iterator tgt_bond_mapping_end = tgtBondMapping.end();

	for (BondPairList::const_iterator it = ptnBondMapping.begin(); it != ptn_bond_mapping_end; ++it) {
		const Bond* ptn_reac_bond = it->first;
		const Bond* mpd_tgt_reac_bond = bond_mapping[ptn_reac_bond];

		if (!mpd_tgt_reac_bond)
			continue;

		BondMap::const_iterator mpd_tgt_prod_bond_it = tgtBondMapping.find(mpd_tgt_reac_bond);

		if (mpd_tgt_prod_bond_it == tgt_bond_mapping_end)
			continue;
		
		const Bond* ptn_prod_bond = it->second;
		Bond* mpd_tgt_prod_bond = mpd_tgt_prod_bond_it->second;

		tgtBondMapping[ptn_reac_bond] = mpd_tgt_prod_bond;
		tgtBondMapping[ptn_prod_bond] = mpd_tgt_prod_bond;
	}

	return tgt_prod;
}

void Chem::Reactor::createAtoms(Molecule* tgt_prod)
{
	assert(tgt_prod);

	IDAtomMap::const_iterator created_atoms_end = prodAtomsToCreate.end();

	for (IDAtomMap::const_iterator it = prodAtomsToCreate.begin(); it != created_atoms_end; ++it) {
		const Atom* ptn_prod_atom = it->second;
		Atom* new_tgt_prod_atom = &tgt_prod->addAtom();

		tgtAtomMapping[ptn_prod_atom] = new_tgt_prod_atom;

		copyProperty(ptn_prod_atom, new_tgt_prod_atom, AtomProperty::SYMBOL);
		copyProperty(ptn_prod_atom, new_tgt_prod_atom, AtomProperty::NAME);
		copyProperty(ptn_prod_atom, new_tgt_prod_atom, AtomProperty::FORMAL_CHARGE);
		copyProperty(ptn_prod_atom, new_tgt_prod_atom, AtomProperty::TYPE);
		copyProperty(ptn_prod_atom, new_tgt_prod_atom, AtomProperty::RADICAL_TYPE);
		copyProperty(ptn_prod_atom, new_tgt_prod_atom, AtomProperty::ISOTOPE);
		copyProperty(ptn_prod_atom, new_tgt_prod_atom, AtomProperty::UNPAIRED_ELECTRON_COUNT);
	}
}

void Chem::Reactor::createBonds(Molecule* tgt_prod)
{
	assert(tgt_prod);

	IDPairBondMap::const_iterator created_bonds_end = prodBondsToCreate.end();

	for (IDPairBondMap::const_iterator it = prodBondsToCreate.begin(); it != created_bonds_end; ++it) {
		const Bond* ptn_prod_bond = it->second;

		Atom* tgt_prod_atom1 = getMappedTgtProdAtom(&ptn_prod_bond->getBegin());

		if (!tgt_prod_atom1)
			continue;

		Atom* tgt_prod_atom2 = getMappedTgtProdAtom(&ptn_prod_bond->getEnd());

		if (!tgt_prod_atom2)
			continue;

		clearStereoDescriptor(*tgt_prod_atom1);
		clearStereoDescriptor(*tgt_prod_atom2);

		Bond* new_tgt_prod_bond = &tgt_prod->addBond(tgt_prod->getAtomIndex(*tgt_prod_atom1), tgt_prod->getAtomIndex(*tgt_prod_atom2));
		tgtBondMapping[ptn_prod_bond] = new_tgt_prod_bond;

		copyProperty(ptn_prod_bond, new_tgt_prod_bond, BondProperty::ORDER);
		copyProperty(ptn_prod_bond, new_tgt_prod_bond, BondProperty::STEREO_2D_FLAG);
	}
}

void Chem::Reactor::deleteBonds(const ReactionSite& rxn_site, Molecule* tgt_prod) const
{
	assert(tgt_prod);

	const BondMapping& bond_mapping = rxn_site.getBondMapping();

	IDPairBondMap::const_iterator deleted_bonds_end = reacBondsToDelete.end();
	BondMap::const_iterator tgt_bond_mapping_end = tgtBondMapping.end();

	for (IDPairBondMap::const_iterator it = reacBondsToDelete.begin(); it != deleted_bonds_end; ++it) {
		const Bond* ptn_reac_bond = it->second;
		const Bond* mpd_tgt_reac_bond = bond_mapping[ptn_reac_bond];

		if (!mpd_tgt_reac_bond)
			continue;

		BondMap::const_iterator mpd_tgt_prod_bond_it = tgtBondMapping.find(mpd_tgt_reac_bond);

		if (mpd_tgt_prod_bond_it == tgt_bond_mapping_end)
			continue;

		Bond* tgt_prod_bond = mpd_tgt_prod_bond_it->second;

		assert(tgt_prod == &tgt_prod_bond->getMolecule());

		clearStereoDescriptor(tgt_prod_bond->getBegin());
		clearStereoDescriptor(tgt_prod_bond->getEnd());

		tgt_prod->removeBond(tgt_prod->getBondIndex(*tgt_prod_bond));
	}
}

void Chem::Reactor::deleteAtoms(const ReactionSite& rxn_site, Molecule* tgt_prod) const
{
	assert(tgt_prod);

	const AtomMapping& atom_mapping = rxn_site.getAtomMapping();

	IDAtomMap::const_iterator deleted_atoms_end = reacAtomsToDelete.end();
	AtomMap::const_iterator tgt_atom_mapping_end = tgtAtomMapping.end();

	for (IDAtomMap::const_iterator it = reacAtomsToDelete.begin(); it != deleted_atoms_end; ++it) {
		const Atom* ptn_reac_atom = it->second;
		const Atom* mpd_tgt_reac_atom = atom_mapping[ptn_reac_atom];

		if (!mpd_tgt_reac_atom)
			continue;

		AtomMap::const_iterator mpd_tgt_prod_atom_it = tgtAtomMapping.find(mpd_tgt_reac_atom);

		if (mpd_tgt_prod_atom_it == tgt_atom_mapping_end)
			continue;

		assert(tgt_prod == &mpd_tgt_prod_atom_it->second->getMolecule());

		tgt_prod->removeAtom(tgt_prod->getAtomIndex(*mpd_tgt_prod_atom_it->second));
	}
}

void Chem::Reactor::editAtoms() const
{
	AtomPairList::const_iterator ptn_atom_mapping_end = ptnAtomMapping.end();

	for (AtomPairList::const_iterator it = ptnAtomMapping.begin(); it != ptn_atom_mapping_end; ++it) {
		const Atom* ptn_reac_atom = it->first;
		Atom* tgt_prod_atom = getMappedTgtProdAtom(ptn_reac_atom);

		if (!tgt_prod_atom)
			continue;
		
		const Atom* ptn_prod_atom = it->second;

		copyProperty(ptn_prod_atom, tgt_prod_atom, AtomProperty::FORMAL_CHARGE);
		copyProperty(ptn_prod_atom, tgt_prod_atom, AtomProperty::ISOTOPE);

		const Base::Any& ptn_prod_atom_type_val = getProperty(ptn_prod_atom, AtomProperty::TYPE);

		if (ptn_prod_atom_type_val.isEmpty())
			continue;

		unsigned int ptn_prod_atom_type = ptn_prod_atom_type_val.getData<unsigned int>();

		if (ptn_prod_atom_type == AtomType::UNKNOWN || ptn_prod_atom_type > AtomType::MAX_ATOMIC_NO)
			continue;

		tgt_prod_atom->setProperty(AtomProperty::TYPE, ptn_prod_atom_type);
		tgt_prod_atom->removeProperty(AtomProperty::SYMBOL);
	}
}

void Chem::Reactor::editBonds() const
{
	BondPairList::const_iterator ptn_bond_mapping_end = ptnBondMapping.end();

	for (BondPairList::const_iterator it = ptnBondMapping.begin(); it != ptn_bond_mapping_end; ++it) {
		const Bond* ptn_reac_bond = it->first;
		Bond* tgt_prod_bond = getMappedTgtProdBond(ptn_reac_bond);

		if (!tgt_prod_bond)
			continue;
		
		const Bond* ptn_prod_bond = it->second;

		copyProperty(ptn_prod_bond, tgt_prod_bond, BondProperty::ORDER);
	}
}

void Chem::Reactor::editStereoProperties() const
{
	AtomPairList::const_iterator ptn_atom_mapping_end = ptnAtomMapping.end();

	for (AtomPairList::const_iterator it = ptnAtomMapping.begin(); it != ptn_atom_mapping_end; ++it) {
		const Atom* ptn_prod_atom = it->second;
		Atom* tgt_prod_atom = getMappedTgtProdAtom(ptn_prod_atom);

		if (!tgt_prod_atom)
			continue;

		editProdAtomStereoDescriptor(ptn_prod_atom, tgt_prod_atom);
	}

	IDAtomMap::const_iterator created_atoms_end = prodAtomsToCreate.end();

	for (IDAtomMap::const_iterator it = prodAtomsToCreate.begin(); it != created_atoms_end; ++it) {
		const Atom* ptn_prod_atom = it->second;
		Atom* tgt_prod_atom = getMappedTgtProdAtom(ptn_prod_atom);

		if (!tgt_prod_atom)
			continue;

		editProdAtomStereoDescriptor(ptn_prod_atom, tgt_prod_atom);
	}

	BondPairList::const_iterator ptn_bond_mapping_end = ptnBondMapping.end();

	for (BondPairList::const_iterator it = ptnBondMapping.begin(); it != ptn_bond_mapping_end; ++it) {
		const Bond* ptn_prod_bond = it->second;
		Bond* tgt_prod_bond = getMappedTgtProdBond(ptn_prod_bond);

		if (!tgt_prod_bond)
			continue;

		editProdBondStereoDescriptor(ptn_prod_bond, tgt_prod_bond);
	}

	IDPairBondMap::const_iterator created_bonds_end = prodBondsToCreate.end();
	//AtomMap::const_iterator tgt_atom_mapping_end = tgtAtomMapping.end();

	for (IDPairBondMap::const_iterator it = prodBondsToCreate.begin(); it != created_bonds_end; ++it) {
		const Bond* ptn_prod_bond = it->second;
		Bond* tgt_prod_bond = getMappedTgtProdBond(ptn_prod_bond);

		if (!tgt_prod_bond)
			continue;

		editProdBondStereoDescriptor(ptn_prod_bond, tgt_prod_bond);
	}
}

void Chem::Reactor::editProdAtomStereoDescriptor(const Atom* ptn_prod_atom, Atom* tgt_prod_atom) const
{
	assert(ptn_prod_atom && tgt_prod_atom);

	std::size_t num_ptn_nbrs = ptn_prod_atom->getNumBonds();

	if (num_ptn_nbrs > 4 || num_ptn_nbrs < 3)
		return;

	std::size_t num_tgt_nbrs = tgt_prod_atom->getNumBonds();

	if (num_tgt_nbrs < 3 || num_tgt_nbrs > 4)
		return;

	const Base::Any& ptn_stereo_desc_val = getProperty(ptn_prod_atom, AtomProperty::STEREO_DESCRIPTOR);

	if (ptn_stereo_desc_val.isEmpty())
		return;

	const StereoDescriptor& ptn_stereo_desc = ptn_stereo_desc_val.getData<StereoDescriptor>();

	if (!ptn_stereo_desc.isValid(*ptn_prod_atom))
		return;

	std::size_t num_ptn_ref_atoms = ptn_stereo_desc.getNumReferenceAtoms();

	if (num_tgt_nbrs < num_ptn_ref_atoms)
		return;

	const Atom* const* ptn_ref_atoms = ptn_stereo_desc.getReferenceAtoms();
	const Atom* tgt_ref_atoms[4] = { 0 };

	for (std::size_t i = 0; i < num_ptn_ref_atoms; i++) {
		const Atom* mpd_ptn_nbr = getMappedTgtProdAtom(ptn_ref_atoms[i]);
		
		if (!mpd_ptn_nbr) 
			return;

		tgt_ref_atoms[i] = mpd_ptn_nbr;
	}

	unsigned int ptn_config = ptn_stereo_desc.getConfiguration();
		
	if (num_ptn_ref_atoms == 3)
		setStereoDescriptor(*tgt_prod_atom, StereoDescriptor(ptn_config, *tgt_ref_atoms[0], *tgt_ref_atoms[1], *tgt_ref_atoms[2]));
	else
		setStereoDescriptor(*tgt_prod_atom, StereoDescriptor(ptn_config, *tgt_ref_atoms[0], *tgt_ref_atoms[1], *tgt_ref_atoms[2], *tgt_ref_atoms[3]));
}

void Chem::Reactor::editProdBondStereoDescriptor(const Bond* ptn_prod_bond, Bond* tgt_prod_bond) const
{
	assert(ptn_prod_bond && tgt_prod_bond);

	if (getOrder(*tgt_prod_bond) != 2)
		return;

	const Base::Any& ptn_stereo_desc_val = getProperty(ptn_prod_bond, BondProperty::STEREO_DESCRIPTOR);

	if (ptn_stereo_desc_val.isEmpty())
		return;

	const StereoDescriptor& ptn_stereo_desc = ptn_stereo_desc_val.getData<StereoDescriptor>();

	if (!ptn_stereo_desc.isValid(*ptn_prod_bond))
		return;

	const Atom* const* ptn_ref_atoms = ptn_stereo_desc.getReferenceAtoms();
	const Atom* tgt_ref_atoms[4];

	for (std::size_t i = 0; i < 4; i++) {
		const Atom* mpd_ptn_nbr = getMappedTgtProdAtom(ptn_ref_atoms[i]);
		
		if (!mpd_ptn_nbr) 
			return;

		tgt_ref_atoms[i] = mpd_ptn_nbr;
	}

	unsigned int ptn_config = ptn_stereo_desc.getConfiguration();

	setStereoDescriptor(*tgt_prod_bond, StereoDescriptor(ptn_config, *tgt_ref_atoms[0], *tgt_ref_atoms[1], *tgt_ref_atoms[2], *tgt_ref_atoms[3]));
}

Chem::Atom* Chem::Reactor::getMappedTgtProdAtom(const Atom* ptn_atom) const
{
	AtomMap::const_iterator tgt_atom_mapping_end = tgtAtomMapping.end();
	AtomMap::const_iterator it = tgtAtomMapping.find(ptn_atom);

	if (it != tgt_atom_mapping_end)
		return it->second;

	return 0;
}

Chem::Bond* Chem::Reactor::getMappedTgtProdBond(const Bond* ptn_bond) const
{
	BondMap::const_iterator tgt_bond_mapping_end = tgtBondMapping.end();
	BondMap::const_iterator it = tgtBondMapping.find(ptn_bond);

	if (it != tgt_bond_mapping_end)
		return it->second;

	return 0;
}

const Base::Any& Chem::Reactor::getProperty(const Atom* atom, const Base::LookupKey& key) const
{
	const Base::Any& prop_val = atom->getProperty(key, false);

	if (!prop_val.isEmpty())
		return prop_val;

	PropertyToConstraintIDMap::const_iterator it = propertyToConstraintIDMap.find(key);

	if (it == propertyToConstraintIDMap.end())
		return NULL_PROPERTY;

	return extractConstraintValue(it->second, *getMatchConstraints(*atom));
}

const Base::Any& Chem::Reactor::getProperty(const Bond* bond, const Base::LookupKey& key) const
{
	const Base::Any& prop_val = bond->getProperty(key, false);

	if (!prop_val.isEmpty())
		return prop_val;

	PropertyToConstraintIDMap::const_iterator it = propertyToConstraintIDMap.find(key);

	if (it == propertyToConstraintIDMap.end())
		return NULL_PROPERTY;

	return extractConstraintValue(it->second, *getMatchConstraints(*bond));
}

template <typename T>
void Chem::Reactor::copyProperty(const T* ptn_prod_obj, T* tgt_prod_obj, const Base::LookupKey& key) const
{
	const Base::Any& prop_val = getProperty(ptn_prod_obj, key);

	if (prop_val.isEmpty())
		return;

	tgt_prod_obj->setProperty(key, prop_val);
}

bool Chem::Reactor::IDPairLessCmpFunc::operator()(const IDPair& pair1, const IDPair& pair2) const
{
	if (pair1.first == pair2.first)
		return (pair1.second < pair2.second);

	return (pair1.first < pair2.first);
}
