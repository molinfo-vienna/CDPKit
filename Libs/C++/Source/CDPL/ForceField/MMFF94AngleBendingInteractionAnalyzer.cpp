/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * MMFF94AngleBendingInteractionAnalyzer.cpp 
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

#include <iterator>
#include <cmath>

#include "CDPL/ForceField/MMFF94AngleBendingInteractionAnalyzer.hpp"
#include "CDPL/ForceField/AtomFunctions.hpp"
#include "CDPL/ForceField/BondFunctions.hpp"
#include "CDPL/Chem/MolecularGraph.hpp"
#include "CDPL/Chem/Atom.hpp"
#include "CDPL/Chem/Bond.hpp"
#include "CDPL/Chem/AtomFunctions.hpp"
#include "CDPL/Chem/AtomType.hpp"
#include "CDPL/Base/Exceptions.hpp"


using namespace CDPL; 


namespace
{
	
	double empRuleZParamTable[Chem::AtomType::MAX_TYPE + 1] = { 0.0 };
	double empRuleCParamTable[Chem::AtomType::MAX_TYPE + 1] = { 0.0 };

	double getEmpiricalRuleZParameter(unsigned int atomic_no)
	{
		if (atomic_no > Chem::AtomType::MAX_TYPE)
			return 0.0;

		return empRuleZParamTable[atomic_no];
	}

	double getEmpiricalRuleCParameter(unsigned int atomic_no)
	{
		if (atomic_no > Chem::AtomType::MAX_TYPE)
			return 0.0;

		return empRuleCParamTable[atomic_no];
	}

	struct Init
	{
		
		Init() {
			empRuleZParamTable[Chem::AtomType::H]  = 1.395;
			empRuleZParamTable[Chem::AtomType::C]  = 2.494;
			empRuleZParamTable[Chem::AtomType::N]  = 2.711;
			empRuleZParamTable[Chem::AtomType::O]  = 3.045;
			empRuleZParamTable[Chem::AtomType::F]  = 2.847;
			empRuleZParamTable[Chem::AtomType::Si] = 2.350;
			empRuleZParamTable[Chem::AtomType::P]  = 2.350;
			empRuleZParamTable[Chem::AtomType::S]  = 2.980;
			empRuleZParamTable[Chem::AtomType::Cl] = 2.909;
			empRuleZParamTable[Chem::AtomType::Br] = 3.017;
			empRuleZParamTable[Chem::AtomType::I]  = 3.086;

			empRuleCParamTable[Chem::AtomType::B]  = 0.704;
			empRuleCParamTable[Chem::AtomType::C]  = 1.016;
			empRuleCParamTable[Chem::AtomType::N]  = 1.113;
			empRuleCParamTable[Chem::AtomType::O]  = 1.337;
			empRuleCParamTable[Chem::AtomType::Si] = 0.811;
			empRuleCParamTable[Chem::AtomType::P]  = 1.068;
			empRuleCParamTable[Chem::AtomType::S]  = 1.249;
			empRuleCParamTable[Chem::AtomType::Cl] = 1.078;
			empRuleCParamTable[Chem::AtomType::As] = 0.825;
		}

	} init;
}


ForceField::MMFF94AngleBendingInteractionAnalyzer::MMFF94AngleBendingInteractionAnalyzer(const Chem::MolecularGraph& molgraph, 
																						 MMFF94AngleBendingInteractionList& iactions):
	filterFunc(), atomTypeFunc(&getMMFF94NumericType), bondTypeIdxFunc(&getMMFF94TypeIndex), paramTable(MMFF94AngleBendingParameterTable::get()),
	typePropTable(MMFF94AtomTypePropertyTable::get()), paramTypeMap(MMFF94PrimaryToParameterAtomTypeMap::get())
{
    analyze(molgraph, iactions);
}

ForceField::MMFF94AngleBendingInteractionAnalyzer::MMFF94AngleBendingInteractionAnalyzer():
	filterFunc(), atomTypeFunc(&getMMFF94NumericType), bondTypeIdxFunc(&getMMFF94TypeIndex), paramTable(MMFF94AngleBendingParameterTable::get()),
	typePropTable(MMFF94AtomTypePropertyTable::get()), paramTypeMap(MMFF94PrimaryToParameterAtomTypeMap::get()) 
{}

