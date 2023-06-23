/* 
 * AtomMDLParityFunction.cpp 
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
#include <functional>

#include "CDPL/Chem/AtomFunctions.hpp"
#include "CDPL/Chem/Atom.hpp"
#include "CDPL/Chem/Bond.hpp"
#include "CDPL/Chem/StereoDescriptor.hpp"
#include "CDPL/Chem/AtomConfiguration.hpp"
#include "CDPL/Chem/AtomPropertyFlag.hpp"
#include "CDPL/Chem/MDLParity.hpp"
#include "CDPL/Chem/HybridizationState.hpp"
#include "CDPL/Util/Dereferencer.hpp"
#include "CDPL/Internal/AtomFunctions.hpp"


using namespace CDPL; 


unsigned int Chem::calcMDLParity(const Atom& atom, const MolecularGraph& molgraph)
{
    using namespace std::placeholders;

    std::size_t num_bonds = Internal::getExplicitBondCount(atom, molgraph);

    if (num_bonds < 3 || num_bonds > 4)
        return MDLParity::NONE;

    if (getHybridizationState(atom) != HybridizationState::SP3)
        return MDLParity::NONE;

    if (getAromaticityFlag(atom))
        return MDLParity::NONE;

    if ((num_bonds + getImplicitHydrogenCount(atom)) > 4)
        return MDLParity::NONE;

    const Atom* ordered_nbrs[4];
    const Atom* ordinary_h_nbr = 0;

    Atom::ConstAtomIterator atoms_end = atom.getAtomsEnd();
    Atom::ConstBondIterator b_it = atom.getBondsBegin();
    std::size_t i = 0;

    for (Atom::ConstAtomIterator a_it = atom.getAtomsBegin(); a_it != atoms_end; ++a_it, ++b_it) {
        const Atom& nbr_atom = *a_it;

        if (!molgraph.containsAtom(nbr_atom) || !molgraph.containsBond(*b_it))
            continue;

        if (Internal::isOrdinaryHydrogen(nbr_atom, molgraph, AtomPropertyFlag::ISOTOPE | AtomPropertyFlag::FORMAL_CHARGE | AtomPropertyFlag::H_COUNT)) {
            if (ordinary_h_nbr) 
                return MDLParity::NONE;

            ordinary_h_nbr = &nbr_atom;
            continue;
        }

        ordered_nbrs[i++] = &nbr_atom;
    }

    if (ordinary_h_nbr) {
        if (i != 3) // sanity check
            return MDLParity::NONE;

        ordered_nbrs[3] = ordinary_h_nbr;
    }

    std::sort(ordered_nbrs, ordered_nbrs + i,
              std::bind(std::less<std::size_t>(),
                        std::bind(&MolecularGraph::getAtomIndex, &molgraph, 
                                  std::bind(Util::Dereferencer<const Atom*, const Atom&>(), _1)), 
                        std::bind(&MolecularGraph::getAtomIndex, &molgraph, 
                                  std::bind(Util::Dereferencer<const Atom*, const Atom&>(), _2))));

    const StereoDescriptor stereo_desc = getStereoDescriptor(atom);
    unsigned int perm_parity = (num_bonds == 3 ? stereo_desc.getPermutationParity(*ordered_nbrs[0], *ordered_nbrs[1], *ordered_nbrs[2]) :
                                stereo_desc.getPermutationParity(*ordered_nbrs[0], *ordered_nbrs[1], *ordered_nbrs[2], *ordered_nbrs[3]));

    if (perm_parity != 1 && perm_parity != 2)
        return MDLParity::UNDEF;

    switch (stereo_desc.getConfiguration()) {

        case AtomConfiguration::R:
            return (perm_parity == 2 ? MDLParity::ODD : MDLParity::EVEN);

        case AtomConfiguration::S:
            return (perm_parity == 2 ? MDLParity::EVEN : MDLParity::ODD);

        case AtomConfiguration::EITHER:
            return MDLParity::EITHER;

        default:
            return MDLParity::UNDEF;
    }
}
    
