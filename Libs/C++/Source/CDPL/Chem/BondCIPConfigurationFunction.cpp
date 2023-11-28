/* 
 * BondCIPConfigurationFunction.cpp 
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

#include "CDPL/Chem/BondFunctions.hpp"
#include "CDPL/Chem/AtomFunctions.hpp"
#include "CDPL/Chem/Bond.hpp"
#include "CDPL/Chem/Atom.hpp"
#include "CDPL/Chem/StereoDescriptor.hpp"
#include "CDPL/Chem/BondConfiguration.hpp"
#include "CDPL/Chem/CIPDescriptor.hpp"
#include "CDPL/Chem/HybridizationState.hpp"
#include "CDPL/Chem/AtomPropertyFlag.hpp"
#include "CDPL/Internal/AtomFunctions.hpp"


using namespace CDPL; 


unsigned int Chem::calcCIPConfiguration(const Bond& bond, const MolecularGraph& molgraph)
{
    if (getOrder(bond) != 2)
        return BondConfiguration::NONE;

    if (getAromaticityFlag(bond))
        return BondConfiguration::NONE;

    const Atom* bond_atoms[2] = { &bond.getBegin(), &bond.getEnd() };

    for (std::size_t i = 0; i < 2; i++) {
        std::size_t num_bonds = Internal::getExplicitBondCount(*bond_atoms[i], molgraph);

        if (num_bonds < 2 || num_bonds > 3)
            return BondConfiguration::NONE;

        if (getHybridizationState(*bond_atoms[i]) != HybridizationState::SP2)
            return BondConfiguration::NONE;

        if ((num_bonds + getImplicitHydrogenCount(*bond_atoms[i])) > 3)
            return BondConfiguration::NONE;

        if (Internal::getOrdinaryHydrogenCount(*bond_atoms[i], molgraph, AtomPropertyFlag::ISOTOPE | AtomPropertyFlag::FORMAL_CHARGE | AtomPropertyFlag::H_COUNT) > 1)
            return BondConfiguration::NONE;
    }
  
    const Atom* cip_ref_atoms[2] = { 0, 0 };
  
    for (std::size_t i = 0; i < 2; i++) {
        Atom::ConstAtomIterator atoms_end = bond_atoms[i]->getAtomsEnd();
        Atom::ConstBondIterator b_it = bond_atoms[i]->getBondsBegin();

        for (Atom::ConstAtomIterator a_it = bond_atoms[i]->getAtomsBegin(); a_it != atoms_end; ++a_it, ++b_it) {
            const Bond& nbr_bond = *b_it;

            if (&nbr_bond == &bond)
                continue;

            if (!molgraph.containsBond(nbr_bond))
                continue;

            const Atom* nbr_atom = &*a_it;

            if (!molgraph.containsAtom(*nbr_atom))
                continue;

            if (!cip_ref_atoms[i])
                cip_ref_atoms[i] = nbr_atom;
            
            else {
                std::size_t pri1 = getCIPPriority(*cip_ref_atoms[i]);
                std::size_t pri2 = getCIPPriority(*nbr_atom);

                if (pri1 == pri2)
                    return BondConfiguration::NONE;

                if (pri2 > pri1)
                    cip_ref_atoms[i] = nbr_atom;
            }
        }
    }

    const StereoDescriptor& stereo_desc = getStereoDescriptor(bond);

    if (!stereo_desc.isValid(bond))
        return CIPDescriptor::UNDEF;

    const Atom* const* sto_ref_atoms = stereo_desc.getReferenceAtoms();

    if (bond_atoms[0] == sto_ref_atoms[2] && bond_atoms[1] == sto_ref_atoms[1])
        std::swap(cip_ref_atoms[0], cip_ref_atoms[1]);

    unsigned int bond_config = stereo_desc.getConfiguration();

    switch (bond_config) {

        case BondConfiguration::CIS:
            return ((cip_ref_atoms[0] == sto_ref_atoms[0]) ^ (cip_ref_atoms[1] == sto_ref_atoms[3]) ?
                    CIPDescriptor::E : CIPDescriptor::Z);

        case BondConfiguration::TRANS:
            return ((cip_ref_atoms[0] == sto_ref_atoms[0]) ^ (cip_ref_atoms[1] == sto_ref_atoms[3]) ? 
                    CIPDescriptor::Z : CIPDescriptor::E);

        case BondConfiguration::EITHER:
            return CIPDescriptor::NS;
            
        default:
            return CIPDescriptor::UNDEF;
    }
}
    
