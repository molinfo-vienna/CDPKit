/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * ReactionPropertyDefault.cpp 
 *
 * This file is part of the Chemical Data Processing Toolkit
 *
 * Copyright (C) 2003-2020 Thomas A. Seidel <thomas.seidel@univie.ac.at>
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


#include "StaticInit.hpp"

#include "CDPL/Vis/ReactionPropertyDefault.hpp"
#include "CDPL/Vis/LayoutStyle.hpp"
#include "CDPL/Vis/LayoutDirection.hpp"
#include "CDPL/Vis/Alignment.hpp"
#include "CDPL/Vis/ArrowStyle.hpp"


namespace CDPL
{

	namespace Vis
	{

		namespace ReactionPropertyDefault
		{

			const unsigned int ARROW_STYLE                = ArrowStyle::REACTION_SOLID;
			const Color ARROW_COLOR                       = Color(0, 0, 0);
			const SizeSpecification ARROW_LENGTH          = SizeSpecification(35.0, true, true, true);
			const SizeSpecification ARROW_HEAD_LENGTH     = SizeSpecification(8.0, false, true, true);
			const SizeSpecification ARROW_HEAD_WIDTH      = SizeSpecification(5.0, false, true, true);
			const SizeSpecification ARROW_SHAFT_WIDTH     = SizeSpecification(0.0, false, true, true);
			const SizeSpecification ARROW_LINE_WIDTH      = SizeSpecification(1.0, false, true, true);
			const unsigned int COMPONENT_LAYOUT           = LayoutStyle::PACKED;
			const unsigned int COMPONENT_LAYOUT_DIRECTION = LayoutDirection::HORIZONTAL;
			const SizeSpecification COMPONENT_MARGIN      = SizeSpecification(5.0, false, true, true);
			const bool SHOW_REACTANTS                     = true;
			const bool SHOW_AGENTS                        = true;
			const bool SHOW_PRODUCTS                      = true;
			const unsigned int AGENT_ALIGNMENT            = Alignment::V_CENTER;
			const unsigned int AGENT_LAYOUT               = LayoutStyle::LINEAR;
			const unsigned int AGENT_LAYOUT_DIRECTION     = LayoutDirection::HORIZONTAL;
			const Color PLUS_SIGN_COLOR                   = Color(0, 0, 0);
			const SizeSpecification PLUS_SIGN_SIZE        = SizeSpecification(10.0, false, true, true);
			const SizeSpecification PLUS_SIGN_LINE_WIDTH  = SizeSpecification(3.0, false, true, true);
			const bool SHOW_PLUS_SIGNS                    = true;
		}

		void initReactionPropertyDefaults() {}
	}
}
