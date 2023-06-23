/* 
 * TorsionRuleMatch.hpp 
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

/**
 * \file
 * \brief Definition of the class CDPL::ConfGen::TorsionRuleMatch.
 */

#ifndef CDPL_CONFGEN_TORSIONRULEMATCH_HPP
#define CDPL_CONFGEN_TORSIONRULEMATCH_HPP

#include <vector>
#include <cstddef>

#include "CDPL/ConfGen/APIPrefix.hpp"
#include "CDPL/Chem/MolecularGraph.hpp"


namespace CDPL 
{

    namespace Chem
    {
    
        class Atom;
        class Bond;
    }

    namespace ConfGen 
    {

        class TorsionRule;

        class CDPL_CONFGEN_API TorsionRuleMatch
        {

          public:
            TorsionRuleMatch(const TorsionRule& rule, const Chem::Bond& bond, 
                             const Chem::Atom* atom1, const Chem::Atom* atom2, 
                             const Chem::Atom* atom3, const Chem::Atom* atom4);

            const Chem::Atom* const* getAtoms() const;

            const TorsionRule& getRule() const;

            const Chem::Bond& getBond() const;

          private:
            const TorsionRule* rule;
            const Chem::Bond*  bond;
            const Chem::Atom*  atoms[4];
        };
    }
}

#endif // CDPL_CONFGEN_TORSIONRULEMATCH_HPP
