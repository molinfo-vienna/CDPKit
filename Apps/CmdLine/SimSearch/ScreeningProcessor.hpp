/* 
 * ScreeningProcessor.hpp
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


#ifndef SIMSEARCH_SCREENINGPROCESSOR_HPP
#define SIMSEARCH_SCREENINGPROCESSOR_HPP

#include <cstddef>


namespace CDPL
{

    namespace Chem
    {

        class MolecularGraph;
        class Molecule;
    }
} // namespace CDPL


namespace SimSearch
{

    class ScreeningProcessor
    {

      public:
        struct Result
        {

            double      score;
            std::size_t queryMolIdx;
            std::size_t queryMolConfIdx;
            std::size_t dbMolConfIdx;
        };

        enum ScreeningMode
        {

            BEST_OVERALL_MATCH,
            BEST_MATCH_PER_QUERY,
            BEST_MATCH_PER_QUERY_CONF
        };

        void addQuery(const CDPL::Chem::MolecularGraph& query_mol)
        {
            // TODO
        }

        bool process(const CDPL::Chem::Molecule& db_mol, Result& res)
        {
            return false; // TODO
        }

      private:

    };
} // namespace SimSearch

#endif // SIMSEARCH_SCREENINGPROCESSOR_HPP
