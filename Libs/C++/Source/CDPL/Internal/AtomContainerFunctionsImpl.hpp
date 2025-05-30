/* 
 * AtomContainerFunctionsImpl.hpp 
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


#include "CDPL/Chem/AtomFunctions.hpp"
#include "CDPL/Chem/AtomContainer.hpp"
#include "CDPL/Chem/Atom.hpp"
#include "CDPL/Chem/UtilityFunctions.hpp"


std::size_t CDPL::Internal::getExplicitAtomCount(const Chem::AtomContainer& cntnr, unsigned int type, bool strict)
{
    std::size_t count = 0;

    for (Chem::AtomContainer::ConstAtomIterator it = cntnr.getAtomsBegin(), end = cntnr.getAtomsEnd(); it != end; ++it)
        if (strict ? type == getType(*it) : Chem::atomTypesMatch(type, getType(*it)))
            count++;

    return count;
}

long CDPL::Internal::getNetFormalCharge(const Chem::AtomContainer& cntnr)
{
    long charge = 0;

    for (auto& atom : cntnr.getAtoms())
        charge += getFormalCharge(atom);

    return charge;
}
