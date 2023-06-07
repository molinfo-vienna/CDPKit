/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * MMFF94InteractionParameterizer.cpp 
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

#include <boost/bind.hpp>

#include "CDPL/ForceField/MMFF94InteractionParameterizer.hpp"
#include "CDPL/ForceField/MMFF94InteractionData.hpp"
#include "CDPL/ForceField/AtomFunctions.hpp"
#include "CDPL/ForceField/BondFunctions.hpp"
#include "CDPL/ForceField/MolecularGraphFunctions.hpp"
#include "CDPL/ForceField/Exceptions.hpp"
#include "CDPL/Chem/MolecularGraphFunctions.hpp"


using namespace CDPL; 

	
ForceField::MMFF94InteractionParameterizer::MMFF94InteractionParameterizer(unsigned int param_set)
{
	setPropertyFunctions();
	setParameterSet(param_set);
}

ForceField::MMFF94InteractionParameterizer::MMFF94InteractionParameterizer(const MMFF94InteractionParameterizer& parameterizer):
	bondStretchingParameterizer(parameterizer.bondStretchingParameterizer),
	angleBendingParameterizer(parameterizer.angleBendingParameterizer),
	stretchBendParameterizer(parameterizer.stretchBendParameterizer),
	outOfPlaneParameterizer(parameterizer.outOfPlaneParameterizer),
	torsionParameterizer(parameterizer.torsionParameterizer),
	vanDerWaalsParameterizer(parameterizer.vanDerWaalsParameterizer),
	electrostaticParameterizer(parameterizer.electrostaticParameterizer),
	atomTyper(parameterizer.atomTyper),
	bondTyper(parameterizer.bondTyper),
	chargeCalculator(parameterizer.chargeCalculator)
{
	setPropertyFunctions();
}

void ForceField::MMFF94InteractionParameterizer::setBondStretchingFilterFunction(const InteractionFilterFunction2& func)
{
	bondStretchingParameterizer.setFilterFunction(func);
} 

void ForceField::MMFF94InteractionParameterizer::setAngleBendingFilterFunction(const InteractionFilterFunction3& func)
{
	angleBendingParameterizer.setFilterFunction(func);
} 

void ForceField::MMFF94InteractionParameterizer::setStretchBendFilterFunction(const InteractionFilterFunction3& func)
{
	stretchBendParameterizer.setFilterFunction(func);
} 

void ForceField::MMFF94InteractionParameterizer::setOutOfPlaneBendingFilterFunction(const InteractionFilterFunction4& func)
{
	outOfPlaneParameterizer.setFilterFunction(func);
} 

void ForceField::MMFF94InteractionParameterizer::setTorsionFilterFunction(const InteractionFilterFunction4& func)
{
	torsionParameterizer.setFilterFunction(func);
} 

void ForceField::MMFF94InteractionParameterizer::setElectrostaticFilterFunction(const InteractionFilterFunction2& func)
{
	electrostaticParameterizer.setFilterFunction(func);
} 

void ForceField::MMFF94InteractionParameterizer::setVanDerWaalsFilterFunction(const InteractionFilterFunction2& func)
{
	vanDerWaalsParameterizer.setFilterFunction(func);
} 

void ForceField::MMFF94InteractionParameterizer::clearFilterFunctions()
{
	bondStretchingParameterizer.setFilterFunction(InteractionFilterFunction2());
	angleBendingParameterizer.setFilterFunction(InteractionFilterFunction3());
	stretchBendParameterizer.setFilterFunction(InteractionFilterFunction3());
	outOfPlaneParameterizer.setFilterFunction(InteractionFilterFunction4());
	torsionParameterizer.setFilterFunction(InteractionFilterFunction4());
	vanDerWaalsParameterizer.setFilterFunction(InteractionFilterFunction2());
	electrostaticParameterizer.setFilterFunction(InteractionFilterFunction2());
}

void ForceField::MMFF94InteractionParameterizer::setSymbolicAtomTypePatternTable(const MMFF94SymbolicAtomTypePatternTable::SharedPointer& table)
{
	atomTyper.setSymbolicAtomTypePatternTable(table);
}

void ForceField::MMFF94InteractionParameterizer::setHeavyToHydrogenAtomTypeMap(const MMFF94HeavyToHydrogenAtomTypeMap::SharedPointer& map)
{
	atomTyper.setHeavyToHydrogenAtomTypeMap(map);
}

