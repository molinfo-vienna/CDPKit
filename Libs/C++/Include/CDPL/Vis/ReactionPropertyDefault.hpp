/* 
 * ReactionPropertyDefault.hpp 
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
 * \brief Definition of constants in namespace CDPL::Vis::ReactionPropertyDefault.
 */

#ifndef CDPL_VIS_REACTIONPROPERTYDEFAULT_HPP
#define CDPL_VIS_REACTIONPROPERTYDEFAULT_HPP

#include "CDPL/Vis/APIPrefix.hpp"
#include "CDPL/Vis/Color.hpp"
#include "CDPL/Vis/Font.hpp"
#include "CDPL/Vis/SizeSpecification.hpp"


namespace CDPL
{

    namespace Vis
    {

        /**
         * \brief Provides default values for built-in Chem::Reaction properties.
         */
        namespace ReactionPropertyDefault
        {

            extern CDPL_VIS_API const unsigned int      ARROW_STYLE;
            extern CDPL_VIS_API const Color             ARROW_COLOR;
            extern CDPL_VIS_API const SizeSpecification ARROW_LENGTH;
            extern CDPL_VIS_API const SizeSpecification ARROW_HEAD_LENGTH;
            extern CDPL_VIS_API const SizeSpecification ARROW_HEAD_WIDTH;
            extern CDPL_VIS_API const SizeSpecification ARROW_SHAFT_WIDTH;
            extern CDPL_VIS_API const SizeSpecification ARROW_LINE_WIDTH;
            extern CDPL_VIS_API const unsigned int      COMPONENT_LAYOUT;
            extern CDPL_VIS_API const unsigned int      COMPONENT_LAYOUT_DIRECTION;
            extern CDPL_VIS_API const SizeSpecification COMPONENT_MARGIN;
            extern CDPL_VIS_API const bool              SHOW_REACTANTS;
            extern CDPL_VIS_API const bool              SHOW_AGENTS;
            extern CDPL_VIS_API const bool              SHOW_PRODUCTS;
            extern CDPL_VIS_API const unsigned int      AGENT_ALIGNMENT;
            extern CDPL_VIS_API const unsigned int      AGENT_LAYOUT;
            extern CDPL_VIS_API const unsigned int      AGENT_LAYOUT_DIRECTION;
            extern CDPL_VIS_API const Color             PLUS_SIGN_COLOR;
            extern CDPL_VIS_API const SizeSpecification PLUS_SIGN_SIZE;
            extern CDPL_VIS_API const SizeSpecification PLUS_SIGN_LINE_WIDTH;
            extern CDPL_VIS_API const bool              SHOW_PLUS_SIGNS;
        } // namespace ReactionPropertyDefault
    } // namespace Vis
} // namespace CDPL

#endif // CDPL_VIS_REACTIONPROPERTYDEFAULT_HPP
