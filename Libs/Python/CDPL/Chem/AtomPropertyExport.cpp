/* 
 * AtomPropertyExport.cpp 
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

#include "CDPL/Chem/AtomProperty.hpp"
#include "CDPL/Base/LookupKey.hpp"

#include "NamespaceExports.hpp"


namespace 
{

	struct AtomProperty {};
}


void CDPLPythonChem::exportAtomProperties()
{
	using namespace boost;
	using namespace CDPL;

	python::class_<AtomProperty, boost::noncopyable>("AtomProperty", python::no_init)
		.def_readonly("NAME", &Chem::AtomProperty::NAME)
		.def_readonly("SYMBOL", &Chem::AtomProperty::SYMBOL)
		.def_readonly("TYPE", &Chem::AtomProperty::TYPE)
		.def_readonly("FORMAL_CHARGE", &Chem::AtomProperty::FORMAL_CHARGE)
		.def_readonly("ISOTOPE", &Chem::AtomProperty::ISOTOPE)
		.def_readonly("RADICAL_TYPE", &Chem::AtomProperty::RADICAL_TYPE)
		.def_readonly("HYBRIDIZATION", &Chem::AtomProperty::HYBRIDIZATION) 
		.def_readonly("RING_FLAG", &Chem::AtomProperty::RING_FLAG)
		.def_readonly("AROMATICITY_FLAG", &Chem::AtomProperty::AROMATICITY_FLAG)
		.def_readonly("UNPAIRED_ELECTRON_COUNT", &Chem::AtomProperty::UNPAIRED_ELECTRON_COUNT)
		.def_readonly("IMPLICIT_HYDROGEN_COUNT", &Chem::AtomProperty::IMPLICIT_HYDROGEN_COUNT)
		.def_readonly("COORDINATES_2D", &Chem::AtomProperty::COORDINATES_2D)
		.def_readonly("COORDINATES_3D_ARRAY", &Chem::AtomProperty::COORDINATES_3D_ARRAY)
		.def_readonly("MORGAN_NUMBER", &Chem::AtomProperty::MORGAN_NUMBER)
		.def_readonly("CANONICAL_NUMBER", &Chem::AtomProperty::CANONICAL_NUMBER)
		.def_readonly("CIP_PRIORITY", &Chem::AtomProperty::CIP_PRIORITY)
		.def_readonly("SYMMETRY_CLASS", &Chem::AtomProperty::SYMMETRY_CLASS)
		.def_readonly("STEREO_DESCRIPTOR", &Chem::AtomProperty::STEREO_DESCRIPTOR)
		.def_readonly("STEREO_CENTER_FLAG", &Chem::AtomProperty::STEREO_CENTER_FLAG)
		.def_readonly("CIP_CONFIGURATION", &Chem::AtomProperty::CIP_CONFIGURATION)
		.def_readonly("MDL_PARITY", &Chem::AtomProperty::MDL_PARITY)
		.def_readonly("MDL_DB_STEREO_CARE_FLAG", &Chem::AtomProperty::MDL_DB_STEREO_CARE_FLAG)
		.def_readonly("SYBYL_TYPE", &Chem::AtomProperty::SYBYL_TYPE)
		.def_readonly("MOL2_NAME", &Chem::AtomProperty::MOL2_NAME)
		.def_readonly("MOL2_CHARGE", &Chem::AtomProperty::MOL2_CHARGE)
		.def_readonly("MOL2_SUBSTRUCTURE_ID", &Chem::AtomProperty::MOL2_SUBSTRUCTURE_ID)
		.def_readonly("MOL2_SUBSTRUCTURE_NAME", &Chem::AtomProperty::MOL2_SUBSTRUCTURE_NAME)
		.def_readonly("MOL2_SUBSTRUCTURE_SUBTYPE", &Chem::AtomProperty::MOL2_SUBSTRUCTURE_SUBTYPE)
		.def_readonly("MOL2_SUBSTRUCTURE_CHAIN", &Chem::AtomProperty::MOL2_SUBSTRUCTURE_CHAIN)
		.def_readonly("REACTION_CENTER_STATUS", &Chem::AtomProperty::REACTION_CENTER_STATUS)
		.def_readonly("ATOM_MAPPING_ID", &Chem::AtomProperty::ATOM_MAPPING_ID)
		.def_readonly("MATCH_CONSTRAINTS", &Chem::AtomProperty::MATCH_CONSTRAINTS)
		.def_readonly("MATCH_EXPRESSION", &Chem::AtomProperty::MATCH_EXPRESSION)
		.def_readonly("MATCH_EXPRESSION_STRING", &Chem::AtomProperty::MATCH_EXPRESSION_STRING)
		.def_readonly("COMPONENT_GROUP_ID", &Chem::AtomProperty::COMPONENT_GROUP_ID);
}
