/* 
 * AtomEnvironmentFunction.cpp 
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

#include "CDPL/Chem/AtomFunctions.hpp"
#include "CDPL/Chem/MolecularGraph.hpp"
#include "CDPL/Chem/Atom.hpp"
#include "CDPL/Chem/Bond.hpp"


using namespace CDPL; 


std::size_t Chem::getEnvironment(const Atom& atom, const MolecularGraph& molgraph, std::size_t max_dist, Fragment& env, bool append)
{
    if (!append)
    env.clear();

    std::size_t last_num_atoms = env.getNumAtoms();

    env.addAtom(atom);
    
    for (std::size_t i = 0; i < max_dist; i++) {
    std::size_t curr_num_atoms = env.getNumAtoms();
    
    for (std::size_t j = last_num_atoms; j < curr_num_atoms; j++) {
        const Atom& curr_atom = env.getAtom(j);
        Atom::ConstBondIterator nb_it = curr_atom.getBondsBegin();

        for (Atom::ConstAtomIterator na_it = curr_atom.getAtomsBegin(), na_end = curr_atom.getAtomsEnd(); na_it != na_end; ++na_it, ++nb_it) {
        const Atom& nbr_atom = *na_it;

        if (!molgraph.containsAtom(nbr_atom))
            continue;

        const Bond& nbr_bond = *nb_it;

        if (!molgraph.containsBond(nbr_bond))
            continue;

        env.addBond(nbr_bond);
        }
    }

    if (curr_num_atoms == env.getNumAtoms())
        return i;

    last_num_atoms = curr_num_atoms;
    }

    return max_dist;
}
