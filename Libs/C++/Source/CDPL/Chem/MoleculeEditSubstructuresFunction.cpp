/* 
 * MoleculeEditSubstructuresFunction.cpp 
 *
 * This file is part of the Chemical Data Processing Toolkit
 *
 * Copyright (C) 2003 Thomas Seidel <thomas.seidel@univie.ac.at>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this library; see the file COPYING. If not, write to
 * the Free Software Foundation, Inc., 59 Temple Place - Suite 330,
 * Boston, MA 02111-1307, USA.
 */


#include "StaticInit.hpp"

#include <boost/tokenizer.hpp>

#include "CDPL/Chem/MoleculeFunctions.hpp"
#include "CDPL/Chem/UtilityFunctions.hpp"
#include "CDPL/Chem/SubstructureEditor.hpp"


using namespace CDPL; 


std::size_t Chem::editSubstructures(Molecule& mol, const std::string& search_ptns,
                                    const std::string& result_ptn, const std::string& exclude_ptns)
{
    typedef boost::tokenizer<boost::char_separator<char> > Tokenizer;
    typedef boost::char_separator<char> Separator;
    
    SubstructureEditor editor;

    for (auto& ptn : Tokenizer(search_ptns, Separator(" \t\r\n")))
        editor.addSearchPattern(parseSMARTS(ptn));

    for (auto& ptn : Tokenizer(exclude_ptns, Separator(" \t\r\n")))
        editor.addExcludePattern(parseSMARTS(ptn));

    editor.setResultPattern(parseSMILES(result_ptn));
    
    return editor.edit(mol);
}