void ForceField::MMFF94InteractionParameterizer::setSymbolicToNumericAtomTypeMap(const MMFF94SymbolicToNumericAtomTypeMap::SharedPointer& map)
{
	atomTyper.setSymbolicToNumericAtomTypeMap(map);
}

void ForceField::MMFF94InteractionParameterizer::setAromaticAtomTypeDefinitionTable(const MMFF94AromaticAtomTypeDefinitionTable::SharedPointer& table)
{
	atomTyper.setAromaticAtomTypeDefinitionTable(table);
}

void ForceField::MMFF94InteractionParameterizer::setAtomTypePropertyTable(const MMFF94AtomTypePropertyTable::SharedPointer& table)
{
	bondStretchingParameterizer.setAtomTypePropertyTable(table);
	angleBendingParameterizer.setAtomTypePropertyTable(table);
	stretchBendParameterizer.setAtomTypePropertyTable(table);
	outOfPlaneParameterizer.setAtomTypePropertyTable(table);
	torsionParameterizer.setAtomTypePropertyTable(table);
	bondTyper.setAtomTypePropertyTable(table);
	atomTyper.setAtomTypePropertyTable(table);
	chargeCalculator.setAtomTypePropertyTable(table);
}

void ForceField::MMFF94InteractionParameterizer::setFormalAtomChargeDefinitionTable(const MMFF94FormalAtomChargeDefinitionTable::SharedPointer& table)
{
	chargeCalculator.setFormalChargeDefinitionTable(table);
}

void ForceField::MMFF94InteractionParameterizer::setBondChargeIncrementTable(const MMFF94BondChargeIncrementTable::SharedPointer& table)
{
	chargeCalculator.setBondChargeIncrementTable(table);
}

void ForceField::MMFF94InteractionParameterizer::setPartialBondChargeIncrementTable(const MMFF94PartialBondChargeIncrementTable::SharedPointer& table)
{
	chargeCalculator.setPartialBondChargeIncrementTable(table);
}

void ForceField::MMFF94InteractionParameterizer::setPrimaryToParameterAtomTypeMap(const MMFF94PrimaryToParameterAtomTypeMap::SharedPointer& map)
{
	angleBendingParameterizer.setParameterAtomTypeMap(map);
	outOfPlaneParameterizer.setParameterAtomTypeMap(map);
	torsionParameterizer.setParameterAtomTypeMap(map);
}

void ForceField::MMFF94InteractionParameterizer::setAngleBendingParameterTable(const MMFF94AngleBendingParameterTable::SharedPointer& table)
{
	angleBendingParameterizer.setAngleBendingParameterTable(table);
}

void ForceField::MMFF94InteractionParameterizer::setBondStretchingParameterTable(const MMFF94BondStretchingParameterTable::SharedPointer& table)
{
	bondStretchingParameterizer.setBondStretchingParameterTable(table);
	angleBendingParameterizer.setBondStretchingParameterTable(table);
}

void ForceField::MMFF94InteractionParameterizer::setBondStretchingRuleParameterTable(const MMFF94BondStretchingRuleParameterTable::SharedPointer& table)
{
	bondStretchingParameterizer.setBondStretchingRuleParameterTable(table);
	angleBendingParameterizer.setBondStretchingRuleParameterTable(table);
}

void ForceField::MMFF94InteractionParameterizer::setStretchBendParameterTable(const MMFF94StretchBendParameterTable::SharedPointer& table)
{
	stretchBendParameterizer.setStretchBendParameterTable(table);
}

void ForceField::MMFF94InteractionParameterizer::setDefaultStretchBendParameterTable(const MMFF94DefaultStretchBendParameterTable::SharedPointer& table)
{
	stretchBendParameterizer.setDefaultStretchBendParameterTable(table);
}

void ForceField::MMFF94InteractionParameterizer::setOutOfPlaneBendingParameterTable(const MMFF94OutOfPlaneBendingParameterTable::SharedPointer& table)
{
	outOfPlaneParameterizer.setOutOfPlaneBendingParameterTable(table);
}

void ForceField::MMFF94InteractionParameterizer::setTorsionParameterTable(const MMFF94TorsionParameterTable::SharedPointer& table)
{
	torsionParameterizer.setTorsionParameterTable(table);
}

