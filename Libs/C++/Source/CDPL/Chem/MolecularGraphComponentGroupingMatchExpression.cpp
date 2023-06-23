/* 
 * MolecularGraphComponentGroupingMatchExpression.cpp 
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

#include <iterator>
#include <algorithm>
#include <functional>

#include "CDPL/Chem/MolecularGraphComponentGroupingMatchExpression.hpp"
#include "CDPL/Chem/AtomBondMapping.hpp"
#include "CDPL/Chem/Atom.hpp"
#include "CDPL/Chem/MolecularGraphFunctions.hpp"


using namespace CDPL;


Chem::MolecularGraphComponentGroupingMatchExpression::MolecularGraphComponentGroupingMatchExpression(const FragmentList::SharedPointer& comp_grouping): 
    compGrouping(comp_grouping) {} 

Chem::MolecularGraphComponentGroupingMatchExpression::MolecularGraphComponentGroupingMatchExpression(const MolecularGraphComponentGroupingMatchExpression& rhs):
    compGrouping(rhs.compGrouping) {}

bool Chem::MolecularGraphComponentGroupingMatchExpression::operator()(const MolecularGraph&, const MolecularGraph& target_molgraph, 
                                                                      const AtomBondMapping& mapping, const Base::Any&) const
{
    if (!compGrouping || compGrouping->getSize() == 0)
        return true;

    const FragmentList& target_comps = *getComponents(target_molgraph);

    std::lock_guard<std::mutex> lock(mutex);

    compList.clear();
    compList.reserve(target_comps.getSize());

    std::transform(target_comps.getElementsBegin(), target_comps.getElementsEnd(), std::back_inserter(compList),
                   [](const Fragment& frag) { return &frag; });

    const AtomMapping& atom_mapping = mapping.getAtomMapping();

    FragmentList::ConstElementIterator comp_grps_end = compGrouping->getElementsEnd();

    for (FragmentList::ConstElementIterator cg_it = compGrouping->getElementsBegin(); cg_it != comp_grps_end; ) {
        const Fragment& comp_grp = *cg_it;
        const Atom* first_mpd_atom = 0;

        Fragment::ConstAtomIterator atoms_end = comp_grp.getAtomsEnd();
        Fragment::ConstAtomIterator a_it = comp_grp.getAtomsBegin();

        for ( ; a_it != atoms_end && !(first_mpd_atom = atom_mapping[&*a_it]); ++a_it);

        if (!first_mpd_atom) {
            ++cg_it;
            continue;
        }

        ComponentList::iterator target_comp_it = std::find_if(compList.begin(), compList.end(),
                                                              std::bind(&Fragment::containsAtom,
                                                                        std::placeholders::_1, std::ref(*first_mpd_atom)));

        if (target_comp_it == compList.end())
            return false;

        const Fragment* target_comp = *target_comp_it;

        for  (++a_it; a_it != atoms_end; ++a_it) {
            const Atom* mpd_atom = atom_mapping[&*a_it];

            if (mpd_atom && !target_comp->containsAtom(*mpd_atom))
                return false;
        }

        for (FragmentList::ConstElementIterator cg_it2 = ++cg_it; cg_it2 != comp_grps_end; ++cg_it2) {
            const Fragment& other_comp_grp = *cg_it2;

            atoms_end = other_comp_grp.getAtomsEnd();

            for (a_it = other_comp_grp.getAtomsBegin(); a_it != atoms_end; ++a_it) {
                const Atom* mpd_atom = atom_mapping[&*a_it];
                
                if (mpd_atom && target_comp->containsAtom(*mpd_atom))
                    return false;
            }
        }

        compList.erase(target_comp_it);
    }

    return true;
}

bool Chem::MolecularGraphComponentGroupingMatchExpression::requiresAtomBondMapping() const
{
    return true;
}

Chem::MolecularGraphComponentGroupingMatchExpression& 
Chem::MolecularGraphComponentGroupingMatchExpression::operator=(const MolecularGraphComponentGroupingMatchExpression& rhs)
{
    if (this == &rhs)
        return *this;

    compGrouping = rhs.compGrouping;

    return *this;
}
