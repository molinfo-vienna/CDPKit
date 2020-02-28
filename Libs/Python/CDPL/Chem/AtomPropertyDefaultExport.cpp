/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * AtomPropertyDefaultExport.cpp 
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


#include <boost/python.hpp>

#include "CDPL/Chem/AtomPropertyDefault.hpp"

#include "NamespaceExports.hpp"


namespace 
{

	struct AtomPropertyDefault {};
}


void CDPLPythonChem::exportAtomPropertyDefaults()
{
	using namespace boost;
	using namespace CDPL;

	python::class_<AtomPropertyDefault, boost::noncopyable>("AtomPropertyDefault", python::no_init)
		.def_readonly("SYMBOL", &Chem::AtomPropertyDefault::SYMBOL)
		.def_readonly("NAME", &Chem::AtomPropertyDefault::NAME)
		.def_readonly("FORMAL_CHARGE", &Chem::AtomPropertyDefault::FORMAL_CHARGE)
		.def_readonly("ISOTOPE", &Chem::AtomPropertyDefault::ISOTOPE)
		.def_readonly("UNPAIRED_ELECTRON_COUNT", &Chem::AtomPropertyDefault::UNPAIRED_ELECTRON_COUNT)
		.def_readonly("RADICAL_TYPE", &Chem::AtomPropertyDefault::RADICAL_TYPE)
		.def_readonly("TYPE", &Chem::AtomPropertyDefault::TYPE)
		.def_readonly("SYBYL_TYPE", &Chem::AtomPropertyDefault::SYBYL_TYPE)
		.def_readonly("REACTION_CENTER_STATUS", &Chem::AtomPropertyDefault::REACTION_CENTER_STATUS)
		.def_readonly("STEREO_DESCRIPTOR", &Chem::AtomPropertyDefault::STEREO_DESCRIPTOR)
		.def_readonly("COMPONENT_GROUP_ID", &Chem::AtomPropertyDefault::COMPONENT_GROUP_ID)
		.def_readonly("ATOM_MAPPING_ID", &Chem::AtomPropertyDefault::ATOM_MAPPING_ID)
		.def_readonly("MATCH_CONSTRAINTS", &Chem::AtomPropertyDefault::MATCH_CONSTRAINTS)
		.def_readonly("MOL2_NAME", &Chem::AtomPropertyDefault::MOL2_NAME)
		.def_readonly("MOL2_CHARGE", &Chem::AtomPropertyDefault::MOL2_CHARGE)
		.def_readonly("MDL_DB_STEREO_CARE_FLAG", &Chem::AtomPropertyDefault::MDL_DB_STEREO_CARE_FLAG);
}
