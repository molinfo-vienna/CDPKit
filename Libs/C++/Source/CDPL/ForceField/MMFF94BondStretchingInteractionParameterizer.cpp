/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * MMFF94BondStretchingInteractionParameterizer.cpp 
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

#include <string>
#include <cstddef>
#include <cmath>

#include <boost/lexical_cast.hpp>

#include "CDPL/ForceField/MMFF94BondStretchingInteractionParameterizer.hpp"
#include "CDPL/ForceField/MolecularGraphFunctions.hpp"
#include "CDPL/ForceField/AtomFunctions.hpp"
#include "CDPL/ForceField/BondFunctions.hpp"
#include "CDPL/ForceField/Exceptions.hpp"
#include "CDPL/Chem/MolecularGraph.hpp"
#include "CDPL/Chem/Bond.hpp"
#include "CDPL/Chem/BondFunctions.hpp"
#include "CDPL/Chem/UtilityFunctions.hpp"
#include "CDPL/Chem/AtomType.hpp"


using namespace CDPL; 


namespace
{

	double covRadiusTable[Chem::AtomType::MAX_TYPE + 1];
	double elnegTable[Chem::AtomType::MAX_TYPE + 1]     = { 2.50 };

	double getCovalentRadius(unsigned int atomic_no)
	{
		if (atomic_no > Chem::AtomType::MAX_TYPE)
			return covRadiusTable[Chem::AtomType::C];

		return covRadiusTable[atomic_no];
	}

	double getElectronegativity(unsigned int atomic_no)
	{
		if (atomic_no > Chem::AtomType::MAX_TYPE)
			return elnegTable[Chem::AtomType::C];

		return elnegTable[atomic_no];
	}

	struct Init
	{

