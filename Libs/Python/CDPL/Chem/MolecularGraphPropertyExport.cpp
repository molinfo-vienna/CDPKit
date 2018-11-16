/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * MolecularGraphPropertyExport.cpp 
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

#include "CDPL/Chem/MolecularGraphProperty.hpp"
#include "CDPL/Base/LookupKey.hpp"

#include "NamespaceExports.hpp"


namespace 
{

	struct MolecularGraphProperty {};
}


void CDPLPythonChem::exportMolecularGraphProperties()
{
	using namespace boost;
	using namespace CDPL;

	python::class_<MolecularGraphProperty, boost::noncopyable>("MolecularGraphProperty", python::no_init)
		.def_readonly("NAME", &Chem::MolecularGraphProperty::NAME) 
		.def_readonly("COMPONENTS", &Chem::MolecularGraphProperty::COMPONENTS)
		.def_readonly("RINGS", &Chem::MolecularGraphProperty::RINGS)
		.def_readonly("SSSR", &Chem::MolecularGraphProperty::SSSR)
		.def_readonly("CYCLIC_SUBSTRUCTURE", &Chem::MolecularGraphProperty::CYCLIC_SUBSTRUCTURE)
		.def_readonly("AROMATIC_SUBSTRUCTURE", &Chem::MolecularGraphProperty::AROMATIC_SUBSTRUCTURE)
		.def_readonly("MATCH_CONSTRAINTS", &Chem::MolecularGraphProperty::MATCH_CONSTRAINTS)
		.def_readonly("MATCH_EXPRESSION", &Chem::MolecularGraphProperty::MATCH_EXPRESSION)
		.def_readonly("COMPONENT_GROUPS", &Chem::MolecularGraphProperty::COMPONENT_GROUPS)
		.def_readonly("TOPOLOGICAL_DISTANCE_MATRIX", &Chem::MolecularGraphProperty::TOPOLOGICAL_DISTANCE_MATRIX)
		.def_readonly("GEOMETRICAL_DISTANCE_MATRIX", &Chem::MolecularGraphProperty::GEOMETRICAL_DISTANCE_MATRIX)
		.def_readonly("STOICHIOMETRIC_NUMBER", &Chem::MolecularGraphProperty::STOICHIOMETRIC_NUMBER)
		.def_readonly("CONFORMATION_INDEX", &Chem::MolecularGraphProperty::CONFORMATION_INDEX)
		.def_readonly("CONFORMATION_ENERGIES", &Chem::MolecularGraphProperty::CONFORMATION_ENERGIES)
		.def_readonly("STRUCTURE_DATA", &Chem::MolecularGraphProperty::STRUCTURE_DATA)
		.def_readonly("HASH_CODE", &Chem::MolecularGraphProperty::HASH_CODE)
		.def_readonly("MDL_USER_INITIALS", &Chem::MolecularGraphProperty::MDL_USER_INITIALS)
		.def_readonly("MDL_PROGRAM_NAME", &Chem::MolecularGraphProperty::MDL_PROGRAM_NAME)
		.def_readonly("MDL_TIMESTAMP", &Chem::MolecularGraphProperty::MDL_TIMESTAMP)
		.def_readonly("MDL_REGISTRY_NUMBER", &Chem::MolecularGraphProperty::MDL_REGISTRY_NUMBER)
		.def_readonly("MDL_COMMENT", &Chem::MolecularGraphProperty::MDL_COMMENT)
		.def_readonly("MDL_CTAB_VERSION", &Chem::MolecularGraphProperty::MDL_CTAB_VERSION)
		.def_readonly("MDL_DIMENSIONALITY", &Chem::MolecularGraphProperty::MDL_DIMENSIONALITY) 
		.def_readonly("MDL_SCALING_FACTOR1", &Chem::MolecularGraphProperty::MDL_SCALING_FACTOR1)
		.def_readonly("MDL_SCALING_FACTOR2", &Chem::MolecularGraphProperty::MDL_SCALING_FACTOR2)
		.def_readonly("MDL_ENERGY", &Chem::MolecularGraphProperty::MDL_ENERGY)
		.def_readonly("MDL_CHIRAL_FLAG", &Chem::MolecularGraphProperty::MDL_CHIRAL_FLAG)
		.def_readonly("MOL2_CHARGE_TYPE", &Chem::MolecularGraphProperty::MOL2_CHARGE_TYPE)
		.def_readonly("MOL2_MOLECULE_TYPE", &Chem::MolecularGraphProperty::MOL2_MOLECULE_TYPE);
}
