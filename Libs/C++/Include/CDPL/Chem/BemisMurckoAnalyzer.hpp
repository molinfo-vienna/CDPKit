/* 
 * BemisMurckoAnalyzer.hpp 
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
 * \brief Definition of class CDPL::Chem::BemisMurckoAnalyzer.
 */

#ifndef CDPL_CHEM_BEMISMURCKOANALYZER_HPP
#define CDPL_CHEM_BEMISMURCKOANALYZER_HPP

#include <memory>
#include <vector>

#include "CDPL/Chem/APIPrefix.hpp"
#include "CDPL/Chem/ComponentSet.hpp"


namespace CDPL
{

    namespace Chem
    {
        
        /**
         * \brief Decomposes a molecular graph into its Bemis-Murcko framework, ring systems, linkers and side chains.
         *
         * After calling analyze() the four constituent fragment sets can be queried separately via
         * getRingSystems(), getLinkers(), getFrameworks() and getSideChains(). The framework of a molecule is
         * the union of all ring systems together with the linker chains that connect them; side chains are
         * the remaining acyclic substituents. Hydrogen atoms can optionally be stripped from the input.
         *
         * \see [\ref BEMU]
         * \since 1.1
         */
        class CDPL_CHEM_API BemisMurckoAnalyzer
        {

          public:
            /** \brief A reference-counted smart pointer [\ref SHPTR] for dynamically allocated \c %BemisMurckoAnalyzer instances. */
            typedef std::shared_ptr<BemisMurckoAnalyzer> SharedPointer;

            /**
             * \brief Constructs the \c %BemisMurckoAnalyzer instance.
             */
            BemisMurckoAnalyzer();

            /**
             * \brief Specifies whether hydrogen atoms shall be stripped from the input before the decomposition.
             * \param strip If \c true, hydrogens are removed prior to analysis.
             */
            void stripHydrogens(bool strip);

            /**
             * \brief Tells whether hydrogen atoms are stripped from the input before the decomposition.
             * \return \c true if hydrogens are stripped, and \c false otherwise.
             */
            bool hydrogensStripped() const;

            /**
             * \brief Performs the Bemis-Murcko decomposition of the molecular graph \a molgraph.
             *
             * After this call the four fragment sets produced by the decomposition are available via
             * getRingSystems(), getLinkers(), getFrameworks() and getSideChains().
             *
             * \param molgraph The molecular graph to decompose.
             */
            void analyze(const MolecularGraph& molgraph);

            /**
             * \brief Returns the perceived ring systems of the input molecular graph.
             * \return A \c const reference to the list of ring-system fragments.
             */
            const FragmentList& getRingSystems() const;

            /**
             * \brief Returns the side chains (acyclic substituents) of the input molecular graph.
             * \return A \c const reference to the list of side-chain fragments.
             */
            const FragmentList& getSideChains() const;

            /**
             * \brief Returns the linker fragments connecting different ring systems of the input molecular graph.
             * \return A \c const reference to the list of linker fragments.
             */
            const FragmentList& getLinkers() const;

            /**
             * \brief Returns the Bemis-Murcko frameworks of the input molecular graph (union of ring systems and linkers).
             * \return A \c const reference to the list of framework fragments.
             */
            const FragmentList& getFrameworks() const;
            
          private:
            void extractSideChains(const MolecularGraph& molgraph);
            void extractFrameworks(const MolecularGraph& molgraph);
            void splitFrameworks();
            
            typedef std::vector<std::size_t> BondCountArray;

            bool           hDeplete;
            BondCountArray bondCounts;
            Fragment       workingFrag;
            FragmentList   ringSystems;
            FragmentList   sideChains;
            FragmentList   linkers;
            FragmentList   frameworks;
            ComponentSet   compSet;
        };
    } // namespace Chem
} // namespace CDPL

#endif // CDPL_CHEM_BEMISMURCKOANALYZER_HPP
