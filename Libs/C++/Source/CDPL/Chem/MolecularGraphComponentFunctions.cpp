/* 
 * MolecularGraphComponentFunctions.cpp 
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
#include "CDPL/Chem/ComponentSet.hpp"
#include "CDPL/Chem/Molecule.hpp"


using namespace CDPL; 


namespace
{

    void translateComponents(Chem::Molecule& tgt_mol, const Chem::MolecularGraph& src_molgraph)
    {
        using namespace Chem;
        
        if (tgt_mol.getNumAtoms() != src_molgraph.getNumAtoms() ||
            tgt_mol.getNumBonds() != src_molgraph.getNumBonds() ||
            !hasComponents(src_molgraph))
            return;

        const FragmentList::SharedPointer& src_comps = getComponents(src_molgraph);
        FragmentList::SharedPointer tgt_comps(new FragmentList());

        translateFragments(src_molgraph, *src_comps, tgt_mol, *tgt_comps);
        setComponents(tgt_mol, tgt_comps);
    }
    
    struct Init
    {

        Init() {
            Chem::Molecule::registerCopyPostprocessingFunction(&translateComponents);
        }
    } init;
}


Chem::FragmentList::SharedPointer Chem::perceiveComponents(const MolecularGraph& molgraph)
{
    FragmentList::SharedPointer comps_ptr(new ComponentSet(molgraph));

    return comps_ptr;
}

Chem::FragmentList::SharedPointer Chem::perceiveComponents(MolecularGraph& molgraph, bool overwrite)
{
    if (!overwrite) {
        Base::Any prev_comps = molgraph.getProperty(MolecularGraphProperty::COMPONENTS, false);
    
        if (!prev_comps.isEmpty())
            return prev_comps.getData<FragmentList::SharedPointer>();
    }

    FragmentList::SharedPointer comps_ptr(new ComponentSet(molgraph));

    molgraph.setProperty(MolecularGraphProperty::COMPONENTS, comps_ptr);

    return comps_ptr;
}
