/* 
 * BondMatchConstraint.hpp 
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
 * \brief Definition of constants in namespace CDPL::Chem::BondMatchConstraint.
 */

#ifndef CDPL_CHEM_BONDMATCHCONSTRAINT_HPP
#define CDPL_CHEM_BONDMATCHCONSTRAINT_HPP


namespace CDPL
{

    namespace Chem
    {

        /**
         * \brief Provides numerical identifiers for built-in Chem::Bond matching constraints and flags for the
         *        specification of bond orders.
         */
        namespace BondMatchConstraint
        {

            /**
             * \brief Specifies a single bond.
             */
            const unsigned int SINGLE = 0x1;

            /**
             * \brief Specifies a double bond.
             */
            const unsigned int DOUBLE = 0x2;

            /**
             * \brief Specifies a triple bond.
             */
            const unsigned int TRIPLE = 0x4;

            /**
             * \brief Specifies an aromatic bond with delocalized electrons.
             */
            const unsigned int AROMATIC = 0x8;

            /**
             * \brief Specifies that the target bond must have the specified order even if the bond
             *        is aromatic.
             */
            const unsigned int IGNORE_AROMATICITY = 0x10;

            /**
             * \brief Specifies a bond of any order.
             */
            const unsigned int ANY_ORDER = SINGLE | DOUBLE | TRIPLE | AROMATIC;

            /**
             * \brief Specifies a constraint which requires the target bond to fulfill additional contraints
             *        specified by a Chem::MatchConstraintList object.
             */
            const unsigned int CONSTRAINT_LIST = 0;

            /**
             * \brief Specifies a constraint on the order of the target bond.
             */
            const unsigned int ORDER = 1;

            /**
             * \brief Specifies a constraint on the aromaticity of the target bond.
             */
            const unsigned int AROMATICITY = 2;

            /**
             * \brief Specifies a constraint on the ring-membership of the target bond.
             */
            const unsigned int RING_TOPOLOGY = 3;

            /**
             * \brief Specifies a constraint on the steric configuration of the target bond.
             */
            const unsigned int CONFIGURATION = 4;

            /**
             * \brief Specifies a constraint on the steric configuration of the target bond that is defined by
             *        the relative direction of attached bonds.
             * \see Chem::BondDirection
             */
            const unsigned int DIRECTION_CONFIG = 5;

            /**
             * \brief Specifies a constraint on the relative direction of the target bond.
             * \see Chem::BondDirection
             */
            const unsigned int DIRECTION = 6;

            /**
             * \brief Specifies a constraint on the reaction center status of the target bond.
             * \see Chem::ReactionCenterStatus
             */
            const unsigned int REACTION_CENTER_STATUS = 7;
        } // namespace BondMatchConstraint
    } // namespace Chem
} // namespace CDPL

#endif // CDPL_CHEM_BONDMATCHCONSTRAINT_HPP
