/* 
 * ReactionRole.hpp 
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
 * \brief Definition of constants in namespace CDPL::Chem::ReactionRole.
 */

#ifndef CDPL_CHEM_REACTIONROLE_HPP
#define CDPL_CHEM_REACTIONROLE_HPP


namespace CDPL
{

    namespace Chem
    {

        /**
         * \brief Provides constants that are used to specify the role of molecules (components) in
         *        a chemical reaction.
         */
        namespace ReactionRole
        {

            /**
             * \brief Specifies that a molecule is not a reaction component.
             */
            constexpr unsigned int NONE = 0x0;

            /**
             * \brief Specifies the reactants of a reaction.
             */
            constexpr unsigned int REACTANT = 0x1;

            /**
             * \brief Specifies the agents of a reaction (e.g. solvent or catalyst).
             */
            constexpr unsigned int AGENT = 0x2;

            /**
             * \brief Equivalent to ReactionRole::AGENT.
             */
            constexpr unsigned int CATALYST = AGENT;

            /**
             * \brief Specifies the products of a reaction.
             */
            constexpr unsigned int PRODUCT = 0x4;

            /**
             * \brief Specifies reactants, agents and products of a reaction.
             */
            constexpr unsigned int ALL = REACTANT | AGENT | PRODUCT;
        } // namespace ReactionRole
    } // namespace Chem
} // namespace CDPL

#endif // CDPL_CHEM_REACTIONROLE_HPP
