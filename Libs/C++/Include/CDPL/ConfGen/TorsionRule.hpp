/* 
 * TorsionRule.hpp 
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
 * \brief Definition of the class CDPL::ConfGen::TorsionRule.
 */

#ifndef CDPL_CONFGEN_TORSIONRULE_HPP
#define CDPL_CONFGEN_TORSIONRULE_HPP

#include <vector>
#include <cstddef>
#include <string>

#include "CDPL/ConfGen/APIPrefix.hpp"
#include "CDPL/Chem/MolecularGraph.hpp"


namespace CDPL
{

    namespace ConfGen
    {

        class CDPL_CONFGEN_API TorsionRule
        {

          public:
            class AngleEntry;

          private:
            typedef std::vector<AngleEntry> AngleEntryList;

          public:
            class AngleEntry
            {

              public:
                AngleEntry(double ang, double tol1 = 0.0, double tol2 = 0.0, double score = 0.0):
                    angle(ang), tolerance1(tol1), tolerance2(tol2), score(score) {}

                double getAngle() const
                {
                    return angle;
                }

                double getTolerance1() const
                {
                    return tolerance1;
                }

                double getTolerance2() const
                {
                    return tolerance2;
                }

                double getScore() const
                {
                    return score;
                }

              private:
                double angle;
                double tolerance1;
                double tolerance2;
                double score;
            };

            typedef AngleEntryList::iterator       AngleEntryIterator;
            typedef AngleEntryList::const_iterator ConstAngleEntryIterator;

            const std::string& getMatchPatternString() const;

            void setMatchPatternString(const std::string& ptn_str);

            const Chem::MolecularGraph::SharedPointer& getMatchPattern() const;

            void setMatchPattern(const Chem::MolecularGraph::SharedPointer& ptn);

            void addAngle(const AngleEntry& ang_entry);

            void addAngle(double angle, double tol1 = 0.0, double tol2 = 0.0, double score = 0.0);

            std::size_t getNumAngles() const;

            const AngleEntry& getAngle(std::size_t idx) const;

            void removeAngle(std::size_t idx);

            void removeAngle(const AngleEntryIterator& it);

            AngleEntryIterator getAnglesBegin();

            AngleEntryIterator getAnglesEnd();

            ConstAngleEntryIterator getAnglesBegin() const;

            ConstAngleEntryIterator getAnglesEnd() const;

            AngleEntryIterator begin();

            AngleEntryIterator end();

            ConstAngleEntryIterator begin() const;

            ConstAngleEntryIterator end() const;

            void swap(TorsionRule& rule);

            void clear();

          private:
            void checkAngleIndex(std::size_t idx, bool it) const;

            std::string                         matchPatternStr;
            Chem::MolecularGraph::SharedPointer matchPattern;
            AngleEntryList                      angles;
        };
    } // namespace ConfGen
} // namespace CDPL

#endif // CDPL_CONFGEN_TORSIONRULE_HPP
