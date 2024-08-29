/* 
 * ComponentSet.cpp 
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

#include "CDPL/Chem/ComponentSet.hpp"
#include "CDPL/Chem/Fragment.hpp"
#include "CDPL/Chem/Atom.hpp"
#include "CDPL/Chem/Bond.hpp"


using namespace CDPL;


Chem::ComponentSet::ComponentSet(const MolecularGraph& molgraph)
{
    perceive(molgraph);
}

void Chem::ComponentSet::perceive(const MolecularGraph& molgraph, std::size_t min_atom_idx)
{
    clear();

    if (min_atom_idx >= molgraph.getNumAtoms())
        return;

    visAtomMask.resize(molgraph.getNumAtoms());
    visAtomMask.reset();

    molGraph = &molgraph;

    std::size_t i = min_atom_idx;
    MolecularGraph::ConstAtomIterator atoms_end = molgraph.getAtomsEnd();

    for (MolecularGraph::ConstAtomIterator it = molgraph.getAtomsBegin() + min_atom_idx; it != atoms_end; ++it, i++)
        if (!visAtomMask.test(i)) {
            Fragment::SharedPointer comp_ptr(new Fragment());

            const Atom& atom = *it;

            comp_ptr->addAtom(atom);

            visitAtom(atom, *comp_ptr, min_atom_idx);
            
            addElement(comp_ptr);
        }
}

void Chem::ComponentSet::visitAtom(const Atom& atom, Fragment& comp, std::size_t min_atom_idx)
{
    visAtomMask.set(molGraph->getAtomIndex(atom));

    Atom::ConstAtomIterator atoms_end = atom.getAtomsEnd();
    Atom::ConstBondIterator b_it = atom.getBondsBegin();
        
    for (Atom::ConstAtomIterator a_it = atom.getAtomsBegin(); a_it != atoms_end; ++a_it, ++b_it) {
        const Bond& bond = *b_it;

        if (!molGraph->containsBond(bond))
            continue;

        const Atom& nbr_atom = *a_it;

        if (!molGraph->containsAtom(nbr_atom))
            continue;

        if (molGraph->getAtomIndex(nbr_atom) < min_atom_idx)
            continue;
        
        if (!comp.containsBond(bond))
            comp.addBond(bond);

        if (!visAtomMask.test(molGraph->getAtomIndex(nbr_atom))) 
            visitAtom(nbr_atom, comp, min_atom_idx);
    }
}
