/* 
 * MMFF94AtomTyperTest.cpp 
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

#include <boost/test/auto_unit_test.hpp>

#include "CDPL/ForceField/MMFF94AtomTyper.hpp"
#include "CDPL/Chem/MolecularGraphFunctions.hpp"
#include "CDPL/Chem/AtomFunctions.hpp"

#include "MMFF94TestData.hpp"


BOOST_AUTO_TEST_CASE(MMFF94AtomTyperTest)
{
    using namespace CDPL;
    using namespace Testing;

    OptimolLogReader::SymbolicAtomTypeArray sym_types;
    OptimolLogReader::NumericAtomTypeArray num_types;

    ForceField::MMFF94AtomTyper atom_typer;
    Util::UIArray perc_num_types;
    Util::SArray perc_sym_types;

    for (std::size_t mol_idx = 0; mol_idx <    MMFF94TestData::DYN_TEST_MOLECULES.size(); mol_idx++) {
        const Chem::Molecule& mol =    *MMFF94TestData::DYN_TEST_MOLECULES[mol_idx];
        const std::string& mol_name = getName(mol);

        BOOST_CHECK(MMFF94TestData::DYN_LOG_READER.getSymbolicAtomTypes(mol_name, sym_types));
        BOOST_CHECK_EQUAL(sym_types.size(), mol.getNumAtoms());

        BOOST_CHECK(MMFF94TestData::DYN_LOG_READER.getNumericAtomTypes(mol_name, num_types));
        BOOST_CHECK_EQUAL(num_types.size(), mol.getNumAtoms());

        atom_typer.perceiveTypes(mol, perc_sym_types, perc_num_types, true);

        for (std::size_t i = 0; i < mol.getNumAtoms(); i++) {
            const std::string& correct_type = sym_types[i];
            const std::string& perceived_type = perc_sym_types[i];

            BOOST_CHECK_MESSAGE(perceived_type == correct_type, "Symbolic atom type mismatch for atom #" << i << "(" << getMOL2Name(mol.getAtom(i)) << 
                                ") of molecule #" << mol_idx << " (" << mol_name << "): " << perceived_type << " != " << correct_type);
        }
            
        for (std::size_t i = 0; i < mol.getNumAtoms(); i++) {
            unsigned int correct_type = num_types[i];
            unsigned int perceived_type = perc_num_types[i];

            BOOST_CHECK_MESSAGE(perceived_type == correct_type, "Numeric atom type mismatch for atom #" << i << "(" << getMOL2Name(mol.getAtom(i)) << 
                                ") of molecule #" << mol_idx << " (" << mol_name << "): " << perceived_type << " != " << correct_type);
        }
    }
}
