/* 
 * AtomInductiveEffectFunction.cpp 
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

#include "CDPL/MolProp/AtomFunctions.hpp"
#include "CDPL/MolProp/BondFunctions.hpp"
#include "CDPL/Chem/Atom.hpp"
#include "CDPL/Chem/Bond.hpp"
#include "CDPL/Chem/MolecularGraph.hpp"
#include "CDPL/Util/BitSet.hpp"


using namespace CDPL; 


namespace
{

    constexpr double REF_BOND_ORDER  = 1.66;
    constexpr double REF_ENEGATIVITY = 7.41;

    double calcInductiveEffect(std::size_t atom_idx, const Chem::MolecularGraph& molgraph, std::size_t num_bonds,
                               std::size_t path_len, Util::BitSet& vis_atoms, double damping_fact)
    {
        using namespace Chem;
        using namespace MolProp;
    
        if (path_len >= num_bonds)
            return 0.0;
    
        double result = 0.0;

        vis_atoms.set(atom_idx);

        const Atom& atom = molgraph.getAtom(atom_idx);
        MolecularGraph::ConstBondIterator b_it = atom.getBondsBegin();

        for (MolecularGraph::ConstAtomIterator a_it = atom.getAtomsBegin(), a_end = atom.getAtomsEnd(); a_it != a_end; ++a_it, ++b_it) {
            const Atom& nbr_atom = *a_it;

            if (!molgraph.containsAtom(nbr_atom))
                continue;

            std::size_t nbr_atom_idx = molgraph.getAtomIndex(nbr_atom);

            if (vis_atoms.test(nbr_atom_idx))
                continue;
            
            const Bond& nbr_bond = *b_it;

            if (!molgraph.containsBond(nbr_bond))
                continue;

            double next_dmpg_fact = damping_fact * ((1.0 + getMHMOPiOrder(nbr_bond)) / REF_BOND_ORDER);
            
            result += next_dmpg_fact * (getPEOESigmaElectronegativity(nbr_atom) - REF_ENEGATIVITY) +
                calcInductiveEffect(nbr_atom_idx, molgraph, num_bonds, path_len + 1, vis_atoms, next_dmpg_fact);
        }
    
        vis_atoms.reset(atom_idx);

        return result;
    }
}


double MolProp::calcInductiveEffect(const Chem::Atom& atom, const Chem::MolecularGraph& molgraph, std::size_t num_bonds)
{
    Util::BitSet vis_atoms;

    vis_atoms.resize(molgraph.getNumAtoms());
    
    return ::calcInductiveEffect(molgraph.getAtomIndex(atom), molgraph, num_bonds, 0, vis_atoms, 1.0);
}
