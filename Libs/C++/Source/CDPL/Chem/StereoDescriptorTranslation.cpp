/* 
 * StereoDescriptorTranslation.cpp 
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

#include "CDPL/Chem/AtomFunctions.hpp"
#include "CDPL/Chem/BondFunctions.hpp"
#include "CDPL/Chem/Atom.hpp"
#include "CDPL/Chem/Bond.hpp"
#include "CDPL/Chem/Molecule.hpp"
#include "CDPL/Chem/StereoDescriptor.hpp"
#include "CDPL/Base/Exceptions.hpp"


using namespace CDPL; 


namespace
{

    void translateAtomStereoDescriptors(const Chem::MolecularGraph& src_molgraph, Chem::Molecule& tgt_mol,
                                        std::size_t atom_idx_offs)
    {
        using namespace Chem;
        
        MolecularGraph::ConstAtomIterator atoms_end     = src_molgraph.getAtomsEnd();
        std::size_t                       i             = atom_idx_offs;
        std::size_t                       num_tgt_atoms = tgt_mol.getNumAtoms();

        for (MolecularGraph::ConstAtomIterator a_it = src_molgraph.getAtomsBegin(); a_it != atoms_end && i < num_tgt_atoms; ++a_it, i++) {
            const Atom&             atom        = *a_it;
            Atom&                   tgt_atom    = tgt_mol.getAtom(i);
            const StereoDescriptor& stereo_desc = getStereoDescriptor(atom);

            if (!stereo_desc.isValid(atom)) {
                clearStereoDescriptor(tgt_atom);
                continue;
            }

            const Atom* const* ref_atoms = stereo_desc.getReferenceAtoms();

            try {
                if (stereo_desc.getNumReferenceAtoms() == 3)
                    setStereoDescriptor(tgt_atom,
                                        StereoDescriptor(stereo_desc.getConfiguration(),
                                                         tgt_mol.getAtom(src_molgraph.getAtomIndex(*ref_atoms[0]) + atom_idx_offs),
                                                         tgt_mol.getAtom(src_molgraph.getAtomIndex(*ref_atoms[1]) + atom_idx_offs),
                                                         tgt_mol.getAtom(src_molgraph.getAtomIndex(*ref_atoms[2]) + atom_idx_offs)));
                else
                    setStereoDescriptor(tgt_atom,
                                        StereoDescriptor(stereo_desc.getConfiguration(),
                                                         tgt_mol.getAtom(src_molgraph.getAtomIndex(*ref_atoms[0]) + atom_idx_offs),
                                                         tgt_mol.getAtom(src_molgraph.getAtomIndex(*ref_atoms[1]) + atom_idx_offs),
                                                         tgt_mol.getAtom(src_molgraph.getAtomIndex(*ref_atoms[2]) + atom_idx_offs),
                                                         tgt_mol.getAtom(src_molgraph.getAtomIndex(*ref_atoms[3]) + atom_idx_offs)));
            } catch (const Base::IndexError& e) {
                clearStereoDescriptor(tgt_atom);
            } catch (const Base::ItemNotFound& e) {
                clearStereoDescriptor(tgt_atom);
            }
        }
    }

    void translateBondStereoDescriptors(const Chem::MolecularGraph& src_molgraph, Chem::Molecule& tgt_mol,
                                        std::size_t atom_idx_offs, std::size_t bond_idx_offs)
    {
        using namespace Chem;
        
        MolecularGraph::ConstBondIterator bonds_end     = src_molgraph.getBondsEnd();
        std::size_t                       i             = bond_idx_offs;
        std::size_t                       num_tgt_bonds = tgt_mol.getNumBonds();

        for (MolecularGraph::ConstBondIterator b_it = src_molgraph.getBondsBegin(); b_it != bonds_end && i < num_tgt_bonds; ++b_it, i++) {
            const Bond&             bond        = *b_it;
            Bond&                   tgt_bond    = tgt_mol.getBond(i);
            const StereoDescriptor& stereo_desc = getStereoDescriptor(bond);

            if (!stereo_desc.isValid(bond)) {
                clearStereoDescriptor(tgt_bond);
                continue;
            }

            const Atom* const* ref_atoms = stereo_desc.getReferenceAtoms();

            try {
                setStereoDescriptor(tgt_bond,
                                    StereoDescriptor(stereo_desc.getConfiguration(),
                                                     tgt_mol.getAtom(src_molgraph.getAtomIndex(*ref_atoms[0]) + atom_idx_offs),
                                                     tgt_mol.getAtom(src_molgraph.getAtomIndex(*ref_atoms[1]) + atom_idx_offs),
                                                     tgt_mol.getAtom(src_molgraph.getAtomIndex(*ref_atoms[2]) + atom_idx_offs),
                                                     tgt_mol.getAtom(src_molgraph.getAtomIndex(*ref_atoms[3]) + atom_idx_offs)));
            } catch (const Base::IndexError& e) {
                clearStereoDescriptor(tgt_bond);
            } catch (const Base::ItemNotFound& e) {
                clearStereoDescriptor(tgt_bond);
            }
        }
    }

    void translateStereoDescriptors(Chem::Molecule& tgt_mol, const Chem::MolecularGraph& src_molgraph)
    {
        if (tgt_mol.getNumAtoms() < src_molgraph.getNumAtoms())
            return;

        if (tgt_mol.getNumBonds() < src_molgraph.getNumBonds())
            return;

        std::size_t atom_idx_offs = tgt_mol.getNumAtoms() - src_molgraph.getNumAtoms();
        std::size_t bond_idx_offs = tgt_mol.getNumBonds() - src_molgraph.getNumBonds();
        
        translateAtomStereoDescriptors(src_molgraph, tgt_mol, atom_idx_offs);
        translateBondStereoDescriptors(src_molgraph, tgt_mol, atom_idx_offs, bond_idx_offs);
    }
    
    struct Init
    {

        Init() {
            Chem::Molecule::registerCopyPostprocessingFunction(&translateStereoDescriptors);
        }
    } init;
}
