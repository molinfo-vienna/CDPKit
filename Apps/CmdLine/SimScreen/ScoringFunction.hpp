/* 
 * ScoringFunction.hpp
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


#ifndef SIMSCREEN_SCORINGFUNCTION_HPP
#define SIMSCREEN_SCORINGFUNCTION_HPP

#include <string>

#include "CDPL/Util/BitSet.hpp"
#include "CDPL/Math/Vector.hpp"


namespace CmdLineLib
{

    class CmdLineBase;
}


namespace SimScreen
{

    class ScoringFunction
    {

      public:
        enum DescriptorType
        {

            BITSET,
            VECTOR,
            ANY
        };

        ScoringFunction(const std::string& id, const std::string& disp_name, bool dist_score, DescriptorType descr_type):
            id(id), displayName(disp_name), isDistScore(dist_score), descrType(descr_type) {}

        virtual ~ScoringFunction() {}

        virtual void addOptions(CmdLineLib::CmdLineBase& cl_base) {}

        virtual void processOptions(CmdLineLib::CmdLineBase& cl_base) {}

        virtual void getOptionSummary(std::string& summary) {}

        virtual double calculate(const CDPL::Util::BitSet& query_fp, const CDPL::Util::BitSet& db_mol_fp) const = 0;

        virtual double calculate(const CDPL::Math::DVector& query_descr, const CDPL::Math::DVector& db_mol_descr) const = 0;
 
        bool compare(double score1, double score2) const
        {
            if (isDistScore)
                return (score1 > score2);

            return (score1 < score2);
        }

        const std::string& getID() const
        {
            return id;
        }

        const std::string& getDisplayName() const
        {
            return displayName;
        }

        DescriptorType getDescriptorType() const
        {
            return descrType;
        }

        bool isDistanceScore() const
        {
            return isDistScore;
        }

      private:
        std::string    id;
        std::string    displayName;
        bool           isDistScore;
        DescriptorType descrType;
    };
} // namespace SimScreen

#endif // SIMSCREEN_SCORINGFUNCTION_HPP
