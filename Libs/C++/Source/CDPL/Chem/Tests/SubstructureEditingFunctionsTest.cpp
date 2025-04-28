/* 
 * SubstructureEditingFunctionsTest.cpp 
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
#include <string>
#include <fstream>

#include <boost/test/auto_unit_test.hpp>
#include <boost/tokenizer.hpp>

#include "CDPL/Chem/BasicMolecule.hpp"
#include "CDPL/Chem/MolecularGraphFunctions.hpp"
#include "CDPL/Chem/MoleculeFunctions.hpp"
#include "CDPL/Chem/UtilityFunctions.hpp"


BOOST_AUTO_TEST_CASE(SubstructureEditingFunctionsTest)
{
    using namespace CDPL;
    using namespace Chem;

    typedef boost::tokenizer<boost::char_separator<char> > Tokenizer;

    std::ifstream ifs(std::string(std::string(std::getenv("CDPKIT_TEST_DATA_DIR")) + "/SubstructureEditorTestData.txt").c_str());

    BOOST_CHECK(ifs);

    BasicMolecule edited_mol;
    std::string line;
    std::string search_ptns;
    std::string excl_ptns;
    std::string res_ptn;
    std::string res_smiles;
    
    while (std::getline(ifs, line)) {
        Tokenizer tokenizer(line, boost::char_separator<char>(" "));
        auto it = tokenizer.begin();
        auto num_srch_ptns = std::stoul(*it++);

        search_ptns.clear();
        
        for (std::size_t i = 0; i < num_srch_ptns; i++, ++it) {
            search_ptns += *it;
            search_ptns.push_back(' ');
        }
        
        auto num_excl_ptns = std::stoul(*it++);

        excl_ptns.clear();

        for (std::size_t i = 0; i < num_excl_ptns; i++, ++it) {
            excl_ptns += *it;
            excl_ptns.push_back('\n');
        }

        res_ptn = *it++;
        
        if (res_ptn == "-")
            continue;
        
        auto start_mol = parseSMILES(*it++);
        auto num_edits = std::stoul(*it++);

        // ------
        
        BOOST_CHECK(editSubstructures(*start_mol, edited_mol, search_ptns, res_ptn, excl_ptns) == num_edits);

        calcBasicProperties(edited_mol, false);
        generateSMILES(edited_mol, res_smiles, true);
   
        BOOST_CHECK(res_smiles == *it);

        // ------
        
        BOOST_CHECK(editSubstructures(*start_mol, search_ptns, res_ptn, excl_ptns) == num_edits);

        calcBasicProperties(*start_mol, false);
        generateSMILES(*start_mol, res_smiles, true);
        
        BOOST_CHECK(res_smiles == *it);
    }
}
