/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * MMFF94GradientFunctionsTest.cpp 
 *
 * This file is part of the Chemical Data Processing Toolkit
 *
 * Copyright (C) 2003-2020 Thomas A. Seidel <thomas.seidel@univie.ac.at>
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

#include "CDPL/ForceField/MMFF94BondStretchingInteractionParameterizer.hpp"
#include "CDPL/ForceField/MMFF94AngleBendingInteractionParameterizer.hpp"
#include "CDPL/ForceField/MMFF94StretchBendInteractionParameterizer.hpp"
#include "CDPL/ForceField/MMFF94OutOfPlaneBendingInteractionParameterizer.hpp"
#include "CDPL/ForceField/MMFF94OutOfPlaneBendingParameterTable.hpp"
#include "CDPL/ForceField/MMFF94TorsionInteractionParameterizer.hpp"
#include "CDPL/ForceField/MMFF94TorsionParameterTable.hpp"
#include "CDPL/ForceField/MMFF94VanDerWaalsInteractionParameterizer.hpp"
#include "CDPL/ForceField/MMFF94ElectrostaticInteractionParameterizer.hpp"
#include "CDPL/ForceField/MMFF94EnergyFunctions.hpp"
#include "CDPL/ForceField/MMFF94GradientFunctions.hpp"
#include "CDPL/ForceField/MolecularGraphFunctions.hpp"
#include "CDPL/Chem/MolecularGraphFunctions.hpp"
#include "CDPL/Chem/Entity3DContainerFunctions.hpp"
#include "CDPL/Chem/AtomFunctions.hpp"
#include "CDPL/Math/IO.hpp"

#include "MMFF94TestData.hpp"


namespace
{

	template <typename IAction, typename Func>
	void calcNumericalGradient(const IAction& iaction, CDPL::Math::Vector3DArray& coords, std::size_t atom_idx, CDPL::Math::Vector3D& grad, const Func& func)
	{
		const static double EPSILON = 0.0000001;

		for (std::size_t i = 0; i < 3; i++) {
			double c = coords[atom_idx][i];

			coords[atom_idx][i] = c + EPSILON;
			double e1 = func(iaction, coords);

			coords[atom_idx][i] = c - EPSILON;
			double e2 = func(iaction, coords);

			coords[atom_idx][i] = c;
			grad[i] = (e1 - e2) / (2 * EPSILON);
		}
	}
}


BOOST_AUTO_TEST_CASE(MMFF94BondStretchingGradientFunctionTest)
{
 	const static double E_DELTA_MAX = 0.000000001;
	const static double GRAD_DELTA_MAX = 0.000001;

	using namespace CDPL;
    using namespace Testing;

	ForceField::MMFF94BondStretchingInteractionParameterizer parameterizer;
    ForceField::MMFF94BondStretchingInteractionData found_ia_data;
    Math::Vector3DArray coords;
	Math::Vector3DArray grad;
	Math::Vector3D num_atom1_grad;
	Math::Vector3D num_atom2_grad;

    for (std::size_t mol_idx = 0; mol_idx < MMFF94TestData::DYN_TEST_MOLECULES.size(); mol_idx++) {
		const Chem::Molecule& mol = *MMFF94TestData::DYN_TEST_MOLECULES[mol_idx];

		parameterizer.parameterize(mol, found_ia_data, true);
	
		coords.clear();
		get3DCoordinates(mol, coords);

		grad.resize(coords.getSize());

		for (std::size_t i = 0; i < found_ia_data.size(); i++) {
			const ForceField::MMFF94BondStretchingInteraction& iaction = found_ia_data[i];

			grad[iaction.getAtom1Index()].clear();
			grad[iaction.getAtom2Index()].clear();

			double energy = ForceField::calcMMFF94BondStretchingEnergy<double>(iaction, coords);
			double grad_energy = ForceField::calcMMFF94BondStretchingGradient<double>(iaction, coords, grad);

			BOOST_CHECK_MESSAGE(std::abs(grad_energy - energy) < E_DELTA_MAX, 
								"Energy mismatch for bond stretching interaction #" << iaction.getAtom1Index() << "(" << 
								getMOL2Name(mol.getAtom(iaction.getAtom1Index())) << ")-#" << iaction.getAtom2Index() << "(" << 
								getMOL2Name(mol.getAtom(iaction.getAtom2Index())) << ") of molecule #" << mol_idx << " (" << getName(mol) <<
								"): grad. func. energy " << grad_energy << " != " << energy);
			
			calcNumericalGradient(iaction, coords, iaction.getAtom1Index(), num_atom1_grad, 
								  static_cast<double (*)(const ForceField::MMFF94BondStretchingInteraction&, const Math::Vector3DArray&)>
								  (&ForceField::calcMMFF94BondStretchingEnergy<double, Math::Vector3DArray>));
			calcNumericalGradient(iaction, coords, iaction.getAtom2Index(), num_atom2_grad, 
								  static_cast<double (*)(const ForceField::MMFF94BondStretchingInteraction&, const Math::Vector3DArray&)>
								  (&ForceField::calcMMFF94BondStretchingEnergy<double, Math::Vector3DArray>));

			double max_diff = std::max(normInf(num_atom1_grad - grad[iaction.getAtom1Index()]), normInf(num_atom2_grad - grad[iaction.getAtom2Index()]));

			BOOST_CHECK_MESSAGE((max_diff <= GRAD_DELTA_MAX), 
								"Gradient deviation too large for bond stretching interaction #" << iaction.getAtom1Index() << "(" << 
								getMOL2Name(mol.getAtom(iaction.getAtom1Index())) << ")-#" << iaction.getAtom2Index() << "(" << 
								getMOL2Name(mol.getAtom(iaction.getAtom2Index())) << ") of molecule #" << mol_idx << " (" << getName(mol) <<
								"): max. numerical/analytical grad. element deviation of " << max_diff << " > " << GRAD_DELTA_MAX);
		}
    }
}

