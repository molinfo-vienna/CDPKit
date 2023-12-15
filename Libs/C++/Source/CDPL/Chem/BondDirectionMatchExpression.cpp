/* 
 * BondDirectionMatchExpression.cpp
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

#include "CDPL/Chem/BondDirectionMatchExpression.hpp"
#include "CDPL/Chem/Atom.hpp"
#include "CDPL/Chem/Bond.hpp"
#include "CDPL/Chem/BondDirection.hpp"
#include "CDPL/Chem/AtomBondMapping.hpp"
#include "CDPL/Base/Any.hpp"


using namespace CDPL;


namespace
{

    int getLevel(const Chem::Bond& bond, const Chem::Atom& atom, unsigned int dir)
    {
        using namespace Chem;

        switch (dir) {

            case BondDirection::UP:
                return (&atom == &bond.getEnd() ? 1 : -1);

            case BondDirection::DOWN:
                return (&atom == &bond.getEnd() ? -1 : 1);

            default:
                return 0;
        }
    }
}


Chem::BondDirectionMatchExpression::BondDirectionMatchExpression(unsigned int dir_flags, bool not_match): 
    dirFlags(dir_flags & (BondDirection::UP | BondDirection::DOWN | BondDirection::UNSPECIFIED)), notMatch(not_match) {}

bool Chem::BondDirectionMatchExpression::operator()(const Bond& qry_bond, const MolecularGraph&,
                                                    const Bond& tgt_bond, const MolecularGraph&,
                                                    const AtomBondMapping& mapping, const Base::Any& target_bond_dir) const
{
    if (dirFlags == 0)
        return true;

    if (target_bond_dir.isEmpty())
        return true;
 
    const Atom* tgt_atom = mapping.getAtomMapping()[&qry_bond.getEnd()];

    if (!tgt_atom || !tgt_bond.containsAtom(*tgt_atom))
        return true;
    
    unsigned int tgt_bnd_dir = target_bond_dir.getData<unsigned int>();
    
    if ((dirFlags & BondDirection::UNSPECIFIED) && (tgt_bnd_dir == BondDirection::NONE))
        return !notMatch;

    unsigned int qry_bnd_dir = dirFlags & (BondDirection::UP | BondDirection::DOWN);

    if (!qry_bnd_dir)
        return notMatch;
    
    if (qry_bnd_dir == (BondDirection::UP | BondDirection::DOWN)) {
        if (tgt_bnd_dir & (BondDirection::UP | BondDirection::DOWN))
            return !notMatch;

        return notMatch;
    }
    
    int qry_level = getLevel(qry_bond, qry_bond.getEnd(), qry_bnd_dir);
    int tgt_level = getLevel(tgt_bond, *tgt_atom, tgt_bnd_dir);

    return ((qry_level == tgt_level) ^ notMatch);
}
