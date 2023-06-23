/* 
 * AtomHybridizationPerceptionFunction.cpp 
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

#include <map>
#include <cstdint>

#include "CDPL/Chem/AtomFunctions.hpp"
#include "CDPL/Chem/BondFunctions.hpp"
#include "CDPL/Chem/Atom.hpp"
#include "CDPL/Chem/Bond.hpp"
#include "CDPL/Chem/AtomType.hpp"
#include "CDPL/Chem/HybridizationState.hpp"
#include "CDPL/Internal/AtomFunctions.hpp"


using namespace CDPL; 


namespace
{

#define MAKE_ATOM_DESCR(atom_num, sb_cnt, db_cnt, tb_cnt, fval_el) \
    (std::uint64_t(atom_num) << 32) + (std::uint64_t(sb_cnt) << 24) + (std::uint64_t(db_cnt) << 16) + \
    (std::uint64_t(tb_cnt) << 8) + std::uint64_t(fval_el)

    typedef std::map<std::uint64_t, unsigned int> HybridizationMap;

    HybridizationMap::value_type hybrMapEntries[] = {
    HybridizationMap::value_type(MAKE_ATOM_DESCR(Chem::AtomType::C,  4, 0, 0, 0 ), Chem::HybridizationState::SP3  ),
    HybridizationMap::value_type(MAKE_ATOM_DESCR(Chem::AtomType::C,  2, 1, 0, 0 ), Chem::HybridizationState::SP2  ),
    HybridizationMap::value_type(MAKE_ATOM_DESCR(Chem::AtomType::C,  0, 2, 0, 0 ), Chem::HybridizationState::SP   ),
    HybridizationMap::value_type(MAKE_ATOM_DESCR(Chem::AtomType::C,  1, 0, 1, 0 ), Chem::HybridizationState::SP   ),
    HybridizationMap::value_type(MAKE_ATOM_DESCR(Chem::AtomType::C,  0, 0, 1, 2 ), Chem::HybridizationState::SP   ),
    HybridizationMap::value_type(MAKE_ATOM_DESCR(Chem::AtomType::C,  0, 1, 0, 2 ), Chem::HybridizationState::SP   ),
    HybridizationMap::value_type(MAKE_ATOM_DESCR(Chem::AtomType::C,  0, 2, 0, 0 ), Chem::HybridizationState::SP   ),
    HybridizationMap::value_type(MAKE_ATOM_DESCR(Chem::AtomType::B,  3, 0, 0, 0 ), Chem::HybridizationState::SP2  ),
    HybridizationMap::value_type(MAKE_ATOM_DESCR(Chem::AtomType::B,  4, 0, 0, 0 ), Chem::HybridizationState::SP3  ),
    HybridizationMap::value_type(MAKE_ATOM_DESCR(Chem::AtomType::Si, 4, 0, 0, 0 ), Chem::HybridizationState::SP3  ),
    HybridizationMap::value_type(MAKE_ATOM_DESCR(Chem::AtomType::Si, 6, 0, 0, 0 ), Chem::HybridizationState::SP3D2),
    HybridizationMap::value_type(MAKE_ATOM_DESCR(Chem::AtomType::N,  4, 0, 0, 0 ), Chem::HybridizationState::SP3  ),
    HybridizationMap::value_type(MAKE_ATOM_DESCR(Chem::AtomType::N,  3, 0, 0, 2 ), Chem::HybridizationState::SP3  ),
    HybridizationMap::value_type(MAKE_ATOM_DESCR(Chem::AtomType::N,  1, 1, 0, 2 ), Chem::HybridizationState::SP2  ),
    HybridizationMap::value_type(MAKE_ATOM_DESCR(Chem::AtomType::N,  0, 0, 1, 2 ), Chem::HybridizationState::SP   ),
    HybridizationMap::value_type(MAKE_ATOM_DESCR(Chem::AtomType::N,  0, 0, 1, 0 ), Chem::HybridizationState::SP   ),
    HybridizationMap::value_type(MAKE_ATOM_DESCR(Chem::AtomType::N,  1, 0, 1, 0 ), Chem::HybridizationState::SP   ),
    HybridizationMap::value_type(MAKE_ATOM_DESCR(Chem::AtomType::N,  1, 2, 0, 0 ), Chem::HybridizationState::SP2  ),
    HybridizationMap::value_type(MAKE_ATOM_DESCR(Chem::AtomType::N,  2, 1, 0, 0 ), Chem::HybridizationState::SP2  ),
    HybridizationMap::value_type(MAKE_ATOM_DESCR(Chem::AtomType::N,  0, 2, 0, 0 ), Chem::HybridizationState::SP   ),
    HybridizationMap::value_type(MAKE_ATOM_DESCR(Chem::AtomType::N,  0, 1, 0, 4 ), Chem::HybridizationState::SP2  ),
    HybridizationMap::value_type(MAKE_ATOM_DESCR(Chem::AtomType::P,  3, 0, 0, 2 ), Chem::HybridizationState::SP3  ),
    HybridizationMap::value_type(MAKE_ATOM_DESCR(Chem::AtomType::P,  3, 1, 0, 0 ), Chem::HybridizationState::SP3  ),
    HybridizationMap::value_type(MAKE_ATOM_DESCR(Chem::AtomType::P,  5, 0, 0, 0 ), Chem::HybridizationState::SP3D ),
    HybridizationMap::value_type(MAKE_ATOM_DESCR(Chem::AtomType::Sb, 5, 0, 0, 0 ), Chem::HybridizationState::SP3D ),
    HybridizationMap::value_type(MAKE_ATOM_DESCR(Chem::AtomType::O,  1, 0, 0, 6 ), Chem::HybridizationState::SP3  ),
    HybridizationMap::value_type(MAKE_ATOM_DESCR(Chem::AtomType::O,  2, 0, 0, 4 ), Chem::HybridizationState::SP3  ),
    HybridizationMap::value_type(MAKE_ATOM_DESCR(Chem::AtomType::O,  0, 1, 0, 4 ), Chem::HybridizationState::SP2  ),
    HybridizationMap::value_type(MAKE_ATOM_DESCR(Chem::AtomType::O,  0, 0, 1, 2 ), Chem::HybridizationState::SP   ),
    HybridizationMap::value_type(MAKE_ATOM_DESCR(Chem::AtomType::S,  0, 1, 0, 6 ), Chem::HybridizationState::SP2  ),
    HybridizationMap::value_type(MAKE_ATOM_DESCR(Chem::AtomType::S,  0, 3, 0, 0 ), Chem::HybridizationState::SP2  ),
    HybridizationMap::value_type(MAKE_ATOM_DESCR(Chem::AtomType::S,  2, 2, 0, 0 ), Chem::HybridizationState::SP3  ),
    HybridizationMap::value_type(MAKE_ATOM_DESCR(Chem::AtomType::S,  2, 1, 0, 2 ), Chem::HybridizationState::SP3  ),
    HybridizationMap::value_type(MAKE_ATOM_DESCR(Chem::AtomType::S,  2, 0, 0, 4 ), Chem::HybridizationState::SP3  ),
    HybridizationMap::value_type(MAKE_ATOM_DESCR(Chem::AtomType::S,  4, 0, 0, 2 ), Chem::HybridizationState::SP3D ),
    HybridizationMap::value_type(MAKE_ATOM_DESCR(Chem::AtomType::Cl, 3, 0, 0, 4 ), Chem::HybridizationState::SP3D ),
    HybridizationMap::value_type(MAKE_ATOM_DESCR(Chem::AtomType::I,  2, 0, 0, 6 ), Chem::HybridizationState::DP   ),
    HybridizationMap::value_type(MAKE_ATOM_DESCR(Chem::AtomType::I,  7, 0, 0, 0 ), Chem::HybridizationState::SP3D3),
    HybridizationMap::value_type(MAKE_ATOM_DESCR(Chem::AtomType::Hg, 2, 0, 0, 10), Chem::HybridizationState::SP   ),
    HybridizationMap::value_type(MAKE_ATOM_DESCR(Chem::AtomType::Au, 2, 0, 0, 9 ), Chem::HybridizationState::SP   ),
    HybridizationMap::value_type(MAKE_ATOM_DESCR(Chem::AtomType::Xe, 2, 0, 0, 6 ), Chem::HybridizationState::DP   ),
    HybridizationMap::value_type(MAKE_ATOM_DESCR(Chem::AtomType::Cr, 2, 2, 0, 0 ), Chem::HybridizationState::SD3  ),
    HybridizationMap::value_type(MAKE_ATOM_DESCR(Chem::AtomType::Mn, 1, 3, 0, 0 ), Chem::HybridizationState::SD3  ),
    HybridizationMap::value_type(MAKE_ATOM_DESCR(Chem::AtomType::Au, 4, 0, 0, 7 ), Chem::HybridizationState::SP2D ),
    HybridizationMap::value_type(MAKE_ATOM_DESCR(Chem::AtomType::Ni, 4, 0, 0, 6 ), Chem::HybridizationState::SP2D ),
    HybridizationMap::value_type(MAKE_ATOM_DESCR(Chem::AtomType::Pt, 4, 0, 0, 6 ), Chem::HybridizationState::SP2D ),
    HybridizationMap::value_type(MAKE_ATOM_DESCR(Chem::AtomType::Ta, 5, 0, 0, 0 ), Chem::HybridizationState::SP3D ),
    HybridizationMap::value_type(MAKE_ATOM_DESCR(Chem::AtomType::Te, 6, 0, 0, 0 ), Chem::HybridizationState::SP3D2)
    };

    HybridizationMap atomHybridizations(hybrMapEntries, hybrMapEntries + sizeof(hybrMapEntries) 
                    / sizeof(HybridizationMap::value_type));
}


unsigned int Chem::perceiveHybridizationState(const Atom& atom, const MolecularGraph& molgraph)
{
    std::size_t bnd_order_counts[3] = { 0, 0, 0 };

    Atom::ConstAtomIterator a_it = atom.getAtomsBegin();
    Atom::ConstBondIterator bonds_end = atom.getBondsEnd();
 
    for (Atom::ConstBondIterator b_it = atom.getBondsBegin(); b_it != bonds_end; ++b_it, ++a_it) {
        if (!molgraph.containsAtom(*a_it))
            continue;

        const Bond& bond = *b_it;

        if (!molgraph.containsBond(bond))
            continue;

        std::size_t bnd_order = getOrder(bond);

        if (bnd_order > 3 || bnd_order < 1)
            return HybridizationState::UNKNOWN;

        bnd_order_counts[bnd_order - 1]++;
    }

    std::size_t impl_h_count = getImplicitHydrogenCount(atom);
    
    bnd_order_counts[0] += impl_h_count;

    long free_val_el_count = Internal::calcValenceElectronCount(atom) - Internal::calcExplicitValence(atom, molgraph) - impl_h_count;

    std::uint64_t atom_descr = MAKE_ATOM_DESCR(getType(atom),
                                               bnd_order_counts[0], bnd_order_counts[1], bnd_order_counts[2],
                                               (free_val_el_count < 0 ? 0 : free_val_el_count));

    HybridizationMap::const_iterator it = atomHybridizations.find(atom_descr);

    if (it != atomHybridizations.end())
        return it->second;

    return HybridizationState::UNKNOWN;
}
