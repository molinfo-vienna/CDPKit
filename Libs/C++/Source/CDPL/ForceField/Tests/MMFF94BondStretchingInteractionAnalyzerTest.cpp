/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * MMFF94BondStretchingAnalyzerTest.cpp 
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

#include <boost/test/auto_unit_test.hpp>

#include "CDPL/ForceField/MMFF94BondStretchingInteractionAnalyzer.hpp"
#include "CDPL/Chem/MolecularGraphFunctions.hpp"
#include "CDPL/Chem/AtomFunctions.hpp"

#include "MMFF94TestData.hpp"


BOOST_AUTO_TEST_CASE(MMFF94BondStretchingInteractionAnalyzerTest)
{
	using namespace CDPL;

	MMFF94TestUtils::OptimolLogReader::BondStretchingInteractionList iactions;

	ForceField::MMFF94BondStretchingInteractionAnalyzer analyzer;
	ForceField::MMFF94BondStretchingInteractionList found_iactions;

	for (std::size_t mol_idx = 0; mol_idx <	MMFF94TestData::DYN_TEST_MOLECULES.size(); mol_idx++) {
		const Chem::Molecule& mol =	*MMFF94TestData::DYN_TEST_MOLECULES[mol_idx];
		const std::string& mol_name = getName(mol);

		BOOST_CHECK(MMFF94TestData::DYN_LOG_READER.getBondStretchingInteractions(mol_name, iactions));

		analyzer.analyze(mol, found_iactions);

		BOOST_CHECK_MESSAGE(found_iactions.getSize() == iactions.size(), "Bond stretching interaction count mismatch for molecule #" << mol_idx << " (" << mol_name << "): " <<
							found_iactions.getSize() << " != " << iactions.size());

		for (std::size_t i = 0; i < iactions.size(); i++) {
			bool iaction_found = false;

			for (std::size_t j = 0; j < found_iactions.getSize(); j++) {
				const ForceField::MMFF94BondStretchingInteraction& iaction = found_iactions[j];

				if ((iaction.getAtom1Index() == iactions[i].atom1Idx && iaction.getAtom2Index() == iactions[i].atom2Idx) ||
					(iaction.getAtom1Index() == iactions[i].atom2Idx && iaction.getAtom2Index() == iactions[i].atom1Idx)) {
		
					BOOST_CHECK_MESSAGE(iaction.getBondTypeIndex() == iactions[i].ffClass, 
										"Bond type index mismatch for bond stretching interaction #" << iactions[i].atom1Idx << "(" << 
										getMOL2Name(mol.getAtom(iactions[i].atom1Idx)) << ")-#" << iactions[i].atom2Idx << "(" << 
										getMOL2Name(mol.getAtom(iactions[i].atom2Idx)) << ") of molecule #" << mol_idx << " (" << mol_name <<
										"): " << iaction.getBondTypeIndex() << " != " << iactions[i].ffClass);
		
					BOOST_CHECK_MESSAGE(std::abs(iaction.getReferenceLength() - iactions[i].refLength) < 0.0005, 
										"Reference bond length mismatch for bond stretching interaction #" << iactions[i].atom1Idx << "(" << 
										getMOL2Name(mol.getAtom(iactions[i].atom1Idx)) << ")-#" << iactions[i].atom2Idx << "(" << 
										getMOL2Name(mol.getAtom(iactions[i].atom2Idx)) << ") of molecule #" << mol_idx << " (" << mol_name <<
										"): " << iaction.getReferenceLength() << " != " << iactions[i].refLength);
		
					BOOST_CHECK_MESSAGE(std::abs(iaction.getForceConstant() - iactions[i].forceConst) < 0.0005, 
										"Force constant mismatch for bond stretching interaction #" << iactions[i].atom1Idx << "(" << 
										getMOL2Name(mol.getAtom(iactions[i].atom1Idx)) << ")-#" << iactions[i].atom2Idx << "(" << 
										getMOL2Name(mol.getAtom(iactions[i].atom2Idx)) << ") of molecule #" << mol_idx << " (" << mol_name <<
										"): " << iaction.getForceConstant() << " != " << iactions[i].forceConst);

					iaction_found = true;
					break;
				}
			}
		
			BOOST_CHECK_MESSAGE(iaction_found, "Bond stretching interaction #" << iactions[i].atom1Idx << "(" << getMOL2Name(mol.getAtom(iactions[i].atom1Idx)) << 
								")-#" << iactions[i].atom2Idx << "(" << getMOL2Name(mol.getAtom(iactions[i].atom2Idx)) << ") of molecule #" << mol_idx << " (" << mol_name <<
								") has not been found");
		}
	
		found_iactions.clear();
	}
}
