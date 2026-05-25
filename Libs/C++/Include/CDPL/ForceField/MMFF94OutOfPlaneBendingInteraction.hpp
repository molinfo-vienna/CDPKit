/* 
 * MMFF94OutOfPlaneBendingInteraction.hpp 
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
 * \brief Definition of class CDPL::ForceField::MMFF94OutOfPlaneBendingInteraction.
 */

#ifndef CDPL_FORCEFIELD_MMFF94OUTOFPLANEBENDINGINTERACTION_HPP
#define CDPL_FORCEFIELD_MMFF94OUTOFPLANEBENDINGINTERACTION_HPP

#include <cstddef>


namespace CDPL
{

    namespace ForceField
    {

        /**
         * \brief A single MMFF94 out-of-plane bending interaction at a trigonal center.
         *
         * The interaction restrains the out-of-plane angle \f$ \chi \f$ that the bond from the central
         * atom \e j to the out-of-plane atom \e l makes with the plane defined by the central atom and
         * its two in-plane neighbors \e i and \e k. The associated energy term is
         * \f$ E_{oop} = \frac{1}{2} k_{oop} \chi^2 \f$.
         */
        class MMFF94OutOfPlaneBendingInteraction
        {

          public:
            /**
             * \brief Constructs the out-of-plane bending interaction record.
             * \param term_atom1_idx The zero-based index of the first in-plane terminal atom \e i.
             * \param ctr_atom_idx The zero-based index of the central trigonal atom \e j.
             * \param term_atom2_idx The zero-based index of the second in-plane terminal atom \e k.
             * \param oop_atom_idx The zero-based index of the out-of-plane atom \e l.
             * \param force_const The out-of-plane force constant \f$ k_{oop} \f$.
             */
            MMFF94OutOfPlaneBendingInteraction(std::size_t term_atom1_idx, std::size_t ctr_atom_idx, std::size_t term_atom2_idx,
                                               std::size_t oop_atom_idx, double force_const):
                termAtom1Idx(term_atom1_idx),
                ctrAtomIdx(ctr_atom_idx), termAtom2Idx(term_atom2_idx),
                oopAtomIdx(oop_atom_idx), forceConst(force_const) {}

            /**
             * \brief Returns the zero-based index of the first in-plane terminal atom \e i.
             * \return The first terminal-atom index.
             */
            std::size_t getTerminalAtom1Index() const
            {
                return termAtom1Idx;
            }

            /**
             * \brief Returns the zero-based index of the central trigonal atom \e j.
             * \return The center-atom index.
             */
            std::size_t getCenterAtomIndex() const
            {
                return ctrAtomIdx;
            }

            /**
             * \brief Returns the zero-based index of the second in-plane terminal atom \e k.
             * \return The second terminal-atom index.
             */
            std::size_t getTerminalAtom2Index() const
            {
                return termAtom2Idx;
            }

            /**
             * \brief Returns the zero-based index of the out-of-plane atom \e l.
             * \return The out-of-plane-atom index.
             */
            std::size_t getOutOfPlaneAtomIndex() const
            {
                return oopAtomIdx;
            }

            /**
             * \brief Returns the zero-based index of the first in-plane terminal atom (alias for getTerminalAtom1Index()).
             * \return The first terminal-atom index.
             */
            std::size_t getAtom1Index() const
            {
                return termAtom1Idx;
            }

            /**
             * \brief Returns the zero-based index of the central atom (alias for getCenterAtomIndex()).
             * \return The center-atom index.
             */
            std::size_t getAtom2Index() const
            {
                return ctrAtomIdx;
            }

            /**
             * \brief Returns the zero-based index of the second in-plane terminal atom (alias for getTerminalAtom2Index()).
             * \return The second terminal-atom index.
             */
            std::size_t getAtom3Index() const
            {
                return termAtom2Idx;
            }

            /**
             * \brief Returns the zero-based index of the out-of-plane atom (alias for getOutOfPlaneAtomIndex()).
             * \return The out-of-plane-atom index.
             */
            std::size_t getAtom4Index() const
            {
                return oopAtomIdx;
            }

            /**
             * \brief Returns the out-of-plane force constant.
             * \return The force constant \f$ k_{oop} \f$.
             */
            double getForceConstant() const
            {
                return forceConst;
            }

          private:
            std::size_t termAtom1Idx;
            std::size_t ctrAtomIdx;
            std::size_t termAtom2Idx;
            std::size_t oopAtomIdx;
            double      forceConst;
        };
    } // namespace ForceField
} // namespace CDPL

#endif // CDPL_FORCEFIELD_MMFF94OUTOFPLANEBENDINGINTERACTION_HPP
