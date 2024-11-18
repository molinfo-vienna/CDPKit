/* 
 * ControlParameterDefaultExport.cpp 
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
        .def_readonly("MDL_OUTPUT_CONF_ENERGY_TO_ENERGY_FIELD", &Chem::ControlParameterDefault::MDL_OUTPUT_CONF_ENERGY_TO_ENERGY_FIELD)
        .def_readonly("MDL_OUTPUT_CONF_ENERGY_AS_SD_ENTRY", &Chem::ControlParameterDefault::MDL_OUTPUT_CONF_ENERGY_AS_SD_ENTRY)
        .def_readonly("MDL_CONF_ENERGY_SD_TAG", &Chem::ControlParameterDefault::MDL_CONF_ENERGY_SD_TAG)
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
        .def_readonly("MULTI_CONF_INPUT_PROCESSOR", &Chem::ControlParameterDefault::MULTI_CONF_INPUT_PROCESSOR)
        .def_readonly("OUTPUT_CONF_ENERGY_AS_COMMENT", &Chem::ControlParameterDefault::OUTPUT_CONF_ENERGY_AS_COMMENT)
        .def_readonly("CONF_INDEX_NAME_SUFFIX_PATTERN", &Chem::ControlParameterDefault::CONF_INDEX_NAME_SUFFIX_PATTERN)
        .def_readonly("CDF_WRITE_SINGLE_PRECISION_FLOATS", &Chem::ControlParameterDefault::CDF_WRITE_SINGLE_PRECISION_FLOATS)
        .def_readonly("MOL2_ENABLE_EXTENDED_ATOM_TYPES", &Chem::ControlParameterDefault::MOL2_ENABLE_EXTENDED_ATOM_TYPES)
        .def_readonly("MOL2_ENABLE_AROMATIC_BOND_TYPES", &Chem::ControlParameterDefault::MOL2_ENABLE_AROMATIC_BOND_TYPES)
        .def_readonly("MOL2_CALC_FORMAL_CHARGES", &Chem::ControlParameterDefault::MOL2_CALC_FORMAL_CHARGES)
        .def_readonly("MOL2_CHARGE_TYPE", &Chem::ControlParameterDefault::MOL2_CHARGE_TYPE)
        .def_readonly("MOL2_MOLECULE_TYPE", &Chem::ControlParameterDefault::MOL2_MOLECULE_TYPE)
        .def_readonly("MOL2_OUTPUT_SUBSTRUCTURES", &Chem::ControlParameterDefault::MOL2_OUTPUT_SUBSTRUCTURES)
        .def_readonly("COMMENT_IS_NAME", &Chem::ControlParameterDefault::XYZ_COMMENT_IS_NAME)
        .def_readonly("XYZ_PERCEIVE_CONNECTIVITY", &Chem::ControlParameterDefault::XYZ_PERCEIVE_CONNECTIVITY)
        .def_readonly("XYZ_PERCEIVE_BOND_ORDERS", &Chem::ControlParameterDefault::XYZ_PERCEIVE_BOND_ORDERS)
        .def_readonly("XYZ_CALC_FORMAL_CHARGES", &Chem::ControlParameterDefault::XYZ_CALC_FORMAL_CHARGES)
        .def_readonly("CML_OUTPUT_XML_DECLARATION", &Chem::ControlParameterDefault::CML_OUTPUT_XML_DECLARATION)
        .def_readonly("CML_OUTPUT_ELEMENT_NAMESPACE", &Chem::ControlParameterDefault::CML_OUTPUT_ELEMENT_NAMESPACE)
        .def_readonly("CML_OUTPUT_ATOM_PARITY", &Chem::ControlParameterDefault::CML_OUTPUT_ATOM_PARITY)
        .def_readonly("CML_OUTPUT_SINGLE_BOND_STEREO", &Chem::ControlParameterDefault::CML_OUTPUT_SINGLE_BOND_STEREO)
        .def_readonly("CML_OUTPUT_DOUBLE_BOND_STEREO", &Chem::ControlParameterDefault::CML_OUTPUT_DOUBLE_BOND_STEREO)
        .def_readonly("CML_OUTPUT_BOND_AROMATICITY", &Chem::ControlParameterDefault::CML_OUTPUT_BOND_AROMATICITY)
        .def_readonly("CML_OUTPUT_MOLECULE_NAME", &Chem::ControlParameterDefault::CML_OUTPUT_MOLECULE_NAME)
        .def_readonly("CML_OUTPUT_STRUCTURE_DATA", &Chem::ControlParameterDefault::CML_OUTPUT_STRUCTURE_DATA)
        .def_readonly("CML_OUTPUT_ISOTOPE", &Chem::ControlParameterDefault::CML_OUTPUT_ISOTOPE)
        .def_readonly("CML_OUTPUT_SPIN_MULTIPLICITY", &Chem::ControlParameterDefault::CML_OUTPUT_SPIN_MULTIPLICITY)
        .def_readonly("CML_OUTPUT_COMPACT_ATOM_DATA", &Chem::ControlParameterDefault::CML_OUTPUT_COMPACT_ATOM_DATA)
        .def_readonly("CML_OUTPUT_COMPACT_BOND_DATA", &Chem::ControlParameterDefault::CML_OUTPUT_COMPACT_BOND_DATA);
}
