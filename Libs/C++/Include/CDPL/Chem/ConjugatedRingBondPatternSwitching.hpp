/* 
 * ConjugatedRingBondPatternSwitching.hpp 
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
 * \brief Definition of class CDPL::Chem::ConjugatedRingBondPatternSwitching.
 */

#ifndef CDPL_CHEM_CONJUGATEDRINGBONDPATTERNSWITCHING_HPP
#define CDPL_CHEM_CONJUGATEDRINGBONDPATTERNSWITCHING_HPP

#include <memory>
#include <vector>
#include <cstddef>

#include "CDPL/Chem/APIPrefix.hpp"
#include "CDPL/Chem/TautomerizationRule.hpp"
#include "CDPL/Chem/Fragment.hpp"


namespace CDPL
{

    namespace Chem
    {

        /**
         * \brief Chem::TautomerizationRule implementation that enumerates tautomers obtained by switching the
         *        single/double bond pattern of conjugated rings (e.g. the two Kekulé forms of benzene).
         * \since 1.3
         */
        class CDPL_CHEM_API ConjugatedRingBondPatternSwitching : public TautomerizationRule
        {

          public:
            /** \brief A reference-counted smart pointer [\ref SHPTR] for dynamically allocated \c %ConjugatedRingBondPatternSwitching instances. */
            typedef std::shared_ptr<ConjugatedRingBondPatternSwitching> SharedPointer;

            /**
             * \brief Sets the parent molecular graph and identifies its conjugated rings for tautomer enumeration.
             * \param parent_molgraph The molecular graph to be tautomerized.
             * \return \c true if at least one conjugated ring was found, and \c false otherwise.
             */
            bool setup(MolecularGraph& parent_molgraph);

            /**
             * \brief Returns the rule's identifier (Chem::TautomerizationType::CONJ_RING_BOND_SWITCH).
             * \return The rule identifier.
             */
            unsigned int getID() const;

            /**
             * \brief Generates the next bond-pattern-switched tautomer.
             * \param tautomer The tautomer output molecule object.
             * \return \c true if a tautomer was generated, and \c false if no more tautomers are available.
             */
            bool generate(Molecule& tautomer);

            /**
             * \brief Returns a deep copy of this rule instance.
             * \return A shared pointer to the cloned rule.
             */
            TautomerizationRule::SharedPointer clone() const;

          private:
            typedef std::vector<Fragment::SharedPointer> RingList;

            bool isConjugated(const Fragment& ring) const;
            bool hasHeteroSubstituent(const Atom& atom, const Fragment& ring) const;

            void flipBondOrders(Molecule& tautomer, const Fragment& ring) const;

            const MolecularGraph* parentMolGraph;
            RingList              conjRings;
            std::size_t           currRingIdx;
        };
    } // namespace Chem
} // namespace CDPL

#endif // CDPL_CHEM_CONJUGATEDRINGBONDPATTERNSWITCHING_HPP
