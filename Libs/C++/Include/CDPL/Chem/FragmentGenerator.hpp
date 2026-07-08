/* 
 * FragmentGenerator.hpp 
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
 * \brief Definition of class CDPL::Chem::FragmentGenerator.
 */

#ifndef CDPL_CHEM_FRAGMENTGENERATOR_HPP
#define CDPL_CHEM_FRAGMENTGENERATOR_HPP

#include <cstddef>
#include <vector>
#include <memory>
#include <functional>

#include "CDPL/Chem/APIPrefix.hpp"
#include "CDPL/Chem/MolecularGraph.hpp"
#include "CDPL/Chem/FragmentList.hpp"
#include "CDPL/Chem/SubstructureSearch.hpp"
#include "CDPL/Util/BitSet.hpp"


namespace CDPL
{

    namespace Chem
    {

        /**
         * \brief Generic rule-based molecule fragmentation engine that splits a molecular graph along
         *        bonds matching user-defined fragmentation rules.
         *
         * Fragmentation rules are added via addFragmentationRule() (each rule has a substructure pattern describing
         * a bond plus a numeric rule ID). Bonds matching any registered rule are scheduled for splitting,
         * unless a registered exclude pattern overrides the split. The optional fragment filter rejects
         * generated fragments based on a user-supplied predicate. The connectivity between the resulting
         * fragments is exposed via the FragmentLink list, recording for each cleaved bond the two adjacent
         * fragment indices, the cleaved bond, the matching rule and per-side atom labels.
         */
        class CDPL_CHEM_API FragmentGenerator
        {

          public:
            /**
             * \brief A reference-counted smart pointer [\ref SHPTR] for dynamically allocated \c %FragmentGenerator instances.
             */
            typedef std::shared_ptr<FragmentGenerator> SharedPointer;

            /**
             * \brief Type of a predicate accepting/rejecting a generated fragment.
             */
            typedef std::function<bool(const MolecularGraph&)> FragmentFilterFunction;

            /**
             * \brief A single fragmentation rule, consisting of a bond substructure match pattern and a numeric rule ID.
             */
            class CDPL_CHEM_API FragmentationRule
            {

              public:
                /**
                 * \brief Constructs the fragmentation rule.
                 * \param match_ptn The bond substructure match pattern (must match a single bond to be cleaved).
                 * \param id The rule identifier (forwarded to FragmentLink::getRuleID() for cleaved bonds).
                 */
                FragmentationRule(const MolecularGraph::SharedPointer& match_ptn, unsigned int id);

                /**
                 * \brief Returns the bond substructure match pattern of this rule.
                 * \return A \c const shared pointer to the match pattern molecular graph.
                 */
                const MolecularGraph::SharedPointer& getMatchPattern() const;

                /**
                 * \brief Sets the bond substructure match pattern of this rule.
                 * \param ptn The new bond substructure match pattern.
                 */
                void setMatchPattern(const MolecularGraph::SharedPointer& ptn);

                /**
                 * \brief Returns the rule identifier.
                 * \return The numeric rule ID.
                 */
                unsigned int getID() const;

                /**
                 * \brief Sets the rule identifier.
                 * \param id The new numeric rule ID.
                 */
                void setID(unsigned int id);

              private:
                MolecularGraph::SharedPointer matchPtn;
                unsigned int                  id;
            };

            /**
             * \brief A pattern descriptor specifying bonds that shall not be cleaved.
             *
             * An exclude pattern is either rule-specific (only the matching rule is suppressed) or generic
             * (all rules are suppressed for the matching bonds).
             */
            class CDPL_CHEM_API ExcludePattern
            {

              public:
                /**
                 * \brief Constructs a rule-specific exclude pattern.
                 * \param match_ptn The substructure match pattern.
                 * \param rule_id The rule ID this exclusion applies to.
                 */
                ExcludePattern(const MolecularGraph::SharedPointer& match_ptn, unsigned int rule_id);

                /**
                 * \brief Constructs a generic exclude pattern (applies to all fragmentation rules).
                 * \param match_ptn The substructure match pattern.
                 */
                ExcludePattern(const MolecularGraph::SharedPointer& match_ptn);

                /**
                 * \brief Returns the substructure match pattern.
                 * \return A \c const shared pointer to the match pattern molecular graph.
                 */
                const MolecularGraph::SharedPointer& getMatchPattern() const;

                /**
                 * \brief Sets the substructure match pattern.
                 * \param ptn The new substructure match pattern.
                 */
                void setMatchPattern(const MolecularGraph::SharedPointer& ptn);