		Init() {
			// Definition of covalent radii as used in MMFF94

			for (std::size_t i = 0; i < Chem::AtomType::MAX_TYPE + 1; i++)
				covRadiusTable[i] = 0.77;
	
			covRadiusTable[Chem::AtomType::H]  = 0.33;
			covRadiusTable[Chem::AtomType::Li] = 1.34;
			covRadiusTable[Chem::AtomType::Be] = 0.90;
			covRadiusTable[Chem::AtomType::B]  = 0.81;
			//covRadiusTable[Chem::AtomType::C]  = 0.77;
			covRadiusTable[Chem::AtomType::N]  = 0.7287;
			covRadiusTable[Chem::AtomType::O]  = 0.72;
			covRadiusTable[Chem::AtomType::F]  = 0.7385;
			covRadiusTable[Chem::AtomType::Na] = 1.54;
			covRadiusTable[Chem::AtomType::Mg] = 1.30;
			covRadiusTable[Chem::AtomType::Al] = 1.22;
			covRadiusTable[Chem::AtomType::Si] = 1.15;
			covRadiusTable[Chem::AtomType::P]  = 1.091;
			covRadiusTable[Chem::AtomType::S]  = 1.03;
			covRadiusTable[Chem::AtomType::Cl] = 1.01;
			covRadiusTable[Chem::AtomType::K]  = 1.96;
			covRadiusTable[Chem::AtomType::Ca] = 1.74;
			covRadiusTable[Chem::AtomType::Sc] = 1.44;
			covRadiusTable[Chem::AtomType::Ti] = 1.36;
			covRadiusTable[Chem::AtomType::Cu] = 1.38;
			covRadiusTable[Chem::AtomType::Zn] = 1.31;
			covRadiusTable[Chem::AtomType::Ga] = 1.19;
			covRadiusTable[Chem::AtomType::Ge] = 1.20;
			covRadiusTable[Chem::AtomType::As] = 1.20;
			covRadiusTable[Chem::AtomType::Se] = 1.16;
			covRadiusTable[Chem::AtomType::Br] = 1.15;
			covRadiusTable[Chem::AtomType::Rb] = 2.11;
			covRadiusTable[Chem::AtomType::Sr] = 1.92;
			covRadiusTable[Chem::AtomType::Y]  = 1.62;
			covRadiusTable[Chem::AtomType::Zr] = 1.48;
			covRadiusTable[Chem::AtomType::Ag] = 1.53;
			covRadiusTable[Chem::AtomType::Cd] = 1.48;
			covRadiusTable[Chem::AtomType::In] = 1.46;
			covRadiusTable[Chem::AtomType::Sn] = 1.40;
			covRadiusTable[Chem::AtomType::Sb] = 1.41;
			covRadiusTable[Chem::AtomType::Te] = 1.35;
			covRadiusTable[Chem::AtomType::I]  = 1.33;

			// Definition of Allred Rochow electronegativities as used in MMFF94

			for (std::size_t i = 0; i < Chem::AtomType::MAX_TYPE + 1; i++)
				elnegTable[i] = 2.50;

			elnegTable[Chem::AtomType::H]  = 2.20;
			elnegTable[Chem::AtomType::Li] = 0.97;
			elnegTable[Chem::AtomType::Be] = 1.47;
			elnegTable[Chem::AtomType::B]  = 2.01;
			//elnegTable[Chem::AtomType::C]  = 2.50;
			elnegTable[Chem::AtomType::N]  = 3.07;
			elnegTable[Chem::AtomType::O]  = 3.50;
			elnegTable[Chem::AtomType::F]  = 4.10;
			elnegTable[Chem::AtomType::Na] = 1.01;
			elnegTable[Chem::AtomType::Mg] = 1.23;
			elnegTable[Chem::AtomType::Al] = 1.47;
			elnegTable[Chem::AtomType::Si] = 1.74;
			elnegTable[Chem::AtomType::P]  = 2.06;
			elnegTable[Chem::AtomType::S]  = 2.44;
			elnegTable[Chem::AtomType::Cl] = 2.83;
			elnegTable[Chem::AtomType::K]  = 0.91;
			elnegTable[Chem::AtomType::Ca] = 1.04;
			elnegTable[Chem::AtomType::Sc] = 1.30;
			elnegTable[Chem::AtomType::Ti] = 1.50;
			elnegTable[Chem::AtomType::V]  = 1.60;
			elnegTable[Chem::AtomType::Cr] = 1.60;
			elnegTable[Chem::AtomType::Mn] = 1.50;
			elnegTable[Chem::AtomType::Fe] = 1.80;
			elnegTable[Chem::AtomType::Co] = 1.80;
			elnegTable[Chem::AtomType::Ni] = 1.80;
			elnegTable[Chem::AtomType::Cu] = 1.90;
			elnegTable[Chem::AtomType::Zn] = 1.60;
			elnegTable[Chem::AtomType::Ga] = 1.82;
			elnegTable[Chem::AtomType::Ge] = 2.02;
			elnegTable[Chem::AtomType::As] = 2.20;
			elnegTable[Chem::AtomType::Se] = 2.48;
			elnegTable[Chem::AtomType::Br] = 2.74;
			elnegTable[Chem::AtomType::Rb] = 0.89;
			elnegTable[Chem::AtomType::Sr] = 0.99;
			elnegTable[Chem::AtomType::Y]  = 1.30;
			elnegTable[Chem::AtomType::Zr] = 1.40;
			elnegTable[Chem::AtomType::Nb] = 1.60;
			elnegTable[Chem::AtomType::Mo] = 1.80;
			elnegTable[Chem::AtomType::Tc] = 1.90;
			elnegTable[Chem::AtomType::Ru] = 2.20;
			elnegTable[Chem::AtomType::Rh] = 2.20;
			elnegTable[Chem::AtomType::Pd] = 2.20;
			elnegTable[Chem::AtomType::Ag] = 1.90;
			elnegTable[Chem::AtomType::Cd] = 1.70;
			elnegTable[Chem::AtomType::In] = 1.49;
			elnegTable[Chem::AtomType::Sn] = 1.72;
			elnegTable[Chem::AtomType::Sb] = 1.82;
			elnegTable[Chem::AtomType::Te] = 2.01;
			elnegTable[Chem::AtomType::I]  = 2.21;
		}

	} init;

	const unsigned int FALLBACK_ATOM_TYPE = 1;
}


ForceField::MMFF94BondStretchingInteractionParameterizer::MMFF94BondStretchingInteractionParameterizer(const Chem::MolecularGraph& molgraph, 
																									   MMFF94BondStretchingInteractionData& ia_data,
																									   bool strict):
	filterFunc(), atomTypeFunc(&getMMFF94NumericType), bondTypeIdxFunc(&getMMFF94TypeIndex), aromRingSetFunc(&getMMFF94AromaticRings),
	paramTable(MMFF94BondStretchingParameterTable::get()), ruleParamTable(MMFF94BondStretchingRuleParameterTable::get()),
	typePropTable(MMFF94AtomTypePropertyTable::get())
{
    parameterize(molgraph, ia_data, strict);
}

