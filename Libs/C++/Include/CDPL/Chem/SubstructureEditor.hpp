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
#include <unordered_set>

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
        class StereoDescriptor;

        /**
         * \brief SubstructureEditor.
         * \since 1.3.0
         */
        class CDPL_CHEM_API SubstructureEditor
        {

            struct Pattern;

            typedef std::vector<Pattern> PatternList;
            typedef const MolecularGraph::SharedPointer& (*GetMolGraphFunc)(const Pattern&);

          public:
            typedef std::shared_ptr<SubstructureEditor> SharedPointer;

            typedef boost::transform_iterator<GetMolGraphFunc, PatternList::const_iterator> ConstPatternIterator;
            typedef boost::transform_iterator<GetMolGraphFunc, PatternList::iterator>       PatternIterator;

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
             * \param molgraph The molecular graph of the substructure search pattern to add.
             */
            void addSearchPattern(const MolecularGraph::SharedPointer& molgraph);

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
             * \param molgraph The molecular graph of the substructure exclude pattern to add.
             */
            void addExcludePattern(const MolecularGraph::SharedPointer& molgraph);

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

            /**
             * \brief Clears the current editing result pattern and the sets of substructure search and exclude patterns.
             */
            void clear();

            std::size_t edit(Molecule& mol);

            std::size_t edit(const MolecularGraph& molgraph, Molecule& res_mol);

            /**
             * \brief Copies the state of the \c %SubstructureEditor instance \a gen.
             * \param gen The \c %SubstructureEditor instance to copy.
             * \return A reference to itself.
             */
            SubstructureEditor& operator=(const SubstructureEditor& gen);

          private:
            struct Pattern
            {

                Pattern(const MolecularGraph::SharedPointer& molgraph):
                    molGraph(molgraph), subSearch(new Chem::SubstructureSearch(*molgraph))
                    {}

                MolecularGraph::SharedPointer     molGraph;
                SubstructureSearch::SharedPointer subSearch;
            };

            bool edit(Molecule& mol, const AtomMapping& mapping);

            bool editAtomStereoDescriptors(Molecule& mol) const;
            bool editBondStereoDescriptors(Molecule& mol) const;

            void getExcludeMatches(const MolecularGraph& molgraph);

            bool createMatchedAtomAndBondMask(const MolecularGraph& molgraph, const AtomBondMapping& mapping,
                                              Util::BitSet& mask, bool lbld_only, bool init) const;

            Chem::Atom* getMappedAtomForID(const AtomMapping& mapping, std::size_t id) const;
            const Chem::Atom* getNeighbor(const Atom* ctr_atom, const Atom* excl_nbr) const;

            template <typename T>
            void copyProperty(const T& src_cntnr, T& tgt_cntnr, const Base::LookupKey& key) const;

            template <typename VT, typename T>
            bool copyPropertyWithChangeCheck(const T& src_cntnr, T& tgt_cntnr, const Base::LookupKey& key) const;

            bool setStereoDescriptorWithChangeCheck(Atom& atom, const StereoDescriptor& descr) const;
            bool setStereoDescriptorWithChangeCheck(Bond& bond, const StereoDescriptor& descr) const;

            static const MolecularGraph::SharedPointer& getMolGraph(const Pattern& ptn);

            typedef Util::ObjectStack<Util::BitSet> BitSetCache;
            typedef std::vector<Util::BitSet*>      BitSetList;
            typedef std::vector<Atom*>              AtomArray;
            typedef std::unordered_set<Atom*>       AtomSet;
            typedef std::unordered_set<Bond*>       BondSet;

            const MolecularGraph*         molGraph;
            PatternList                   searchPatterns;
            PatternList                   excludePatterns;
            MolecularGraph::SharedPointer resultPattern;
            BitSetList                    excludeMatches;
            AtomArray                     resPtnAtomMapping;
            AtomSet                       hybStateUpdateAtoms;
            AtomSet                       configUpdateAtoms;
            BondSet                       configUpdateBonds;
            BitSetCache                   bitSetCache;
        };
    } // namespace Chem
} // namespace CDPL

#endif // CDPL_CHEM_SUBSTRUCTUREEDITOR_HPP
