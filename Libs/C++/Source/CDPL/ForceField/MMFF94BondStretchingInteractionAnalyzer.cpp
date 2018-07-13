/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * MMFF94BondStretchingInteractionAnalyzer.cpp 
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

#include "CDPL/ForceField/MMFF94BondStretchingInteractionAnalyzer.hpp"
#include "CDPL/ForceField/MolecularGraphFunctions.hpp"
#include "CDPL/ForceField/AtomFunctions.hpp"
#include "CDPL/ForceField/BondFunctions.hpp"
#include "CDPL/Chem/MolecularGraph.hpp"
#include "CDPL/Chem/Bond.hpp"
#include "CDPL/Chem/BondFunctions.hpp"
#include "CDPL/Chem/UtilityFunctions.hpp"
#include "CDPL/Chem/AtomType.hpp"
#include "CDPL/Base/Exceptions.hpp"


using namespace CDPL; 


namespace
{

	struct CovalentRadiusEntry
	{

		unsigned int atomicNo;
		double       radius;
	};

	struct ElectronegativityEntry
	{

		unsigned int atomicNo;
		double       enegativity;
	};
	
	// Definition of covalent radii as used in MMFF94

	CovalentRadiusEntry covRadiusList[] = {
        { Chem::AtomType::H, 0.33 },
		{ Chem::AtomType::Li, 1.34 },
		{ Chem::AtomType::Be, 0.90 },
		{ Chem::AtomType::B, 0.81 },
		{ Chem::AtomType::C, 0.77 },
		{ Chem::AtomType::N, 0.7287 },
		{ Chem::AtomType::O, 0.72 },
		{ Chem::AtomType::F, 0.7385 },
		{ Chem::AtomType::Na, 1.54 },
		{ Chem::AtomType::Mg, 1.30 },
		{ Chem::AtomType::Al, 1.22 },
		{ Chem::AtomType::Si, 1.15 },
		{ Chem::AtomType::P, 1.091 },
		{ Chem::AtomType::S, 1.03 },
		{ Chem::AtomType::Cl, 1.01 },
		{ Chem::AtomType::K, 1.96 },
		{ Chem::AtomType::Ca, 1.74 },
		{ Chem::AtomType::Sc, 1.44 },
		{ Chem::AtomType::Ti, 1.36 },
		{ Chem::AtomType::Cu, 1.38 },
		{ Chem::AtomType::Zn, 1.31 },
		{ Chem::AtomType::Ga, 1.19 },
		{ Chem::AtomType::Ge, 1.20 },
		{ Chem::AtomType::As, 1.20 },
		{ Chem::AtomType::Se, 1.16 },
		{ Chem::AtomType::Br, 1.15 },
		{ Chem::AtomType::Rb, 2.11 },
		{ Chem::AtomType::Sr, 1.92 },
		{ Chem::AtomType::Y, 1.62 },
		{ Chem::AtomType::Zr, 1.48 },
		{ Chem::AtomType::Ag, 1.53 },
		{ Chem::AtomType::Cd, 1.48 },
		{ Chem::AtomType::In, 1.46 },
		{ Chem::AtomType::Sn, 1.40 },
		{ Chem::AtomType::Sb, 1.41 },
		{ Chem::AtomType::Te, 1.35 },
		{ Chem::AtomType::I, 1.33 }
	};

    // Definition of Allred Rochow electronegativities as used in MMFF94

