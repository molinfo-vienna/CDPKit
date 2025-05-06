/* 
 * ConjugatedRingBondPatternSwitching.cpp 
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

#include "CDPL/Chem/ConjugatedRingBondPatternSwitching.hpp"
#include "CDPL/Chem/Molecule.hpp"
#include "CDPL/Chem/Bond.hpp"
#include "CDPL/Chem/Atom.hpp"
#include "CDPL/Chem/MolecularGraphFunctions.hpp"
#include "CDPL/Chem/AtomFunctions.hpp"
#include "CDPL/Chem/BondFunctions.hpp"
#include "CDPL/Chem/TautomerizationType.hpp"
#include "CDPL/Chem/AtomType.hpp"
#include "CDPL/Internal/AtomFunctions.hpp"


using namespace CDPL;


Chem::TautomerizationRule::SharedPointer Chem::ConjugatedRingBondPatternSwitching::clone() const
{
    return SharedPointer(new ConjugatedRingBondPatternSwitching(*this));
}

bool Chem::ConjugatedRingBondPatternSwitching::setup(MolecularGraph& parent_molgraph)
{
    perceiveSSSR(parent_molgraph, false);

    conjRings.clear();
    currRingIdx = 0;
    parentMolGraph = &parent_molgraph;
    
    for (auto& ring_ptr : getSSSR(parent_molgraph)->getBase())
        if (isConjugated(*ring_ptr))
            conjRings.push_back(ring_ptr);

    return !conjRings.empty();
}

unsigned int Chem::ConjugatedRingBondPatternSwitching::getID() const
{
    return TautomerizationType::CONJ_RING_BOND_SWITCH;
}

bool Chem::ConjugatedRingBondPatternSwitching::generate(Molecule& tautomer)
{
    if (currRingIdx >= conjRings.size())
        return false;

    tautomer = *parentMolGraph;
    
    flipBondOrders(tautomer, *conjRings[currRingIdx++]);

    return true;
}
#include <iostream>
bool Chem::ConjugatedRingBondPatternSwitching::isConjugated(const Fragment& ring) const
{
    auto num_bonds = ring.getNumBonds();
    
    if ((num_bonds == 0) || (num_bonds % 2) != 0)
        return false;

    auto exp_sb = false;
    auto has_het_subst = false;

    for (std::size_t i = 0; i < num_bonds; i++) {
        auto order = getOrder(ring.getBond(i));

        if (order < 1 || order > 2)
            return false;

        if (!has_het_subst)
            has_het_subst = hasHeteroSubstituent(ring.getAtom(i), ring);
       
        if (i == 0) {
            exp_sb = (order != 1);
            continue;
        }
        
        if (exp_sb) {
            if (order != 1)
                return false;

        } else if (order == 1)
            return false;
 
        exp_sb = !exp_sb;
    }

    return has_het_subst;
}

bool Chem::ConjugatedRingBondPatternSwitching::hasHeteroSubstituent(const Atom& atom, const Fragment& ring) const
{
    auto b_it = atom.getBondsBegin();

    for (auto a_it = atom.getAtomsBegin(), a_end = atom.getAtomsEnd(); a_it != a_end; ++a_it, ++b_it) {
        auto& nbr_bond = *b_it;

        if (ring.containsBond(nbr_bond))
            continue;
        
        auto& nbr_atom = *a_it;

        if (!parentMolGraph->containsAtom(nbr_atom) || !parentMolGraph->containsBond(nbr_bond))
            continue;

        switch (getType(nbr_atom)) {

            case AtomType::O:
            case AtomType::N:
            case AtomType::S:
            case AtomType::Se:
            case AtomType::P:
                if (Internal::getExplicitBondCount(nbr_atom, *parentMolGraph, 1, AtomType::H, true) > 0)
                    return true;
        }
    }

    return false;
}

void Chem::ConjugatedRingBondPatternSwitching::flipBondOrders(Molecule& tautomer, const Fragment& ring) const
{
    for (auto& bond : ring.getBonds()) {
        auto& taut_bond = tautomer.getBond(parentMolGraph->getBondIndex(bond));
        auto order = getOrder(taut_bond);

         if (order == 1)
             setOrder(taut_bond, 2);
         else
             setOrder(taut_bond, 1);
    }
}
