/* 
 * AtomContainerAtomCountFunctions.cpp 
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

#include "CDPL/MolProp/AtomContainerFunctions.hpp"
#include "CDPL/Chem/AtomFunctions.hpp"
#include "CDPL/Chem/AtomContainer.hpp"
#include "CDPL/Chem/Atom.hpp"
#include "CDPL/Chem/AtomType.hpp"
#include "CDPL/Internal/AtomContainerFunctions.hpp"


using namespace CDPL; 


std::size_t MolProp::getExplicitAtomCount(const Chem::AtomContainer& cntnr)
{
    return cntnr.getNumAtoms();
}

std::size_t MolProp::getExplicitAtomCount(const Chem::AtomContainer& cntnr, unsigned int type, bool strict)
{
    return Internal::getExplicitAtomCount(cntnr, type, strict);
}

std::size_t MolProp::getExplicitChainAtomCount(const Chem::AtomContainer& cntnr)
{
    std::size_t count = 0;

    for (Chem::AtomContainer::ConstAtomIterator it = cntnr.getAtomsBegin(), end = cntnr.getAtomsEnd(); it != end; ++it)
        if (!getRingFlag(*it))
            count++;

    return count;
}

std::size_t MolProp::getRingAtomCount(const Chem::AtomContainer& cntnr)
{
    std::size_t count = 0;

    for (Chem::AtomContainer::ConstAtomIterator it = cntnr.getAtomsBegin(), end = cntnr.getAtomsEnd(); it != end; ++it)
        if (getRingFlag(*it))
            count++;

    return count;
}

std::size_t MolProp::getAromaticAtomCount(const Chem::AtomContainer& cntnr)
{
    std::size_t count = 0;

    for (Chem::AtomContainer::ConstAtomIterator it = cntnr.getAtomsBegin(), end = cntnr.getAtomsEnd(); it != end; ++it)
        if (getAromaticityFlag(*it))
            count++;

    return count;
}

std::size_t MolProp::getHeavyAtomCount(const Chem::AtomContainer& cntnr)
{
    using namespace Chem;
    
    std::size_t count = 0;

    for (AtomContainer::ConstAtomIterator it = cntnr.getAtomsBegin(), end = cntnr.getAtomsEnd(); it != end; ++it)
        if (getType(*it) != AtomType::H)
            count++;

    return count;
}
