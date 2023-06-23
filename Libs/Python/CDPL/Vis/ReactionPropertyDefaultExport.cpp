/* 
 * ReactionPropertyDefaultExport.cpp 
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

#include "CDPL/Vis/ReactionPropertyDefault.hpp"

#include "NamespaceExports.hpp"


namespace 
{

    struct ReactionPropertyDefault {};
}


void CDPLPythonVis::exportReactionPropertyDefaults()
{
    using namespace boost;
    using namespace CDPL;

    python::class_<ReactionPropertyDefault, boost::noncopyable>("ReactionPropertyDefault", python::no_init)
        .def_readonly("ARROW_STYLE", &Vis::ReactionPropertyDefault::ARROW_STYLE)
        .def_readonly("ARROW_COLOR", &Vis::ReactionPropertyDefault::ARROW_COLOR)
        .def_readonly("ARROW_LENGTH", &Vis::ReactionPropertyDefault::ARROW_LENGTH)
        .def_readonly("ARROW_HEAD_LENGTH", &Vis::ReactionPropertyDefault::ARROW_HEAD_LENGTH)
        .def_readonly("ARROW_HEAD_WIDTH", &Vis::ReactionPropertyDefault::ARROW_HEAD_WIDTH)
        .def_readonly("ARROW_SHAFT_WIDTH", &Vis::ReactionPropertyDefault::ARROW_SHAFT_WIDTH)
        .def_readonly("ARROW_LINE_WIDTH", &Vis::ReactionPropertyDefault::ARROW_LINE_WIDTH)
        .def_readonly("COMPONENT_LAYOUT", &Vis::ReactionPropertyDefault::COMPONENT_LAYOUT)
        .def_readonly("COMPONENT_LAYOUT_DIRECTION", &Vis::ReactionPropertyDefault::COMPONENT_LAYOUT_DIRECTION)
        .def_readonly("COMPONENT_MARGIN", &Vis::ReactionPropertyDefault::COMPONENT_MARGIN)
        .def_readonly("SHOW_REACTANTS", &Vis::ReactionPropertyDefault::SHOW_REACTANTS)
        .def_readonly("SHOW_AGENTS", &Vis::ReactionPropertyDefault::SHOW_AGENTS)
        .def_readonly("SHOW_PRODUCTS", &Vis::ReactionPropertyDefault::SHOW_PRODUCTS)
        .def_readonly("AGENT_ALIGNMENT", &Vis::ReactionPropertyDefault::AGENT_ALIGNMENT)
        .def_readonly("AGENT_LAYOUT", &Vis::ReactionPropertyDefault::AGENT_LAYOUT)
        .def_readonly("AGENT_LAYOUT_DIRECTION", &Vis::ReactionPropertyDefault::AGENT_LAYOUT_DIRECTION)
        .def_readonly("PLUS_SIGN_COLOR", &Vis::ReactionPropertyDefault::PLUS_SIGN_COLOR)
        .def_readonly("PLUS_SIGN_SIZE", &Vis::ReactionPropertyDefault::PLUS_SIGN_SIZE)
        .def_readonly("PLUS_SIGN_LINE_WIDTH", &Vis::ReactionPropertyDefault::PLUS_SIGN_LINE_WIDTH)
        .def_readonly("SHOW_PLUS_SIGNS", &Vis::ReactionPropertyDefault::SHOW_PLUS_SIGNS);
}