BOOST_AUTO_TEST_CASE(MMFF94AngleBendingGradientFunctionTest)
{
 	const static double E_DELTA_MAX = 0.000000001;
	const static double GRAD_DELTA_MAX = 0.000001;

	using namespace CDPL;
    using namespace Testing;

    ForceField::MMFF94AngleBendingInteractionParameterizer parameterizer;
    ForceField::MMFF94AngleBendingInteractionData found_ia_data;
    Math::Vector3DArray coords;
	Math::Vector3DArray grad;
	Math::Vector3D num_term_atom1_grad;
	Math::Vector3D num_term_atom2_grad;
	Math::Vector3D num_ctr_atom_grad;

    for (std::size_t mol_idx = 0; mol_idx < MMFF94TestData::DYN_TEST_MOLECULES.size(); mol_idx++) {
		const Chem::Molecule& mol = *MMFF94TestData::DYN_TEST_MOLECULES[mol_idx];
	
		parameterizer.parameterize(mol, found_ia_data, true);

		coords.clear();
		get3DCoordinates(mol, coords);

		grad.resize(coords.getSize());

		for (std::size_t i = 0; i < found_ia_data.size(); i++) {
			const ForceField::MMFF94AngleBendingInteraction& iaction = found_ia_data[i];

			grad[iaction.getTerminalAtom1Index()].clear();
			grad[iaction.getTerminalAtom2Index()].clear();
			grad[iaction.getCenterAtomIndex()].clear();

			double energy = ForceField::calcMMFF94AngleBendingEnergy<double>(iaction, coords);
			double grad_energy = ForceField::calcMMFF94AngleBendingGradient<double>(iaction, coords, grad);
		
			BOOST_CHECK_MESSAGE(std::abs(grad_energy - energy) < E_DELTA_MAX, 
								"Energy mismatch for angle bending interaction #" << iaction.getTerminalAtom1Index() << "(" << 
								getMOL2Name(mol.getAtom(iaction.getTerminalAtom1Index())) << ")-#" << iaction.getCenterAtomIndex() << "(" << 
								getMOL2Name(mol.getAtom(iaction.getCenterAtomIndex())) << ")-#" << iaction.getTerminalAtom2Index() << "(" << 
								getMOL2Name(mol.getAtom(iaction.getTerminalAtom2Index())) << ") of molecule #" << mol_idx << " (" << getName(mol) <<
								"): grad. func. energy " << grad_energy << " != " << energy);

			calcNumericalGradient(iaction, coords, iaction.getTerminalAtom1Index(), num_term_atom1_grad, 
								  static_cast<double (*)(const ForceField::MMFF94AngleBendingInteraction&, const Math::Vector3DArray&)>
								  (&ForceField::calcMMFF94AngleBendingEnergy<double, Math::Vector3DArray>));
			calcNumericalGradient(iaction, coords, iaction.getTerminalAtom2Index(), num_term_atom2_grad, 
								  static_cast<double (*)(const ForceField::MMFF94AngleBendingInteraction&, const Math::Vector3DArray&)>
								  (&ForceField::calcMMFF94AngleBendingEnergy<double, Math::Vector3DArray>));
			calcNumericalGradient(iaction, coords, iaction.getCenterAtomIndex(), num_ctr_atom_grad, 
								  static_cast<double (*)(const ForceField::MMFF94AngleBendingInteraction&, const Math::Vector3DArray&)>
								  (&ForceField::calcMMFF94AngleBendingEnergy<double, Math::Vector3DArray>));
			
			double max_diff = std::max(std::max(normInf(num_term_atom1_grad - grad[iaction.getTerminalAtom1Index()]), normInf(num_term_atom2_grad - grad[iaction.getTerminalAtom2Index()])),
									   normInf(num_ctr_atom_grad - grad[iaction.getCenterAtomIndex()]));

			BOOST_CHECK_MESSAGE((max_diff <= GRAD_DELTA_MAX), 
								"Gradient deviation too large for angle bending interaction #" << iaction.getTerminalAtom1Index() << "(" << 
								getMOL2Name(mol.getAtom(iaction.getTerminalAtom1Index())) << ")-#" << iaction.getCenterAtomIndex() << "(" << 
								getMOL2Name(mol.getAtom(iaction.getCenterAtomIndex())) << ")-#" << iaction.getTerminalAtom2Index() << "(" << 
								getMOL2Name(mol.getAtom(iaction.getTerminalAtom2Index())) << ") of molecule #" << mol_idx << " (" << getName(mol) <<
								"): max. numerical/analytical grad. element deviation of " << max_diff << " > " << GRAD_DELTA_MAX);
		}
    }
}

