/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * ReactionFunctionExport.cpp 
 *
 * This file is part of the Chemical Data Processing Toolkit
 *
 * Copyright (C) 2003-2010 Thomas A. Seidel <thomas.seidel@univie.ac.at>
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

#include "CDPL/Chem/Reaction.hpp"
#include "CDPL/Vis/ReactionFunctions.hpp"
#include "CDPL/Vis/Color.hpp"
#include "CDPL/Vis/SizeSpecification.hpp"

#include "FunctionExports.hpp"


#define MAKE_REACTION_FUNC_WRAPPERS(TYPE, FUNC_SUFFIX)     \
TYPE get##FUNC_SUFFIX##Wrapper(CDPL::Chem::Reaction& rxn)  \
{                                                          \
	return CDPL::Vis::get##FUNC_SUFFIX(rxn);			   \
}                                                          \
                                                           \
bool has##FUNC_SUFFIX##Wrapper(CDPL::Chem::Reaction& rxn)  \
{                                                          \
	return CDPL::Vis::has##FUNC_SUFFIX(rxn);			   \
}

#define EXPORT_REACTION_FUNCS_INT_REF(FUNC_SUFFIX, ARG_NAME)                                                \
python::def("get"#FUNC_SUFFIX, &get##FUNC_SUFFIX##Wrapper, python::arg("rxn"),                              \
            python::return_internal_reference<1>());                                                        \
python::def("has"#FUNC_SUFFIX, &has##FUNC_SUFFIX##Wrapper, python::arg("rxn"));                             \
python::def("clear"#FUNC_SUFFIX, &Vis::clear##FUNC_SUFFIX, python::arg("rxn"));                             \
python::def("set"#FUNC_SUFFIX, &Vis::set##FUNC_SUFFIX, (python::arg("rxn"), python::arg(#ARG_NAME))); 

#define EXPORT_REACTION_FUNCS(FUNC_SUFFIX, ARG_NAME)                                                        \
python::def("get"#FUNC_SUFFIX, &get##FUNC_SUFFIX##Wrapper, python::arg("rxn"));                             \
python::def("has"#FUNC_SUFFIX, &has##FUNC_SUFFIX##Wrapper, python::arg("rxn"));                             \
python::def("clear"#FUNC_SUFFIX, &Vis::clear##FUNC_SUFFIX, python::arg("rxn"));                             \
python::def("set"#FUNC_SUFFIX, &Vis::set##FUNC_SUFFIX, (python::arg("rxn"), python::arg(#ARG_NAME))); 


namespace
{

	MAKE_REACTION_FUNC_WRAPPERS(unsigned int, ArrowStyle)
	MAKE_REACTION_FUNC_WRAPPERS(const CDPL::Vis::Color&, ArrowColor)
	MAKE_REACTION_FUNC_WRAPPERS(const CDPL::Vis::SizeSpecification&, ArrowLength)
	MAKE_REACTION_FUNC_WRAPPERS(const CDPL::Vis::SizeSpecification&, ArrowHeadLength)
	MAKE_REACTION_FUNC_WRAPPERS(const CDPL::Vis::SizeSpecification&, ArrowHeadWidth)
	MAKE_REACTION_FUNC_WRAPPERS(const CDPL::Vis::SizeSpecification&, ArrowShaftWidth)
	MAKE_REACTION_FUNC_WRAPPERS(const CDPL::Vis::SizeSpecification&, ArrowLineWidth)
	MAKE_REACTION_FUNC_WRAPPERS(unsigned int, ComponentLayout)
	MAKE_REACTION_FUNC_WRAPPERS(unsigned int, ComponentLayoutDirection)
	MAKE_REACTION_FUNC_WRAPPERS(const CDPL::Vis::SizeSpecification&, ComponentMargin)
	MAKE_REACTION_FUNC_WRAPPERS(bool, ShowReactants)
	MAKE_REACTION_FUNC_WRAPPERS(bool, ShowAgents)
	MAKE_REACTION_FUNC_WRAPPERS(bool, ShowProducts)
	MAKE_REACTION_FUNC_WRAPPERS(unsigned int, AgentAlignment)
	MAKE_REACTION_FUNC_WRAPPERS(unsigned int, AgentLayout)
	MAKE_REACTION_FUNC_WRAPPERS(unsigned int, AgentLayoutDirection)
	MAKE_REACTION_FUNC_WRAPPERS(const CDPL::Vis::Color&, PlusSignColor)
	MAKE_REACTION_FUNC_WRAPPERS(const CDPL::Vis::SizeSpecification&, PlusSignSize)
	MAKE_REACTION_FUNC_WRAPPERS(const CDPL::Vis::SizeSpecification&, PlusSignLineWidth)
	MAKE_REACTION_FUNC_WRAPPERS(bool, ShowPlusSigns)
}


void CDPLPythonVis::exportReactionFunctions()
{
	using namespace boost;
	using namespace CDPL;

	EXPORT_REACTION_FUNCS(ArrowStyle, style)
	EXPORT_REACTION_FUNCS_INT_REF(ArrowColor, color)
	EXPORT_REACTION_FUNCS_INT_REF(ArrowLength, length)
	EXPORT_REACTION_FUNCS_INT_REF(ArrowHeadLength, length)
	EXPORT_REACTION_FUNCS_INT_REF(ArrowHeadWidth, width)
	EXPORT_REACTION_FUNCS_INT_REF(ArrowShaftWidth, width)
	EXPORT_REACTION_FUNCS_INT_REF(ArrowLineWidth, width)
	EXPORT_REACTION_FUNCS(ComponentLayout, layout)
	EXPORT_REACTION_FUNCS(ComponentLayoutDirection, dir)
	EXPORT_REACTION_FUNCS_INT_REF(ComponentMargin, margin)
	EXPORT_REACTION_FUNCS(ShowReactants, show)
	EXPORT_REACTION_FUNCS(ShowAgents, show)
	EXPORT_REACTION_FUNCS(ShowProducts, show)
	EXPORT_REACTION_FUNCS(AgentAlignment, show)
	EXPORT_REACTION_FUNCS(AgentLayout, show)
	EXPORT_REACTION_FUNCS(AgentLayoutDirection, dir)
	EXPORT_REACTION_FUNCS_INT_REF(PlusSignColor, color)
	EXPORT_REACTION_FUNCS_INT_REF(PlusSignSize, size)
	EXPORT_REACTION_FUNCS_INT_REF(PlusSignLineWidth, width)
	EXPORT_REACTION_FUNCS(ShowPlusSigns, show)
}
