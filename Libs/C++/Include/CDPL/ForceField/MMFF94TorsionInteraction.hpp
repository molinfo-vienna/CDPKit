/* 
 * MMFF94TorsionInteraction.hpp 
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
 * \brief Definition of class CDPL::ForceField::MMFF94TorsionInteraction.
 */

#ifndef CDPL_FORCEFIELD_MMFF94TORSIONINTERACTION_HPP
#define CDPL_FORCEFIELD_MMFF94TORSIONINTERACTION_HPP

#include <cstddef>


namespace CDPL
{

    namespace ForceField
    {

        /**
         * \brief Stores parameters for a single MMFF94 torsion interaction over an atom quadruplet \e i-\e j-\e k-\e l.
         */
        class MMFF94TorsionInteraction
        {

          public:
            /**
             * \brief Constructs the torsion interaction parameter set.
             * \param term_atom1_idx The zero-based index of the first terminal atom \e i.
             * \param ctr_atom1_idx The zero-based index of the first central atom \e j (bonded to \e i and \e k).
             * \param ctr_atom2_idx The zero-based index of the second central atom \e k (bonded to \e j and \e l).
             * \param term_atom2_idx The zero-based index of the second terminal atom \e l.
             * \param tor_type_idx The MMFF94 torsion type index (0-5).
             * \param tor_param1 The torsion parameter \f$ V_1 \f$.
             * \param tor_param2 The torsion parameter \f$ V_2 \f$.
             * \param tor_param3 The torsion parameter \f$ V_3 \f$.
             */
            MMFF94TorsionInteraction(std::size_t term_atom1_idx, std::size_t ctr_atom1_idx, std::size_t ctr_atom2_idx,
                                     std::size_t term_atom2_idx, unsigned int tor_type_idx, double tor_param1,
                                     double tor_param2, double tor_param3):
                termAtom1Idx(term_atom1_idx),
                ctrAtom1Idx(ctr_atom1_idx), ctrAtom2Idx(ctr_atom2_idx),
                termAtom2Idx(term_atom2_idx), torTypeIdx(tor_type_idx), torParam1(tor_param1), torParam2(tor_param2),
                torParam3(tor_param3) {}

            /**
             * \brief Returns the zero-based index of the first terminal atom \e i.
             * \return The first terminal-atom index.
             */
            std::size_t getTerminalAtom1Index() const
            {
                return termAtom1Idx;
            }

            /**
             * \brief Returns the zero-based index of the first central atom \e j.
             * \return The first center-atom index.
             */
            std::size_t getCenterAtom1Index() const
            {
                return ctrAtom1Idx;
            }

            /**
             * \brief Returns the zero-based index of the second central atom \e k.
             * \return The second center-atom index.
             */
            std::size_t getCenterAtom2Index() const
            {
                return ctrAtom2Idx;
            }

            /**
             * \brief Returns the zero-based index of the second terminal atom \e l.
             * \return The second terminal-atom index.
             */
            std::size_t getTerminalAtom2Index() const
            {
                return termAtom2Idx;
            }

            /**
             * \brief Returns the zero-based index of the first terminal atom (alias for getTerminalAtom1Index()).
             * \return The first terminal-atom index.
             */
            std::size_t getAtom1Index() const
            {
                return termAtom1Idx;
            }

            /**
             * \brief Returns the zero-based index of the first central atom (alias for getCenterAtom1Index()).
             * \return The first center-atom index.
             */
            std::size_t getAtom2Index() const
            {
                return ctrAtom1Idx;
            }

            /**
             * \brief Returns the zero-based index of the second central atom (alias for getCenterAtom2Index()).
             * \return The second center-atom index.
             */
            std::size_t getAtom3Index() const
            {
                return ctrAtom2Idx;
            }

            /**
             * \brief Returns the zero-based index of the second terminal atom (alias for getTerminalAtom2Index()).
             * \return The second terminal-atom index.
             */
            std::size_t getAtom4Index() const
            {
                return termAtom2Idx;
            }

            /**
             * \brief Returns the MMFF94 torsion type index.
             * \return The torsion type index (0-5).
             */
            unsigned int getTorsionTypeIndex() const
            {
                return torTypeIdx;
            }

            /**
             * \brief Returns the first torsion parameter.
             * \return The torsion parameter \f$ V_1 \f$.
             */
            double getTorsionParameter1() const
            {
                return torParam1;
            }

            /**
             * \brief Returns the second torsion parameter.
             * \return The torsion parameter \f$ V_2 \f$.
             */
            double getTorsionParameter2() const
            {
                return torParam2;
            }

            /**
             * \brief Returns the third torsion parameter.
             * \return The torsion parameter \f$ V_3 \f$.
             */
            double getTorsionParameter3() const
            {
                return torParam3;
            }

          private:
            std::size_t  termAtom1Idx;
            std::size_t  ctrAtom1Idx;
            std::size_t  ctrAtom2Idx;
            std::size_t  termAtom2Idx;
            unsigned int torTypeIdx;
            double       torParam1;
            double       torParam2;
            double       torParam3;
        };
    } // namespace ForceField
} // namespace CDPL

#endif // CDPL_FORCEFIELD_MMFF94TORSIONINTERACTION_HPP