	ElectronegativityEntry enegativityList[] = {
        { Chem::AtomType::H, 2.20 },
		{ Chem::AtomType::Li, 0.97 },
		{ Chem::AtomType::Be, 1.47 },
		{ Chem::AtomType::B, 2.01 },
		{ Chem::AtomType::C, 2.50 },
		{ Chem::AtomType::N, 3.07 },
		{ Chem::AtomType::O, 3.50 },
		{ Chem::AtomType::F, 4.10 },
		{ Chem::AtomType::Na, 1.01 },
		{ Chem::AtomType::Mg, 1.23 },
		{ Chem::AtomType::Al, 1.47 },
		{ Chem::AtomType::Si, 1.74 },
		{ Chem::AtomType::P, 2.06 },
		{ Chem::AtomType::S, 2.44 },
		{ Chem::AtomType::Cl, 2.83 },
		{ Chem::AtomType::K, 0.91 },
		{ Chem::AtomType::Ca, 1.04 },
		{ Chem::AtomType::Sc, 1.30 },
		{ Chem::AtomType::Ti, 1.50 },
		{ Chem::AtomType::V, 1.60 },
		{ Chem::AtomType::Cr, 1.60 },
		{ Chem::AtomType::Mn, 1.50 },
		{ Chem::AtomType::Fe, 1.80 },
		{ Chem::AtomType::Co, 1.80 },
		{ Chem::AtomType::Ni, 1.80 },
		{ Chem::AtomType::Cu, 1.90 },
		{ Chem::AtomType::Zn, 1.60 },
		{ Chem::AtomType::Ga, 1.82 },
		{ Chem::AtomType::Ge, 2.02 },
		{ Chem::AtomType::As, 2.20 },
		{ Chem::AtomType::Se, 2.48 },
		{ Chem::AtomType::Br, 2.74 },
		{ Chem::AtomType::Rb, 0.89 },
		{ Chem::AtomType::Sr, 0.99 },
		{ Chem::AtomType::Y, 1.30 },
		{ Chem::AtomType::Zr, 1.40 },
		{ Chem::AtomType::Nb, 1.60 },
		{ Chem::AtomType::Mo, 1.80 },
		{ Chem::AtomType::Tc, 1.90 },
		{ Chem::AtomType::Ru, 2.20 },
		{ Chem::AtomType::Rh, 2.20 },
		{ Chem::AtomType::Pd, 2.20 },
		{ Chem::AtomType::Ag, 1.90 },
		{ Chem::AtomType::Cd, 1.70 },
		{ Chem::AtomType::In, 1.49 },
		{ Chem::AtomType::Sn, 1.72 },
		{ Chem::AtomType::Sb, 1.82 },
		{ Chem::AtomType::Te, 2.01 },
		{ Chem::AtomType::I, 2.21 }
	};

	double covRadiusLookupTable[Chem::AtomType::MAX_TYPE + 1]   = { 0.0 };
	double enegativityLookupTable[Chem::AtomType::MAX_TYPE + 1] = { 0.0 };

	double getCovalentRadius(unsigned int atomic_no)
	{
		if (atomic_no > Chem::AtomType::MAX_TYPE)
			return 0.0;

		return covRadiusLookupTable[atomic_no];
	}

	double getElectronegativity(unsigned int atomic_no)
	{
		if (atomic_no > Chem::AtomType::MAX_TYPE)
			return 0.0;

		return enegativityLookupTable[atomic_no];
	}

	struct Init
	{

		Init() {
			for (std::size_t i = 0; i < sizeof(covRadiusList) / sizeof(CovalentRadiusEntry); i++)
				covRadiusLookupTable[covRadiusList[i].atomicNo] = covRadiusList[i].radius;

			for (std::size_t i = 0; i < sizeof(enegativityList) / sizeof(ElectronegativityEntry); i++)
				enegativityLookupTable[enegativityList[i].atomicNo] = enegativityList[i].enegativity;
		}

	} init;
}


ForceField::MMFF94BondStretchingInteractionAnalyzer::MMFF94BondStretchingInteractionAnalyzer(const Chem::MolecularGraph& molgraph, 
																							 MMFF94BondStretchingInteractionList& iactions):
	filterFunc(), atomTypeFunc(&getMMFF94NumericType), bondTypeIdxFunc(&getMMFF94TypeIndex), aromRingSetFunc(&getMMFF94AromaticRings),
	paramTable(MMFF94BondStretchingParameterTable::get()), ruleParamTable(MMFF94BondStretchingRuleParameterTable::get()),
	typePropTable(MMFF94AtomTypePropertyTable::get())
{
    analyze(molgraph, iactions);
}

ForceField::MMFF94BondStretchingInteractionAnalyzer::MMFF94BondStretchingInteractionAnalyzer():
	filterFunc(), atomTypeFunc(&getMMFF94NumericType), bondTypeIdxFunc(&getMMFF94TypeIndex), aromRingSetFunc(&getMMFF94AromaticRings),
	paramTable(MMFF94BondStretchingParameterTable::get()), ruleParamTable(MMFF94BondStretchingRuleParameterTable::get()),
	typePropTable(MMFF94AtomTypePropertyTable::get())
{}

void ForceField::MMFF94BondStretchingInteractionAnalyzer::setFilterFunction(const InteractionFilterFunction2& func)
{
	filterFunc = func;
} 