BOOST_AUTO_TEST_CASE(MMFF94StretchBendGradientFunctionTest)
{
 	const static double E_DELTA_MAX = 0.000000001;
	const static double GRAD_DELTA_MAX = 0.000001;

    using namespace CDPL;
    using namespace Testing;

    ForceField::MMFF94AngleBendingInteractionParameterizer ab_parameterizer;
    ForceField::MMFF94BondStretchingInteractionParameterizer bs_parameterizer;
    ForceField::MMFF94StretchBendInteractionParameterizer sb_parameterizer;
    ForceField::MMFF94StretchBendInteractionData found_ia_data;
    ForceField::MMFF94AngleBendingInteractionData ab_ia_data;
    ForceField::MMFF94BondStretchingInteractionData bs_ia_data;
    Math::Vector3DArray coords;
	Math::Vector3DArray grad;
	Math::Vector3D num_term_atom1_grad;
	Math::Vector3D num_term_atom2_grad;
	Math::Vector3D num_ctr_atom_grad;

    for (std::size_t mol_idx = 0; mol_idx < MMFF94TestData::DYN_TEST_MOLECULES.size(); mol_idx++) {
		const Chem::Molecule& mol = *MMFF94TestData::DYN_TEST_MOLECULES[mol_idx];

		bs_parameterizer.parameterize(mol, bs_ia_data, true);
		ab_parameterizer.parameterize(mol, ab_ia_data, true);
		sb_parameterizer.parameterize(mol, bs_ia_data, ab_ia_data, found_ia_data, true);

		coords.clear();
		get3DCoordinates(mol, coords);

		grad.resize(coords.getSize());

		for (std::size_t i = 0; i < found_ia_data.size(); i++) {
			const ForceField::MMFF94StretchBendInteraction& iaction = found_ia_data[i];

			grad[iaction.getTerminalAtom1Index()].clear();
			grad[iaction.getTerminalAtom2Index()].clear();
			grad[iaction.getCenterAtomIndex()].clear();

			double energy = ForceField::calcMMFF94StretchBendEnergy<double>(iaction, coords);
			double grad_energy = ForceField::calcMMFF94StretchBendGradient<double>(iaction, coords, grad);
		
			BOOST_CHECK_MESSAGE(std::abs(grad_energy - energy) < E_DELTA_MAX, 
								"Energy mismatch for stretch-bend interaction #" << iaction.getTerminalAtom1Index() << "(" << 
								getMOL2Name(mol.getAtom(iaction.getTerminalAtom1Index())) << ")-#" << iaction.getCenterAtomIndex() << "(" << 
								getMOL2Name(mol.getAtom(iaction.getCenterAtomIndex())) << ")-#" << iaction.getTerminalAtom2Index() << "(" << 
								getMOL2Name(mol.getAtom(iaction.getTerminalAtom2Index())) << ") of molecule #" << mol_idx << " (" << getName(mol) <<
								"): grad. func. energy " << grad_energy << " != " << energy);

			calcNumericalGradient(iaction, coords, iaction.getTerminalAtom1Index(), num_term_atom1_grad, 
								  static_cast<double (*)(const ForceField::MMFF94StretchBendInteraction&, const Math::Vector3DArray&)>
								  (&ForceField::calcMMFF94StretchBendEnergy<double, Math::Vector3DArray>));
			calcNumericalGradient(iaction, coords, iaction.getTerminalAtom2Index(), num_term_atom2_grad, 
								  static_cast<double (*)(const ForceField::MMFF94StretchBendInteraction&, const Math::Vector3DArray&)>
								  (&ForceField::calcMMFF94StretchBendEnergy<double, Math::Vector3DArray>));
			calcNumericalGradient(iaction, coords, iaction.getCenterAtomIndex(), num_ctr_atom_grad, 
								  static_cast<double (*)(const ForceField::MMFF94StretchBendInteraction&, const Math::Vector3DArray&)>
								  (&ForceField::calcMMFF94StretchBendEnergy<double, Math::Vector3DArray>));
			
			double max_diff = std::max(std::max(normInf(num_term_atom1_grad - grad[iaction.getTerminalAtom1Index()]), normInf(num_term_atom2_grad - grad[iaction.getTerminalAtom2Index()])),
									   normInf(num_ctr_atom_grad - grad[iaction.getCenterAtomIndex()]));

			BOOST_CHECK_MESSAGE((max_diff <= GRAD_DELTA_MAX), 
								"Gradient deviation too large for stretch-bend interaction #" << iaction.getTerminalAtom1Index() << "(" << 
								getMOL2Name(mol.getAtom(iaction.getTerminalAtom1Index())) << ")-#" << iaction.getCenterAtomIndex() << "(" << 
								getMOL2Name(mol.getAtom(iaction.getCenterAtomIndex())) << ")-#" << iaction.getTerminalAtom2Index() << "(" << 
								getMOL2Name(mol.getAtom(iaction.getTerminalAtom2Index())) << ") of molecule #" << mol_idx << " (" << getName(mol) <<
								"): max. numerical/analytical grad. element deviation of " << max_diff << " > " << GRAD_DELTA_MAX);
		}
    }  
}