void ForceField::MMFF94InteractionParameterizer::setVanDerWaalsParameterTable(const MMFF94VanDerWaalsParameterTable::SharedPointer& table)
{
	vanDerWaalsParameterizer.setVanDerWaalsParameterTable(table);
}

void ForceField::MMFF94InteractionParameterizer::setDielectricConstant(double de_const)
{
	electrostaticParameterizer.setDielectricConstant(de_const);
} 

void ForceField::MMFF94InteractionParameterizer::setDistanceExponent(double dist_expo)
{
	electrostaticParameterizer.setDistanceExponent(dist_expo);
} 

void ForceField::MMFF94InteractionParameterizer::setParameterSet(unsigned int param_set)
{
	outOfPlaneParameterizer.setOutOfPlaneBendingParameterTable(MMFF94OutOfPlaneBendingParameterTable::get(param_set));
	torsionParameterizer.setTorsionParameterTable(MMFF94TorsionParameterTable::get(param_set));
}

void ForceField::MMFF94InteractionParameterizer::parameterize(const Chem::MolecularGraph& molgraph, MMFF94InteractionData& ia_data,
															  unsigned int ia_types, bool strict)
{
	setup(molgraph, ia_types, strict);

	if ((ia_types & InteractionType::BOND_STRETCHING) || (ia_types & InteractionType::STRETCH_BEND))
		bondStretchingParameterizer.parameterize(molgraph, ia_data.getBondStretchingInteractions(), strict);

	if ((ia_types & InteractionType::ANGLE_BENDING) || (ia_types & InteractionType::STRETCH_BEND))
		angleBendingParameterizer.parameterize(molgraph, ia_data.getAngleBendingInteractions(), strict);

	if (ia_types & InteractionType::STRETCH_BEND)
		stretchBendParameterizer.parameterize(molgraph, ia_data.getBondStretchingInteractions(), 
											  ia_data.getAngleBendingInteractions(), ia_data.getStretchBendInteractions(), strict);

	if (!(ia_types & InteractionType::BOND_STRETCHING))
		ia_data.getBondStretchingInteractions().clear();

	if (!(ia_types & InteractionType::ANGLE_BENDING))
		ia_data.getAngleBendingInteractions().clear();

	if (ia_types & InteractionType::OUT_OF_PLANE_BENDING)
		outOfPlaneParameterizer.parameterize(molgraph, ia_data.getOutOfPlaneBendingInteractions(), strict);

	if (ia_types & InteractionType::TORSION)
		torsionParameterizer.parameterize(molgraph, ia_data.getTorsionInteractions(), strict);

	if (ia_types & InteractionType::ELECTROSTATIC)
		electrostaticParameterizer.parameterize(molgraph, ia_data.getElectrostaticInteractions(), strict);

	if (ia_types & InteractionType::VAN_DER_WAALS)
		vanDerWaalsParameterizer.parameterize(molgraph, ia_data.getVanDerWaalsInteractions(), strict);
}

ForceField::MMFF94InteractionParameterizer& ForceField::MMFF94InteractionParameterizer::operator=(const MMFF94InteractionParameterizer& parameterizer)
{
	if (this == &parameterizer)
		return *this;

	bondStretchingParameterizer = parameterizer.bondStretchingParameterizer;
	angleBendingParameterizer = parameterizer.angleBendingParameterizer;
	stretchBendParameterizer = parameterizer.stretchBendParameterizer;
	outOfPlaneParameterizer = parameterizer.outOfPlaneParameterizer;
	torsionParameterizer = parameterizer.torsionParameterizer;
	vanDerWaalsParameterizer = parameterizer.vanDerWaalsParameterizer;
	electrostaticParameterizer = parameterizer.electrostaticParameterizer;
	atomTyper = parameterizer.atomTyper;
	bondTyper = parameterizer.bondTyper;
	chargeCalculator = parameterizer.chargeCalculator;
	
	setPropertyFunctions();

	return *this;
}

