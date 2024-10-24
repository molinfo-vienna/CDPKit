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

#include "CDPL/Chem/BasicMolecule.hpp"
#include "CDPL/Chem/Atom.hpp"
#include "CDPL/Chem/Entity3DFunctions.hpp"
#include "CDPL/Chem/AtomFunctions.hpp"
#include "CDPL/Chem/BondFunctions.hpp"
#include "CDPL/Chem/ControlParameterFunctions.hpp"
#include "CDPL/Base/DataIOBase.hpp"
#include "CDPL/Base/Exceptions.hpp"

#include "CMLDataReader.hpp"


using namespace CDPL;


bool Chem::CMLDataReader::readMolecule(std::istream& is, Molecule& mol)
{
    using namespace std::placeholders;
    
    if (!hasMoreData(is))
        return false;

    init(is);

    return false; // TODO
}

bool Chem::CMLDataReader::skipMolecule(std::istream& is)
{
    using namespace std::placeholders;
    
    if (!hasMoreData(is))
        return false;

    init(is);

    return false; // TODO
}

bool Chem::CMLDataReader::hasMoreData(std::istream& is) const
{
    return !std::istream::traits_type::eq_int_type(is.peek(), std::istream::traits_type::eof());
}

void Chem::CMLDataReader::init(std::istream& is)
{
    strictErrorChecking = getStrictErrorCheckingParameter(ioBase); 
}
