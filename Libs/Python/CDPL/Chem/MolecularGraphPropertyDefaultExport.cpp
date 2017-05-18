/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * MolecularGraphPropertyDefaultExport.cpp 
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

#include "CDPL/Chem/MolecularGraphPropertyDefault.hpp"

#include "NamespaceExports.hpp"


namespace 
{

	struct MolecularGraphPropertyDefault {};
}


void CDPLPythonChem::exportMolecularGraphPropertyDefaults()
{
	using namespace boost;
	using namespace CDPL;

	python::class_<MolecularGraphPropertyDefault, boost::noncopyable>("MolecularGraphPropertyDefault", python::no_init)
		.def_readonly("NAME", &Chem::MolecularGraphPropertyDefault::NAME)
		.def_readonly("STOICHIOMETRIC_NUMBER", &Chem::MolecularGraphPropertyDefault::STOICHIOMETRIC_NUMBER)
		.def_readonly("MATCH_CONSTRAINTS", &Chem::MolecularGraphPropertyDefault::MATCH_CONSTRAINTS)
		.def_readonly("MDL_CTAB_VERSION", &Chem::MolecularGraphPropertyDefault::MDL_CTAB_VERSION)
		.def_readonly("MDL_COMMENT", &Chem::MolecularGraphPropertyDefault::MDL_COMMENT)
		.def_readonly("MDL_PROGRAM_NAME", &Chem::MolecularGraphPropertyDefault::MDL_PROGRAM_NAME)
		.def_readonly("MDL_USER_INITIALS", &Chem::MolecularGraphPropertyDefault::MDL_USER_INITIALS)
		.def_readonly("MDL_DIMENSIONALITY", &Chem::MolecularGraphPropertyDefault::MDL_DIMENSIONALITY)
		.def_readonly("MDL_ENERGY", &Chem::MolecularGraphPropertyDefault::MDL_ENERGY)
		.def_readonly("MDL_CHIRAL_FLAG", &Chem::MolecularGraphPropertyDefault::MDL_CHIRAL_FLAG)
		.def_readonly("MDL_SCALING_FACTOR1", &Chem::MolecularGraphPropertyDefault::MDL_SCALING_FACTOR1)
		.def_readonly("MDL_SCALING_FACTOR2", &Chem::MolecularGraphPropertyDefault::MDL_SCALING_FACTOR2)
		.def_readonly("MOL2_MOLECULE_TYPE", &Chem::MolecularGraphPropertyDefault::MOL2_MOLECULE_TYPE)
		.def_readonly("MOL2_CHARGE_TYPE", &Chem::MolecularGraphPropertyDefault::MOL2_CHARGE_TYPE);
}
