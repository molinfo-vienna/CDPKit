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
 * \brief Definition of class CDPL::ConfGen::TorsionRule.
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

        /**
         * \brief Data structure for the representation of single torsion library rules.
         *
         * Eeach rule consists of a \e SMARTS match pattern and a list of
         * preferred torsion angles (each with tolerances and a score).
         */
        class CDPL_CONFGEN_API TorsionRule
        {

          public:
            class AngleEntry;

          private:
            typedef std::vector<AngleEntry> AngleEntryList;

          public:
            /**
             * \brief One preferred torsion angle for a rule, characterized by its value, the two tolerance bands and a score.
             */
            class AngleEntry
            {

              public:
                /**
                 * \brief Constructs the \c %AngleEntry with the given angle value, tolerances and score.
                 * \param ang The angle value in degrees.
                 * \param tol1 The first (preferred) tolerance band.
                 * \param tol2 The second (relaxed) tolerance band.
                 * \param score The score (higher = more preferred).
                 */
                AngleEntry(double ang, double tol1 = 0.0, double tol2 = 0.0, double score = 0.0):
                    angle(ang), tolerance1(tol1), tolerance2(tol2), score(score) {}

                /**
                 * \brief Returns the angle value.
                 * \return The angle value in degrees.
                 */
                double getAngle() const
                {
                    return angle;
                }

                /**
                 * \brief Returns the first (preferred) tolerance band.
                 * \return The first tolerance band in degrees.
                 */
                double getTolerance1() const
                {
                    return tolerance1;
                }

                /**
                 * \brief Returns the second (relaxed) tolerance band.
                 * \return The second tolerance band in degrees.
                 */
                double getTolerance2() const
                {
                    return tolerance2;
                }

                /**
                 * \brief Returns the score (higher values mark more strongly preferred angles).
                 * \return The score.
                 */
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


            /**
             * \brief A mutable iterator over the angle entries.
             */
            typedef AngleEntryList::iterator       AngleEntryIterator;

            /**
             * \brief A constant iterator over the angle entries.
             */
            typedef AngleEntryList::const_iterator ConstAngleEntryIterator;

            /**
             * \brief Returns the \e SMARTS match pattern.
             * \return A \c const reference to the \e SMARTS match pattern.
             */
            const std::string& getMatchPatternString() const;

            /**
             * \brief Sets the \e SMARTS match pattern.
             * \param ptn_str The new \e SMARTS match pattern.
             */
            void setMatchPatternString(const std::string& ptn_str);

            /**
             * \brief Returns the match pattern molecular graph.
             * \return A \c const shared pointer to the match pattern molecular graph.
             */
            const Chem::MolecularGraph::SharedPointer& getMatchPattern() const;

            /**
             * \brief Sets the match pattern molecular graph.
             * \param ptn The new match pattern molecular graph.
             */
            void setMatchPattern(const Chem::MolecularGraph::SharedPointer& ptn);

            /**
             * \brief Appends the angle entry \a ang_entry to the rule.
             * \param ang_entry The angle entry to append.
             */
            void addAngle(const AngleEntry& ang_entry);

            /**
             * \brief Constructs and appends a new angle entry.
             * \param angle The angle value in degrees.
             * \param tol1 The first (preferred) tolerance band.
             * \param tol2 The second (relaxed) tolerance band.
             * \param score The score.
             */
            void addAngle(double angle, double tol1 = 0.0, double tol2 = 0.0, double score = 0.0);

            /**
             * \brief Returns the number of stored angle entries.
             * \return The angle entry count.
             */
            std::size_t getNumAngles() const;

            /**
             * \brief Returns the angle entry at index \a idx.
             * \param idx The zero-based angle entry index.
             * \return A \c const reference to the angle entry.
             * \throw Base::IndexError if the number of angle entries is zero or \a idx is not in the range [0, getNumAngles() - 1].
             */
            const AngleEntry& getAngle(std::size_t idx) const;

            /**
             * \brief Removes the angle entry at index \a idx.
             * \param idx The zero-based angle entry index.
             * \throw Base::IndexError if the number of angle entries is zero or \a idx is not in the range [0, getNumAngles() - 1].
             */
            void removeAngle(std::size_t idx);

            /**
             * \brief Removes the angle entry referenced by iterator \a it.
             * \param it The iterator pointing to the angle entry.
             * \throw Base::RangeError if the number of angle entries is zero or \a it is not in the range [getAnglesBegin(), getAnglesEnd() - 1].
             */
            void removeAngle(const AngleEntryIterator& it);

            /**
             * \brief Returns a mutable iterator pointing to the first angle entry.
             * \return A mutable iterator pointing to the first angle entry.
             */
            AngleEntryIterator getAnglesBegin();

            /**
             * \brief Returns a mutable iterator pointing one past the last angle entry.
             * \return A mutable iterator pointing one past the last angle entry.
             */
            AngleEntryIterator getAnglesEnd();

            /**
             * \brief Returns a constant iterator pointing to the first angle entry.
             * \return A constant iterator pointing to the first angle entry.
             */
            ConstAngleEntryIterator getAnglesBegin() const;

            /**
             * \brief Returns a constant iterator pointing one past the last angle entry.
             * \return A constant iterator pointing one past the last angle entry.
             */
            ConstAngleEntryIterator getAnglesEnd() const;

            /**
             * \brief Returns a mutable iterator pointing to the first angle entry (range-based for support).
             * \return A mutable iterator pointing to the first angle entry.
             */
            AngleEntryIterator begin();

            /**
             * \brief Returns a mutable iterator pointing one past the last angle entry (range-based for support).
             * \return A mutable iterator pointing one past the last angle entry.
             */
            AngleEntryIterator end();

            /**
             * \brief Returns a constant iterator pointing to the first angle entry (range-based for support).
             * \return A constant iterator pointing to the first angle entry.
             */
            ConstAngleEntryIterator begin() const;

            /**
             * \brief Returns a constant iterator pointing one past the last angle entry (range-based for support).
             * \return A constant iterator pointing one past the last angle entry.
             */
            ConstAngleEntryIterator end() const;

            /**
             * \brief Swaps the contents of this rule with \a rule.
             * \param rule The other torsion rule.
             */
            void swap(TorsionRule& rule);

            /**
             * \brief Clears the match pattern and removes all angle entries.
             */
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
