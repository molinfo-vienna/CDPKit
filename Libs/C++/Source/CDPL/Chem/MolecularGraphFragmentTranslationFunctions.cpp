/* 
 * MolecularGraphFragmentTranslationFunctions.cpp 
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


using namespace CDPL; 


void Chem::translateFragment(const MolecularGraph& src_molgraph, const Fragment& src_frag,
                             const MolecularGraph& tgt_molgraph, Fragment& tgt_frag, bool append)
{
    if (!append)
        tgt_frag.clear();
     
    for (const auto& src_atom : src_frag.getAtoms())
        tgt_frag.addAtom(tgt_molgraph.getAtom(src_molgraph.getAtomIndex(src_atom)));

    for (const auto& src_bond : src_frag.getBonds())
        tgt_frag.addBond(tgt_molgraph.getBond(src_molgraph.getBondIndex(src_bond)));
}

void Chem::translateFragments(const MolecularGraph& src_molgraph, const FragmentList& src_frag_list,
                              const MolecularGraph& tgt_molgraph, FragmentList& tgt_frag_list, bool append)
{
    if (!append)
        tgt_frag_list.clear();
  
    for (const auto& src_frag : src_frag_list) {
        Fragment::SharedPointer tgt_frag(new Fragment());

        translateFragment(src_molgraph, src_frag, tgt_molgraph, *tgt_frag);
            
        tgt_frag_list.addElement(tgt_frag);
    }
}
