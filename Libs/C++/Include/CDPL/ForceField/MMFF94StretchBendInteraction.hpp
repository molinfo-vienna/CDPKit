/* 
 * MMFF94StretchBendInteraction.hpp 
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
 * \brief Definition of class CDPL::ForceField::MMFF94StretchBendInteraction.
 */

#ifndef CDPL_FORCEFIELD_MMFF94STRETCHBENDINTERACTION_HPP
#define CDPL_FORCEFIELD_MMFF94STRETCHBENDINTERACTION_HPP

#include <cstddef>


namespace CDPL
{

    namespace ForceField
    {

        class MMFF94StretchBendInteraction
        {

          public:
            MMFF94StretchBendInteraction(std::size_t term_atom1_idx, std::size_t ctr_atom_idx, std::size_t term_atom2_idx,
                                         unsigned int sb_type_idx, double ref_angle, double ref_length1, double ref_length2,
                                         double ijk_force_const, double kji_force_const):
                termAtom1Idx(term_atom1_idx),
                ctrAtomIdx(ctr_atom_idx), termAtom2Idx(term_atom2_idx),
                sbTypeIdx(sb_type_idx), refAngle(ref_angle), refLength1(ref_length1), refLength2(ref_length2),
                ijkForceConst(ijk_force_const), kjiForceConst(kji_force_const) {}

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

            unsigned int getStretchBendTypeIndex() const
            {
                return sbTypeIdx;
            }

            double getIJKForceConstant() const
            {
                return ijkForceConst;
            }

            double getKJIForceConstant() const
            {
                return kjiForceConst;
            }

            double getReferenceAngle() const
            {
                return refAngle;
            }

            void setReferenceAngle(double angle)
            {
                refAngle = angle;
            }

            double getReferenceLength1() const
            {
                return refLength1;
            }

            void setReferenceLength1(double length)
            {
                refLength1 = length;
            }

            double getReferenceLength2() const
            {
                return refLength2;
            }

            void setReferenceLength2(double length)
            {
                refLength2 = length;
            }

          private:
            std::size_t  termAtom1Idx;
            std::size_t  ctrAtomIdx;
            std::size_t  termAtom2Idx;
            unsigned int sbTypeIdx;
            double       refAngle;
            double       refLength1;
            double       refLength2;
            double       ijkForceConst;
            double       kjiForceConst;
        };
    } // namespace ForceField
} // namespace CDPL

#endif // CDPL_FORCEFIELD_MMFF94STRETCHBENDINTERACTION_HPP
