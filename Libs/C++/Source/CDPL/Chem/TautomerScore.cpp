/* 
 * TautomerScore.cpp 
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

#include "CDPL/Chem/TautomerScore.hpp"
#include "CDPL/Chem/MolecularGraph.hpp"
#include "CDPL/Chem/Atom.hpp"
#include "CDPL/Chem/Bond.hpp"
#include "CDPL/Chem/FragmentList.hpp"
#include "CDPL/Chem/MolecularGraphFunctions.hpp"
#include "CDPL/Chem/AtomFunctions.hpp"
#include "CDPL/Chem/BondFunctions.hpp"
#include "CDPL/Chem/AtomType.hpp"
#include "CDPL/Internal/AtomFunctions.hpp"


using namespace CDPL; 


Chem::TautomerScore::TautomerScore() {}

Chem::TautomerScore::TautomerScore(const TautomerScore& ts) {}

double Chem::TautomerScore::operator()(const MolecularGraph& molgraph)
{
    double score = 0.0;

    for (auto& atom : molgraph.getAtoms())
        if (isAmideNitrogen(atom, molgraph) || isCarboxyOxygen(atom, molgraph))
            score += 2.0;
    
    for (auto it = molgraph.getBondsBegin(), end = molgraph.getBondsEnd(); it != end; ++it) {
        auto& bond = *it;
    
        if (getOrder(bond) < 2)
            continue;

        auto in_ring = getRingFlag(bond);
        
        score += getAtomTypeScoreIncrement(getType(bond.getBegin()), in_ring);
        score += getAtomTypeScoreIncrement(getType(bond.getEnd()), in_ring);
        score += std::max(getUnsaturatedNeighborCount(bond.getBegin(), bond, molgraph), getUnsaturatedNeighborCount(bond.getEnd(), bond, molgraph));
    }

    auto& sssr = *getSSSR(molgraph);

    for (auto it = sssr.getElementsBegin(), end = sssr.getElementsEnd(); it != end; ++it) {
        auto& ring = *it;

        if (std::find_if(ring.getBondsBegin(), ring.getBondsEnd(), 
                         [](const Bond& bond) { return (getAromaticityFlag(bond) == false); }) != ring.getBondsEnd())
            continue;
    
        if (is24HydroxyPyridineLike(ring, molgraph))
            continue;

        score += ring.getNumBonds() * 5.0;
    }
    
    return score;
}

Chem::TautomerScore& Chem::TautomerScore::operator=(const TautomerScore& ts)
{
    return *this;
}

double Chem::TautomerScore::getAtomTypeScoreIncrement(unsigned int type, bool in_ring) const
{
    switch (type) {

        case AtomType::O:
            return 6.0;

        case AtomType::N:
            return 2.0;

        case AtomType::C:
            return (in_ring ? 1.5 : 0.0);

        case AtomType::S:
            return 4.0;

        default:
            return 0.0;
    }
}

std::size_t Chem::TautomerScore::getUnsaturatedNeighborCount(const Atom& atom, const Bond& bond, const MolecularGraph& molgraph) const
{
    std::size_t count = 0;
    auto b_it = atom.getBondsBegin();

    for (auto a_it = atom.getAtomsBegin(), a_end = atom.getAtomsEnd(); a_it != a_end; ++a_it, ++b_it) {
        auto& nbr_bond = *b_it;

        if (&nbr_bond == &bond)
            continue;

        auto& nbr_atom = *a_it;

        if (!molgraph.containsAtom(nbr_atom) || !molgraph.containsBond(nbr_bond))
            continue;
    
        if (Internal::isUnsaturated(nbr_atom, molgraph))
            count++;
    }

    return count;
}

bool Chem::TautomerScore::is24HydroxyPyridineLike(const Fragment& ring, const MolecularGraph& molgraph) const
{
    for (std::size_t i = 0, num_atoms = ring.getNumAtoms(); i < num_atoms; i++) {
        auto& atom = ring.getAtom(i);
        
        if (getType(atom) != AtomType::C)
            continue;

        if (!hasExocyclicOH(atom, molgraph))
            continue;

        if (getType(ring.getAtom((i + 1) % num_atoms)) == AtomType::N)
            return true;

        if (getType(ring.getAtom((i + 3) % num_atoms)) == AtomType::N)
            return true;

        if (getType(ring.getAtom((i + num_atoms - 1) % num_atoms)) == AtomType::N)
            return true;

        if (getType(ring.getAtom((i + num_atoms - 3) % num_atoms)) == AtomType::N)
            return true;
    }

    return false;
}

bool Chem::TautomerScore::hasExocyclicOH(const Atom& atom, const MolecularGraph& molgraph) const
{
    auto b_it = atom.getBondsBegin();

    for (auto a_it = atom.getAtomsBegin(), a_end = atom.getAtomsEnd(); a_it != a_end; ++a_it, ++b_it) {
        auto& nbr_bond = *b_it;
        auto& nbr_atom = *a_it;

        if (!molgraph.containsAtom(nbr_atom) || !molgraph.containsBond(nbr_bond))
            continue;

        if (getRingFlag(nbr_bond))
            continue;

        if (getType(nbr_atom) != AtomType::O)
            continue;

        if (Internal::getHeavyAtomCount(nbr_atom, molgraph) != 1)
            continue;

        return true;
    }

    return false;
}

bool Chem::TautomerScore::isAmideNitrogen(const Atom& atom, const MolecularGraph& molgraph) const
{
    if (getType(atom) != AtomType::N)
        return false;

    auto atoms_end = atom.getAtomsEnd();
    auto b_it = atom.getBondsBegin();
    auto seen_unsat_nbr = false;
    
    for (auto a_it = atom.getAtomsBegin(); a_it != atoms_end; ++a_it, ++b_it) {
        auto& bond = *b_it;
        auto& nbr_atom = *a_it;

        if (!molgraph.containsAtom(nbr_atom) || !molgraph.containsBond(bond))
            continue;

        if (getOrder(bond) != 1)
            return false;

        if (!seen_unsat_nbr)
            seen_unsat_nbr = Internal::isCarbonylLike(nbr_atom, molgraph, false, false);
    }

    return seen_unsat_nbr;
}

bool Chem::TautomerScore::isCarboxyOxygen(const Atom& atom, const MolecularGraph& molgraph) const
{
    if (getType(atom) != AtomType::O)
        return false;

    auto atoms_end = atom.getAtomsEnd();
    auto b_it = atom.getBondsBegin();
    auto seen_unsat_nbr = false;
    
    for (auto a_it = atom.getAtomsBegin(); a_it != atoms_end; ++a_it, ++b_it) {
        auto& bond = *b_it;
        auto& nbr_atom = *a_it;

        if (!molgraph.containsAtom(nbr_atom) || !molgraph.containsBond(bond))
            continue;

        if (getOrder(bond) != 1)
            return false;

        if (!seen_unsat_nbr)
            seen_unsat_nbr = Internal::isCarbonylLike(nbr_atom, molgraph, true, true);
    }

    return seen_unsat_nbr;
}
