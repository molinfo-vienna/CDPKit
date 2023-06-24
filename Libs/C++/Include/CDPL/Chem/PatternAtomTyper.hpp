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
 * \brief Definition of the class CDPL::Chem::PatternAtomTyper.
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
         * \brief PatternAtomTyper.
         */
        class CDPL_CHEM_API PatternAtomTyper
        {

          public:
            class Pattern;

          private:
            typedef std::vector<Pattern>     PatternList;
            typedef std::vector<std::size_t> SizeTypeArray;

          public:
            typedef std::shared_ptr<PatternAtomTyper> SharedPointer;

            typedef PatternList::const_iterator ConstPatternIterator;
            typedef PatternList::iterator       PatternIterator;

            class CDPL_CHEM_API Pattern
            {

                friend class PatternAtomTyper;

              public:
                Pattern(const MolecularGraph::SharedPointer& structure, std::size_t atom_label = 0, std::size_t priority = 0,
                        bool all_matches = true, bool unique_matches = false);

                const MolecularGraph::SharedPointer& getStructure() const;

                std::size_t getPriority() const;

                std::size_t getAtomLabel() const;

                bool processAllMatches() const;

                bool processUniqueMatchesOnly() const;

              private:
                typedef std::pair<const Atom*, std::size_t> AtomLabelPair;
                typedef std::vector<AtomLabelPair>          LabeledAtomList;

                const LabeledAtomList& getLabeledAtoms() const;

                MolecularGraph::SharedPointer structure;
                std::size_t                   priority;
                std::size_t                   atomLabel;
                bool                          allMatches;
                bool                          uniqueMatches;
                LabeledAtomList               labeledAtoms;
            };

            PatternAtomTyper();

            PatternAtomTyper(const PatternAtomTyper& typer);

            void addPattern(const MolecularGraph::SharedPointer& structure, std::size_t atom_label = 0, std::size_t priority = 0,
                            bool all_matches = true, bool unique_matches = false);

            void addPattern(const Pattern& ptn);

            const Pattern& getPattern(std::size_t idx) const;

            void removePattern(std::size_t idx);

            void removePattern(const PatternIterator& ptn_it);

            void clear();

            std::size_t getNumPatterns() const;

            ConstPatternIterator getPatternsBegin() const;
            ConstPatternIterator getPatternsEnd() const;

            PatternIterator getPatternsBegin();
            PatternIterator getPatternsEnd();

            ConstPatternIterator begin() const;
            ConstPatternIterator end() const;

            PatternIterator begin();
            PatternIterator end();

            bool hasAtomLabel(std::size_t idx) const;

            std::size_t getAtomLabel(std::size_t idx) const;

            std::size_t getPatternIndex(std::size_t idx) const;

            void execute(const MolecularGraph& molgraph);

            PatternAtomTyper& operator=(const PatternAtomTyper& typer);

          private:
            void init(const MolecularGraph& molgraph);

            void processPattern(const Pattern& ptn, std::size_t ptn_idx);
            bool processMatch(const AtomMapping& mapping, const Pattern& ptn, std::size_t ptn_idx);

            const MolecularGraph* molGraph;
            PatternList           patterns;
            SizeTypeArray         atomLabeling;
            SizeTypeArray         matchingPatternIndices;
            SubstructureSearch    substructSearch;
            Util::BitSet          labeledAtomMask;
        };
    } // namespace Chem
} // namespace CDPL

#endif // CDPL_CHEM_PATTERNATOMTYPER_HPP
