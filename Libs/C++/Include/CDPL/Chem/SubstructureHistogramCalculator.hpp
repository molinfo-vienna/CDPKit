/* 
 * SubstructureHistogramCalculator.hpp 
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
 * \brief Definition of class CDPL::Chem::SubstructureHistogramCalculator.
 */

#ifndef CDPL_CHEM_SUBSTRUCTUREHISTOGRAMCALCULATOR_HPP
#define CDPL_CHEM_SUBSTRUCTUREHISTOGRAMCALCULATOR_HPP

#include <cstddef>
#include <vector>
#include <map>
#include <utility>
#include <memory>
#include <functional>

#include "CDPL/Chem/APIPrefix.hpp"
#include "CDPL/Chem/MolecularGraph.hpp"
#include "CDPL/Chem/SubstructureSearch.hpp"
#include "CDPL/Util/BitSet.hpp"


namespace CDPL
{

    namespace Chem
    {

        /**
         * \brief Counts occurrences of registered substructure patterns in a molecular graph,
         *        emitting the per-pattern hit counts into a user-supplied histogram container.
         *
         * Patterns are added via addPattern() (each pattern carries a query molecular graph, a numeric ID, a priority and
         * match-handling flags). On calculate() the registered patterns are run in priority order
         * against the input molecular graph. Matched atom/bond regions are masked so that subsequent
         * lower-priority patterns cannot re-count overlapping substructures. The per-pattern hit count
         * is then forwarded to the histogram via the expression \c histo[id]++ for every accepted match.
         */
        class CDPL_CHEM_API SubstructureHistogramCalculator
        {

          public:
            class Pattern;

          private:
            typedef std::vector<Pattern> PatternList;

          public:
            /** \brief A reference-counted smart pointer [\ref SHPTR] for dynamically allocated \c %SubstructureHistogramCalculator instances. */
            typedef std::shared_ptr<SubstructureHistogramCalculator> SharedPointer;

            /** \brief A constant iterator over the registered patterns. */
            typedef PatternList::const_iterator ConstPatternIterator;
            /** \brief A mutable iterator over the registered patterns. */
            typedef PatternList::iterator       PatternIterator;

            /**
             * \brief Stores a single substructure query molecular graph, its histogram ID, its priority and match-handling flags.
             */
            class CDPL_CHEM_API Pattern
            {

              public:
                /**
                 * \brief Constructs a \c %Pattern instance for the specified values.
                 * \param molgraph The query molecular graph.
                 * \param id The histogram bin ID to which matches of this pattern contribute.
                 * \param priority The priority of this pattern (higher priority patterns are evaluated first).
                 * \param all_matches If \c true, every match of \a molgraph in the target is processed. If \c false, only the first match is processed.
                 * \param unique_matches If \c true, only one of multiple equivalent substructure mappings is processed per match.
                 */
                Pattern(const MolecularGraph::SharedPointer& molgraph, std::size_t id, std::size_t priority = 0,
                        bool all_matches = true, bool unique_matches = true);

                /**
                 * \brief Returns the query molecular graph of this pattern.
                 * \return A \c const shared pointer to the query molecular graph.
                 */
                const MolecularGraph::SharedPointer& getStructure() const;

                /**
                 * \brief Returns the histogram bin ID of this pattern.
                 * \return The histogram bin ID.
                 */
                std::size_t getID() const;

                /**
                 * \brief Returns the pattern priority.
                 * \return The priority value.
                 */
                std::size_t getPriority() const;

                /**
                 * \brief Tells whether all substructure matches are processed.
                 * \return \c true if all matches are processed, and \c false if only the first match is.
                 */
                bool processAllMatches() const;

                /**
                 * \brief Tells whether only one of multiple equivalent mappings is processed per match.
                 * \return \c true if unique-only mode is enabled, and \c false otherwise.
                 */
                bool processUniqueMatchesOnly() const;

              private:
                MolecularGraph::SharedPointer molGraph;
                std::size_t                   id;
                std::size_t                   priority;
                bool                          allMatches;
                bool                          uniqueMatches;
            };

            /**
             * \brief Constructs an empty \c %SubstructureHistogramCalculator instance.
             */
            SubstructureHistogramCalculator();

            /**
             * \brief Constructs a copy of the \c %SubstructureHistogramCalculator instance \a gen.
             * \param gen The \c %SubstructureHistogramCalculator to copy.
             */
            SubstructureHistogramCalculator(const SubstructureHistogramCalculator& gen);

            /**
             * \brief Registers a new pattern by its query molecular graph and per-pattern settings.
             * \param molgraph The query molecular graph.
             * \param id The histogram bin ID to which matches of this pattern contribute.
             * \param priority The pattern's priority (higher priority patterns are evaluated first).
             * \param all_matches If \c true, every match of the query is processed. Otherwise, only the first.
             * \param unique_matches If \c true, only one of multiple equivalent substructure mappings is processed per match.
             */
            void addPattern(const MolecularGraph::SharedPointer& molgraph, std::size_t id, std::size_t priority = 0,
                            bool all_matches = true, bool unique_matches = true);

