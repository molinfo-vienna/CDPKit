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
 * \brief Definition of the class CDPL::ForceField::ElasticPotential.
 */

#ifndef CDPL_FORCEFIELD_ELASTICPOTENTIAL_HPP
#define CDPL_FORCEFIELD_ELASTICPOTENTIAL_HPP

#include <cstddef>

#include "CDPL/ForceField/APIPrefix.hpp"


namespace CDPL
{

    namespace ForceField
    {

        /*
         * \since 1.1
         */
        class CDPL_FORCEFIELD_API ElasticPotential
        {

          public:
            ElasticPotential(std::size_t atom1_idx, std::size_t atom2_idx, double force_const, double ref_length):
                atom1Idx(atom1_idx), atom2Idx(atom2_idx), forceConst(force_const), refLength(ref_length) {}

            std::size_t getAtom1Index() const
            {
                return atom1Idx;
            }

            std::size_t getAtom2Index() const
            {
                return atom2Idx;
            }

            double getForceConstant() const
            {
                return forceConst;
            }

            double getReferenceLength() const
            {
                return refLength;
            }

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
