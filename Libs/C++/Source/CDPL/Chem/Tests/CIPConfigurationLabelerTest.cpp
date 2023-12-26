/* 
 * CIPConfigurationLabelerTest.cpp 
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


#include <cstdlib>
#include <string>
#include <fstream>
#include <set>
#include <cctype>

#include <boost/test/auto_unit_test.hpp>
#include <boost/tokenizer.hpp>

#include "CDPL/Chem/BasicMolecule.hpp"
#include "CDPL/Chem/MolecularGraphFunctions.hpp"
#include "CDPL/Chem/CIPConfigurationLabeler.hpp"
#include "CDPL/Chem/CIPDescriptor.hpp"
#include "CDPL/Chem/SMILESMoleculeReader.hpp"


namespace
{

    std::string toString(unsigned int descr)
    {
        using namespace CDPL;
        using namespace Chem;

        switch (descr) {

            case CIPDescriptor::NS:
                return "ns";

            case CIPDescriptor::R:
                return "R";

            case CIPDescriptor::S:
                return "S";
                
            case CIPDescriptor::r:
                return "r";

            case CIPDescriptor::s:
                return "s";

            case CIPDescriptor::seqTrans:
                return "e";
                
            case CIPDescriptor::seqCis:
                return "z";
                
            case CIPDescriptor::E:
                return "E";
                
            case CIPDescriptor::Z:
                return "Z";
                
            case CIPDescriptor::M:
                return "M";
                
            case CIPDescriptor::P:
                return "P";

            case CIPDescriptor::m:
                return "m";
                
            case CIPDescriptor::p:
                return "p";
        }

        return "";
    }

    std::string toString(const std::set<std::string>& str_set)
    {
        std::string str;

        for (const auto& e : str_set) {
            if (str.empty())
                str = e;
            else
                str += ", " + e;
        }

        return str;
    }
}


BOOST_AUTO_TEST_CASE(CIPConfigurationLabelerTest)
{
    using namespace CDPL;
    using namespace Chem;

    typedef boost::tokenizer<boost::char_separator<char> > Tokenizer;

    std::ifstream ifs(std::string(std::string(std::getenv("CDPKIT_TEST_DATA_DIR")) + "/CIPConfigLabelingTestSet.smi").c_str());

    BOOST_CHECK(ifs);

    BasicMolecule mol;
    SMILESMoleculeReader reader(ifs);
    CIPConfigurationLabeler labeler;
    
    while (reader.read(mol)) {
        const std::string& title = getName(mol);

        Tokenizer title_tokenizer(title, boost::char_separator<char>(" \t"));
        std::set<std::string> exp_labels;
        std::string rules;
        std::string ctr_types;
        std::string mol_name;
        
        for (const auto& token : title_tokenizer) {
            if (mol_name.empty()) {
                mol_name = token;
                continue;
            }

            if (token.front() == 'P')
                continue;

            if (std::isdigit(static_cast<unsigned char>(token.front()))) {
                if (!std::isdigit(static_cast<unsigned char>(token.back()))) {
                    switch (token.back()) {
       
                        case 'a':
                        case 'b':
                        case 'c':
                            rules = token;

                        case 'M':
                        case 'P':
                        case 'm':
                        case 'p':
                            continue;
                    }

                    exp_labels.insert(token);
                    
                } else
                    rules = token;
            } else
                ctr_types = token;
        }

        if (ctr_types == "HE" || ctr_types == "AT") // not supported
            continue;

        calcBasicProperties(mol, false);
        
        std::set<std::string> found_labels;
        
        labeler.setup(mol);

        for (const auto& atom : mol.getAtoms()) {
            const std::string& label_str = toString(labeler.getLabel(atom));

            if (label_str.empty() || label_str == "ns")
                continue;
        
            found_labels.insert(std::to_string(atom.getIndex() + 1) + label_str);
        }

        for (const auto& bond : mol.getBonds()) {
            const std::string& label_str = toString(labeler.getLabel(bond));

            if (label_str.empty() || label_str == "ns")
                continue;
            
            found_labels.insert(std::to_string(bond.getBegin().getIndex() + 1) + label_str);
            found_labels.insert(std::to_string(bond.getEnd().getIndex() + 1) + label_str);
        }

        bool print_info = false;
        
        if (ctr_types.find("CT3") != std::string::npos || ctr_types.find("CT4") != std::string::npos ||
            ctr_types.find("TH3") != std::string::npos) {

            for (auto& label : found_labels) {
                bool found = (exp_labels.find(label) != exp_labels.end());

                BOOST_CHECK(found);
                print_info |= !found; 
            }
        } else {
            bool all_found = (found_labels == exp_labels);

            BOOST_CHECK(all_found);
            print_info = !all_found;
        }
        
        if (print_info) {
            BOOST_TEST_MESSAGE("Molecule name: " << mol_name);
            BOOST_TEST_MESSAGE("Found labels: " << toString(found_labels));
            BOOST_TEST_MESSAGE("Expected labels: " << toString(exp_labels));
            BOOST_TEST_MESSAGE("Center types: " << ctr_types);
            BOOST_TEST_MESSAGE("Deciding rules: " << rules);
        }
    }
}
