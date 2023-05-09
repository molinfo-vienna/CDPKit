/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

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

#include "CDPL/Biomol/AtomProperty.hpp"
#include "CDPL/Base/LookupKey.hpp"

#include "NamespaceExports.hpp"


namespace 
{

	struct AtomProperty {};
}


void CDPLPythonBiomol::exportAtomProperties()
{
	using namespace boost;
	using namespace CDPL;

	python::class_<AtomProperty, boost::noncopyable>("AtomProperty", python::no_init)
		.def_readonly("RESIDUE_ATOM_NAME", &Biomol::AtomProperty::RESIDUE_ATOM_NAME)
		.def_readonly("RESIDUE_ALT_ATOM_NAME", &Biomol::AtomProperty::RESIDUE_ALT_ATOM_NAME)
		.def_readonly("RESIDUE_LEAVING_ATOM_FLAG", &Biomol::AtomProperty::RESIDUE_LEAVING_ATOM_FLAG)
		.def_readonly("RESIDUE_LINKING_ATOM_FLAG", &Biomol::AtomProperty::RESIDUE_LINKING_ATOM_FLAG)
		.def_readonly("RESIDUE_CODE", &Biomol::AtomProperty::RESIDUE_CODE)
		.def_readonly("RESIDUE_SEQUENCE_NUMBER", &Biomol::AtomProperty::RESIDUE_SEQUENCE_NUMBER)
		.def_readonly("RESIDUE_INSERTION_CODE", &Biomol::AtomProperty::RESIDUE_INSERTION_CODE)
		.def_readonly("HETERO_ATOM_FLAG", &Biomol::AtomProperty::HETERO_ATOM_FLAG)
		.def_readonly("CHAIN_ID", &Biomol::AtomProperty::CHAIN_ID)
		.def_readonly("ALT_LOCATION_ID", &Biomol::AtomProperty::ALT_LOCATION_ID)
		.def_readonly("MODEL_NUMBER", &Biomol::AtomProperty::MODEL_NUMBER)
		.def_readonly("SERIAL_NUMBER", &Biomol::AtomProperty::SERIAL_NUMBER)
		.def_readonly("OCCUPANCY", &Biomol::AtomProperty::OCCUPANCY)
		.def_readonly("B_FACTOR", &Biomol::AtomProperty::B_FACTOR);
}
