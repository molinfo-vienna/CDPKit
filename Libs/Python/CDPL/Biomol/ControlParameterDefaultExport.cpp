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

#include "CDPL/Biomol/ControlParameterDefault.hpp"

#include "NamespaceExports.hpp"


namespace 
{

    struct ControlParameterDefault {};
}


void CDPLPythonBiomol::exportControlParameterDefaults()
{
    using namespace boost;
    using namespace CDPL;

    python::class_<ControlParameterDefault, boost::noncopyable>("ControlParameterDefault", python::no_init)
        .def_readonly("STRICT_ERROR_CHECKING", &Biomol::ControlParameterDefault::STRICT_ERROR_CHECKING)
        .def_readonly("CHECK_LINE_LENGTH", &Biomol::ControlParameterDefault::CHECK_LINE_LENGTH)
        .def_readonly("RESIDUE_DICTIONARY", &Biomol::ControlParameterDefault::RESIDUE_DICTIONARY)
        .def_readonly("COMBINE_INTERFERING_RESIDUE_COORDINATES", &Biomol::ControlParameterDefault::COMBINE_INTERFERING_RESIDUE_COORDINATES)
        .def_readonly("APPLY_DICT_FORMAL_CHARGES", &Biomol::ControlParameterDefault::APPLY_DICT_FORMAL_CHARGES)
        .def_readonly("APPLY_DICT_ATOM_TYPES", &Biomol::ControlParameterDefault::APPLY_DICT_ATOM_TYPES)
        .def_readonly("CALC_MISSING_FORMAL_CHARGES", &Biomol::ControlParameterDefault::CALC_MISSING_FORMAL_CHARGES)
        .def_readonly("PERCEIVE_MISSING_BOND_ORDERS", &Biomol::ControlParameterDefault::PERCEIVE_MISSING_BOND_ORDERS)
        .def_readonly("PDB_APPLY_DICT_ATOM_BONDING_TO_NON_STD_RESIDUES", &Biomol::ControlParameterDefault::PDB_APPLY_DICT_ATOM_BONDING_TO_NON_STD_RESIDUES)
        .def_readonly("PDB_APPLY_DICT_ATOM_BONDING_TO_STD_RESIDUES", &Biomol::ControlParameterDefault::PDB_APPLY_DICT_ATOM_BONDING_TO_STD_RESIDUES)
        .def_readonly("PDB_APPLY_DICT_BOND_ORDERS_TO_NON_STD_RESIDUES", &Biomol::ControlParameterDefault::PDB_APPLY_DICT_BOND_ORDERS_TO_NON_STD_RESIDUES)
        .def_readonly("PDB_IGNORE_CONECT_RECORDS", &Biomol::ControlParameterDefault::PDB_IGNORE_CONECT_RECORDS)
        .def_readonly("PDB_DEDUCE_BOND_ORDERS_FROM_CONECT_RECORDS", &Biomol::ControlParameterDefault::PDB_DEDUCE_BOND_ORDERS_FROM_CONECT_RECORDS)
        .def_readonly("PDB_IGNORE_FORMAL_CHARGE_FIELD", &Biomol::ControlParameterDefault::PDB_IGNORE_FORMAL_CHARGE_FIELD)
        .def_readonly("PDB_EVALUATE_MASTER_RECORD", &Biomol::ControlParameterDefault::PDB_EVALUATE_MASTER_RECORD)
        .def_readonly("PDB_TRUNCATE_LINES", &Biomol::ControlParameterDefault::PDB_TRUNCATE_LINES)
        .def_readonly("PDB_WRITE_FORMAL_CHARGES", &Biomol::ControlParameterDefault::PDB_WRITE_FORMAL_CHARGES)
        .def_readonly("PDB_WRITE_CONECT_RECORDS", &Biomol::ControlParameterDefault::PDB_WRITE_CONECT_RECORDS)
        .def_readonly("PDB_WRITE_CONECT_RECORDS_FOR_ALL_BONDS", &Biomol::ControlParameterDefault::PDB_WRITE_CONECT_RECORDS_FOR_ALL_BONDS)
        .def_readonly("PDB_WRITE_CONECT_RECORDS_REFLECTING_BOND_ORDER", &Biomol::ControlParameterDefault::PDB_WRITE_CONECT_RECORDS_REFLECTING_BOND_ORDER)
        .def_readonly("PDB_FORMAT_VERSION", &Biomol::ControlParameterDefault::PDB_FORMAT_VERSION)
        .def_readonly("MMCIF_APPLY_DICT_ATOM_BONDING", &Biomol::ControlParameterDefault::MMCIF_APPLY_DICT_ATOM_BONDING)
        .def_readonly("MMCIF_APPLY_DICT_BOND_ORDERS", &Biomol::ControlParameterDefault::MMCIF_APPLY_DICT_BOND_ORDERS)
        .def_readonly("MMCIF_OUTPUT_BIOPOLYMERS_AS_CHEM_COMP", &Biomol::ControlParameterDefault::MMCIF_OUTPUT_BIOPOLYMERS_AS_CHEM_COMP)
        ;
}
