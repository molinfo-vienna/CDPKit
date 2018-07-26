/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * MMFF94AngleBendingAnalyzerTest.cpp 
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

#include "CDPL/ForceField/MMFF94StretchBendInteractionAnalyzer.hpp"
#include "CDPL/ForceField/MMFF94BondStretchingInteractionAnalyzer.hpp"
#include "CDPL/ForceField/MMFF94AngleBendingInteractionAnalyzer.hpp"
#include "CDPL/Chem/MolecularGraphFunctions.hpp"
#include "CDPL/Chem/AtomFunctions.hpp"

#include "MMFF94TestData.hpp"
#include "TestUtils.hpp"


BOOST_AUTO_TEST_CASE(MMFF94StretchBendInteractionAnalyzerTest)
{
	using namespace CDPL;

	MMFF94TestUtils::OptimolLogReader::StretchBendInteractionList iactions;

	ForceField::MMFF94AngleBendingInteractionAnalyzer ab_analyzer;
	ForceField::MMFF94BondStretchingInteractionAnalyzer bs_analyzer;
	ForceField::MMFF94StretchBendInteractionAnalyzer sb_analyzer;
	ForceField::MMFF94StretchBendInteractionList found_iactions;
	ForceField::MMFF94AngleBendingInteractionList ab_iactions;
	ForceField::MMFF94BondStretchingInteractionList bs_iactions;

	for (std::size_t mol_idx = 0; mol_idx <	MMFF94TestData::DYN_TEST_MOLECULES.size(); mol_idx++) {
		const Chem::Molecule& mol =	*MMFF94TestData::DYN_TEST_MOLECULES[mol_idx];
		const std::string& mol_name = getName(mol);

		BOOST_CHECK(MMFF94TestData::DYN_LOG_READER.getStretchBendInteractions(mol_name, iactions));

		bs_analyzer.analyze(mol, bs_iactions);
		ab_analyzer.analyze(mol, ab_iactions);
		sb_analyzer.analyze(mol, bs_iactions, ab_iactions, found_iactions);

		for (std::size_t i = 0; i < iactions.size(); i++) {
			bool iaction_found = false;
			std::size_t term_atom1_idx = TestUtils::getAtomIndex(mol, iactions[i].termAtom1Name);
			std::size_t term_atom2_idx = TestUtils::getAtomIndex(mol, iactions[i].termAtom2Name);

			for (std::size_t j = 0; j < found_iactions.getSize(); j++) {
				const ForceField::MMFF94StretchBendInteraction& iaction = found_iactions[j];

				if (iaction.getCenterAtomIndex() != iactions[i].ctrAtomIdx)
					continue;

				if ((iaction.getTerminalAtom1Index() == term_atom1_idx && iaction.getTerminalAtom2Index() == term_atom2_idx) ||
					(iaction.getTerminalAtom1Index() == term_atom2_idx && iaction.getTerminalAtom2Index() == term_atom1_idx)) {
		

					BOOST_CHECK_MESSAGE(iaction.getStretchBendTypeIndex() == iactions[i].ffClass, 
										"Stretch-bend type index mismatch for stretch-bend interaction #" << term_atom1_idx << "(" << 
										iactions[i].termAtom1Name << ")-#" << iactions[i].ctrAtomIdx << "(" << 
										getMOL2Name(mol.getAtom(iactions[i].ctrAtomIdx)) << ")-#" << term_atom2_idx << "(" << 
										iactions[i].termAtom2Name << ") of molecule #" << mol_idx << " (" << mol_name << "): " << 
										iaction.getStretchBendTypeIndex() << " != " << iactions[i].ffClass);

					if (iaction.getTerminalAtom1Index() == term_atom1_idx)
						BOOST_CHECK_MESSAGE(std::abs(iaction.getIJKForceConstant() - iactions[i].forceConst) < 0.0005, 
											"IJK force constant mismatch for stretch-bend interaction #" << term_atom1_idx << "(" << 
											iactions[i].termAtom1Name << ")-#" << iactions[i].ctrAtomIdx << "(" << 
											getMOL2Name(mol.getAtom(iactions[i].ctrAtomIdx)) << ")-#" << term_atom2_idx << "(" << 
											iactions[i].termAtom2Name << ") of molecule #" << mol_idx << " (" << mol_name << "): " << 
											iaction.getIJKForceConstant() << " != " << iactions[i].forceConst);

					else
						BOOST_CHECK_MESSAGE(std::abs(iaction.getKJIForceConstant() - iactions[i].forceConst) < 0.0005, 
											"KJI force constant mismatch for stretch-bend interaction #" << term_atom1_idx << "(" << 
											iactions[i].termAtom1Name << ")-#" << iactions[i].ctrAtomIdx << "(" << 
											getMOL2Name(mol.getAtom(iactions[i].ctrAtomIdx)) << ")-#" << term_atom2_idx << "(" << 
											iactions[i].termAtom2Name << ") of molecule #" << mol_idx << " (" << mol_name << "): " << 
											iaction.getKJIForceConstant() << " != " << iactions[i].forceConst);

					iaction_found = true;
					break;
				}
			}
		
			BOOST_CHECK_MESSAGE(iaction_found, "Stretch-bend interaction #" << term_atom1_idx << "(" << 
										iactions[i].termAtom1Name << ")-#" << iactions[i].ctrAtomIdx << "(" << 
										getMOL2Name(mol.getAtom(iactions[i].ctrAtomIdx)) << ")-#" << term_atom2_idx << "(" << 
										iactions[i].termAtom2Name << ") of molecule #" << mol_idx << " (" << mol_name << ") has not been found");
		}

		found_iactions.clear();
		bs_iactions.clear();
		ab_iactions.clear();
	}
}
