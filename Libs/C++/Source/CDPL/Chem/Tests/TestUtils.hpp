/* 
 * TestUtils.hpp 
 *
 * This file is part of the Chemical Data Processing Toolkit
 *
 * Copyright (C) 2003 Thomas Seidel <thomas.seidel@univie.ac.at>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program; see the file COPYING. If not, write to
 * the Free Software Foundation, Inc., 59 Temple Place - Suite 330,
 * Boston, MA 02111-1307, USA.
 */


#include <set>

#include "CDPL/Chem/FragmentList.hpp"


namespace
{

    std::size_t getUniqueAtomCount(const CDPL::Chem::FragmentList& frag_list)
    {
        using namespace CDPL;
        using namespace Chem;

        std::set<const Atom*> atoms;

        for (FragmentList::ConstElementIterator it = frag_list.getElementsBegin(), end = frag_list.getElementsEnd(); it != end; ++it) {
            const Fragment& frag = *it;

            for (Fragment::ConstAtomIterator a_it = frag.getAtomsBegin(), a_end = frag.getAtomsEnd(); a_it != a_end; ++a_it)
                atoms.insert(&*a_it);
        }

        return atoms.size();
    }

    std::size_t getUniqueBondCount(const CDPL::Chem::FragmentList& frag_list)
    {
        using namespace CDPL;
        using namespace Chem;

        std::set<const Bond*> bonds;

        for (FragmentList::ConstElementIterator it = frag_list.getElementsBegin(), end = frag_list.getElementsEnd(); it != end; ++it) {
            const Fragment& frag = *it;

            for (Fragment::ConstBondIterator b_it = frag.getBondsBegin(), b_end = frag.getBondsEnd(); b_it != b_end; ++b_it)
                bonds.insert(&*b_it);
        }

        return bonds.size();
    }
}
