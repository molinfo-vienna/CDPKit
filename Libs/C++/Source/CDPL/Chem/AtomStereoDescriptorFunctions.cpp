/* 
 * AtomStereoDescriptorFunctions.cpp 
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

#include "CDPL/Chem/Entity3DFunctions.hpp"
#include "CDPL/Chem/AtomFunctions.hpp"
#include "CDPL/Chem/BondFunctions.hpp"
#include "CDPL/Chem/Atom.hpp"
#include "CDPL/Chem/Bond.hpp"
#include "CDPL/Chem/StereoDescriptor.hpp"
#include "CDPL/Chem/AtomConfiguration.hpp"
#include "CDPL/Chem/MDLParity.hpp"
#include "CDPL/Chem/AtomPropertyFlag.hpp"
#include "CDPL/Chem/HybridizationState.hpp"
#include "CDPL/Chem/BondStereoFlag.hpp"
#include "CDPL/Base/Exceptions.hpp"
#include "CDPL/Util/Dereferencer.hpp"
#include "CDPL/Internal/AtomFunctions.hpp"


using namespace CDPL; 


namespace
{

    Chem::StereoDescriptor makeStereoDescriptor(unsigned int config, const Chem::Atom& atom, const Chem::MolecularGraph& molgraph)
    {
        using namespace Chem;

        const Atom* atoms[4];
        std::size_t num_atoms = getConnectedAtoms(atom, molgraph, &atoms[0]);

        if (num_atoms == 3)
            return Chem::StereoDescriptor(config, *atoms[0], *atoms[1], *atoms[2]);

        if (num_atoms == 4)
            return Chem::StereoDescriptor(config, *atoms[0], *atoms[1], *atoms[2], *atoms[3]);

        return Chem::StereoDescriptor(config);
    }

    const Chem::StereoDescriptor DEF_DESCRIPTOR = Chem::StereoDescriptor(Chem::AtomConfiguration::UNDEF);
}


Chem::StereoDescriptor Chem::calcStereoDescriptor(const Atom& atom, const MolecularGraph& molgraph, std::size_t dim)
{
    std::size_t num_bonds = Internal::getExplicitBondCount(atom, molgraph);

    if (num_bonds < 3 || num_bonds > 4)
        return StereoDescriptor(AtomConfiguration::NONE);

    if (getHybridizationState(atom) != HybridizationState::SP3)
        return makeStereoDescriptor(AtomConfiguration::NONE, atom, molgraph);

    if (getAromaticityFlag(atom))
        return makeStereoDescriptor(AtomConfiguration::NONE, atom, molgraph);

    if ((num_bonds + getImplicitHydrogenCount(atom)) > 4)
        return makeStereoDescriptor(AtomConfiguration::NONE, atom, molgraph);

    typedef std::pair<const Chem::Atom*, const Chem::Bond*> Ligand;

    Ligand ligands[4];
    int z_signs[4] = { 0, 0, 0, 0 };
    bool has_stereo_bond = false;

    Atom::ConstAtomIterator atoms_end = atom.getAtomsEnd();
    Atom::ConstBondIterator b_it = atom.getBondsBegin();

    Ligand* ligand = ligands;
    int* z_sign = z_signs;
    bool has_either_bond = false;
    num_bonds = 0;

    for (Atom::ConstAtomIterator a_it = atom.getAtomsBegin(); a_it != atoms_end; ++a_it, ++b_it)  {
        const Atom* lig_atom = &*a_it; 

        if (!molgraph.containsAtom(*lig_atom))
            continue;

        const Bond* lig_bond = &*b_it; 

        if (!molgraph.containsBond(*lig_bond))
            continue;

        *ligand = Ligand(lig_atom, lig_bond);

        if (dim != 3 && dim != 0) {
            unsigned int bnd_stereo = get2DStereoFlag(*lig_bond);

            switch (bnd_stereo) {

                case BondStereoFlag::UP:
                case BondStereoFlag::REVERSE_UP:
                    *z_sign = 1;
                    has_stereo_bond = true;
                    break;

                case BondStereoFlag::DOWN:
                case BondStereoFlag::REVERSE_DOWN:
                    *z_sign = -1;
                    has_stereo_bond = true;
                    break;
/*
                case BondStereoFlag::UP:
                case BondStereoFlag::REVERSE_DOWN:
                    *z_sign = (&lig_bond->getEnd() == lig_atom ? 1 : -1);
                    has_stereo_bond = true;
                    break;

                case BondStereoFlag::DOWN:
                case BondStereoFlag::REVERSE_UP:
                    *z_sign = (&lig_bond->getEnd() == lig_atom ? -1 : 1);
                    has_stereo_bond = true;
                    break;
*/
                case BondStereoFlag::EITHER:
                case BondStereoFlag::REVERSE_EITHER:
                    if (dim == 2)
                        return makeStereoDescriptor(AtomConfiguration::EITHER, atom, molgraph);

                    has_either_bond = true;

                default:
                    break;
            }
        }

        ligand++;
        z_sign++;
        num_bonds++; 
    }

    if (num_bonds < 3) // sanity check
        return StereoDescriptor(AtomConfiguration::NONE);

    if (dim != 2 && dim != 3) {
        const StereoDescriptor& stereo_desc = getStereoDescriptor(atom);
        unsigned int config = stereo_desc.getConfiguration();

        if ((config == AtomConfiguration::R || config == AtomConfiguration::S) && stereo_desc.isValid(atom)) {
            unsigned int perm_parity = (num_bonds == 3 ? 
                                        stereo_desc.getPermutationParity(*ligands[0].first, *ligands[1].first, *ligands[2].first) :
                                        stereo_desc.getPermutationParity(*ligands[0].first, *ligands[1].first, *ligands[2].first, *ligands[3].first));

            if (perm_parity == 1)
                return makeStereoDescriptor(config == AtomConfiguration::R ? AtomConfiguration::S : AtomConfiguration::R, atom, molgraph);

            if (perm_parity == 2)
                return makeStereoDescriptor(config, atom, molgraph);
        } 

        if (config == AtomConfiguration::EITHER || config == AtomConfiguration::NONE)
            return makeStereoDescriptor(config, atom, molgraph);

        if (dim == 0)
            return makeStereoDescriptor(AtomConfiguration::NONE, atom, molgraph);
    }

    if (num_bonds == 3) 
        ligands[3] = Ligand(&atom, static_cast<const Bond*>(0));

    if (dim != 2) {
        try {
            const Math::Vector3D& atom1_coords = get3DCoordinates(*ligands[0].first);
            const Math::Vector3D& atom2_coords = get3DCoordinates(*ligands[1].first);
            const Math::Vector3D& atom3_coords = get3DCoordinates(*ligands[2].first);
            const Math::Vector3D& atom4_coords = get3DCoordinates(*ligands[3].first);

            double vol = innerProd(crossProd(atom4_coords - atom2_coords, atom4_coords - atom1_coords), 
                                   atom4_coords - atom3_coords); 

            return (vol > 0.0 ? makeStereoDescriptor(AtomConfiguration::S, atom, molgraph) : vol < 0.0 ? 
                    makeStereoDescriptor(AtomConfiguration::R, atom, molgraph) : makeStereoDescriptor(AtomConfiguration::EITHER, atom, molgraph));
    
        } catch (const Base::ItemNotFound& e) {
            if (dim == 3)
                throw e;
        }
    }

    if (!has_stereo_bond || has_either_bond) 
        return makeStereoDescriptor(AtomConfiguration::EITHER, atom, molgraph);

    try {
        const Math::Vector2D& atom1_coords = get2DCoordinates(*ligands[0].first);
        const Math::Vector2D& atom2_coords = get2DCoordinates(*ligands[1].first);
        const Math::Vector2D& atom3_coords = get2DCoordinates(*ligands[2].first);
        const Math::Vector2D& atom4_coords = get2DCoordinates(*ligands[3].first);

        // Determinat Algorithm (T. Cieplak, J. L. Wisniewski, Molecules 2001, 6, 915-926)

        double sign = 0.0;

        if (z_signs[0] != 0) {
            double tmp = (atom2_coords[0] - atom4_coords[0]) * (atom3_coords[1] - atom4_coords[1])
                - (atom2_coords[1] - atom4_coords[1]) * (atom3_coords[0] - atom4_coords[0]);

            sign += z_signs[0] * tmp;
        }

        if (z_signs[1] != 0) {
            double tmp = (atom1_coords[0] - atom4_coords[0]) * (atom3_coords[1] - atom4_coords[1])
                - (atom1_coords[1] - atom4_coords[1]) * (atom3_coords[0] - atom4_coords[0]);

            sign -= z_signs[1] * tmp;
        }

        if (z_signs[2] != 0) {
            double tmp = (atom1_coords[0] - atom4_coords[0]) * (atom2_coords[1] - atom4_coords[1])
                - (atom1_coords[1] - atom4_coords[1]) * (atom2_coords[0] - atom4_coords[0]);

            sign += z_signs[2] * tmp;
        }

        if (z_signs[3] != 0) {
            double tmp = (atom1_coords[0] - atom3_coords[0]) * (atom2_coords[1] - atom3_coords[1])
                - (atom1_coords[1] - atom3_coords[1]) * (atom2_coords[0] - atom3_coords[0]);

            sign -= z_signs[3] * tmp;
        }

        return (sign > 0.0 ? makeStereoDescriptor(AtomConfiguration::S, atom, molgraph) : sign < 0.0 ? 
                makeStereoDescriptor(AtomConfiguration::R, atom, molgraph) : makeStereoDescriptor(AtomConfiguration::EITHER, atom, molgraph));
    
    } catch (const Base::ItemNotFound& e) {
        if (dim == 2)
            throw e;
    }

    return makeStereoDescriptor(AtomConfiguration::EITHER, atom, molgraph);
}

