/* 
 * SubstructureEditor.hpp 
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
 * \brief Definition of the class CDPL::Chem::SubstructureEditor.
 */

#ifndef CDPL_CHEM_SUBSTRUCTUREEDITOR_HPP
#define CDPL_CHEM_SUBSTRUCTUREEDITOR_HPP

#include <cstddef>
#include <vector>
#include <memory>

#include <boost/iterator/transform_iterator.hpp>

#include "CDPL/Chem/APIPrefix.hpp"
#include "CDPL/Chem/MolecularGraph.hpp"
#include "CDPL/Chem/SubstructureSearch.hpp"
#include "CDPL/Util/BitSet.hpp"
#include "CDPL/Util/ObjectStack.hpp"


namespace CDPL
{

    namespace Chem
    {

        class Molecule;

        /**
         * \brief SubstructureEditor.
         * \since 1.3.0
         */
        class CDPL_CHEM_API SubstructureEditor
        {

            struct SubstructPattern
            {

                SubstructPattern(const MolecularGraph::SharedPointer& ptn, bool unique_mpgs):
                    pattern(ptn), subSearch(new Chem::SubstructureSearch(*ptn))
                {
                    subSearch->uniqueMappingsOnly(unique_mpgs);
                }

                MolecularGraph::SharedPointer     pattern;
                SubstructureSearch::SharedPointer subSearch;
            };

            typedef std::vector<SubstructPattern> SubstructPatternList;
            typedef const MolecularGraph::SharedPointer& (*GetPatternFunction)(const SubstructPattern&);

          public:
            typedef std::shared_ptr<SubstructureEditor> SharedPointer;

            typedef boost::transform_iterator<GetPatternFunction, SubstructPatternList::const_iterator> ConstPatternIterator;
            typedef boost::transform_iterator<GetPatternFunction, SubstructPatternList::iterator>       PatternIterator;

            /**
             * \brief Constructs the \c %SubstructureEditor instance.
             */
            SubstructureEditor();

            /**
             * \brief Constructs a copy of the \c %SubstructureEditor instance \a editor.
             * \param editor The \c %SubstructureEditor instance to copy.
             */
            SubstructureEditor(const SubstructureEditor& editor);

            /**
             * \brief Destructor.
             */
            ~SubstructureEditor();

            /**
             * \brief Appends a new substructure search pattern to the current set of patterns.
             * \param pattern The substructure search pattern to add.
             */
            void addSearchPattern(const MolecularGraph::SharedPointer& pattern);

            std::size_t getNumSearchPatterns() const;

            const MolecularGraph::SharedPointer& getSearchPattern(std::size_t idx) const;

            void removeSearchPattern(std::size_t idx);

            void removeSearchPattern(const PatternIterator& it);

            /**
             * \brief Clears the current set of substructuresearch patterns.
             */
            void clearSearchPatterns();

            PatternIterator getSearchPatternsBegin();

            PatternIterator getSearchPatternsEnd();

            ConstPatternIterator getSearchPatternsBegin() const;

            ConstPatternIterator getSearchPatternsEnd() const;

            /**
             * \brief Appends a new substructure exclude pattern to the current set of patterns.
             * \param pattern The substructure exclude pattern to add.
             */
            void addExcludePattern(const MolecularGraph::SharedPointer& pattern);

            std::size_t getNumExcludePatterns() const;

            const MolecularGraph::SharedPointer& getExcludePattern(std::size_t idx) const;

            void removeExcludePattern(std::size_t idx);

            void removeExcludePattern(const PatternIterator& it);

            /**
             * \brief Clears the current set of substructure exclude patterns.
             */
            void clearExcludePatterns();

            PatternIterator getExcludePatternsBegin();

            PatternIterator getExcludePatternsEnd();

            ConstPatternIterator getExcludePatternsBegin() const;

            ConstPatternIterator getExcludePatternsEnd() const;

            void setResultPattern(const MolecularGraph::SharedPointer& pattern);

            const MolecularGraph::SharedPointer& getResultPattern() const;

            std::size_t edit(Molecule& mol);

            std::size_t edit(const MolecularGraph& molgraph, Molecule& res_mol);

            /**
             * \brief Copies the state of the \c %SubstructureEditor instance \a gen.
             * \param gen The \c %SubstructureEditor instance to copy.
             * \return A reference to itself.
             */
            SubstructureEditor& operator=(const SubstructureEditor& gen);

          private:
            static const MolecularGraph::SharedPointer& getPattern(const SubstructPattern& ptn)
            {
                return ptn.pattern;
            }

            const MolecularGraph*         molGraph;
            SubstructPatternList          searchPatterns;
            SubstructPatternList          excludePatterns;
            MolecularGraph::SharedPointer resultPattern;
        };
    } // namespace Chem
} // namespace CDPL

#endif // CDPL_CHEM_SUBSTRUCTUREEDITOR_HPP
