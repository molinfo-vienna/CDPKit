/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * MMFF94EnergyCalculatorTest.cpp 
 *
 * This file is part of the Chemical Data Processing Toolkit
 *
 * Copyright (C) 2003 Thomas Seidel <thomas.seidel@univie.ac.at>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program; see the file COPYING. If not, write to
 * the Free Software Foundation, Inc., 59 Temple Place - Suite 330,
 * Boston, MA 02111-1307, USA.
 */


#include <cstddef>
#include <cmath>

#include <boost/test/auto_unit_test.hpp>

#include "CDPL/ForceField/MMFF94InteractionData.hpp"
#include "CDPL/ForceField/MMFF94InteractionParameterizer.hpp"
#include "CDPL/ForceField/MMFF94EnergyCalculator.hpp"
#include "CDPL/Chem/MolecularGraphFunctions.hpp"
#include "CDPL/Chem/Entity3DContainerFunctions.hpp"

#include "MMFF94TestData.hpp"


BOOST_AUTO_TEST_CASE(MMFF94EnergyCalculatorTest)
{
    using namespace CDPL;
    using namespace Testing;

    OptimolLogReader::EnergyData energies;

    ForceField::MMFF94InteractionParameterizer parameterizer;
    ForceField::MMFF94InteractionData ia_data;
    ForceField::MMFF94EnergyCalculator<double> calculator;
    Math::Vector3DArray coords;

    //double max_en_diff = 0;

    for (bool stat = false; !stat; stat = true) {
		OptimolLogReader& log_reader = (stat ? MMFF94TestData::STAT_LOG_READER : MMFF94TestData::DYN_LOG_READER);
		const MMFF94TestData::MoleculeList& mols = (stat ? MMFF94TestData::STAT_TEST_MOLECULES : MMFF94TestData::DYN_TEST_MOLECULES);

		if (stat)
			parameterizer.setParameterSet(ForceField::MMFF94ParameterSet::STATIC);
		else
			parameterizer.setParameterSet(ForceField::MMFF94ParameterSet::DYNAMIC);

		for (std::size_t mol_idx = 0; mol_idx < mols.size(); mol_idx++) {
			const Chem::Molecule& mol = *mols[mol_idx];
			const std::string& mol_name = getName(mol);

			BOOST_CHECK(log_reader.getEnergies(mol_name, energies));

			coords.clear();
			get3DCoordinates(mol, coords);

			parameterizer.parameterize(mol, ia_data);
			calculator.setup(ia_data);

			double energy = calculator(coords);
		
			//max_en_diff = std::max(max_en_diff, std::abs(energy - energies.total));
		    
			BOOST_CHECK_MESSAGE(std::abs(energy - energies.total) < 0.0704, 
								"Total energy mismatch for molecule #" << mol_idx << " (" << mol_name <<
								"): calc. " << energy << " != " << energies.total);

			BOOST_CHECK_MESSAGE(std::abs(calculator.getBondStretchingEnergy() - energies.bondStretching) < 0.00552, 
								"Total bond stretching energy mismatch for molecule #" << mol_idx << " (" << mol_name <<
								"): calc. " << calculator.getBondStretchingEnergy() << " != " << energies.bondStretching);

			BOOST_CHECK_MESSAGE(std::abs(calculator.getAngleBendingEnergy() - energies.angleBending) < 0.0704, 
								"Total angle bending energy mismatch for molecule #" << mol_idx << " (" << mol_name <<
								"): calc. " << calculator.getAngleBendingEnergy() << " != " << energies.angleBending);

			BOOST_CHECK_MESSAGE(std::abs(calculator.getStretchBendEnergy() - energies.stretchBend) < 0.00422, 
								"Total stretch-bend energy mismatch for molecule #" << mol_idx << " (" << mol_name <<
								"): calc. " << calculator.getStretchBendEnergy() << " != " << energies.stretchBend);

  			BOOST_CHECK_MESSAGE(std::abs(calculator.getOutOfPlaneBendingEnergy() - energies.outOfPlaneBending) < 0.00168, 
								"Total out-of-plane bending energy mismatch for molecule #" << mol_idx << " (" << mol_name <<
								"): calc. " << calculator.getOutOfPlaneBendingEnergy() << " != " << energies.outOfPlaneBending);

			BOOST_CHECK_MESSAGE(std::abs(calculator.getTorsionEnergy() - energies.torsion) < 0.00141, 
								"Total torsion energy mismatch for molecule #" << mol_idx << " (" << mol_name <<
								"): calc. " << calculator.getTorsionEnergy() << " != " << energies.torsion);
	    
			BOOST_CHECK_MESSAGE(std::abs(calculator.getVanDerWaalsEnergy() - energies.vanDerWaals) < 0.00621, 
								"Total van der Waals energy mismatch for molecule #" << mol_idx << " (" << mol_name <<
								"): calc. " << calculator.getVanDerWaalsEnergy() << " != " << energies.vanDerWaals);
    
			BOOST_CHECK_MESSAGE(std::abs(calculator.getElectrostaticEnergy() - energies.electrostatic) < 0.00564, 
								"Total electrostatic energy mismatch for molecule #" << mol_idx << " (" << mol_name <<
								"): calc. " << calculator.getElectrostaticEnergy() << " != " << energies.electrostatic);
		}
    }

    //BOOST_MESSAGE("Max. energy difference: " << max_en_diff); 
}
