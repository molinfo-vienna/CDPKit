/* 
 * MMFF94VanDerWaalsParameterizerTest.cpp 
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

#include "CDPL/ForceField/MMFF94VanDerWaalsInteractionParameterizer.hpp"
#include "CDPL/Chem/MolecularGraphFunctions.hpp"
#include "CDPL/Chem/AtomFunctions.hpp"

#include "MMFF94TestData.hpp"


BOOST_AUTO_TEST_CASE(MMFF94VanDerWaalsInteractionParameterizerTest)
{
    using namespace CDPL;
    using namespace Testing;

    OptimolLogReader::VanDerWaalsInteractionData ia_data;

    ForceField::MMFF94VanDerWaalsInteractionParameterizer parameterizer;
    ForceField::MMFF94VanDerWaalsInteractionData found_ia_data;

    for (std::size_t mol_idx = 0; mol_idx <    MMFF94TestData::DYN_TEST_MOLECULES.size(); mol_idx++) {
        const Chem::Molecule& mol =    *MMFF94TestData::DYN_TEST_MOLECULES[mol_idx];
        const std::string& mol_name = getName(mol);

        BOOST_CHECK(MMFF94TestData::DYN_LOG_READER.getVanDerWaalsInteractions(mol_name, ia_data));

        parameterizer.parameterize(mol, found_ia_data, true);

        //BOOST_CHECK_MESSAGE(found_ia_data.getSize() == ia_data.size(), "Van der Waals interaction count mismatch for molecule #" << mol_idx << " (" << mol_name << "): " <<
        //                    found_ia_data.getSize() << " != " << ia_data.size());

        for (std::size_t i = 0; i < ia_data.size(); i++) {
            bool iaction_found = false;

            for (std::size_t j = 0; j < found_ia_data.getSize(); j++) {
                const ForceField::MMFF94VanDerWaalsInteraction& iaction = found_ia_data[j];

                if ((iaction.getAtom1Index() == ia_data[i].atom1Idx && iaction.getAtom2Index() == ia_data[i].atom2Idx) ||
                    (iaction.getAtom1Index() == ia_data[i].atom2Idx && iaction.getAtom2Index() == ia_data[i].atom1Idx)) {
        
                    iaction_found = true;
                    break;
                }
            }
        
            BOOST_CHECK_MESSAGE(iaction_found, "Van der Waals interaction #" << ia_data[i].atom1Idx << "(" << getMOL2Name(mol.getAtom(ia_data[i].atom1Idx)) << 
                                ")-#" << ia_data[i].atom2Idx << "(" << getMOL2Name(mol.getAtom(ia_data[i].atom2Idx)) << ") of molecule #" << mol_idx << " (" << mol_name <<
                                ") has not been found");
        }
    }
}