BOOST_AUTO_TEST_CASE(MMFF94OutOfPlaneBendingGradientFunctionTest)
{
 	const static double E_DELTA_MAX = 0.000000001;
	const static double GRAD_DELTA_MAX = 0.000001;

    using namespace CDPL;
    using namespace Testing;

    ForceField::MMFF94OutOfPlaneBendingInteractionParameterizer parameterizer;
    ForceField::MMFF94OutOfPlaneBendingInteractionData found_ia_data;
    Math::Vector3DArray coords;
	Math::Vector3DArray grad;
	Math::Vector3D num_term_atom1_grad;
	Math::Vector3D num_term_atom2_grad;
	Math::Vector3D num_ctr_atom_grad;
	Math::Vector3D num_oop_atom_grad;

    for (bool stat = false; !stat; stat = true) {
		const MMFF94TestData::MoleculeList& mols = (stat ? MMFF94TestData::STAT_TEST_MOLECULES : MMFF94TestData::DYN_TEST_MOLECULES);

		parameterizer.setOutOfPlaneBendingParameterTable(ForceField::MMFF94OutOfPlaneBendingParameterTable::get(stat));

		for (std::size_t mol_idx = 0; mol_idx < mols.size(); mol_idx++) {
			const Chem::Molecule& mol = *mols[mol_idx];

			parameterizer.parameterize(mol, found_ia_data, true);

			coords.clear();
			get3DCoordinates(mol, coords);

			grad.resize(coords.getSize());

			for (std::size_t i = 0; i < found_ia_data.size(); i++) {
				const ForceField::MMFF94OutOfPlaneBendingInteraction& iaction = found_ia_data[i];

				grad[iaction.getTerminalAtom1Index()].clear();
				grad[iaction.getTerminalAtom2Index()].clear();
				grad[iaction.getCenterAtomIndex()].clear();
				grad[iaction.getOutOfPlaneAtomIndex()].clear();

				double energy = ForceField::calcMMFF94OutOfPlaneBendingEnergy<double>(iaction, coords);
				double grad_energy = ForceField::calcMMFF94OutOfPlaneBendingGradient<double>(iaction, coords, grad);
		
				BOOST_CHECK_MESSAGE(std::abs(grad_energy - energy) < E_DELTA_MAX, 
									"Energy mismatch for out-of-plane bending interaction <#" << iaction.getTerminalAtom1Index() << "(" << 
									getMOL2Name(mol.getAtom(iaction.getTerminalAtom1Index())) << ")-#" << iaction.getCenterAtomIndex() << "(" << 
									getMOL2Name(mol.getAtom(iaction.getCenterAtomIndex())) << ")-#" << iaction.getTerminalAtom2Index() << "(" << 
									getMOL2Name(mol.getAtom(iaction.getTerminalAtom2Index())) << ")>~#" << iaction.getOutOfPlaneAtomIndex() << "(" << 
									getMOL2Name(mol.getAtom(iaction.getOutOfPlaneAtomIndex())) << ") of molecule #" << mol_idx << " (" << getName(mol) <<
									"): grad. func. energy " << grad_energy << " != " << energy);

				calcNumericalGradient(iaction, coords, iaction.getTerminalAtom1Index(), num_term_atom1_grad, 
									  static_cast<double (*)(const ForceField::MMFF94OutOfPlaneBendingInteraction&, const Math::Vector3DArray&)>
									  (&ForceField::calcMMFF94OutOfPlaneBendingEnergy<double, Math::Vector3DArray>));
				calcNumericalGradient(iaction, coords, iaction.getTerminalAtom2Index(), num_term_atom2_grad, 
									  static_cast<double (*)(const ForceField::MMFF94OutOfPlaneBendingInteraction&, const Math::Vector3DArray&)>
									  (&ForceField::calcMMFF94OutOfPlaneBendingEnergy<double, Math::Vector3DArray>));
				calcNumericalGradient(iaction, coords, iaction.getCenterAtomIndex(), num_ctr_atom_grad, 
									  static_cast<double (*)(const ForceField::MMFF94OutOfPlaneBendingInteraction&, const Math::Vector3DArray&)>
									  (&ForceField::calcMMFF94OutOfPlaneBendingEnergy<double, Math::Vector3DArray>));
				calcNumericalGradient(iaction, coords, iaction.getOutOfPlaneAtomIndex(), num_oop_atom_grad, 
									  static_cast<double (*)(const ForceField::MMFF94OutOfPlaneBendingInteraction&, const Math::Vector3DArray&)>
									  (&ForceField::calcMMFF94OutOfPlaneBendingEnergy<double, Math::Vector3DArray>));
			
				double max_diff = std::max(
					std::max(normInf(num_term_atom1_grad - grad[iaction.getTerminalAtom1Index()]), normInf(num_term_atom2_grad - grad[iaction.getTerminalAtom2Index()])),
					std::max(normInf(num_ctr_atom_grad - grad[iaction.getCenterAtomIndex()]), normInf(num_oop_atom_grad - grad[iaction.getOutOfPlaneAtomIndex()])));

				BOOST_CHECK_MESSAGE((max_diff <= GRAD_DELTA_MAX), 
									"Gradient deviation too large for out-of-plane bending interaction <#" << iaction.getTerminalAtom1Index() << "(" << 
									getMOL2Name(mol.getAtom(iaction.getTerminalAtom1Index())) << ")-#" << iaction.getCenterAtomIndex() << "(" << 
									getMOL2Name(mol.getAtom(iaction.getCenterAtomIndex())) << ")-#" << iaction.getTerminalAtom2Index() << "(" << 
									getMOL2Name(mol.getAtom(iaction.getTerminalAtom2Index())) << ")>~#" << iaction.getOutOfPlaneAtomIndex() << "(" << 
									getMOL2Name(mol.getAtom(iaction.getOutOfPlaneAtomIndex())) << ") of molecule #" << mol_idx << " (" << getName(mol) <<
									"): max. numerical/analytical grad. element deviation of " << max_diff << " > " << GRAD_DELTA_MAX);
			}
		}
    }
}