unsigned int Chem::calcAtomConfiguration(const Atom& atom, const MolecularGraph& molgraph, 
                                         const StereoDescriptor& descr, const Math::Vector3DArray& coords) 
{
    std::size_t num_ref_atoms = descr.getNumReferenceAtoms();

    if (num_ref_atoms < 3)
        return AtomConfiguration::NONE;

    const Math::Vector3D& atom1_coords = coords[molgraph.getAtomIndex(*descr.getReferenceAtoms()[0])];
    const Math::Vector3D& atom2_coords = coords[molgraph.getAtomIndex(*descr.getReferenceAtoms()[1])];
    const Math::Vector3D& atom3_coords = coords[molgraph.getAtomIndex(*descr.getReferenceAtoms()[2])];
    const Math::Vector3D& atom4_coords = coords[molgraph.getAtomIndex(num_ref_atoms == 3 ? atom : *descr.getReferenceAtoms()[3])];

    double vol = innerProd(crossProd(atom4_coords - atom2_coords, atom4_coords - atom1_coords), 
                           atom4_coords - atom3_coords); 

    if (vol > 0.0)
        return AtomConfiguration::S;

    if (vol < 0.0)
        return AtomConfiguration::R;

    return AtomConfiguration::EITHER;
}

Chem::StereoDescriptor Chem::calcStereoDescriptorFromMDLParity(const Atom& atom, const MolecularGraph& molgraph)
{
    using namespace std::placeholders;
    
    std::size_t num_bonds = Internal::getExplicitBondCount(atom, molgraph);

    if (num_bonds < 3 || num_bonds > 4)
        return StereoDescriptor(AtomConfiguration::NONE);

    if (getHybridizationState(atom) != HybridizationState::SP3)
        return makeStereoDescriptor(AtomConfiguration::NONE, atom, molgraph);

    if ((num_bonds + getImplicitHydrogenCount(atom)) > 4)
        return makeStereoDescriptor(AtomConfiguration::NONE, atom, molgraph);

    const Atom* ordered_nbrs[4];

    std::size_t i = 0;
    const Atom* ordinary_h_nbr = 0;

    Atom::ConstAtomIterator atoms_end = atom.getAtomsEnd();
    Atom::ConstBondIterator b_it = atom.getBondsBegin();
 
    for (Atom::ConstAtomIterator a_it = atom.getAtomsBegin(); a_it != atoms_end; ++a_it, ++b_it)  {
        const Atom& nbr_atom = *a_it; 

        if (!molgraph.containsAtom(nbr_atom) || !molgraph.containsBond(*b_it))
            continue;

        if (Internal::isOrdinaryHydrogen(nbr_atom, molgraph, AtomPropertyFlag::ISOTOPE | AtomPropertyFlag::FORMAL_CHARGE | AtomPropertyFlag::H_COUNT)) {
            if (ordinary_h_nbr) 
                return makeStereoDescriptor(AtomConfiguration::NONE, atom, molgraph);

            ordinary_h_nbr = &nbr_atom;
            continue;
        }

        ordered_nbrs[i++] = &nbr_atom;
    }

    if (ordinary_h_nbr) {
        if (i != 3) // sanity check
            return makeStereoDescriptor(AtomConfiguration::NONE, atom, molgraph);

        ordered_nbrs[3] = ordinary_h_nbr;
    }

    std::sort(ordered_nbrs, ordered_nbrs + i,
              std::bind(std::less<std::size_t>(),
                        std::bind(&MolecularGraph::getAtomIndex, &molgraph, 
                                  std::bind(Util::Dereferencer<const Atom*, const Atom&>(), _1)), 
                        std::bind(&MolecularGraph::getAtomIndex, &molgraph, 
                                  std::bind(Util::Dereferencer<const Atom*, const Atom&>(), _2))));

    unsigned int parity = getMDLParity(atom);

    switch (parity) {

        case MDLParity::EVEN:
            if (num_bonds == 4)
                return StereoDescriptor(AtomConfiguration::S, *ordered_nbrs[0], *ordered_nbrs[1], *ordered_nbrs[2], *ordered_nbrs[3]);

            return StereoDescriptor(AtomConfiguration::S, *ordered_nbrs[0], *ordered_nbrs[1], *ordered_nbrs[2]);

        case MDLParity::ODD:
            if (num_bonds == 4)
                return StereoDescriptor(AtomConfiguration::R, *ordered_nbrs[0], *ordered_nbrs[1], *ordered_nbrs[2], *ordered_nbrs[3]);

            return StereoDescriptor(AtomConfiguration::R, *ordered_nbrs[0], *ordered_nbrs[1], *ordered_nbrs[2]);

        case MDLParity::EITHER:
            return makeStereoDescriptor(AtomConfiguration::EITHER, atom, molgraph);

        default:
            return makeStereoDescriptor(AtomConfiguration::UNDEF, atom, molgraph);
    }
}
