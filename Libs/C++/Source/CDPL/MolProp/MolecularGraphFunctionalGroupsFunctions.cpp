/* 
 * MolecularGraphFunctionalGroupsFunctions.cpp 
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

#include "CDPL/MolProp/MolecularGraphFunctions.hpp"
#include "CDPL/MolProp/FunctionalGroupList.hpp"
#include "CDPL/MolProp/MolecularGraphProperty.hpp"
#include "CDPL/Chem/MolecularGraphFunctions.hpp"
#include "CDPL/Chem/Molecule.hpp"


using namespace CDPL; 


namespace
{

    void translateFuncGroups(Chem::Molecule& tgt_mol, const Chem::MolecularGraph& src_molgraph)
    {
        using namespace Chem;
        using namespace MolProp;
        
        if (tgt_mol.getNumAtoms() != src_molgraph.getNumAtoms() ||
            tgt_mol.getNumBonds() != src_molgraph.getNumBonds() ||
            !hasFunctionalGroups(src_molgraph))
            return;

        const FragmentList::SharedPointer& src_fgl = getFunctionalGroups(src_molgraph);
        FragmentList::SharedPointer tgt_fgl(new FragmentList());

        translateFragments(src_molgraph, *src_fgl, tgt_mol, *tgt_fgl);
        setFunctionalGroups(tgt_mol, tgt_fgl);
    }
    
    struct Init
    {

        Init() {
            Chem::Molecule::registerCopyPostprocessingFunction(&translateFuncGroups);
        }
    } init;
}


Chem::FragmentList::SharedPointer MolProp::perceiveFunctionalGroups(const Chem::MolecularGraph& molgraph)
{
    Chem::FragmentList::SharedPointer fgl_ptr(new FunctionalGroupList(molgraph));

    return fgl_ptr;
}

Chem::FragmentList::SharedPointer MolProp::perceiveFunctionalGroups(Chem::MolecularGraph& molgraph, bool overwrite)
{
     using namespace Chem;

     if (!overwrite) {
        Base::Any prev_fgl = molgraph.getProperty(MolecularGraphProperty::FUNCTIONAL_GROUPS, false);
    
        if (!prev_fgl.isEmpty())
            return prev_fgl.getData<FragmentList::SharedPointer>();
    }

    FunctionalGroupList fgl(molgraph);
    FragmentList::SharedPointer fgl_ptr(new FragmentList());

    fgl_ptr->swap(fgl);

    molgraph.setProperty(MolecularGraphProperty::FUNCTIONAL_GROUPS, fgl_ptr);

    return fgl_ptr;
}