void ForceField::MMFF94AngleBendingInteractionAnalyzer::setFilterFunction(const InteractionFilterFunction3& func)
{
	filterFunc = func;
} 

void ForceField::MMFF94AngleBendingInteractionAnalyzer::setAtomTypeFunction(const MMFF94NumericAtomTypeFunction& func)
{
	atomTypeFunc = func;

	bsAnalyzer.setAtomTypeFunction(func);
}  

void ForceField::MMFF94AngleBendingInteractionAnalyzer::setBondTypeIndexFunction(const MMFF94BondTypeIndexFunction& func)
{
	bondTypeIdxFunc = func;

	bsAnalyzer.setBondTypeIndexFunction(func);
}  

void ForceField::MMFF94AngleBendingInteractionAnalyzer::setAromaticRingSetFunction(const MMFF94AromaticRingSetFunction& func)
{
	bsAnalyzer.setAromaticRingSetFunction(func);
}

void ForceField::MMFF94AngleBendingInteractionAnalyzer::setBondStretchingParameterTable(const MMFF94BondStretchingParameterTable::SharedPointer& table)
{
	bsAnalyzer.setBondStretchingParameterTable(table);
}

void ForceField::MMFF94AngleBendingInteractionAnalyzer::setBondStretchingRuleParameterTable(const MMFF94BondStretchingRuleParameterTable::SharedPointer& table)
{
	bsAnalyzer.setBondStretchingRuleParameterTable(table);
}

void ForceField::MMFF94AngleBendingInteractionAnalyzer::setAtomTypePropertyTable(const MMFF94AtomTypePropertyTable::SharedPointer& table)
{
	typePropTable = table;

	bsAnalyzer.setAtomTypePropertyTable(table);
}

void ForceField::MMFF94AngleBendingInteractionAnalyzer::setAngleBendingParameterTable(const MMFF94AngleBendingParameterTable::SharedPointer& table)
{
	paramTable = table;
}

void ForceField::MMFF94AngleBendingInteractionAnalyzer::setParameterAtomTypeMap(const MMFF94PrimaryToParameterAtomTypeMap::SharedPointer& map)
{
	paramTypeMap = map;
}

void ForceField::MMFF94AngleBendingInteractionAnalyzer::analyze(const Chem::MolecularGraph& molgraph, 
																MMFF94AngleBendingInteractionList& iactions)
{
	using namespace Chem;

	for (std::size_t i = 0, num_atoms = molgraph.getNumAtoms(); i < num_atoms; i++) {
		const Atom& ctr_atom = molgraph.getAtom(i);

		nbrAtoms.clear();
		nbrBonds.clear();

		std::size_t num_nbrs = getConnectedAtomsAndBonds(ctr_atom, molgraph, std::back_inserter(nbrAtoms), std::back_inserter(nbrBonds));

		for (std::size_t j = 0; j < num_nbrs; j++) {
			const Atom& term_atom1 = *nbrAtoms[j];
			const Bond& term_atom1_bnd = *nbrBonds[j];
			std::size_t term_atom1_idx = molgraph.getAtomIndex(term_atom1);

			for (std::size_t k = j + 1; k < num_nbrs; k++) {
				const Atom& term_atom2 = *nbrAtoms[k];

				if (filterFunc && !filterFunc(term_atom1, ctr_atom, term_atom2))
					continue;

				double force_const = 0.0;
				double ref_angle = 0.0;
				unsigned int angle_type_idx = 0;
				bool linear = false;

				getParameters(molgraph, term_atom1, ctr_atom, term_atom2, term_atom1_bnd, *nbrBonds[k], 
							  angle_type_idx, linear, force_const, ref_angle);

				iactions.addElement(MMFF94AngleBendingInteraction(term_atom1_idx, i, molgraph.getAtomIndex(term_atom2), 
																  angle_type_idx, linear, force_const, ref_angle));
			}
		}
	}
}

