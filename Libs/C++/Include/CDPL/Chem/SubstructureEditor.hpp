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
 * \brief Definition of class CDPL::Chem::SubstructureEditor.
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
         * \brief Pattern-driven editor that rewrites matched substructures of a Chem::Molecule using a
         *        result template, with optional exclude patterns guarding sites that must not be touched.
         *
         * Search patterns supply the substructures the editor will look for; the (single) result pattern
         * defines what each match is rewritten to; exclude patterns mark matches that must be skipped (a
         * search match is discarded when its atoms/bonds form a subset of any exclude match). The editor
         * iterates until no further matches can be transformed and returns the number of applied edits.
         *
         * \since 1.3.0
         */
        class CDPL_CHEM_API SubstructureEditor
        {

            struct Pattern;

            typedef std::vector<Pattern> PatternList;
            typedef const MolecularGraph::SharedPointer& (*GetMolGraphFunc)(const Pattern&);

          public:
            /**
             * \brief A reference-counted smart pointer [\ref SHPTR] for dynamically allocated \c %SubstructureEditor instances.
             */
            typedef std::shared_ptr<SubstructureEditor> SharedPointer;

            /**
             * \brief A constant iterator over the molecular graphs of the stored search/exclude patterns.
             */
            typedef boost::transform_iterator<GetMolGraphFunc, PatternList::const_iterator> ConstPatternIterator;

            /**
             * \brief A mutable iterator over the molecular graphs of the stored search/exclude patterns.
             */
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

            /**
             * \brief Returns the number of stored substructure-search patterns.
             * \return The number of stored search patterns.
             */
            std::size_t getNumSearchPatterns() const;

            /**
             * \brief Returns the molecular graph of the search pattern at index \a idx.
             * \param idx The zero-based search-pattern index.
             * \return The molecular graph of the search pattern at index \a idx.
             * \throw Base::IndexError if \a idx is not in the range [0, getNumSearchPatterns() - 1].
             */
            const MolecularGraph::SharedPointer& getSearchPattern(std::size_t idx) const;

            /**
             * \brief Removes the search pattern at index \a idx.
             * \param idx The zero-based search-pattern index to remove.
             * \throw Base::IndexError if \a idx is not in the range [0, getNumSearchPatterns() - 1].
             */
            void removeSearchPattern(std::size_t idx);

            /**
             * \brief Removes the search pattern pointed to by \a it.
             * \param it An iterator pointing to the search pattern to remove.
             * \throw Base::RangeError if \a it does not point into the current search-pattern range.
             */
            void removeSearchPattern(const PatternIterator& it);

            /**
             * \brief Clears the current set of substructuresearch patterns.
             */
            void clearSearchPatterns();

            /**
             * \brief Returns a mutable iterator pointing to the beginning of the stored search patterns.
             * \return A mutable iterator pointing to the beginning of the stored search patterns.
             */
            PatternIterator getSearchPatternsBegin();

            /**
             * \brief Returns a mutable iterator pointing to the end of the stored search patterns.
             * \return A mutable iterator pointing to the end of the stored search patterns.
             */
            PatternIterator getSearchPatternsEnd();

            /**
             * \brief Returns a constant iterator pointing to the beginning of the stored search patterns.
             * \return A constant iterator pointing to the beginning of the stored search patterns.
             */
            ConstPatternIterator getSearchPatternsBegin() const;

            /**
             * \brief Returns a constant iterator pointing to the end of the stored search patterns.
             * \return A constant iterator pointing to the end of the stored search patterns.
             */
            ConstPatternIterator getSearchPatternsEnd() const;

            /**
             * \brief Appends a new substructure exclude pattern to the current set of patterns.
             * \param molgraph The molecular graph of the substructure exclude pattern to add.
             */
            void addExcludePattern(const MolecularGraph::SharedPointer& molgraph);

            /**
             * \brief Returns the number of stored substructure-exclude patterns.
             * \return The number of stored exclude patterns.
             */
            std::size_t getNumExcludePatterns() const;

            /**
             * \brief Returns the molecular graph of the exclude pattern at index \a idx.
             * \param idx The zero-based exclude-pattern index.
             * \return The molecular graph of the exclude pattern at index \a idx.
             * \throw Base::IndexError if \a idx is not in the range [0, getNumExcludePatterns() - 1].
             */
            const MolecularGraph::SharedPointer& getExcludePattern(std::size_t idx) const;

            /**
             * \brief Removes the exclude pattern at index \a idx.
             * \param idx The zero-based exclude-pattern index to remove.
             * \throw Base::IndexError if \a idx is not in the range [0, getNumExcludePatterns() - 1].
             */
            void removeExcludePattern(std::size_t idx);

            /**
             * \brief Removes the exclude pattern pointed to by \a it.
             * \param it An iterator pointing to the exclude pattern to remove.
             * \throw Base::RangeError if \a it does not point into the current exclude-pattern range.
             */
            void removeExcludePattern(const PatternIterator& it);

            /**
             * \brief Clears the current set of substructure exclude patterns.
             */
            void clearExcludePatterns();

            /**
             * \brief Returns a mutable iterator pointing to the beginning of the stored exclude patterns.
             * \return A mutable iterator pointing to the beginning of the stored exclude patterns.
             */
            PatternIterator getExcludePatternsBegin();

            /**
             * \brief Returns a mutable iterator pointing to the end of the stored exclude patterns.
             * \return A mutable iterator pointing to the end of the stored exclude patterns.
             */
            PatternIterator getExcludePatternsEnd();

            /**
             * \brief Returns a constant iterator pointing to the beginning of the stored exclude patterns.
             * \return A constant iterator pointing to the beginning of the stored exclude patterns.
             */
            ConstPatternIterator getExcludePatternsBegin() const;

            /**
             * \brief Returns a constant iterator pointing to the end of the stored exclude patterns.
             * \return A constant iterator pointing to the end of the stored exclude patterns.
             */
            ConstPatternIterator getExcludePatternsEnd() const;

            /**
             * \brief Sets the result pattern that defines how each matched search-pattern instance will be rewritten.
             * \param pattern The molecular graph of the result pattern.
             */
            void setResultPattern(const MolecularGraph::SharedPointer& pattern);

            /**
             * \brief Returns the currently set result pattern.
             * \return The currently set result pattern, or a null pointer if none has been set.
             */
            const MolecularGraph::SharedPointer& getResultPattern() const;

            /**
             * \brief Clears the current editing result pattern and the sets of substructure search and exclude patterns.
             */
            void clear();

            /**
             * \brief Edits \a mol in place by applying the result pattern at every search-pattern match
             *        that is not covered by an exclude pattern; repeats until no further changes occur.
             * \param mol The molecule to edit.
             * \return The number of applied transformations.
             */
            std::size_t edit(Molecule& mol);

            /**
             * \brief Copies \a molgraph into \a res_mol and then edits \a res_mol via edit(Molecule&).
             * \param molgraph The source molecular graph.
             * \param res_mol The molecule receiving the edited result.
             * \return The number of applied transformations.
             */
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