void ForceField::MMFF94BondStretchingInteractionAnalyzer::setAtomTypeFunction(const MMFF94NumericAtomTypeFunction& func)
{
	atomTypeFunc = func;
}  

void ForceField::MMFF94BondStretchingInteractionAnalyzer::setBondTypeIndexFunction(const MMFF94BondTypeIndexFunction& func)
{
	bondTypeIdxFunc = func;
}  

void ForceField::MMFF94BondStretchingInteractionAnalyzer::setAromaticRingSetFunction(const MMFF94AromaticRingSetFunction& func)
{
	aromRingSetFunc = func;
}

void ForceField::MMFF94BondStretchingInteractionAnalyzer::setBondStretchingParameterTable(const MMFF94BondStretchingParameterTable::SharedPointer& table)
{
	paramTable = table;
}

void ForceField::MMFF94BondStretchingInteractionAnalyzer::setBondStretchingRuleParameterTable(const MMFF94BondStretchingRuleParameterTable::SharedPointer& table)
{
	ruleParamTable = table;
}

void ForceField::MMFF94BondStretchingInteractionAnalyzer::setAtomTypePropertyTable(const MMFF94AtomTypePropertyTable::SharedPointer& table)
{
	typePropTable = table;
}

void ForceField::MMFF94BondStretchingInteractionAnalyzer::analyze(const Chem::MolecularGraph& molgraph, 
																  MMFF94BondStretchingInteractionList& iactions)
{
	using namespace Chem;

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
	
		double ref_length = 0.0;
		double force_const = 0.0;

		getParameters(molgraph, bond, force_const, ref_length);
	
		iactions.addElement(MMFF94BondStretchingInteraction(molgraph.getAtomIndex(atom1), molgraph.getAtomIndex(atom2), force_const, ref_length));
	}
}

void ForceField::MMFF94BondStretchingInteractionAnalyzer::getParameters(const Chem::MolecularGraph& molgraph, const Chem::Bond& bond, 
																		double& force_const, double& ref_length) const
{
	typedef MMFF94BondStretchingParameterTable::Entry ParamEntry;
	typedef MMFF94BondStretchingRuleParameterTable::Entry RuleParamEntry;

	unsigned int bond_type_idx = bondTypeIdxFunc(bond);
	unsigned int atom1_type = atomTypeFunc(bond.getBegin());
	unsigned int atom2_type = atomTypeFunc(bond.getEnd());

	const ParamEntry& param_entry = paramTable->getEntry(bond_type_idx, atom1_type, atom2_type);

	if (param_entry) {
		force_const = param_entry.getForceConstant();
		ref_length = param_entry.getReferenceLength();
		return;
	}

	// Empirical rule fallback

	const AtomTypePropEntry& type1_prop_entry = typePropTable->getEntry(atom1_type);
	
	if (!type1_prop_entry)
		throw Base::ItemNotFound("MMFF94BondStretchingInteractionAnalyzer: could not find MMFF94 atom type properties for atom #" + 
								 boost::lexical_cast<std::string>(molgraph.getAtomIndex(bond.getBegin())));

	const AtomTypePropEntry& type2_prop_entry = typePropTable->getEntry(atom2_type);
	
	if (!type2_prop_entry)
		throw Base::ItemNotFound("MMFF94BondStretchingInteractionAnalyzer: could not find MMFF94 atom type properties for atom #" + 
								 boost::lexical_cast<std::string>(molgraph.getAtomIndex(bond.getEnd())));

	const RuleParamEntry& rule_param_entry = ruleParamTable->getEntry(type1_prop_entry.getAtomicNumber(), type2_prop_entry.getAtomicNumber());

	if (!rule_param_entry)
		throw Base::ItemNotFound("MMMFF94BondStretchingInteractionAnalyzer: could not find MMFF94 bond stretching rule parameters for interaction #" + 
								 boost::lexical_cast<std::string>(molgraph.getAtomIndex(bond.getBegin())) + "-#" + 
								 boost::lexical_cast<std::string>(molgraph.getAtomIndex(bond.getEnd())));

	ref_length = calcReferenceBondLength(molgraph, bond, type1_prop_entry, type2_prop_entry);	
	force_const = rule_param_entry.getForceConstant() * std::pow(rule_param_entry.getReferenceLength() / ref_length, 6.0);
}

double ForceField::MMFF94BondStretchingInteractionAnalyzer::calcReferenceBondLength(const Chem::MolecularGraph& molgraph, const Chem::Bond& bond, 
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