BOOST_AUTO_TEST_CASE(MMFF94TorsionGradientFunctionTest)
{
 	const static double E_DELTA_MAX = 0.000000001;
	const static double GRAD_DELTA_MAX = 0.000001;

    using namespace CDPL;
    using namespace Testing;

    ForceField::MMFF94TorsionInteractionParameterizer parameterizer;
    ForceField::MMFF94TorsionInteractionData found_ia_data;
    Math::Vector3DArray coords;
	Math::Vector3DArray grad;
	Math::Vector3D num_term_atom1_grad;
	Math::Vector3D num_term_atom2_grad;
	Math::Vector3D num_ctr_atom1_grad;
	Math::Vector3D num_ctr_atom2_grad;

    for (bool stat = false; !stat; stat = true) {
		const MMFF94TestData::MoleculeList& mols = (stat ? MMFF94TestData::STAT_TEST_MOLECULES : MMFF94TestData::DYN_TEST_MOLECULES);

		parameterizer.setTorsionParameterTable(ForceField::MMFF94TorsionParameterTable::get(stat));

		for (std::size_t mol_idx = 0; mol_idx <	mols.size(); mol_idx++) {
			const Chem::Molecule& mol =	*mols[mol_idx];

			parameterizer.parameterize(mol, found_ia_data, true);

			coords.clear();
			get3DCoordinates(mol, coords);

			grad.resize(coords.getSize());

			for (std::size_t i = 0; i < found_ia_data.size(); i++) {
				const ForceField::MMFF94TorsionInteraction& iaction = found_ia_data[i];

				grad[iaction.getTerminalAtom1Index()].clear();
				grad[iaction.getTerminalAtom2Index()].clear();
				grad[iaction.getCenterAtom1Index()].clear();
				grad[iaction.getCenterAtom2Index()].clear();

				double energy = ForceField::calcMMFF94TorsionEnergy<double>(iaction, coords);
				double grad_energy = ForceField::calcMMFF94TorsionGradient<double>(iaction, coords, grad);
		
				BOOST_CHECK_MESSAGE(std::abs(grad_energy - energy) < E_DELTA_MAX, 
									"Energy mismatch for torsion interaction #" << iaction.getTerminalAtom1Index() << "(" << 
									getMOL2Name(mol.getAtom(iaction.getTerminalAtom1Index())) << ")-#" << iaction.getCenterAtom1Index() << "(" << 
									getMOL2Name(mol.getAtom(iaction.getCenterAtom1Index())) << ")-#" << iaction.getCenterAtom2Index() << "(" << 
									getMOL2Name(mol.getAtom(iaction.getCenterAtom2Index())) << ")-#" << iaction.getTerminalAtom2Index() << "(" << 
									getMOL2Name(mol.getAtom(iaction.getTerminalAtom2Index())) << ") of molecule #" << mol_idx << " (" << getName(mol) <<
									"): grad. func. energy " << grad_energy << " != " << energy);

				calcNumericalGradient(iaction, coords, iaction.getTerminalAtom1Index(), num_term_atom1_grad, 
									  &ForceField::calcMMFF94TorsionEnergy<double, Math::Vector3DArray>);
				calcNumericalGradient(iaction, coords, iaction.getTerminalAtom2Index(), num_term_atom2_grad, 
									  &ForceField::calcMMFF94TorsionEnergy<double, Math::Vector3DArray>);
				calcNumericalGradient(iaction, coords, iaction.getCenterAtom1Index(), num_ctr_atom1_grad, 
									  &ForceField::calcMMFF94TorsionEnergy<double, Math::Vector3DArray>);
				calcNumericalGradient(iaction, coords, iaction.getCenterAtom2Index(), num_ctr_atom2_grad, 
									  &ForceField::calcMMFF94TorsionEnergy<double, Math::Vector3DArray>);
			
				double max_diff = std::max(
					std::max(normInf(num_term_atom1_grad - grad[iaction.getTerminalAtom1Index()]), normInf(num_term_atom2_grad - grad[iaction.getTerminalAtom2Index()])),
					std::max(normInf(num_ctr_atom1_grad - grad[iaction.getCenterAtom1Index()]), normInf(num_ctr_atom2_grad - grad[iaction.getCenterAtom2Index()])));

				BOOST_CHECK_MESSAGE((max_diff <= GRAD_DELTA_MAX), 
									"Gradient deviation too large for torsion interaction #" << iaction.getTerminalAtom1Index() << "(" << 
									getMOL2Name(mol.getAtom(iaction.getTerminalAtom1Index())) << ")-#" << iaction.getCenterAtom1Index() << "(" << 
									getMOL2Name(mol.getAtom(iaction.getCenterAtom1Index())) << ")-#" << iaction.getCenterAtom2Index() << "(" << 
									getMOL2Name(mol.getAtom(iaction.getCenterAtom2Index())) << ")-#" << iaction.getTerminalAtom2Index() << "(" << 
									getMOL2Name(mol.getAtom(iaction.getTerminalAtom2Index())) << ") of molecule #" << mol_idx << " (" << getName(mol) <<
									"): max. numerical/analytical grad. element deviation of " << max_diff << " > " << GRAD_DELTA_MAX);
			}
		}
    }
}

