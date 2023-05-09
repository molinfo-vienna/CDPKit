/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * MMFF94ElectrostaticInteractionParameterizer.cpp 
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

#include "CDPL/ForceField/MMFF94ElectrostaticInteractionParameterizer.hpp"
#include "CDPL/ForceField/AtomFunctions.hpp"
#include "CDPL/Chem/MolecularGraph.hpp"
#include "CDPL/Chem/AtomFunctions.hpp"


using namespace CDPL; 


const double ForceField::MMFF94ElectrostaticInteractionParameterizer::DEF_DISTANCE_EXPONENT     = 1.0;
const double ForceField::MMFF94ElectrostaticInteractionParameterizer::DEF_DIELECTRIC_CONSTANT   = 1.0;
const double ForceField::MMFF94ElectrostaticInteractionParameterizer::DIELECTRIC_CONSTANT_WATER = 80.0;


ForceField::MMFF94ElectrostaticInteractionParameterizer::MMFF94ElectrostaticInteractionParameterizer(const Chem::MolecularGraph& molgraph, 
																									 MMFF94ElectrostaticInteractionData& ia_data,
																									 bool strict):
	filterFunc(), chargeFunc(&getMMFF94Charge), distFunc(&Chem::getTopologicalDistance), 
	deConst(DEF_DIELECTRIC_CONSTANT), distExpo(DEF_DISTANCE_EXPONENT)
{
    parameterize(molgraph, ia_data, strict);
}

ForceField::MMFF94ElectrostaticInteractionParameterizer::MMFF94ElectrostaticInteractionParameterizer():
	filterFunc(), chargeFunc(&getMMFF94Charge), distFunc(&Chem::getTopologicalDistance), 
	deConst(DEF_DIELECTRIC_CONSTANT), distExpo(DEF_DISTANCE_EXPONENT) 
{}
	
void ForceField::MMFF94ElectrostaticInteractionParameterizer::setFilterFunction(const InteractionFilterFunction2& func)
{
	filterFunc = func;
} 

void ForceField::MMFF94ElectrostaticInteractionParameterizer::setAtomChargeFunction(const MMFF94AtomChargeFunction& func)
{
	chargeFunc = func;
}  

void ForceField::MMFF94ElectrostaticInteractionParameterizer::setTopologicalDistanceFunction(const TopologicalAtomDistanceFunction& func)
{
	distFunc = func;
}  

void ForceField::MMFF94ElectrostaticInteractionParameterizer::setDielectricConstant(double de_const)
{
	deConst = de_const;
} 

void ForceField::MMFF94ElectrostaticInteractionParameterizer::setDistanceExponent(double dist_expo)
{
	distExpo = dist_expo;
} 

void ForceField::MMFF94ElectrostaticInteractionParameterizer::parameterize(const Chem::MolecularGraph& molgraph, 
																		   MMFF94ElectrostaticInteractionData& ia_data, bool strict)
{
	using namespace Chem;

	ia_data.clear();

	for (std::size_t i = 0, num_atoms = molgraph.getNumAtoms(); i < num_atoms; i++) {
		const Atom& atom1 = molgraph.getAtom(i);

		for (std::size_t j = i + 1; j < num_atoms; j++) {
			const Atom& atom2 = molgraph.getAtom(j);
			std::size_t top_dist = distFunc(atom1, atom2, molgraph);
			double factor = 0.0;

			if (top_dist == 0 || top_dist > 3)
				factor = 1.0;
			else if (top_dist == 3)
				factor = 0.75;
			else
				continue;

			if (filterFunc && !filterFunc(atom1, atom2))
				continue;
	
			ia_data.addElement(MMFF94ElectrostaticInteraction(i, j, chargeFunc(atom1), chargeFunc(atom2), factor, deConst, distExpo));
		}
	}
}