ForceField::MMFF94BondStretchingInteractionParameterizer::MMFF94BondStretchingInteractionParameterizer():
	filterFunc(), atomTypeFunc(&getMMFF94NumericType), bondTypeIdxFunc(&getMMFF94TypeIndex), aromRingSetFunc(&getMMFF94AromaticRings),
	paramTable(MMFF94BondStretchingParameterTable::get()), ruleParamTable(MMFF94BondStretchingRuleParameterTable::get()),
	typePropTable(MMFF94AtomTypePropertyTable::get())
{}

void ForceField::MMFF94BondStretchingInteractionParameterizer::setFilterFunction(const InteractionFilterFunction2& func)
{
	filterFunc = func;
} 

void ForceField::MMFF94BondStretchingInteractionParameterizer::setAtomTypeFunction(const MMFF94NumericAtomTypeFunction& func)
{
	atomTypeFunc = func;
}  

void ForceField::MMFF94BondStretchingInteractionParameterizer::setBondTypeIndexFunction(const MMFF94BondTypeIndexFunction& func)
{
	bondTypeIdxFunc = func;
}  

void ForceField::MMFF94BondStretchingInteractionParameterizer::setAromaticRingSetFunction(const MMFF94RingSetFunction& func)
{
	aromRingSetFunc = func;
}

void ForceField::MMFF94BondStretchingInteractionParameterizer::setBondStretchingParameterTable(const MMFF94BondStretchingParameterTable::SharedPointer& table)
{
	paramTable = table;
}

void ForceField::MMFF94BondStretchingInteractionParameterizer::setBondStretchingRuleParameterTable(const MMFF94BondStretchingRuleParameterTable::SharedPointer& table)
{
	ruleParamTable = table;
}

void ForceField::MMFF94BondStretchingInteractionParameterizer::setAtomTypePropertyTable(const MMFF94AtomTypePropertyTable::SharedPointer& table)
{
	typePropTable = table;
}

void ForceField::MMFF94BondStretchingInteractionParameterizer::parameterize(const Chem::MolecularGraph& molgraph, 
																			MMFF94BondStretchingInteractionData& ia_data, bool strict)
{
	using namespace Chem;

	ia_data.clear();

	for (MolecularGraph::ConstBondIterator it = molgraph.getBondsBegin(), end = molgraph.getBondsEnd(); it != end; ++it) {
		const Bond& bond = *it;
		const Atom& atom1 = bond.getBegin();

		if (!molgraph.containsAtom(atom1))
			continue;

		const Atom& atom2 = bond.getEnd();

		if (!molgraph.containsAtom(atom2))
			continue;

		if (filterFunc && !filterFunc(atom1, atom2))
			continue;
	
		unsigned int bond_type_idx = 0;
		double ref_length = 0.0;
		double force_const = 0.0;

		try {
			getParameters(molgraph, bond, bond_type_idx, force_const, ref_length, strict);

		} catch (const ParameterizationFailed& e) {
			if (strict)
				throw e;

			getParameters(molgraph, bond, bond_type_idx, FALLBACK_ATOM_TYPE, FALLBACK_ATOM_TYPE, force_const, ref_length);
		}

		ia_data.addElement(MMFF94BondStretchingInteraction(molgraph.getAtomIndex(atom1), molgraph.getAtomIndex(atom2), 
														   bond_type_idx, force_const, ref_length));
	}
}

void ForceField::MMFF94BondStretchingInteractionParameterizer::getParameters(const Chem::MolecularGraph& molgraph, const Chem::Bond& bond, 
																			 unsigned int& bond_type_idx, double& force_const, double& ref_length, 
																			 bool strict) const
{
	unsigned int atom1_type = atomTypeFunc(bond.getBegin());
	unsigned int atom2_type = atomTypeFunc(bond.getEnd());

	if (!strict) {
		if (atom1_type == 0)
			atom1_type = FALLBACK_ATOM_TYPE;

		if (atom2_type == 0)
			atom2_type = FALLBACK_ATOM_TYPE;
	}

	bond_type_idx = bondTypeIdxFunc(bond);

	getParameters(molgraph, bond, bond_type_idx, atom1_type, atom2_type, force_const, ref_length);
}

