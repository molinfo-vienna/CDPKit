/* 
 * MMFF94BondStretchingInteraction.hpp 
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
 * \brief Definition of class CDPL::ForceField::MMFF94BondStretchingInteraction.
 */

#ifndef CDPL_FORCEFIELD_MMFF94BONDSTRETCHINGINTERACTION_HPP
#define CDPL_FORCEFIELD_MMFF94BONDSTRETCHINGINTERACTION_HPP

#include <cstddef>


namespace CDPL
{

    namespace ForceField
    {

        /**
         * \brief Store parameters for a single MMFF94 bond-stretching interaction between two bonded atoms.
         */
        class MMFF94BondStretchingInteraction
        {

          public:
            /**
             * \brief Constructs the bond-stretching interaction parameter set.
             * \param atom1_idx The zero-based index of the first bonded atom.
             * \param atom2_idx The zero-based index of the second bonded atom.
             * \param bond_type_idx The MMFF94 bond type index (0 or 1).
             * \param force_const The bond-stretching force constant.
             * \param ref_length The reference bond length \f$ r_0 \f$.
             */
            MMFF94BondStretchingInteraction(std::size_t atom1_idx, std::size_t atom2_idx, unsigned int bond_type_idx,
                                            double force_const, double ref_length):
                atom1Idx(atom1_idx),
                atom2Idx(atom2_idx), bondTypeIdx(bond_type_idx), forceConst(force_const), refLength(ref_length) {}

            /**
             * \brief Returns the zero-based index of the first bonded atom.
             * \return The first atom index.
             */
            std::size_t getAtom1Index() const
            {
                return atom1Idx;
            }

            /**
             * \brief Returns the zero-based index of the second bonded atom.
             * \return The second atom index.
             */
            std::size_t getAtom2Index() const
            {
                return atom2Idx;
            }

            /**
             * \brief Returns the MMFF94 bond type index of this bond.
             * \return The bond type index (0 or 1).
             */
            unsigned int getBondTypeIndex() const
            {
                return bondTypeIdx;
            }

            /**
             * \brief Returns the bond-stretching force constant.
             * \return The force constant.
             */
            double getForceConstant() const
            {
                return forceConst;
            }

            /**
             * \brief Returns the reference bond length.
             * \return The reference bond length \f$ r_0 \f$.
             */
            double getReferenceLength() const
            {
                return refLength;
            }

            /**
             * \brief Sets the reference bond length.
             * \param length The new reference bond length \f$ r_0 \f$.
             */
            void setReferenceLength(double length)
            {
                refLength = length;
            }

          private:
            std::size_t  atom1Idx;
            std::size_t  atom2Idx;
            unsigned int bondTypeIdx;
            double       forceConst;
            double       refLength;
        };
    } // namespace ForceField
} // namespace CDPL

#endif // CDPL_FORCEFIELD_MMFF94BONDSTRETCHINGINTERACTION_HPP