                /**
                 * \brief Returns the rule ID this exclusion applies to (only meaningful when isGeneric() is \c false).
                 * \return The rule ID.
                 */
                unsigned int getRuleID() const;

                /**
                 * \brief Sets the rule ID this exclusion applies to.
                 * \param id The new rule ID.
                 */
                void setRuleID(unsigned int id);

                /**
                 * \brief Tells whether this exclude pattern applies to all rules (generic) or only to a specific one.
                 * \return \c true if the pattern is generic, and \c false otherwise.
                 */
                bool isGeneric() const;

                /**
                 * \brief Sets whether this exclude pattern is generic.
                 * \param generic If \c true, the pattern applies to all rules. If \c false, only to the configured rule ID.
                 */
                void setGeneric(bool generic);

              private:
                MolecularGraph::SharedPointer matchPtn;
                unsigned int                  ruleID;
                bool                          generic;
            };

            /**
             * \brief Records the connectivity between two fragments produced by a single bond cleavage.
             */
            class CDPL_CHEM_API FragmentLink
            {

              public:
                /**
                 * \brief Constructs the fragment link.
                 * \param frag1_idx The index of the first fragment in the output fragment list.
                 * \param frag2_idx The index of the second fragment in the output fragment list.
                 * \param bond The cleaved bond (from the original molecular graph).
                 * \param rule_id The rule ID that triggered the cleavage.
                 * \param atom1_label The label assigned to the first atom of the cleaved bond.
                 * \param atom2_label The label assigned to the second atom of the cleaved bond.
                 */
                FragmentLink(std::size_t frag1_idx, std::size_t frag2_idx, const Bond& bond,
                             unsigned int rule_id, unsigned int atom1_label, unsigned int atom2_label);

                /**
                 * \brief Returns the index of the first fragment in the output fragment list.
                 * \return The first fragment index.
                 */
                std::size_t getFragment1Index() const;

                /**
                 * \brief Returns the index of the second fragment in the output fragment list.
                 * \return The second fragment index.
                 */
                std::size_t getFragment2Index() const;

                /**
                 * \brief Returns the cleaved bond from the original molecular graph.
                 * \return A \c const reference to the bond.
                 */
                const Bond& getBond() const;

                /**
                 * \brief Returns the rule ID that triggered the cleavage of this bond.
                 * \return The rule ID.
                 */
                unsigned int getRuleID() const;

                /**
                 * \brief Returns the label of the first atom of the cleaved bond.
                 * \return The first atom label.
                 */
                unsigned int getAtom1Label() const;

                /**
                 * \brief Returns the label of the second atom of the cleaved bond.
                 * \return The second atom label.
                 */
                unsigned int getAtom2Label() const;

              private:
                std::size_t  frag1Idx;
                std::size_t  frag2Idx;
                const Bond*  bond;
                unsigned int ruleID;
                unsigned int atom1Label;
                unsigned int atom2Label;
            };

          private:
            typedef std::vector<FragmentationRule> FragmentationRuleList;
            typedef std::vector<ExcludePattern>    ExcludePatternList;
            typedef std::vector<FragmentLink>      FragmentLinkList;

          public:
            /**
             * \brief A constant iterator over the registered fragmentation rules.
             */
            typedef FragmentationRuleList::const_iterator ConstFragmentationRuleIterator;
            
            /**
             * \brief A mutable iterator over the registered fragmentation rules.
             */
            typedef FragmentationRuleList::iterator       FragmentationRuleIterator;

            /**
             * \brief A constant iterator over the registered exclude patterns.
             */
            typedef ExcludePatternList::const_iterator ConstExcludePatternIterator;
            
            /**
             * \brief A mutable iterator over the registered exclude patterns.
             */
            typedef ExcludePatternList::iterator       ExcludePatternIterator;

            /**
             * \brief A constant iterator over the generated fragment links.
             */
            typedef FragmentLinkList::const_iterator ConstFragmentLinkIterator;

            /**
             * \brief Constructs the \c %FragmentGenerator instance.
             */
            FragmentGenerator();

            /**
             * \brief Constructs a copy of the \c %FragmentGenerator instance \a gen.
             * \param gen The \c %FragmentGenerator to copy.
             */
            FragmentGenerator(const FragmentGenerator& gen);

            /**
             * \brief Virtual destructor.
             */
            virtual ~FragmentGenerator() {}

            /**
             * \brief Replaces the state of this generator by a copy of the state of \a gen.
             * \param gen The \c %FragmentGenerator instance to copy.
             * \return A reference to itself.
             */
            FragmentGenerator& operator=(const FragmentGenerator& gen);

