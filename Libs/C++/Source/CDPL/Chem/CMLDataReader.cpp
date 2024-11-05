/* 
 * CMLDataReader.cpp 
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

#include <istream>
#include <string_view>

#include "CDPL/Chem/BasicMolecule.hpp"
#include "CDPL/Chem/Atom.hpp"
#include "CDPL/Chem/Entity3DFunctions.hpp"
#include "CDPL/Chem/AtomFunctions.hpp"
#include "CDPL/Chem/BondFunctions.hpp"
#include "CDPL/Chem/ControlParameterFunctions.hpp"
#include "CDPL/Base/DataIOBase.hpp"
#include "CDPL/Base/Exceptions.hpp"
#include "CDPL/Internal/StringDataIOUtilities.hpp"

#include "CMLDataReader.hpp"
#include "CMLFormatData.hpp"

//#include <iostream>
using namespace CDPL;


bool Chem::CMLDataReader::readMolecule(std::istream& is, Molecule& mol)
{
    return skipMolecule(is); // TODO

    /*
    init(is);

    if (!hasMoreData(is))
        return false;

    return true;
    */
}

bool Chem::CMLDataReader::skipMolecule(std::istream& is)
{
    using namespace Internal;

    if (!hasMoreData(is))
        return false;

    XMLTagInfo tag_info;
    std::size_t mol_elem_cnt = 0;

    do {
        if (!getNextXMLTag(is, tag_info))
            return false;
        
        if (tag_info.name != CML::Element::MOLECULE)
            continue;
        
        switch (tag_info.type) {

            case XMLTagInfo::START:
                mol_elem_cnt++;
                break;

            case XMLTagInfo::END:
                if (mol_elem_cnt > 0)
                    mol_elem_cnt--;

            default:
                break;
        }

    } while (mol_elem_cnt > 0);

    return true;
}

bool Chem::CMLDataReader::hasMoreData(std::istream& is) const
{
    using namespace Internal;

    XMLTagInfo tag_info;
    
    while (getNextXMLTag(is, tag_info)) {
        if ((tag_info.name == CML::Element::MOLECULE) && (tag_info.type != XMLTagInfo::END)) {
            if (!is.seekg(tag_info.streamPos))
                return false;
            
            return true;
        }
    }
    
    return false;
}

void Chem::CMLDataReader::init(std::istream& is)
{
    strictErrorChecking = getStrictErrorCheckingParameter(ioBase); 
}
