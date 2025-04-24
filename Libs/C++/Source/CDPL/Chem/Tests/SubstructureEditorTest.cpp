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

    BasicMolecule edited_mol;
    SubstructureEditor editor;
    std::string line;
    std::string res_smiles;
    
    while (std::getline(ifs, line)) {
        Tokenizer tokenizer(line, boost::char_separator<char>(" "));
        auto it = tokenizer.begin();

        editor.clear();

        BOOST_CHECK(editor.getNumSearchPatterns() == 0);
        BOOST_CHECK(const_cast<SubstructureEditor&>(editor).getSearchPatternsBegin() == const_cast<SubstructureEditor&>(editor).getSearchPatternsEnd());
        BOOST_CHECK(const_cast<const SubstructureEditor&>(editor).getSearchPatternsBegin() == const_cast<const SubstructureEditor&>(editor).getSearchPatternsEnd());
        BOOST_CHECK((const_cast<SubstructureEditor&>(editor).getSearchPatternsEnd() - const_cast<SubstructureEditor&>(editor).getSearchPatternsBegin()) == 0);
        BOOST_CHECK((const_cast<const SubstructureEditor&>(editor).getSearchPatternsEnd() - const_cast<const SubstructureEditor&>(editor).getSearchPatternsBegin()) == 0);

        BOOST_CHECK(editor.getNumExcludePatterns() == 0);
        BOOST_CHECK(const_cast<SubstructureEditor&>(editor).getExcludePatternsBegin() == const_cast<SubstructureEditor&>(editor).getExcludePatternsEnd());
        BOOST_CHECK(const_cast<const SubstructureEditor&>(editor).getExcludePatternsBegin() == const_cast<const SubstructureEditor&>(editor).getExcludePatternsEnd());
        BOOST_CHECK((const_cast<SubstructureEditor&>(editor).getExcludePatternsEnd() - const_cast<SubstructureEditor&>(editor).getExcludePatternsBegin()) == 0);
        BOOST_CHECK((const_cast<const SubstructureEditor&>(editor).getExcludePatternsEnd() - const_cast<const SubstructureEditor&>(editor).getExcludePatternsBegin()) == 0);

        BOOST_CHECK(!editor.getResultPattern());

        auto num_srch_ptns = std::stoul(*it++);
                
        for (std::size_t i = 0; i < num_srch_ptns; i++, ++it)
            editor.addSearchPattern(parseSMARTS(*it));
        
        BOOST_CHECK(num_srch_ptns == editor.getNumSearchPatterns());

        if (num_srch_ptns > 0) {
            BOOST_CHECK(const_cast<SubstructureEditor&>(editor).getSearchPatternsBegin() != const_cast<SubstructureEditor&>(editor).getSearchPatternsEnd());
            BOOST_CHECK(const_cast<const SubstructureEditor&>(editor).getSearchPatternsBegin() != const_cast<const SubstructureEditor&>(editor).getSearchPatternsEnd());
        } else {
            BOOST_CHECK(const_cast<SubstructureEditor&>(editor).getSearchPatternsBegin() == const_cast<SubstructureEditor&>(editor).getSearchPatternsEnd());
            BOOST_CHECK(const_cast<const SubstructureEditor&>(editor).getSearchPatternsBegin() == const_cast<const SubstructureEditor&>(editor).getSearchPatternsEnd());
        }
        
        BOOST_CHECK(std::size_t(const_cast<SubstructureEditor&>(editor).getSearchPatternsEnd() - const_cast<SubstructureEditor&>(editor).getSearchPatternsBegin()) == editor.getNumSearchPatterns());
        BOOST_CHECK(std::size_t(const_cast<const SubstructureEditor&>(editor).getSearchPatternsEnd() - const_cast<const SubstructureEditor&>(editor).getSearchPatternsBegin()) == editor.getNumSearchPatterns());
   
        auto num_excl_ptns = std::stoul(*it++);

        for (std::size_t i = 0; i < num_excl_ptns; i++, ++it)
            editor.addExcludePattern(parseSMARTS(*it));

        BOOST_CHECK(num_excl_ptns == editor.getNumExcludePatterns());

        if (num_excl_ptns > 0) {
            BOOST_CHECK(const_cast<SubstructureEditor&>(editor).getExcludePatternsBegin() != const_cast<SubstructureEditor&>(editor).getExcludePatternsEnd());
            BOOST_CHECK(const_cast<const SubstructureEditor&>(editor).getExcludePatternsBegin() != const_cast<const SubstructureEditor&>(editor).getExcludePatternsEnd());
        } else {
            BOOST_CHECK(const_cast<SubstructureEditor&>(editor).getExcludePatternsBegin() == const_cast<SubstructureEditor&>(editor).getExcludePatternsEnd());
            BOOST_CHECK(const_cast<const SubstructureEditor&>(editor).getExcludePatternsBegin() == const_cast<const SubstructureEditor&>(editor).getExcludePatternsEnd());
        }
        
        BOOST_CHECK(std::size_t(const_cast<SubstructureEditor&>(editor).getExcludePatternsEnd() - const_cast<SubstructureEditor&>(editor).getExcludePatternsBegin()) == editor.getNumExcludePatterns());
        BOOST_CHECK(std::size_t(const_cast<const SubstructureEditor&>(editor).getExcludePatternsEnd() - const_cast<const SubstructureEditor&>(editor).getExcludePatternsBegin()) == editor.getNumExcludePatterns());

        if (*it == "-") {
            ++it;
            editor.setResultPattern(MolecularGraph::SharedPointer());

            BOOST_CHECK(!editor.getResultPattern());    

        } else {
            editor.setResultPattern(parseSMILES(*it++));
            
            BOOST_CHECK(editor.getResultPattern());    
        }
        
        auto start_mol = parseSMILES(*it++);
        auto num_edits = std::stoul(*it++);

        // ------
        
        BOOST_CHECK(editor.edit(*start_mol, edited_mol) == num_edits);

        calcBasicProperties(edited_mol, false);
        generateSMILES(edited_mol, res_smiles, true);

        //BOOST_TEST_MESSAGE("edit result: " << res_smiles);
        
        BOOST_CHECK(res_smiles == *it);

        // ------
        
        BOOST_CHECK(editor.edit(*start_mol) == num_edits);

        calcBasicProperties(*start_mol, false);
        generateSMILES(*start_mol, res_smiles, true);
        
        BOOST_CHECK(res_smiles == *it);
    }

    // ------

    editor.clearSearchPatterns();

    BOOST_CHECK(editor.getNumSearchPatterns() == 0);
    BOOST_CHECK(const_cast<SubstructureEditor&>(editor).getSearchPatternsBegin() == const_cast<SubstructureEditor&>(editor).getSearchPatternsEnd());
    BOOST_CHECK(const_cast<const SubstructureEditor&>(editor).getSearchPatternsBegin() == const_cast<const SubstructureEditor&>(editor).getSearchPatternsEnd());
    BOOST_CHECK((const_cast<SubstructureEditor&>(editor).getSearchPatternsEnd() - const_cast<SubstructureEditor&>(editor).getSearchPatternsBegin()) == 0);
    BOOST_CHECK((const_cast<const SubstructureEditor&>(editor).getSearchPatternsEnd() - const_cast<const SubstructureEditor&>(editor).getSearchPatternsBegin()) == 0);
    
    editor.clearExcludePatterns();

    BOOST_CHECK(editor.getNumExcludePatterns() == 0);
    BOOST_CHECK(const_cast<SubstructureEditor&>(editor).getExcludePatternsBegin() == const_cast<SubstructureEditor&>(editor).getExcludePatternsEnd());
    BOOST_CHECK(const_cast<const SubstructureEditor&>(editor).getExcludePatternsBegin() == const_cast<const SubstructureEditor&>(editor).getExcludePatternsEnd());
    BOOST_CHECK((const_cast<SubstructureEditor&>(editor).getExcludePatternsEnd() - const_cast<SubstructureEditor&>(editor).getExcludePatternsBegin()) == 0);
    BOOST_CHECK((const_cast<const SubstructureEditor&>(editor).getExcludePatternsEnd() - const_cast<const SubstructureEditor&>(editor).getExcludePatternsBegin()) == 0);

    editor.setResultPattern(MolecularGraph::SharedPointer());

    BOOST_CHECK(!editor.getResultPattern());

    // ------
    
    SubstructureEditor editor1;

    BOOST_CHECK(editor1.getNumSearchPatterns() == 0);
    BOOST_CHECK(const_cast<SubstructureEditor&>(editor1).getSearchPatternsBegin() == const_cast<SubstructureEditor&>(editor1).getSearchPatternsEnd());
    BOOST_CHECK(const_cast<const SubstructureEditor&>(editor1).getSearchPatternsBegin() == const_cast<const SubstructureEditor&>(editor1).getSearchPatternsEnd());
    BOOST_CHECK((const_cast<SubstructureEditor&>(editor1).getSearchPatternsEnd() - const_cast<SubstructureEditor&>(editor1).getSearchPatternsBegin()) == 0);
    BOOST_CHECK((const_cast<const SubstructureEditor&>(editor1).getSearchPatternsEnd() - const_cast<const SubstructureEditor&>(editor1).getSearchPatternsBegin()) == 0);

    BOOST_CHECK(editor1.getNumExcludePatterns() == 0);
    BOOST_CHECK(const_cast<SubstructureEditor&>(editor1).getExcludePatternsBegin() == const_cast<SubstructureEditor&>(editor1).getExcludePatternsEnd());
    BOOST_CHECK(const_cast<const SubstructureEditor&>(editor1).getExcludePatternsBegin() == const_cast<const SubstructureEditor&>(editor1).getExcludePatternsEnd());
    BOOST_CHECK((const_cast<SubstructureEditor&>(editor1).getExcludePatternsEnd() - const_cast<SubstructureEditor&>(editor1).getExcludePatternsBegin()) == 0);
    BOOST_CHECK((const_cast<const SubstructureEditor&>(editor1).getExcludePatternsEnd() - const_cast<const SubstructureEditor&>(editor1).getExcludePatternsBegin()) == 0);

    BOOST_CHECK(!editor1.getResultPattern());

    // ------

    editor1 = editor;

    BOOST_CHECK(editor1.getNumSearchPatterns() == 0);
    BOOST_CHECK(const_cast<SubstructureEditor&>(editor1).getSearchPatternsBegin() == const_cast<SubstructureEditor&>(editor1).getSearchPatternsEnd());
    BOOST_CHECK(const_cast<const SubstructureEditor&>(editor1).getSearchPatternsBegin() == const_cast<const SubstructureEditor&>(editor1).getSearchPatternsEnd());
    BOOST_CHECK((const_cast<SubstructureEditor&>(editor1).getSearchPatternsEnd() - const_cast<SubstructureEditor&>(editor1).getSearchPatternsBegin()) == 0);
    BOOST_CHECK((const_cast<const SubstructureEditor&>(editor1).getSearchPatternsEnd() - const_cast<const SubstructureEditor&>(editor1).getSearchPatternsBegin()) == 0);

    BOOST_CHECK(editor1.getNumExcludePatterns() == 0);
    BOOST_CHECK(const_cast<SubstructureEditor&>(editor1).getExcludePatternsBegin() == const_cast<SubstructureEditor&>(editor1).getExcludePatternsEnd());
    BOOST_CHECK(const_cast<const SubstructureEditor&>(editor1).getExcludePatternsBegin() == const_cast<const SubstructureEditor&>(editor1).getExcludePatternsEnd());
    BOOST_CHECK((const_cast<SubstructureEditor&>(editor1).getExcludePatternsEnd() - const_cast<SubstructureEditor&>(editor1).getExcludePatternsBegin()) == 0);
    BOOST_CHECK((const_cast<const SubstructureEditor&>(editor1).getExcludePatternsEnd() - const_cast<const SubstructureEditor&>(editor1).getExcludePatternsBegin()) == 0);

    BOOST_CHECK(!editor1.getResultPattern());

    // ------
    
    SubstructureEditor editor2(editor);

    BOOST_CHECK(editor2.getNumSearchPatterns() == 0);
    BOOST_CHECK(const_cast<SubstructureEditor&>(editor2).getSearchPatternsBegin() == const_cast<SubstructureEditor&>(editor2).getSearchPatternsEnd());
    BOOST_CHECK(const_cast<const SubstructureEditor&>(editor2).getSearchPatternsBegin() == const_cast<const SubstructureEditor&>(editor2).getSearchPatternsEnd());
    BOOST_CHECK((const_cast<SubstructureEditor&>(editor2).getSearchPatternsEnd() - const_cast<SubstructureEditor&>(editor2).getSearchPatternsBegin()) == 0);
    BOOST_CHECK((const_cast<const SubstructureEditor&>(editor2).getSearchPatternsEnd() - const_cast<const SubstructureEditor&>(editor2).getSearchPatternsBegin()) == 0);

    BOOST_CHECK(editor2.getNumExcludePatterns() == 0);
    BOOST_CHECK(const_cast<SubstructureEditor&>(editor2).getExcludePatternsBegin() == const_cast<SubstructureEditor&>(editor2).getExcludePatternsEnd());
    BOOST_CHECK(const_cast<const SubstructureEditor&>(editor2).getExcludePatternsBegin() == const_cast<const SubstructureEditor&>(editor2).getExcludePatternsEnd());
    BOOST_CHECK((const_cast<SubstructureEditor&>(editor2).getExcludePatternsEnd() - const_cast<SubstructureEditor&>(editor2).getExcludePatternsBegin()) == 0);
    BOOST_CHECK((const_cast<const SubstructureEditor&>(editor2).getExcludePatternsEnd() - const_cast<const SubstructureEditor&>(editor2).getExcludePatternsBegin()) == 0);

    BOOST_CHECK(!editor2.getResultPattern());

    // ------

    BOOST_CHECK_THROW(editor.getSearchPattern(0), Base::IndexError);
    BOOST_CHECK_THROW(editor.getExcludePattern(0), Base::IndexError);
    
    editor.addSearchPattern(parseSMARTS("[a:1]1[a:2][a:3][a:4][a:5][a:6]1"));
    editor.addSearchPattern(parseSMARTS("[c:1]1[a:2][a:3][a:4][a:5][a:6]1"));
    editor.addSearchPattern(parseSMARTS("[c:1]1[c:2][a:3][a:4][a:5][a:6]1"));
    editor.addSearchPattern(parseSMARTS("[c:1]1[c:2][c:3][a:4][a:5][a:6]1"));

    BOOST_CHECK(editor.getNumSearchPatterns() == 4);
    BOOST_CHECK(const_cast<SubstructureEditor&>(editor).getSearchPatternsBegin() != const_cast<SubstructureEditor&>(editor).getSearchPatternsEnd());
    BOOST_CHECK(const_cast<const SubstructureEditor&>(editor).getSearchPatternsBegin() != const_cast<const SubstructureEditor&>(editor).getSearchPatternsEnd());
    BOOST_CHECK((const_cast<SubstructureEditor&>(editor).getSearchPatternsEnd() - const_cast<SubstructureEditor&>(editor).getSearchPatternsBegin()) == 4);
    BOOST_CHECK((const_cast<const SubstructureEditor&>(editor).getSearchPatternsEnd() - const_cast<const SubstructureEditor&>(editor).getSearchPatternsBegin()) == 4);

    BOOST_CHECK(editor.getSearchPattern(0) == *(const_cast<SubstructureEditor&>(editor).getSearchPatternsBegin() + 0));
    BOOST_CHECK(editor.getSearchPattern(1) == *(const_cast<SubstructureEditor&>(editor).getSearchPatternsBegin() + 1));
    BOOST_CHECK(editor.getSearchPattern(2) == *(const_cast<SubstructureEditor&>(editor).getSearchPatternsBegin() + 2)); 
    BOOST_CHECK(editor.getSearchPattern(3) == *(const_cast<SubstructureEditor&>(editor).getSearchPatternsBegin() + 3));
    BOOST_CHECK(editor.getSearchPattern(0) == *(const_cast<const SubstructureEditor&>(editor).getSearchPatternsBegin() + 0));
    BOOST_CHECK(editor.getSearchPattern(1) == *(const_cast<const SubstructureEditor&>(editor).getSearchPatternsBegin() + 1));
    BOOST_CHECK(editor.getSearchPattern(2) == *(const_cast<const SubstructureEditor&>(editor).getSearchPatternsBegin() + 2)); 
    BOOST_CHECK(editor.getSearchPattern(3) == *(const_cast<const SubstructureEditor&>(editor).getSearchPatternsBegin() + 3)); 
    BOOST_CHECK_THROW(editor.getSearchPattern(4), Base::IndexError);

    BOOST_CHECK(editor.getSearchPattern(0) != editor.getSearchPattern(1));
    BOOST_CHECK(editor.getSearchPattern(0) != editor.getSearchPattern(2));
    BOOST_CHECK(editor.getSearchPattern(0) != editor.getSearchPattern(3));
    BOOST_CHECK(editor.getSearchPattern(1) != editor.getSearchPattern(2));
    BOOST_CHECK(editor.getSearchPattern(1) != editor.getSearchPattern(3));
    BOOST_CHECK(editor.getSearchPattern(2) != editor.getSearchPattern(3));
        
    BOOST_CHECK(editor.getNumExcludePatterns() == 0);
    BOOST_CHECK(const_cast<SubstructureEditor&>(editor).getExcludePatternsBegin() == const_cast<SubstructureEditor&>(editor).getExcludePatternsEnd());
    BOOST_CHECK(const_cast<const SubstructureEditor&>(editor).getExcludePatternsBegin() == const_cast<const SubstructureEditor&>(editor).getExcludePatternsEnd());
    BOOST_CHECK((const_cast<SubstructureEditor&>(editor).getExcludePatternsEnd() - const_cast<SubstructureEditor&>(editor).getExcludePatternsBegin()) == 0);
    BOOST_CHECK((const_cast<const SubstructureEditor&>(editor).getExcludePatternsEnd() - const_cast<const SubstructureEditor&>(editor).getExcludePatternsBegin()) == 0);

    BOOST_CHECK_THROW(editor.getExcludePattern(0), Base::IndexError);
    
    BOOST_CHECK(!editor.getResultPattern());

    // ------
 
    editor.addExcludePattern(parseSMARTS("[c:1]1[c:2][c:3][c:4][c:5][c:6]1"));
    editor.addExcludePattern(parseSMARTS("[c:1]1[c:2][c:3][c:4][c:5][n:6]1"));
    editor.addExcludePattern(parseSMARTS("[c:1]1[c:2][n:3][c:4][c:5][n:6]1"));

    BOOST_CHECK(editor.getNumExcludePatterns() == 3);
    BOOST_CHECK(const_cast<SubstructureEditor&>(editor).getExcludePatternsBegin() != const_cast<SubstructureEditor&>(editor).getExcludePatternsEnd());
    BOOST_CHECK(const_cast<const SubstructureEditor&>(editor).getExcludePatternsBegin() != const_cast<const SubstructureEditor&>(editor).getExcludePatternsEnd());
    BOOST_CHECK((const_cast<SubstructureEditor&>(editor).getExcludePatternsEnd() - const_cast<SubstructureEditor&>(editor).getExcludePatternsBegin()) == 3);
    BOOST_CHECK((const_cast<const SubstructureEditor&>(editor).getExcludePatternsEnd() - const_cast<const SubstructureEditor&>(editor).getExcludePatternsBegin()) == 3);

    BOOST_CHECK(editor.getExcludePattern(0) == *(const_cast<SubstructureEditor&>(editor).getExcludePatternsBegin() + 0));
    BOOST_CHECK(editor.getExcludePattern(1) == *(const_cast<SubstructureEditor&>(editor).getExcludePatternsBegin() + 1));
    BOOST_CHECK(editor.getExcludePattern(2) == *(const_cast<SubstructureEditor&>(editor).getExcludePatternsBegin() + 2));
    BOOST_CHECK(editor.getExcludePattern(0) == *(const_cast<const SubstructureEditor&>(editor).getExcludePatternsBegin() + 0));
    BOOST_CHECK(editor.getExcludePattern(1) == *(const_cast<const SubstructureEditor&>(editor).getExcludePatternsBegin() + 1));
    BOOST_CHECK(editor.getExcludePattern(2) == *(const_cast<const SubstructureEditor&>(editor).getExcludePatternsBegin() + 2));
    BOOST_CHECK_THROW(editor.getExcludePattern(3), Base::IndexError);

    BOOST_CHECK(editor.getExcludePattern(0) != editor.getExcludePattern(1));
    BOOST_CHECK(editor.getExcludePattern(0) != editor.getExcludePattern(2));
    BOOST_CHECK(editor.getExcludePattern(1) != editor.getExcludePattern(2));

    BOOST_CHECK(editor.getNumSearchPatterns() == 4);
      
    BOOST_CHECK(!editor.getResultPattern());

    // ------

    editor.setResultPattern(parseSMILES("[N:1]1[~:2]=[~:3][~:4][~:5][~:6]1CC"));

    BOOST_CHECK(editor.getResultPattern());
    
    BOOST_CHECK(editor.getNumExcludePatterns() == 3);
    BOOST_CHECK(editor.getNumSearchPatterns() == 4);

    // ------

    editor1 = editor;

    BOOST_CHECK(editor1.getNumSearchPatterns() == 4);
    BOOST_CHECK(const_cast<SubstructureEditor&>(editor1).getSearchPatternsBegin() != const_cast<SubstructureEditor&>(editor1).getSearchPatternsEnd());
    BOOST_CHECK(const_cast<const SubstructureEditor&>(editor1).getSearchPatternsBegin() != const_cast<const SubstructureEditor&>(editor1).getSearchPatternsEnd());
    BOOST_CHECK((const_cast<SubstructureEditor&>(editor1).getSearchPatternsEnd() - const_cast<SubstructureEditor&>(editor1).getSearchPatternsBegin()) == 4);
    BOOST_CHECK((const_cast<const SubstructureEditor&>(editor1).getSearchPatternsEnd() - const_cast<const SubstructureEditor&>(editor1).getSearchPatternsBegin()) == 4);

    BOOST_CHECK(editor1.getSearchPattern(0) == *(const_cast<SubstructureEditor&>(editor1).getSearchPatternsBegin() + 0));
    BOOST_CHECK(editor1.getSearchPattern(1) == *(const_cast<SubstructureEditor&>(editor1).getSearchPatternsBegin() + 1));
    BOOST_CHECK(editor1.getSearchPattern(2) == *(const_cast<SubstructureEditor&>(editor1).getSearchPatternsBegin() + 2)); 
    BOOST_CHECK(editor1.getSearchPattern(3) == *(const_cast<SubstructureEditor&>(editor1).getSearchPatternsBegin() + 3));
    BOOST_CHECK(editor1.getSearchPattern(0) == *(const_cast<const SubstructureEditor&>(editor1).getSearchPatternsBegin() + 0));
    BOOST_CHECK(editor1.getSearchPattern(1) == *(const_cast<const SubstructureEditor&>(editor1).getSearchPatternsBegin() + 1));
    BOOST_CHECK(editor1.getSearchPattern(2) == *(const_cast<const SubstructureEditor&>(editor1).getSearchPatternsBegin() + 2)); 
    BOOST_CHECK(editor1.getSearchPattern(3) == *(const_cast<const SubstructureEditor&>(editor1).getSearchPatternsBegin() + 3)); 
    BOOST_CHECK_THROW(editor1.getSearchPattern(4), Base::IndexError);

    BOOST_CHECK(editor1.getSearchPattern(0) != editor1.getSearchPattern(1));
    BOOST_CHECK(editor1.getSearchPattern(0) != editor1.getSearchPattern(2));
    BOOST_CHECK(editor1.getSearchPattern(0) != editor1.getSearchPattern(3));
    BOOST_CHECK(editor1.getSearchPattern(1) != editor1.getSearchPattern(2));
    BOOST_CHECK(editor1.getSearchPattern(1) != editor1.getSearchPattern(3));
    BOOST_CHECK(editor1.getSearchPattern(2) != editor1.getSearchPattern(3));

    for (int i = 0; i < 4; i++)
        BOOST_CHECK(editor.getSearchPattern(i) == editor1.getSearchPattern(i));
    
    BOOST_CHECK(editor1.getNumExcludePatterns() == 3);
    BOOST_CHECK(const_cast<SubstructureEditor&>(editor1).getExcludePatternsBegin() != const_cast<SubstructureEditor&>(editor1).getExcludePatternsEnd());
    BOOST_CHECK(const_cast<const SubstructureEditor&>(editor1).getExcludePatternsBegin() != const_cast<const SubstructureEditor&>(editor1).getExcludePatternsEnd());
    BOOST_CHECK((const_cast<SubstructureEditor&>(editor1).getExcludePatternsEnd() - const_cast<SubstructureEditor&>(editor1).getExcludePatternsBegin()) == 3);
    BOOST_CHECK((const_cast<const SubstructureEditor&>(editor1).getExcludePatternsEnd() - const_cast<const SubstructureEditor&>(editor1).getExcludePatternsBegin()) == 3);

    BOOST_CHECK(editor1.getExcludePattern(0) == *(const_cast<SubstructureEditor&>(editor1).getExcludePatternsBegin() + 0));
    BOOST_CHECK(editor1.getExcludePattern(1) == *(const_cast<SubstructureEditor&>(editor1).getExcludePatternsBegin() + 1));
    BOOST_CHECK(editor1.getExcludePattern(2) == *(const_cast<SubstructureEditor&>(editor1).getExcludePatternsBegin() + 2));
    BOOST_CHECK(editor1.getExcludePattern(0) == *(const_cast<const SubstructureEditor&>(editor1).getExcludePatternsBegin() + 0));
    BOOST_CHECK(editor1.getExcludePattern(1) == *(const_cast<const SubstructureEditor&>(editor1).getExcludePatternsBegin() + 1));
    BOOST_CHECK(editor1.getExcludePattern(2) == *(const_cast<const SubstructureEditor&>(editor1).getExcludePatternsBegin() + 2));
    BOOST_CHECK_THROW(editor1.getExcludePattern(3), Base::IndexError);

    BOOST_CHECK(editor1.getExcludePattern(0) != editor1.getExcludePattern(1));
    BOOST_CHECK(editor1.getExcludePattern(0) != editor1.getExcludePattern(2));
    BOOST_CHECK(editor1.getExcludePattern(1) != editor1.getExcludePattern(2));

    for (int i = 0; i < 3; i++)
        BOOST_CHECK(editor.getExcludePattern(i) == editor1.getExcludePattern(i));
  
    BOOST_CHECK(editor1.getResultPattern());
    BOOST_CHECK(editor.getResultPattern() == editor1.getResultPattern());

   // ------

    SubstructureEditor editor3(editor);

    BOOST_CHECK(editor3.getNumSearchPatterns() == 4);
    BOOST_CHECK(const_cast<SubstructureEditor&>(editor3).getSearchPatternsBegin() != const_cast<SubstructureEditor&>(editor3).getSearchPatternsEnd());
    BOOST_CHECK(const_cast<const SubstructureEditor&>(editor3).getSearchPatternsBegin() != const_cast<const SubstructureEditor&>(editor3).getSearchPatternsEnd());
    BOOST_CHECK((const_cast<SubstructureEditor&>(editor3).getSearchPatternsEnd() - const_cast<SubstructureEditor&>(editor3).getSearchPatternsBegin()) == 4);
    BOOST_CHECK((const_cast<const SubstructureEditor&>(editor3).getSearchPatternsEnd() - const_cast<const SubstructureEditor&>(editor3).getSearchPatternsBegin()) == 4);

    BOOST_CHECK(editor3.getSearchPattern(0) == *(const_cast<SubstructureEditor&>(editor3).getSearchPatternsBegin() + 0));
    BOOST_CHECK(editor3.getSearchPattern(1) == *(const_cast<SubstructureEditor&>(editor3).getSearchPatternsBegin() + 1));
    BOOST_CHECK(editor3.getSearchPattern(2) == *(const_cast<SubstructureEditor&>(editor3).getSearchPatternsBegin() + 2)); 
    BOOST_CHECK(editor3.getSearchPattern(3) == *(const_cast<SubstructureEditor&>(editor3).getSearchPatternsBegin() + 3));
    BOOST_CHECK(editor3.getSearchPattern(0) == *(const_cast<const SubstructureEditor&>(editor3).getSearchPatternsBegin() + 0));
    BOOST_CHECK(editor3.getSearchPattern(1) == *(const_cast<const SubstructureEditor&>(editor3).getSearchPatternsBegin() + 1));
    BOOST_CHECK(editor3.getSearchPattern(2) == *(const_cast<const SubstructureEditor&>(editor3).getSearchPatternsBegin() + 2)); 
    BOOST_CHECK(editor3.getSearchPattern(3) == *(const_cast<const SubstructureEditor&>(editor3).getSearchPatternsBegin() + 3)); 
    BOOST_CHECK_THROW(editor3.getSearchPattern(4), Base::IndexError);

    BOOST_CHECK(editor3.getSearchPattern(0) != editor3.getSearchPattern(1));
    BOOST_CHECK(editor3.getSearchPattern(0) != editor3.getSearchPattern(2));
    BOOST_CHECK(editor3.getSearchPattern(0) != editor3.getSearchPattern(3));
    BOOST_CHECK(editor3.getSearchPattern(1) != editor3.getSearchPattern(2));
    BOOST_CHECK(editor3.getSearchPattern(1) != editor3.getSearchPattern(3));
    BOOST_CHECK(editor3.getSearchPattern(2) != editor3.getSearchPattern(3));

    for (int i = 0; i < 4; i++)
        BOOST_CHECK(editor.getSearchPattern(i) == editor3.getSearchPattern(i));
    
    BOOST_CHECK(editor3.getNumExcludePatterns() == 3);
    BOOST_CHECK(const_cast<SubstructureEditor&>(editor3).getExcludePatternsBegin() != const_cast<SubstructureEditor&>(editor3).getExcludePatternsEnd());
    BOOST_CHECK(const_cast<const SubstructureEditor&>(editor3).getExcludePatternsBegin() != const_cast<const SubstructureEditor&>(editor3).getExcludePatternsEnd());
    BOOST_CHECK((const_cast<SubstructureEditor&>(editor3).getExcludePatternsEnd() - const_cast<SubstructureEditor&>(editor3).getExcludePatternsBegin()) == 3);
    BOOST_CHECK((const_cast<const SubstructureEditor&>(editor3).getExcludePatternsEnd() - const_cast<const SubstructureEditor&>(editor3).getExcludePatternsBegin()) == 3);

    BOOST_CHECK(editor3.getExcludePattern(0) == *(const_cast<SubstructureEditor&>(editor3).getExcludePatternsBegin() + 0));
    BOOST_CHECK(editor3.getExcludePattern(1) == *(const_cast<SubstructureEditor&>(editor3).getExcludePatternsBegin() + 1));
    BOOST_CHECK(editor3.getExcludePattern(2) == *(const_cast<SubstructureEditor&>(editor3).getExcludePatternsBegin() + 2));
    BOOST_CHECK(editor3.getExcludePattern(0) == *(const_cast<const SubstructureEditor&>(editor3).getExcludePatternsBegin() + 0));
    BOOST_CHECK(editor3.getExcludePattern(1) == *(const_cast<const SubstructureEditor&>(editor3).getExcludePatternsBegin() + 1));
    BOOST_CHECK(editor3.getExcludePattern(2) == *(const_cast<const SubstructureEditor&>(editor3).getExcludePatternsBegin() + 2));
    BOOST_CHECK_THROW(editor3.getExcludePattern(3), Base::IndexError);

    BOOST_CHECK(editor3.getExcludePattern(0) != editor3.getExcludePattern(1));
    BOOST_CHECK(editor3.getExcludePattern(0) != editor3.getExcludePattern(2));
    BOOST_CHECK(editor3.getExcludePattern(1) != editor3.getExcludePattern(2));

    for (int i = 0; i < 3; i++)
        BOOST_CHECK(editor.getExcludePattern(i) == editor3.getExcludePattern(i));
  
    BOOST_CHECK(editor3.getResultPattern());
    BOOST_CHECK(editor.getResultPattern() == editor3.getResultPattern());

    // ------

    editor3 = editor3;

    BOOST_CHECK(editor3.getNumSearchPatterns() == 4);
    BOOST_CHECK(const_cast<SubstructureEditor&>(editor3).getSearchPatternsBegin() != const_cast<SubstructureEditor&>(editor3).getSearchPatternsEnd());
    BOOST_CHECK(const_cast<const SubstructureEditor&>(editor3).getSearchPatternsBegin() != const_cast<const SubstructureEditor&>(editor3).getSearchPatternsEnd());
    BOOST_CHECK((const_cast<SubstructureEditor&>(editor3).getSearchPatternsEnd() - const_cast<SubstructureEditor&>(editor3).getSearchPatternsBegin()) == 4);
    BOOST_CHECK((const_cast<const SubstructureEditor&>(editor3).getSearchPatternsEnd() - const_cast<const SubstructureEditor&>(editor3).getSearchPatternsBegin()) == 4);

    BOOST_CHECK(editor3.getSearchPattern(0) == *(const_cast<SubstructureEditor&>(editor3).getSearchPatternsBegin() + 0));
    BOOST_CHECK(editor3.getSearchPattern(1) == *(const_cast<SubstructureEditor&>(editor3).getSearchPatternsBegin() + 1));
    BOOST_CHECK(editor3.getSearchPattern(2) == *(const_cast<SubstructureEditor&>(editor3).getSearchPatternsBegin() + 2)); 
    BOOST_CHECK(editor3.getSearchPattern(3) == *(const_cast<SubstructureEditor&>(editor3).getSearchPatternsBegin() + 3));
    BOOST_CHECK(editor3.getSearchPattern(0) == *(const_cast<const SubstructureEditor&>(editor3).getSearchPatternsBegin() + 0));
    BOOST_CHECK(editor3.getSearchPattern(1) == *(const_cast<const SubstructureEditor&>(editor3).getSearchPatternsBegin() + 1));
    BOOST_CHECK(editor3.getSearchPattern(2) == *(const_cast<const SubstructureEditor&>(editor3).getSearchPatternsBegin() + 2)); 
    BOOST_CHECK(editor3.getSearchPattern(3) == *(const_cast<const SubstructureEditor&>(editor3).getSearchPatternsBegin() + 3)); 
    BOOST_CHECK_THROW(editor3.getSearchPattern(4), Base::IndexError);

    BOOST_CHECK(editor3.getSearchPattern(0) != editor3.getSearchPattern(1));
    BOOST_CHECK(editor3.getSearchPattern(0) != editor3.getSearchPattern(2));
    BOOST_CHECK(editor3.getSearchPattern(0) != editor3.getSearchPattern(3));
    BOOST_CHECK(editor3.getSearchPattern(1) != editor3.getSearchPattern(2));
    BOOST_CHECK(editor3.getSearchPattern(1) != editor3.getSearchPattern(3));
    BOOST_CHECK(editor3.getSearchPattern(2) != editor3.getSearchPattern(3));

    for (int i = 0; i < 4; i++)
        BOOST_CHECK(editor.getSearchPattern(i) == editor3.getSearchPattern(i));
    
    BOOST_CHECK(editor3.getNumExcludePatterns() == 3);
    BOOST_CHECK(const_cast<SubstructureEditor&>(editor3).getExcludePatternsBegin() != const_cast<SubstructureEditor&>(editor3).getExcludePatternsEnd());
    BOOST_CHECK(const_cast<const SubstructureEditor&>(editor3).getExcludePatternsBegin() != const_cast<const SubstructureEditor&>(editor3).getExcludePatternsEnd());
    BOOST_CHECK((const_cast<SubstructureEditor&>(editor3).getExcludePatternsEnd() - const_cast<SubstructureEditor&>(editor3).getExcludePatternsBegin()) == 3);
    BOOST_CHECK((const_cast<const SubstructureEditor&>(editor3).getExcludePatternsEnd() - const_cast<const SubstructureEditor&>(editor3).getExcludePatternsBegin()) == 3);

    BOOST_CHECK(editor3.getExcludePattern(0) == *(const_cast<SubstructureEditor&>(editor3).getExcludePatternsBegin() + 0));
    BOOST_CHECK(editor3.getExcludePattern(1) == *(const_cast<SubstructureEditor&>(editor3).getExcludePatternsBegin() + 1));
    BOOST_CHECK(editor3.getExcludePattern(2) == *(const_cast<SubstructureEditor&>(editor3).getExcludePatternsBegin() + 2));
    BOOST_CHECK(editor3.getExcludePattern(0) == *(const_cast<const SubstructureEditor&>(editor3).getExcludePatternsBegin() + 0));
    BOOST_CHECK(editor3.getExcludePattern(1) == *(const_cast<const SubstructureEditor&>(editor3).getExcludePatternsBegin() + 1));
    BOOST_CHECK(editor3.getExcludePattern(2) == *(const_cast<const SubstructureEditor&>(editor3).getExcludePatternsBegin() + 2));
    BOOST_CHECK_THROW(editor3.getExcludePattern(3), Base::IndexError);

    BOOST_CHECK(editor3.getExcludePattern(0) != editor3.getExcludePattern(1));
    BOOST_CHECK(editor3.getExcludePattern(0) != editor3.getExcludePattern(2));
    BOOST_CHECK(editor3.getExcludePattern(1) != editor3.getExcludePattern(2));

    for (int i = 0; i < 3; i++)
        BOOST_CHECK(editor.getExcludePattern(i) == editor3.getExcludePattern(i));
  
    BOOST_CHECK(editor3.getResultPattern());
    BOOST_CHECK(editor.getResultPattern() == editor3.getResultPattern());
    
    // ------

    editor1 = SubstructureEditor();
    
    BOOST_CHECK(editor1.getNumSearchPatterns() == 0);
    BOOST_CHECK(const_cast<SubstructureEditor&>(editor1).getSearchPatternsBegin() == const_cast<SubstructureEditor&>(editor1).getSearchPatternsEnd());
    BOOST_CHECK(const_cast<const SubstructureEditor&>(editor1).getSearchPatternsBegin() == const_cast<const SubstructureEditor&>(editor1).getSearchPatternsEnd());
    BOOST_CHECK((const_cast<SubstructureEditor&>(editor1).getSearchPatternsEnd() - const_cast<SubstructureEditor&>(editor1).getSearchPatternsBegin()) == 0);
    BOOST_CHECK((const_cast<const SubstructureEditor&>(editor1).getSearchPatternsEnd() - const_cast<const SubstructureEditor&>(editor1).getSearchPatternsBegin()) == 0);

    BOOST_CHECK_THROW(editor1.getSearchPattern(0), Base::IndexError);
    
    BOOST_CHECK(editor1.getNumExcludePatterns() == 0);
    BOOST_CHECK(const_cast<SubstructureEditor&>(editor1).getExcludePatternsBegin() == const_cast<SubstructureEditor&>(editor1).getExcludePatternsEnd());
    BOOST_CHECK(const_cast<const SubstructureEditor&>(editor1).getExcludePatternsBegin() == const_cast<const SubstructureEditor&>(editor1).getExcludePatternsEnd());
    BOOST_CHECK((const_cast<SubstructureEditor&>(editor1).getExcludePatternsEnd() - const_cast<SubstructureEditor&>(editor1).getExcludePatternsBegin()) == 0);
    BOOST_CHECK((const_cast<const SubstructureEditor&>(editor1).getExcludePatternsEnd() - const_cast<const SubstructureEditor&>(editor1).getExcludePatternsBegin()) == 0);

    BOOST_CHECK_THROW(editor1.getExcludePattern(0), Base::IndexError);
    
    BOOST_CHECK(!editor1.getResultPattern());

    // ------
    
    BOOST_CHECK_THROW(editor.removeSearchPattern(4), Base::IndexError);
    BOOST_CHECK_THROW(editor.removeSearchPattern(editor.getSearchPatternsBegin() - 1), Base::RangeError);
    BOOST_CHECK_THROW(editor.removeSearchPattern(editor.getSearchPatternsBegin() + 4), Base::RangeError);
    BOOST_CHECK_THROW(editor.removeSearchPattern(editor.getSearchPatternsEnd()), Base::RangeError);
    
    BOOST_CHECK_THROW(editor.removeExcludePattern(3), Base::IndexError);
    BOOST_CHECK_THROW(editor.removeExcludePattern(editor.getExcludePatternsBegin() - 1), Base::RangeError);
    BOOST_CHECK_THROW(editor.removeExcludePattern(editor.getExcludePatternsBegin() + 3), Base::RangeError);
    BOOST_CHECK_THROW(editor.removeExcludePattern(editor.getExcludePatternsEnd()), Base::RangeError);
 
    BOOST_CHECK(editor.getResultPattern() == editor3.getResultPattern());
    
    BOOST_CHECK(editor.getNumExcludePatterns() == 3);
    BOOST_CHECK(editor.getNumSearchPatterns() == 4);

    // ------

    editor3.removeSearchPattern(0);
    editor3.removeSearchPattern(editor3.getSearchPatternsBegin() + 1);

    editor3.removeExcludePattern(1);
    editor3.removeExcludePattern(editor3.getExcludePatternsBegin());

    BOOST_CHECK(editor3.getNumSearchPatterns() == 2);
    BOOST_CHECK(const_cast<SubstructureEditor&>(editor3).getSearchPatternsBegin() != const_cast<SubstructureEditor&>(editor3).getSearchPatternsEnd());
    BOOST_CHECK(const_cast<const SubstructureEditor&>(editor3).getSearchPatternsBegin() != const_cast<const SubstructureEditor&>(editor3).getSearchPatternsEnd());
    BOOST_CHECK((const_cast<SubstructureEditor&>(editor3).getSearchPatternsEnd() - const_cast<SubstructureEditor&>(editor3).getSearchPatternsBegin()) == 2);
    BOOST_CHECK((const_cast<const SubstructureEditor&>(editor3).getSearchPatternsEnd() - const_cast<const SubstructureEditor&>(editor3).getSearchPatternsBegin()) == 2);

    BOOST_CHECK(editor3.getSearchPattern(0) == *(const_cast<SubstructureEditor&>(editor3).getSearchPatternsBegin() + 0));
    BOOST_CHECK(editor3.getSearchPattern(1) == *(const_cast<SubstructureEditor&>(editor3).getSearchPatternsBegin() + 1));
    BOOST_CHECK(editor3.getSearchPattern(0) == *(const_cast<const SubstructureEditor&>(editor3).getSearchPatternsBegin() + 0));
    BOOST_CHECK(editor3.getSearchPattern(1) == *(const_cast<const SubstructureEditor&>(editor3).getSearchPatternsBegin() + 1));
 
    BOOST_CHECK_THROW(editor3.getSearchPattern(2), Base::IndexError);

    BOOST_CHECK(editor.getSearchPattern(1) == editor3.getSearchPattern(0));
    BOOST_CHECK(editor.getSearchPattern(3) == editor3.getSearchPattern(1));
    
    BOOST_CHECK(editor3.getNumExcludePatterns() == 1);
    BOOST_CHECK(const_cast<SubstructureEditor&>(editor3).getExcludePatternsBegin() != const_cast<SubstructureEditor&>(editor3).getExcludePatternsEnd());
    BOOST_CHECK(const_cast<const SubstructureEditor&>(editor3).getExcludePatternsBegin() != const_cast<const SubstructureEditor&>(editor3).getExcludePatternsEnd());
    BOOST_CHECK((const_cast<SubstructureEditor&>(editor3).getExcludePatternsEnd() - const_cast<SubstructureEditor&>(editor3).getExcludePatternsBegin()) == 1);
    BOOST_CHECK((const_cast<const SubstructureEditor&>(editor3).getExcludePatternsEnd() - const_cast<const SubstructureEditor&>(editor3).getExcludePatternsBegin()) == 1);

    BOOST_CHECK(editor3.getExcludePattern(0) == *const_cast<SubstructureEditor&>(editor3).getExcludePatternsBegin());
    BOOST_CHECK(editor3.getExcludePattern(0) == *const_cast<const SubstructureEditor&>(editor3).getExcludePatternsBegin());
    BOOST_CHECK_THROW(editor3.getExcludePattern(1), Base::IndexError);

    BOOST_CHECK(editor.getExcludePattern(2) == editor3.getExcludePattern(0));
  
    BOOST_CHECK(editor.getResultPattern() == editor3.getResultPattern());

    // ------

    editor3.clearSearchPatterns();

    BOOST_CHECK(editor3.getNumSearchPatterns() == 0);
    BOOST_CHECK(const_cast<SubstructureEditor&>(editor3).getSearchPatternsBegin() == const_cast<SubstructureEditor&>(editor3).getSearchPatternsEnd());
    BOOST_CHECK(const_cast<const SubstructureEditor&>(editor3).getSearchPatternsBegin() == const_cast<const SubstructureEditor&>(editor3).getSearchPatternsEnd());
    BOOST_CHECK((const_cast<SubstructureEditor&>(editor3).getSearchPatternsEnd() - const_cast<SubstructureEditor&>(editor3).getSearchPatternsBegin()) == 0);
    BOOST_CHECK((const_cast<const SubstructureEditor&>(editor3).getSearchPatternsEnd() - const_cast<const SubstructureEditor&>(editor3).getSearchPatternsBegin()) == 0);

    BOOST_CHECK_THROW(editor3.getSearchPattern(0), Base::IndexError);
    BOOST_CHECK_THROW(editor3.getSearchPattern(1), Base::IndexError);
    
    BOOST_CHECK_THROW(editor3.removeSearchPattern(0), Base::IndexError);
    BOOST_CHECK_THROW(editor3.removeSearchPattern(1), Base::IndexError);
    BOOST_CHECK_THROW(editor3.removeSearchPattern(editor3.getSearchPatternsBegin()), Base::RangeError);
    BOOST_CHECK_THROW(editor3.removeSearchPattern(editor3.getSearchPatternsEnd()), Base::RangeError);
 
    BOOST_CHECK(editor3.getNumExcludePatterns() == 1);
    BOOST_CHECK(const_cast<SubstructureEditor&>(editor3).getExcludePatternsBegin() != const_cast<SubstructureEditor&>(editor3).getExcludePatternsEnd());
    BOOST_CHECK(const_cast<const SubstructureEditor&>(editor3).getExcludePatternsBegin() != const_cast<const SubstructureEditor&>(editor3).getExcludePatternsEnd());
    BOOST_CHECK((const_cast<SubstructureEditor&>(editor3).getExcludePatternsEnd() - const_cast<SubstructureEditor&>(editor3).getExcludePatternsBegin()) == 1);
    BOOST_CHECK((const_cast<const SubstructureEditor&>(editor3).getExcludePatternsEnd() - const_cast<const SubstructureEditor&>(editor3).getExcludePatternsBegin()) == 1);

    BOOST_CHECK(editor3.getExcludePattern(0) == *const_cast<SubstructureEditor&>(editor3).getExcludePatternsBegin());
    BOOST_CHECK(editor3.getExcludePattern(0) == *const_cast<const SubstructureEditor&>(editor3).getExcludePatternsBegin());
    BOOST_CHECK_THROW(editor3.getExcludePattern(1), Base::IndexError);

    BOOST_CHECK(editor.getExcludePattern(2) == editor3.getExcludePattern(0));
  
    BOOST_CHECK(editor.getResultPattern() == editor3.getResultPattern());

    // ------

    editor3.clearExcludePatterns();

    BOOST_CHECK(editor3.getNumSearchPatterns() == 0);
    BOOST_CHECK(const_cast<SubstructureEditor&>(editor3).getSearchPatternsBegin() == const_cast<SubstructureEditor&>(editor3).getSearchPatternsEnd());
    BOOST_CHECK(const_cast<const SubstructureEditor&>(editor3).getSearchPatternsBegin() == const_cast<const SubstructureEditor&>(editor3).getSearchPatternsEnd());
    BOOST_CHECK((const_cast<SubstructureEditor&>(editor3).getSearchPatternsEnd() - const_cast<SubstructureEditor&>(editor3).getSearchPatternsBegin()) == 0);
    BOOST_CHECK((const_cast<const SubstructureEditor&>(editor3).getSearchPatternsEnd() - const_cast<const SubstructureEditor&>(editor3).getSearchPatternsBegin()) == 0);

    BOOST_CHECK_THROW(editor3.getSearchPattern(0), Base::IndexError);
    BOOST_CHECK_THROW(editor3.getSearchPattern(1), Base::IndexError);
    
    BOOST_CHECK_THROW(editor3.removeSearchPattern(0), Base::IndexError);
    BOOST_CHECK_THROW(editor3.removeSearchPattern(1), Base::IndexError);
    BOOST_CHECK_THROW(editor3.removeSearchPattern(editor3.getSearchPatternsBegin()), Base::RangeError);
    BOOST_CHECK_THROW(editor3.removeSearchPattern(editor3.getSearchPatternsEnd()), Base::RangeError);
 
    BOOST_CHECK(editor3.getNumExcludePatterns() == 0);
    BOOST_CHECK(const_cast<SubstructureEditor&>(editor3).getExcludePatternsBegin() == const_cast<SubstructureEditor&>(editor3).getExcludePatternsEnd());
    BOOST_CHECK(const_cast<const SubstructureEditor&>(editor3).getExcludePatternsBegin() == const_cast<const SubstructureEditor&>(editor3).getExcludePatternsEnd());
    BOOST_CHECK((const_cast<SubstructureEditor&>(editor3).getExcludePatternsEnd() - const_cast<SubstructureEditor&>(editor3).getExcludePatternsBegin()) == 0);
    BOOST_CHECK((const_cast<const SubstructureEditor&>(editor3).getExcludePatternsEnd() - const_cast<const SubstructureEditor&>(editor3).getExcludePatternsBegin()) == 0);

    BOOST_CHECK_THROW(editor3.getExcludePattern(0), Base::IndexError);
    BOOST_CHECK_THROW(editor3.getExcludePattern(1), Base::IndexError);
    
    BOOST_CHECK_THROW(editor3.removeExcludePattern(0), Base::IndexError);
    BOOST_CHECK_THROW(editor3.removeExcludePattern(1), Base::IndexError);
    BOOST_CHECK_THROW(editor3.removeExcludePattern(editor3.getExcludePatternsBegin()), Base::RangeError);
    BOOST_CHECK_THROW(editor3.removeExcludePattern(editor3.getExcludePatternsEnd()), Base::RangeError);
 
    BOOST_CHECK(editor.getResultPattern() == editor3.getResultPattern());

    // ------

    editor.clear();

    BOOST_CHECK(editor.getNumSearchPatterns() == 0);
    BOOST_CHECK(const_cast<SubstructureEditor&>(editor).getSearchPatternsBegin() == const_cast<SubstructureEditor&>(editor).getSearchPatternsEnd());
    BOOST_CHECK(const_cast<const SubstructureEditor&>(editor).getSearchPatternsBegin() == const_cast<const SubstructureEditor&>(editor).getSearchPatternsEnd());
    BOOST_CHECK((const_cast<SubstructureEditor&>(editor).getSearchPatternsEnd() - const_cast<SubstructureEditor&>(editor).getSearchPatternsBegin()) == 0);
    BOOST_CHECK((const_cast<const SubstructureEditor&>(editor).getSearchPatternsEnd() - const_cast<const SubstructureEditor&>(editor).getSearchPatternsBegin()) == 0);

    BOOST_CHECK_THROW(editor.getSearchPattern(0), Base::IndexError);
    BOOST_CHECK_THROW(editor.getSearchPattern(1), Base::IndexError);
    
    BOOST_CHECK_THROW(editor.removeSearchPattern(0), Base::IndexError);
    BOOST_CHECK_THROW(editor.removeSearchPattern(1), Base::IndexError);
    BOOST_CHECK_THROW(editor.removeSearchPattern(editor.getSearchPatternsBegin()), Base::RangeError);
    BOOST_CHECK_THROW(editor.removeSearchPattern(editor.getSearchPatternsEnd()), Base::RangeError);
 
    BOOST_CHECK(editor.getNumExcludePatterns() == 0);
    BOOST_CHECK(const_cast<SubstructureEditor&>(editor).getExcludePatternsBegin() == const_cast<SubstructureEditor&>(editor).getExcludePatternsEnd());
    BOOST_CHECK(const_cast<const SubstructureEditor&>(editor).getExcludePatternsBegin() == const_cast<const SubstructureEditor&>(editor).getExcludePatternsEnd());
    BOOST_CHECK((const_cast<SubstructureEditor&>(editor).getExcludePatternsEnd() - const_cast<SubstructureEditor&>(editor).getExcludePatternsBegin()) == 0);
    BOOST_CHECK((const_cast<const SubstructureEditor&>(editor).getExcludePatternsEnd() - const_cast<const SubstructureEditor&>(editor).getExcludePatternsBegin()) == 0);

    BOOST_CHECK_THROW(editor.getExcludePattern(0), Base::IndexError);
    BOOST_CHECK_THROW(editor.getExcludePattern(1), Base::IndexError);
    
    BOOST_CHECK_THROW(editor.removeExcludePattern(0), Base::IndexError);
    BOOST_CHECK_THROW(editor.removeExcludePattern(1), Base::IndexError);
    BOOST_CHECK_THROW(editor.removeExcludePattern(editor.getExcludePatternsBegin()), Base::RangeError);
    BOOST_CHECK_THROW(editor.removeExcludePattern(editor.getExcludePatternsEnd()), Base::RangeError);
 
    BOOST_CHECK(!editor.getResultPattern());
}