BOOST_AUTO_TEST_CASE(MMFF94VanDerWaalsGradientFunctionTest)
{
	const static double E_DELTA_MAX = 0.000000001;
	const static double GRAD_DELTA_MAX = 0.000001;

    using namespace CDPL;
    using namespace Testing;

    ForceField::MMFF94VanDerWaalsInteractionParameterizer parameterizer;
    ForceField::MMFF94VanDerWaalsInteractionData found_ia_data;
    Math::Vector3DArray coords;
	Math::Vector3DArray grad;
	Math::Vector3D num_atom1_grad;
	Math::Vector3D num_atom2_grad;

    for (std::size_t mol_idx = 0; mol_idx < MMFF94TestData::DYN_TEST_MOLECULES.size(); mol_idx++) {
		const Chem::Molecule& mol = *MMFF94TestData::DYN_TEST_MOLECULES[mol_idx];

		parameterizer.parameterize(mol, found_ia_data, true);

		coords.clear();
		get3DCoordinates(mol, coords);

		grad.resize(coords.getSize());

		for (std::size_t i = 0; i < found_ia_data.size(); i++) {
			const ForceField::MMFF94VanDerWaalsInteraction& iaction = found_ia_data[i];

			grad[iaction.getAtom1Index()].clear();
			grad[iaction.getAtom2Index()].clear();

			double energy = ForceField::calcMMFF94VanDerWaalsEnergy<double>(iaction, coords);
			double grad_energy = ForceField::calcMMFF94VanDerWaalsGradient<double>(iaction, coords, grad);

			BOOST_CHECK_MESSAGE(std::abs(grad_energy - energy) < E_DELTA_MAX, 
								"Energy mismatch for van der Waals interaction #" << iaction.getAtom1Index() << "(" << 
								getMOL2Name(mol.getAtom(iaction.getAtom1Index())) << ")-#" << iaction.getAtom2Index() << "(" << 
								getMOL2Name(mol.getAtom(iaction.getAtom2Index())) << ") of molecule #" << mol_idx << " (" << getName(mol) <<
								"): grad. func. energy " << grad_energy << " != " << energy);
			
			calcNumericalGradient(iaction, coords, iaction.getAtom1Index(), num_atom1_grad, 
								  static_cast<double (*)(const ForceField::MMFF94VanDerWaalsInteraction&, const Math::Vector3DArray&)>
								  (&ForceField::calcMMFF94VanDerWaalsEnergy<double, Math::Vector3DArray>));
			calcNumericalGradient(iaction, coords, iaction.getAtom2Index(), num_atom2_grad, 
								  static_cast<double (*)(const ForceField::MMFF94VanDerWaalsInteraction&, const Math::Vector3DArray&)>
								  (&ForceField::calcMMFF94VanDerWaalsEnergy<double, Math::Vector3DArray>));

			double max_diff = std::max(normInf(num_atom1_grad - grad[iaction.getAtom1Index()]), normInf(num_atom2_grad - grad[iaction.getAtom2Index()]));

			BOOST_CHECK_MESSAGE((max_diff <= GRAD_DELTA_MAX), 
								"Gradient deviation too large for van der Waals interaction #" << iaction.getAtom1Index() << "(" << 
								getMOL2Name(mol.getAtom(iaction.getAtom1Index())) << ")-#" << iaction.getAtom2Index() << "(" << 
								getMOL2Name(mol.getAtom(iaction.getAtom2Index())) << ") of molecule #" << mol_idx << " (" << getName(mol) <<
								"): max. numerical/analytical grad. element deviation of " << max_diff << " > " << GRAD_DELTA_MAX);
		}
    }
}

