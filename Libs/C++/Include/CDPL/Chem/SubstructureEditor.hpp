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

#include <vector>
#include <memory>

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
         */
        class CDPL_CHEM_API SubstructureEditor
        {

          public:
            typedef std::shared_ptr<SubstructureEditor> SharedPointer;

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
            void addSearchPattern(const Chem::MolecularGraph::SharedPointer& pattern);

            /**
             * \brief Appends a new substructure exclude pattern to the current set of patterns.
             * \param pattern The substructure exclude pattern to add.
             */
            void addExcludePattern(const Chem::MolecularGraph::SharedPointer& pattern);

            /**
             * \brief Clears the current set of substructuresearch patterns.
             */
            void clearSearchPatterns();

            /**
             * \brief Clears the current set of substructure exclude patterns.
             */
            void clearExcludePatterns();

            /**
             * \brief Copies the state of the \c %SubstructureEditor instance \a gen.
             * \param gen The \c %SubstructureEditor instance to copy.
             * \return A reference to itself.
             */
            SubstructureEditor& operator=(const SubstructureEditor& gen);

          private:
            struct SubstructPattern
            {

                SubstructPattern(const Chem::MolecularGraph::SharedPointer& ptn):
                    pattern(ptn), subSearch(new Chem::SubstructureSearch(*ptn))
                {
                    subSearch->uniqueMappingsOnly(false);
                }

                MolecularGraph::SharedPointer     pattern;
                SubstructureSearch::SharedPointer subSearch;
            };

            typedef std::vector<SubstructPattern>     SubstructPatternList;

            const Chem::MolecularGraph* molGraph;
            SubstructPatternList        searchPatterns;
            SubstructPatternList        excludePatterns;
        };
    } // namespace Chem
} // namespace CDPL

#endif // CDPL_CHEM_SUBSTRUCTUREEDITOR_HPP
