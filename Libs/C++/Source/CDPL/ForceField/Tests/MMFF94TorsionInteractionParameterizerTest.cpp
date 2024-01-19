/* 
 * MMFF94TorsionInteractionParameterizerTest.cpp 
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

#include "CDPL/ForceField/MMFF94TorsionInteractionParameterizer.hpp"
#include "CDPL/ForceField/MMFF94TorsionParameterTable.hpp"
#include "CDPL/Chem/MolecularGraphFunctions.hpp"
#include "CDPL/Chem/AtomFunctions.hpp"

#include "MMFF94TestData.hpp"
#include "TestUtils.hpp"


namespace
{

    void performTesting(const Testing::MMFF94TestData::MoleculeList& mols, Testing::OptimolLogReader& log_reader, bool stat)
    {
        using namespace CDPL;
        using namespace Testing;

        OptimolLogReader::TorsionInteractionList ia_list;
        ForceField::MMFF94TorsionInteractionParameterizer parameterizer;
        ForceField::MMFF94TorsionInteractionList found_ia_list;

        parameterizer.setTorsionParameterTable(ForceField::MMFF94TorsionParameterTable::get(stat));

        for (std::size_t mol_idx = 0; mol_idx <    mols.size(); mol_idx++) {
            const Chem::Molecule& mol =    *mols[mol_idx];
            const std::string& mol_name = getName(mol);

            BOOST_CHECK(log_reader.getTorsionInteractions(mol_name, ia_list));

            parameterizer.parameterize(mol, found_ia_list, true);

            BOOST_CHECK_MESSAGE(found_ia_list.getSize() == ia_list.size(), "Torsion interaction count mismatch for molecule #" << mol_idx << " (" << mol_name << "): " <<
                                found_ia_list.getSize() << " != " << ia_list.size());

            for (std::size_t i = 0; i < ia_list.size(); i++) {
                bool iaction_found = false;
                std::size_t term_atom1_idx = TestUtils::getAtomIndex(mol, ia_list[i].termAtom1Name);
                std::size_t term_atom2_idx = TestUtils::getAtomIndex(mol, ia_list[i].termAtom2Name);

                for (std::size_t j = 0; j < found_ia_list.getSize(); j++) {
                    const ForceField::MMFF94TorsionInteraction& iaction = found_ia_list[j];

                    if (!((iaction.getTerminalAtom1Index() == term_atom1_idx && iaction.getCenterAtom1Index() == ia_list[i].ctrAtom1Idx && 
                         iaction.getCenterAtom2Index() == ia_list[i].ctrAtom2Idx && iaction.getTerminalAtom2Index() == term_atom2_idx) ||
                        (iaction.getTerminalAtom2Index() == term_atom1_idx && iaction.getCenterAtom2Index() == ia_list[i].ctrAtom1Idx && 
                         iaction.getCenterAtom1Index() == ia_list[i].ctrAtom2Idx && iaction.getTerminalAtom1Index() == term_atom2_idx)))
                        continue;

                    BOOST_CHECK_MESSAGE(iaction.getTorsionTypeIndex() == ia_list[i].ffClass, 
                                        "Torsion type index mismatch for torsion interaction #" << term_atom1_idx << "(" << 
                                        ia_list[i].termAtom1Name << ")-#" << ia_list[i].ctrAtom1Idx << "(" << 
                                        getMOL2Name(mol.getAtom(ia_list[i].ctrAtom1Idx)) << ")-#" << ia_list[i].ctrAtom2Idx << "(" << 
                                        getMOL2Name(mol.getAtom(ia_list[i].ctrAtom2Idx)) << ")-#" << term_atom2_idx << "(" << 
                                        ia_list[i].termAtom2Name << ") of molecule #" << mol_idx << 
                                        " (" << mol_name << "): " << iaction.getTorsionTypeIndex() << " != " << ia_list[i].ffClass);

                    BOOST_CHECK_MESSAGE(std::abs(iaction.getTorsionParameter1() - ia_list[i].torParams[0]) < 0.0005, 
                                        "Torsion parameter V1 mismatch for torsion interaction #" << term_atom1_idx << "(" << 
                                        ia_list[i].termAtom1Name << ")-#" << ia_list[i].ctrAtom1Idx << "(" << 
                                        getMOL2Name(mol.getAtom(ia_list[i].ctrAtom1Idx)) << ")-#" << ia_list[i].ctrAtom2Idx << "(" << 
                                        getMOL2Name(mol.getAtom(ia_list[i].ctrAtom2Idx)) << ")-#" << term_atom2_idx << "(" << 
                                        ia_list[i].termAtom2Name << ") of molecule #" << mol_idx << 
                                        " (" << mol_name << "): " << iaction.getTorsionParameter1() << " != " << ia_list[i].torParams[0]);
    
                    BOOST_CHECK_MESSAGE(std::abs(iaction.getTorsionParameter2() - ia_list[i].torParams[1]) < 0.0005, 
                                        "Torsion parameter V2 mismatch for torsion interaction #" << term_atom1_idx << "(" << 
                                        ia_list[i].termAtom1Name << ")-#" << ia_list[i].ctrAtom1Idx << "(" << 
                                        getMOL2Name(mol.getAtom(ia_list[i].ctrAtom1Idx)) << ")-#" << ia_list[i].ctrAtom2Idx << "(" << 
                                        getMOL2Name(mol.getAtom(ia_list[i].ctrAtom2Idx)) << ")-#" << term_atom2_idx << "(" << 
                                        ia_list[i].termAtom2Name << ") of molecule #" << mol_idx << 
                                        " (" << mol_name << "): " << iaction.getTorsionParameter2() << " != " << ia_list[i].torParams[1]);
    
                    BOOST_CHECK_MESSAGE(std::abs(iaction.getTorsionParameter3() - ia_list[i].torParams[2]) < 0.0005, 
                                        "Torsion parameter V3 mismatch for torsion interaction #" << term_atom1_idx << "(" << 
                                        ia_list[i].termAtom1Name << ")-#" << ia_list[i].ctrAtom1Idx << "(" << 
                                        getMOL2Name(mol.getAtom(ia_list[i].ctrAtom1Idx)) << ")-#" << ia_list[i].ctrAtom2Idx << "(" << 
                                        getMOL2Name(mol.getAtom(ia_list[i].ctrAtom2Idx)) << ")-#" << term_atom2_idx << "(" << 
                                        ia_list[i].termAtom2Name << ") of molecule #" << mol_idx << 
                                        " (" << mol_name << "): " << iaction.getTorsionParameter3() << " != " << ia_list[i].torParams[2]);

                    iaction_found = true;
                    break;
                }
        
                BOOST_CHECK_MESSAGE(iaction_found, "Torsion interaction #" << term_atom1_idx << "(" << 
                                    ia_list[i].termAtom1Name << ")-#" << ia_list[i].ctrAtom1Idx << "(" << 
                                    getMOL2Name(mol.getAtom(ia_list[i].ctrAtom1Idx)) << ")-#" << ia_list[i].ctrAtom2Idx << "(" << 
                                    getMOL2Name(mol.getAtom(ia_list[i].ctrAtom2Idx)) << ")-#" << term_atom2_idx << "(" << 
                                    ia_list[i].termAtom2Name << ") of molecule #" << mol_idx << 
                                    " (" << mol_name << ") has not been found");
            }
        }
    }
}


BOOST_AUTO_TEST_CASE(MMFF94TorsionInteractionParameterizerTest)
{
    using namespace CDPL;
    using namespace Testing;

    performTesting(MMFF94TestData::DYN_TEST_MOLECULES, MMFF94TestData::DYN_LOG_READER, false);
    performTesting(MMFF94TestData::STAT_TEST_MOLECULES, MMFF94TestData::STAT_LOG_READER, true);
}
