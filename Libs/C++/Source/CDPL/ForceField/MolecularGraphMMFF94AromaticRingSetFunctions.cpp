/* 
 * MolecularGraphMMFF94AromaticRingSetFunctions.cpp 
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

#include "CDPL/ForceField/MolecularGraphFunctions.hpp"
#include "CDPL/ForceField/MolecularGraphProperty.hpp"
#include "CDPL/ForceField/MMFF94AromaticSSSRSubset.hpp"
#include "CDPL/Chem/MolecularGraphFunctions.hpp"
#include "CDPL/Chem/Molecule.hpp"


using namespace CDPL; 


namespace
{

    void translateMMFF94AromaticRings(Chem::Molecule& tgt_mol, const Chem::MolecularGraph& src_molgraph)
    {
        using namespace Chem;
        
        if (tgt_mol.getNumAtoms() != src_molgraph.getNumAtoms() ||
            tgt_mol.getNumBonds() != src_molgraph.getNumBonds() ||
            !ForceField::hasMMFF94AromaticRings(src_molgraph))
            return;

        const FragmentList::SharedPointer& src_rings = ForceField::getMMFF94AromaticRings(src_molgraph);
        FragmentList::SharedPointer tgt_rings(new FragmentList());

        translateFragments(src_molgraph, *src_rings, tgt_mol, *tgt_rings);
        ForceField::setMMFF94AromaticRings(tgt_mol, tgt_rings);
    }
    
    struct Init
    {

        Init() {
            Chem::Molecule::registerCopyPostprocessingFunction(&translateMMFF94AromaticRings);
        }
    } init;
}


Chem::FragmentList::SharedPointer ForceField::perceiveMMFF94AromaticRings(const Chem::MolecularGraph& molgraph)
{
    Chem::FragmentList::SharedPointer rings_ptr(new MMFF94AromaticSSSRSubset(molgraph));

    return rings_ptr;
}

Chem::FragmentList::SharedPointer ForceField::perceiveMMFF94AromaticRings(Chem::MolecularGraph& molgraph, bool overwrite)
{
    if (!overwrite) {
        Base::Any prev_rings = molgraph.getProperty(MolecularGraphProperty::MMFF94_AROMATIC_RINGS, false);
    
        if (!prev_rings.isEmpty())
            return prev_rings.getData<Chem::FragmentList::SharedPointer>();
    }

    Chem::FragmentList::SharedPointer rings_ptr(new MMFF94AromaticSSSRSubset(molgraph));

    molgraph.setProperty(MolecularGraphProperty::MMFF94_AROMATIC_RINGS, rings_ptr);

    return rings_ptr;
}
