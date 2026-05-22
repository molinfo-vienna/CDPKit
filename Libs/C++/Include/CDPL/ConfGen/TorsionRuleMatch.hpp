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
 * \brief Definition of class CDPL::ConfGen::TorsionRuleMatch.
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
    } // namespace Chem

    namespace ConfGen
    {

        class TorsionRule;

        /**
         * \brief A single match of a ConfGen::TorsionRule against a rotatable bond: the rule, the bond and the four atoms that span the torsion.
         */
        class CDPL_CONFGEN_API TorsionRuleMatch
        {

          public:
            /**
             * \brief Constructs the \c %TorsionRuleMatch instance.
             * \param rule The matched torsion rule.
             * \param bond The rotatable bond.
             * \param atom1 The first torsion atom (A in A-B-C-D).
             * \param atom2 The second torsion atom (B).
             * \param atom3 The third torsion atom (C).
             * \param atom4 The fourth torsion atom (D).
             */
            TorsionRuleMatch(const TorsionRule& rule, const Chem::Bond& bond,
                             const Chem::Atom* atom1, const Chem::Atom* atom2,
                             const Chem::Atom* atom3, const Chem::Atom* atom4);

            /**
             * \brief Returns the four torsion atoms (A, B, C, D).
             * \return A pointer to a 4-element array of \c const Chem::Atom* (A, B, C, D).
             */
            const Chem::Atom* const* getAtoms() const;

            /**
             * \brief Returns the matched torsion rule.
             * \return A \c const reference to the rule.
             */
            const TorsionRule& getRule() const;

            /**
             * \brief Returns the rotatable bond at which the rule matched.
             * \return A \c const reference to the bond.
             */
            const Chem::Bond& getBond() const;

          private:
            const TorsionRule* rule;
            const Chem::Bond*  bond;
            const Chem::Atom*  atoms[4];
        };
    } // namespace ConfGen
} // namespace CDPL

#endif // CDPL_CONFGEN_TORSIONRULEMATCH_HPP
