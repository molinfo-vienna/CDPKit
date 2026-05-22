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

        /**
         * \brief A single MMFF94 angle-bending interaction defined over an atom triplet.
         *
         * Stores the indices of the central atom plus the two terminal atoms, the MMFF94 angle-type index,
         * a linear-angle flag, the harmonic force constant and the reference angle. For non-linear angles the
         * MMFF94 angle-bending energy is the cubic-bend form
         * \f$ E_a = \frac{1}{2} k_a (\Theta - \Theta_0)^2 (1 + c_b (\Theta - \Theta_0)) \f$;
         * for linear angles the cosine-form \f$ E_a = k_a (1 + \cos\Theta) \f$ is used (evaluated by the calculator).
         */
        class MMFF94AngleBendingInteraction
        {

          public:
            /**
             * \brief Constructs the angle-bending interaction record.
             * \param term_atom1_idx The zero-based index of the first terminal atom.
             * \param ctr_atom_idx The zero-based index of the central (vertex) atom.
             * \param term_atom2_idx The zero-based index of the second terminal atom.
             * \param angle_type_idx The MMFF94 angle-type index (0-8).
             * \param linear \c true if the equilibrium angle is treated as linear (180&deg;).
             * \param force_const The angle-bending force constant.
             * \param ref_angle The reference angle \f$ \Theta_0 \f$ (in degrees).
             */
            MMFF94AngleBendingInteraction(std::size_t term_atom1_idx, std::size_t ctr_atom_idx, std::size_t term_atom2_idx,
                                          unsigned int angle_type_idx, bool linear, double force_const, double ref_angle):
                termAtom1Idx(term_atom1_idx),
                ctrAtomIdx(ctr_atom_idx), termAtom2Idx(term_atom2_idx),
                angleTypeIdx(angle_type_idx), linear(linear), forceConst(force_const), refAngle(ref_angle) {}

            /**
             * \brief Returns the zero-based index of the first terminal atom.
             * \return The first terminal-atom index.
             */
            std::size_t getTerminalAtom1Index() const
            {
                return termAtom1Idx;
            }

            /**
             * \brief Returns the zero-based index of the central (vertex) atom.
             * \return The center-atom index.
             */
            std::size_t getCenterAtomIndex() const
            {
                return ctrAtomIdx;
            }

            /**
             * \brief Returns the zero-based index of the second terminal atom.
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
             * \brief Returns the MMFF94 angle-type index.
             * \return The angle-type index (0-8).
             */
            unsigned int getAngleTypeIndex() const
            {
                return angleTypeIdx;
            }

            /**
             * \brief Tells whether the equilibrium angle is treated as linear.
             * \return \c true if the angle is linear, and \c false otherwise.
             */
            bool isLinearAngle() const
            {
                return linear;
            }

            /**
             * \brief Returns the angle-bending force constant.
             * \return The force constant.
             */
            double getForceConstant() const
            {
                return forceConst;
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