void ForceField::MMFF94InteractionParameterizer::setPropertyFunctions()
{
	bondStretchingParameterizer.setAtomTypeFunction(boost::bind(&MMFF94InteractionParameterizer::getNumericAtomType, this, _1));
	bondStretchingParameterizer.setBondTypeIndexFunction(boost::bind(&MMFF94InteractionParameterizer::getBondTypeIndex, this, _1));
	bondStretchingParameterizer.setAromaticRingSetFunction(boost::bind(&MMFF94InteractionParameterizer::getAromaticRings, this, _1));

	angleBendingParameterizer.setAtomTypeFunction(boost::bind(&MMFF94InteractionParameterizer::getNumericAtomType, this, _1));
	angleBendingParameterizer.setBondTypeIndexFunction(boost::bind(&MMFF94InteractionParameterizer::getBondTypeIndex, this, _1));
	angleBendingParameterizer.setAromaticRingSetFunction(boost::bind(&MMFF94InteractionParameterizer::getAromaticRings, this, _1));

	stretchBendParameterizer.setAtomTypeFunction(boost::bind(&MMFF94InteractionParameterizer::getNumericAtomType, this, _1));

	outOfPlaneParameterizer.setAtomTypeFunction(boost::bind(&MMFF94InteractionParameterizer::getNumericAtomType, this, _1));

	torsionParameterizer.setAtomTypeFunction(boost::bind(&MMFF94InteractionParameterizer::getNumericAtomType, this, _1));
	torsionParameterizer.setBondTypeIndexFunction(boost::bind(&MMFF94InteractionParameterizer::getBondTypeIndex, this, _1));
	torsionParameterizer.setAromaticRingSetFunction(boost::bind(&MMFF94InteractionParameterizer::getAromaticRings, this, _1));

	vanDerWaalsParameterizer.setAtomTypeFunction(boost::bind(&MMFF94InteractionParameterizer::getNumericAtomType, this, _1));
	vanDerWaalsParameterizer.setTopologicalDistanceFunction(boost::bind(&MMFF94InteractionParameterizer::getTopologicalDistance, this, _1, _2, _3));

	electrostaticParameterizer.setAtomChargeFunction(boost::bind(&MMFF94InteractionParameterizer::getAtomCharge, this, _1));
	electrostaticParameterizer.setTopologicalDistanceFunction(boost::bind(&MMFF94InteractionParameterizer::getTopologicalDistance, this, _1, _2, _3));

	atomTyper.setAromaticRingSetFunction(boost::bind(&MMFF94InteractionParameterizer::getAromaticRings, this, _1));

	bondTyper.setAtomTypeFunction(boost::bind(&MMFF94InteractionParameterizer::getNumericAtomType, this, _1));
	bondTyper.setAromaticRingSetFunction(boost::bind(&MMFF94InteractionParameterizer::getAromaticRings, this, _1));

	chargeCalculator.setNumericAtomTypeFunction(boost::bind(&MMFF94InteractionParameterizer::getNumericAtomType, this, _1));
	chargeCalculator.setSymbolicAtomTypeFunction(boost::bind(&MMFF94InteractionParameterizer::getSymbolicAtomType, this, _1));
	chargeCalculator.setBondTypeIndexFunction(boost::bind(&MMFF94InteractionParameterizer::getBondTypeIndex, this, _1));
	chargeCalculator.setAromaticRingSetFunction(boost::bind(&MMFF94InteractionParameterizer::getAromaticRings, this, _1));
}

unsigned int ForceField::MMFF94InteractionParameterizer::getBondTypeIndex(const Chem::Bond& bond) const
{
	return bondTypeIndices[molGraph->getBondIndex(bond)];
}

unsigned int ForceField::MMFF94InteractionParameterizer::getNumericAtomType(const Chem::Atom& atom) const
{
	return numAtomTypes[molGraph->getAtomIndex(atom)];
}

const std::string& ForceField::MMFF94InteractionParameterizer::getSymbolicAtomType(const Chem::Atom& atom) const
{
	return symAtomTypes[molGraph->getAtomIndex(atom)];
}

double ForceField::MMFF94InteractionParameterizer::getAtomCharge(const Chem::Atom& atom) const
{
	return atomCharges[molGraph->getAtomIndex(atom)];
}

const Chem::FragmentList::SharedPointer& 
ForceField::MMFF94InteractionParameterizer::getAromaticRings(const Chem::MolecularGraph& molgraph) const
{
	return usedAromRings;
}

