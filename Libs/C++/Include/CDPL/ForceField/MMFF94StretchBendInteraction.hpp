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

        /**
         * \brief A single MMFF94 stretch-bend coupling interaction.
         *
         * The stretch-bend term couples the angle defined by an atom triplet (\e i-\e j-\e k) with the two
         * bond lengths \e i-\e j and \e j-\e k. The associated energy contribution is
         * \f$ E_{sb} = (k_{ijk} \Delta r_{ij} + k_{kji} \Delta r_{jk}) (\Theta - \Theta_0) \f$
         * where the two distinct force constants account for the asymmetric coupling between the two bonds and
         * the central angle.
         */
        class MMFF94StretchBendInteraction
        {

          public:
            /**
             * \brief Constructs the stretch-bend interaction record.
             * \param term_atom1_idx The zero-based index of the first terminal atom \e i.
             * \param ctr_atom_idx The zero-based index of the central atom \e j.
             * \param term_atom2_idx The zero-based index of the second terminal atom \e k.
             * \param sb_type_idx The MMFF94 stretch-bend type index (0-11).
             * \param ref_angle The reference angle \f$ \Theta_0 \f$ (in degrees).
             * \param ref_length1 The reference length \f$ r_{ij,0} \f$ of bond \e i-\e j.
             * \param ref_length2 The reference length \f$ r_{jk,0} \f$ of bond \e j-\e k.
             * \param ijk_force_const The force constant \f$ k_{ijk} \f$ coupling \e i-\e j stretching to the angle.
             * \param kji_force_const The force constant \f$ k_{kji} \f$ coupling \e j-\e k stretching to the angle.
             */
            MMFF94StretchBendInteraction(std::size_t term_atom1_idx, std::size_t ctr_atom_idx, std::size_t term_atom2_idx,
                                         unsigned int sb_type_idx, double ref_angle, double ref_length1, double ref_length2,
                                         double ijk_force_const, double kji_force_const):
                termAtom1Idx(term_atom1_idx),
                ctrAtomIdx(ctr_atom_idx), termAtom2Idx(term_atom2_idx),
                sbTypeIdx(sb_type_idx), refAngle(ref_angle), refLength1(ref_length1), refLength2(ref_length2),
                ijkForceConst(ijk_force_const), kjiForceConst(kji_force_const) {}

            /**
             * \brief Returns the zero-based index of the first terminal atom \e i.
             * \return The first terminal-atom index.
             */
            std::size_t getTerminalAtom1Index() const
            {
                return termAtom1Idx;
            }

            /**
             * \brief Returns the zero-based index of the central atom \e j.
             * \return The center-atom index.
             */
            std::size_t getCenterAtomIndex() const
            {
                return ctrAtomIdx;
            }

            /**
             * \brief Returns the zero-based index of the second terminal atom \e k.
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
             * \brief Returns the zero-based index of the central atom (alias for getCenterAtomIndex()).
             * \return The center-atom index.
             */
            std::size_t getAtom2Index() const
            {
                return ctrAtomIdx;
            }

            /**
             * \brief Returns the zero-based index of the second terminal atom (alias for getTerminalAtom2Index()).
             * \return The second terminal-atom index.
             */
            std::size_t getAtom3Index() const
            {
                return termAtom2Idx;
            }

            /**
             * \brief Returns the MMFF94 stretch-bend type index.
             * \return The stretch-bend type index (0-11).
             */
            unsigned int getStretchBendTypeIndex() const
            {
                return sbTypeIdx;
            }

            /**
             * \brief Returns the force constant coupling \e i-\e j bond stretching with the central angle.
             * \return The force constant \f$ k_{ijk} \f$.
             */
            double getIJKForceConstant() const
            {
                return ijkForceConst;
            }

            /**
             * \brief Returns the force constant coupling \e j-\e k bond stretching with the central angle.
             * \return The force constant \f$ k_{kji} \f$.
             */
            double getKJIForceConstant() const
            {
                return kjiForceConst;
            }

            /**
             * \brief Returns the reference angle.
             * \return The reference angle \f$ \Theta_0 \f$ (in degrees).
             */
            double getReferenceAngle() const
            {
                return refAngle;
            }

            /**
             * \brief Sets the reference angle.
             * \param angle The new reference angle \f$ \Theta_0 \f$ (in degrees).
             */
            void setReferenceAngle(double angle)
            {
                refAngle = angle;
            }

            /**
             * \brief Returns the reference length of bond \e i-\e j.
             * \return The reference length \f$ r_{ij,0} \f$.
             */
            double getReferenceLength1() const
            {
                return refLength1;
            }

            /**
             * \brief Sets the reference length of bond \e i-\e j.
             * \param length The new reference length \f$ r_{ij,0} \f$.
             */
            void setReferenceLength1(double length)
            {
                refLength1 = length;
            }

            /**
             * \brief Returns the reference length of bond \e j-\e k.
             * \return The reference length \f$ r_{jk,0} \f$.
             */
            double getReferenceLength2() const
            {
                return refLength2;
            }

            /**
             * \brief Sets the reference length of bond \e j-\e k.
             * \param length The new reference length \f$ r_{jk,0} \f$.
             */
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