void ForceField::MMFF94AngleBendingInteractionAnalyzer::getParameters(const Chem::MolecularGraph& molgraph, const Chem::Atom& term_atom1, const Chem::Atom& ctr_atom, 
																	  const Chem::Atom& term_atom2, const Chem::Bond& term_atom1_bnd, const Chem::Bond& term_atom2_bnd,
																	  unsigned int& angle_type_idx, bool& linear, double& force_const, double& ref_angle) const
{
	typedef MMFF94AngleBendingParameterTable::Entry ParamEntry;
	typedef MMFF94AtomTypePropertyTable::Entry AtomTypePropEntry;

	unsigned int term_atom1_type = atomTypeFunc(term_atom1);
	unsigned int ctr_atom_type = atomTypeFunc(ctr_atom);
	unsigned int term_atom2_type = atomTypeFunc(term_atom2);
	std::size_t r_size = getSizeOfContaining3Or4Ring(molgraph, term_atom1, ctr_atom, term_atom2);

	angle_type_idx = getAngleTypeIndex(term_atom1_bnd, term_atom2_bnd, r_size);

	const AtomTypePropEntry& ctr_prop_entry = typePropTable->getEntry(ctr_atom_type);
	
	if (!ctr_prop_entry)
		throw Base::ItemNotFound("MMFF94AngleBendingInteractionAnalyzer: could not find MMFF94 atom type properties for atom #" + 
								 boost::lexical_cast<std::string>(molgraph.getAtomIndex(ctr_atom)));

	linear = ctr_prop_entry.formsLinearBondAngle();		  

	const unsigned int* term_atom1_param_types = paramTypeMap->getEntry(term_atom1_type).getParameterTypes();

	if (!term_atom1_param_types)
		throw Base::ItemNotFound("MMFF94AngleBendingInteractionAnalyzer: could not find MMFF94 parameter atom type equivalence list for atom #" + 
								 boost::lexical_cast<std::string>(molgraph.getAtomIndex(term_atom1)));

	const unsigned int* term_atom2_param_types = paramTypeMap->getEntry(term_atom2_type).getParameterTypes();

	if (!term_atom2_param_types)
		throw Base::ItemNotFound("MMFF94AngleBendingInteractionAnalyzer: could not find MMFF94 parameter atom type equivalence list for atom #" + 
								 boost::lexical_cast<std::string>(molgraph.getAtomIndex(term_atom2)));

	for (std::size_t i = 0; i < MMFF94PrimaryToParameterAtomTypeMap::Entry::NUM_TYPES - 1; i++) {
		const ParamEntry& param_entry = paramTable->getEntry(angle_type_idx, term_atom1_param_types[i], ctr_atom_type, term_atom2_param_types[i]);

		if (!param_entry)
			continue;

		force_const = param_entry.getForceConstant();
		ref_angle = param_entry.getReferenceAngle();
		return;
	}

	const ParamEntry& param_entry = paramTable->getEntry(angle_type_idx, term_atom1_param_types[MMFF94PrimaryToParameterAtomTypeMap::Entry::NUM_TYPES - 1], 
														 ctr_atom_type, term_atom2_param_types[MMFF94PrimaryToParameterAtomTypeMap::Entry::NUM_TYPES - 1]);

	if (!param_entry) {
		// Empirical rule for finding a suitable ref. bond angle

		ref_angle = 120.0;

		if (r_size == 3)
			ref_angle = 60.0;

		else if (r_size == 4)
			ref_angle = 90.0;

		else {
			switch (ctr_prop_entry.getNumNeighbors()) {

				case 4:
					ref_angle = 109.45;
					break;

				case 3: {
					std::size_t valence = ctr_prop_entry.getValence();
					unsigned int mltb = ctr_prop_entry.getMultiBondDesignator();

					if (valence == 3 && mltb == 0) {
						if (ctr_prop_entry.getAtomicNumber() == 7)
							ref_angle = 107.0;
						else
							ref_angle = 92.0;
					}

					break;
				}

				case 2:
					if (linear)
						ref_angle = 180.0;

					else {
						if (ctr_prop_entry.getAtomicNumber() == 8)
							ref_angle = 105.0;
						else if (ctr_prop_entry.getAtomicNumber() > 10)
							ref_angle = 95.0;
					}
				
				default:
					break;
			}
		}

    } else
		ref_angle = param_entry.getReferenceAngle();

	// Empirical rule for calculating a force constant

    double beta = 1.75;

    if (r_size == 3)
		beta *= 0.05;
    
    else if (r_size == 4)
		beta *= 0.85;
    
	const AtomTypePropEntry& term1_prop_entry = typePropTable->getEntry(term_atom1_type);
	
	if (!term1_prop_entry)
		throw Base::ItemNotFound("MMFF94AngleBendingInteractionAnalyzer: could not find MMFF94 atom type properties for atom #" + 
								 boost::lexical_cast<std::string>(molgraph.getAtomIndex(term_atom1)));

	const AtomTypePropEntry& term2_prop_entry = typePropTable->getEntry(term_atom2_type);
	
	if (!term2_prop_entry)
		throw Base::ItemNotFound("MMFF94AngleBendingInteractionAnalyzer: could not find MMFF94 atom type properties for atom #" + 
								 boost::lexical_cast<std::string>(molgraph.getAtomIndex(term_atom2)));

    double zI = getEmpiricalRuleZParameter(term1_prop_entry.getAtomicNumber());
    double zK = getEmpiricalRuleZParameter(term2_prop_entry.getAtomicNumber());
    double cJ = getEmpiricalRuleCParameter(ctr_prop_entry.getAtomicNumber());

    double r0IJ = 0.0;
    double r0JK = 0.0;
	unsigned int tmp = 0;

	bsAnalyzer.getParameters(molgraph, term_atom1_bnd, tmp, force_const, r0IJ);
	bsAnalyzer.getParameters(molgraph, term_atom2_bnd, tmp, force_const, r0JK);

    double d = (r0IJ - r0JK) * (r0IJ - r0JK) / ((r0IJ + r0JK) * (r0IJ + r0JK));
	double ref_ang_rad = M_PI * ref_angle / 180.0;

	force_const = beta * zI * cJ * zK / ((r0IJ + r0JK) * ref_ang_rad * ref_ang_rad) * std::exp(-2.0 * d);
}

