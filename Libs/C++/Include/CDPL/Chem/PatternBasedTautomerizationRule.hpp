/* 
 * PatternBasedTautomerizationRule.hpp 
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
 * \brief Definition of class CDPL::Chem::PatternBasedTautomerizationRule.
 */

#ifndef CDPL_CHEM_PATTERNBASEDTAUTOMERIZATIONRULE_HPP
#define CDPL_CHEM_PATTERNBASEDTAUTOMERIZATIONRULE_HPP

#include <cstddef>
#include <vector>
#include <algorithm>
#include <iterator>
#include <memory>
#include <functional>

#include "CDPL/Chem/APIPrefix.hpp"
#include "CDPL/Chem/TautomerizationRule.hpp"
#include "CDPL/Chem/MolecularGraph.hpp"
#include "CDPL/Chem/SubstructureSearch.hpp"
#include "CDPL/Util/BitSet.hpp"
#include "CDPL/Util/ObjectStack.hpp"


namespace CDPL
{

    namespace Chem
    {

        /**
         * \brief Substructure search pattern-based implementation of the Chem::TautomerizationRule interface.
         *
         * The rule is configured with a set of <em>transformation patterns</em> describing
         * the source substructure together with per-atom pair bond order changes that apply when the pattern
         * matches plus optional <em>exclude patterns</em> (substructures that, when present, suppress the
         * application of the rule). The setup() / generate() pair from the base class then enumerates the
         * tautomers reachable from the parent molecular graph by applying the configured transformations.
         */
        class CDPL_CHEM_API PatternBasedTautomerizationRule : public TautomerizationRule
        {

          public:
            /**
             * \brief A reference-counted smart pointer [\ref SHPTR] for dynamically allocated \c %PatternBasedTautomerizationRule instances.
             */
            typedef std::shared_ptr<PatternBasedTautomerizationRule> SharedPointer;

            /**
             * \brief Encodes a single bond order change between two pattern atoms applied when the parent
             *        transformation pattern matches.
             */
            struct BondOrderChange
            {

                /**
                 * \brief Pattern atom mapping ID of the first atom of the bond whose order changes.
                 */
                std::size_t atom1ID;
    
                /**
                 * \brief Pattern atom mapping ID of the second atom of the bond whose order changes.
                 */
                std::size_t atom2ID;
    
                /**
                 * \brief Signed bond order delta applied to the matched bond (positive = increase, negative = decrease).
                 */
                long        orderChange;
            };

            /**
             * \brief Constructs the \c %PatternBasedTautomerizationRule instance with the given rule identifier.
             * \param rule_id The rule identifier (returned by getID()).
             */
            PatternBasedTautomerizationRule(unsigned int rule_id);

            /**
             * \brief Constructs a \c %PatternBasedTautomerizationRule instance that is copy of \a rule.
             * \param rule The other rule to copy.
             */
            PatternBasedTautomerizationRule(const PatternBasedTautomerizationRule& rule);

            /**
             * \brief Replaces the state of this rule by a copy of the state of \a rule.
             * \param rule The other rule to copy.
             * \return A reference to itself.
             */
            PatternBasedTautomerizationRule& operator=(const PatternBasedTautomerizationRule& rule);

            /**
             * \brief Registers a new transformation pattern.
             *
             * Bond order changes are read from the iterator range [\a bond_chgs_beg, \a bond_chgs_end).
             * Each element must be a value of type BondOrderChange that specifies the bond to change
             * via the mapping IDs of the match pattern atoms.
             *
             * \tparam Iter Input iterator type yielding BondOrderChange values.
             * \param molgraph The match pattern specifying the substructure to transform.
             * \param bond_chgs_beg Iterator pointing to the first bond order change.
             * \param bond_chgs_end Iterator pointing one past the last bond order change.
             */
            template <typename Iter>
            void addTransformationPattern(const MolecularGraph::SharedPointer& molgraph, Iter bond_chgs_beg, Iter bond_chgs_end)
            {
                structPatterns.push_back(molgraph);
                patternSubSearchList.push_back(SubstructureSearch::SharedPointer(new SubstructureSearch(*molgraph)));
                patternBondChangeLists.resize(patternBondChangeLists.size() + 1);

                std::copy(bond_chgs_beg, bond_chgs_end, std::back_inserter(patternBondChangeLists.back()));
            }

            /**
             * \brief Registers a rule exclude pattern.
             *
             * Any matching substructures present in the parent molecular
             * graph will be excluded from structure transformations.
             *
             * \param molgraph The exclude match pattern.
             */
            void addExcludePattern(const MolecularGraph::SharedPointer& molgraph);

            /**
             * \brief Appends all registered search patterns of \a rule to the exclude pattern list of this rule.
             * \param rule The source rule whose search patterns shall be added.
             */
            void addExcludePatterns(const PatternBasedTautomerizationRule& rule);

            /**
             * \brief Removes all registered exclude patterns.
             */
            void clearExcludePatterns();

            bool setup(MolecularGraph& parent_molgraph);

            unsigned int getID() const;

            bool generate(Molecule& tautomer);

            TautomerizationRule::SharedPointer clone() const;

          private:
            bool applyTransformation(Molecule& tautomer);

            Atom* getTautomerAtom(Molecule& tautomer, std::size_t ptn_atom_id, const AtomMapping& mapping) const;

            void freeBitSet(Util::BitSet* bset);

            void createMatchedBondMask(const BondMapping& mapping, Util::BitSet& bond_mask) const;

            typedef std::vector<BondOrderChange>                   BondOrderChangeList;
            typedef std::vector<BondOrderChangeList>               BondOrderChangeListArray;
            typedef std::vector<MolecularGraph::SharedPointer>     StructPatternList;
            typedef std::vector<SubstructureSearch::SharedPointer> SubstructureSearchList;
            typedef std::vector<Util::BitSet*>                     BitSetList;
            typedef Util::ObjectStack<Util::BitSet>                BitSetCache;

            unsigned int             ruleID;
            StructPatternList        structPatterns;
            StructPatternList        excludePatterns;
            BondOrderChangeListArray patternBondChangeLists;
            SubstructureSearchList   patternSubSearchList;
            SubstructureSearchList   excludeSubSearchList;
            const MolecularGraph*    parentMolGraph;
            std::size_t              currPatternIdx;
            std::size_t              currMappingIdx;
            Util::BitSet             bondMask;
            BitSetList               excludeMatches;
            BitSetCache              bitSetCache;
        };
    } // namespace Chem
} // namespace CDPL

#endif // CDPL_CHEM_PATTERNBASEDTAUTOMERIZATIONRULE_HPP
