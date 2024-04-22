/* 
 * AtomMatchConstraint.hpp 
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
 * \brief Definition of constants in namespace CDPL::Chem::AtomMatchConstraint.
 */

#ifndef CDPL_CHEM_ATOMMATCHCONSTRAINT_HPP
#define CDPL_CHEM_ATOMMATCHCONSTRAINT_HPP


namespace CDPL
{

    namespace Chem
    {

        /**
         * \brief Provides numerical identifiers for built-in Chem::Atom matching constraints.
         */
        namespace AtomMatchConstraint
        {

            /**
             * \brief Specifies a constraint which requires the target atom to fulfill additional constraints
             *        specified by a Chem::MatchConstraintList object.
             */
            constexpr unsigned int CONSTRAINT_LIST = 0;

            /**
             * \brief Specifies a constraint on the type of the target atom.
             */
            constexpr unsigned int TYPE = 1;

            /**
             * \brief Specifies a constraint on the structural environment of the target atom.
             */
            constexpr unsigned int ENVIRONMENT = 2;

            /**
             * \brief Specifies a constraint on the isotopic mass of the target atom.
             */
            constexpr unsigned int ISOTOPE = 3;

            /**
             * \brief Specifies a constraint on the fromal charge of the target atom.
             */
            constexpr unsigned int CHARGE = 4;

            /**
             * \brief Specifies a constraint on the ring bond count of the target atom.
             */
            constexpr unsigned int RING_BOND_COUNT = 5;

            /**
             * \brief Specifies a constraint on the total hydrogen count of the target atom.
             */
            constexpr unsigned int H_COUNT = 6;

            /**
             * \brief Specifies a constraint on the implicit hydrogen count of the target atom.
             */
            constexpr unsigned int IMPLICIT_H_COUNT = 7;

            /**
             * \brief Specifies a constraint on the explicit hydrogen count of the target atom.
             */
            constexpr unsigned int EXPLICIT_H_COUNT = 8;

            /**
             * \brief Specifies a constraint on the total bond count of the target atom.
             */
            constexpr unsigned int BOND_COUNT = 9;

            /**
             * \brief Specifies a constraint on the explicit bond count of the target atom.
             */
            constexpr unsigned int EXPLICIT_BOND_COUNT = 10;

            /**
             * \brief Specifies a constraint on the heavy bond count of the target atom.
             */
            constexpr unsigned int HEAVY_BOND_COUNT = 11;

            /**
             * \brief Specifies a constraint on the valence of the target atom.
             */
            constexpr unsigned int VALENCE = 12;

            /**
             * \brief Specifies a constraint on the explicit valence of the target atom.
             */
            constexpr unsigned int EXPLICIT_VALENCE = 13;

            /**
             * \brief Specifies a constraint on the aromaticity of the target atom.
             */
            constexpr unsigned int AROMATICITY = 14;

            /**
             * \brief Specifies a constraint on the ring-membership of the target atom.
             */
            constexpr unsigned int RING_TOPOLOGY = 15;

            /**
             * \brief Specifies a constraint on the steric configuration of the target atom.
             */
            constexpr unsigned int CONFIGURATION = 16;

            /**
             * \brief Specifies a constraint on the (non-)membership of the target atom in a double or triple bond.
             */
            constexpr unsigned int UNSATURATION = 17;

            /**
             * \brief Specifies a constraint on the number of rings (from the SSSR) the target atom is a member of.
             */
            constexpr unsigned int SSSR_RING_COUNT = 18;

            /**
             * \brief Specifies a constraint on the size of the rings (from the SSSR) the target atom is a member of.
             */
            constexpr unsigned int SSSR_RING_SIZE = 19;

            /**
             * \brief Specifies a constraint on the hybridization state of the target atom.
             */
            constexpr unsigned int HYBRIDIZATION_STATE = 20;
        } // namespace AtomMatchConstraint
    } // namespace Chem
} // namespace CDPL

#endif // CDPL_CHEM_ATOMMATCHCONSTRAINT_HPP
