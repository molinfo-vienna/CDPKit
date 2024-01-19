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

    OptimolLogReader::AngleBendingInteractionList ia_list;

    ForceField::MMFF94AngleBendingInteractionParameterizer parameterizer;
    ForceField::MMFF94AngleBendingInteractionList found_ia_list;

    for (std::size_t mol_idx = 0; mol_idx <    MMFF94TestData::DYN_TEST_MOLECULES.size(); mol_idx++) {
        const Chem::Molecule& mol =    *MMFF94TestData::DYN_TEST_MOLECULES[mol_idx];
        const std::string& mol_name = getName(mol);

        BOOST_CHECK(MMFF94TestData::DYN_LOG_READER.getAngleBendingInteractions(mol_name, ia_list));

        parameterizer.parameterize(mol, found_ia_list, true);

        BOOST_CHECK_MESSAGE(found_ia_list.getSize() == ia_list.size(), "Angle bending interaction count mismatch for molecule #" << mol_idx << " (" << mol_name << "): " <<
                            found_ia_list.getSize() << " != " << ia_list.size());

        for (std::size_t i = 0; i < ia_list.size(); i++) {
            bool iaction_found = false;
            std::size_t term_atom1_idx = TestUtils::getAtomIndex(mol, ia_list[i].termAtom1Name);
            std::size_t term_atom2_idx = TestUtils::getAtomIndex(mol, ia_list[i].termAtom2Name);

            for (std::size_t j = 0; j < found_ia_list.getSize(); j++) {
                const ForceField::MMFF94AngleBendingInteraction& iaction = found_ia_list[j];

                if (iaction.getCenterAtomIndex() != ia_list[i].ctrAtomIdx)
                    continue;

                if ((iaction.getTerminalAtom1Index() == term_atom1_idx && iaction.getTerminalAtom2Index() == term_atom2_idx) ||
                    (iaction.getTerminalAtom1Index() == term_atom2_idx && iaction.getTerminalAtom2Index() == term_atom1_idx)) {
        
                    BOOST_CHECK_MESSAGE(iaction.getAngleTypeIndex() == ia_list[i].ffClass, 
                                        "Angle type index mismatch for angle bending interaction #" << term_atom1_idx << "(" << 
                                        ia_list[i].termAtom1Name << ")-#" << ia_list[i].ctrAtomIdx << "(" << 
                                        getMOL2Name(mol.getAtom(ia_list[i].ctrAtomIdx)) << ")-#" << term_atom2_idx << "(" << 
                                        ia_list[i].termAtom2Name << ") of molecule #" << mol_idx << " (" << mol_name << "): " << 
                                        iaction.getAngleTypeIndex() << " != " << ia_list[i].ffClass);
        
                    BOOST_CHECK_MESSAGE(std::abs(iaction.getReferenceAngle() - ia_list[i].refAngle) < 0.0005, 
                                        "Reference bond angle mismatch for angle bending interaction #" << term_atom1_idx << "(" << 
                                        ia_list[i].termAtom1Name << ")-#" << ia_list[i].ctrAtomIdx << "(" << 
                                        getMOL2Name(mol.getAtom(ia_list[i].ctrAtomIdx)) << ")-#" << term_atom2_idx << "(" << 
                                        ia_list[i].termAtom2Name << ") of molecule #" << mol_idx << " (" << mol_name << "): " << 
                                        iaction.getReferenceAngle() << " != " << ia_list[i].refAngle);
        
                    BOOST_CHECK_MESSAGE(std::abs(iaction.getForceConstant() - ia_list[i].forceConst) < 0.0005, 
                                        "Force constant mismatch for angle bending interaction #" << term_atom1_idx << "(" << 
                                        ia_list[i].termAtom1Name << ")-#" << ia_list[i].ctrAtomIdx << "(" << 
                                        getMOL2Name(mol.getAtom(ia_list[i].ctrAtomIdx)) << ")-#" << term_atom2_idx << "(" << 
                                        ia_list[i].termAtom2Name << ") of molecule #" << mol_idx << " (" << mol_name << "): " << 
                                        iaction.getForceConstant() << " != " << ia_list[i].forceConst);

                    iaction_found = true;
                    break;
                }
            }
        
            BOOST_CHECK_MESSAGE(iaction_found, "Angle bending interaction #" << term_atom1_idx << "(" << 
                                        ia_list[i].termAtom1Name << ")-#" << ia_list[i].ctrAtomIdx << "(" << 
                                        getMOL2Name(mol.getAtom(ia_list[i].ctrAtomIdx)) << ")-#" << term_atom2_idx << "(" << 
                                        ia_list[i].termAtom2Name << ") of molecule #" << mol_idx << " (" << mol_name << ") has not been found");
        }
    }
}