std::size_t ForceField::MMFF94InteractionParameterizer::getTopologicalDistance(const Chem::Atom& atom1, const Chem::Atom& atom2, 
																			   const Chem::MolecularGraph& molgraph) const
{
	return (*usedTopDistMatrix)(molgraph.getAtomIndex(atom1), molgraph.getAtomIndex(atom2));
} 

void ForceField::MMFF94InteractionParameterizer::setup(const Chem::MolecularGraph& molgraph, unsigned int ia_types, bool strict)
{
	molGraph = &molgraph;

	setupAromaticRingSet();
	setupAtomTypes(strict);
	setupBondTypeIndices(strict);

	if ((ia_types & InteractionType::ELECTROSTATIC) || (ia_types & InteractionType::VAN_DER_WAALS))
		setupTopDistances();

	if (ia_types & InteractionType::ELECTROSTATIC)
		setupAtomCharges(strict);
}

void ForceField::MMFF94InteractionParameterizer::setupAromaticRingSet()
{
	if (hasMMFF94AromaticRings(*molGraph))
		usedAromRings = getMMFF94AromaticRings(*molGraph);

	else {
		if (!aromRings)
			aromRings = MMFF94AromaticSSSRSubset::SharedPointer(new MMFF94AromaticSSSRSubset());

		aromRings->extract(*molGraph);
		usedAromRings = aromRings;
	}
}

void ForceField::MMFF94InteractionParameterizer::setupAtomTypes(bool strict)
{
	using namespace Chem;

	std::size_t num_atoms = molGraph->getNumAtoms();

	numAtomTypes.resize(num_atoms);
	symAtomTypes.resize(num_atoms);

	for (std::size_t i = 0; i < num_atoms; i++) {
		const Atom& atom = molGraph->getAtom(i);

		if (hasMMFF94NumericType(atom) && hasMMFF94SymbolicType(atom)) {
			numAtomTypes[i] = getMMFF94NumericType(atom);
			symAtomTypes[i] = getMMFF94SymbolicType(atom);

			if (strict && numAtomTypes[i] == 0)
				throw ParameterizationFailed("MMFF94InteractionParameterizer: encountered invalid MMFF94 type for atom #" + std::to_string(i));

		} else {
			atomTyper.perceiveTypes(*molGraph, symAtomTypes, numAtomTypes, strict);

			if (strict) {
				for (std::size_t j = 0; j < num_atoms; j++) 
					if (numAtomTypes[j] == 0) 
						throw ParameterizationFailed("MMFF94InteractionParameterizer: could not determine MMFF94 type of atom #" + std::to_string(j));
			}

			return;
		}
	}
}

void ForceField::MMFF94InteractionParameterizer::setupBondTypeIndices(bool strict)
{
	using namespace Chem;

	std::size_t num_bonds = molGraph->getNumBonds();

	bondTypeIndices.resize(num_bonds);

	for (std::size_t i = 0; i < num_bonds; i++) {
		const Bond& bond = molGraph->getBond(i);

		if (hasMMFF94TypeIndex(bond)) {
			bondTypeIndices[i] = getMMFF94TypeIndex(bond);

		} else {
			bondTyper.perceiveTypes(*molGraph, bondTypeIndices, strict);
			return;
		}
	}
}

void ForceField::MMFF94InteractionParameterizer::setupAtomCharges(bool strict)
{
	using namespace Chem;

	std::size_t num_atoms = molGraph->getNumAtoms();

	atomCharges.resize(num_atoms);

	for (std::size_t i = 0; i < num_atoms; i++) {
		const Atom& atom = molGraph->getAtom(i);

		if (hasMMFF94Charge(atom))
			atomCharges[i] = getMMFF94Charge(atom);

		else {
			chargeCalculator.calculate(*molGraph, atomCharges, strict);
			return;
		}
	}
}

void ForceField::MMFF94InteractionParameterizer::setupTopDistances()
{
	if (hasTopologicalDistanceMatrix(*molGraph))
		usedTopDistMatrix = getTopologicalDistanceMatrix(*molGraph);

	else {
		if (!topDistMatrix)
			topDistMatrix = Math::ULMatrix::SharedPointer(new Math::ULMatrix());

		calcTopologicalDistanceMatrix(*molGraph, *topDistMatrix);
		usedTopDistMatrix = topDistMatrix;
	}
}