BOOST_AUTO_TEST_CASE(MMFF94ElectrostaticGradientFunctionTest)
{
	const static double E_DELTA_MAX = 0.000000001;
	const static double GRAD_DELTA_MAX = 0.000001;

    using namespace CDPL;
    using namespace Testing;

	ForceField::MMFF94ElectrostaticInteractionParameterizer parameterizer;
    ForceField::MMFF94ElectrostaticInteractionData found_ia_data;
    Math::Vector3DArray coords;
    Math::Vector3DArray grad;
	Math::Vector3D num_atom1_grad;
	Math::Vector3D num_atom2_grad;

    for (std::size_t mol_idx = 0; mol_idx < MMFF94TestData::DYN_TEST_MOLECULES.size(); mol_idx++) {
		Chem::Molecule& mol = *MMFF94TestData::DYN_TEST_MOLECULES[mol_idx];

		ForceField::calcMMFF94AtomCharges(mol, true, false);

		parameterizer.parameterize(mol, found_ia_data, true);

		coords.clear();
		get3DCoordinates(mol, coords);
		
		grad.resize(coords.getSize());

		for (std::size_t i = 0; i < found_ia_data.size(); i++) {
			const ForceField::MMFF94ElectrostaticInteraction& iaction = found_ia_data[i];

			grad[iaction.getAtom1Index()].clear();
			grad[iaction.getAtom2Index()].clear();

			double energy = ForceField::calcMMFF94ElectrostaticEnergy<double>(iaction, coords);
			double grad_energy = ForceField::calcMMFF94ElectrostaticGradient<double>(iaction, coords, grad);

			BOOST_CHECK_MESSAGE(std::abs(grad_energy - energy) < E_DELTA_MAX, 
								"Energy mismatch for electrostatic interaction #" << iaction.getAtom1Index() << "(" << 
								getMOL2Name(mol.getAtom(iaction.getAtom1Index())) << ")-#" << iaction.getAtom2Index() << "(" << 
								getMOL2Name(mol.getAtom(iaction.getAtom2Index())) << ") of molecule #" << mol_idx << " (" << getName(mol) <<
								"): grad. func. energy " << grad_energy << " != " << energy);
			
			calcNumericalGradient(iaction, coords, iaction.getAtom1Index(), num_atom1_grad, 
								  static_cast<double (*)(const ForceField::MMFF94ElectrostaticInteraction&, const Math::Vector3DArray&)>
								  (&ForceField::calcMMFF94ElectrostaticEnergy<double, Math::Vector3DArray>));
			calcNumericalGradient(iaction, coords, iaction.getAtom2Index(), num_atom2_grad, 
								  static_cast<double (*)(const ForceField::MMFF94ElectrostaticInteraction&, const Math::Vector3DArray&)>
								  (&ForceField::calcMMFF94ElectrostaticEnergy<double, Math::Vector3DArray>));

			double max_diff = std::max(normInf(num_atom1_grad - grad[iaction.getAtom1Index()]), normInf(num_atom2_grad - grad[iaction.getAtom2Index()]));

			BOOST_CHECK_MESSAGE((max_diff <= GRAD_DELTA_MAX), 
								"Gradient deviation too large for electrostatic interaction #" << iaction.getAtom1Index() << "(" << 
								getMOL2Name(mol.getAtom(iaction.getAtom1Index())) << ")-#" << iaction.getAtom2Index() << "(" << 
								getMOL2Name(mol.getAtom(iaction.getAtom2Index())) << ") of molecule #" << mol_idx << " (" << getName(mol) <<
								"): max. numerical/analytical grad. element deviation of " << max_diff << " > " << GRAD_DELTA_MAX);
		}
    }
}
