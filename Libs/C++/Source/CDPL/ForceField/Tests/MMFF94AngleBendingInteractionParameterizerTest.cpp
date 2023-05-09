/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * MMFF94AngleBendingParameterizerTest.cpp 
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

#include "CDPL/ForceField/MMFF94AngleBendingInteractionParameterizer.hpp"
#include "CDPL/Chem/MolecularGraphFunctions.hpp"
#include "CDPL/Chem/AtomFunctions.hpp"

#include "MMFF94TestData.hpp"
#include "TestUtils.hpp"


BOOST_AUTO_TEST_CASE(MMFF94AngleBendingInteractionParameterizerTest)
{
	using namespace CDPL;
	using namespace Testing;

	OptimolLogReader::AngleBendingInteractionData ia_data;

	ForceField::MMFF94AngleBendingInteractionParameterizer parameterizer;
	ForceField::MMFF94AngleBendingInteractionData found_ia_data;

	for (std::size_t mol_idx = 0; mol_idx <	MMFF94TestData::DYN_TEST_MOLECULES.size(); mol_idx++) {
		const Chem::Molecule& mol =	*MMFF94TestData::DYN_TEST_MOLECULES[mol_idx];
		const std::string& mol_name = getName(mol);

		BOOST_CHECK(MMFF94TestData::DYN_LOG_READER.getAngleBendingInteractions(mol_name, ia_data));

		parameterizer.parameterize(mol, found_ia_data, true);

		BOOST_CHECK_MESSAGE(found_ia_data.getSize() == ia_data.size(), "Angle bending interaction count mismatch for molecule #" << mol_idx << " (" << mol_name << "): " <<
							found_ia_data.getSize() << " != " << ia_data.size());

		for (std::size_t i = 0; i < ia_data.size(); i++) {
			bool iaction_found = false;
			std::size_t term_atom1_idx = TestUtils::getAtomIndex(mol, ia_data[i].termAtom1Name);
			std::size_t term_atom2_idx = TestUtils::getAtomIndex(mol, ia_data[i].termAtom2Name);

			for (std::size_t j = 0; j < found_ia_data.getSize(); j++) {
				const ForceField::MMFF94AngleBendingInteraction& iaction = found_ia_data[j];

				if (iaction.getCenterAtomIndex() != ia_data[i].ctrAtomIdx)
					continue;

				if ((iaction.getTerminalAtom1Index() == term_atom1_idx && iaction.getTerminalAtom2Index() == term_atom2_idx) ||
					(iaction.getTerminalAtom1Index() == term_atom2_idx && iaction.getTerminalAtom2Index() == term_atom1_idx)) {
		
					BOOST_CHECK_MESSAGE(iaction.getAngleTypeIndex() == ia_data[i].ffClass, 
										"Angle type index mismatch for angle bending interaction #" << term_atom1_idx << "(" << 
										ia_data[i].termAtom1Name << ")-#" << ia_data[i].ctrAtomIdx << "(" << 
										getMOL2Name(mol.getAtom(ia_data[i].ctrAtomIdx)) << ")-#" << term_atom2_idx << "(" << 
										ia_data[i].termAtom2Name << ") of molecule #" << mol_idx << " (" << mol_name << "): " << 
										iaction.getAngleTypeIndex() << " != " << ia_data[i].ffClass);
		
					BOOST_CHECK_MESSAGE(std::abs(iaction.getReferenceAngle() - ia_data[i].refAngle) < 0.0005, 
										"Reference bond angle mismatch for angle bending interaction #" << term_atom1_idx << "(" << 
										ia_data[i].termAtom1Name << ")-#" << ia_data[i].ctrAtomIdx << "(" << 
										getMOL2Name(mol.getAtom(ia_data[i].ctrAtomIdx)) << ")-#" << term_atom2_idx << "(" << 
										ia_data[i].termAtom2Name << ") of molecule #" << mol_idx << " (" << mol_name << "): " << 
										iaction.getReferenceAngle() << " != " << ia_data[i].refAngle);
		
					BOOST_CHECK_MESSAGE(std::abs(iaction.getForceConstant() - ia_data[i].forceConst) < 0.0005, 
										"Force constant mismatch for angle bending interaction #" << term_atom1_idx << "(" << 
										ia_data[i].termAtom1Name << ")-#" << ia_data[i].ctrAtomIdx << "(" << 
										getMOL2Name(mol.getAtom(ia_data[i].ctrAtomIdx)) << ")-#" << term_atom2_idx << "(" << 
										ia_data[i].termAtom2Name << ") of molecule #" << mol_idx << " (" << mol_name << "): " << 
										iaction.getForceConstant() << " != " << ia_data[i].forceConst);

					iaction_found = true;
					break;
				}
			}
		
			BOOST_CHECK_MESSAGE(iaction_found, "Angle bending interaction #" << term_atom1_idx << "(" << 
										ia_data[i].termAtom1Name << ")-#" << ia_data[i].ctrAtomIdx << "(" << 
										getMOL2Name(mol.getAtom(ia_data[i].ctrAtomIdx)) << ")-#" << term_atom2_idx << "(" << 
										ia_data[i].termAtom2Name << ") of molecule #" << mol_idx << " (" << mol_name << ") has not been found");
		}
	}
}
