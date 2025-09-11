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
         * \brief BemisMurckoAnalyzer.
         * \see [\ref BEMU]
         * \since 1.1
         */
        class CDPL_CHEM_API BemisMurckoAnalyzer
        {

          public:
            typedef std::shared_ptr<BemisMurckoAnalyzer> SharedPointer;

            BemisMurckoAnalyzer();

            void stripHydrogens(bool strip);

            bool hydrogensStripped() const;
            
            void analyze(const MolecularGraph& molgraph);

            const FragmentList& getRingSystems() const;

            const FragmentList& getSideChains() const;

            const FragmentList& getLinkers() const;

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
