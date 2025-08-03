/* 
 * ControlParameterExport.cpp 
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

#include "CDPL/Chem/ControlParameter.hpp"
#include "CDPL/Base/LookupKey.hpp"

#include "NamespaceExports.hpp"


namespace 
{

    struct ControlParameter {};
}


void CDPLPythonChem::exportControlParameters()
{
    using namespace boost;
    using namespace CDPL;

    python::class_<ControlParameter, boost::noncopyable>("ControlParameter", python::no_init)
        .def_readonly("COORDINATES_DIMENSION", &Chem::ControlParameter::COORDINATES_DIMENSION)
        .def_readonly("ORDINARY_HYDROGEN_DEPLETE", &Chem::ControlParameter::ORDINARY_HYDROGEN_DEPLETE)
        .def_readonly("STRICT_ERROR_CHECKING", &Chem::ControlParameter::STRICT_ERROR_CHECKING)
        .def_readonly("BOND_MEMBER_SWAP_STEREO_FIX", &Chem::ControlParameter::BOND_MEMBER_SWAP_STEREO_FIX)
        .def_readonly("CHECK_LINE_LENGTH", &Chem::ControlParameter::CHECK_LINE_LENGTH)
        .def_readonly("RECORD_SEPARATOR", &Chem::ControlParameter::RECORD_SEPARATOR)
        .def_readonly("JME_SEPARATE_COMPONENTS", &Chem::ControlParameter::JME_SEPARATE_COMPONENTS)
        .def_readonly("MDL_CTAB_VERSION", &Chem::ControlParameter::MDL_CTAB_VERSION)
        .def_readonly("MDL_IGNORE_PARITY", &Chem::ControlParameter::MDL_IGNORE_PARITY)
        .def_readonly("MDL_RXN_FILE_VERSION", &Chem::ControlParameter::MDL_RXN_FILE_VERSION)
        .def_readonly("MDL_TRIM_LINES", &Chem::ControlParameter::MDL_TRIM_LINES)
        .def_readonly("MDL_TRIM_STRINGS", &Chem::ControlParameter::MDL_TRIM_STRINGS)
        .def_readonly("MDL_TRUNCATE_LINES", &Chem::ControlParameter::MDL_TRUNCATE_LINES)
        .def_readonly("MDL_TRUNCATE_STRINGS", &Chem::ControlParameter::MDL_TRUNCATE_STRINGS)
        .def_readonly("MDL_UPDATE_TIMESTAMP", &Chem::ControlParameter::MDL_UPDATE_TIMESTAMP)
        .def_readonly("MDL_OUTPUT_CONF_ENERGY_TO_ENERGY_FIELD", &Chem::ControlParameter::MDL_OUTPUT_CONF_ENERGY_TO_ENERGY_FIELD)
        .def_readonly("MDL_OUTPUT_CONF_ENERGY_AS_SD_ENTRY", &Chem::ControlParameter::MDL_OUTPUT_CONF_ENERGY_AS_SD_ENTRY)
        .def_readonly("MDL_CONF_ENERGY_SD_TAG", &Chem::ControlParameter::MDL_CONF_ENERGY_SD_TAG)
        .def_readonly("MDL_OUTPUT_AROMATIC_BOND_TYPES", &Chem::ControlParameter::MDL_OUTPUT_AROMATIC_BOND_TYPES)
        .def_readonly("SMILES_RECORD_FORMAT", &Chem::ControlParameter::SMILES_RECORD_FORMAT)
        .def_readonly("SMILES_MIN_STEREO_BOND_RING_SIZE", &Chem::ControlParameter::SMILES_MIN_STEREO_BOND_RING_SIZE)
        .def_readonly("SMILES_NO_ORGANIC_SUBSET", &Chem::ControlParameter::SMILES_NO_ORGANIC_SUBSET)
        .def_readonly("SMILES_OUTPUT_AROMATIC_BONDS", &Chem::ControlParameter::SMILES_OUTPUT_AROMATIC_BONDS)
        .def_readonly("SMILES_OUTPUT_ISOTOPE", &Chem::ControlParameter::SMILES_OUTPUT_ISOTOPE)
        .def_readonly("SMILES_OUTPUT_HYDROGEN_COUNT", &Chem::ControlParameter::SMILES_OUTPUT_HYDROGEN_COUNT)
        .def_readonly("SMILES_MOL_OUTPUT_ATOM_MAPPING_ID", &Chem::ControlParameter::SMILES_MOL_OUTPUT_ATOM_MAPPING_ID)
        .def_readonly("SMILES_RXN_OUTPUT_ATOM_MAPPING_ID", &Chem::ControlParameter::SMILES_RXN_OUTPUT_ATOM_MAPPING_ID)
        .def_readonly("SMILES_OUTPUT_ATOM_STEREO", &Chem::ControlParameter::SMILES_OUTPUT_ATOM_STEREO)
        .def_readonly("SMILES_OUTPUT_BOND_STEREO", &Chem::ControlParameter::SMILES_OUTPUT_BOND_STEREO)
        .def_readonly("SMILES_OUTPUT_CANONICAL_FORM", &Chem::ControlParameter::SMILES_OUTPUT_CANONICAL_FORM)
        .def_readonly("SMILES_OUTPUT_KEKULE_FORM", &Chem::ControlParameter::SMILES_OUTPUT_KEKULE_FORM)
        .def_readonly("SMILES_OUTPUT_RING_BOND_STEREO", &Chem::ControlParameter::SMILES_OUTPUT_RING_BOND_STEREO)
        .def_readonly("SMILES_OUTPUT_SINGLE_BONDS", &Chem::ControlParameter::SMILES_OUTPUT_SINGLE_BONDS)
        .def_readonly("INCHI_INPUT_OPTIONS", &Chem::ControlParameter::INCHI_INPUT_OPTIONS)
        .def_readonly("INCHI_OUTPUT_OPTIONS", &Chem::ControlParameter::INCHI_OUTPUT_OPTIONS)
        .def_readonly("MULTI_CONF_IMPORT", &Chem::ControlParameter::MULTI_CONF_IMPORT)
        .def_readonly("MULTI_CONF_EXPORT", &Chem::ControlParameter::MULTI_CONF_EXPORT)
        .def_readonly("MULTI_CONF_INPUT_PROCESSOR", &Chem::ControlParameter::MULTI_CONF_INPUT_PROCESSOR)
        .def_readonly("OUTPUT_CONF_ENERGY_AS_COMMENT", &Chem::ControlParameter::OUTPUT_CONF_ENERGY_AS_COMMENT)
        .def_readonly("CONF_INDEX_NAME_SUFFIX_PATTERN", &Chem::ControlParameter::CONF_INDEX_NAME_SUFFIX_PATTERN)
        .def_readonly("CDF_OUTPUT_SINGLE_PRECISION_FLOATS", &Chem::ControlParameter::CDF_OUTPUT_SINGLE_PRECISION_FLOATS)
        .def_readonly("MOL2_ENABLE_EXTENDED_ATOM_TYPES", &Chem::ControlParameter::MOL2_ENABLE_EXTENDED_ATOM_TYPES)
        .def_readonly("MOL2_ENABLE_AROMATIC_BOND_TYPES", &Chem::ControlParameter::MOL2_ENABLE_AROMATIC_BOND_TYPES)
        .def_readonly("MOL2_CALC_FORMAL_CHARGES", &Chem::ControlParameter::MOL2_CALC_FORMAL_CHARGES)
        .def_readonly("MOL2_CHARGE_TYPE", &Chem::ControlParameter::MOL2_CHARGE_TYPE)
        .def_readonly("MOL2_OUTPUT_SUBSTRUCTURES", &Chem::ControlParameter::MOL2_OUTPUT_SUBSTRUCTURES)
        .def_readonly("MOL2_MOLECULE_TYPE", &Chem::ControlParameter::MOL2_MOLECULE_TYPE)
        .def_readonly("MOL2_READ_PARTIAL_AS_FORMAL_CHARGES", &Chem::ControlParameter::MOL2_READ_PARTIAL_AS_FORMAL_CHARGES)
        .def_readonly("MOL2_OUTPUT_FORMAL_CHARGES", &Chem::ControlParameter::MOL2_OUTPUT_FORMAL_CHARGES)
        .def_readonly("COMMENT_IS_NAME", &Chem::ControlParameter::XYZ_COMMENT_IS_NAME)
        .def_readonly("XYZ_PERCEIVE_CONNECTIVITY", &Chem::ControlParameter::XYZ_PERCEIVE_CONNECTIVITY)
        .def_readonly("XYZ_PERCEIVE_BOND_ORDERS", &Chem::ControlParameter::XYZ_PERCEIVE_BOND_ORDERS)
        .def_readonly("XYZ_CALC_FORMAL_CHARGES", &Chem::ControlParameter::XYZ_CALC_FORMAL_CHARGES)
        .def_readonly("CML_OUTPUT_XML_DECLARATION", &Chem::ControlParameter::CML_OUTPUT_XML_DECLARATION)
        .def_readonly("CML_OUTPUT_ELEMENT_NAMESPACE", &Chem::ControlParameter::CML_OUTPUT_ELEMENT_NAMESPACE)
        .def_readonly("CML_OUTPUT_ATOM_PARITY", &Chem::ControlParameter::CML_OUTPUT_ATOM_PARITY)
        .def_readonly("CML_OUTPUT_SINGLE_BOND_STEREO", &Chem::ControlParameter::CML_OUTPUT_SINGLE_BOND_STEREO)
        .def_readonly("CML_OUTPUT_DOUBLE_BOND_STEREO", &Chem::ControlParameter::CML_OUTPUT_DOUBLE_BOND_STEREO)
        .def_readonly("CML_OUTPUT_KEKULE_FORM", &Chem::ControlParameter::CML_OUTPUT_KEKULE_FORM)
        .def_readonly("CML_OUTPUT_MOLECULE_NAME", &Chem::ControlParameter::CML_OUTPUT_MOLECULE_NAME)
        .def_readonly("CML_OUTPUT_STRUCTURE_DATA", &Chem::ControlParameter::CML_OUTPUT_STRUCTURE_DATA)
        .def_readonly("CML_OUTPUT_ISOTOPE", &Chem::ControlParameter::CML_OUTPUT_ISOTOPE)
        .def_readonly("CML_OUTPUT_SPIN_MULTIPLICITY", &Chem::ControlParameter::CML_OUTPUT_SPIN_MULTIPLICITY)
        .def_readonly("CML_OUTPUT_COMPACT_ATOM_DATA", &Chem::ControlParameter::CML_OUTPUT_COMPACT_ATOM_DATA)
        .def_readonly("CML_OUTPUT_COMPACT_BOND_DATA", &Chem::ControlParameter::CML_OUTPUT_COMPACT_BOND_DATA);
}
