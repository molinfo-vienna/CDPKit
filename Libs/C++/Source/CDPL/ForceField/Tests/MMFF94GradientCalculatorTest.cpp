/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * MMFF94GradientCalculatorTest.cpp 
 *
 * This file is part of the Chemical Data Processing Toolkit
 *
 * Copyright (C) 2003-2010 Thomas A. Seidel <thomas.seidel@univie.ac.at>
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
#include <algorithm>

#include <boost/test/auto_unit_test.hpp>

#include "CDPL/ForceField/MMFF94InteractionData.hpp"
#include "CDPL/ForceField/MMFF94InteractionParameterizer.hpp"
#include "CDPL/ForceField/MMFF94EnergyCalculator.hpp"
#include "CDPL/ForceField/MMFF94GradientCalculator.hpp"
#include "CDPL/Chem/MolecularGraphFunctions.hpp"
#include "CDPL/Chem/AtomContainerFunctions.hpp"

#include "MMFF94TestData.hpp"


BOOST_AUTO_TEST_CASE(MMFF94GradientCalculatorTest)
{
	const static double E_DELTA_MAX = 0.00000001;
	const static double GRAD_DELTA_MAX = 0.000004;
	const static double EPSILON = 0.0000001;

    using namespace CDPL;
    using namespace Testing;

	ForceField::MMFF94InteractionParameterizer parameterizer;
    ForceField::MMFF94InteractionData ia_data;
    ForceField::MMFF94EnergyCalculator<double> en_calc(ia_data);
    ForceField::MMFF94GradientCalculator<double> gr_calc(ia_data);
    Math::Vector3DArray coords;
    Math::Vector3DArray grad;
    Math::Vector3D num_atom_grad;

	for (bool stat = false; !stat; stat = true) {
		const MMFF94TestData::MoleculeList& mols = (stat ? MMFF94TestData::STAT_TEST_MOLECULES : MMFF94TestData::DYN_TEST_MOLECULES);

		if (stat)
			parameterizer.setStaticParameterDefaults();
		else
			parameterizer.setDynamicParameterDefaults();

		for (std::size_t mol_idx = 0; mol_idx < mols.size(); mol_idx++) {
			const Chem::Molecule& mol = *mols[mol_idx];
	
			coords.clear();
			get3DCoordinates(mol, coords);

			grad.resize(coords.getSize());
	
			parameterizer.parameterize(mol, ia_data);
			en_calc.setup(ia_data);
			gr_calc.setup(ia_data);

			gr_calc(coords, grad);
			en_calc(coords);
		   
			BOOST_CHECK_MESSAGE(std::abs(gr_calc.getTotalEnergy() - en_calc.getTotalEnergy()) <= E_DELTA_MAX, 
								"Total energy mismatch for molecule #" << mol_idx << " (" << getName(mol) <<
								"): grad. calculator energy " << gr_calc.getTotalEnergy() << " != " << en_calc.getTotalEnergy());

			BOOST_CHECK_MESSAGE(std::abs(gr_calc.getBondStretchingEnergy() - en_calc.getBondStretchingEnergy()) <= E_DELTA_MAX, 
								"Total bond stretching energy mismatch for molecule #" << mol_idx << " (" << getName(mol) <<
								"): grad. calculator energy " << gr_calc.getBondStretchingEnergy() << " != " << en_calc.getBondStretchingEnergy());

			BOOST_CHECK_MESSAGE(std::abs(gr_calc.getAngleBendingEnergy() - en_calc.getAngleBendingEnergy()) <= E_DELTA_MAX, 
								"Total angle bending energy mismatch for molecule #" << mol_idx << " (" << getName(mol) <<
								"): grad. calculator energy " << gr_calc.getAngleBendingEnergy() << " != " << en_calc.getAngleBendingEnergy());

			BOOST_CHECK_MESSAGE(std::abs(gr_calc.getStretchBendEnergy() - en_calc.getStretchBendEnergy()) <= E_DELTA_MAX, 
								"Total stretch-bend energy mismatch for molecule #" << mol_idx << " (" << getName(mol) <<
								"): grad. calculator energy " << gr_calc.getStretchBendEnergy() << " != " << en_calc.getStretchBendEnergy());

  			BOOST_CHECK_MESSAGE(std::abs(gr_calc.getOutOfPlaneBendingEnergy() - en_calc.getOutOfPlaneBendingEnergy()) <= E_DELTA_MAX, 
								"Total out-of-plane bending energy mismatch for molecule #" << mol_idx << " (" << getName(mol) <<
								"): grad. calculator energy " << gr_calc.getOutOfPlaneBendingEnergy() << " != " << en_calc.getOutOfPlaneBendingEnergy());

			BOOST_CHECK_MESSAGE(std::abs(gr_calc.getTorsionEnergy() - en_calc.getTorsionEnergy()) <= E_DELTA_MAX, 
								"Total torsion energy mismatch for molecule #" << mol_idx << " (" << getName(mol) <<
								"): grad. calculator energy " << gr_calc.getTorsionEnergy() << " != " << en_calc.getTorsionEnergy());
	    
			BOOST_CHECK_MESSAGE(std::abs(gr_calc.getVanDerWaalsEnergy() - en_calc.getVanDerWaalsEnergy()) <= E_DELTA_MAX, 
								"Total van der Waals energy mismatch for molecule #" << mol_idx << " (" << getName(mol) <<
								"): grad. calculator energy " << gr_calc.getVanDerWaalsEnergy() << " != " << en_calc.getVanDerWaalsEnergy());
    
			BOOST_CHECK_MESSAGE(std::abs(gr_calc.getElectrostaticEnergy() - en_calc.getElectrostaticEnergy()) <= E_DELTA_MAX, 
								"Total electrostatic energy mismatch for molecule #" << mol_idx << " (" << getName(mol) <<
								"): grad. calculator energy " << gr_calc.getElectrostaticEnergy() << " != " << en_calc.getElectrostaticEnergy());

			double max_diff = 0.0;

			for (std::size_t i = 0; i < coords.getSize(); i++) {
				Math::Vector3D& atom_pos = coords[i];

				for (std::size_t j = 0; j < 3; j++) {
					double c = atom_pos[j];

					atom_pos[j] = c + EPSILON;
					double e1 = en_calc(coords);

					atom_pos[j] = c - EPSILON;
					double e2 = en_calc(coords);

					atom_pos[j] = c;
					num_atom_grad[j] = (e1 - e2) / (2 * EPSILON);
				}

				max_diff = std::max(max_diff, normInf(grad[i] - num_atom_grad));
			}

			BOOST_CHECK_MESSAGE((max_diff <= GRAD_DELTA_MAX), 
								"Gradient deviation too large for molecule #" << mol_idx << " (" << getName(mol) <<
								"): max. numerical/analytical grad. element deviation of " << max_diff << " > " << GRAD_DELTA_MAX);
		}
    }
}
