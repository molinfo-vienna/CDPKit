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


#ifndef SIMSCREEN_SCREENINGPROCESSOR_HPP
#define SIMSCREEN_SCREENINGPROCESSOR_HPP

#include <cstddef>
#include <functional>
#include <memory>


namespace CDPL
{

    namespace Chem
    {

        class Molecule;
    }
}


namespace SimScreen
{

    class ScoringFunction;
    class DescriptorCalculator;
    
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

        typedef std::function<void(const Result& res)> ResultCallbackFunc;

        ScreeningProcessor(const ScoringFunction& scr_func, const DescriptorCalculator& calc, const ResultCallbackFunc& cb_func);

        ~ScreeningProcessor();
        
        void addQuery(CDPL::Chem::Molecule& query_mol);

        bool process(CDPL::Chem::Molecule& db_mol);

      private:
        typedef std::unique_ptr<DescriptorCalculator> DescriptorCalculatorPtr;

        const ScoringFunction&  scoringFunc;
        DescriptorCalculatorPtr descrCalculator;
        ResultCallbackFunc      callbackFunc;
    };
} // namespace SimScreen

#endif // SIMSCREEN_SCREENINGPROCESSOR_HPP
