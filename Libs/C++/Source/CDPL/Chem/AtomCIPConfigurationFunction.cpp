/* 
 * AtomCIPConfigurationFunction.cpp 
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
#include "CDPL/Chem/CIPDescriptor.hpp"
#include "CDPL/Chem/HybridizationState.hpp"
#include "CDPL/Chem/AtomPropertyFlag.hpp"
#include "CDPL/Util/Dereferencer.hpp"
#include "CDPL/Internal/AtomFunctions.hpp"


using namespace CDPL; 


unsigned int Chem::calcCIPConfiguration(const Atom& atom, const MolecularGraph& molgraph)
{
    using namespace std::placeholders;
    
    std::size_t num_bonds = Internal::getExplicitBondCount(atom, molgraph);

    if (num_bonds < 3 || num_bonds > 4)
        return CIPDescriptor::NONE;
  
    if (getHybridizationState(atom) != HybridizationState::SP3)
        return CIPDescriptor::NONE;

    if (getAromaticityFlag(atom))
        return CIPDescriptor::NONE;

    if ((num_bonds + getImplicitHydrogenCount(atom)) > 4)
        return CIPDescriptor::NONE;

    if (Internal::getOrdinaryHydrogenCount(atom, molgraph, AtomPropertyFlag::ISOTOPE | AtomPropertyFlag::FORMAL_CHARGE | AtomPropertyFlag::H_COUNT) > 1)
        return CIPDescriptor::NONE;
    
    if (Internal::isPlanarNitrogen(atom, molgraph))
        return CIPDescriptor::NONE;
    
    const Atom* nbr_atoms[4];
    num_bonds = getConnectedAtoms(atom, molgraph, &nbr_atoms[0]);

    if (num_bonds < 3)
        return CIPDescriptor::NONE;

    std::sort(nbr_atoms, nbr_atoms + num_bonds,
              std::bind(std::greater<std::size_t>(),
                        std::bind(&getCIPPriority, std::bind(Util::Dereferencer<const Atom*, const Atom&>(), _1)), 
                        std::bind(&getCIPPriority, std::bind(Util::Dereferencer<const Atom*, const Atom&>(), _2))));

    std::size_t cip_pri1 = getCIPPriority(*nbr_atoms[0]);
    std::size_t cip_pri2 = getCIPPriority(*nbr_atoms[1]);
    std::size_t cip_pri3 = getCIPPriority(*nbr_atoms[2]);
    std::size_t cip_pri4 = (num_bonds > 3 ? getCIPPriority(*nbr_atoms[3]) : 0);

    if (cip_pri1 == cip_pri2 || cip_pri2 == cip_pri3 || (num_bonds == 4 && cip_pri3 == cip_pri4))
        return CIPDescriptor::NONE;

    const StereoDescriptor stereo_desc = getStereoDescriptor(atom);
 
    switch (stereo_desc.getConfiguration()) {

        case AtomConfiguration::R:
        case AtomConfiguration::S: {
            unsigned int perm_parity = (num_bonds == 3 ? stereo_desc.getPermutationParity(*nbr_atoms[0], *nbr_atoms[1], *nbr_atoms[2]) :
                                        stereo_desc.getPermutationParity(*nbr_atoms[0], *nbr_atoms[1], *nbr_atoms[2], *nbr_atoms[3]));

            if (perm_parity != 1 && perm_parity != 2)
                return CIPDescriptor::UNDEF;
    
            if (stereo_desc.getConfiguration() == AtomConfiguration::R)
                return (perm_parity == 2 ? CIPDescriptor::R : CIPDescriptor::S);

            return (perm_parity == 2 ? CIPDescriptor::S : CIPDescriptor::R);
        }
            
        case AtomConfiguration::EITHER:
            return CIPDescriptor::NS;
            
        default:
            return CIPDescriptor::UNDEF;
    }
}
    