            /**
             * \brief Appends a copy of the pre-built pattern \a pattern.
             * \param pattern The pattern to copy and register.
             */
            void addPattern(const Pattern& pattern);

            /**
             * \brief Returns the registered pattern at index \a idx.
             * \param idx The zero-based pattern index.
             * \return A \c const reference to the pattern.
             * \throw Base::IndexError if the number of patterns is zero or \a idx is not in the range [0, getNumPatterns() - 1].
             */
            const Pattern& getPattern(std::size_t idx) const;

            /**
             * \brief Removes the registered pattern at index \a idx.
             * \param idx The zero-based pattern index.
             * \throw Base::IndexError if the number of patterns is zero or \a idx is not in the range [0, getNumPatterns() - 1].
             */
            void removePattern(std::size_t idx);

            /**
             * \brief Removes the registered pattern referenced by \a it.
             * \param it Iterator referencing the pattern to remove.
             * \throw Base::IndexError if \a it is not in the range [getPatternsBegin(), getPatternsEnd() - 1].
             */
            void removePattern(const PatternIterator& it);

            /**
             * \brief Removes all registered patterns.
             */
            void clear();

            /**
             * \brief Returns the number of registered patterns.
             * \return The pattern count.
             */
            std::size_t getNumPatterns() const;

            /**
             * \brief Returns a constant iterator pointing to the first registered pattern.
             * \return A constant iterator pointing to the first pattern.
             */
            ConstPatternIterator getPatternsBegin() const;

            /**
             * \brief Returns a constant iterator pointing one past the last registered pattern.
             * \return A constant iterator pointing one past the last pattern.
             */
            ConstPatternIterator getPatternsEnd() const;

            /**
             * \brief Returns a mutable iterator pointing to the first registered pattern.
             * \return A mutable iterator pointing to the first pattern.
             */
            PatternIterator getPatternsBegin();

            /**
             * \brief Returns a mutable iterator pointing one past the last registered pattern.
             * \return A mutable iterator pointing one past the last pattern.
             */
            PatternIterator getPatternsEnd();

            /**
             * \brief Returns a constant iterator pointing to the first registered pattern (range-based for support).
             * \return A constant iterator pointing to the first pattern.
             */
            ConstPatternIterator begin() const;

            /**
             * \brief Returns a constant iterator pointing one past the last registered pattern (range-based for support).
             * \return A constant iterator pointing one past the last pattern.
             */
            ConstPatternIterator end() const;

            /**
             * \brief Returns a mutable iterator pointing to the first registered pattern (range-based for support).
             * \return A mutable iterator pointing to the first pattern.
             */
            PatternIterator begin();

            /**
             * \brief Returns a mutable iterator pointing one past the last registered pattern (range-based for support).
             * \return A mutable iterator pointing one past the last pattern.
             */
            PatternIterator end();

            /**
             * \brief Counts substructure occurrences in \a molgraph and writes the per-pattern hit counts to \a histo.
             *
             * For every accepted match, the histogram is updated via \c histo[id] += 1 with the ID being the
             * histogram-bin ID of the matching pattern.
             *
             * \tparam T The histogram type (must support \c operator[] returning an arithmetic value).
             * \param molgraph The molecular graph to be analyzed.
             * \param histo The histogram receiving the hit counts.
             */
            template <typename T>
            void calculate(const MolecularGraph& molgraph, T& histo);

            /**
             * \brief Replaces the state of this calculator by a copy of the state of \a gen.
             * \param gen The source \c %SubstructureHistogramCalculator.
             * \return A reference to itself.
             */
            SubstructureHistogramCalculator& operator=(const SubstructureHistogramCalculator& gen);

          private:
            typedef std::function<void(std::size_t)> HistoUpdateFunction;

            template <typename T>
            class HistoUpdateFunctor
            {

              public:
                HistoUpdateFunctor(T& histo):
                    histo(histo) {}

                void operator()(std::size_t id)
                {
                    histo[id] += 1;
                }

              private:
                T& histo;
            };

            void doCalculate(const MolecularGraph& molgraph, const HistoUpdateFunction& func);

            void init(const MolecularGraph& molgraph);

            void processPattern(const Pattern& ptn, const HistoUpdateFunction& func);
            bool processMatch(const AtomBondMapping& mapping, const Pattern& ptn, const HistoUpdateFunction& func);

            typedef std::pair<Util::BitSet, Util::BitSet> AtomBondMask;
            typedef std::map<std::size_t, AtomBondMask>   PriorityToAtomBondMaskMap;

            const MolecularGraph*     molGraph;
            PatternList               patterns;
            SubstructureSearch        subSearch;
            PriorityToAtomBondMaskMap matchedSubstructMasks;
            AtomBondMask              testingAtomBondMask;
            Util::BitSet              tmpMask;
        };
    } // namespace Chem
} // namespace CDPL


template <typename T>
void CDPL::Chem::SubstructureHistogramCalculator::calculate(const MolecularGraph& molgraph, T& histo)
{
    doCalculate(molgraph, HistoUpdateFunctor<T>(histo));
}

#endif // CDPL_CHEM_SUBSTRUCTUREHISTOGRAMCALCULATOR_HPP
