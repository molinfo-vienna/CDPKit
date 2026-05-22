/* 
 * TorsionRuleMatcher.hpp 
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
 * \brief Definition of class CDPL::ConfGen::TorsionRuleMatcher.
 */

#ifndef CDPL_CONFGEN_TORSIONRULEMATCHER_HPP
#define CDPL_CONFGEN_TORSIONRULEMATCHER_HPP

#include <vector>

#include "CDPL/ConfGen/APIPrefix.hpp"
#include "CDPL/ConfGen/TorsionLibrary.hpp"
#include "CDPL/ConfGen/TorsionRuleMatch.hpp"
#include "CDPL/Chem/SubstructureSearch.hpp"


namespace CDPL
{

    namespace ConfGen
    {

        /**
         * \brief Finds torsion rules from a TorsionLibrary that apply to a given rotatable bond.
         *
         * For a queried bond in a molecular graph the matcher iterates the configured TorsionLibrary
         * (top-down through torsion categories) and reports every rule whose central-bond SMARTS
         * pattern matches at the queried bond. Each match is stored as a TorsionRuleMatch object
         * providing the four matching atoms, the matched rule and the underlying atom/bond mapping.
         */
        class CDPL_CONFGEN_API TorsionRuleMatcher
        {

            typedef std::vector<TorsionRuleMatch> RuleMatchList;

          public:
            /** \brief A constant iterator over the stored torsion rule matches. */
            typedef RuleMatchList::const_iterator ConstMatchIterator;

            /**
             * \brief Constructs the \c %TorsionRuleMatcher instance without an associated torsion library.
             */
            TorsionRuleMatcher();

            /**
             * \brief Constructs the \c %TorsionRuleMatcher instance and associates it with \a lib.
             * \param lib The torsion library to query.
             */
            TorsionRuleMatcher(const TorsionLibrary::SharedPointer& lib);

            /**
             * \brief Specifies whether only unique substructure mappings shall be reported during matching.
             * \param unique If \c true, only one of multiple equivalent mappings is reported per rule.
             */
            void findUniqueMappingsOnly(bool unique);

            /**
             * \brief Tells whether only unique substructure mappings are reported during matching.
             * \return \c true if only unique mappings are reported, and \c false otherwise.
             */
            bool findUniqueMappingsOnly() const;

            /**
             * \brief Specifies whether all matching rules shall be reported (instead of just the most-specific one).
             * \param all If \c true, every matching rule across all categories is reported.
             */
            void findAllRuleMappings(bool all);

            /**
             * \brief Tells whether all matching rules are reported during matching.
             * \return \c true if all matching rules are reported, and \c false otherwise.
             */
            bool findAllRuleMappings() const;

            /**
             * \brief Specifies whether the matching process shall stop at the first rule that produces matches.
             * \param stop If \c true, matching stops as soon as a rule yields at least one match.
             */
            void stopAtFirstMatchingRule(bool stop);

            /**
             * \brief Tells whether matching stops at the first rule that produces matches.
             * \return \c true if matching stops at the first matching rule, and \c false otherwise.
             */
            bool stopAtFirstMatchingRule() const;

            /**
             * \brief Sets the torsion library to query.
             * \param lib The new torsion library.
             */
            void setTorsionLibrary(const TorsionLibrary::SharedPointer& lib);

            /**
             * \brief Returns the currently associated torsion library.
             * \return A \c const reference to the torsion library smart pointer.
             */
            const TorsionLibrary::SharedPointer& getTorsionLibrary() const;

            /**
             * \brief Returns the number of stored torsion rule matches found by calls to findMatches().
             * \return The number of stored torsion rule matches.
             */
            std::size_t getNumMatches() const;

            /**
             * \brief Returns a \c const reference to the stored torsion rule match object at index \a idx.
             * \param idx The zero-based index of the torsion rule match object to return.
             * \return A \c const reference to the torsion rule match object at index \a idx.
             * \throw Base::IndexError if no torsion rule matches are available or \a idx is not in the range [0, getNumMatches() - 1].
             */
            const TorsionRuleMatch& getMatch(std::size_t idx) const;

            /**
             * \brief Returns a constant iterator pointing to the beginning of the stored torsion rule matches.
             * \return A constant iterator pointing to the beginning of the stored torsion rule matches.
             */
            ConstMatchIterator getMatchesBegin() const;

            /**
             * \brief Returns a constant iterator pointing to the end of the stored torsion rule matches.
             * \return A constant iterator pointing to the end of the stored torsion rule matches.
             */
            ConstMatchIterator getMatchesEnd() const;

            /**
             * \brief Returns a constant iterator pointing to the beginning of the stored torsion rule matches.
             * \return A constant iterator pointing to the beginning of the stored torsion rule matches.
             */
            ConstMatchIterator begin() const;

            /**
             * \brief Returns a constant iterator pointing to the end of the stored torsion rule matches.
             * \return A constant iterator pointing to the end of the stored torsion rule matches.
             */
            ConstMatchIterator end() const;

            /**
             * \brief Searches the associated TorsionLibrary for rules that apply to the bond \a bond of \a molgraph.
             * \param bond The rotatable bond for which matching torsion rules are sought.
             * \param molgraph The molecular graph the bond belongs to.
             * \param append If \c true, new matches are appended to the previously stored ones; otherwise stored matches are cleared first.
             * \return \c true if at least one matching rule was found, and \c false otherwise.
             */
            bool findMatches(const Chem::Bond& bond, const Chem::MolecularGraph& molgraph, bool append = false);

          private:
            bool findMatchingRules(const TorsionCategory& tor_cat, const Chem::Bond& bond, const Chem::MolecularGraph& molgraph);
            bool getRuleMatches(const TorsionRule& rule, const Chem::Bond& bond, const Chem::MolecularGraph& molgraph);
            bool matchesCategory(const TorsionCategory& tor_cat, const Chem::Bond& bond, const Chem::MolecularGraph& molgraph);

            void outputMatch(const Chem::AtomBondMapping& ab_mapping, const Chem::Bond& bond, const TorsionRule& rule);

            std::size_t getCentralBondIndex(const Chem::MolecularGraph& ptn) const;

            TorsionLibrary::SharedPointer torLib;
            Chem::SubstructureSearch      subSearch;
            bool                          uniqueMappingsOnly;
            bool                          stopAtFirstRule;
            RuleMatchList                 matches;
        };
    } // namespace ConfGen
} // namespace CDPL

#endif // CDPL_CONFGEN_TORSIONRULEMATCHER_HPP
