/* 
 * FragmentHydrogenManipulationFunctions.cpp 
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

#include "CDPL/Chem/FragmentFunctions.hpp"
#include "CDPL/Chem/AtomFunctions.hpp"
#include "CDPL/Chem/Fragment.hpp"
#include "CDPL/Chem/Atom.hpp"
#include "CDPL/Chem/AtomType.hpp"
#include "CDPL/Internal/AtomFunctions.hpp"


using namespace CDPL; 


bool Chem::makeHydrogenDeplete(Fragment& frag)
{
     std::size_t num_atoms = frag.getNumAtoms();
    bool changes = false;

    for (std::size_t i = 0; i < num_atoms; ) {
        const Atom& atom = frag.getAtom(i);

        if (getType(atom) != AtomType::H) {
            i++;
            continue;
        }

        frag.removeAtom(i);

        num_atoms--;
        changes = true;
    }

    return changes;
}

bool Chem::makeOrdinaryHydrogenDeplete(Fragment& frag, unsigned int flags)
{
     std::size_t num_atoms = frag.getNumAtoms();
    bool changes = false;

    for (std::size_t i = 0; i < num_atoms; ) {
        const Atom& atom = frag.getAtom(i);

        if (!Internal::isOrdinaryHydrogen(atom, frag, flags)) {
            i++;
            continue;
        }

        frag.removeAtom(i);

        num_atoms--;
        changes = true;
    }

    return changes;
}
