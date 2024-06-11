/* 
 * ExtendedSSSR.cpp 
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

#include <algorithm>

#include "CDPL/Chem/ExtendedSSSR.hpp"
#include "CDPL/Chem/Atom.hpp"
#include "CDPL/Chem/Bond.hpp"
#include "CDPL/Chem/MolecularGraphFunctions.hpp"
#include "CDPL/Chem/AtomFunctions.hpp"
#include "CDPL/Chem/BondFunctions.hpp"


using namespace CDPL;


Chem::ExtendedSSSR::ExtendedSSSR(const MolecularGraph& molgraph)
{
    perceive(molgraph);
}

void Chem::ExtendedSSSR::perceive(const MolecularGraph& molgraph)
{
    FragmentList::operator=(*getSSSR(molgraph));

    if (getSize() <= 1)
        return;
    
    init(molgraph);

    for (std::size_t i = 0, num_atoms = molgraph.getNumAtoms(); i < num_atoms; i++) {
        auto& atom = molgraph.getAtom(i);

        if (!getRingFlag(atom))
            continue;
        
        atomRingNbrs.clear();

        auto b_it = atom.getBondsBegin();

        for (auto a_it = atom.getAtomsBegin(), a_end = atom.getAtomsEnd(); a_it != a_end; ++a_it, ++b_it) {
            auto& nbr_atom = *a_it;

            if (!molgraph.containsAtom(nbr_atom))
                continue;

            auto& nbr_bond = *b_it;

            if (!molgraph.containsBond(nbr_bond))
                continue;

            if (!ringBonds.test(molgraph.getBondIndex(nbr_bond)))
                continue;

            atomRingNbrs.emplace_back(&nbr_atom, &nbr_bond);
        }

        auto num_ring_nbrs = atomRingNbrs.size();
        
        if (num_ring_nbrs <= 2)
            continue;
        
        for (std::size_t j = 0; j < num_ring_nbrs; j++) {
            auto& nbr1_data = atomRingNbrs[j];
            auto nbr1_bond_idx = molgraph.getBondIndex(*nbr1_data.second);

            currBondPath.set(nbr1_bond_idx);
            
            for (std::size_t k = j + 1; k < num_ring_nbrs; k++) {
                 auto& nbr2_data = atomRingNbrs[k];
                 auto nbr2_bond_idx = molgraph.getBondIndex(*nbr2_data.second);
     
                 if (findRingContainingBonds(*nbr1_data.second, *nbr2_data.second))
                     continue;

                 smallestRingSize = 0;
                 currBondPath.set(nbr2_bond_idx);
                 
                 perceiveRings(molgraph, *nbr2_data.first, *nbr1_data.first);

                 if (smallestRingSize >= 2) {
                     Fragment::SharedPointer ring_ptr(new Fragment());

                     ring_ptr->addAtom(*nbr1_data.first);
                     ring_ptr->addBond(*nbr1_data.second);
                     ring_ptr->addBond(*nbr2_data.second);

                     for (auto curr_atom = nbr2_data.first; ring_ptr->getNumBonds() < smallestRingSize; ) {
                         for (auto& nbr_bond : curr_atom->getBonds()) {
                             if (!molgraph.containsBond(nbr_bond))
                                 continue;

                             if (!smallestRingBonds.test(molgraph.getBondIndex(nbr_bond)))
                                 continue;

                             if (ring_ptr->containsBond(nbr_bond))
                                 continue;

                             ring_ptr->addBond(nbr_bond);
                             curr_atom = &nbr_bond.getNeighbor(*curr_atom);
                             break;
                         }
                     }

                     addElement(ring_ptr);
                 }

                 currBondPath.reset(nbr2_bond_idx);
            }

            currBondPath.reset(nbr1_bond_idx);
        }
    }

    std::sort(this->Array::getElementsBegin(), this->Array::getElementsEnd(),
              [](const Fragment::SharedPointer& r_ptr1, const Fragment::SharedPointer& r_ptr2) {
                  return (r_ptr1->getNumAtoms() < r_ptr2->getNumAtoms());
              });
}

void Chem::ExtendedSSSR::init(const MolecularGraph& molgraph)
{
    auto num_bonds = molgraph.getNumBonds();

    ringBonds.resize(num_bonds);

    for (std::size_t i = 0; i < num_bonds; i++)
        ringBonds.set(i, getRingFlag(molgraph.getBond(i)));

    currBondPath.resize(molgraph.getNumBonds());
    currBondPath.reset();
}

bool Chem::ExtendedSSSR::findRingContainingBonds(const Bond& bond1, const Bond& bond2) const
{
    for (auto& ring : *this)
        if (ring.containsBond(bond1) && ring.containsBond(bond2))
            return true;

    return false;
}

void Chem::ExtendedSSSR::perceiveRings(const MolecularGraph& molgraph, const Atom& curr_atom, const Atom& start_atom)
{
    auto b_it = curr_atom.getBondsBegin();
    
    for (auto a_it = curr_atom.getAtomsBegin(), a_end = curr_atom.getAtomsEnd(); a_it != a_end; ++a_it, ++b_it) {
        auto& nbr_atom = *a_it;

        if (!molgraph.containsAtom(nbr_atom))
            continue;

        auto& nbr_bond = *b_it;

        if (!molgraph.containsBond(nbr_bond))
            continue;

        auto nbr_bond_idx = molgraph.getBondIndex(nbr_bond);
        
        if (!ringBonds.test(nbr_bond_idx))
            continue;

        if (currBondPath.test(nbr_bond_idx))
            continue;

        currBondPath.set(nbr_bond_idx);
        
        if (&nbr_atom == &start_atom)
            processFoundRing(molgraph);
        else
            perceiveRings(molgraph, nbr_atom, start_atom);

        currBondPath.reset(nbr_bond_idx);
    }
}

void Chem::ExtendedSSSR::processFoundRing(const MolecularGraph& molgraph)
{
    auto found_r_size = currBondPath.count();

    if (smallestRingSize > 0 && found_r_size >= smallestRingSize)
        return;

    for (auto& ring : *this) {
        auto r_size = ring.getNumBonds();

        if (r_size != found_r_size)
            continue;

        auto full_match = true;
        
        for (auto& bond : ring.getBonds()) {
            if (!currBondPath.test(molgraph.getBondIndex(bond))) {
                full_match = false;
                break;
            }
        }
        
        if (full_match)
            return;
    }

    smallestRingSize = found_r_size;
    smallestRingBonds = currBondPath;
}
