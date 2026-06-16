/* 
 * PatternAtomTyper.hpp 
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
 * \brief Definition of class CDPL::Chem::PatternAtomTyper.
 */

#ifndef CDPL_CHEM_PATTERNATOMTYPER_HPP
#define CDPL_CHEM_PATTERNATOMTYPER_HPP

#include <cstddef>
#include <vector>
#include <memory>

#include "CDPL/Chem/APIPrefix.hpp"
#include "CDPL/Chem/MolecularGraph.hpp"
#include "CDPL/Chem/SubstructureSearch.hpp"
#include "CDPL/Util/BitSet.hpp"


namespace CDPL
{

    namespace Chem
    {

        /**
         * \brief Assigns numeric labels to the atoms of a molecular graph by SMARTS-pattern matching.
         *
         * Patterns are added via addPattern() (each pattern carries an atom-label value, a priority and
         * match-handling flags). On execute() the typer iterates the registered patterns in priority order,
         * runs each as a substructure query and assigns the corresponding atom label to every matched atom
         * unless the atom has already received a label from a higher-priority pattern.
         */
        class CDPL_CHEM_API PatternAtomTyper
        {

          public:
            class Pattern;

          private:
            typedef std::vector<Pattern>     PatternList;
            typedef std::vector<std::size_t> SizeTypeArray;

          public:
            /** \brief A reference-counted smart pointer [\ref SHPTR] for dynamically allocated \c %PatternAtomTyper instances. */
            typedef std::shared_ptr<PatternAtomTyper> SharedPointer;

            /** \brief A constant iterator over the registered patterns. */
            typedef PatternList::const_iterator ConstPatternIterator;
            /** \brief A mutable iterator over the registered patterns. */
            typedef PatternList::iterator       PatternIterator;

            /**
             * \brief Holds a single SMARTS query pattern, its atom-label value, its priority and match-handling flags.
             */
            class CDPL_CHEM_API Pattern
            {

                friend class PatternAtomTyper;

              public:
                /**
                 * \brief Constructs a pattern from the query molecular graph \a molgraph.
                 * \param molgraph The SMARTS query molecular graph.
                 * \param atom_label The atom label to assign to atoms matching this pattern.
                 * \param priority The priority of this pattern; higher-priority patterns are evaluated first.
                 * \param all_matches If \c true, every match of \a molgraph in the target is processed;
                 *                    if \c false, only the first match is processed.
                 * \param unique_matches If \c true, only one of multiple equivalent substructure mappings is reported per match.
                 */
                Pattern(const MolecularGraph::SharedPointer& molgraph, std::size_t atom_label = 0, std::size_t priority = 0,
                        bool all_matches = true, bool unique_matches = false);

                /**
                 * \brief Returns the SMARTS query molecular graph of this pattern.
                 * \return A \c const reference to the query smart pointer.
                 */
                const MolecularGraph::SharedPointer& getStructure() const;

                /**
                 * \brief Returns the pattern priority.
                 * \return The priority value.
                 */
                std::size_t getPriority() const;

                /**
                 * \brief Returns the atom label assigned by this pattern.
                 * \return The atom-label value.
                 */
                std::size_t getAtomLabel() const;

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
                typedef std::pair<const Atom*, std::size_t> AtomLabelPair;
                typedef std::vector<AtomLabelPair>          LabeledAtomList;

                const LabeledAtomList& getLabeledAtoms() const;

                MolecularGraph::SharedPointer molGraph;
                std::size_t                   priority;
                std::size_t                   atomLabel;
                bool                          allMatches;
                bool                          uniqueMatches;
                LabeledAtomList               labeledAtoms;
            };

            /**
             * \brief Constructs an empty \c %PatternAtomTyper instance.
             */
            PatternAtomTyper();

            /**
             * \brief Constructs a copy of the \c %PatternAtomTyper instance \a typer.
             * \param typer The \c %PatternAtomTyper to copy.
             */
            PatternAtomTyper(const PatternAtomTyper& typer);

            /**
             * \brief Registers a new pattern by its query molecular graph and per-pattern settings.
             * \param molgraph The SMARTS query molecular graph.
             * \param atom_label The atom label to assign to matched atoms.
             * \param priority The pattern's priority; higher-priority patterns are evaluated first.
             * \param all_matches If \c true, every match of the query is processed. Otherwise, only the first.
             * \param unique_matches If \c true, only one of multiple equivalent substructure mappings is processed per match.
             */
            void addPattern(const MolecularGraph::SharedPointer& molgraph, std::size_t atom_label = 0, std::size_t priority = 0,
                            bool all_matches = true, bool unique_matches = false);

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
             * \brief Tells whether the atom at index \a idx has received a label from any matching pattern.
             * \param idx The zero-based atom index in the molecular graph last processed by execute().
             * \return \c true if the atom carries a label, and \c false otherwise.
             * \throw Base::IndexError if \a idx is not in the range [0, N - 1], where N is the number of atoms of the molecular graph last processed by execute().
             */
            bool hasAtomLabel(std::size_t idx) const;

            /**
             * \brief Returns the atom label assigned to the atom at index \a idx during the last execute() call.
             * \param idx The zero-based atom index.
             * \return The atom label (zero if no pattern matched the atom).
             * \throw Base::IndexError if \a idx is not in the range [0, N - 1], where N is the number of atoms of the molecular graph last processed by execute().
             */
            std::size_t getAtomLabel(std::size_t idx) const;

            /**
             * \brief Returns the index of the pattern that produced the label of the atom at index \a idx.
             * \param idx The zero-based atom index.
             * \return The matching pattern index (returns an undefined value if hasAtomLabel(idx) is \c false).
             * \throw Base::IndexError if \a idx is not in the range [0, N - 1], where N is the number of atoms of the molecular graph last processed by execute().
             */
            std::size_t getPatternIndex(std::size_t idx) const;

            /**
             * \brief Runs the registered patterns against \a molgraph and assigns atom labels accordingly.
             * \param molgraph The molecular graph to be typed.
             */
            void execute(const MolecularGraph& molgraph);

            /**
             * \brief Replaces the state of this typer by a copy of the state of \a typer.
             * \param typer The source \c %PatternAtomTyper.
             * \return A reference to itself.
             */
            PatternAtomTyper& operator=(const PatternAtomTyper& typer);

          private:
            void init(const MolecularGraph& molgraph);

            void processPattern(const Pattern& ptn, std::size_t ptn_idx);
            bool processMatch(const AtomMapping& mapping, const Pattern& ptn, std::size_t ptn_idx);

            const MolecularGraph* molGraph;
            PatternList           patterns;
            SizeTypeArray         atomLabeling;
            SizeTypeArray         matchingPatternIndices;
            SubstructureSearch    subSearch;
            Util::BitSet          labeledAtomMask;
        };
    } // namespace Chem
} // namespace CDPL

#endif // CDPL_CHEM_PATTERNATOMTYPER_HPP
