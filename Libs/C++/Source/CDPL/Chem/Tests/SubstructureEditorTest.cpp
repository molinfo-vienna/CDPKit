/* 
 * SubstructureEditorTest.cpp 
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
#include "CDPL/Chem/UtilityFunctions.hpp"
#include "CDPL/Chem/SubstructureEditor.hpp"


BOOST_AUTO_TEST_CASE(SubstructureEditorTest)
{
    using namespace CDPL;
    using namespace Chem;

    typedef boost::tokenizer<boost::char_separator<char> > Tokenizer;

    std::ifstream ifs(std::string(std::string(std::getenv("CDPKIT_TEST_DATA_DIR")) + "/SubstructureEditorTestData.txt").c_str());

    BOOST_CHECK(ifs);

    BasicMolecule res_mol;
    SubstructureEditor editor;
    std::string line;
    std::string res_smiles;
    
    while (std::getline(ifs, line)) {
        Tokenizer tokenizer(line, boost::char_separator<char>(" "));
        auto it = tokenizer.begin();

        editor.clearSearchPatterns();
        editor.clearExcludePatterns();

        auto num_srch_ptns = std::stoul(*it++);
                
        for (std::size_t i = 0; i < num_srch_ptns; i++, ++it)
            editor.addSearchPattern(parseSMARTS(*it));
        
        BOOST_CHECK(num_srch_ptns == editor.getNumSearchPatterns());
        
        auto num_excl_ptns = std::stoul(*it++);

        for (std::size_t i = 0; i < num_excl_ptns; i++, ++it)
            editor.addExcludePattern(parseSMARTS(*it));

        BOOST_CHECK(num_excl_ptns == editor.getNumExcludePatterns());

        editor.setResultPattern(parseSMILES(*it++));

        auto start_mol = parseSMILES(*it++);
        auto num_edits = std::stoul(*it++);

        BOOST_CHECK(editor.edit(*start_mol, res_mol) == num_edits);

        calcBasicProperties(res_mol, false);
        generateSMILES(res_mol, res_smiles, true);

        //BOOST_TEST_MESSAGE("res_smiles:" << res_smiles);
        
        BOOST_CHECK(res_smiles == *it);

        BOOST_CHECK(editor.edit(*start_mol) == num_edits);

        calcBasicProperties(*start_mol, false);
        generateSMILES(*start_mol, res_smiles, true);
        
        BOOST_CHECK(res_smiles == *it);
    }
}
