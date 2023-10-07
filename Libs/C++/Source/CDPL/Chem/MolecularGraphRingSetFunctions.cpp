/* 
 * MolecularGraphRingSetFunctions.cpp 
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
#include "CDPL/Chem/CompleteRingSet.hpp"
#include "CDPL/Chem/Molecule.hpp"


using namespace CDPL; 


namespace
{

    void translateRings(Chem::Molecule& tgt_mol, const Chem::MolecularGraph& src_molgraph)
    {
        using namespace Chem;
        
        if (tgt_mol.getNumAtoms() != src_molgraph.getNumAtoms() ||
            tgt_mol.getNumBonds() != src_molgraph.getNumBonds() ||
            !hasRings(src_molgraph))
            return;

        const FragmentList::SharedPointer& src_rings = getRings(src_molgraph);
        FragmentList::SharedPointer tgt_rings(new FragmentList());

        translateFragments(src_molgraph, *src_rings, tgt_mol, *tgt_rings);
        setRings(tgt_mol, tgt_rings);
    }
    
    struct Init
    {

        Init() {
            Chem::Molecule::registerCopyPostprocessingFunction(&translateRings);
        }
    } init;
}


Chem::FragmentList::SharedPointer Chem::perceiveRings(const MolecularGraph& molgraph)
{
    FragmentList::SharedPointer rings_ptr(new CompleteRingSet(molgraph));

    return rings_ptr;
}

Chem::FragmentList::SharedPointer Chem::perceiveRings(MolecularGraph& molgraph, bool overwrite)
{
    if (!overwrite) {
        Base::Any prev_rings = molgraph.getProperty(MolecularGraphProperty::RINGS, false);
    
        if (!prev_rings.isEmpty())
            return prev_rings.getData<FragmentList::SharedPointer>();
    }

    CompleteRingSet rset(molgraph);
    FragmentList::SharedPointer rings_ptr(new FragmentList());

    rings_ptr->swap(rset);

    molgraph.setProperty(MolecularGraphProperty::RINGS, rings_ptr);

    return rings_ptr;
}