            /**
             * \brief Registers a new fragmentation rule by its bond substructure match pattern and rule ID.
             * \param match_ptn The bond substructure match pattern (must match a single bond to be cleaved).
             * \param rule_id The rule identifier.
             */
            void addFragmentationRule(const MolecularGraph::SharedPointer& match_ptn, unsigned int rule_id);

            /**
             * \brief Appends a copy of the pre-built fragmentation rule \a rule.
             * \param rule The rule to copy and register.
             */
            void addFragmentationRule(const FragmentationRule& rule);

            /**
             * \brief Returns the fragmentation rule at index \a idx.
             * \param idx The zero-based rule index.
             * \return A \c const reference to the rule.
             * \throw Base::IndexError if \a idx is not in the range [0, getNumFragmentationRules()).
             */
            const FragmentationRule& getFragmentationRule(std::size_t idx) const;

            /**
             * \brief Returns the fragmentation rule at index \a idx.
             * \param idx The zero-based rule index.
             * \return A reference to the rule.
             * \throw Base::IndexError if \a idx is not in the range [0, getNumFragmentationRules()).
             */
            FragmentationRule& getFragmentationRule(std::size_t idx);

            /**
             * \brief Returns a constant iterator pointing to the first registered fragmentation rule.
             * \return A constant iterator pointing to the first rule.
             */
            ConstFragmentationRuleIterator getFragmentationRulesBegin() const;

            /**
             * \brief Returns a constant iterator pointing one past the last registered fragmentation rule.
             * \return A constant iterator pointing one past the last rule.
             */
            ConstFragmentationRuleIterator getFragmentationRulesEnd() const;

            /**
             * \brief Returns a mutable iterator pointing to the first registered fragmentation rule.
             * \return A mutable iterator pointing to the first rule.
             */
            FragmentationRuleIterator getFragmentationRulesBegin();

            /**
             * \brief Returns a mutable iterator pointing one past the last registered fragmentation rule.
             * \return A mutable iterator pointing one past the last rule.
             */
            FragmentationRuleIterator getFragmentationRulesEnd();

            /**
             * \brief Removes the fragmentation rule at index \a idx.
             * \param idx The zero-based rule index.
             * \throw Base::IndexError if \a idx is not in the range [0, getNumFragmentationRules()).
             */
            void removeFragmentationRule(std::size_t idx);

            /**
             * \brief Returns the number of registered fragmentation rules.
             * \return The rule count.
             */
            std::size_t getNumFragmentationRules() const;

            /**
             * \brief Removes all registered fragmentation rules.
             */
            void clearFragmentationRules();

            /**
             * \brief Registers a rule-specific exclude pattern.
             * \param match_ptn The substructure match pattern.
             * \param rule_id The rule ID this exclusion applies to.
             */
            void addExcludePattern(const MolecularGraph::SharedPointer& match_ptn, unsigned int rule_id);

            /**
             * \brief Registers a generic exclude pattern (applies to all fragmentation rules).
             * \param match_ptn The substructure match pattern.
             */
            void addExcludePattern(const MolecularGraph::SharedPointer& match_ptn);

            /**
             * \brief Appends a copy of the pre-built exclude pattern \a excl_ptn.
             * \param excl_ptn The exclude pattern to copy and register.
             */
            void addExcludePattern(const ExcludePattern& excl_ptn);

            /**
             * \brief Returns the exclude pattern at index \a idx.
             * \param idx The zero-based pattern index.
             * \return A \c const reference to the exclude pattern.
             * \throw Base::IndexError if \a idx is not in the range [0, getNumExcludePatterns()).
             */
            const ExcludePattern& getExcludePattern(std::size_t idx) const;

            /**
             * \brief Returns the exclude pattern at index \a idx.
             * \param idx The zero-based pattern index.
             * \return A reference to the exclude pattern.
             * \throw Base::IndexError if \a idx is not in the range [0, getNumExcludePatterns()).
             */
            ExcludePattern& getExcludePattern(std::size_t idx);

            /**
             * \brief Returns a constant iterator pointing to the first registered exclude pattern.
             * \return A constant iterator pointing to the first exclude pattern.
             */
            ConstExcludePatternIterator getExcludePatternsBegin() const;

            /**
             * \brief Returns a constant iterator pointing one past the last registered exclude pattern.
             * \return A constant iterator pointing one past the last exclude pattern.
             */
            ConstExcludePatternIterator getExcludePatternsEnd() const;

