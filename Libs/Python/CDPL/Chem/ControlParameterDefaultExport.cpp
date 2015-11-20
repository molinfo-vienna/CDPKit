/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * ControlParameterDefaultExport.cpp 
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

#include "CDPL/Chem/ControlParameterDefault.hpp"

#include "NamespaceExports.hpp"


namespace 
{

	struct ControlParameterDefault {};
}


void CDPLPythonChem::exportControlParameterDefaults()
{
	using namespace boost;
	using namespace CDPL;

	python::class_<ControlParameterDefault, boost::noncopyable>("ControlParameterDefault", python::no_init)
		.def_readonly("STRICT_ERROR_CHECKING", &Chem::ControlParameterDefault::STRICT_ERROR_CHECKING)
		.def_readonly("ORDINARY_HYDROGEN_DEPLETE", &Chem::ControlParameterDefault::ORDINARY_HYDROGEN_DEPLETE)
		.def_readonly("BOND_MEMBER_SWAP_STEREO_FIX", &Chem::ControlParameterDefault::BOND_MEMBER_SWAP_STEREO_FIX)
		.def_readonly("RECORD_SEPARATOR", &Chem::ControlParameterDefault::RECORD_SEPARATOR)
		.def_readonly("JME_SEPARATE_COMPONENTS", &Chem::ControlParameterDefault::JME_SEPARATE_COMPONENTS)
		.def_readonly("COORDINATES_DIMENSION", &Chem::ControlParameterDefault::COORDINATES_DIMENSION)
		.def_readonly("INCHI_INPUT_OPTIONS", &Chem::ControlParameterDefault::INCHI_INPUT_OPTIONS)
		.def_readonly("INCHI_OUTPUT_OPTIONS", &Chem::ControlParameterDefault::INCHI_OUTPUT_OPTIONS)
		.def_readonly("CHECK_LINE_LENGTH", &Chem::ControlParameterDefault::CHECK_LINE_LENGTH)
		.def_readonly("MDL_IGNORE_PARITY", &Chem::ControlParameterDefault::MDL_IGNORE_PARITY)
		.def_readonly("MDL_TRIM_STRINGS", &Chem::ControlParameterDefault::MDL_TRIM_STRINGS)
		.def_readonly("MDL_TRIM_LINES", &Chem::ControlParameterDefault::MDL_TRIM_LINES)
		.def_readonly("MDL_TRUNCATE_STRINGS", &Chem::ControlParameterDefault::MDL_TRUNCATE_STRINGS)
		.def_readonly("MDL_TRUNCATE_LINESS", &Chem::ControlParameterDefault::MDL_TRUNCATE_LINES)
		.def_readonly("MDL_UPDATE_TIMESTAMP", &Chem::ControlParameterDefault::MDL_UPDATE_TIMESTAMP)
		.def_readonly("MDL_CTAB_VERSION", &Chem::ControlParameterDefault::MDL_CTAB_VERSION)
		.def_readonly("MDL_RXN_FILE_VERSION", &Chem::ControlParameterDefault::MDL_RXN_FILE_VERSION)
		.def_readonly("SMILES_RECORD_FORMAT", &Chem::ControlParameterDefault::SMILES_RECORD_FORMAT)
		.def_readonly("SMILES_WRITE_CANONICAL_FORM", &Chem::ControlParameterDefault::SMILES_WRITE_CANONICAL_FORM)
		.def_readonly("SMILES_WRITE_KEKULE_FORM", &Chem::ControlParameterDefault::SMILES_WRITE_KEKULE_FORM)
		.def_readonly("SMILES_WRITE_ATOM_STEREO", &Chem::ControlParameterDefault::SMILES_WRITE_ATOM_STEREO)
		.def_readonly("SMILES_WRITE_BOND_STEREO", &Chem::ControlParameterDefault::SMILES_WRITE_BOND_STEREO)
		.def_readonly("SMILES_WRITE_RING_BOND_STEREO", &Chem::ControlParameterDefault::SMILES_WRITE_RING_BOND_STEREO)
		.def_readonly("SMILES_MIN_STEREO_BOND_RING_SIZE", &Chem::ControlParameterDefault::SMILES_MIN_STEREO_BOND_RING_SIZE)
		.def_readonly("SMILES_WRITE_ISOTOPE", &Chem::ControlParameterDefault::SMILES_WRITE_ISOTOPE)
		.def_readonly("SMILES_RXN_WRITE_ATOM_MAPPING_ID", &Chem::ControlParameterDefault::SMILES_RXN_WRITE_ATOM_MAPPING_ID)
		.def_readonly("SMILES_MOL_WRITE_ATOM_MAPPING_ID", &Chem::ControlParameterDefault::SMILES_MOL_WRITE_ATOM_MAPPING_ID)
		.def_readonly("SMILES_WRITE_SINGLE_BONDS", &Chem::ControlParameterDefault::SMILES_WRITE_SINGLE_BONDS)
		.def_readonly("SMILES_WRITE_AROMATIC_BONDS", &Chem::ControlParameterDefault::SMILES_WRITE_AROMATIC_BONDS)
		.def_readonly("SMILES_NO_ORGANIC_SUBSET", &Chem::ControlParameterDefault::SMILES_NO_ORGANIC_SUBSET)
		.def_readonly("MULTI_CONF_IMPORT", &Chem::ControlParameterDefault::MULTI_CONF_IMPORT)
		.def_readonly("MULTI_CONF_EXPORT", &Chem::ControlParameterDefault::MULTI_CONF_EXPORT)
		.def_readonly("MULTI_CONF_INPUT_PROCESSOR", &Chem::ControlParameterDefault::MULTI_CONF_INPUT_PROCESSOR);
}