std::size_t ForceField::MMFF94AngleBendingInteractionAnalyzer::getSizeOfContaining3Or4Ring(const Chem::MolecularGraph& molgraph, const Chem::Atom& term_atom1, 
																						   const Chem::Atom& ctr_atom, const Chem::Atom& term_atom2) const
{
	using namespace Chem;

    if (!getRingFlag(ctr_atom))
		return 0;

    const Bond* bond = term_atom1.findBondToAtom(term_atom2);

	if (bond && molgraph.containsBond(*bond))
		return 3;

	Atom::ConstBondIterator b_it = term_atom1.getBondsBegin();

	for (Atom::ConstAtomIterator a_it = term_atom1.getAtomsBegin(), a_end = term_atom1.getAtomsEnd(); a_it != a_end; ++a_it, ++b_it) {
		const Atom& nbr_atom = *a_it;

		if (&nbr_atom == &ctr_atom)
			continue;

		if (!molgraph.containsAtom(nbr_atom) || !molgraph.containsBond(*b_it))
			continue;

		bond = nbr_atom.findBondToAtom(term_atom2);

		if (bond && molgraph.containsBond(*bond))
			return 4;
	}

    return 0;
}

unsigned int ForceField::MMFF94AngleBendingInteractionAnalyzer::getAngleTypeIndex(const Chem::Bond& bond1, const Chem::Bond& bond2, std::size_t r_size) const
{
    unsigned int bond_type_idx1 = bondTypeIdxFunc(bond1);
    unsigned int bond_type_idx2 = bondTypeIdxFunc(bond2);
    unsigned int bond_type_idx_sum = bond_type_idx1 + bond_type_idx2;

    switch (r_size) {

		case 3:
			switch (bond_type_idx_sum) {

				case 2:
					return 6;

				case 1:
					return 5;

				default:
					return 3;
			}

		case 4:
			switch (bond_type_idx_sum) {

				case 2:
					return 8;

				case 1:
					return 7;

				default:
					return 4;
			}

		default:
			switch (bond_type_idx_sum) {

				case 2:
					return 2;

				case 1:
					return 1;

				default:
					return 0;
			}
    }
}
