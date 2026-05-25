/* 
 * MMFF94ElectrostaticInteraction.hpp 
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
 * \brief Definition of class CDPL::ForceField::MMFF94ElectrostaticInteraction.
 */

#ifndef CDPL_FORCEFIELD_MMFF94ELECTROSTATICINTERACTION_HPP
#define CDPL_FORCEFIELD_MMFF94ELECTROSTATICINTERACTION_HPP

#include <cstddef>


namespace CDPL
{

    namespace ForceField
    {

        /**
         * \brief A single MMFF94 electrostatic interaction between two non-bonded atoms.
         *
         * The MMFF94 electrostatic-energy contribution between two atoms with partial charges
         * \f$ q_i \f$ and \f$ q_j \f$ separated by distance \e r is
         * \f$ E_q = f \frac{q_i q_j}{\varepsilon (r + \delta)^n} \f$
         * where \e f is a scaling factor (e.g. 0.75 for 1-4 pairs), \f$ \varepsilon \f$ the dielectric
         * constant, \e n the distance exponent and \f$ \delta = 0.05 \f$ &Aring; the MMFF94 buffer.
         */
        class MMFF94ElectrostaticInteraction
        {

          public:
            /**
             * \brief Constructs the electrostatic interaction record.
             * \param atom1_idx The zero-based index of the first atom.
             * \param atom2_idx The zero-based index of the second atom.
             * \param atom1_chg The partial charge \f$ q_i \f$ of the first atom.
             * \param atom2_chg The partial charge \f$ q_j \f$ of the second atom.
             * \param scale_fact The scaling factor \e f applied to the energy contribution (e.g. 0.75 for 1-4 pairs).
             * \param de_const The dielectric constant \f$ \varepsilon \f$.
             * \param dist_expo The distance exponent \e n.
             */
            MMFF94ElectrostaticInteraction(std::size_t atom1_idx, std::size_t atom2_idx, double atom1_chg,
                                           double atom2_chg, double scale_fact, double de_const, double dist_expo):
                atom1Idx(atom1_idx),
                atom2Idx(atom2_idx), atom1Chg(atom1_chg), atom2Chg(atom2_chg),
                scaleFact(scale_fact), deConst(de_const), distExpo(dist_expo) {}

            /**
             * \brief Returns the zero-based index of the first atom.
             * \return The first atom index.
             */
            std::size_t getAtom1Index() const
            {
                return atom1Idx;
            }

            /**
             * \brief Returns the zero-based index of the second atom.
             * \return The second atom index.
             */
            std::size_t getAtom2Index() const
            {
                return atom2Idx;
            }

            /**
             * \brief Returns the partial charge of the first atom.
             * \return The charge \f$ q_i \f$.
             */
            double getAtom1Charge() const
            {
                return atom1Chg;
            }

            /**
             * \brief Returns the partial charge of the second atom.
             * \return The charge \f$ q_j \f$.
             */
            double getAtom2Charge() const
            {
                return atom2Chg;
            }

            /**
             * \brief Returns the scaling factor applied to the energy contribution.
             * \return The scaling factor \e f.
             */
            double getScalingFactor() const
            {
                return scaleFact;
            }

            /**
             * \brief Returns the dielectric constant used by this interaction.
             * \return The dielectric constant \f$ \varepsilon \f$.
             */
            double getDielectricConstant() const
            {
                return deConst;
            }

            /**
             * \brief Returns the distance exponent of the electrostatic potential.
             * \return The distance exponent \e n.
             */
            double getDistanceExponent() const
            {
                return distExpo;
            }

          private:
            std::size_t atom1Idx;
            std::size_t atom2Idx;
            double      atom1Chg;
            double      atom2Chg;
            double      scaleFact;
            double      deConst;
            double      distExpo;
        };
    } // namespace ForceField
} // namespace CDPL

#endif // CDPL_FORCEFIELD_MMFF94ELECTROSTATICINTERACTION_HPP
