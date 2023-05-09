/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * ReactionPropertyExport.cpp 
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


#include <boost/python.hpp>

#include "CDPL/Vis/ReactionProperty.hpp"
#include "CDPL/Base/LookupKey.hpp"

#include "NamespaceExports.hpp"


namespace 
{

	struct ReactionProperty {};
}


void CDPLPythonVis::exportReactionProperties()
{
	using namespace boost;
	using namespace CDPL;

	python::class_<ReactionProperty, boost::noncopyable>("ReactionProperty", python::no_init)
		.def_readonly("AGENT_ALIGNMENT", &Vis::ReactionProperty::AGENT_ALIGNMENT)
		.def_readonly("AGENT_LAYOUT", &Vis::ReactionProperty::AGENT_LAYOUT)
		.def_readonly("AGENT_LAYOUT_DIRECTION", &Vis::ReactionProperty::AGENT_LAYOUT_DIRECTION)
		.def_readonly("ARROW_COLOR", &Vis::ReactionProperty::ARROW_COLOR)
		.def_readonly("ARROW_HEAD_LENGTH", &Vis::ReactionProperty::ARROW_HEAD_LENGTH)
		.def_readonly("ARROW_HEAD_WIDTH", &Vis::ReactionProperty::ARROW_HEAD_WIDTH)
		.def_readonly("ARROW_LENGTH", &Vis::ReactionProperty::ARROW_LENGTH)
		.def_readonly("ARROW_LINE_WIDTH", &Vis::ReactionProperty::ARROW_LINE_WIDTH)
		.def_readonly("ARROW_SHAFT_WIDTH", &Vis::ReactionProperty::ARROW_SHAFT_WIDTH)
		.def_readonly("ARROW_STYLE", &Vis::ReactionProperty::ARROW_STYLE)
		.def_readonly("COMPONENT_LAYOUT", &Vis::ReactionProperty::COMPONENT_LAYOUT)
		.def_readonly("COMPONENT_LAYOUT_DIRECTION", &Vis::ReactionProperty::COMPONENT_LAYOUT_DIRECTION)
		.def_readonly("COMPONENT_MARGIN", &Vis::ReactionProperty::COMPONENT_MARGIN)
		.def_readonly("SHOW_REACTANTS", &Vis::ReactionProperty::SHOW_REACTANTS)
		.def_readonly("SHOW_AGENTS", &Vis::ReactionProperty::SHOW_AGENTS)
		.def_readonly("SHOW_PRODUCTS", &Vis::ReactionProperty::SHOW_PRODUCTS)
		.def_readonly("PLUS_SIGN_COLOR", &Vis::ReactionProperty::PLUS_SIGN_COLOR)
		.def_readonly("PLUS_SIGN_LINE_WIDTH", &Vis::ReactionProperty::PLUS_SIGN_LINE_WIDTH)
		.def_readonly("PLUS_SIGN_SIZE", &Vis::ReactionProperty::PLUS_SIGN_SIZE)
		.def_readonly("SHOW_PLUS_SIGNS", &Vis::ReactionProperty::SHOW_PLUS_SIGNS);
}
