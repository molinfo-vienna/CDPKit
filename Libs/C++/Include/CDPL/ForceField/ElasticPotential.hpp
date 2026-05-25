/* 
 * ElasticPotential.hpp 
 *
 * This file is part of the Chemical Data Processing Toolkit
 *
 * Copyright (C) 2003 Thomas Seidel <thomas.seidel@univie.ac.at>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the s of the GNU Lesser General Public
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
 * \brief Definition of class CDPL::ForceField::ElasticPotential.
 */

#ifndef CDPL_FORCEFIELD_ELASTICPOTENTIAL_HPP
#define CDPL_FORCEFIELD_ELASTICPOTENTIAL_HPP

#include <cstddef>


namespace CDPL
{

    namespace ForceField
    {

        /**
         * \brief Harmonic distance-restraint potential between a pair of atoms.
         *
         * The potential evaluates to \f$ \frac{1}{2} k (r - r_0)^2 \f$, where \e k is the force constant,
         * \f$ r_0 \f$ the reference length and \e r the current distance between the two atoms. It is used
         * by ForceField::MMFF94EnergyCalculator/ForceField::MMFF94GradientCalculator as an auxiliary restraint
         * to bias the energy minimization toward a desired geometry.
         *
         * \since 1.1
         */
        class ElasticPotential
        {

          public:
            /**
             * \brief Constructs the elastic potential between atoms \a atom1_idx and \a atom2_idx with the specified force constant and reference length.
             * \param atom1_idx The zero-based index of the first restrained atom.
             * \param atom2_idx The zero-based index of the second restrained atom.
             * \param force_const The force constant \e k of the harmonic potential.
             * \param ref_length The reference length \f$ r_0 \f$ of the harmonic potential.
             */
            ElasticPotential(std::size_t atom1_idx, std::size_t atom2_idx, double force_const, double ref_length):
                atom1Idx(atom1_idx), atom2Idx(atom2_idx), forceConst(force_const), refLength(ref_length) {}

            /**
             * \brief Returns the zero-based index of the first restrained atom.
             * \return The first atom index.
             */
            std::size_t getAtom1Index() const
            {
                return atom1Idx;
            }

            /**
             * \brief Returns the zero-based index of the second restrained atom.
             * \return The second atom index.
             */
            std::size_t getAtom2Index() const
            {
                return atom2Idx;
            }

            /**
             * \brief Returns the force constant of the potential.
             * \return The force constant \e k.
             */
            double getForceConstant() const
            {
                return forceConst;
            }

            /**
             * \brief Returns the reference length of the potential.
             * \return The reference length \f$ r_0 \f$.
             */
            double getReferenceLength() const
            {
                return refLength;
            }

            /**
             * \brief Sets the reference length of the potential.
             * \param length The new reference length \f$ r_0 \f$.
             */
            void setReferenceLength(double length)
            {
                refLength = length;
            }

          private:
            std::size_t  atom1Idx;
            std::size_t  atom2Idx;
            double       forceConst;
            double       refLength;
        };
    } // namespace ForceField
} // namespace CDPL

#endif // CDPL_FORCEFIELD_ELASTICPOTENTIAL_HPP
