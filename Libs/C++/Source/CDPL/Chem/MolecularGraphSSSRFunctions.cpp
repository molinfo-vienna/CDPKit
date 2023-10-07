/* 
 * MolecularGraphSSSRFunctions.cpp 
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
#include "CDPL/Chem/Atom.hpp"
#include "CDPL/Chem/Bond.hpp"
#include "CDPL/Chem/Molecule.hpp"
#include "CDPL/Chem/MolecularGraphProperty.hpp"
#include "CDPL/Chem/SmallestSetOfSmallestRings.hpp"


using namespace CDPL; 


namespace
{

    void translateSSSR(Chem::Molecule& tgt_mol, const Chem::MolecularGraph& src_molgraph)
    {
        using namespace Chem;
        
        if (tgt_mol.getNumAtoms() != src_molgraph.getNumAtoms() ||
            tgt_mol.getNumBonds() != src_molgraph.getNumBonds() ||
            !hasSSSR(src_molgraph))
            return;

        const FragmentList::SharedPointer& src_rings = getSSSR(src_molgraph);
        FragmentList::SharedPointer tgt_rings(new FragmentList());

        translateFragments(src_molgraph, *src_rings, tgt_mol, *tgt_rings);
        setSSSR(tgt_mol, tgt_rings);
    }
    
    struct Init
    {

        Init() {
            Chem::Molecule::registerCopyPostprocessingFunction(&translateSSSR);
        }
    } init;
}


Chem::FragmentList::SharedPointer Chem::perceiveSSSR(const MolecularGraph& molgraph)
{
    FragmentList::SharedPointer sssr_ptr(new SmallestSetOfSmallestRings(molgraph));

    return sssr_ptr;
}

Chem::FragmentList::SharedPointer Chem::perceiveSSSR(MolecularGraph& molgraph, bool overwrite)
{
    if (!overwrite) {
        Base::Any prev_sssr = molgraph.getProperty(MolecularGraphProperty::SSSR, false);
    
        if (!prev_sssr.isEmpty())
            return prev_sssr.getData<FragmentList::SharedPointer>();
    }

    SmallestSetOfSmallestRings sssr(molgraph);
    FragmentList::SharedPointer sssr_ptr(new FragmentList());

    sssr_ptr->swap(sssr);

    setSSSR(molgraph, sssr_ptr);

    return sssr_ptr;
}

Chem::FragmentList::SharedPointer Chem::extractSSSRSubset(const MolecularGraph& src_molgraph, const MolecularGraph& tgt_molgraph)
{
    FragmentList::SharedPointer tgt_sssr(new FragmentList());
    const FragmentList::SharedPointer& src_sssr = getSSSR(src_molgraph);

    getContainedFragments(tgt_molgraph, *src_sssr, *tgt_sssr, true, true, true);

    return tgt_sssr;
}

Chem::FragmentList::SharedPointer Chem::extractSSSRSubset(const MolecularGraph& src_molgraph, MolecularGraph& tgt_molgraph, bool overwrite)
{
    if (!overwrite) {
        Base::Any tgt_sssr = tgt_molgraph.getProperty(MolecularGraphProperty::SSSR, false);
    
        if (!tgt_sssr.isEmpty())
            return tgt_sssr.getData<FragmentList::SharedPointer>();
    }

    FragmentList::SharedPointer tgt_sssr = extractSSSRSubset(src_molgraph, tgt_molgraph);

    setSSSR(tgt_molgraph, tgt_sssr);

    return tgt_sssr;
}
