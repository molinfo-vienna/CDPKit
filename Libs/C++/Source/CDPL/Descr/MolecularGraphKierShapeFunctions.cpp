/* 
 * MolecularGraphKierShapeFunctions.cpp 
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

#include <cassert>

#include "CDPL/Descr/MolecularGraphFunctions.hpp"
#include "CDPL/Chem/MolecularGraph.hpp"
#include "CDPL/Chem/AtomContainerFunctions.hpp"
#include "CDPL/Chem/Bond.hpp"
#include "CDPL/Chem/Atom.hpp"
#include "CDPL/Chem/AtomType.hpp"
#include "CDPL/Util/BitSet.hpp"


using namespace CDPL; 


double Descr::calcKierShape1(const Chem::MolecularGraph& molgraph)
{
    using namespace Chem;
        
    Util::BitSet h_mask(molgraph.getNumAtoms());
    std::size_t num_hvy_atoms = molgraph.getNumAtoms() - buildAtomTypeMask(molgraph, h_mask, AtomType::H);

    MolecularGraph::ConstBondIterator bonds_end = molgraph.getBondsEnd();
    std::size_t num_hvy_bonds = 0;

    for (MolecularGraph::ConstBondIterator it = molgraph.getBondsBegin(); it != bonds_end; ++it) {
        const Bond& bond = *it;
        const Atom& atom1 = bond.getBegin();

        if (!molgraph.containsAtom(atom1))
            continue;

        const Atom& atom2 = bond.getEnd();

        if (!molgraph.containsAtom(atom2))
            continue;

        if (h_mask.test(molgraph.getAtomIndex(atom1)) || h_mask.test(molgraph.getAtomIndex(atom2)))
            continue;

        num_hvy_bonds++;
    }

    double shape1 = (num_hvy_bonds > 0 && num_hvy_atoms > 0 ?
                     double((num_hvy_atoms - 1) * (num_hvy_atoms - 1) * num_hvy_atoms) / (num_hvy_bonds * num_hvy_bonds)
                     : 0.0);

    return shape1;
}

double Descr::calcKierShape2(const Chem::MolecularGraph& molgraph)
{
    using namespace Chem;
    
    Util::BitSet h_mask(molgraph.getNumAtoms());
    std::size_t num_hvy_atoms = molgraph.getNumAtoms() - buildAtomTypeMask(molgraph, h_mask, AtomType::H);
    std::size_t num_2_bond_paths = 0;
    
    MolecularGraph::ConstAtomIterator atoms_end = molgraph.getAtomsEnd();

    for (MolecularGraph::ConstAtomIterator it = molgraph.getAtomsBegin(); it != atoms_end; ++it) {
        const Atom& atom = *it;

        if (h_mask.test(molgraph.getAtomIndex(atom)))
            continue;

        std::size_t hvy_bond_count = 0;

        Atom::ConstBondIterator nbr_bonds_end = atom.getBondsEnd();
        Atom::ConstAtomIterator nbr_a_it = atom.getAtomsBegin();

        for (Atom::ConstBondIterator nbr_b_it = atom.getBondsBegin(); nbr_b_it != nbr_bonds_end; ++nbr_b_it, ++nbr_a_it) {
            const Atom& nbr_atom= *nbr_a_it;

            if (!molgraph.containsAtom(nbr_atom) || !molgraph.containsBond(*nbr_b_it))
                continue;

            if (!h_mask.test(molgraph.getAtomIndex(nbr_atom)))
                hvy_bond_count++;
        }

        num_2_bond_paths += hvy_bond_count * (hvy_bond_count - 1) / 2;
    }

    double shape2 = (num_2_bond_paths > 0 && num_hvy_atoms >= 2 ?
                     double((num_hvy_atoms - 1) * (num_hvy_atoms - 2) * (num_hvy_atoms - 2)) / (num_2_bond_paths * num_2_bond_paths)
                     : 0.0);

    return shape2;
}

double Descr::calcKierShape3(const Chem::MolecularGraph& molgraph)
{
    using namespace Chem;
    
    Util::BitSet h_mask(molgraph.getNumAtoms());
    std::size_t num_hvy_atoms = molgraph.getNumAtoms() - buildAtomTypeMask(molgraph, h_mask, AtomType::H);

    MolecularGraph::ConstBondIterator bonds_end = molgraph.getBondsEnd();
    std::size_t num_3_bond_paths = 0;

    for (MolecularGraph::ConstBondIterator it = molgraph.getBondsBegin(); it != bonds_end; ++it) {
        const Bond& bond = *it;
        const Atom* atoms[2] = { &bond.getBegin(), &bond.getEnd() };

        if (!molgraph.containsAtom(*atoms[0]) || !molgraph.containsAtom(*atoms[1]))
            continue;

        if (h_mask.test(molgraph.getAtomIndex(*atoms[0])) || h_mask.test(molgraph.getAtomIndex(*atoms[1])))
            continue;

        std::size_t bond_counts[2] = { 0, 0 };

        for (std::size_t i = 0; i < 2; i++) {
            Atom::ConstBondIterator nbr_bonds_end = atoms[i]->getBondsEnd();
            Atom::ConstAtomIterator nbr_a_it = atoms[i]->getAtomsBegin();

            for (Atom::ConstBondIterator nbr_b_it = atoms[i]->getBondsBegin(); nbr_b_it != nbr_bonds_end; ++nbr_b_it, ++nbr_a_it) {
                const Atom& nbr_atom= *nbr_a_it;

                if (!molgraph.containsAtom(nbr_atom) || !molgraph.containsBond(*nbr_b_it))
                    continue;

                if (!h_mask.test(molgraph.getAtomIndex(nbr_atom)))
                    bond_counts[i]++;
            }
        }

        assert(bond_counts[0] >= 1 && bond_counts[1] >= 1);

        num_3_bond_paths += (bond_counts[0] - 1) * (bond_counts[1] - 1);
    }

    double shape3 = 0.0;

    if (num_hvy_atoms >= 3 && num_3_bond_paths > 0) {
        if (num_hvy_atoms % 2 == 0) 
            shape3 = double((num_hvy_atoms - 3) * (num_hvy_atoms - 2) * (num_hvy_atoms - 2)) 
                / (num_3_bond_paths * num_3_bond_paths);
        else
            shape3 = double((num_hvy_atoms - 1) * (num_hvy_atoms - 3) * (num_hvy_atoms - 3)) 
                / (num_3_bond_paths * num_3_bond_paths);
    }

    return shape3;
}
