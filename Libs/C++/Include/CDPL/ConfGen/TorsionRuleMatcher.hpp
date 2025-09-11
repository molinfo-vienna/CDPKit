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

        class CDPL_CONFGEN_API TorsionRuleMatcher
        {

            typedef std::vector<TorsionRuleMatch> RuleMatchList;

          public:
            typedef RuleMatchList::const_iterator ConstMatchIterator;

            TorsionRuleMatcher();

            TorsionRuleMatcher(const TorsionLibrary::SharedPointer& lib);

            void findUniqueMappingsOnly(bool unique);

            bool findUniqueMappingsOnly() const;

            void findAllRuleMappings(bool all);

            bool findAllRuleMappings() const;

            void stopAtFirstMatchingRule(bool stop);

            bool stopAtFirstMatchingRule() const;

            void setTorsionLibrary(const TorsionLibrary::SharedPointer& lib);

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
