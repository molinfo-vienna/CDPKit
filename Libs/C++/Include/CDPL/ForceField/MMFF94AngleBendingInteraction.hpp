/* 
 * MMFF94AngleBendingInteraction.hpp 
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
 * \brief Definition of class CDPL::ForceField::MMFF94AngleBendingInteraction.
 */

#ifndef CDPL_FORCEFIELD_MMFF94ANGLEBENDINGINTERACTION_HPP
#define CDPL_FORCEFIELD_MMFF94ANGLEBENDINGINTERACTION_HPP

#include <cstddef>


namespace CDPL
{

    namespace ForceField
    {

        class MMFF94AngleBendingInteraction
        {

          public:
            MMFF94AngleBendingInteraction(std::size_t term_atom1_idx, std::size_t ctr_atom_idx, std::size_t term_atom2_idx,
                                          unsigned int angle_type_idx, bool linear, double force_const, double ref_angle):
                termAtom1Idx(term_atom1_idx),
                ctrAtomIdx(ctr_atom_idx), termAtom2Idx(term_atom2_idx),
                angleTypeIdx(angle_type_idx), linear(linear), forceConst(force_const), refAngle(ref_angle) {}

            std::size_t getTerminalAtom1Index() const
            {
                return termAtom1Idx;
            }

            std::size_t getCenterAtomIndex() const
            {
                return ctrAtomIdx;
            }

            std::size_t getTerminalAtom2Index() const
            {
                return termAtom2Idx;
            }

            std::size_t getAtom1Index() const
            {
                return termAtom1Idx;
            }

            std::size_t getAtom2Index() const
            {
                return ctrAtomIdx;
            }

            std::size_t getAtom3Index() const
            {
                return termAtom2Idx;
            }

            unsigned int getAngleTypeIndex() const
            {
                return angleTypeIdx;
            }

            bool isLinearAngle() const
            {
                return linear;
            }

            double getForceConstant() const
            {
                return forceConst;
            }

            double getReferenceAngle() const
            {
                return refAngle;
            }

            void setReferenceAngle(double angle)
            {
                refAngle = angle;
            }

          private:
            std::size_t  termAtom1Idx;
            std::size_t  ctrAtomIdx;
            std::size_t  termAtom2Idx;
            unsigned int angleTypeIdx;
            bool         linear;
            double       forceConst;
            double       refAngle;
        };
    } // namespace ForceField
} // namespace CDPL

#endif // CDPL_FORCEFIELD_MMFF94ANGLEBENDINGINTERACTION_HPP
