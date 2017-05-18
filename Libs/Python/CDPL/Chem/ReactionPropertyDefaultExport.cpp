/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * ReactionPropertyDefaultExport.cpp 
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

#include "CDPL/Chem/ReactionPropertyDefault.hpp"

#include "NamespaceExports.hpp"


namespace 
{

	struct ReactionPropertyDefault {};
}


void CDPLPythonChem::exportReactionPropertyDefaults()
{
	using namespace boost;
	using namespace CDPL;

	python::class_<ReactionPropertyDefault, boost::noncopyable>("ReactionPropertyDefault", python::no_init)
		.def_readonly("NAME", &Chem::ReactionPropertyDefault::NAME)
		.def_readonly("MATCH_CONSTRAINTS", &Chem::ReactionPropertyDefault::MATCH_CONSTRAINTS)
		.def_readonly("MDL_RXN_FILE_VERSION", &Chem::ReactionPropertyDefault::MDL_RXN_FILE_VERSION)
		.def_readonly("MDL_COMMENT", &Chem::ReactionPropertyDefault::MDL_COMMENT)
		.def_readonly("MDL_PROGRAM_NAME", &Chem::ReactionPropertyDefault::MDL_PROGRAM_NAME)
		.def_readonly("MDL_USER_INITIALS", &Chem::ReactionPropertyDefault::MDL_USER_INITIALS);
}
