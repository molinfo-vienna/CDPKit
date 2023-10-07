/* 
 * MolecularGraphPiElectronSystemsFunctions.cpp 
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

#include "CDPL/Chem/MolecularGraphFunctions.hpp"
#include "CDPL/Chem/MolecularGraphProperty.hpp"
#include "CDPL/Chem/PiElectronSystemList.hpp"
#include "CDPL/Chem/Molecule.hpp"


using namespace CDPL; 


namespace
{

    void translatePiElectronSystems(Chem::Molecule& tgt_mol, const Chem::MolecularGraph& src_molgraph)
    {
        using namespace Chem;
        
        if (tgt_mol.getNumAtoms() != src_molgraph.getNumAtoms() ||
            tgt_mol.getNumBonds() != src_molgraph.getNumBonds() ||
            !hasPiElectronSystems(src_molgraph))
            return;

        const ElectronSystemList::SharedPointer& src_pi_sys_list = getPiElectronSystems(src_molgraph);
        ElectronSystemList::SharedPointer tgt_pi_sys_list(new ElectronSystemList());

        for (const auto& src_pi_sys : *src_pi_sys_list) {
            ElectronSystem::SharedPointer tgt_pi_sys(new ElectronSystem());

            for (std::size_t i = 0, num_atoms = src_pi_sys.getNumAtoms(); i < num_atoms; i++)
                tgt_pi_sys->addAtom(tgt_mol.getAtom(src_molgraph.getAtomIndex(src_pi_sys.getAtom(i))), src_pi_sys.getElectronContrib(i));
            
            tgt_pi_sys_list->addElement(tgt_pi_sys);
        }

        setPiElectronSystems(tgt_mol, tgt_pi_sys_list);
    }
    
    struct Init
    {

        Init() {
            Chem::Molecule::registerCopyPostprocessingFunction(&translatePiElectronSystems);
        }
    } init;
}


Chem::ElectronSystemList::SharedPointer Chem::perceivePiElectronSystems(const MolecularGraph& molgraph)
{
    ElectronSystemList::SharedPointer pi_systems_ptr(new PiElectronSystemList(molgraph));

    return pi_systems_ptr;
}

Chem::ElectronSystemList::SharedPointer Chem::perceivePiElectronSystems(MolecularGraph& molgraph, bool overwrite)
{
    if (!overwrite) {
        Base::Any prev_pi_systems = molgraph.getProperty(MolecularGraphProperty::PI_ELECTRON_SYSTEMS, false);
    
        if (!prev_pi_systems.isEmpty())
            return prev_pi_systems.getData<ElectronSystemList::SharedPointer>();
    }

    PiElectronSystemList pi_systems(molgraph);
    ElectronSystemList::SharedPointer pi_systems_ptr(new ElectronSystemList());

    pi_systems_ptr->swap(pi_systems);
    
    setPiElectronSystems(molgraph, pi_systems_ptr);

    return pi_systems_ptr;
}
