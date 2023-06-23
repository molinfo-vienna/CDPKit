/* 
 * ReactionProperty.cpp 
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


#include "StaticInit.hpp"

#include "CDPL/Vis/ReactionProperty.hpp"

#include "CDPL/Base/LookupKeyDefinition.hpp"


namespace CDPL
{

	namespace Vis
	{

		namespace ReactionProperty
		{

			CDPL_DEFINE_LOOKUP_KEY(ARROW_STYLE);
			CDPL_DEFINE_LOOKUP_KEY(ARROW_COLOR);
			CDPL_DEFINE_LOOKUP_KEY(ARROW_LENGTH);
			CDPL_DEFINE_LOOKUP_KEY(ARROW_HEAD_LENGTH);
			CDPL_DEFINE_LOOKUP_KEY(ARROW_HEAD_WIDTH);
			CDPL_DEFINE_LOOKUP_KEY(ARROW_SHAFT_WIDTH);
			CDPL_DEFINE_LOOKUP_KEY(ARROW_LINE_WIDTH);
			CDPL_DEFINE_LOOKUP_KEY(COMPONENT_LAYOUT);
			CDPL_DEFINE_LOOKUP_KEY(COMPONENT_LAYOUT_DIRECTION);
			CDPL_DEFINE_LOOKUP_KEY(COMPONENT_MARGIN);
			CDPL_DEFINE_LOOKUP_KEY(SHOW_REACTANTS);
			CDPL_DEFINE_LOOKUP_KEY(SHOW_AGENTS);
			CDPL_DEFINE_LOOKUP_KEY(SHOW_PRODUCTS);
			CDPL_DEFINE_LOOKUP_KEY(AGENT_ALIGNMENT);
			CDPL_DEFINE_LOOKUP_KEY(AGENT_LAYOUT);
			CDPL_DEFINE_LOOKUP_KEY(AGENT_LAYOUT_DIRECTION);
			CDPL_DEFINE_LOOKUP_KEY(PLUS_SIGN_COLOR);
			CDPL_DEFINE_LOOKUP_KEY(PLUS_SIGN_SIZE);
			CDPL_DEFINE_LOOKUP_KEY(PLUS_SIGN_LINE_WIDTH);
			CDPL_DEFINE_LOOKUP_KEY(SHOW_PLUS_SIGNS);
		}

		void initReactionProperties() {}
	}
}