void ForceField::MMFF94BondStretchingInteractionParameterizer::getParameters(const Chem::MolecularGraph& molgraph, const Chem::Bond& bond, 
																			 unsigned int bond_type_idx, unsigned int atom1_type, unsigned int atom2_type, 
																			 double& force_const, double& ref_length) const
{
	typedef MMFF94BondStretchingParameterTable::Entry ParamEntry;
	typedef MMFF94BondStretchingRuleParameterTable::Entry RuleParamEntry;

	const ParamEntry& param_entry = paramTable->getEntry(bond_type_idx, atom1_type, atom2_type);

	if (param_entry) {
		force_const = param_entry.getForceConstant();
		ref_length = param_entry.getReferenceLength();
		return;
	}

	// Empirical rule fallback

	const AtomTypePropEntry& type1_prop_entry = typePropTable->getEntry(atom1_type);
	
	if (!type1_prop_entry)
		throw ParameterizationFailed("MMFF94BondStretchingInteractionParameterizer: could not find MMFF94 atom type properties for atom #" + 
									 boost::lexical_cast<std::string>(molgraph.getAtomIndex(bond.getBegin())));

	const AtomTypePropEntry& type2_prop_entry = typePropTable->getEntry(atom2_type);
	
	if (!type2_prop_entry)
		throw ParameterizationFailed("MMFF94BondStretchingInteractionParameterizer: could not find MMFF94 atom type properties for atom #" + 
									 boost::lexical_cast<std::string>(molgraph.getAtomIndex(bond.getEnd())));

	const RuleParamEntry& rule_param_entry = ruleParamTable->getEntry(type1_prop_entry.getAtomicNumber(), type2_prop_entry.getAtomicNumber());

	if (!rule_param_entry)
		throw ParameterizationFailed("MMMFF94BondStretchingInteractionParameterizer: could not find MMFF94 bond stretching rule parameters for interaction #" + 
									 boost::lexical_cast<std::string>(molgraph.getAtomIndex(bond.getBegin())) + "-#" + 
									 boost::lexical_cast<std::string>(molgraph.getAtomIndex(bond.getEnd())));

	ref_length = calcReferenceBondLength(molgraph, bond, type1_prop_entry, type2_prop_entry);	
	force_const = rule_param_entry.getForceConstant() * std::pow(rule_param_entry.getReferenceLength() / ref_length, 6.0);
}

double ForceField::MMFF94BondStretchingInteractionParameterizer::calcReferenceBondLength(const Chem::MolecularGraph& molgraph, const Chem::Bond& bond, 
																						 const AtomTypePropEntry& type1_prop_entry, const AtomTypePropEntry& type2_prop_entry) const
{
	using namespace Chem;

	unsigned int mltb_desig1 = type1_prop_entry.getMultiBondDesignator();
    unsigned int mltb_desig2 = type2_prop_entry.getMultiBondDesignator();
	std::size_t bond_order_idx = getOrder(bond);

    if (mltb_desig1 == 1 && mltb_desig2 == 1)
		bond_order_idx = 4;
	
	else if ((mltb_desig1 == 1 && mltb_desig2 == 2) || (mltb_desig1 == 2 && mltb_desig2 == 1))
		bond_order_idx = 5;
	
	else if (containsFragmentWithBond(*aromRingSetFunc(molgraph), bond)) {
		bool pilp_flag1 = type1_prop_entry.hasPiLonePair();
		bool pilp_flag2 = type2_prop_entry.hasPiLonePair();

		if (!pilp_flag1 && !pilp_flag2)
			bond_order_idx = 4;
		else
			bond_order_idx = 5;
	}

    unsigned int atomic_no1 = type1_prop_entry.getAtomicNumber();
    unsigned int atomic_no2 = type2_prop_entry.getAtomicNumber();
    double cov_rad1 = getCovalentRadius(atomic_no1);
    double cov_rad2 = getCovalentRadius(atomic_no2);

    switch (bond_order_idx) {

		case 1:
			switch (mltb_desig1 * 10 + mltb_desig2) {

				case 11:
				case 12:
				case 21:
				case 22:
					cov_rad1 -= 0.03;
					cov_rad2 -= 0.03;
					break;

				case 33:
					cov_rad1 -= 0.08;
					cov_rad2 -= 0.08;

				default:
					break;
			}

			break;

		case 2:
			cov_rad1 -= 0.1;
			cov_rad2 -= 0.1;
			break;

		case 3:
			cov_rad1 -= 0.17;
			cov_rad2 -= 0.17;
			break;

		case 4:
			cov_rad1 -= 0.075;
			cov_rad2 -= 0.075;
			break;

		case 5:
			cov_rad1 -= 0.04;
			cov_rad2 -= 0.04;

		default:
			break;
    }

    double elneg1 = getElectronegativity(atomic_no1);
    double elneg2 = getElectronegativity(atomic_no2);
    double c = 0.085;

    if (atomic_no1 == AtomType::H || atomic_no2 == AtomType::H)
		c = 0.05;

    double r0IJ = cov_rad1 + cov_rad2 - c * std::pow(std::abs(elneg1 - elneg2), 1.4); // - 0.008; // test suite values seem not to have this value subtracted!

    return r0IJ;
}