            /**
             * \brief Returns a mutable iterator pointing to the first registered exclude pattern.
             * \return A mutable iterator pointing to the first exclude pattern.
             */
            ExcludePatternIterator getExcludePatternsBegin();

            /**
             * \brief Returns a mutable iterator pointing one past the last registered exclude pattern.
             * \return A mutable iterator pointing one past the last exclude pattern.
             */
            ExcludePatternIterator getExcludePatternsEnd();

            /**
             * \brief Removes the exclude pattern at index \a idx.
             * \param idx The zero-based pattern index.
             * \throw Base::IndexError if \a idx is not in the range [0, getNumExcludePatterns()).
             */
            void removeExcludePattern(std::size_t idx);

            /**
             * \brief Returns the number of registered exclude patterns.
             * \return The exclude-pattern count.
             */
            std::size_t getNumExcludePatterns() const;

            /**
             * \brief Removes all registered exclude patterns.
             */
            void clearExcludePatterns();

            /**
             * \brief Tells whether the split (cleaved) bonds are retained in the output fragments.
             * \return \c true if split bonds are retained, and \c false otherwise.
             */
            bool splitBondsIncluded() const;

            /**
             * \brief Specifies whether the split (cleaved) bonds shall be retained in the output fragments.
             * \param include If \c true, the cleaved bonds remain part of the adjacent output fragments.
             */
            void includeSplitBonds(bool include);

            /**
             * \brief Returns the predicate used to filter the generated fragments.
             * \return A \c const reference to the fragment filter function.
             */
            const FragmentFilterFunction& getFragmentFilterFunction() const;

            /**
             * \brief Sets the predicate used to filter the generated fragments (fragments for which the
             *        predicate returns \c false are discarded).
             * \param func The new fragment filter function.
             */
            void setFragmentFilterFunction(const FragmentFilterFunction& func);

            /**
             * \brief Performs the fragmentation of \a molgraph and appends the resulting fragments to \a frag_list.
             * \param molgraph The molecular graph to fragment.
             * \param frag_list The output fragment list.
             * \param append If \c true, new fragments are appended to \a frag_list. Otherwise, the list is cleared first.
             */
            void generate(const MolecularGraph& molgraph, FragmentList& frag_list, bool append = false);

            /**
             * \brief Returns the number of fragment links produced by the most recent generate() call.
             * \return The fragment link count.
             */
            std::size_t getNumFragmentLinks() const;

            /**
             * \brief Returns the fragment link at index \a idx.
             * \param idx The zero-based link index.
             * \return A \c const reference to the fragment link.
             * \throw Base::IndexError if \a idx is not in the range [0, getNumFragmentLinks()).
             */
            const FragmentLink& getFragmentLink(std::size_t idx) const;

            /**
             * \brief Returns a constant iterator pointing to the first fragment link.
             * \return A constant iterator pointing to the first fragment link.
             */
            ConstFragmentLinkIterator getFragmentLinksBegin() const;

            /**
             * \brief Returns a constant iterator pointing one past the last fragment link.
             * \return A constant iterator pointing one past the last fragment link.
             */
            ConstFragmentLinkIterator getFragmentLinksEnd() const;

          private:
            void init(const MolecularGraph& molgraph);

            void processFragRuleMatches(const MolecularGraph& molgraph, const FragmentationRule& rule);
            void processExcludePatternMatches(const MolecularGraph& molgraph, const ExcludePattern& ptn);
            void splitIntoFragments(const MolecularGraph& molgraph, FragmentList& frag_list, bool append);
            void growFragment(const Chem::Atom& atom, const Chem::MolecularGraph& molgraph, Chem::Fragment& frag);

            std::size_t findContainingFragment(const Chem::Atom& atom, const FragmentList& frag_list,
                                               std::size_t start_idx) const;

            struct SplitBondData
            {

                const Bond*  bond;
                unsigned int ruleID;
                unsigned int atom1Label;
                unsigned int atom2Label;
            };

            typedef std::vector<SplitBondData> SplitBondDataArray;

            FragmentationRuleList  fragRules;
            ExcludePatternList     exclPatterns;
            FragmentLinkList       fragLinks;
            bool                   incSplitBonds;
            FragmentFilterFunction fragFilterFunc;
            SubstructureSearch     subSearch;
            Util::BitSet           splitBondMask;
            Util::BitSet           visAtomMask;
            SplitBondDataArray     splitBondData;
        };
    } // namespace Chem
} // namespace CDPL

#endif // CDPL_CHEM_FRAGMENTGENERATOR_HPP
