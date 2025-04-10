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
 * \brief Definition of the class CDPL::Chem::SubstructureHistogramCalculator.
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
         * \brief SubstructureHistogramCalculator.
         */
        class CDPL_CHEM_API SubstructureHistogramCalculator
        {

          public:
            class Pattern;

          private:
            typedef std::vector<Pattern> PatternList;

          public:
            typedef std::shared_ptr<SubstructureHistogramCalculator> SharedPointer;

            typedef PatternList::const_iterator ConstPatternIterator;
            typedef PatternList::iterator       PatternIterator;

            class CDPL_CHEM_API Pattern
            {

              public:
                Pattern(const MolecularGraph::SharedPointer& molgraph, std::size_t id, std::size_t priority = 0,
                        bool all_matches = true, bool unique_matches = true);

                const MolecularGraph::SharedPointer& getStructure() const;

                std::size_t getID() const;

                std::size_t getPriority() const;

                bool processAllMatches() const;

                bool processUniqueMatchesOnly() const;

              private:
                MolecularGraph::SharedPointer molGraph;
                std::size_t                   id;
                std::size_t                   priority;
                bool                          allMatches;
                bool                          uniqueMatches;
            };

            SubstructureHistogramCalculator();

            SubstructureHistogramCalculator(const SubstructureHistogramCalculator& gen);

            void addPattern(const MolecularGraph::SharedPointer& molgraph, std::size_t id, std::size_t priority = 0,
                            bool all_matches = true, bool unique_matches = true);

            void addPattern(const Pattern& pattern);

            const Pattern& getPattern(std::size_t idx) const;

            void removePattern(std::size_t idx);

            void removePattern(const PatternIterator& it);

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

            template <typename T>
            void calculate(const MolecularGraph& molgraph, T& histo);

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
